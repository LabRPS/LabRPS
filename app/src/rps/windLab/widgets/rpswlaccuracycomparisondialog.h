#ifndef RPSWLACCURACYCOMPARISONDIALOG_H
#define RPSWLACCURACYCOMPARISONDIALOG_H

#include <QDialog>

namespace Ui {
class RPSWLAccuracyComparisonDialog;
}

class RPSWLAccuracyComparisonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLAccuracyComparisonDialog(QWidget *parent = nullptr);
    ~RPSWLAccuracyComparisonDialog();
    void saveTableItemsToList(std::vector<QString> &itemList);
    void readTableItemsFromList(std::vector<QString> itemList);

private:
    Ui::RPSWLAccuracyComparisonDialog *ui;

public:
    QString comparisonCategory;
    QString comparisonFunction;
    QString comparisonCandidate;
    int resultOutputType;

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


public slots:
    void comboBoxCategoryCurrentIndexChanged(int);
    void comboBoxFunctionCurrentIndexChanged(int);
    void OnBnClickedFunctionInit();
    void OnBnClickedCategoryInit();
    void OnBnClickedCadidateInit();
    void radioButtonByLocationToggled(bool);
    void radioButtonByFrequencyToggled(bool);
    void radioButtonByTimeWindToggled(bool);
    void acceptInput();
    void OnBnClickedTableAddRow();
    void OnBnClickedTableDeleteRow();
};

#endif // RPSWLACCURACYCOMPARISONDIALOG_H
