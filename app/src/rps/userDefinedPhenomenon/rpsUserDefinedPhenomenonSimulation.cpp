#include "rpsUserDefinedPhenomenonSimulation.h"

#include "RPSUserDefinedPhenomenonAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenonsimuoptionsdlg.h"
#include "rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenondefinitiondlg.h"
#include "rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenoncomparisondialog.h"
#include "rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenonaccuracycomparisondialog.h"
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

RPSUserDefinedPhenomenonSimulation::RPSUserDefinedPhenomenonSimulation(QWidget *parent) : QWidget(parent)
{
    phenomenonIndex = 0;
    indexSetIndex = 0;

	// initialize simulation data
	simuDataInitialize();

    UDPReadAllTobeInstallObjVersionToRegistry();
    UDPReadAllTobeInstallObjPublicationTitleToRegistry();
    UDPReadAllTobeInstallObjPublicationLinkToRegistry();
    UDPReadAllTobeInstallObjPublicationAuthorToRegistry();
    UDPReadAllTobeInstallObjPublicationDateToRegistry();

    // read install userDefinedPhenomenon from registry if any
    UDPReadAllTobeInstallObjectsFromRegistry();
    UDPClearAllTobeInstallObjectsFromRegistry();

    // comparison
    comparisonInitial();
}

RPSUserDefinedPhenomenonSimulation::~RPSUserDefinedPhenomenonSimulation()
{
    // write install windLab from registry if any

    UDPWriteAllTobeInstallObjPublicationTitleToRegistry();
    UDPWriteAllTobeInstallObjPublicationLinkToRegistry();
    UDPWriteAllTobeInstallObjPublicationAuthorToRegistry();
    UDPWriteAllTobeInstallObjPublicationDateToRegistry();
    UDPWriteAllTobeInstallObjVersionToRegistry();

    UDPWriteAllTobeInstallObjectsToRegistry();

    if(nullptr != comparisonThread)
    {
        QMessageBox::warning(0, "User Defined Phenomenon", "worker thread still running.");
        comparisonThread->exit(0);
        comparisonThread->wait(); // <-- wits till the thread has exited
        deleteLater(); // <-- ensures that it will be deleted later when the (main?) event loop executes again
    }
}

void RPSUserDefinedPhenomenonSimulation::userDefinedPhenomenon()
{
	std::unique_ptr<RPSUserDefinedPhenomenonDefinitionDlg> dlg(new RPSUserDefinedPhenomenonDefinitionDlg(this));

    if (dlg->exec() == QDialog::Accepted)
	{
		GetUserDefinedPhenomenonSimulationData().numberOfSample = dlg->numberOfSample;
		GetUserDefinedPhenomenonSimulationData().stationarity = dlg->stationarity;
		GetUserDefinedPhenomenonSimulationData().gaussianity = dlg->gaussianity;
        GetUserDefinedPhenomenonSimulationData().numberOfProcess = dlg->numberOfProcess;
        GetUserDefinedPhenomenonSimulationData().indexSetSize = dlg->indexSetSize;
        GetUserDefinedPhenomenonSimulationData().indexIncrement = dlg->indexIncrement;
        GetUserDefinedPhenomenonSimulationData().minIndexSetValue = dlg->minIndexSetValue;
        GetUserDefinedPhenomenonSimulationData().maxIndexSetValue = dlg->maxIndexSetValue;
        GetUserDefinedPhenomenonSimulationData().userDefinedPhenomenon = dlg->userDefinedPhenomenon;

		// update the statusbar combobox content

		RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
		rpsSimulator->fillLocationJComboBox();
		rpsSimulator->fillTimeComboBox();
	}
}

void RPSUserDefinedPhenomenonSimulation::userDefinedPhenomenonOutput()
{
	if (GetUserDefinedPhenomenonSimulationData().isSimulationSuccessful == true)
	{
        displayUserDefinedPhenomenon();
	}
	else
	{
		information.append("Please make sure you successfully run a simulation first");
		emit sendInformation(information);
	}
}


CRPSUserDefinedPhenomenonSimuData &RPSUserDefinedPhenomenonSimulation::GetUserDefinedPhenomenonSimulationData()
{
	return simuData;
}

RPSUserDefinedPhenomenonSimulationOutputWorker *RPSUserDefinedPhenomenonSimulation::GetUserDefinedPhenomenonSimulationOutputWorker()
{
	return simulationOutputWorker;
}

RPSUserDefinedPhenomenonSimulationWorker *RPSUserDefinedPhenomenonSimulation::GetUserDefinedPhenomenonSimulationWorker()
{
	return simulationWorker;
}

