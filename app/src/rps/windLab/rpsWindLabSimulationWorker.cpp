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
                                                                                    m_locationJ(locationJ),
                                                                                    m_locationK(locationK),
                                                                                    m_frequencyIndex(frequencyIndex),
                                                                                    m_timeIndex(timeIndex),
                                                                                    stopped(true)
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

    
void RPSWindLabSimulationWorker::windVelocityOutp()
{
    if (m_locationJ > 0 &&
        m_locationJ <= m_windLabData.numberOfSpatialPosition &&
        m_locationK == 0 &&
        m_timeIndex == m_windLabData.numberOfTimeIncrements + 1
    )
    {
        // Build an object
	IrpsWLSimuMethod *currentSimuMethod = CrpsSimuMethodFactory::BuildSimuMethod(m_windLabData.simulationMethod);

	// Check whether good object
	if (NULL == currentSimuMethod)
	{
		m_information.append("Invalid random wind simulation method");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
	}
	
    m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

	// simulation
    currentSimuMethod->Simulate(m_windLabData, m_ResultMatrix, minStep, maxStep, currentStep, m_information);
	
    m_information.append(tr("The simulation took %1 ms").arg(QString::number(t.elapsed())));

    // Delete the object
	delete currentSimuMethod;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    if(m_windLabData.isInterruptionRequested)
    {
     emit progressBarHide();
     return;
    }

    emit showWindVelocityOutput();

}

QStringList RPSWindLabSimulationWorker::getInformation()
{
    return m_information;
}

