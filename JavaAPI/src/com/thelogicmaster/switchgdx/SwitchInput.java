package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;

public class SwitchInput implements Input {

	private InputProcessor inputProcessor;
	private long currentEventTimeStamp;

	@Override
	public float getAccelerometerX () {
		return 0;
	}

	@Override
	public float getAccelerometerY () {
		return 0;
	}

	@Override
	public float getAccelerometerZ () {
		return 0;
	}

	@Override
	public float getGyroscopeX () {
		return 0;
	}

	@Override
	public float getGyroscopeY () {
		return 0;
	}

	@Override
	public float getGyroscopeZ () {
		return 0;
	}

	@Override
	public int getMaxPointers () {
		return 0;
	}

	@Override
	public int getX () {
		return 0;
	}

	@Override
	public int getX (int pointer) {
		return 0;
	}

	@Override
	public int getDeltaX () {
		return 0;
	}

	@Override
	public int getDeltaX (int pointer) {
		return 0;
	}

	@Override
	public int getY () {
		return 0;
	}

	@Override
	public int getY (int pointer) {
		return 0;
	}

	@Override
	public int getDeltaY () {
		return 0;
	}

	@Override
	public int getDeltaY (int pointer) {
		return 0;
	}

	@Override
	public boolean isTouched () {
		return false;
	}

	@Override
	public boolean justTouched () {
		return false;
	}

	@Override
	public boolean isTouched (int pointer) {
		return false;
	}

	@Override
	public float getPressure () {
		return 0;
	}

	@Override
	public float getPressure (int pointer) {
		return 0;
	}

	@Override
	public boolean isButtonPressed (int button) {
		return false;
	}

	@Override
	public boolean isButtonJustPressed (int button) {
		return false;
	}

	@Override
	public boolean isKeyPressed (int key) {
		return false;
	}

	@Override
	public boolean isKeyJustPressed (int key) {
		return false;
	}

	@Override
	public void getTextInput (TextInputListener listener, String title, String text, String hint) {
		getTextInput(listener, title, text, hint, OnscreenKeyboardType.Default);
	}

	@Override
	public native void getTextInput (TextInputListener listener, String title, String text, String hint, OnscreenKeyboardType type);

	@Override
	public void setOnscreenKeyboardVisible (boolean visible) {
		setOnscreenKeyboardVisible(visible, OnscreenKeyboardType.Default);
	}

	@Override
	public native void setOnscreenKeyboardVisible (boolean visible, OnscreenKeyboardType type);

	@Override
	public void vibrate (int milliseconds) {

	}

	@Override
	public void vibrate (long[] pattern, int repeat) {

	}

	@Override
	public void cancelVibrate () {

	}

	@Override
	public float getAzimuth () {
		return 0;
	}

	@Override
	public float getPitch () {
		return 0;
	}

	@Override
	public float getRoll () {
		return 0;
	}

	@Override
	public void getRotationMatrix (float[] matrix) {

	}

	@Override
	public long getCurrentEventTime () {
		return currentEventTimeStamp;
	}

	@Override
	public void setCatchBackKey (boolean catchBack) {

	}

	@Override
	public boolean isCatchBackKey () {
		return false;
	}

	@Override
	public void setCatchMenuKey (boolean catchMenu) {

	}

	@Override
	public boolean isCatchMenuKey () {
		return false;
	}

	@Override
	public void setCatchKey (int keycode, boolean catchKey) {

	}

	@Override
	public boolean isCatchKey (int keycode) {
		return false;
	}

	@Override
	public void setInputProcessor (InputProcessor processor) {
		inputProcessor = processor;
	}

	@Override
	public InputProcessor getInputProcessor () {
		return inputProcessor;
	}

	@Override
	public boolean isPeripheralAvailable (Peripheral peripheral) {
		switch (peripheral) {
		case Vibrator:
		case OnscreenKeyboard:
		case MultitouchScreen:
			return true;
		default:
			return false;
		}
	}

	@Override
	public int getRotation () {
		return 0;
	}

	@Override
	public Orientation getNativeOrientation () {
		return Orientation.Landscape;
	}

	@Override
	public void setCursorCatched (boolean catched) {

	}

	@Override
	public boolean isCursorCatched () {
		return false;
	}

	@Override
	public void setCursorPosition (int x, int y) {

	}
}
