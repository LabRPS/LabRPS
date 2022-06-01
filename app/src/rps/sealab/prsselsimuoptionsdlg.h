#ifndef PRSSELSIMUOPTIONSDLG_H
#define PRSSELSIMUOPTIONSDLG_H

#include <QDialog>

#include "ApplicationWindow.h"

namespace Ui {
class PRSSeLSimuOptionsDlg;
}

class PRSSeLSimuOptionsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PRSSeLSimuOptionsDlg(QWidget *parent = nullptr);
    ~PRSSeLSimuOptionsDlg();

private:
    Ui::PRSSeLSimuOptionsDlg *ui;
    
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



signals:
};

#endif // PRSSELSIMUOPTIONSDLG_H
