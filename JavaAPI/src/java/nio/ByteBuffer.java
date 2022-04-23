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

package java.nio;

import com.thelogicmaster.switchgdx.NativeUtils;

public class ByteBuffer extends Buffer implements Comparable<ByteBuffer> {

	private final ByteBuffer owner;
	private final boolean isOwner;

	ByteBuffer (ByteBuffer owner, int mark, int pos, int lim, int cap, int off) {
		super(mark, pos, lim, cap);
		this.owner = owner;
		isOwner = false;
		address = owner.address + off;
	}

	ByteBuffer (long address, int cap) {
		this(address, cap, true);
	}

	ByteBuffer (long address, int cap, boolean isOwner) {
		super(-1, 0, cap, cap);
		owner = null;
		this.address = address;
		this.isOwner = isOwner;
	}

	private native static void deallocate(long address);

	public native static ByteBuffer allocateDirect (int capacity);

	protected void finalize () {
		if (address != 0 && isOwner) {
			deallocate(address);
			address = 0;
		}
	}

	public static ByteBuffer allocate (int capacity) {
		return allocateDirect(capacity);
	}

	public static ByteBuffer wrap (byte[] array, int offset, int length) {
		throw new UnsupportedOperationException();
	}

	public static ByteBuffer wrap (byte[] array) {
		return wrap(array, 0, array.length);
	}

	public ByteBuffer slice () {
		int pos = this.position();
		int lim = this.limit();
		int rem = (pos <= lim ? lim - pos : 0);
		int off = (pos << 0);
		assert (off >= 0);
		return new ByteBuffer(this, -1, 0, rem, rem, off);
	}

	public ByteBuffer duplicate () {
		return new ByteBuffer(this, this.markValue(), this.position(), this.limit(), this.capacity(), 0);
	}

	public ByteBuffer asReadOnlyBuffer () {
		throw new UnsupportedOperationException();
	}

	@Override
	public boolean isReadOnly () {
		return false;
	}

	private long ix (int i) {
		return address + ((long)i << 0);
	}

	byte _get(int i) {
		return NativeUtils.getByte(ix(i));
	}

	void _put(int i, byte b) {
		NativeUtils.putByte(ix(i), b);
	}

	public byte get () {
		return NativeUtils.getByte(ix(nextGetIndex()));
	}

	public ByteBuffer put (byte b) {
		NativeUtils.putByte(ix(nextPutIndex()), b);
		return this;
	}

	public byte get (int index) {
		return NativeUtils.getByte(ix(checkIndex(index)));
	}

	public ByteBuffer put (int index, byte b) {
		NativeUtils.putByte(ix(checkIndex(index)), b);
		return this;
	}

	public ByteBuffer get (byte[] dst, int offset, int length) {
		checkBounds(offset, length, dst.length);
		if (length > remaining())
			throw new BufferUnderflowException();
		int end = offset + length;
		for (int i = offset; i < end; i++)
			dst[i] = get();
		return this;
	}

	public ByteBuffer get (byte[] dst) {
		return get(dst, 0, dst.length);
	}

	public ByteBuffer put (ByteBuffer src) {
		if (src == this)
			throw new IllegalArgumentException();
		if (isReadOnly())
			throw new ReadOnlyBufferException();
		int n = src.remaining();
		if (n > remaining())
			throw new BufferOverflowException();
		for (int i = 0; i < n; i++)
			put(src.get());
		return this;
	}

	public ByteBuffer put (byte[] src, int offset, int length) {
		checkBounds(offset, length, src.length);
		if (length > remaining())
			throw new BufferOverflowException();
		int end = offset + length;
		for (int i = offset; i < end; i++)
			this.put(src[i]);
		return this;
	}

	public final ByteBuffer put (byte[] src) {
		return put(src, 0, src.length);
	}

	public final boolean hasArray () {
		return false;
	}

	public final byte[] array () {
		throw new UnsupportedOperationException();
	}

	public final int arrayOffset () {
		throw new UnsupportedOperationException();
	}

	public ByteBuffer compact () {
		int pos = position();
		int lim = limit();
		assert (pos <= lim);
		int rem = (pos <= lim ? lim - pos : 0);
		NativeUtils.copyMemory(ix(pos), ix(0), (long)rem << 0);
		position(rem);
		limit(capacity());
		discardMark();
		return this;
	}

	public boolean isDirect () {
		return true;
	}

