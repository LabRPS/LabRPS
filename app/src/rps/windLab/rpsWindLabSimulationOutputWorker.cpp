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
        IrpsWLFrequencyDistribution *currentFreqDistr = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

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

        QTime t;
        t.start();

        // running the computation
        currentFreqDistr->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector, m_information);
        m_information.append(tr("The computation of the frequencies took %1 ms").arg(QString::number(t.elapsed())));

        delete currentFreqDistr;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex == 0)
    {
        // Build an coherence function and frequency distribution functions
        IrpsWLFrequencyDistribution *currentFreqDistr = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good coherence object
        if (NULL == currentFreqDistr)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfFrequency, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentFreqDistr->ComputeFrequenciesMatrixFP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the frequencies took %1 ms").arg(QString::number(t.elapsed())));

        delete currentFreqDistr;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    emit showFrequencyDistributionOutput();
}
void RPSWindLabSimulationOutputWorker::locationDistributionOutp()
{
    IrpsWLLocationDistribution *currentLocationDistribution = CrpsLocationDistributionFactory::BuildLocationDistribution(m_windLabData.spatialDistribution);

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

    QTime t;
    t.start();

    // running the computation
    currentLocationDistribution->ComputeLocationCoordinateMatrixP3(m_windLabData, m_ResultMatrix, m_information);

    m_information.append(tr("The computation of the spatial distribution took %1 ms").arg(QString::number(t.elapsed())));

    delete currentLocationDistribution;

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
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(m_windLabData.spectrumModel);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorF(m_windLabData, m_ResultVector, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
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
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(m_windLabData.spectrumModel);

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

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorT(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorP(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(m_windLabData.spectrumModel);

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

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixTP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(m_windLabData.spectrumModel);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfFrequency, m_windLabData.numberOfSpatialPosition);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixFP(m_windLabData, m_ResultMatrix, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLXSpectrum *currentPSD = CrpsXSpectrumFactory::BuildXSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixTF(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    emit showXSpectrumOutput();
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
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(m_windLabData.spectrumModel);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumVectorF(m_windLabData, m_ResultVector, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
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
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(m_windLabData.spectrumModel);

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

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumVectorT(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumVectorP(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(m_windLabData.spectrumModel);

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

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumMatrixTP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(m_windLabData.spectrumModel);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfFrequency, m_windLabData.numberOfSpatialPosition);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumMatrixFP(m_windLabData, m_ResultMatrix, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLYSpectrum *currentPSD = CrpsYSpectrumFactory::BuildYSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeYCrossSpectrumMatrixTF(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
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
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(m_windLabData.spectrumModel);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumVectorF(m_windLabData, m_ResultVector, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
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
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(m_windLabData.spectrumModel);

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

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumVectorT(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumVectorP(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(m_windLabData.spectrumModel);

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

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumMatrixTP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(m_windLabData.spectrumModel);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfFrequency, m_windLabData.numberOfSpatialPosition);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumMatrixFP(m_windLabData, m_ResultMatrix, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLZSpectrum *currentPSD = CrpsZSpectrumFactory::BuildZSpectrum(m_windLabData.spectrumModel);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeZCrossSpectrumMatrixTF(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
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
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(m_windLabData.cpsdDecompositionMethod);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorF(m_windLabData, m_ResultVector, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
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
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(m_windLabData.cpsdDecompositionMethod);

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

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorT(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumVectorP(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
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
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix2.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumMatrixPP(m_windLabData, m_ResultMatrix2, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumMatrixTP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(m_windLabData.cpsdDecompositionMethod);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfFrequency, m_windLabData.numberOfSpatialPosition);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumMatrixFP(m_windLabData, m_ResultMatrix, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK > 0 &&
             m_locationK <= m_windLabData.numberOfSpatialPosition &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1

    )
    {
        // Build the psd model and the frequency distribution functions
        IrpsWLPSDdecompositionMethod *currentPSD = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(m_windLabData.cpsdDecompositionMethod);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum decomposition method");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeDecomposedCrossSpectrumMatrixTF(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the decomposed spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    emit showDecomposedSpectrumOutput();
}



void RPSWindLabSimulationOutputWorker::coherenceOutp()
{
    // Build an coherence function and frequency distribution functions
    IrpsWLCoherence *currentCoherenceFunction = CrpsCoherenceFactory::BuildCoherence(m_windLabData.coherenceFunction);

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
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentCoherenceFunction->ComputeCrossCoherenceVectorF(m_windLabData, m_ResultVector, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentFrequencyDistribution;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == m_windLabData.numberOfSpatialPosition + 1 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();
        // running the computation
        currentCoherenceFunction->ComputeCrossCoherenceMatrixPP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the coherence function took %1 ms").arg(QString::number(t.elapsed())));
        delete currentFrequencyDistribution;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        delete currentCoherenceFunction;
        return;
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
        m_frequencyIndex > 0 &&
        m_frequencyIndex <= m_windLabData.numberOfFrequency &&
        m_timeIndex == m_windLabData.numberOfTimeIncrements + 1)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(m_windLabData.modulationFunction);

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

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorT(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {
        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(m_windLabData.modulationFunction);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfFrequency);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorF(m_windLabData, m_ResultVector, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {
        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(m_windLabData.modulationFunction);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultVector.resize(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationVectorP(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex > 0 &&
             m_frequencyIndex <= m_windLabData.numberOfFrequency &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1)
    {
        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(m_windLabData.modulationFunction);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationMatrixTP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex > 0 &&
             m_timeIndex <= m_windLabData.numberOfTimeIncrements)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(m_windLabData.modulationFunction);
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }
        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfFrequency, m_windLabData.numberOfSpatialPosition);
        m_ResultVector2.resize(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationMatrixFP(m_windLabData, m_ResultMatrix, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, m_ResultVector2, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK == 0 &&
             m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLModulation *currentModulationFtn = CrpsModulationFactory::BuildModulation(m_windLabData.modulationFunction);

        // Check whether good coherence object
        if (NULL == currentModulationFtn)
        {
            m_information.append("Invalid modulation function");
            emit sendInformation(m_information);
            emit progressBarHide();
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentModulationFtn->ComputeModulationMatrixTF(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the modulation function took %1 ms").arg(QString::number(t.elapsed())));

        delete currentModulationFtn;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
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
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(m_windLabData.meanFunction);

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

        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedVectorP(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

        delete currentMeanWindProfil;
    }
    else if (m_locationJ > 0 &&
             m_locationJ <= m_windLabData.numberOfSpatialPosition &&
             m_locationK == 0 &&
             m_frequencyIndex == 0 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1)
    {
        // allocate memories to receive the computed coherence and frequencies
        // Build an coherence function and frequency distribution functions
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(m_windLabData.meanFunction);

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

        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedVectorT(m_windLabData, m_ResultVector, m_information);

        m_information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

        delete currentMeanWindProfil;
    }
    else if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
             m_locationK == 0 &&
             m_frequencyIndex == 0 &&
             m_timeIndex == m_windLabData.numberOfTimeIncrements + 1)
    {
        // allocate memories to receive the computed coherence and frequencies
        // Build an coherence function and frequency distribution functions
        IrpsWLMean *currentMeanWindProfil = CrpsMeanFactory::BuildMean(m_windLabData.meanFunction);

        // Check whether good coherence object
        if (NULL == currentMeanWindProfil)
        {
            m_information.append("Invalid mean wind profil");
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        m_ResultMatrix.resize(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentMeanWindProfil->ComputeMeanWindSpeedMatrixTP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the mean wind took %1 ms").arg(QString::number(t.elapsed())));

        delete currentMeanWindProfil;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    emit showMeanWindVelocityOutput();
}

void RPSWindLabSimulationOutputWorker::randomPhaseOutp()
{
    if (m_locationJ == m_windLabData.numberOfSpatialPosition + 1 &&
        m_locationK == 0 &&
        m_frequencyIndex == m_windLabData.numberOfFrequency + 1 &&
        m_timeIndex == 0)
    {

        // Build an coherence function and frequency distribution functions
        IrpsWLRandomness *currentRandomnessProvider = CrpsRandomnessFactory::BuildRandomness(m_windLabData.randomnessProvider);

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

        QTime t;
        t.start();

        // running the computation
        currentRandomnessProvider->GenerateRandomArrayFP(m_windLabData, m_ResultMatrix, m_information);

        m_information.append(tr("The computation of the random phase took %1 ms").arg(QString::number(t.elapsed())));

        delete currentRandomnessProvider;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
        emit sendInformation(m_information);
        emit progressBarHide();
        return;
    }

    emit showRandomPhaseOutput();
}
