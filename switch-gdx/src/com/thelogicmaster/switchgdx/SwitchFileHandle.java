package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Files;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.utils.GdxRuntimeException;

import java.io.File;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

public class SwitchFileHandle extends FileHandle {

	public SwitchFileHandle (String fileName, Files.FileType type) {
		super(fileName, type);
	}

	public SwitchFileHandle (File file, Files.FileType type) {
		super(file, type);
	}

	@Override
	public FileHandle child (String name) {
		if (file.getPath().length() == 0) return new SwitchFileHandle(new File(name), type);
		return new SwitchFileHandle(new File(file, name), type);
	}

	@Override
	public FileHandle sibling (String name) {
		if (file.getPath().length() == 0) throw new GdxRuntimeException("Cannot get the sibling of the root.");
		return new SwitchFileHandle(new File(file.getParent(), name), type);
	}

	@Override
	public FileHandle parent () {
		File parent = file.getParentFile();
		if (parent == null) {
			if (type == Files.FileType.Absolute)
				parent = new File("/");
			else
				parent = new File("");
		}
		return new SwitchFileHandle(parent, type);
	}

	@Override
	public File file () {
		if (type == Files.FileType.Internal)
			return new File(SwitchApplication.isSwitch ? "romfs:" : (SwitchApplication.isUWP ? "" : "romfs"), file.getPath());
		if (type == Files.FileType.Local)
			return new File(Gdx.files.getLocalStoragePath(), file.getPath());
		return super.file();
	}

	@Override
	public boolean isDirectory() {
		if (path().startsWith("classpath/"))
			return false;
		return super.isDirectory();
	}

	@Override
	public ByteBuffer map (FileChannel.MapMode mode) {
		throw new GdxRuntimeException("Cannot map files in Switch backend");
	}
}
