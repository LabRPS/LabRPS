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

#include "SeismicLabComparisonStarter.h"
#include <Mod/SeismicLab/App/SeismicLabUtils.h>
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

using namespace SeismicLabGui;

SeismicLabComparisonStarter::SeismicLabComparisonStarter(SeismicLab::SeismicLabSimulation* sim1,SeismicLab::SeismicLabSimulation* sim2, std::string comparisonName, QObject* parent)
    : m_sim1(sim1), m_sim2(sim2), m_comparisonName(comparisonName), QObject(parent)
{ 
}

SeismicLabComparisonStarter::~SeismicLabComparisonStarter()
{
    
}

RPSSeismicLabSimulationWorker *SeismicLabComparisonStarter::GetSeismicLabSimulationWorker1()
{
    return simulationWorker1;
}

RPSSeismicLabSimulationWorker* SeismicLabComparisonStarter::GetSeismicLabSimulationWorker2()
{
    return simulationWorker2;
}

QThread* SeismicLabComparisonStarter::getSeismicLabSimulationThread1()
{ 
    return simulationThread1; 
}

QThread* SeismicLabComparisonStarter::getSeismicLabSimulationThread2() 
{ 
    return simulationThread2; 
}

std::string SeismicLabComparisonStarter::getComparisonName()
{ return m_comparisonName; }

