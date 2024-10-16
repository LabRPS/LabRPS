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

set(SeismicLabPlugin_LIBS
    LabRPSGui
    SeismicLabAPI
    GeneralTools
    SeismicLabTools
)

if(BUILD_QT5)
    qt5_add_resources(SeismicLabPlugin_SRCS Resources/SeismicLabPlugin.qrc)
else()
    qt4_add_resources(SeismicLabPlugin_SRCS Resources/SeismicLabPlugin.qrc)
endif()

set(SeismicLabPlugin_UIC_SRCS
Widgets/DlgHorizontalLocationDistribution.ui
Widgets/DlgVerticalLocationDistribution.ui
Widgets/RPSFrequencyDistributionDialog.ui
Widgets/DlgUniformDistributionLocation.ui
Widgets/DlgUniformRandomPhases.ui
Widgets/DlgRandomPhasesFromFile.ui
Widgets/DlgWavePassageEffect.ui
Widgets/DlgCloughPenzienSpectrum.ui
Widgets/DlgKanaiTajimiSpectrum.ui
Widgets/DlgHuZhouSpectrum.ui
Widgets/DlgConstantModulation.ui
Widgets/DlgExponentialModulation.ui
Widgets/DlgJenningsEtAl1968Modulation.ui
Widgets/DlgSaragoniHart1974Modulation.ui
Widgets/DlgTrapezoidalModulation.ui
Widgets/DlgBogdanoffGoldbergBernardModulation.ui
Widgets/DlgBoxCarModulation.ui
Widgets/DlgAbrahamsonCoherence.ui
Widgets/DlgHarichandranVanmarckeCoherence.ui
Widgets/DlgLohAndLinCoherence.ui
Widgets/DlgGridPoints.ui


)

