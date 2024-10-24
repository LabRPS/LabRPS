add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppSeaLabAPI -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(SeaLabAPI_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND SeaLabAPI_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND SeaLabAPI_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(SeaLabSimulationDataPy)
generate_from_xml(SeaLabFeaturePy)

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
SeaLabSimulationDataPy.xml
SeaLabSimulationDataPyImp.cpp
SeaLabFeaturePy.xml
SeaLabFeaturePyImp.cpp
)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(SeaLabAPI_Interface_SRCS
    IrpsSeLCoherence.h
    IrpsSeLCorrelation.h
    IrpsSeLFrequencyDistribution.h
    IrpsSeLLocationDistribution.h
    IrpsSeLMeanAcceleration.h
    IrpsSeLModulation.h
    IrpsSeLPSDdecompositionMethod.h
    IrpsSeLRandomness.h
    IrpsSeLSpectrum.h
    IrpsSeLSimulationMethod.h
    IrpsSeLMatrixTool.h
    IrpsSeLTableTool.h
    IrpsSeLUserDefinedRPSObject.h
    IrpsSeLCumulativeProbabilityDistribution.h
    IrpsSeLKurtosis.h
    IrpsSeLPeakFactor.h
    IrpsSeLProbabilityDensityFunction.h
    IrpsSeLShearVelocityOfFlow.h
    IrpsSeLSkewness.h
    IrpsSeLStandardDeviation.h
    IrpsSeLVariance.h
    IrpsSeLWavePassageEffect.h
)

SOURCE_GROUP("Interface" FILES ${SeaLabAPI_Interface_SRCS})

SET(WindModule_SRCS
    AppSeaLabAPI.cpp
    AppSeaLabAPIPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    RPSSeaLabAPI.cpp
    RPSSeaLabFramework.cpp
    RPSSeaLabPluginAPI.cpp
    SeaLabSimulationData.cpp
    SeaLabFeatureDescription.cpp
    SeaLabFeatureDescription.h
    RPSSeaLabAPI.h
    RPSSeaLabAPIdefines.h
    RPSSeaLabFramework.h
    RPSSeaLabPluginAPI.h
    SeaLabSimulationData.h
    RPS.h
    RPS.cpp

)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The SeaLab stuff
SET(SeaLab_Features_CPP_SRCS
    SeaLabFeature.cpp
    SeaLabFeatureCoherence.cpp
    SeaLabFeatureCorrelation.cpp
    SeaLabFeatureCumulativeProbabilityDistribution.cpp
    SeaLabFeatureFrequencyDistribution.cpp
    SeaLabFeatureKurtosis.cpp
    SeaLabFeatureLocationDistribution.cpp
    SeaLabFeatureMatrixTool.cpp
    SeaLabFeatureMeanAcceleration.cpp
    SeaLabFeatureModulation.cpp
    SeaLabFeaturePeakFactor.cpp
    SeaLabFeatureProbabilityDensityFunction.cpp
    SeaLabFeaturePSDDecompositionMethod.cpp
    SeaLabFeatureRandomness.cpp
    SeaLabFeatureShearVelocityOfFlow.cpp
    SeaLabFeatureSimulationMethod.cpp
    SeaLabFeatureSkewness.cpp
    SeaLabFeatureStandardDeviation.cpp
    SeaLabFeatureTableTool.cpp
    SeaLabFeatureUserDefinedRPSObject.cpp
    SeaLabFeatureVariance.cpp
    SeaLabFeatureWavePassageEffect.cpp
    SeaLabFeatureSpectrum.cpp
)

SET(SeaLab_Features_HPP_SRCS
    SeaLabFeature.h
    SeaLabFeatureCoherence.h
    SeaLabFeatureCorrelation.h
    SeaLabFeatureCumulativeProbabilityDistribution.h
    SeaLabFeatureFrequencyDistribution.h
    SeaLabFeatureKurtosis.h
    SeaLabFeatureLocationDistribution.h
    SeaLabFeatureMatrixTool.h
    SeaLabFeatureMeanAcceleration.h
    SeaLabFeatureModulation.h
    SeaLabFeaturePeakFactor.h
    SeaLabFeatureProbabilityDensityFunction.h
    SeaLabFeaturePSDDecompositionMethod.h
    SeaLabFeatureRandomness.h
    SeaLabFeatureShearVelocityOfFlow.h
    SeaLabFeatureSimulationMethod.h
    SeaLabFeatureSkewness.h
    SeaLabFeatureStandardDeviation.h
    SeaLabFeatureTableTool.h
    SeaLabFeatureUserDefinedRPSObject.h
    SeaLabFeatureVariance.h
    SeaLabFeatureWavePassageEffect.h
    SeaLabFeatureSpectrum.h    
)

SET(SeaLab_Features_SRCS
    ${SeaLab_Features_CPP_SRCS}
    ${SeaLab_Features_HPP_SRCS}
)

SOURCE_GROUP("SeaLab Features" FILES ${SeaLab_Features_SRCS})

SET(SeaLabAPI_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${SeaLabAPI_Interface_SRCS}
    ${SeaLab_Features_SRCS}

    # PythonPlugin.py

)

SET(SeaLabAPI_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${SeaLab_Features_SRCS}

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


add_library(SeaLabAPI SHARED ${SeaLabAPI_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(SeaLabAPI ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(SeaLabAPI ${Boost_LIBRARIES})

target_link_libraries(SeaLabAPI ${SeaLabAPI_LIBS})
set_target_properties(SeaLabAPI PROPERTIES FOLDER "Workbenches/SeaLabAPI")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" SeaLabAPI_CPP_SRCS ${SeaLabAPI_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeaLabAPI PreCompiled.h PreCompiled.cpp SeaLabAPI_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(SeaLabAPI SeaLabAPI /Mod/SeaLabAPI)
SET_PYTHON_PREFIX_SUFFIX(SeaLabAPI)

INSTALL(TARGETS SeaLabAPI DESTINATION ${CMAKE_INSTALL_LIBDIR})
