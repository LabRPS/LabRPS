QMAKE_PROJECT_DEPTH = 0
linux-g++-64: libsuff=64
QT -= gui

TARGET = rpsTools
TEMPLATE = lib
DEFINES += RPSTOOLS_LIBRARY
DEFINES += RPS_BUILDING_CORE

CONFIG += c++17
QMAKE_CXXFLAGS +=-Wall

################################################################################
### Dependencies                                                               #
################################################################################

contains(PRESET, linux_all_dynamic) {

  LIBS         += -lgsl -lgslcblas

}

contains(PRESET, linux_static) {
  ### Link statically and dynamically against rest.
  LIBS         += -lgsl -lgslcblas

}

contains(PRESET, linux_all_static) {
  ### mostly static linking, for self-contained binaries
  message(Build configuration: Linux all static)

  LIBS         += /usr/lib/libgsl.a /usr/lib/libgslcblas.a

}

contains(PRESET, osx_dist) {
  # Uses HomeBrew supplied versions of the dependencies
  message(Build configuration: OSX Distro)

  LIBS         += -lgsl -lgslcblas

}

win32: {
  !mxe {
    ### Static linking mostly.
    message(Build configuration: Win32)

    isEmpty(LIBPATH): LIBPATH = E:/LabRPS/3rdparty

    INCLUDEPATH  += "$${LIBPATH}/gsl/include"

    LIBS         += "$${LIBPATH}/gsl/lib/libgsl.a"
    LIBS         += "$${LIBPATH}/gsl/lib/libgslcblas.a"

   }
}

mxe {
  ### Mingw cross compilation environment on Linux.
  message(Build configuration: Mxe all static)

  LIBS           += -lgsl -lgslcblas
}
SOURCES += \
    rpsTools/RPSTools.cpp\
    rpsTools/src/general/CholeskyDecomposition.cpp\
    rpsTools/src/general/UniformRandomPhaseMatrixGenerator.cpp\
    rpsTools/src/general/AvailableWindows.cpp\
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
    rpsTools/src/general/AvailableWindows.h\
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

