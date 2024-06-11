if(MSVC)
    add_definitions(-DFCAppGeneralTools -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
else(MSVC)
    add_definitions(-DHAVE_LIMITS_H -DHAVE_CONFIG_H)
endif(MSVC)

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${Boost_INCLUDE_DIRS}
    ${OCC_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)
link_directories(${OCC_LIBRARY_DIR})

set(GeneralTools_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND GeneralTools_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND GeneralTools_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

SET(GeneralTools_CPP_SRCS
CholeskyDecomposition.cpp
UniformRandomPhaseMatrixGenerator.cpp
AvailableWindows.cpp
   
)

SET(GeneralTools_HPP_SRCS
RPS.h
CholeskyDecomposition.h
UniformRandomPhaseMatrixGenerator.h
AvailableWindows.h

)

SET(GeneralTools_SRCS

    PreCompiled.cpp
    PreCompiled.h
)

SET(Python_SRCS

)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    ${GeneralTools_CPP_SRCS}
    ${GeneralTools_HPP_SRCS}
    AppGeneralTools.cpp
    AppGeneralToolsPy.cpp
    PreCompiled.cpp
    PreCompiled.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The WindLab stuff

SET(GeneralTools_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}
)

SET(GeneralTools_PCH_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}

)

add_library(GeneralTools SHARED ${GeneralTools_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(GeneralTools ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(GeneralTools ${Boost_LIBRARIES})

target_link_libraries(GeneralTools ${GeneralTools_LIBS})
set_target_properties(GeneralTools PROPERTIES FOLDER "Workbenches/GeneralTools")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" GeneralTools_CPP_SRCS ${GeneralTools_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(GeneralTools PreCompiled.h PreCompiled.cpp GeneralTools_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(GeneralTools GeneralTools /Mod/GeneralTools)
SET_PYTHON_PREFIX_SUFFIX(GeneralTools)

INSTALL(TARGETS GeneralTools DESTINATION ${CMAKE_INSTALL_LIBDIR})
