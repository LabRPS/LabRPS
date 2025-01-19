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
#include "PreCompiled.h"

#include "RPSGlobals.h"

#include <QDate>
#include <QIcon>
#include <QMessageBox>
#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>
#include <QtDebug>

using namespace Gui;

const int RPSGlobals::RPS_versionNo = 1022022;
const char* RPSGlobals::RPS_version = "1.02";
const char* RPSGlobals::extra_version = "stable";
const QDate RPSGlobals::release_date =
    QDate::fromString(QString::fromLatin1("18-01-2022"), QString::fromLatin1("dd-MM-yyyy"));
const char* RPSGlobals::homepage_Uri = "https://labrps.com/";
const char* RPSGlobals::manual_Uri = "https://alphaplot.sourceforge.io/wiki";
const char* RPSGlobals::forum_Uri = "https://sourceforge.net/p/alphaplot/discussion/";
const char* RPSGlobals::bugreport_Uri = "https://github.com/narunlifescience/AlphaPlot/issues/new";
const char* RPSGlobals::download_Uri ="https://sourceforge.net/projects/alphaplot/";
const char* RPSGlobals::wiki_Uri = "https://wiki.labrps.com/";

//phenomenon
QString RPSGlobals::rpsPhenomenonWindVelocity = tr("Wind Velocity");
QString RPSGlobals::rpsPhenomenonSeaSurface = tr("Sea Surface");
QString RPSGlobals::rpsPhenomenonSeismicGroundMotion = tr("Seismic Ground Motion");
QString RPSGlobals::rpsPhenomenonUserDefined = tr("User Defined Phenomenon");

// object groups
QString RPSGlobals::objGroupLocationDistribution = tr("Location Distribution");
QString RPSGlobals::objGroupMeanWindProfile = tr("Mean Wind Profile");
QString RPSGlobals::objGroupAlongWindSpectrum = tr("Along Wind Spectrum");
QString RPSGlobals::objGroupVerticalWindSpectrum = tr("Vertical Wind Spectrum");
QString RPSGlobals::objGroupAcrossWindSpectrum = tr("Across Wind Spectrum");
QString RPSGlobals::objGroupSpectrumDecompositionMethod = tr("Spectrum Decomposition Method");
QString RPSGlobals::objGroupCoherenceFunction = tr("Coherence Function");
QString RPSGlobals::objGroupSimulationMethod = tr("Simulation Method");
QString RPSGlobals::objGroupFrequencyDistribution = tr("Frequency Distribution");
QString RPSGlobals::objGroupRandomnessProvider = tr("Randomness Provider");
QString RPSGlobals::objGroupModulationFunction = tr("Modulation Function");
QString RPSGlobals::objGroupCorrelationFunction = tr("Correlation Function");
QString RPSGlobals::objGroupTableTool = tr("Table Tool");
QString RPSGlobals::objGroupMatrixTool = tr("Matrix Tool");
QString RPSGlobals::objGroupUserDefinedRPSObject = tr("User Defined RPS object");
QString RPSGlobals::objGroupUserObject = tr("User Defined Phenomenon");
QString RPSGlobals::objGroupCumulativeProbabilityDistribution = tr("Cumulative Probability Distribution");
QString RPSGlobals::objGroupGustFactor = tr("Gust Factor");
QString RPSGlobals::objGroupKurtosis = tr("Kurtosis");
QString RPSGlobals::objGroupPeakFactor = tr("Peak Factor");
QString RPSGlobals::objGroupProbabilityDensityFunction = tr("Probability Density Function");
QString RPSGlobals::objGroupRoughness = tr("Roughness");
QString RPSGlobals::objGroupShearVelocityOfFlow = tr("Shear Velocity of Flow");
QString RPSGlobals::objGroupSkewness = tr("Skewness");
QString RPSGlobals::objGroupStandardDeviation = tr("Standard Deviation");
QString RPSGlobals::objGroupTurbulenceIntensity = tr("Turbulence Intensity");
QString RPSGlobals::objGroupTurbulenceScale = tr("Turbulence Scale");
QString RPSGlobals::objGroupVariance = tr("Variance");
QString RPSGlobals::objGroupWavePassageEffect = tr("Wave Passage Effect");

QString RPSGlobals::docRPSFeatures = tr("RPS Features");
QString RPSGlobals::docSimulations = tr("Simulations");



