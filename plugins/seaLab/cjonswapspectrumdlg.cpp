#include "cjonswapspectrumdlg.h"
#include "ui_cjonswapspectrumdlg.h"

CJonswapSpectrumDlg::CJonswapSpectrumDlg(double sigma1, double fetcLength, double gravityAcceleration, double windSpeed_U10, double sigma2, double gamma, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CJonswapSpectrumDlg)
{
    ui->setupUi(this);
    
    ui->lineEditsigma1->setText(QString::number(sigma1));
    ui->lineEditfetcLength->setText(QString::number(fetcLength));
    ui->lineEditgravityAcceleration->setText(QString::number(gravityAcceleration));
    ui->lineEditwindSpeed_U10->setText(QString::number(windSpeed_U10));
    ui->lineEditsigma2->setText(QString::number(sigma2));
    ui->lineEditgamma->setText(QString::number(gamma));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

CJonswapSpectrumDlg::~CJonswapSpectrumDlg()
{
    delete ui;
}

void CJonswapSpectrumDlg::acceptInput()
{
    msigma1 = ui->lineEditsigma1->text().toDouble();
    mfetcLength = ui->lineEditfetcLength->text().toDouble();
    mgravityAcceleration = ui->lineEditgravityAcceleration->text().toDouble();
    mwindSpeed_U10 = ui->lineEditwindSpeed_U10->text().toDouble();
    msigma2 = ui->lineEditsigma2->text().toDouble();
    mgamma = ui->lineEditgamma->text().toDouble();
    
}

