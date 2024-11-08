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
#include <Mod/UserLab/App/UserLabSimulationComparison.h>
#include <Mod/UserLab/App/UserLabSimulation.h>
#include <QThread>
#include <QTime>


using namespace UserLabGui;

RPSUserLabSimulationWorker::RPSUserLabSimulationWorker(UserLab::UserLabSimulation* sim) : m_sim(sim)
{
    m_sim->getSimulationData()->isInterruptionRequested.setValue(false);
    stopped = true;
}

RPSUserLabSimulationWorker::~RPSUserLabSimulationWorker() {}
void RPSUserLabSimulationWorker::setComputationTime()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return;
    auto obj = doc->getObject(m_comparisonName.c_str());
    UserLab::UserLabSimulationComparison* comp = static_cast<UserLab::UserLabSimulationComparison*>(obj);
    if (!comp)
        return;
    std::string simName = static_cast<App::DocumentObject*>(m_sim)->getNameInDocument();

    if (strcmp(simName.c_str(), comp->SimulationCandidate1.getValue()) == 0) {
        comp->ComputationTime1.setValue(m_simulationTime);
    }
    else if (strcmp(simName.c_str(), comp->SimulationCandidate2.getValue()) == 0) {
        comp->ComputationTime2.setValue(m_simulationTime);
    }

    m_sim->getSimulationData()->comparisonMode.setValue(false);
}

bool RPSUserLabSimulationWorker::workerSimulate()
{
    if (isStopped()) {
        stopped = false;
        if (m_computingFunction == UserLab::UserLabUtils::Simulate) {
            //get the active document
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc)
                return false;

            m_ResultMatrix.resize(m_sim->getSimulationData()->numberOfTimeIncrements.getValue(),
                                  m_sim->getSimulationData()->numberOfSpatialPosition.getValue()
                                      + 1);
            m_ResultMatrix.setZero();
            Base::StopWatch watch;
            watch.start();
            bool returnResult = m_sim->simulate(m_ResultMatrix, featureName);

            m_simulationTime = watch.elapsed();
            std::string str = watch.toString(m_simulationTime);
            Base::Console().Message("The computation %s\n", str.c_str());

            if (m_sim->getSimulationData()->comparisonMode.getValue())
                setComputationTime();

            if (!returnResult) {
                Base::Console().Error("The computation of the wind velocity matrix has failed.\n");
                return false;
            }

            signalDisplayResultInTable(QString::fromLatin1(featureName.c_str()), 1);
        }
    }

    stopped = true;
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
                return false;
            }
        }
    }

    stopped = true;
    return true;
}

void RPSUserLabSimulationWorker::stop()
{
    mutex.lock();
    stopped = true;
    m_sim->getSimulationData()->isInterruptionRequested.setValue(true);
    m_sim->getSimulationData()->isSimulationSuccessful.setValue(false);
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