QString RPSGlobals::ComputeCrossCoherenceVectorF = tr("ComputeCrossCoherenceVectorF");
QString RPSGlobals::ComputeCrossCoherenceVectorT = tr("ComputeCrossCoherenceVectorT");
QString RPSGlobals::ComputeCrossCorrelationVectorT = tr("ComputeCrossCorrelationVectorT");
QString RPSGlobals::ComputeFrequenciesVectorF = tr("ComputeFrequenciesVectorF");
QString RPSGlobals::ComputeMeanWindSpeedVectorP = tr("ComputeMeanWindSpeedVectorP");
QString RPSGlobals::ComputeMeanWindSpeedVectorT = tr("ComputeMeanWindSpeedVectorT");
QString RPSGlobals::ComputeModulationVectorT = tr("ComputeModulationVectorT");
QString RPSGlobals::ComputeModulationVectorP = tr("ComputeModulationVectorP");
QString RPSGlobals::ComputeDecomposedCrossSpectrumVectorF = tr("ComputeDecomposedCrossSpectrumVectorF");
QString RPSGlobals::ComputeDecomposedCrossSpectrumVectorT = tr("ComputeDecomposedCrossSpectrumVectorT");

QString RPSGlobals::Simulate = QString::fromLatin1("Simulate");
QString RPSGlobals::ComputeXCrossSpectrumVectorF = QString::fromLatin1("ComputeXCrossSpectrumVectorF");
QString RPSGlobals::ComputeYCrossSpectrumVectorF = QString::fromLatin1("ComputeYCrossSpectrumVectorF");
QString RPSGlobals::ComputeZCrossSpectrumVectorF = QString::fromLatin1("ComputeZCrossSpectrumVectorF");
QString RPSGlobals::ComputeXCrossSpectrumVectorT = QString::fromLatin1("ComputeXCrossSpectrumVectorT");
QString RPSGlobals::ComputeYCrossSpectrumVectorT = QString::fromLatin1("ComputeYCrossSpectrumVectorT");
QString RPSGlobals::ComputeZCrossSpectrumVectorT = QString::fromLatin1("ComputeZCrossSpectrumVectorT");
QString RPSGlobals::UserDefinedRPSObjectCompute = QString::fromLatin1("UserDefinedRPSObjectCompute");

QString RPSGlobals::ComputeCPDVectorX = QString::fromLatin1("ComputeCPDVectorX");
QString RPSGlobals::ComputeGustFactorVectorP = QString::fromLatin1("ComputeGustFactorVectorP");
QString RPSGlobals::ComputeKurtosisVectorP = QString::fromLatin1("ComputeKurtosisVectorP");
QString RPSGlobals::ComputePeakFactorVectorP = QString::fromLatin1("ComputePeakFactorVectorP");
QString RPSGlobals::ComputePDFVectorX = QString::fromLatin1("ComputePDFVectorX");
QString RPSGlobals::ComputeRoughnessVectorP = QString::fromLatin1("ComputeRoughnessVectorP");
QString RPSGlobals::ComputeShearVelocityOfFlowVectorP = QString::fromLatin1("ComputeShearVelocityOfFlowVectorP");
QString RPSGlobals::ComputeSkewnessVectorP = QString::fromLatin1("ComputeSkewnessVectorP");
QString RPSGlobals::ComputeStandardDeviationVectorP = QString::fromLatin1("ComputeStandardDeviationVectorP");
QString RPSGlobals::ComputeTurbulenceIntensityVectorP = QString::fromLatin1("ComputeTurbulenceIntensityVectorP");
QString RPSGlobals::ComputeTurbulenceScaleVectorP = QString::fromLatin1("ComputeTurbulenceScaleVectorP");
QString RPSGlobals::ComputeVarianceVectorP = QString::fromLatin1("ComputeVarianceVectorP");
QString RPSGlobals::ComputeWavePassageEffectVectorF = QString::fromLatin1("ComputeWavePassageEffectVectorF");
QString RPSGlobals::ComputeWavePassageEffectVectorT = QString::fromLatin1("ComputeWavePassageEffectVectorT");

