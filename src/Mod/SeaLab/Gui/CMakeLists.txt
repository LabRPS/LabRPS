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

generate_from_xml(ViewProviderSeaLabFeatureCoherencePy)
generate_from_xml(ViewProviderSeaLabFeatureCorrelationPy)
generate_from_xml(ViewProviderSeaLabFeatureCumulativeProbabilityDistributionPy)
generate_from_xml(ViewProviderSeaLabFeatureFrequencyDistributionPy)
generate_from_xml(ViewProviderSeaLabFeatureKurtosisPy)
generate_from_xml(ViewProviderSeaLabFeatureLocationDistributionPy)
generate_from_xml(ViewProviderSeaLabFeatureMeanAccelerationPy)
generate_from_xml(ViewProviderSeaLabFeatureModulationPy)
generate_from_xml(ViewProviderSeaLabFeaturePeakFactorPy)
generate_from_xml(ViewProviderSeaLabFeatureProbabilityDensityFunctionPy)
generate_from_xml(ViewProviderSeaLabFeaturePSDDecompositionMethodPy)
generate_from_xml(ViewProviderSeaLabFeatureRandomnessPy)
generate_from_xml(ViewProviderSeaLabFeatureShearVelocityOfFlowPy)
generate_from_xml(ViewProviderSeaLabFeatureSimulationMethodPy)
generate_from_xml(ViewProviderSeaLabFeatureSkewnessPy)
generate_from_xml(ViewProviderSeaLabFeatureStandardDeviationPy)
generate_from_xml(ViewProviderSeaLabFeatureUserDefinedRPSObjectPy)
generate_from_xml(ViewProviderSeaLabFeatureVariancePy)
generate_from_xml(ViewProviderSeaLabFeatureWavePassageEffectPy)
generate_from_xml(ViewProviderSeaLabFeatureSpectrumPy)
generate_from_xml(ViewProviderSeaLabFeatureMatrixToolPy)
generate_from_xml(ViewProviderSeaLabFeatureTableToolPy)
generate_from_xml(ViewProviderSeaLabSimulationPy)
generate_from_xml(ViewProviderSeaLabSimulationComparisonPy)


# The XML files
set(SeaLabGui_XML_SRCS
    ViewProviderSeaLabFeatureCoherencePy.xml
    ViewProviderSeaLabFeatureCorrelationPy.xml
    ViewProviderSeaLabFeatureCumulativeProbabilityDistributionPy.xml
    ViewProviderSeaLabFeatureFrequencyDistributionPy.xml
    ViewProviderSeaLabFeatureKurtosisPy.xml
    ViewProviderSeaLabFeatureLocationDistributionPy.xml
    ViewProviderSeaLabFeatureMeanAccelerationPy.xml
    ViewProviderSeaLabFeatureModulationPy.xml
    ViewProviderSeaLabFeaturePeakFactorPy.xml
    ViewProviderSeaLabFeatureProbabilityDensityFunctionPy.xml
    ViewProviderSeaLabFeaturePSDDecompositionMethodPy.xml
    ViewProviderSeaLabFeatureRandomnessPy.xml
    ViewProviderSeaLabFeatureShearVelocityOfFlowPy.xml
    ViewProviderSeaLabFeatureSimulationMethodPy.xml
    ViewProviderSeaLabFeatureSkewnessPy.xml
    ViewProviderSeaLabFeatureStandardDeviationPy.xml
    ViewProviderSeaLabFeatureUserDefinedRPSObjectPy.xml
    ViewProviderSeaLabFeatureVariancePy.xml
    ViewProviderSeaLabFeatureWavePassageEffectPy.xml
    ViewProviderSeaLabFeatureSpectrumPy.xml
    ViewProviderSeaLabFeatureMatrixToolPy.xml
    ViewProviderSeaLabFeatureTableToolPy.xml
    ViewProviderSeaLabSimulationPy.xml
    ViewProviderSeaLabSimulationComparisonPy.xml
)

set(SeaLabGui_LIBS
    SeaLabAPI
    SeaLab
    LabRPSGui
    LabRPSApp
    Part
)

if(BUILD_QT5)
    qt5_add_resources(SeaLabGui_SRCS Resources/SeaLab.qrc)
else()
    qt4_add_resources(SeaLabGui_SRCS Resources/SeaLab.qrc)
