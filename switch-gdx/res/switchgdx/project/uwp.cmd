if not defined DevEnvDir (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
)
if not exist ".\build-uwp" mkdir .\build-uwp
if not exist "%USERPROFILE%\.SwitchGDX\" mkdir "%USERPROFILE%\.SwitchGDX"
if not exist "%USERPROFILE%\.SwitchGDX\vcpkg\" (
	git clone -b 2022.10.19 https://github.com/Microsoft/vcpkg "%USERPROFILE%\.SwitchGDX\vcpkg"
	call "%USERPROFILE%\.SwitchGDX\vcpkg\bootstrap-vcpkg.bat"
)

"%USERPROFILE%\.SwitchGDX\vcpkg\vcpkg.exe" install angle:x64-uwp sdl2:x64-uwp libffi:x64-uwp curl:x64-uwp freetype:x64-uwp zziplib:x64-uwp zlib:x64-uwp libvorbis:x64-uwp libogg:x64-uwp mpg123:x64-uwp

cmake -B build-uwp -S . -DVCPKG_ROOT="%USERPROFILE%\.SwitchGDX\vcpkg" -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION="10.0"
cmake --open build-uwp
