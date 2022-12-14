#include "rpsWindLabSimulationOutputWorker.h"
#include "RPSWindLabAPI.h"
#include "RPS.h"
#include <QTime>

RPSWindLabSimulationOutputWorker::RPSWindLabSimulationOutputWorker(CRPSWindLabsimuData windLabData,
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
    workerOutputType = 1; // vector and 2 for matrix

}

RPSWindLabSimulationOutputWorker::~RPSWindLabSimulationOutputWorker()
{
    m_information.clear();
    m_information.append("Output worker distroyed");
    emit sendInformation(m_information);
}

void RPSWindLabSimulationOutputWorker::stop()
{
    mutex.lock();
    stopped = true;
    mutex.unlock();
}

bool RPSWindLabSimulationOutputWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}

void RPSWindLabSimulationOutputWorker::progressBarMinMaxValue()
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

QStringList RPSWindLabSimulationOutputWorker::getInformation()
{
    return m_information;
}

void RPSWindLabSimulationOutputWorker::windVelocityOut()
{
    if (isStopped())
    {

        stopped = false;
        windVelocityOutp();
    }

    stopped = true;
}
void RPSWindLabSimulationOutputWorker::frequencyDistributionOut()
{
    if (isStopped())
    {
        stopped = false;
        frequencyDistributionOutp();
    }

    stopped = true;
}
void RPSWindLabSimulationOutputWorker::locationDistributionOut()
{
    if (isStopped())
    {
        stopped = false;
        locationDistributionOutp();
    }

    stopped = true;
}

void RPSWindLabSimulationOutputWorker::spectrumXModelOut()
{

    if (isStopped())
    {
        stopped = false;
        spectrumXModelOutp();
    }

    stopped = true;
}

void RPSWindLabSimulationOutputWorker::spectrumYModelOut()
{
    if (isStopped())
    {
        stopped = false;
        spectrumYModelOutp();
    }

    stopped = true;
}
void RPSWindLabSimulationOutputWorker::spectrumZModelOut()
{
    if (isStopped())
    {
        stopped = false;
        spectrumZModelOutp();
    }

    stopped = true;
}


void RPSWindLabSimulationOutputWorker::decomposedSpectrumModelOut()
{

    if (isStopped())
    {
        stopped = false;
        decomposedSpectrumModelOutp();
    }

    stopped = true;
}

void RPSWindLabSimulationOutputWorker::coherenceOut()
{
    if (isStopped())
    {
        stopped = false;
        coherenceOutp();
    }

    stopped = true;
}

void RPSWindLabSimulationOutputWorker::correlationOut()
{
    if (isStopped())
    {
        stopped = false;
        correlationOutp();
    }

    stopped = true;
}
void RPSWindLabSimulationOutputWorker::modulationOut()
{
    if (isStopped())
    {
        stopped = false;
        modulationOutp();
    }

    stopped = true;
}
void RPSWindLabSimulationOutputWorker::meanWindVelocityOut()
{
    if (isStopped())
    {
        stopped = false;
        meanWindVelocityOutp();
    }

    stopped = true;
}

void RPSWindLabSimulationOutputWorker::randomPhaseOut()
{
    if (isStopped())
    {
        stopped = false;
        randomPhaseOutp();
    }

    stopped = true;
}

