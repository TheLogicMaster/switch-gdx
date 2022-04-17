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

package com.codename1.tools.translator;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 *
 * @author Shai Almog
 */
public class ByteCodeTranslator {
    public enum OutputType {
        
        OUTPUT_TYPE_IOS {
            @Override
            public String extension() {
                return "c";
            }
        },
        OUTPUT_TYPE_CSHARP {
            @Override
            public String extension() {
                return "cs";
            }
        
        };

        public abstract String extension();
    };
    public static OutputType output = OutputType.OUTPUT_TYPE_IOS;
    public static boolean verbose = true;
    
    ByteCodeTranslator() {
    }
    
    /**
     * Recursively parses the files in the hierarchy to the output directory
     */
    void execute(File[] sourceDirs, File outputDir) throws Exception {
        for(File f : sourceDirs) {
            execute(f, outputDir);
        }
    }
    
    void execute(File sourceDir, File outputDir) throws Exception {
        File[] directoryList = sourceDir.listFiles(new FileFilter() {
            @Override
            public boolean accept(File pathname) {
                return !pathname.isHidden() && !pathname.getName().startsWith(".") && pathname.isDirectory();
            }
        });
        File[] fileList = sourceDir.listFiles(new FileFilter() {
            @Override
            public boolean accept(File pathname) {
                return !pathname.isHidden() && !pathname.getName().startsWith(".") && !pathname.isDirectory();
            }
        });
        if(fileList != null) {
            for(File f : fileList) {
                if (f.getName().equals("module-info.class")) {
                    // Remove module-info.class that might have been added by jdk9 compile
                    System.out.println("WARNING: Found module-info.class file at "+f+".  One or more of your jars must have been built for JDK9 or higher.  -target 8 or lower is required.");
                    System.out.println("         Will ignore this warning and attempt build anyways.");
                    continue;
                }
                if(f.getName().endsWith(".class")) {
                    Parser.parse(f);
                } else {
                    if(!f.isDirectory()) {
                        // copy the file to the dest dir
                        copy(new FileInputStream(f), new FileOutputStream(new File(outputDir, f.getName())));
                    }
                }
            }
        }
        if(directoryList != null) {
            for(File f : directoryList) {
                if(f.getName().endsWith(".bundle") || f.getName().endsWith(".xcdatamodeld")) {
                    copyDir(f, outputDir);
                    continue;
                }
                execute(f, outputDir);
            }
        }
    }
    
    private void copyDir(File source, File destDir) throws IOException {
        File destFile = new File(destDir, source.getName());
        destFile.mkdirs();
        File[] files = source.listFiles();
        for(File f : files) {
            if(f.isDirectory()) {
                copyDir(f, destFile);
            } else {
                copy(new FileInputStream(f), new FileOutputStream(new File(destFile, f.getName())));
            }
        }
    }
    //
    // make sure a directory is clean.  This is applied
    // to output directories, and should normally be a no-op
    // .. except if some accident occurred or this is a reliberate
    // re-run of a failed build.
    // the underlying purpose is to make repeated builds produce the same result.
    //
    /*private static void cleanDir(File dir)
    {	//
    	// this recursively deletes everything, so be cautious about this!
    	// this is called only on directories we supposedly have just created.
    	// 
    	File [] current = dir.listFiles();
    	if(current.length>0) { // unusual and worth a mention
    		System.out.println("cleanup before build, removing "+current.length+" files in "+dir);
    		for(File cf : current) 
    			{ if(cf.isDirectory()) { cleanDir(cf); }
    			  cf.delete(); 
    			}
    	}
    }*/

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
//        System.setProperty("optimizer", "off");

        if(args.length != 2 && args.length != 3) {
            System.out.println("Usage: <input directory> <output directory> ?<config>");
            System.exit(1);
            return;
        }

        String[] sourceDirectories = args[0].split(";");
        File[] sources = new File[sourceDirectories.length];
        for(int iter = 0 ; iter < sourceDirectories.length ; iter++) {
            sources[iter] = new File(sourceDirectories[iter]);
            if(!sources[iter].exists() && sources[iter].isDirectory()) {
                System.out.println("Source directory doesn't exist: " + sources[iter].getAbsolutePath());
                System.exit(2);
                return;
            }
        }
        File dest = new File(args[1]);
        if(!dest.exists() && dest.isDirectory()) {
            System.out.println("Dest directory doesn't exist: " + dest.getAbsolutePath());
            System.exit(3);
            return;
        }
        
        ByteCodeTranslator b = new ByteCodeTranslator();

        dest.mkdirs();

        System.out.println("srcRoot is: " + dest.getAbsolutePath() );

        b.execute(sources, dest);

//        File cn1Globals = new File(dest, "cn1_globals.h");
//        copy(ByteCodeTranslator.class.getResourceAsStream("/cn1_globals.h"), new FileOutputStream(cn1Globals));
//        if (System.getProperty("INCLUDE_NPE_CHECKS", "false").equals("true")) {
//            replaceInFile(cn1Globals, "//#define CN1_INCLUDE_NPE_CHECKS",  "#define CN1_INCLUDE_NPE_CHECKS");
//        }
//        File cn1GlobalsM = new File(dest, "cn1_globals.c");
//        copy(ByteCodeTranslator.class.getResourceAsStream("/cn1_globals.c"), new FileOutputStream(cn1GlobalsM));
//        File nativeMethods = new File(dest, "nativeMethods.c");
//        copy(ByteCodeTranslator.class.getResourceAsStream("/nativeMethods.c"), new FileOutputStream(nativeMethods));

