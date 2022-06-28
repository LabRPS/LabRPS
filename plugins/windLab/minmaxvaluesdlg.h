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
    explicit MinMaxValuesDlg(double minValue, double maxValue, QWidget *parent = nullptr);
    ~MinMaxValuesDlg();

private:
    Ui::MinMaxValuesDlg *ui;

private slots:
void acceptInput();
void rejectInput();

public:
double m_minValue;
double m_maxValue;


};

#endif // MINMAXVALUESDLG_H
