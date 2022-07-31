#ifndef RPSWINDLABCOMPARISONWORKER_H
#define RPSWINDLABCOMPARISONWORKER_H

#include "RPSWindLabsimuData.h"

#include <QMutex>
#include <QObject>

class RPSWindLabComparisonWorker : public QObject 
{
    Q_OBJECT
 
public:
    RPSWindLabComparisonWorker(CRPSWindLabsimuData windLabData,
                                     QStringList information,
                                     int locationJ,
                                     int locationK,
                                     int frequencyIndex,
                                     int timeIndex,
                                     std::vector<QString> candidateList);
    ~RPSWindLabComparisonWorker();
    bool isStopped();

public slots:
    void compareAccuracy();
    void compareTime();
    void compareMemory();

    void stop();
    void progressBarMinMaxValue();


signals:
    void showAccuracyComparisonOutput();
    void showTimeComparisonOutput();
    void showMemoryComparisonOutput();

    void sendInformation(QStringList infoList);
    void progressBarShow();
    void progressBarHide();
    void progressBarSetValue(int value);
    void progressBarSetMin(int value);
    void progressBarSetMax(int value);
    void progressBarReset();
    void finished();

public:
void accuracyOutp();
void timeOutp();
void memoryOutp();

void ComputeFrequenciesVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeCrossCoherenceVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeMeanWindSpeedVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeMeanWindSpeedVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeModulationVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeModulationVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeModulationVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeDecomposedCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeDecomposedCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeDecomposedCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeXCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeXCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeXCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeYCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeYCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeYCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeZCrossSpectrumVectorF(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeZCrossSpectrumVectorT(const QString &name, vec &result, int &time, int &memory, QStringList &information);
void ComputeZCrossSpectrumVectorP(const QString &name, vec &result, int &time, int &memory, QStringList &information);

void fillVectorWithNumbers(vec &vector, const int &row);
void fillVectorWithTimeIncrements(vec &vector);

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

  std::vector<QString> m_candidateList;


public:
    vec m_resultVectorVariable;
    vec m_resultVectorCandidate1;
    vec m_resultVectorCandidate2;

    mat m_resultCandidate1;
    mat m_resultCandidate2;

    int computationTime1;
    int computationTime2;

    int memoryConsumption1;
    int memoryConsumption2;

public:
    QStringList getInformation();
};

#endif // RPSWINDLABCOMPARISONWORKER_H