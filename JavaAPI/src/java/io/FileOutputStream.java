/*
 * Copyright (c) 1994, 2013, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
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
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

package java.io;


/**
 * A file output stream is an output stream for writing data to a
 * <code>File</code> or to a <code>FileDescriptor</code>. Whether or not
 * a file is available or may be created depends upon the underlying
 * platform.  Some platforms, in particular, allow a file to be opened
 * for writing by only one <tt>FileOutputStream</tt> (or other
 * file-writing object) at a time.  In such situations the constructors in
 * this class will fail if the file involved is already open.
 *
 * <p><code>FileOutputStream</code> is meant for writing streams of raw bytes
 * such as image data. For writing streams of characters, consider using
 * <code>FileWriter</code>.
 *
 * @author  Arthur van Hoff
 * @see     java.io.File
 * @see     java.io.FileDescriptor
 * @see     java.io.FileInputStream
 * @see     java.nio.file.Files#newOutputStream
 * @since   JDK1.0
 */
public
class FileOutputStream extends OutputStream
{
	private long file;

	/**
	 * True if the file is opened for append.
	 */
	private final boolean append;

	/**
	 * The path of the referenced file
	 * (null if the stream is created with a file descriptor)
	 */
	private final String path;

	private final Object closeLock = new Object();
	private volatile boolean closed = false;

	/**
	 * Creates a file output stream to write to the file with the
	 * specified name. A new <code>FileDescriptor</code> object is
	 * created to represent this file connection.
	 * <p>
	 * First, if there is a security manager, its <code>checkWrite</code>
	 * method is called with <code>name</code> as its argument.
	 * <p>
	 * If the file exists but is a directory rather than a regular file, does
	 * not exist but cannot be created, or cannot be opened for any other
	 * reason then a <code>FileNotFoundException</code> is thrown.
	 *
	 * @param      name   the system-dependent filename
	 * @exception  FileNotFoundException  if the file exists but is a directory
	 *                   rather than a regular file, does not exist but cannot
	 *                   be created, or cannot be opened for any other reason
	 * @exception  SecurityException  if a security manager exists and its
	 *               <code>checkWrite</code> method denies write access
	 *               to the file.
	 * @see        java.lang.SecurityManager#checkWrite(java.lang.String)
	 */
	public FileOutputStream(String name) throws FileNotFoundException {
		this(name != null ? new File(name) : null, false);
	}

	/**
	 * Creates a file output stream to write to the file with the specified
	 * name.  If the second argument is <code>true</code>, then
	 * bytes will be written to the end of the file rather than the beginning.
	 * A new <code>FileDescriptor</code> object is created to represent this
	 * file connection.
	 * <p>
	 * First, if there is a security manager, its <code>checkWrite</code>
	 * method is called with <code>name</code> as its argument.
	 * <p>
	 * If the file exists but is a directory rather than a regular file, does
	 * not exist but cannot be created, or cannot be opened for any other
	 * reason then a <code>FileNotFoundException</code> is thrown.
	 *
	 * @param     name        the system-dependent file name
	 * @param     append      if <code>true</code>, then bytes will be written
	 *                   to the end of the file rather than the beginning
	 * @exception  FileNotFoundException  if the file exists but is a directory
	 *                   rather than a regular file, does not exist but cannot
	 *                   be created, or cannot be opened for any other reason.
	 * @exception  SecurityException  if a security manager exists and its
	 *               <code>checkWrite</code> method denies write access
	 *               to the file.
	 * @see        java.lang.SecurityManager#checkWrite(java.lang.String)
	 * @since     JDK1.1
	 */
	public FileOutputStream(String name, boolean append)
		throws FileNotFoundException
	{
		this(name != null ? new File(name) : null, append);
	}

	/**
	 * Creates a file output stream to write to the file represented by
	 * the specified <code>File</code> object. A new
	 * <code>FileDescriptor</code> object is created to represent this
	 * file connection.
	 * <p>
	 * First, if there is a security manager, its <code>checkWrite</code>
	 * method is called with the path represented by the <code>file</code>
	 * argument as its argument.
	 * <p>
	 * If the file exists but is a directory rather than a regular file, does
	 * not exist but cannot be created, or cannot be opened for any other
	 * reason then a <code>FileNotFoundException</code> is thrown.
	 *
	 * @param      file               the file to be opened for writing.
	 * @exception  FileNotFoundException  if the file exists but is a directory
	 *                   rather than a regular file, does not exist but cannot
	 *                   be created, or cannot be opened for any other reason
	 * @exception  SecurityException  if a security manager exists and its
	 *               <code>checkWrite</code> method denies write access
	 *               to the file.
	 * @see        java.io.File#getPath()
	 * @see        java.lang.SecurityException
	 * @see        java.lang.SecurityManager#checkWrite(java.lang.String)
	 */
	public FileOutputStream(File file) throws FileNotFoundException {
		this(file, false);
	}

