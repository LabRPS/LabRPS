#include "rpsWindLabSimulation.h"

#include "RPSWindLabAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/windLab/widgets/prswlsimuoptionsdlg.h"
#include "rps/windLab/widgets/rpswindvelocitydefinitiondlg.h"
#include "rps/windLab/widgets/rpswlpsddefinitiondialog.h"
#include "rps/windLab/widgets/rpswlcoherencedlg.h"
#include "rps/windLab/widgets/rpswlcorrelationdlg.h"
#include "rps/windLab/widgets/rpswlmodulationdlg.h"
#include "rps/windLab/widgets/rpswlmeanwinddlg.h"
#include "rps/windLab/widgets/rpswlcomparisondialog.h"
#include "rps/windLab/widgets/rpswlaccuracycomparisondialog.h"
#include "rps/rpsSimulation.h"
#include "ApplicationWindow.h"

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QTime>

RPSWindLabSimulation::RPSWindLabSimulation(QWidget *parent) : QWidget(parent)
{
	locationJ = 0;
    locationK = 0;
    frequencyIndex = 0;
    timeIndex = 0;

	// initialized windLab simulation data
	windLabDataInitialize();

	// read install windLab from registry if any
	WLReadAllTobeInstallObjectsFromRegistry();
	WLClearAllTobeInstallObjectsFromRegistry();

	// comparison
	comparisonInitial();
}

RPSWindLabSimulation::~RPSWindLabSimulation()
{
	// write install windLab from registry if any
	WLWriteAllTobeInstallObjectsToRegistry();
}

