package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Net;
import com.badlogic.gdx.net.ServerSocket;
import com.badlogic.gdx.net.ServerSocketHints;
import com.badlogic.gdx.net.Socket;
import com.badlogic.gdx.net.SocketHints;
import com.badlogic.gdx.utils.GdxRuntimeException;
import com.badlogic.gdx.utils.IdentityMap;
import com.badlogic.gdx.utils.ObjectMap;
import com.badlogic.gdx.utils.StreamUtils;

import java.util.ArrayList;
import java.util.Map;

public class SwitchNet implements Net {

	private final ObjectMap<HttpRequest, SwitchHttpResponse> responses = new IdentityMap<>();

	@Override
	public void sendHttpRequest (HttpRequest httpRequest, HttpResponseListener httpResponseListener) {
		SwitchHttpResponse response = new SwitchHttpResponse(httpResponseListener);

		try {
			final String method = httpRequest.getMethod();
			String url;
			if (method.equalsIgnoreCase(HttpMethods.GET) || method.equalsIgnoreCase(HttpMethods.HEAD)) {
				String queryString = "";
				String value = httpRequest.getContent();
				if (value != null && !"".equals(value))
					queryString = "?" + value;
				url = httpRequest.getUrl() + queryString;
			} else
				url = httpRequest.getUrl();

			byte[] content;
			if (httpRequest.getContent() != null)
				content = httpRequest.getContent().getBytes();
			else if (httpRequest.getContentStream() != null)
				content = StreamUtils.copyStreamToString(httpRequest.getContentStream()).getBytes();
			else
				content = null;

			ArrayList<String> headers = new ArrayList<>();
			for (Map.Entry<String, String> entry: httpRequest.getHeaders().entrySet())
				headers.add(entry.getKey() + ": " + entry.getValue());

			synchronized (responses) {
				responses.put(httpRequest, response);
			}

			new Thread(() -> {
				String error = sendRequest(url, content, headers.toArray(new String[0]), httpRequest.getMethod(), httpRequest.getTimeOut(), response);
				if (httpResponseListener != null) {
					if (error != null)
						httpResponseListener.failed(new GdxRuntimeException(error));
					else if (!response.isCancelled())
						httpResponseListener.handleHttpResponse(response);
				}

				synchronized (responses) {
					if (responses.containsKey(httpRequest))
						responses.remove(httpRequest);
				}
			}).start();

		} catch (Exception e) {
			if (httpResponseListener != null)
				httpResponseListener.failed(e);
		}
	}

	@Override
	public void cancelHttpRequest (HttpRequest httpRequest) {
		synchronized (responses) {
			if (responses.containsKey(httpRequest))
				responses.remove(httpRequest).cancel();
		}
	}

	@Override
	public ServerSocket newServerSocket (Protocol protocol, String hostname, int port, ServerSocketHints hints) {
		return new SwitchServerSocket(port, hints);
	}

	@Override
	public ServerSocket newServerSocket (Protocol protocol, int port, ServerSocketHints hints) {
		return new SwitchServerSocket(port, hints);
	}

	@Override
	public Socket newClientSocket (Protocol protocol, String host, int port, SocketHints hints) {
		return new SwitchSocket(host, port, hints);
	}

	@Override
	public native boolean openURI (String URI);

	private static native String sendRequest(String url, byte[] content, String[] headers, String method, long timeout, SwitchHttpResponse response);
}
