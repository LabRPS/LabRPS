QMAKE_PROJECT_DEPTH = 0
linux-g++-64: libsuff=64
QT -= gui

TARGET = windlabapi
TEMPLATE = lib
DEFINES += WINDLABAPI_LIBRARY
DEFINES += RPS_BUILDING_CORE

CONFIG += c++17

SOURCES += \
    RPSWindLabAPI.cpp\
    RPSWindLabFramework.cpp\
    RPSWindLabpluginAPI.cpp\
    RPSWindLabsimuData.cpp\
    RPSWindLabTools.cpp\
    ObjectDescription.cpp\

HEADERS += \
    IrpsWLCoherence.h\
    IrpsWLCorrelation.h\
    IrpsWLFrequencyDistribution.h\
    IrpsWLLocationDistribution.h\
    IrpsWLMean.h\
    IrpsWLModulation.h\
    IrpsWLPSDdecompositionMethod.h\
    IrpsWLRandomness.h\
    IrpsWLXSpectrum.h\
    IrpsWLYSpectrum.h\
    IrpsWLSimuMethod.h\
    IrpsWLZSpectrum.h\
    RPSWindLabAPIdefines.h\
    RPSWindLabFramework.h\
    RPSWindLabpluginAPI.h\
    RPSWindLabsimuData.h\
    RPSWindLabTools.h\
    RPS.h\
    ObjectDescription.h\
    IrpsWLMatrixTool.h\
    IrpsWLTableTool.h\
    IrpsWLUserDefinedRPSObject.h\


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