void RPSWindLabSimulation::windVelocity()
{
	std::unique_ptr<RPSWindVelocityDefinitionDlg> dlg(new RPSWindVelocityDefinitionDlg(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetWindLabData().numberOfSpatialPosition = dlg->numberOfSpatialPosition;
		GetWindLabData().numberOfTimeIncrements = dlg->numberOfTimeIncrements;
		GetWindLabData().timeIncrement = dlg->timeIncrement;
		GetWindLabData().minTime = dlg->minTime;
		GetWindLabData().maxTime = dlg->maxTime;
		GetWindLabData().numberOfSample = dlg->numberOfSample;
		GetWindLabData().stationarity = dlg->stationarity;
		GetWindLabData().gaussianity = dlg->gaussianity;
		GetWindLabData().spatialDistribution = dlg->spatialDistribution;

		// update the statusbar combobox content

		RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
		rpsSimulator->fillLocationJComboBox();
		rpsSimulator->fillLocationKComboBox();
		rpsSimulator->fillTimeComboBox();
	}
}

void RPSWindLabSimulation::spectrumWind()
{
	std::unique_ptr<RPSWLPSDDefinitionDialog> dlg(new RPSWLPSDDefinitionDialog(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetWindLabData().numberOfFrequency = dlg->numberOfFrequency;
		GetWindLabData().minFrequency = dlg->minFrequency;
		GetWindLabData().maxFrequency = dlg->maxFrequency;
		GetWindLabData().frequencyIncrement = dlg->frequencyIncrement;
		GetWindLabData().direction = dlg->windDirection;

		GetWindLabData().spectrumModel = dlg->spectrumModel;
		GetWindLabData().cpsdDecompositionMethod = dlg->cpsdDecompositionMethod;
		GetWindLabData().freqencyDistribution = dlg->freqencyDistribution;

		RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
		rpsSimulator->fillFrequencyComboBox();
	}
}

void RPSWindLabSimulation::coherenceWind()
{
	std::unique_ptr<RPSWLCoherenceDlg> dlg(new RPSWLCoherenceDlg(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetWindLabData().coherenceFunction = dlg->coherenceFunction;
	}
}
void RPSWindLabSimulation::correlationWind()
{
	std::unique_ptr<RPSWLCorrelationDlg> dlg(new RPSWLCorrelationDlg(this));

	if (dlg->exec() == QDialog::Accepted)
	{
		GetWindLabData().correlationFunction = dlg->correlationFunction;
	}
}
void RPSWindLabSimulation::modulationWind()
{
	std::unique_ptr<RPSWLModulationDlg> dlg(new RPSWLModulationDlg(this));
	if (dlg->exec() == QDialog::Accepted)
	{
		GetWindLabData().modulationFunction = dlg->modulationFunction;
	}
}

void RPSWindLabSimulation::meanWindVelocity()
{
	std::unique_ptr<RPSWLMeanDlg> dlg(new RPSWLMeanDlg(this));
	if (dlg->exec() == QDialog::Accepted)
	{
		GetWindLabData().meanFunction = dlg->meanFunction;
	}
}

void RPSWindLabSimulation::frequencyDistributionOutput()
{
	frequencyDistributionOut();
}
void RPSWindLabSimulation::locationDistributionOutput()
{
	spatialPositionOut();
}
void RPSWindLabSimulation::windVelocityOutput()
{
	QMessageBox::warning(0, "windLab", "Output wind velocity");
}
void RPSWindLabSimulation::spectrumWindOutput()
{
	if (1 == GetWindLabData().direction)
	{
		spectrumXModelOut();
	}
	else if (2 == GetWindLabData().direction)
	{
		spectrumYModelOut();
	}
	else if (3 == GetWindLabData().direction)
	{
		spectrumZModelOut();
	}
}
void RPSWindLabSimulation::coherenceWindOutput()
{
	CoherenceFunctionOutput();
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
	meanWindVelocityOut();
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
	lstObject.clear();

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
	lstObject.clear();
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
	// simulationThread = new QThread(this);
	// simulationWorker = new RPSWindLabSimulationWorker(windLabData, information);

	// simulationWorker->moveToThread(simulationThread);
	// connect(simulationWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
	// connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(simulate()));
	// connect(simulationWorker, SIGNAL(finished()), simulationThread, SLOT(quit()));
	// connect(simulationWorker, SIGNAL(finished()), simulationWorker, SLOT(deleteLater()));
	// connect(simulationThread, SIGNAL(finished()), simulationThread, SLOT(deleteLater()));
	// simulationThread->start();

	// from https://stackoverflow.com/questions/4093159/what-is-the-correct-way-to-implement-a-qthread-example-please
	simulationThread = new QThread();
	simulationWorker = new RPSWindLabSimulationWorker(windLabData, information);

	simulationTimer = new QTimer();
	simulationTimer->setInterval(1000); // Timer's inteveral set to 0 means that timer will trigger an event as soon as there are no other events to be processed

	simulationWorker->moveToThread(simulationThread);
	simulationTimer->moveToThread(simulationThread);

	// Make the worker watch when the thread starts then let the worker start simulation
	connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(simulate()));

	// Make the worker set its 'stop' flag when we're done.
	// This is performed while the simulate() method is still running,
	// so we need to execute it concurrently from this thread,
	// hence the Qt::DirectConnection. The stop() method is thread-safe
	// (uses a mutex to set the flag).
	connect(this, SIGNAL(stopped()), simulationWorker, SLOT(stop()), Qt::DirectConnection);

	// Make the thread quit when the worker self-destructs:
	connect(simulationWorker, SIGNAL(destroyed()), simulationThread, SLOT(quit()));

	// Make the thread self-destruct when it finishes,
	// or rather, make the main thread delete it:
	connect(simulationThread, SIGNAL(finished()), simulationThread, SLOT(deleteLater()));

	connect(simulationWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
	connect(simulationWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
	connect(simulationWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));
	connect(simulationWorker, SIGNAL(progressBarSetMin(int)), this, SLOT(progressBarSetMinSL(int)));
	connect(simulationWorker, SIGNAL(progressBarSetMax(int)), this, SLOT(progressBarSetMaxSL(int)));
	connect(simulationWorker, SIGNAL(progressBarSetValue(int)), this, SLOT(progressBarSetValueSL(int)));
	connect(simulationWorker, SIGNAL(progressBarReset()), this, SLOT(progressBarResetSL()));

	connect(simulationTimer, SIGNAL(timeout()), simulationWorker, SLOT(progressBarMinMaxValue()));
	connect(simulationThread, SIGNAL(started()), simulationTimer, SLOT(start()));
	connect(simulationWorker, SIGNAL(destroyed()), simulationTimer, SLOT(deleteLater()));

	simulationThread->start();
	// simulationTimer->start();
	// QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection);

	// QMessageBox::warning(0, "in thread", "WindLab simulation");

	// int i = 1;
	// while(10>i){ i++;}

	//   // Build an object
	// 	IrpsSeLRandomness* currentRndProvider = CrpsSeLRandomnessFactory::BuildRandomness(GetWindLabData().randomnessProvider);

	// 	// Check whether good object
	// 	if (NULL == currentRndProvider) { return; }

	//   mat randomValueArray(GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

	// 	// Apply iniatial setting
	// 	currentRndProvider->GenerateRandomArrayFP(GetWindLabData(), randomValueArray, information);

	//   QMessageBox::warning(
	//         this, ("sim"),
	//         QString::number(randomValueArray(0,0)));

	//   logInfo = ("hahahahahahaha");
	//   showResults(true);

	//   QString arrayName = ("Random Phase (%1,%2)").arg( GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

	//   Table *table = newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

	//   for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++) {
	//     for (int i = 0; i < GetWindLabData().numberOfFrequency; i++) {
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

void RPSWindLabSimulation::compareAccuracy()
{
	std::unique_ptr<RPSWLAccuracyComparisonDialog> dlg(new RPSWLAccuracyComparisonDialog(this));
	if (dlg->exec() == QDialog::Accepted)
	{
		comparisonCategory = dlg->comparisonCategory;
		comparisonFunction = dlg->comparisonFunction;
		comparisonCandidate = dlg->comparisonCandidate;
		resultOutputTime = dlg->resultOutputTime;
	}
}
void RPSWindLabSimulation::compareComputationTime()
{
	mcompareComputationTime = true;
	std::unique_ptr<RPSWLComparisonDialog> dlg(new RPSWLComparisonDialog(this));
	if (dlg->exec() == QDialog::Accepted)
	{
		mcompareComputationTime = dlg->compareComputationTime;
		mcompareMemoryUsage = dlg->compareMemoryUsage;
		comparisonCategory = dlg->comparisonCategory;
		comparisonFunction = dlg->comparisonFunction;
		comparisonCandidate = dlg->comparisonCandidate;
		minNumberOfLocation = dlg->minNumberOfLocation;
		minNumberOfFrequency = dlg->minNumberOfFrequency;
		minNumberOfTime = dlg->minNumberOfTime;
		numberOfLocationIncrement = dlg->numberOfLocationIncrement;
		numberOfFrequencyIncrement = dlg->numberOfFrequencyIncrement;
		numberOfTimeIncrement = dlg->numberOfTimeIncrement;
		totalNumber = dlg->totalNumber;
		resultOutputTime = dlg->resultOutputTime;
	}
}
void RPSWindLabSimulation::compareMemoryUsage()
{
	mcompareMemoryUsage = true;
	std::unique_ptr<RPSWLComparisonDialog> dlg(new RPSWLComparisonDialog(this));
	if (dlg->exec() == QDialog::Accepted)
	{
	}
}

void RPSWindLabSimulation::comparisonInitial()
{
	int index = 0;
	categories.append("Coherence Function");
	categories.append("Correlation Function");
	categories.append("Frequency Distribution");
	categories.append("Mean Wind Profil");
	categories.append("Modulation Function");
	categories.append("PSD Decomposition Method");
	categories.append("Simulation Method");
	categories.append("Along Wind Spectrum");
	categories.append("Cross Wind Spectrum");
	categories.append("Vertical Wind Spectrum");

	functions.append("ComputeCrossCoherenceVectorF");
	categoryFunctionListMap[categories.at(0)] = functions;
	functions.clear();

	functions.append("ComputeCrossCorrelationVectorT");
	functions.append("ComputeCrossCorrelationVectorP");
	categoryFunctionListMap[categories.at(1)] = functions;
	functions.clear();

	functions.append("ComputeFrequenciesVectorF");
	categoryFunctionListMap[categories.at(2)] = functions;
	functions.clear();

	functions.append("ComputeMeanWindSpeedVectorP");
	functions.append("ComputeMeanWindSpeedVectorT");
	categoryFunctionListMap[categories.at(3)] = functions;
	functions.clear();

	functions.append("ComputeModulationVectorT");
	functions.append("ComputeModulationVectorF");
	functions.append("ComputeModulationVectorP");
	categoryFunctionListMap[categories.at(4)] = functions;
	functions.clear();

	functions.append("ComputeDecomposedCrossSpectrumVectorF");
	functions.append("ComputeDecomposedCrossSpectrumVectorT");
	functions.append("ComputeDecomposedCrossSpectrumVectorP");
	categoryFunctionListMap[categories.at(5)] = functions;
	functions.clear();

	functions.append("Simulate");
	functions.append("SimulateInLargeScaleMode");
	categoryFunctionListMap[categories.at(6)] = functions;
	functions.clear();

	functions.append("ComputeXCrossSpectrumVectorF");
	functions.append("ComputeXCrossSpectrumVectorT");
	functions.append("ComputeXCrossSpectrumVectorP");
	categoryFunctionListMap[categories.at(7)] = functions;
	functions.clear();

	functions.append("ComputeYCrossSpectrumVectorF");
	functions.append("ComputeYCrossSpectrumVectorT");
	functions.append("ComputeYCrossSpectrumVectorP");
	categoryFunctionListMap[categories.at(8)] = functions;
	functions.clear();

	functions.append("ComputeZCrossSpectrumVectorF");
	functions.append("ComputeZCrossSpectrumVectorT");
	functions.append("ComputeZCrossSpectrumVectorP");
	categoryFunctionListMap[categories.at(9)] = functions;
	functions.clear();

	comparisonCategory = categories.at(6);
	comparisonFunction = categoryFunctionListMap[comparisonCategory].at(0);
	comparisonCandidate = "";
	minNumberOfLocation = GetWindLabData().numberOfSpatialPosition;
	minNumberOfFrequency = GetWindLabData().numberOfFrequency;
	minNumberOfTime = GetWindLabData().numberOfTimeIncrements;
	numberOfLocationIncrement = 0;
	numberOfFrequencyIncrement = 0;
	numberOfTimeIncrement = 0;
	totalNumber = 3;
	resultOutputTime = 1;
}

QStringList RPSWindLabSimulation::FindAllCoherenceFunction()
{
	QStringList theList;
	/////******coherence model start*******/////////
	typedef IrpsWLCoherence *(*CreateCoherenceCallback)();
	std::map<const QString, CreateCoherenceCallback>::iterator cohIt;

	// Iterate though the map and show all the registed spectrum models in the combo box
	for (cohIt = CrpsCoherenceFactory::GetCoherenceNamesMap().begin(); cohIt != CrpsCoherenceFactory::GetCoherenceNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		theList.append(cohIt->first);
	}

	return theList;
}

QStringList RPSWindLabSimulation::FindAllCorrelationFunctions()
{
	QStringList theList;

	/////******correlation model start*******/////////
	typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();
	std::map<const QString, CreateCorrelationCallback>::iterator corrIt;

	// Iterate though the map and show all the registed spectrum models in the combo box
	for (corrIt = CrpsCorrelationFactory::GetCorrelationNamesMap().begin(); corrIt != CrpsCorrelationFactory::GetCorrelationNamesMap().end(); ++corrIt)
	{
		// Add it to the combo box
		theList.append(corrIt->first);
	}

	return theList;
}
QStringList RPSWindLabSimulation::FindAllFrequencyDistributions()
{
	QStringList theList;

	typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
	std::map<const QString, CreateFrequencyDistributionCallback>::iterator freqDistrIt;

	// Iterate though the map and show all the registed spatial distribution in the combo box
	for (freqDistrIt = CrpsFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().begin(); freqDistrIt != CrpsFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().end(); ++freqDistrIt)
	{
		// Add it to the combo box
		theList.append(freqDistrIt->first);
	}
	return theList;
}
QStringList RPSWindLabSimulation::FindAllMeanWindProfils()
{
	QStringList theList;
	typedef IrpsWLMean *(*CreateMeanCallback)();
	std::map<const QString, CreateMeanCallback>::iterator meanIt;

	// Iterate though the map and show all the registed spectrum models in the combo box
	for (meanIt = CrpsMeanFactory::GetMeanNamesMap().begin(); meanIt != CrpsMeanFactory::GetMeanNamesMap().end(); ++meanIt)
	{
		// Add it to the combo box
		theList.append(meanIt->first);
	}

	return theList;
}
QStringList RPSWindLabSimulation::FindAllModulationFunctions()
{
	QStringList theList;
	typedef IrpsWLModulation *(*CreateModulationCallback)();
	std::map<const QString, CreateModulationCallback>::iterator cohIt;

	// Iterate though the map and show all the registed spectrum models in the combo box
	for (cohIt = CrpsModulationFactory::GetModulationNamesMap().begin(); cohIt != CrpsModulationFactory::GetModulationNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		theList.append(cohIt->first);
	}
	return theList;
}
QStringList RPSWindLabSimulation::FindAllPSDDecompositionMethods()
{
	QStringList theList;
	typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
	std::map<const QString, CreatePSDdecomMethodCallback>::iterator psdDecIt;

	// Iterate though the map and show all the registed spatial distribution in the combo box
	for (psdDecIt = CrpsPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().begin(); psdDecIt != CrpsPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().end(); ++psdDecIt)
	{
		// Add it to the combo box
		theList.append(psdDecIt->first);
	}
	return theList;
}
QStringList RPSWindLabSimulation::FindAllSimulationMethods()
{
	QStringList theList;
	typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();
	std::map<const QString, CreateSimuMethodCallback>::iterator simuMethIt;

	// Iterate though the map and show all the registed randomness providers in the combo box
	for (simuMethIt = CrpsSimuMethodFactory::GetSimuMethodNamesMap().begin(); simuMethIt != CrpsSimuMethodFactory::GetSimuMethodNamesMap().end(); ++simuMethIt)
	{
		// Add it to the combo box
		theList.append(simuMethIt->first);
	}
	return theList;
}

QStringList RPSWindLabSimulation::FindAllSpectrumModels()
{
	QStringList theList;
	if (1 == GetWindLabData().direction)
	{
		/////******spectrum model start*******/////////
		typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();
		std::map<const QString, CreateXSpectrumCallback>::iterator psdIt;

		// Iterate though the map and show all the registed spectrum models in the combo box
		for (psdIt = CrpsXSpectrumFactory::GetXSpectrumNamesMap().begin(); psdIt != CrpsXSpectrumFactory::GetXSpectrumNamesMap().end(); ++psdIt)
		{
			// Add it to the combo box
			theList.append(psdIt->first);
		}
	}
	else if (2 == GetWindLabData().direction)
	{
		/////******spectrum model start*******/////////
		typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();
		std::map<const QString, CreateYSpectrumCallback>::iterator psdIt;

		// Iterate though the map and show all the registed spectrum models in the combo box
		for (psdIt = CrpsYSpectrumFactory::GetYSpectrumNamesMap().begin(); psdIt != CrpsYSpectrumFactory::GetYSpectrumNamesMap().end(); ++psdIt)
		{
			// Add it to the combo box
			theList.append(psdIt->first);
		}
	}
	else if (3 == GetWindLabData().direction)
	{
		/////******spectrum model start*******/////////
		typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();
		std::map<const QString, CreateZSpectrumCallback>::iterator psdIt;

		// Iterate though the map and show all the registed spectrum models in the combo box
		for (psdIt = CrpsZSpectrumFactory::GetZSpectrumNamesMap().begin(); psdIt != CrpsZSpectrumFactory::GetZSpectrumNamesMap().end(); ++psdIt)
		{
			// Add it to the combo box
			theList.append(psdIt->first);
		}
	}
	return theList;
}

void RPSWindLabSimulation::fillCategoryComboBox(QComboBox *categoryComboBox)
{
	categoryComboBox->addItems(categories);
	categoryComboBox->setCurrentText(comparisonCategory);
}

void RPSWindLabSimulation::fillFunctionAndCandidateComboBoxes(QString category, QComboBox *functionComboBox, QComboBox *candidatesComboBox)
{
	functionComboBox->clear();
	candidatesComboBox->clear();

	switch (categories.indexOf(category))
	{
	case 0:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(0)]);
		candidatesComboBox->addItems(FindAllCoherenceFunction());
		break;
	case 1:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(1)]);
		candidatesComboBox->addItems(FindAllCorrelationFunctions());
		break;
	case 2:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(2)]);
		candidatesComboBox->addItems(FindAllFrequencyDistributions());
		break;
	case 3:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(3)]);
		candidatesComboBox->addItems(FindAllMeanWindProfils());
		break;
	case 4:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(4)]);
		candidatesComboBox->addItems(FindAllModulationFunctions());
		break;
	case 5:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(5)]);
		candidatesComboBox->addItems(FindAllPSDDecompositionMethods());
		break;
	case 6:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(6)]);
		candidatesComboBox->addItems(FindAllSimulationMethods());
		break;
	case 7:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(7)]);
		candidatesComboBox->addItems(FindAllSpectrumModels());
		break;
	case 8:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(8)]);
		candidatesComboBox->addItems(FindAllSpectrumModels());
		break;
	case 9:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(9)]);
		candidatesComboBox->addItems(FindAllSpectrumModels());
		break;
	default:
		qWarning("Unknown comparison category");
		break;
	}

	functionComboBox->setCurrentText(comparisonFunction);
	candidatesComboBox->setCurrentText(comparisonCandidate);
}