RPSUserDefinedPhenomenonComparisonWorker *RPSUserDefinedPhenomenonSimulation::GetUserDefinedPhenomenonComparisonWorker()
{
    return comparisonWorker;
}


void RPSUserDefinedPhenomenonSimulation::simuDataInitialize()
{
    simuData.numberOfProcess = 3;
	simuData.numberOfSample = 1;
    simuData.simulationApproach = "Spectral Representation Approach";
    simuData.simulationMethod = "Deodatis et al 1987";
    simuData.stationarity = true;
	simuData.gaussianity = true;
	simuData.comparisonMode = false;
	simuData.largeScaleSimulationMode = false;
    simuData.comparisonCategory = LabRPS::objGroupSimulationMethod;
	simuData.comparisonType = 1;
	simuData.isInterruptionRequested = false;
	simuData.isSimulationSuccessful = false;
    simuData.indexSetSize = 1000;
    simuData.indexIncrement = 0.001;
    simuData.minIndexSetValue = 0;
    simuData.maxIndexSetValue = 1000;

}

void RPSUserDefinedPhenomenonSimulation::WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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

void RPSUserDefinedPhenomenonSimulation::ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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

void RPSUserDefinedPhenomenonSimulation::WriteMapToRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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

void RPSUserDefinedPhenomenonSimulation::ReadMapFromRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
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

