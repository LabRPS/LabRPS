/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>         *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"
#include "SeaLabUtils.h"


using namespace SeaLab;

//phenomenon
QString SeaLabUtils::rpsPhenomenonWindVelocity = QString::fromLatin1("Sea Surface");

// object groups
QString SeaLabUtils::objGroupLocationDistribution =  QString::fromLatin1("Location Distribution");
QString SeaLabUtils::objGroupMeanAccelerationProfile =  QString::fromLatin1("Mean Acceleration");
QString SeaLabUtils::objGroupSpectrum =  QString::fromLatin1("Spectrum");
QString SeaLabUtils::objGroupSpectrumDecompositionMethod =  QString::fromLatin1("Spectrum Decomposition Method");
QString SeaLabUtils::objGroupCoherenceFunction =  QString::fromLatin1("Coherence Function");
QString SeaLabUtils::objGroupSimulationMethod =  QString::fromLatin1("Simulation Method");
QString SeaLabUtils::objGroupFrequencyDistribution =  QString::fromLatin1("Frequency Distribution");
QString SeaLabUtils::objGroupRandomnessProvider =  QString::fromLatin1("Randomness Provider");
QString SeaLabUtils::objGroupModulationFunction =  QString::fromLatin1("Modulation Function");
QString SeaLabUtils::objGroupCorrelationFunction =  QString::fromLatin1("Correlation Function");
QString SeaLabUtils::objGroupTableTool =  QString::fromLatin1("Table Tool");
QString SeaLabUtils::objGroupMatrixTool =  QString::fromLatin1("Matrix Tool");
QString SeaLabUtils::objGroupUserDefinedRPSObject =  QString::fromLatin1("User Defined RPS object");
QString SeaLabUtils::objGroupUserObject =  QString::fromLatin1("User Defined Phenomenon");
QString SeaLabUtils::objGroupCumulativeProbabilityDistribution =  QString::fromLatin1("Cumulative Probability Distribution");
QString SeaLabUtils::objGroupKurtosis =  QString::fromLatin1("Kurtosis");
QString SeaLabUtils::objGroupPeakFactor =  QString::fromLatin1("Peak Factor");
QString SeaLabUtils::objGroupProbabilityDensityFunction =  QString::fromLatin1("Probability Density Function");
QString SeaLabUtils::objGroupShearVelocityOfFlow =  QString::fromLatin1("Shear Velocity of Flow");
QString SeaLabUtils::objGroupSkewness =  QString::fromLatin1("Skewness");
QString SeaLabUtils::objGroupStandardDeviation =  QString::fromLatin1("Standard Deviation");
QString SeaLabUtils::objGroupVariance =  QString::fromLatin1("Variance");
QString SeaLabUtils::objGroupWavePassageEffect =  QString::fromLatin1("Wave Passage Effect");

QString SeaLabUtils::docRPSFeatures =  QString::fromLatin1("RPS Features");
QString SeaLabUtils::docSimulations =  QString::fromLatin1("Simulations");


 
QString SeaLabUtils::ComputeLocationCoordinateMatrixP3 = QString::fromLatin1("ComputeLocationCoordinateMatrixP3");

QString SeaLabUtils::ComputeCrossCoherenceValue = QString::fromLatin1("ComputeCrossCoherenceValue");
QString SeaLabUtils::ComputeCrossCoherenceVectorF =  QString::fromLatin1("ComputeCrossCoherenceVectorF");
QString SeaLabUtils::ComputeCrossCoherenceVectorT = QString::fromLatin1("ComputeCrossCoherenceVectorT");
QString SeaLabUtils::ComputeCrossCoherenceMatrixPP = QString::fromLatin1("ComputeCrossCoherenceMatrixPP");

QString SeaLabUtils::ComputeCPDValue = QString::fromLatin1("ComputeCPDValue");
QString SeaLabUtils::ComputeCPDVectorX = QString::fromLatin1("ComputeCPDVectorX");

QString SeaLabUtils::ComputeCrossCorrelationValue = QString::fromLatin1("ComputeCrossCorrelationValue");
QString SeaLabUtils::ComputeCrossCorrelationVectorT = QString::fromLatin1("ComputeCrossCorrelationVectorT");
QString SeaLabUtils::ComputeCrossCorrelationMatrixPP = QString::fromLatin1("ComputeCrossCorrelationMatrixPP");

