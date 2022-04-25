package com.thelogicmaster.test;

import com.thelogicmaster.switchgdx.SwitchApplication;

public class SwitchLauncher {

	public static void main (String[] arg) {
		try {
			new SwitchApplication(new SwitchTestWrapper());
		} catch (Exception e) {
			e.printStackTrace();
			System.err.println(e.getMessage());
			Throwable cause = e.getCause();
			while (cause != null) {
				System.err.println(cause.getMessage());
				cause = cause.getCause();
			}
		}
	}
}
