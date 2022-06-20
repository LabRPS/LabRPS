#ifndef RPSWINDLABSIMULATIONOUTPUTWORKER_H
#define RPSWINDLABSIMULATIONOUTPUTWORKER_H

#include "RPSWindLabsimuData.h"

#include <QMutex>
#include <QObject>

class RPSWindLabSimulationOutputWorker : public QObject 
{
    Q_OBJECT
 
public:
    RPSWindLabSimulationOutputWorker(CRPSWindLabsimuData windLabData,
                                     QStringList information,
                                     int locationJ,
                                     int locationK,
                                     int frequencyIndex,
                                     int timeIndex);
    ~RPSWindLabSimulationOutputWorker();
    bool isStopped();

public slots:
    void spectrumXModelOut();
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
    void spectrumXModelGraph(mat psdMatrix);
    void finished();
    
public:
    void spectrumXModelOutp();

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
vec dPSDVector;
mat dPSDMatrix;
vec dFrequencyVector;

};

#endif // RPSWINDLABSIMULATIONOUTPUTWORKER_H