void RPSWindLabSimulation::CoherenceFunctionInital(QString currentSelected)
{
	// Build an object
	IrpsWLCoherence *currentSelection = CrpsCoherenceFactory::BuildCoherence(currentSelected);

	// Check whether good object
	if (NULL == currentSelection)
	{
		return;
	}

	// Apply iniatial setting
	currentSelection->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentSelection;
}
void RPSWindLabSimulation::correlationFunctionInital(QString currentSelected)
{
	// Build an object
	IrpsWLCorrelation *currentSelection = CrpsCorrelationFactory::BuildCorrelation(currentSelected);

	// Check whether good object
	if (NULL == currentSelection)
	{
		return;
	}

	// Apply iniatial setting
	currentSelection->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentSelection;
}
void RPSWindLabSimulation::frequencyDistributionInital(QString currentSelected)
{
	// Build an object
	IrpsWLFrequencyDistribution *currentSelection = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(currentSelected);

	// Check whether good object
	if (NULL == currentSelection)
	{
		return;
	}

	// Apply iniatial setting
	currentSelection->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentSelection;
}
void RPSWindLabSimulation::meanWindProfilInital(QString currentSelected)
{
	// Build an object
	IrpsWLMean *currentSelection = CrpsMeanFactory::BuildMean(currentSelected);

	// Check whether good object
	if (NULL == currentSelection)
	{
		return;
	}

	// Apply iniatial setting
	currentSelection->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentSelection;
}
void RPSWindLabSimulation::modulationFunctionInital(QString currentSelected)
{
	// Build an object
	IrpsWLModulation *currentSelection = CrpsModulationFactory::BuildModulation(currentSelected);

	// Check whether good object
	if (NULL == currentSelection)
	{
		return;
	}

	// Apply iniatial setting
	currentSelection->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentSelection;
}
void RPSWindLabSimulation::psdDecompositionMethodInital(QString currentSelected)
{
	// Build an object
	IrpsWLPSDdecompositionMethod *currentSelection = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(currentSelected);

	// Check whether good object
	if (NULL == currentSelection)
	{
		return;
	}

	// Apply iniatial setting
	currentSelection->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentSelection;
}
void RPSWindLabSimulation::simulationMethodInital(QString currentSelected)
{
	// Build an object
	IrpsWLSimuMethod *currentRndProvider = CrpsSimuMethodFactory::BuildSimuMethod(currentSelected);

	// Check whether good object
	if (NULL == currentRndProvider)
	{
		return;
	}

	// Apply iniatial setting
	currentRndProvider->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentRndProvider;
}
void RPSWindLabSimulation::spectrumModelInital(QString currentSelected)
{
	if (1 == GetWindLabData().direction)
	{

		// Build an object
		IrpsWLXSpectrum *currentSelection = CrpsXSpectrumFactory::BuildXSpectrum(currentSelected);

		// Check whether good object
		if (NULL == currentSelection)
		{
			return;
		}

		// Apply iniatial setting
		currentSelection->OnInitialSetting(GetWindLabData(), information);

		// Delete the object
		delete currentSelection;
	}
	else if (2 == GetWindLabData().direction)
	{

		// Build an object
		IrpsWLYSpectrum *currentSelection = CrpsYSpectrumFactory::BuildYSpectrum(currentSelected);

		// Check whether good object
		if (NULL == currentSelection)
		{
			return;
		}

		// Apply iniatial setting
		currentSelection->OnInitialSetting(GetWindLabData(), information);

		// Delete the object
		delete currentSelection;
	}
	else if (3 == GetWindLabData().direction)
	{

		// Build an object
		IrpsWLZSpectrum *currentSelection = CrpsZSpectrumFactory::BuildZSpectrum(currentSelected);

		// Check whether good object
		if (NULL == currentSelection)
		{
			return;
		}
		// Apply iniatial setting
		currentSelection->OnInitialSetting(GetWindLabData(), information);

		// Delete the object
		delete currentSelection;
	}
}

