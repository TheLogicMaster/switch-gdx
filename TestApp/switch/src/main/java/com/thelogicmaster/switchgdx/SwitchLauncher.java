package com.thelogicmaster.switchgdx;

import com.thelogicmaster.test.TestApp;

public class SwitchLauncher {

	public static void main (String[] arg) {
		try {
			new SwitchApplication(new TestApp());
		} catch (Exception e) {
			e.printStackTrace();
			System.err.println(e.getMessage());
		}
	}
}
