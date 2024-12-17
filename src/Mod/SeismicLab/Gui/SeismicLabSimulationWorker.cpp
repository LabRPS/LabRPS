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
#include "SeismicLabSimulationWorker.h"
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/SeismicLab/App/SeismicLabUtils.h>
#include <Mod/SeismicLabAPI/App/RPSSeismicLabAPI.h>

#include <Base/Tools.h>
#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include <Mod/SeismicLab/Gui/SeismicLabSimulationObserver.h>


#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include <QThread>
#include <QTime>


using namespace SeismicLabGui;

RPSSeismicLabSimulationWorker::RPSSeismicLabSimulationWorker(SeismicLab::SeismicLabSimulation* sim) : m_sim(sim)
{
    m_sim->getSimulationData()->isInterruptionRequested.setValue(false);
    stopped = true;
}

RPSSeismicLabSimulationWorker::~RPSSeismicLabSimulationWorker() {}
void RPSSeismicLabSimulationWorker::setComputationTime()
{
    // auto doc = App::GetApplication().getActiveDocument();
    // if (!doc)
    //     return;
    // auto obj = doc->getObject(m_comparisonName.c_str());
    // SeismicLab::SeismicLabSimulationComparison* comp = static_cast<SeismicLab::SeismicLabSimulationComparison*>(obj);
    // if (!comp)
    //     return;
    // std::string simName = static_cast<App::DocumentObject*>(m_sim)->getNameInDocument();

    // if (strcmp(simName.c_str(), comp->SimulationCandidate1.getValue()) == 0) {
    //     comp->ComputationTime1.setValue(m_simulationTime);
    // }
    // else if (strcmp(simName.c_str(), comp->SimulationCandidate2.getValue()) == 0) {
    //     comp->ComputationTime2.setValue(m_simulationTime);
    // }

    // m_sim->getSimulationData()->comparisonMode.setValue(false);
}

