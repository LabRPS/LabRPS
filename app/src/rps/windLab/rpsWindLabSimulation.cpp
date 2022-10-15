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
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"
#include "globals.h"

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMetaType>

RPSWindLabSimulation::RPSWindLabSimulation(QWidget *parent) : QWidget(parent)
{
	locationJ = 0;
	locationK = 0;
	frequencyIndex = 0;
	timeIndex = 0;

	// initialized windLab simulation data
	windLabDataInitialize();

	WLReadAllTobeInstallObjVersionToRegistry();
	WLReadAllTobeInstallObjPublicationTitleToRegistry();
	WLReadAllTobeInstallObjPublicationLinkToRegistry();
	WLReadAllTobeInstallObjPublicationAuthorToRegistry();
	WLReadAllTobeInstallObjPublicationDateToRegistry();

	// read install windLab from registry if any
	WLReadAllTobeInstallObjectsFromRegistry();
	WLClearAllTobeInstallObjectsFromRegistry();

	// comparison
	comparisonInitial();
}

RPSWindLabSimulation::~RPSWindLabSimulation()
{
	// write install windLab from registry if any

	WLWriteAllTobeInstallObjPublicationTitleToRegistry();
	WLWriteAllTobeInstallObjPublicationLinkToRegistry();
	WLWriteAllTobeInstallObjPublicationAuthorToRegistry();
	WLWriteAllTobeInstallObjPublicationDateToRegistry();
	WLWriteAllTobeInstallObjVersionToRegistry();

	WLWriteAllTobeInstallObjectsToRegistry();

	if(nullptr != comparisonThread)
	{
		QMessageBox::warning(0, "windLab", "worker thread still running.");
        comparisonThread->exit(0);
        comparisonThread->wait(); // <-- wits till the thread has exited
        deleteLater(); // <-- ensures that it will be deleted later when the (main?) event loop executes again
	}
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
	createOutputWorker();

	connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(frequencyDistributionOut()));
	connect(simulationOutputWorker, SIGNAL(showFrequencyDistributionOutput()), this, SLOT(displayFrequencyDistribution()));

	emit progressBarShow();
	simulationOutputThread->start();
}
void RPSWindLabSimulation::locationDistributionOutput()
{
	createOutputWorker();
	connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(locationDistributionOut()));
	connect(simulationOutputWorker, SIGNAL(showLocationDistributionOutput()), this, SLOT(displayLocationDistribution()));

	emit progressBarShow();
	simulationOutputThread->start();
}
void RPSWindLabSimulation::windVelocityOutput()
{
	if (GetWindLabData().isSimulationSuccessful == true)
	{
		displayWindVelocity();
	}
	else
	{
		information.append("Please make sure you successfully run a simulation first");
		emit sendInformation(information);
	}
}

void RPSWindLabSimulation::spectrumWindOutput()
{
	createOutputWorker();

	if (1 == GetWindLabData().direction)
	{
		// QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumXModelOut);
		connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumXModelOut()));
		connect(simulationOutputWorker, SIGNAL(showXSpectrumOutput()), this, SLOT(displayXSpectrum()));
		psdPrefix = "X";
		emit progressBarShow();
		simulationOutputThread->start();
	}
	else if (2 == GetWindLabData().direction)
	{
		// QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumYModelOut);
		connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumYModelOut()));
		connect(simulationOutputWorker, SIGNAL(showYSpectrumOutput()), this, SLOT(displayYSpectrum()));
		psdPrefix = "Y";
		emit progressBarShow();
		simulationOutputThread->start();
	}
	else if (3 == GetWindLabData().direction)
	{
		// QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumZModelOut);
		connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumZModelOut()));
		connect(simulationOutputWorker, SIGNAL(showZSpectrumOutput()), this, SLOT(displayZSpectrum()));
		psdPrefix = "Z";
		emit progressBarShow();
		simulationOutputThread->start();
	}
}

void RPSWindLabSimulation::decomposedSpectrumWindOutput()
{
	createOutputWorker();

	// QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumXModelOut);
	connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(decomposedSpectrumModelOut()));
	connect(simulationOutputWorker, SIGNAL(showDecomposedSpectrumOutput()), this, SLOT(displayDecomposedSpectrum()));
	emit progressBarShow();
	simulationOutputThread->start();
}

void RPSWindLabSimulation::coherenceWindOutput()
{
	createOutputWorker();
	connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(coherenceOut()));
	connect(simulationOutputWorker, SIGNAL(showCoherenceOutput()), this, SLOT(displayCoherenceWind()));

	emit progressBarShow();
	simulationOutputThread->start();
}
void RPSWindLabSimulation::correlationWindOutput()
{
	QMessageBox::warning(0, "windLab", "Output correlation");
}
void RPSWindLabSimulation::modulationWindOutput()
{
	createOutputWorker();
	connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(modulationOut()));
	connect(simulationOutputWorker, SIGNAL(showModulationOutput()), this, SLOT(displayModulationWind()));

	emit progressBarShow();
	simulationOutputThread->start();
}

void RPSWindLabSimulation::meanWindVelocityOutput()
{
	createOutputWorker();
	connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(meanWindVelocityOut()));
	connect(simulationOutputWorker, SIGNAL(showMeanWindVelocityOutput()), this, SLOT(displayMeanWindVelocity()));

	emit progressBarShow();
	simulationOutputThread->start();
}

void RPSWindLabSimulation::randomPhaseWindOutput()
{
	createOutputWorker();
	connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(randomPhaseOut()));
	connect(simulationOutputWorker, SIGNAL(showRandomPhaseOutput()), this, SLOT(displayRandomPhase()));

	emit progressBarShow();
	simulationOutputThread->start();
}

CRPSWindLabsimuData &RPSWindLabSimulation::GetWindLabData()
{
	return windLabData;
}

RPSWindLabSimulationOutputWorker *RPSWindLabSimulation::GetWindLabSimulationOutputWorker()
{
	return simulationOutputWorker;
}

RPSWindLabSimulationWorker *RPSWindLabSimulation::GetWindLabSimulationWorker()
{
	return simulationWorker;
}

RPSWindLabComparisonWorker *RPSWindLabSimulation::GetWindLabComparisonWorker()
{
	return comparisonWorker;
}

void RPSWindLabSimulation::windLabDataInitialize()
{
	windLabData.numberOfSpatialPosition = 3;
	windLabData.numberOfSample = 1;
    windLabData.spatialDistribution = "Horizontal Distribution";
    windLabData.numberOfFrequency = 1024;
	windLabData.minFrequency = 0;
    windLabData.maxFrequency = 4*3.14;
	windLabData.frequencyIncrement = windLabData.maxFrequency / windLabData.numberOfFrequency;
    windLabData.coherenceFunction = "Davenport Coherence";
    windLabData.meanFunction = "RPS Logarithmic Low";
    windLabData.simulationApproach = "Spectral Representation Approach";
    windLabData.simulationMethod = "Deodatis et al 1987";
    windLabData.randomnessProvider = "Uniform Random Phases";
    windLabData.spectrumModel = "Kaimal Along Wind Spectrum";
    windLabData.cpsdDecompositionMethod = "RPS Cholesky Decomposition";
    windLabData.freqencyDistribution = "Double Index Frequency";
    windLabData.modulationFunction = "RPS Exponential Model";
	windLabData.direction = 1;
	windLabData.numberOfTimeIncrements = 2 * windLabData.numberOfFrequency * windLabData.numberOfSpatialPosition;
    windLabData.timeIncrement = 3.14/windLabData.maxFrequency;
	windLabData.stationarity = true;
	windLabData.gaussianity = true;
	windLabData.minTime = 0;
	windLabData.comparisonMode = false;
	windLabData.largeScaleSimulationMode = false;
	windLabData.frequencyDistrType = 2;
	windLabData.frequencyIndex = 0;
	windLabData.timeIndex = 0;
	windLabData.directionIndex = 0;
	windLabData.comparisonCategory = LabRPS::objGroupSimulationMethod;
	windLabData.numberOfTimeLags = windLabData.numberOfFrequency;
	windLabData.comparisonType = 1;
	windLabData.isInterruptionRequested = false;
	windLabData.isSimulationSuccessful = false;
    windLabData.workingDirPath = QCoreApplication::instance()->applicationDirPath();
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
	}

	count++;
}

void RPSWindLabSimulation::WriteMapToRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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