void RPSWindLabSimulationOutputWorker::windVelocityOutp()
{
}
void RPSWindLabSimulationOutputWorker::frequencyDistributionOutp()
{
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK == 0 &&
            m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
            m_timeIndex == 0)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLFrequencyDistribution *currentFreqDistr = CrpsFrequencyDistributionFactory::BuildObject(m_windLabData.freqencyDistribution);

        // Check whether good coherence object
        if (NULL == currentFreqDistr)
        {
            m_information.append("Invalid mean wind profil");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;

        QTime t;
        t.start();

        // running the computation
        currentFreqDistr->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);
        m_information.append(tr("The computation of the frequencies took %1 ms").arg(QString::number(t.elapsed())));

        delete currentFreqDistr;
    }
    else
    {
        m_locationJ = 1;
        m_locationK = 0;
        m_frequencyIndex = 1;
        m_timeIndex = 0;

        // Build an coherence function and frequency distribution functions
        IrpsWLFrequencyDistribution *currentFreqDistr = CrpsFrequencyDistributionFactory::BuildObject(m_windLabData.freqencyDistribution);

        // Check whether good coherence object
        if (NULL == currentFreqDistr)
        {
            m_information.append("Invalid mean wind profil");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentFreqDistr->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);
        m_information.append(tr("The computation of the frequencies took %1 ms").arg(QString::number(t.elapsed())));

        delete currentFreqDistr;
    }

    tableName = "Frequencies";
    plotTitle = "Frequencies";
    plotxlable = "Indexes";
    plotylabel = "Frequencies";

    emit showFrequencyDistributionOutput();
}
void RPSWindLabSimulationOutputWorker::locationDistributionOutp()
{
    IrpsWLLocationDistribution *currentLocationDistribution = CrpsLocationDistributionFactory::BuildObject(m_windLabData.spatialDistribution);

    // Check whether good spatial distribution object
    if (NULL == currentLocationDistribution)
    {
        m_information.append("Invalid spatial distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories to receive the computed coherence and frequencies
    m_ResultMatrix.resize(m_windLabData.numberOfSpatialPosition, 3);
    workerOutputType = 2;
    QTime t;
    t.start();

    // running the computation
    currentLocationDistribution->ComputeLocationCoordinateMatrixP3(m_windLabData, m_ResultMatrix, m_information);

    m_information.append(tr("The computation of the spatial distribution took %1 ms").arg(QString::number(t.elapsed())));

    delete currentLocationDistribution;

    tableName = "Locations";
    plotTitle = "Locations";
    plotxlable = "Indexes";
    plotylabel = "Locations";

    emit showLocationDistributionOutput();
}

void RPSWindLabSimulationOutputWorker::spectrumXModelOutp()
{
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
            m_timeIndex > 0 &&
            m_timeIndex <= m_windLabData.numberOfTimeIncrements

            )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXAutoSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "spectrumX";
        plotTitle = "Along Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

             )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXAutoSpectrumVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        tableName = "spectrumX";
        plotTitle = "Along Wind Spectrum";
        plotxlable = "Time";
        plotylabel = "spectrum";
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == m_locationJ &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

             )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);
        workerOutputType = 2;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        tableName = "spectrumX";
        plotTitle = "Along Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }
    else
    {
        
        // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXAutoSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        tableName = "spectrumX";
        plotTitle = "Along Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }

    emit showXSpectrumOutput();

    // m_information.append("Sorry, there is no function that meet your requirements.");
    // emit sendInformation(m_information);
    // emit progressBarHide();
    // return;
}

void RPSWindLabSimulationOutputWorker::spectrumYModelOutp()
{
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
            m_timeIndex > 0 &&
            m_timeIndex <= m_windLabData.numberOfTimeIncrements

            )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYAutoSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        tableName = "spectrumY";
        plotTitle = "Across Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1
             )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYAutoSpectrumVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "spectrumY";
        plotTitle = "Across Wind Spectrum";
        plotxlable = "Time";
        plotylabel = "spectrum";
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == m_locationJ &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

             )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);
        workerOutputType = 2;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "spectrumY";
        plotTitle = "Across Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }
    else
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYAutoSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "spectrumY";
        plotTitle = "Across Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }

    emit showYSpectrumOutput();
}
void RPSWindLabSimulationOutputWorker::spectrumZModelOutp()
{
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
            m_timeIndex > 0 &&
            m_timeIndex <= m_windLabData.numberOfTimeIncrements

            )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZAutoSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "spectrumZ";
        plotTitle = "Vertical Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1
             )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZAutoSpectrumVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "spectrumZ";
        plotTitle = "Vertical Wind Spectrum";
        plotxlable = "Time";
        plotylabel = "spectrum";
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

             )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);
        workerOutputType = 2;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        tableName = "spectrumZ";
        plotTitle = "Vertical Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }
    else
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildObject(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZAutoSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "spectrumZ";
        plotTitle = "Vertical Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "spectrum";
    }

    emit showZSpectrumOutput();
}


