/*
 * Copyright (c) 2012, Codename One and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Codename One designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *  
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 * 
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * Please contact Codename One through http://www.codenameone.com/ if you 
 * need additional information or have any questions.
 */

package java.nio;

import java.util.Spliterator;

public abstract class Buffer {

	static final int SPLITERATOR_CHARACTERISTICS = Spliterator.SIZED | Spliterator.SUBSIZED | Spliterator.ORDERED;

	private int mark = -1;
	private int position = 0;
	private int limit;
	private int capacity;

	long address;

	Buffer(int mark, int pos, int lim, int cap) {
		if (cap < 0)
			throw new IllegalArgumentException("Negative capacity: " + cap);
		this.capacity = cap;
		limit(lim);
		position(pos);
		if (mark >= 0) {
			if (mark > pos)
				throw new IllegalArgumentException("mark > position: ("
					+ mark + " > " + pos + ")");
			this.mark = mark;
		}
	}

	public final int capacity() {
		return capacity;
	}

	public final int position() {
		return position;
	}

	public final Buffer position(int newPosition) {
		if ((newPosition > limit) || (newPosition < 0))
			throw new IllegalArgumentException();
		if (mark > newPosition) mark = -1;
		position = newPosition;
		return this;
	}

	public final int limit() {
		return limit;
	}

	public final Buffer limit(int newLimit) {
		if ((newLimit > capacity) || (newLimit < 0))
			throw new IllegalArgumentException();
		limit = newLimit;
		if (position > newLimit) position = newLimit;
		if (mark > newLimit) mark = -1;
		return this;
	}

	public final Buffer mark() {
		mark = position;
		return this;
	}

	public final Buffer reset() {
		int m = mark;
		if (m < 0)
			throw new InvalidMarkException();
		position = m;
		return this;
	}

	public final Buffer clear() {
		position = 0;
		limit = capacity;
		mark = -1;
		return this;
	}

	public final Buffer flip() {
		limit = position;
		position = 0;
		mark = -1;
		return this;
	}

	public final Buffer rewind() {
		position = 0;
		mark = -1;
		return this;
	}

	public final int remaining() {
		int rem = limit - position;
		return rem > 0 ? rem : 0;
	}

	public final boolean hasRemaining() {
		return position < limit;
	}

	public abstract boolean isReadOnly();

	public abstract boolean hasArray();

	public abstract Object array();

	public abstract int arrayOffset();

	public abstract boolean isDirect();

	final int nextGetIndex() {                          // package-private
		int p = position;
		if (p >= limit)
			throw new BufferUnderflowException();
		position = p + 1;
		return p;
	}

	final int nextGetIndex(int nb) {                    // package-private
		int p = position;
		if (limit - p < nb)
			throw new BufferUnderflowException();
		position = p + nb;
		return p;
	}

	final int nextPutIndex() {                          // package-private
		int p = position;
		if (p >= limit)
			throw new BufferOverflowException();
		position = p + 1;
		return p;
	}

	final int nextPutIndex(int nb) {                    // package-private
		int p = position;
		if (limit - p < nb)
			throw new BufferOverflowException();
		position = p + nb;
		return p;
	}

	final int checkIndex(int i) {                       // package-private
		if ((i < 0) || (i >= limit))
			throw new IndexOutOfBoundsException();
		return i;
	}

	final int checkIndex(int i, int nb) {               // package-private
		if ((i < 0) || (nb > limit - i))
			throw new IndexOutOfBoundsException();
		return i;
	}

	final int markValue() {                             // package-private
		return mark;
	}

	final void truncate() {                             // package-private
		mark = -1;
		position = 0;
		limit = 0;
		capacity = 0;
	}

	final void discardMark() {                          // package-private
		mark = -1;
	}

	static void checkBounds(int off, int len, int size) { // package-private
		if ((off | len | (off + len) | (size - (off + len))) < 0)
			throw new IndexOutOfBoundsException();
	}
}
