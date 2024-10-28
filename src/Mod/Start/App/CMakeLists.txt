include_directories(
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)

set(Start_LIBS
    LabRPSApp
)

SET(Start_SRCS
    AppStart.cpp
    PreCompiled.cpp
    PreCompiled.h
    StartConfiguration.h
)



add_library(Start SHARED ${Start_SRCS})
target_link_libraries(Start ${Start_LIBS})

set_target_properties(Start PROPERTIES FOLDER "Workbenches/Start")

SET_BIN_DIR(Start Start /Mod/Start)
SET_PYTHON_PREFIX_SUFFIX(Start)

INSTALL(TARGETS Start DESTINATION ${CMAKE_INSTALL_LIBDIR})
