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
#include "WindLabSimulationWorker.h"
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/WindLab/App/WindLabUtils.h>
#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>

#include <Base/Tools.h>
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>


#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/WindLab/App/WindLabSimulation.h>

#include <QThread>
#include <QTime>


using namespace WindLabGui;

RPSWindLabSimulationWorker::RPSWindLabSimulationWorker(WindLab::WindLabSimulation* sim) : m_sim(sim)
{
    m_sim->getSimulationData()->isInterruptionRequested.setValue(false);
    stopped = true;
    m_simulationTime = 0.0;
}

RPSWindLabSimulationWorker::~RPSWindLabSimulationWorker()
{ 
    stop();
}

void RPSWindLabSimulationWorker::setComputationTime()
{
    // auto doc = App::GetApplication().getActiveDocument();
    // if (!doc)
    //     return;
    // auto obj = doc->getObject(m_comparisonName.c_str());
    // WindLab::WindLabSimulationComparison* comp = static_cast<WindLab::WindLabSimulationComparison*>(obj);
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

bool RPSWindLabSimulationWorker::workerComputeLocationCoordinateMatrixP3()
{
    if (isStopped()) {
        stopped = false;

        if (m_computingFunction == WindLab::WindLabUtils::ComputeLocationCoordinateMatrixP3) {
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
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}


bool RPSWindLabSimulationWorker::workerComputeCrossCoherenceValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCrossCoherenceValue) {
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue.real();
            m_ResultMatrix(0, 3) = computedValue.imag();
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeCrossCoherenceVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCrossCoherenceVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeCrossCoherenceVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCrossCoherenceVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeCrossCoherenceMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCrossCoherenceMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 5);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeCrossCorrelationValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCrossCorrelationValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = correlationValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeCrossCorrelationVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCrossCorrelationVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeCrossCorrelationMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCrossCorrelationMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 1);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeCPDValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCPDValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = CPDValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeCPDVectorX()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeCPDVectorX) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeFrequencyValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeFrequencyValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 1);
            m_ResultMatrix(0, 0) = frequency;        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeFrequenciesVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeFrequenciesVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Warning("The computation of the location coordinates fails.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 3);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeFrequenciesMatrixFP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeFrequenciesMatrixFP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeGustFactorValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeGustFactorValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfFrequency.getValue());

            int locationIndexJ = m_sim->getSimulationData()->locationJ.getValue();

            Base::Vector3d locationJ(locationCoord(locationIndexJ, 1),
                                     locationCoord(locationIndexJ, 2),
                                     locationCoord(locationIndexJ, 3));

            double gustFactorValue = 0.0;
            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeGustFactorValue(locationJ, time, gustFactorValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the gust factor value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = gustFactorValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeGustFactorVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeGustFactorVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            returnResult = m_sim->computeGustFactorVectorP(time, m_ResultVectorVar,
                                                           m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the gust factor value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeGustFactorVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeGustFactorVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeGustFactorVectorT(locationJ, m_ResultVectorVar,
                                                           m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the gust factor vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeKurtosisValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeKurtosisValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeKurtosisVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeKurtosisVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeKurtosisVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeKurtosisVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerMatrixToolCompute()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::MatrixToolCompute) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active feature
            WindLabAPI::IrpsWLMatrixTool* activefeature =
                static_cast<WindLabAPI::IrpsWLMatrixTool*>(
                    doc->getObject(m_sim->getSimulationData()->matrixTool.getValue()));

            if (!activefeature) {
                Base::Console().Warning("No valid active matrix tool feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active simulation
            WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(
                WindLabGui::WindLabSimulationObserver::instance()->active());

            if (!sim) {
                Base::Console().Warning("No valid active simulation found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 1);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeMeanWindSpeedValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeMeanWindSpeedValue) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                m_sim->computeMeanWindSpeedValue(location, time, meanValue, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the mean wind speed has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix(0, 0) = location.z;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = meanValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeMeanWindSpeedVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeMeanWindSpeedVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            bool returnResult = m_sim->computeMeanWindSpeedVectorP(time, m_ResultVectorVar,
                                                                   m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the mean wind speed has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeMeanWindSpeedVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeMeanWindSpeedVectorT) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            bool returnResult = m_sim->computeMeanWindSpeedVectorT(location, m_ResultVectorVar,
                                                                   m_ResultVectorVal, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the mean wind speed has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeModulationValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeModulationValue) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                m_sim->computeModulationValue(location, frequency, time, modulationValue, featureName);
            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the modulation function has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = modulationValue;        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeModulationVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeModulationVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeModulationVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeModulationVectorT) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeModulationVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeModulationVectorF) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            double time = m_sim->getSimulationData()->minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                + m_sim->getSimulationData()->timeIndex.getValue()
                    * m_sim->getSimulationData()->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);

            m_ResultVectorVar.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());
            m_ResultVectorVal.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue());

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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputePeakFactorValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputePeakFactorValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputePeakFactorVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputePeakFactorVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputePeakFactorVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputePeakFactorVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputePDFValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputePDFValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = xValue;
            m_ResultMatrix(0, 1) = PDFValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputePDFVectorX()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputePDFVectorX) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeDecomposedPSDValue()
{
    if (isStopped()) {
        stopped = false;
    }

    stopped = true;
   complete();
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeDecomposedCrossSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeDecomposedCrossSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }


            //get the active simulation


            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeDecomposedCrossSpectrumMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeDecomposedCrossSpectrumMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 5);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeRandomValue()
{
    if (isStopped()) {
        stopped = false;
    }

    stopped = true;
   complete();
    return true;
}
bool RPSWindLabSimulationWorker::workerGenerateRandomMatrixFP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::GenerateRandomMatrixFP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix.resize(m_sim->getSimulationData()->numberOfFrequency.getValue(),
                                  m_sim->getSimulationData()->numberOfSpatialPosition.getValue());
            Base::StopWatch watch;
            watch.start();
            //compute the mean wind velocity vector at all locations
            bool returnResult = m_sim->generateRandomMatrixFP(m_ResultMatrix, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The generation of the random phase angle has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}

