package com.thelogicmaster.switchgdx;

public class NativeUtils {

	public static native long getLong(long address);

	public static native void putLong(long address, long value);

	public static native int getInt(long address);

	public static native void putInt(long address, int value);

	public static native short getShort(long address);

	public static native void putShort(long address, short value);

	public static native char getChar(long address);

	public static native void putChar(long address, char value);

	public static native byte getByte(long address);

	public static native void putByte(long address, byte value);

	public static native boolean isSwitch();

	public static native Class<?> getPrimitive(String name);
}
