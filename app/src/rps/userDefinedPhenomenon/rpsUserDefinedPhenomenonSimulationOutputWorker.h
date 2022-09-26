#ifndef RPSUSERDEFINEDPHENOMENONSIMULATIONOUTPUTWORKER_H
#define RPSUSERDEFINEDPHENOMENONSIMULATIONOUTPUTWORKER_H

#include "RPSUserDefinedPhenomenonSimuData.h"

#include <QMutex>
#include <QObject>

class RPSUserDefinedPhenomenonSimulationOutputWorker : public QObject
{
    Q_OBJECT

public:
    RPSUserDefinedPhenomenonSimulationOutputWorker(CRPSUserDefinedPhenomenonSimuData simuData,
                                     QStringList information,
                                     int phenomenonIndex,
                                     int indexSetIndex);
    ~RPSUserDefinedPhenomenonSimulationOutputWorker();
    bool isStopped();

public slots:

    void stop();
    void progressBarMinMaxValue();

    // output
    void userDefinedPhenomenonOut();

signals:
    void sendInformation(QStringList infoList);
    void progressBarShow();
    void progressBarHide();
    void progressBarSetValue(int value);
    void progressBarSetMin(int value);
    void progressBarSetMax(int value);
    void progressBarReset();
    void finished();

public:
    // output
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

#endif // RPSUSERDEFINEDPHENOMENONSIMULATIONOUTPUTWORKER_H
