# SwitchGDX

## About
This is a WIP Nintendo Switch Homebrew LibGDX backend based on LibNX and the CodenameOne Parpar VM. It's early in development and only works for simple GDX applications. It also provides a CMake project configuration for natively debugging applications on a PC. It's similar to
RoboVM, except it generates C code which is then compiled for the specific target.

## Usage
For now, reference the TestApp subproject for the Gradle setup. It's entirely untested on Windows at this point. The fat JARs created by the
ShadowJar (*-all.jar) tasks in the JavaAPI and ByteCodeTranslator Gradle projects need to be manually copied from `build/libs` into the `TestApp/switch/libs` directory
currently, then the TestApp switch subproject Gradle tasks can be run to run the transpiler. The `transpile` task does just that and outputs
the C projecct into the `TestApp/switch/build/dist` directory. `run` executes the transpiler and runs the native PC backend. `deploy`
does the same but deploys to a Switch via NXLink. Compiling for desktop is over twice as fast and allows for full IDE debugging, so it's
more convenient for development.

## Features implemented
- Regex (RegExodus)
- Basic File I/O
- GL20 bindings
- GDX Native bindings
- Buffers (Only direct buffers and ByteBuffer wrappers are supported)
- Syncronous AssetManager (GWT)
- Single controller gdx-controllers support
- GDX Preferences
- Default Yuzu keyboard mapping for switch pro-controller emulation
- GDX Input multitouch with PC touch emulation
- System language/locale
- Basic GDX Audio support (SDL_mixer)

## Todo
- Gradle libs as repo dependencies
- Internal VM logging
- GDX Networking
- Finish GDX filesystem support
- Possibly GDX threading stuff
- GL30?
- More complete Reflection support
- Incremental compilation, if possible, to cut down on compilation times
- Switch wrapper buffers to use memory directly since it's always aligned, rather than the super inefficient byte by byte implementation
- Ensure code licensing is all good (Probably noting modifications to comply with GPLv2)
- Remove any unnecessary java.util.concurrent stuff
- Replace any class stubs with generic equivalents
- Switch specific Java APIs to enable switch unique features (Probably needed for controller remapping, for example)

## Notes
- Requires retrolambda for lambda support (Use pre-v7 Gradle wrapper)
- Exceptions thrown without a try-catch block are ignored (Maybe adding try-catch block in thread init code, in addition to main function)
- JDK-8 is required for compiling the JavaAPI project
- Concurrent access to files is more limited on Switch where it might normally work on PC, so ensure files are closed properly
- Sound effects are limited to OGG and WAV, Music supports MP3, OGG, and WAV
- Only one Music instance can be played at a time

## Current Status
- Compiler bug in com_badlogic_gdx_assets_AssetManager_update___R_boolean, so comment out for now (Probably related to setjmp/try-catch)
- Switch crash in __GC_MARK_com_badlogic_gdx_utils_JsonValue, so comment out for now

## Bugs Fixed
- For exceptions, local variable restoreTo* must be volatile, presumably as a result of setjmp
- Parameter evaluation order isn't specified in C, so POPs in member setters must be evaluated outside
- For Switch, all pthreads need to be terminated manually or it will crash on exit. Any program threads must be manually stopped on dispose.
