#ifndef RPSWLGUSTFACTORDLG_H
#define RPSWLGUSTFACTORDLG_H

#include <QDialog>

namespace Ui {
class RPSWLGustFactorDlg;
}

class RPSWLGustFactorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLGustFactorDlg(QWidget *parent = nullptr);
    ~RPSWLGustFactorDlg();

private slots:

     void comboBoxGustFactorFnIndexChanged(int index);
     void OnBnClickedGustFactorInit();


private:
    Ui::RPSWLGustFactorDlg *ui;

public:
   QString gustFactor;
};

#endif // RPSWLGUSTFACTORDLG_H
