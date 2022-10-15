#ifndef RPSUSERDEFINEDPHENOMENONCOMPARISONDIALOG_H
#define RPSUSERDEFINEDPHENOMENONCOMPARISONDIALOG_H

#include <QDialog>

namespace Ui
{
    class RPSUserDefinedPhenomenonComparisonDialog;
}

class RPSUserDefinedPhenomenonComparisonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSUserDefinedPhenomenonComparisonDialog(QWidget *parent = nullptr);
    ~RPSUserDefinedPhenomenonComparisonDialog();
    
    void saveTableItemsToList(std::vector<QString> &itemList);
    void readTableItemsFromList(std::vector<QString> itemList);

private:
    Ui::RPSUserDefinedPhenomenonComparisonDialog *ui;
  
public:
    bool compareComputationTime;
    bool compareMemoryUsage;
    QString comparisonCategory;
    QString comparisonFunction;
    QString comparisonCandidate;
    int minNumberOfProcess;
    int minNumberOfIndexSetIndex;
    int minNumberOfSample;
    int numberOfProcessIncrement;
    int numberOfIndexSetIndexIncrement;
    int numberOfSampleIncrement;
    int totalNumber;
    int resultOutputType;

    QString userDefinedPhenomenon;

public slots:
    void comboBoxCategoryCurrentIndexChanged(int);
    void comboBoxFunctionCurrentIndexChanged(int);
    void checkBoxComputationTimeModeChanged(int);
    void checkBoxMemoryUsageModeChanged(int);
    void OnBnClickedFunctionInit();
    void OnBnClickedCategoryInit();
    void OnBnClickedCadidateInit();
    void radioButtonByProcessNumberToggled(bool);
    void radioButtonByindexSetIndexToggled(bool);
    void radioButtonBySampleNumberToggled(bool);
    void acceptInput();
    void OnBnClickedTableAddRow();
    void OnBnClickedTableDeleteRow();
    
};

#endif // RPSUSERDEFINEDPHENOMENONCOMPARISONDIALOG_H