QString SeaLabUtils::ComputeFrequencyValue = QString::fromLatin1("ComputeFrequencyValue");
QString SeaLabUtils::ComputeFrequenciesVectorF = QString::fromLatin1("ComputeFrequenciesVectorF");
QString SeaLabUtils::ComputeFrequenciesMatrixFP = QString::fromLatin1("ComputeFrequenciesMatrixFP");

QString SeaLabUtils::ComputeKurtosisValue = QString::fromLatin1("ComputeKurtosisValue");
QString SeaLabUtils::ComputeKurtosisVectorP = QString::fromLatin1("ComputeKurtosisVectorP");
QString SeaLabUtils::ComputeKurtosisVectorT = QString::fromLatin1("ComputeKurtosisVectorT");

QString SeaLabUtils::MatrixToolCompute = QString::fromLatin1("MatrixToolCompute");

QString SeaLabUtils::ComputeMeanAccelerationValue =  QString::fromLatin1("ComputeMeanAccelerationValue");
QString SeaLabUtils::ComputeMeanAccelerationVectorP =  QString::fromLatin1("ComputeMeanAccelerationVectorP");
QString SeaLabUtils::ComputeMeanAccelerationVectorT =  QString::fromLatin1("ComputeMeanAccelerationVectorT");

QString SeaLabUtils::ComputeModulationValue = QString::fromLatin1("ComputeModulationValue");
QString SeaLabUtils::ComputeModulationVectorP = QString::fromLatin1("ComputeModulationVectorP");
QString SeaLabUtils::ComputeModulationVectorT = QString::fromLatin1("ComputeModulationVectorT");

QString SeaLabUtils::ComputePeakFactorValue = QString::fromLatin1("ComputePeakFactorValue");
QString SeaLabUtils::ComputePeakFactorVectorP = QString::fromLatin1("ComputePeakFactorVectorP");
QString SeaLabUtils::ComputePeakFactorVectorT = QString::fromLatin1("ComputePeakFactorVectorT");

QString SeaLabUtils::ComputePDFValue = QString::fromLatin1("ComputePDFValue");
QString SeaLabUtils::ComputePDFVectorX = QString::fromLatin1("ComputePDFVectorX");

QString SeaLabUtils::ComputeDecomposedPSDValue = QString::fromLatin1("ComputeDecomposedPSDValue");
QString SeaLabUtils::ComputeDecomposedCrossSpectrumVectorF = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorF");
QString SeaLabUtils::ComputeDecomposedCrossSpectrumVectorT = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorT");
QString SeaLabUtils::ComputeDecomposedCrossSpectrumMatrixPP = QString::fromLatin1("ComputeDecomposedCrossSpectrumMatrixPP");

QString SeaLabUtils::ComputeRandomValue = QString::fromLatin1("ComputeRandomValue");
QString SeaLabUtils::GenerateRandomMatrixFP = QString::fromLatin1("GenerateRandomMatrixFP");
QString SeaLabUtils::GenerateRandomCubeFPS = QString::fromLatin1("GenerateRandomCubeFPS");

QString SeaLabUtils::ComputeShearVelocityOfFlowValue = QString::fromLatin1("ComputeShearVelocityOfFlowValue");
QString SeaLabUtils::ComputeShearVelocityOfFlowVectorT = QString::fromLatin1("ComputeShearVelocityOfFlowVectorT");
QString SeaLabUtils::ComputeShearVelocityOfFlowVectorP = QString::fromLatin1("ComputeShearVelocityOfFlowVectorP");

QString SeaLabUtils::Simulate = QString::fromLatin1("Simulate");
QString SeaLabUtils::SimulateInLargeScaleMode = QString::fromLatin1("SimulateInLargeScaleMode");

QString SeaLabUtils::ComputeSkewnessValue = QString::fromLatin1("ComputeSkewnessValue");
QString SeaLabUtils::ComputeSkewnessVectorP = QString::fromLatin1("ComputeSkewnessVectorP");
QString SeaLabUtils::ComputeSkewnessVectorT = QString::fromLatin1("ComputeSkewnessVectorT");

