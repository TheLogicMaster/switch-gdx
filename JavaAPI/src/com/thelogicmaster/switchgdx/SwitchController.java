package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.controllers.Controller;
import com.badlogic.gdx.controllers.ControllerListener;
import com.badlogic.gdx.controllers.ControllerMapping;
import com.badlogic.gdx.controllers.ControllerPowerLevel;
import com.badlogic.gdx.utils.Array;

public class SwitchController implements Controller {

	private final Array<ControllerListener> listeners = new Array<>();
	final float[] axes = new float[4];
	int buttons;

	@Override
	public boolean getButton (int buttonCode) {
		return (buttons & (1 << buttonCode)) != 0;
	}

	@Override
	public float getAxis (int axisCode) {
		return axes[axisCode];
	}

	@Override
	public String getName () {
		return "Switch Controller";
	}

	@Override
	public String getUniqueId () {
		return "Switch Controller";
	}

	@Override
	public int getMinButtonIndex () {
		return 0;
	}

	@Override
	public int getMaxButtonIndex () {
		return 31;
	}

	@Override
	public int getAxisCount () {
		return 4;
	}

	@Override
	public boolean isConnected () {
		return true;
	}

	@Override
	public boolean canVibrate () {
		return false;
	}

	@Override
	public boolean isVibrating () {
		return false;
	}

	@Override
	public void startVibration (int duration, float strength) {

	}

	@Override
	public void cancelVibration () {

	}

	@Override
	public boolean supportsPlayerIndex () {
		return false;
	}

	@Override
	public int getPlayerIndex () {
		return Controller.PLAYER_IDX_UNSET;
	}

	@Override
	public void setPlayerIndex (int index) {

	}

	@Override
	public ControllerMapping getMapping () {
		return SwitchControllerMapping.getInstance();
	}

	@Override
	public ControllerPowerLevel getPowerLevel () {
		return ControllerPowerLevel.POWER_UNKNOWN;
	}

	@Override
	public void addListener (ControllerListener listener) {
		listeners.add(listener);
	}

	@Override
	public void removeListener (ControllerListener listener) {
		listeners.removeValue(listener, true);
	}
}
