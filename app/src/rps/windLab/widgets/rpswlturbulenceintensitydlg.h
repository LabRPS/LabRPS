#ifndef RPSWLTURBULENCEINTENSITYDLG_H
#define RPSWLTURBULENCEINTENSITYDLG_H

#include <QDialog>

namespace Ui {
class RPSWLTurbulenceIntensityDlg;
}

class RPSWLTurbulenceIntensityDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLTurbulenceIntensityDlg(QWidget *parent = nullptr);
    ~RPSWLTurbulenceIntensityDlg();

private slots:

     void comboBoxTurbulenceIntensityFnIndexChanged(int index);
     void OnBnClickedTurbulenceIntensityInit();


private:
    Ui::RPSWLTurbulenceIntensityDlg *ui;

public:
   QString turbulenceIntensity;
};

#endif // RPSWLTURBULENCEINTENSITYDLG_H
