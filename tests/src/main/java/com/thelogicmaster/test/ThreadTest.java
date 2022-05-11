package com.thelogicmaster.test;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.tests.utils.GdxTest;

public class ThreadTest extends GdxTest {

	private final Object lock = new Object();

	private volatile boolean notified;

	@Override
	public void create () {
		new Thread(() -> {
			try {
				Thread.currentThread().interrupt();
				Thread.sleep(1);
				Gdx.app.log("Preemptive interrupt", "fail");
			} catch (InterruptedException e) {
				Gdx.app.log("Preemptive interrupt", "success");
			}
		}).start();

		Thread thread = new Thread(() -> {
			try {
				Thread.sleep(100);
				Gdx.app.log("Sleep interrupt", "fail");
			} catch (InterruptedException e) {
				Gdx.app.log("Sleep interrupt", "success");
			}
		});
		thread.start();

		new Thread(() -> {
			try {
				Thread.sleep(50);
			} catch (InterruptedException ignored) {}
			Gdx.app.log("Sleep interrupt", "Interrupting thread...");
			thread.interrupt();
		}).start();

		new Thread(() -> {
			try {
				Thread.sleep(100);
				Gdx.app.log("No interrupt", "success");
			} catch (InterruptedException e) {
				Gdx.app.log("No interrupt", "fail");
			}
		}).start();

		new Thread(() -> {
			try {
				synchronized (lock) {
					lock.wait(25);
					Gdx.app.log("Wait timeout", notified ? "fail" : "success");
				}
			} catch (InterruptedException e) {
				Gdx.app.log("Wait timeout", "fail");
			}
		}).start();

		new Thread(() -> {
			try {
				synchronized (lock) {
					lock.wait(75);
					Gdx.app.log("Wait no-timeout", notified ? "success" : "fail");
				}
			} catch (InterruptedException e) {
				Gdx.app.log("Wait no-timeout", "fail");
			}
		}).start();

		new Thread(() -> {
			try {
				synchronized (lock) {
					lock.wait();
					Gdx.app.log("Wait forever", "success");
				}
			} catch (InterruptedException e) {
				Gdx.app.log("Wait forever", "fail");
			}
		}).start();

		Thread thread2 = new Thread(() -> {
			try {
				try {
					Thread.sleep(125);
				} catch (InterruptedException ignored) {}

				// Todo: Bug concerning try-catch around synchronized block
				synchronized (lock) {
					lock.wait();
					Gdx.app.log("Wait interrupt", "fail");
				}
			} catch (InterruptedException e) {
				Gdx.app.log("Wait interrupt", "success");
			}
		});
		thread2.start();

		new Thread(() -> {
			try {
				Thread.sleep(50);

				Gdx.app.log("Wait", "Notifying...");
				synchronized (lock) {
					lock.notifyAll();
					notified = true;
				}

				Thread.sleep(50);

				Gdx.app.log("Wait", "Notifying...");
				synchronized (lock) {
					lock.notifyAll();
				}

				Thread.sleep(50);
				Gdx.app.log("Wait", "Interrupting...");
				thread2.interrupt();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}).start();
	}
}
