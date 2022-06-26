#include "sinemodulationdialog.h"
#include "ui_sinemodulationdialog.h"

SineModulationDialog::SineModulationDialog(double pulseDuration, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SineModulationDialog)
{
    ui->setupUi(this);

     ui->lineEditPulseDuration->setText(QString::number(pulseDuration));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

SineModulationDialog::~SineModulationDialog()
{
    delete ui;
}

void SineModulationDialog::acceptInput()
{
    m_dPulseDuration = ui->lineEditPulseDuration->text().toDouble();
}

