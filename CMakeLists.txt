project(moon)

cmake_minimum_required(VERSION 2.6.0)
include(CTest)
enable_testing()

if(MINGW)
	set(default_depdir "moon-dependencies-mingw-i686")
elseif(WIN32)
    set(default_depdir "moon-dependencies-win32")
elseif(APPLE)
    set(default_depdir "moon-dependencies-mac-${CMAKE_SYSTEM_PROCESSOR}")
else()
    string(TOLOWER ${CMAKE_SYSTEM_NAME} unamelow)
    set(default_depdir "moon-dependencies-${unamelow}-${CMAKE_SYSTEM_PROCESSOR}")
endif()
set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/${default_depdir} CACHE PATH "Location of moon-dependencies")

add_subdirectory(src)
