package com.thelogicmaster.test;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.tests.utils.GdxTest;

public class JniGenTest extends GdxTest {

	private static native int test(int a, int b); /*
		return a + b;
	*/

	@Override
	public void create () {
		Gdx.app.log("JniGenTest", "test(1, 2) = " + test(1, 2));
	}
}
