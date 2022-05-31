#ifndef RPSSELCORRELATIONDLG_H
#define RPSSELCORRELATIONDLG_H

#include <QDialog>

namespace Ui {
class RPSSeLCorrelationDlg;
}

class RPSSeLCorrelationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSeLCorrelationDlg(QWidget *parent = nullptr);
    ~RPSSeLCorrelationDlg();

private slots:

     void comboBoxCorrelationFnIndexChanged(int index);
     void OnBnClickedCorrelationFnInit();

private:
    Ui::RPSSeLCorrelationDlg *ui;

public:
   QString correlationFunction;
};

#endif // RPSSELCORRELATIONDLG_H
