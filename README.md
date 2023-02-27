# SwitchGDX
[![Release](https://jitpack.io/v/com.thelogicmaster/switch-gdx.svg)](https://jitpack.io/#com.thelogicmaster/switch-gdx)

## About
This is a Nintendo Switch Homebrew and Xbox UWP backend for the [LibGDX](https://libgdx.com) game framework. It uses
the [Clearwing VM](https://github.com/TheLogicMaster/clearwing-vm) project to transpile Java to C++ along with custom
native bindings for LibGDX. It supports Nintendo Switch Homebrew builds using LibNX, and Xbox/Windows Store with UWP.
See the SwitchGDX [thread](https://discord.com/channels/348229412858101762/965372515285352468) on the LibGDX Discord 
server for support.

**Pixel Wheels and Shattered Pixel Dungeon Ports**
![Pixel Wheels](media/PixelWheels.png)
![Shattered Pixel Dungeon](media/ShatteredPixel.png)

## Features
- Full GDX Reflection support
- GDX Controllers support for all Switch controller layouts
- GDX Preferences for persistent data
- Desktop builds for debugging with emulated controller inputs
- Xbox UWP builds

## Compatibility
The majority of LibGDX is fully supported. A few features such as GL30 and audio recording are currently unsupported.

## Extensions
FreeType, Controllers, and Box2D are supported. Bullet may be supported in the future.

## JVM Languages
Since Clearwing takes Bytecode as an input, it can support any JVM language. The main limitation would be the Clearwing
runtime library, which is limited and may not support all required functionality, though this can typically be easily
added as needed. Java and Kotlin have been tested and work.

## Libraries
Pure Java libraries should work without any extra work, assuming they don't use unsupported runtime library features or
JNI. Libraries compiled with a JDK version greater than 8 could also pose an issue. If a library uses JNI, custom native
bindings could be provided and things should just work, the shared library loading API has no effect. See
[Libraries](LIBRARIES.md) for a list of tested libraries.

## Ports
These are some LibGDX games that have been ported using SwitchGDX.
- [Shattered Pixel Dungeon](https://github.com/TheLogicMaster/shattered-pixel-dungeon-switchgdx)
- [Pixel Wheels](https://github.com/TheLogicMaster/pixelwheels-switchgdx)
- [Bomberman GDX](https://github.com/TheLogicMaster/Bomberman-SwitchGDX)
- [Pepper and Carrot Running Game](https://github.com/TheLogicMaster/PepperAndCarrotRunningGame)
- [TriPeaks](https://github.com/TheLogicMaster/tripeaks-switchgdx)
- [A Square Astray](https://github.com/TheLogicMaster/A-Square-Astray-SwitchGDX)
- [Unlucky](https://github.com/TheLogicMaster/Unlucky)
- [Klooni 1010](https://github.com/TheLogicMaster/Klooni1010)
- [Jewel Thief](https://github.com/TheLogicMaster/jewelthief)
- [nO mooRe](https://github.com/TheLogicMaster/nomoore)

## Todo
- Bullet bindings
- Multithreaded AssetManager support
- Switch-specific API (Controller remapping)
- Controller analog trigger support, remapping API, rumble
- I18N non-simple
- Sound effect pitch control
- GL30
- Set main thread exception handler to show error dialog
- Fix sockets
- VSCode project support
- Keyboard input support
- Mac OS support

## Limitations
See the [Clearwing](https://github.com/TheLogicMaster/clearwing-vm) documentation for the limitations inherent to the "VM"
- Only one Music instance can play at a time
- Sound effects are limited to OGG and WAV, Music supports MP3, OGG, and WAV
- Reflection is disabled by default, use the `reflective` `switch.json` config option to enable it for specific classes
- Socket server only supports IPv4

## Installation
In addition to the C++ dependencies, JDK 16 is required. Rsync is used for incremental compilation, and CMake is used
for building the generated C++ project.

### Linux
- Install CMake, Ninja, Rsync, Texinfo, SDL2, SDL2_Mixer, GLEW, zlib, Freetype, curl, Bullet
- With APT: `sudo apt install build-essential texinfo rsync cmake ninja-build libsdl2-mixer-dev zlib1g-dev libglew-dev libfreetype-dev libcurl4-gnutls-dev libzzip-dev`
- Install [devkitPro pacman](https://github.com/devkitPro/pacman/releases/tag/v1.0.2)
- `dkp-pacman -S switch-zlib switch-libvorbis switch-zziplib switch-sdl2 switch-sdl2_mixer switch-freetype switch-glad switch-curl switch-bulletphysics dkp-toolchain-vars`

### Windows
- Install [devkitPro Updater](https://github.com/devkitPro/installer/releases/latest) with Switch packages selected (Leave downloaded files)
- Open MSYS2 from the start menu
- `pacman -Syu`
- `pacman -S switch-zlib switch-libvorbis switch-zziplib switch-sdl2_mixer switch-freetype switch-glad switch-curl switch-bulletphysics dkp-toolchain-vars`
- `pacman -S gcc git rsync cmake mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake texinfo mingw-w64-x86_64-glew mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-curl-gnutls mingw-w64-x86_64-freetype mingw-w64-x86_64-zziplib mingw-w64-x86_64-zlib mingw-w64-x86_64-bullet`

### UWP
- Follow `Windows` steps above
- Install [git](https://git-scm.com/downloads) and add to path
- Install Visual Studio Community 2019 with UWP/C++ support
- Remove the devKitPro MinGW bin directory from `Path` in _Environment Variables_, or it will mess with vcpkg

## Project Setup
For reference, there's an `example` project provided with the needed Gradle config to build a SwitchGDX project. If you
are creating a new LibGDX project, there's a fork of the project builder, [gdx-liftoff](https://github.com/tommyettinger/gdx-liftoff), 
with the SwitchGDX backend [here](https://github.com/TheLogicMaster/gdx-liftoff). Just enable the Switch backend, and it
will take care of the rest. To add SwitchGDX to an existing project, a new Gradle subproject needs to be created, 
adding the `switch` directory with the icon, `switch.json` config file, `build.gradle` file, and the actual `src`
directory with the `SwitchLauncher` source class. The module needs to be added to `settings.gradle`, and the 
`clearwingVersion` and `switchGdxVersion` properties need to be set in either `gradle.properties` or the top level 
`build.gradle`, depending on the project layout. The switch `build.gradle` can be mostly copy-pasted, changing only
the title and author variables and the asset copy paths, if not in `core/assets`. Any source paths to be used with the
jnigen style native code inlining also needs to be added to the transpiler arguments in `switch/build.gradle`. As far
as [libraries](LIBRARIES.md) are concerned, if they require using GDX reflection, then those classes need to be added
to the `switch.json` `reflective` class pattern list. The list of verified libraries details the needed config 
entries. To enable the Ryujinx emulator, download/install it then set `ryujinxPath` in the `local.properties` file 
(Create if needed). Make sure Java Home points to Java 16 or select a Java 16 JDK as the Gradle JDK in Intellij build 
settings. Ensure that the project itself compiles with the Java 8 language level. 

## Usage
All the main tasks are present in the `switchgdx` Gradle group in the `switch` submodule. The first time transpiling
will be quite long, but subsequent runs will be comparatively snappy. Incremental compilation is achieved here by
transpiling into one directory then using rsync to only copy the changed files into the final C++ project directory.
- __transpile__: Run the transpiler and generate the C++ project
- __run__: Transpile, then run the C++ project in desktop-mode with emulated controller inputs (Yuzu layout)
- __nro__: Transpile, then build a Nintendo Switch Homebrew NRO executable
- __deploy__: Build NRO, then deploy to a Switch over LAN using NxLink
- __ryujinx__: Build NRO, then run in Ryujinx emulator
- __uwp__: Transpile, then open UWP project in Visual Studio

### Deploying to Switch
Ensure that the Homebrew Launcher is opened to the NetLoader before running the deploy task. By default, it tries
pinging the Switch to find it, but manually specifying the IP in the nxlink command may be necessary depending on the 
network.

### UWP
The UWP task opens Visual Studio, where the project settings need to be adjusted for the signing certificate and remote 
deployment options for running on an Xbox console in devkit mode. Running a debug build should be as simple as building
the project and running it. There's a bug where the UWP project needs to be manually rebuilt to for the assets to be 
copied over into the UWP build directory. The first time 
the task is run will be quite slow, as it needs to install the VCPKG dependencies into `<home_dir>/.SwitchGDX`. If this
first task gets interrupted before finishing, deleting the vcpkg directory and trying again may be necessary. Currently,
for Release builds to link successfully, the debug runtime library (/MDd) needs to be used. 

## Debugging
The project can be debugged as a normal C++ project with your IDE of choice. CLion works out of the box with
the CMake project. Simply run one of the Gradle tasks to transpile the project, then
open the `<project>/switch/build/<project>` directory with CLion as a CMake project. A Run configuration should be automatically created. 
Set the working directory in the run config to the `switch/build/<project>` project directory so that assets
can be properly loaded at runtime. To trace back a native crash, simply press the debug icon next to the run
configuration, and it should jump right to the exception and show the native stack trace. By inspecting the
generated code and call stack, null fields can be found and traced back to Java source code by looking at the
`vm::setLineNumber` line numbers. Code changes may lead to additional classes being included by the transpiler, in which case
the CLion CMake project needs to be reloaded using `Tools/Cmake/Reload CMake Project` or it won't compile.
If using Windows, the devkitPro MinGW toolchain has to be selected under the project build settings. To debug a Java
Exception being thrown, setting a breakpoint at the throw statement can be quite useful. If it's a place you can't
easily add print-lines like a library, `printf` combined with `vm::getNativeString` can also be helpful to print out a
Java string, potentially obtained from `Object#toString`. In CLion, `vm::getNativeString` can also be evaluated while
debugging, which is often extremely useful for dynamically inspecting values without recompiling.
### Windows
On Windows, if you change the working directory in CLion, it doesn't seem to find the required shared libraries, so
manually copying the DLLs from `C:\devkitPro\msys2\mingw64\bin` into the executable directory may be necessary. Adding
the directory to the `Path` doesn't seem to be sufficient.

## Test Suite
The `tests` module is for running the GDX test suite and verifying GDX functionality. See [Tests](TESTS.md) for working
features. Building the test module requires building the tests module JAR in the libgdx repo and putting it in 
`tests/libs`, in addition to the lwjgl3 test module JAR for the required assets. The `tests` module is disabled if the 
`tests/libs` directory doesn't exist to not break JitPack builds and such.

## Notes
- Concurrent access to files is more limited on Switch where it might normally work on PC, so ensure files are closed properly
- For Switch, all threads need to be joined manually, or it will crash on exit or when ran a second time. Any program 
threads must be manually stopped/joined on dispose.
- If using SNAPSHOT Gradle dependency (Not recommended), refresh Gradle dependencies using the Intellij Gradle menu to not use cached versions and update to the latest.
- The UWP project generation has a bug where the project has to be manually rebuilt in Visual Studio for the assets to be properly copied
- The UWP project requires a custom build of SDL2_mixer since the VCPKG library doesn't support UWP, for some reason. 
This requires downloading the SDL2_mixer and SDL2 source and building the UWP subproject to update it.
- When using Joycons individually, the inputs will be rotated horizontally. Controllers must be remapped from the home menu for now. 
- `Controllers#getCurrentController` returns a controller representing all controller input, rather than the last controller.
