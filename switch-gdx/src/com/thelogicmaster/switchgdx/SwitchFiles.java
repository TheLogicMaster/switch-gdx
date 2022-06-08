package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Files;
import com.badlogic.gdx.files.FileHandle;

public class SwitchFiles implements Files {

	@Override
	public FileHandle getFileHandle (String path, FileType type) {
		if (type == FileType.Classpath) {
			type = FileType.Internal;
			path = "classpath/" + path;
		}
		return new SwitchFileHandle(path, type);
	}

	@Override
	public FileHandle classpath (String path) {
		return getFileHandle(path, FileType.Classpath);
	}

	@Override
	public FileHandle internal (String path) {
		return getFileHandle(path, FileType.Internal);
	}

	@Override
	public FileHandle external (String path) {
		return getFileHandle(path, FileType.External);
	}

	@Override
	public FileHandle absolute (String path) {
		return getFileHandle(path, FileType.Absolute);
	}

	@Override
	public FileHandle local (String path) {
		return getFileHandle(path, FileType.Local);
	}

	@Override
	public String getExternalStoragePath () {
		return SwitchApplication.isSwitch ? "sdmc:" : "sdmc";
	}

	@Override
	public boolean isExternalStorageAvailable () {
		return SwitchApplication.isSwitch;
	}

	@Override
	public native String getLocalStoragePath ();

	@Override
	public boolean isLocalStorageAvailable () {
		return true;
	}
}
