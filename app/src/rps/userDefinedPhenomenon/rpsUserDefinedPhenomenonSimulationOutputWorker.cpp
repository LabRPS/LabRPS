#include "rpsUserDefinedPhenomenonSimulationOutputWorker.h"
#include "RPSUserDefinedPhenomenonAPI.h"
#include "RPS.h"
#include <QTime>

RPSUserDefinedPhenomenonSimulationOutputWorker::RPSUserDefinedPhenomenonSimulationOutputWorker(CRPSUserDefinedPhenomenonSimuData simuData,
                                                                   QStringList information,
                                                                   int phenomenonIndex,
                                                                   int indexSetIndex) : m_simuData(simuData),
                                                                                    m_phenomenonIndex(phenomenonIndex),
                                                                                    m_indexSetIndex(indexSetIndex),
                                                                                    stopped(true)
{
    minStep = 0;
    maxStep = 0;
    currentStep = 0;
    maxStepOld = 0;
}

RPSUserDefinedPhenomenonSimulationOutputWorker::~RPSUserDefinedPhenomenonSimulationOutputWorker()
{
    m_information.clear();
    m_information.append("Output worker distroyed");
    emit sendInformation(m_information);
}

void RPSUserDefinedPhenomenonSimulationOutputWorker::stop()
{
    mutex.lock();
    stopped = true;
    mutex.unlock();
}

bool RPSUserDefinedPhenomenonSimulationOutputWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}

void RPSUserDefinedPhenomenonSimulationOutputWorker::progressBarMinMaxValue()
{
    mutex.lock();
    // emit progressBarSetValue(currentStep);
    // emit progressBarHide();

    if (0 != maxStep || maxStep != maxStepOld)
    {

        emit progressBarSetMin(minStep);
        emit progressBarSetMax(maxStep);
        emit progressBarReset();

        maxStepOld = maxStep;
    }
    mutex.unlock();
}

QStringList RPSUserDefinedPhenomenonSimulationOutputWorker::getInformation()
{
    return m_information;
}

void RPSUserDefinedPhenomenonSimulationOutputWorker::userDefinedPhenomenonOut()
{
    if (isStopped())
    {

        stopped = false;
        userDefinedPhenomenonOutp();
    }

    stopped = true;
}


void RPSUserDefinedPhenomenonSimulationOutputWorker::userDefinedPhenomenonOutp()
{
}
