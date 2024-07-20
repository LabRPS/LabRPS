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
#include "SeismicLabUtils.h"


using namespace SeismicLab;

//phenomenon
QString SeismicLabUtils::rpsPhenomenonWindVelocity = QString::fromLatin1("Seismic Ground Motion");

// object groups
QString SeismicLabUtils::objGroupLocationDistribution =  QString::fromLatin1("Location Distribution");
QString SeismicLabUtils::objGroupMeanAccelerationProfile =  QString::fromLatin1("Mean Acceleration");
QString SeismicLabUtils::objGroupSpectrum =  QString::fromLatin1("Spectrum");
QString SeismicLabUtils::objGroupSpectrumDecompositionMethod =  QString::fromLatin1("Spectrum Decomposition Method");
QString SeismicLabUtils::objGroupCoherenceFunction =  QString::fromLatin1("Coherence Function");
QString SeismicLabUtils::objGroupSimulationMethod =  QString::fromLatin1("Simulation Method");
QString SeismicLabUtils::objGroupFrequencyDistribution =  QString::fromLatin1("Frequency Distribution");
QString SeismicLabUtils::objGroupRandomnessProvider =  QString::fromLatin1("Randomness Provider");
QString SeismicLabUtils::objGroupModulationFunction =  QString::fromLatin1("Modulation Function");
QString SeismicLabUtils::objGroupCorrelationFunction =  QString::fromLatin1("Correlation Function");
QString SeismicLabUtils::objGroupTableTool =  QString::fromLatin1("Table Tool");
QString SeismicLabUtils::objGroupMatrixTool =  QString::fromLatin1("Matrix Tool");
QString SeismicLabUtils::objGroupUserDefinedRPSObject =  QString::fromLatin1("User Defined RPS object");
QString SeismicLabUtils::objGroupUserDefinedPhenomenonObject =  QString::fromLatin1("User Defined Phenomenon");
QString SeismicLabUtils::objGroupCumulativeProbabilityDistribution =  QString::fromLatin1("Cumulative Probability Distribution");
QString SeismicLabUtils::objGroupKurtosis =  QString::fromLatin1("Kurtosis");
QString SeismicLabUtils::objGroupPeakFactor =  QString::fromLatin1("Peak Factor");
QString SeismicLabUtils::objGroupProbabilityDensityFunction =  QString::fromLatin1("Probability Density Function");
QString SeismicLabUtils::objGroupShearVelocityOfFlow =  QString::fromLatin1("Shear Velocity of Flow");
QString SeismicLabUtils::objGroupSkewness =  QString::fromLatin1("Skewness");
QString SeismicLabUtils::objGroupStandardDeviation =  QString::fromLatin1("Standard Deviation");
QString SeismicLabUtils::objGroupVariance =  QString::fromLatin1("Variance");
QString SeismicLabUtils::objGroupWavePassageEffect =  QString::fromLatin1("Wave Passage Effect");

QString SeismicLabUtils::docRPSFeatures =  QString::fromLatin1("RPS Features");
QString SeismicLabUtils::docSimulations =  QString::fromLatin1("Simulations");


 
QString SeismicLabUtils::ComputeLocationCoordinateMatrixP3 = QString::fromLatin1("ComputeLocationCoordinateMatrixP3");

QString SeismicLabUtils::ComputeCrossCoherenceValue = QString::fromLatin1("ComputeCrossCoherenceValue");
QString SeismicLabUtils::ComputeCrossCoherenceVectorF =  QString::fromLatin1("ComputeCrossCoherenceVectorF");
QString SeismicLabUtils::ComputeCrossCoherenceVectorT = QString::fromLatin1("ComputeCrossCoherenceVectorT");
QString SeismicLabUtils::ComputeCrossCoherenceMatrixPP = QString::fromLatin1("ComputeCrossCoherenceMatrixPP");

QString SeismicLabUtils::ComputeCPDValue = QString::fromLatin1("ComputeCPDValue");
QString SeismicLabUtils::ComputeCPDVectorX = QString::fromLatin1("ComputeCPDVectorX");

QString SeismicLabUtils::ComputeCrossCorrelationValue = QString::fromLatin1("ComputeCrossCorrelationValue");
QString SeismicLabUtils::ComputeCrossCorrelationVectorT = QString::fromLatin1("ComputeCrossCorrelationVectorT");
QString SeismicLabUtils::ComputeCrossCorrelationMatrixPP = QString::fromLatin1("ComputeCrossCorrelationMatrixPP");