void RPSWindLabSimulation::randomnessProviderInital(QString currentSelected)
{
	// Build an object
	IrpsWLRandomness *currentRndProvider = CrpsRandomnessFactory::BuildRandomness(currentSelected);

	// Check whether good object
	if (NULL == currentRndProvider)
	{
		return;
	}

	// Apply iniatial setting
	currentRndProvider->OnInitialSetting(GetWindLabData(), information);

	// Delete the object
	delete currentRndProvider;
}

void RPSWindLabSimulation::candidateInitialData(QString category, QString currentSelected)
{
	switch (categories.indexOf(category))
	{
	case 0:
		CoherenceFunctionInital(currentSelected);
		break;
	case 1:
		correlationFunctionInital(currentSelected);
		break;
	case 2:
		frequencyDistributionInital(currentSelected);
		break;
	case 3:
		meanWindProfilInital(currentSelected);
		break;
	case 4:
		modulationFunctionInital(currentSelected);
		break;
	case 5:
		psdDecompositionMethodInital(currentSelected);
		break;
	case 6:
		simulationMethodInital(currentSelected);
		break;
	case 7:
		spectrumModelInital(currentSelected);
		break;
	case 8:
		spectrumModelInital(currentSelected);
		break;
	case 9:
		spectrumModelInital(currentSelected);
		break;
	default:
		qWarning("Unknown comparison category");
		break;
	}
}

