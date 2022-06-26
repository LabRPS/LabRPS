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

    void stop();
    void progressBarMinMaxValue();

    // output
    void windVelocityOut();
    void frequencyDistributionOut();
    void locationDistributionOut();
    void spectrumXModelOut();
    void spectrumYModelOut();
    void spectrumZModelOut();
    void coherenceOut();
    void correlationOut();
    void modulationOut();
    void meanWindVelocityOut();

signals:
    void sendInformation(QStringList infoList);
    void progressBarShow();
    void progressBarHide();
    void progressBarSetValue(int value);
    void progressBarSetMin(int value);
    void progressBarSetMax(int value);
    void progressBarReset();
    void finished();

    // output
    void showWindVelocityOutput();
    void showFrequencyDistributionOutput();
    void showLocationDistributionOutput();
    void showXSpectrumOutput();
    void showYSpectrumOutput();
    void showZSpectrumOutput();
    void showCoherenceOutput();
    void showCorrelationOutput();
    void showModulationOutput();
    void showMeanWindVelocityOutput();

public:
    // output
    void windVelocityOutp();
    void frequencyDistributionOutp();
    void locationDistributionOutp();
    void spectrumXModelOutp();
    void spectrumYModelOutp();
    void spectrumZModelOutp();
    void coherenceOutp();
    void correlationOutp();
    void modulationOutp();
    void meanWindVelocityOutp();

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

public:
    QStringList getInformation();
};

#endif // RPSWINDLABSIMULATIONOUTPUTWORKER_H