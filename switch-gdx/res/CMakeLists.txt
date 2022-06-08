cmake_minimum_required(VERSION 3.0)
project(SwitchGDX)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
	include(uwp.cmake)
else()
	include(desktop.cmake)
endif()
