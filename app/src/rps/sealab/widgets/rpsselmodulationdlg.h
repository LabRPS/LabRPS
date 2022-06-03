#ifndef RPSSELMODULATIONDLG_H
#define RPSSELMODULATIONDLG_H

#include <QDialog>

namespace Ui {
class RPSSeLModulationDlg;
}

class RPSSeLModulationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSeLModulationDlg(QWidget *parent = nullptr);
    ~RPSSeLModulationDlg();

private slots:

     void comboBoxModulationFnIndexChanged(int index);
     void OnBnClickedModulationFnInit();

private:
    Ui::RPSSeLModulationDlg *ui;

public:
   QString modulationFunction;
};

#endif // RPSSELMODULATIONDLG_H
