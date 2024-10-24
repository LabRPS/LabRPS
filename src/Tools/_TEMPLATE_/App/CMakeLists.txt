
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${XercesC_INCLUDE_DIRS}
)

set(_TEMPLATE__LIBS
    LabRPSApp
)

SET(_TEMPLATE__SRCS
    App_TEMPLATE_.cpp
    PreCompiled.cpp
    PreCompiled.h
)

add_library(_TEMPLATE_ SHARED ${_TEMPLATE__SRCS})
target_link_libraries(_TEMPLATE_ ${_TEMPLATE__LIBS})


SET_BIN_DIR(_TEMPLATE_ _TEMPLATE_ /Mod/_TEMPLATE_)
SET_PYTHON_PREFIX_SUFFIX(_TEMPLATE_)

install(TARGETS _TEMPLATE_ DESTINATION ${CMAKE_INSTALL_LIBDIR})
