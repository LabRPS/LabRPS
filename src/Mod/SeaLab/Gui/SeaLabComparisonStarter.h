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

#ifndef RPSSEALABCOMPARISONSTARTER_H
#define RPSSEALABCOMPARISONSTARTER_H

#include <QObject>
#include <QComboBox>
#include <QThread>
#include <QTimer>

#include <Mod/SeaLab/App/SeaLabSimulation.h>
#include "SeaLabSimulationWorker.h"

namespace SeaLabGui
{

class SeaLabComparisonStarter: public QObject
{
    Q_OBJECT

public:
    SeaLabComparisonStarter(SeaLab::SeaLabSimulation* sim1, SeaLab::SeaLabSimulation* sim2, std::string comparisonName, QObject* parent = nullptr);
    ~SeaLabComparisonStarter();
   
Q_SIGNALS:
    void stopped();

public Q_SLOTS:

    void slotDisplayResultInTable(QString str, int what);
    void slotDisplayResultInMatrix(QString str, int what);
    void slotDisplayResultInTable1(QString str, int what);
    void slotDisplayResultInMatrix1(QString str, int what);
    void slotDisplayResultInTable2(QString str, int what);
    void slotDisplayResultInMatrix2(QString str, int what);

private:
    //// Seismic Ground Motion simulation 
    SeaLab::SeaLabSimulation* m_sim1;
    SeaLab::SeaLabSimulation* m_sim2;
    std::string m_comparisonName;

    QThread* simulationThread1 = nullptr;
    QThread* simulationThread2 = nullptr;

    RPSSeaLabSimulationWorker* simulationWorker1 = nullptr;
    RPSSeaLabSimulationWorker* simulationWorker2 = nullptr;

public:
    int complexRrealImag;

public:
    RPSSeaLabSimulationWorker *GetSeaLabSimulationWorker1();
    RPSSeaLabSimulationWorker* GetSeaLabSimulationWorker2();
    std::string getComparisonName();
    QThread* getSeaLabSimulationThread1();
    QThread* getSeaLabSimulationThread2();

    QString logSimulationInfo(bool status, const QString& name);
    void startSimulationWorker(QString function, const char* complexNumberDisplay = "Real");
    void setComplexNumberDisplay(const char* displayType);
};

}//namespace SeaLabGui


#endif// RPSSEALABSIMULATIONWORKER_H
