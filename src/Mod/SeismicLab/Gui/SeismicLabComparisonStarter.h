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

#ifndef RPSSEISMICLABCOMPARISONSTARTER_H
#define RPSSEISMICLABCOMPARISONSTARTER_H

#include <QObject>
#include <QComboBox>
#include <QThread>
#include <QTimer>

#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include "SeismicLabSimulationWorker.h"

namespace SeismicLabGui
{

class SeismicLabComparisonStarter: public QObject
{
    Q_OBJECT

public:
    SeismicLabComparisonStarter(SeismicLab::SeismicLabSimulation* sim1, SeismicLab::SeismicLabSimulation* sim2, std::string comparisonName, QObject* parent = nullptr);
    ~SeismicLabComparisonStarter();
   
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
    SeismicLab::SeismicLabSimulation* m_sim1;
    SeismicLab::SeismicLabSimulation* m_sim2;
    std::string m_comparisonName;

    QThread* simulationThread1 = nullptr;
    QThread* simulationThread2 = nullptr;

    RPSSeismicLabSimulationWorker* simulationWorker1 = nullptr;
    RPSSeismicLabSimulationWorker* simulationWorker2 = nullptr;

public:
    int complexRrealImag;

public:
    RPSSeismicLabSimulationWorker *GetSeismicLabSimulationWorker1();
    RPSSeismicLabSimulationWorker* GetSeismicLabSimulationWorker2();
    std::string getComparisonName();
    QThread* getSeismicLabSimulationThread1();
    QThread* getSeismicLabSimulationThread2();

    QString logSimulationInfo(bool status, const QString& name);
    void startSimulationWorker(QString function, const char* complexNumberDisplay = "Real");
    void setComplexNumberDisplay(const char* displayType);
};

}//namespace SeismicLabGui


#endif// RPSSEISMICLABSIMULATIONWORKER_H
