package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.net.Socket;
import com.badlogic.gdx.net.SocketHints;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class SwitchSocket implements Socket {

	private boolean connected;
	private final int fd;
	private final SocketInputStream inputStream = new SocketInputStream();
	private final SocketOutputStream outputStream = new SocketOutputStream();

	public SwitchSocket (int fd) {
		this.fd = fd;
		connected = true;
	}

	public SwitchSocket (String host, int port, SocketHints hints) {
		if (hints == null)
			hints = new SocketHints();
		this.fd = create(host, port, hints.connectTimeout, hints.socketTimeout);
	}

	@Override
	public boolean isConnected () {
		return connected;
	}

	@Override
	public InputStream getInputStream () {
		return inputStream;
	}

	@Override
	public OutputStream getOutputStream () {
		return outputStream;
	}

	@Override
	public native String getRemoteAddress ();

	@Override
	public native void dispose ();

	private static native int create (String host, int port, int connectTimeout, int timeout);

	private native int read ();

	private native void write (int b);

	class SocketInputStream extends InputStream {

		@Override
		public int read () throws IOException {
			return SwitchSocket.this.read();
		}
	}

	class SocketOutputStream extends OutputStream {

		@Override
		public void write (int b) throws IOException {
			SwitchSocket.this.write(b);
		}
	}
}