	public String toString () {
		StringBuffer sb = new StringBuffer();
		sb.append(getClass().getName());
		sb.append("[pos=");
		sb.append(position());
		sb.append(" lim=");
		sb.append(limit());
		sb.append(" cap=");
		sb.append(capacity());
		sb.append("]");
		return sb.toString();
	}

	public int hashCode () {
		int h = 1;
		int p = position();
		for (int i = limit() - 1; i >= p; i--)
			h = 31 * h + (int)get(i);
		return h;
	}

	public boolean equals (Object ob) {
		if (this == ob)
			return true;
		if (!(ob instanceof ByteBuffer))
			return false;
		ByteBuffer that = (ByteBuffer)ob;
		int thisPos = this.position();
		int thisLim = this.limit();
		int thatPos = that.position();
		int thatLim = that.limit();
		int thisRem = thisLim - thisPos;
		int thatRem = thatLim - thatPos;
		if (thisRem < 0 || thisRem != thatRem)
			return false;
		for (int i = thisLim - 1, j = thatLim - 1; i >= thisPos; i--, j--)
			if (!equals(this.get(i), that.get(j)))
				return false;
		return true;
	}

	private static boolean equals (byte x, byte y) {
		return x == y;
	}

	public int compareTo (ByteBuffer that) {
		int thisPos = this.position();
		int thisRem = this.limit() - thisPos;
		int thatPos = that.position();
		int thatRem = that.limit() - thatPos;
		int length = Math.min(thisRem, thatRem);
		if (length < 0)
			return -1;
		int n = thisPos + Math.min(thisRem, thatRem);
		for (int i = thisPos, j = thatPos; i < n; i++, j++) {
			int cmp = compare(this.get(i), that.get(j));
			if (cmp != 0)
				return cmp;
		}
		return thisRem - thatRem;
	}

	private static int compare (byte x, byte y) {
		return Byte.compare(x, y);
	}

	boolean bigEndian = true;
	boolean nativeByteOrder = (ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN);

	public final ByteOrder order () {
		return bigEndian ? ByteOrder.BIG_ENDIAN : ByteOrder.LITTLE_ENDIAN;
	}

	public final ByteBuffer order (ByteOrder bo) {
		bigEndian = (bo == ByteOrder.BIG_ENDIAN);
		nativeByteOrder = (bigEndian == (ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN));
		return this;
	}

	private char getChar (long a) {
		char x = NativeUtils.getChar(a);
		return nativeByteOrder ? x : Character.reverseBytes(x);
	}

	public char getChar () {
		return getChar(ix(nextGetIndex((1 << 1))));
	}

	public char getChar (int i) {
		return getChar(ix(checkIndex(i, (1 << 1))));
	}

	private ByteBuffer putChar (long a, char x) {
		NativeUtils.putChar(a, nativeByteOrder ? x : Character.reverseBytes(x));
		return this;
	}

	public ByteBuffer putChar (char x) {
		return putChar(ix(nextPutIndex((1 << 1))), x);
	}

	public ByteBuffer putChar (int i, char x) {
		return putChar(ix(checkIndex(i, (1 << 1))), x);
	}

	public CharBuffer asCharBuffer () {
		int off = this.position();
		int lim = this.limit();
		assert (off <= lim);
		int rem = (off <= lim ? lim - off : 0);
		int size = rem >> 1;
		return new ByteBufferAsCharBufferL(this, -1, 0, size, size, off);
	}

	private short getShort (long a) {
		short x = NativeUtils.getShort(a);
		return nativeByteOrder ? x : Short.reverseBytes(x);
	}

	public short getShort () {
		return getShort(ix(nextGetIndex((1 << 1))));
	}

	public short getShort (int i) {
		return getShort(ix(checkIndex(i, (1 << 1))));
	}

	private ByteBuffer putShort (long a, short x) {
		NativeUtils.putShort(a, nativeByteOrder ? x : Short.reverseBytes(x));
		return this;
	}

	public ByteBuffer putShort (short x) {
		return putShort(ix(nextPutIndex((1 << 1))), x);
	}

	public ByteBuffer putShort (int i, short x) {
		return putShort(ix(checkIndex(i, (1 << 1))), x);
	}

	public ShortBuffer asShortBuffer () {
		int off = this.position();
		int lim = this.limit();
		assert (off <= lim);
		int rem = (off <= lim ? lim - off : 0);
		int size = rem >> 1;
		return new ByteBufferAsShortBufferL(this, -1, 0, size, size, off);
	}

