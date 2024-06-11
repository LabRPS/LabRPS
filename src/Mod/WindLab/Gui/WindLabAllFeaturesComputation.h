#ifndef RPSWINDLABALLFEATURECOMPUTATION_H
#define RPSWINDLABALLFEATURECOMPUTATION_H

#include <QObject>
#include <QComboBox>
#include <QThread>
#include <QTimer>

#include <Mod/WindLab/App/WindLabSimulation.h>
#include "WindLabSimulationWorker.h"

namespace WindLabGui
{

class WindLabAllFeaturesComputation: public QObject
{
    Q_OBJECT

public:
    WindLabAllFeaturesComputation(WindLab::WindLabSimulation* sim, QObject* parent = nullptr);
    ~WindLabAllFeaturesComputation();
   
Q_SIGNALS:
    void stopped();

public Q_SLOTS:

    // // simulation
    //void runSimulation();
    //void pauseSimulation();
    //void stopSimulation();
    //void simulationOptions();
    //void runTableTool(const mat &table);
    //void runMatrixTool(const mat &matrix);

    //void receiveInformation(QStringList infoList);
    //void progressBarShowSL();
    //void progressBarHideSL();
    //void progressBarSetValueSL(int value);
    //void progressBarSetMinSL(int value);
    //void progressBarSetMaxSL(int value);
    //void progressBarResetSL();
    void slotDisplayResultInTable(QString str, int what);
    void slotDisplayResultInMatrix(QString str, int what);

 
private:
    //// wind velocity simulation 
    WindLab::WindLabSimulation* m_sim;

    QThread* simulationThread = nullptr;
    RPSWindLabSimulationWorker* simulationWorker = nullptr;

public:
    int complexRrealImag;

public:
    //WindLabAPI::WindLabSimuData* GetWindLabData();
    RPSWindLabSimulationWorker *GetWindLabSimulationWorker();
    QThread* getWindLabSimulationThread();
    QString logSimulationInfo(bool status, const QString& name);
    void startSimulationWorker(QString function, const char* complexNumberDisplay = "Real");
    void setComplexNumberDisplay(const char* displayType);
};

}//namespace WindLabGui


#endif// RPSWINDLABSIMULATIONWORKER_H
