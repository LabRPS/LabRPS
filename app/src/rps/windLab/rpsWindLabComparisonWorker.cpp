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
                                                       std::vector<QString> candidateList,
                                                       int resultOutputType,
                                                       int minNumberOfLocation,
                                                       int minNumberOfFrequency,
                                                       int minNumberOfTime,
                                                       int numberOfLocationIncrement,
                                                       int numberOfFrequencyIncrement,
                                                       int numberOfTimeIncrement,
                                                       int totalNumber,
                                                       QString coherence,
                                                       QString correlation,
                                                       QString frequency,
                                                       QString mean,
                                                       QString modulation,
                                                       QString decomposition,
                                                       QString simulation,
                                                       QString spatial,
                                                       QString randomness,
                                                       QString spectrum) : m_windLabData(windLabData),
                                                                   m_information(information),
                                                                   m_locationJ(locationJ),
                                                                   m_locationK(locationK),
                                                                   m_frequencyIndex(frequencyIndex),
                                                                   m_timeIndex(timeIndex),
                                                                   stopped(true),
                                                                   m_candidateList(candidateList),
                                                                   m_resultOutputType(resultOutputType),
                                                                   m_minNumberOfLocation(minNumberOfLocation),
                                                                   m_minNumberOfFrequency(minNumberOfFrequency),
                                                                   m_minNumberOfTime(minNumberOfTime),
                                                                   m_numberOfLocationIncrement(numberOfLocationIncrement),
                                                                   m_numberOfFrequencyIncrement(numberOfFrequencyIncrement),
                                                                   m_numberOfTimeIncrement(numberOfTimeIncrement),
                                                                   m_totalNumber(totalNumber),
                                                                   m_coherence(coherence),
                                                                   m_correlation(correlation),
                                                                   m_frequency(frequency),
                                                                   m_mean(mean),
                                                                   m_modulation(modulation),
                                                                   m_decomposition(decomposition),
                                                                   m_simulation(simulation),
                                                                   m_spatial(spatial),
                                                                   m_randomness(randomness),
                                                                   m_spectrum(spectrum)
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
        //emit QThread::currentThread()->finished();
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

