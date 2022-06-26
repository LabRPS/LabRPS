#include "rpsWindLabSimulationWorker.h"
#include "RPSWindLabAPI.h"
#include "RPS.h"
#include <QTime>

RPSWindLabSimulationWorker::RPSWindLabSimulationWorker(CRPSWindLabsimuData windLabData, QStringList information):
m_windLabData(windLabData), 
m_information(information), 
stopped(true) 
{
    minStep = 0;
    maxStep = 0;
    currentStep = 0;
    maxStepOld = 0;
}
 
RPSWindLabSimulationWorker::~RPSWindLabSimulationWorker() 
{

}
 
void RPSWindLabSimulationWorker::simulate() 
{
    QTime t;
   t.start();

    if (isStopped()) 
    {

    stopped = false;
        // Build an object
	IrpsWLSimuMethod *currentRndProvider = CrpsSimuMethodFactory::BuildSimuMethod(m_windLabData.simulationMethod);

	// Check whether good object
	if (NULL == currentRndProvider)
	{
		return;
	}
	
    mat randomWindVelocity(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

    emit progressBarShow();

	// simulation
    currentRndProvider->Simulate(m_windLabData, randomWindVelocity, minStep, maxStep, currentStep, m_information);
	
    // Delete the object
	delete currentRndProvider;

    
    }
    m_information.append(QString::number(t.elapsed())) ;
    
    emit sendInformation(m_information);
    // emit progressBarHide();

    stopped = true;

    // Self-destruct now!
    deleteLater(); 
}

void RPSWindLabSimulationWorker::stop()
{
    mutex.lock();
    stopped = true;
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
