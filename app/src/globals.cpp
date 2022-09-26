/***************************************************************************
    File                 : globals.cpp
    Description          : Definition of global constants and enums
    --------------------------------------------------------------------
    Copyright            : (C) 2006-2009 Tilman Benkert (thzs*gmx.net)
    Copyright            : (C) 2006-2007 Ion Vasilief (ion_vasilief*yahoo.fr)
                           (replace * with @ in the email addresses)

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/

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


  QString LabRPS::ComputeCrossCoherenceVectorF = "ComputeCrossCoherenceVectorF";
	QString LabRPS::ComputeCrossCorrelationVectorT = "ComputeCrossCorrelationVectorT";
	QString LabRPS::ComputeCrossCorrelationVectorP = "ComputeCrossCorrelationVectorP";
	QString LabRPS::ComputeFrequenciesVectorF = "ComputeFrequenciesVectorF";
	QString LabRPS::ComputeMeanWindSpeedVectorP = "ComputeMeanWindSpeedVectorP";
	QString LabRPS::ComputeMeanWindSpeedVectorT = "ComputeMeanWindSpeedVectorT";
	QString LabRPS::ComputeModulationVectorT = "ComputeModulationVectorT";
	QString LabRPS::ComputeModulationVectorF = "ComputeModulationVectorF";
	QString LabRPS::ComputeModulationVectorP = "ComputeModulationVectorP";
	QString LabRPS::ComputeDecomposedCrossSpectrumVectorF = "ComputeDecomposedCrossSpectrumVectorF";
	QString LabRPS::ComputeDecomposedCrossSpectrumVectorT = "ComputeDecomposedCrossSpectrumVectorT";
	QString LabRPS::ComputeDecomposedCrossSpectrumVectorP = "ComputeDecomposedCrossSpectrumVectorP";
	QString LabRPS::Simulate = "Simulate";
	QString LabRPS::SimulateInLargeScaleMode = "SimulateInLargeScaleMode";
	QString LabRPS::ComputeXCrossSpectrumVectorF = "ComputeXCrossSpectrumVectorF";
	QString LabRPS::ComputeXCrossSpectrumVectorT = "ComputeXCrossSpectrumVectorT";
	QString LabRPS::ComputeXCrossSpectrumVectorP = "ComputeXCrossSpectrumVectorP";
	QString LabRPS::ComputeYCrossSpectrumVectorF = "ComputeYCrossSpectrumVectorF";
	QString LabRPS::ComputeYCrossSpectrumVectorT = "ComputeYCrossSpectrumVectorT";
	QString LabRPS::ComputeYCrossSpectrumVectorP = "ComputeYCrossSpectrumVectorP";
	QString LabRPS::ComputeZCrossSpectrumVectorF = "ComputeZCrossSpectrumVectorF";
	QString LabRPS::ComputeZCrossSpectrumVectorT = "ComputeZCrossSpectrumVectorT";
	QString LabRPS::ComputeZCrossSpectrumVectorP = "ComputeZCrossSpectrumVectorP";
    QString LabRPS::UserDefinedRPSObjectComputePFT = "UserDefinedRPSObjectComputePFT";



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
