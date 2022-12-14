#ifndef RPSWLPDFDLG_H
#define RPSWLPDFDLG_H

#include <QDialog>

namespace Ui {
class RPSWLProbabilityDensityFunctionDlg;
}

class RPSWLProbabilityDensityFunctionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLProbabilityDensityFunctionDlg(QWidget *parent = nullptr);
    ~RPSWLProbabilityDensityFunctionDlg();

private slots:

     void comboBoxProbabilityDensityFunctionFnIndexChanged(int index);
     void OnBnClickedProbabilityDensityFunctionInit();


private:
    Ui::RPSWLProbabilityDensityFunctionDlg *ui;

public:
   QString probabilityDensityFunction;
};

#endif // RPSWLPDFDLG_H
