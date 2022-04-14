package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.ApplicationLogger;

public class SwitchLogger implements ApplicationLogger {

	@Override
	public void log (String tag, String message) {
		System.out.println(tag + ": " + message);
	}

	@Override
	public void log (String tag, String message, Throwable exception) {
		log(tag, message + ": " + exception);
	}

	@Override
	public void error (String tag, String message) {
		System.err.println(tag + ": " + message);
	}

	@Override
	public void error (String tag, String message, Throwable exception) {
		error(tag, message + ": " + exception);
	}

	@Override
	public void debug (String tag, String message) {
		System.out.println(tag + ": " + message);
	}

	@Override
	public void debug (String tag, String message, Throwable exception) {
		debug(tag, message + ": " + exception);
	}
}
