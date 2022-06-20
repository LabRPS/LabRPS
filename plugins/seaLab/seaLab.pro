QT += gui
QT += widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

DEFINES += SEALAB_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

################################################################################
### Dependencies                                                               #
################################################################################

contains(PRESET, linux_all_dynamic) {

  LIBS         +=  -libsealabapi
}

contains(PRESET, linux_static) {
  ### Link statically and dynamically against rest.
  LIBS         +=  -libsealabapi
}

contains(PRESET, linux_all_static) {
  ### mostly static linking, for self-contained binaries
  message(Build configuration: Linux all static)

  LIBS         += /usr/lib/libsealabapi.a
}

contains(PRESET, osx_dist) {
  # Uses HomeBrew supplied versions of the dependencies
  message(Build configuration: OSX Distro)

  LIBS         += -libsealabapi 
}

win32: {
  !mxe {
    ### Static linking mostly.
    message(Build configuration: Win32)

    isEmpty(APILIBPATH): APILIBPATH =E:/LabRPS/pluginapi

    INCLUDEPATH  += "$${APILIBPATH}/sealabapi"

    LIBS         += "$${APILIBPATH}/sealabapi/release/libsealabapi.a"
   }
}

SOURCES += \
    SeaLab.cpp\
    RPSSLUniformRandomPhases.cpp\
    minmaxvaluesdlg.cpp\
    RPSDeodatis1996.cpp\
    RPSSLRandomPhasesFromFile.cpp\
    SLHorizontalUniformDistribution.cpp\
    cslhorizontallocdistr.cpp\
    SLVerticalUniformDistribution.cpp\
    slvertdistrdialog.cpp\
    JonswapSpectrum.cpp\
    cjonswapspectrumdlg.cpp\
    RPSSLSingleIndexFrequency.cpp\
    RPSSLDoubleIndexFrequency.cpp\
    RPSUniformFrequencyDistribution.cpp\
    AbrahamsonCoherence.cpp\
    HarichandranVanmarcheCoherence.cpp\
    SLCholeskyDecomposition.cpp\
    BogdanoffGoldbergBernarModulation.cpp\
    JenningEtAlModulation.cpp\
    RPSSpreadingFunction1.cpp\
    RPSSpreadingFunction2.cpp\
    UnifDistrDirection.cpp\
    RPSDirectionalSpectrum.cpp\
    RPSCorrelationFunction.cpp\


HEADERS += \
    RPSSLUniformRandomPhases.h\
    minmaxvaluesdlg.h\
    RPSDeodatis1996.h\
    RPSSLRandomPhasesFromFile.h\
    SLHorizontalUniformDistribution.h\
    cslhorizontallocdistr.h\
    SLVerticalUniformDistribution.h\
    slvertdistrdialog.h\
    JonswapSpectrum.h\
    cjonswapspectrumdlg.h\
    RPSSLSingleIndexFrequency.h\
    RPSSLDoubleIndexFrequency.h\
    RPSUniformFrequencyDistribution.h\
    AbrahamsonCoherence.h\
    HarichandranVanmarcheCoherence.h\
    SLCholeskyDecomposition.h\
    BogdanoffGoldbergBernarModulation.h\
    JenningEtAlModulation.h\
    RPSSpreadingFunction1.h\
    RPSSpreadingFunction2.h\
    UnifDistrDirection.h\
    RPSDirectionalSpectrum.h\
    RPSCorrelationFunction.h\


FORMS  += minmaxvaluesdlg.ui\
          cslhorizontallocdistr.ui\
          slvertdistrdialog.ui\
          cjonswapspectrumdlg.ui\




DISTFILES += seaLab.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


