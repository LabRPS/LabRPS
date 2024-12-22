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
#include "UserLabSimulationWorker.h"
#include <App/Application.h>
#include <App/Document.h>
#include <Mod/UserLab/App/UserLabUtils.h>
#include <Mod/UserLabAPI/App/RPSUserLabAPI.h>

#include <Base/Tools.h>
#include <Mod/UserLab/App/UserLabSimulation.h>
#include <Mod/UserLab/Gui/UserLabSimulationObserver.h>


#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <Mod/UserLab/App/UserLabSimulation.h>
#include <QThread>
#include <QTime>


using namespace UserLabGui;

RPSUserLabSimulationWorker::RPSUserLabSimulationWorker(UserLab::UserLabSimulation* sim) : m_sim(sim)
{
    m_sim->getSimulationData()->isInterruptionRequested.setValue(false);
    stopped = true;
    m_simulationTime = 0.0;
}

RPSUserLabSimulationWorker::~RPSUserLabSimulationWorker() {}
void RPSUserLabSimulationWorker::setComputationTime()
{

}

bool RPSUserLabSimulationWorker::workerSimulate()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == UserLab::UserLabUtils::Simulate) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
            {
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }

            m_ResultCube.resize(m_sim->getSimulationData()->numberOfSpatialCoordinateIncrement.getValue(),
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
bool RPSUserLabSimulationWorker::workerSimulateInLargeScaleMode()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == UserLab::UserLabUtils::SimulateInLargeScaleMode) {

            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
                return false;

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
                    "The computation of the wind velocity matrix has failed.\n");
                stopped = true;
                m_sim->setStatus(App::SimulationStatus::Failed, true);
                signalDisplayResultInTable(m_computingFunction, 0);
                return false;
            }
        }
    }

    stopped = true;
    complete();
    return true;
}

void RPSUserLabSimulationWorker::stop()
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

void RPSUserLabSimulationWorker::complete()
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

bool RPSUserLabSimulationWorker::isStopped()
{
    bool stopped;
    mutex.lock();
    stopped = this->stopped;
    mutex.unlock();
    return stopped;
}


double RPSUserLabSimulationWorker::getSimulationTime() { return m_simulationTime; }

std::string RPSUserLabSimulationWorker::getComparisonName() const { return m_comparisonName; }
void RPSUserLabSimulationWorker::setComparisonName(std::string name) { m_comparisonName = name; }