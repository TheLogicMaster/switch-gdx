package com.thelogicmaster.test;

import com.badlogic.gdx.controllers.Controller;
import com.badlogic.gdx.controllers.Controllers;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.tests.utils.GdxTest;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.utils.ScreenUtils;

public class SwitchControllerTest extends GdxTest {

	private ShapeRenderer shapeRenderer;
	private BitmapFont font;
	private SpriteBatch batch;
	private final Vector2[] positions = new Vector2[8];
	private final static Color[] COLORS = {Color.BROWN, Color.BLUE, Color.RED, Color.CHARTREUSE, Color.CORAL, Color.GRAY, Color.GREEN, Color.FIREBRICK};

	@Override
	public void create () {
		shapeRenderer = new ShapeRenderer();
		shapeRenderer.setAutoShapeType(true);
		font = new BitmapFont();
		font.setColor(Color.CYAN);
		batch = new SpriteBatch();

		for (int i = 0; i < 8; i++)
			positions[i] = new Vector2(300 + 50 * i, 300);
	}

	@Override
	public void render () {
		ScreenUtils.clear(Color.BLACK);

		Array<Controller> controllers = Controllers.getControllers();

		batch.begin();
		font.draw(batch, "Controllers: " + controllers.size, 50, 50);
		batch.end();

		shapeRenderer.begin();

		shapeRenderer.set(ShapeRenderer.ShapeType.Line);
		for (int i = 0; i < controllers.size; i++) {
			shapeRenderer.setColor(COLORS[i]);
			Vector2 position = positions[i];
			Controller controller = controllers.get(i);

			position.x += controller.getAxis(0);
			position.y -= controller.getAxis(1);

			shapeRenderer.circle(position.x, position.y, 10);
		}

		shapeRenderer.end();
	}

	@Override
	public void dispose () {
		shapeRenderer.dispose();
		font.dispose();
	}
}
