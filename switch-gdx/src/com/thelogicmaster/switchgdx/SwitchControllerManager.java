package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.controllers.Controller;
import com.badlogic.gdx.controllers.ControllerListener;
import com.badlogic.gdx.controllers.ControllerManager;
import com.badlogic.gdx.utils.Array;

public class SwitchControllerManager implements ControllerManager {

	private final Array<ControllerListener> listeners = new Array<>();
	private final Array<Controller> controllers = new Array<>();
	private final SwitchController combinedController;

	private static SwitchControllerManager instance;

	public SwitchControllerManager () {
		instance = this;
		combinedController = new SwitchController(-1);

		update();
	}

	@Override
	public Array<Controller> getControllers () {
		return controllers;
	}

	@Override
	public Controller getCurrentController () {
		return combinedController;
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
		updateController(combinedController, -1);

		int toRemove = 0;

		for (int i = 0; i < 8; i++) {
			if (!isConnected(i)) {
				if (controllers.size > i)
					toRemove++;
				continue;
			} else if (controllers.size <= i) {
				controllers.add(new SwitchController(i));
				for (ControllerListener listener: listeners)
					listener.connected(controllers.peek());
			}

			SwitchController controller = (SwitchController)controllers.get(i);
			updateController(controller, i);
		}

		for (int i = 0; i < toRemove; i++) {
			Controller removed = controllers.pop();
			((SwitchController)removed).dispose();
		for (ControllerListener listener: ((SwitchController)removed).listeners)
				listener.disconnected(removed);
			for (ControllerListener listener: listeners)
				listener.disconnected(removed);
		}
	}

	private void updateController(SwitchController controller, int index) {
		System.arraycopy(controller.axes, 0, controller.prevAxes, 0, 4);
		getAxes(index, controller.axes);
		controller.prevButtons = controller.buttons;
		controller.buttons = getButtons(index);

		int pressed = controller.buttons & ~controller.prevButtons;
		int released = ~controller.buttons & controller.prevButtons;
		for (int i = 0; i < 32; i++) {
			if ((pressed & 1 << i) != 0) {
				if (index != -1)
					for (ControllerListener listener : listeners)
						listener.buttonDown(controller, i);
				for (ControllerListener listener : controller.listeners)
					listener.buttonDown(controller, i);
			}
			if ((released & 1 << i) != 0) {
				if (index != -1)
					for (ControllerListener listener : listeners)
						listener.buttonUp(controller, i);
				for (ControllerListener listener : controller.listeners)
					listener.buttonUp(controller, i);
			}
		}

		for (int i = 0; i < 4; i++)
			if (controller.axes[i] != controller.prevAxes[i]) {
				if (index != -1)
					for (ControllerListener listener : listeners)
						listener.axisMoved(controller, i, controller.axes[i]);
				for (ControllerListener listener : controller.listeners)
					listener.axisMoved(controller, i, controller.axes[i]);
			}
	}

	static SwitchControllerManager getInstance () {
		return instance;
	}

	private static native int getButtons(int controller);

	private static native void getAxes(int controller, float[] axes);

	private static native boolean isConnected(int controller);

	private static native void remapControllers(int min, int max, boolean enableDualJoy, boolean enableSingle);
}
