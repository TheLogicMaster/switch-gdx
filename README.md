# SwitchGDX

## About
This is a WIP Nintendo Switch Homebrew LibGDX backend based on LibNX and the CodenameOne Parpar VM. It's early in development and only works for simple GDX applications. It also provides a CMake project configuration for natively debugging applications on a PC. It's similar to
RoboVM, except it generates C code which is then compiled for the specific target.

## Requrements
### Desktop
- CMake
- SDL2
- SDL2_Mixer
- libffi
- GLEW
- pthreads
- zlib
- C++ 17 Filesystem support
### Switch
- DevKitPro
- SDL2_Mixer, GLAD, and zlib for Switch
- Custom build of libffi for Switch (Todo)

## Usage
For now, reference the TestApp subproject for the Gradle setup. It's entirely untested on Windows at this point. The fat JARs created by the
ShadowJar (*-all.jar) tasks in the JavaAPI and ByteCodeTranslator Gradle projects need to be manually copied from `build/libs` into the `TestApp/switch/libs` directory without the `-all` part of the filename
currently, then the TestApp switch subproject Gradle tasks can be run to run the transpiler. The `transpile` task does just that and outputs
the C projecct into the `TestApp/switch/build/dist` directory. `run` executes the transpiler and runs the native PC backend. `deploy`
does the same but deploys to a Switch via NXLink. Compiling for desktop is over twice as fast and allows for full IDE debugging, so it's
more convenient for development.

## Debugging
The project can be debugged as a normal C project with your IDE of choice. CLion works out of the box with
the CMake project if you have a license. Simply run one of the Gradle tasks to transpile the project, then
open the `switch/build/dist` directory with CLion as a CMake project. A Run configuration should be automatically created. Set the working directory in the run config to the `dist` directory so that assets
cam be properly loaded at runtime. To trace back a seg fault, simply press the debug icon next to the run
configuration and it should jump right to the exception and show the native stack trace. By inspecting the
generated code and call stack, null fields can be found and traced back to Java source code by looking at the
`__CN1_DEBUG_INFO` macro line numbers. When regenerating the project with CLion open, reload the CMake project
under `Tools/Cmake/Reload CMake Project` or it won't run. Sometimes closing CLion and deleting the
`dist/.idea` directory or transpiling the project again is neccesary.

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
- GDX Input button keys mapped to default controller
- System language/locale
- Basic GDX Audio support (SDL_mixer)
- Field Reflection
- Scene2d Skins

## Todo
- Gradle libs as repo dependencies
- Internal VM logging
- GDX Networking
- Possibly GDX threading stuff
- Interruptable Thread.sleep() for clean exit
- GL30?
- Reflection method support (libffi)
- Incremental compilation, if possible, to cut down on compilation times (Something like rsync to only copy changed files into dist)
- Switch wrapper buffers to use memory directly since it's always aligned, rather than the super inefficient byte by byte implementation (Profile using BufferUtilsTest)
- Ensure code licensing is all good (Probably noting modifications to comply with GPLv2)
- Remove any unnecessary java.util.concurrent stuff
- Replace any class stubs with generic equivalents
- Switch specific Java APIs to enable switch unique features (Probably needed for controller remapping, for example)
- Enable NPE checks, possibly enhance the feature further
- VSCode debugging testing/instructions
- Organize natives better, probably port C native function implementations to C++
- GDX test suite
- Bullet
- Box2D
- gdx-dialogs
- Freetype
- Debug server
- Don't optimize out methods needed for reflection
- Include native source files from dependency JARs

## Needs Testing
- Windows everything, CMake libs, filesystem APIs, Gradle task commands, file separators
- Full GDX Audio API (Change looping on playing Music, for instance)
- All AssetManager and Skin types
- Full GDX File API (map functions should throw exceptions but compile)

## Notes
- Requires retrolambda for lambda support (Use pre-v7 Gradle wrapper)
- Exceptions thrown without a try-catch block are ignored (Maybe adding try-catch block in thread init code, in addition to main function)
- JDK-8 is required for compiling the JavaAPI project
- Concurrent access to files is more limited on Switch where it might normally work on PC, so ensure files are closed properly
- Sound effects are limited to OGG and WAV, Music supports MP3, OGG, and WAV
- Only one Music instance can be played at a time
- Classes referenced with reflection must be included in switch.json
- Only supports up to 3D arrays

## Current Status
- Compiler bug in com_badlogic_gdx_assets_AssetManager_update___R_boolean, so comment out for now (Probably related to setjmp/try-catch)
- Switch crash in __GC_MARK_com_badlogic_gdx_utils_JsonValue, so comment out for now
- Flick gesture detection is broken

## Bugs Fixed
- For exceptions, local variable restoreTo* must be volatile, presumably as a result of setjmp
- Parameter evaluation order isn't specified in C, so POPs in member setters must be evaluated outside
- For Switch, all pthreads need to be terminated manually or it will crash on exit. Any program threads must be manually stopped on dispose.
