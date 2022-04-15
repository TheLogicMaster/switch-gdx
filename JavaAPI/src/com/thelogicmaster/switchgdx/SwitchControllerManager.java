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
		System.arraycopy(controller.axes, 0, controller.prevAxes, 0, 4);
		getAxes(controller.axes);
		controller.prevButtons = controller.buttons;
		controller.buttons = getButtons();

		int pressed = controller.buttons & ~controller.prevButtons;
		int released = ~controller.buttons & controller.prevButtons;
		for (int i = 0; i < 32; i++) {
			if ((pressed & 1 << i) != 0)
				for (ControllerListener listener: listeners)
					listener.buttonDown(controller, i);
			if ((released & 1 << i) != 0)
				for (ControllerListener listener: listeners)
					listener.buttonUp(controller, i);
		}

		for (int i = 0; i < 4; i++)
			if (controller.axes[i] != controller.prevAxes[i])
				for (ControllerListener listener: listeners)
					listener.axisMoved(controller, i, controller.axes[i]);
	}

	static SwitchControllerManager getInstance () {
		return instance;
	}

	private static native int getButtons();

	private static native void getAxes(float[] axes);
}
