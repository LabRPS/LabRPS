if(MSVC)
    add_definitions(-DFCAppSeaLabTools -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(SeaLabTools_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND SeaLabTools_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND SeaLabTools_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(spectrum/JonswapSpectrumPy)
generate_from_xml(spectrum/TorsethaugenSpectrumPy)
generate_from_xml(spectrum/OchiAndHubbleSpectrumPy)
generate_from_xml(spectrum/PiersonMoskowitzSpectrumPy)
generate_from_xml(spectrum/SeaSurfaceSpectrumPy)



SET(SeaLabTools_CPP_SRCS
    SeaLabTools.cpp   
    spectrum/JonswapSpectrum.cpp
    spectrum/TorsethaugenSpectrum.cpp
    spectrum/OchiAndHubbleSpectrum.cpp
    spectrum/PiersonMoskowitzSpectrum.cpp
    spectrum/SeaSurfaceSpectrum.cpp

)

SET(SeaLabTools_HPP_SRCS
    RPS.h
    SeaLabTools.h
    spectrum/JonswapSpectrum.h
    spectrum/TorsethaugenSpectrum.h
    spectrum/OchiAndHubbleSpectrum.h
    spectrum/PiersonMoskowitzSpectrum.h
    spectrum/SeaSurfaceSpectrum.h
)

SET(SeaLabTools_SRCS

    PreCompiled.cpp
    PreCompiled.h
)

SET(Python_SRCS
    spectrum/JonswapSpectrumPyImp.cpp
    spectrum/JonswapSpectrumPy.xml
    spectrum/PiersonMoskowitzSpectrumPyImp.cpp
    spectrum/PiersonMoskowitzSpectrumPy.xml
    spectrum/OchiAndHubbleSpectrumPyImp.cpp
    spectrum/OchiAndHubbleSpectrumPy.xml
    spectrum/TorsethaugenSpectrumPyImp.cpp
    spectrum/TorsethaugenSpectrumPy.xml
    spectrum/SeaSurfaceSpectrumPyImp.cpp
    spectrum/SeaSurfaceSpectrumPy.xml
)

SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    ${SeaLabTools_CPP_SRCS}
    ${SeaLabTools_HPP_SRCS}
    AppSeaLabTools.cpp
    AppSeaLabToolsPy.cpp
    PreCompiled.cpp
    PreCompiled.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The SeaLab stuff

SET(SeaLabTools_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}
)

SET(SeaLabTools_PCH_SRCS
    ${WindModule_SRCS}
    ${Python_SRCS}

)

add_library(SeaLabTools SHARED ${SeaLabTools_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(SeaLabTools ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(SeaLabTools ${Boost_LIBRARIES})

target_link_libraries(SeaLabTools ${SeaLabTools_LIBS})
set_target_properties(SeaLabTools PROPERTIES FOLDER "Workbenches/SeaLabTools")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" SeaLabTools_CPP_SRCS ${SeaLabTools_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeaLabTools PreCompiled.h PreCompiled.cpp SeaLabTools_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(SeaLabTools SeaLabTools /Mod/SeaLabTools)
SET_PYTHON_PREFIX_SUFFIX(SeaLabTools)

INSTALL(TARGETS SeaLabTools DESTINATION ${CMAKE_INSTALL_LIBDIR})
