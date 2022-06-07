#ifndef PRSSLSIMUOPTIONSDLG_H
#define PRSSLSIMUOPTIONSDLG_H

#include <QDialog>

namespace Ui {
class PRSSLSimuOptionsDlg;
}

class PRSSLSimuOptionsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PRSSLSimuOptionsDlg(QWidget *parent = nullptr);
    ~PRSSLSimuOptionsDlg();

private:
    Ui::PRSSLSimuOptionsDlg *ui;
    
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
};

#endif // PRSSLSIMUOPTIONSDLG_H
