/*
 * Copyright (c) 2012, Codename One and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Codename One designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Codename One through http://www.codenameone.com/ if you
 * need additional information or have any questions.
 */

/*
 * Modified by TheLogicMaster at 4/14/22
 */

package java.io;

import java.net.URI;
import java.net.URL;

/**
 * @author shannah
 */
public class File {
	public static final String pathSeparator = ":";
	public static final char pathSeparatorChar = ':';
	public static final String separator = "/";
	public static final char separatorChar = '/';

	private final String path;

	public File (File parent, String child) {
		this(parent.path.isEmpty() ? child : (parent.path + separator + child).replace("//", "/"));
	}

	public File (String pathname) {
		this.path = pathname;
	}

	public File (URI uri) {
		throw new UnsupportedOperationException();
	}

	public File (String parent, String child) {
		this(parent.isEmpty() ? child : (parent + separator + child).replace("//", "/"));
	}

	public boolean canExecute () {
		return true;
	}

	public boolean canRead () {
		return true;
	}

	public boolean canWrite () {
		return true;
	}

	public int compareTo (File pathname) {
		return 0;
	}

	public boolean createNewFile () {
		return false;
	}

	public static File createTempFile (String prefix, String suffix) {
		return createTempFile(prefix, suffix, null);
	}

	public static File createTempFile (String prefix, String suffix, File directory) {
		File tempDir = directory == null ? new File("temp") : directory;
		if (!(tempDir.exists() && tempDir.isDirectory()) && !tempDir.mkdir())
			return null;
        String name = prefix + (suffix == null ? ".tmp" : suffix);
        File tempFile = new File(tempDir, name);
		if (!createFile(tempFile.path))
            return null;
        return tempFile;
	}

	private static native boolean createFile (String path);

	public native boolean delete ();

	public void deleteOnExit () {
	}

	public native boolean exists ();

	public File getAbsoluteFile () {
		return null;
	}

	public String getAbsolutePath () {
		return null;
	}

	public String getCanonicalPath () {
		return null;
	}

	public File getCanonicalFile () {
		return null;
	}

	public long getFreeSpace () {
		return 0;
	}

	public String getName () {
		int index = path.lastIndexOf(separatorChar);
		if (index == -1 || index == path.length() - 1)
			return path;
		else
			return path.substring(index + 1);
	}

	public String getParent () {
		if (path.isEmpty())
			return null;
		int index = path.lastIndexOf(separatorChar);
		return index == -1 ? "" : path.substring(0, path.lastIndexOf(separatorChar));
	}

	public File getParentFile () {
		String parent = getParent();
		if (parent != null)
			return new File(parent);
		return null;
	}

	public String getPath () {
		return path;
	}

	public long getTotalSpace () {
		return 0;
	}

	public long getUsableSpace () {
		return 0;
	}

	public boolean isAbsolute () {
		return false;
	}

	public native boolean isDirectory ();

	public boolean isFile () {
		return !isDirectory();
	}

	public boolean isInvalid () {
		return false;
	}

	public boolean isHidden () {
		return false;
	}

	public native long lastModified ();

	public native long length ();

	public native String[] list ();

	public File[] listFiles () {
		String[] filenames = list();
		if (filenames == null)
			return null;
		File[] files = new File[filenames.length];
		for (int i = 0; i < filenames.length; i++)
			files[i] = new File(filenames[i]);
		return files;
	}

	public static File[] listRoots () {
		return null;
	}

	public native boolean mkdir ();

	public boolean mkdirs () {
		File dir = this;
		while (dir != null && !dir.path.isEmpty()) {
			if (!dir.exists() && !dir.mkdir())
				return false;
			dir = dir.getParentFile();
		}
		return true;
	}

	public boolean renameTo (File f) {
		return false;
	}

	public boolean setExecutable (boolean b) {
		return false;
	}

	public boolean setExecutable (boolean b, boolean owner) {
		return false;
	}

	public boolean setReadable (boolean b) {
		return false;
	}

	public boolean setReadable (boolean b1, boolean b2) {
		return false;
	}

	public boolean setReadOnly () {
		return false;
	}

	public boolean setWritable (boolean writable) {
		return false;
	}

	public boolean setWritable (boolean writable, boolean ownerOnly) {
		return false;
	}

	public URI toURI () {
		return null;
	}

	public URL toURL () {
		return null;
	}

	@Override
	public String toString () {
		return "File(" + path + ")";
	}
}
