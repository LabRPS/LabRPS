#include "expomodulationdialog.h"
#include "ui_expomodulationdialog.h"

ExpoModulationDialog::ExpoModulationDialog(double timeOfMax, double stormLength, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpoModulationDialog)
{
    ui->setupUi(this);

     ui->lineEditTimeofMax->setText(QString::number(timeOfMax));
     ui->lineEditStormLength->setText(QString::number(stormLength));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

ExpoModulationDialog::~ExpoModulationDialog()
{
    delete ui;
}

void ExpoModulationDialog::acceptInput()
{
    m_dTimeOfMax = ui->lineEditTimeofMax->text().toDouble();
    m_dStormLength = ui->lineEditStormLength->text().toDouble();
}