void RPSWindLabSimulationOutputWorker::decomposedSpectrumModelOutp()
{
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
            m_timeIndex > 0 &&
            m_timeIndex <= m_windLabData.numberOfTimeIncrements

            )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildObject(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "DecomposedSpectrum";
        plotTitle = "Decomposed Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "Decomposed Spectrum";
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

             )
    {

        // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildObject(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "DecomposedSpectrum";
        plotTitle = "Decomposed Wind Spectrum";
        plotxlable = "Time";
        plotylabel = "Decomposed Spectrum";
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == m_locationJ &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

             )
    {
        if(1 == m_windLabData.direction)
        {
            spectrumXModelOutp();
        }
        if(2 == m_windLabData.direction)
        {
            spectrumYModelOutp();
        }
        if(3 == m_windLabData.direction)
        {
            spectrumZModelOutp();
        }

        // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildObject(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }
        workerOutputType = 3;
        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix2.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix2, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "DecomposedSpectrum";
        plotTitle = "Decomposed Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "Decomposed Spectrum";
    }
    else
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildObject(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;

        tableName = "DecomposedSpectrum";
        plotTitle = "Decomposed Wind Spectrum";
        plotxlable = "Frequency";
        plotylabel = "Decomposed Spectrum";
    }

    emit showDecomposedSpectrumOutput();
}



void RPSWindLabSimulationOutputWorker::coherenceOutp()
{
    // Build an coherence function and frequency distribution functions
    IrpsWLCoherence *currentCoherenceFunction = CrpsCoherenceFactory::BuildObject(m_windLabData.coherenceFunction);

    // Check whether good coherence object
    if (NULL == currentCoherenceFunction)
    {
        m_information.append("Invalid coherence function");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
            m_timeIndex > 0 &&
            m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {
        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentCoherenceFunction->ComputeCrossCoherenceVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));

        tableName = "Coherence";
        plotTitle = "Cross coherence";
        plotxlable = "Frequency";
        plotylabel = "Coherence";
    }
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex > 0 &&
            m_frequencyIndex <= m_windLabData.numberOfFrequency &&
            m_timeIndex == m_windLabData.numberOfTimeIncrements + 1
            )
    {
        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentCoherenceFunction->ComputeCrossCoherenceVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));

        tableName = "Coherence";
        plotTitle = "Cross coherence";
        plotxlable = "Time";
        plotylabel = "Coherence";
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == m_windLabData.numberOfSpatialPosition + 1 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {
        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);
        workerOutputType = 2;
        QTime t;
        t.start();
        // running the computation
        currentCoherenceFunction->ComputeCrossCoherenceMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));

        tableName = "Coherence";
        plotTitle = "Cross coherence";
        plotxlable = "Frequency";
        plotylabel = "Coherence";
    }
    else
    {
        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentCoherenceFunction->ComputeCrossCoherenceVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));

        tableName = "Coherence";
        plotTitle = "Cross coherence";
        plotxlable = "Frequency";
        plotylabel = "Coherence";
    }

    // Delete the object
    delete currentCoherenceFunction;

    emit showCoherenceOutput();
}
void RPSWindLabSimulationOutputWorker::correlationOutp()
{
}