endif()

set(SeaLabGui_UIC_SRCS
DlgNewSimulation.ui
DlgSeaLabFeatures.ui
DlgSeaLabFeaturesCreation.ui
DlgSimulationComparison.ui
DlgSettingsSeaLabLimit.ui
DlgSettingsSeaLabGeneral.ui

)


SET(SeaLabGui_DLG_SRCS
    ${SeaLabGui_UIC_HDRS}
    DlgSettingsSeaLabLimit.ui
    DlgSettingsSeaLabLimitImp.cpp
    DlgSettingsSeaLabLimitImp.h
    DlgSettingsSeaLabGeneral.ui
    DlgSettingsSeaLabGeneralImp.cpp
    DlgSettingsSeaLabGeneralImp.h

)

SOURCE_GROUP("Setting-Dialogs" FILES ${SeaLabGui_DLG_SRCS})


if(BUILD_QT5)
    qt5_wrap_ui(SeaLabGui_UIC_HDRS ${SeaLabGui_UIC_SRCS})
else()
    qt4_wrap_ui(SeaLabGui_UIC_HDRS ${SeaLabGui_UIC_SRCS})
endif()

SET(ViewProvider_CPP_SRCS
ViewProviderSeaLabSimulation.cpp
DlgSeaLabFeaturesCreation.cpp
DlgSimulationComparison.cpp
ViewProviderSeaLabFeatureCoherence.cpp
ViewProviderSeaLabFeatureCorrelation.cpp
ViewProviderSeaLabFeatureCumulativeProbabilityDistribution.cpp
ViewProviderSeaLabFeatureFrequencyDistribution.cpp
ViewProviderSeaLabFeatureKurtosis.cpp
ViewProviderSeaLabFeatureLocationDistribution.cpp
ViewProviderSeaLabFeatureMeanAcceleration.cpp
ViewProviderSeaLabFeatureModulation.cpp
ViewProviderSeaLabFeaturePeakFactor.cpp
ViewProviderSeaLabFeatureProbabilityDensityFunction.cpp
ViewProviderSeaLabFeaturePSDDecompositionMethod.cpp
ViewProviderSeaLabFeatureRandomness.cpp
ViewProviderSeaLabFeatureShearVelocityOfFlow.cpp
ViewProviderSeaLabFeatureSimulationMethod.cpp
ViewProviderSeaLabFeatureSkewness.cpp
ViewProviderSeaLabFeatureStandardDeviation.cpp
ViewProviderSeaLabFeatureUserDefinedRPSObject.cpp
ViewProviderSeaLabFeatureVariance.cpp
ViewProviderSeaLabFeatureWavePassageEffect.cpp
ViewProviderSeaLabFeatureSpectrum.cpp
ViewProviderSeaLabFeatureMatrixTool.cpp
ViewProviderSeaLabFeatureTableTool.cpp
ViewProviderSeaLabSimulation.cpp
ViewProviderSeaLabSimulationComparison.cpp

ViewProviderSeaLabFeatureCoherencePyImp.cpp
ViewProviderSeaLabFeatureCorrelationPyImp.cpp
ViewProviderSeaLabFeatureCumulativeProbabilityDistributionPyImp.cpp
ViewProviderSeaLabFeatureFrequencyDistributionPyImp.cpp
ViewProviderSeaLabFeatureKurtosisPyImp.cpp
ViewProviderSeaLabFeatureLocationDistributionPyImp.cpp
ViewProviderSeaLabFeatureMeanAccelerationPyImp.cpp
ViewProviderSeaLabFeatureModulationPyImp.cpp
ViewProviderSeaLabFeaturePeakFactorPyImp.cpp
ViewProviderSeaLabFeatureProbabilityDensityFunctionPyImp.cpp
ViewProviderSeaLabFeaturePSDDecompositionMethodPyImp.cpp
ViewProviderSeaLabFeatureRandomnessPyImp.cpp
ViewProviderSeaLabFeatureShearVelocityOfFlowPyImp.cpp
ViewProviderSeaLabFeatureSimulationMethodPyImp.cpp
ViewProviderSeaLabFeatureSkewnessPyImp.cpp
ViewProviderSeaLabFeatureStandardDeviationPyImp.cpp
ViewProviderSeaLabFeatureUserDefinedRPSObjectPyImp.cpp
ViewProviderSeaLabFeatureVariancePyImp.cpp
ViewProviderSeaLabFeatureWavePassageEffectPyImp.cpp
ViewProviderSeaLabFeatureSpectrumPyImp.cpp
ViewProviderSeaLabFeatureMatrixToolPyImp.cpp
ViewProviderSeaLabFeatureTableToolPyImp.cpp
ViewProviderSeaLabSimulationPyImp.cpp
ViewProviderSeaLabSimulationComparisonPyImp.cpp

)
SET(ViewProvider_HPP_SRCS
ViewProviderSeaLabSimulation.h
DlgSeaLabFeaturesCreation.h
DlgSimulationComparison.h
ViewProviderSeaLabFeatureCoherence.h
ViewProviderSeaLabFeatureCorrelation.h
ViewProviderSeaLabFeatureCumulativeProbabilityDistribution.h
ViewProviderSeaLabFeatureFrequencyDistribution.h
ViewProviderSeaLabFeatureKurtosis.h
ViewProviderSeaLabFeatureLocationDistribution.h
ViewProviderSeaLabFeatureMeanAcceleration.h
ViewProviderSeaLabFeatureModulation.h
ViewProviderSeaLabFeaturePeakFactor.h
ViewProviderSeaLabFeatureProbabilityDensityFunction.h
ViewProviderSeaLabFeaturePSDDecompositionMethod.h
ViewProviderSeaLabFeatureRandomness.h
ViewProviderSeaLabFeatureShearVelocityOfFlow.h
ViewProviderSeaLabFeatureSimulationMethod.h
ViewProviderSeaLabFeatureSkewness.h
ViewProviderSeaLabFeatureStandardDeviation.h
ViewProviderSeaLabFeatureUserDefinedRPSObject.h
ViewProviderSeaLabFeatureVariance.h
ViewProviderSeaLabFeatureWavePassageEffect.h
ViewProviderSeaLabFeatureSpectrum.h
ViewProviderSeaLabFeatureMatrixTool.h
ViewProviderSeaLabFeatureTableTool.h
ViewProviderSeaLabSimulationComparison.h
)

