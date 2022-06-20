#include "wlvertdistrdialog.h"
#include "ui_wlvertdistrdialog.h"

WLVertDistrDialog::WLVertDistrDialog(double minHeight, double spacing, double length, double xCoord, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLVertDistrDialog)
{
    ui->setupUi(this);

    ui->lineEditMinHeight->setText(QString::number(minHeight));
    ui->lineEditSpacing->setText(QString::number(spacing));
    ui->lineEditLength->setText(QString::number(length));
    ui->lineEditXCoord->setText(QString::number(xCoord));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

WLVertDistrDialog::~WLVertDistrDialog()
{
    delete ui;
}

void WLVertDistrDialog::acceptInput()
{
    mminHeightHo = ui->lineEditMinHeight->text().toDouble();
    mspacing = ui->lineEditSpacing->text().toDouble();
    mlength = ui->lineEditLength->text().toDouble();
    mpositionX = ui->lineEditXCoord->text().toDouble();   
   
}