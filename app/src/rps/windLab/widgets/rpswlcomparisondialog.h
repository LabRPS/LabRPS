#ifndef RPSWLCOMPARISONDIALOG_H
#define RPSWLCOMPARISONDIALOG_H

#include <QDialog>

namespace Ui
{
    class RPSWLComparisonDialog;
}

class RPSWLComparisonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLComparisonDialog(QWidget *parent = nullptr);
    ~RPSWLComparisonDialog();
    
    void saveTableItemsToList(std::vector<QString> &itemList);
    void readTableItemsFromList(std::vector<QString> itemList);

private:
    Ui::RPSWLComparisonDialog *ui;
  
public:
    bool compareComputationTime;
    bool compareMemoryUsage;
    QString comparisonCategory;
    QString comparisonFunction;
    QString comparisonCandidate;
    int minNumberOfLocation;
    int minNumberOfFrequency;
    int minNumberOfTime;
    int numberOfLocationIncrement;
    int numberOfFrequencyIncrement;
    int numberOfTimeIncrement;
    int totalNumber;
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


public slots:
    void comboBoxCategoryCurrentIndexChanged(int);
    void comboBoxFunctionCurrentIndexChanged(int);
    void checkBoxComputationTimeModeChanged(int);
    void checkBoxMemoryUsageModeChanged(int);
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

#endif // RPSWLCOMPARISONDIALOG_H
