# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppUserLab -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(UserLab_LIBS
    UserLabAPI
    LabRPSApp
)

generate_from_xml(UserLabSimulationPy)
generate_from_xml(UserLabSimulationComparisonPy)

SET(Properties_SRCS

)
SOURCE_GROUP("Properties" FILES ${Properties_SRCS})


SET(Features_SRCS

)
SOURCE_GROUP("Features" FILES ${Features_SRCS})

SET(Datatypes_SRCS
    UserLabSimulation.cpp
    UserLabSimulation.h
    UserLabSimulationComparison.h
    UserLabSimulationComparison.cpp
)
SOURCE_GROUP("Datatypes" FILES ${Datatypes_SRCS})

SET(Python_SRCS
    UserLabSimulationPy.xml
    UserLabSimulationPyImp.cpp
    UserLabSimulationComparisonPyImp.cpp

)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    AppUserLab.cpp
    AppUserLabPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    UserLabUtils.cpp
    UserLabUtils.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

SET(UserLab_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

SET(UserLab_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

add_library(UserLab SHARED ${UserLab_SRCS})
target_link_libraries(UserLab ${UserLab_LIBS})
set_target_properties(UserLab PROPERTIES FOLDER "Workbenches/UserLab")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" UserLab_CPP_SRCS ${UserLab_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(UserLab PreCompiled.h PreCompiled.cpp UserLab_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(UserLab UserLab /Mod/UserLab)
SET_PYTHON_PREFIX_SUFFIX(UserLab)

INSTALL(TARGETS UserLab DESTINATION ${CMAKE_INSTALL_LIBDIR})
