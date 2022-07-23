#ifndef RPSWINDLABSIMULATIONWORKER_H
#define RPSWINDLABSIMULATIONWORKER_H

#include "RPSWindLabsimuData.h"

#include <QMutex>
#include <QObject>

class RPSWindLabSimulationWorker : public QObject 
{
    Q_OBJECT
 
public:
    RPSWindLabSimulationWorker(CRPSWindLabsimuData windLabData,
                                     QStringList information,
                                     int locationJ,
                                     int locationK,
                                     int frequencyIndex,
                                     int timeIndex);
    ~RPSWindLabSimulationWorker();
    bool isStopped();

public slots:
    void simulate();
    void stop();
    void progressBarMinMaxValue();


signals:
    void showWindVelocityOutput();
    void sendInformation(QStringList infoList);
    void progressBarShow();
    void progressBarHide();
    void progressBarSetValue(int value);
    void progressBarSetMin(int value);
    void progressBarSetMax(int value);
    void progressBarReset();
    void finished();

public:
void windVelocityOutp();
    
private:
    CRPSWindLabsimuData m_windLabData;
    QStringList m_information;
    QMutex mutex;
    bool stopped;
    int minStep;
    int maxStep;
    int currentStep;
    int maxStepOld;

    int m_locationJ;
    int m_locationK;
    int m_frequencyIndex;
    int m_timeIndex;

public:
    vec m_ResultVector;
    vec m_ResultVector2;

    mat m_ResultMatrix;
    mat m_ResultMatrix2;

public:
    QStringList getInformation();
};

#endif // RPSWINDLABSIMULATIONWORKER_H