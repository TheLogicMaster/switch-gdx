package com.thelogicmaster.test;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputAdapter;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.controllers.Controller;
import com.badlogic.gdx.controllers.ControllerListener;
import com.badlogic.gdx.controllers.Controllers;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.VertexAttributes;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g3d.Environment;
import com.badlogic.gdx.graphics.g3d.Material;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelBatch;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.attributes.BlendingAttribute;
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute;
import com.badlogic.gdx.graphics.g3d.environment.DirectionalLight;
import com.badlogic.gdx.graphics.g3d.loader.G3dModelLoader;
import com.badlogic.gdx.graphics.g3d.utils.ModelBuilder;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Quaternion;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.utils.UBJsonReader;

import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public class TestApp implements ApplicationListener {

	private static final float[] VERTICES = new float[]{
		// Base
		-1, -1, -1,
		-1, -1, 1,
		-1, -1, 1,
		1, -1, 1,
		1, -1, 1,
		1, -1, -1,
		1, -1, -1,
		-1, -1, -1,

		// Sides
		-1, -1, -1,
		0, 1, 0,
		-1, -1, 1,
		0, 1, 0,
		1, -1, -1,
		0, 1, 0,
		1, -1, 1,
		0, 1, 0
	};

	private static final String VERTEX_SHADER = "" +
		"uniform mat4 uMVPMatrix;" +
		"attribute vec4 vPosition;" +
		"void main() {" +
		"  gl_Position = uMVPMatrix * vPosition;" +
		"}";
	private static final String FRAGMENT_SHADER = "" +
		"uniform vec4 vColor;" +
		"void main() {" +
		"  gl_FragColor = vColor;" +
		"}";

	private int shader;
	private FloatBuffer vertexBuffer;
	private final Matrix4 vPMatrix = new Matrix4();
	private final Matrix4 projectionMatrix = new Matrix4();
	private final Matrix4 viewMatrix = new Matrix4();

	private AssetManager assets;

	private SpriteBatch spriteBatch;
	private Texture texture;
	private ShapeRenderer shapeRenderer;
	private Pixmap pixmap;
	private Texture pixmapTexture;

	private Environment environment;
	PerspectiveCamera camera;
	Model model, robot;
	ModelInstance modelInstance, robotInstance;
	ModelBatch modelBatch;

	private boolean running = true;

	@Override
	public void create () {
		System.out.println("Hello World!");

		System.out.println("os.arch: " + System.getProperty("os.arch"));

		File file = new File("test.txt");
		System.out.println("test.txt exists: " + file.exists());
		try {
			FileInputStream fileInputStream = new FileInputStream(file);
			byte[] bytes = new byte[fileInputStream.available()];
			int read = fileInputStream.read(bytes);
			System.out.println("Read: " + read + " " + new String(bytes));
		} catch (IOException e) {
			e.printStackTrace();
		}

		file = new File("test2.txt");
		try {
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file)));
			writer.write("test2\n");
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		Preferences prefs = Gdx.app.getPreferences("Test");
		Gdx.app.log("Pref Test", prefs.getString("value", "Value not set"));
		prefs.putString("value", "Value set");
		prefs.flush();

		FileHandle fileHandle = Gdx.files.internal("test.png");
		System.out.println("test.png path: " + fileHandle.file().getPath());
		System.out.println("Exists: " + fileHandle.exists());

		assets = new AssetManager();

		shapeRenderer = new ShapeRenderer();

		spriteBatch = new SpriteBatch();
		spriteBatch.disableBlending();

		texture = new Texture("test.png");
