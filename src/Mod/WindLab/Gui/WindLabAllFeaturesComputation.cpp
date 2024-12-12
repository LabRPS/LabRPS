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

#include "WindLabAllFeaturesComputation.h"
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
#include <Gui/Application.h>
#include "ViewProviderWindLabSimulation.h"
#include <App/Application.h>
#include <App/Document.h>

using namespace WindLabGui;

WindLabAllFeaturesComputation::WindLabAllFeaturesComputation(WindLab::WindLabSimulation* sim, QObject* parent)
    : m_sim(sim), QObject(parent)
{
    WindLabGui::ViewProviderWindLabSimulation* vp = dynamic_cast<WindLabGui::ViewProviderWindLabSimulation*>(Gui::Application::Instance->getViewProvider(m_sim));
    if (vp)
        vp->setAllComputation(this);

    App::Document* doc = App::GetApplication().getActiveDocument();
    Gui::Document* guiDoc = Gui::Application::Instance->getDocument(doc);
    guiDoc->setRunning(true);

}

WindLabAllFeaturesComputation::~WindLabAllFeaturesComputation()
{
    App::Document* doc = App::GetApplication().getActiveDocument();
    Gui::Document* guiDoc = Gui::Application::Instance->getDocument(doc);
    guiDoc->setRunning(false);

    WindLabGui::ViewProviderWindLabSimulation* vp = dynamic_cast<WindLabGui::ViewProviderWindLabSimulation*>(Gui::Application::Instance->getViewProvider(m_sim));
    if (vp)
        vp->setAllComputation(nullptr);
 
}

RPSWindLabSimulationWorker *WindLabAllFeaturesComputation::GetWindLabSimulationWorker()
{
    return simulationWorker;
}

QThread* WindLabAllFeaturesComputation::getWindLabSimulationThread()
{ return simulationThread; }