SET(ViewProvider_SRCS
    ${ViewProvider_CPP_SRCS}
    ${ViewProvider_HPP_SRCS}
    ${SeaLabGui_XML_SRCS}

)
SOURCE_GROUP("ViewProvider" FILES ${ViewProvider_SRCS})

SET(SeaLabGui_SRCS
    ${SeaLabGui_SRCS}
    ${SeaLabGui_UIC_HDRS}
    ${ViewProvider_SRCS}
    ${SeaLabGui_DLG_SRCS}
    AppSeaLabGui.cpp
    Command.cpp
    Resources/SeaLab.qrc
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
    DlgNewSimulation.cpp
    DlgNewSimulation.h
    RPSSeaLabPyTool.cpp
    RPSSeaLabPyTool.h
    SeaLabSimulationObserver.h
    SeaLabSimulationObserver.cpp
    SeaLabSimulationWorker.h
    SeaLabSimulationWorker.cpp
    SeaLabAllFeaturesComputation.h
    SeaLabAllFeaturesComputation.cpp
    SeaLabComparisonStarter.h
    SeaLabComparisonStarter.cpp

)

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" PCH_SRCS ${SeaLabGui_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeaLabGui PreCompiled.h PreCompiled.cpp PCH_SRCS)
endif(LABRPS_USE_PCH)


SET(SeaLabGuiIcon_SVG
    Resources/icons/SeaLabWorkbench.svg
)

add_library(SeaLabGui SHARED ${SeaLabGui_SRCS} ${SeaLabGuiIcon_SVG})
target_link_libraries(SeaLabGui ${SeaLabGui_LIBS})
set_target_properties(SeaLabGui PROPERTIES FOLDER "Workbenches/SeaLab")


SET_BIN_DIR(SeaLabGui SeaLabGui /Mod/SeaLab)
SET_PYTHON_PREFIX_SUFFIX(SeaLabGui)

rps_copy_sources(SeaLabGui "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/Mod/SeaLab" ${SeaLabGuiIcon_SVG})

INSTALL(TARGETS SeaLabGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(FILES ${SeaLabGuiIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Mod/SeaLab/Resources/icons")