QString SeismicLabComparisonStarter::logSimulationInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = QString::fromLatin1("<b>[") + dt.toString(Qt::LocalDate) + QString::fromLatin1("&emsp;") +
            QString::fromLatin1(": ''") + name + QString::fromLatin1("'']</b><hr>");


    SeismicLab::SeismicLabUtils::TableColorProfile profile =
        SeismicLab::SeismicLabUtils::TableColorProfile::Success;
    
    if (status != true)
        profile = SeismicLab::SeismicLabUtils::TableColorProfile::Failure;

    QString table;
    table = SeismicLab::SeismicLabUtils::makeHtmlTable(37, 3, false, profile);

    table = table.arg(tr("Computation Time"), QString::number(GetSeismicLabSimulationWorker1()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"), QString::number(GetSeismicLabSimulationWorker2()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"));
    table = table.arg(tr("Simulation Method"), QString::fromLatin1(m_sim1->getSimulationData()->simulationMethod.getValue()),QString::fromLatin1(m_sim2->getSimulationData()->simulationMethod.getValue()));
    table = table.arg(tr("Coherence Function"), QString::fromLatin1(m_sim1->getSimulationData()->coherenceFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->coherenceFunction.getValue()));
    table = table.arg(tr("Location Distribution"), QString::fromLatin1(m_sim1->getSimulationData()->spatialDistribution.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->spatialDistribution.getValue()));
    table = table.arg(tr("Mean Acceleration"), QString::fromLatin1(m_sim1->getSimulationData()->meanFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->meanFunction.getValue()));
    table = table.arg(tr("Spectrum"), QString::fromLatin1(m_sim1->getSimulationData()->spectrumModel.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->spectrumModel.getValue()));
    table = table.arg(tr("PSD Decomposition Method"), QString::fromLatin1(m_sim1->getSimulationData()->cpsdDecompositionMethod.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->cpsdDecompositionMethod.getValue()));
    table = table.arg(tr("Frequency Distribution"), QString::fromLatin1(m_sim1->getSimulationData()->frequencyDistribution.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->frequencyDistribution.getValue()));
    table = table.arg(tr("Randomness Provider"), QString::fromLatin1(m_sim1->getSimulationData()->randomnessProvider.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->randomnessProvider.getValue()));
    table = table.arg(tr("Modulation Method"), QString::fromLatin1(m_sim1->getSimulationData()->modulationFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->modulationFunction.getValue()));
    table = table.arg(tr("Number of Locations"), m_sim1->getSimulationData()->numberOfSpatialPosition.getValue(), m_sim2->getSimulationData()->numberOfSpatialPosition.getValue());
    table = table.arg(tr("Number of Frequency Increments"), m_sim1->getSimulationData()->numberOfFrequency.getValue(), m_sim2->getSimulationData()->numberOfFrequency.getValue());
    table = table.arg(tr("Frequency Increment"), QString::number(m_sim1->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)), QString::number(m_sim2->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)));
    table = table.arg(tr("Upper Cutoff Frequency"), QString::number(m_sim1->getSimulationData()->maxFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)), QString::number(m_sim2->getSimulationData()->maxFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)));
    table = table.arg(tr("Minimum Frequency"), QString::number(m_sim1->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)), QString::number(m_sim2->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)));
    table = table.arg(tr("Number of Time Increments"), QString::number(m_sim1->getSimulationData()->numberOfTimeIncrements.getValue()), QString::number(m_sim2->getSimulationData()->numberOfTimeIncrements.getValue()));
    table = table.arg(tr("Time Increment"), QString::number(m_sim1->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second)), QString::number(m_sim2->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second)));
    table = table.arg(tr("Minimum Time"), QString::number(m_sim1->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)), QString::number(m_sim2->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)));

    table = table.arg(tr("Cumulative Probability Distribution"), QString::fromLatin1(m_sim1->getSimulationData()->cumulativeProbabilityDistribution.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->cumulativeProbabilityDistribution.getValue()));
    table = table.arg(tr("Kurtosis"), QString::fromLatin1(m_sim1->getSimulationData()->kurtosis.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->kurtosis.getValue()));
    table = table.arg(tr("Peak Factor"), QString::fromLatin1(m_sim1->getSimulationData()->peakFactor.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->peakFactor.getValue()));
    table = table.arg(tr("Probability Density Function"), QString::fromLatin1(m_sim1->getSimulationData()->probabilityDensityFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->probabilityDensityFunction.getValue()));
    table = table.arg(tr("Shear Velocity Of Flow"), QString::fromLatin1(m_sim1->getSimulationData()->shearVelocityOfFlow.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->shearVelocityOfFlow.getValue()));
    table = table.arg(tr("Skewness"), QString::fromLatin1(m_sim1->getSimulationData()->skewness.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->skewness.getValue()));
    table = table.arg(tr("Standard Deviation"), QString::fromLatin1(m_sim1->getSimulationData()->standardDeviation.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->standardDeviation.getValue()));
    table = table.arg(tr("Variance"), QString::fromLatin1(m_sim1->getSimulationData()->variance.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->variance.getValue()));
    table = table.arg(tr("Wave Passage Effect"), QString::fromLatin1(m_sim1->getSimulationData()->wavePassageEffect.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->wavePassageEffect.getValue()));


    if (true == m_sim1->getSimulationData()->stationarity.getValue())
    {
        table = table.arg(tr("Stationarity"), QString::fromLatin1("Stationary"));
    }
    else
    {
        table = table.arg(tr("Stationarity"), QString::fromLatin1("Non-Stationary"));
    }

    if (true == m_sim1->getSimulationData()->uniformModulation.getValue())
    {
        table = table.arg(tr("Modulation"), QString::fromLatin1("Uniform"));
    }
    else
    {
        table = table.arg(tr("Modulation"), QString::fromLatin1("General"));
    }

    if (true == m_sim1->getSimulationData()->gaussianity.getValue())
    {
        table = table.arg(tr("Gaussianity"), QString::fromLatin1("Gaussian"));
    }
    else
    {
        table = table.arg(tr("Gaussianity"), QString::fromLatin1("Non-Gaussian"));
    }

    if (true == m_sim1->getSimulationData()->largeScaleSimulationMode.getValue())
    {
        table = table.arg(tr("Large Scale Simulation Mode"), QString::fromLatin1("Yes"));
    }
    else
    {
        table = table.arg(tr("Large Scale Simulation Mode"), QString::fromLatin1("No"));
    }


    if (true == m_sim2->getSimulationData()->stationarity.getValue())
    {
        table = table.arg(tr("Stationarity"), QString::fromLatin1("Stationary"));
    }
    else
    {
        table = table.arg(tr("Stationarity"), QString::fromLatin1("Non-Stationary"));
    }

    if (true == m_sim2->getSimulationData()->uniformModulation.getValue())
    {
        table = table.arg(tr("Modulation"), QString::fromLatin1("Uniform"));
    }
    else
    {
        table = table.arg(tr("Modulation"), QString::fromLatin1("General"));
    }

    if (true == m_sim2->getSimulationData()->gaussianity.getValue())
    {
        table = table.arg(tr("Gaussianity"), QString::fromLatin1("Gaussian"));
    }
    else
    {
        table = table.arg(tr("Gaussianity"), QString::fromLatin1("Non-Gaussian"));
    }

    if (true == m_sim2->getSimulationData()->largeScaleSimulationMode.getValue())
    {
        table = table.arg(tr("Large Scale Simulation Mode"), QString::fromLatin1("Yes"));
    }
    else
    {
        table = table.arg(tr("Large Scale Simulation Mode"), QString::fromLatin1("No"));
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



void SeismicLabComparisonStarter::startSimulationWorker(QString function, const char* complexNumberDisplay)
{
    // create a worker
    simulationWorker1 = new RPSSeismicLabSimulationWorker(m_sim1);
    simulationWorker2 = new RPSSeismicLabSimulationWorker(m_sim2);

    simulationWorker1->setComparisonName(m_comparisonName);
    simulationWorker2->setComparisonName(m_comparisonName); 

    setComplexNumberDisplay(complexNumberDisplay);

    // create a new thread and attach the worker to it
    simulationThread1 = new QThread(this);
    simulationThread2 = new QThread(this);

    simulationWorker1->moveToThread(simulationThread1);
    simulationWorker2->moveToThread(simulationThread2);


    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), simulationWorker1, SLOT(RPSSeismicLabSimulationWorker::stop()), Qt::DirectConnection);
    connect(this, SIGNAL(stopped()), simulationWorker2, SLOT(RPSSeismicLabSimulationWorker::stop()), Qt::DirectConnection);


    // add the functionaly to delete the worker after work is done
    connect(simulationWorker1, SIGNAL(finished()), simulationWorker1, SLOT(deleteLater()));
    connect(simulationWorker1, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker1, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));

    connect(simulationWorker2, SIGNAL(finished()), simulationWorker2, SLOT(deleteLater()));
    connect(simulationWorker2, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker2, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));
    
    //QString function = simulationWorker->getComputingFunction();
    
    if (function == SeismicLab::SeismicLabUtils::ComputeLocationCoordinateMatrixP3)
    {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);

        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeLocationCoordinateMatrixP3()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeLocationCoordinateMatrixP3()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceVectorF()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceVectorT()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceMatrixPP()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossCorrelationValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCorrelationValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCorrelationValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossCorrelationVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCorrelationVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCorrelationVectorT()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossCorrelationMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCorrelationMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCorrelationMatrixPP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCPDValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCPDValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCPDValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCPDVectorX) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCPDVectorX()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCPDVectorX()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeFrequencyValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeFrequencyValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeFrequencyValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeFrequenciesVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeFrequenciesVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeFrequenciesVectorF()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeFrequenciesMatrixFP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeFrequenciesMatrixFP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeFrequenciesMatrixFP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeKurtosisValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeKurtosisValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeKurtosisValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeKurtosisVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeKurtosisVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeKurtosisVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeKurtosisVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeKurtosisVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeKurtosisVectorT()));
    }

    else if(function == SeismicLab::SeismicLabUtils::MatrixToolCompute) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerMatrixToolCompute()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerMatrixToolCompute()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeMeanAccelerationValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeMeanAccelerationValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeMeanAccelerationValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeMeanAccelerationVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeMeanAccelerationVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeMeanAccelerationVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeMeanAccelerationVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeMeanAccelerationVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeMeanAccelerationVectorT()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeModulationValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeModulationValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeModulationValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeModulationVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeModulationVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeModulationVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeModulationVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeModulationVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeModulationVectorT()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputePeakFactorValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePeakFactorValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePeakFactorValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputePeakFactorVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePeakFactorVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePeakFactorVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputePeakFactorVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePeakFactorVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePeakFactorVectorT()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputePDFValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePDFValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePDFValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputePDFVectorX) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePDFVectorX()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePDFVectorX()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeDecomposedPSDValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedPSDValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedPSDValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedCrossSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedCrossSpectrumVectorF()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedCrossSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedCrossSpectrumVectorT()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedCrossSpectrumMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedCrossSpectrumMatrixPP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeRandomValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeRandomValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeRandomValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::GenerateRandomMatrixFP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerGenerateRandomMatrixFP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerGenerateRandomMatrixFP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::GenerateRandomCubeFPS) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerGenerateRandomCubeFPS()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerGenerateRandomCubeFPS()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeShearVelocityOfFlowValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeShearVelocityOfFlowValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeShearVelocityOfFlowVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeShearVelocityOfFlowVectorT()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeShearVelocityOfFlowVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeShearVelocityOfFlowVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::Simulate)
        {
            simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerSimulate()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerSimulate()));
        }
    else if(function == SeismicLab::SeismicLabUtils::SimulateInLargeScaleMode) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerSimulateInLargeScaleMode()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerSimulateInLargeScaleMode()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeSkewnessValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeSkewnessValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeSkewnessValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeSkewnessVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeSkewnessVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeSkewnessVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeSkewnessVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeSkewnessVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeSkewnessVectorT()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeStandardDeviationValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeStandardDeviationValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeStandardDeviationValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeStandardDeviationVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeStandardDeviationVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeStandardDeviationVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeStandardDeviationVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeStandardDeviationVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeStandardDeviationVectorT()));
    }

    else if(function == SeismicLab::SeismicLabUtils::TableToolCompute) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerTableToolCompute()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerTableToolCompute()));
    }

    else if(function == SeismicLab::SeismicLabUtils::UserDefinedRPSObjectCompute) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerUserDefinedRPSObjectCompute()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerUserDefinedRPSObjectCompute()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeVarianceValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeVarianceValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeVarianceValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeVarianceVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeVarianceVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeVarianceVectorP()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeVarianceVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeVarianceVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeVarianceVectorT()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectVectorF()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectVectorT()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectMatrixPP()));
    }

    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossSpectrumValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossSpectrumVectorF()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossSpectrumVectorT()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossSpectrumMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossSpectrumMatrixPP()));
    }
        else if(function == SeismicLab::SeismicLabUtils::ComputeAutoSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeAutoSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeAutoSpectrumValue()));
    }
    else if(function == SeismicLab::SeismicLabUtils::ComputeAutoSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeAutoSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeAutoSpectrumVectorF()));
    }
    else if (function == SeismicLab::SeismicLabUtils::ComputeAutoSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeAutoSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeAutoSpectrumVectorT()));
    }

    
    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setRange(0, 100);
    bar->show();
    Gui::getMainWindow()->showMessage(tr("Loading %1...").arg(QString::fromLatin1(simulationWorker2->getComparisonName().c_str())));

}

