#ifndef RPSWLTURBULENCESCALEDLG_H
#define RPSWLTURBULENCESCALEDLG_H

#include <QDialog>

namespace Ui {
class RPSWLTurbulenceScaleDlg;
}

class RPSWLTurbulenceScaleDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLTurbulenceScaleDlg(QWidget *parent = nullptr);
    ~RPSWLTurbulenceScaleDlg();

private slots:

     void comboBoxTurbulenceScaleFnIndexChanged(int index);
     void OnBnClickedTurbulenceScaleInit();


private:
    Ui::RPSWLTurbulenceScaleDlg *ui;

public:
   QString turbulenceScale;
};

#endif // RPSWLTURBULENCESCALEDLG_H