	private int getInt (long a) {
		int x = NativeUtils.getInt(a);
		return nativeByteOrder ? x : Integer.reverseBytes(x);
	}

	public int getInt () {
		return getInt(ix(nextGetIndex((1 << 2))));
	}

	public int getInt (int i) {
		return getInt(ix(checkIndex(i, (1 << 2))));
	}

	private ByteBuffer putInt (long a, int x) {
		NativeUtils.putInt(a, nativeByteOrder ? x : Integer.reverseBytes(x));
		return this;
	}

	public ByteBuffer putInt (int x) {
		return putInt(ix(nextPutIndex((1 << 2))), x);
	}

	public ByteBuffer putInt (int i, int x) {
		return putInt(ix(checkIndex(i, (1 << 2))), x);
	}

	public IntBuffer asIntBuffer () {
		int off = this.position();
		int lim = this.limit();
		assert (off <= lim);
		int rem = (off <= lim ? lim - off : 0);
		int size = rem >> 2;
		return new ByteBufferAsIntBufferL(this, -1, 0, size, size, off);
	}

	private long getLong (long a) {
		long x = NativeUtils.getLong(a);
		return nativeByteOrder ? x : Long.reverseBytes(x);
	}

	public long getLong () {
		return getLong(ix(nextGetIndex((1 << 3))));
	}

	public long getLong (int i) {
		return getLong(ix(checkIndex(i, (1 << 3))));
	}

	private ByteBuffer putLong (long a, long x) {
		NativeUtils.putLong(a, nativeByteOrder ? x : Long.reverseBytes(x));
		return this;
	}

	public ByteBuffer putLong (long x) {
		return putLong(ix(nextPutIndex((1 << 3))), x);
	}

	public ByteBuffer putLong (int i, long x) {
		return putLong(ix(checkIndex(i, (1 << 3))), x);
	}

	public LongBuffer asLongBuffer () {
		int off = this.position();
		int lim = this.limit();
		assert (off <= lim);
		int rem = (off <= lim ? lim - off : 0);
		int size = rem >> 3;
		return new ByteBufferAsLongBufferL(this, -1, 0, size, size, off);
	}

	private float getFloat (long a) {
		int x = NativeUtils.getInt(a);
		return Float.intBitsToFloat(nativeByteOrder ? x : Integer.reverseBytes(x));
	}

	public float getFloat () {
		return getFloat(ix(nextGetIndex((1 << 2))));
	}

	public float getFloat (int i) {
		return getFloat(ix(checkIndex(i, (1 << 2))));
	}

	private ByteBuffer putFloat (long a, float x) {
		int y = Float.floatToIntBits(x);
		NativeUtils.putInt(a, nativeByteOrder ? y : Integer.reverseBytes(y));
		return this;
	}

	public ByteBuffer putFloat (float x) {
		return putFloat(ix(nextPutIndex((1 << 2))), x);
	}

	public ByteBuffer putFloat (int i, float x) {
		return putFloat(ix(checkIndex(i, (1 << 2))), x);
	}

	public FloatBuffer asFloatBuffer () {
		int off = this.position();
		int lim = this.limit();
		assert (off <= lim);
		int rem = (off <= lim ? lim - off : 0);
		int size = rem >> 2;
		return new ByteBufferAsFloatBufferL(this, -1, 0, size, size, off);
	}

	private double getDouble (long a) {
		long x = NativeUtils.getLong(a);
		return Double.longBitsToDouble(nativeByteOrder ? x : Long.reverseBytes(x));
	}

	public double getDouble () {
		return getDouble(ix(nextGetIndex((1 << 3))));
	}

	public double getDouble (int i) {
		return getDouble(ix(checkIndex(i, (1 << 3))));
	}

	private ByteBuffer putDouble (long a, double x) {
		long y = Double.doubleToLongBits(x);
		NativeUtils.putLong(a, nativeByteOrder ? y : Long.reverseBytes(y));
		return this;
	}

	public ByteBuffer putDouble (double x) {
		return putDouble(ix(nextPutIndex((1 << 3))), x);
	}

	public ByteBuffer putDouble (int i, double x) {
		return putDouble(ix(checkIndex(i, (1 << 3))), x);
	}

	public DoubleBuffer asDoubleBuffer () {
		int off = this.position();
		int lim = this.limit();
		assert (off <= lim);
		int rem = (off <= lim ? lim - off : 0);
		int size = rem >> 3;
		return new ByteBufferAsDoubleBufferL(this, -1, 0, size, size, off);
	}
}
