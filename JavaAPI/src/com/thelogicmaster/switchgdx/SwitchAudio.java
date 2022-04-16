package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Audio;
import com.badlogic.gdx.audio.AudioDevice;
import com.badlogic.gdx.audio.AudioRecorder;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.utils.Array;

public class SwitchAudio implements Audio {

	private static final Array<SwitchMusic> musics = new Array<>();
	private static final Array<SwitchSound> sounds = new Array<>();

	void update(float delta) {
		Array.ArrayIterator<SwitchMusic> musicIter = new Array.ArrayIterator<>(musics);
		for (SwitchMusic music: musicIter)
			if (music.update(delta))
				musicIter.remove();

		Array.ArrayIterator<SwitchSound> soundIter = new Array.ArrayIterator<>(sounds);
		for (SwitchSound sound: soundIter)
			if (sound.update())
				soundIter.remove();
	}

	@Override
	public AudioDevice newAudioDevice (int samplingRate, boolean isMono) {
		return null;
	}

	@Override
	public AudioRecorder newAudioRecorder (int samplingRate, boolean isMono) {
		return null;
	}

	@Override
	public Sound newSound (FileHandle fileHandle) {
		SwitchSound sound = new SwitchSound(fileHandle);
		sounds.add(sound);
		return sound;
	}

	@Override
	public Music newMusic (FileHandle fileHandle) {
		SwitchMusic music = new SwitchMusic(fileHandle);
		musics.add(music);
		return music;
	}

	private static void onMusicFinished() {
		for (SwitchMusic music: new Array.ArrayIterator<>(musics))
			music.onMusicFinished();
	}

	private static void onSoundFinished(int channel) {
		for (SwitchSound sound: new Array.ArrayIterator<>(sounds))
			sound.onSoundFinished(channel);
	}
}
