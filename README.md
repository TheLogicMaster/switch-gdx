# SwitchGDX
[![Release](https://jitpack.io/v/com.thelogicmaster/switch-gdx.svg)](https://jitpack.io/#com.thelogicmaster/switch-gdx)

## About
This is a WIP Nintendo Switch Homebrew LibGDX backend based on LibNX and the CodenameOne [Parpar VM](https://github.com/codenameone/CodenameOne/tree/master/vm). 
It uses a custom fork of the VM named [Clearwing VM](https://github.com/TheLogicMaster/clearwing-vm).
It's early in development and only works for simple GDX applications. It also provides a CMake project configuration for natively debugging applications 
on a PC. It's similar to RoboVM, except it generates C code which is then compiled for the specific target. See [Tests](TESTS.md)
for current GDX compatibility.

## Installation
- Install JDK 8
### Linux
- Install CMake, Ninja, Rsync, Texinfo, SDL2, SDL2_Mixer, GLEW, libffi, zlib, freetype
- With APT: `sudo apt install build-essential texinfo rsync cmake ninja-build libffi-dev libsdl2-mixer-dev zlib1g-dev libglew-dev libfreetype-dev libcurl4-gnutls-dev`
- Install [devkitPro pacman](https://github.com/devkitPro/pacman/releases/tag/v1.0.2)
- `dkp-pacman -S switch-zlib switch-sdl2 switch-sdl2_mixer switch-freetype switch-glad switch-curl switch-bulletphysics dkp-toolchain-vars`

### Windows
- Install [devkitPro Updater](https://github.com/devkitPro/installer/releases/latest) with Switch packages selected
- Open MSYS2 two from the start menu
- `pacman -Syu`
- `pacman -S switch-zlib switch-sdl2_mixer switch-freetype switch-glad switch-curl switch-bulletphysics dkp-toolchain-vars`
- `pacman -S gcc git rsync texinfo mingw-w64-x86_64-glew mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-curl-gnutls mingw-w64-x86_64-freetype mingw-w64-x86_64-bullet`

### libffi
This is a library that has to be compiled and installed manually for Switch. Run this for Linux normally and on Windows under 
MSYS2. Ensure that the working directory doesn't contain any spaces.
``` bash
git clone https://github.com/libffi/libffi.git
cd libffi
./autogen.sh
source $DEVKITPRO/switchvars.sh
source $DEVKITPRO/devkita64.sh
CFLAGS="-g -O2 -march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIC -ftls-model=local-exec" CHOST=aarch64-none-elf ./configure --prefix="$DEVKITPRO/portlibs/switch" --host=aarch64-none-elf
make
sudo cp ./aarch64-none-elf/include/*.h $DEVKITPRO/portlibs/switch/include/
sudo cp ./aarch64-none-elf/.libs/libffi.a $DEVKITPRO/portlibs/switch/lib
sudo cp ./aarch64-none-elf/.libs/libffi.la $DEVKITPRO/portlibs/switch/lib
sudo cp ./aarch64-none-elf/libffi.pc $DEVKITPRO/portlibs/switch/lib/pkgconfig/
```

## Usage
For now, reference the `example` project for the Gradle setup. If you don't yet have a LibGDX project, create one using 
[gdx-liftoff](https://github.com/tommyettinger/gdx-liftoff). Ensure that your project path contains
no spaces. In your project, add a new Gradle submodule called `switch` and
copy `switch.json` and `build.gradle` from the `example` project's `switch` directory into the new submodule. Create a new Class called 
`SwitchLauncher` or whatever you want to call it and add a main method that simply creates a new `SwitchApplication` instance
that takes your `ApplicationListener` as a parameter. Edit `build.gradle` to update the main class name and artifact IDs. 
Ensure that the core project has `sourceCompatibility` set no higher than 1.8 for now.
The `transpile` task does just that and outputs the C project into the `<project>/switch/build/<project>` directory. `run` executes
the transpiler and runs the native PC backend. `deploy` does the same but deploys to a Switch via NXLink. Ensure that the path
to the project directory doesn't contain any spaces. 

## Debugging
The project can be debugged as a normal C project with your IDE of choice. CLion works out of the box with
the CMake project if you have a license. Simply run one of the Gradle tasks to transpile the project, then
open the `<project>/switch/build/<project>` directory with CLion as a CMake project. A Run configuration should be automatically created. 
Set the working directory in the run config to the `build/<project>` project directory so that assets
can be properly loaded at runtime. To trace back a seg fault, simply press the debug icon next to the run
configuration, and it should jump right to the exception and show the native stack trace. By inspecting the
generated code and call stack, null fields can be found and traced back to Java source code by looking at the
`__CN1_DEBUG_INFO` macro line numbers. Code changes may lead to additional classes being included by the transpiler, in which case
the CLion CMake project needs to be reloaded using `Tools/Cmake/Reload CMake Project` or it won't compile.
If using Windows, the devkitPro MinGW toolchain has to be selected under the project build settings.

## Features implemented
- Regex (RegExodus)
- Basic File I/O
- GL20 bindings
- GDX Native bindings
- Buffers (Only direct buffers and ByteBuffer wrappers are supported)
- Synchronous AssetManager (GWT)
- Single controller gdx-controllers support
- GDX Preferences
- Default Yuzu keyboard mapping for switch pro-controller emulation
- GDX Input multitouch with PC touch emulation
- GDX Input button keys mapped to default controller
- Basic GDX Audio support (SDL_mixer)
- Scene2d Skins
- Partial GDX Reflection support
- FreeType
- Box2D

## Todo
- GDX Networking
- Possibly threading stuff
- GL30 (Requires regenerating glad2 online)
- Switch specific Java APIs to enable switch unique features (Probably needed for controller remapping, for example)
- Bullet

## Notes
- Requires retrolambda for lambda support (Use pre-v7 Gradle wrapper)
- Exceptions thrown without a try-catch block are ignored (Maybe adding try-catch block in thread init code, in addition to main function)
- Concurrent access to files is more limited on Switch where it might normally work on PC, so ensure files are closed properly
- Sound effects are limited to OGG and WAV, Music supports MP3, OGG, and WAV
- Only one Music instance can be played at a time
- Classes referenced with reflection must be included in switch.json
- Only supports up to 3D arrays
- For Switch, all pthreads need to be terminated manually, or it will crash on exit. Any program threads must be manually stopped on dispose.
- If using SNAPSHOT Gradle dependency, refresh Gradle dependencies using the Intellij Gradle menu to not use cached versions and update to the latest.
- Project folder paths can't contain spaces due to Make not supporting them

## Current Status
- Compiler bug in com_badlogic_gdx_assets_AssetManager_update___R_boolean, so patch for now (Probably related to setjmp/try-catch)
- Switch crash in __GC_MARK_com_badlogic_gdx_utils_JsonValue, so comment out for now
- Flick gesture detection is broken
- GC bug where it tries to dispose of primitive array contents (JSON test)
- Windows PC program crash related to filesystem writing
