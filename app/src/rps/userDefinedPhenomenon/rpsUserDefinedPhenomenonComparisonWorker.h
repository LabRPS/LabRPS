#ifndef RPSUSERDEFINEDPHENOMENONCOMPARISONWORKER_H
#define RPSUSERDEFINEDPHENOMENONCOMPARISONWORKER_H

#include "RPSUserDefinedPhenomenonSimuData.h"

#include <QMutex>
#include <QObject>

class RPSUserDefinedPhenomenonComparisonWorker : public QObject 
{
    Q_OBJECT

public:
    RPSUserDefinedPhenomenonComparisonWorker(CRPSUserDefinedPhenomenonSimuData userDefinedPhenomenonData,
                               QStringList information,
                               int phenomenonIndex,
                               int indexSetIndex,
                               std::vector<QString> candidateList,
                               int resultOutputType,
                               int minNumberOfProcess,
                               int minNumberOfIndexSetIndex,
                               int minNumberOfSample,
                               int numberOfProcessIncrement,
                               int numberOfIndexSetIndexIncrement,
                               int numberOfSampleIncrement,
                               int totalNumber,
                               QString userDefinedPhenomenon);


    ~RPSUserDefinedPhenomenonComparisonWorker();
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
void saveComputationTimeConsumption();

void sendInformation(QStringList infoList);
void progressBarShow();
void progressBarHide();
void progressBarSetValue(int value);
void progressBarSetMin(int value);
void progressBarSetMax(int value);
void progressBarReset();
void finished();

public:
void workerComparing();
void accuracyOutp();
void timeOutp();
void memoryOutp();

void Simulate(const QString &name, mat &result, int &time, int &memory, QStringList &information);
void SimulateInLargeScaleMode(const QString &name, QString &strFileName, int &time, int &memory, QStringList &information);

void fillVectorWithNumbers(vec &vector, const int &row);
void fillVectorWithTimeIncrements(vec &vector);

void setOjectDependencyForCanditate1();
void setOjectDependencyForCanditate2();

private:
    CRPSUserDefinedPhenomenonSimuData m_userDefinedPhenomenonData;
    QStringList m_information;
    QMutex mutex;
    bool stopped;
    int minStep;
    int maxStep;
    int currentStep;
    int maxStepOld;

    int m_phenomenonIndex;
    int m_indexSetIndex;

  std::vector<QString> m_candidateList;
  int m_resultOutputType;
  int m_minNumberOfProcess;
  int m_minNumberOfIndexSetIndex;
  int m_minNumberOfSample;
  int m_numberOfProcessIncrement;
  int m_numberOfIndexSetIndexIncrement;
  int m_numberOfSampleIncrement;
  int m_totalNumber;

    QString m_userDefinedPhenomenon;


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

    QString windVelocityFileName1;
    QString windVelocityFileName2;

//    std::vector<int> m_resultVectorVariableVec;
//    std::vector<int> m_resultVectorCandidate1Vec;
//    std::vector<int> m_resultVectorCandidate2Vec;


public:
    QStringList getInformation();
};

#endif // RPSUSERDEFINEDPHENOMENONCOMPARISONWORKER_H
