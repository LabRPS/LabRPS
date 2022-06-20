#ifndef RPSSLCORRELATIONDLG_H
#define RPSSLCORRELATIONDLG_H

#include <QDialog>

namespace Ui {
class RPSSLCorrelationDlg;
}

class RPSSLCorrelationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSLCorrelationDlg(QWidget *parent = nullptr);
    ~RPSSLCorrelationDlg();

private slots:

     void comboBoxCorrelationFnIndexChanged(int index);
     void OnBnClickedCorrelationFnInit();

private:
    Ui::RPSSLCorrelationDlg *ui;

public:
   QString correlationFunction;
};

#endif // RPSSLCORRELATIONDLG_H
