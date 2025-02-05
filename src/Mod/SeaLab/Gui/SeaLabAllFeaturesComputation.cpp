/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "PreCompiled.h"

#include "SeaLabAllFeaturesComputation.h"
#include <Mod/SeaLab/App/SeaLabUtils.h>
#include <Gui/MainWindow.h>
#include <Gui/AlphaPlot.h>

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMetaType>
#include <Gui/ProgressBar.h>

using namespace SeaLabGui;

SeaLabAllFeaturesComputation::SeaLabAllFeaturesComputation(SeaLab::SeaLabSimulation* sim, QObject* parent)
    : m_sim(sim), QObject(parent)
{ 
}

SeaLabAllFeaturesComputation::~SeaLabAllFeaturesComputation()
{
    
}

RPSSeaLabSimulationWorker *SeaLabAllFeaturesComputation::GetSeaLabSimulationWorker()
{
    return simulationWorker;
}

QThread* SeaLabAllFeaturesComputation::getSeaLabSimulationThread()
{ 
    return simulationThread; 
}


QString SeaLabAllFeaturesComputation::logSimulationInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = QString::fromLatin1("<b>[") + dt.toString(Qt::LocalDate) + QString::fromLatin1("&emsp;") +
            QString::fromLatin1(": ''") + name + QString::fromLatin1("'']</b><hr>");


    SeaLab::SeaLabUtils::TableColorProfile profile =
        SeaLab::SeaLabUtils::TableColorProfile::Success;
    
    if (status != true)
        profile = SeaLab::SeaLabUtils::TableColorProfile::Failure;

    QString table;
    table = SeaLab::SeaLabUtils::makeHtmlTable(33, 2, false, profile);

    table = table.arg(tr("Computation Time"), QString::number(GetSeaLabSimulationWorker()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"));
    table = table.arg(tr("Simulation Method"), QString::fromLatin1(m_sim->getSimulationData()->simulationMethod.getValue()));
    table = table.arg(tr("Coherence Function"), QString::fromLatin1(m_sim->getSimulationData()->coherenceFunction.getValue()));
    table = table.arg(tr("Location Distribution"), QString::fromLatin1(m_sim->getSimulationData()->spatialDistribution.getValue()));
    table = table.arg(tr("Mean Acceleration"), QString::fromLatin1(m_sim->getSimulationData()->meanFunction.getValue()));
    table = table.arg(tr("Frequency Spectrum"), QString::fromLatin1(m_sim->getSimulationData()->frequencySpectrum.getValue()));
    table = table.arg(tr("Directional Spectrum"), QString::fromLatin1(m_sim->getSimulationData()->directionalSpectrum.getValue()));
    table = table.arg(tr("Directional Spreading Function"), QString::fromLatin1(m_sim->getSimulationData()->directionalSpreadingFunction.getValue()));  
    table = table.arg(tr("PSD Decomposition Method"), QString::fromLatin1(m_sim->getSimulationData()->cpsdDecompositionMethod.getValue()));
    table = table.arg(tr("Frequency Distribution"), QString::fromLatin1(m_sim->getSimulationData()->frequencyDistribution.getValue()));
    table = table.arg(tr("Randomness Provider"), QString::fromLatin1(m_sim->getSimulationData()->randomnessProvider.getValue()));
    table = table.arg(tr("Modulation Method"), QString::fromLatin1(m_sim->getSimulationData()->modulationFunction.getValue()));
    table = table.arg(tr("Number of Locations"), QString::number((m_sim->getSimulationData()->numberOfSpatialPosition).getValue()));
    table = table.arg(tr("Number of Frequency Increments"), QString::number((m_sim->getSimulationData()->numberOfFrequency).getValue()));
    table = table.arg(tr("Frequency Increment"), QString::number((m_sim->getSimulationData()->frequencyIncrement).getValue()));
    table = table.arg(tr("Upper Cutoff Frequency"), QString::number((m_sim->getSimulationData()->maxFrequency).getValue()));
    table = table.arg(tr("Minimum Frequency"), QString::number((m_sim->getSimulationData()->minFrequency).getValue()));
    table = table.arg(tr("Number of Time Increments"), QString::number((m_sim->getSimulationData()->numberOfTimeIncrements).getValue()));
    table = table.arg(tr("Time Increment"), QString::number((m_sim->getSimulationData()->timeIncrement).getValue()));
    table = table.arg(tr("Minimum Time"), QString::number((m_sim->getSimulationData()->minTime).getValue()));

    table = table.arg(tr("Cumulative Probability Distribution"), QString::fromLatin1(m_sim->getSimulationData()->cumulativeProbabilityDistribution.getValue()));
    table = table.arg(tr("Kurtosis"), QString::fromLatin1(m_sim->getSimulationData()->kurtosis.getValue()));
    table = table.arg(tr("Peak Factor"), QString::fromLatin1(m_sim->getSimulationData()->peakFactor.getValue()));
    table = table.arg(tr("Probability Density Function"), QString::fromLatin1(m_sim->getSimulationData()->probabilityDensityFunction.getValue()));
    table = table.arg(tr("Shear Velocity Of Flow"), QString::fromLatin1(m_sim->getSimulationData()->shearVelocityOfFlow.getValue()));
    table = table.arg(tr("Skewness"), QString::fromLatin1(m_sim->getSimulationData()->skewness.getValue()));
    table = table.arg(tr("Standard Deviation"), QString::fromLatin1(m_sim->getSimulationData()->standardDeviation.getValue()));
    table = table.arg(tr("Variance"), QString::fromLatin1(m_sim->getSimulationData()->variance.getValue()));
    table = table.arg(tr("Wave Passage Effect"), QString::fromLatin1(m_sim->getSimulationData()->wavePassageEffect.getValue()));

   
    if (true == m_sim->getSimulationData()->stationarity.getValue())
    {
        table = table.arg(tr("Stationarity"), QString::fromLatin1("Stationary"));
    }
    else
    {
        table = table.arg(tr("Stationarity"), QString::fromLatin1("Non-Stationary"));
    }

    if (true == m_sim->getSimulationData()->uniformModulation.getValue())
    {
        table = table.arg(tr("Modulation"), QString::fromLatin1("Uniform"));
    }
    else
    {
        table = table.arg(tr("Modulation"), QString::fromLatin1("General"));
    }

    if (true == m_sim->getSimulationData()->gaussianity.getValue())
    {
        table = table.arg(tr("Gaussianity"), QString::fromLatin1("Gaussian"));
    }
    else
    {
        table = table.arg(tr("Gaussianity"), QString::fromLatin1("Non-Gaussian"));
    }

    if(true == status)
    {
        table = table.arg(tr("Status"), QString::fromLatin1("Success"));
    }
    else
    {
        table = table.arg(tr("Status"), QString::fromLatin1("Failure"));
    }

    info += table + QString::fromLatin1("<br>");

    return info;
}



void SeaLabAllFeaturesComputation::startSimulationWorker(QString function, const char* complexNumberDisplay)
{
    // create the worker
    simulationWorker = new RPSSeaLabSimulationWorker(m_sim);

    setComplexNumberDisplay(complexNumberDisplay);

    // create a new thread and attach the worker to it
    simulationThread = new QThread(this);
    simulationWorker->moveToThread(simulationThread);


    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), simulationWorker, SLOT(stop()), Qt::DirectConnection);
    // connect(simulationWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
    // connect(simulationWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
    // connect(simulationWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

    // add the functionaly to delete the worker after work is done
    connect(simulationWorker, SIGNAL(finished()), simulationWorker, SLOT(deleteLater()));
    connect(simulationWorker, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));

    
    if (function == SeaLab::SeaLabUtils::ComputeLocationCoordinateMatrixP3)
    {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeLocationCoordinateMatrixP3()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossCoherenceValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossCoherenceVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossCoherenceVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossCoherenceMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceMatrixPP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossCorrelationValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCorrelationValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossCorrelationVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCorrelationVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossCorrelationMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCorrelationMatrixPP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCPDValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCPDValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCPDVectorX) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCPDVectorX()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeFrequencyValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeFrequencyValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeFrequenciesVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeFrequenciesVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeFrequenciesMatrixFP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeFrequenciesMatrixFP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeKurtosisValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeKurtosisValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeKurtosisVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeKurtosisVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeKurtosisVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeKurtosisVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::MatrixToolCompute) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerMatrixToolCompute()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeMeanAccelerationValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeMeanAccelerationValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeMeanAccelerationVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeMeanAccelerationVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeMeanAccelerationVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeMeanAccelerationVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeModulationValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeModulationValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeModulationVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeModulationVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeModulationVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeModulationVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputePeakFactorValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePeakFactorValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputePeakFactorVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePeakFactorVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputePeakFactorVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePeakFactorVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputePDFValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePDFValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputePDFVectorX) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePDFVectorX()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDecomposedPSDValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedPSDValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDecomposedCrossSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedCrossSpectrumVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDecomposedCrossSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedCrossSpectrumVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDecomposedCrossSpectrumMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedCrossSpectrumMatrixPP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeRandomValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeRandomValue()));
    }
    else if(function == SeaLab::SeaLabUtils::GenerateRandomMatrixFP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerGenerateRandomMatrixFP()));
    }
    else if(function == SeaLab::SeaLabUtils::GenerateRandomCubeFPS) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerGenerateRandomCubeFPS()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeShearVelocityOfFlowValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeShearVelocityOfFlowValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeShearVelocityOfFlowVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeShearVelocityOfFlowVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeShearVelocityOfFlowVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeShearVelocityOfFlowVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::Simulate)
    {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerSimulate()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeSkewnessValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeSkewnessValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeSkewnessVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeSkewnessVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeSkewnessVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeSkewnessVectorT()));
    }

    else if(function == SeaLab::SeaLabUtils::ComputeStandardDeviationValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeStandardDeviationValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeStandardDeviationVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeStandardDeviationVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeStandardDeviationVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeStandardDeviationVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::TableToolCompute) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerTableToolCompute()));
    }
    else if(function == SeaLab::SeaLabUtils::UserDefinedRPSObjectCompute) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerUserDefinedRPSObjectCompute()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeVarianceValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeVarianceValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeVarianceVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeVarianceVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeVarianceVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeVarianceVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeWavePassageEffectValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeWavePassageEffectVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeWavePassageEffectVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeWavePassageEffectMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectMatrixPP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeAutoFrequencySpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeAutoFrequencySpectrumValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeAutoFrequencySpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeAutoFrequencySpectrumVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeAutoFrequencySpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeAutoFrequencySpectrumVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossFrequencySpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossFrequencySpectrumVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossFrequencySpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossFrequencySpectrumVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossFrequencySpectrumMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossFrequencySpectrumMatrixPP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossDirectionalSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossDirectionalSpectrumValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossFrequencySpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossFrequencySpectrumValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossDirectionalSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossDirectionalSpectrumVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossDirectionalSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossDirectionalSpectrumVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossDirectionalSpectrumVectorD) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossDirectionalSpectrumVectorD()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeCrossDirectionalSpectrumMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossDirectionalSpectrumMatrixPP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeAutoDirectionalSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeAutoDirectionalSpectrumValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeAutoDirectionalSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeAutoDirectionalSpectrumVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeAutoDirectionalSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeAutoDirectionalSpectrumVectorT()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeAutoDirectionalSpectrumVectorD) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeAutoDirectionalSpectrumVectorD()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDirectionalSpreadingFunctionValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDirectionalSpreadingFunctionValue()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDirectionalSpreadingFunctionVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDirectionalSpreadingFunctionVectorF()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDirectionalSpreadingFunctionVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDirectionalSpreadingFunctionVectorP()));
    }
    else if(function == SeaLab::SeaLabUtils::ComputeDirectionalSpreadingFunctionVectorD) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDirectionalSpreadingFunctionVectorD()));
    }

    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setRange(0, 0);
    bar->show();
}

