QT += gui
QT += widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

DEFINES += WINDLAB_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

################################################################################
### Dependencies                                                               #
################################################################################

contains(PRESET, linux_all_dynamic) {

  LIBS         +=  -libwindlabapi
  LIBS         += -lGLU -lgsl -lgslcblas -libsealabapi -libseismiclabapi -libwindlabapi

}

contains(PRESET, linux_static) {
  ### Link statically and dynamically against rest.
  LIBS         +=  -libwindlabapi
  LIBS         += -lgsl -lgslcblas -lGLU -libsealabapi -libseismiclabapi -libwindlabapi

}

contains(PRESET, linux_all_static) {
  ### mostly static linking, for self-contained binaries
  message(Build configuration: Linux all static)

  LIBS         += /usr/lib/libwindlabapi.a
  LIBS         += /usr/lib/libgsl.a /usr/lib/libgslcblas.a

}

contains(PRESET, osx_dist) {
  # Uses HomeBrew supplied versions of the dependencies
  message(Build configuration: OSX Distro)

  LIBS         += -libwindlabapi
  LIBS         += -lgsl -lgslcblas -libsealabapi -libseismiclabapi -libwindlabapi
 
}

win32: {
  !mxe {
    ### Static linking mostly.
    message(Build configuration: Win32)
    
    isEmpty(LIBPATH): LIBPATH = E:/LabRPS/3rdparty
    isEmpty(APILIBPATH): APILIBPATH =E:/LabRPS/pluginapi

    INCLUDEPATH  += "$${APILIBPATH}/windlabapi"
    INCLUDEPATH  += "$${LIBPATH}/gsl/include"

    LIBS         += "$${APILIBPATH}/windlabapi/release/libwindlabapi.a"
    LIBS         += "$${LIBPATH}/gsl/lib/libgsl.a"
    LIBS         += "$${LIBPATH}/gsl/lib/libgslcblas.a"
   }
}

mxe {
  ### Mingw cross compilation environment on Linux.
  message(Build configuration: Mxe all static)
  
  LIBS           +=  -mwindows -lgsl -lgslcblas libsealabapi libseismiclabapi libwindlabapi

}


SOURCES += \
    CholeskyDecomposition.cpp\
    ExpoModulation.cpp\
    RPSDavenportCoherence.cpp\
    RPSDeodatis1987.cpp\
    RPSDoubleIndexFrequency.cpp\
    RPSKaimalSpectr.cpp\
    RPSLogarithmicLowProfile.cpp\
    RPSRandomPhasesFromFile.cpp\
    RPSSingleIndexFrequency.cpp\
    RPSUniformRandomPhases.cpp\
    RPSWLPowerLowProfile.cpp\
    SineModulation.cpp\
    ThreeParaModulation.cpp\
    WindLab.cpp\
    WLHorizontalUniformDistribution.cpp\
    WLVerticalUniformDistribution.cpp\
    meanwindlogprofildialog.cpp\
    meanwindpowerprofildialog.cpp\
    davenportcoherencedialog.cpp\
    wlvertdistrdialog.cpp\
    cwlhorizontallocdistr.cpp\
    kaimalpsdshearvelocitydialog.cpp\
    expomodulationdialog.cpp\
    sinemodulationdialog.cpp\
    threeparamodulationdialog.cpp\
    generaldistributiondialog.cpp\
    GeneralSpatialDistribution.cpp\
    minmaxvaluesdlg.cpp\

HEADERS += \
    CholeskyDecomposition.h\
    ExpoModulation.h\
    RPSDavenportCoherence.h\
    RPSDeodatis1987.h\
    RPSDoubleIndexFrequency.h\
    RPSKaimalSpectr.h\
    RPSLogarithmicLowProfile.h\
    RPSRandomPhasesFromFile.h\
    RPSSingleIndexFrequency.h\
    RPSUniformRandomPhases.h\
    RPSWLPowerLowProfile.h\
    SineModulation.h\
    ThreeParaModulation.h\
    WLHorizontalUniformDistribution.h\
    WLVerticalUniformDistribution.h\
    meanwindlogprofildialog.h\
    meanwindpowerprofildialog.h\
    davenportcoherencedialog.h\
    wlvertdistrdialog.h\
    cwlhorizontallocdistr.h\
    kaimalpsdshearvelocitydialog.h\
    expomodulationdialog.h\
    sinemodulationdialog.h\
    threeparamodulationdialog.h\
    generaldistributiondialog.h\
    GeneralSpatialDistribution.h\
    minmaxvaluesdlg.h\

FORMS  += meanwindlogprofildialog.ui\
          meanwindpowerprofildialog.ui\
          davenportcoherencedialog.ui\
          wlvertdistrdialog.ui\
          cwlhorizontallocdistr.ui\
          kaimalpsdshearvelocitydialog.ui\
          expomodulationdialog.ui\
          sinemodulationdialog.ui\
          threeparamodulationdialog.ui\
          generaldistributiondialog.ui\
          minmaxvaluesdlg.ui\



DISTFILES += windLab.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


