#include "globals.h"

#include <QDate>
#include <QIcon>
#include <QMessageBox>
#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>
#include <QtDebug>

const int LabRPS::LabRPS_versionNo = 00012023;
const char* LabRPS::LabRPS_version = "0.001";
const char* LabRPS::LabRPS_Windlab_api_version = "0.001";
const char* LabRPS::LabRPS_Windlab_plugin_api_version = "0.001";
const char* LabRPS::LabRPS_UserDefinedPhenomenon_api_version = "0.001";
const char* LabRPS::LabRPS_UserDefinedPhenomenon_plugin_api_version = "0.001";
const char* LabRPS::extra_version = "stable";
const QDate LabRPS::release_date =
    QDate::fromString(QString("01-01-2023"), "dd-MM-yyyy");
const char* LabRPS::homepage_Uri = "https://labrps.com/";
const char* LabRPS::wiki_Uri = "https://wiki.labrps.com/";
const char* LabRPS::forum_Uri =
    "https://labrps.com/boards/";
const char* LabRPS::bugreport_Uri =
    "https://github.com/LabRPS/LabRPS/issues/new";
const char* LabRPS::download_Uri =
    "https://github.com/LabRPS/LabRPS/";

// rps phenomena
  QString LabRPS::rpsPhenomenonWindVelocity = "Wind Velocity";
  QString LabRPS::rpsPhenomenonSeaSurface = "Sea Surface";
  QString LabRPS::rpsPhenomenonSeismicGroundMotion = "Seismic Ground Motion";
  QString LabRPS::rpsPhenomenonUserDefined = "User Defined Phenomenon";

  // object groups
  QString LabRPS::objGroupLocationDistribution = "Location Distributions";
  QString LabRPS::objGroupMeanWindProfile = "Mean Wind Profiles";
  QString LabRPS::objGroupAlongWindSpectrum = "Along Wind Spectrum";
  QString LabRPS::objGroupVerticalWindSpectrum = "Vertical Wind Spectrum";
  QString LabRPS::objGroupAcrossWindSpectrum = "Across Wind Spectrum";
  QString LabRPS::objGroupSpectrumDecompositionMethod = "Spectrum Decomposition Method";
  QString LabRPS::objGroupCoherenceFunction = "Coherence Function";
  QString LabRPS::objGroupSimulationMethod = "Simulation Method";
  QString LabRPS::objGroupFrequencyDistribution = "Frequency Distribution";
  QString LabRPS::objGroupRandomnessProvider = "Randomness Provider";
  QString LabRPS::objGroupModulationFunction = "Modulation Function";
  QString LabRPS::objGroupCorrelationFunction = "Correlation Function";
  QString LabRPS::objGroupTableTool = "Table Tool";
  QString LabRPS::objGroupMatrixTool = "Matrix Tool";
  QString LabRPS::objGroupUserDefinedRPSObject = "User Defined RPS object";
  QString LabRPS::objGroupUserDefinedPhenomenonObject = "User Defined Phenomenon";
  QString LabRPS::objGroupCumulativeProbabilityDistribution = "Cumulative Probability Distribution";
  QString LabRPS::objGroupGustFactor = "Gust Factor";
  QString LabRPS::objGroupKurtosis = "Kurtosis";
  QString LabRPS::objGroupPeakFactor = "Peak Factor";
  QString LabRPS::objGroupProbabilityDensityFunction = "Probability Density Function";
  QString LabRPS::objGroupRoughness = "Roughness";
  QString LabRPS::objGroupShearVelocityOfFlow = "Shear Velocity of Flow";
  QString LabRPS::objGroupSkewness = "Skewness";
  QString LabRPS::objGroupStandardDeviation = "Standard Deviation";
  QString LabRPS::objGroupTurbulenceIntensity = "Turbulence Intensity";
  QString LabRPS::objGroupTurbulenceScale = "Turbulence Scale";
  QString LabRPS::objGroupVariance = "Variance";
  QString LabRPS::objGroupWavePassageEffect = "Wave Passage Effect";


  QString LabRPS::ComputeCrossCoherenceVectorF = "ComputeCrossCoherenceVectorF";
  QString LabRPS::ComputeCrossCoherenceVectorT = "ComputeCrossCoherenceVectorT";
	QString LabRPS::ComputeCrossCorrelationVectorT = "ComputeCrossCorrelationVectorT";
	QString LabRPS::ComputeFrequenciesVectorF = "ComputeFrequenciesVectorF";
	QString LabRPS::ComputeMeanWindSpeedVectorP = "ComputeMeanWindSpeedVectorP";
    QString LabRPS::ComputeMeanWindSpeedVectorT = "ComputeMeanWindSpeedVectorT";
	QString LabRPS::ComputeModulationVectorT = "ComputeModulationVectorT";
    QString LabRPS::ComputeModulationVectorP = "ComputeModulationVectorP";
	QString LabRPS::ComputeDecomposedCrossSpectrumVectorF = "ComputeDecomposedCrossSpectrumVectorF";
    QString LabRPS::ComputeDecomposedCrossSpectrumVectorT = "ComputeDecomposedCrossSpectrumVectorT";

	QString LabRPS::Simulate = "Simulate";
	QString LabRPS::SimulateInLargeScaleMode = "SimulateInLargeScaleMode";
    QString LabRPS::ComputeXAutoSpectrumVectorF = "ComputeXAutoSpectrumVectorF";
    QString LabRPS::ComputeYAutoSpectrumVectorF = "ComputeYAutoSpectrumVectorF";
    QString LabRPS::ComputeZAutoSpectrumVectorF = "ComputeZAutoSpectrumVectorF";
    QString LabRPS::ComputeXAutoSpectrumVectorT = "ComputeXAutoSpectrumVectorT";
    QString LabRPS::ComputeYAutoSpectrumVectorT = "ComputeYAutoSpectrumVectorT";
    QString LabRPS::ComputeZAutoSpectrumVectorT = "ComputeZAutoSpectrumVectorT";
    QString LabRPS::UserDefinedRPSObjectCompute = "UserDefinedRPSObjectCompute";