void SeaLabAllFeaturesComputation::slotDisplayResultInTable(QString str, int what)
{
    if (what == 0) 
    {
        m_sim->setStatus(App::SimulationStatus::Failed, true);
        m_sim->setStatus(App::SimulationStatus::Successfull, false);
    }
    else if (what == 1)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowMatrix(simulationWorker->m_ResultMatrix, str);
    }
    else if (what == 2)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowVectors(simulationWorker->m_ResultVectorVar, simulationWorker->m_ResultVectorVal, str);
    }
    else if (what == 3)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowVector(simulationWorker->m_ResultVectorVal, str);
    }
    else if (what == 4)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowComplexVectors(simulationWorker->m_ResultVectorVar, simulationWorker->m_ResultVectorVal_cx, str, complexRrealImag);
    }
    else if (what == 5)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowComplexMatrix(simulationWorker->m_ResultMatrix_cx, str, complexRrealImag);
    }


    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setValue(100);
    bar->hide();
    Gui::MainWindow* win = Gui::getMainWindow();
    if (win) {
        win->showMessage(QString());
    }
    QString info = logSimulationInfo(m_sim->isSuccessfull(), str);

    Gui::getMainWindow()->showResults(info);

    Q_EMIT simulationWorker->finished();

    Gui::getMainWindow()->updateActions();
}