QString WindLabAllFeaturesComputation::logSimulationInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = QString::fromLatin1("<b>[") + dt.toString(Qt::LocalDate) + QString::fromLatin1("&emsp;") +
            QString::fromLatin1(": ''") + name + QString::fromLatin1("'']</b><hr>");


    WindLab::WindLabUtils::TableColorProfile profile =
        WindLab::WindLabUtils::TableColorProfile::Success;
    
    if (status != true)
        profile = WindLab::WindLabUtils::TableColorProfile::Failure;

    QString table;
    table = WindLab::WindLabUtils::makeHtmlTable(37, 2, false, profile);

    table = table.arg(tr("Computation Time"), QString::number(GetWindLabSimulationWorker()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"));
    table = table.arg(tr("Simulation Method"), QString::fromLatin1(m_sim->getSimulationData()->simulationMethod.getValue()));
    table = table.arg(tr("Coherence Function"), QString::fromLatin1(m_sim->getSimulationData()->coherenceFunction.getValue()));
    table = table.arg(tr("Location Distribution"), QString::fromLatin1(m_sim->getSimulationData()->spatialDistribution.getValue()));
    table = table.arg(tr("Mean Wind Profile"), QString::fromLatin1(m_sim->getSimulationData()->meanFunction.getValue()));
    table = table.arg(tr("Along Wind Spectrum"), QString::fromLatin1(m_sim->getSimulationData()->alongWindSpectrumModel.getValue()));
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
    table = table.arg(tr("Gust Factor"), QString::fromLatin1(m_sim->getSimulationData()->gustFactor.getValue()));
    table = table.arg(tr("Kurtosis"), QString::fromLatin1(m_sim->getSimulationData()->kurtosis.getValue()));
    table = table.arg(tr("Peak Factor"), QString::fromLatin1(m_sim->getSimulationData()->peakFactor.getValue()));
    table = table.arg(tr("Probability Density Function"), QString::fromLatin1(m_sim->getSimulationData()->probabilityDensityFunction.getValue()));
    table = table.arg(tr("Roughness"), QString::fromLatin1(m_sim->getSimulationData()->roughness.getValue()));
    table = table.arg(tr("Shear Velocity Of Flow"), QString::fromLatin1(m_sim->getSimulationData()->shearVelocityOfFlow.getValue()));
    table = table.arg(tr("Skewness"), QString::fromLatin1(m_sim->getSimulationData()->skewness.getValue()));
    table = table.arg(tr("Standard Deviation"), QString::fromLatin1(m_sim->getSimulationData()->standardDeviation.getValue()));
    table = table.arg(tr("Turbulence Intensity"), QString::fromLatin1(m_sim->getSimulationData()->turbulenceIntensity.getValue()));
    table = table.arg(tr("Turbulence Scale"), QString::fromLatin1(m_sim->getSimulationData()->turbulenceScale.getValue()));
    table = table.arg(tr("Variance"), QString::fromLatin1(m_sim->getSimulationData()->variance.getValue()));
    table = table.arg(tr("Wave Passage Effect"), QString::fromLatin1(m_sim->getSimulationData()->wavePassageEffect.getValue()));

    if ("Along wind" == m_sim->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Along Wind"));
    }
    else if ("Across wind" == m_sim->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Across Wind"));
    }
    else if ("Vertical wind" == m_sim->getSimulationData()->WindDirection.getValueAsString())
    {
        table = table.arg(tr("Wind Direction"), QString::fromLatin1("Vertical Wind"));
    }

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

    if (true == m_sim->getSimulationData()->largeScaleSimulationMode.getValue())
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

void WindLabAllFeaturesComputation::startSimulationWorker(QString function, const char* complexNumberDisplay)
{
    // create the worker
    simulationWorker = new RPSWindLabSimulationWorker(m_sim);

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

    
    if (function == WindLab::WindLabUtils::ComputeLocationCoordinateMatrixP3)
    {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeLocationCoordinateMatrixP3()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCoherenceMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCoherenceMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCorrelationValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCorrelationValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCorrelationVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCorrelationVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCrossCorrelationMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCrossCorrelationMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCPDValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCPDValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeCPDVectorX) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeCPDVectorX()));
    }
    else if(function == WindLab::WindLabUtils::ComputeFrequencyValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeFrequencyValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeFrequenciesVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeFrequenciesVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeFrequenciesMatrixFP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeFrequenciesMatrixFP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeGustFactorValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeGustFactorValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeGustFactorVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeGustFactorVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeGustFactorVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeGustFactorVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeKurtosisValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeKurtosisValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeKurtosisVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeKurtosisVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeKurtosisVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeKurtosisVectorT()));
    }
    else if(function == WindLab::WindLabUtils::MatrixToolCompute) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerMatrixToolCompute()));
    }
    else if(function == WindLab::WindLabUtils::ComputeMeanWindSpeedValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeMeanWindSpeedValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeMeanWindSpeedVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeMeanWindSpeedVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeMeanWindSpeedVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeMeanWindSpeedVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeModulationValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeModulationValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeModulationVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeModulationVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeModulationVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeModulationVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputePeakFactorValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePeakFactorValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputePeakFactorVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePeakFactorVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputePeakFactorVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePeakFactorVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputePDFValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePDFValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputePDFVectorX) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputePDFVectorX()));
    }
    else if(function == WindLab::WindLabUtils::ComputeDecomposedPSDValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedPSDValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeDecomposedCrossSpectrumMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeRandomValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeRandomValue()));
    }
    else if(function == WindLab::WindLabUtils::GenerateRandomMatrixFP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerGenerateRandomMatrixFP()));
    }
    else if(function == WindLab::WindLabUtils::GenerateRandomCubeFPS) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerGenerateRandomCubeFPS()));
    }
    else if(function == WindLab::WindLabUtils::ComputeRoughnessValue)
    {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeRoughnessValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeRoughnessVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeRoughnessVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeRoughnessVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeRoughnessVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeShearVelocityOfFlowValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeShearVelocityOfFlowValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeShearVelocityOfFlowVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeShearVelocityOfFlowVectorP()));
    }
    else if(function == WindLab::WindLabUtils::Simulate)
        {
            simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerSimulate()));
        }
    else if(function == WindLab::WindLabUtils::SimulateInLargeScaleMode) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerSimulateInLargeScaleMode()));
    }
    else if(function == WindLab::WindLabUtils::ComputeSkewnessValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeSkewnessValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeSkewnessVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeSkewnessVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeSkewnessVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeSkewnessVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeStandardDeviationValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeStandardDeviationValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeStandardDeviationVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeStandardDeviationVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeStandardDeviationVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeStandardDeviationVectorT()));
    }
    else if(function == WindLab::WindLabUtils::TableToolCompute) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerTableToolCompute()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceIntensityValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeTurbulenceIntensityValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeTurbulenceIntensityVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeTurbulenceIntensityVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceScaleValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeTurbulenceScaleValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceScaleVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeTurbulenceScaleVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeTurbulenceScaleVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeTurbulenceScaleVectorT()));
    }

    else if(function == WindLab::WindLabUtils::UserDefinedRPSObjectCompute) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerUserDefinedRPSObjectCompute()));
    }
    else if(function == WindLab::WindLabUtils::ComputeVarianceValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeVarianceValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeVarianceVectorP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeVarianceVectorP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeVarianceVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeVarianceVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeWavePassageEffectMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeWavePassageEffectMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeXCrossSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeXCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeXCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXCrossSpectrumMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeXCrossSpectrumMatrixPP()));
    }
        else if(function == WindLab::WindLabUtils::ComputeXAutoSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeXAutoSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeXAutoSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeXAutoSpectrumVectorF()));
    }
    else if (function == WindLab::WindLabUtils::ComputeXAutoSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeXAutoSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeYCrossSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeYCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeYCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYCrossSpectrumMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeYCrossSpectrumMatrixPP()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYAutoSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeYAutoSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeYAutoSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeYAutoSpectrumVectorF()));
    }
    else if (function == WindLab::WindLabUtils::ComputeYAutoSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeYAutoSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeZCrossSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeZCrossSpectrumVectorF()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeZCrossSpectrumVectorT()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZCrossSpectrumMatrixPP) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeZCrossSpectrumMatrixPP()));
    }
        else if(function == WindLab::WindLabUtils::ComputeZAutoSpectrumValue) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeZAutoSpectrumValue()));
    }
    else if(function == WindLab::WindLabUtils::ComputeZAutoSpectrumVectorF) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeZAutoSpectrumVectorF()));
    }
    else if (function == WindLab::WindLabUtils::ComputeZAutoSpectrumVectorT) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerComputeZAutoSpectrumVectorT()));
    }

    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setRange(0, 0);
    bar->show();

}

void WindLabAllFeaturesComputation::slotDisplayResultInTable(QString str, int what)
{
    if (what == 1)
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
    QString info = logSimulationInfo(true, QString::fromLatin1("Results"));

    Gui::getMainWindow()->showResults(info);
}

void WindLabAllFeaturesComputation::slotDisplayResultInMatrix(QString str, int what)
{
    if (what == 1)
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
}

void WindLabAllFeaturesComputation::setComplexNumberDisplay(const char* displayType)
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