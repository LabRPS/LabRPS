#include "rpsSeaLabSimulation.h"

#include "RPSSeaLabAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/sealab/widgets/rpsseawavedefinitiondlg.h"
#include "rps/sealab/widgets/rpsselpsddefinitiondialog.h"
#include "rps/sealab/widgets/rpsselcoherencedlg.h"
#include "rps/sealab/widgets/rpsselcorrelationdlg.h"
#include "rps/sealab/widgets/rpsselmodulationdlg.h"
#include "rps/seaLab/widgets/prsselsimuoptionsdlg.h"

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>

RPSSeaLabSimulation::RPSSeaLabSimulation(QWidget *parent) : QWidget(parent)
{
	// initialized seaLab simulation data
	seaLabDataInitialize();

	// read install seaLab from registry if any
	SeLReadAllTobeInstallObjectsFromRegistry();
	SeLClearAllTobeInstallObjectsFromRegistry();
}

RPSSeaLabSimulation::~RPSSeaLabSimulation()
{
	SeLWriteAllTobeInstallObjectsToRegistry();
}

void RPSSeaLabSimulation::seaSurface()
{

	std::unique_ptr<RPSSeaWaveDefinitionDlg> dlg(new RPSSeaWaveDefinitionDlg(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetSeaLabData().numberOfSpatialPosition = dlg->numberOfSpatialPosition;
		GetSeaLabData().numberOfTimeIncrements = dlg->numberOfTimeIncrements;
		GetSeaLabData().timeIncrement = dlg->timeIncrement;
		GetSeaLabData().minTime = dlg->minTime;
	    GetSeaLabData().maxTime = dlg->maxTime;
		GetSeaLabData().numberOfSample = dlg->numberOfSample;
		GetSeaLabData().stationarity = dlg->stationarity;
		GetSeaLabData().gaussianity = dlg->gaussianity;
		GetSeaLabData().spatialDistribution = dlg->spatialDistribution;
		GetSeaLabData().waveType = dlg->waveType;
	}
}
void RPSSeaLabSimulation::spectrumSea()
{

	std::unique_ptr<RPSSeLPSDDefinitionDialog> dlg(new RPSSeLPSDDefinitionDialog(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetSeaLabData().numberOfFrequency = dlg->numberOfFrequency;
		GetSeaLabData().minFrequency = dlg->minFrequency;
		GetSeaLabData().maxFrequency = dlg->maxFrequency;
		GetSeaLabData().frequencyIncrement = dlg->frequencyIncrement;
		GetSeaLabData().numberOfDirection = dlg->numberOfDirection;
		GetSeaLabData().minDirection = dlg->minDirection;
		GetSeaLabData().maxDirection = dlg->maxDirection;
		GetSeaLabData().directionIncrement = dlg->directionIncrement;

		GetSeaLabData().spectrumModel = dlg->spectrumModel;
		GetSeaLabData().cpsdDecompositionMethod = dlg->cpsdDecompositionMethod;
		GetSeaLabData().freqencyDistribution = dlg->freqencyDistribution;
		GetSeaLabData().directionDistributionFunction = dlg->directionDistributionFunction;
		GetSeaLabData().directionSpreadingFunction = dlg->directionSpreadingFunction;
		GetSeaLabData().directionalSpectrumFunction = dlg->directionalSpectrumFunction;
	}
}

void RPSSeaLabSimulation::coherenceSea()
{

	std::unique_ptr<RPSSeLCoherenceDlg> dlg(new RPSSeLCoherenceDlg(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetSeaLabData().coherenceFunction = dlg->coherenceFunction;
	}
}
void RPSSeaLabSimulation::correlationSea()
{

	std::unique_ptr<RPSSeLCorrelationDlg> dlg(new RPSSeLCorrelationDlg(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetSeaLabData().correlationFunction = dlg->correlationFunction;
	}
}
void RPSSeaLabSimulation::modulationSea()
{

	std::unique_ptr<RPSSeLModulationDlg> dlg(new RPSSeLModulationDlg(this));
	if (dlg->exec() == QDialog::Accepted)
	{
		GetSeaLabData().modulationFunction = dlg->modulationFunction;
	}
}

void RPSSeaLabSimulation::seaSurfaceOutput()
{
	QMessageBox::warning(0, "seaLab", "Output sea surface");
}
void RPSSeaLabSimulation::frequencyDistributionOutput()
{
	QMessageBox::warning(0, "seimicLab", "Output spectrum");
}
void RPSSeaLabSimulation::locationDistributionOutput()
{
	QMessageBox::warning(0, "seimicLab", "Output spectrum");
}
void RPSSeaLabSimulation::spectrumSeaOutput()
{
	QMessageBox::warning(0, "seaLab", "Output spectrum");
}
void RPSSeaLabSimulation::coherenceSeaOutput()
{
	QMessageBox::warning(0, "seaLab", "Output coherence");
}
void RPSSeaLabSimulation::correlationSeaOutput()
{
	QMessageBox::warning(0, "seaLab", "Output correlation");
}
void RPSSeaLabSimulation::modulationSeaOutput()
{
	QMessageBox::warning(0, "seaLab", "Output modulation");
}
CRPSSeaLabsimuData &RPSSeaLabSimulation::GetSeaLabData()
{
	return seaLabData;
}

void RPSSeaLabSimulation::seaLabDataInitialize()
{
	seaLabData.numberOfSpatialPosition = 3;
	seaLabData.numberOfSample = 1;
	seaLabData.numberOfFrequency = 1024;
	seaLabData.minFrequency = 0;
	seaLabData.maxFrequency = 20;
	seaLabData.numberOfTimeIncrements = 2 * seaLabData.numberOfFrequency * seaLabData.numberOfSpatialPosition;
	seaLabData.timeIncrement = 0.25;
	seaLabData.frequencyIncrement = seaLabData.maxFrequency / seaLabData.numberOfFrequency;
	seaLabData.stationarity = 1;
	seaLabData.gaussianity = 1;
	seaLabData.minTime = 0;
	seaLabData.frequencyIndex = 0;
	seaLabData.timeIndex = 0;
	seaLabData.directionIndex = 0;
	seaLabData.directionalSpectrumFunction = ("RPS Directional Spectrum");
	seaLabData.simulationMethod = ("Deodatis et al 1996");
	seaLabData.spatialDistribution = ("Horizontal Distribution");
	seaLabData.coherenceFunction = ("Abrahamson Coherence");
	seaLabData.randomnessProvider = ("Uniform Random Phases");
	seaLabData.spectrumModel = ("Jonswap Spectrum");
	seaLabData.directionSpreadingFunction = ("RPS Spreading Function 1");
	seaLabData.directionDistributionFunction = ("RPS Uniform Direction Distribution");
	seaLabData.cpsdDecompositionMethod = ("RPS Cholesky Decomposition");
	seaLabData.freqencyDistribution = ("RPS Uniform Frequency Distribution");
	seaLabData.modulationFunction = ("Bogdanoff-Goldberg-Bernard Modulation function");
	seaLabData.direction = 1;
	seaLabData.numberOfDirection = 1024;
	seaLabData.minDirection = -1.57;
	seaLabData.maxDirection = 1.57;
	seaLabData.directionIncrement = (seaLabData.maxDirection - seaLabData.minDirection) / seaLabData.numberOfDirection;
	seaLabData.comparisonCategory = ("Simulation Method");
	seaLabData.numberOfTimeLags = seaLabData.numberOfFrequency;
	seaLabData.waveType = "Wind wave";
	seaLabData.correlationFunction = ("RPS Correlation");
}

void RPSSeaLabSimulation::WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{

	if (map.empty())
	{
		return;
	}

	QStringList mapkeylst;
	QStringList mapvaluelst;

	// Iterate though the map
	for (auto it1 = map.begin(); it1 != map.end(); ++it1)
	{
		mapkeylst.append(it1->first);
		mapvaluelst.append(it1->second);
	}

	QSettings settings;

	settings.beginGroup(settingsGroup);
	settings.setValue("mapkey", mapkeylst);
	settings.setValue("mapValue", mapvaluelst);
	settings.endGroup();

	count++;
}

void RPSSeaLabSimulation::ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{
	QSettings settings;

	settings.beginGroup(settingsGroup);
	QStringList mapkeylst = settings.value("mapkey").toStringList();
	QStringList mapvaluelst = settings.value("mapValue").toStringList();
	settings.endGroup();

	if (mapkeylst.isEmpty())
	{
		return;
	}

	for (int i = 0; i < mapkeylst.size(); ++i)
	{
		QString key = mapkeylst.at(i);
		QString value = mapvaluelst.at(i);

		map[key] = value;
		PluginManager::GetInstance().GetAllPlugedObjectsMap()[key] = value;
	}

	count++;
}

void RPSSeaLabSimulation::SeLWriteAllTobeInstallObjectsToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("SeLSimMethod"), count = 1;
	WriteMapToRegistry(CrpsSeLSimulationMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLLoc"), count = 1;
	WriteMapToRegistry(CrpsSeLLocationDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLXPSD"), count = 1;
	WriteMapToRegistry(CrpsSeLXSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLCoh"), count = 1;
	WriteMapToRegistry(CrpsSeLCoherenceFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDecomp"), count = 1;
	WriteMapToRegistry(CrpsSeLPSDdecomMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLFreq"), count = 1;
	WriteMapToRegistry(CrpsSeLFrequencyDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLRand"), count = 1;
	WriteMapToRegistry(CrpsSeLRandomnessFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLMod"), count = 1;
	WriteMapToRegistry(CrpsSeLModulationFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpec"), count = 1;
	WriteMapToRegistry(CrpsSeLDirectionalSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDirDistr"), count = 1;
	WriteMapToRegistry(CrpsSeLDirectionDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpread"), count = 1;
	WriteMapToRegistry(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLCorr"), count = 1;
	WriteMapToRegistry(CrpsSeLCorrelationFactory::GetOjectDescriptionMap(), settingsGroup, count);
}

void RPSSeaLabSimulation::SeLReadAllTobeInstallObjectsFromRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("SeLSimMethod"), count = 1;
	ReadMapFromRegistry(CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLLoc"), count = 1;
	ReadMapFromRegistry(CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLXPSD"), count = 1;
	ReadMapFromRegistry(CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLCoh"), count = 1;
	ReadMapFromRegistry(CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDecomp"), count = 1;
	ReadMapFromRegistry(CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLFreq"), count = 1;
	ReadMapFromRegistry(CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLRand"), count = 1;
	ReadMapFromRegistry(CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLMod"), count = 1;
	ReadMapFromRegistry(CrpsSeLModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpec"), count = 1;
	ReadMapFromRegistry(CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDirDistr"), count = 1;
	ReadMapFromRegistry(CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpread"), count = 1;
	ReadMapFromRegistry(CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLCorr"), count = 1;
	ReadMapFromRegistry(CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);
}

void RPSSeaLabSimulation::SeLClearAllTobeInstallObjectsFromRegistry()
{
	QString settingsGroup;

	settingsGroup = ("SeLSimMethod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLLoc");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLXPSD");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLCoh");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDecomp");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLFreq");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLRand");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLMod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDirSpec");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDirDistr");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDirSpread");
	ClearMapFromRegistry(settingsGroup);
}

void RPSSeaLabSimulation::ClearMapFromRegistry(QString &settingsGroup)
{
	QSettings settings;

	settings.beginGroup(settingsGroup);
	settings.remove(""); // removes the group, and all it keys
	settings.endGroup();
}

bool RPSSeaLabSimulation::GetObjects(std::map<const QString, QString> &map, QStringList &lstObject, QString pluginName)
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

bool RPSSeaLabSimulation::GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));

	try
	{
		GetObjects(CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLMeanFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeaLabSimulation::GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));

	try
	{
		GetObjects(CrpsSeLSimulationMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLMeanFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLXSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCorrelationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionalSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeaLabSimulation::IsObjectInstalled(QString &object)
{
	if (IsThisObjectInstalled(CrpsSeLSimulationMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLCoherenceFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLLocationDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLMeanFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLXSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLRandomnessFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLCorrelationFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLModulationFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLDirectionalSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLDirectionDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	return false;
}

bool RPSSeaLabSimulation::UpdateObjectsMap(std::map<const QString, QString> &map, const QString &lstObject)
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

bool RPSSeaLabSimulation::UpdateObjectToSkipMap(std::map<const QString, QString> &map, const QString name, const QString pluginName)
{
	map[name] = pluginName;
	return true;
}

bool RPSSeaLabSimulation::UpdateToBeInstalledObjectsMap(const QString &lstObject)
{
	try
	{
		UpdateObjectsMap(CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLMeanFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap(), lstObject);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeaLabSimulation::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
	try
	{
		UpdateObjectToSkipMap(CrpsSeLSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLMeanFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLXSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLCorrelationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLDirectionalSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLDirectionDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeaLabSimulation::IsThisObjectInstalled(std::map<const QString, QString> &map, QString &object)
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


void RPSSeaLabSimulation::runSimulation()
{
  //   // Build an object
  // 	IrpsSeLRandomness* currentRndProvider = CrpsSeLRandomnessFactory::BuildRandomness(GetSeaLabData().randomnessProvider);

  // 	// Check whether good object
  // 	if (NULL == currentRndProvider) { return; }

  //   mat randomValueArray(GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

  // 	// Apply iniatial setting
  // 	currentRndProvider->GenerateRandomArrayFP(GetSeaLabData(), randomValueArray, information);

  //   QMessageBox::warning(
  //         this, ("sim"),
  //         QString::number(randomValueArray(0,0)));

  //   logInfo = ("hahahahahahaha");
  //   showResults(true);

  //   QString arrayName = ("Random Phase (%1,%2)").arg( GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

  //   Table *table = newTable(arrayName, GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

  //   for (int j = 0; j < GetSeaLabData().numberOfSpatialPosition; j++) {
  //     for (int i = 0; i < GetSeaLabData().numberOfFrequency; i++) {
  //     table->setCellValue(i, j, randomValueArray(i,j));
  //       table->showNormal();

  //     // t->column(i)->setTextAt(i, randomValueArray(i,j));
  //   }  }
}
void RPSSeaLabSimulation::pauseSimulation()
{

}
void RPSSeaLabSimulation::stopSimulation()
{

}
void RPSSeaLabSimulation::simulationOptions()
{
  std::unique_ptr<PRSSeLSimuOptionsDlg> dlg(new PRSSeLSimuOptionsDlg(this));
  if (dlg->exec() == QDialog::Accepted)
  {
      GetSeaLabData().simulationMethod = dlg->currentsimulationMethod;
      GetSeaLabData().randomnessProvider = dlg->currentRandomnessProvider;
      GetSeaLabData().comparisonMode = dlg->comparisonMode;
      GetSeaLabData().largeScaleSimulationMode = dlg->largeScaleMode;
  }
}

  void RPSSeaLabSimulation::compareAccuracy()
  {

  }
  void RPSSeaLabSimulation::compareComputationTime()
  {

  }
  void RPSSeaLabSimulation::compareMemoryUsage()
  {
	  
  }