if (WIN32 AND NOT MINGW)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD" )
endif()

file(GLOB_RECURSE test_sources test_*.cpp)

add_library(moonplug_test MODULE moon/TestPlugin.h moon/TestPlugin.cpp)
target_link_libraries(moonplug_test moon)
moonplugin_target_properties(moonplug_test)

get_target_property(plugpath moonplug_test LIBRARY_OUTPUT_DIRECTORY)
add_definitions(-DMOONTEST_PLUGIN_PATH="${plugpath}")

add_executable(moontest ${test_sources})
target_link_libraries(moontest moon ${LIB_UNITTEST})
moon_target_properties(moontest)

moon_target_install(moontest)
moonplugin_target_install(moonplug_test)
