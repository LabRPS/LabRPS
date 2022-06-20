#include "kaimalpsdshearvelocitydialog.h"
#include "ui_kaimalpsdshearvelocitydialog.h"

KaimalPSDShearVelocityDialog::KaimalPSDShearVelocityDialog(double shearVelocity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KaimalPSDShearVelocityDialog)
{
    ui->setupUi(this);

    ui->lineEditShearVelocity->setText(QString::number(shearVelocity));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

KaimalPSDShearVelocityDialog::~KaimalPSDShearVelocityDialog()
{
    delete ui;
}

void KaimalPSDShearVelocityDialog::acceptInput()
{
    m_shearVelocity = ui->lineEditShearVelocity->text().toDouble();
}