//		texture.getTextureData().prepare();
//		Pixmap pixmap = texture.getTextureData().consumePixmap();
//		System.out.println(pixmap.getPixel(127, 127));

		pixmap = new Pixmap(128, 128, Pixmap.Format.RGB888);
		pixmap.setColor(Color.GREEN);
		pixmap.fill();
		pixmap.setColor(Color.BROWN);
		pixmap.fillCircle(64, 64, 32);
		pixmapTexture = new Texture(pixmap);

		environment = new Environment();
		environment.add(new DirectionalLight().setDirection(-0.3f, -0.1f, -1).setColor(Color.WHITE));
		camera = new PerspectiveCamera(67, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
		camera.position.set(10f, 10f, 10f);
		camera.lookAt(0, 0, 0);
		camera.near = 1f;
		camera.far = 300f;
		camera.update();

		ModelBuilder modelBuilder = new ModelBuilder();
		model = modelBuilder.createBox(5f, 5f, 5f, new Material(ColorAttribute.createDiffuse(Color.GREEN)), VertexAttributes.Usage.Position | VertexAttributes.Usage.Normal);
		modelInstance = new ModelInstance(model);

		G3dModelLoader modelLoader = new G3dModelLoader(new UBJsonReader());
//		robot = modelLoader.loadModel(Gdx.files.internal("robot.g3db"));
		assets.load("robot.g3db", Model.class);
		assets.finishLoading();
		robot = assets.get("robot.g3db");
		for (Material mat : new Array.ArrayIterator<>(robot.materials)) {
			mat.remove(ColorAttribute.Emissive);
			mat.remove(BlendingAttribute.Type);
		}
		robotInstance = new ModelInstance(robot);
		robotInstance.transform.set(new Vector3(7, 5 ,-5), new Quaternion(), new Vector3(4, 4, 4));

		modelBatch = new ModelBatch();

//		new Thread(() -> {
//			while (running) {
//				try {
//					System.out.println("Looping...");
//					Thread.sleep(1000);
//				} catch (InterruptedException ignored) {}
//			}
//		}).start();

		vertexBuffer = ByteBuffer.allocateDirect(VERTICES.length * 4)
			.order(ByteOrder.nativeOrder())
			.asFloatBuffer();
		vertexBuffer.put(VERTICES);
		vertexBuffer.position(0);

		Gdx.gl.glBufferData(GL20.GL_ARRAY_BUFFER, VERTICES.length * 4, vertexBuffer, GL20.GL_STATIC_DRAW);

		int vertexShader = Gdx.gl.glCreateShader(GL20.GL_VERTEX_SHADER);
		int fragmentShader = Gdx.gl.glCreateShader(GL20.GL_FRAGMENT_SHADER);

		Gdx.gl.glShaderSource(vertexShader, VERTEX_SHADER);
		Gdx.gl.glCompileShader(vertexShader);
//		System.out.println("Vertex log: " + Gdx.gl.glGetShaderInfoLog(vertexShader));

		Gdx.gl.glShaderSource(fragmentShader, FRAGMENT_SHADER);
		Gdx.gl.glCompileShader(fragmentShader);
//		System.out.println("Fragment log: " + Gdx.gl.glGetShaderInfoLog(fragmentShader));

		shader = Gdx.gl.glCreateProgram();
		Gdx.gl.glAttachShader(shader, vertexShader);
		Gdx.gl.glAttachShader(shader, fragmentShader);
		Gdx.gl.glLinkProgram(shader);

//		System.out.println("Shader: " + shader + " (" + vertexShader + ", " + fragmentShader + ")");

//		Controllers.addListener(new ControllerListener() {
//			@Override
//			public void connected (Controller controller) {
//
//			}
//
//			@Override
//			public void disconnected (Controller controller) {
//
//			}
//
//			@Override
//			public boolean buttonDown (Controller controller, int buttonCode) {
//				System.out.println("Button Pressed: " + buttonCode);
//				return false;
//			}
//
//			@Override
//			public boolean buttonUp (Controller controller, int buttonCode) {
//				System.out.println("Button Released: " + buttonCode);
//				return false;
//			}
//
//			@Override
//			public boolean axisMoved (Controller controller, int axisCode, float value) {
//				System.out.println("Joystick Moved: " + axisCode + " --- " + value);
//				return false;
//			}
//		});

//		Gdx.input.setInputProcessor(new InputAdapter() {
//			@Override
//			public boolean touchDown (int screenX, int screenY, int pointer, int button) {
//				System.out.println("Touch down: (" + screenX + ", " + screenY + "): " + pointer);
//				return false;
//			}
//
//			@Override
//			public boolean touchUp (int screenX, int screenY, int pointer, int button) {
//				System.out.println("Touch up: (" + screenX + ", " + screenY + "): " + pointer);
//				return false;
//			}
//
//			@Override
//			public boolean touchDragged (int screenX, int screenY, int pointer) {
//				System.out.println("Touch dragged: (" + screenX + ", " + screenY + "): " + pointer);
//				return false;
//			}
//		});
	}

	@Override
	public void resize (int width, int height) {
		Gdx.gl.glViewport(0, 0, width, height);
		projectionMatrix.setToProjection(1, 100, 90, (float)width / height);
	}

	@Override
	public void render () {
		Controller controller = Controllers.getCurrent();

		if (controller != null) {
			Vector3 horizontal = camera.direction.cpy().crs(camera.up).nor().scl(controller.getAxis(2) / 3);
			Vector3 vertical = camera.direction.cpy().nor().scl(controller.getAxis(3) / 3);
			camera.translate(horizontal.add(vertical));

			if (controller.getButton(0))
				camera.translate(0, 0.1f, 0);
			else if (controller.getButton(1))
				camera.translate(0, -0.1f, 0);

			camera.direction.rotate(camera.up, controller.getAxis(0) * -1);
			camera.direction.rotate(camera.direction.cpy().crs(camera.up).nor(), controller.getAxis(1));

			camera.update();
		}

//		System.out.println("getX: " + Gdx.input.getX() + ", getY: " + Gdx.input.getY() + ", touched: " + Gdx.input.isTouched() + ", justTouched: " + Gdx.input.justTouched());

		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
		Gdx.gl.glClearColor(0, 0, 1, 1);

		modelBatch.begin(camera);
		modelBatch.render(modelInstance, environment);
		modelBatch.render(robotInstance);
		modelBatch.end();

		spriteBatch.begin();
		spriteBatch.draw(texture, 0, 0);
		spriteBatch.draw(pixmapTexture, 1000, 100);
		spriteBatch.end();

		shapeRenderer.begin(ShapeRenderer.ShapeType.Filled);
		shapeRenderer.circle(150, 500, 50);
		shapeRenderer.end();

		viewMatrix.setToLookAt(new Vector3(0, 0, 3), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
		vPMatrix.set(projectionMatrix).mul(viewMatrix);

		Gdx.gl.glUseProgram(shader);
		int positionHandle = Gdx.gl.glGetAttribLocation(shader, "vPosition");
		Gdx.gl.glEnableVertexAttribArray(positionHandle);
		Gdx.gl.glVertexAttribPointer(positionHandle, 3, GL20.GL_FLOAT, false, 12, vertexBuffer);

		int colorHandle = Gdx.gl.glGetUniformLocation(shader, "vColor");
		Gdx.gl.glUniform4fv(colorHandle, 1, new float[]{1, 0, 0, 1}, 0);

		int vPMatrixHandle = Gdx.gl.glGetUniformLocation(shader, "uMVPMatrix");
		Gdx.gl.glUniformMatrix4fv(vPMatrixHandle, 1, false, vPMatrix.val, 0);

		Gdx.gl.glDrawArrays(GL20.GL_LINES, 0, VERTICES.length / 3);
		Gdx.gl.glDisableVertexAttribArray(positionHandle);

//		Gdx.app.exit();
	}

	@Override
	public void pause () {

	}

	@Override
	public void resume () {

	}

	@Override
	public void dispose () {
		pixmap.dispose();
		shapeRenderer.dispose();
		running = false;
		spriteBatch.dispose();
		modelBatch.dispose();
		model.dispose();
//		robot.dispose();
		assets.dispose();
	}
}
