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

#include "WindLabComparisonStarter.h"
#include <Mod/WindLab/App/WindLabUtils.h>
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

using namespace WindLabGui;

WindLabComparisonStarter::WindLabComparisonStarter(WindLab::WindLabSimulation* sim1,WindLab::WindLabSimulation* sim2, std::string comparisonName, QObject* parent)
    : m_sim1(sim1), m_sim2(sim2), m_comparisonName(comparisonName), QObject(parent)
{ 
}

WindLabComparisonStarter::~WindLabComparisonStarter()
{
    
}

RPSWindLabSimulationWorker *WindLabComparisonStarter::GetWindLabSimulationWorker1()
{
    return simulationWorker1;
}

RPSWindLabSimulationWorker* WindLabComparisonStarter::GetWindLabSimulationWorker2()
{
    return simulationWorker2;
}

QThread* WindLabComparisonStarter::getWindLabSimulationThread1()
{ 
    return simulationThread1; 
}

QThread* WindLabComparisonStarter::getWindLabSimulationThread2() 
{ 
    return simulationThread2; 
}

std::string WindLabComparisonStarter::getComparisonName()
{ return m_comparisonName; }

QString WindLabComparisonStarter::logSimulationInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = QString::fromLatin1("<b>[") + dt.toString(Qt::LocalDate) + QString::fromLatin1("&emsp;") +
            QString::fromLatin1(": ''") + name + QString::fromLatin1("'']</b><hr>");


    WindLab::WindLabUtils::TableColorProfile profile =
        WindLab::WindLabUtils::TableColorProfile::Success;
    
    if (status != true)
        profile = WindLab::WindLabUtils::TableColorProfile::Failure;

    QString table;
    table = WindLab::WindLabUtils::makeHtmlTable(37, 3, false, profile);

    table = table.arg(tr("Computation Time"), QString::number(GetWindLabSimulationWorker1()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"), QString::number(GetWindLabSimulationWorker2()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"));
    table = table.arg(tr("Simulation Method"), QString::fromLatin1(m_sim1->getSimulationData()->simulationMethod.getValue()),QString::fromLatin1(m_sim2->getSimulationData()->simulationMethod.getValue()));
    table = table.arg(tr("Coherence Function"), QString::fromLatin1(m_sim1->getSimulationData()->coherenceFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->coherenceFunction.getValue()));
    table = table.arg(tr("Location Distribution"), QString::fromLatin1(m_sim1->getSimulationData()->spatialDistribution.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->spatialDistribution.getValue()));
    table = table.arg(tr("Mean Wind Profile"), QString::fromLatin1(m_sim1->getSimulationData()->meanFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->meanFunction.getValue()));
    table = table.arg(tr("Along Wind Spectrum"), QString::fromLatin1(m_sim1->getSimulationData()->alongWindSpectrumModel.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->alongWindSpectrumModel.getValue()));
    table = table.arg(tr("PSD Decomposition Method"), QString::fromLatin1(m_sim1->getSimulationData()->cpsdDecompositionMethod.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->cpsdDecompositionMethod.getValue()));
    table = table.arg(tr("Frequency Distribution"), QString::fromLatin1(m_sim1->getSimulationData()->frequencyDistribution.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->frequencyDistribution.getValue()));
    table = table.arg(tr("Randomness Provider"), QString::fromLatin1(m_sim1->getSimulationData()->randomnessProvider.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->randomnessProvider.getValue()));
    table = table.arg(tr("Modulation Method"), QString::fromLatin1(m_sim1->getSimulationData()->modulationFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->modulationFunction.getValue()));
    table = table.arg(tr("Number of Locations"), m_sim1->getSimulationData()->numberOfSpatialPosition.getValue(), m_sim2->getSimulationData()->numberOfSpatialPosition.getValue());
    table = table.arg(tr("Number of Frequency Increments"), m_sim1->getSimulationData()->numberOfFrequency.getValue(), m_sim2->getSimulationData()->numberOfFrequency.getValue());
    table = table.arg(tr("Frequency Increment"), QString::number(m_sim1->getSimulationData()->frequencyIncrement.getValue()), QString::number(m_sim2->getSimulationData()->frequencyIncrement.getValue()));
    table = table.arg(tr("Upper Cutoff Frequency"), QString::number(m_sim1->getSimulationData()->maxFrequency.getValue()), QString::number(m_sim2->getSimulationData()->maxFrequency.getValue()));
    table = table.arg(tr("Minimum Frequency"), QString::number(m_sim1->getSimulationData()->minFrequency.getValue()), QString::number(m_sim2->getSimulationData()->minFrequency.getValue()));
    table = table.arg(tr("Number of Time Increments"), QString::number(m_sim1->getSimulationData()->numberOfTimeIncrements.getValue()), QString::number(m_sim2->getSimulationData()->numberOfTimeIncrements.getValue()));
    table = table.arg(tr("Time Increment"), QString::number(m_sim1->getSimulationData()->timeIncrement.getValue()), QString::number(m_sim2->getSimulationData()->timeIncrement.getValue()));
    table = table.arg(tr("Minimum Time"), QString::number(m_sim1->getSimulationData()->minTime.getValue()), QString::number(m_sim2->getSimulationData()->minTime.getValue()));

    table = table.arg(tr("Cumulative Probability Distribution"), QString::fromLatin1(m_sim1->getSimulationData()->cumulativeProbabilityDistribution.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->cumulativeProbabilityDistribution.getValue()));
    table = table.arg(tr("Gust Factor"), QString::fromLatin1(m_sim1->getSimulationData()->gustFactor.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->gustFactor.getValue()));
    table = table.arg(tr("Kurtosis"), QString::fromLatin1(m_sim1->getSimulationData()->kurtosis.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->kurtosis.getValue()));
    table = table.arg(tr("Peak Factor"), QString::fromLatin1(m_sim1->getSimulationData()->peakFactor.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->peakFactor.getValue()));
    table = table.arg(tr("Probability Density Function"), QString::fromLatin1(m_sim1->getSimulationData()->probabilityDensityFunction.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->probabilityDensityFunction.getValue()));
    table = table.arg(tr("Roughness"), QString::fromLatin1(m_sim1->getSimulationData()->roughness.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->roughness.getValue()));
    table = table.arg(tr("Shear Velocity Of Flow"), QString::fromLatin1(m_sim1->getSimulationData()->shearVelocityOfFlow.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->shearVelocityOfFlow.getValue()));
    table = table.arg(tr("Skewness"), QString::fromLatin1(m_sim1->getSimulationData()->skewness.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->skewness.getValue()));
    table = table.arg(tr("Standard Deviation"), QString::fromLatin1(m_sim1->getSimulationData()->standardDeviation.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->standardDeviation.getValue()));
    table = table.arg(tr("Turbulence Intensity"), QString::fromLatin1(m_sim1->getSimulationData()->turbulenceIntensity.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->turbulenceIntensity.getValue()));
    table = table.arg(tr("Turbulence Scale"), QString::fromLatin1(m_sim1->getSimulationData()->turbulenceScale.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->turbulenceScale.getValue()));
    table = table.arg(tr("Variance"), QString::fromLatin1(m_sim1->getSimulationData()->variance.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->variance.getValue()));
    table = table.arg(tr("Wave Passage Effect"), QString::fromLatin1(m_sim1->getSimulationData()->wavePassageEffect.getValue()), QString::fromLatin1(m_sim2->getSimulationData()->wavePassageEffect.getValue()));

    if ("Along wind" == m_sim1->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Along Wind"));
    }
    else if ("Across wind" == m_sim1->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Across Wind"));
    }
    else if ("Vertical wind" == m_sim1->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Vertical Wind"));
    }

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

    ///////////////////////
    if ("Along wind" == m_sim2->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Along Wind"));
    }
    else if ("Across wind" == m_sim2->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Across Wind"));
    }
    else if ("Vertical wind" == m_sim2->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Vertical Wind"));
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



void WindLabComparisonStarter::startSimulationWorker(QString function, const char* complexNumberDisplay)
{
    // create a worker
    simulationWorker1 = new RPSWindLabSimulationWorker(m_sim1);
    simulationWorker2 = new RPSWindLabSimulationWorker(m_sim2);

    simulationWorker1->setComparisonName(m_comparisonName);
    simulationWorker2->setComparisonName(m_comparisonName); 

    setComplexNumberDisplay(complexNumberDisplay);

    // create a new thread and attach the worker to it
    simulationThread1 = new QThread(this);
    simulationThread2 = new QThread(this);

    simulationWorker1->moveToThread(simulationThread1);
    simulationWorker2->moveToThread(simulationThread2);


    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), simulationWorker1, SLOT(RPSWindLabSimulationWorker::stop()), Qt::DirectConnection);
    connect(this, SIGNAL(stopped()), simulationWorker2, SLOT(RPSWindLabSimulationWorker::stop()), Qt::DirectConnection);


    // add the functionaly to delete the worker after work is done
    connect(simulationWorker1, SIGNAL(finished()), simulationWorker1, SLOT(deleteLater()));
    connect(simulationWorker1, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker1, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));

    connect(simulationWorker2, SIGNAL(finished()), simulationWorker2, SLOT(deleteLater()));
    connect(simulationWorker2, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker2, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));
    
    //QString function = simulationWorker->getComputingFunction();
    
    if (function == WindLab::WindLabUtils::ComputeLocationCoordinateMatrixP3)
    {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);

        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeLocationCoordinateMatrixP3()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeLocationCoordinateMatrixP3()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCoherenceMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCoherenceMatrixPP()));
    }

    else if(function == WindLab::WindLabUtils::ComputeCrossCorrelationValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCorrelationValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCorrelationValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCorrelationVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCorrelationVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCorrelationVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCorrelationMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCrossCorrelationMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCrossCorrelationMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCPDValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCPDValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCPDValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCPDVectorX) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeCPDVectorX()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeCPDVectorX()));
    }

    else if(function == WindLab::WindLabUtils::ComputeFrequencyValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeFrequencyValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeFrequencyValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeFrequenciesVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeFrequenciesVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeFrequenciesVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeFrequenciesMatrixFP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeFrequenciesMatrixFP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeFrequenciesMatrixFP()));
    }

    else if(function == WindLab::WindLabUtils::ComputeGustFactorValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeGustFactorValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeGustFactorValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeGustFactorVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeGustFactorVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeGustFactorVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeGustFactorVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeGustFactorVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeGustFactorVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeKurtosisValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeKurtosisValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeKurtosisValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeKurtosisVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeKurtosisVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeKurtosisVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeKurtosisVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeKurtosisVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeKurtosisVectorT()));
    }

    else if(function == WindLab::WindLabUtils::MatrixToolCompute) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerMatrixToolCompute()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerMatrixToolCompute()));
    }

    else if(function == WindLab::WindLabUtils::ComputeMeanWindSpeedValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeMeanWindSpeedValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeMeanWindSpeedValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeMeanWindSpeedVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeMeanWindSpeedVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeMeanWindSpeedVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeMeanWindSpeedVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeMeanWindSpeedVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeMeanWindSpeedVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeModulationValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeModulationValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeModulationValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeModulationVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeModulationVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeModulationVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeModulationVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeModulationVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeModulationVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputePeakFactorValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePeakFactorValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePeakFactorValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputePeakFactorVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePeakFactorVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePeakFactorVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputePeakFactorVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePeakFactorVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePeakFactorVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputePDFValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePDFValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePDFValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputePDFVectorX) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputePDFVectorX()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputePDFVectorX()));
    }

    else if(function == WindLab::WindLabUtils::ComputeDecomposedPSDValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedPSDValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedPSDValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedCrossSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedCrossSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeDecomposedCrossSpectrumMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeDecomposedCrossSpectrumMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeRandomValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeRandomValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeRandomValue()));
    }
    else if(function == WindLab::WindLabUtils::GenerateRandomMatrixFP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerGenerateRandomMatrixFP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerGenerateRandomMatrixFP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeRoughnessValue)
        {
            simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
            connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeRoughnessValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeRoughnessValue()));
        }
    else if(function == WindLab::WindLabUtils::ComputeRoughnessVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeRoughnessVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeRoughnessVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeRoughnessVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeRoughnessVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeRoughnessVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeShearVelocityOfFlowValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeShearVelocityOfFlowValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeShearVelocityOfFlowValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeShearVelocityOfFlowVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeShearVelocityOfFlowVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeShearVelocityOfFlowVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeShearVelocityOfFlowVectorP()));
    }
    else if(function == WindLab::WindLabUtils::Simulate)
        {
            simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerSimulate()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerSimulate()));
        }
    else if(function == WindLab::WindLabUtils::SimulateInLargeScaleMode) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerSimulateInLargeScaleMode()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerSimulateInLargeScaleMode()));
    }

    else if(function == WindLab::WindLabUtils::ComputeSkewnessValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeSkewnessValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeSkewnessValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeSkewnessVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeSkewnessVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeSkewnessVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeSkewnessVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeSkewnessVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeSkewnessVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeStandardDeviationValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeStandardDeviationValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeStandardDeviationValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeStandardDeviationVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeStandardDeviationVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeStandardDeviationVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeStandardDeviationVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeStandardDeviationVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeStandardDeviationVectorT()));
    }

    else if(function == WindLab::WindLabUtils::TableToolCompute) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerTableToolCompute()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerTableToolCompute()));
    }

    else if(function == WindLab::WindLabUtils::ComputeTurbulenceIntensityValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeTurbulenceIntensityValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeTurbulenceIntensityValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeTurbulenceIntensityVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeTurbulenceIntensityVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeTurbulenceIntensityVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeTurbulenceIntensityVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeTurbulenceScaleValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeTurbulenceScaleValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeTurbulenceScaleValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceScaleVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeTurbulenceScaleVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeTurbulenceScaleVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceScaleVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeTurbulenceScaleVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeTurbulenceScaleVectorT()));
    }

    else if(function == WindLab::WindLabUtils::UserDefinedRPSObjectCompute) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerUserDefinedRPSObjectCompute()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerUserDefinedRPSObjectCompute()));
    }

    else if(function == WindLab::WindLabUtils::ComputeVarianceValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeVarianceValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeVarianceValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeVarianceVectorP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeVarianceVectorP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeVarianceVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeVarianceVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeVarianceVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeVarianceVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeWavePassageEffectMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeWavePassageEffectMatrixPP()));
    }

    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeXCrossSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeXCrossSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeXCrossSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeXCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeXCrossSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeXCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeXCrossSpectrumMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeXCrossSpectrumMatrixPP()));
    }
        else if(function == WindLab::WindLabUtils::ComputeXAutoSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeXAutoSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeXAutoSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXAutoSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeXAutoSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeXAutoSpectrumVectorF()));
    }
    else if (function == WindLab::WindLabUtils::ComputeXAutoSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeXAutoSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeXAutoSpectrumVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeYCrossSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeYCrossSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeYCrossSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeYCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeYCrossSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeYCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeYCrossSpectrumMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeYCrossSpectrumMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYAutoSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeYAutoSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeYAutoSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYAutoSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeYAutoSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeYAutoSpectrumVectorF()));
    }
    else if (function == WindLab::WindLabUtils::ComputeYAutoSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeYAutoSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeYAutoSpectrumVectorT()));
    }

    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeZCrossSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeZCrossSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeZCrossSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeZCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeZCrossSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeZCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumMatrixPP) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeZCrossSpectrumMatrixPP()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeZCrossSpectrumMatrixPP()));
    }
        else if(function == WindLab::WindLabUtils::ComputeZAutoSpectrumValue) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeZAutoSpectrumValue()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeZAutoSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZAutoSpectrumVectorF) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeZAutoSpectrumVectorF()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeZAutoSpectrumVectorF()));
    }
    else if (function == WindLab::WindLabUtils::ComputeZAutoSpectrumVectorT) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerComputeZAutoSpectrumVectorT()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerComputeZAutoSpectrumVectorT()));
    }

    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setRange(0, 100);
    bar->show();
    Gui::getMainWindow()->showMessage(tr("Loading %1...").arg(QString::fromLatin1(simulationWorker2->getComparisonName().c_str())));

}

void WindLabComparisonStarter::slotDisplayResultInTable(QString str, int what)
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

void WindLabComparisonStarter::slotDisplayResultInMatrix(QString str, int what)
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

void WindLabComparisonStarter::slotDisplayResultInTable1(QString str, int what)
{
    slotDisplayResultInTable(str, what);
}
void WindLabComparisonStarter::slotDisplayResultInMatrix1(QString str, int what)
{
    slotDisplayResultInMatrix(str, what);
}
void WindLabComparisonStarter::slotDisplayResultInTable2(QString str, int what)
{
    slotDisplayResultInTable(str, what);
}
void WindLabComparisonStarter::slotDisplayResultInMatrix2(QString str, int what)
{
    slotDisplayResultInMatrix(str, what);
}

void WindLabComparisonStarter::setComplexNumberDisplay(const char* displayType)
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