package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Net;
import com.badlogic.gdx.net.ServerSocket;
import com.badlogic.gdx.net.ServerSocketHints;
import com.badlogic.gdx.net.Socket;
import com.badlogic.gdx.net.SocketHints;
import com.badlogic.gdx.utils.GdxRuntimeException;

public class SwitchServerSocket implements ServerSocket {

	private final int fd;

	public SwitchServerSocket (int port, ServerSocketHints hints) {
		if (hints == null)
			hints = new ServerSocketHints();
		fd = create(port, hints.reuseAddress, hints.acceptTimeout);
	}

	@Override
	public Net.Protocol getProtocol () {
		return Net.Protocol.TCP;
	}

	@Override
	public Socket accept (SocketHints hints) {
		if (hints == null)
			hints = new SocketHints();
		if (fd == 0)
			throw new GdxRuntimeException("Server socket closed");
		return new SwitchSocket(accept(hints.socketTimeout));
	}

	@Override
	public native void dispose ();

	private static native int create(int port, boolean reuseAddress, int acceptTimeout);

	private native int accept(int timeout);
}
