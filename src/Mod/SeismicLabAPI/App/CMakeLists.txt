add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppSeismicLabAPI -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(SeismicLabAPI_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND SeismicLabAPI_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND SeismicLabAPI_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(SeismicLabSimulationDataPy)
generate_from_xml(SeismicLabFeaturePy)

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
SeismicLabSimulationDataPy.xml
SeismicLabSimulationDataPyImp.cpp
SeismicLabFeaturePy.xml
SeismicLabFeaturePyImp.cpp
)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(SeismicLabAPI_Interface_SRCS
    IrpsSLCoherence.h
    IrpsSLCorrelation.h
    IrpsSLFrequencyDistribution.h
    IrpsSLLocationDistribution.h
    IrpsSLMeanAcceleration.h
    IrpsSLModulation.h
    IrpsSLPSDdecompositionMethod.h
    IrpsSLRandomness.h
    IrpsSLSpectrum.h
    IrpsSLSimulationMethod.h
    IrpsSLMatrixTool.h
    IrpsSLTableTool.h
    IrpsSLUserDefinedRPSObject.h
    IrpsSLCumulativeProbabilityDistribution.h
    IrpsSLKurtosis.h
    IrpsSLPeakFactor.h
    IrpsSLProbabilityDensityFunction.h
    IrpsSLShearVelocityOfFlow.h
    IrpsSLSkewness.h
    IrpsSLStandardDeviation.h
    IrpsSLVariance.h
    IrpsSLWavePassageEffect.h
)

SOURCE_GROUP("Interface" FILES ${SeismicLabAPI_Interface_SRCS})

SET(WindModule_SRCS
    AppSeismicLabAPI.cpp
    AppSeismicLabAPIPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    RPSSeismicLabAPI.cpp
    RPSSeismicLabFramework.cpp
    RPSSeismicLabPluginAPI.cpp
    SeismicLabSimulationData.cpp
    SeismicLabFeatureDescription.cpp
    SeismicLabFeatureDescription.h
    RPSSeismicLabAPI.h
    RPSSeismicLabAPIdefines.h
    RPSSeismicLabFramework.h
    RPSSeismicLabPluginAPI.h
    SeismicLabSimulationData.h
    RPS.h
    RPS.cpp

)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The SeismicLab stuff
SET(SeismicLab_Features_CPP_SRCS
    SeismicLabFeature.cpp
    SeismicLabFeatureCoherence.cpp
    SeismicLabFeatureCorrelation.cpp
    SeismicLabFeatureCumulativeProbabilityDistribution.cpp
    SeismicLabFeatureFrequencyDistribution.cpp
    SeismicLabFeatureKurtosis.cpp
    SeismicLabFeatureLocationDistribution.cpp
    SeismicLabFeatureMatrixTool.cpp
    SeismicLabFeatureMeanAcceleration.cpp
    SeismicLabFeatureModulation.cpp
    SeismicLabFeaturePeakFactor.cpp
    SeismicLabFeatureProbabilityDensityFunction.cpp
    SeismicLabFeaturePSDDecompositionMethod.cpp
    SeismicLabFeatureRandomness.cpp
    SeismicLabFeatureShearVelocityOfFlow.cpp
    SeismicLabFeatureSimulationMethod.cpp
    SeismicLabFeatureSkewness.cpp
    SeismicLabFeatureStandardDeviation.cpp
    SeismicLabFeatureTableTool.cpp
    SeismicLabFeatureUserDefinedRPSObject.cpp
    SeismicLabFeatureVariance.cpp
    SeismicLabFeatureWavePassageEffect.cpp
    SeismicLabFeatureSpectrum.cpp
)

SET(SeismicLab_Features_HPP_SRCS
    SeismicLabFeature.h
    SeismicLabFeatureCoherence.h
    SeismicLabFeatureCorrelation.h
    SeismicLabFeatureCumulativeProbabilityDistribution.h
    SeismicLabFeatureFrequencyDistribution.h
    SeismicLabFeatureKurtosis.h
    SeismicLabFeatureLocationDistribution.h
    SeismicLabFeatureMatrixTool.h
    SeismicLabFeatureMeanAcceleration.h
    SeismicLabFeatureModulation.h
    SeismicLabFeaturePeakFactor.h
    SeismicLabFeatureProbabilityDensityFunction.h
    SeismicLabFeaturePSDDecompositionMethod.h
    SeismicLabFeatureRandomness.h
    SeismicLabFeatureShearVelocityOfFlow.h
    SeismicLabFeatureSimulationMethod.h
    SeismicLabFeatureSkewness.h
    SeismicLabFeatureStandardDeviation.h
    SeismicLabFeatureTableTool.h
    SeismicLabFeatureUserDefinedRPSObject.h
    SeismicLabFeatureVariance.h
    SeismicLabFeatureWavePassageEffect.h
    SeismicLabFeatureSpectrum.h    
)

SET(SeismicLab_Features_SRCS
    ${SeismicLab_Features_CPP_SRCS}
    ${SeismicLab_Features_HPP_SRCS}
)

SOURCE_GROUP("SeismicLab Features" FILES ${SeismicLab_Features_SRCS})

SET(SeismicLabAPI_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${SeismicLabAPI_Interface_SRCS}
    ${SeismicLab_Features_SRCS}

    # PythonPlugin.py

)

SET(SeismicLabAPI_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${SeismicLab_Features_SRCS}

)

# boost-python >= 1.67 on some platforms has suffix
set(BOOST_PY_SUFFIX ${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})

find_package( Boost COMPONENTS python${BOOST_PY_SUFFIX} )
if (NOT Boost_PYTHON${BOOST_PY_SUFFIX}_FOUND)
    # try just the major version
    find_package( Boost COMPONENTS python${PYTHON_VERSION_MAJOR} )
    if (NOT Boost_PYTHON${PYTHON_VERSION_MAJOR}_FOUND)
        # unversioned
        find_package( Boost COMPONENTS python REQUIRED)
    endif()
endif()


add_library(SeismicLabAPI SHARED ${SeismicLabAPI_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(SeismicLabAPI ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(SeismicLabAPI ${Boost_LIBRARIES})

target_link_libraries(SeismicLabAPI ${SeismicLabAPI_LIBS})
set_target_properties(SeismicLabAPI PROPERTIES FOLDER "Workbenches/SeismicLabAPI")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" SeismicLabAPI_CPP_SRCS ${SeismicLabAPI_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeismicLabAPI PreCompiled.h PreCompiled.cpp SeismicLabAPI_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(SeismicLabAPI SeismicLabAPI /Mod/SeismicLabAPI)
SET_PYTHON_PREFIX_SUFFIX(SeismicLabAPI)

INSTALL(TARGETS SeismicLabAPI DESTINATION ${CMAKE_INSTALL_LIBDIR})
