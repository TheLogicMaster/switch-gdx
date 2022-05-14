cmake_minimum_required(VERSION 3.0)
project(dist)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(OpenGL_GL_PREFERENCE GLVND)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_mixer REQUIRED SDL2_mixer)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)
find_package(FFI REQUIRED)
find_package(Freetype REQUIRED)
find_package(CURL REQUIRED)

add_definitions(-DNOJNI)

include_directories(include)
FILE(GLOB_RECURSE SRCS include/*.h source/*.c source/*.cpp)
add_executable(dist ${SRCS})

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(dist PUBLIC "-pthread")
endif()

target_include_directories(dist PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${FFI_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
target_link_libraries(dist ${SDL2_LIBRARIES} ${SDL2_mixer_LIBRARIES} ${OPENGL_LIBRARIES} ${ZLIB_LIBRARIES} stdc++fs ${FFI_LIBRARIES} ${FREETYPE_LIBRARIES} ${CURL_LIBRARIES})
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(dist "${CMAKE_THREAD_LIBS_INIT}")
endif()
