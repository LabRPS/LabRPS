#ifndef RPSUSERDEFINEDPHENOMENONSIMUOPTIONSDLG_H
#define RPSUSERDEFINEDPHENOMENONSIMUOPTIONSDLG_H

#include <QDialog>

namespace Ui {
class RPSUserDefinedPhenomenonSimuOptionsDlg;
}

class RPSUserDefinedPhenomenonSimuOptionsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSUserDefinedPhenomenonSimuOptionsDlg(QWidget *parent = nullptr);
    ~RPSUserDefinedPhenomenonSimuOptionsDlg();

private:
    Ui::RPSUserDefinedPhenomenonSimuOptionsDlg *ui;
    
public:
    QString noSelection;
    QString currentRandomnessProvider;
    QString currentsimulationMethod;
    bool comparisonMode;
    bool largeScaleMode;



private slots:
void comboBoxRandomnessCurrentIndexChanged( int index);
void comboBoxSimuMethodCurrentIndexChanged( int index);
void checkBoxComparisonModeChanged( int state);
void checkBoxSLargeScaleSimulationModeChanged( int state);
void OnBnClickedRandomnessInit();
void OnBnClickedSimulationMethodInit();



signals:
};

#endif // RPSUSERDEFINEDPHENOMENONSIMUOPTIONSDLG_H
