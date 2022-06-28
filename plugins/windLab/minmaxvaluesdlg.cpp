#include "minmaxvaluesdlg.h"
#include "ui_minmaxvaluesdlg.h"
#include <QSettings>
#include <QMessageBox>

MinMaxValuesDlg::MinMaxValuesDlg(double minValue, double maxValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MinMaxValuesDlg)
{
    ui->setupUi(this);
    
    m_minValue = minValue;
    m_maxValue = maxValue;

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectInput()));
        
    ui->lineEditMinValue->setText(QString::number(m_minValue));
    ui->lineEditMaxValue->setText(QString::number(m_maxValue));


}

MinMaxValuesDlg::~MinMaxValuesDlg()
{
    delete ui;
}

void MinMaxValuesDlg::acceptInput()
{
    m_minValue = ui->lineEditMinValue->text().toDouble();
    m_maxValue = ui->lineEditMaxValue->text().toDouble();
}

void MinMaxValuesDlg::rejectInput()
{
        
}
