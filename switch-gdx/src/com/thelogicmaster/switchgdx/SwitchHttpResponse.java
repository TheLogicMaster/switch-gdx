package com.thelogicmaster.switchgdx;

import com.badlogic.gdx.Net;
import com.badlogic.gdx.net.HttpStatus;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SwitchHttpResponse implements Net.HttpResponse {

	private byte[] result;
	private int status;
	private final HashMap<String, List<String>> headers = new HashMap<>();
	private boolean cancelled;
	private Net.HttpResponseListener listener;

	public SwitchHttpResponse (Net.HttpResponseListener listener) {
		this.listener = listener;
	}

	@Override
	public byte[] getResult () {
		return result;
	}

	@Override
	public String getResultAsString () {
		if (result == null)
			return null;
		return new String(result);
	}

	@Override
	public InputStream getResultAsStream () {
		if (result == null)
			return null;
		return new ByteArrayInputStream(result);
	}

	@Override
	public HttpStatus getStatus () {
		return new HttpStatus(status);
	}

	@Override
	public String getHeader (String name) {
		if (headers.containsKey(name)) {
			List<String> list = headers.get(name);
			return list.get(list.size() - 1);
		}
		return null;
	}

	@Override
	public Map<String, List<String>> getHeaders () {
		return headers;
	}

	void cancel() {
		listener.cancelled();
		cancelled = true;
	}

	public boolean isCancelled () {
		return cancelled;
	}

	private void addHeader(String name, String value) {
		if (!headers.containsKey(name))
			headers.put(name, new ArrayList<>());
		headers.get(name).add(value);
	}
}
