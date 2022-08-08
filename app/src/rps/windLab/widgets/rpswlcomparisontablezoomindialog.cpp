#include "rpswlcomparisontablezoomindialog.h"
#include "ui_rpswlcomparisontablezoomindialog.h"
#include "rpswlcomparisondialog.h"

RPSWLComparisonTableZoomInDialog::RPSWLComparisonTableZoomInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLComparisonTableZoomInDialog)
{
    ui->setupUi(this);

    RPSWLComparisonDialog *rpsWindLabComparisonDialog = (RPSWLComparisonDialog *)this->parent();

    QStringList tableHeader;
    ui->tableWidget->setColumnCount(13);
    tableHeader << "Candidate"
                << "Category"
                << "Function"
                << "Coh F."
                << "Cor F."
                << "Freq D."
                << "Mean P."
                << "Mod F."
                << "Decomp. M."
                << "Simu M."
                << "Spatial D."
                << "Rand P."
                << "PSD";

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
    ui->tableWidget->horizontalHeaderItem(3)->setToolTip("Coherence function");
    ui->tableWidget->horizontalHeaderItem(4)->setToolTip("Correlation function");
    ui->tableWidget->horizontalHeaderItem(5)->setToolTip("Frequency distribution");
    ui->tableWidget->horizontalHeaderItem(6)->setToolTip("Mean profile");
    ui->tableWidget->horizontalHeaderItem(7)->setToolTip("Modulation function");
    ui->tableWidget->horizontalHeaderItem(8)->setToolTip("Decomposition method");
    ui->tableWidget->horizontalHeaderItem(9)->setToolTip("Simulation method");
    ui->tableWidget->horizontalHeaderItem(10)->setToolTip("Spatial distribution");
    ui->tableWidget->horizontalHeaderItem(11)->setToolTip("Randomness providers");
    ui->tableWidget->horizontalHeaderItem(12)->setToolTip("Spectrum model");
    
    std::vector<QString> itemList;
    rpsWindLabComparisonDialog->saveTableItemsToList(itemList);
    
    int row = (int)(itemList.size()/13);
    int col = 13;
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

RPSWLComparisonTableZoomInDialog::~RPSWLComparisonTableZoomInDialog()
{
    delete ui;
}
