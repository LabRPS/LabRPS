#ifndef RPSWLMODULATIONDLG_H
#define RPSWLMODULATIONDLG_H

#include <QDialog>

namespace Ui {
class RPSWLModulationDlg;
}

class RPSWLModulationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLModulationDlg(QWidget *parent = nullptr);
    ~RPSWLModulationDlg();

private slots:

     void comboBoxModulationFnIndexChanged(int index);
     void OnBnClickedModulationFnInit();

private:
    Ui::RPSWLModulationDlg *ui;

public:
   QString modulationFunction;
};

#endif // RPSWLMODULATIONDLG_H
