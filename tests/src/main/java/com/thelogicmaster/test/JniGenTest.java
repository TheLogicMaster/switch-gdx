package com.thelogicmaster.test;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.tests.utils.GdxTest;
import com.badlogic.gdx.utils.BufferUtils;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.DoubleBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.nio.LongBuffer;
import java.nio.ShortBuffer;

public class JniGenTest extends GdxTest {

	private static native int sum (int a, int b); /*
		return a + b;
	*/

	private static native int sum (ByteBuffer buffer, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += buffer[i];
		return sum;
	*/

	private static native int sum (ShortBuffer buffer, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += buffer[i];
		return sum;
	*/

	private static native int sum (IntBuffer buffer, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += buffer[i];
		return sum;
	*/

	private static native int sum (LongBuffer buffer, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += buffer[i];
		return sum;
	*/

	private static native int sum (CharBuffer buffer, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += buffer[i];
		return sum;
	*/

	private static native int sum (FloatBuffer buffer, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += buffer[i];
		return sum;
	*/

	private static native int sum (DoubleBuffer buffer, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += buffer[i];
		return sum;
	*/

	private static native int sum (byte[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	private static native int sum (short[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	private static native int sum (int[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	private static native int sum (long[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	private static native int sum (char[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	private static native int sum (float[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	private static native int sum (double[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	private static native int sum (boolean[] array, int len); /*
		int sum = 0;
		for (int i = 0; i < len; i++)
			sum += array[i];
		return sum;
	*/

	@Override
	public void create () {
		Gdx.app.log("JNI Primitives", "sum(1, 2) = " + sum(1, 2));

		ByteBuffer buffer = BufferUtils.newByteBuffer(16);
		buffer.put((byte)1);
		buffer.put((byte)2);
		buffer.put((byte)3);
		buffer.put((byte)4);
		Gdx.app.log("JNI ByteBuffer", "sum(1, 2, 3, 4) = " + sum(buffer, 4));
		buffer.clear();

		ShortBuffer shortBuffer = buffer.asShortBuffer();
		shortBuffer.put((short)1);
		shortBuffer.put((short)2);
		shortBuffer.put((short)3);
		shortBuffer.put((short)4);
		Gdx.app.log("JNI ShortBuffer", "sum(1, 2, 3, 4) = " + sum(shortBuffer, 4));
		buffer.clear();

		IntBuffer intBuffer = buffer.asIntBuffer();
		intBuffer.put(1);
		intBuffer.put(2);
		intBuffer.put(3);
		intBuffer.put(4);
		Gdx.app.log("JNI IntBuffer", "sum(1, 2, 3, 4) = " + sum(intBuffer, 4));
		buffer.clear();

		LongBuffer longBuffer = buffer.asLongBuffer();
		longBuffer.put(1);
		longBuffer.put(2);
		Gdx.app.log("JNI LongBuffer", "sum(1, 2) = " + sum(longBuffer, 2));
		buffer.clear();

		CharBuffer charBuffer = buffer.asCharBuffer();
		charBuffer.put((char)1);
		charBuffer.put((char)2);
		charBuffer.put((char)3);
		charBuffer.put((char)4);
		Gdx.app.log("JNI CharBuffer", "sum(1, 2, 3, 4) = " + sum(charBuffer, 4));
		buffer.clear();

		FloatBuffer floatBuffer = buffer.asFloatBuffer();
		floatBuffer.put(1);
		floatBuffer.put(2);
		floatBuffer.put(3);
		floatBuffer.put(4);
		Gdx.app.log("JNI FloatBuffer", "sum(1, 2, 3, 4) = " + sum(floatBuffer, 4));
		buffer.clear();

		DoubleBuffer doubleBuffer = buffer.asDoubleBuffer();
		doubleBuffer.put(1);
		doubleBuffer.put(2);
		Gdx.app.log("JNI DoubleBuffer", "sum(1, 2) = " + sum(doubleBuffer, 2));

		Gdx.app.log("JNI byte[]", "sum(1, 2, 3, 4) = " + sum(new byte[]{1, 2, 3, 4}, 4));
		Gdx.app.log("JNI short[]", "sum(1, 2, 3, 4) = " + sum(new short[]{1, 2, 3, 4}, 4));
		Gdx.app.log("JNI int[]", "sum(1, 2, 3, 4) = " + sum(new int[]{1, 2, 3, 4}, 4));
		Gdx.app.log("JNI long[]", "sum(1, 2) = " + sum(new long[]{1, 2}, 2));
		Gdx.app.log("JNI char[]", "sum(1, 2, 3, 4) = " + sum(new char[]{1, 2, 3, 4}, 4));
		Gdx.app.log("JNI float[]", "sum(1, 2, 3, 4) = " + sum(new float[]{1, 2, 3, 4}, 4));
		Gdx.app.log("JNI double[]", "sum(1, 2) = " + sum(new double[]{1, 2}, 2));
		Gdx.app.log("JNI boolean[]", "sum(1, 1) = " + sum(new boolean[]{true, true}, 2));
	}
}
