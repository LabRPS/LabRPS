#define QT_NO_KEYWORDS

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
    ${EIGEN3_INCLUDE_DIR}
)

set(WindLabPlugin_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

if(BUILD_QT5)
    qt5_add_resources(WindLabPlugin_SRCS Resources/WindLabPlugin.qrc)
else()
    qt4_add_resources(WindLabPlugin_SRCS Resources/WindLabPlugin.qrc)
endif()

set(WindLabPlugin_UIC_SRCS
Widgets/DlgHorizontalLocationDistribution.ui
Widgets/DlgVerticalLocationDistribution.ui
Widgets/RPSFrequencyDistributionDialog.ui
Widgets/RPSModulationDialog.ui
Widgets/RPSVonKarmanDialog.ui
Widgets/DlgUniformDistributionLocation.ui
Widgets/DlgDHLowProfile.ui
Widgets/DlgLogarithmicLowProfile.ui
Widgets/DlgPowerLowProfile.ui
Widgets/DlgDavenportSpectrum.ui
Widgets/DlgDavenportCoherence.ui
Widgets/DlgHarrisSpectrum.ui
Widgets/DlgKaimalAlongWindSpectrum.ui
Widgets/DlgSimuAlongWindSpectrum.ui
Widgets/DlgSimuAcrossWindSpectrum.ui
Widgets/DlgSimuVerticalWindSpectrum.ui
Widgets/DlgKaimalAcrossWindSpectrum.ui
Widgets/DlgKaimalVerticalWindSpectrum.ui
Widgets/DlgvonKarmanAlongWindSpectrum.ui
Widgets/DlgvonKarmanAcrossWindSpectrum.ui
Widgets/DlgvonKarmanVerticalWindSpectrum.ui
Widgets/DlgUniformRandomPhases.ui
Widgets/DlgRandomPhasesFromFile.ui
Widgets/DlgExpoModulation.ui
Widgets/DlgSineModulation.ui
Widgets/DlgThreeParaModulation.ui
Widgets/DlgWavePassageEffect.ui
Widgets/DlgKrenkCoherence.ui
Widgets/DlgTurbulenceIntensityASCE798.ui
Widgets/DlgGridPoints.ui



)

if(BUILD_QT5)
    qt5_wrap_ui(WindLabPlugin_UIC_HDRS ${WindLabPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(WindLabPlugin_UIC_HDRS ${WindLabPlugin_UIC_SRCS})
endif()

SET(WindLabPlugin_SRCS
${WindLabPlugin_SRCS}
${WindLabPlugin_UIC_HDRS}
# AppWindLabPlugin.cpp
Resources/WindLabPlugin.qrc
PreCompiled.cpp
PreCompiled.h
WindLabPlugin.cpp
GeneralSpatialDistribution.cpp
GeneralSpatialDistribution.h
RPSLogarithmicLowProfile.cpp
RPSLogarithmicLowProfile.h
RPSWLPowerLowProfile.cpp
RPSWLPowerLowProfile.h
RPSDHLowProfile.h
RPSDHLowProfile.cpp
Widgets/IconLoader.cpp
Widgets/IconLoader.h
WLHorizontalUniformDistribution.h
WLVerticalUniformDistribution.h
WLHorizontalUniformDistribution.cpp
WLVerticalUniformDistribution.cpp
Widgets/DlgHorizontalLocationDistribution.h
Widgets/DlgHorizontalLocationDistribution.cpp
Widgets/DlgVerticalLocationDistribution.cpp
Widgets/DlgVerticalLocationDistribution.h
Widgets/DlgUniformDistributionLocation.h
Widgets/DlgUniformDistributionLocation.cpp
Widgets/DlgDHLowProfile.h
Widgets/DlgDHLowProfile.cpp
Widgets/DlgLogarithmicLowProfile.h
Widgets/DlgLogarithmicLowProfile.cpp
Widgets/DlgPowerLowProfile.h
Widgets/DlgPowerLowProfile.cpp
Widgets/DlgDavenportSpectrum.h
Widgets/DlgDavenportSpectrum.cpp
Widgets/DlgDavenportCoherence.h
Widgets/DlgDavenportCoherence.cpp
Widgets/DlgHarrisSpectrum.h
Widgets/DlgHarrisSpectrum.cpp
Widgets/DlgKaimalAlongWindSpectrum.h
Widgets/DlgKaimalAlongWindSpectrum.cpp
Widgets/DlgSimuAlongWindSpectrum.h
Widgets/DlgSimuAlongWindSpectrum.cpp
Widgets/DlgSimuAcrossWindSpectrum.h
Widgets/DlgSimuAcrossWindSpectrum.cpp
Widgets/DlgSimuVerticalWindSpectrum.h
Widgets/DlgSimuVerticalWindSpectrum.cpp
Widgets/DlgKaimalAcrossWindSpectrum.h
Widgets/DlgKaimalAcrossWindSpectrum.cpp
Widgets/DlgKaimalVerticalWindSpectrum.h
Widgets/DlgKaimalVerticalWindSpectrum.cpp
Widgets/DlgvonKarmanAlongWindSpectrum.h
Widgets/DlgvonKarmanAlongWindSpectrum.cpp
Widgets/DlgvonKarmanAcrossWindSpectrum.h
Widgets/DlgvonKarmanAcrossWindSpectrum.cpp
Widgets/DlgvonKarmanVerticalWindSpectrum.h
Widgets/DlgvonKarmanVerticalWindSpectrum.cpp
Widgets/DlgUniformRandomPhases.h
Widgets/DlgUniformRandomPhases.cpp
Widgets/DlgRandomPhasesFromFile.h
Widgets/DlgRandomPhasesFromFile.cpp
Widgets/DlgExpoModulation.h
Widgets/DlgExpoModulation.cpp
Widgets/DlgSineModulation.h
Widgets/DlgSineModulation.cpp
Widgets/DlgThreeParaModulation.h
Widgets/DlgThreeParaModulation.cpp
Widgets/DlgWavePassageEffect.h
Widgets/DlgWavePassageEffect.cpp
Widgets/DlgKrenkCoherence.h
Widgets/DlgKrenkCoherence.cpp
Widgets/DlgTurbulenceIntensityASCE798.h
Widgets/DlgTurbulenceIntensityASCE798.cpp
Widgets/DlgGridPoints.h
Widgets/DlgGridPoints.cpp


RPSDoubleIndexFrequency.cpp
RPSSingleIndexFrequency.cpp
RPSDoubleIndexFrequency.h
RPSSingleIndexFrequency.h
Widgets/RPSFrequencyDistributionDialog.cpp 
Widgets/RPSFrequencyDistributionDialog.h
RPSDavenportCoherence.cpp
RPSDavenportCoherence.h
RPSRandomPhasesFromFile.h    
RPSRandomPhasesFromFile.cpp
RPSUniformRandomPhases.h
RPSUniformRandomPhases.cpp
CholeskyDecomposition.cpp
CholeskyDecomposition.h
ExpoModulation.cpp
ExpoModulation.h
SineModulation.cpp
SineModulation.h
ThreeParaModulation.cpp
ThreeParaModulation.h
Widgets/RPSModulationDialog.cpp    
Widgets/RPSModulationDialog.h
RPSDavenportSpectrum.cpp 
RPSHarrisSpectrum.cpp 
RPSKaimalAcrossSpectr.cpp 
RPSKaimalSpectr.cpp 
RPSKaimalVerticalSpectr.cpp 
RPSSimuAcrossWindSpectrum.cpp 
RPSSimuAlongWindSpectrum.cpp 
RPSSimuVerticalWindSpectrum.cpp 
RPSvonKarmanAcrossWindSpectrum.cpp 
RPSvonKarmanAlongWindSpectrum.cpp 
RPSvonKarmanVerticalWindSpectrum.cpp 
RPSDavenportSpectrum.h
RPSHarrisSpectrum.h
RPSKaimalAcrossSpectr.h
RPSKaimalSpectr.h
RPSKaimalVerticalSpectr.h
RPSSimuAcrossWindSpectrum.h
RPSSimuAlongWindSpectrum.h
RPSSimuVerticalWindSpectrum.h
RPSvonKarmanAcrossWindSpectrum.h
RPSvonKarmanAlongWindSpectrum.h
RPSvonKarmanVerticalWindSpectrum.h
Widgets/RPSVonKarmanDialog.cpp
Widgets/RPSVonKarmanDialog.h
RPSDeodatis1987.h
RPSDeodatis1987.cpp
WLUniformDistributionLocations.h
WLUniformDistributionLocations.cpp
RPSWavePassageEffect.h
RPSWavePassageEffect.cpp
TargetCorrelation.h
TargetCorrelation.cpp
AppWindLabPlugin.cpp
ZervaModelFrequencyDistribution.cpp
ZervaModelFrequencyDistribution.h
RPSKrenkCoherence.cpp
RPSKrenkCoherence.h
RPSTurbulenceIntensityASCE798.cpp
RPSTurbulenceIntensityASCE798.h
WLGridPoints.cpp
WLGridPoints.h
)

SET(Metadata_Files
WindLabPlugin.txt

)


SET(WindLabPluginIcon_SVG
    # Resources/icons/WindLabPluginWorkbench.svg
)

add_library(WindLabPlugin SHARED ${WindLabPlugin_SRCS} ${Metadata_Files} ${WindLabPluginIcon_SVG})
target_link_libraries(WindLabPlugin ${WindLabPlugin_LIBS})
set_target_properties(WindLabPlugin PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(WindLabPlugin WindLabPlugin /Plugins/WindLabWorkbench/WindLabPlugin)

rps_copy_sources(WindLabPlugin "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/WindLabPlugin" ${Metadata_Files})
INSTALL(TARGETS WindLabPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindLabPlugin")
INSTALL(FILES WindLabPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindLabPlugin")
INSTALL(FILES ${WindLabPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/WindLabPlugin/Resources/icons")

