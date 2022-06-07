#include "rpsWindLabSimulation.h"

#include "RPSWindLabAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/windLab/widgets/prswlsimuoptionsdlg.h"

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>

RPSWindLabSimulation::RPSWindLabSimulation(QWidget *parent) : QWidget(parent)
{
	// initialized windLab simulation data
	windLabDataInitialize();

	// read install windLab from registry if any
	WLReadAllTobeInstallObjectsFromRegistry();
	WLClearAllTobeInstallObjectsFromRegistry();
}

RPSWindLabSimulation::~RPSWindLabSimulation()
{
	// write install windLab from registry if any
	WLWriteAllTobeInstallObjectsToRegistry();
}

void RPSWindLabSimulation::windVelocity()
{
	QMessageBox::warning(0, "windLab", "intput velocity");
}

void RPSWindLabSimulation::spectrumWind()
{
	QMessageBox::warning(0, "windLab", "intput spectrum");
}

void RPSWindLabSimulation::coherenceWind()
{
	QMessageBox::warning(0, "windLab", "intput coherence");
}
void RPSWindLabSimulation::correlationWind()
{
	QMessageBox::warning(0, "windLab", "intput correlation");
}
void RPSWindLabSimulation::modulationWind()
{
	QMessageBox::warning(0, "windLab", "intput modulation");
}

void RPSWindLabSimulation::meanWindVelocity()
{
	QMessageBox::warning(0, "windLab", "intput mean wind");
}

void RPSWindLabSimulation::windVelocityOutput()
{
	QMessageBox::warning(0, "windLab", "Output wind velocity");
}
void RPSWindLabSimulation::spectrumWindOutput()
{
	QMessageBox::warning(0, "windLab", "Output spectrum");
}
void RPSWindLabSimulation::coherenceWindOutput()
{
	QMessageBox::warning(0, "windLab", "Output coherence");
}
void RPSWindLabSimulation::correlationWindOutput()
{
	QMessageBox::warning(0, "windLab", "Output correlation");
}
void RPSWindLabSimulation::modulationWindOutput()
{
	QMessageBox::warning(0, "windLab", "Output modulation");
}

void RPSWindLabSimulation::meanWindVelocityOutput()
{
	QMessageBox::warning(0, "windLab", "Output mean wind velocity");
}

CRPSWindLabsimuData &RPSWindLabSimulation::GetWindLabData()
{
	return windLabData;
}

void RPSWindLabSimulation::windLabDataInitialize()
{
	windLabData.numberOfSpatialPosition = 3;
	windLabData.numberOfSample = 1;
	windLabData.spatialDistribution = ("Horizontal Distribution");
	windLabData.numberOfFrequency = 1024;
	windLabData.minFrequency = 0;
	windLabData.maxFrequency = 4;
	windLabData.frequencyIncrement = windLabData.maxFrequency / windLabData.numberOfFrequency;
	windLabData.coherenceFunction = ("Davenport Coherence");
	windLabData.meanFunction = ("RPS Logarithmic Low");
	windLabData.simulationApproach = ("Spectral Representation Approach");
	windLabData.simulationMethod = ("Deodatis et al 1987");
	windLabData.randomnessProvider = ("Uniform Random Phases");
	windLabData.spectrumModel = ("Kaimail Along Wind Spectrum");
	windLabData.cpsdDecompositionMethod = ("RPS Cholesky Decomposition");
	windLabData.freqencyDistribution = ("Double Index Frequency");
	windLabData.modulationFunction = ("RPS Exponential Model");
	windLabData.direction = 1;
	windLabData.numberOfTimeIncrements = 2 * windLabData.numberOfFrequency * windLabData.numberOfSpatialPosition;
	windLabData.timeIncrement = 0.25;
	windLabData.stationarity = true;
	windLabData.gaussianity = true;
	windLabData.minTime = 0;
	windLabData.comparisonMode = false;
	windLabData.largeScaleSimulationMode = false;
	windLabData.frequencyDistrType = 2;
	windLabData.frequencyIndex = 0;
	windLabData.timeIndex = 0;
	windLabData.directionIndex = 0;
	windLabData.comparisonCategory = ("Simulation Method");
	windLabData.numberOfTimeLags = windLabData.numberOfFrequency;
}

void RPSWindLabSimulation::WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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

void RPSWindLabSimulation::ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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

