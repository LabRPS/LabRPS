# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppSeismicLab -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(SeismicLab_LIBS
    SeismicLabAPI
    LabRPSApp
)

generate_from_xml(SeismicLabSimulationPy)
generate_from_xml(SeismicLabSimulationComparisonPy)

SET(Properties_SRCS

)
SOURCE_GROUP("Properties" FILES ${Properties_SRCS})


SET(Features_SRCS

)
SOURCE_GROUP("Features" FILES ${Features_SRCS})

SET(Datatypes_SRCS
    SeismicLabSimulation.cpp
    SeismicLabSimulation.h
    SeismicLabSimulationComparison.h
    SeismicLabSimulationComparison.cpp
)
SOURCE_GROUP("Datatypes" FILES ${Datatypes_SRCS})

SET(Python_SRCS
    SeismicLabSimulationPy.xml
    SeismicLabSimulationPyImp.cpp
    SeismicLabSimulationComparisonPyImp.cpp

)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    AppSeismicLab.cpp
    AppSeismicLabPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    SeismicLabUtils.cpp
    SeismicLabUtils.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

SET(SeismicLab_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

SET(SeismicLab_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

add_library(SeismicLab SHARED ${SeismicLab_SRCS})
target_link_libraries(SeismicLab ${SeismicLab_LIBS})
set_target_properties(SeismicLab PROPERTIES FOLDER "Workbenches/SeismicLab")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" SeismicLab_CPP_SRCS ${SeismicLab_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeismicLab PreCompiled.h PreCompiled.cpp SeismicLab_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(SeismicLab SeismicLab /Mod/SeismicLab)
SET_PYTHON_PREFIX_SUFFIX(SeismicLab)

INSTALL(TARGETS SeismicLab DESTINATION ${CMAKE_INSTALL_LIBDIR})
