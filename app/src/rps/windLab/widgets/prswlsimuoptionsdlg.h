#ifndef PRSWLSIMUOPTIONSDLG_H
#define PRSWLSIMUOPTIONSDLG_H

#include <QDialog>

namespace Ui {
class PRSWLSimuOptionsDlg;
}

class PRSWLSimuOptionsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PRSWLSimuOptionsDlg(QWidget *parent = nullptr);
    ~PRSWLSimuOptionsDlg();

private:
    Ui::PRSWLSimuOptionsDlg *ui;
    
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

#endif // PRSWLSIMUOPTIONSDLG_H
