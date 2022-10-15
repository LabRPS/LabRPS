#include "rpsUserDefinedPhenomenonComparisonWorker.h"
#include "RPSUserDefinedPhenomenonAPI.h"
#include "RPS.h"
#include "globals.h"

#include <QTime>
#include <QThread>

RPSUserDefinedPhenomenonComparisonWorker::RPSUserDefinedPhenomenonComparisonWorker(CRPSUserDefinedPhenomenonSimuData userDefinedPhenomenonData,
                                                       QStringList information,
                                                       int phenomenonIndex,
                                                       int indexSetIndex,
                                                       std::vector<QString> candidateList,
                                                       int resultOutputType,
                                                       int minNumberOfProcess,
                                                       int minNumberOfIndexSetIndex,
                                                       int minNumberOfSample,
                                                       int numberOfProcessIncrement,
                                                       int numberOfIndexSetIndexIncrement,
                                                       int numberOfSampleIncrement,
                                                       int totalNumber,
                                                       QString userDefinedPhenomenon) : m_userDefinedPhenomenonData(userDefinedPhenomenonData),
                                                                   m_information(information),
                                                                   stopped(true),
                                                                   m_phenomenonIndex(phenomenonIndex),
                                                                   m_indexSetIndex(indexSetIndex),
                                                                   m_candidateList(candidateList),
                                                                   m_resultOutputType(resultOutputType),
                                                                   m_minNumberOfProcess(minNumberOfProcess),
                                                                   m_minNumberOfIndexSetIndex(minNumberOfIndexSetIndex),
                                                                   m_minNumberOfSample(minNumberOfSample),
                                                                   m_numberOfProcessIncrement(numberOfProcessIncrement),
                                                                   m_numberOfIndexSetIndexIncrement(numberOfIndexSetIndexIncrement),
                                                                   m_numberOfSampleIncrement(numberOfSampleIncrement),
                                                                   m_totalNumber(totalNumber),
                                                                   m_userDefinedPhenomenon(userDefinedPhenomenon)
{
    minStep = 0;
    maxStep = 0;
    currentStep = 0;
    maxStepOld = 0;
    m_userDefinedPhenomenonData.isInterruptionRequested = false;
}

RPSUserDefinedPhenomenonComparisonWorker::~RPSUserDefinedPhenomenonComparisonWorker()
{
    m_information.clear();
    m_information.append("Comparison worker distroyed");
    emit sendInformation(m_information);
}

void RPSUserDefinedPhenomenonComparisonWorker::compareAccuracy()
{
    if (isStopped())
    {
        stopped = false;
        accuracyOutp();
    }

    stopped = true;
}

void RPSUserDefinedPhenomenonComparisonWorker::compareTime()
{
    if (isStopped())
    {
        stopped = false;
        timeOutp();
    }

    stopped = true;
}

void RPSUserDefinedPhenomenonComparisonWorker::compareMemory()
{
    if (isStopped())
    {
        stopped = false;
        memoryOutp();
    }

    stopped = true;
}

void RPSUserDefinedPhenomenonComparisonWorker::stop()
{
    mutex.lock();
    stopped = true;
    m_userDefinedPhenomenonData.isInterruptionRequested = true;
    m_userDefinedPhenomenonData.isSimulationSuccessful = false;
    mutex.unlock();
}

bool RPSUserDefinedPhenomenonComparisonWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}

void RPSUserDefinedPhenomenonComparisonWorker::progressBarMinMaxValue()
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


