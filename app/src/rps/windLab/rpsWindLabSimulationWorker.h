#ifndef RPSWINDLABSIMULATIONWORKER_H
#define RPSWINDLABSIMULATIONWORKER_H

#include "RPSWindLabsimuData.h"

#include <QMutex>
#include <QObject>

class RPSWindLabSimulationWorker : public QObject 
{
    Q_OBJECT
 
public:
    RPSWindLabSimulationWorker(CRPSWindLabsimuData windLabData, QStringList information);
    ~RPSWindLabSimulationWorker();
    bool isStopped();

public slots:
    void simulate();
    void stop();
    void progressBarMinMaxValue();


signals:
    void sendInformation(QStringList infoList);
    void progressBarShow();
    void progressBarHide();
    void progressBarSetValue(int value);
    void progressBarSetMin(int value);
    void progressBarSetMax(int value);
    void progressBarReset();
    
private:
    CRPSWindLabsimuData m_windLabData;
    QStringList m_information;
    QMutex mutex;
    bool stopped;
    int minStep;
    int maxStep;
    int currentStep;
    int maxStepOld;
};

#endif // RPSWINDLABSIMULATIONWORKER_H