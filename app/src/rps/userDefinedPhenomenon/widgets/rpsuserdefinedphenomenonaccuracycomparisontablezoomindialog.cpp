#include "rpsuserdefinedphenomenonaccuracycomparisontablezoomindialog.h"
#include "ui_rpsuserdefinedphenomenonaccuracycomparisontablezoomindialog.h"
#include "rpsuserdefinedphenomenonaccuracycomparisondialog.h"

RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog::RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog)
{
    ui->setupUi(this);

    RPSUserDefinedPhenomenonAccuracyComparisonDialog *rpsWindLabComparisonDialog = (RPSUserDefinedPhenomenonAccuracyComparisonDialog *)this->parent();

    QStringList tableHeader;
    ui->tableWidget->setColumnCount(4);
    tableHeader << "Candidate"
                << "Category"
                << "Function"
                << "Simu M.";

    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    //ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // ui->tableWidget->setShowGrid(false);
    // ui->tableWidget->setStyleSheet("QTableView {selection-background-color: blue;}");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    ui->tableWidget->horizontalHeaderItem(0)->setToolTip("Candidate name");
    ui->tableWidget->horizontalHeaderItem(1)->setToolTip("Comparison category");
    ui->tableWidget->horizontalHeaderItem(2)->setToolTip("Comparison function");
    ui->tableWidget->horizontalHeaderItem(3)->setToolTip("Simulation method");

    std::vector<QString> itemList;
    rpsWindLabComparisonDialog->saveTableItemsToList(itemList);
    
    int row = (int)(itemList.size()/4);
    int col = 4;
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
            txt = itemList.at(index++);
            item->setText(txt);
            ui->tableWidget->setItem(i, j, item);
        }
    } 

}

RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog::~RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog()
{
    delete ui;
}
