package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.controllers.Controller;
import com.badlogic.gdx.controllers.ControllerListener;
import com.badlogic.gdx.controllers.ControllerManager;
import com.badlogic.gdx.utils.Array;

public class SwitchControllerManager implements ControllerManager {

	private final Array<ControllerListener> listeners = new Array<>();
	private final Array<Controller> controllers = new Array<>();
	private final SwitchController controller;

	private static SwitchControllerManager instance;

	public SwitchControllerManager () {
		instance = this;
		controller = new SwitchController();
		controllers.add(controller);

		update();
	}

	@Override
	public Array<Controller> getControllers () {
		return controllers;
	}

	@Override
	public Controller getCurrentController () {
		return controller;
	}

	@Override
	public void addListener (ControllerListener listener) {
		listeners.add(listener);
	}

	@Override
	public void removeListener (ControllerListener listener) {
		listeners.removeValue(listener, true);
	}

	@Override
	public Array<ControllerListener> getListeners () {
		return listeners;
	}

	@Override
	public void clearListeners () {
		listeners.clear();
	}

	void update() {
		getAxes(controller.axes);
		controller.buttons = getButtons();
		// Todo: Event callbacks
	}

	static SwitchControllerManager getInstance () {
		return instance;
	}

	private static native int getButtons();

	private static native void getAxes(float[] axes);
}
