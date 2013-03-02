file(GLOB headers *.h)
file(GLOB sources *.cpp)

add_definitions(-DMDRAW_LIBRARY)

add_library(mdraw SHARED ${headers} ${sources})

if (WIN32 AND NOT MINGW)
    target_link_libraries(mdraw
    	debug ${LIB_OSG_D} optimized ${LIB_OSG}
    	debug ${LIB_OSGDB_D} optimized ${LIB_OSGDB}
    	debug ${LIB_OSGUTIL_D} optimized ${LIB_OSGUTIL}
    	debug ${LIB_OSGTEXT_D} optimized ${LIB_OSGTEXT}
    	debug ${LIB_OSGFX_D} optimized ${LIB_OSGFX}
    	debug ${LIB_OSGPARTICLE_D} optimized ${LIB_OSGPARTICLE}
    	debug ${LIB_OPENTHREADS_D} optimized ${LIB_OPENTHREADS}
    )
else()
    target_link_libraries(mdraw 
    	${LIB_OSG}
    	${LIB_OSGDB}
    	${LIB_OSGUTIL}
    	${LIB_OSGTEXT}
    	${LIB_OSGFX}
    	${LIB_OSGPARTICLE}
    	${LIB_OPENTHREADS}
    )
endif()

moon_target_properties(mdraw)
moon_target_install(mdraw)
install(FILES ${headers} DESTINATION include/mdraw)
