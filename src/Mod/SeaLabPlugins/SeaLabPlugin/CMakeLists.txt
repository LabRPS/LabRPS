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

set(SeaLabPlugin_LIBS
    LabRPSGui
    SeaLabAPI
    GeneralTools
    SeaLabTools
)

if(BUILD_QT5)
    qt5_add_resources(SeaLabPlugin_SRCS Resources/SeaLabPlugin.qrc)
else()
    qt4_add_resources(SeaLabPlugin_SRCS Resources/SeaLabPlugin.qrc)
endif()

set(SeaLabPlugin_UIC_SRCS
Widgets/RPSFrequencyDistributionDialog.ui
Widgets/DlgUniformRandomPhases.ui
Widgets/DlgRandomPhasesFromFile.ui
Widgets/DlgGridPoints.ui
Widgets/DlgJonswapSpectrum.ui
Widgets/DlgPiersonMoskowitzSpectrum.ui
Widgets/DlgTorsethaugenSpectrum.ui
Widgets/DlgOchiAndHubbleSpectrum.ui
Widgets/DlgGaussianSwellSpectrum.ui

)

if(BUILD_QT5)
    qt5_wrap_ui(SeaLabPlugin_UIC_HDRS ${SeaLabPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(SeaLabPlugin_UIC_HDRS ${SeaLabPlugin_UIC_SRCS})
endif()

SET(SeaLabPlugin_SRCS
${SeaLabPlugin_SRCS}
${SeaLabPlugin_UIC_HDRS}
# AppSeaLabPlugin.cpp
Resources/SeaLabPlugin.qrc
PreCompiled.cpp
PreCompiled.h
Widgets/DlgUniformRandomPhases.h
Widgets/DlgUniformRandomPhases.cpp
Widgets/DlgRandomPhasesFromFile.h
Widgets/DlgRandomPhasesFromFile.cpp
Widgets/DlgGridPoints.h
Widgets/DlgGridPoints.cpp
Widgets/DlgJonswapSpectrum.h
Widgets/DlgJonswapSpectrum.cpp
Widgets/DlgPiersonMoskowitzSpectrum.h
Widgets/DlgPiersonMoskowitzSpectrum.cpp
Widgets/DlgTorsethaugenSpectrum.h
Widgets/DlgTorsethaugenSpectrum.cpp
Widgets/DlgOchiAndHubbleSpectrum.h
Widgets/DlgOchiAndHubbleSpectrum.cpp
Widgets/DlgGaussianSwellSpectrum.h
Widgets/DlgGaussianSwellSpectrum.cpp


SeaLabPlugin.cpp
GeneralSpatialDistribution.cpp
GeneralSpatialDistribution.h
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
AppSeaLabPlugin.cpp
ZervaModelFrequencyDistribution.cpp
ZervaModelFrequencyDistribution.h
WLGridPoints.cpp
WLGridPoints.h
RPSJonswapSpectrum.cpp
RPSJonswapSpectrum.h
RPSPiersonMoskowitzSpectrum.cpp
RPSPiersonMoskowitzSpectrum.h
RPSTorsethaugenSpectrum.cpp
RPSTorsethaugenSpectrum.h
RPSOchiAndHubbleSpectrum.cpp
RPSOchiAndHubbleSpectrum.h
RPSGaussianSwellSpectrum.cpp
RPSGaussianSwellSpectrum.h
RPSBretschneiderSpectrum.h
RPSBretschneiderSpectrum.cpp
RPSISSCSpectrum.h
RPSISSCSpectrum.cpp
)

SET(Metadata_Files
SeaLabPlugin.txt

)


SET(SeaLabPluginIcon_SVG
    # Resources/icons/SeaLabPluginWorkbench.svg
)

add_library(SeaLabPlugin SHARED ${SeaLabPlugin_SRCS} ${Metadata_Files} ${SeaLabPluginIcon_SVG})
target_link_libraries(SeaLabPlugin ${SeaLabPlugin_LIBS})
set_target_properties(SeaLabPlugin PROPERTIES FOLDER "Plugins/SeaLab")


SET_BIN_DIR(SeaLabPlugin SeaLabPlugin /Plugins/SeaLabWorkbench/SeaLabPlugin)

rps_copy_sources(SeaLabPlugin "${CMAKE_BINARY_DIR}/Plugins/SeaLabWorkbench/SeaLabPlugin" ${Metadata_Files})
INSTALL(TARGETS SeaLabPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeaLabWorkbench/SeaLabPlugin")
INSTALL(FILES SeaLabPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeaLabWorkbench/SeaLabPlugin")
INSTALL(FILES ${SeaLabPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/SeaLab/SeaLabPlugin/Resources/icons")