void SeismicLabComparisonStarter::slotDisplayResultInTable(QString str, int what)
{
    if (what == 1)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowMatrix(simulationWorker1->m_ResultMatrix, str);
        Gui::getMainWindow()->getAlphaPlot()->newTableShowMatrix(simulationWorker2->m_ResultMatrix, str);

    }
    else if (what == 2)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowVectors(simulationWorker1->m_ResultVectorVar, simulationWorker1->m_ResultVectorVal, str);
        Gui::getMainWindow()->getAlphaPlot()->newTableShowVectors(simulationWorker2->m_ResultVectorVar, simulationWorker2->m_ResultVectorVal, str);

    }
    else if (what == 3)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowVector(simulationWorker1->m_ResultVectorVal, str);
        Gui::getMainWindow()->getAlphaPlot()->newTableShowVector(simulationWorker2->m_ResultVectorVal, str);

    }
    else if (what == 4)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowComplexVectors(simulationWorker1->m_ResultVectorVar, simulationWorker1->m_ResultVectorVal_cx, str, complexRrealImag);
        Gui::getMainWindow()->getAlphaPlot()->newTableShowComplexVectors(simulationWorker2->m_ResultVectorVar, simulationWorker2->m_ResultVectorVal_cx, str, complexRrealImag);

    }
    else if (what == 5)
    {
        Gui::getMainWindow()->getAlphaPlot()->newTableShowComplexMatrix(simulationWorker1->m_ResultMatrix_cx, str, complexRrealImag);
        Gui::getMainWindow()->getAlphaPlot()->newTableShowComplexMatrix(simulationWorker2->m_ResultMatrix_cx, str, complexRrealImag);

    }

    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setValue(100);
    bar->hide();
    Gui::MainWindow* win = Gui::getMainWindow();
    if (win) {
        win->showMessage(QString());
    }
    
     QString info = logSimulationInfo(true, QString::fromLatin1("hahaha"));

    Gui::getMainWindow()->showResults(info);
}

