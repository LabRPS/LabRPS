#ifndef RPSWLACCURACYCOMPARISONOBJECTDEPENDENCYDIALOG_H
#define RPSWLACCURACYCOMPARISONOBJECTDEPENDENCYDIALOG_H

#include <QDialog>

namespace Ui {
class RPSWLAccuracyComparisonObjectDependencyDialog;
}

class RPSWLAccuracyComparisonObjectDependencyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLAccuracyComparisonObjectDependencyDialog(QWidget *parent = nullptr);
    ~RPSWLAccuracyComparisonObjectDependencyDialog();

public slots:
    void acceptInput();
    void OnBnClickedCoherenceInit( );
    void OnBnClickedCorrelationInit( );
    void OnBnClickedFrequencyDistrInit( );
    void OnBnClickedSpatialDistrInit( );
    void OnBnClickedMeanWindInit( );
    void OnBnClickedModulationInit( );
    void OnBnClickedSimuMethodInit( );
    void OnBnClickedRandomnessInit( );
    void OnBnClickedSpectrumDecompInit( );
    void OnBnClickedSpectrumInit( );
    void OnBnClickedCumulativeProbabilityDistribution( );
    void OnBnClickedGustFactor( );
    void OnBnClickedKurtosis( );
    void OnBnClickedPeakFactor( );
    void OnBnClickedProbabilityDensityFunction( );
    void OnBnClickedRoughness( );
    void OnBnClickedShearVelocityOfFlow( );
    void OnBnClickedSkewness( );
    void OnBnClickedStandardDeviation( );
    void OnBnClickedTurbulenceIntensity( );
    void OnBnClickedTurbulenceScale( );
    void OnBnClickedVariance( );
    void OnBnClickedWavePassageEffect( );


private:
    Ui::RPSWLAccuracyComparisonObjectDependencyDialog *ui;

public:
    QString noSelection;

    QString coherence;
    QString correlation;
    QString frequency;
    QString mean;
    QString modulation;
    QString decomposition;
    QString simulation;
    QString spatial;
    QString randomness;
    QString spectrum;

    QString cumulativeProbabilityDistribution;
    QString gustFactor;
    QString kurtosis;
    QString peakFactor;
    QString probabilityDensityFunction;
    QString roughness;
    QString shearVelocityOfFlow;
    QString skewness;
    QString standardDeviation;
    QString turbulenceIntensity;
    QString turbulenceScale;
    QString variance;
    QString wavePassageEffect;
};

#endif // RPSWLCOMPARISONOBJECTDEPENDENCYDIALOG_H