QString RPSGlobals::ComputeGustFactorVectorT = QString::fromLatin1("ComputeGustFactorVectorT");
QString RPSGlobals::ComputeKurtosisVectorT = QString::fromLatin1("ComputeKurtosisVectorT");
QString RPSGlobals::ComputePeakFactorVectorT = QString::fromLatin1("ComputePeakFactorVectorT");
QString RPSGlobals::ComputeRoughnessVectorT = QString::fromLatin1("ComputeRoughnessVectorT");
QString RPSGlobals::ComputeShearVelocityOfFlowVectorT = QString::fromLatin1("ComputeShearVelocityOfFlowVectorT");
QString RPSGlobals::ComputeSkewnessVectorT = QString::fromLatin1("ComputeSkewnessVectorT");
QString RPSGlobals::ComputeStandardDeviationVectorT = QString::fromLatin1("ComputeStandardDeviationVectorT");
QString RPSGlobals::ComputeTurbulenceIntensityVectorT = QString::fromLatin1("ComputeTurbulenceIntensityVectorT");
QString RPSGlobals::ComputeTurbulenceScaleVectorT = QString::fromLatin1("ComputeTurbulenceScaleVectorT");
QString RPSGlobals::ComputeVarianceVectorT = QString::fromLatin1("ComputeVarianceVectorT");

QStringList RPSGlobals::locales_ = QStringList();

int RPSGlobals::version() { return RPS_versionNo; }

QString RPSGlobals::schemaVersion() {
  return QString::fromLatin1("AlphaPlot ") + QString::number((version() & 0xFF0000) >> 16) + QString::fromLatin1(".") +
         QString::number((version() & 0x00FF00) >> 8) + QString::fromLatin1(".") +
         QString::number(version() & 0x0000FF);
}

QString RPSGlobals::versionString() {return QString::fromLatin1(RPS_version); }

QString RPSGlobals::extraVersion() {return QString::fromLatin1(extra_version); }

QString RPSGlobals::releaseDateString() {
  return release_date.toString(QString::fromLatin1("dd-MM-yyyy"));
}

QDate RPSGlobals::releaseDate() { return release_date; }

QString RPSGlobals::originalAuthor() {return QString::fromLatin1("Koffi Daniel"); }

QString RPSGlobals::originalAuthorWithMail() {
  return QString::fromLatin1("Koffi Daniel: <kfdani@labrps.com");
}

QStringList RPSGlobals::getLocales() { return locales_; }

void RPSGlobals::setLocales(QStringList locales) { locales_ = locales; }

QString RPSGlobals::enumValueToString(int key, const QString& enum_name) {
  int index = staticMetaObject.indexOfEnumerator(enum_name.toUtf8());
    if (index == -1) return QString::fromLatin1("invalid");
  QMetaEnum meta_enum = staticMetaObject.enumerator(index);
  return QString::fromLatin1(meta_enum.valueToKey(key));
}

int RPSGlobals::enumStringToValue(const QString& string,
                                 const QString& enum_name) {
  int index = staticMetaObject.indexOfEnumerator(enum_name.toUtf8());
  if (index == -1) return -1;
  QMetaEnum meta_enum = staticMetaObject.enumerator(index);
  return meta_enum.keyToValue(string.toUtf8());
}


bool RPSGlobals::getObjects(std::map<const QString, QString>& map, QStringList& lstObject, QString pluginName)
{
    if (!map.empty())
    {
        // Iterate though the map and show all the registed objects
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (!it->first.isEmpty())
            {
                if (it->second == pluginName)
                {
                    lstObject.append(it->first);
                }
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}


bool RPSGlobals::updateObjectsMap(std::map<const QString, QString>& map, const QString& lstObject)
{
    if (!map.empty())
    {
        if (map.find(lstObject) != map.end())
        {
            map.erase(lstObject);
        }
    }

    return true;
}

bool RPSGlobals::updateObjectToSkipMap(std::map<const QString, QString>& map, const QString name, const QString pluginName)
{
    map[name] = pluginName;
    return true;
}

bool RPSGlobals::isThisObjectGroupPluggedInThisPlugin(const std::map<const QString, QString>& map, const QString& pluginName)
{
    if (!map.empty())
    {
        //go through the map
        for (auto& it : map)
        {
            //if mapped value is pluginName
            //then return true
            if (it.second == pluginName)
            {
                return true;
            }
        }
    }

    return false;
}

bool RPSGlobals::isThisObjectInstalled(std::map<const QString, QString>& map, QString& object)
{
    if (!map.empty())
    {
        if (map.find(object) != map.end())
        {
            return true;
        }
    }

    return false;
}