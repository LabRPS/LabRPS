#ifndef CGAUSSIANRANDOMNESSPROVIDERDLG_H
#define CGAUSSIANRANDOMNESSPROVIDERDLG_H

#include <QDialog>

namespace Ui {
class CGaussianRandomnessProviderDlg;
}

class CGaussianRandomnessProviderDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CGaussianRandomnessProviderDlg(double sigma, double mu, QWidget *parent = nullptr);
    ~CGaussianRandomnessProviderDlg();

private:
    Ui::CGaussianRandomnessProviderDlg *ui;

private Q_SLOTS:
    void acceptInput();

public:
    //standard deviation
    double m_sigma;
    double m_mu;


};

#endif // CGAUSSIANRANDOMNESSPROVIDERDLG_H