void SeaLabAllFeaturesComputation::slotDisplayResultInMatrix(QString str, int what)
{
    if (what == 0) 
    {
        m_sim->setStatus(App::SimulationStatus::Failed, true);
        m_sim->setStatus(App::SimulationStatus::Successfull, false);
    }
    else if (what == 1)
    {
         Gui::getMainWindow()->getAlphaPlot()->newMatrixShowMatrix(simulationWorker->m_ResultMatrix, str);
    }
    else if (what == 2)
    {
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowVector(simulationWorker->m_ResultVectorVal, str);
    }
    else if (what == 3)
    {
       Gui::getMainWindow()->getAlphaPlot()->newMatrixShowVector(simulationWorker->m_ResultVectorVal, str);
    }
    else if (what == 4)
    {
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowComplexVectors(simulationWorker->m_ResultVectorVar, simulationWorker->m_ResultVectorVal_cx, str, complexRrealImag);
    }
    else if (what == 5)
    {
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowComplexMatrix(simulationWorker->m_ResultMatrix_cx, str, complexRrealImag);
    }

    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setValue(100);
    bar->hide();
    Gui::MainWindow* win = Gui::getMainWindow();
    if (win) {
        win->showMessage(QString());
    }
    QString info = logSimulationInfo(m_sim->isSuccessfull(), str);

    Gui::getMainWindow()->showResults(info);

    Q_EMIT simulationWorker->finished();

    Gui::getMainWindow()->updateActions();
}

void SeaLabAllFeaturesComputation::setComplexNumberDisplay(const char* displayType)
{
    if (strcmp(displayType, "Real") == 0)
	{
       complexRrealImag = 0;
    }
    else if (strcmp(displayType, "Imaginary") == 0)
	{
       complexRrealImag = 1;
    }

    Q_EMIT simulationWorker->finished();

    Gui::getMainWindow()->updateActions();
}