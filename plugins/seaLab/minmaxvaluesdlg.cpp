#include "minmaxvaluesdlg.h"
#include "ui_minmaxvaluesdlg.h"
#include <QSettings>
#include <QMessageBox>

MinMaxValuesDlg::MinMaxValuesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MinMaxValuesDlg)
{
    ui->setupUi(this);

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectInput()));
    readData();
    ui->lineEditMinValue->setText(QString::number(minValue));
    ui->lineEditMaxValue->setText(QString::number(maxValue));


}

MinMaxValuesDlg::~MinMaxValuesDlg()
{
    delete ui;
}

void MinMaxValuesDlg::acceptInput()
{
    minValue = ui->lineEditMinValue->text().toDouble();
    maxValue = ui->lineEditMaxValue->text().toDouble();
    writeData();
}

void MinMaxValuesDlg::rejectInput()
{
        
}

void MinMaxValuesDlg::writeData()
{
     QSettings settings;

    settings.beginGroup("plugins/seaLab/uniformRandomness");
    settings.setValue("minValue", minValue);
    settings.setValue("maxValue", maxValue);
    settings.endGroup();   
}

void MinMaxValuesDlg::readData()
{
    QSettings settings;
    settings.beginGroup("plugins/seaLab/uniformRandomness");
    minValue = settings.value("minValue").toDouble();
    maxValue = settings.value("maxValue").toDouble();
    settings.endGroup(); 
}