QString SeismicLabUtils::ComputeFrequencyValue = QString::fromLatin1("ComputeFrequencyValue");
QString SeismicLabUtils::ComputeFrequenciesVectorF = QString::fromLatin1("ComputeFrequenciesVectorF");
QString SeismicLabUtils::ComputeFrequenciesMatrixFP = QString::fromLatin1("ComputeFrequenciesMatrixFP");

QString SeismicLabUtils::ComputeKurtosisValue = QString::fromLatin1("ComputeKurtosisValue");
QString SeismicLabUtils::ComputeKurtosisVectorP = QString::fromLatin1("ComputeKurtosisVectorP");
QString SeismicLabUtils::ComputeKurtosisVectorT = QString::fromLatin1("ComputeKurtosisVectorT");

QString SeismicLabUtils::MatrixToolCompute = QString::fromLatin1("MatrixToolCompute");

QString SeismicLabUtils::ComputeMeanAccelerationValue =  QString::fromLatin1("ComputeMeanAccelerationValue");
QString SeismicLabUtils::ComputeMeanAccelerationVectorP =  QString::fromLatin1("ComputeMeanAccelerationVectorP");
QString SeismicLabUtils::ComputeMeanAccelerationVectorT =  QString::fromLatin1("ComputeMeanAccelerationVectorT");

QString SeismicLabUtils::ComputeModulationValue = QString::fromLatin1("ComputeModulationValue");
QString SeismicLabUtils::ComputeModulationVectorP = QString::fromLatin1("ComputeModulationVectorP");
QString SeismicLabUtils::ComputeModulationVectorT = QString::fromLatin1("ComputeModulationVectorT");

QString SeismicLabUtils::ComputePeakFactorValue = QString::fromLatin1("ComputePeakFactorValue");
QString SeismicLabUtils::ComputePeakFactorVectorP = QString::fromLatin1("ComputePeakFactorVectorP");
QString SeismicLabUtils::ComputePeakFactorVectorT = QString::fromLatin1("ComputePeakFactorVectorT");

QString SeismicLabUtils::ComputePDFValue = QString::fromLatin1("ComputePDFValue");
QString SeismicLabUtils::ComputePDFVectorX = QString::fromLatin1("ComputePDFVectorX");

QString SeismicLabUtils::ComputeDecomposedPSDValue = QString::fromLatin1("ComputeDecomposedPSDValue");
QString SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorF = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorF");
QString SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorT = QString::fromLatin1("ComputeDecomposedCrossSpectrumVectorT");
QString SeismicLabUtils::ComputeDecomposedCrossSpectrumMatrixPP = QString::fromLatin1("ComputeDecomposedCrossSpectrumMatrixPP");

QString SeismicLabUtils::ComputeRandomValue = QString::fromLatin1("ComputeRandomValue");
QString SeismicLabUtils::GenerateRandomMatrixFP = QString::fromLatin1("GenerateRandomMatrixFP");

QString SeismicLabUtils::ComputeShearVelocityOfFlowValue = QString::fromLatin1("ComputeShearVelocityOfFlowValue");
QString SeismicLabUtils::ComputeShearVelocityOfFlowVectorT = QString::fromLatin1("ComputeShearVelocityOfFlowVectorT");
QString SeismicLabUtils::ComputeShearVelocityOfFlowVectorP = QString::fromLatin1("ComputeShearVelocityOfFlowVectorP");

QString SeismicLabUtils::Simulate = QString::fromLatin1("Simulate");
QString SeismicLabUtils::SimulateInLargeScaleMode = QString::fromLatin1("SimulateInLargeScaleMode");

QString SeismicLabUtils::ComputeSkewnessValue = QString::fromLatin1("ComputeSkewnessValue");
QString SeismicLabUtils::ComputeSkewnessVectorP = QString::fromLatin1("ComputeSkewnessVectorP");
QString SeismicLabUtils::ComputeSkewnessVectorT = QString::fromLatin1("ComputeSkewnessVectorT");

QString SeismicLabUtils::ComputeStandardDeviationValue = QString::fromLatin1("ComputeStandardDeviationValue");
QString SeismicLabUtils::ComputeStandardDeviationVectorP = QString::fromLatin1("ComputeStandardDeviationVectorP");
QString SeismicLabUtils::ComputeStandardDeviationVectorT = QString::fromLatin1("ComputeStandardDeviationVectorT");

