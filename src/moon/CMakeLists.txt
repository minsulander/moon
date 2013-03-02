file(GLOB_RECURSE sources *.cpp)
file(GLOB_RECURSE headers *.h)

set(USE_PLIB YES CACHE BOOL "Use PLIB joystick code?")
if (USE_PLIB)
	add_definitions(-DMOON_USE_PLIB_JOYSTICK)
endif()

add_library(moon SHARED 
	${headers} ${sources} 
	../units/units.h ../units/units.cpp)

target_link_libraries(moon
	mlog
	mdraw
	moonet
)
if (WIN32 AND NOT MINGW)
    target_link_libraries(moon
    	debug ${LIB_OSGGA_D} optimized ${LIB_OSGGA}
    	debug ${LIB_OSGMANIPULATOR_D} optimized ${LIB_OSGMANIPULATOR}
    	debug ${LIB_OSGSHADOW_D} optimized ${LIB_OSGSHADOW}
    	debug ${LIB_OSGSIM_D} optimized ${LIB_OSGSIM}
    	debug ${LIB_OSGTERRAIN_D} optimized ${LIB_OSGTERRAIN}
    	debug ${LIB_OSGVIEWER_D} optimized ${LIB_OSGVIEWER}
    	debug ${LIB_TINYXML_D} optimized ${LIB_TINYXML}
    	debug ${LIB_TOLUA_D} optimized ${LIB_TOLUA}
    	debug ${LIB_LUA_D} optimized ${LIB_LUA}
    )
    if (LIB_FLTK)
    	target_link_libraries(moon
            debug ${LIB_FLTK_D} optimized ${LIB_FLTK}
            comctl32 wsock32
        )
    endif()

	set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT" )
else()
    target_link_libraries(moon
    	${LIB_OSGGA}
    	${LIB_OSGMANIPULATOR}
    	${LIB_OSGSHADOW}
    	${LIB_OSGSIM}
    	${LIB_OSGTERRAIN}
    	${LIB_OSGVIEWER}
    	${LIB_TINYXML}
    	${LIB_TOLUA}
    	${LIB_LUA}
    )
    if (LIB_FLTK)
	    target_link_libraries(moon ${LIB_FLTK})
    endif()
endif()

if (LIB_READLINE)
	# Used by TerminalConsole
	target_link_libraries(moon ${LIB_READLINE})
	add_definitions(-DLUA_USE_READLINE)
endif()

if (APPLE)
	target_link_libraries(moon ${LIB_CARBON} ${LIB_IOKIT})
endif()

if (USE_PLIB)
	find_library(LIB_PLIBJS plibjs)
	find_library(LIB_PLIBUL plibul)
	target_link_libraries(moon ${LIB_PLIBJS} ${LIB_PLIBUL})
endif()

if (WIN32)
    target_link_libraries(moon winmm)
endif()
	
moon_target_properties(moon)
set_target_properties(moon PROPERTIES COMPILE_DEFINITIONS "MOON_LIBRARY;TOLUA_EXPORTS")
moon_target_install(moon)
install(FILES ${headers} DESTINATION include/moon)

list(APPEND build_items "core")