	/**
	 * Creates a file output stream to write to the file represented by
	 * the specified <code>File</code> object. If the second argument is
	 * <code>true</code>, then bytes will be written to the end of the file
	 * rather than the beginning. A new <code>FileDescriptor</code> object is
	 * created to represent this file connection.
	 * <p>
	 * First, if there is a security manager, its <code>checkWrite</code>
	 * method is called with the path represented by the <code>file</code>
	 * argument as its argument.
	 * <p>
	 * If the file exists but is a directory rather than a regular file, does
	 * not exist but cannot be created, or cannot be opened for any other
	 * reason then a <code>FileNotFoundException</code> is thrown.
	 *
	 * @param      file               the file to be opened for writing.
	 * @param     append      if <code>true</code>, then bytes will be written
	 *                   to the end of the file rather than the beginning
	 * @exception  FileNotFoundException  if the file exists but is a directory
	 *                   rather than a regular file, does not exist but cannot
	 *                   be created, or cannot be opened for any other reason
	 * @exception  SecurityException  if a security manager exists and its
	 *               <code>checkWrite</code> method denies write access
	 *               to the file.
	 * @see        java.io.File#getPath()
	 * @see        java.lang.SecurityException
	 * @see        java.lang.SecurityManager#checkWrite(java.lang.String)
	 * @since 1.4
	 */
	public FileOutputStream(File file, boolean append)
		throws FileNotFoundException
	{
		String name = (file != null ? file.getPath() : null);
		if (name == null)
			throw new NullPointerException();
		if (file.isInvalid())
			throw new FileNotFoundException("Invalid file path");
		this.append = append;
		this.path = name;

		open(name, append);
	}

	/**
	 * Opens a file, with the specified name, for overwriting or appending.
	 * @param name name of file to be opened
	 * @param append whether the file is to be opened in append mode
	 */
	public native void open(String name, boolean append) throws FileNotFoundException;

	/**
	 * Writes the specified byte to this file output stream.
	 *
	 * @param   b   the byte to be written.
	 * @param   append   {@code true} if the write operation first
	 *     advances the position to the end of file
	 */
	private native void write(int b, boolean append) throws IOException;

	/**
	 * Writes the specified byte to this file output stream. Implements
	 * the <code>write</code> method of <code>OutputStream</code>.
	 *
	 * @param      b   the byte to be written.
	 * @exception  IOException  if an I/O error occurs.
	 */
	public void write(int b) throws IOException {
		write(b, append);
	}

	/**
	 * Writes a sub array as a sequence of bytes.
	 * @param b the data to be written
	 * @param off the start offset in the data
	 * @param len the number of bytes that are written
	 * @param append {@code true} to first advance the position to the
	 *     end of file
	 * @exception IOException If an I/O error has occurred.
	 */
	private native void writeBytes(byte b[], int off, int len, boolean append)
		throws IOException;

	/**
	 * Writes <code>b.length</code> bytes from the specified byte array
	 * to this file output stream.
	 *
	 * @param      b   the data.
	 * @exception  IOException  if an I/O error occurs.
	 */
	public void write(byte b[]) throws IOException {
		writeBytes(b, 0, b.length, append);
	}

	/**
	 * Writes <code>len</code> bytes from the specified byte array
	 * starting at offset <code>off</code> to this file output stream.
	 *
	 * @param      b     the data.
	 * @param      off   the start offset in the data.
	 * @param      len   the number of bytes to write.
	 * @exception  IOException  if an I/O error occurs.
	 */
	public void write(byte b[], int off, int len) throws IOException {
		writeBytes(b, off, len, append);
	}

	/**
	 * Closes this file output stream and releases any system resources
	 * associated with this stream. This file output stream may no longer
	 * be used for writing bytes.
	 *
	 * <p> If this stream has an associated channel then the channel is closed
	 * as well.
	 *
	 * @exception  IOException  if an I/O error occurs.
	 *
	 * @revised 1.4
	 * @spec JSR-51
	 */
	public void close() throws IOException {
		synchronized (closeLock) {
			if (closed)
				return;
			closed = true;
		}

		close0();
	}

	/**
	 * Cleans up the connection to the file, and ensures that the
	 * <code>close</code> method of this file output stream is
	 * called when there are no more references to this stream.
	 *
	 * @exception  IOException  if an I/O error occurs.
	 * @see        java.io.FileInputStream#close()
	 */
	protected void finalize() throws IOException {
		close();
	}

	private native void close0() throws IOException;
}
