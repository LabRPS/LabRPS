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

generate_from_xml(ViewProviderSeismicLabFeatureCoherencePy)
generate_from_xml(ViewProviderSeismicLabFeatureCorrelationPy)
generate_from_xml(ViewProviderSeismicLabFeatureCumulativeProbabilityDistributionPy)
generate_from_xml(ViewProviderSeismicLabFeatureFrequencyDistributionPy)
generate_from_xml(ViewProviderSeismicLabFeatureKurtosisPy)
generate_from_xml(ViewProviderSeismicLabFeatureLocationDistributionPy)
generate_from_xml(ViewProviderSeismicLabFeatureMeanAccelerationPy)
generate_from_xml(ViewProviderSeismicLabFeatureModulationPy)
generate_from_xml(ViewProviderSeismicLabFeaturePeakFactorPy)
generate_from_xml(ViewProviderSeismicLabFeatureProbabilityDensityFunctionPy)
generate_from_xml(ViewProviderSeismicLabFeaturePSDDecompositionMethodPy)
generate_from_xml(ViewProviderSeismicLabFeatureRandomnessPy)
generate_from_xml(ViewProviderSeismicLabFeatureShearVelocityOfFlowPy)
generate_from_xml(ViewProviderSeismicLabFeatureSimulationMethodPy)
generate_from_xml(ViewProviderSeismicLabFeatureSkewnessPy)
generate_from_xml(ViewProviderSeismicLabFeatureStandardDeviationPy)
generate_from_xml(ViewProviderSeismicLabFeatureUserDefinedRPSObjectPy)
generate_from_xml(ViewProviderSeismicLabFeatureVariancePy)
generate_from_xml(ViewProviderSeismicLabFeatureWavePassageEffectPy)
generate_from_xml(ViewProviderSeismicLabFeatureSpectrumPy)
generate_from_xml(ViewProviderSeismicLabFeatureMatrixToolPy)
generate_from_xml(ViewProviderSeismicLabFeatureTableToolPy)
generate_from_xml(ViewProviderSeismicLabSimulationPy)
generate_from_xml(ViewProviderSeismicLabSimulationComparisonPy)


# The XML files
set(SeismicLabGui_XML_SRCS
    ViewProviderSeismicLabFeatureCoherencePy.xml
    ViewProviderSeismicLabFeatureCorrelationPy.xml
    ViewProviderSeismicLabFeatureCumulativeProbabilityDistributionPy.xml
    ViewProviderSeismicLabFeatureFrequencyDistributionPy.xml
    ViewProviderSeismicLabFeatureKurtosisPy.xml
    ViewProviderSeismicLabFeatureLocationDistributionPy.xml
    ViewProviderSeismicLabFeatureMeanAccelerationPy.xml
    ViewProviderSeismicLabFeatureModulationPy.xml
    ViewProviderSeismicLabFeaturePeakFactorPy.xml
    ViewProviderSeismicLabFeatureProbabilityDensityFunctionPy.xml
    ViewProviderSeismicLabFeaturePSDDecompositionMethodPy.xml
    ViewProviderSeismicLabFeatureRandomnessPy.xml
    ViewProviderSeismicLabFeatureShearVelocityOfFlowPy.xml
    ViewProviderSeismicLabFeatureSimulationMethodPy.xml
    ViewProviderSeismicLabFeatureSkewnessPy.xml
    ViewProviderSeismicLabFeatureStandardDeviationPy.xml
    ViewProviderSeismicLabFeatureUserDefinedRPSObjectPy.xml
    ViewProviderSeismicLabFeatureVariancePy.xml
    ViewProviderSeismicLabFeatureWavePassageEffectPy.xml
    ViewProviderSeismicLabFeatureSpectrumPy.xml
    ViewProviderSeismicLabFeatureMatrixToolPy.xml
    ViewProviderSeismicLabFeatureTableToolPy.xml
    ViewProviderSeismicLabSimulationPy.xml
    ViewProviderSeismicLabSimulationComparisonPy.xml
)

set(SeismicLabGui_LIBS
    SeismicLabAPI
    SeismicLab
    LabRPSGui
    LabRPSApp
    Part
)

if(BUILD_QT5)
    qt5_add_resources(SeismicLabGui_SRCS Resources/SeismicLab.qrc)
else()
    qt4_add_resources(SeismicLabGui_SRCS Resources/SeismicLab.qrc)
endif()