void RPSWindLabSimulation::receiveInformation(QStringList infoList)
{
	// RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	//  QMessageBox::warning(0, "hehe", infoList.at(0));
	emit sendInformation(infoList);
}

void RPSWindLabSimulation::progressBarShowSL()
{
	// QMessageBox::warning(0, "1", "in show");
	emit progressBarShow();
}
void RPSWindLabSimulation::progressBarHideSL()
{
	// QMessageBox::warning(0, "1", "in hide");
	emit progressBarHide();
}
void RPSWindLabSimulation::progressBarSetValueSL(int value)
{
	// QMessageBox::warning(0, "1", "in setvalue");
	emit progressBarSetValue(value);
}
void RPSWindLabSimulation::progressBarSetMinSL(int value)
{
	QMessageBox::warning(0, "1", "in set min");
	emit progressBarSetMin(value);
}
void RPSWindLabSimulation::progressBarSetMaxSL(int value)
{
	// QMessageBox::warning(0, "1", "in set max");
	emit progressBarSetMax(value);
}

void RPSWindLabSimulation::progressBarResetSL()
{
	// QMessageBox::warning(0, "1", "in reset");
	emit progressBarReset();
}

void RPSWindLabSimulation::CoherenceFunctionOutput()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	// Build an coherence function and frequency distribution functions
	IrpsWLCoherence *currentCoherenceFunction = CrpsCoherenceFactory::BuildCoherence(GetWindLabData().coherenceFunction);

	// Check whether good coherence object
	if (NULL == currentCoherenceFunction)
	{
		information.append("Invalid coherence function");
		return;
	}

	if (GetWindLabData().locationJ > 0 &&
		GetWindLabData().locationJ <= GetWindLabData().numberOfSpatialPosition &&
		GetWindLabData().locationK > 0 &&
		GetWindLabData().locationK <= GetWindLabData().numberOfSpatialPosition &&
		GetWindLabData().frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		GetWindLabData().timeIndex > 0 &&
		GetWindLabData().timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(GetWindLabData().freqencyDistribution);

		// Check whether good frequency object
		if (NULL == currentFrequencyDistribution)
		{
			information.append("Invalid frequency distribution");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		vec dCohVector(GetWindLabData().numberOfFrequency);
		vec dFrequencyVector(GetWindLabData().numberOfFrequency);

		QTime t;
		t.start();

		// running the computation
		currentCoherenceFunction->ComputeCrossCoherenceVectorF(GetWindLabData(), dCohVector, information);
		currentFrequencyDistribution->ComputeFrequenciesVectorF(GetWindLabData(), dFrequencyVector, information);

		information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("Coherence (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		//   app->logInfo = (QString::number(dFrequencyVector(0)));
		//   app->showResults(true);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, dFrequencyVector(i));
			table->setCellValue(i, 1, dCohVector(i));
		}

		table->showNormal();

		delete currentFrequencyDistribution;
	}
	else if (GetWindLabData().locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 GetWindLabData().locationK == GetWindLabData().numberOfSpatialPosition + 1 &&
			 GetWindLabData().frequencyIndex > 0 &&
			 GetWindLabData().frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 GetWindLabData().timeIndex > 0 &&
			 GetWindLabData().timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		// allocate memories to receive the computed coherence and frequencies
		mat dCoherenceMatrix(GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);

		QTime t;
		t.start();
		// running the computation
		currentCoherenceFunction->ComputeCrossCoherenceMatrixPP(GetWindLabData(), dCoherenceMatrix, information);

		information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the matrix
		QString arrayName = tr("Coherence (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the matrix
		Matrix *matrix = app->newMatrix(arrayName, GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);
		matrix->setCoordinates(1, GetWindLabData().numberOfSpatialPosition, 1, GetWindLabData().numberOfSpatialPosition);
		// fill the matrix with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				matrix->setText(i, j, QString::number(dCoherenceMatrix(i, j)));
			}
		}

		matrix->showNormal();
	}
	else
	{
		information.append("Sorry, there is no function that meet your requirements.");
	}

	// Delete the object
	delete currentCoherenceFunction;

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();
}

