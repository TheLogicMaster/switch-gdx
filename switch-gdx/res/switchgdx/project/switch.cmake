cmake_minimum_required(VERSION 3.1)

get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
include(SwitchTools)

add_definitions(-DNOJNI -DEGL_NO_X11 -D_REENTRANT)

file(GLOB_RECURSE SRCS src/*.cpp src/*.c)
include_directories(src)
add_executable(${PROJECT_NAME} ${SRCS})

target_compile_options(${PROJECT_NAME} PRIVATE -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-unused-label -Wno-unused-function)

set_target_properties(${PROJECT_NAME} PROPERTIES
        APP_TITLE "$ENV{APP_TITLE}"
        APP_AUTHOR "$ENV{APP_AUTHOR}"
        APP_VERSION "$ENV{APP_VERSION}"
        ROMFS "${CMAKE_SOURCE_DIR}/romfs")

target_include_directories(${PROJECT_NAME} PUBLIC include ${DEVKITPRO}/libnx/include ${PORTLIBS}/include ${PORTLIBS}/include/freetype2 ${PORTLIBS}/include/SDL2)
target_link_libraries(${PROJECT_NAME} -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIC -ftls-model=local-exec -fPIE -L${DEVKITPRO}/libnx/lib -L${PORTLIBS}/lib
        -lglad -lEGL -lglapi -ldrm_nouveau -lcurl -lzzip -lSDL2_mixer -lSDL2 -lvorbisidec -lvorbis -lmodplug -logg -lopusfile -lopus -lmpg123 -lpthread -lfreetype
        -lz -lbz2 -lpng -lnx -lstdc++ -lm)

add_nro_target(${PROJECT_NAME})
