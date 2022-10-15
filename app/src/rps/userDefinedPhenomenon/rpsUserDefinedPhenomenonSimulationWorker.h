#ifndef RPSUSERDEFINEDPHENOMENONSIMULATIONWORKER_H
#define RPSUSERDEFINEDPHENOMENONSIMULATIONWORKER_H

#include "RPSUserDefinedPhenomenonSimuData.h"

#include <QMutex>
#include <QObject>

class RPSUserDefinedPhenomenonSimulationWorker : public QObject 
{
    Q_OBJECT
 
public:
    RPSUserDefinedPhenomenonSimulationWorker(CRPSUserDefinedPhenomenonSimuData simuData,
                                     QStringList information,
                                     int phenomenonIndex,
                                     int indexSetIndex);
    ~RPSUserDefinedPhenomenonSimulationWorker();
    bool isStopped();

public slots:
    void simulate();
    void stop();
    void progressBarMinMaxValue();


signals:
    void showUserDefinedPhenomenonOutput();
    void sendInformation(QStringList infoList);
    void progressBarShow();
    void progressBarHide();
    void progressBarSetValue(int value);
    void progressBarSetMin(int value);
    void progressBarSetMax(int value);
    void progressBarReset();
    void finished();

public:
void userDefinedPhenomenonOutp();
    
private:
    CRPSUserDefinedPhenomenonSimuData m_simuData;
    QStringList m_information;
    QMutex mutex;
    bool stopped;
    int minStep;
    int maxStep;
    int currentStep;
    int maxStepOld;

    int m_phenomenonIndex;
    int m_indexSetIndex;

public:
    vec m_ResultVector;

    mat m_ResultMatrix;

public:
    QStringList getInformation();
};

#endif // RPSUSERDEFINEDPHENOMENONSIMULATIONWORKER_H
