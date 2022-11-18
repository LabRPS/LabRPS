#include "meanwindpowerprofildialog.h"
#include "ui_meanwindpowerprofildialog.h"

MeanWindPowerProfilDialog::MeanWindPowerProfilDialog(double referenceHeight, double referenceSpeed, double dimensionlessPower, double zeroPlanDisplacement, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeanWindPowerProfilDialog)
{
    ui->setupUi(this);

    ui->lineEditReferenceHeight->setText(QString::number(referenceHeight));
    ui->lineEditReferenceSpeed->setText(QString::number(referenceSpeed));
    ui->lineEditDimensionlessPower->setText(QString::number(dimensionlessPower));
    ui->lineEditZeroPlanDisplacement->setText(QString::number(zeroPlanDisplacement));


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
    m_zeroPlanDisplacement = ui->lineEditZeroPlanDisplacement->text().toDouble();

}