void RPSWindLabSimulation::WLWriteAllTobeInstallObjectsToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("WLSimMethod"), count = 1;
	WriteMapToRegistry(CrpsSimuMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLLoc"), count = 1;
	WriteMapToRegistry(CrpsLocationDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLXPSD"), count = 1;
	WriteMapToRegistry(CrpsXSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLYPSD"), count = 1;
	WriteMapToRegistry(CrpsYSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLZPSD"), count = 1;
	WriteMapToRegistry(CrpsZSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLCoh"), count = 1;
	WriteMapToRegistry(CrpsCoherenceFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLDecomp"), count = 1;
	WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLFreq"), count = 1;
	WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLRand"), count = 1;
	WriteMapToRegistry(CrpsRandomnessFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLMod"), count = 1;
	WriteMapToRegistry(CrpsModulationFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLCorr"), count = 1;
	WriteMapToRegistry(CrpsCorrelationFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("WLMean"), count = 1;
	WriteMapToRegistry(CrpsMeanFactory::GetOjectDescriptionMap(), settingsGroup, count);
}

void RPSWindLabSimulation::WLReadAllTobeInstallObjectsFromRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("WLSimMethod"), count = 1;
	ReadMapFromRegistry(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLLoc"), count = 1;
	ReadMapFromRegistry(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLXPSD"), count = 1;
	ReadMapFromRegistry(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLYPSD"), count = 1;
	ReadMapFromRegistry(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLZPSD"), count = 1;
	ReadMapFromRegistry(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLCoh"), count = 1;
	ReadMapFromRegistry(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLDecomp"), count = 1;
	ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLFreq"), count = 1;
	ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLRand"), count = 1;
	ReadMapFromRegistry(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLMod"), count = 1;
	ReadMapFromRegistry(CrpsModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLCorr"), count = 1;
	ReadMapFromRegistry(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLMean"), count = 1;
	ReadMapFromRegistry(CrpsMeanFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);
}

void RPSWindLabSimulation::WLClearAllTobeInstallObjectsFromRegistry()
{
	QString settingsGroup;

	settingsGroup = ("WLSimMethod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLLoc");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLXPSD");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLYPSD");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLZPSD");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCoh");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLDecomp");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLFreq");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLRand");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLMod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCorr");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLMean");
	ClearMapFromRegistry(settingsGroup);
}

void RPSWindLabSimulation::ClearMapFromRegistry(QString &settingsGroup)
{
	QSettings settings;

	settings.beginGroup(settingsGroup);
	settings.remove(""); // removes the group, and all it keys
	settings.endGroup();
}

bool RPSWindLabSimulation::GetObjects(std::map<const QString, QString> &map, QStringList &lstObject, QString pluginName)
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

bool RPSWindLabSimulation::GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));

	try
	{
		GetObjects(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSWindLabSimulation::GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));

	try
	{
		GetObjects(CrpsSimuMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsXSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsYSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsZSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsMeanFactory::GetOjectAndPluginMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSWindLabSimulation::IsObjectInstalled(QString &object)
{
	if (IsThisObjectInstalled(CrpsSimuMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsLocationDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsXSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsYSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsZSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsCoherenceFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsRandomnessFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsModulationFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsMeanFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}

	return false;
}

bool RPSWindLabSimulation::UpdateObjectsMap(std::map<const QString, QString> &map, const QString &lstObject)
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

bool RPSWindLabSimulation::UpdateObjectToSkipMap(std::map<const QString, QString> &map, const QString name, const QString pluginName)
{
	map[name] = pluginName;
	return true;
}

bool RPSWindLabSimulation::UpdateToBeInstalledObjectsMap(const QString &lstObject)
{
	try
	{
		UpdateObjectsMap(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSWindLabSimulation::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
	try
	{
		UpdateObjectToSkipMap(CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSWindLabSimulation::IsThisObjectInstalled(std::map<const QString, QString> &map, QString &object)
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

void RPSWindLabSimulation::runSimulation()
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
void RPSWindLabSimulation::pauseSimulation()
{

}
void RPSWindLabSimulation::stopSimulation()
{

}
void RPSWindLabSimulation::simulationOptions()
{
	std::unique_ptr<PRSWLSimuOptionsDlg> dlg(new PRSWLSimuOptionsDlg(this));
	if (dlg->exec() == QDialog::Accepted)
	{
		GetWindLabData().simulationMethod = dlg->currentsimulationMethod;
		GetWindLabData().randomnessProvider = dlg->currentRandomnessProvider;
		GetWindLabData().comparisonMode = dlg->comparisonMode;
		GetWindLabData().largeScaleSimulationMode = dlg->largeScaleMode;
	}
}
