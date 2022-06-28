#include "generaldistributiondialog.h"
#include "ui_generaldistributiondialog.h"
#include <QMessageBox>

GeneralDistributionDialog::GeneralDistributionDialog(int nomberOfPoints, mat& pointsMatrix, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneralDistributionDialog)
{
    ui->setupUi(this);
    m_pointsMatrix = pointsMatrix;
    m_nomberOfPoint = nomberOfPoints;

    QStringList tableHeader;
    ui->tableWidget->setColumnCount(3);
    tableHeader << "X Coordinate"
                << "Y Coordinate"
                << "Z Coordinate";
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    readTableItemsFromMatrix();

    connect(ui->pushButtonAdd, SIGNAL(clicked()),
            this, SLOT(OnBnClickedTableAddRow()));

    connect(ui->pushButtonDelete, SIGNAL(clicked()),
            this, SLOT(OnBnClickedTableDeleteRow()));

    connect(ui->pushButtonDeleteAll, SIGNAL(clicked()),
            this, SLOT(OnBnClickedTableDeleteAllRows()));
    
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));


}

GeneralDistributionDialog::~GeneralDistributionDialog()
{
    delete ui;
}


void GeneralDistributionDialog::acceptInput()
{
    int row = ui->tableWidget->rowCount();
    
    //QMessageBox::warning(this, QString::number(row), QString::number(m_nomberOfPoint));

    if(row != m_nomberOfPoint)
    {
        QString info = tr("The number of points must be %1.").arg(m_nomberOfPoint);
        m_information.append(info);
        return;
    }

    saveTableItemsToMatrix();
}

void GeneralDistributionDialog::OnBnClickedTableAddRow()
{
    int row = ui->tableWidget->rowCount();

    if(row > m_nomberOfPoint)
    {
        QString info = tr("The number of points cannot exceed %1.").arg(m_nomberOfPoint);
        m_information.append(info);
        return;
    }
    
    ui->tableWidget->insertRow(row);
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();

    item1->setText(ui->lineEditXCoord->text());
    item2->setText(ui->lineEditYCoord->text());
    item3->setText(ui->lineEditZCoord->text());

    ui->tableWidget->setItem(row, 0, item1);
    ui->tableWidget->setItem(row, 1, item2);
    ui->tableWidget->setItem(row, 2, item3);
}
void GeneralDistributionDialog::OnBnClickedTableDeleteRow()
{
    int row = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(row);
}

void GeneralDistributionDialog::OnBnClickedTableDeleteAllRows()
{
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }
}

void GeneralDistributionDialog::saveTableItemsToMatrix()
{
    m_pointsMatrix.resize(m_nomberOfPoint,3);

    int row = ui->tableWidget->rowCount();
    int col = ui->tableWidget->columnCount();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            QString txt = item->text();
            m_pointsMatrix(i,j) = txt.toDouble();
        }
    } 
}

void GeneralDistributionDialog::readTableItemsFromMatrix()
{
    int row = m_nomberOfPoint;
    int col = 3;
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(col);
    QTableWidgetItem *item;
    QString txt;
    int index = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            item = new QTableWidgetItem();
            txt = QString::number(m_pointsMatrix(i,j));
            item->setText(txt);
            ui->tableWidget->setItem(i, j, item);
        }
    } 
}
