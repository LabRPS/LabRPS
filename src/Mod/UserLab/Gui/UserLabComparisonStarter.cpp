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

#include "UserLabComparisonStarter.h"
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

UserLabComparisonStarter::UserLabComparisonStarter(UserLab::UserLabSimulation* sim1,UserLab::UserLabSimulation* sim2, std::string comparisonName, QObject* parent)
    : m_sim1(sim1), m_sim2(sim2), m_comparisonName(comparisonName), QObject(parent)
{ 
}

UserLabComparisonStarter::~UserLabComparisonStarter()
{
    
}

RPSUserLabSimulationWorker *UserLabComparisonStarter::GetUserLabSimulationWorker1()
{
    return simulationWorker1;
}

RPSUserLabSimulationWorker* UserLabComparisonStarter::GetUserLabSimulationWorker2()
{
    return simulationWorker2;
}

QThread* UserLabComparisonStarter::getUserLabSimulationThread1()
{ 
    return simulationThread1; 
}

QThread* UserLabComparisonStarter::getUserLabSimulationThread2() 
{ 
    return simulationThread2; 
}

std::string UserLabComparisonStarter::getComparisonName()
{ return m_comparisonName; }

QString UserLabComparisonStarter::logSimulationInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = QString::fromLatin1("<b>[") + dt.toString(Qt::LocalDate) + QString::fromLatin1("&emsp;") +
            QString::fromLatin1(": ''") + name + QString::fromLatin1("'']</b><hr>");


    UserLab::UserLabUtils::TableColorProfile profile =
        UserLab::UserLabUtils::TableColorProfile::Success;
    
    if (status != true)
        profile = UserLab::UserLabUtils::TableColorProfile::Failure;

    QString table;
    table = UserLab::UserLabUtils::makeHtmlTable(7, 3, false, profile);

    table = table.arg(tr("Computation Time"), QString::number(GetUserLabSimulationWorker1()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"), QString::number(GetUserLabSimulationWorker2()->getSimulationTime()/1000) + QString::fromLatin1(" seconds"));
    table = table.arg(tr("Simulation Method"), QString::fromLatin1(m_sim1->getSimulationData()->simulationMethod.getValue()),QString::fromLatin1(m_sim2->getSimulationData()->simulationMethod.getValue()));
   
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



void UserLabComparisonStarter::startSimulationWorker(QString function, const char* complexNumberDisplay)
{
    // create a worker
    simulationWorker1 = new RPSUserLabSimulationWorker(m_sim1);
    simulationWorker2 = new RPSUserLabSimulationWorker(m_sim2);

    simulationWorker1->setComparisonName(m_comparisonName);
    simulationWorker2->setComparisonName(m_comparisonName); 

    setComplexNumberDisplay(complexNumberDisplay);

    // create a new thread and attach the worker to it
    simulationThread1 = new QThread(this);
    simulationThread2 = new QThread(this);

    simulationWorker1->moveToThread(simulationThread1);
    simulationWorker2->moveToThread(simulationThread2);


    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), simulationWorker1, SLOT(RPSUserLabSimulationWorker::stop()), Qt::DirectConnection);
    connect(this, SIGNAL(stopped()), simulationWorker2, SLOT(RPSUserLabSimulationWorker::stop()), Qt::DirectConnection);


    // add the functionaly to delete the worker after work is done
    connect(simulationWorker1, SIGNAL(finished()), simulationWorker1, SLOT(deleteLater()));
    connect(simulationWorker1, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker1, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));

    connect(simulationWorker2, SIGNAL(finished()), simulationWorker2, SLOT(deleteLater()));
    connect(simulationWorker2, SIGNAL(signalDisplayResultInTable(QString, int)), this, SLOT(slotDisplayResultInTable(QString, int)));
    connect(simulationWorker2, SIGNAL(signalDisplayResultInMatrix(QString, int)), this, SLOT(slotDisplayResultInMatrix(QString, int)));
    
    //QString function = simulationWorker->getComputingFunction();
    
 if(function == UserLab::UserLabUtils::Simulate)
        {
            simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerSimulate()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerSimulate()));
        }
    else if(function == UserLab::UserLabUtils::SimulateInLargeScaleMode) {
        simulationWorker1->setComputingFunction(function);
        simulationWorker2->setComputingFunction(function);
        connect(simulationThread1, SIGNAL(started()), simulationWorker1, SLOT(workerSimulateInLargeScaleMode()));
        connect(simulationThread2, SIGNAL(started()), simulationWorker2, SLOT(workerSimulateInLargeScaleMode()));
    }

    QProgressBar* bar = Gui::SequencerBar::instance()->getProgressBar();
    bar->setRange(0, 100);
    bar->show();
    Gui::getMainWindow()->showMessage(tr("Loading %1...").arg(QString::fromLatin1(simulationWorker2->getComparisonName().c_str())));

}

void UserLabComparisonStarter::slotDisplayResultInTable(QString str, int what)
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

void UserLabComparisonStarter::slotDisplayResultInMatrix(QString str, int what)
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

void UserLabComparisonStarter::slotDisplayResultInTable1(QString str, int what)
{
    slotDisplayResultInTable(str, what);
}
void UserLabComparisonStarter::slotDisplayResultInMatrix1(QString str, int what)
{
    slotDisplayResultInMatrix(str, what);
}
void UserLabComparisonStarter::slotDisplayResultInTable2(QString str, int what)
{
    slotDisplayResultInTable(str, what);
}
void UserLabComparisonStarter::slotDisplayResultInMatrix2(QString str, int what)
{
    slotDisplayResultInMatrix(str, what);
}

void UserLabComparisonStarter::setComplexNumberDisplay(const char* displayType)
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