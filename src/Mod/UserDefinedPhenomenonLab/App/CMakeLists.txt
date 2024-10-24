# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppUserDefinedPhenomenonLab -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(UserDefinedPhenomenonLab_LIBS
    UserDefinedPhenomenonLabAPI
    LabRPSApp
)

generate_from_xml(UserDefinedPhenomenonLabSimulationPy)
generate_from_xml(UserDefinedPhenomenonLabSimulationComparisonPy)

SET(Properties_SRCS

)
SOURCE_GROUP("Properties" FILES ${Properties_SRCS})


SET(Features_SRCS

)
SOURCE_GROUP("Features" FILES ${Features_SRCS})

SET(Datatypes_SRCS
    UserDefinedPhenomenonLabSimulation.cpp
    UserDefinedPhenomenonLabSimulation.h
    UserDefinedPhenomenonLabSimulationComparison.h
    UserDefinedPhenomenonLabSimulationComparison.cpp
)
SOURCE_GROUP("Datatypes" FILES ${Datatypes_SRCS})

SET(Python_SRCS
    UserDefinedPhenomenonLabSimulationPy.xml
    UserDefinedPhenomenonLabSimulationPyImp.cpp
    UserDefinedPhenomenonLabSimulationComparisonPyImp.cpp

)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    AppUserDefinedPhenomenonLab.cpp
    AppUserDefinedPhenomenonLabPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    UserDefinedPhenomenonLabUtils.cpp
    UserDefinedPhenomenonLabUtils.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

SET(UserDefinedPhenomenonLab_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

SET(UserDefinedPhenomenonLab_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

add_library(UserDefinedPhenomenonLab SHARED ${UserDefinedPhenomenonLab_SRCS})
target_link_libraries(UserDefinedPhenomenonLab ${UserDefinedPhenomenonLab_LIBS})
set_target_properties(UserDefinedPhenomenonLab PROPERTIES FOLDER "Workbenches/UserDefinedPhenomenonLab")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" UserDefinedPhenomenonLab_CPP_SRCS ${UserDefinedPhenomenonLab_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(UserDefinedPhenomenonLab PreCompiled.h PreCompiled.cpp UserDefinedPhenomenonLab_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(UserDefinedPhenomenonLab UserDefinedPhenomenonLab /Mod/UserDefinedPhenomenonLab)
SET_PYTHON_PREFIX_SUFFIX(UserDefinedPhenomenonLab)

INSTALL(TARGETS UserDefinedPhenomenonLab DESTINATION ${CMAKE_INSTALL_LIBDIR})
