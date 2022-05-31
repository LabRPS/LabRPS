#ifndef MINMAXVALUESDLG_H
#define MINMAXVALUESDLG_H

#include <QDialog>

namespace Ui {
class MinMaxValuesDlg;
}

class MinMaxValuesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MinMaxValuesDlg(QWidget *parent = nullptr);
    ~MinMaxValuesDlg();

private:
    Ui::MinMaxValuesDlg *ui;
    void writeData();
    void readData();

private slots:
void acceptInput();
void rejectInput();

public:
double minValue;
double maxValue;


};

#endif // MINMAXVALUESDLG_H
