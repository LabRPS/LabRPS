#include "rpsUserDefinedPhenomenonSimulation.h"

#include "RPSUserDefinedPhenomenonAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenonsimuoptionsdlg.h"
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

	// initialized windLab simulation data
	simuDataInitialize();
}

RPSUserDefinedPhenomenonSimulation::~RPSUserDefinedPhenomenonSimulation()
{
	
}

void RPSUserDefinedPhenomenonSimulation::userDefinedPhenomenon()
{
//	std::unique_ptr<RPSWindVelocityDefinitionDlg> dlg(new RPSWindVelocityDefinitionDlg(this));

//	if (dlg->exec() == QDialog::Accepted)
//	{
//		GetUserDefinedPhenomenonSimulationData().numberOfSample = dlg->numberOfSample;
//		GetUserDefinedPhenomenonSimulationData().stationarity = dlg->stationarity;
//		GetUserDefinedPhenomenonSimulationData().gaussianity = dlg->gaussianity;

//		// update the statusbar combobox content

//		RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//		rpsSimulator->fillLocationJComboBox();
//		rpsSimulator->fillTimeComboBox();
//	}
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

void RPSUserDefinedPhenomenonSimulation::simuDataInitialize()
{
	simuData.numberOfSample = 1;
    simuData.simulationApproach = ("Spectral Representation Approach");
	simuData.simulationMethod = ("Deodatis et al 1987");
    simuData.stationarity = true;
	simuData.gaussianity = true;
	simuData.comparisonMode = false;
	simuData.largeScaleSimulationMode = false;
    simuData.comparisonCategory = LabRPS::objGroupSimulationMethod;
	simuData.comparisonType = 1;
	simuData.isInterruptionRequested = false;
	simuData.isSimulationSuccessful = false;
}

void RPSUserDefinedPhenomenonSimulation::runSimulation()
{
	createSimulationWorker();
	connect(simulationWorker, SIGNAL(showWindVelocityOutput()), this, SLOT(displayWindVelocity()));
	emit progressBarShow();
	simulationThread->start();
}

void RPSUserDefinedPhenomenonSimulation::pauseSimulation()
{
	// // from https://stackoverflow.com/questions/4093159/what-is-the-correct-way-to-implement-a-qthread-example-please
	// simulationOutputThread = new QThread();
	// simulationOutputWorker = new RPSUserDefinedPhenomenonSimulationOutputWorker(simuData, information, locationJ, locationK, frequencyIndex, timeIndex);

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

	// QFuture<mat> future = QtConcurrent::run(simulationOutputWorker, &RPSUserDefinedPhenomenonSimulationOutputWorker::spectrumXModelOut);

	// mat result = future.result();

	// RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
	// ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

	// // allocate memory for the table
	// 	Table *table = app->newTable("haha", GetUserDefinedPhenomenonSimulationData().numberOfFrequency, GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements);

	// 	// fill the table with computed coherence
	// 	for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().numberOfFrequency; i++)
	// 	{
	// 		for (int j = 0; j < GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements; j++)
	// 		{
	// 			table->setCellValue(i, j, result(i,j));
	// 		}
	// 	}

	// 	table->showNormal();

	// QMessageBox::warning(this, "future", QString::number(result.rows()));
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

QStringList RPSUserDefinedPhenomenonSimulation::FindAllSimulationMethods()
{
	QStringList theList;
//	typedef IrpsUserDefinedPhenomenonSimuMethod *(*CreateSimuMethodCallback)();
//	std::map<const QString, CreateSimuMethodCallback>::iterator simuMethIt;

//	// Iterate though the map and show all the registed randomness providers in the combo box
//	for (simuMethIt = CrpsSimuMethodFactory::GetSimuMethodNamesMap().begin(); simuMethIt != CrpsSimuMethodFactory::GetSimuMethodNamesMap().end(); ++simuMethIt)
//	{
//		// Add it to the combo box
//		theList.append(simuMethIt->first);
//	}
	return theList;
}

void RPSUserDefinedPhenomenonSimulation::simulationMethodInital(QString currentSelected)
{
//	// Build an object
//	IrpsWLSimuMethod *currentRndProvider = CrpsSimuMethodFactory::BuildSimuMethod(currentSelected);

//	// Check whether good object
//	if (NULL == currentRndProvider)
//	{
//		return;
//	}

//	// Apply iniatial setting
//	currentRndProvider->OnInitialSetting(GetUserDefinedPhenomenonSimulationData(), information);

//	// Delete the object
//	delete currentRndProvider;
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

void RPSUserDefinedPhenomenonSimulation::displayUserDefinedPhenomenon()
{
//	RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//	ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//	if (nullptr != GetUserDefinedPhenomenonSimulationWorker())
//	{
//		information = information + GetUserDefinedPhenomenonSimulationWorker()->getInformation();
//		information.append("Please wait. LabRPS is now showing the random velocity results...");
//		emit sendInformation(information);
//		information.clear();
//		emit progressBarHide();

//		// save a copy of the simulated wind velocity
//		m_resultMatrix = GetUserDefinedPhenomenonSimulationWorker()->m_ResultMatrix;
//	}
//	else if (m_resultMatrix.size() <= 0)
//	{
//		information.append("Please,run the simulation first.");
//		emit sendInformation(information);
//		information.clear();
//		return;
//	}

//	qApp->processEvents();
//	information.clear();

//	if (locationJ > 0 &&
//		locationJ <= GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition &&
//		locationK == 0 &&
//		frequencyIndex == 0 &&
//		timeIndex == GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements + 1)
//	{
//		QTime t;
//		t.start();

//		// prepare the name of the table
//		QString arrayName = tr("RandomVelocity (%1, None, None, All)").arg(locationJ);

//		// allocate memory for the table
//		Table *table = app->newTable(arrayName, GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements, 2);

//		table->setColName(0, "Time");
//		table->setColName(1, tr("Location %1").arg(locationJ));

//		double timeInr = 0.0;

//		// fill the table with computed coherence
//		for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements; i++)
//		{
//			timeInr = GetUserDefinedPhenomenonSimulationData().minTime + i * GetUserDefinedPhenomenonSimulationData().timeIncrement;

//			table->setCellValue(i, 0, timeInr);
//			table->setCellValue(i, 1, m_resultMatrix(i, locationJ));
//		}

//		table->showNormal();

//		information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//	}
//	else if (locationJ <= GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition + 1 &&
//			 locationK == 0 &&
//			 frequencyIndex == 0 &&
//			 timeIndex == GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements + 1)
//	{
//		QTime t;
//		t.start();

//		// prepare the name of the table
//		QString arrayName = "RandomVelocity (All, None, None, All)";

//		// allocate memory for the table
//		Table *table = app->newTable(arrayName, GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements, GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition + 1);

//		table->setColName(0, "Time");

//		for (int j = 0; j < GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition; j++)
//		{
//			table->setColName(j + 1, tr("Location %1").arg(j + 1));
//		}

//		double timeInr = 0.0;

//		// fill the table with computed coherence
//		for (int i = 0; i < GetUserDefinedPhenomenonSimulationData().numberOfTimeIncrements; i++)
//		{
//			timeInr = GetUserDefinedPhenomenonSimulationData().minTime + i * GetUserDefinedPhenomenonSimulationData().timeIncrement;

//			table->setCellValue(i, 0, timeInr);

//			for (int j = 0; j < GetUserDefinedPhenomenonSimulationData().numberOfSpatialPosition; j++)
//			{
//				table->setCellValue(i, j + 1, m_resultMatrix(i, j));
//			}
//		}
//		table->showNormal();

//		information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//	}
//	else
//	{
//		information.append("Sorry, there is no function that meet your requirements.");
//	}

//	// send info the main window to show it
//	emit sendInformation(information);

//	// clear the information list
//	information.clear();

//	if (nullptr != GetUserDefinedPhenomenonSimulationWorker())
//	{
//		// delete the worker
//		GetUserDefinedPhenomenonSimulationWorker()->finished();
//	}
}

void RPSUserDefinedPhenomenonSimulation::save(XmlStreamWriter *xmlwriter)
{

	xmlwriter->writeStartElement("windLab");
    saveUserDefinedPhenomenonSimulationData(xmlwriter);
	xmlwriter->writeEndElement();
}

bool RPSUserDefinedPhenomenonSimulation::load(XmlStreamReader *xmlreader)
{

	if (xmlreader->isStartElement() && xmlreader->name() == "windLab")
	{
        loadUserDefinedPhenomenonSimulationData(xmlreader);
	}
	else // no element
	{
		xmlreader->raiseError(tr("no windLab element found"));
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
