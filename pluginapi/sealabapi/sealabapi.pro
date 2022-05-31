QMAKE_PROJECT_DEPTH = 0
linux-g++-64: libsuff=64
QT -= gui

TARGET = sealabapi
TEMPLATE = lib
DEFINES += SEALABAPI_LIBRARY
DEFINES += RPS_BUILDING_CORE

CONFIG += c++17

SOURCES += \
    untitled3.cpp\
    RPSSeaLabAPI.cpp\
    RPSSeaLabFramework.cpp\
    RPSSeaLabpluginAPI.cpp\
    RPSSeaLabsimuData.cpp\
    RPSSeaLabTools.cpp

HEADERS += \
    RPSSeaLabAPIdefines.h \
    untitled3.h\
    IrpsSeLCoherence.h\
    IrpsSeLCorrelation.h\
    IrpsSeLDirectionalSpectrum.h\
    IrpsSeLDirectionDistribution.h\
    IrpsSeLDirectionSpreadingFunction.h\
    IrpsSeLFrequencyDistribution.h\
    IrpsSeLLocationDistribution.h\
    IrpsSeLMean.h\
    IrpsSeLModulation.h\
    IrpsSeLPSDdecompositionMethod.h\
    IrpsSeLRandomness.h\
    IrpsSeLSimulationMethod.h\
    IrpsSeLSpectrum.h\
    RPSSeaLabAPI.h\
    RPSSeaLabFramework.h\
    RPSSeaLabpluginAPI.h\
    RPSSeaLabsimuData.h\
    RPSSeaLabTools.h\
    RPS.h



# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


