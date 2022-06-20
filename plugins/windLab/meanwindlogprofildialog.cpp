#include "meanwindlogprofildialog.h"
#include "ui_meanwindlogprofildialog.h"

MeanWindLogProfilDialog::MeanWindLogProfilDialog(double terrainRoughness, double shearVelocity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeanWindLogProfilDialog)
{
    ui->setupUi(this);

    ui->lineEditTerrainRoughness->setText(QString::number(terrainRoughness));
    ui->lineEditShearVelocity->setText(QString::number(shearVelocity));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

MeanWindLogProfilDialog::~MeanWindLogProfilDialog()
{
    delete ui;
}

void MeanWindLogProfilDialog::acceptInput()
{
    m_terrainRoughness = ui->lineEditTerrainRoughness->text().toDouble();
    m_shearVelocity = ui->lineEditShearVelocity->text().toDouble();    
}
