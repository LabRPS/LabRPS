#ifndef RPSUSERDEFINEDPHENOMENONACCURACYCOMPARISONDIALOG_H
#define RPSUSERDEFINEDPHENOMENONACCURACYCOMPARISONDIALOG_H

#include <QDialog>

namespace Ui {
class RPSUserDefinedPhenomenonAccuracyComparisonDialog;
}

class RPSUserDefinedPhenomenonAccuracyComparisonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSUserDefinedPhenomenonAccuracyComparisonDialog(QWidget *parent = nullptr);
    ~RPSUserDefinedPhenomenonAccuracyComparisonDialog();
   void saveTableItemsToList(std::vector<QString> &itemList);
   void readTableItemsFromList(std::vector<QString> itemList);

private:
    Ui::RPSUserDefinedPhenomenonAccuracyComparisonDialog *ui;

public:
    QString comparisonCategory;
    QString comparisonFunction;
    QString comparisonCandidate;
    int resultOutputType;

    QString userDefinedPhenemenon;


public slots:
    void comboBoxCategoryCurrentIndexChanged(int);
    void comboBoxFunctionCurrentIndexChanged(int);
    void OnBnClickedFunctionInit();
    void OnBnClickedCategoryInit();
    void OnBnClickedCadidateInit();
    void radioButtonByProcessNumberToggled(bool);
    void radioButtonByIndexSetIndexToggled(bool);
    void radioButtonBySampleNumberToggled(bool);
    void acceptInput();
    void OnBnClickedTableAddRow();
    void OnBnClickedTableDeleteRow();
};

#endif // RPSUSERDEFINEDPHENOMENONACCURACYCOMPARISONDIALOG_H
