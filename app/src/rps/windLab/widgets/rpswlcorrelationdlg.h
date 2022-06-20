#ifndef RPSWLCORRELATIONDLG_H
#define RPSWLCORRELATIONDLG_H

#include <QDialog>

namespace Ui {
class RPSWLCorrelationDlg;
}

class RPSWLCorrelationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLCorrelationDlg(QWidget *parent = nullptr);
    ~RPSWLCorrelationDlg();

private slots:

     void comboBoxCorrelationFnIndexChanged(int index);
     void OnBnClickedCorrelationFnInit();

private:
    Ui::RPSWLCorrelationDlg *ui;

public:
   QString correlationFunction;
};

#endif // RPSSELCORRELATIONDLG_H
