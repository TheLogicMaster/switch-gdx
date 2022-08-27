package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.utils.IntMap;
import com.badlogic.gdx.utils.Pool;
import com.badlogic.gdx.utils.ReflectionPool;

public class SwitchSound implements Sound {

	private static class SoundInstance {
		int channel;
		boolean looping;
	}

	private long handle;

	private final IntMap<SoundInstance> instanceMap = new IntMap<>();
	private boolean disposed;
	private int id;
	private final Pool<SoundInstance> soundPool = new ReflectionPool<>(SoundInstance.class, 32);

	public SwitchSound (FileHandle file) {
		create(file.file().getPath());
	}

	boolean update() {
		return disposed;
	}

	void onSoundFinished(int channel) {
		IntMap.Entry<SoundInstance> instanceEntry = null;
		for (IntMap.Entry<SoundInstance> entry: instanceMap.entries())
			if (entry.value.channel == channel) {
				instanceEntry = entry;
				break;
			}
		if (instanceEntry == null || instanceEntry.value.looping)
			return;
		soundPool.free(instanceMap.remove(instanceEntry.key));
	}

	private long play(float volume, float pitch, float pan, boolean looping) {
		int channel = play0(looping);
		setVolume0(channel, volume);
		setPitch0(channel, pitch);
		setPan0(channel, pan);
		SoundInstance instance = soundPool.obtain();
		instanceMap.put(id, instance);
		instance.channel = channel;
		instance.looping = looping;
		return id++;
	}

	@Override
	public long play () {
		return play(1);
	}

	@Override
	public long play (float volume) {
		return play(volume, 1, 0);
	}

	@Override
	public long play (float volume, float pitch, float pan) {
		return play(volume, pitch, pan, false);
	}

	@Override
	public long loop () {
		return loop(1);
	}

	@Override
	public long loop (float volume) {
		return loop(volume, 1, 0);
	}

	@Override
	public long loop (float volume, float pitch, float pan) {
		return play(volume, pitch, pan, true);
	}

	@Override
	public void stop () {
		for (IntMap.Entry<SoundInstance> entry : new IntMap.Entries<SoundInstance>(instanceMap)) {
			stop0(entry.value.channel);
			soundPool.free(entry.value);
		}
		instanceMap.clear();
	}

	@Override
	public void pause () {
		for (IntMap.Entry<SoundInstance> entry : new IntMap.Entries<SoundInstance>(instanceMap))
			pause0(entry.value.channel);
	}

	@Override
	public void resume () {
		for (IntMap.Entry<SoundInstance> entry : new IntMap.Entries<SoundInstance>(instanceMap))
			resume0(entry.value.channel);
	}

	@Override
	public void dispose () {
		if (disposed)
			return;

		stop();
		dispose0();
		disposed = true;
	}

	@Override
	public void stop (long soundId) {
		if (instanceMap.containsKey((int)soundId)) {
			stop0(instanceMap.get((int)soundId, null).channel);
			SoundInstance removed = instanceMap.remove((int)soundId);
			soundPool.free(removed);
		}
	}

	@Override
	public void pause (long soundId) {
		if (instanceMap.containsKey((int)soundId))
			pause0(instanceMap.get((int)soundId).channel);
	}

	@Override
	public void resume (long soundId) {
		if (instanceMap.containsKey((int)soundId))
			resume0(instanceMap.get((int)soundId).channel);
	}

	@Override
	public void setLooping (long soundId, boolean looping) {
		// It's not possible to change looping flag, so restart sound...
		SoundInstance instance = instanceMap.get((int)soundId);
		if (instance != null && instance.looping != looping) {
			setLooping0(instance.channel, looping);
			instance.looping = looping;
		}
	}

	@Override
	public void setPitch (long soundId, float pitch) {
		// Todo: Actually implement effect
		if (instanceMap.containsKey((int)soundId))
			setPitch0(instanceMap.get((int)soundId).channel, pitch);
	}

	@Override
	public void setVolume (long soundId, float volume) {
		if (instanceMap.containsKey((int)soundId))
			setVolume0(instanceMap.get((int)soundId).channel, volume);
	}

	@Override
	public void setPan (long soundId, float pan, float volume) {
		if (instanceMap.containsKey((int)soundId)) {
			int channel = instanceMap.get((int)soundId).channel;
			setPan0(channel, pan);
			setVolume0(channel, volume);
		}
	}

	private native void create(String path);

	private native void dispose0();

	private native int play0(boolean looping);

	private native void setLooping0(int channel, boolean looping);

	private static native void stop0(int channel);

	private static native void pause0(int channel);

	private static native void resume0(int channel);

	private static native void setPitch0(int channel, float pitch);

	private static native void setVolume0(int channel, float volume);

	private static native void setPan0(int channel, float pan);
}
