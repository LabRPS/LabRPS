# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppSeaLab -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(SeaLab_LIBS
    SeaLabAPI
    LabRPSApp
)

generate_from_xml(SeaLabSimulationPy)
generate_from_xml(SeaLabSimulationComparisonPy)

SET(Properties_SRCS

)
SOURCE_GROUP("Properties" FILES ${Properties_SRCS})


SET(Features_SRCS

)
SOURCE_GROUP("Features" FILES ${Features_SRCS})

SET(Datatypes_SRCS
    SeaLabSimulation.cpp
    SeaLabSimulation.h
    SeaLabSimulationComparison.h
    SeaLabSimulationComparison.cpp
)
SOURCE_GROUP("Datatypes" FILES ${Datatypes_SRCS})

SET(Python_SRCS
    SeaLabSimulationPy.xml
    SeaLabSimulationPyImp.cpp
    SeaLabSimulationComparisonPyImp.cpp

)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    AppSeaLab.cpp
    AppSeaLabPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    SeaLabUtils.cpp
    SeaLabUtils.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

SET(SeaLab_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

SET(SeaLab_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

add_library(SeaLab SHARED ${SeaLab_SRCS})
target_link_libraries(SeaLab ${SeaLab_LIBS})
set_target_properties(SeaLab PROPERTIES FOLDER "Workbenches/SeaLab")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" SeaLab_CPP_SRCS ${SeaLab_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeaLab PreCompiled.h PreCompiled.cpp SeaLab_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(SeaLab SeaLab /Mod/SeaLab)
SET_PYTHON_PREFIX_SUFFIX(SeaLab)

INSTALL(TARGETS SeaLab DESTINATION ${CMAKE_INSTALL_LIBDIR})
