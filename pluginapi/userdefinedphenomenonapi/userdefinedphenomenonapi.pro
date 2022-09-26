QMAKE_PROJECT_DEPTH = 0
linux-g++-64: libsuff=64
QT -= gui

TARGET = userdefinedphenomenonapi
TEMPLATE = lib
DEFINES += USERDEFINEDPHENOMENON_LIBRARY
DEFINES += RPS_BUILDING_CORE

CONFIG += c++17

SOURCES += \
    RPSUserDefinedPhenomenonAPI.cpp\
    RPSUserDefinedPhenomenonPluginAPI.cpp\
    ObjectDescription.cpp\
    RPSUserDefinedPhenomenonSimuData.cpp\

HEADERS += \
    IrpsUserDefinedPhenomenon.h\
    RPSUserDefinedPhenomenonAPIdefines.h\
    RPSUserDefinedPhenomenonPluginAPI.h\
    RPS.h\
    ObjectDescription.h\
    RPSUserDefinedPhenomenonSimuData.h\


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

