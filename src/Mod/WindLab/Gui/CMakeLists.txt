# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

add_compile_definitions(RPS_BUILDING_CORE)

if(MSVC)
    add_definitions(-DHAVE_ACOSH -DHAVE_ATANH -DHAVE_ASINH)
else(MSVC)
    add_definitions(-DHAVE_LIMITS_H -DHAVE_CONFIG_H)
endif(MSVC)

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${XercesC_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

generate_from_xml(ViewProviderWindLabFeatureCoherencePy)
generate_from_xml(ViewProviderWindLabFeatureCorrelationPy)
generate_from_xml(ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy)
generate_from_xml(ViewProviderWindLabFeatureFrequencyDistributionPy)
generate_from_xml(ViewProviderWindLabFeatureGustFactorPy)
generate_from_xml(ViewProviderWindLabFeatureKurtosisPy)
generate_from_xml(ViewProviderWindLabFeatureLocationDistributionPy)
generate_from_xml(ViewProviderWindLabFeatureMeanWindPy)
generate_from_xml(ViewProviderWindLabFeatureModulationPy)
generate_from_xml(ViewProviderWindLabFeaturePeakFactorPy)
generate_from_xml(ViewProviderWindLabFeatureProbabilityDensityFunctionPy)
generate_from_xml(ViewProviderWindLabFeaturePSDDecompositionMethodPy)
generate_from_xml(ViewProviderWindLabFeatureRandomnessPy)
generate_from_xml(ViewProviderWindLabFeatureRoughnessPy)
generate_from_xml(ViewProviderWindLabFeatureShearVelocityOfFlowPy)
generate_from_xml(ViewProviderWindLabFeatureSimulationMethodPy)
generate_from_xml(ViewProviderWindLabFeatureSkewnessPy)
generate_from_xml(ViewProviderWindLabFeatureStandardDeviationPy)
generate_from_xml(ViewProviderWindLabFeatureTurbulenceIntensityPy)
generate_from_xml(ViewProviderWindLabFeatureTurbulenceScalePy)
generate_from_xml(ViewProviderWindLabFeatureUserDefinedRPSObjectPy)
generate_from_xml(ViewProviderWindLabFeatureVariancePy)
generate_from_xml(ViewProviderWindLabFeatureWavePassageEffectPy)
generate_from_xml(ViewProviderWindLabFeatureXSpectrumPy)
generate_from_xml(ViewProviderWindLabFeatureYSpectrumPy)
generate_from_xml(ViewProviderWindLabFeatureZSpectrumPy)
generate_from_xml(ViewProviderWindLabFeatureMatrixToolPy)
generate_from_xml(ViewProviderWindLabFeatureTableToolPy)
generate_from_xml(ViewProviderWindLabSimulationPy)
generate_from_xml(ViewProviderWindLabSimulationComparisonPy)


# The XML files
set(WindLabGui_XML_SRCS
    ViewProviderWindLabFeatureCoherencePy.xml
    ViewProviderWindLabFeatureCorrelationPy.xml
    ViewProviderWindLabFeatureCumulativeProbabilityDistributionPy.xml
    ViewProviderWindLabFeatureFrequencyDistributionPy.xml
    ViewProviderWindLabFeatureGustFactorPy.xml
    ViewProviderWindLabFeatureKurtosisPy.xml
    ViewProviderWindLabFeatureLocationDistributionPy.xml
    ViewProviderWindLabFeatureMeanWindPy.xml
    ViewProviderWindLabFeatureModulationPy.xml
    ViewProviderWindLabFeaturePeakFactorPy.xml
    ViewProviderWindLabFeatureProbabilityDensityFunctionPy.xml
    ViewProviderWindLabFeaturePSDDecompositionMethodPy.xml
    ViewProviderWindLabFeatureRandomnessPy.xml
    ViewProviderWindLabFeatureRoughnessPy.xml
    ViewProviderWindLabFeatureShearVelocityOfFlowPy.xml
    ViewProviderWindLabFeatureSimulationMethodPy.xml
    ViewProviderWindLabFeatureSkewnessPy.xml
    ViewProviderWindLabFeatureStandardDeviationPy.xml
    ViewProviderWindLabFeatureTurbulenceIntensityPy.xml
    ViewProviderWindLabFeatureTurbulenceScalePy.xml
    ViewProviderWindLabFeatureUserDefinedRPSObjectPy.xml
    ViewProviderWindLabFeatureVariancePy.xml
    ViewProviderWindLabFeatureWavePassageEffectPy.xml
    ViewProviderWindLabFeatureXSpectrumPy.xml
    ViewProviderWindLabFeatureYSpectrumPy.xml
    ViewProviderWindLabFeatureZSpectrumPy.xml
    ViewProviderWindLabFeatureMatrixToolPy.xml
    ViewProviderWindLabFeatureTableToolPy.xml
    ViewProviderWindLabSimulationPy.xml
    ViewProviderWindLabSimulationComparisonPy.xml
)

set(WindLabGui_LIBS
    WindLabAPI
    QtPropertyBrowser
    WindLab
    LabRPSGui
    Part
)

if(BUILD_QT5)
    qt5_add_resources(WindLabGui_SRCS Resources/WindLab.qrc)
else()
    qt4_add_resources(WindLabGui_SRCS Resources/WindLab.qrc)
endif()

set(WindLabGui_UIC_SRCS
DlgNewSimulation.ui
DlgWindLabFeatures.ui
DlgWindLabFeaturesCreation.ui
DlgSimulationComparison.ui
DlgSettingsWindLabLimit.ui
DlgSettingsWindLabGeneral.ui

)


SET(WindLabGui_DLG_SRCS
    ${WindLabGui_UIC_HDRS}
    DlgSettingsWindLabLimit.ui
    DlgSettingsWindLabLimitImp.cpp
    DlgSettingsWindLabLimitImp.h
    DlgSettingsWindLabGeneral.ui
    DlgSettingsWindLabGeneralImp.cpp
    DlgSettingsWindLabGeneralImp.h

)

SOURCE_GROUP("Setting-Dialogs" FILES ${WindLabGui_DLG_SRCS})


if(BUILD_QT5)
    qt5_wrap_ui(WindLabGui_UIC_HDRS ${WindLabGui_UIC_SRCS})
else()
    qt4_wrap_ui(WindLabGui_UIC_HDRS ${WindLabGui_UIC_SRCS})
endif()

SET(ViewProvider_CPP_SRCS
ViewProviderWindLabSimulation.cpp
DlgWindLabFeaturesCreation.cpp
DlgSimulationComparison.cpp
ViewProviderWindLabFeatureCoherence.cpp
ViewProviderWindLabFeatureCorrelation.cpp
ViewProviderWindLabFeatureCumulativeProbabilityDistribution.cpp
ViewProviderWindLabFeatureFrequencyDistribution.cpp
ViewProviderWindLabFeatureGustFactor.cpp
ViewProviderWindLabFeatureKurtosis.cpp
ViewProviderWindLabFeatureLocationDistribution.cpp
ViewProviderWindLabFeatureMeanWind.cpp
ViewProviderWindLabFeatureModulation.cpp
ViewProviderWindLabFeaturePeakFactor.cpp
ViewProviderWindLabFeatureProbabilityDensityFunction.cpp
ViewProviderWindLabFeaturePSDDecompositionMethod.cpp
ViewProviderWindLabFeatureRandomness.cpp
ViewProviderWindLabFeatureRoughness.cpp
ViewProviderWindLabFeatureShearVelocityOfFlow.cpp
ViewProviderWindLabFeatureSimulationMethod.cpp
ViewProviderWindLabFeatureSkewness.cpp
ViewProviderWindLabFeatureStandardDeviation.cpp
ViewProviderWindLabFeatureTurbulenceIntensity.cpp
ViewProviderWindLabFeatureTurbulenceScale.cpp
ViewProviderWindLabFeatureUserDefinedRPSObject.cpp
ViewProviderWindLabFeatureVariance.cpp
ViewProviderWindLabFeatureWavePassageEffect.cpp
ViewProviderWindLabFeatureXSpectrum.cpp
ViewProviderWindLabFeatureYSpectrum.cpp
ViewProviderWindLabFeatureZSpectrum.cpp
ViewProviderWindLabFeatureMatrixTool.cpp
ViewProviderWindLabFeatureTableTool.cpp
ViewProviderWindLabSimulation.cpp
ViewProviderWindLabSimulationComparison.cpp

ViewProviderWindLabFeatureCoherencePyImp.cpp
ViewProviderWindLabFeatureCorrelationPyImp.cpp
ViewProviderWindLabFeatureCumulativeProbabilityDistributionPyImp.cpp
ViewProviderWindLabFeatureFrequencyDistributionPyImp.cpp
ViewProviderWindLabFeatureGustFactorPyImp.cpp
ViewProviderWindLabFeatureKurtosisPyImp.cpp
ViewProviderWindLabFeatureLocationDistributionPyImp.cpp
ViewProviderWindLabFeatureMeanWindPyImp.cpp
ViewProviderWindLabFeatureModulationPyImp.cpp
ViewProviderWindLabFeaturePeakFactorPyImp.cpp
ViewProviderWindLabFeatureProbabilityDensityFunctionPyImp.cpp
ViewProviderWindLabFeaturePSDDecompositionMethodPyImp.cpp
ViewProviderWindLabFeatureRandomnessPyImp.cpp
ViewProviderWindLabFeatureRoughnessPyImp.cpp
ViewProviderWindLabFeatureShearVelocityOfFlowPyImp.cpp
ViewProviderWindLabFeatureSimulationMethodPyImp.cpp
ViewProviderWindLabFeatureSkewnessPyImp.cpp
ViewProviderWindLabFeatureStandardDeviationPyImp.cpp
ViewProviderWindLabFeatureTurbulenceIntensityPyImp.cpp
ViewProviderWindLabFeatureTurbulenceScalePyImp.cpp
ViewProviderWindLabFeatureUserDefinedRPSObjectPyImp.cpp
ViewProviderWindLabFeatureVariancePyImp.cpp
ViewProviderWindLabFeatureWavePassageEffectPyImp.cpp
ViewProviderWindLabFeatureXSpectrumPyImp.cpp
ViewProviderWindLabFeatureYSpectrumPyImp.cpp
ViewProviderWindLabFeatureZSpectrumPyImp.cpp
ViewProviderWindLabFeatureMatrixToolPyImp.cpp
ViewProviderWindLabFeatureTableToolPyImp.cpp
ViewProviderWindLabSimulationPyImp.cpp
ViewProviderWindLabSimulationComparisonPyImp.cpp

)
SET(ViewProvider_HPP_SRCS
ViewProviderWindLabSimulation.h
DlgWindLabFeaturesCreation.h
DlgSimulationComparison.h
ViewProviderWindLabFeatureCoherence.h
ViewProviderWindLabFeatureCorrelation.h
ViewProviderWindLabFeatureCumulativeProbabilityDistribution.h
ViewProviderWindLabFeatureFrequencyDistribution.h
ViewProviderWindLabFeatureGustFactor.h
ViewProviderWindLabFeatureKurtosis.h
ViewProviderWindLabFeatureLocationDistribution.h
ViewProviderWindLabFeatureMeanWind.h
ViewProviderWindLabFeatureModulation.h
ViewProviderWindLabFeaturePeakFactor.h
ViewProviderWindLabFeatureProbabilityDensityFunction.h
ViewProviderWindLabFeaturePSDDecompositionMethod.h
ViewProviderWindLabFeatureRandomness.h
ViewProviderWindLabFeatureRoughness.h
ViewProviderWindLabFeatureShearVelocityOfFlow.h
ViewProviderWindLabFeatureSimulationMethod.h
ViewProviderWindLabFeatureSkewness.h
ViewProviderWindLabFeatureStandardDeviation.h
ViewProviderWindLabFeatureTurbulenceIntensity.h
ViewProviderWindLabFeatureTurbulenceScale.h
ViewProviderWindLabFeatureUserDefinedRPSObject.h
ViewProviderWindLabFeatureVariance.h
ViewProviderWindLabFeatureWavePassageEffect.h
ViewProviderWindLabFeatureXSpectrum.h
ViewProviderWindLabFeatureYSpectrum.h
ViewProviderWindLabFeatureZSpectrum.h
ViewProviderWindLabFeatureMatrixTool.h
ViewProviderWindLabFeatureTableTool.h
ViewProviderWindLabSimulationComparison.h
)

SET(ViewProvider_SRCS
    ${ViewProvider_CPP_SRCS}
    ${ViewProvider_HPP_SRCS}
    ${WindLabGui_XML_SRCS}

)
SOURCE_GROUP("ViewProvider" FILES ${ViewProvider_SRCS})

SET(WindLabGui_SRCS
    ${WindLabGui_SRCS}
    ${WindLabGui_UIC_HDRS}
    ${ViewProvider_SRCS}
    ${WindLabGui_DLG_SRCS}
    AppWindLabGui.cpp
    Command.cpp
    Resources/WindLab.qrc
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
    DlgNewSimulation.cpp
    DlgNewSimulation.h
    RPSWindLabPyTool.cpp
    RPSWindLabPyTool.h
    WindLabSimulationObserver.h
    WindLabSimulationObserver.cpp
    WindLabSimulationWorker.h
    WindLabSimulationWorker.cpp
    WindLabAllFeaturesComputation.h
    WindLabAllFeaturesComputation.cpp
    WindLabComparisonStarter.h
    WindLabComparisonStarter.cpp

)

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" PCH_SRCS ${WindLabGui_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(WindLabGui PreCompiled.h PreCompiled.cpp PCH_SRCS)
endif(LABRPS_USE_PCH)


SET(WindLabGuiIcon_SVG
    Resources/icons/WindLabWorkbench.svg
)

add_library(WindLabGui SHARED ${WindLabGui_SRCS} ${WindLabGuiIcon_SVG})
target_link_libraries(WindLabGui ${WindLabGui_LIBS})
set_target_properties(WindLabGui PROPERTIES FOLDER "Workbenches/WindLab")


SET_BIN_DIR(WindLabGui WindLabGui /Mod/WindLab)
SET_PYTHON_PREFIX_SUFFIX(WindLabGui)

rps_copy_sources(WindLabGui "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/Mod/WindLab" ${WindLabGuiIcon_SVG})

INSTALL(TARGETS WindLabGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(FILES ${WindLabGuiIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Mod/WindLab/Resources/icons")
