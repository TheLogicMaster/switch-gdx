package com.badlogic.gdx.utils;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.UUID;

import com.badlogic.gdx.math.MathUtils;

public class SharedLibraryLoader {
	static public boolean isWindows = System.getProperty("os.name").contains("Windows");
	static public boolean isLinux = System.getProperty("os.name").contains("Linux");
	static public boolean isMac = false;
	static public boolean isIos = false;
	static public boolean isAndroid = false;
	static public boolean isARM = System.getProperty("os.arch").startsWith("arm") || System.getProperty("os.arch").startsWith("aarch64");
	static public boolean is64Bit = System.getProperty("os.arch").contains("64") || System.getProperty("os.arch").startsWith("armv8");

	public SharedLibraryLoader () {
	}

	static String randomUUID () {
		return new UUID(MathUtils.random.nextLong(), MathUtils.random.nextLong()).toString();
	}

	public SharedLibraryLoader (String nativesJar) {

	}

	public String crc (InputStream input) {
		throw new UnsupportedOperationException();
	}

	public String mapLibraryName (String libraryName) {
		throw new UnsupportedOperationException();
	}

	public void load (String libraryName) {

	}

	public File extractFile (String sourcePath, String dirName) throws IOException {
		throw new UnsupportedOperationException();
	}

	public void extractFileTo (String sourcePath, File dir) throws IOException {
		throw new UnsupportedOperationException();
	}

	public static synchronized void setLoaded (String libraryName) {

	}

	public static synchronized boolean isLoaded (String libraryName) {
		return true;
	}
}
