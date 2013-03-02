file(GLOB headers *.h)
file(GLOB sources *.cpp)

add_definitions(-DMLOG_LIBRARY)

add_library(mlog SHARED ${headers} ${sources})
moon_target_properties(mlog)
moon_target_install(mlog)
install(FILES ${headers} DESTINATION include/mlog)
