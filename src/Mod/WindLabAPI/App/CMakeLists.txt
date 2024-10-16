add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DFCAppWindLabAPI -DHAVE_ACOSH -DHAVE_ASINH -DHAVE_ATANH)
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

set(WindLabAPI_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
    )
    list(APPEND WindLabAPI_LIBS
         ${Qt5Core_LIBRARIES}
         ${Qt5Xml_LIBRARIES}
    )
else()
    include_directories(
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND WindLabAPI_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

generate_from_xml(WindLabSimuDataPy)
generate_from_xml(WindLabFeaturePy)

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
WindLabSimuDataPy.xml
WindLabSimuDataPyImp.cpp
WindLabFeaturePy.xml
WindLabFeaturePyImp.cpp
)
SOURCE_GROUP("Python" FILES ${Python_SRCS})

SET(WindLabAPI_Interface_SRCS
    IrpsWLCoherence.h
    IrpsWLCorrelation.h
    IrpsWLFrequencyDistribution.h
    IrpsWLLocationDistribution.h
    IrpsWLMean.h
    IrpsWLModulation.h
    IrpsWLPSDdecompositionMethod.h
    IrpsWLRandomness.h
    IrpsWLXSpectrum.h
    IrpsWLYSpectrum.h
    IrpsWLSimuMethod.h
    IrpsWLZSpectrum.h
    IrpsWLMatrixTool.h
    IrpsWLTableTool.h
    IrpsWLUserDefinedRPSObject.h
    IrpsWLCumulativeProbabilityDistribution.h
    IrpsWLGustFactor.h
    IrpsWLKurtosis.h
    IrpsWLPeakFactor.h
    IrpsWLProbabilityDensityFunction.h
    IrpsWLRoughness.h
    IrpsWLShearVelocityOfFlow.h
    IrpsWLSkewness.h
    IrpsWLStandardDeviation.h
    IrpsWLTurbulenceIntensity.h
    IrpsWLTurbulenceScale.h
    IrpsWLVariance.h
    IrpsWLWavePassageEffect.h
)

SOURCE_GROUP("Interface" FILES ${WindLabAPI_Interface_SRCS})

SET(WindModule_SRCS
    AppWindLabAPI.cpp
    AppWindLabAPIPy.cpp
    PreCompiled.cpp
    PreCompiled.h
    RPSWindLabAPI.cpp
    RPSWindLabFramework.cpp
    RPSWindLabpluginAPI.cpp
    WindLabSimuData.cpp
    WindLabFeatureDescription.cpp
    WindLabFeatureDescription.h
    RPSWindLabAPI.h
    RPSWindLabAPIdefines.h
    RPSWindLabFramework.h
    RPSWindLabpluginAPI.h
    WindLabSimuData.h
    RPS.h
    RPS.cpp

)
SOURCE_GROUP("Module" FILES ${WindModule_SRCS})

# The WindLab stuff
SET(WindLab_Features_CPP_SRCS
    WindLabFeature.cpp
    WindLabFeatureCoherence.cpp
    WindLabFeatureCorrelation.cpp
    WindLabFeatureCumulativeProbabilityDistribution.cpp
    WindLabFeatureFrequencyDistribution.cpp
    WindLabFeatureGustFactor.cpp
    WindLabFeatureKurtosis.cpp
    WindLabFeatureLocationDistribution.cpp
    WindLabFeatureMatrixTool.cpp
    WindLabFeatureMeanWind.cpp
    WindLabFeatureModulation.cpp
    WindLabFeaturePeakFactor.cpp
    WindLabFeatureProbabilityDensityFunction.cpp
    WindLabFeaturePSDDecompositionMethod.cpp
    WindLabFeatureRandomness.cpp
    WindLabFeatureRoughness.cpp
    WindLabFeatureShearVelocityOfFlow.cpp
    WindLabFeatureSimulationMethod.cpp
    WindLabFeatureSkewness.cpp
    WindLabFeatureStandardDeviation.cpp
    WindLabFeatureTableTool.cpp
    WindLabFeatureTurbulenceIntensity.cpp
    WindLabFeatureTurbulenceScale.cpp
    WindLabFeatureUserDefinedRPSObject.cpp
    WindLabFeatureVariance.cpp
    WindLabFeatureWavePassageEffect.cpp
    WindLabFeatureXSpectrum.cpp
    WindLabFeatureYSpectrum.cpp
    WindLabFeatureZSpectrum.cpp
)

SET(WindLab_Features_HPP_SRCS
    WindLabFeature.h
    WindLabFeatureCoherence.h
    WindLabFeatureCorrelation.h
    WindLabFeatureCumulativeProbabilityDistribution.h
    WindLabFeatureFrequencyDistribution.h
    WindLabFeatureGustFactor.h
    WindLabFeatureKurtosis.h
    WindLabFeatureLocationDistribution.h
    WindLabFeatureMatrixTool.h
    WindLabFeatureMeanWind.h
    WindLabFeatureModulation.h
    WindLabFeaturePeakFactor.h
    WindLabFeatureProbabilityDensityFunction.h
    WindLabFeaturePSDDecompositionMethod.h
    WindLabFeatureRandomness.h
    WindLabFeatureRoughness.h
    WindLabFeatureShearVelocityOfFlow.h
    WindLabFeatureSimulationMethod.h
    WindLabFeatureSkewness.h
    WindLabFeatureStandardDeviation.h
    WindLabFeatureTableTool.h
    WindLabFeatureTurbulenceIntensity.h
    WindLabFeatureTurbulenceScale.h
    WindLabFeatureUserDefinedRPSObject.h
    WindLabFeatureVariance.h
    WindLabFeatureWavePassageEffect.h
    WindLabFeatureXSpectrum.h
    WindLabFeatureYSpectrum.h
    WindLabFeatureZSpectrum.h
    
)

SET(WindLab_Features_SRCS
    ${WindLab_Features_CPP_SRCS}
    ${WindLab_Features_HPP_SRCS}
)

SOURCE_GROUP("WindLab Features" FILES ${WindLab_Features_SRCS})

SET(WindLabAPI_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${WindLabAPI_Interface_SRCS}
    ${WindLab_Features_SRCS}

    # PythonPlugin.py

)

SET(WindLabAPI_PCH_SRCS
    ${Features_SRCS}
    ${WindModule_SRCS}
    ${Python_SRCS}
    ${Properties_SRCS}
    ${Datatypes_SRCS}
    ${WindLab_Features_SRCS}

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


add_library(WindLabAPI SHARED ${WindLabAPI_SRCS})

if (BUILD_DYNAMIC_LINK_PYTHON)
   target_link_libraries(WindLabAPI ${PYTHON_LIBRARIES})
endif(BUILD_DYNAMIC_LINK_PYTHON)
target_link_libraries(WindLabAPI ${Boost_LIBRARIES})

target_link_libraries(WindLabAPI ${WindLabAPI_LIBS})
set_target_properties(WindLabAPI PROPERTIES FOLDER "Workbenches/WindLabAPI")

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" WindLabAPI_CPP_SRCS ${WindLabAPI_PCH_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(WindLabAPI PreCompiled.h PreCompiled.cpp WindLabAPI_CPP_SRCS)
endif(LABRPS_USE_PCH)

SET_BIN_DIR(WindLabAPI WindLabAPI /Mod/WindLabAPI)
SET_PYTHON_PREFIX_SUFFIX(WindLabAPI)

INSTALL(TARGETS WindLabAPI DESTINATION ${CMAKE_INSTALL_LIBDIR})