bool RPSSeismicLabSimulationWorker::workerComputeLocationCoordinateMatrixP3()
{
    if (isStopped()) {
        stopped = false;

        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeLocationCoordinateMatrixP3) {
            m_ResultMatrix.resize(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),4);
            bool returnResult = false;

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeLocationCoordinateMatrixP3(m_ResultMatrix, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();

            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}


bool RPSSeismicLabSimulationWorker::workerComputeCrossCoherenceValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceValue) {
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(1, 4);
            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));
            std::complex<double> computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossCoherenceValue(locationJ, locationK, frequency, time,
                                                             computedValue, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();

            if (!returnResult) {
                Base::Console().Warning("The computation of the coherence value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue.real();
            m_ResultMatrix(0, 3) = computedValue.imag();

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCrossCoherenceVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());
            m_ResultVectorVal_cx.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossCoherenceVectorF(
                locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the coherence vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCrossCoherenceVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal_cx.resize(
                m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossCoherenceVectorT(locationJ, locationK, frequency,
                                                               m_ResultVectorVar,
                                                               m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the coherence vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCrossCoherenceMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossCoherenceMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix_cx.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeCrossCoherenceMatrixPP(
                frequency, time, m_ResultMatrix_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Error("The computation of the coherence matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInMatrix(QString::fromLatin1(featureName.c_str()), 5);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeCrossCorrelationValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossCorrelationValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(1, 2);
            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));
            double correlationValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossCorrelationValue(locationJ, locationK, time,
                                                               correlationValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the correlation value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = correlationValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCrossCorrelationVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossCorrelationVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossCorrelationVectorT(
                locationJ, locationK, m_ResultVectorVar, m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the correlation vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeCrossCorrelationMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossCorrelationMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),
                                  m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult =
                m_sim->computeCrossCorrelationMatrixPP(time, m_ResultMatrix, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the correlation matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInMatrix(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeCPDValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCPDValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active simulation
            m_ResultMatrix.resize(1, 2);

            double CPDValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeCPDValue(CPDValue, time, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the coherence value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = CPDValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCPDVectorX()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCPDVectorX) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfIncrementOfVariableX.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfIncrementOfVariableX.getValue());
            Base::StopWatch watch;
            watch.start();
            bool returnResult =
                m_sim->computeCPDVectorX(m_ResultVectorVar, m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the cpd has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeFrequencyValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeFrequencyValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int frequencyIndex = m_sim->getSimulationData()->frequencyIndex.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double frequency = 0.0;

            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeFrequencyValue(locationJ, frequencyIndex, frequency, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the frequency value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix.resize(1, 1);
            m_ResultMatrix(0, 0) = frequency;
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeFrequenciesVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeFrequenciesVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning("The computation of the location coordinates fails.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeFrequenciesVectorF(locationJ, m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the frequency vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 3);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeFrequenciesMatrixFP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeFrequenciesMatrixFP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }


            m_ResultMatrix.resize(m_sim->getSimulationData()->numberOfFrequency.getValue(),
                                  m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeFrequenciesMatrixFP(m_ResultMatrix, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Error("The computation of the coherence matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeKurtosisValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeKurtosisValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeKurtosisValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the kurtosis value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeKurtosisVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeKurtosisVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeKurtosisVectorP(time, m_ResultVectorVar, m_ResultVectorVal,
                                                         featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the kurtosis vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeKurtosisVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeKurtosisVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeKurtosisVectorT(locationJ, m_ResultVectorVar,
                                                         m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the kurtosis vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerMatrixToolCompute()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::MatrixToolCompute) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active feature
            SeismicLabAPI::IrpsSLMatrixTool* activefeature =
                static_cast<SeismicLabAPI::IrpsSLMatrixTool*>(
                    doc->getObject(m_sim->getSimulationData()->matrixTool.getValue()));

            if (!activefeature) {
                Base::Console().Warning("No valid active matrix tool feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active simulation
            SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(
                SeismicLabGui::SeismicLabSimulationObserver::instance()->active());

            if (!sim) {
                Base::Console().Warning("No valid active simulation found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat activeAlphaPlotMatrix;
            Gui::getMainWindow()->getAlphaPlot()->getActiveMatrixAsEigenMatrix(
                activeAlphaPlotMatrix);

            m_ResultMatrix.resize(activeAlphaPlotMatrix.rows(), activeAlphaPlotMatrix.cols());

            bool returnResult = activefeature->MatrixToolCompute(
                *m_sim->getSimulationData(), activeAlphaPlotMatrix, m_ResultMatrix);

            if (!returnResult) {
                Base::Console().Warning("The running of the matrix tool has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInMatrix(QString::fromLatin1(activefeature->Label.getValue()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeMeanAccelerationValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeMeanAccelerationValue) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            activeSpatialDistr->ComputeLocationCoordinateMatrixP3(*m_sim->getSimulationData(),
                                                                  locationCoord);

            m_ResultMatrix.resize(1, 3);
            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d location(locationCoord(locationIndexJ, 1),
                                    locationCoord(locationIndexJ, 2),
                                    locationCoord(locationIndexJ, 3));
            double meanValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult =
                m_sim->computeMeanAccelerationValue(location, time, meanValue, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the mean ground motion acceleration has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix(0, 0) = location.z;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = meanValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeMeanAccelerationVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeMeanAccelerationVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeMeanAccelerationVectorP(time, m_ResultVectorVar,
                                                                   m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the mean ground motion acceleration has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeMeanAccelerationVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeMeanAccelerationVectorT) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            activeSpatialDistr->ComputeLocationCoordinateMatrixP3(*m_sim->getSimulationData(),
                                                                  locationCoord);

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d location(locationCoord(locationIndexJ, 1),
                                    locationCoord(locationIndexJ, 2),
                                    locationCoord(locationIndexJ, 3));


            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeMeanAccelerationVectorT(location, m_ResultVectorVar,
                                                                   m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the mean ground motion acceleration has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeModulationValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeModulationValue) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            activeSpatialDistr->ComputeLocationCoordinateMatrixP3(*m_sim->getSimulationData(),
                                                                  locationCoord);

            m_ResultMatrix.resize(1, 2);
            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d location(locationCoord(locationIndexJ, 1),
                                    locationCoord(locationIndexJ, 2),
                                    locationCoord(locationIndexJ, 3));
            double modulationValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
            Base::StopWatch watch;
            watch.start();
            bool returnResult =
                m_sim->computeModulationValue(location,frequency, time, modulationValue, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the modulation function has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = modulationValue;
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeModulationVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeModulationVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);            
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeModulationVectorP(frequency, time, m_ResultVectorVar,
                                                                m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the modulation function has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeModulationVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeModulationVectorT) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active simulation


            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            activeSpatialDistr->ComputeLocationCoordinateMatrixP3(*m_sim->getSimulationData(),
                                                                  locationCoord);

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d location(locationCoord(locationIndexJ, 1),
                                    locationCoord(locationIndexJ, 2),
                                    locationCoord(locationIndexJ, 3));


            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeModulationVectorT(location, frequency, m_ResultVectorVar,
                                                                m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the modulation function has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}




bool RPSSeismicLabSimulationWorker::workerComputeModulationVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeModulationVectorF) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active simulation


            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            activeSpatialDistr->ComputeLocationCoordinateMatrixP3(*m_sim->getSimulationData(),
                                                                  locationCoord);

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d location(locationCoord(locationIndexJ, 1),
                                    locationCoord(locationIndexJ, 2),
                                    locationCoord(locationIndexJ, 3));


            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeModulationVectorF(location, time, m_ResultVectorVar,
                                                                m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the modulation function has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputePeakFactorValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputePeakFactorValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computePeakFactorValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the kurtosis value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputePeakFactorVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputePeakFactorVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computePeakFactorVectorP(time, m_ResultVectorVar,
                                                           m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the peak factor vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputePeakFactorVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputePeakFactorVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computePeakFactorVectorT(locationJ, m_ResultVectorVar,
                                                           m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the peack factor vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputePDFValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputePDFValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(1, 2);

            double PDFValue = 0.0;
            double xValue = m_sim->getSimulationData()->minVariableX.getValue()
                + m_sim->getSimulationData()->indexOfVariableX.getValue()
                    * m_sim->getSimulationData()->numberOfIncrementOfVariableX.getValue();
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computePDFValue(PDFValue, xValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of probability density function has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix(0, 0) = xValue;
            m_ResultMatrix(0, 1) = PDFValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputePDFVectorX()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputePDFVectorX) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfIncrementOfVariableX.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfIncrementOfVariableX.getValue());
            Base::StopWatch watch;
            watch.start();
            bool returnResult =
                m_sim->computePDFVectorX(m_ResultVectorVar, m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of probability density function has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeDecomposedPSDValue()
{
    if (isStopped()) {
        stopped = false;
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeDecomposedCrossSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());
            m_ResultVectorVal_cx.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeDecomposedCrossSpectrumVectorF(
                locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the decomposed spectrum vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeDecomposedCrossSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }


            //get the active simulation


            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal_cx.resize(
                m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeDecomposedCrossSpectrumVectorT(
                locationJ, locationK, frequency, m_ResultVectorVar, m_ResultVectorVal_cx,
                featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the decomposed spectrum vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeDecomposedCrossSpectrumMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeDecomposedCrossSpectrumMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix_cx.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeDecomposedCrossSpectrumMatrixPP(
                frequency, time, m_ResultMatrix_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the decomposed spectrum matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInMatrix(QString::fromLatin1(featureName.c_str()), 5);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeRandomValue()
{
    if (isStopped()) {
        stopped = false;
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerGenerateRandomMatrixFP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::GenerateRandomMatrixFP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(m_sim->getSimulationData()->numberOfFrequency.getValue(),
                                  m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->generateRandomMatrixFP(m_ResultMatrix, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The generation of the random phase angle has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerGenerateRandomCubeFPS()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::GenerateRandomCubeFPS) {

            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultCube.resize(m_sim->getSimulationData()->numberOfFrequency.getValue(),
                                  m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),
                                  m_sim->getSimulationData()->numberOfSample.getValue());
            Base::StopWatch watch;
            watch.start();

            bool returnResult = m_sim->generateRandomCubeFPS(m_ResultCube, featureName);
            if (!returnResult) {
                Base::Console().Warning("The generation of the random phase angle has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            Eigen::Tensor<double, 2> matrix_at_k = m_ResultCube.chip(m_sim->getSimulationData()->sampleIndex.getValue(), 2);
            Eigen::Map<Eigen::MatrixXd> matrix_k(matrix_at_k.data(), matrix_at_k.dimension(0), matrix_at_k.dimension(1));
            m_ResultMatrix = matrix_k;

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The generation of the random phase angle has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeShearVelocityOfFlowValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeShearVelocityOfFlowValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the shear velocity value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeShearVelocityOfFlowVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeShearVelocityOfFlowVectorP(time, m_ResultVectorVar,
                                                                    m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the shear velocity vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeShearVelocityOfFlowVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeShearVelocityOfFlowVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeShearVelocityOfFlowVectorT(locationJ, m_ResultVectorVar,
                                                                    m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the shear vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerSimulate()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::Simulate) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultCube.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue(),
                      m_sim->getSimulationData()->numberOfSpatialPosition.getValue()
                          + 1, m_sim->getSimulationData()->numberOfSample.getValue());
            m_ResultCube.setZero();
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->simulate(m_ResultCube, featureName);
            if (!returnResult) {
                Base::Console().Warning("The generation of the random sea surface heights has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            Eigen::Tensor<double, 2> matrix_at_k = m_ResultCube.chip(m_sim->getSimulationData()->sampleIndex.getValue(), 2);
            Eigen::Map<Eigen::MatrixXd> matrix_k(matrix_at_k.data(), matrix_at_k.dimension(0), matrix_at_k.dimension(1));
            m_ResultMatrix = matrix_k;

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());

            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerSimulateInLargeScaleMode()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::SimulateInLargeScaleMode) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            QString fineName = QString::fromLatin1("WindVelocity\n");
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->simulateInLargeScaleMode(featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the ground motion matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeSkewnessValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeSkewnessValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeSkewnessValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeSkewnessVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeSkewnessVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeSkewnessVectorP(time, m_ResultVectorVar, m_ResultVectorVal,
                                                         featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeSkewnessVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeSkewnessVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeSkewnessVectorT(locationJ, m_ResultVectorVar,
                                                         m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeStandardDeviationValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeStandardDeviationValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeStandardDeviationValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeStandardDeviationVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeStandardDeviationVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeStandardDeviationVectorP(time, m_ResultVectorVar,
                                                                  m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the standard deviation vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeStandardDeviationVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeStandardDeviationVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeStandardDeviationVectorT(locationJ, m_ResultVectorVar,
                                                                  m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerTableToolCompute()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::TableToolCompute) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active feature
            SeismicLabAPI::IrpsSLTableTool* activefeature = static_cast<SeismicLabAPI::IrpsSLTableTool*>(
                doc->getObject(m_sim->getSimulationData()->tableTool.getValue()));

            if (!activefeature) {
                Base::Console().Warning("No valid active table tool feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active simulation
            SeismicLab::SeismicLabSimulation* sim = static_cast<SeismicLab::SeismicLabSimulation*>(
                SeismicLabGui::SeismicLabSimulationObserver::instance()->active());

            if (!sim) {
                Base::Console().Warning("No valid active simulation found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat activeAlphaPlotTable;
            Gui::getMainWindow()->getAlphaPlot()->getActiveTableAsEigenMatrix(activeAlphaPlotTable);

            m_ResultMatrix.resize(activeAlphaPlotTable.rows(), activeAlphaPlotTable.cols());


            bool returnResult = activefeature->TableToolCompute(
                *m_sim->getSimulationData(), activeAlphaPlotTable, m_ResultMatrix);

            if (!returnResult) {
                Base::Console().Warning("The running of the table tool has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(activefeature->Label.getValue()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerUserDefinedRPSObjectCompute()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::UserDefinedRPSObjectCompute) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),
                                  m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->userDefinedRPSObjectCompute(m_ResultMatrix, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the user defined feature has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeVarianceValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeVarianceValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeVarianceValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the variance value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeVarianceVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeVarianceVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultVectorVar.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            m_ResultVectorVal.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeVarianceVectorP(time, m_ResultVectorVar, m_ResultVectorVal,
                                                         featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the variance vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }
            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeVarianceVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeVarianceVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeVarianceVectorT(locationJ, m_ResultVectorVar,
                                                         m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}


bool RPSSeismicLabSimulationWorker::workerComputeWavePassageEffectValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);

            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(1, 4);
            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));
            std::complex<double> computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeWavePassageEffectValue(locationJ, locationK, frequency,
                                                                time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the coherence value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue.real();
            m_ResultMatrix(0, 3) = computedValue.imag();

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeWavePassageEffectVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }


            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());
            m_ResultVectorVal_cx.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);

            Base::StopWatch watch;
            watch.start();
            //returnResult = m_sim->computeWavePassageEffectVectorF(locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);
            returnResult = m_sim->computeWavePassageEffectVectorF(
                locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of wave passage effect vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeWavePassageEffectVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal_cx.resize(
                m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeWavePassageEffectVectorT(
                locationJ, locationK, frequency, m_ResultVectorVar, m_ResultVectorVal_cx,
                featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the coherence vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeWavePassageEffectMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeWavePassageEffectMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix_cx.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeWavePassageEffectMatrixPP(
                frequency, time, m_ResultMatrix_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Error("The computation of the coherence matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInMatrix(QString::fromLatin1(featureName.c_str()), 5);
        }
    }

    stopped = true;
    complete();
    return true;
}


bool RPSSeismicLabSimulationWorker::workerComputeCrossSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(1, 4);
            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));
            std::complex<double> computedValue(0.0, 0.0);
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossSpectrumValue(locationJ, locationK, frequency, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue.real();
            m_ResultMatrix(0, 3) = computedValue.imag();

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCrossSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());
            m_ResultVectorVal_cx.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossSpectrumVectorF(locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCrossSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();
            int locationIndexK = m_sim->getSimulationData()->locationK.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            Base::Vector3d locationK(locationCoord(locationIndexK, 1),
                                     locationCoord(locationIndexK, 2),
                                     locationCoord(locationIndexK, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal_cx.resize(
                m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeCrossSpectrumVectorT(locationJ, locationK, frequency,
                                                               m_ResultVectorVar,
                                                               m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 4);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeCrossSpectrumMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeCrossSpectrumMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix_cx.resize(
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue(),
                m_sim->getSimulationData()->numberOfSpatialPosition.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->computeCrossSpectrumMatrixPP(
                frequency, time, m_ResultMatrix_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInMatrix(QString::fromLatin1(featureName.c_str()), 5);
        }
    }

    stopped = true;
    complete();
    return true;
}

bool RPSSeismicLabSimulationWorker::workerComputeAutoSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeAutoSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix.resize(1, 3);
            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));
            double computedValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeAutoSpectrumValue(locationJ, frequency, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue;

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeAutoSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeAutoSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeAutoSpectrumVectorF(locationJ, time, m_ResultVectorVar,
                                                              m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}
bool RPSSeismicLabSimulationWorker::workerComputeAutoSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == SeismicLab::SeismicLabUtils::ComputeAutoSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            //get the active location distribution feature
            SeismicLabAPI::IrpsSLLocationDistribution* activeSpatialDistr =
                static_cast<SeismicLabAPI::IrpsSLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Warning("No valid active location distribution feature found.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the location coordinates has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

            double frequency = m_sim->getSimulationData()->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond)
                + m_sim->getSimulationData()->frequencyIndex.getValue()
                    * m_sim->getSimulationData()->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);

            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeAutoSpectrumVectorT(
                locationJ, frequency, m_ResultVectorVar, m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 2);
        }
    }

    stopped = true;
    complete();
    return true;
}

void RPSSeismicLabSimulationWorker::stop()
{
    mutex.lock();
    stopped = true;
    m_sim->getSimulationData()->isInterruptionRequested.setValue(true);
    m_sim->getSimulationData()->isSimulationSuccessful.setValue(false);
    mutex.unlock();
}

void RPSSeismicLabSimulationWorker::complete()
{
    mutex.lock();
    m_sim->setStatus(App::SimulationStatus::Completed, true);
    m_sim->getSimulationData()->isSimulationSuccessful.setValue(true);
    mutex.unlock();
}

bool RPSSeismicLabSimulationWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}


double RPSSeismicLabSimulationWorker::getSimulationTime() { return m_simulationTime; }

std::string RPSSeismicLabSimulationWorker::getComparisonName() const { return m_comparisonName; }
void RPSSeismicLabSimulationWorker::setComparisonName(std::string name) { m_comparisonName = name; }