void RPSUserDefinedPhenomenonComparisonWorker::Simulate(const QString &name, mat &result, int &time, int &memory, QStringList &information)
{
    // Build an object
    IrpsUserDefinedPhenomenon *currentUserDefinedPhenomenon = CrpsUserDefinedPhenomenonFactory::BuildUserDefinedPhenomenon(name);

    // Check whether good object
    if (NULL == currentUserDefinedPhenomenon)
    {
        information.append("Invalid random wind simulation method");
        emit sendInformation(information);
        m_userDefinedPhenomenonData.isSimulationSuccessful = false;
        emit progressBarHide();
        return;
    }

    //result.resize(m_userDefinedPhenomenonData.indexSetSize, m_userDefinedPhenomenonData.numberOfProcess);
    result = Eigen::MatrixXd::Zero(m_userDefinedPhenomenonData.indexSetSize, m_userDefinedPhenomenonData.numberOfProcess);

    QTime t;
    t.start();

    // simulation
    currentUserDefinedPhenomenon->Simulate(m_userDefinedPhenomenonData, result, information);

    time = t.elapsed();
    information.append(tr("The computation of the simulation method (%1) took %2 ms").arg(name).arg(QString::number(time)));

    // Delete the object
    delete currentUserDefinedPhenomenon;

    if (m_userDefinedPhenomenonData.isInterruptionRequested)
    {
        emit progressBarHide();
        m_userDefinedPhenomenonData.isSimulationSuccessful = false;
        information.append("The simulation has been stopped.");
        emit sendInformation(information);
        information.clear();
        return;
    }
}

void RPSUserDefinedPhenomenonComparisonWorker::SimulateInLargeScaleMode(const QString &name, QString &strFileName, int &time, int &memory, QStringList &information)
{
    // Build an object
    IrpsUserDefinedPhenomenon *currentUserDefinedPhenomenon = CrpsUserDefinedPhenomenonFactory::BuildUserDefinedPhenomenon(name);

    // Check whether good object
    if (NULL == currentUserDefinedPhenomenon)
    {
        information.append("Invalid random wind simulation method");
        emit sendInformation(information);
        m_userDefinedPhenomenonData.isSimulationSuccessful = false;
        emit progressBarHide();
        return;
    }

    QTime t;
    t.start();

    // simulation
    currentUserDefinedPhenomenon->SimulateInLargeScaleMode(m_userDefinedPhenomenonData, strFileName, information);

    time = t.elapsed();
    information.append(tr("The computation of the simulation method (%1) took %2 ms").arg(name).arg(QString::number(time)));

    // Delete the object
    delete currentUserDefinedPhenomenon;

    if (m_userDefinedPhenomenonData.isInterruptionRequested)
    {
        emit progressBarHide();
        m_userDefinedPhenomenonData.isSimulationSuccessful = false;
        information.append("The simulation has been stopped.");
        emit sendInformation(information);
        information.clear();
        return;
    }
}

void RPSUserDefinedPhenomenonComparisonWorker::fillVectorWithNumbers(vec &vector, const int &row)
{
    for (int loop = 0; loop < row; loop++)
    {
        vector(loop) = loop + 1;
    }
}

void RPSUserDefinedPhenomenonComparisonWorker::fillVectorWithTimeIncrements(vec &vector)
{
    for (int loop = 0; loop < m_userDefinedPhenomenonData.indexSetSize; loop++)
    {
        vector(loop) = m_userDefinedPhenomenonData.minIndexSetValue + loop * m_userDefinedPhenomenonData.indexIncrement;
    }
}
void RPSUserDefinedPhenomenonComparisonWorker::accuracyOutp()
{
    workerComparing();
}

