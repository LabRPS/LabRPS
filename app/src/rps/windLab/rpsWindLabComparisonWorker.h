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
                               std::vector<QString> candidateList,
                               int resultOutputType,
                               int minNumberOfLocation,
                               int minNumberOfFrequency,
                               int minNumberOfTime,
                               int numberOfLocationIncrement,
                               int numberOfFrequencyIncrement,
                               int numberOfTimeIncrement,
                               int totalNumber,
                               QString coherence,
                               QString correlation,
                               QString frequency,
                               QString mean,
                               QString modulation,
                               QString decomposition,
                               QString simulation,
                               QString spatial,
                               QString randomness,
                               QString spectrum,
                                  QString cumulativeProbabilityDistribution,
   QString gustFactor,
   QString kurtosis,
   QString peakFactor,
   QString probabilityDensityFunction,
   QString roughness,
   QString shearVelocityOfFlow,
   QString skewness,
   QString standardDeviation,
   QString turbulenceIntensity,
   QString turbulenceScale,
   QString variance,
   QString wavePassageEffect);


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

void ComputeFrequenciesVectorF(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeCrossCoherenceVectorF(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeCrossCoherenceVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeMeanWindSpeedVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeMeanWindSpeedVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeModulationVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeModulationVectorF(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeModulationVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeDecomposedCrossSpectrumVectorF(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeDecomposedCrossSpectrumVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeDecomposedCrossSpectrumVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeXCrossSpectrumVectorF(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeXCrossSpectrumVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeXCrossSpectrumVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeYCrossSpectrumVectorF(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeYCrossSpectrumVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeYCrossSpectrumVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeZCrossSpectrumVectorF(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeZCrossSpectrumVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);
void ComputeZCrossSpectrumVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information);

void ComputeCDFVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeGustFactorVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeKurtosisVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputePeakFactorVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputePDFVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeRoughnessVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeShearVelocityOfFlowVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeSkewnessVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeStandardDeviationVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeTurbulenceIntensityVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeTurbulenceScaleVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeVarianceVectorP(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeWavePassageEffectVectorF(const QString &name, vec &resultVar, cx_vec &result, int &time, int &memory, QStringList &information);
void ComputeWavePassageEffectVectorT(const QString &name, vec &resultVar, cx_vec &result, int &time, int &memory, QStringList &information);

void ComputeGustFactorVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeKurtosisVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputePeakFactorVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeRoughnessVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeShearVelocityOfFlowVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeSkewnessVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeStandardDeviationVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeTurbulenceIntensityVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeTurbulenceScaleVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;
void ComputeVarianceVectorT(const QString &name, vec &resultVar, vec &result, int &time, int &memory, QStringList &information) ;

void Simulate(const QString &name, mat &result, int &time, int &memory, QStringList &information);
void SimulateInLargeScaleMode(const QString &name, QString &strFileName, int &time, int &memory, QStringList &information);

void fillVectorWithNumbers(vec &vector, const int &row);
void fillVectorWithTimeIncrements(vec &vector);

void setOjectDependencyForCanditate1();
void setOjectDependencyForCanditate2();

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


  int m_resultOutputType;
  int m_minNumberOfLocation;
  int m_minNumberOfFrequency;
  int m_minNumberOfTime;
  int m_numberOfLocationIncrement;
  int m_numberOfFrequencyIncrement;
  int m_numberOfTimeIncrement;
  int m_totalNumber;

    QString m_coherence;
    QString m_correlation;
    QString m_frequency;
    QString m_mean;
    QString m_modulation;
    QString m_decomposition;
    QString m_simulation;
    QString m_spatial;
    QString m_randomness;
    QString m_spectrum;
    QString m_cumulativeProbabilityDistribution;
   QString m_gustFactor;
   QString m_kurtosis;
   QString m_peakFactor;
   QString m_probabilityDensityFunction;
   QString m_roughness;
   QString m_shearVelocityOfFlow;
   QString m_skewness;
   QString m_standardDeviation;
   QString m_turbulenceIntensity;
   QString m_turbulenceScale;
   QString m_variance;
   QString m_wavePassageEffect;


public:

    std::vector<QString> m_candidateList;

    vec m_locationVectorVariable;
    vec m_frequencyVectorVariable;
    vec m_timeVectorVariable;
    vec m_computationTimeResultVectorCandidate1;
    vec m_computationTimeResultVectorCandidate2;

    vec m_memoryComsumptionResultVectorVariable;
    vec m_memoryComsumptionResultVectorCandidate1;
    vec m_memoryComsumptionResultVectorCandidate2;

    vec m_resultValueResultVectorCandidate1Variable;
    vec m_resultValueResultVectorCandidate2Variable;

    vec m_resultValueResultVectorCandidate1;
    vec m_resultValueResultVectorCandidate2;

    cx_vec m_resultValueResultVectorCandidate1_xc;
    cx_vec m_resultValueResultVectorCandidate2_xc;

    mat m_resultValueMatrixCandidate1;
    mat m_resultValueMatrixCandidate2;

    int computationTime1;
    int computationTime2;

    int memoryConsumption1;
    int memoryConsumption2;

    QString windVelocityFileName1;
    QString windVelocityFileName2;

    double accuracy;
    bool isComparisonSuccessful;
    bool iscomputationSuccessful;

//   std::vector<int> m_resultVectorVariableVec;
//   std::vector<int> m_resultVectorCandidate1Vec;
//   std::vector<int> m_resultVectorCandidate2Vec;


public:
    QStringList getInformation();
    double computeAccuracyValue();
};

#endif // RPSWINDLABCOMPARISONWORKER_H
