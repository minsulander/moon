find_library(LIB_ODE ode)
if (LIB_ODE)

	if (WIN32 AND NOT MINGW)
		set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD" )
	endif()
	
	# Library used by both plugin and unit tests
	file(GLOB headers *.h objects/*.h components/*.h bindings/*.h)
	file(GLOB sources *.cpp objects/*.cpp components/*.cpp bindings/*.cpp)
	add_library(moodyn SHARED ${headers} ${sources})
	target_link_libraries(moodyn moon ${LIB_ODE})
	moon_target_properties(moodyn)
	set_target_properties(moodyn PROPERTIES COMPILE_DEFINITIONS "MOODYN_LIBRARY;TOLUA_EXPORTS")
	
	file(GLOB plugin_sources plugin/*.h plugin/*.cpp)
	add_library(moonplug_moodyn MODULE ${plugin_sources})
	target_link_libraries(moonplug_moodyn moodyn)
	moonplugin_target_properties(moonplug_moodyn)
	
	file(GLOB test_sources test/*.cpp)
	add_executable(moontest_moodyn ${test_sources} ../test/test_main.cpp)
	target_link_libraries(moontest_moodyn moodyn ${LIB_UNITTEST})
	moon_target_properties(moontest_moodyn)
	
	moon_target_install(moodyn moontest_moodyn)
	moonplugin_target_install(moonplug_moodyn)
	install(FILES ${headers} DESTINATION include/moodyn)

	message("Dynamics plugin (moodyn) configured")
	set(BUILD_DYNAMICS YES PARENT_SCOPE)
else()
	message("Dynamics plugin (moodyn) NOT configured")
endif()
