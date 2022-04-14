package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Net;
import com.badlogic.gdx.net.ServerSocket;
import com.badlogic.gdx.net.ServerSocketHints;
import com.badlogic.gdx.net.Socket;
import com.badlogic.gdx.net.SocketHints;

public class SwitchNet implements Net {

	@Override
	public void sendHttpRequest (HttpRequest httpRequest, HttpResponseListener httpResponseListener) {

	}

	@Override
	public void cancelHttpRequest (HttpRequest httpRequest) {

	}

	@Override
	public ServerSocket newServerSocket (Protocol protocol, String hostname, int port, ServerSocketHints hints) {
		return null;
	}

	@Override
	public ServerSocket newServerSocket (Protocol protocol, int port, ServerSocketHints hints) {
		return null;
	}

	@Override
	public Socket newClientSocket (Protocol protocol, String host, int port, SocketHints hints) {
		return null;
	}

	@Override
	public boolean openURI (String URI) {
		return false;
	}
}
