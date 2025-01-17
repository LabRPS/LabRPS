#include "cgaussianrandomnessproviderdlg.h"
#include "ui_cgaussianrandomnessproviderdlg.h"

CGaussianRandomnessProviderDlg::CGaussianRandomnessProviderDlg(double sigma, double mu, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGaussianRandomnessProviderDlg)
{
    ui->setupUi(this);

    ui->lineEditSigma->setText(QString::number(sigma));
    ui->lineEditMu->setText(QString::number(mu));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

CGaussianRandomnessProviderDlg::~CGaussianRandomnessProviderDlg()
{
    delete ui;
}

void CGaussianRandomnessProviderDlg::acceptInput()
{
      m_sigma = ui->lineEditSigma->text().toDouble();
      m_mu = ui->lineEditMu->text().toDouble();
}
