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

#include "UserLabAllFeaturesComputation.h"
#include <Mod/UserLab/App/UserLabUtils.h>
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

using namespace UserLabGui;

UserLabAllFeaturesComputation::UserLabAllFeaturesComputation(UserLab::UserLabSimulation* sim, QObject* parent)
    : m_sim(sim), QObject(parent)
{ 
}

UserLabAllFeaturesComputation::~UserLabAllFeaturesComputation()
{
    
}

RPSUserLabSimulationWorker *UserLabAllFeaturesComputation::GetUserLabSimulationWorker()
{
    return simulationWorker;
}

QThread* UserLabAllFeaturesComputation::getUserLabSimulationThread()
{ return simulationThread; }


QString UserLabAllFeaturesComputation::logSimulationInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = QString::fromLatin1("<b>[") + dt.toString(Qt::LocalDate) + QString::fromLatin1("&emsp;") +
            QString::fromLatin1(": ''") + name + QString::fromLatin1("'']</b><hr>");


    UserLab::UserLabUtils::TableColorProfile profile =
        UserLab::UserLabUtils::TableColorProfile::Success;
    
    if (status != true)
        profile = UserLab::UserLabUtils::TableColorProfile::Failure;

    QString table;
    table = UserLab::UserLabUtils::makeHtmlTable(7, 2, false, profile);

    table = table.arg(tr("Computation Time"), QString::number(GetUserLabSimulationWorker()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"));
    table = table.arg(tr("Simulation Method"), QString::fromLatin1(m_sim->getSimulationData()->simulationMethod.getValue()));
    
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



void UserLabAllFeaturesComputation::startSimulationWorker(QString function, const char* complexNumberDisplay)
{
    // create the worker
    simulationWorker = new RPSUserLabSimulationWorker(m_sim);

    setComplexNumberDisplay(complexNumberDisplay);

    // create a new thread and attach the worker to it
    simulationThread = new QThread(this);
    simulationWorker->moveToThread(simulationThread);


    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), simulationWorker, SLOT(RPSUserLabSimulationWorker::stop()), Qt::DirectConnection);
    connect(simulationWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
    connect(simulationWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
    connect(simulationWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

    // add the functionaly to delete the worker after work is done
    connect(simulationWorker, SIGNAL(finished()), simulationWorker, SLOT(deleteLater()));
    connect(simulationWorker, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));

    
    if(function == UserLab::UserLabUtils::Simulate)
        {
            simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerSimulate()));
        }
    else if(function == UserLab::UserLabUtils::SimulateInLargeScaleMode) {
        simulationWorker->setComputingFunction(function);
        connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(workerSimulateInLargeScaleMode()));
    }
    
    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setRange(0, 100);
    bar->show();
    Gui::getMainWindow()->showMessage(tr("Loading %1...").arg(QString::fromLatin1(simulationWorker->getComparisonName().c_str())));

}

void UserLabAllFeaturesComputation::slotDisplayResultInTable(QString str, int what)
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
    QString info = logSimulationInfo(true, QString::fromLatin1("hahaha"));

    Gui::getMainWindow()->showResults(info);
}

void UserLabAllFeaturesComputation::slotDisplayResultInMatrix(QString str, int what)
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

void UserLabAllFeaturesComputation::setComplexNumberDisplay(const char* displayType)
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