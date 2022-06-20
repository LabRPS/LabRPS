#ifndef RPSSLMODULATIONDLG_H
#define RPSSLMODULATIONDLG_H

#include <QDialog>

namespace Ui {
class RPSSLModulationDlg;
}

class RPSSLModulationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSLModulationDlg(QWidget *parent = nullptr);
    ~RPSSLModulationDlg();

private slots:

     void comboBoxModulationFnIndexChanged(int index);
     void OnBnClickedModulationFnInit();

private:
    Ui::RPSSLModulationDlg *ui;

public:
   QString modulationFunction;
};

#endif // RPSSLMODULATIONDLG_H
