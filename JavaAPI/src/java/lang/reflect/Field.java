/*
 * Copyright (c) 1996, 2015, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
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
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

package java.lang.reflect;

import java.lang.annotation.Annotation;

/**
 * A {@code Field} provides information about, and dynamic access to, a
 * single field of a class or an interface.  The reflected field may
 * be a class (static) field or an instance field.
 *
 * <p>A {@code Field} permits widening conversions to occur during a get or
 * set access operation, but throws an {@code IllegalArgumentException} if a
 * narrowing conversion would occur.
 *
 * @see Member
 * @see Class
 * @see Class#getFields()
 * @see Class#getField(String)
 * @see Class#getDeclaredFields()
 * @see Class#getDeclaredField(String)
 *
 * @author Kenneth Russell
 * @author Nakul Saraiya
 */
public final class Field {

    private final int index;
    private final Class<?> declaringClass;
    private final Class<?> type;
    private final String name;
    private final int modifiers;

    private Field(int index, Class<?> declaringClass, Class<?> type, String name, int modifiers) {
        this.index = index;
        this.declaringClass = declaringClass;
        this.type = type;
        this.name = name;
        this.modifiers = modifiers;
    }

    public Class<?> getDeclaringClass() {
        return declaringClass;
    }

    public String getName() {
        return name;
    }

    public boolean isAccessible() {
        return true;
    }

    public void setAccessible(boolean accessible) {

    }

    public int getModifiers() {
        return modifiers;
    }

    public boolean isEnumConstant() {
        return (modifiers & Modifier.ENUM) != 0;
    }

    public boolean isSynthetic() {
        return Modifier.isSynthetic(modifiers);
    }

    public Class<?> getType() {
        return type;
    }

    public Type getGenericType() {
        return getType(); // Doesn't support generics...
    }

    // Todo: type checking?
    public native Object get(Object obj) throws IllegalArgumentException, IllegalAccessException;

    public native void set(Object obj, Object value) throws IllegalArgumentException, IllegalAccessException;

    public Annotation[] getDeclaredAnnotations() {
        return new Annotation[0];
    }

    public boolean isAnnotationPresent(Class<?> annotation) {
        return false;
    }
}