void RPSWindLabSimulationOutputWorker::modulationOutp()
{
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK == 0 &&
            m_frequencyIndex == 0 &&
            m_timeIndex == m_windLabData.numberOfTimeIncrements + 1)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildObject(m_windLabData.modulationFunction);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;

        tableName = "Modulation";
        plotTitle = "Modulation";
        plotxlable = "Time";
        plotylabel = "Modulation";
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == 0 &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildObject(m_windLabData.modulationFunction);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;

        tableName = "Modulation";
        plotTitle = "Modulation";
        plotxlable = "Location Index";
        plotylabel = "Modulation";
    }
    else
    {
        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildObject(m_windLabData.modulationFunction);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;

        tableName = "Modulation";
        plotTitle = "Modulation";
        plotxlable = "Time";
        plotylabel = "Modulation";
    }

    emit showModulationOutput();
}

void RPSWindLabSimulationOutputWorker::meanWindVelocityOutp()
{
    if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
            m_locationK == 0 &&
            m_frequencyIndex == 0 &&
            m_timeIndex > 0 &&
            m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildObject(m_windLabData.meanFunction);

        // Check whether good coherence object
        if (NULL == currentMeanWindProfil)
        {
            m_information.append("Invalid mean wind profil");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
        m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

        delete currentMeanWindProfil;

        tableName = "MeanWindSpeed";
        plotTitle = "Mean Wind Speed";
        plotxlable = "Location Index";
        plotylabel = "Mean Wind Speed";
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK == 0 &&
             m_frequencyIndex == 0 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildObject(m_windLabData.meanFunction);

        // Check whether good coherence object
        if (NULL == currentMeanWindProfil)
        {
            m_information.append("Invalid mean wind profil");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;
        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

        delete currentMeanWindProfil;

        tableName = "MeanWindSpeed";
        plotTitle = "Mean Wind Speed";
        plotxlable = "Time";
        plotylabel = "Mean Wind Speed";
    }
    else
    {
        // Build an coherence function and frequency distribution functions
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildObject(m_windLabData.meanFunction);

        // Check whether good coherence object
        if (NULL == currentMeanWindProfil)
        {
            m_information.append("Invalid mean wind profil");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
        m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
        workerOutputType = 1;

        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

        delete currentMeanWindProfil;

        tableName = "MeanWindSpeed";
        plotTitle = "Mean Wind Speed";
        plotxlable = "Location Index";
        plotylabel = "Mean Wind Speed";
    }

    emit showMeanWindVelocityOutput();
}

void RPSWindLabSimulationOutputWorker::randomPhaseOutp()
{
    // Build an coherence function and frequency distribution functions
    IrpsWLRandomness *currentRandomnessProvider = CrpsRandomnessFactory::BuildObject(m_windLabData.randomnessProvider);

    // Check whether good coherence object
    if (NULL == currentRandomnessProvider)
    {
        m_information.append("Invalid randomness provider");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories to receive the computed coherence and frequencies
    m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);
    workerOutputType = 2;

    QTime t;
    t.start();

    // running the computation
    currentRandomnessProvider->GenerateRandomArrayFP(m_windLabData, m_ResultMatrix, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentRandomnessProvider;

    tableName = "RandomPhase";
    plotTitle = "Random Phase";
    plotxlable = "Index";
    plotylabel = "Random Phase";

    emit showRandomPhaseOutput();
}
void RPSWindLabSimulationOutputWorker::cumulativeProbabilityDistributionOutp()
{
    // Build the object
    IrpsWLCumulativeProbabilityDistribution *currentObject = CrpsCumulativeProbabilityDistributionFactory::BuildObject(m_windLabData.cumulativeProbabilityDistribution);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeCDFVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "CPD";
    plotTitle = "Cumulative Probability";
    plotxlable = "x";
    plotylabel = "Cumulative Probability";

    emit showCumulativeProbabilityDistributionOutput();
}
void RPSWindLabSimulationOutputWorker::gustFactorOutp()
{
    // Build the object
    IrpsWLGustFactor *currentObject = CrpsGustFactorFactory::BuildObject(m_windLabData.gustFactor);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeGustFactorVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    emit showGustFactorOutput();

    tableName = "GustFactor";
    plotTitle = "Gust Factor";
    plotxlable = "x";
    plotylabel = "Gust Factor";
}

void RPSWindLabSimulationOutputWorker::kurtosisOutp()
{
    // Build the object
    IrpsWLKurtosis *currentObject = CrpsKurtosisFactory::BuildObject(m_windLabData.kurtosis);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeKurtosisVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "Kurtosis";
    plotTitle = "Kurtosis";
    plotxlable = "x";
    plotylabel = "Kurtosis";

    emit showKurtosisOutput();
}
void RPSWindLabSimulationOutputWorker::peakFactorOutp()
{
    // Build the object
    IrpsWLPeakFactor *currentObject = CrpsPeakFactorFactory::BuildObject(m_windLabData.peakFactor);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputePeakFactorVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "PeackFactor";
    plotTitle = "Peack Factor";
    plotxlable = "x";
    plotylabel = "Peack Factor";

    emit showPeakFactorOutput();
}
void RPSWindLabSimulationOutputWorker::probabilityDensityFunctionOutp()
{
    // Build the object
    IrpsWLProbabilityDensityFunction *currentObject = CrpsProbabilityDensityFunctionFactory::BuildObject(m_windLabData.probabilityDensityFunction);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputePDFVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "PDF";
    plotTitle = "Probability Distribution Function";
    plotxlable = "x";
    plotylabel = "Probability Distribution Function";

    emit showProbabilityDensityFunctionOutput();
}

void RPSWindLabSimulationOutputWorker::roughnessOutp()
{
    // Build the object
    IrpsWLRoughness *currentObject = CrpsRoughnessFactory::BuildObject(m_windLabData.roughness);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeRoughnessVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "Roughness";
    plotTitle = "Roughness";
    plotxlable = "x";
    plotylabel = "Roughness";

    emit showRoughnessOutput();
}
void RPSWindLabSimulationOutputWorker::shearVelocityOfFlowOutp()
{
    // Build the object
    IrpsWLShearVelocityOfFlow *currentObject = CrpsShearVelocityOfFlowFactory::BuildObject(m_windLabData.shearVelocityOfFlow);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeShearVelocityOfFlowVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "Shear Velocity";
    plotTitle = "Shear Velocity";
    plotxlable = "x";
    plotylabel = "Shear Velocity";

    emit showShearVelocityOfFlowOutput();
}
void RPSWindLabSimulationOutputWorker::skewnessOutp()
{
    // Build the object
    IrpsWLSkewness *currentObject = CrpsSkewnessFactory::BuildObject(m_windLabData.skewness);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeSkewnessVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "Skewness";
    plotTitle = "Skewness";
    plotxlable = "x";
    plotylabel = "Skewness";

    emit showSkewnessOutput();
}
void RPSWindLabSimulationOutputWorker::standardDeviationOutp()
{
    // Build the object
    IrpsWLStandardDeviation *currentObject = CrpsStandardDeviationFactory::BuildObject(m_windLabData.standardDeviation);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeStandardDeviationVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "StandardDeviation";
    plotTitle = "Standard Deviation";
    plotxlable = "x";
    plotylabel = "Standard Deviation";

    emit showStandardDeviationOutput();
}
void RPSWindLabSimulationOutputWorker::turbulenceIntensityOutp()
{
    // Build the object
    IrpsWLTurbulenceIntensity *currentObject = CrpsTurbulenceIntensityFactory::BuildObject(m_windLabData.turbulenceIntensity);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeTurbulenceIntensityVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "TurbulenceIntensity";
    plotTitle = "Turbulence Intensity";
    plotxlable = "x";
    plotylabel = "Turbulence Intensity";

    emit showTurbulenceIntensityOutput();
}
void RPSWindLabSimulationOutputWorker::turbulenceScaleOutp()
{
    // Build the object
    IrpsWLTurbulenceScale *currentObject = CrpsTurbulenceScaleFactory::BuildObject(m_windLabData.turbulenceScale);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeTurbulenceScaleVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "TurbulenceScale";
    plotTitle = "Turbulence Scale";
    plotxlable = "x";
    plotylabel = "Turbulence Scale";

    emit showTurbulenceScaleOutput();
}
void RPSWindLabSimulationOutputWorker::varianceOutp()
{
    // Build the object
    IrpsWLVariance *currentObject = CrpsVarianceFactory::BuildObject(m_windLabData.variance);

    // Check whether good object
    if (NULL == currentObject)
    {
        m_information.append("Invalid cumulative probability distribution");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    // allocate memories
    m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);
    m_ResultVector2.resize(m_windLabData.numberOfSpatialPosition);
    workerOutputType = 1;

    QTime t;
    t.start();

    // running the computation
    currentObject->ComputeVarianceVectorP(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

    m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

    delete currentObject;

    tableName = "Variance";
    plotTitle = "Variance";
    plotxlable = "x";
    plotylabel = "Variance";

    emit showVarianceOutput();
}

void RPSWindLabSimulationOutputWorker::wavePassageEffectOutp()
{
    // Build an wave passage effect and frequency distribution functions
    IrpsWLWavePassageEffect *currentObject = CrpsWavePassageEffectFactory::BuildObject(m_windLabData.wavePassageEffect);

    // Check whether good wave passage effect object
    if (NULL == currentObject)
    {
        m_information.append("Invalid wave passage effect");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
            m_timeIndex > 0 &&
            m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {
        // allocate memories to receive the computed wave passage effect and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;

        QTime t;
        t.start();

        // running the computation
        currentObject->ComputeWavePassageEffectVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the wave passage effect took %1 ms").arg(QString::number(t.elapsed())));

        tableName = "WavePassage";
        plotTitle = "Wave Passage Effect";
        plotxlable = "Frequency";
        plotylabel = "Wave Passage Effect";
    }
    if (m_locationJ > 0 &&
            m_locationJ <= m_windLabData.numberOfSpatialPosition &&
            m_locationK > 0 &&
            m_locationK <= m_windLabData.numberOfSpatialPosition &&
            m_frequencyIndex > 0 &&
            m_frequencyIndex <= m_windLabData.numberOfFrequency &&
            m_timeIndex == m_windLabData.numberOfTimeIncrements + 1
            )
    {
        // allocate memories to receive the computed wave passage effect and frequencies
        m_ResultVector.resize(m_windLabData.numberOfTimeIncrements);
        m_ResultVector2.resize(m_windLabData.numberOfTimeIncrements);
        workerOutputType = 1;

        QTime t;
        t.start();

        // running the computation
        currentObject->ComputeWavePassageEffectVectorT(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the wave passage effect took %1 ms").arg(QString::number(t.elapsed())));

        tableName = "WavePassage";
        plotTitle = "Wave Passage Effect";
        plotxlable = "Time";
        plotylabel = "Wave Passage Effect";
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == m_windLabData.numberOfSpatialPosition + 1 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {
        // allocate memories to receive the computed wave passage effect and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);
        workerOutputType = 2;

        QTime t;
        t.start();
        // running the computation
        currentObject->ComputeWavePassageEffectMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the wave passage effect took %1 ms").arg(QString::number(t.elapsed())));
    }
    else
    {
        // allocate memories to receive the computed wave passage effect and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);
        workerOutputType = 1;

        QTime t;
        t.start();

        // running the computation
        currentObject->ComputeWavePassageEffectVectorF(m_windLabData, m_ResultVector2, m_ResultVector, m_information);

        m_information.append(tr("The computation of the wave passage effect took %1 ms").arg(QString::number(t.elapsed())));

        tableName = "WavePassage";
        plotTitle = "Wave Passage Effect";
        plotxlable = "Frequency";
        plotylabel = "Wave Passage Effect";
    }

    // Delete the object
    delete currentObject;

    emit showWavePassageEffectOutput();
}