QString LabRPS::ComputeCDFVectorP = "ComputeCDFVectorP";
QString LabRPS::ComputeGustFactorVectorP = "ComputeGustFactorVectorP";
QString LabRPS::ComputeKurtosisVectorP = "ComputeKurtosisVectorP";
QString LabRPS::ComputePeakFactorVectorP = "ComputePeakFactorVectorP";
QString LabRPS::ComputePDFVectorP = "ComputePDFVectorP";
QString LabRPS::ComputeRoughnessVectorP = "ComputeRoughnessVectorP";
QString LabRPS::ComputeShearVelocityOfFlowVectorP = "ComputeShearVelocityOfFlowVectorP";
QString LabRPS::ComputeSkewnessVectorP = "ComputeSkewnessVectorP";
QString LabRPS::ComputeStandardDeviationVectorP = "ComputeStandardDeviationVectorP";
QString LabRPS::ComputeTurbulenceIntensityVectorP = "ComputeTurbulenceIntensityVectorP";
QString LabRPS::ComputeTurbulenceScaleVectorP = "ComputeTurbulenceScaleVectorP";
QString LabRPS::ComputeVarianceVectorP = "ComputeVarianceVectorP";
QString LabRPS::ComputeWavePassageEffectVectorF = "ComputeWavePassageEffectVectorF";
QString LabRPS::ComputeWavePassageEffectVectorT = "ComputeWavePassageEffectVectorT";


QStringList LabRPS::locales_ = QStringList();

int LabRPS::version() { return LabRPS_versionNo; }

QString LabRPS::schemaVersion() {
  return "LabRPS " + QString::number((version() & 0xFF0000) >> 16) + "." +
         QString::number((version() & 0x00FF00) >> 8) + "." +
         QString::number(version() & 0x0000FF);
}

QString LabRPS::versionString() { return LabRPS_version; }
QString LabRPS::windLabAPIVersionString() { return LabRPS_Windlab_api_version; }
QString LabRPS::windLabPluginAPIVersionString() { return LabRPS_Windlab_plugin_api_version; }
QString LabRPS::userDefinedPhenomenonAPIVersionString() { return LabRPS_UserDefinedPhenomenon_api_version; }
QString LabRPS::userDefinedPhenomenonPluginAPIVersionString() { return LabRPS_UserDefinedPhenomenon_plugin_api_version; }


QString LabRPS::extraVersion() { return QString(extra_version); }

QString LabRPS::releaseDateString() {
  return release_date.toString("dd-MM-yyyy");
}

QDate LabRPS::releaseDate() { return release_date; }

QString LabRPS::originalAuthor() { return "LabRPS Team"; }

QString LabRPS::originalAuthorWithMail() {
  return "LabRPS Team: <labrps@glabrps.com";
}

QStringList LabRPS::getLocales() { return locales_; }

void LabRPS::setLocales(QStringList locales) { locales_ = locales; }

QString LabRPS::enumValueToString(int key, const QString& enum_name) {
  int index = staticMetaObject.indexOfEnumerator(enum_name.toUtf8());
  if (index == -1) return QString("invalid");
  QMetaEnum meta_enum = staticMetaObject.enumerator(index);
  return QString(meta_enum.valueToKey(key));
}

int LabRPS::enumStringToValue(const QString& string,
                                 const QString& enum_name) {
  int index = staticMetaObject.indexOfEnumerator(enum_name.toUtf8());
  if (index == -1) return -1;
  QMetaEnum meta_enum = staticMetaObject.enumerator(index);
  return meta_enum.keyToValue(string.toUtf8());
}
