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
    RPSWindLabAPI.h\
    RPSWindLabAPIdefines.h\
    RPSWindLabFramework.h\
    RPSWindLabpluginAPI.h\
    RPSWindLabsimuData.h\
    RPS.h\
    ObjectDescription.h\
    IrpsWLMatrixTool.h\
    IrpsWLTableTool.h\
    IrpsWLUserDefinedRPSObject.h\
    IrpsWLCumulativeProbabilityDistribution.h\
    IrpsWLGustFactor.h\
    IrpsWLKurtosis.h\
    IrpsWLPeakFactor.h\
    IrpsWLProbabilityDensityFunction.h\
    IrpsWLRoughness.h\
    IrpsWLShearVelocityOfFlow.h\
    IrpsWLSkewness.h\
    IrpsWLStandardDeviation.h\
    IrpsWLTurbulenceIntensity.h\
    IrpsWLTurbulenceScale.h\
    IrpsWLVariance.h\
    IrpsWLWavePassageEffect.h\


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

