#include "generaldistributiondialog.h"
#include "ui_generaldistributiondialog.h"

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
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
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
    saveTableItemsToMatrix();
}

void GeneralDistributionDialog::OnBnClickedTableAddRow()
{
    int row = ui->tableWidget->rowCount();

    if(row - 1 > m_nomberOfPoint)
    {
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
    int row = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(row);
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
