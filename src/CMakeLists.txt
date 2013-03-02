set(USE_RAKNET YES CACHE BOOL "Use RakNet-based network code?")
set(CMAKE_INCLUDE_PATH ${DEPENDENCIES_DIR}/include)
set(CMAKE_LIBRARY_PATH ${DEPENDENCIES_DIR}/lib)

message("Dependencies in ${DEPENDENCIES_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/src ${DEPENDENCIES_DIR}/include /usr/include/lua5.1)
link_directories(${DEPENDENCIES_DIR}/lib)

option(COVERAGE "Compile for coverage testing")
if (COVERAGE)
  add_definitions(-fprofile-arcs -ftest-coverage)
endif()

find_library(LIB_OSG osg)
find_library(LIB_OSGDB osgDB)
find_library(LIB_OSGUTIL osgUtil)
find_library(LIB_OSGFX osgFX)
find_library(LIB_OSGGA osgGA)
find_library(LIB_OSGMANIPULATOR osgManipulator)
find_library(LIB_OSGPARTICLE osgParticle)
find_library(LIB_OSGSHADOW osgShadow)
find_library(LIB_OSGSIM osgSim)
find_library(LIB_OSGTERRAIN osgTerrain)
find_library(LIB_OSGTEXT osgText)
find_library(LIB_OSGVIEWER osgViewer)
find_library(LIB_OPENTHREADS OpenThreads)
find_library(LIB_TINYXML tinyxml)
find_library(LIB_TOLUA tolua)
find_library(LIB_LUA lua)
find_library(LIB_UNITTEST unittest++)
find_library(LIB_FLTK FLTK)
find_library(LIB_READLINE readline)

if (LIB_FLTK)
	add_definitions(-DMOON_USE_FLTK)
endif()

if (WIN32 AND NOT MINGW)
    find_library(LIB_OSG_D osgd)
    find_library(LIB_OSGDB_D osgDBd)
    find_library(LIB_OSGUTIL_D osgUtild)
    find_library(LIB_OSGFX_D osgFXd)
    find_library(LIB_OSGGA_D osgGAd)
    find_library(LIB_OSGMANIPULATOR_D osgManipulatord)
    find_library(LIB_OSGPARTICLE_D osgParticled)
    find_library(LIB_OSGSHADOW_D osgShadowd)
    find_library(LIB_OSGSIM_D osgSimd)
    find_library(LIB_OSGTERRAIN_D osgTerraind)
    find_library(LIB_OSGTEXT_D osgTextd)
    find_library(LIB_OSGVIEWER_D osgViewerd)
    find_library(LIB_OPENTHREADS_D OpenThreadsd)
    find_library(LIB_TINYXML_D TinyXMLd)
    find_library(LIB_TOLUA_D toluad)
    find_library(LIB_LUA_D luad)
    find_library(LIB_FLTK_D FLTKd)
endif()

if (APPLE)
    find_library(LIB_CARBON Carbon)
    find_library(LIB_IOKIT IOKit)
endif()

if (USE_RAKNET)
    add_definitions(-DMOONET_USE_RAKNET)
endif()

if (UNIX)
	add_definitions(-Wno-unused)
endif()

set_directory_properties(PROPERTIES
        COMPILE_DEFINITIONS_DEBUG MOON_DEBUG
)

if (NOT WIN32)
  set_directory_properties(PROPERTIES
    LINK_FLAGS -rdynamic
    )
endif()

macro(moon_target_properties)
    set_target_properties(${ARGV} PROPERTIES
        DEBUG_POSTFIX d
        ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
    )
    if (COVERAGE)
      target_link_libraries(${ARGV0} gcov)
    endif()
endmacro()
macro(moonplugin_target_properties)
    moon_target_properties(${ARGV})
    set_target_properties(${ARGV} PROPERTIES
        COMPILE_DEFINITIONS MOON_PLUGIN 
        PREFIX ""
    )
    if (WIN32)
        set_target_properties(${ARGV} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/moonPlugins
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/moonPlugins
        )
    else()
        set_target_properties(${ARGV} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/moonPlugins
        )
    endif()
    if (COVERAGE)
      target_link_libraries(${ARGV0} gcov)
    endif()
endmacro()

macro(moon_target_install)
    install(
        TARGETS ${ARGV}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endmacro()

macro(moonplugin_target_install)
    install(
        TARGETS ${ARGV}
        RUNTIME DESTINATION bin/moonPlugins
        LIBRARY DESTINATION lib/moonPlugins
        ARCHIVE DESTINATION lib/moonPlugins
    )
endmacro()

# TODO: move remaining moodyn code into plugin and remove MOON_NO_PHYSICS definition
add_definitions(-DMOON_NO_PHYSICS)

add_subdirectory(mlog)
add_subdirectory(moonet)
add_subdirectory(mdraw)
add_subdirectory(moon)
add_subdirectory(test)
add_subdirectory(maudio)
add_subdirectory(moodyn)

add_executable(moonshell moonshell.cpp)
target_link_libraries(moonshell moon)
add_executable(moonmodelinfo moonmodelinfo.cpp)
target_link_libraries(moonmodelinfo moon)
moon_target_properties(moonshell moonmodelinfo)
moon_target_install(moonshell moonmodelinfo)

if (WIN32)
    set(testenv "${PROJECT_BINARY_DIR}/../scripts/moon-test-env.bat;${PROJECT_BINARY_DIR};${DEPENDENCIES_DIR}")
    set(testdisplay "${testenv};moonshell")
    # The windows batch file can only take 8 arguments.... argh. need workaround.
else()
    set(testenv "${PROJECT_BINARY_DIR}/../scripts/moon-test-env;${PROJECT_BINARY_DIR};${DEPENDENCIES_DIR}")
    set(testdisplay "${testenv};moonshell;-window;0;0;800;500")
endif()

add_test(UnitTests ${testenv} moontest)
if (BUILD_AUDIO)
    add_test(AudioUnitTests ${testenv} moontest_maudio)
endif()
if(BUILD_DYNAMICS)
    add_test(DynamicsUnitTests ${testenv} moontest_moodyn)
endif()
add_test(LuaSetup ${testenv} moonshell -nodisplay -end 0.1 test/check_setup.lua)
add_test(LuaPlugins ${testenv} moonshell -allplugins -nodisplay -end 0.1 test/check_plugins.lua)

if (NOT WIN32)
	add_test(NetTest ${testenv} ${PROJECT_BINARY_DIR}/../scripts/moon-net-test d2e test/test_network.xml test/test_network.lua)
endif()

set(TEST_DISPLAY NO CACHE BOOL "Run scenario tests with display?")
if(TEST_DISPLAY)
    add_test(LuaSmallestPossible ${testdisplay} -end 0.5 examples/smallest_possible.xml test/check_smallest_possible.lua)
    add_test(LuaKinematic ${testdisplay} -end 5 -simscale 3 -c examples/kinematic.xml test/check_kinematic.lua)
    add_test(LuaScriptedObject ${testdisplay} -end 6 -simscale 3 -c examples/scripted_object.xml test/check_scripted_object.lua)
    if(BUILD_DYNAMICS)
        add_test(LuaDynamicsBounce ${testdisplay} -end 30 -c -simnrt 10 examples/dynamics_bounce.xml test/check_dynamics_bounce.lua)
    endif()
else()
    add_test(LuaSmallestPossible ${testenv} moonshell -nodisplay -end 0.1 examples/smallest_possible.xml test/check_smallest_possible.lua)
    add_test(LuaKinematic ${testenv} moonshell -nodisplay -end 3 -simnrt 10 examples/kinematic.xml test/check_kinematic.lua)
    add_test(LuaScriptedObject ${testenv} moonshell -nodisplay -end 3.5 -simnrt 10 examples/scripted_object.xml test/check_scripted_object.lua)
    if(BUILD_DYNAMICS)
        add_test(LuaDynamicsBounce ${testenv} moonshell -nodisplay -end 21 -simnrt 10 examples/dynamics_bounce.xml test/check_dynamics_bounce.lua)
    endif()
endif()

