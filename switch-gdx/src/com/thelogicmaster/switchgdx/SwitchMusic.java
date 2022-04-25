package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.files.FileHandle;

public class SwitchMusic implements Music {

	private long handle;

	private OnCompletionListener listener;
	private boolean paused;
	private boolean playing;
	private boolean looping;
	private float volume = 1;
	private float position;
	private boolean disposed;

	public SwitchMusic (FileHandle file) {
		create(file.file().getPath());
	}

	boolean update(float delta) {
		if (isPlaying())
			position += delta;

		return disposed;
	}

	void onMusicFinished() {
		if (!playing)
			return;

		position = 0;
		if (!looping)
			playing = false;

		if (listener != null)
			Gdx.app.postRunnable(() -> listener.onCompletion(this));
	}

	@Override
	public void play () {
		if (paused)
			resume();
		else
			start(looping);
		setVolume0(volume);

		paused = false;
		playing = true;
	}

	@Override
	public void pause () {
		if (!playing)
			return;
		paused = true;
		pause0();
	}

	@Override
	public void stop () {
		if (!playing)
			return;
		playing = false;
		stop0();
	}

	@Override
	public boolean isPlaying () {
		return !paused && playing;
	}

	@Override
	public void setLooping (boolean isLooping) {
		if (playing) {
			float pos = position;
			stop();
			setPosition0(pos);
			start(isLooping);
			position = pos;
			if (paused)
				pause0();
		}
		looping = isLooping;
	}

	@Override
	public boolean isLooping () {
		return looping;
	}

	@Override
	public void setVolume (float volume) {
		this.volume = volume;
		if (playing)
			setVolume0(volume);
	}

	@Override
	public float getVolume () {
		return volume;
	}

	@Override
	public void setPan (float pan, float volume) {
		// Not supported by SDL2_MIXER
	}

	@Override
	public void setPosition (float position) {
		this.position = position;
		if (playing)
			setPosition0(position);
	}

	@Override
	public float getPosition () {
		return position;
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
	public void setOnCompletionListener (OnCompletionListener listener) {
		this.listener = listener;
	}

	private native void create(String path);

	private native void start(boolean isLooping);

	private static native void resume();

	private static native void pause0();

	private static native void stop0();

	private static native void setVolume0(float volume);

	private static native void setPosition0(float position);

	private native void dispose0();
}