void RPSWindLabSimulation::fillLocationJComboBox(QComboBox *locationJComboBox)
{
	locationJComboBox->clear();

	locationJComboBox->addItem("None");
	for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
	{
		locationJComboBox->addItem(QString::number(i + 1));
	}
	locationJComboBox->addItem("All");
}
void RPSWindLabSimulation::fillLocationKComboBox(QComboBox *locationKComboBox)
{
	fillLocationJComboBox(locationKComboBox);
}
void RPSWindLabSimulation::fillFrequencyComboBox(QComboBox *frequencyComboBox)
{
	frequencyComboBox->clear();

	frequencyComboBox->addItem("None");
	for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
	{
		frequencyComboBox->addItem(QString::number(i + 1));
	}
	frequencyComboBox->addItem("All");
}
void RPSWindLabSimulation::fillTimeComboBox(QComboBox *timeComboBox)
{
	timeComboBox->clear();

	timeComboBox->addItem("None");
	for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
	{
		timeComboBox->addItem(QString::number(i + 1));
	}
	timeComboBox->addItem("All");
}

void RPSWindLabSimulation::locJCurrentIndexChanged(int index)
{
	locationJ = index;

	if(0 == index || GetWindLabData().numberOfSpatialPosition + 1 == index)
	{
		GetWindLabData().locationJ = 0;
	}
	else if(index > 0 &&
		    index <= GetWindLabData().numberOfSpatialPosition)
	{
		GetWindLabData().locationJ = index - 1;
	}
}
void RPSWindLabSimulation::locKCurrentIndexChanged(int index)
{
	locationK = index;

	if(0 == index || GetWindLabData().numberOfSpatialPosition + 1 == index)
	{
		GetWindLabData().locationK = 0;
	}
	else if(index > 0 &&
		    index <= GetWindLabData().numberOfSpatialPosition)
	{
		GetWindLabData().locationK = index - 1;
	}
}
void RPSWindLabSimulation::freqCurrentIndexChanged(int index)
{
	frequencyIndex = index;

	if(0 == index || GetWindLabData().numberOfFrequency + 1 == index)
	{
		GetWindLabData().frequencyIndex = 0;
	}
	else if(index > 0 &&
		    index <= GetWindLabData().numberOfFrequency)
	{
		GetWindLabData().frequencyIndex = index - 1;
	}
}
void RPSWindLabSimulation::timCurrentIndexChanged(int index)
{
	timeIndex = index;

	if(0 == index || GetWindLabData().numberOfTimeIncrements + 1 == index)
	{
		GetWindLabData().timeIndex = 0;
	}
	else if(index > 0 &&
		    index <= GetWindLabData().numberOfTimeIncrements)
	{
		GetWindLabData().timeIndex = index - 1;
	}
}

void RPSWindLabSimulation::spatialPositionOut()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	IrpsWLLocationDistribution *currentLocationDistribution = CrpsLocationDistributionFactory::BuildLocationDistribution(GetWindLabData().spatialDistribution);

	// Check whether good spatial distribution object
	if (NULL == currentLocationDistribution)
	{
		information.append("Invalid spatial distribution");
		return;
	}

	// allocate memories to receive the computed coherence and frequencies
	mat dLocCoord(GetWindLabData().numberOfSpatialPosition, 3);

	QTime t;
	t.start();

	// running the computation
	currentLocationDistribution->ComputeLocationCoordinateMatrixP3(GetWindLabData(), dLocCoord, information);

	information.append(tr("The computation of the spatial distribution took %1 ms").arg(QString::number(t.elapsed())));
	
	// prepare the name of the table
	QString arrayName = tr("Locations (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

	// allocate memory for the table
	Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 3);

	//   app->logInfo = (QString::number(dFrequencyVector(0)));
	//   app->showResults(true);

	// fill the table with computed coherence
	for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
	{
		table->setCellValue(i, 0, dLocCoord(i, 0));
		table->setCellValue(i, 1, dLocCoord(i, 1));
		table->setCellValue(i, 2, dLocCoord(i, 2));
	}

	table->showNormal();

	delete currentLocationDistribution;
}

