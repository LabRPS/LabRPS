#include "rpsWindLabComparisonWorker.h"
#include "RPSWindLabAPI.h"
#include "RPS.h"
#include "globals.h"

#include <QTime>
#include <QThread>

RPSWindLabComparisonWorker::RPSWindLabComparisonWorker(CRPSWindLabsimuData windLabData,
                                                                   QStringList information,
                                                                   int locationJ,
                                                                   int locationK,
                                                                   int frequencyIndex,
                                                                   int timeIndex,
                                                                   std::vector<QString> candidateList) : m_windLabData(windLabData),
                                                                                    m_information(information),
                                                                                    m_locationJ(locationJ),
                                                                                    m_locationK(locationK),
                                                                                    m_frequencyIndex(frequencyIndex),
                                                                                    m_timeIndex(timeIndex),
                                                                                    stopped(true),
                                                                                    m_candidateList(candidateList)
{
    minStep = 0;
    maxStep = 0;
    currentStep = 0;
    maxStepOld = 0;
    m_windLabData.isInterruptionRequested = false;

}
 
RPSWindLabComparisonWorker::~RPSWindLabComparisonWorker() 
{
    m_information.clear();
    m_information.append("Comparison worker distroyed");
    emit sendInformation(m_information);
}
 
void RPSWindLabComparisonWorker::compareAccuracy() 
{
    if (isStopped())
    {
        stopped = false;
        accuracyOutp();
    }

    stopped = true;
}

void RPSWindLabComparisonWorker::compareTime() 
{
    if (isStopped())
    {
        stopped = false;
        timeOutp();
    }

    stopped = true;
}

void RPSWindLabComparisonWorker::compareMemory() 
{
    if (isStopped())
    {
        stopped = false;
        memoryOutp();
    }

    stopped = true;
}

void RPSWindLabComparisonWorker::stop()
{
    mutex.lock();
    stopped = true;
    m_windLabData.isInterruptionRequested = true;
    m_windLabData.isSimulationSuccessful = false;   
    mutex.unlock();
}

bool RPSWindLabComparisonWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}

void RPSWindLabComparisonWorker::progressBarMinMaxValue()
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

