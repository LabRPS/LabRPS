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
    ui->tableWidget->setColumnCount(26);
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
                << "PSD"
                << "CPF"
                << "Gust F."
                << "Kurtosis"
                << "Peak F."
                << "PDF"
                << "Roughness"
                << "Shear V."
                << "Skewness"
                << "Standard D."
                << "Turbulence I."
                << "Turbulence S."
                << "Variance"
                << "Wave P.";

    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    //ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // ui->tableWidget->setShowGrid(false);
    // ui->tableWidget->setStyleSheet("QTableView {selection-background-color: blue;}");
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
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
    ui->tableWidget->horizontalHeaderItem(13)->setToolTip("Cumulative Probability Distribution");
    ui->tableWidget->horizontalHeaderItem(14)->setToolTip("Gust Factor");
    ui->tableWidget->horizontalHeaderItem(15)->setToolTip("Kurtosis");
    ui->tableWidget->horizontalHeaderItem(16)->setToolTip("Peak Factor");
    ui->tableWidget->horizontalHeaderItem(17)->setToolTip("Probability Density Function");
    ui->tableWidget->horizontalHeaderItem(18)->setToolTip("Roughness");
    ui->tableWidget->horizontalHeaderItem(19)->setToolTip("Shear Velocity of Flow");
    ui->tableWidget->horizontalHeaderItem(20)->setToolTip("Skewness");
    ui->tableWidget->horizontalHeaderItem(21)->setToolTip("Standard Deviation");
    ui->tableWidget->horizontalHeaderItem(22)->setToolTip("Turbulence Intensity");
    ui->tableWidget->horizontalHeaderItem(23)->setToolTip("Turbulence Scale");
    ui->tableWidget->horizontalHeaderItem(24)->setToolTip("Variance");
    ui->tableWidget->horizontalHeaderItem(25)->setToolTip("Wave Passage Effect");

    std::vector<QString> itemList;
    rpsWindLabComparisonDialog->saveTableItemsToList(itemList);
    
    int row = (int)(itemList.size()/26);
    int col = 26;
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