void RPSWindLabSimulation::meanWindVelocityOut()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
		locationK == GetWindLabData().numberOfSpatialPosition + 1 &&
		timeIndex > 0 &&
		timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{

		// Build an coherence function and frequency distribution functions
		IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(GetWindLabData().meanFunction);

		// Check whether good coherence object
		if (NULL == currentMeanWindProfil)
		{
			information.append("Invalid mean wind profil");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		vec dMeanSpeedVector(GetWindLabData().numberOfSpatialPosition);

		QTime t;
		t.start();

		// running the computation
		currentMeanWindProfil->ComputeMeanWindSpeedVectorP(GetWindLabData(), dMeanSpeedVector, information);

		information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, dMeanSpeedVector(i));
		}

		table->showNormal();

		delete currentMeanWindProfil;
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK == locationJ &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		// allocate memories to receive the computed coherence and frequencies
		// Build an coherence function and frequency distribution functions
		IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(GetWindLabData().meanFunction);

		// Check whether good coherence object
		if (NULL == currentMeanWindProfil)
		{
			information.append("Invalid mean wind profil");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		vec dMeanSpeedVector(GetWindLabData().numberOfTimeIncrements);

		QTime t;
		t.start();

		// running the computation
		currentMeanWindProfil->ComputeMeanWindSpeedVectorT(GetWindLabData(), dMeanSpeedVector, information);

		information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);
        
		double timeInr = 0.0;
		
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i*GetWindLabData().timeIncrement;
			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, dMeanSpeedVector(i));
		}

		table->showNormal();

		delete currentMeanWindProfil;
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == GetWindLabData().numberOfSpatialPosition + 1 &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		// allocate memories to receive the computed coherence and frequencies
		// Build an coherence function and frequency distribution functions
		IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(GetWindLabData().meanFunction);

		// Check whether good coherence object
		if (NULL == currentMeanWindProfil)
		{
			information.append("Invalid mean wind profil");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		mat dMeanSpeedMatrix(GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition);

		QTime t;
		t.start();

		// running the computation
		currentMeanWindProfil->ComputeMeanWindSpeedMatrixTP(GetWindLabData(), dMeanSpeedMatrix, information);

		information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j, dMeanSpeedMatrix(i, j));
			}
		}

		table->showNormal();

		delete currentMeanWindProfil;
	}
	else
	{
		information.append("Sorry, there is no function that meet your requirements.");
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();
}

