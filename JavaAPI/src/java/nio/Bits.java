/*
 * Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
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

package java.nio;

class Bits {

	private Bits () {
	}

	static short swap (short x) {
		return Short.reverseBytes(x);
	}

	static char swap (char x) {
		return Character.reverseBytes(x);
	}

	static int swap (int x) {
		return Integer.reverseBytes(x);
	}

	static long swap (long x) {
		return Long.reverseBytes(x);
	}

	static private char makeChar (byte b1, byte b0) {
		return (char)((b1 << 8) | (b0 & 0xff));
	}

	static char getCharL (ByteBuffer bb, int bi) {
		return makeChar(bb._get(bi + 1), bb._get(bi));
	}

	static char getCharB (ByteBuffer bb, int bi) {
		return makeChar(bb._get(bi), bb._get(bi + 1));
	}

	static char getChar (ByteBuffer bb, int bi, boolean bigEndian) {
		return bigEndian ? getCharB(bb, bi) : getCharL(bb, bi);
	}

	private static byte char1 (char x) {
		return (byte)(x >> 8);
	}

	private static byte char0 (char x) {
		return (byte)(x);
	}

	static void putCharL (ByteBuffer bb, int bi, char x) {
		bb._put(bi, char0(x));
		bb._put(bi + 1, char1(x));
	}

	static void putCharB (ByteBuffer bb, int bi, char x) {
		bb._put(bi, char1(x));
		bb._put(bi + 1, char0(x));
	}

	static void putChar (ByteBuffer bb, int bi, char x, boolean bigEndian) {
		if (bigEndian)
			putCharB(bb, bi, x);
		else
			putCharL(bb, bi, x);
	}

	static private short makeShort (byte b1, byte b0) {
		return (short)((b1 << 8) | (b0 & 0xff));
	}

	static short getShortL (ByteBuffer bb, int bi) {
		return makeShort(bb._get(bi + 1), bb._get(bi));
	}

	static short getShortB (ByteBuffer bb, int bi) {
		return makeShort(bb._get(bi), bb._get(bi + 1));
	}

	static short getShort (ByteBuffer bb, int bi, boolean bigEndian) {
		return bigEndian ? getShortB(bb, bi) : getShortL(bb, bi);
	}

	private static byte short1 (short x) {
		return (byte)(x >> 8);
	}

	private static byte short0 (short x) {
		return (byte)(x);
	}

	static void putShortL (ByteBuffer bb, int bi, short x) {
		bb._put(bi, short0(x));
		bb._put(bi + 1, short1(x));
	}

	static void putShortB (ByteBuffer bb, int bi, short x) {
		bb._put(bi, short1(x));
		bb._put(bi + 1, short0(x));
	}

	static void putShort (ByteBuffer bb, int bi, short x, boolean bigEndian) {
		if (bigEndian)
			putShortB(bb, bi, x);
		else
			putShortL(bb, bi, x);
	}

	static private int makeInt (byte b3, byte b2, byte b1, byte b0) {
		return (((b3) << 24) | ((b2 & 0xff) << 16) | ((b1 & 0xff) << 8) | ((b0 & 0xff)));
	}

	static int getIntL (ByteBuffer bb, int bi) {
		return makeInt(bb._get(bi + 3), bb._get(bi + 2), bb._get(bi + 1), bb._get(bi));
	}

	static int getIntB (ByteBuffer bb, int bi) {
		return makeInt(bb._get(bi), bb._get(bi + 1), bb._get(bi + 2), bb._get(bi + 3));
	}

	static int getInt (ByteBuffer bb, int bi, boolean bigEndian) {
		return bigEndian ? getIntB(bb, bi) : getIntL(bb, bi);
	}

	private static byte int3 (int x) {
		return (byte)(x >> 24);
	}

	private static byte int2 (int x) {
		return (byte)(x >> 16);
	}

	private static byte int1 (int x) {
		return (byte)(x >> 8);
	}

	private static byte int0 (int x) {
		return (byte)(x);
	}

	static void putIntL (ByteBuffer bb, int bi, int x) {
		bb._put(bi + 3, int3(x));
		bb._put(bi + 2, int2(x));
		bb._put(bi + 1, int1(x));
		bb._put(bi, int0(x));
	}

	static void putIntB (ByteBuffer bb, int bi, int x) {
		bb._put(bi, int3(x));
		bb._put(bi + 1, int2(x));
		bb._put(bi + 2, int1(x));
		bb._put(bi + 3, int0(x));
	}

	static void putInt (ByteBuffer bb, int bi, int x, boolean bigEndian) {
		if (bigEndian)
			putIntB(bb, bi, x);
		else
			putIntL(bb, bi, x);
	}

	static private long makeLong (byte b7, byte b6, byte b5, byte b4, byte b3, byte b2, byte b1, byte b0) {
		return ((((long)b7) << 56) | (((long)b6 & 0xff) << 48) | (((long)b5 & 0xff) << 40) | (((long)b4 & 0xff) << 32) | (((long)b3 & 0xff) << 24) | (((long)b2 & 0xff) << 16) | (((long)b1 & 0xff) << 8) | (((long)b0 & 0xff)));
	}

	static long getLongL (ByteBuffer bb, int bi) {
		return makeLong(bb._get(bi + 7), bb._get(bi + 6), bb._get(bi + 5), bb._get(bi + 4), bb._get(bi + 3), bb._get(bi + 2), bb._get(bi + 1), bb._get(bi));
	}

	static long getLongB (ByteBuffer bb, int bi) {
		return makeLong(bb._get(bi), bb._get(bi + 1), bb._get(bi + 2), bb._get(bi + 3), bb._get(bi + 4), bb._get(bi + 5), bb._get(bi + 6), bb._get(bi + 7));
	}

	static long getLong (ByteBuffer bb, int bi, boolean bigEndian) {
		return bigEndian ? getLongB(bb, bi) : getLongL(bb, bi);
	}

	private static byte long7 (long x) {
		return (byte)(x >> 56);
	}

	private static byte long6 (long x) {
		return (byte)(x >> 48);
	}

	private static byte long5 (long x) {
		return (byte)(x >> 40);
	}

	private static byte long4 (long x) {
		return (byte)(x >> 32);
	}

	private static byte long3 (long x) {
		return (byte)(x >> 24);
	}

	private static byte long2 (long x) {
		return (byte)(x >> 16);
	}

	private static byte long1 (long x) {
		return (byte)(x >> 8);
	}

	private static byte long0 (long x) {
		return (byte)(x);
	}

	static void putLongL (ByteBuffer bb, int bi, long x) {
		bb._put(bi + 7, long7(x));
		bb._put(bi + 6, long6(x));
		bb._put(bi + 5, long5(x));
		bb._put(bi + 4, long4(x));
		bb._put(bi + 3, long3(x));
		bb._put(bi + 2, long2(x));
		bb._put(bi + 1, long1(x));
		bb._put(bi, long0(x));
	}

	static void putLongB (ByteBuffer bb, int bi, long x) {
		bb._put(bi, long7(x));
		bb._put(bi + 1, long6(x));
		bb._put(bi + 2, long5(x));
		bb._put(bi + 3, long4(x));
		bb._put(bi + 4, long3(x));
		bb._put(bi + 5, long2(x));
		bb._put(bi + 6, long1(x));
		bb._put(bi + 7, long0(x));
	}

	static void putLong (ByteBuffer bb, int bi, long x, boolean bigEndian) {
		if (bigEndian)
			putLongB(bb, bi, x);
		else
			putLongL(bb, bi, x);
	}

	static float getFloatL (ByteBuffer bb, int bi) {
		return Float.intBitsToFloat(getIntL(bb, bi));
	}

	static float getFloatB (ByteBuffer bb, int bi) {
		return Float.intBitsToFloat(getIntB(bb, bi));
	}

	static float getFloat (ByteBuffer bb, int bi, boolean bigEndian) {
		return bigEndian ? getFloatB(bb, bi) : getFloatL(bb, bi);
	}

	static void putFloatL (ByteBuffer bb, int bi, float x) {
		putIntL(bb, bi, Float.floatToIntBits(x));
	}

	static void putFloatB (ByteBuffer bb, int bi, float x) {
		putIntB(bb, bi, Float.floatToIntBits(x));
	}

	static void putFloat (ByteBuffer bb, int bi, float x, boolean bigEndian) {
		if (bigEndian)
			putFloatB(bb, bi, x);
		else
			putFloatL(bb, bi, x);
	}

	static double getDoubleL (ByteBuffer bb, int bi) {
		return Double.longBitsToDouble(getLongL(bb, bi));
	}

	static double getDoubleB (ByteBuffer bb, int bi) {
		return Double.longBitsToDouble(getLongB(bb, bi));
	}

	static double getDouble (ByteBuffer bb, int bi, boolean bigEndian) {
		return bigEndian ? getDoubleB(bb, bi) : getDoubleL(bb, bi);
	}

	static void putDoubleL (ByteBuffer bb, int bi, double x) {
		putLongL(bb, bi, Double.doubleToLongBits(x));
	}

	static void putDoubleB (ByteBuffer bb, int bi, double x) {
		putLongB(bb, bi, Double.doubleToLongBits(x));
	}

	static void putDouble (ByteBuffer bb, int bi, double x, boolean bigEndian) {
		if (bigEndian)
			putDoubleB(bb, bi, x);
		else
			putDoubleL(bb, bi, x);
	}

	private static boolean unaligned;
	private static boolean unalignedKnown = false;

	static boolean unaligned () {
		if (unalignedKnown)
			return unaligned;
		String arch = System.getProperty("os.arch");
		unaligned = arch.equals("i386") || arch.equals("x86") || arch.equals("amd64") || arch.equals("x86_64") || arch.equals("ppc64") || arch.equals("ppc64le") || arch.equals("aarch64");
		unalignedKnown = true;
		return unaligned;
	}

	private static boolean isPrimitiveArray (Class<?> c) {
		Class<?> componentType = c.getComponentType();
		return componentType != null && componentType.isPrimitive();
	}
}
