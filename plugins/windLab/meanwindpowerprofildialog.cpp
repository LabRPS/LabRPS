#include "meanwindpowerprofildialog.h"
#include "ui_meanwindpowerprofildialog.h"

MeanWindPowerProfilDialog::MeanWindPowerProfilDialog(double referenceHeight, double referenceSpeed, double dimensionlessPower, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeanWindPowerProfilDialog)
{
    ui->setupUi(this);

    ui->lineEditReferenceHeight->setText(QString::number(referenceHeight));
    ui->lineEditReferenceSpeed->setText(QString::number(referenceSpeed));
    ui->lineEditDimensionlessPower->setText(QString::number(dimensionlessPower));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

MeanWindPowerProfilDialog::~MeanWindPowerProfilDialog()
{
    delete ui;
}

void MeanWindPowerProfilDialog::acceptInput()
{
    m_referenceHeight = ui->lineEditReferenceHeight->text().toDouble();
    m_referenceSpeed = ui->lineEditReferenceSpeed->text().toDouble();
    m_dimensionlessPower = ui->lineEditDimensionlessPower->text().toDouble();    
}