void RPSWindLabComparisonWorker::Simulate(const QString &name, mat &result, int &time, int &memory, QStringList &information)
{
    // Build an object
    IrpsWLSimuMethod *currentSimuMethod = CrpsSimuMethodFactory::BuildSimuMethod(name);

    // Check whether good object
    if (NULL == currentSimuMethod)
    {
        information.append("Invalid random wind simulation method");
        emit sendInformation(information);
        m_windLabData.isSimulationSuccessful = false;
        emit progressBarHide();
        return;
    }

    //result.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);
    result = Eigen::MatrixXd::Zero(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

    QTime t;
    t.start();

    // simulation
    currentSimuMethod->Simulate(m_windLabData, result, information);

    time = t.elapsed();
    information.append(tr("The computation of the simulation method (%1) took %2 ms").arg(name).arg(QString::number(time)));

    // Delete the object
    delete currentSimuMethod;

    if (m_windLabData.isInterruptionRequested)
    {
        emit progressBarHide();
        m_windLabData.isSimulationSuccessful = false;
        information.append("The simulation has been stopped.");
        emit sendInformation(information);
        information.clear();
        return;
    }
}

void RPSWindLabComparisonWorker::SimulateInLargeScaleMode(const QString &name, QString &strFileName, int &time, int &memory, QStringList &information)
{
    // Build an object
    IrpsWLSimuMethod *currentSimuMethod = CrpsSimuMethodFactory::BuildSimuMethod(name);

    // Check whether good object
    if (NULL == currentSimuMethod)
    {
        information.append("Invalid random wind simulation method");
        emit sendInformation(information);
        m_windLabData.isSimulationSuccessful = false;
        emit progressBarHide();
        return;
    }

    QTime t;
    t.start();

    // simulation
    currentSimuMethod->SimulateInLargeScaleMode(m_windLabData, strFileName, information);

    time = t.elapsed();
    information.append(tr("The computation of the simulation method (%1) took %2 ms").arg(name).arg(QString::number(time)));

    // Delete the object
    delete currentSimuMethod;

    if (m_windLabData.isInterruptionRequested)
    {
        emit progressBarHide();
        m_windLabData.isSimulationSuccessful = false;
        information.append("The simulation has been stopped.");
        emit sendInformation(information);
        information.clear();
        return;
    }
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
    workerComparing();
}

void RPSWindLabComparisonWorker::workerComparing()
{
    int count = m_candidateList.size();

    if (count < 26)
    {
        m_information.append("Please you need at least two candidates to run the comparison.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    QString candidate1 = m_candidateList[0];
    QString comparisonCategory = m_candidateList[1];
    QString comparisonFunction = m_candidateList[2];
    QString coherence1 = m_candidateList[3];
    QString correlation1 = m_candidateList[4];
    QString frequency1 = m_candidateList[5];
    QString mean1 = m_candidateList[6];
    QString modulation1 = m_candidateList[7];
    QString decomposition1 = m_candidateList[8];
    QString simulation1 = m_candidateList[9];
    QString spatial1 = m_candidateList[10];
    QString randomness1 = m_candidateList[11];
    QString spectrum1 = m_candidateList[12];
    
    QString candidate2 = m_candidateList[13];
    QString coherence2 = m_candidateList[16];
    QString correlation2 = m_candidateList[17];
    QString frequency2 = m_candidateList[18];
    QString mean2 = m_candidateList[19];
    QString modulation2 = m_candidateList[20];
    QString decomposition2 = m_candidateList[21];
    QString simulation2 = m_candidateList[22];
    QString spatial2 = m_candidateList[23];
    QString randomness2 = m_candidateList[24];
    QString spectrum2 = m_candidateList[25];

    if (comparisonCategory == LabRPS::objGroupCoherenceFunction)
    {
        if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate1();
            ComputeCrossCoherenceVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
           
            setOjectDependencyForCanditate2();
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
            
            setOjectDependencyForCanditate1();
            ComputeFrequenciesVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
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
            
            setOjectDependencyForCanditate1();
            ComputeMeanWindSpeedVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeMeanWindSpeedVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            
            setOjectDependencyForCanditate1();
            ComputeMeanWindSpeedVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
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
            
            setOjectDependencyForCanditate1();
            ComputeModulationVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeModulationVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeModulationVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate1();
            ComputeModulationVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
           
            setOjectDependencyForCanditate2();
            ComputeModulationVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeModulationVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            
            setOjectDependencyForCanditate1();
            ComputeModulationVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
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
            
            setOjectDependencyForCanditate1();
            ComputeDecomposedCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeDecomposedCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            
            setOjectDependencyForCanditate1();
            ComputeDecomposedCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeDecomposedCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
           
            setOjectDependencyForCanditate1();
            ComputeDecomposedCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeDecomposedCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupSimulationMethod)
    {
        if (comparisonFunction == LabRPS::Simulate)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultCandidate1.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);
            m_resultCandidate2.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfTimeIncrements);
            
            setOjectDependencyForCanditate1();
            Simulate(candidate1, m_resultCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            Simulate(candidate2, m_resultCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && m_windLabData.largeScaleSimulationMode)
        {
            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfTimeIncrements);
            
            setOjectDependencyForCanditate1();
            SimulateInLargeScaleMode(candidate1, windVelocityFileName1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            SimulateInLargeScaleMode(candidate2, windVelocityFileName2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupAlongWindSpectrum && 1 == m_windLabData.direction)
    {
        if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate1();
            ComputeXCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
           
            setOjectDependencyForCanditate2();
            ComputeXCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            
            setOjectDependencyForCanditate1();
            ComputeXCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeXCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeXCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            
            setOjectDependencyForCanditate1();
            ComputeXCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeXCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupAcrossWindSpectrum && 2 == m_windLabData.direction)
    {
        if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
           
            setOjectDependencyForCanditate1();
            ComputeYCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeYCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            
            setOjectDependencyForCanditate1();
            ComputeYCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeYCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeYCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
           
            setOjectDependencyForCanditate1();
            ComputeYCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeYCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupVerticalWindSpectrum && 3 == m_windLabData.direction)
    {
        if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorF)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfFrequency);

            ComputeFrequenciesVectorF(m_windLabData.freqencyDistribution, m_resultVectorVariable, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate1();
            ComputeZCrossSpectrumVectorF(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeZCrossSpectrumVectorF(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorT)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfTimeIncrements);

            fillVectorWithTimeIncrements(m_resultVectorVariable);
            
            setOjectDependencyForCanditate1();
            ComputeZCrossSpectrumVectorT(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
           
            setOjectDependencyForCanditate2();
            ComputeZCrossSpectrumVectorT(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
        else if (comparisonFunction == LabRPS::ComputeZCrossSpectrumVectorP)
        {
            m_resultVectorVariable.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1.resize(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate2.resize(m_windLabData.numberOfSpatialPosition);

            fillVectorWithNumbers(m_resultVectorVariable, m_windLabData.numberOfSpatialPosition);
            
            setOjectDependencyForCanditate1();
            ComputeZCrossSpectrumVectorP(candidate1, m_resultVectorCandidate1, computationTime1, memoryConsumption1, m_information);
            
            setOjectDependencyForCanditate2();
            ComputeZCrossSpectrumVectorP(candidate2, m_resultVectorCandidate2, computationTime2, memoryConsumption2, m_information);
        }
    }

    if (m_windLabData.comparisonType == 1) // accuracy
    {
        emit showAccuracyComparisonOutput();
    }
}

void RPSWindLabComparisonWorker::timeOutp()
{
    if (1 == m_resultOutputType)
    {

        for (int i = 0; i < m_totalNumber; i ++)
        {
            m_windLabData.numberOfSpatialPosition = m_minNumberOfLocation + i*m_numberOfLocationIncrement;
            workerComparing();
            m_resultVectorVariableVec.push_back(m_windLabData.numberOfSpatialPosition);
            m_resultVectorCandidate1Vec.push_back(computationTime1);
            m_resultVectorCandidate2Vec.push_back(computationTime2);
        }
    }
    else if (2 == m_resultOutputType)
    {
        for (int i = 0; i < m_totalNumber; i++ )
        {
            m_windLabData.numberOfFrequency = m_minNumberOfFrequency + i*m_numberOfFrequencyIncrement;
            workerComparing();
            m_resultVectorVariableVec.push_back(m_windLabData.numberOfFrequency);
            m_resultVectorCandidate1Vec.push_back(computationTime1);
            m_resultVectorCandidate2Vec.push_back(computationTime2);
        }
    }
    else if (3 == m_resultOutputType)
    {
        for (int i = 0; i < m_totalNumber; i++ )
        {
            m_windLabData.numberOfTimeIncrements = m_minNumberOfTime + i*m_numberOfTimeIncrement;
            workerComparing();
            m_resultVectorVariableVec.push_back(m_windLabData.numberOfTimeIncrements);
            m_resultVectorCandidate1Vec.push_back(computationTime1);
            m_resultVectorCandidate2Vec.push_back(computationTime2);
        }
    }

    if (m_windLabData.comparisonType == 2) // time
    {
        emit showTimeComparisonOutput();
    }
}

void RPSWindLabComparisonWorker::memoryOutp()
{
    emit showMemoryComparisonOutput();
}

QStringList RPSWindLabComparisonWorker::getInformation()
{
    return m_information;
}

void RPSWindLabComparisonWorker::setOjectDependencyForCanditate1()
{
    QString noSelection = "<None>";

    QString coherence1 = m_candidateList[3];
    QString correlation1 = m_candidateList[4];
    QString frequency1 = m_candidateList[5];
    QString mean1 = m_candidateList[6];
    QString modulation1 = m_candidateList[7];
    QString decomposition1 = m_candidateList[8];
    QString simulation1 = m_candidateList[9];
    QString spatial1 = m_candidateList[10];
    QString randomness1 = m_candidateList[11];
    QString spectrum1 = m_candidateList[12];

    if (noSelection != coherence1)
    {
        m_windLabData.coherenceFunction = coherence1;
    }
    if (noSelection != correlation1)
    {
        m_windLabData.correlationFunction = correlation1;
    }
    if (noSelection != frequency1)
    {
        m_windLabData.freqencyDistribution = frequency1;
    }
    if (noSelection != mean1)
    {
        m_windLabData.meanFunction = mean1;
    }
    if (noSelection != modulation1)
    {
        m_windLabData.modulationFunction = modulation1;
    }
    if (noSelection != decomposition1)
    {
        m_windLabData.cpsdDecompositionMethod = decomposition1;
    }
    if (noSelection != simulation1)
    {
        m_windLabData.simulationMethod = simulation1;
    }
    if (noSelection != spatial1)
    {
        m_windLabData.spatialDistribution = spatial1;
    }
    if (noSelection != randomness1)
    {
        m_windLabData.randomnessProvider = randomness1;
    }
    if (noSelection != spectrum1)
    {
        m_windLabData.spectrumModel = spectrum1;
    }
}


void RPSWindLabComparisonWorker::setOjectDependencyForCanditate2()
{
    QString noSelection = "<None>";
    
    QString candidate2 = m_candidateList[13];
    QString coherence2 = m_candidateList[16];
    QString correlation2 = m_candidateList[17];
    QString frequency2 = m_candidateList[18];
    QString mean2 = m_candidateList[19];
    QString modulation2 = m_candidateList[20];
    QString decomposition2 = m_candidateList[21];
    QString simulation2 = m_candidateList[22];
    QString spatial2 = m_candidateList[23];
    QString randomness2 = m_candidateList[24];
    QString spectrum2 = m_candidateList[25];

    if (noSelection != coherence2)
    {
        m_windLabData.coherenceFunction = coherence2;
    }
    if (noSelection != correlation2)
    {
        m_windLabData.correlationFunction = correlation2;
    }
    if (noSelection != frequency2)
    {
        m_windLabData.freqencyDistribution = frequency2;
    }
    if (noSelection != mean2)
    {
        m_windLabData.meanFunction = mean2;
    }
    if (noSelection != modulation2)
    {
        m_windLabData.modulationFunction = modulation2;
    }
    if (noSelection != decomposition2)
    {
        m_windLabData.cpsdDecompositionMethod = decomposition2;
    }
    if (noSelection != simulation2)
    {
        m_windLabData.simulationMethod = simulation2;
    }
    if (noSelection != spatial2)
    {
        m_windLabData.spatialDistribution = spatial2;
    }
    if (noSelection != randomness2)
    {
        m_windLabData.randomnessProvider = randomness2;
    }
    if (noSelection != spectrum2)
    {
        m_windLabData.spectrumModel = spectrum2;
    }
}