void RPSWindLabSimulation::ReadMapFromRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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
    WriteMapToRegistry(CrpsSimuMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLLoc"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLXPSD"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLYPSD"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLZPSD"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLCoh"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLDecomp"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLFreq"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLRand"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLMod"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLCorr"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetOjectAndPluginMap(), settingsGroup, count);

	settingsGroup = ("WLMean"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLTableTool"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixTool"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObj"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjectsFromRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("WLSimMethod"), count = 1;
	ReadMapFromRegistry2(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLLoc"), count = 1;
	ReadMapFromRegistry2(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLXPSD"), count = 1;
	ReadMapFromRegistry2(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLYPSD"), count = 1;
	ReadMapFromRegistry2(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLZPSD"), count = 1;
	ReadMapFromRegistry2(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLCoh"), count = 1;
	ReadMapFromRegistry2(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLDecomp"), count = 1;
	ReadMapFromRegistry2(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLFreq"), count = 1;
	ReadMapFromRegistry2(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLRand"), count = 1;
	ReadMapFromRegistry2(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLMod"), count = 1;
	ReadMapFromRegistry2(CrpsModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLCorr"), count = 1;
	ReadMapFromRegistry2(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLMean"), count = 1;
	ReadMapFromRegistry2(CrpsMeanFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("WLTableTool"), count = 1;
	ReadMapFromRegistry2(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixTool"), count = 1;
	ReadMapFromRegistry2(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObj"), count = 1;
	ReadMapFromRegistry2(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationTitleToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("WLSimMethodTitle"), count = 1;
	WriteMapToRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLLocTitle"), count = 1;
	WriteMapToRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDTitle"), count = 1;
	WriteMapToRegistry(CrpsXSpectrumFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDTitle"), count = 1;
	WriteMapToRegistry(CrpsYSpectrumFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDTitle"), count = 1;
	WriteMapToRegistry(CrpsZSpectrumFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLCohTitle"), count = 1;
	WriteMapToRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLDecompTitle"), count = 1;
	WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLFreqTitle"), count = 1;
	WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLRandTitle"), count = 1;
	WriteMapToRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLModTitle"), count = 1;
	WriteMapToRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLCorrTitle"), count = 1;
	WriteMapToRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLMeanTitle"), count = 1;
	WriteMapToRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolTitle"), count = 1;
	WriteMapToRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolTitle"), count = 1;
	WriteMapToRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjTitle"), count = 1;
	WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationTitleToRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("WLSimMethodTitle"), count = 1;
	ReadMapFromRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLLocTitle"), count = 1;
	ReadMapFromRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDTitle"), count = 1;
	ReadMapFromRegistry(CrpsXSpectrumFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDTitle"), count = 1;
	ReadMapFromRegistry(CrpsYSpectrumFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDTitle"), count = 1;
	ReadMapFromRegistry(CrpsZSpectrumFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLCohTitle"), count = 1;
	ReadMapFromRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLDecompTitle"), count = 1;
	ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLFreqTitle"), count = 1;
	ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLRandTitle"), count = 1;
	ReadMapFromRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLModTitle"), count = 1;
	ReadMapFromRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLCorrTitle"), count = 1;
	ReadMapFromRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLMeanTitle"), count = 1;
	ReadMapFromRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolTitle"), count = 1;
	ReadMapFromRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolTitle"), count = 1;
	ReadMapFromRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjTitle"), count = 1;
	ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationLinkToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("WLSimMethodLink"), count = 1;
	WriteMapToRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLLocLink"), count = 1;
	WriteMapToRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDLink"), count = 1;
	WriteMapToRegistry(CrpsXSpectrumFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDLink"), count = 1;
	WriteMapToRegistry(CrpsYSpectrumFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDLink"), count = 1;
	WriteMapToRegistry(CrpsZSpectrumFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLCohLink"), count = 1;
	WriteMapToRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLDecompLink"), count = 1;
	WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLFreqLink"), count = 1;
	WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLRandLink"), count = 1;
	WriteMapToRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLModLink"), count = 1;
	WriteMapToRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLCorrLink"), count = 1;
	WriteMapToRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLMeanLink"), count = 1;
	WriteMapToRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolLink"), count = 1;
	WriteMapToRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolLink"), count = 1;
	WriteMapToRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjLink"), count = 1;
	WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationLinkToRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("WLSimMethodLink"), count = 1;
	ReadMapFromRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLLocLink"), count = 1;
	ReadMapFromRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDLink"), count = 1;
	ReadMapFromRegistry(CrpsXSpectrumFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDLink"), count = 1;
	ReadMapFromRegistry(CrpsYSpectrumFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDLink"), count = 1;
	ReadMapFromRegistry(CrpsZSpectrumFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLCohLink"), count = 1;
	ReadMapFromRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLDecompLink"), count = 1;
	ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLFreqLink"), count = 1;
	ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLRandLink"), count = 1;
	ReadMapFromRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLModLink"), count = 1;
	ReadMapFromRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLCorrLink"), count = 1;
	ReadMapFromRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLMeanLink"), count = 1;
	ReadMapFromRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolLink"), count = 1;
	ReadMapFromRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolLink"), count = 1;
	ReadMapFromRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjLink"), count = 1;
	ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationAuthorToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("WLSimMethodAuthor"), count = 1;
	WriteMapToRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLLocAuthor"), count = 1;
	WriteMapToRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDAuthor"), count = 1;
	WriteMapToRegistry(CrpsXSpectrumFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDAuthor"), count = 1;
	WriteMapToRegistry(CrpsYSpectrumFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDAuthor"), count = 1;
	WriteMapToRegistry(CrpsZSpectrumFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLCohAuthor"), count = 1;
	WriteMapToRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLDecompAuthor"), count = 1;
	WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLFreqAuthor"), count = 1;
	WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLRandAuthor"), count = 1;
	WriteMapToRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLModAuthor"), count = 1;
	WriteMapToRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLCorrAuthor"), count = 1;
	WriteMapToRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLMeanAuthor"), count = 1;
	WriteMapToRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolAuthor"), count = 1;
	WriteMapToRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolAuthor"), count = 1;
	WriteMapToRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjAuthor"), count = 1;
	WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationAuthorToRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("WLSimMethodAuthor"), count = 1;
	ReadMapFromRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLLocAuthor"), count = 1;
	ReadMapFromRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDAuthor"), count = 1;
	ReadMapFromRegistry(CrpsXSpectrumFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDAuthor"), count = 1;
	ReadMapFromRegistry(CrpsYSpectrumFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDAuthor"), count = 1;
	ReadMapFromRegistry(CrpsZSpectrumFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLCohAuthor"), count = 1;
	ReadMapFromRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLDecompAuthor"), count = 1;
	ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLFreqAuthor"), count = 1;
	ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLRandAuthor"), count = 1;
	ReadMapFromRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLModAuthor"), count = 1;
	ReadMapFromRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLCorrAuthor"), count = 1;
	ReadMapFromRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLMeanAuthor"), count = 1;
	ReadMapFromRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolAuthor"), count = 1;
	ReadMapFromRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolAuthor"), count = 1;
	ReadMapFromRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjAuthor"), count = 1;
	ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationDateToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("WLSimMethodDate"), count = 1;
	WriteMapToRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLLocDate"), count = 1;
	WriteMapToRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDDate"), count = 1;
	WriteMapToRegistry(CrpsXSpectrumFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDDate"), count = 1;
	WriteMapToRegistry(CrpsYSpectrumFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDDate"), count = 1;
	WriteMapToRegistry(CrpsZSpectrumFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLCohDate"), count = 1;
	WriteMapToRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLDecompDate"), count = 1;
	WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLFreqDate"), count = 1;
	WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLRandDate"), count = 1;
	WriteMapToRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLModDate"), count = 1;
	WriteMapToRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLCorrDate"), count = 1;
	WriteMapToRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLMeanDate"), count = 1;
	WriteMapToRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolDate"), count = 1;
	WriteMapToRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolDate"), count = 1;
	WriteMapToRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjDate"), count = 1;
	WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationDateToRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("WLSimMethodDate"), count = 1;
	ReadMapFromRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLLocDate"), count = 1;
	ReadMapFromRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDDate"), count = 1;
	ReadMapFromRegistry(CrpsXSpectrumFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDDate"), count = 1;
	ReadMapFromRegistry(CrpsYSpectrumFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDDate"), count = 1;
	ReadMapFromRegistry(CrpsZSpectrumFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLCohDate"), count = 1;
	ReadMapFromRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLDecompDate"), count = 1;
	ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLFreqDate"), count = 1;
	ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLRandDate"), count = 1;
	ReadMapFromRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLModDate"), count = 1;
	ReadMapFromRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLCorrDate"), count = 1;
	ReadMapFromRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLMeanDate"), count = 1;
	ReadMapFromRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolDate"), count = 1;
	ReadMapFromRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolDate"), count = 1;
	ReadMapFromRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjDate"), count = 1;
	ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjVersionToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("WLSimMethodVersion"), count = 1;
	WriteMapToRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLLocVersion"), count = 1;
	WriteMapToRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDVersion"), count = 1;
	WriteMapToRegistry(CrpsXSpectrumFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDVersion"), count = 1;
	WriteMapToRegistry(CrpsYSpectrumFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDVersion"), count = 1;
	WriteMapToRegistry(CrpsZSpectrumFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLCohVersion"), count = 1;
	WriteMapToRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLDecompVersion"), count = 1;
	WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLFreqVersion"), count = 1;
	WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLRandVersion"), count = 1;
	WriteMapToRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLModVersion"), count = 1;
	WriteMapToRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLCorrVersion"), count = 1;
	WriteMapToRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLMeanVersion"), count = 1;
	WriteMapToRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolVersion"), count = 1;
	WriteMapToRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolVersion"), count = 1;
	WriteMapToRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjVersion"), count = 1;
	WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjVersionToRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("WLSimMethod"), count = 1;
	ReadMapFromRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLLocVersion"), count = 1;
	ReadMapFromRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLXPSDVersion"), count = 1;
	ReadMapFromRegistry(CrpsXSpectrumFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLYPSDVersion"), count = 1;
	ReadMapFromRegistry(CrpsYSpectrumFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLZPSDVersion"), count = 1;
	ReadMapFromRegistry(CrpsZSpectrumFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLCohVersion"), count = 1;
	ReadMapFromRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLDecompVersion"), count = 1;
	ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLFreqVersion"), count = 1;
	ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLRandVersion"), count = 1;
	ReadMapFromRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLModVersion"), count = 1;
	ReadMapFromRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLCorrVersion"), count = 1;
	ReadMapFromRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLMeanVersion"), count = 1;
	ReadMapFromRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

	settingsGroup = ("WLTableToolVersion"), count = 1;
	ReadMapFromRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolVersion"), count = 1;
	ReadMapFromRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjVersion"), count = 1;
	ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

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

	//
	settingsGroup = ("WLSimMethodTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLLocTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLXPSDTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLYPSDTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLZPSDTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCohTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLDecompTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLFreqTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLRandTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLModTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCorrTitle");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLMeanTitle");
	ClearMapFromRegistry(settingsGroup);

	//
	settingsGroup = ("WLSimMethodLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLLocLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLXPSDLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLYPSDLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLZPSDLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCohLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLDecompLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLFreqLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLRandLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLModLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCorrLink");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLMeanLink");
	ClearMapFromRegistry(settingsGroup);

	//
	settingsGroup = ("WLSimMethodAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLLocAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLXPSDAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLYPSDAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLZPSDAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCohAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLDecompAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLFreqAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLRandAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLModAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCorrAuthor");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLMeanAuthor");
	ClearMapFromRegistry(settingsGroup);

	//
	settingsGroup = ("WLSimMethodDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLLocDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLXPSDDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLYPSDDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLZPSDDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCohDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLDecompDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLFreqDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLRandDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLModDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCorrDate");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLMeanDate");
	ClearMapFromRegistry(settingsGroup);

	//
	settingsGroup = ("WLSimMethodVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLLocVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLXPSDVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLYPSDVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLZPSDVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCohVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLDecompVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLFreqVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLRandVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLModVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLCorrVersion");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("WLMeanVersion");
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
	if (!GetWindLabData().comparisonMode)
	{
		createSimulationWorker();
		connect(simulationWorker, SIGNAL(showWindVelocityOutput()), this, SLOT(displayWindVelocity()));
		emit progressBarShow();
		simulationThread->start();
	}
	else
	{
		if (GetWindLabData().comparisonType == 1) // accuracy
		{
			createComparisonWorker();
			connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareAccuracy()));
			connect(comparisonWorker, SIGNAL(showAccuracyComparisonOutput()), this, SLOT(displayAccuracyComparisonResults()));
			emit progressBarShow();
			comparisonThread->start();
		}
		else if (GetWindLabData().comparisonType == 2) // time
		{
			createComparisonWorker();
			connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareTime()));
			connect(comparisonWorker, SIGNAL(showTimeComparisonOutput()), this, SLOT(displayTimeComparisonResults()));

			emit progressBarShow();
			comparisonThread->start();
		}
		else if (GetWindLabData().comparisonType == 3) // memory
		{
			createComparisonWorker();
			connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareMemory()));
			connect(comparisonWorker, SIGNAL(showMemoryComparisonOutput()), this, SLOT(displayMemoryComparisonResults()));
			emit progressBarShow();
			comparisonThread->start();
		}
	}
}
void RPSWindLabSimulation::pauseSimulation()
{
	// // from https://stackoverflow.com/questions/4093159/what-is-the-correct-way-to-implement-a-qthread-example-please
	// simulationOutputThread = new QThread();
	// simulationOutputWorker = new RPSWindLabSimulationOutputWorker(windLabData, information, locationJ, locationK, frequencyIndex, timeIndex);

	// simulationOutputWorker->moveToThread(simulationOutputThread);

	// connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumXModelOut()));
	// connect(this, SIGNAL(stopped()), simulationOutputWorker, SLOT(stop()), Qt::DirectConnection);

	// // connect(simulationOutputWorker, SIGNAL(destroyed()), simulationOutputThread, SLOT(quit()));
	// // connect(simulationOutputThread, SIGNAL(finished()), simulationOutputThread, SLOT(deleteLater()));

	// connect(simulationOutputWorker, SIGNAL(finished()), simulationOutputThread, SLOT(quit()));
	// connect(simulationOutputWorker, SIGNAL(finished()), simulationOutputWorker, SLOT(deleteLater()));
	// connect(simulationOutputThread, SIGNAL(finished()), simulationOutputThread, SLOT(deleteLater()));

	// connect(simulationOutputWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
	// connect(simulationOutputWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
	// connect(simulationOutputWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

	// //qRegisterMetaType<MatrixXd> >("MatrixXd");
	// connect(simulationOutputWorker, SIGNAL(sendOutputMatrix(MatrixXd)), this, SLOT(receiveOutputMatrix(MatrixXd)), Qt::QueuedConnection);

	// simulationOutputThread->start();

	// qDebug() << "Allowed thread:" << pool.maxThreadCount() ;
	// qDebug() << QThread::idealThreadCount();
	// qDebug() << QThreadPool::globalInstance->maxThreadCount();

	// information.append(QString::number(QThread::idealThreadCount()));
	// information.append(QString::number(QThreadPool::globalInstance->maxThreadCount()));

	// emit sendInformation(information);

	// QFuture<mat> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumXModelOut);

	// mat result = future.result();

	// RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	// ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	// // allocate memory for the table
	// 	Table *table = app->newTable("haha", GetWindLabData().numberOfFrequency, GetWindLabData().numberOfTimeIncrements);

	// 	// fill the table with computed coherence
	// 	for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
	// 	{
	// 		for (int j = 0; j < GetWindLabData().numberOfTimeIncrements; j++)
	// 		{
	// 			table->setCellValue(i, j, result(i,j));
	// 		}
	// 	}

	// 	table->showNormal();

	// QMessageBox::warning(this, "future", QString::number(result.rows()));
}
void RPSWindLabSimulation::stopSimulation()
{
	if (nullptr == simulationThread || !simulationThread->isRunning())
	{
		return;
	}
	information.append("Stopping the simulation...");
	emit sendInformation(information);
	information.clear();
	emit stopped();
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
		// resultOutputType = dlg->resultOutputType;
		GetWindLabData().comparisonType = 1;
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
		resultOutputType = dlg->resultOutputType;
		
		GetWindLabData().comparisonType = 2;

		coherence = dlg->coherence;
		correlation = dlg->correlation;
		frequency = dlg->frequency;
		mean = dlg->mean;
		modulation = dlg->modulation;
		decomposition = dlg->decomposition;
		simulation = dlg->simulation;
		spatial = dlg->spatial;
		randomness = dlg->randomness;
		spectrum = dlg->spectrum;
	}
}
void RPSWindLabSimulation::compareMemoryUsage()
{
	mcompareMemoryUsage = true;
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
		resultOutputType = dlg->resultOutputType;
		
		GetWindLabData().comparisonType = 3;

		coherence = dlg->coherence;
		correlation = dlg->correlation;
		frequency = dlg->frequency;
		mean = dlg->mean;
		modulation = dlg->modulation;
		decomposition = dlg->decomposition;
		simulation = dlg->simulation;
		spatial = dlg->spatial;
		randomness = dlg->randomness;
		spectrum = dlg->spectrum;
	}
}

void RPSWindLabSimulation::comparisonInitial()
{
	int index = 0;
	categories.append(LabRPS::objGroupCoherenceFunction);
	categories.append(LabRPS::objGroupCorrelationFunction);
	categories.append(LabRPS::objGroupFrequencyDistribution);
	categories.append(LabRPS::objGroupMeanWindProfile);
	categories.append(LabRPS::objGroupModulationFunction);
	categories.append(LabRPS::objGroupSpectrumDecompositionMethod);
	categories.append(LabRPS::objGroupSimulationMethod);
	categories.append(LabRPS::objGroupAlongWindSpectrum);
	categories.append(LabRPS::objGroupAcrossWindSpectrum);
	categories.append(LabRPS::objGroupVerticalWindSpectrum);

	functions.append(LabRPS::ComputeCrossCoherenceVectorF);
	categoryFunctionListMap[categories.at(0)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeCrossCorrelationVectorT);
	functions.append(LabRPS::ComputeCrossCorrelationVectorP);
	categoryFunctionListMap[categories.at(1)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeFrequenciesVectorF);
	categoryFunctionListMap[categories.at(2)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeMeanWindSpeedVectorP);
	functions.append(LabRPS::ComputeMeanWindSpeedVectorT);
	categoryFunctionListMap[categories.at(3)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeModulationVectorT);
	functions.append(LabRPS::ComputeModulationVectorF);
	functions.append(LabRPS::ComputeModulationVectorP);
	categoryFunctionListMap[categories.at(4)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeDecomposedCrossSpectrumVectorF);
	functions.append(LabRPS::ComputeDecomposedCrossSpectrumVectorT);
	functions.append(LabRPS::ComputeDecomposedCrossSpectrumVectorP);
	categoryFunctionListMap[categories.at(5)] = functions;
	functions.clear();

	functions.append(LabRPS::Simulate);
	functions.append(LabRPS::SimulateInLargeScaleMode);
	categoryFunctionListMap[categories.at(6)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeXCrossSpectrumVectorF);
	functions.append(LabRPS::ComputeXCrossSpectrumVectorT);
	functions.append(LabRPS::ComputeXCrossSpectrumVectorP);
	categoryFunctionListMap[categories.at(7)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeYCrossSpectrumVectorF);
	functions.append(LabRPS::ComputeYCrossSpectrumVectorT);
	functions.append(LabRPS::ComputeYCrossSpectrumVectorP);
	categoryFunctionListMap[categories.at(8)] = functions;
	functions.clear();

	functions.append(LabRPS::ComputeZCrossSpectrumVectorF);
	functions.append(LabRPS::ComputeZCrossSpectrumVectorT);
	functions.append(LabRPS::ComputeZCrossSpectrumVectorP);
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
	resultOutputType = 1;
}

QStringList RPSWindLabSimulation::FindAllSpatialDistribution()
{
	QStringList theList;
	/////******coherence model start*******/////////
	typedef IrpsWLLocationDistribution *(*CreateLocDistrCallback)();
	std::map<const QString, CreateLocDistrCallback>::iterator locIt;

	// Iterate though the map and show all the registed spectrum models in the combo box
	for (locIt = CrpsLocationDistributionFactory::GetLocDistrNamesMap().begin(); locIt != CrpsLocationDistributionFactory::GetLocDistrNamesMap().end(); ++locIt)
	{
		// Add it to the combo box
		theList.append(locIt->first);
	}

	return theList;
}

QStringList RPSWindLabSimulation::FindAllRandomnessProvider()
{
	QStringList theList;
	/////******coherence model start*******/////////
	typedef IrpsWLRandomness *(*CreateRandomnessCallback)();
	std::map<const QString, CreateRandomnessCallback>::iterator randIt;

	// Iterate though the map and show all the registed spectrum models in the combo box
	for (randIt = CrpsRandomnessFactory::GetRandomnessNamesMap().begin(); randIt != CrpsRandomnessFactory::GetRandomnessNamesMap().end(); ++randIt)
	{
		// Add it to the combo box
		theList.append(randIt->first);
	}

	return theList;
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
		if (1 != GetWindLabData().direction)
		{
			break;
		}
		candidatesComboBox->addItems(FindAllSpectrumModels());
		break;
	case 8:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(8)]);
		if (2 != GetWindLabData().direction)
		{
			break;
		}
		candidatesComboBox->addItems(FindAllSpectrumModels());
		break;
	case 9:
		functionComboBox->addItems(categoryFunctionListMap[categories.at(9)]);
		if (3 != GetWindLabData().direction)
		{
			break;
		}
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
void RPSWindLabSimulation::locationDistributionFunctionInital(QString currentSelected)
{
    // Build an object
    IrpsWLLocationDistribution *currentSelection = CrpsLocationDistributionFactory::BuildLocationDistribution(currentSelected);

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
	emit sendInformation(infoList);
}

void RPSWindLabSimulation::progressBarShowSL()
{
	emit progressBarShow();
}
void RPSWindLabSimulation::progressBarHideSL()
{
	emit progressBarHide();
	qApp->processEvents();
}
void RPSWindLabSimulation::progressBarSetValueSL(int value)
{
	// QMessageBox::warning(0, "1", "in setvalue");
	emit progressBarSetValue(value);
}
void RPSWindLabSimulation::progressBarSetMinSL(int value)
{
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

	if (0 == index || GetWindLabData().numberOfSpatialPosition + 1 == index)
	{
		GetWindLabData().locationJ = 0;
	}
	else if (index > 0 &&
			 index <= GetWindLabData().numberOfSpatialPosition)
	{
		GetWindLabData().locationJ = index - 1;
	}
}
void RPSWindLabSimulation::locKCurrentIndexChanged(int index)
{
	locationK = index;

	if (0 == index || GetWindLabData().numberOfSpatialPosition + 1 == index)
	{
		GetWindLabData().locationK = 0;
	}
	else if (index > 0 &&
			 index <= GetWindLabData().numberOfSpatialPosition)
	{
		GetWindLabData().locationK = index - 1;
	}
}
void RPSWindLabSimulation::freqCurrentIndexChanged(int index)
{
	frequencyIndex = index;

	if (0 == index || GetWindLabData().numberOfFrequency + 1 == index)
	{
		GetWindLabData().frequencyIndex = 0;
	}
	else if (index > 0 &&
			 index <= GetWindLabData().numberOfFrequency)
	{
		GetWindLabData().frequencyIndex = index - 1;
	}
}
void RPSWindLabSimulation::timCurrentIndexChanged(int index)
{
	timeIndex = index;

	if (0 == index || GetWindLabData().numberOfTimeIncrements + 1 == index)
	{
		GetWindLabData().timeIndex = 0;
	}
	else if (index > 0 &&
			 index <= GetWindLabData().numberOfTimeIncrements)
	{
		GetWindLabData().timeIndex = index - 1;
	}
}

void RPSWindLabSimulation::displayLocationDistribution()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the spectrum results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	QTime t;
	t.start();

	// prepare the name of the table
	QString arrayName = "Locations";

	// allocate memory for the table
	Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 3);

	// fill the table with computed coherence
	for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
	{
		table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, 0));
		table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, 1));
		table->setCellValue(i, 2, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, 2));
	}

	table->showNormal();
	information.append(tr("The computed spatial distribution took %1 ms to be displayed").arg(QString::number(t.elapsed())));

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayMeanWindVelocity()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the spectrum results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
		locationK == 0 &&
		frequencyIndex == 0 &&
		timeIndex > 0 &&
		timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Mean (All, None, None, %1)").arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
		information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK == 0 &&
			 frequencyIndex == 0 &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, None, None, All)").arg(locationJ);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
		information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex == 0 &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = "Mean (All, None, None, All)";

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Mean (All, None, None, %1)").arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
		information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayRandomPhase()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the frequency results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
		locationK == 0 &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex == 0)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = "RandomPhase (All, None, All, None)";

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}
		table->showNormal();
		information.append(tr("The computed random phases took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = "RandomPhase (All, None, All, None)";

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}
		table->showNormal();
		information.append(tr("The computed random phases took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayAComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabComparisonWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the comparison results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	QTime t;
	t.start();

	// allocate memory for the table
	Table *table = app->newTable(tableName, row, 3);
	table->setColName(0, variableName);
	table->setColName(1, candidat1);
	table->setColName(2, candidat2);

	// fill the table with computed coherence
	for (int i = 0; i < row; i++)
	{
		table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_resultVectorVariable(i));
		table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_resultVectorCandidate1(i));
		table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_resultVectorCandidate2(i));
	}

	table->showNormal();
	information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayWindVelocitySimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabComparisonWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the comparison results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

    if (!(locationJ > 0 && locationJ <= GetWindLabData().numberOfSpatialPosition))
    {
        GetWindLabData().locationJ = 0;
//        emit GetWindLabComparisonWorker()->finished();
//        return;
    }

	QTime t;
	t.start();

	// allocate memory for the table
	Table *table = app->newTable(tableName, row, 3);
	table->setColName(0, variableName);
	table->setColName(1, candidat1);
	table->setColName(2, candidat2);

	// fill the table with computed coherence
	for (int i = 0; i < row; i++)
	{
		table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_resultVectorVariable(i));
		table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_resultCandidate1(i, GetWindLabData().locationJ));
		table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_resultCandidate2(i, GetWindLabData().locationJ));
	}

	table->showNormal();
	information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayTComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabComparisonWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the comparison results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	QTime t;
	t.start();

	// allocate memory for the table
	Table *table = app->newTable(tableName, row, 3);
	table->setColName(0, variableName);
	table->setColName(1, candidat1);
	table->setColName(2, candidat2);

	// fill the table with computed coherence
	for (int i = 0; i < row; i++)
	{
		table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_resultVectorVariableVec.at(i));
		table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_resultVectorCandidate1Vec.at(i));
		table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_resultVectorCandidate2Vec.at(i));
	}

	table->showNormal();
	information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayWindVelocityLargeScaleSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
	// RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	// ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	// information = information + GetWindLabComparisonWorker()->getInformation();
	// information.append("Please wait. LabRPS is now showing the comparison results...");
	// emit sendInformation(information);
	// emit progressBarHide();

	// qApp->processEvents();
	// information.clear();

	// QTime t;
	// t.start();

	// // allocate memory for the table
	// Table *table = app->newTable(tableName, row, 3);
	// table->setColName(0, variableName);
	// table->setColName(1, candidat1);
	// table->setColName(2, candidat2);

	// // fill the table with computed coherence
	// for (int i = 0; i < row; i++)
	// {
	// 	table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_resultVectorVariable(i));
	// 	table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_resultCandidate1(i, GetWindLabData().locationJ));
	// 	table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_resultCandidate2(i, GetWindLabData().locationJ));
	// }

	// table->showNormal();
	// information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

	// // send info the main window to show it
	// emit sendInformation(information);

	// // clear the information list
	// information.clear();

	// // delete the worker
	// GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayAccuracyComparisonResults()
{
	int count = candidateList.size();
	QString candidate1 = candidateList[0];
    QString comparisonCategory = candidateList[1];
    QString comparisonFunction = candidateList[2];
    QString coherence1 = candidateList[3];
    QString correlation1 = candidateList[4];
    QString frequency1 = candidateList[5];
    QString mean1 = candidateList[6];
    QString modulation1 = candidateList[7];
    QString decomposition1 = candidateList[8];
    QString simulation1 = candidateList[9];
    QString spatial1 = candidateList[10];
    QString randomness1 = candidateList[11];
    QString spectrum1 = candidateList[12];
    
    QString candidate2 = candidateList[13];
    QString coherence2 = candidateList[16];
    QString correlation2 = candidateList[17];
    QString frequency2 = candidateList[18];
    QString mean2 = candidateList[19];
    QString modulation2 = candidateList[20];
    QString decomposition2 = candidateList[21];
    QString simulation2 = candidateList[22];
    QString spatial2 = candidateList[23];
    QString randomness2 = candidateList[24];
    QString spectrum2 = candidateList[25];

	if (comparisonCategory == LabRPS::objGroupCoherenceFunction)
	{
		if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorF)
		{
			displayAComparisonResults(candidate1, candidate2, "CoherenceF", "Frequency", GetWindLabData().numberOfFrequency);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupCorrelationFunction)
	{
		if (comparisonFunction == LabRPS::ComputeCrossCorrelationVectorT)
		{
		}
		else if (comparisonFunction == LabRPS::ComputeCrossCorrelationVectorP)
		{
		}
	}
	else if (comparisonCategory == LabRPS::objGroupFrequencyDistribution)
	{
		if (comparisonFunction == LabRPS::ComputeFrequenciesVectorF)
		{
			displayAComparisonResults(candidate1, candidate2, "Frequency", "Numbering", GetWindLabData().numberOfFrequency);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupMeanWindProfile)
	{
		if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorP)
		{
			displayAComparisonResults(candidate1, candidate2, "MeanP", "Location", GetWindLabData().numberOfSpatialPosition);
		}
		else if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorT)
		{
			displayAComparisonResults(candidate1, candidate2, "MeanT", "Time", GetWindLabData().numberOfTimeIncrements);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupModulationFunction)
	{
		if (comparisonFunction == LabRPS::ComputeModulationVectorT)
		{
			displayAComparisonResults(candidate1, candidate2, "ModulationT", "Time", GetWindLabData().numberOfTimeIncrements);
		}
		else if (comparisonFunction == LabRPS::ComputeModulationVectorF)
		{
			displayAComparisonResults(candidate1, candidate2, "ModulationF", "Frequency", GetWindLabData().numberOfFrequency);
		}
		else if (comparisonFunction == LabRPS::ComputeModulationVectorP)
		{
			displayAComparisonResults(candidate1, candidate2, "ModulationP", "Frequency", GetWindLabData().numberOfSpatialPosition);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupSpectrumDecompositionMethod)
	{
		if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorF)
		{
			displayAComparisonResults(candidate1, candidate2, "DecomposedpsdF", "Frequency", GetWindLabData().numberOfFrequency);
		}
		else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorT)
		{
			displayAComparisonResults(candidate1, candidate2, "DecomposedpsdT", "Time", GetWindLabData().numberOfTimeIncrements);
		}
		else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorP)
		{
			displayAComparisonResults(candidate1, candidate2, "DecomposedpsdP", "Location", GetWindLabData().numberOfSpatialPosition);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupSimulationMethod)
	{
		if (comparisonFunction == LabRPS::Simulate)
		{
			displayWindVelocitySimComparisonResults(candidate1, candidate2, "Velocity", "Time", GetWindLabData().numberOfTimeIncrements);
		}
		else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && GetWindLabData().largeScaleSimulationMode)
		{
			displayWindVelocityLargeScaleSimComparisonResults(candidate1, candidate2, "Velocity", "Time", GetWindLabData().numberOfTimeIncrements);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupAlongWindSpectrum && 1 == GetWindLabData().direction)
	{
		if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorF)
		{
			displayAComparisonResults(candidate1, candidate2, "XSpectrumF", "Frequency", GetWindLabData().numberOfFrequency);
		}
		else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorT)
		{
			displayAComparisonResults(candidate1, candidate2, "XSpectrumT", "Time", GetWindLabData().numberOfTimeIncrements);
		}
		else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorP)
		{
			displayAComparisonResults(candidate1, candidate2, "XSpectrumP", "Location", GetWindLabData().numberOfSpatialPosition);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupAcrossWindSpectrum && 2 == GetWindLabData().direction)
	{
		if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorF)
		{
			displayAComparisonResults(candidate1, candidate2, "YSpectrumF", "Frequency", GetWindLabData().numberOfFrequency);
		}
		else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorT)
		{
			displayAComparisonResults(candidate1, candidate2, "YSpectrumT", "Time", GetWindLabData().numberOfTimeIncrements);
		}
		else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorP)
		{
			displayAComparisonResults(candidate1, candidate2, "YSpectrumP", "Location", GetWindLabData().numberOfSpatialPosition);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupVerticalWindSpectrum && 3 == GetWindLabData().direction)
	{
		if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorF)
		{
			displayAComparisonResults(candidate1, candidate2, "ZSpectrumF", "Frequency", GetWindLabData().numberOfFrequency);
		}
		else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorT)
		{
			displayAComparisonResults(candidate1, candidate2, "ZSpectrumT", "Time", GetWindLabData().numberOfTimeIncrements);
		}
		else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorP)
		{
			displayAComparisonResults(candidate1, candidate2, "ZSpectrumP", "Location", GetWindLabData().numberOfSpatialPosition);
		}
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabComparisonWorker()->finished();
}
void RPSWindLabSimulation::displayTimeComparisonResults()
{
	int count = candidateList.size();
	QString candidate1 = candidateList[0];
    QString comparisonCategory = candidateList[1];
    QString comparisonFunction = candidateList[2];
    QString coherence1 = candidateList[3];
    QString correlation1 = candidateList[4];
    QString frequency1 = candidateList[5];
    QString mean1 = candidateList[6];
    QString modulation1 = candidateList[7];
    QString decomposition1 = candidateList[8];
    QString simulation1 = candidateList[9];
    QString spatial1 = candidateList[10];
    QString randomness1 = candidateList[11];
    QString spectrum1 = candidateList[12];
    
    QString candidate2 = candidateList[13];
    QString coherence2 = candidateList[16];
    QString correlation2 = candidateList[17];
    QString frequency2 = candidateList[18];
    QString mean2 = candidateList[19];
    QString modulation2 = candidateList[20];
    QString decomposition2 = candidateList[21];
    QString simulation2 = candidateList[22];
    QString spatial2 = candidateList[23];
    QString randomness2 = candidateList[24];
    QString spectrum2 = candidateList[25];

	QString variableName;

	if (1 == resultOutputType)
	{
		variableName = "Locations(n)";
	}
	else if (2 == resultOutputType)
	{
		variableName = "Frequencies(n)";
	}
	else if (3 == resultOutputType)
	{
		variableName = "Times(n)";
	}

	if (comparisonCategory == LabRPS::objGroupCoherenceFunction)
	{
		if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorF)
		{
			displayTComparisonResults(candidate1, candidate2, "CoherenceF", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupCorrelationFunction)
	{
		if (comparisonFunction == LabRPS::ComputeCrossCorrelationVectorT)
		{
		}
		else if (comparisonFunction == LabRPS::ComputeCrossCorrelationVectorP)
		{
		}
	}
	else if (comparisonCategory == LabRPS::objGroupFrequencyDistribution)
	{
		if (comparisonFunction == LabRPS::ComputeFrequenciesVectorF)
		{
			displayTComparisonResults(candidate1, candidate2, "Frequency", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupMeanWindProfile)
	{
		if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorP)
		{
			displayTComparisonResults(candidate1, candidate2, "MeanP", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorT)
		{
			displayTComparisonResults(candidate1, candidate2, "MeanT", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupModulationFunction)
	{
		if (comparisonFunction == LabRPS::ComputeModulationVectorT)
		{
			displayTComparisonResults(candidate1, candidate2, "ModulationT", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeModulationVectorF)
		{
			displayTComparisonResults(candidate1, candidate2, "ModulationF", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeModulationVectorP)
		{
			displayTComparisonResults(candidate1, candidate2, "ModulationP", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupSpectrumDecompositionMethod)
	{
		if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorF)
		{
			displayTComparisonResults(candidate1, candidate2, "DecomposedpsdF", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorT)
		{
			displayTComparisonResults(candidate1, candidate2, "DecomposedpsdT", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorP)
		{
			displayTComparisonResults(candidate1, candidate2, "DecomposedpsdP", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupSimulationMethod)
	{
		if (comparisonFunction == LabRPS::Simulate)
		{
			displayWindVelocitySimComparisonResults(candidate1, candidate2, "Velocity", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && GetWindLabData().largeScaleSimulationMode)
		{
			displayWindVelocityLargeScaleSimComparisonResults(candidate1, candidate2, "Velocity", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupAlongWindSpectrum && 1 == GetWindLabData().direction)
	{
		if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorF)
		{
			displayTComparisonResults(candidate1, candidate2, "XSpectrumF", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorT)
		{
			displayTComparisonResults(candidate1, candidate2, "XSpectrumT", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorP)
		{
			displayTComparisonResults(candidate1, candidate2, "XSpectrumP", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupAcrossWindSpectrum && 2 == GetWindLabData().direction)
	{
		if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorF)
		{
			displayTComparisonResults(candidate1, candidate2, "YSpectrumF", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorT)
		{
			displayTComparisonResults(candidate1, candidate2, "YSpectrumT", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorP)
		{
			displayTComparisonResults(candidate1, candidate2, "YSpectrumP", variableName, totalNumber);
		}
	}
	else if (comparisonCategory == LabRPS::objGroupVerticalWindSpectrum && 3 == GetWindLabData().direction)
	{
		if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorF)
		{
			displayTComparisonResults(candidate1, candidate2, "ZSpectrumF", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorT)
		{
			displayTComparisonResults(candidate1, candidate2, "ZSpectrumT", variableName, totalNumber);
		}
		else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorP)
		{
			displayTComparisonResults(candidate1, candidate2, "ZSpectrumP", variableName, totalNumber);
		}
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayMemoryComparisonResults()
{
}

void RPSWindLabSimulation::displayWindVelocity()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	if (nullptr != GetWindLabSimulationWorker())
	{
		information = information + GetWindLabSimulationWorker()->getInformation();
		information.append("Please wait. LabRPS is now showing the random velocity results...");
		emit sendInformation(information);
		information.clear();
		emit progressBarHide();

		// save a copy of the simulated wind velocity
		m_resultMatrix = GetWindLabSimulationWorker()->m_ResultMatrix;
	}
	else if (m_resultMatrix.size() <= 0)
	{
		information.append("Please,run the simulation first.");
		emit sendInformation(information);
		information.clear();
		return;
	}

	qApp->processEvents();
	information.clear();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK == 0 &&
		frequencyIndex == 0 &&
		timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("RandomVelocity (%1, None, None, All)").arg(locationJ);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

		table->setColName(0, "Time");
		table->setColName(1, tr("Location %1").arg(locationJ));

		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, m_resultMatrix(i, locationJ));
		}

		table->showNormal();

		information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ <= GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex == 0 &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = "RandomVelocity (All, None, None, All)";

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition + 1);

		table->setColName(0, "Time");

		for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
		{
			table->setColName(j + 1, tr("Location %1").arg(j + 1));
		}

		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j + 1, m_resultMatrix(i, j));
			}
		}
		table->showNormal();

		information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("RandomVelocity (%1, None, None, All)").arg(locationJ);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

		table->setColName(0, "Time");
		table->setColName(1, tr("Location %1").arg(locationJ));

		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, m_resultMatrix(i, locationJ));
		}

		table->showNormal();

		information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	if (nullptr != GetWindLabSimulationWorker())
	{
		// delete the worker
		GetWindLabSimulationWorker()->finished();
	}
}

void RPSWindLabSimulation::displayFrequencyDistribution()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the frequency results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK == 0 &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex == 0)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, None, All, None)").arg(locationJ);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
		information.append(tr("The computed frequencies took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex == 0)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = "Mean (All, None, All, None)";

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}
		table->showNormal();
		information.append(tr("The computed frequencies took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Mean (%1, None, All, None)").arg(locationJ);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
		information.append(tr("The computed frequencies took %1 ms to be displayed").arg(QString::number(t.elapsed())));
		// information.append("Sorry, there is no function that meet your requirements.");
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayCoherenceWind()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the frequency results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK > 0 &&
		locationK <= GetWindLabData().numberOfSpatialPosition &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex > 0 &&
		timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Coherence (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == GetWindLabData().numberOfSpatialPosition + 1 &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		QTime t;
		t.start();

		// prepare the name of the matrix
		QString arrayName = tr("Coherence (All, All, %1, %2)").arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the matrix
		Matrix *matrix = app->newMatrix(arrayName, GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);
		matrix->setCoordinates(1, GetWindLabData().numberOfSpatialPosition, 1, GetWindLabData().numberOfSpatialPosition);
		// fill the matrix with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				matrix->setText(i, j, QString::number(GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j)));
			}
		}

		matrix->showNormal();
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Coherence (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displaySpectrum()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the spectrum results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK > 0 &&
		locationK <= GetWindLabData().numberOfSpatialPosition &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex > 0 &&
		timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		table->setColName(0, "Frequency");
		table->setColName(1, "Spectrum");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK > 0 &&
			 locationK <= GetWindLabData().numberOfSpatialPosition &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (%1, %2, %3, All)").arg(locationJ).arg(locationK).arg(frequencyIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

		table->setColName(0, "Time");
		table->setColName(1, "Spectrum");

		double timeInr = 0.0;
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (All, None, %1, %2)").arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		table->setColName(0, "Location");
		table->setColName(1, "Spectrum");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == locationJ &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (All, All, %1, %2)").arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the matrix
		Matrix *matrix = app->newMatrix(arrayName, GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);
		matrix->setCoordinates(1, GetWindLabData().numberOfSpatialPosition, 1, GetWindLabData().numberOfSpatialPosition);

		// fill the matrix with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				matrix->setText(i, j, QString::number(GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j)));
			}
		}

		matrix->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (All, None, %1, All)").arg(frequencyIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition + 1);

		table->setColName(0, "Time");

		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (All, None, All, %1)").arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition + 1);

		table->setColName(0, "Frequency");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK > 0 &&
			 locationK <= GetWindLabData().numberOfSpatialPosition &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1

	)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (%1, %2, All, All)").arg(locationJ).arg(locationK);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfFrequency + 1);

		table->setColName(0, "Time");

		double timeInr;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfFrequency; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("Spectrum (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		table->setColName(0, "Frequency");
		table->setColName(1, "Spectrum");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayXSpectrum()
{
	displaySpectrum();
}

void RPSWindLabSimulation::displayYSpectrum()
{
	displaySpectrum();
}

void RPSWindLabSimulation::displayZSpectrum()
{
	displaySpectrum();
}

void RPSWindLabSimulation::displayDecomposedSpectrum()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the spectrum results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK > 0 &&
		locationK <= GetWindLabData().numberOfSpatialPosition &&
		frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
		timeIndex > 0 &&
		timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		table->setColName(0, "Frequency");
		table->setColName(1, "Spectrum");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK > 0 &&
			 locationK <= GetWindLabData().numberOfSpatialPosition &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (%1, %2, %3, All)").arg(locationJ).arg(locationK).arg(frequencyIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

		table->setColName(0, "Time");
		table->setColName(1, "Spectrum");

		double timeInr = 0.0;
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (All, None, %1, %2)").arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		table->setColName(0, "Location");
		table->setColName(1, "Spectrum");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == locationJ &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (All, All, %1, %2)").arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the matrix
		Matrix *matrix = app->newMatrix(arrayName, GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);
		matrix->setCoordinates(1, GetWindLabData().numberOfSpatialPosition, 1, GetWindLabData().numberOfSpatialPosition);

		// fill the matrix with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				matrix->setText(i, j, QString::number(GetWindLabSimulationOutputWorker()->m_ResultMatrix2(i, j)));
			}
		}

		matrix->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1

	)
	{

		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (All, None, %1, All)").arg(frequencyIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition + 1);

		table->setColName(0, "Time");

		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements

	)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (All, None, All, %1)").arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition + 1);

		table->setColName(0, "Frequency");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK > 0 &&
			 locationK <= GetWindLabData().numberOfSpatialPosition &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1

	)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (%1, %2, All, All)").arg(locationJ).arg(locationK);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfFrequency + 1);

		table->setColName(0, "Time");

		double timeInr;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfFrequency; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = psdPrefix + tr("DecomposedSpectrum (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		table->setColName(0, "Frequency");
		table->setColName(1, "Spectrum");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayCorrelationWind()
{
}
void RPSWindLabSimulation::displayModulationWind()
{
	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	information = information + GetWindLabSimulationOutputWorker()->getInformation();
	information.append("Please wait. LabRPS is now showing the spectrum results...");
	emit sendInformation(information);
	emit progressBarHide();

	qApp->processEvents();
	information.clear();

	if (locationJ > 0 &&
		locationJ <= GetWindLabData().numberOfSpatialPosition &&
		locationK == 0 &&
		frequencyIndex > 0 &&
		frequencyIndex <= GetWindLabData().numberOfFrequency &&
		timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Modulation (%1, None, %2, All)").arg(locationJ).arg(frequencyIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

		table->setColName(0, "Time");
		table->setColName(1, "Modulation");

		double timeInr = 0.0;
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK == 0 &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Modulation (%1, None, All, %2)").arg(locationJ).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

		table->setColName(0, "Frequency");
		table->setColName(1, "Modulation");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Modulation (All, None, %1, %2)").arg(frequencyIndex).arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

		table->setColName(0, "Locations");
		table->setColName(1, "Modulation");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
		{
			table->setCellValue(i, 0, i + 1);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();
		information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex > 0 &&
			 frequencyIndex <= GetWindLabData().numberOfFrequency &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Modulation (All, None, %1, All)").arg(frequencyIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition + 1);

		table->setColName(0, "Time");

		double timeInr = 0.0;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
			 locationK == 0 &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex > 0 &&
			 timeIndex <= GetWindLabData().numberOfTimeIncrements)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Modulation (All, None, All, %1)").arg(timeIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition + 1);

		table->setColName(0, "Frequency");

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
		{
			table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));

			for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else if (locationJ > 0 &&
			 locationJ <= GetWindLabData().numberOfSpatialPosition &&
			 locationK == 0 &&
			 frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
			 timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Modulation (%1, None, All, All)").arg(locationJ);

		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfFrequency + 1);

		table->setColName(0, "Time");

		double timeInr;

		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

			table->setCellValue(i, 0, timeInr);

			for (int j = 0; j < GetWindLabData().numberOfFrequency; j++)
			{
				table->setCellValue(i, j + 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
			}
		}

		table->showNormal();

		information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}
	else
	{
		QTime t;
		t.start();

		// prepare the name of the table
		QString arrayName = tr("Modulation (%1, None, %2, All)").arg(locationJ).arg(frequencyIndex);

		// allocate memory for the table
		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

		table->setColName(0, "Time");
		table->setColName(1, "Modulation");

		double timeInr = 0.0;
		// fill the table with computed coherence
		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
		{
			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
			table->setCellValue(i, 0, timeInr);
			table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
		}

		table->showNormal();

		information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
	}

	// send info the main window to show it
	emit sendInformation(information);

	// clear the information list
	information.clear();

	// delete the worker
	GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::save(XmlStreamWriter *xmlwriter)
{

	xmlwriter->writeStartElement("windLab");
	saveWindLabData(xmlwriter);
	xmlwriter->writeEndElement();
}

bool RPSWindLabSimulation::load(XmlStreamReader *xmlreader)
{

	if (xmlreader->isStartElement() && xmlreader->name() == "windLab")
	{
		loadWindLabData(xmlreader);
	}
	else // no element
	{
		xmlreader->raiseError(tr("no windLab element found"));
	}

	return !xmlreader->hasError();
}

void RPSWindLabSimulation::saveWindLabData(XmlStreamWriter *xmlwriter)
{

	(windLabData.stationarity) ? xmlwriter->writeAttribute("stationarity", "true")
							   : xmlwriter->writeAttribute("stationarity", "false");
	(windLabData.gaussianity) ? xmlwriter->writeAttribute("gaussianity", "true")
							  : xmlwriter->writeAttribute("gaussianity", "false");
	(windLabData.comparisonMode) ? xmlwriter->writeAttribute("comparisonMode", "true")
								 : xmlwriter->writeAttribute("comparisonMode", "false");
	(windLabData.largeScaleSimulationMode) ? xmlwriter->writeAttribute("largeScaleSimulationMode", "true")
										   : xmlwriter->writeAttribute("largeScaleSimulationMode", "false");

	xmlwriter->writeAttribute("numberOfSpatialPosition", QString::number(windLabData.numberOfSpatialPosition));
	xmlwriter->writeAttribute("numberOfFrequency", QString::number(windLabData.numberOfFrequency));
	xmlwriter->writeAttribute("numberOfSample", QString::number(windLabData.numberOfSample));
	xmlwriter->writeAttribute("direction", QString::number(windLabData.direction));
	xmlwriter->writeAttribute("frequencyDistrType", QString::number(windLabData.frequencyDistrType));
	xmlwriter->writeAttribute("numberOfTimeIncrements", QString::number(windLabData.numberOfTimeIncrements));
	xmlwriter->writeAttribute("frequencyIncrement", QString::number(windLabData.frequencyIncrement));
	xmlwriter->writeAttribute("timeIncrement", QString::number(windLabData.timeIncrement));
	xmlwriter->writeAttribute("minTime", QString::number(windLabData.minTime));
	xmlwriter->writeAttribute("maxTime", QString::number(windLabData.maxTime));
	xmlwriter->writeAttribute("minFrequency", QString::number(windLabData.minFrequency));
	xmlwriter->writeAttribute("maxFrequency", QString::number(windLabData.maxFrequency));
	xmlwriter->writeAttribute("locationJ", QString::number(windLabData.locationJ));
	xmlwriter->writeAttribute("locationK", QString::number(windLabData.locationK));
	xmlwriter->writeAttribute("frequencyIndex", QString::number(windLabData.frequencyIndex));
	xmlwriter->writeAttribute("directionIndex", QString::number(windLabData.directionIndex));
	xmlwriter->writeAttribute("timeIndex", QString::number(windLabData.timeIndex));
	xmlwriter->writeAttribute("numberOfTimeLags", QString::number(windLabData.numberOfTimeLags));

	xmlwriter->writeAttribute("spatialDistribution", windLabData.spatialDistribution);
	xmlwriter->writeAttribute("shearVelocity", windLabData.shearVelocity);
	xmlwriter->writeAttribute("meanFunction", windLabData.meanFunction);
	xmlwriter->writeAttribute("spectrumModel", windLabData.spectrumModel);
	xmlwriter->writeAttribute("coherenceFunction", windLabData.coherenceFunction);
	xmlwriter->writeAttribute("simulationApproach", windLabData.simulationApproach);
	xmlwriter->writeAttribute("simulationMethod", windLabData.simulationMethod);
	xmlwriter->writeAttribute("freqencyDistribution", windLabData.freqencyDistribution);
	xmlwriter->writeAttribute("cpsdDecompositionMethod", windLabData.cpsdDecompositionMethod);
	xmlwriter->writeAttribute("randomnessProvider", windLabData.randomnessProvider);
	xmlwriter->writeAttribute("modulationFunction", windLabData.modulationFunction);
	xmlwriter->writeAttribute("correlationFunction", windLabData.correlationFunction);
	xmlwriter->writeAttribute("varianceFunction", windLabData.varianceFunction);
	xmlwriter->writeAttribute("workingDirPath", windLabData.workingDirPath);
	xmlwriter->writeAttribute("comparisonCategory", windLabData.comparisonCategory);
}

bool RPSWindLabSimulation::loadWindLabData(XmlStreamReader *xmlreader)
{

	bool ok;
	bool bvalue;
	int ivalue;
	double dvalue;
	QString svalue;

	bvalue = xmlreader->readAttributeBool("stationarity", &ok);
	if (ok)
	{
		windLabData.stationarity = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Stationarity setting error");
	}

	bvalue = xmlreader->readAttributeBool("gaussianity", &ok);
	if (ok)
	{
		windLabData.gaussianity = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Gaussianity setting error");
	}

	bvalue = xmlreader->readAttributeBool("comparisonMode", &ok);
	if (ok)
	{
		windLabData.comparisonMode = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Comparison mode setting error");
	}

	bvalue = xmlreader->readAttributeBool("largeScaleSimulationMode", &ok);
	if (ok)
	{
		windLabData.largeScaleSimulationMode = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Large scale simulation mode setting error");
	}

	ivalue = xmlreader->readAttributeInt("numberOfSpatialPosition", &ok);
	if (ok)
	{
		windLabData.numberOfSpatialPosition = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Number of spatial postion setting error");
	}

	ivalue = xmlreader->readAttributeInt("numberOfFrequency", &ok);
	if (ok)
	{
		windLabData.numberOfFrequency = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Number of frequency setting error");
	}

	ivalue = xmlreader->readAttributeInt("numberOfSample", &ok);
	if (ok)
	{
		windLabData.numberOfSample = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Number of sample setting error");
	}

	ivalue = xmlreader->readAttributeInt("direction", &ok);
	if (ok)
	{
		windLabData.direction = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Wind direction setting error");
	}

	ivalue = xmlreader->readAttributeInt("frequencyDistrType", &ok);
	if (ok)
	{
		windLabData.frequencyDistrType = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Frequency distribution type setting error");
	}

	ivalue = xmlreader->readAttributeInt("numberOfTimeIncrements", &ok);
	if (ok)
	{
		windLabData.numberOfTimeIncrements = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Number of time increments setting error");
	}

	ivalue = xmlreader->readAttributeInt("locationJ", &ok);
	if (ok)
	{
		windLabData.locationJ = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Location J index setting error");
	}

	ivalue = xmlreader->readAttributeInt("locationK", &ok);
	if (ok)
	{
		windLabData.locationK = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Location K index setting error");
	}

	ivalue = xmlreader->readAttributeInt("frequencyIndex", &ok);
	if (ok)
	{
		windLabData.frequencyIndex = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Frequency index setting error");
	}

	ivalue = xmlreader->readAttributeInt("directionIndex", &ok);
	if (ok)
	{
		windLabData.directionIndex = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Direction index setting error");
	}

	ivalue = xmlreader->readAttributeInt("timeIndex", &ok);
	if (ok)
	{
		windLabData.timeIndex = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Time index setting error");
	}

	ivalue = xmlreader->readAttributeInt("numberOfTimeLags", &ok);
	if (ok)
	{
		windLabData.numberOfTimeLags = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Number of time lags setting error");
	}

	dvalue = xmlreader->readAttributeDouble("frequencyIncrement", &ok);
	if (ok)
	{
		windLabData.frequencyIncrement = dvalue;
	}
	else
	{
		xmlreader->raiseWarning("Frequency increment setting error");
	}

	dvalue = xmlreader->readAttributeDouble("timeIncrement", &ok);
	if (ok)
	{
		windLabData.timeIncrement = dvalue;
	}
	else
	{
		xmlreader->raiseWarning("Time increment setting error");
	}

	dvalue = xmlreader->readAttributeDouble("minTime", &ok);
	if (ok)
	{
		windLabData.minTime = dvalue;
	}
	else
	{
		xmlreader->raiseWarning("Minimum time setting error");
	}

	dvalue = xmlreader->readAttributeDouble("maxTime", &ok);
	if (ok)
	{
		windLabData.maxTime = dvalue;
	}
	else
	{
		xmlreader->raiseWarning("Maximum time setting error");
	}

	dvalue = xmlreader->readAttributeDouble("minFrequency", &ok);
	if (ok)
	{
		windLabData.minFrequency = dvalue;
	}
	else
	{
		xmlreader->raiseWarning("Minimum frequency setting error");
	}

	dvalue = xmlreader->readAttributeDouble("maxFrequency", &ok);
	if (ok)
	{
		windLabData.maxFrequency = dvalue;
	}
	else
	{
		xmlreader->raiseWarning("Maximum frequency setting error");
	}

	svalue = xmlreader->readAttributeString("spatialDistribution", &ok);
	if (ok)
	{
		windLabData.spatialDistribution = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Spatial distribution setting error");
	}

	svalue = xmlreader->readAttributeString("shearVelocity", &ok);
	if (ok)
	{
		windLabData.shearVelocity = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Shear velocity setting error");
	}

	svalue = xmlreader->readAttributeString("meanFunction", &ok);
	if (ok)
	{
		windLabData.meanFunction = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Mean function setting error");
	}

	svalue = xmlreader->readAttributeString("spectrumModel", &ok);
	if (ok)
	{
		windLabData.spectrumModel = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Spectrum model setting error");
	}

	svalue = xmlreader->readAttributeString("coherenceFunction", &ok);
	if (ok)
	{
		windLabData.coherenceFunction = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Coherence function setting error");
	}

	svalue = xmlreader->readAttributeString("simulationApproach", &ok);
	if (ok)
	{
		windLabData.simulationApproach = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Simulation approach setting error");
	}

	svalue = xmlreader->readAttributeString("simulationMethod", &ok);
	if (ok)
	{
		windLabData.simulationMethod = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Simulation method setting error");
	}

	svalue = xmlreader->readAttributeString("freqencyDistribution", &ok);
	if (ok)
	{
		windLabData.freqencyDistribution = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Frequency distribution setting error");
	}

	svalue = xmlreader->readAttributeString("cpsdDecompositionMethod", &ok);
	if (ok)
	{
		windLabData.cpsdDecompositionMethod = svalue;
	}
	else
	{
		xmlreader->raiseWarning("cpsd decompositionMethod setting error");
	}

	svalue = xmlreader->readAttributeString("randomnessProvider", &ok);
	if (ok)
	{
		windLabData.randomnessProvider = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Randomness provider setting error");
	}

	svalue = xmlreader->readAttributeString("modulationFunction", &ok);
	if (ok)
	{
		windLabData.modulationFunction = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Modulation function setting error");
	}

	svalue = xmlreader->readAttributeString("correlationFunction", &ok);
	if (ok)
	{
		windLabData.correlationFunction = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Correlation function setting error");
	}

	svalue = xmlreader->readAttributeString("varianceFunction", &ok);
	if (ok)
	{
		windLabData.varianceFunction = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Variance function setting error");
	}

	svalue = xmlreader->readAttributeString("workingDirPath", &ok);
	if (ok)
	{
		windLabData.workingDirPath = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Working directory path setting error");
	}

	svalue = xmlreader->readAttributeString("comparisonCategory", &ok);
	if (ok)
	{
		windLabData.comparisonCategory = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Comparison category setting error");
	}

	return !xmlreader->hasError();
}

void RPSWindLabSimulation::createOutputWorker()
{
	// create a worker
	simulationOutputWorker = new RPSWindLabSimulationOutputWorker(windLabData, information, locationJ, locationK, frequencyIndex, timeIndex);

	// create a new thread and attach the worker to it
	simulationOutputThread = new QThread(this);
	simulationOutputWorker->moveToThread(simulationOutputThread);

	// add the functionality to stop the outputing process
	connect(this, SIGNAL(stopped()), simulationOutputWorker, SLOT(stop()), Qt::DirectConnection);

	connect(simulationOutputWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
	connect(simulationOutputWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
	connect(simulationOutputWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

	// add the functionaly to delete the worker after work is done
	connect(simulationOutputWorker, SIGNAL(finished()), simulationOutputWorker, SLOT(deleteLater()));
}

void RPSWindLabSimulation::createSimulationWorker()
{
	// create a worker
	simulationWorker = new RPSWindLabSimulationWorker(windLabData, information, locationJ, locationK, frequencyIndex, timeIndex);

	// create a new thread and attach the worker to it
	simulationThread = new QThread(this);
	simulationWorker->moveToThread(simulationThread);

	// Make the worker watch when the thread starts then let the worker start simulation
	connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(simulate()));

	// add the functionality to stop the outputing process
	connect(this, SIGNAL(stopped()), simulationWorker, SLOT(stop()), Qt::DirectConnection);
	connect(simulationWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
	connect(simulationWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
	connect(simulationWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

	// // add the functionaly to delete the worker after work is done
	// connect(simulationWorker, SIGNAL(finished()), simulationThread, SLOT(quit()));
	// connect(simulationWorker, SIGNAL(finished()), simulationWorker, SLOT(deleteLater()));
	// connect(simulationThread, SIGNAL(finished()), simulationThread, SLOT(deleteLater()));

	// add the functionaly to delete the worker after work is done
	connect(simulationWorker, SIGNAL(finished()), simulationWorker, SLOT(deleteLater()));
}

void RPSWindLabSimulation::createComparisonWorker()
{
	// create a worker
	comparisonWorker = new RPSWindLabComparisonWorker(windLabData,
													  information,
													  locationJ,
													  locationK,
													  frequencyIndex,
													  timeIndex,
													  candidateList,
													  resultOutputType,
													  minNumberOfLocation,
													  minNumberOfFrequency,
													  minNumberOfTime,
													  numberOfLocationIncrement,
													  numberOfFrequencyIncrement,
													  numberOfTimeIncrement,
													  totalNumber,
													  coherence,
													  correlation,
													  frequency,
													  mean,
													  modulation,
													  decomposition,
													  simulation,
													  spatial,
													  randomness,
													  spectrum);

	// create a new thread and attach the worker to it
	comparisonThread = new QThread(this);
	comparisonWorker->moveToThread(comparisonThread);

	// add the functionality to stop the outputing process
	connect(this, SIGNAL(stopped()), comparisonWorker, SLOT(stop()), Qt::DirectConnection);
	connect(comparisonWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
	connect(comparisonWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
	connect(comparisonWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

	// // add the functionaly to delete the worker after work is done
	// connect(comparisonWorker, SIGNAL(finished()), comparisonThread, SLOT(quit()));
	// connect(comparisonWorker, SIGNAL(finished()), comparisonWorker, SLOT(deleteLater()));
	// connect(comparisonThread, SIGNAL(finished()), comparisonThread, SLOT(deleteLater()));

	// add the functionaly to delete the worker after work is done
	connect(comparisonWorker, SIGNAL(finished()), comparisonWorker, SLOT(deleteLater()));
}