QString SeaLabUtils::ComputeStandardDeviationValue = QString::fromLatin1("ComputeStandardDeviationValue");
QString SeaLabUtils::ComputeStandardDeviationVectorP = QString::fromLatin1("ComputeStandardDeviationVectorP");
QString SeaLabUtils::ComputeStandardDeviationVectorT = QString::fromLatin1("ComputeStandardDeviationVectorT");

QString SeaLabUtils::TableToolCompute = QString::fromLatin1("TableToolCompute");

QString SeaLabUtils::UserDefinedRPSObjectCompute = QString::fromLatin1("UserDefinedRPSObjectCompute");

QString SeaLabUtils::ComputeVarianceValue = QString::fromLatin1("ComputeVarianceValue");
QString SeaLabUtils::ComputeVarianceVectorP = QString::fromLatin1("ComputeVarianceVectorP");
QString SeaLabUtils::ComputeVarianceVectorT = QString::fromLatin1("ComputeVarianceVectorT");


QString SeaLabUtils::ComputeWavePassageEffectValue = QString::fromLatin1("ComputeWavePassageEffectValue");
QString SeaLabUtils::ComputeWavePassageEffectVectorF = QString::fromLatin1("ComputeWavePassageEffectVectorF");
QString SeaLabUtils::ComputeWavePassageEffectVectorT = QString::fromLatin1("ComputeWavePassageEffectVectorT");
QString SeaLabUtils::ComputeWavePassageEffectMatrixPP = QString::fromLatin1("ComputeWavePassageEffectMatrixPP");

QString SeaLabUtils::ComputeCrossSpectrumValue = QString::fromLatin1("ComputeCrossSpectrumValue");
QString SeaLabUtils::ComputeCrossSpectrumVectorF = QString::fromLatin1("ComputeCrossSpectrumVectorF");
QString SeaLabUtils::ComputeCrossSpectrumVectorT = QString::fromLatin1("ComputeCrossSpectrumVectorT");
QString SeaLabUtils::ComputeCrossSpectrumMatrixPP = QString::fromLatin1("ComputeCrossSpectrumMatrixPP");
QString SeaLabUtils::ComputeAutoSpectrumValue = QString::fromLatin1("ComputeAutoSpectrumValue");
QString SeaLabUtils::ComputeAutoSpectrumVectorF = QString::fromLatin1("ComputeAutoSpectrumVectorF");
QString SeaLabUtils::ComputeAutoSpectrumVectorT = QString::fromLatin1("ComputeAutoSpectrumVectorT");


