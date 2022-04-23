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

package java.util;

/**
 *
 * @author Shai Almog
 */
public class Locale {
    private static Locale defaultLocale;

    /** Useful constant for language.
     */
    static public final Locale ENGLISH = new Locale("en", "");

    /** Useful constant for language.
     */
    static public final Locale FRENCH = new Locale("fr", "");

    /** Useful constant for language.
     */
    static public final Locale GERMAN = new Locale("de", "");

    /** Useful constant for language.
     */
    static public final Locale ITALIAN = new Locale("it", "");

    /** Useful constant for language.
     */
    static public final Locale JAPANESE = new Locale("ja", "");

    /** Useful constant for language.
     */
    static public final Locale KOREAN = new Locale("ko", "");

    /** Useful constant for language.
     */
    static public final Locale CHINESE = new Locale("zh", "");

    /** Useful constant for language.
     */
    static public final Locale SIMPLIFIED_CHINESE = new Locale("zh", "CN");

    /** Useful constant for language.
     */
    static public final Locale TRADITIONAL_CHINESE = new Locale("zh", "TW");

    /** Useful constant for country.
     */
    static public final Locale FRANCE = new Locale("fr", "FR");

    /** Useful constant for country.
     */
    static public final Locale GERMANY = new Locale("de", "DE");

    /** Useful constant for country.
     */
    static public final Locale ITALY = new Locale("it", "IT");

    /** Useful constant for country.
     */
    static public final Locale JAPAN = new Locale("ja", "JP");

    /** Useful constant for country.
     */
    static public final Locale KOREA = new Locale("ko", "KR");

    /** Useful constant for country.
     */
    static public final Locale CHINA = SIMPLIFIED_CHINESE;

    /** Useful constant for country.
     */
    static public final Locale PRC = SIMPLIFIED_CHINESE;

    /** Useful constant for country.
     */
    static public final Locale TAIWAN = TRADITIONAL_CHINESE;

    /** Useful constant for country.
     */
    static public final Locale UK = new Locale("en", "GB");

    /** Useful constant for country.
     */
    static public final Locale US = new Locale("en", "US");

    /** Useful constant for country.
     */
    static public final Locale CANADA = new Locale("en", "CA");

    /** Useful constant for country.
     */
    static public final Locale CANADA_FRENCH = new Locale("fr", "CA");

    /**
     * Useful constant for the root locale.  The root locale is the locale whose
     * language, country, and variant are empty ("") strings.  This is regarded
     * as the base locale of all locales, and is used as the language/country
     * neutral locale for the locale sensitive operations.
     *
     * @since 1.6
     */
    static public final Locale ROOT = new Locale("", "");
    
    private String language;
    private String country;
    
    public Locale(String language, String locale) {
        this.language = language;
        this.country = locale;
    }
    
    public Locale() {
        language = getOSLanguage();
        int pos;
        if (language != null && (pos = language.indexOf('-')) != -1) {
            country = language.substring(pos+1);
            language = language.substring(0, pos);
        }
        if (language != null && (pos = language.indexOf('_')) != -1) {
            country = language.substring(pos+1);
            language = language.substring(0, pos);
        }
        if (country == null) {
            country = "US";
        }
    }

    public Locale(String a) {
        throw new UnsupportedOperationException();
    }

    public Locale(String a, String b, String c) {
        throw new UnsupportedOperationException();
    }

    public static Locale getDefault() {
        if(defaultLocale == null) {
            defaultLocale = new Locale();
        }
        return defaultLocale;
    }
    
    public static void setDefault(Locale l) {
        defaultLocale = l;
    }
    
    public String getLanguage() {
        return language;
    }
        
    public String getCountry() {
        return country;
    }

    public String getVariant() {
        return null;
    }

    private static native String getOSLanguage();

    public enum Category {

        /**
         * Category used to represent the default locale for
         * displaying user interfaces.
         */
        DISPLAY("user.language.display",
            "user.script.display",
            "user.country.display",
            "user.variant.display"),

        /**
         * Category used to represent the default locale for
         * formatting dates, numbers, and/or currencies.
         */
        FORMAT("user.language.format",
            "user.script.format",
            "user.country.format",
            "user.variant.format");

        Category(String languageKey, String scriptKey, String countryKey, String variantKey) {
            this.languageKey = languageKey;
            this.scriptKey = scriptKey;
            this.countryKey = countryKey;
            this.variantKey = variantKey;
        }

        final String languageKey;
        final String scriptKey;
        final String countryKey;
        final String variantKey;
    }
}
