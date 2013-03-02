find_library(LIB_OPENAL openal)
find_library(LIB_VORBISFILE vorbisfile)
find_library(LIB_SNDFILE sndfile)
find_library(LIB_MPG123 mpg123)

if (LIB_OPENAL AND LIB_VORBISFILE AND LIB_SNDFILE AND LIB_MPG123)

	if (UNIX)
		add_definitions(-D_FILE_OFFSET_BITS=64)
	elseif (WIN32 AND NOT MINGW)
		set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD" )
	endif()

	# Library used by both plugin and unit tests
	file(GLOB headers *.h objects/*.h bindings/*.h)
	file(GLOB sources *.cpp objects/*.cpp bindings/*.cpp)
	add_library(maudio SHARED ${headers} ${sources})
	target_link_libraries(maudio
		moon
		${LIB_VORBISFILE}
		${LIB_SNDFILE}
		${LIB_MPG123}
		${LIB_OPENAL}
	)
	moon_target_properties(maudio)
	set_target_properties(maudio PROPERTIES COMPILE_DEFINITIONS "MAUDIO_LIBRARY;TOLUA_EXPORTS")
	
	file(GLOB plugin_sources plugin/*.h plugin/*.cpp)
	add_library(moonplug_maudio MODULE ${plugin_sources})
	target_link_libraries(moonplug_maudio maudio)
	moonplugin_target_properties(moonplug_maudio)
	
	set(TEST_AUDIO NO CACHE BOOL "Run maudio unit tests with audio output")
	if (NOT TEST_AUDIO)
		add_definitions(-DMAUDIO_TEST_SILENT)
	endif()
	add_definitions(-DMAUDIO_TESTFILE_WAV="audio/test/test.wav")
	add_definitions(-DMAUDIO_TESTFILE_OGG="audio/test/test.ogg")
	add_definitions(-DMAUDIO_TESTFILE_MP3="audio/test/test.mp3")
	add_definitions(-DMAUDIO_TESTSTREAM_WAV="audio/test/test-stream.wav")
	add_definitions(-DMAUDIO_TESTSTREAM_OGG="audio/test/test-stream.ogg")
	add_definitions(-DMAUDIO_TESTSTREAM_MP3="audio/test/test-stream.mp3")
	file(GLOB test_sources test/*.cpp)
	add_executable(moontest_maudio ${test_sources})
	target_link_libraries(moontest_maudio maudio UnitTest++)
	moon_target_properties(moontest_maudio)

	add_executable(alinfo alinfo.cpp)
	target_link_libraries(alinfo ${LIB_OPENAL})
	moon_target_properties(alinfo)
	
	moon_target_install(maudio alinfo moontest_maudio)
	moonplugin_target_install(moonplug_maudio)
	install(FILES ${headers} DESTINATION include/maudio)
	
	message("Audio plugin (maudio) configured")
	set(BUILD_AUDIO YES PARENT_SCOPE)
else()
	message("Audio plugin (maudio) NOT configured")
	message("  Audio libraries:\n  ${LIB_OPENAL}\n  ${LIB_VORBISFILE}\n  ${LIB_SNDFILE}\n  ${LIB_MPG123}")
endif()
