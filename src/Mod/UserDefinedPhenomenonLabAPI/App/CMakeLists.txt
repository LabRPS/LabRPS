add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppUserDefinedPhenomenonLabAPI -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(UserDefinedPhenomenonLabAPI_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND UserDefinedPhenomenonLabAPI_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND UserDefinedPhenomenonLabAPI_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(UserDefinedPhenomenonLabSimulationDataPy)
generate_from_xml(UserDefinedPhenomenonLabFeaturePy)

SET(Properties_SRCS

)
SOURCE_GROUP("Properties" FILES ${Properties_SRCS})


SET(Features_SRCS

)
SOURCE_GROUP("Features" FILES ${Features_SRCS})

SET(Datatypes_SRCS

)
SOURCE_GROUP("Datatypes" FILES ${Datatypes_SRCS})

SET(Python_SRCS
UserDefinedPhenomenonLabSimulationDataPy.xml
UserDefinedPhenomenonLabSimulationDataPyImp.cpp
UserDefinedPhenomenonLabFeaturePy.xml
UserDefinedPhenomenonLabFeaturePyImp.cpp
)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(UserDefinedPhenomenonLabAPI_Interface_SRCS
    IrpsULSimulationMethod.h
)

SOURCE_GROUP("Interface" FILES ${UserDefinedPhenomenonLabAPI_Interface_SRCS})

SET(WindModule_SRCS
    AppUserDefinedPhenomenonLabAPI.cpp
    AppUserDefinedPhenomenonLabAPIPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    RPSUserDefinedPhenomenonLabAPI.cpp
    RPSUserDefinedPhenomenonLabpluginAPI.cpp
    UserDefinedPhenomenonLabSimulationData.cpp
    UserDefinedPhenomenonLabFeatureDescription.cpp
    UserDefinedPhenomenonLabFeatureDescription.h
    RPSUserDefinedPhenomenonLabAPI.h
    RPSUserDefinedPhenomenonLabAPIdefines.h
    RPSUserDefinedPhenomenonLabpluginAPI.h
    UserDefinedPhenomenonLabSimulationData.h
    RPS.h
    RPS.cpp

)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The UserDefinedPhenomenonLab stuff
SET(UserDefinedPhenomenonLab_Features_CPP_SRCS
    UserDefinedPhenomenonLabFeature.cpp
    UserDefinedPhenomenonLabFeatureSimulationMethod.cpp
)

SET(UserDefinedPhenomenonLab_Features_HPP_SRCS
    UserDefinedPhenomenonLabFeature.h
    UserDefinedPhenomenonLabFeatureSimulationMethod.h    
)

SET(UserDefinedPhenomenonLab_Features_SRCS
    ${UserDefinedPhenomenonLab_Features_CPP_SRCS}
    ${UserDefinedPhenomenonLab_Features_HPP_SRCS}
)

SOURCE_GROUP("UserDefinedPhenomenonLab Features" FILES ${UserDefinedPhenomenonLab_Features_SRCS})

SET(UserDefinedPhenomenonLabAPI_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${UserDefinedPhenomenonLabAPI_Interface_SRCS}
    ${UserDefinedPhenomenonLab_Features_SRCS}

    # PythonPlugin.py

)

SET(UserDefinedPhenomenonLabAPI_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${UserDefinedPhenomenonLab_Features_SRCS}

)

# # boost-python >= 1.67 on some platforms has suffix
# set(BOOST_PY_SUFFIX ${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})

# find_package( Boost COMPONENTS python${BOOST_PY_SUFFIX} )
# if (NOT Boost_PYTHON${BOOST_PY_SUFFIX}_FOUND)
#     # try just the major version
#     find_package( Boost COMPONENTS python${PYTHON_VERSION_MAJOR} )
#     if (NOT Boost_PYTHON${PYTHON_VERSION_MAJOR}_FOUND)
#         # unversioned
#         find_package( Boost COMPONENTS python REQUIRED)
#     endif()
# endif()


add_library(UserDefinedPhenomenonLabAPI SHARED ${UserDefinedPhenomenonLabAPI_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(UserDefinedPhenomenonLabAPI ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(UserDefinedPhenomenonLabAPI ${Boost_LIBRARIES})

target_link_libraries(UserDefinedPhenomenonLabAPI ${UserDefinedPhenomenonLabAPI_LIBS})
set_target_properties(UserDefinedPhenomenonLabAPI PROPERTIES FOLDER "Workbenches/UserDefinedPhenomenonLabAPI")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" UserDefinedPhenomenonLabAPI_CPP_SRCS ${UserDefinedPhenomenonLabAPI_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(UserDefinedPhenomenonLabAPI PreCompiled.h PreCompiled.cpp UserDefinedPhenomenonLabAPI_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(UserDefinedPhenomenonLabAPI UserDefinedPhenomenonLabAPI /Mod/UserDefinedPhenomenonLabAPI)
SET_PYTHON_PREFIX_SUFFIX(UserDefinedPhenomenonLabAPI)

INSTALL(TARGETS UserDefinedPhenomenonLabAPI DESTINATION ${CMAKE_INSTALL_LIBDIR})
