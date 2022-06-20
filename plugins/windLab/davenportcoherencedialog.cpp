#include "davenportcoherencedialog.h"
#include "ui_davenportcoherencedialog.h"

DavenportCoherenceDialog::DavenportCoherenceDialog(double decayCx, double decayCy, double decayCz, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DavenportCoherenceDialog)
{
    ui->setupUi(this);

    ui->lineEditDecayCx->setText(QString::number(decayCx));
    ui->lineEditDecayCy->setText(QString::number(decayCy));
    ui->lineEditDecayCz->setText(QString::number(decayCz));

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

DavenportCoherenceDialog::~DavenportCoherenceDialog()
{
    delete ui;
}

void DavenportCoherenceDialog::acceptInput()
{
    m_decayCx = ui->lineEditDecayCx->text().toDouble();
    m_decayCy = ui->lineEditDecayCy->text().toDouble();
    m_decayCz = ui->lineEditDecayCz->text().toDouble();
}
