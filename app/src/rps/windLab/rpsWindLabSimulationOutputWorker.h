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
    void decomposedSpectrumModelOut();
    void coherenceOut();
    void correlationOut();
    void modulationOut();
    void meanWindVelocityOut();
    void randomPhaseOut();

    void cumulativeProbabilityDistributionOutp();
    void gustFactorOutp();
    void kurtosisOutp();
    void peakFactorOutp();
    void probabilityDensityFunctionOutp();
    void roughnessOutp();
    void shearVelocityOfFlowOutp();
    void skewnessOutp();
    void standardDeviationOutp();
    void turbulenceIntensityOutp();
    void turbulenceScaleOutp();
    void varianceOutp();
    void wavePassageEffectOutp();




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
    
    void showFrequencyDistributionOutput();
    void showLocationDistributionOutput();
    void showXSpectrumOutput();
    void showYSpectrumOutput();
    void showZSpectrumOutput();
    void showDecomposedSpectrumOutput();
    void showCoherenceOutput();
    void showCorrelationOutput();
    void showModulationOutput();
    void showMeanWindVelocityOutput();
    void showRandomPhaseOutput();

    void showCumulativeProbabilityDistributionOutput();
    void showGustFactorOutput();
    void showKurtosisOutput();
    void showPeakFactorOutput();
    void showProbabilityDensityFunctionOutput();
    void showRoughnessOutput();
    void showShearVelocityOfFlowOutput();
    void showSkewnessOutput();
    void showStandardDeviationOutput();
    void showTurbulenceIntensityOutput();
    void showTurbulenceScaleOutput();
    void showVarianceOutput();
    void showWavePassageEffectOutput();

public:
    // output
    void windVelocityOutp();
    void frequencyDistributionOutp();
    void locationDistributionOutp();
    void spectrumXModelOutp();
    void spectrumYModelOutp();
    void spectrumZModelOutp();
    void decomposedSpectrumModelOutp();
    void coherenceOutp();
    void correlationOutp();
    void modulationOutp();
    void meanWindVelocityOutp();
    void randomPhaseOutp();

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
    cx_vec m_ResultVector3;

    mat m_ResultMatrix;
    mat m_ResultMatrix2;
    cx_mat m_ResultMatrix3;

    int workerOutputType;

public:
    QStringList getInformation();

    QString tableName;
    QString plotTitle;
    QString plotxlable;
    QString plotylabel;
};

#endif // RPSWINDLABSIMULATIONOUTPUTWORKER_H
