add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppUserLabAPI -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(UserLabAPI_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND UserLabAPI_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND UserLabAPI_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(UserLabSimulationDataPy)
generate_from_xml(UserLabFeaturePy)

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
UserLabSimulationDataPy.xml
UserLabSimulationDataPyImp.cpp
UserLabFeaturePy.xml
UserLabFeaturePyImp.cpp
)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(UserLabAPI_Interface_SRCS
    IrpsULSimulationMethod.h
)

SOURCE_GROUP("Interface" FILES ${UserLabAPI_Interface_SRCS})

SET(WindModule_SRCS
    AppUserLabAPI.cpp
    AppUserLabAPIPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    RPSUserLabAPI.cpp
    RPSUserLabpluginAPI.cpp
    UserLabSimulationData.cpp
    UserLabFeatureDescription.cpp
    UserLabFeatureDescription.h
    RPSUserLabAPI.h
    RPSUserLabAPIdefines.h
    RPSUserLabpluginAPI.h
    UserLabSimulationData.h
    RPS.h
    RPS.cpp

)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The UserLab stuff
SET(UserLab_Features_CPP_SRCS
    UserLabFeature.cpp
    UserLabFeatureSimulationMethod.cpp
)

SET(UserLab_Features_HPP_SRCS
    UserLabFeature.h
    UserLabFeatureSimulationMethod.h    
)

SET(UserLab_Features_SRCS
    ${UserLab_Features_CPP_SRCS}
    ${UserLab_Features_HPP_SRCS}
)

SOURCE_GROUP("UserLab Features" FILES ${UserLab_Features_SRCS})

SET(UserLabAPI_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${UserLabAPI_Interface_SRCS}
    ${UserLab_Features_SRCS}

    # PythonPlugin.py

)

SET(UserLabAPI_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${UserLab_Features_SRCS}

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


add_library(UserLabAPI SHARED ${UserLabAPI_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(UserLabAPI ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(UserLabAPI ${Boost_LIBRARIES})

target_link_libraries(UserLabAPI ${UserLabAPI_LIBS})
set_target_properties(UserLabAPI PROPERTIES FOLDER "Workbenches/UserLabAPI")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" UserLabAPI_CPP_SRCS ${UserLabAPI_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(UserLabAPI PreCompiled.h PreCompiled.cpp UserLabAPI_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(UserLabAPI UserLabAPI /Mod/UserLabAPI)
SET_PYTHON_PREFIX_SUFFIX(UserLabAPI)

INSTALL(TARGETS UserLabAPI DESTINATION ${CMAKE_INSTALL_LIBDIR})