void RPSUserDefinedPhenomenonSimulation::UDPWriteAllTobeInstallObjectsToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("UDPSimMethod"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPReadAllTobeInstallObjectsFromRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("UDPSimMethod"), count = 1;
    ReadMapFromRegistry2(CrpsUserDefinedPhenomenonFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPWriteAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("UDPSimMethodTitle"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedPhenomenonFactory::GetTitleMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPReadAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("UDPSimMethodTitle"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedPhenomenonFactory::GetTitleMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPWriteAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("UDPSimMethodLink"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedPhenomenonFactory::GetLinkMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPReadAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("UDPSimMethodLink"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedPhenomenonFactory::GetLinkMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPWriteAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("UDPSimMethodAuthor"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedPhenomenonFactory::GetAuthorMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPReadAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("UDPSimMethodAuthor"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedPhenomenonFactory::GetAuthorMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPWriteAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("UDPSimMethodDate"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedPhenomenonFactory::GetDateMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPReadAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("UDPSimMethodDate"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedPhenomenonFactory::GetDateMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPWriteAllTobeInstallObjVersionToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("UDPSimMethodVersion"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedPhenomenonFactory::GetVersionMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPReadAllTobeInstallObjVersionToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("UDPSimMethod"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedPhenomenonFactory::GetVersionMap(), settingsGroup, count);
}

void RPSUserDefinedPhenomenonSimulation::UDPClearAllTobeInstallObjectsFromRegistry()
{
    QString settingsGroup;

    settingsGroup = ("UDPSimMethod");
    ClearMapFromRegistry(settingsGroup);

     //
    settingsGroup = ("UDPSimMethodTitle");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = ("UDPSimMethodLink");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = ("UDPSimMethodAuthor");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = ("UDPSimMethodDate");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = ("UDPSimMethodVersion");
    ClearMapFromRegistry(settingsGroup);
}

void RPSUserDefinedPhenomenonSimulation::ClearMapFromRegistry(QString &settingsGroup)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.remove(""); // removes the group, and all it keys
    settings.endGroup();
}
bool RPSUserDefinedPhenomenonSimulation::GetObjects(std::map<const QString, QString> &map, QStringList &lstObject, QString pluginName)
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

bool RPSUserDefinedPhenomenonSimulation::GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.clear();

	try
	{
		GetObjects(CrpsUserDefinedPhenomenonFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSUserDefinedPhenomenonSimulation::GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.clear();
	try
	{
		GetObjects(CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSUserDefinedPhenomenonSimulation::IsObjectInstalled(QString &object)
{
	if (IsThisObjectInstalled(CrpsUserDefinedPhenomenonFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	
	return false;
}

bool RPSUserDefinedPhenomenonSimulation::UpdateObjectsMap(std::map<const QString, QString> &map, const QString &lstObject)
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

bool RPSUserDefinedPhenomenonSimulation::UpdateObjectToSkipMap(std::map<const QString, QString> &map, const QString name, const QString pluginName)
{
	map[name] = pluginName;
	return true;
}

bool RPSUserDefinedPhenomenonSimulation::UpdateToBeInstalledObjectsMap(const QString &lstObject)
{
	try
	{
		UpdateObjectsMap(CrpsUserDefinedPhenomenonFactory::GetTobeInstalledObjectsMap(), lstObject);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSUserDefinedPhenomenonSimulation::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
	try
	{
		UpdateObjectToSkipMap(CrpsUserDefinedPhenomenonFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSUserDefinedPhenomenonSimulation::IsThisObjectInstalled(std::map<const QString, QString> &map, QString &object)
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


void RPSUserDefinedPhenomenonSimulation::runSimulation()
{

    if (!GetUserDefinedPhenomenonSimulationData().comparisonMode)
    {
        createSimulationWorker();
        connect(simulationWorker, SIGNAL(showUserDefinedPhenomenonOutput()), this, SLOT(displayUserDefinedPhenomenon()));
        emit progressBarShow();
        simulationThread->start();
    }
    else
    {
        if (GetUserDefinedPhenomenonSimulationData().comparisonType == 1) // accuracy
        {
            createComparisonWorker();
            connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareAccuracy()));
            connect(comparisonWorker, SIGNAL(showAccuracyComparisonOutput()), this, SLOT(displayAccuracyComparisonResults()));
            emit progressBarShow();
            comparisonThread->start();
        }
        else if (GetUserDefinedPhenomenonSimulationData().comparisonType == 2) // time
        {
            createComparisonWorker();
            connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareTime()));
            connect(comparisonWorker, SIGNAL(showTimeComparisonOutput()), this, SLOT(displayTimeComparisonResults()));

            emit progressBarShow();
            comparisonThread->start();
        }
        else if (GetUserDefinedPhenomenonSimulationData().comparisonType == 3) // memory
        {
            createComparisonWorker();
            connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareMemory()));
            connect(comparisonWorker, SIGNAL(showMemoryComparisonOutput()), this, SLOT(displayMemoryComparisonResults()));
            emit progressBarShow();
            comparisonThread->start();
        }
    }
}

void RPSUserDefinedPhenomenonSimulation::pauseSimulation()
{

}
void RPSUserDefinedPhenomenonSimulation::stopSimulation()
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

void RPSUserDefinedPhenomenonSimulation::simulationOptions()
{
    std::unique_ptr<RPSUserDefinedPhenomenonSimuOptionsDlg> dlg(new RPSUserDefinedPhenomenonSimuOptionsDlg(this));
	if (dlg->exec() == QDialog::Accepted)
	{
		GetUserDefinedPhenomenonSimulationData().simulationMethod = dlg->currentsimulationMethod;
		GetUserDefinedPhenomenonSimulationData().comparisonMode = dlg->comparisonMode;
		GetUserDefinedPhenomenonSimulationData().largeScaleSimulationMode = dlg->largeScaleMode;
	}
}

void RPSUserDefinedPhenomenonSimulation::compareAccuracy()
{
     std::unique_ptr<RPSUserDefinedPhenomenonAccuracyComparisonDialog> dlg(new RPSUserDefinedPhenomenonAccuracyComparisonDialog(this));
     if (dlg->exec() == QDialog::Accepted)
     {
        comparisonCategory = dlg->comparisonCategory;
        comparisonFunction = dlg->comparisonFunction;
        comparisonCandidate = dlg->comparisonCandidate;
        resultOutputType = dlg->resultOutputType;
        GetUserDefinedPhenomenonSimulationData().comparisonType = 1;
     }
}
void RPSUserDefinedPhenomenonSimulation::compareComputationTime()
{
     mcompareComputationTime = true;
     std::unique_ptr<RPSUserDefinedPhenomenonComparisonDialog> dlg(new RPSUserDefinedPhenomenonComparisonDialog(this));
     if (dlg->exec() == QDialog::Accepted)
     {
        mcompareComputationTime = dlg->compareComputationTime;
        mcompareMemoryUsage = dlg->compareMemoryUsage;
        comparisonCategory = dlg->comparisonCategory;
        comparisonFunction = dlg->comparisonFunction;
        comparisonCandidate = dlg->comparisonCandidate;
        minNumberOfProcess = dlg->minNumberOfProcess;
        minNumberOfIndexSetIndex = dlg->minNumberOfIndexSetIndex;
        minNumberOfSample = dlg->minNumberOfSample;
        numberOfProcessIncrement = dlg->numberOfProcessIncrement;
        numberOfIndexSetIndexIncrement = dlg->numberOfIndexSetIndexIncrement;
        numberOfSampleIncrement = dlg->numberOfSampleIncrement;
        totalNumber = dlg->totalNumber;
        resultOutputType = dlg->resultOutputType;
		
        GetUserDefinedPhenomenonSimulationData().comparisonType = 2;

        _userDefinedPhenomenon = dlg->userDefinedPhenomenon;
     }
}
void RPSUserDefinedPhenomenonSimulation::compareMemoryUsage()
{
	// mcompareMemoryUsage = true;
	// std::unique_ptr<RPSWLComparisonDialog> dlg(new RPSWLComparisonDialog(this));
	// if (dlg->exec() == QDialog::Accepted)
	// {
	// 	mcompareComputationTime = dlg->compareComputationTime;
	// 	mcompareMemoryUsage = dlg->compareMemoryUsage;
	// 	comparisonCategory = dlg->comparisonCategory;
	// 	comparisonFunction = dlg->comparisonFunction;
	// 	comparisonCandidate = dlg->comparisonCandidate;
	// 	minNumberOfLocation = dlg->minNumberOfLocation;
	// 	minNumberOfFrequency = dlg->minNumberOfFrequency;
	// 	minNumberOfTime = dlg->minNumberOfTime;
	// 	numberOfLocationIncrement = dlg->numberOfLocationIncrement;
	// 	numberOfFrequencyIncrement = dlg->numberOfFrequencyIncrement;
	// 	numberOfTimeIncrement = dlg->numberOfTimeIncrement;
	// 	totalNumber = dlg->totalNumber;
	// 	resultOutputType = dlg->resultOutputType;
		
	// 	GetUserDefinedPhenomenonData().comparisonType = 3;

	// 	coherence = dlg->coherence;
	// 	correlation = dlg->correlation;
	// 	frequency = dlg->frequency;
	// 	mean = dlg->mean;
	// 	modulation = dlg->modulation;
	// 	decomposition = dlg->decomposition;
	// 	simulation = dlg->simulation;
	// 	spatial = dlg->spatial;
	// 	randomness = dlg->randomness;
	// 	spectrum = dlg->spectrum;
    // }
}

QStringList RPSUserDefinedPhenomenonSimulation::FindAllSimulationMethods()
{
	QStringList theList;
    typedef IrpsUserDefinedPhenomenon *(*CreateSimuMethodCallback)();
    std::map<const QString, CreateSimuMethodCallback>::iterator simuMethIt;

    // Iterate though the map and show all the registed randomness providers in the combo box
    for (simuMethIt = CrpsUserDefinedPhenomenonFactory::GetUserDefinedPhenomenonNamesMap().begin(); simuMethIt != CrpsUserDefinedPhenomenonFactory::GetUserDefinedPhenomenonNamesMap().end(); ++simuMethIt)
    {
        // Add it to the combo box
        theList.append(simuMethIt->first);
    }
	return theList;
}

void RPSUserDefinedPhenomenonSimulation::simulationMethodInital(QString currentSelected)
{
    // Build an object
    IrpsUserDefinedPhenomenon *currentUserDefinedPhenomenon = CrpsUserDefinedPhenomenonFactory::BuildUserDefinedPhenomenon(currentSelected);

    // Check whether good object
    if (NULL == currentUserDefinedPhenomenon)
    {
        return;
    }

    // Apply iniatial setting
    currentUserDefinedPhenomenon->OnInitialSetting(GetUserDefinedPhenomenonSimulationData(), information);

    // Delete the object
    delete currentUserDefinedPhenomenon;
}

void RPSUserDefinedPhenomenonSimulation::receiveInformation(QStringList infoList)
{
	emit sendInformation(infoList);
}

void RPSUserDefinedPhenomenonSimulation::progressBarShowSL()
{
	emit progressBarShow();
}
void RPSUserDefinedPhenomenonSimulation::progressBarHideSL()
{
	emit progressBarHide();
	qApp->processEvents();
}
void RPSUserDefinedPhenomenonSimulation::progressBarSetValueSL(int value)
{
	// QMessageBox::warning(0, "1", "in setvalue");
	emit progressBarSetValue(value);
}
void RPSUserDefinedPhenomenonSimulation::progressBarSetMinSL(int value)
{
	QMessageBox::warning(0, "1", "in set min");
	emit progressBarSetMin(value);
}
void RPSUserDefinedPhenomenonSimulation::progressBarSetMaxSL(int value)
{
	// QMessageBox::warning(0, "1", "in set max");
	emit progressBarSetMax(value);
}

void RPSUserDefinedPhenomenonSimulation::progressBarResetSL()
{
	// QMessageBox::warning(0, "1", "in reset");
	emit progressBarReset();
}

void RPSUserDefinedPhenomenonSimulation::phenomenonCurrentIndexChanged(int index)
{
	phenomenonIndex = index;

    if (0 == index || GetUserDefinedPhenomenonSimulationData().numberOfProcess + 1 == index)
	{
		GetUserDefinedPhenomenonSimulationData().phenomenonIndex = 0;
	}
	else if (index > 0 &&
             index <= GetUserDefinedPhenomenonSimulationData().numberOfProcess)
	{
		GetUserDefinedPhenomenonSimulationData().phenomenonIndex = index - 1;
	}
}

void RPSUserDefinedPhenomenonSimulation::indexSetCurrentIndexChanged(int index)
{
	indexSetIndex = index;

	if (0 == index || GetUserDefinedPhenomenonSimulationData().indexSetSize + 1 == index)
	{
		GetUserDefinedPhenomenonSimulationData().indexSetIndex = 0;
	}
	else if (index > 0 &&
			 index <= GetUserDefinedPhenomenonSimulationData().indexSetSize)
	{
		GetUserDefinedPhenomenonSimulationData().indexSetIndex = index - 1;
	}
}

void RPSUserDefinedPhenomenonSimulation::fillIndexSetComboBox(QComboBox *indexSetComboBox)
{
	indexSetComboBox->clear();

	indexSetComboBox->addItem("None");
	for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().indexSetSize; i++)
	{
		indexSetComboBox->addItem(QString::number(i + 1));
	}
	indexSetComboBox->addItem("All");
}

void RPSUserDefinedPhenomenonSimulation::fillPhenomenonComboBox(QComboBox *phenomenonComboBox)
{
	phenomenonComboBox->clear();

	phenomenonComboBox->addItem("None");
    for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().numberOfProcess; i++)
	{
		phenomenonComboBox->addItem(QString::number(i + 1));
	}
	phenomenonComboBox->addItem("All");
}


void RPSUserDefinedPhenomenonSimulation::fillLocationJComboBox(QComboBox *locationJComboBox)
{
//	locationJComboBox->clear();

//	locationJComboBox->addItem("None");
//	for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition; i++)
//	{
//		locationJComboBox->addItem(QString::number(i + 1));
//	}
//	locationJComboBox->addItem("All");
}

void RPSUserDefinedPhenomenonSimulation::fillTimeComboBox(QComboBox *timeComboBox)
{
//	timeComboBox->clear();

//	timeComboBox->addItem("None");
//	for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements; i++)
//	{
//		timeComboBox->addItem(QString::number(i + 1));
//	}
//	timeComboBox->addItem("All");
}

void RPSUserDefinedPhenomenonSimulation::locJCurrentIndexChanged(int index)
{
//	locationJ = index;

//	if (0 == index || GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition + 1 == index)
//	{
//		GetUserDefinedPhenomenonSimulationData().locationJ = 0;
//	}
//	else if (index > 0 &&
//			 index <= GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition)
//	{
//		GetUserDefinedPhenomenonSimulationData().locationJ = index - 1;
//	}
}

void RPSUserDefinedPhenomenonSimulation::timCurrentIndexChanged(int index)
{
//	timeIndex = index;

//	if (0 == index || GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements + 1 == index)
//	{
//		GetUserDefinedPhenomenonSimulationData().timeIndex = 0;
//	}
//	else if (index > 0 &&
//			 index <= GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements)
//	{
//		GetUserDefinedPhenomenonSimulationData().timeIndex = index - 1;
//	}
}


void RPSUserDefinedPhenomenonSimulation::displayAComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    information = information + GetUserDefinedPhenomenonComparisonWorker()->getInformation();
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
        table->setCellValue(i, 0, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorVariable(i));
        table->setCellValue(i, 1, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorCandidate1(i));
        table->setCellValue(i, 2, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorCandidate2(i));
    }

    table->showNormal();
    information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetUserDefinedPhenomenonComparisonWorker()->finished();
}

void RPSUserDefinedPhenomenonSimulation::displayUserDefinedPhenomenonSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    information = information + GetUserDefinedPhenomenonComparisonWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the comparison results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    if (!(phenomenonIndex > 0 && phenomenonIndex <= GetUserDefinedPhenomenonSimulationData().numberOfProcess))
    {
        emit GetUserDefinedPhenomenonComparisonWorker()->finished();
        return;
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
        table->setCellValue(i, 0, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorVariable(i));
        table->setCellValue(i, 1, GetUserDefinedPhenomenonComparisonWorker()->m_resultCandidate1(i, GetUserDefinedPhenomenonSimulationData().phenomenonIndex));
        table->setCellValue(i, 2, GetUserDefinedPhenomenonComparisonWorker()->m_resultCandidate2(i, GetUserDefinedPhenomenonSimulationData().phenomenonIndex));
    }

    table->showNormal();
    information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetUserDefinedPhenomenonComparisonWorker()->finished();
}

void RPSUserDefinedPhenomenonSimulation::displayTComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    information = information + GetUserDefinedPhenomenonComparisonWorker()->getInformation();
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
        table->setCellValue(i, 0, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorVariableVec.at(i));
        table->setCellValue(i, 1, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorCandidate1Vec.at(i));
        table->setCellValue(i, 2, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorCandidate2Vec.at(i));
    }

    table->showNormal();
    information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetUserDefinedPhenomenonComparisonWorker()->finished();
}

void RPSUserDefinedPhenomenonSimulation::displayUserDefinedPhenomenonLargeScaleSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    // RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    // ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    // information = information + GetUserDefinedPhenomenonComparisonWorker()->getInformation();
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
    // 	table->setCellValue(i, 0, GetUserDefinedPhenomenonComparisonWorker()->m_resultVectorVariable(i));
    // 	table->setCellValue(i, 1, GetUserDefinedPhenomenonComparisonWorker()->m_resultCandidate1(i, GetUserDefinedPhenomenonSimulationData().locationJ));
    // 	table->setCellValue(i, 2, GetUserDefinedPhenomenonComparisonWorker()->m_resultCandidate2(i, GetUserDefinedPhenomenonSimulationData().locationJ));
    // }

    // table->showNormal();
    // information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // // send info the main window to show it
    // emit sendInformation(information);

    // // clear the information list
    // information.clear();

    // // delete the worker
    // GetUserDefinedPhenomenonComparisonWorker()->finished();
}

void RPSUserDefinedPhenomenonSimulation::displayAccuracyComparisonResults()
{
    int count = candidateList.size();
    QString candidate1 = candidateList[0];
    QString comparisonCategory = candidateList[1];
    QString comparisonFunction = candidateList[2];
    QString userDefinedPhenomenon1 = candidateList[3];

    QString candidate2 = candidateList[4];
    QString userDefinedPhenomenon2 = candidateList[7];


    if (comparisonCategory == LabRPS::objGroupUserDefinedPhenomenonObject)
    {
        if (comparisonFunction == LabRPS::Simulate)
        {
            displayUserDefinedPhenomenonSimComparisonResults(candidate1, candidate2, "Phenomenon", "Index", GetUserDefinedPhenomenonSimulationData().indexSetSize);
        }
        else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && GetUserDefinedPhenomenonSimulationData().largeScaleSimulationMode)
        {
            displayUserDefinedPhenomenonLargeScaleSimComparisonResults(candidate1, candidate2, "Velocity", "Time", GetUserDefinedPhenomenonSimulationData().indexSetSize);
        }
    }

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetUserDefinedPhenomenonComparisonWorker()->finished();
}
void RPSUserDefinedPhenomenonSimulation::displayTimeComparisonResults()
{
    int count = candidateList.size();
    QString candidate1 = candidateList[0];
    QString comparisonCategory = candidateList[1];
    QString comparisonFunction = candidateList[2];
    QString userDefinedPhenomenon1 = candidateList[3];

    QString candidate2 = candidateList[4];
    QString userDefinedPhenomenon2 = candidateList[7];

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
        if (comparisonFunction == LabRPS::Simulate)
        {
            displayUserDefinedPhenomenonSimComparisonResults(candidate1, candidate2, "Phenomenon", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && GetUserDefinedPhenomenonSimulationData().largeScaleSimulationMode)
        {
            displayUserDefinedPhenomenonLargeScaleSimComparisonResults(candidate1, candidate2, "Phenomenon", variableName, totalNumber);
        }
    }

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetUserDefinedPhenomenonComparisonWorker()->finished();
}

void RPSUserDefinedPhenomenonSimulation::displayMemoryComparisonResults()
{
}


void RPSUserDefinedPhenomenonSimulation::displayUserDefinedPhenomenon()
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    if (nullptr != GetUserDefinedPhenomenonSimulationWorker())
    {
        information = information + GetUserDefinedPhenomenonSimulationWorker()->getInformation();
        information.append("Please wait. LabRPS is now showing the random velocity results...");
        emit sendInformation(information);
        information.clear();
        emit progressBarHide();

        // save a copy of the simulated wind velocity
        m_resultMatrix = GetUserDefinedPhenomenonSimulationWorker()->m_ResultMatrix;
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

    if (phenomenonIndex > 0 &&
        phenomenonIndex <= GetUserDefinedPhenomenonSimulationData().numberOfProcess &&
        indexSetIndex == GetUserDefinedPhenomenonSimulationData().indexSetIndex + 1)
    {
        QTime t;
        t.start();

        // prepare the name of the table
        QString arrayName = tr("Phenomenon (%1, None, None, All)").arg(phenomenonIndex);

        // allocate memory for the table
        Table *table = app->newTable(arrayName, GetUserDefinedPhenomenonSimulationData().indexSetSize, 2);

        table->setColName(0, "Time");
        table->setColName(1, tr("Phenomenon %1").arg(phenomenonIndex));

        double timeInr = 0.0;

        // fill the table with computed coherence
        for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().indexSetSize; i++)
        {
            timeInr = GetUserDefinedPhenomenonSimulationData().minIndexSetValue + i * GetUserDefinedPhenomenonSimulationData().indexIncrement;

            table->setCellValue(i, 0, timeInr);
            table->setCellValue(i, 1, m_resultMatrix(i, phenomenonIndex));
        }

        table->showNormal();

        information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
    }
    else if (phenomenonIndex <= GetUserDefinedPhenomenonSimulationData().numberOfProcess + 1 &&
             indexSetIndex == GetUserDefinedPhenomenonSimulationData().indexSetSize + 1)
    {
        QTime t;
        t.start();

        // prepare the name of the table
        QString arrayName = "RandomVelocity (All, None, None, All)";

        // allocate memory for the table
        Table *table = app->newTable(arrayName, GetUserDefinedPhenomenonSimulationData().indexSetSize, GetUserDefinedPhenomenonSimulationData().numberOfProcess + 1);

        table->setColName(0, "Time");

        for (int j = 0; j < GetUserDefinedPhenomenonSimulationData().numberOfProcess; j++)
        {
            table->setColName(j + 1, tr("Location %1").arg(j + 1));
        }

        double timeInr = 0.0;

        // fill the table with computed coherence
        for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().indexSetSize; i++)
        {
            timeInr = GetUserDefinedPhenomenonSimulationData().minIndexSetValue + i * GetUserDefinedPhenomenonSimulationData().indexIncrement;

            table->setCellValue(i, 0, timeInr);

            for (int j = 0; j < GetUserDefinedPhenomenonSimulationData().numberOfProcess; j++)
            {
                table->setCellValue(i, j + 1, m_resultMatrix(i, j));
            }
        }
        table->showNormal();

        information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
    }
    else
    {
        information.append("Sorry, there is no function that meet your requirements.");
    }

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    if (nullptr != GetUserDefinedPhenomenonSimulationWorker())
    {
        // delete the worker
        GetUserDefinedPhenomenonSimulationWorker()->finished();
    }
}

void RPSUserDefinedPhenomenonSimulation::save(XmlStreamWriter *xmlwriter)
{

	xmlwriter->writeStartElement("userDefinedPhenomenon");
    saveUserDefinedPhenomenonSimulationData(xmlwriter);
	xmlwriter->writeEndElement();
}

bool RPSUserDefinedPhenomenonSimulation::load(XmlStreamReader *xmlreader)
{

	if (xmlreader->isStartElement() && xmlreader->name() == "userDefinedPhenomenon")
	{
        loadUserDefinedPhenomenonSimulationData(xmlreader);
	}
	else // no element
	{
		xmlreader->raiseError(tr("no userDefinedPhenomenon element found"));
	}

	return !xmlreader->hasError();
}

void RPSUserDefinedPhenomenonSimulation::saveUserDefinedPhenomenonSimulationData(XmlStreamWriter *xmlwriter)
{

	(simuData.stationarity) ? xmlwriter->writeAttribute("stationarity", "true")
							   : xmlwriter->writeAttribute("stationarity", "false");
	(simuData.gaussianity) ? xmlwriter->writeAttribute("gaussianity", "true")
							  : xmlwriter->writeAttribute("gaussianity", "false");
	(simuData.comparisonMode) ? xmlwriter->writeAttribute("comparisonMode", "true")
								 : xmlwriter->writeAttribute("comparisonMode", "false");
	(simuData.largeScaleSimulationMode) ? xmlwriter->writeAttribute("largeScaleSimulationMode", "true")
										   : xmlwriter->writeAttribute("largeScaleSimulationMode", "false");

    xmlwriter->writeAttribute("numberOfSample", QString::number(simuData.numberOfSample));
    xmlwriter->writeAttribute("simulationApproach", simuData.simulationApproach);
	xmlwriter->writeAttribute("simulationMethod", simuData.simulationMethod);
    xmlwriter->writeAttribute("workingDirPath", simuData.workingDirPath);
	xmlwriter->writeAttribute("comparisonCategory", simuData.comparisonCategory);
}

bool RPSUserDefinedPhenomenonSimulation::loadUserDefinedPhenomenonSimulationData(XmlStreamReader *xmlreader)
{

	bool ok;
	bool bvalue;
	int ivalue;
	double dvalue;
	QString svalue;

	bvalue = xmlreader->readAttributeBool("stationarity", &ok);
	if (ok)
	{
		simuData.stationarity = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Stationarity setting error");
	}

	bvalue = xmlreader->readAttributeBool("gaussianity", &ok);
	if (ok)
	{
		simuData.gaussianity = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Gaussianity setting error");
	}

	bvalue = xmlreader->readAttributeBool("comparisonMode", &ok);
	if (ok)
	{
		simuData.comparisonMode = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Comparison mode setting error");
	}

	bvalue = xmlreader->readAttributeBool("largeScaleSimulationMode", &ok);
	if (ok)
	{
		simuData.largeScaleSimulationMode = bvalue;
	}
	else
	{
		xmlreader->raiseWarning("Large scale simulation mode setting error");
	}

	ivalue = xmlreader->readAttributeInt("numberOfSample", &ok);
	if (ok)
	{
		simuData.numberOfSample = ivalue;
	}
	else
	{
		xmlreader->raiseWarning("Number of sample setting error");
	}

    svalue = xmlreader->readAttributeString("simulationApproach", &ok);
	if (ok)
	{
		simuData.simulationApproach = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Simulation approach setting error");
	}

	svalue = xmlreader->readAttributeString("simulationMethod", &ok);
	if (ok)
	{
		simuData.simulationMethod = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Simulation method setting error");
	}

	svalue = xmlreader->readAttributeString("workingDirPath", &ok);
	if (ok)
	{
		simuData.workingDirPath = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Working directory path setting error");
	}

	svalue = xmlreader->readAttributeString("comparisonCategory", &ok);
	if (ok)
	{
		simuData.comparisonCategory = svalue;
	}
	else
	{
		xmlreader->raiseWarning("Comparison category setting error");
	}

	return !xmlreader->hasError();
}

void RPSUserDefinedPhenomenonSimulation::comparisonInitial()
{
    int index = 0;
    categories.append(LabRPS::objGroupUserDefinedPhenomenonObject);

    functions.append(LabRPS::Simulate);
    functions.append(LabRPS::SimulateInLargeScaleMode);
    categoryFunctionListMap[categories.at(0)] = functions;
    functions.clear();

    comparisonCategory = categories.at(0);
    comparisonFunction = categoryFunctionListMap[comparisonCategory].at(0);
    comparisonCandidate = "";
    minNumberOfProcess = GetUserDefinedPhenomenonSimulationData().numberOfProcess;
    minNumberOfIndexSetIndex = GetUserDefinedPhenomenonSimulationData().indexSetSize;
    minNumberOfSample = GetUserDefinedPhenomenonSimulationData().numberOfSample;
    numberOfProcessIncrement = 0;
    numberOfIndexSetIndexIncrement = 0;
    numberOfSampleIncrement = 0;
    totalNumber = 3;
    resultOutputType = 1;
}

void RPSUserDefinedPhenomenonSimulation::candidateInitialData(QString category, QString currentSelected)
{
    switch (categories.indexOf(category))
    {
    case 0:
        simulationMethodInital(currentSelected);
        break;
    default:
        qWarning("Unknown comparison category");
        break;
    }
}


void RPSUserDefinedPhenomenonSimulation::fillCategoryComboBox(QComboBox *categoryComboBox)
{
    categoryComboBox->addItems(categories);
    categoryComboBox->setCurrentText(comparisonCategory);
}

void RPSUserDefinedPhenomenonSimulation::fillFunctionAndCandidateComboBoxes(QString category, QComboBox *functionComboBox, QComboBox *candidatesComboBox)
{
    functionComboBox->clear();
    candidatesComboBox->clear();

    switch (categories.indexOf(category))
    {
    case 0:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(0)]);
        candidatesComboBox->addItems(FindAllSimulationMethods());
        break;
    default:
        qWarning("Unknown comparison category");
        break;
    }

    functionComboBox->setCurrentText(comparisonFunction);
    candidatesComboBox->setCurrentText(comparisonCandidate);
}

void RPSUserDefinedPhenomenonSimulation::createOutputWorker()
{
	// create a worker
    simulationOutputWorker = new RPSUserDefinedPhenomenonSimulationOutputWorker(simuData, information, phenomenonIndex, indexSetIndex);

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

void RPSUserDefinedPhenomenonSimulation::createSimulationWorker()
{
	// create a worker
    simulationWorker = new RPSUserDefinedPhenomenonSimulationWorker(simuData, information, phenomenonIndex, indexSetIndex);

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

void RPSUserDefinedPhenomenonSimulation::createComparisonWorker()
{
    // create a worker
    comparisonWorker = new RPSUserDefinedPhenomenonComparisonWorker(simuData,
                                                      information,
                                                      phenomenonIndex,
                                                      indexSetIndex,
                                                      candidateList,
                                                      resultOutputType,
                                                      minNumberOfProcess,
                                                      minNumberOfIndexSetIndex,
                                                      minNumberOfSample,
                                                      numberOfProcessIncrement,
                                                      numberOfIndexSetIndexIncrement,
                                                      numberOfSampleIncrement,
                                                      totalNumber,
                                                      _userDefinedPhenomenon);

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

