package java.io;

public class PrintWriter extends Writer {
	protected Writer out;
	private final boolean autoFlush;
	private boolean trouble;
	private PrintStream psOut;

	public PrintWriter(Writer out) {
		this(out, false);
	}

	public PrintWriter(Writer out, boolean autoFlush) {
		super(out);
		this.trouble = false;
		this.psOut = null;
		this.out = out;
		this.autoFlush = autoFlush;
	}

	public PrintWriter(OutputStream out) {
		this(out, false);
	}

	public PrintWriter(OutputStream out, boolean autoFlush) {
		this(new OutputStreamWriter(out), autoFlush);
		if (out instanceof PrintStream) {
			this.psOut = (PrintStream)out;
		}

	}

	private void ensureOpen() throws IOException {
		if (this.out == null) {
			throw new IOException("Stream closed");
		}
	}

	public void flush() {
		try {
			synchronized(this.lock) {
				this.ensureOpen();
				this.out.flush();
			}
		} catch (IOException var4) {
			this.trouble = true;
		}

	}

	public void close() {
		try {
			synchronized(this.lock) {
				if (this.out == null) {
					return;
				}

				this.out.close();
				this.out = null;
			}
		} catch (IOException var4) {
			this.trouble = true;
		}

	}

	public boolean checkError() {
		if (this.out != null) {
			this.flush();
		}

		if (this.out instanceof PrintWriter) {
			PrintWriter pw = (PrintWriter)this.out;
			return pw.checkError();
		} else {
			return this.psOut != null ? this.psOut.checkError() : this.trouble;
		}
	}

	protected void setError() {
		this.trouble = true;
	}

	public void write(int c) {
		try {
			synchronized(this.lock) {
				this.ensureOpen();
				this.out.write(c);
			}
		} catch (InterruptedIOException var5) {
			Thread.currentThread().interrupt();
		} catch (IOException var6) {
			this.trouble = true;
		}

	}

	public void write(char[] buf, int off, int len) {
		try {
			synchronized(this.lock) {
				this.ensureOpen();
				this.out.write(buf, off, len);
			}
		} catch (InterruptedIOException var7) {
			Thread.currentThread().interrupt();
		} catch (IOException var8) {
			this.trouble = true;
		}

	}

	public void write(char[] buf) {
		this.write(buf, 0, buf.length);
	}

	public void write(String s, int off, int len) {
		try {
			synchronized(this.lock) {
				this.ensureOpen();
				this.out.write(s, off, len);
			}
		} catch (InterruptedIOException var7) {
			Thread.currentThread().interrupt();
		} catch (IOException var8) {
			this.trouble = true;
		}

	}

	public void write(String s) {
		this.write(s, 0, s.length());
	}

	private void newLine() {
		try {
			synchronized(this.lock) {
				this.ensureOpen();
				this.out.write('\n');
				if (this.autoFlush) {
					this.out.flush();
				}
			}
		} catch (InterruptedIOException var4) {
			Thread.currentThread().interrupt();
		} catch (IOException var5) {
			this.trouble = true;
		}

	}

	public void print(boolean b) {
		this.write(String.valueOf(b));
	}

	public void print(char c) {
		this.write(c);
	}

	public void print(int i) {
		this.write(String.valueOf(i));
	}

	public void print(long l) {
		this.write(String.valueOf(l));
	}

	public void print(float f) {
		this.write(String.valueOf(f));
	}

	public void print(double d) {
		this.write(String.valueOf(d));
	}

	public void print(char[] s) {
		this.write(s);
	}

	public void print(String s) {
		this.write(String.valueOf(s));
	}

	public void print(Object obj) {
		this.write(String.valueOf(obj));
	}

	public void println() {
		this.newLine();
	}

	public void println(boolean x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(char x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(int x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(long x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(float x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(double x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(char[] x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(String x) {
		synchronized(this.lock) {
			this.print(x);
			this.println();
		}
	}

	public void println(Object x) {
		String s = String.valueOf(x);
		synchronized(this.lock) {
			this.print(s);
			this.println();
		}
	}

	public PrintWriter append(CharSequence csq) {
		this.write(String.valueOf(csq));
		return this;
	}

	public PrintWriter append(CharSequence csq, int start, int end) {
		if (csq == null) {
			csq = "null";
		}

		return this.append(csq.subSequence(start, end));
	}

	public PrintWriter append(char c) {
		this.write(c);
		return this;
	}
}
