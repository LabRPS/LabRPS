# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppWindLab -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(WindLab_LIBS
    WindLabAPI
    LabRPSApp
)

generate_from_xml(WindLabSimulationPy)
generate_from_xml(WindLabSimulationComparisonPy)

SET(Properties_SRCS

)
SOURCE_GROUP("Properties" FILES ${Properties_SRCS})


SET(Features_SRCS

)
SOURCE_GROUP("Features" FILES ${Features_SRCS})

SET(Datatypes_SRCS
    WindLabSimulation.cpp
    WindLabSimulation.h
    WindLabSimulationComparison.h
    WindLabSimulationComparison.cpp
)
SOURCE_GROUP("Datatypes" FILES ${Datatypes_SRCS})

SET(Python_SRCS
    WindLabSimulationPy.xml
    WindLabSimulationPyImp.cpp
    WindLabSimulationComparisonPyImp.cpp

)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindModule_SRCS
    AppWindLab.cpp
    AppWindLabPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    WindLabUtils.cpp
    WindLabUtils.h
)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

SET(WindLab_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

SET(WindLab_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
)

add_library(WindLab SHARED ${WindLab_SRCS})
target_link_libraries(WindLab ${WindLab_LIBS})
set_target_properties(WindLab PROPERTIES FOLDER "Workbenches/WindLab")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" WindLab_CPP_SRCS ${WindLab_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(WindLab PreCompiled.h PreCompiled.cpp WindLab_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(WindLab WindLab /Mod/WindLab)
SET_PYTHON_PREFIX_SUFFIX(WindLab)

INSTALL(TARGETS WindLab DESTINATION ${CMAKE_INSTALL_LIBDIR})
