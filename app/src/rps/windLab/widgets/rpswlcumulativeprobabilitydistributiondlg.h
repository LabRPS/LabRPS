#ifndef RPSWLCPDDLG_H
#define RPSWLCPDDLG_H

#include <QDialog>

namespace Ui {
class RPSWLCumulativeProbabilityDistributionDlg;
}

class RPSWLCumulativeProbabilityDistributionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLCumulativeProbabilityDistributionDlg(QWidget *parent = nullptr);
    ~RPSWLCumulativeProbabilityDistributionDlg();

private slots:

     void comboBoxCumulativeProbabilityDistributionFnIndexChanged(int index);
     void OnBnClickedCumulativeProbabilityDistributionInit();


private:
    Ui::RPSWLCumulativeProbabilityDistributionDlg *ui;

public:
   QString cumulativeProbabilityDistribution;
};

#endif // RPSWLCPDDLG_H