        if (args.length == 3) {
            JSONObject config = new JSONObject(new String(Files.readAllBytes(Paths.get(args[2]))));
            JSONArray reflection = config.getJSONArray("nonOptimized");
            for (Object o: reflection) {
                String name = ((String)o).replace('.', '_');
                ByteCodeClass.addArrayType(name, 1);
                ByteCodeClass.addNonOptimized(name);
            }
        }

        Parser.writeOutput(dest);
    }
    
    private static String getFileType(String s) {
        if(s.endsWith(".framework")) {
            return "wrapper.framework";
        }
        if(s.endsWith(".a")) {
            return "archive.ar";
        }
        if(s.endsWith(".dylib")) {
            return "compiled.mach-o.dylib";
        }
        if(s.endsWith(".h")) {
            return "sourcecode.c.h";
        }
        if(s.endsWith(".pch")) {
            return "sourcecode.c.objc.preprocessed";
        }
        if(s.endsWith(".hh") || s.endsWith(".hpp")) {
            return "sourcecode.cpp.h";
        }
        if(s.endsWith(".plist")) {
            return "text.plist.xml";
        } 
        if(s.endsWith(".bundle") || s.endsWith("xcdatamodeld")) {
            return "wrapper.plug-in";
        }
        if(s.endsWith(".m") || s.endsWith(".c")) {
            return "sourcecode.c.objc";
        }
        if(s.endsWith(".xcassets")) {
            return "folder.assetcatalog";
        }
        if(s.endsWith(".mm") || s.endsWith(".cpp")) {
            return "sourcecode.cpp.objc";
        }
        if(s.endsWith(".xib")) {
            return "file.xib";
        }
        if(s.endsWith(".res") || s.endsWith(".ttf") ) {
            return "file";
        }
        if(s.endsWith(".png")) {
            return "image.png";
        }
        if(s.endsWith(".strings")) {
            return "text.plist.strings";
        }
        return "file";
    }
    //
    // Be kind to the GC; read as a StringBuilder, a data type designed
    // to be mutated. Also, expire the temporary byte[] buffer so it can
    // be collected.
    //
    private static StringBuilder readFileAsStringBuilder(File sourceFile) throws IOException
    {
        DataInputStream dis = new DataInputStream(new FileInputStream(sourceFile));
        byte[] data = new byte[(int)sourceFile.length()];
        dis.readFully(data);
        dis.close();
        StringBuilder b = new StringBuilder(new String(data));
        return b;
    }
    //
    // rewrite 4/2017 by ddyer to use more appropriate data
    // structures, minimizing gc thrashing.  This avoids a big
    // spike in memory and gc usage (and corresponding build 
    // failures due to OutOfMemoryError) at the very end of the build 
    // process for large projects.  
    //
    private static void replaceInFile(File sourceFile, String... values) throws IOException {
        StringBuilder str = readFileAsStringBuilder(sourceFile);
        int totchanges = 0;
    	// perform the mutations on stringbuilder, which ought to implement
        // these operations efficiently.
        for (int iter = 0; iter < values.length; iter += 2) {
            String target = values[iter];
            String replacement = values[iter + 1];
            int index = 0;
            while ((index = str.indexOf(target, index)) >= 0) {
                int targetSize = target.length();
                str.replace(index, index + targetSize, replacement);
                index += replacement.length();
                totchanges++;
            }
        }
        //
        // don't start the output file until all the processing is done
        //
        System.out.println("Rewrite " + sourceFile + " with " + totchanges + " changes");
        FileWriter fios = new FileWriter(sourceFile);
        fios.write(str.toString());
        fios.close();
    }
    

    

    /**
     * Copy the input stream into the output stream, closes both streams when finishing or in
     * a case of an exception
     * 
     * @param i source
     * @param o destination
     */
    public static void copy(InputStream i, OutputStream o) throws IOException {
        copy(i, o, 8192);
    }

    /**
     * Copy the input stream into the output stream, closes both streams when finishing or in
     * a case of an exception
     *
     * @param i source
     * @param o destination
     * @param bufferSize the size of the buffer, which should be a power of 2 large enoguh
     */
    public static void copy(InputStream i, OutputStream o, int bufferSize) throws IOException {
        try {
            byte[] buffer = new byte[bufferSize];
            int size = i.read(buffer);
            while(size > -1) {
                o.write(buffer, 0, size);
                size = i.read(buffer);
            }
        } finally {
            cleanup(o);
            cleanup(i);
        }
    }

    /**
     * Closes the object (connection, stream etc.) without throwing any exception, even if the
     * object is null
     *
     * @param o Connection, Stream or other closeable object
     */
    public static void cleanup(Object o) {
        try {
            if(o instanceof OutputStream) {
                ((OutputStream)o).close();
                return;
            }
            if(o instanceof InputStream) {
                ((InputStream)o).close();
                return;
            }
        } catch(IOException err) {
            err.printStackTrace();
        }
    }
}