set(SeismicLabGui_UIC_SRCS
DlgNewSimulation.ui
DlgSeismicLabFeatures.ui
DlgSeismicLabFeaturesCreation.ui
DlgSimulationComparison.ui
DlgSettingsSeismicLabLimit.ui
DlgSettingsSeismicLabGeneral.ui

)


SET(SeismicLabGui_DLG_SRCS
    ${SeismicLabGui_UIC_HDRS}
    DlgSettingsSeismicLabLimit.ui
    DlgSettingsSeismicLabLimitImp.cpp
    DlgSettingsSeismicLabLimitImp.h
    DlgSettingsSeismicLabGeneral.ui
    DlgSettingsSeismicLabGeneralImp.cpp
    DlgSettingsSeismicLabGeneralImp.h

)

SOURCE_GROUP("Setting-Dialogs" FILES ${SeismicLabGui_DLG_SRCS})


if(BUILD_QT5)
    qt5_wrap_ui(SeismicLabGui_UIC_HDRS ${SeismicLabGui_UIC_SRCS})
else()
    qt4_wrap_ui(SeismicLabGui_UIC_HDRS ${SeismicLabGui_UIC_SRCS})
endif()

SET(ViewProvider_CPP_SRCS
ViewProviderSeismicLabSimulation.cpp
DlgSeismicLabFeaturesCreation.cpp
DlgSimulationComparison.cpp
ViewProviderSeismicLabFeatureCoherence.cpp
ViewProviderSeismicLabFeatureCorrelation.cpp
ViewProviderSeismicLabFeatureCumulativeProbabilityDistribution.cpp
ViewProviderSeismicLabFeatureFrequencyDistribution.cpp
ViewProviderSeismicLabFeatureKurtosis.cpp
ViewProviderSeismicLabFeatureLocationDistribution.cpp
ViewProviderSeismicLabFeatureMeanAcceleration.cpp
ViewProviderSeismicLabFeatureModulation.cpp
ViewProviderSeismicLabFeaturePeakFactor.cpp
ViewProviderSeismicLabFeatureProbabilityDensityFunction.cpp
ViewProviderSeismicLabFeaturePSDDecompositionMethod.cpp
ViewProviderSeismicLabFeatureRandomness.cpp
ViewProviderSeismicLabFeatureShearVelocityOfFlow.cpp
ViewProviderSeismicLabFeatureSimulationMethod.cpp
ViewProviderSeismicLabFeatureSkewness.cpp
ViewProviderSeismicLabFeatureStandardDeviation.cpp
ViewProviderSeismicLabFeatureUserDefinedRPSObject.cpp
ViewProviderSeismicLabFeatureVariance.cpp
ViewProviderSeismicLabFeatureWavePassageEffect.cpp
ViewProviderSeismicLabFeatureSpectrum.cpp
ViewProviderSeismicLabFeatureMatrixTool.cpp
ViewProviderSeismicLabFeatureTableTool.cpp
ViewProviderSeismicLabSimulation.cpp
ViewProviderSeismicLabSimulationComparison.cpp

ViewProviderSeismicLabFeatureCoherencePyImp.cpp
ViewProviderSeismicLabFeatureCorrelationPyImp.cpp
ViewProviderSeismicLabFeatureCumulativeProbabilityDistributionPyImp.cpp
ViewProviderSeismicLabFeatureFrequencyDistributionPyImp.cpp
ViewProviderSeismicLabFeatureKurtosisPyImp.cpp
ViewProviderSeismicLabFeatureLocationDistributionPyImp.cpp
ViewProviderSeismicLabFeatureMeanAccelerationPyImp.cpp
ViewProviderSeismicLabFeatureModulationPyImp.cpp
ViewProviderSeismicLabFeaturePeakFactorPyImp.cpp
ViewProviderSeismicLabFeatureProbabilityDensityFunctionPyImp.cpp
ViewProviderSeismicLabFeaturePSDDecompositionMethodPyImp.cpp
ViewProviderSeismicLabFeatureRandomnessPyImp.cpp
ViewProviderSeismicLabFeatureShearVelocityOfFlowPyImp.cpp
ViewProviderSeismicLabFeatureSimulationMethodPyImp.cpp
ViewProviderSeismicLabFeatureSkewnessPyImp.cpp
ViewProviderSeismicLabFeatureStandardDeviationPyImp.cpp
ViewProviderSeismicLabFeatureUserDefinedRPSObjectPyImp.cpp
ViewProviderSeismicLabFeatureVariancePyImp.cpp
ViewProviderSeismicLabFeatureWavePassageEffectPyImp.cpp
ViewProviderSeismicLabFeatureSpectrumPyImp.cpp
ViewProviderSeismicLabFeatureMatrixToolPyImp.cpp
ViewProviderSeismicLabFeatureTableToolPyImp.cpp
ViewProviderSeismicLabSimulationPyImp.cpp
ViewProviderSeismicLabSimulationComparisonPyImp.cpp

)
SET(ViewProvider_HPP_SRCS
ViewProviderSeismicLabSimulation.h
DlgSeismicLabFeaturesCreation.h
DlgSimulationComparison.h
ViewProviderSeismicLabFeatureCoherence.h
ViewProviderSeismicLabFeatureCorrelation.h
ViewProviderSeismicLabFeatureCumulativeProbabilityDistribution.h
ViewProviderSeismicLabFeatureFrequencyDistribution.h
ViewProviderSeismicLabFeatureKurtosis.h
ViewProviderSeismicLabFeatureLocationDistribution.h
ViewProviderSeismicLabFeatureMeanAcceleration.h
ViewProviderSeismicLabFeatureModulation.h
ViewProviderSeismicLabFeaturePeakFactor.h
ViewProviderSeismicLabFeatureProbabilityDensityFunction.h
ViewProviderSeismicLabFeaturePSDDecompositionMethod.h
ViewProviderSeismicLabFeatureRandomness.h
ViewProviderSeismicLabFeatureShearVelocityOfFlow.h
ViewProviderSeismicLabFeatureSimulationMethod.h
ViewProviderSeismicLabFeatureSkewness.h
ViewProviderSeismicLabFeatureStandardDeviation.h
ViewProviderSeismicLabFeatureUserDefinedRPSObject.h
ViewProviderSeismicLabFeatureVariance.h
ViewProviderSeismicLabFeatureWavePassageEffect.h
ViewProviderSeismicLabFeatureSpectrum.h
ViewProviderSeismicLabFeatureMatrixTool.h
ViewProviderSeismicLabFeatureTableTool.h
ViewProviderSeismicLabSimulationComparison.h
)