void RPSWindLabSimulation::frequencyDistributionOut()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK == locationJ &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1)
	{

		// Build an coherence function and frequency distribution functions
		IrpsWLFrequencyDistribution *currentFreqDistr = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(GetWindLabData().freqencyDistribution);

		// Check whether good coherence object
		if (NULL == currentFreqDistr)
		{
			information.append("Invalid mean wind profil");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		vec dFrequencyVector(GetWindLabData().numberOfFrequency);

		QTime t;
		t.start();

		// running the computation
		currentFreqDistr->ComputeFrequenciesVectorF(GetWindLabData(), dFrequencyVector, information);

		// virtual void ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation) = 0;

		information.append(tr("The computation of the frequencies took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, dFrequencyVector(i));
		}

		table->showNormal();

		delete currentFreqDistr;
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == GetWindLabData().numberOfSpatialPosition + 1 &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1)
	{
		// Build an coherence function and frequency distribution functions
		IrpsWLFrequencyDistribution *currentFreqDistr = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(GetWindLabData().freqencyDistribution);

		// Check whether good coherence object
		if (NULL == currentFreqDistr)
		{
			information.append("Invalid frequency distribution");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		mat dFrequencyMatrix(GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

		QTime t;
		t.start();

		// running the computation
		currentFreqDistr->ComputeFrequenciesMatrixFP(GetWindLabData(), dFrequencyMatrix, information);

		information.append(tr("The computation of the frequencies took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j, dFrequencyMatrix(i, j));
			}
		}
		table->showNormal();

		delete currentFreqDistr;
	}
	else
	{
		information.append("Sorry, there is no function that meet your requirements.");
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();
}

void RPSWindLabSimulation::spectrumXModelOut()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK > 0 &&
		locationK <= GetWindLabData().numberOfSpatialPosition &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex > 0 &&
		timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{

		// Build the psd model and the frequency distribution functions
		IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(GetWindLabData().spectrumModel);
		IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(GetWindLabData().freqencyDistribution);

		// Check whether good frequency object
		if (NULL == currentPSD)
		{
			information.append("Invalid spectrum model");
			return;
		}

		if (NULL == currentFrequencyDistribution)
		{
			information.append("Invalid frequency distribution");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		vec dPSDVector(GetWindLabData().numberOfFrequency);
		vec dFrequencyVector(GetWindLabData().numberOfFrequency);

		QTime t;
		t.start();

		// running the computation
		currentPSD->ComputeXCrossSpectrumVectorF(GetWindLabData(), dPSDVector, information);
		currentFrequencyDistribution->ComputeFrequenciesVectorF(GetWindLabData(), dFrequencyVector, information);

		information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("SpectrumX (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, dFrequencyVector(i));
			table->setCellValue(i, 1, dPSDVector(i));
		}

		table->showNormal();

		delete currentPSD;
		delete currentFrequencyDistribution;
	}
	else if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK > 0 &&
		locationK <= GetWindLabData().numberOfSpatialPosition &&
		frequencyIndex > 0 &&
		frequencyIndex <= GetWindLabData().numberOfFrequency &&
		timeIndex == GetWindLabData().numberOfTimeIncrements +1 

	)
	{
		// Build the psd model and the frequency distribution functions
		IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(GetWindLabData().spectrumModel);

		// Check whether good frequency object
		if (NULL == currentPSD)
		{
			information.append("Invalid spectrum model");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		vec dPSDVector(GetWindLabData().numberOfTimeIncrements);

		QTime t;
		t.start();

		// running the computation
		currentPSD->ComputeXCrossSpectrumVectorT(GetWindLabData(), dPSDVector, information);

		information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("SpectrumX (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);
        
		double timeInr = 0.0;
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i*GetWindLabData().timeIncrement;
			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, dPSDVector(i));
		}

		table->showNormal();

		delete currentPSD;
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
		locationK == 0 &&
		frequencyIndex > 0 &&
		frequencyIndex <= GetWindLabData().numberOfFrequency &&
		timeIndex > 0 && 
		timeIndex <= GetWindLabData().numberOfTimeIncrements 

	)
	{
		// Build the psd model and the frequency distribution functions
		IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(GetWindLabData().spectrumModel);

		// Check whether good frequency object
		if (NULL == currentPSD)
		{
			information.append("Invalid spectrum model");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		vec dPSDVector(GetWindLabData().numberOfSpatialPosition);

		QTime t;
		t.start();
		
		// running the computation
		currentPSD->ComputeXCrossSpectrumVectorP(GetWindLabData(), dPSDVector, information);

		information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("SpectrumX (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);
        
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, dPSDVector(i));
		}

		table->showNormal();

		delete currentPSD;
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
		locationK == locationJ &&
		frequencyIndex > 0 &&
		frequencyIndex <= GetWindLabData().numberOfFrequency &&
		timeIndex > 0 && 
		timeIndex <= GetWindLabData().numberOfTimeIncrements 

	)
	{
		// Build the psd model and the frequency distribution functions
		IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(GetWindLabData().spectrumModel);

		// Check whether good frequency object
		if (NULL == currentPSD)
		{
			information.append("Invalid spectrum model");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		mat dPSDMatrix(GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);

		QTime t;
		t.start();
		
		// running the computation
		currentPSD->ComputeXCrossSpectrumMatrixPP(GetWindLabData(), dPSDMatrix, information);

		information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("SpectrumX (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);
        
		// allocate memory for the matrix
		Matrix *matrix = app->newMatrix(arrayName, GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);
		matrix->setCoordinates(1, GetWindLabData().numberOfSpatialPosition, 1, GetWindLabData().numberOfSpatialPosition);


		// fill the matrix with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				matrix->setText(i, j, QString::number(dPSDMatrix(i, j)));
			}
		}

		matrix->showNormal();

		delete currentPSD;
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
		locationK == 0 &&
		frequencyIndex > 0 &&
		frequencyIndex <= GetWindLabData().numberOfFrequency &&
		timeIndex == GetWindLabData().numberOfTimeIncrements + 1

	)
	{
		// Build the psd model and the frequency distribution functions
		IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(GetWindLabData().spectrumModel);

		// Check whether good frequency object
		if (NULL == currentPSD)
		{
			information.append("Invalid spectrum model");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		mat dPSDMatrix(GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition);

		QTime t;
		t.start();
		
		// running the computation
		currentPSD->ComputeXCrossSpectrumMatrixTP(GetWindLabData(), dPSDMatrix, information);

		information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("SpectrumX (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition + 1);
        
		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i*GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j+1, dPSDMatrix(i,j));
			}
		}


		table->showNormal();

		delete currentPSD;
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
		locationK == 0 &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex > 0 &&
		timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{
		// Build the psd model and the frequency distribution functions
		IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(GetWindLabData().spectrumModel);
		IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(GetWindLabData().freqencyDistribution);

		// Check whether good frequency object
		if (NULL == currentPSD)
		{
			information.append("Invalid spectrum model");
			return;
		}

		if (NULL == currentFrequencyDistribution)
		{
			information.append("Invalid frequency distribution");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		mat dPSDMatrix(GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);
		vec dFrequencyVector(GetWindLabData().numberOfFrequency);

		QTime t;
		t.start();

		// running the computation
		currentPSD->ComputeXCrossSpectrumMatrixFP(GetWindLabData(), dPSDMatrix, information);
		currentFrequencyDistribution->ComputeFrequenciesVectorF(GetWindLabData(), dFrequencyVector, information);

		information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("SpectrumX (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition + 1);
        
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, dFrequencyVector(i));

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j+1, dPSDMatrix(i,j));
			}
		}


		table->showNormal();

		delete currentPSD;
		delete currentFrequencyDistribution;
	}
	else if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK > 0 &&
		locationK <= GetWindLabData().numberOfSpatialPosition &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex == GetWindLabData().numberOfTimeIncrements + 1 

	)
	{
		// Build the psd model and the frequency distribution functions
		IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(GetWindLabData().spectrumModel);
		IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(GetWindLabData().freqencyDistribution);

		// Check whether good frequency object
		if (NULL == currentPSD)
		{
			information.append("Invalid spectrum model");
			return;
		}

		if (NULL == currentFrequencyDistribution)
		{
			information.append("Invalid frequency distribution");
			return;
		}

		// allocate memories to receive the computed coherence and frequencies
		mat dPSDMatrix(GetWindLabData().numberOfFrequency, GetWindLabData().numberOfTimeIncrements);
		vec dFrequencyVector(GetWindLabData().numberOfFrequency);

		QTime t;
		t.start();

		// running the computation
		currentPSD->ComputeXCrossSpectrumMatrixTF(GetWindLabData(), dPSDMatrix, information);
		currentFrequencyDistribution->ComputeFrequenciesVectorF(GetWindLabData(), dFrequencyVector, information);

		information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

		// prepare the name of the table
		QString arrayName = tr("SpectrumX (%1, %2, %3, %4)").arg(locationJ).arg(locationK).arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfTimeIncrements + 1);
        
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, dFrequencyVector(i));

			for (int j = 0; j < GetWindLabData().numberOfTimeIncrements; j++)
			{
				table->setCellValue(i, j+1, dPSDMatrix(i,j));
			}
		}


		table->showNormal();

		delete currentPSD;
		delete currentFrequencyDistribution;
	}
	else
	{
		information.append("Sorry, there is no function that meet your requirements.");
	}

	QApplication::restoreOverrideCursor();


	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

}

void RPSWindLabSimulation::spectrumYModelOut()
{
}

void RPSWindLabSimulation::spectrumZModelOut()
{
}
