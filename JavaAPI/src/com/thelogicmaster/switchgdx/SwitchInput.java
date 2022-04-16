package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;

public class SwitchInput implements Input {

	private static final int MAX_TOUCHES = 16;

	private InputProcessor inputProcessor;
	private long currentEventTimeStamp;
	private final int[] touchData = new int[MAX_TOUCHES * 3];
	private final int[] previousTouchData = new int[MAX_TOUCHES * 3];
	private final int[] rawTouchIds = new int[MAX_TOUCHES];
	private final int[] touchX = new int[MAX_TOUCHES];
	private final int[] touchY = new int[MAX_TOUCHES];
	private final int[] deltaX = new int[MAX_TOUCHES];
	private final int[] deltaY = new int[MAX_TOUCHES];
	private final boolean[] touched = new boolean[MAX_TOUCHES];
	private boolean wasJustTouched;

	public SwitchInput () {
		for (int i = 0; i < MAX_TOUCHES; i++) {
			previousTouchData[i * 3] = -1;
			rawTouchIds[i] = -1;
		}
	}

	void update() {
		currentEventTimeStamp = System.currentTimeMillis();
		wasJustTouched = false;
		getTouchData(touchData);

		// Todo: There's probably a better way to optimize this

		for (int i = 0; i < MAX_TOUCHES; i++) {
			int rawIndex = touchData[i * 3];
			if (rawIndex == -1)
				continue;
			int previousIndex = -1;
			for (int j = 0; j < MAX_TOUCHES; j++)
				if (previousTouchData[j * 3] == rawIndex) {
					previousIndex = j;
					break;
				}
			if (previousIndex == -1) {
				wasJustTouched = true;
				for (int j = 0; j < MAX_TOUCHES; j++)
					if (rawTouchIds[j] == -1) {
						touchX[j] = touchData[i * 3 + 1];
						touchY[j] = touchData[i * 3 + 2];
						touched[j] = true;
						rawTouchIds[j] = rawIndex;
						if (inputProcessor != null)
							inputProcessor.touchDown(touchData[i * 3 + 1], touchData[i * 3 + 2], j, 0);
						break;
					}
			} else if (touchData[i * 3 + 1] != previousTouchData[previousIndex * 3 + 1] || touchData[i * 3 + 2] != previousTouchData[previousIndex * 3 + 2]) {
				for (int j = 0; j < MAX_TOUCHES; j++)
					if (rawTouchIds[j] == rawIndex) {
						deltaX[j] = touchData[i * 3 + 1] - touchX[j];
						deltaY[j] = touchData[i * 3 + 2] - touchY[j];
						touchX[j] = touchData[i * 3 + 1];
						touchY[j] = touchData[i * 3 + 2];
						if (inputProcessor != null)
							inputProcessor.touchDragged(touchData[i * 3 + 1], touchData[i * 3 + 2], j);
						break;
					}
			}
		}

		for (int i = 0; i < MAX_TOUCHES; i++) {
			int rawPreviousIndex = previousTouchData[i * 3];
			if (rawPreviousIndex == -1)
				continue;
			int index = -1;
			for (int j = 0; j < MAX_TOUCHES; j++)
				if (touchData[j * 3] == rawPreviousIndex) {
					index = j;
					break;
				}
			if (index == -1) {
				for (int j = 0; j < MAX_TOUCHES; j++)
					if (rawTouchIds[j] == rawPreviousIndex) {
						touchX[j] = previousTouchData[i * 3 + 1];
						touchY[j] = previousTouchData[i * 3 + 2];
						deltaX[j] = 0;
						deltaY[j] = 0;
						touched[j] = false;
						rawTouchIds[j] = -1;
						if (inputProcessor != null)
							inputProcessor.touchUp(previousTouchData[i * 3 + 1], previousTouchData[i * 3 + 2], j, 0);
						break;
					}
			}
		}

		System.arraycopy(touchData, 0, previousTouchData, 0, MAX_TOUCHES * 3);
	}

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
		return MAX_TOUCHES;
	}

	@Override
	public int getX () {
		return touchX[0];
	}

	@Override
	public int getX (int pointer) {
		return touchX[pointer];
	}

	@Override
	public int getDeltaX () {
		return deltaX[0];
	}

	@Override
	public int getDeltaX (int pointer) {
		return deltaX[pointer];
	}

	@Override
	public int getY () {
		return touchY[0];
	}

	@Override
	public int getY (int pointer) {
		return touchY[pointer];
	}

	@Override
	public int getDeltaY () {
		return deltaY[0];
	}

	@Override
	public int getDeltaY (int pointer) {
		return deltaY[pointer];
	}

	@Override
	public boolean isTouched () {
		return touched[0];
	}

	@Override
	public boolean justTouched () {
		return wasJustTouched;
	}

	@Override
	public boolean isTouched (int pointer) {
		return touched[pointer];
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
		return button == 0 && isTouched();
	}

	@Override
	public boolean isButtonJustPressed (int button) {
		return button == 0 && justTouched();
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

	private static native void getTouchData(int[] touchData);
}