SET(ViewProvider_SRCS
    ${ViewProvider_CPP_SRCS}
    ${ViewProvider_HPP_SRCS}
    ${SeismicLabGui_XML_SRCS}

)
SOURCE_GROUP("ViewProvider" FILES ${ViewProvider_SRCS})

SET(SeismicLabGui_SRCS
    ${SeismicLabGui_SRCS}
    ${SeismicLabGui_UIC_HDRS}
    ${ViewProvider_SRCS}
    ${SeismicLabGui_DLG_SRCS}
    AppSeismicLabGui.cpp
    Command.cpp
    Resources/SeismicLab.qrc
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
    DlgNewSimulation.cpp
    DlgNewSimulation.h
    RPSSeismicLabPyTool.cpp
    RPSSeismicLabPyTool.h
    SeismicLabSimulationObserver.h
    SeismicLabSimulationObserver.cpp
    SeismicLabSimulationWorker.h
    SeismicLabSimulationWorker.cpp
    SeismicLabAllFeaturesComputation.h
    SeismicLabAllFeaturesComputation.cpp
    SeismicLabComparisonStarter.h
    SeismicLabComparisonStarter.cpp

)

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" PCH_SRCS ${SeismicLabGui_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(SeismicLabGui PreCompiled.h PreCompiled.cpp PCH_SRCS)
endif(LABRPS_USE_PCH)


SET(SeismicLabGuiIcon_SVG
    Resources/icons/SeismicLabWorkbench.svg
)

add_library(SeismicLabGui SHARED ${SeismicLabGui_SRCS} ${SeismicLabGuiIcon_SVG})
target_link_libraries(SeismicLabGui ${SeismicLabGui_LIBS})
set_target_properties(SeismicLabGui PROPERTIES FOLDER "Workbenches/SeismicLab")


SET_BIN_DIR(SeismicLabGui SeismicLabGui /Mod/SeismicLab)
SET_PYTHON_PREFIX_SUFFIX(SeismicLabGui)

rps_copy_sources(SeismicLabGui "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/Mod/SeismicLab" ${SeismicLabGuiIcon_SVG})

INSTALL(TARGETS SeismicLabGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(FILES ${SeismicLabGuiIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Mod/SeismicLab/Resources/icons")
