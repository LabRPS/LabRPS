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
    m_information.append("worker distroyed");
    emit sendInformation(m_information);
}

void RPSWindLabSimulationOutputWorker::spectrumXModelOut()
{
    QTime t;
    t.start();

    if (isStopped())
    {

        stopped = false;

        emit progressBarShow();
        spectrumXModelOutp();
    }
    m_information.append(QString::number(t.elapsed()));

    emit sendInformation(m_information);
    emit progressBarHide();
    //emit spectrumXModelGraph(dPSDMatrix);

    stopped = true;

    // Self-destruct now!
    //();
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
    emit progressBarSetValue(currentStep);
    emit progressBarHide();

    if (0 != maxStep || maxStep != maxStepOld)
    {

        emit progressBarSetMin(minStep);
        emit progressBarSetMax(maxStep);
        emit progressBarReset();

        maxStepOld = maxStep;
    }
    mutex.unlock();
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
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        dPSDVector(m_windLabData.numberOfFrequency);
        dFrequencyVector(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorF(m_windLabData, dPSDVector, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, dFrequencyVector, m_information);

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
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        dPSDVector(m_windLabData.numberOfTimeIncrements);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorT(m_windLabData, dPSDVector, m_information);

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
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        dPSDVector(m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumVectorP(m_windLabData, dPSDVector, m_information);

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
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        dPSDMatrix.resize(m_windLabData.numberOfSpatialPosition, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixPP(m_windLabData, dPSDMatrix, m_information);

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
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        dPSDMatrix(m_windLabData.numberOfTimeIncrements, m_windLabData.numberOfSpatialPosition);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixTP(m_windLabData, dPSDMatrix, m_information);

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
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        dPSDMatrix(m_windLabData.numberOfFrequency, m_windLabData.numberOfSpatialPosition);
        dFrequencyVector(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixFP(m_windLabData, dPSDMatrix, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, dFrequencyVector, m_information);

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
        IrpsWLFrequencyDistribution *currentFrequencyDistribution = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(m_windLabData.freqencyDistribution);

        // Check whether good frequency object
        if (NULL == currentPSD)
        {
            m_information.append("Invalid spectrum model");
            return;
        }

        if (NULL == currentFrequencyDistribution)
        {
            m_information.append("Invalid frequency distribution");
            return;
        }

        // allocate memories to receive the computed coherence and frequencies
        dPSDMatrix(m_windLabData.numberOfFrequency, m_windLabData.numberOfTimeIncrements);
        dFrequencyVector(m_windLabData.numberOfFrequency);

        QTime t;
        t.start();

        // running the computation
        currentPSD->ComputeXCrossSpectrumMatrixTF(m_windLabData, dPSDMatrix, m_information);
        currentFrequencyDistribution->ComputeFrequenciesVectorF(m_windLabData, dFrequencyVector, m_information);

        m_information.append(tr("The computation of the spectrum took %1 ms").arg(QString::number(t.elapsed())));

        delete currentPSD;
        delete currentFrequencyDistribution;
    }
    else
    {
        m_information.append("Sorry, there is no function that meet your requirements.");
    }

    // send info the main window to show it
    emit sendInformation(m_information);

    // clear the information list
    m_information.clear();
}