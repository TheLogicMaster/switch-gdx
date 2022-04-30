package com.thelogicmaster.test;

import com.badlogic.gdx.controllers.ControllerMapping;
import com.badlogic.gdx.controllers.Controllers;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.tests.utils.GdxTest;
import com.badlogic.gdx.utils.ScreenUtils;

public class SwitchInputTest extends GdxTest {

	private ShapeRenderer shapeRenderer;
	private ControllerMapping mapping = Controllers.getCurrent().getMapping();

	@Override
	public void create () {
		shapeRenderer = new ShapeRenderer();
		shapeRenderer.setAutoShapeType(true);
	}

	@Override
	public void render () {
		ScreenUtils.clear(Color.BLACK);

		shapeRenderer.begin();

		shapeRenderer.set(ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(200, 720 - 200, 100);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonLeftStick) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(200 + 50 * Controllers.getCurrent().getAxis(mapping.axisLeftX), 720 - 200 + 50 * Controllers.getCurrent().getAxis(mapping.axisLeftY), 50);

		shapeRenderer.set(ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 - 200, 200, 100);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonRightStick) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 - 200 + 50 * Controllers.getCurrent().getAxis(mapping.axisRightX), 200 + 50 * Controllers.getCurrent().getAxis(mapping.axisRightY), 50);

		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonDpadUp) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(200, 200 + 50, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonDpadDown) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(200, 200 - 50, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonDpadLeft) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(200 - 50, 200, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonDpadRight) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(200 + 50, 200, 25);

		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonX) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 - 200, 720 - 200 + 50, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonB) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 - 200, 720 - 200 - 50, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonY) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 - 200 - 50, 720 - 200, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonA) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 - 200 + 50, 720 - 200, 25);

		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonL1) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.rect(100, 720 - 30, 200, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonL2) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.rect(100, 720 - 75, 200, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonR1) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.rect(1280 - 300, 720 - 30, 200, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonR2) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.rect(1280 - 300, 720 - 75, 200, 25);

		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonBack) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 / 2f - 100, 720 / 2f, 25);
		shapeRenderer.set(Controllers.getCurrent().getButton(mapping.buttonStart) ? ShapeRenderer.ShapeType.Filled : ShapeRenderer.ShapeType.Line);
		shapeRenderer.circle(1280 / 2f + 100, 720 / 2f, 25);

		shapeRenderer.end();
	}

	@Override
	public void dispose () {
		shapeRenderer.dispose();
	}
}
