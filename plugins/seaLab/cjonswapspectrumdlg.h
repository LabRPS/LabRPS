#ifndef CJONSWAPSPECTRUMDLG_H
#define CJONSWAPSPECTRUMDLG_H

#include <QDialog>

namespace Ui {
class CJonswapSpectrumDlg;
}

class CJonswapSpectrumDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CJonswapSpectrumDlg(double sigma1, double fetcLength, double gravityAcceleration, double windSpeed_U10, double sigma2, double gamma, QWidget *parent = nullptr);
    ~CJonswapSpectrumDlg();

private slots:
    void acceptInput();

private:
    Ui::CJonswapSpectrumDlg *ui;

public:
	double msigma1;
	double mfetcLength;
	double mgravityAcceleration;
	double mwindSpeed_U10;
	double msigma2;
	double mgamma;
};

#endif // CJONSWAPSPECTRUMDLG_H
