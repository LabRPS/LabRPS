#ifndef RPSWLSHEARVELOCITYDLG_H
#define RPSWLSHEARVELOCITYDLG_H

#include <QDialog>

namespace Ui {
class RPSWLShearVelocityOfFlowDlg;
}

class RPSWLShearVelocityOfFlowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLShearVelocityOfFlowDlg(QWidget *parent = nullptr);
    ~RPSWLShearVelocityOfFlowDlg();

private slots:

     void comboBoxShearVelocityOfFlowFnIndexChanged(int index);
     void OnBnClickedShearVelocityOfFlowInit();


private:
    Ui::RPSWLShearVelocityOfFlowDlg *ui;

public:
   QString shearVelocityOfFlow;
};

#endif // RPSWLCPDDLG_H
