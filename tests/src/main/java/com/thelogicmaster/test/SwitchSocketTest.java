package com.thelogicmaster.test;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Net;
import com.badlogic.gdx.net.ServerSocket;
import com.badlogic.gdx.net.ServerSocketHints;
import com.badlogic.gdx.net.Socket;
import com.badlogic.gdx.net.SocketHints;
import com.badlogic.gdx.tests.utils.GdxTest;

import java.io.IOException;

public class SwitchSocketTest extends GdxTest {
	private ServerSocket server;

	public void create() {
		(new Thread(() -> {
			ServerSocketHints hints = new ServerSocketHints();
			hints.acceptTimeout = 1000;
			server = Gdx.net.newServerSocket(Net.Protocol.TCP, "localhost", 9999, hints);
			SocketHints clientHints = new SocketHints();
			clientHints.socketTimeout = 5000;
			Socket client = server.accept(clientHints);

			try {
				byte[] received = new byte[4];
				client.getInputStream().read(received);
				Gdx.app.log("SwitchSocketTest", "Got client message: " + new String(received));
				client.getOutputStream().write("PONG".getBytes());
				Gdx.app.log("SwitchSocketTest", "Testing server timeout...");
				client.getInputStream().read(received);
			} catch (IOException var5) {
				Gdx.app.log("SwitchSocketTest", "A server error occurred", var5);
			}

			Gdx.app.log("SwitchSocketTest", "Testing accept timeout...");
			try {
				server.accept(null);
			} catch (Exception e) {
				Gdx.app.log("SwitchSocketTest", "Server accept error");
			}

		})).start();

		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		SocketHints hints = new SocketHints();
		hints.socketTimeout = 5000;
		Socket client = Gdx.net.newClientSocket(Net.Protocol.TCP, "localhost", 9999, hints);

		try {
			client.getOutputStream().write("PING".getBytes());
			byte[] received = new byte[4];
			client.getInputStream().read(received);
			Gdx.app.log("SwitchSocketTest", "Got server message: " + new String(received));
			Gdx.app.log("SwitchSocketTest", "Testing client timeout...");
			client.getInputStream().read(received);
		} catch (IOException var4) {
			Gdx.app.log("SwitchSocketTest", "A client error occurred", var4);
		}

		client.dispose();
		server.dispose();
	}
}
