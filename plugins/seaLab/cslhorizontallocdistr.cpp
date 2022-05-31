#include "cslhorizontallocdistr.h"
#include "ui_cslhorizontallocdistr.h"

CSLHorizontalLocDistr::CSLHorizontalLocDistr(double height, double spacing, double length, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSLHorizontalLocDistr)
{
    ui->setupUi(this);
    ui->lineEditHeight->setText(QString::number(height));
    ui->lineEditSpacing->setText(QString::number(spacing));
    ui->lineEditLength->setText(QString::number(length));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectInput()));



}

CSLHorizontalLocDistr::~CSLHorizontalLocDistr()
{
    delete ui;
}

void CSLHorizontalLocDistr::acceptInput()
{
    mdSpacing = ui->lineEditHeight->text().toDouble();
    mdHeight = ui->lineEditSpacing->text().toDouble();
    mdLength = ui->lineEditLength->text().toDouble();
}

void CSLHorizontalLocDistr::rejectInput()
{
        
}
