QMAKE_PROJECT_DEPTH = 0
linux-g++-64: libsuff=64
QT -= gui

TARGET = rpsTools
TEMPLATE = lib
DEFINES += RPSTOOLS_LIBRARY
DEFINES += RPS_BUILDING_CORE

CONFIG += c++17

SOURCES += \
    rpsTools/RPSTools.cpp\
    rpsTools/src/general/CholeskyDecomposition.cpp\
    rpsTools/src/general/UniformRandomPhaseMatrixGenerator.cpp\
    rpsTools/src/windVelocity/spectrum/WindSpectrum.cpp\
    rpsTools/src/windVelocity/spectrum/KaimalSpectrum.cpp\
    rpsTools/src/windVelocity/spectrum/SimuSpectrum.cpp\
    rpsTools/src/windVelocity/spectrum/VonKarmanSpectrum.cpp\
    rpsTools/src/windVelocity/spectrum/HarrisSpectrum.cpp\
    rpsTools/src/windVelocity/spectrum/DavenportSpectrum.cpp\
    rpsTools/src/windVelocity/meanWindSpeed/DeavesHarrisMeanWindSpeed.cpp\
    rpsTools/src/windVelocity/meanWindSpeed/LogarithmicMeanWindSpeed.cpp\
    rpsTools/src/windVelocity/meanWindSpeed/PowerLawMeanWindSpeed.cpp\
    rpsTools/src/windVelocity/coherence/DavenportCoherence.cpp\
    rpsTools/src/windVelocity/modulation/ExponentialModulation.cpp\
    rpsTools/src/windVelocity/modulation/SineModulation.cpp\
    rpsTools/src/windVelocity/modulation/ThreeParametersModulation.cpp\


HEADERS += \
    rpsTools/RPSTools.h\
    rpsTools/RPSToolsDefines.h\
    rpsTools/src/general/CholeskyDecomposition.h\
    rpsTools/src/general/UniformRandomPhaseMatrixGenerator.h\
    rpsTools/src/windVelocity/spectrum/WindSpectrum.h\
    rpsTools/src/windVelocity/spectrum/KaimalSpectrum.h\
    rpsTools/src/windVelocity/spectrum/SimuSpectrum.h\
    rpsTools/src/windVelocity/spectrum/VonKarmanSpectrum.h\
    rpsTools/src/windVelocity/spectrum/HarrisSpectrum.h\
    rpsTools/src/windVelocity/spectrum/DavenportSpectrum.h\
    rpsTools/src/windVelocity/meanWindSpeed/DeavesHarrisMeanWindSpeed.h\
    rpsTools/src/windVelocity/meanWindSpeed/LogarithmicMeanWindSpeed.h\
    rpsTools/src/windVelocity/meanWindSpeed/PowerLawMeanWindSpeed.h\
    rpsTools/src/windVelocity/coherence/DavenportCoherence.h\
    rpsTools/src/windVelocity/modulation/ExponentialModulation.h\
    rpsTools/src/windVelocity/modulation/SineModulation.h\
    rpsTools/src/windVelocity/modulation/ThreeParametersModulation.h\

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

