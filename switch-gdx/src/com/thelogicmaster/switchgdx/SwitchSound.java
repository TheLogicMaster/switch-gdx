package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.utils.IntIntMap;

public class SwitchSound implements Sound {

	private long handle;

	private final IntIntMap channelMap = new IntIntMap();
	private boolean disposed;
	private int id;

	public SwitchSound (FileHandle file) {
		create(file.file().getPath());
	}

	boolean update() {
		return disposed;
	}

	void onSoundFinished(int channel) {
		channelMap.remove(channel, 0);
	}

	private long play(float volume, float pitch, float pan, boolean looping) {
		int channel = play0(looping);
		setVolume0(channel, volume);
		setPitch0(channel, pitch);
		setPan0(channel, pan);
		channelMap.put(id++, channel);
		return channel;
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
		for (IntIntMap.Entry entry : new IntIntMap.Entries(channelMap))
			stop0(entry.value);
		channelMap.clear();
	}

	@Override
	public void pause () {
		for (IntIntMap.Entry entry: new IntIntMap.Entries(channelMap))
			pause0(entry.value);
	}

	@Override
	public void resume () {
		for (IntIntMap.Entry entry: new IntIntMap.Entries(channelMap))
			resume0(entry.value);
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
		if (channelMap.containsKey((int)soundId)) {
			stop0(channelMap.get((int)soundId, -1));
			channelMap.remove((int)soundId, 0);
		}
	}

	@Override
	public void pause (long soundId) {
		if (channelMap.containsKey((int)soundId))
			pause0(channelMap.get((int)soundId, -1));
	}

	@Override
	public void resume (long soundId) {
		if (channelMap.containsKey((int)soundId))
			resume0(channelMap.get((int)soundId, -1));
	}

	@Override
	public void setLooping (long soundId, boolean looping) {
		// Not possible with SDL2_MIXER
	}

	@Override
	public void setPitch (long soundId, float pitch) {
		// Todo: Actually implement effect
		if (channelMap.containsKey((int)soundId))
			setPitch0(channelMap.get((int)soundId, -1), pitch);
	}

	@Override
	public void setVolume (long soundId, float volume) {
		if (channelMap.containsKey((int)soundId))
			setVolume0(channelMap.get((int)soundId, -1), volume);
	}

	@Override
	public void setPan (long soundId, float pan, float volume) {
		if (channelMap.containsKey((int)soundId)) {
			int channel = channelMap.get((int)soundId, -1);
			setPan0(channel, pan);
			setVolume0(channel, volume);
		}
	}

	private native void create(String path);

	private native void dispose0();

	private native int play0(boolean looping);

	private static native void stop0(int channel);

	private static native void pause0(int channel);

	private static native void resume0(int channel);

	private static native void setPitch0(int channel, float pitch);

	private static native void setVolume0(int channel, float volume);

	private static native void setPan0(int channel, float pan);
}