void SeismicLabComparisonStarter::slotDisplayResultInMatrix(QString str, int what)
{
    if (what == 1)
    {
         Gui::getMainWindow()->getAlphaPlot()->newMatrixShowMatrix(simulationWorker1->m_ResultMatrix, str);
         Gui::getMainWindow()->getAlphaPlot()->newMatrixShowMatrix(simulationWorker2->m_ResultMatrix, str);

    }
    else if (what == 2)
    {
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowVector(simulationWorker1->m_ResultVectorVal, str);
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowVector(simulationWorker2->m_ResultVectorVal, str);

    }
    else if (what == 3)
    {
       Gui::getMainWindow()->getAlphaPlot()->newMatrixShowVector(simulationWorker1->m_ResultVectorVal, str);
       Gui::getMainWindow()->getAlphaPlot()->newMatrixShowVector(simulationWorker2->m_ResultVectorVal, str);

    }
    else if (what == 4)
    {
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowComplexVectors(simulationWorker1->m_ResultVectorVar, simulationWorker1->m_ResultVectorVal_cx, str, complexRrealImag);
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowComplexVectors(simulationWorker2->m_ResultVectorVar, simulationWorker2->m_ResultVectorVal_cx, str, complexRrealImag);

    }
    else if (what == 5)
    {
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowComplexMatrix(simulationWorker1->m_ResultMatrix_cx, str, complexRrealImag);
        Gui::getMainWindow()->getAlphaPlot()->newMatrixShowComplexMatrix(simulationWorker2->m_ResultMatrix_cx, str, complexRrealImag);

    }

    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setValue(100);
    bar->hide();
    Gui::MainWindow* win = Gui::getMainWindow();
    if (win) {
        win->showMessage(QString());
    }

    QString info = logSimulationInfo(true, QString::fromLatin1("hahaha"));

    Gui::getMainWindow()->showResults(info);
}

void SeismicLabComparisonStarter::slotDisplayResultInTable1(QString str, int what)
{
    slotDisplayResultInTable(str, what);
}
void SeismicLabComparisonStarter::slotDisplayResultInMatrix1(QString str, int what)
{
    slotDisplayResultInMatrix(str, what);
}
void SeismicLabComparisonStarter::slotDisplayResultInTable2(QString str, int what)
{
    slotDisplayResultInTable(str, what);
}
void SeismicLabComparisonStarter::slotDisplayResultInMatrix2(QString str, int what)
{
    slotDisplayResultInMatrix(str, what);
}

void SeismicLabComparisonStarter::setComplexNumberDisplay(const char* displayType)
{
    if (strcmp(displayType, "Real") == 0)
	{
       complexRrealImag = 0;
    }
    else if (strcmp(displayType, "Imaginary") == 0)
	{
       complexRrealImag = 1;
    }
}