if(BUILD_QT5)
    qt5_wrap_ui(SeismicLabPlugin_UIC_HDRS ${SeismicLabPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(SeismicLabPlugin_UIC_HDRS ${SeismicLabPlugin_UIC_SRCS})
endif()

SET(SeismicLabPlugin_SRCS
${SeismicLabPlugin_SRCS}
${SeismicLabPlugin_UIC_HDRS}
# AppSeismicLabPlugin.cpp
Resources/SeismicLabPlugin.qrc
PreCompiled.cpp
PreCompiled.h
Widgets/DlgVerticalLocationDistribution.cpp
Widgets/DlgVerticalLocationDistribution.h
Widgets/DlgHorizontalLocationDistribution.h
Widgets/DlgHorizontalLocationDistribution.cpp
Widgets/DlgUniformDistributionLocation.h
Widgets/DlgUniformDistributionLocation.cpp
Widgets/DlgUniformRandomPhases.h
Widgets/DlgUniformRandomPhases.cpp
Widgets/DlgRandomPhasesFromFile.h
Widgets/DlgRandomPhasesFromFile.cpp
Widgets/DlgWavePassageEffect.h
Widgets/DlgWavePassageEffect.cpp
Widgets/DlgCloughPenzienSpectrum.h
Widgets/DlgCloughPenzienSpectrum.cpp
Widgets/DlgKanaiTajimiSpectrum.h
Widgets/DlgKanaiTajimiSpectrum.cpp
Widgets/DlgHuZhouSpectrum.h
Widgets/DlgHuZhouSpectrum.cpp
Widgets/DlgConstantModulation.h
Widgets/DlgConstantModulation.cpp
Widgets/DlgExponentialModulation.h
Widgets/DlgExponentialModulation.cpp
Widgets/DlgJenningsEtAl1968Modulation.h
Widgets/DlgJenningsEtAl1968Modulation.cpp
Widgets/DlgSaragoniHart1974Modulation.h
Widgets/DlgSaragoniHart1974Modulation.cpp
Widgets/DlgTrapezoidalModulation.h
Widgets/DlgTrapezoidalModulation.cpp
Widgets/DlgBogdanoffGoldbergBernardModulation.h
Widgets/DlgBogdanoffGoldbergBernardModulation.cpp
Widgets/DlgBoxCarModulation.h
Widgets/DlgBoxCarModulation.cpp
Widgets/DlgAbrahamsonCoherence.h
Widgets/DlgAbrahamsonCoherence.cpp
Widgets/DlgHarichandranVanmarckeCoherence.h
Widgets/DlgHarichandranVanmarckeCoherence.cpp
Widgets/DlgLohAndLinCoherence.h
Widgets/DlgLohAndLinCoherence.cpp
Widgets/DlgGridPoints.h
Widgets/DlgGridPoints.cpp

SeismicLabPlugin.cpp
GeneralSpatialDistribution.cpp
GeneralSpatialDistribution.h
WLHorizontalUniformDistribution.h
WLHorizontalUniformDistribution.cpp
WLVerticalUniformDistribution.h
WLVerticalUniformDistribution.cpp
RPSDoubleIndexFrequency.cpp
RPSSingleIndexFrequency.cpp
RPSDoubleIndexFrequency.h
RPSSingleIndexFrequency.h
Widgets/RPSFrequencyDistributionDialog.cpp 
Widgets/RPSFrequencyDistributionDialog.h
RPSRandomPhasesFromFile.h    
RPSRandomPhasesFromFile.cpp
RPSUniformRandomPhases.h
RPSUniformRandomPhases.cpp
CholeskyDecomposition.cpp
CholeskyDecomposition.h
WLUniformDistributionLocations.h
WLUniformDistributionLocations.cpp
RPSWavePassageEffect.h
RPSWavePassageEffect.cpp
TargetCorrelation.h
TargetCorrelation.cpp
AppSeismicLabPlugin.cpp
ZervaModelFrequencyDistribution.cpp
ZervaModelFrequencyDistribution.h
RPSCloughPenzienSpectrum.h
RPSCloughPenzienSpectrum.cpp
RPSKanaiTajimiSpectrum.h
RPSKanaiTajimiSpectrum.cpp
RPSHuZhouSpectrum.h
RPSHuZhouSpectrum.cpp
RPSConstantModulation.h
RPSConstantModulation.cpp
RPSExponentialModulation.h
RPSExponentialModulation.cpp
RPSJenningsEtAl1968Modulation.h
RPSJenningsEtAl1968Modulation.cpp
RPSSaragoniHart1974Modulation.h
RPSSaragoniHart1974Modulation.cpp
RPSTrapezoidalModulation.h
RPSTrapezoidalModulation.cpp
RPSBogdanoffGoldbergBernardModulation.h
RPSBogdanoffGoldbergBernardModulation.cpp
RPSBoxCarModulation.h
RPSBoxCarModulation.cpp
RPSAbrahamsonCoherence.h
RPSAbrahamsonCoherence.cpp
RPSHarichandranVanmarckeCoherence.h
RPSHarichandranVanmarckeCoherence.cpp
RPSLohAndLinCoherence.h
RPSLohAndLinCoherence.cpp
WLGridPoints.cpp
WLGridPoints.h
)

SET(Metadata_Files
SeismicLabPlugin.txt

)


SET(SeismicLabPluginIcon_SVG
    # Resources/icons/SeismicLabPluginWorkbench.svg
)

add_library(SeismicLabPlugin SHARED ${SeismicLabPlugin_SRCS} ${Metadata_Files} ${SeismicLabPluginIcon_SVG})
target_link_libraries(SeismicLabPlugin ${SeismicLabPlugin_LIBS})
set_target_properties(SeismicLabPlugin PROPERTIES FOLDER "Plugins/SeismicLab")


SET_BIN_DIR(SeismicLabPlugin SeismicLabPlugin /Plugins/SeismicLabWorkbench/SeismicLabPlugin)

rps_copy_sources(SeismicLabPlugin "${CMAKE_BINARY_DIR}/Plugins/SeismicLabWorkbench/SeismicLabPlugin" ${Metadata_Files})
INSTALL(TARGETS SeismicLabPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/SeismicLabPlugin")
INSTALL(FILES SeismicLabPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/SeismicLabPlugin")
INSTALL(FILES ${SeismicLabPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/SeismicLab/SeismicLabPlugin/Resources/icons")