void RPSWindLabComparisonWorker::ComputeFrequenciesVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build an coherence function and frequency distribution functions
        IrpsWLFrequencyDistribution *currentFreqDistr = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(name);

        // Check whether good coherence object
        if (NULL == currentFreqDistr)
        {
            information.append("Invalid mean wind profil");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        QTime t;
        t.start();

        // running the computation
        currentFreqDistr->ComputeFrequenciesVectorF(m_windLabData, result, information);
        time = t.elapsed();
        information.append(tr("The computation of the frequencies (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentFreqDistr;
}

void RPSWindLabComparisonWorker::ComputeCrossCoherenceVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build an coherence function and frequency distribution functions
    IrpsWLCoherence *currentCoherenceFunction = CrpsCoherenceFactory::BuildCoherence(name);

    // Check whether good coherence object
    if (NULL == currentCoherenceFunction)
    {
        information.append("Invalid coherence function");
        emit sendInformation(information);
        emit progressBarHide();
        return;
    }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentCoherenceFunction->ComputeCrossCoherenceVectorF(m_windLabData, result, information);
        time = t.elapsed();
        information.append(tr("The computation of the coherence function (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentCoherenceFunction;
}

void RPSWindLabComparisonWorker::ComputeMeanWindSpeedVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build an coherence function and frequency distribution functions
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(name);

        // Check whether good coherence object
        if (NULL == currentMeanWindProfil)
        {
            information.append("Invalid mean wind profil");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedVectorP(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the mean wind (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentMeanWindProfil;
}


void RPSWindLabComparisonWorker::ComputeMeanWindSpeedVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
       // allocate memories to receive the computed coherence and frequencies
        // Build an coherence function and frequency distribution functions
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(name);

        // Check whether good coherence object
        if (NULL == currentMeanWindProfil)
        {
            information.append("Invalid mean wind profil");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfTimeIncrements);

        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedVectorT(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the mean wind (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentMeanWindProfil;
}


void RPSWindLabComparisonWorker::ComputeModulationVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
     // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(name);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            information.append("Invalid modulation function");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfTimeIncrements);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorT(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the modulation function (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentModulationFtn;
}

void RPSWindLabComparisonWorker::ComputeModulationVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build an coherence function and frequency distribution functions
    IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(name);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            information.append("Invalid modulation function");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorF(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the modulation function (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentModulationFtn;
}

void RPSWindLabComparisonWorker::ComputeModulationVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
     // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(name);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            information.append("Invalid modulation function");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorP(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the modulation function (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentModulationFtn;
}

void RPSWindLabComparisonWorker::ComputeDecomposedCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
      // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum decomposition method");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorF(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the decomposed spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeDecomposedCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
     // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum decomposition method");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfTimeIncrements);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorT(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the decomposed spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeDecomposedCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
     // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum decomposition method");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorP(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the decomposed spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeXCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorF(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeXCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfTimeIncrements);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorT(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeXCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorP(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeYCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumVectorF(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeYCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfTimeIncrements);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumVectorT(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeYCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumVectorP(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeZCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumVectorF(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeZCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfTimeIncrements);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumVectorT(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::ComputeZCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information)
{
    // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(name);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            information.append("Invalid spectrum model");
            emit sendInformation(information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        result.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumVectorP(m_windLabData, result, information);

        time = t.elapsed();
        information.append(tr("The computation of the spectrum (%1) took %2 ms").arg(name).arg(QString::number(time)));

        delete currentPSD;
}

void RPSWindLabComparisonWorker::fillVectorWithNumbers(vec &vector, const int &row)
{
    for (int loop = 0; loop < row; loop++)
    {
       vector(loop) = loop + 1;
    }
}

void RPSWindLabComparisonWorker::fillVectorWithTimeIncrements(vec &vector)
{
    for (int loop = 0; loop < m_windLabData.numberOfTimeIncrements; loop++)
    {
       	vector(loop) = m_windLabData.minTime + loop * m_windLabData.timeIncrement;
    }
}


    
void RPSWindLabComparisonWorker::accuracyOutp()
{
    int count = m_candidateList.size();

    if(count < 6)
    {
        m_information.append("Please you need at least two candidates to run the comparison.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    QString comparisonCategory = m_candidateList[1];
    QString comparisonFunction = m_candidateList[2];
    QString candidate1 = m_candidateList[0];
    QString candidate2 = m_candidateList[3];

    if (comparisonCategory == LabRPS::objGroupCoherenceFunction)
    {
        if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorF)
        {    
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            ComputeCrossCoherenceVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeCrossCoherenceVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
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
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);
            
            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfFrequency);
            ComputeFrequenciesVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeFrequenciesVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupMeanWindProfile)
    {
        if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            ComputeMeanWindSpeedVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeMeanWindSpeedVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);

        }
        else if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            ComputeMeanWindSpeedVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeMeanWindSpeedVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupModulationFunction)
    {
        if (comparisonFunction == LabRPS::ComputeModulationVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            ComputeModulationVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeModulationVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);        
        }
        else if (comparisonFunction == LabRPS::ComputeModulationVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            ComputeModulationVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeModulationVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);

        }
        else if (comparisonFunction == LabRPS::ComputeModulationVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            ComputeModulationVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeModulationVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);

        }
    }
    else if (comparisonCategory == LabRPS::objGroupSpectrumDecompositionMethod)
    {
        if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            ComputeDecomposedCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeDecomposedCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
           
        }
        else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            ComputeDecomposedCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeDecomposedCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);        

        }
        else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            ComputeDecomposedCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeDecomposedCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupSimulationMethod)
    {
        if (comparisonFunction == LabRPS::Simulate)
        {
        }
        else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode)
        {
        }
    }
    else if (comparisonCategory == LabRPS::objGroupAlongWindSpectrum)
    {
        if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            ComputeXCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeXCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);   
        }
        else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            ComputeXCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeXCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);        
        }
        else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            ComputeXCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeXCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupAcrossWindSpectrum)
    {
        if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            ComputeYCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeYCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);   
        }
        else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            ComputeYCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeYCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);        

        }
        else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            ComputeYCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeYCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);

        }
    }
    else if (comparisonCategory == LabRPS::objGroupVerticalWindSpectrum)
    {
        if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            ComputeZCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeZCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);   
        }
        else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            ComputeZCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeZCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);        

        }
        else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            ComputeZCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            ComputeZCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);

        }
    }

    emit showAccuracyComparisonOutput();
}

void RPSWindLabComparisonWorker::timeOutp()
{
    emit showTimeComparisonOutput();
}

void RPSWindLabComparisonWorker::memoryOutp()
{
    emit showMemoryComparisonOutput();
}

QStringList RPSWindLabComparisonWorker::getInformation()
{
    return m_information;
}

