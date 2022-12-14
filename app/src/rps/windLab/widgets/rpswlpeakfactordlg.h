#ifndef RPSWLPEAKFACTORDLG_H
#define RPSWLPEAKFACTORDLG_H

#include <QDialog>

namespace Ui {
class RPSWLPeakFactorDlg;
}

class RPSWLPeakFactorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLPeakFactorDlg(QWidget *parent = nullptr);
    ~RPSWLPeakFactorDlg();

private slots:

     void comboBoxPeakFactorFnIndexChanged(int index);
     void OnBnClickedPeakFactorInit();


private:
    Ui::RPSWLPeakFactorDlg *ui;

public:
   QString peakFactor;
};

#endif // RPSWLPEAKFACTORDLG_H
