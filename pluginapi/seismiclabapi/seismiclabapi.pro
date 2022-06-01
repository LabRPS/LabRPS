QMAKE_PROJECT_DEPTH = 0
linux-g++-64: libsuff=64
QT -= gui

TARGET = seismiclabapi
TEMPLATE = lib
DEFINES += SEISMICAPI_LIBRARY
DEFINES += RPS_BUILDING_CORE

CONFIG += c++17

SOURCES += \
    RPSSeismicLabAPI.cpp\
    RPSSeismicLabFramework.cpp\
    RPSSeismicLabpluginAPI.cpp\
    RPSSeismicLabsimuData.cpp\
    RPSSeismicLabTools.cpp\
    

HEADERS += \
    IrpsSLCoherence.h\
    IrpsSLCorrelation.h\
    IrpsSLFrequencyDistribution.h\
    IrpsSLLocationDistribution.h\
    IrpsSLModulation.h\
    IrpsSLPSDdecompositionMethod.h\
    IrpsSLRandomness.h\
    IrpsSLSimulationMethod.h\
    IrpsSLXSpectrum.h\
    IrpsSLYSpectrum.h\
    IrpsSLZSpectrum.h\
    RPSSeismicLabAPI.h\
    RPSSeismicLabAPIdefines.h\
    RPSSeismicLabFramework.h\
    RPSSeismicLabpluginAPI.h\
    RPSSeismicLabsimuData.h\
    RPSSeaLabFramework.h\
    RPSSeismicLabTools.h\
    RPS.h


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

