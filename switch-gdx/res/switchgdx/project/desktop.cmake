cmake_minimum_required(VERSION 3.0)
project(SwitchGDX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(OpenGL_GL_PREFERENCE GLVND)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_mixer REQUIRED SDL2_mixer)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)
find_package(CURL REQUIRED)
find_package(ZZip REQUIRED)

add_definitions(-DNOJNI)

file(GLOB_RECURSE SRCS src/*.cpp src/*.c)
include_directories(src)
add_executable(SwitchGDX ${SRCS})

target_compile_options(SwitchGDX PRIVATE -Wno-return-type -Wno-invalid-offsetof)

target_include_directories(SwitchGDX PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${ZZip_INCLUDE_DIRS})
target_link_libraries(SwitchGDX ${SDL2_LIBRARIES} ${SDL2_mixer_LIBRARIES} ${OPENGL_LIBRARIES} ${ZLIB_LIBRARIES} stdc++fs ${FREETYPE_LIBRARIES} ${CURL_LIBRARIES} ${ZZip_LIBRARIES})
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(SwitchGDX "${CMAKE_THREAD_LIBS_INIT}")
endif()
if(WIN32)
  target_link_libraries(SwitchGDX wsock32 ws2_32)
endif()
