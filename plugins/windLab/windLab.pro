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
  LIBS         += -lGLU -lgsl -lgslcblas -libsealabapi -libseismiclabapi -libwindlabapi -librpsTools

}

contains(PRESET, linux_static) {
  ### Link statically and dynamically against rest.
  LIBS         +=  -libwindlabapi
  LIBS         += -lgsl -lgslcblas -lGLU -libsealabapi -libseismiclabapi -libwindlabapi -librpsTools

}

contains(PRESET, linux_all_static) {
  ### mostly static linking, for self-contained binaries
  message(Build configuration: Linux all static)

  LIBS         += /usr/lib/libwindlabapi.a
  LIBS         += /usr/lib/libgsl.a /usr/lib/libgslcblas.a /usr/lib/librpsTools.a

}

contains(PRESET, osx_dist) {
  # Uses HomeBrew supplied versions of the dependencies
  message(Build configuration: OSX Distro)

  LIBS         += -libwindlabapi
  LIBS         += -lgsl -lgslcblas -libsealabapi -libseismiclabapi -libwindlabapi -librpsTools
 
}

win32: {
  !mxe {
    ### Static linking mostly.
    message(Build configuration: Win32)
    
    isEmpty(LIBPATH): LIBPATH = E:/LabRPS/3rdparty
    isEmpty(APILIBPATH): APILIBPATH =E:/LabRPS/pluginapi
    isEmpty(LIBRARIESPATH): LIBRARIESPATH = E:/LabRPS/libraries

    INCLUDEPATH  += "$${APILIBPATH}/windlabapi"
    INCLUDEPATH  += "$${LIBPATH}/gsl/include"
    INCLUDEPATH  += "$${LIBRARIESPATH}/rpsTools/rpsTools/src/windVelocity/spectrum"
    INCLUDEPATH  += "$${LIBRARIESPATH}/rpsTools"

    LIBS         += "$${APILIBPATH}/windlabapi/debug/libwindlabapi.a"
    LIBS         += "$${LIBPATH}/gsl/lib/libgsl.a"
    LIBS         += "$${LIBPATH}/gsl/lib/libgslcblas.a"
    LIBS         += "$${LIBRARIESPATH}/rpsTools/debug/librpsTools.a"

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
    widgets/meanwindlogprofildialog.cpp\
    widgets/meanwindpowerprofildialog.cpp\
    widgets/davenportcoherencedialog.cpp\
    widgets/wlvertdistrdialog.cpp\
    widgets/cwlhorizontallocdistr.cpp\
    widgets/kaimalpsdshearvelocitydialog.cpp\
    widgets/expomodulationdialog.cpp\
    widgets/sinemodulationdialog.cpp\
    widgets/threeparamodulationdialog.cpp\
    widgets/generaldistributiondialog.cpp\
    GeneralSpatialDistribution.cpp\
    widgets/minmaxvaluesdlg.cpp\
    RPSKaimalAcrossSpectr.cpp\
    RPSKaimalVerticalSpectr.cpp\
    RPSDavenportSpectrum.cpp\
    RPSHarrisSpectrum.cpp\
    RPSSimuAlongWindSpectrum.cpp\
    RPSSimuAcrossWindSpectrum.cpp\
    RPSSimuVerticalWindSpectrum.cpp\
    RPSvonKarmanAlongWindSpectrum.cpp\
    RPSvonKarmanAcrossWindSpectrum.cpp\
    RPSvonKarmanVerticalWindSpectrum.cpp\
    widgets/vonKarmanpsdinputsdialog.cpp\
    widgets/meanwindDHprofildialog.cpp\
    RPSDHLowProfile.cpp\
    myWidgets/IconLoader.cpp\
    myWidgets/RPSAlongWindKaimalDialog.cpp\

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
    widgets/meanwindlogprofildialog.h\
    widgets/meanwindpowerprofildialog.h\
    widgets/davenportcoherencedialog.h\
    widgets/wlvertdistrdialog.h\
    widgets/cwlhorizontallocdistr.h\
    widgets/kaimalpsdshearvelocitydialog.h\
    widgets/expomodulationdialog.h\
    widgets/sinemodulationdialog.h\
    widgets/threeparamodulationdialog.h\
    widgets/generaldistributiondialog.h\
    GeneralSpatialDistribution.h\
    widgets/minmaxvaluesdlg.h\
    RPSKaimalAcrossSpectr.h\
    RPSKaimalVerticalSpectr.h\
    RPSDavenportSpectrum.h\
    RPSHarrisSpectrum.h\
    RPSSimuAlongWindSpectrum.h\
    RPSSimuAcrossWindSpectrum.h\
    RPSSimuVerticalWindSpectrum.h\
    RPSvonKarmanAlongWindSpectrum.h\
    RPSvonKarmanAcrossWindSpectrum.h\
    RPSvonKarmanVerticalWindSpectrum.h\
    widgets/vonKarmanpsdinputsdialog.h\
    widgets/meanwindDHprofildialog.h\
    RPSDHLowProfile.h\
    myWidgets/IconLoader.h\
    myWidgets/RPSAlongWindKaimalDialog.h\

FORMS  += widgets/meanwindlogprofildialog.ui\
          widgets/meanwindpowerprofildialog.ui\
          widgets/davenportcoherencedialog.ui\
          widgets/wlvertdistrdialog.ui\
          widgets/cwlhorizontallocdistr.ui\
          widgets/kaimalpsdshearvelocitydialog.ui\
          widgets/expomodulationdialog.ui\
          widgets/sinemodulationdialog.ui\
          widgets/threeparamodulationdialog.ui\
          widgets/generaldistributiondialog.ui\
          widgets/minmaxvaluesdlg.ui\
          widgets/vonKarmanpsdinputsdialog.ui\
          widgets/meanwindDHprofildialog.ui\
          myWidgets/RPSAlongWindKaimalDialog.ui\


###################### ICONS ################################################
RESOURCES      += data/icons.qrc

DISTFILES += windLab.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