void RPSUserDefinedPhenomenonComparisonWorker::workerComparing()
{
    int count = m_candidateList.size();

    if (count < 8)
    {
        m_information.append("Please you need at least two candidates to run the comparison.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    QString candidate1 = m_candidateList[0];
    QString comparisonCategory = m_candidateList[1];
    QString comparisonFunction = m_candidateList[2];
    QString userDefinedPhenomenon1 = m_candidateList[3];
    
    QString candidate2 = m_candidateList[4];
    QString userDefinedPhenomenon2 = m_candidateList[7];


    if (comparisonCategory == LabRPS::objGroupUserDefinedPhenomenonObject)
    {
        if (comparisonFunction == LabRPS::Simulate)
        {
            m_resultVectorVariable.resize(m_userDefinedPhenomenonData.indexSetSize);
            m_resultCandidate1.resize(m_userDefinedPhenomenonData.indexSetSize, m_userDefinedPhenomenonData.numberOfProcess);
            m_resultCandidate2.resize(m_userDefinedPhenomenonData.indexSetSize, m_userDefinedPhenomenonData.numberOfProcess);

            fillVectorWithNumbers(m_resultVectorVariable, m_userDefinedPhenomenonData.indexSetSize);

            setOjectDependencyForCanditate1();
            Simulate(candidate1, m_resultCandidate1, computationTime1, memoryConsumption1, m_information);

            setOjectDependencyForCanditate2();
            Simulate(candidate2, m_resultCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && m_userDefinedPhenomenonData.largeScaleSimulationMode)
        {
            fillVectorWithNumbers(m_resultVectorVariable, m_userDefinedPhenomenonData.indexSetSize);

            setOjectDependencyForCanditate1();
            SimulateInLargeScaleMode(candidate1, windVelocityFileName1, computationTime1, memoryConsumption1, m_information);

            setOjectDependencyForCanditate2();
            SimulateInLargeScaleMode(candidate2, windVelocityFileName2, computationTime2, memoryConsumption2, m_information);
        }
    } 

    if (m_userDefinedPhenomenonData.comparisonType == 1) // accuracy
    {
        emit showAccuracyComparisonOutput();
    }
}

void RPSUserDefinedPhenomenonComparisonWorker::timeOutp()
{
    if (1 == m_resultOutputType)
    {

        for (int i = 0; i < m_totalNumber; i ++)
        {
            m_userDefinedPhenomenonData.numberOfProcess = m_minNumberOfProcess + i*m_numberOfProcessIncrement;
            workerComparing();
            m_resultVectorVariableVec.push_back(m_userDefinedPhenomenonData.numberOfProcess);
            m_resultVectorCandidate1Vec.push_back(computationTime1);
            m_resultVectorCandidate2Vec.push_back(computationTime2);
        }
    }
    else if (2 == m_resultOutputType)
    {
        for (int i = 0; i < m_totalNumber; i++ )
        {
            m_userDefinedPhenomenonData.indexSetSize = m_minNumberOfIndexSetIndex + i*m_numberOfIndexSetIndexIncrement;
            workerComparing();
            m_resultVectorVariableVec.push_back(m_userDefinedPhenomenonData.indexSetSize);
            m_resultVectorCandidate1Vec.push_back(computationTime1);
            m_resultVectorCandidate2Vec.push_back(computationTime2);
        }
    }
    else if (3 == m_resultOutputType)
    {
        for (int i = 0; i < m_totalNumber; i++ )
        {
            m_userDefinedPhenomenonData.numberOfSample = m_minNumberOfSample + i*m_numberOfSampleIncrement;
            workerComparing();
            m_resultVectorVariableVec.push_back(m_userDefinedPhenomenonData.numberOfSample);
            m_resultVectorCandidate1Vec.push_back(computationTime1);
            m_resultVectorCandidate2Vec.push_back(computationTime2);
        }
    }

    if (m_userDefinedPhenomenonData.comparisonType == 2) // time
    {
        emit showTimeComparisonOutput();
    }
}

void RPSUserDefinedPhenomenonComparisonWorker::memoryOutp()
{
    emit showMemoryComparisonOutput();
}

QStringList RPSUserDefinedPhenomenonComparisonWorker::getInformation()
{
    return m_information;
}

void RPSUserDefinedPhenomenonComparisonWorker::setOjectDependencyForCanditate1()
{
    QString noSelection = "<None>";

    QString userDefinedPhenomenon1 = m_candidateList[3];


    if (noSelection != userDefinedPhenomenon1)
    {
        m_userDefinedPhenomenonData.userDefinedPhenomenon = userDefinedPhenomenon1;
    }

}

void RPSUserDefinedPhenomenonComparisonWorker::setOjectDependencyForCanditate2()
{
    QString noSelection = "<None>";
    
    QString userDefinedPhenomenon2 = m_candidateList[4];

    if (noSelection != userDefinedPhenomenon2)
    {
        m_userDefinedPhenomenonData.userDefinedPhenomenon = userDefinedPhenomenon2;
    }

}
