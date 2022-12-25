#include "rpsWindLabSimulationWorker.h"
#include "RPSWindLabAPI.h"
#include "RPS.h"
#include <QTime>
#include <QThread>

RPSWindLabSimulationWorker::RPSWindLabSimulationWorker(CRPSWindLabsimuData windLabData,
                                                                   QStringList information,
                                                                   int locationJ,
                                                                   int locationK,
                                                                   int frequencyIndex,
                                                                   int timeIndex) : m_windLabData(windLabData),
                                                                                    m_information(information),
                                                                                    stopped(true),
                                                                                    m_locationJ(locationJ),
                                                                                    m_locationK(locationK),
                                                                                    m_frequencyIndex(frequencyIndex),
                                                                                    m_timeIndex(timeIndex)
{
    minStep = 0;
    maxStep = 0;
    currentStep = 0;
    maxStepOld = 0;
    m_windLabData.isInterruptionRequested = false;
}
 
RPSWindLabSimulationWorker::~RPSWindLabSimulationWorker() 
{
    m_information.clear();
    m_information.append("Simulation worker distroyed");
    emit sendInformation(m_information);
}
 
void RPSWindLabSimulationWorker::simulate() 
{
    if (isStopped())
    {
        stopped = false;
        windVelocityOutp();
    }

    stopped = true;
}

void RPSWindLabSimulationWorker::stop()
{
    mutex.lock();
    stopped = true;
    m_windLabData.isInterruptionRequested = true;
    m_windLabData.isSimulationSuccessful = false;   
    mutex.unlock();
}

bool RPSWindLabSimulationWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}

    void RPSWindLabSimulationWorker::progressBarMinMaxValue()
    {
        mutex.lock();
        // emit progressBarSetValue(currentStep);
        // emit progressBarHide();

        if(0 != maxStep ||  maxStep != maxStepOld)
        {

          emit progressBarSetMin(minStep);
          emit progressBarSetMax(maxStep);
          emit progressBarReset();

          maxStepOld = maxStep;
        }
        mutex.unlock();

    }

    
void RPSWindLabSimulationWorker::windVelocityLargeScale()
{
    // Build an object
    IrpsWLSimuMethod *currentSimuMethod = CrpsSimuMethodFactory::BuildObject(m_windLabData.simulationMethod);

	// Check whether good object
	if (NULL == currentSimuMethod)
	{
		m_information.append("Invalid random wind simulation method");
        emit sendInformation(m_information);
        m_windLabData.isSimulationSuccessful = false;
        emit progressBarHide();
        return;
	}

    QTime t;
    t.start();
	
    QString fn = m_windLabData.workingDirPath + "/windVelocities.txt";

    // simulation
    m_windLabData.isSimulationSuccessful = currentSimuMethod->SimulateInLargeScaleMode(m_windLabData, fn, m_information);
	
    m_information.append(tr("The simulation took %1 ms").arg(QString::number(t.elapsed())));

    // Delete the object
	delete currentSimuMethod;

    if(m_windLabData.isInterruptionRequested)
    {
     emit progressBarHide();
     m_windLabData.isSimulationSuccessful = false;
     m_information.append("The simulation has been stopped.");
     emit sendInformation(m_information);
     m_information.clear();
     return;
    }

    m_windLabData.isSimulationSuccessful = true;

    //emit showWindVelocityOutput();
}

void RPSWindLabSimulationWorker::windVelocityNotLargeScale()
{
    // Build an object
    IrpsWLSimuMethod *currentSimuMethod = CrpsSimuMethodFactory::BuildObject(m_windLabData.simulationMethod);

    // Check whether good object
    if (NULL == currentSimuMethod)
    {
        m_information.append("Invalid random wind simulation method");
        emit sendInformation(m_information);
        m_windLabData.isSimulationSuccessful = false;
        emit progressBarHide();
        return;
    }

    //m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);
    m_ResultMatrix = Eigen::MatrixXd::Zero(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);
        QTime t;
        t.start();

    // simulation
    m_windLabData.isSimulationSuccessful = currentSimuMethod->Simulate(m_windLabData, m_ResultMatrix, m_information);

    m_simulationTime = t.elapsed();

    m_information.append(tr("The simulation took %1 ms").arg(QString::number(m_simulationTime)));
    // Delete the object
    delete currentSimuMethod;

    if(m_windLabData.isInterruptionRequested)
    {
     emit progressBarHide();
     m_windLabData.isSimulationSuccessful = false;
     m_information.append("The simulation has been stopped.");
     emit sendInformation(m_information);
     m_information.clear();
     return;
    }

    emit showWindVelocityOutput(m_windLabData.isSimulationSuccessful);
}

void RPSWindLabSimulationWorker::windVelocityOutp()
{
    if(m_windLabData.largeScaleSimulationMode)
    {
        windVelocityLargeScale();
    }
    else
    {
        windVelocityNotLargeScale();
    }
}

QStringList RPSWindLabSimulationWorker::getInformation()
{
    return m_information;
}

CRPSWindLabsimuData &RPSWindLabSimulationWorker::getSimulationWorkerWindLabData()
{
    return m_windLabData;
}

double RPSWindLabSimulationWorker::getSimulationTime()
{
    return m_simulationTime;
}
