QT += gui
QT += widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

DEFINES += SEISMICLAB_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

################################################################################
### Dependencies                                                               #
################################################################################

contains(PRESET, linux_all_dynamic) {

  LIBS         +=  -libseismiclabapi
}

contains(PRESET, linux_static) {
  ### Link statically and dynamically against rest.
  LIBS         +=  -libseismiclabapi
}

contains(PRESET, linux_all_static) {
  ### mostly static linking, for self-contained binaries
  message(Build configuration: Linux all static)

  LIBS         += /usr/lib/libseismiclabapi.a
}

contains(PRESET, osx_dist) {
  # Uses HomeBrew supplied versions of the dependencies
  message(Build configuration: OSX Distro)

  LIBS         += -libseismiclabapi 
}

win32: {
  !mxe {
    ### Static linking mostly.
    message(Build configuration: Win32)

    isEmpty(APILIBPATH): APILIBPATH =E:/LabRPS/pluginapi

    INCLUDEPATH  += "$${APILIBPATH}/seismiclabapi"

    LIBS         += "$${APILIBPATH}/seismiclabapi/release/libseismiclabapi.a"
   }
}


SOURCES += \
    AbrahamsonCoherence.cpp\
    BogdanoffGoldbergBernarModulation.cpp\
    CloughPenzienSpectrum.cpp\
    HarichandranVanmarcheCoherence.cpp\
    JenningEtAlModulation.cpp\
    KanaiTajimiSpectrum.cpp\
    RPSDeodatis1996.cpp\
    RPSSLDoubleIndexFrequency.cpp\
    RPSSLRandomPhasesFromFile.cpp\
    RPSSLSingleIndexFrequency.cpp\
    RPSSLUniformRandomPhases.cpp\
    SeismicLab.cpp\
    SLCholeskyDecomposition.cpp\
    SLHorizontalUniformDistribution.cpp\
    SLVerticalUniformDistribution.cpp\

HEADERS += \
    AbrahamsonCoherence.h\
    BogdanoffGoldbergBernarModulation.h\
    CloughPenzienSpectrum.h\
    HarichandranVanmarcheCoherence.h\
    JenningEtAlModulation.h\
    KanaiTajimiSpectrum.h\
    RPSDeodatis1996.h\
    RPSSLDoubleIndexFrequency.h\
    RPSSLRandomPhasesFromFile.h\
    RPSSLSingleIndexFrequency.h\
    RPSSLUniformRandomPhases.h\
    SLCholeskyDecomposition.h\
    SLHorizontalUniformDistribution.h\
    SLVerticalUniformDistribution.h\
  

DISTFILES += seismicLab.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


