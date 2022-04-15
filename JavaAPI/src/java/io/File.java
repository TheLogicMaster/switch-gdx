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
 *
 * @author shannah
 */
public class File {
    public static final String pathSeparator = ":";
    public static final char pathSeparatorChar = ':';
    public static final String separator = "/";
    public static final char separatorChar = '/';

    private final String path;

    // Todo: Clean up path joining
    public File(File parent, String child) {
        this(parent.path + separator + child);
    }
    
    public File(String pathname) {
        this.path = pathname;
    }
    
    public File(URI uri) {
        throw new UnsupportedOperationException();
    }
    
    public File(String parent, String child) {
        this(parent.isEmpty() ? child : parent + separator + child);
    }
    
    public boolean canExecute() {
        return false;
    }
    
    public boolean canRead() {
        return false;
    }
    
    public boolean canWrite() {
        return false;
    }
    
    public int compareTo(File pathname) {
        return 0;
    }

    public boolean createNewFile() {
        return false;
    }
    
    public static File createTempFile(String prefix, String suffix) {
        throw new UnsupportedOperationException();
    }
    
    public static File createTempFile(String prefix, String suffix, File directory) {
        throw new UnsupportedOperationException();
    }
    
    public boolean delete() {
        return false;
    }
    
    public void deleteOnExit() {
        
    }
    
    public native boolean exists();
    
    public File getAbsoluteFile() {
        return null;
    }
    
    public String getAbsolutePath() {
        return null;
    }
    
    public String getCanonicalPath() {
        return null;
    }
    
    public File getCanonicalFile() {
        return null;
    }
    
    public long getFreeSpace() {
        return 0;
        
    }
    
    public String getName() {
        int index = path.lastIndexOf(separatorChar);
        return path.substring(index + 1);
    }
    
    public String getParent() {
        return null;
    }
    
    public File getParentFile() {
        return null;
    }
    
    public String getPath() {
        return path;
    }
    
    public long getTotalSpace() {
        return 0;
    }
    
    public long getUsableSpace() {
        return 0;
    }
    
    public boolean isAbsolute() {
        return false;
    }
    
    public native boolean isDirectory();
    
    public boolean isFile() {
        return false;
    }

    public boolean isInvalid() {
        return false;
    }
    
    public boolean isHidden() {
        return false;
    }
    
    public long lastModified() {
        return 0;
    }
    
    public long length() {
        return 0;
    }
    
    public String[] list() {
        return null;
    }
    
    public File[] listFiles() {
        return null;
    }
    
    public static File[] listRoots() {
        throw new UnsupportedOperationException("java.io.File not implemented");
    }
    
    public boolean mkdir() {
        return false;
    }
    
    public boolean mkdirs() {
        return false;
    }
    
    public boolean renameTo(File f) {
        return false;
    }
    
    public boolean setExecutable(boolean b) {
        return false;
    } 
    
    public boolean setExecutable(boolean b, boolean owner) {
        return false;
    }
    
    public boolean setReadable(boolean b) {
        return false;
        
    }
    
    public boolean setReadable(boolean b1, boolean b2) {
        return false;
    }
    
    public boolean setReadOnly() {
        return false;
    }
    
    public boolean setWritable(boolean writable) {
        return false;
    }
    
    public boolean setWritable(boolean writable, boolean ownerOnly) {
        return false;
    }
    
    public URI toURI() {
        return null;
    }
    
    public URL toURL() {
        return null;
    }

    @Override
    public String toString () {
        return "File(" + path + ")";
    }
}
