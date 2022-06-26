#include "threeparamodulationdialog.h"
#include "ui_threeparamodulationdialog.h"

ThreeParaModulationDialog::ThreeParaModulationDialog(double alpha, double betta, double lambda, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThreeParaModulationDialog)
{
    ui->setupUi(this);

    ui->lineEditAlpha->setText(QString::number(alpha));
    ui->lineEditBeta->setText(QString::number(betta));
    ui->lineEditLambda->setText(QString::number(lambda));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

ThreeParaModulationDialog::~ThreeParaModulationDialog()
{
    delete ui;
}

void ThreeParaModulationDialog::acceptInput()
{ 
    m_dAlpha = ui->lineEditAlpha->text().toDouble();
    m_dBeta = ui->lineEditBeta->text().toDouble();
    m_dLambda = ui->lineEditLambda->text().toDouble();
}

