package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Files;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;

import java.io.File;

public class SwitchFileHandle extends FileHandle {

	public SwitchFileHandle (String fileName, Files.FileType type) {
		super(fileName, type);
	}

	public SwitchFileHandle (File file, Files.FileType type) {
		super(file, type);
	}

	@Override
	public File file () {
		if (type == Files.FileType.Internal)
			return new File(SwitchApplication.isSwitch ? "romfs:" : "romfs", file.getPath());
		if (type == Files.FileType.Local)
			return new File(Gdx.files.getLocalStoragePath(), file.getPath());
		return super.file();
	}
}
