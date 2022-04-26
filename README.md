# SwitchGDX
[![Release](https://jitpack.io/v/com.thelogicmaster/switch-gdx.svg)](https://jitpack.io/#com.thelogicmaster/switch-gdx)

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
For now, reference the `example` subproject for the Gradle setup. It's entirely untested on Windows at this point.
The `transpile` task does just that and outputs
the C projecct into the `example/switch/build/dist` directory. `run` executes the transpiler and runs the native PC backend. `deploy`
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
- Basic GDX Audio support (SDL_mixer)
- Scene2d Skins
- Partial GDX Reflection support

## Todo
- GDX Networking
- Possibly GDX threading stuff
- GL30?
- Switch specific Java APIs to enable switch unique features (Probably needed for controller remapping, for example)
- GDX test suite
- Bullet
- Box2D
- gdx-dialogs
- Freetype

## Needs Testing
- Windows everything, CMake libs, filesystem APIs, Gradle task commands, file separators
- Full GDX Audio API (Change looping on playing Music, for instance)
- All AssetManager and Skin types
- Full GDX File API (map functions should throw exceptions but compile)

## Notes
- Requires retrolambda for lambda support (Use pre-v7 Gradle wrapper)
- Exceptions thrown without a try-catch block are ignored (Maybe adding try-catch block in thread init code, in addition to main function)
- Concurrent access to files is more limited on Switch where it might normally work on PC, so ensure files are closed properly
- Sound effects are limited to OGG and WAV, Music supports MP3, OGG, and WAV
- Only one Music instance can be played at a time
- Classes referenced with reflection must be included in switch.json
- Only supports up to 3D arrays
- For Switch, all pthreads need to be terminated manually or it will crash on exit. Any program threads must be manually stopped on dispose.
- If using SNAPSHOT Gradle dependency, refresh Gradle dependencies using the Intellij Gradle menu to not use cached versions and update to the latest.

## Current Status
- Compiler bug in com_badlogic_gdx_assets_AssetManager_update___R_boolean, so comment out for now (Probably related to setjmp/try-catch)
- Switch crash in __GC_MARK_com_badlogic_gdx_utils_JsonValue, so comment out for now
- Flick gesture detection is broken