QString SeismicLabUtils::TableToolCompute = QString::fromLatin1("TableToolCompute");

QString SeismicLabUtils::UserDefinedRPSObjectCompute = QString::fromLatin1("UserDefinedRPSObjectCompute");

QString SeismicLabUtils::ComputeVarianceValue = QString::fromLatin1("ComputeVarianceValue");
QString SeismicLabUtils::ComputeVarianceVectorP = QString::fromLatin1("ComputeVarianceVectorP");
QString SeismicLabUtils::ComputeVarianceVectorT = QString::fromLatin1("ComputeVarianceVectorT");


QString SeismicLabUtils::ComputeWavePassageEffectValue = QString::fromLatin1("ComputeWavePassageEffectValue");
QString SeismicLabUtils::ComputeWavePassageEffectVectorF = QString::fromLatin1("ComputeWavePassageEffectVectorF");
QString SeismicLabUtils::ComputeWavePassageEffectVectorT = QString::fromLatin1("ComputeWavePassageEffectVectorT");
QString SeismicLabUtils::ComputeWavePassageEffectMatrixPP = QString::fromLatin1("ComputeWavePassageEffectMatrixPP");

QString SeismicLabUtils::ComputeCrossSpectrumValue = QString::fromLatin1("ComputeCrossSpectrumValue");
QString SeismicLabUtils::ComputeCrossSpectrumVectorF = QString::fromLatin1("ComputeCrossSpectrumVectorF");
QString SeismicLabUtils::ComputeCrossSpectrumVectorT = QString::fromLatin1("ComputeCrossSpectrumVectorT");
QString SeismicLabUtils::ComputeCrossSpectrumMatrixPP = QString::fromLatin1("ComputeCrossSpectrumMatrixPP");
QString SeismicLabUtils::ComputeAutoSpectrumValue = QString::fromLatin1("ComputeAutoSpectrumValue");
QString SeismicLabUtils::ComputeAutoSpectrumVectorF = QString::fromLatin1("ComputeAutoSpectrumVectorF");
QString SeismicLabUtils::ComputeAutoSpectrumVectorT = QString::fromLatin1("ComputeAutoSpectrumVectorT");


bool SeismicLabUtils::getObjects(std::map<const std::string, std::string>& map, std::map<const std::string, std::string>& lstObject, const std::string& pluginName, const std::string& objectGroup)
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


bool SeismicLabUtils::updateObjectsMap(std::map<const std::string, std::string>& map, const QString& lstObject)
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

bool SeismicLabUtils::updateObjectToSkipMap(std::map<const std::string, std::string>& map, const QString name, const QString pluginName)
{
    map[name.toUtf8().constData()] = pluginName.toUtf8().constData();
    return true;
}

bool SeismicLabUtils::isThisObjectGroupPluggedInThisPlugin(const std::map<const std::string, std::string>& map, const QString& pluginName)
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

bool SeismicLabUtils::isThisObjectInstalled(std::map<const std::string, std::string>& map, QString& object)
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

double SeismicLabUtils::rgbRandomSeed_ = static_cast<double>(rand()) / RAND_MAX;
int SeismicLabUtils::rgbCounter_ = 0;

int SeismicLabUtils::getWordSizeApp() {
#if defined(Q_BUILD_64)
  return 64;
#elif defined(Q_BUILD_32)
  return 32;
#else
  return 0;
#endif
}

QString SeismicLabUtils::getOperatingSystem() {
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

int SeismicLabUtils::getWordSizeOfOS() {
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


QString SeismicLabUtils::splitstring(const QString& string) {
  if (string.isEmpty()) return string;

  // line break
  QStringList stringlist = string.split(QString::fromLatin1("<|>"));
  QString final = stringlist.at(0);
  for (int i = 1; i < stringlist.count(); i++) {
    final += QString::fromLatin1("\n") + stringlist.at(i);
  }

  return final;
}

QString SeismicLabUtils::joinstring(const QString& string) {
  if (string.isEmpty()) return string;

  QStringList stringlist = string.split(QString::fromLatin1("\n"));
  QString final = stringlist.at(0);
  for (int i = 1; i < stringlist.count(); i++) {
    final += QString::fromLatin1("<|>") + stringlist.at(i);
  }
  return final;
}

QString SeismicLabUtils::makeHtmlTable(const int row, const int column,
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
