#include "cwlhorizontallocdistr.h"
#include "ui_cwlhorizontallocdistr.h"

CWLHorizontalLocDistr::CWLHorizontalLocDistr(double height, double spacing, double length, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CWLHorizontalLocDistr)
{
    ui->setupUi(this);
    ui->lineEditHeight->setText(QString::number(height));
    ui->lineEditSpacing->setText(QString::number(spacing));
    ui->lineEditLength->setText(QString::number(length));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectInput()));



}

CWLHorizontalLocDistr::~CWLHorizontalLocDistr()
{
    delete ui;
}

void CWLHorizontalLocDistr::acceptInput()
{
    mdSpacing = ui->lineEditHeight->text().toDouble();
    mdHeight = ui->lineEditSpacing->text().toDouble();
    mdLength = ui->lineEditLength->text().toDouble();
}

void CWLHorizontalLocDistr::rejectInput()
{
        
}