bool SeaLabUtils::getObjects(std::map<const std::string, std::string>& map, std::map<const std::string, std::string>& lstObject, const std::string& pluginName, const std::string& objectGroup)
{
    if (!map.empty())
    {
        // Iterate though the map and show all the registed objects
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (!it->first.empty())
            {
                if (it->second == pluginName)
                {
                    lstObject[it->first] = objectGroup;
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


bool SeaLabUtils::updateObjectsMap(std::map<const std::string, std::string>& map, const QString& lstObject)
{
    if (!map.empty())
    {
        if (map.find(lstObject.toUtf8().constData()) != map.end())
        {
            map.erase(lstObject.toUtf8().constData());
        }
    }

    return true;
}

bool SeaLabUtils::updateObjectToSkipMap(std::map<const std::string, std::string>& map, const QString name, const QString pluginName)
{
    map[name.toUtf8().constData()] = pluginName.toUtf8().constData();
    return true;
}

bool SeaLabUtils::isThisObjectGroupPluggedInThisPlugin(const std::map<const std::string, std::string>& map, const QString& pluginName)
{
    if (!map.empty())
    {
        //go through the map
        for (auto& it : map)
        {
            //if mapped value is pluginName
            //then return true
            if (it.second == pluginName.toUtf8().constData())
            {
                return true;
            }
        }
    }

    return false;
}

bool SeaLabUtils::isThisObjectInstalled(std::map<const std::string, std::string>& map, QString& object)
{
    if (!map.empty())
    {
        if (map.find(object.toUtf8().constData()) != map.end())
        {
            return true;
        }
    }

    return false;
}

double SeaLabUtils::rgbRandomSeed_ = static_cast<double>(rand()) / RAND_MAX;
int SeaLabUtils::rgbCounter_ = 0;

int SeaLabUtils::getWordSizeApp() {
#if defined(Q_BUILD_64)
  return 64;
#elif defined(Q_BUILD_32)
  return 32;
#else
  return 0;
#endif
}

QString SeaLabUtils::getOperatingSystem() {
#if defined(Q_OS_WIN32)
  switch (QSysInfo::windowsVersion()) {
    case QSysInfo::WV_NT:
      return QString::fromLatin1("Windows NT");
    case QSysInfo::WV_2000:
      return QString::fromLatin1("Windows 2000");
    case QSysInfo::WV_XP:
      return QString::fromLatin1("Windows XP");
    case QSysInfo::WV_2003:
      return QString::fromLatin1("Windows Server 2003");
    case QSysInfo::WV_VISTA:
      return QString::fromLatin1("Windows Vista");
    case QSysInfo::WV_WINDOWS7:
      return QString::fromLatin1("Windows 7");
    case QSysInfo::WV_WINDOWS8:
      return QString::fromLatin1("Windows 8");
    case QSysInfo::WV_WINDOWS8_1:
      return QString::fromLatin1("Windows 8.1");
    case QSysInfo::WV_WINDOWS10:
      return QString::fromLatin1("Windows 10");
    default:
      return QString::fromLatin1("Windows");
  }
#elif defined(Q_OS_MAC)
  switch (QSysInfo::MacVersion()) {
    case QSysInfo::MV_10_3:
      return QString::fromLatin1("Mac OS X 10.3");
    case QSysInfo::MV_10_4:
      return QString::fromLatin1("Mac OS X 10.4");
    case QSysInfo::MV_10_5:
      return QString::fromLatin1("Mac OS X 10.5");
    case QSysInfo::MV_10_6:
      return QString::fromLatin1("Mac OS X 10.6");
    case QSysInfo::MV_10_7:
      return QString::fromLatin1("Mac OS X 10.7");
    case QSysInfo::MV_10_8:
      return QString::fromLatin1("Mac OS X 10.8");
    case QSysInfo::MV_10_9:
      return QString::fromLatin1("Mac OS X 10.9");
    case QSysInfo::MV_10_10:
      return QString::fromLatin1("Mac OS X 10.10");
    // case QSysInfo::MV_10_11: (mot available in qt4)
    // return QString::fromLatin1("Mac OS X 10.11");
    default:
      return QString::fromLatin1("Mac OS X");
  }
#elif defined(Q_OS_LINUX)
  QString exe("lsb_release");
  QStringList args;
  args << "-ds";
  QProcess proc;
  proc.setEnvironment(QProcess::systemEnvironment());
  proc.start(exe, args);
  if (proc.waitForStarted() && proc.waitForFinished()) {
    QByteArray info = proc.readAll();
    info.replace('\n', "");
    info.replace("\"", "");
    return QString(info);
  }

  return QString("Linux");
#elif defined(Q_OS_UNIX)
  return QString("UNIX");
#else
  return QString("Unknown");
#endif
}

int SeaLabUtils::getWordSizeOfOS() {
#if defined(Q_OS_WIN64)
  return 64;  // 64-bit process running on 64-bit windows
#elif defined(Q_OS_WIN32)

  // determine if 32-bit process running on 64-bit windows in WOW64 emulation
  // or 32-bit process running on 32-bit windows
  // default bIsWow64 to false for 32-bit process on 32-bit windows

  BOOL bIsWow64 = false;  // must default to false
  typedef BOOL(WINAPI * LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);

  LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
      GetModuleHandle(L"kernel32"), "IsWow64Process");

  if (NULL != fnIsWow64Process) {
    if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64)) {
      assert(false);  // something went majorly wrong
    }
  }
  return bIsWow64 ? 64 : 32;

#elif defined(Q_OS_LINUX)
  // http://stackoverflow.com/questions/246007/how-to-determine-whether-
  // a-given-linux-is-32-bit-or-64-bit
  QString exe(QLatin1String("getconf"));
  QStringList args;
  args << QLatin1String("LONG_BIT");
  QProcess proc;
  proc.setEnvironment(QProcess::systemEnvironment());
  proc.start(exe, args);
  if (proc.waitForStarted() && proc.waitForFinished()) {
    QByteArray info = proc.readAll();
    info.replace('\n', "");
    return info.toInt();
  }

  return 0;  // failed

#elif defined(Q_OS_UNIX) || defined(Q_OS_MAC)
  QString exe(QLatin1String("uname"));
  QStringList args;
  args << QLatin1String("-m");
  QProcess proc;
  proc.setEnvironment(QProcess::systemEnvironment());
  proc.start(exe, args);
  if (proc.waitForStarted() && proc.waitForFinished()) {
    QByteArray info = proc.readAll();
    info.replace('\n', "");
    if (info.indexOf("x86_64") >= 0)
      return 64;
    else if (info.indexOf("amd64") >= 0)
      return 64;
    else if (info.indexOf("ia64") >= 0)
      return 64;
    else if (info.indexOf("ppc64") >= 0)
      return 64;
    else if (info.indexOf("i386") >= 0)
      return 32;
    else if (info.indexOf("i686") >= 0)
      return 32;
    else if (info.indexOf("x86") >= 0)
      return 32;
  }

  return 0;  // failed
#else
  return 0;  // unknown
#endif
}


QString SeaLabUtils::splitstring(const QString& string) {
  if (string.isEmpty()) return string;

  // line break
  QStringList stringlist = string.split(QString::fromLatin1("<|>"));
  QString final = stringlist.at(0);
  for (int i = 1; i < stringlist.count(); i++) {
    final += QString::fromLatin1("\n") + stringlist.at(i);
  }

  return final;
}

QString SeaLabUtils::joinstring(const QString& string) {
  if (string.isEmpty()) return string;

  QStringList stringlist = string.split(QString::fromLatin1("\n"));
  QString final = stringlist.at(0);
  for (int i = 1; i < stringlist.count(); i++) {
    final += QString::fromLatin1("<|>") + stringlist.at(i);
  }
  return final;
}

QString SeaLabUtils::makeHtmlTable(const int row, const int column,
                                 const bool hasheader,
                                 const TableColorProfile& profile) {
  QString strokecolor;
  QString fillcolor;
  QString headerfillcolor;
  switch (profile) {
    case TableColorProfile::Success:
      strokecolor = QString::fromLatin1("rgba(0,180,0,0.8)");
      headerfillcolor = QString::fromLatin1("#00de6c");
      fillcolor = QString::fromLatin1("#00ffa9");
      break;
    case TableColorProfile::Failure:
      strokecolor = QString::fromLatin1("rgba(255,0,0,0.8)");
      headerfillcolor = QString::fromLatin1("#ff5b5b");
      fillcolor = QString::fromLatin1("#ffa9a9");
      break;
    case TableColorProfile::Generic:
      strokecolor = QString::fromLatin1("trnsparent");
      headerfillcolor = QString::fromLatin1("transparent");
      fillcolor = QString::fromLatin1("transparent");
      break;
  }

  QString string =
      QString::fromLatin1("<p><table style = \"border-collapse:collapse;width:100%;\"> ");
  QString thstyle = QString::fromLatin1("style = \"border:1px solid ") + strokecolor +
                    QString::fromLatin1(";background-color:") + headerfillcolor +
                    QString::fromLatin1(";text-align:left;padding:5px;color:black;\"");
  QString tdstyle = QString::fromLatin1("style = \"border:1px solid ") + strokecolor +
                    QString::fromLatin1(";background-color:") + fillcolor +
                    QString::fromLatin1(";text-align:left;padding:5px;color:black;\"");
  QString rowcolumnstring;
  int count = 1;
  // title
  if (hasheader) {
    rowcolumnstring += QString::fromLatin1("<tr>");
    for (int j = 0; j < column; j++) {
      rowcolumnstring +=
          QString::fromLatin1("<th ") + thstyle + QString::fromLatin1(">%") + QString::number(count++) + QString::fromLatin1("</th>");
    }
    rowcolumnstring += QString::fromLatin1("</tr>");
  }
  // rows
  for (int i = 0; i < row; i++) {
    rowcolumnstring += QString::fromLatin1("<tr>");
    for (int j = 0; j < column; j++) {
      rowcolumnstring +=
          QString::fromLatin1("<td ") + tdstyle + QString::fromLatin1(">%") + QString::number(count++) + QString::fromLatin1("</td>");
    }
    rowcolumnstring += QString::fromLatin1("</tr>");
  }
  rowcolumnstring += QString::fromLatin1("</table></p>");
  return string + rowcolumnstring;
}