bool RPSWindLabSimulationWorker::workerGenerateRandomCubeFPS()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::GenerateRandomCubeFPS) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}


bool RPSWindLabSimulationWorker::workerComputeRoughnessValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeRoughnessValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeRoughnessValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the roughness value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeRoughnessVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeRoughnessVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            returnResult = m_sim->computeRoughnessVectorP(time, m_ResultVectorVar,
                                                          m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the roughness vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeRoughnessVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeRoughnessVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeRoughnessVectorT(locationJ, m_ResultVectorVar,
                                                          m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the roughness vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeShearVelocityOfFlowValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeShearVelocityOfFlowValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
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
                Base::Console().Warning("The computation of the roughness value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeShearVelocityOfFlowVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeShearVelocityOfFlowVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeShearVelocityOfFlowVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerSimulate()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::Simulate) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                Base::Console().Error("The generation of the random wind velocity has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}


bool RPSWindLabSimulationWorker::workerComputeSkewnessValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeSkewnessValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeSkewnessVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeSkewnessVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeSkewnessVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeSkewnessVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeStandardDeviationValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeStandardDeviationValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeStandardDeviationVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeStandardDeviationVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeStandardDeviationVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeStandardDeviationVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerTableToolCompute()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::TableToolCompute) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active feature
            WindLabAPI::IrpsWLTableTool* activefeature = static_cast<WindLabAPI::IrpsWLTableTool*>(
                doc->getObject(m_sim->getSimulationData()->tableTool.getValue()));

            if (!activefeature) {
                Base::Console().Warning("No valid active table tool feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active simulation
            WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(
                WindLabGui::WindLabSimulationObserver::instance()->active());

            if (!sim) {
                Base::Console().Warning("No valid active simulation found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeTurbulenceIntensityValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeTurbulenceIntensityValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeTurbulenceIntensityValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeTurbulenceIntensityVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            returnResult = m_sim->computeTurbulenceIntensityVectorP(time, m_ResultVectorVar,
                                                                    m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the turbulence intensity vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeTurbulenceIntensityVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeTurbulenceIntensityVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeTurbulenceIntensityVectorT(locationJ, m_ResultVectorVar,
                                                                    m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeTurbulenceScaleValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeTurbulenceScaleValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult =
                m_sim->computeTurbulenceScaleValue(locationJ, time, computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the turbulence scale value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeTurbulenceScaleVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeTurbulenceScaleVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            returnResult = m_sim->computeTurbulenceScaleVectorP(time, m_ResultVectorVar,
                                                                m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning(
                    "The computation of the turbulence scale vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeTurbulenceScaleVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeTurbulenceScaleVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeTurbulenceScaleVectorT(locationJ, m_ResultVectorVar,
                                                                m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the skewness vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerUserDefinedRPSObjectCompute()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::UserDefinedRPSObjectCompute) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeVarianceValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeVarianceValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
            m_ResultMatrix.resize(1, 2);
            m_ResultMatrix(0, 0) = time;
            m_ResultMatrix(0, 1) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeVarianceVectorP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeVarianceVectorP) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeVarianceVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeVarianceVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}


bool RPSWindLabSimulationWorker::workerComputeWavePassageEffectValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeWavePassageEffectValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);

            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue.real();
            m_ResultMatrix(0, 3) = computedValue.imag();
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeWavePassageEffectVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeWavePassageEffectVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }


            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeWavePassageEffectVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeWavePassageEffectVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeWavePassageEffectMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeWavePassageEffectMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 5);
    return true;
}


bool RPSWindLabSimulationWorker::workerComputeXCrossSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeXCrossSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeXCrossSpectrumValue(locationJ, locationK, frequency, time,
                                                             computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue.real();
            m_ResultMatrix(0, 3) = computedValue.imag();
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeXCrossSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeXCrossSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(*m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of the location coordinates has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeXCrossSpectrumVectorF(
                locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeXCrossSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeXCrossSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeXCrossSpectrumVectorT(locationJ, locationK, frequency,
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeXCrossSpectrumMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeXCrossSpectrumMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            bool returnResult = m_sim->computeXCrossSpectrumMatrixPP(
                frequency, time, m_ResultMatrix_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 5);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeXAutoSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeXAutoSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeXAutoSpectrumValue(locationJ, frequency, time,
                                                            computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeXAutoSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeXAutoSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeXAutoSpectrumVectorF(locationJ, time, m_ResultVectorVar,
                                                              m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeXAutoSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeXAutoSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeXAutoSpectrumVectorT(
                locationJ, frequency, m_ResultVectorVar, m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeYCrossSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeYCrossSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeYCrossSpectrumValue(locationJ, locationK, frequency, time,
                                                             computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue.real();
            m_ResultMatrix(0, 3) = computedValue.imag();
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeYCrossSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeYCrossSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeYCrossSpectrumVectorF(
                locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeYCrossSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeYCrossSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeYCrossSpectrumVectorT(locationJ, locationK, frequency,
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeYCrossSpectrumMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeYCrossSpectrumMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            bool returnResult = m_sim->computeYCrossSpectrumMatrixPP(
                frequency, time, m_ResultMatrix_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 5);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeYAutoSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeYAutoSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeYAutoSpectrumValue(locationJ, frequency, time,
                                                            computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeYAutoSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeYAutoSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeYAutoSpectrumVectorF(locationJ, time, m_ResultVectorVar,
                                                              m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeYAutoSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeYAutoSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeYAutoSpectrumVectorT(
                locationJ, frequency, m_ResultVectorVar, m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeZCrossSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeZCrossSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeZAutoSpectrumValue(locationJ, frequency, time,
                                                            computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeZCrossSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeZCrossSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeZCrossSpectrumVectorF(
                locationJ, locationK, time, m_ResultVectorVar, m_ResultVectorVal_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeZCrossSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeZCrossSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeZCrossSpectrumVectorT(locationJ, locationK, frequency,
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
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 4);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeZCrossSpectrumMatrixPP()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeZCrossSpectrumMatrixPP) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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
            bool returnResult = m_sim->computeZCrossSpectrumMatrixPP(
                frequency, time, m_ResultMatrix_cx, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInMatrix(m_computingFunction, 5);
    return true;
}

bool RPSWindLabSimulationWorker::workerComputeZAutoSpectrumValue()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeZAutoSpectrumValue) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);

            if (!returnResult) {
                Base::Console().Error("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeZAutoSpectrumValue(locationJ, frequency, time,
                                                            computedValue, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum value has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultMatrix(0, 0) = frequency;
            m_ResultMatrix(0, 1) = time;
            m_ResultMatrix(0, 2) = computedValue;
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 1);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeZAutoSpectrumVectorF()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeZAutoSpectrumVectorF) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeZAutoSpectrumVectorF(locationJ, time, m_ResultVectorVar,
                                                              m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}
bool RPSWindLabSimulationWorker::workerComputeZAutoSpectrumVectorT()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == WindLab::WindLabUtils::ComputeZAutoSpectrumVectorT) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            //get the active location distribution feature
            WindLabAPI::IrpsWLLocationDistribution* activeSpatialDistr =
                static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
                    doc->getObject(m_sim->getSimulationData()->spatialDistribution.getValue()));

            if (!activeSpatialDistr) {
                Base::Console().Error("No valid active location distribution feature found.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            mat locationCoord(m_sim->getSimulationData()->numberOfSpatialPosition.getValue(), 4);
            bool returnResult = activeSpatialDistr->ComputeLocationCoordinateMatrixP3(
                *m_sim->getSimulationData(), locationCoord);
            if (!returnResult) {
                Base::Console().Error("The computation of location coordinates matrix has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
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

            //compute the mean wind velocity vector at all locations
            Base::StopWatch watch;
            watch.start();
            returnResult = m_sim->computeZAutoSpectrumVectorT(
                locationJ, frequency, m_ResultVectorVar, m_ResultVectorVal, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());
            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();
            if (!returnResult) {
                Base::Console().Warning("The computation of the spectrum vector has failed.\n");
                stopped = true;
                failed();
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    signalDisplayResultInTable(m_computingFunction, 2);
    return true;
}

void RPSWindLabSimulationWorker::stop()
{
    mutex.lock();
    stopped = true;
    m_sim->getSimulationData()->isInterruptionRequested.setValue(true);
    m_sim->getSimulationData()->isSimulationSuccessful.setValue(false);
    m_sim->setStatus(App::SimulationStatus::Completed, false);
    m_sim->setStatus(App::SimulationStatus::Running, false);
    m_sim->setStatus(App::SimulationStatus::Stopped, true);
    m_sim->setStatus(App::SimulationStatus::Successfull, false);
    mutex.unlock();
}

void RPSWindLabSimulationWorker::complete()
{
    mutex.lock();
    m_sim->setStatus(App::SimulationStatus::Completed, true);
    m_sim->setStatus(App::SimulationStatus::Running, false);
    m_sim->setStatus(App::SimulationStatus::Stopped, true);
    m_sim->setStatus(App::SimulationStatus::Successfull, true);
    m_sim->getSimulationData()->isInterruptionRequested.setValue(false);
    m_sim->getSimulationData()->isSimulationSuccessful.setValue(true);
    mutex.unlock();
}

void RPSWindLabSimulationWorker::failed()
{
    mutex.lock();
    m_sim->setStatus(App::SimulationStatus::Completed, true);
    m_sim->setStatus(App::SimulationStatus::Running, false);
    m_sim->setStatus(App::SimulationStatus::Stopped, true);
    m_sim->setStatus(App::SimulationStatus::Successfull, false);
    m_sim->getSimulationData()->isInterruptionRequested.setValue(false);
    m_sim->getSimulationData()->isSimulationSuccessful.setValue(false);
    mutex.unlock();
}

bool RPSWindLabSimulationWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}


double RPSWindLabSimulationWorker::getSimulationTime() { return m_simulationTime; }

std::string RPSWindLabSimulationWorker::getComparisonName() const { return m_comparisonName; }
void RPSWindLabSimulationWorker::setComparisonName(std::string name) { m_comparisonName = name; }