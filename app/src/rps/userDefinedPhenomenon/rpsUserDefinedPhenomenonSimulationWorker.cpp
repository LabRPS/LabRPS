#include "rpsUserDefinedPhenomenonSimulationWorker.h"
#include "RPSUserDefinedPhenomenonAPI.h"
#include "RPS.h"
#include <QTime>
#include <QThread>

RPSUserDefinedPhenomenonSimulationWorker::RPSUserDefinedPhenomenonSimulationWorker(CRPSUserDefinedPhenomenonSimuData simuData,
                                                                   QStringList information,
                                                                   int locationJ,
                                                                   int timeIndex) : m_simuData(simuData),
                                                                                    m_information(information),
                                                                                    m_locationJ(locationJ),
                                                                                    m_timeIndex(timeIndex),
                                                                                    stopped(true)
{
    minStep = 0;
    maxStep = 0;
    currentStep = 0;
    maxStepOld = 0;
    m_simuData.isInterruptionRequested = false;

}
 
RPSUserDefinedPhenomenonSimulationWorker::~RPSUserDefinedPhenomenonSimulationWorker() 
{
    m_information.clear();
    m_information.append("User defined phenomenon simulation worker distroyed");
    emit sendInformation(m_information);
}
 
void RPSUserDefinedPhenomenonSimulationWorker::simulate() 
{
    if (isStopped())
    {
        stopped = false;
        windVelocityOutp();
    }

    stopped = true;
}

void RPSUserDefinedPhenomenonSimulationWorker::stop()
{
    mutex.lock();
    stopped = true;
    m_simuData.isInterruptionRequested = true;
    m_simuData.isSimulationSuccessful = false;
    mutex.unlock();
}

bool RPSUserDefinedPhenomenonSimulationWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}

    void RPSUserDefinedPhenomenonSimulationWorker::progressBarMinMaxValue()
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

    
void RPSUserDefinedPhenomenonSimulationWorker::windVelocityOutp()
{
    // Build an object
    IrpsUserDefinedPhenomenon *currentUserDefinedPhenomenon = CrpsUserDefinedPhenomenonFactory::BuildUserDefinedPhenomenon(m_simuData.simulationMethod);

	// Check whether good object
    if (NULL == currentUserDefinedPhenomenon)
	{
		m_information.append("Invalid random wind simulation method");
        emit sendInformation(m_information);
        m_simuData.isSimulationSuccessful = false;
        emit progressBarHide();
        return;
	}
	
//    m_ResultMatrix.resize(m_simuData.numberOfTimeIncrements, m_simuData.numberOfSpatialPosition);

        QTime t;
        t.start();

//	// simulation
//    currentSimuMethod->Simulate(m_simuData, m_ResultMatrix, minStep, maxStep, currentStep, m_information);
	
    m_information.append(tr("The simulation took %1 ms").arg(QString::number(t.elapsed())));

    // Delete the object
    delete currentUserDefinedPhenomenon;

    if(m_simuData.isInterruptionRequested)
    {
     emit progressBarHide();
     m_simuData.isSimulationSuccessful = false;
     m_information.append("The simulation has been stopped.");
     emit sendInformation(m_information);
     m_information.clear();
     return;
    }

    m_simuData.isSimulationSuccessful = true;

    emit showWindVelocityOutput();
}

QStringList RPSUserDefinedPhenomenonSimulationWorker::getInformation()
{
    return m_information;
}

