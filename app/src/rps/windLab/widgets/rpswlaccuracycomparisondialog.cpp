#include "rpswlaccuracycomparisondialog.h"
#include "ui_rpswlaccuracycomparisondialog.h"

#include "RPSWindLabAPI.h"
#include "rps/windLab/rpsWindLabSimulation.h"

RPSWLAccuracyComparisonDialog::RPSWLAccuracyComparisonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLAccuracyComparisonDialog)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    comparisonCategory = rpsWindLabSimulator->comparisonCategory;
    comparisonFunction = rpsWindLabSimulator->comparisonFunction;
    comparisonCandidate = rpsWindLabSimulator->comparisonCandidate;
    resultOutputTime = rpsWindLabSimulator->resultOutputTime;

    ui->comboBoxCategory->clear();
    ui->comboBoxFunction->clear();
    ui->comboBoxCandidate->clear();

    ui->comboBoxCategory->addItem(noSelection);
    ui->comboBoxFunction->addItem(noSelection);
    ui->comboBoxCandidate->addItem(noSelection);

    rpsWindLabSimulator->fillCategoryComboBox(ui->comboBoxCategory);
    rpsWindLabSimulator->fillFunctionAndCandidateComboBoxes(rpsWindLabSimulator->comparisonCategory, ui->comboBoxFunction, ui->comboBoxCandidate);

    if (1 == resultOutputTime)
    {
        ui->radioButtonByLoc->setChecked(Qt::Checked);
    }
    else if (2 == resultOutputTime)
    {
        ui->radioButtonByFreq->setChecked(Qt::Checked);
    }
    else if (3 == resultOutputTime)
    {
        ui->radioButtonByTim->setChecked(Qt::Checked);
    }

    QStringList tableHeader;
    ui->tableWidget->setColumnCount(3);
    tableHeader << "Candidate"
                << "Category"
                << "Function";
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    //ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // ui->tableWidget->setShowGrid(false);
    // ui->tableWidget->setStyleSheet("QTableView {selection-background-color: blue;}");
    readTableItemsFromList(rpsWindLabSimulator->candidateList);

    connect(ui->comboBoxCategory, SIGNAL(currentIndexChanged(int)),
            this, SLOT(comboBoxCategoryCurrentIndexChanged(int)));

    connect(ui->pushButtonFunctionInit, SIGNAL(clicked()),
            this, SLOT(OnBnClickedFunctionInit()));

    connect(ui->pushButtonCategoryInit, SIGNAL(clicked()),
            this, SLOT(OnBnClickedCategoryInit()));

    connect(ui->pushButtonCandidateInit, SIGNAL(clicked()),
            this, SLOT(OnBnClickedCadidateInit()));

    connect(ui->radioButtonByLoc, SIGNAL(toggled(bool)),
            this, SLOT(radioButtonByLocationToggled(bool)));

    connect(ui->radioButtonByFreq, SIGNAL(toggled(bool)),
            this, SLOT(radioButtonByFrequencyToggled(bool)));

    connect(ui->radioButtonByTim, SIGNAL(toggled(bool)),
            this, SLOT(radioButtonByTimeWindToggled(bool)));

    connect(ui->pushButtonAdd, SIGNAL(clicked()),
            this, SLOT(OnBnClickedTableAddRow()));

    connect(ui->pushButtonDelete, SIGNAL(clicked()),
            this, SLOT(OnBnClickedTableDeleteRow()));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));
}

RPSWLAccuracyComparisonDialog::~RPSWLAccuracyComparisonDialog()
{
    delete ui;
}


void RPSWLAccuracyComparisonDialog::comboBoxCategoryCurrentIndexChanged(int)
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    QString cat = ui->comboBoxCategory->currentText();

    rpsWindLabSimulator->fillFunctionAndCandidateComboBoxes(cat, ui->comboBoxFunction, ui->comboBoxCandidate);
}

void RPSWLAccuracyComparisonDialog::OnBnClickedFunctionInit()
{
}
void RPSWLAccuracyComparisonDialog::OnBnClickedCategoryInit()
{
}
void RPSWLAccuracyComparisonDialog::OnBnClickedCadidateInit()
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    QString cat = ui->comboBoxCategory->currentText();
    QString candid = ui->comboBoxCandidate->currentText();

    rpsWindLabSimulator->candidateInitialData(cat, candid);
}
void RPSWLAccuracyComparisonDialog::radioButtonByLocationToggled(bool)
{
    resultOutputTime = 1;
}
void RPSWLAccuracyComparisonDialog::radioButtonByFrequencyToggled(bool)
{
    resultOutputTime = 2;
}
void RPSWLAccuracyComparisonDialog::radioButtonByTimeWindToggled(bool)
{
    resultOutputTime = 3;
}

void RPSWLAccuracyComparisonDialog::acceptInput()
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    comparisonCategory = ui->comboBoxCategory->currentText();
    comparisonFunction = ui->comboBoxFunction->currentText();
    comparisonCandidate = ui->comboBoxCandidate->currentText();

    saveTableItemsToList(rpsWindLabSimulator->candidateList);

}

void RPSWLAccuracyComparisonDialog::OnBnClickedTableAddRow()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();

    item1->setText(ui->comboBoxCandidate->currentText());
    item2->setText(ui->comboBoxCategory->currentText());
    item3->setText(ui->comboBoxFunction->currentText());

    ui->tableWidget->setItem(row, 0, item1);
    ui->tableWidget->setItem(row, 1, item2);
    ui->tableWidget->setItem(row, 2, item3);
}
void RPSWLAccuracyComparisonDialog::OnBnClickedTableDeleteRow()
{
    int row = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(row);
}

void RPSWLAccuracyComparisonDialog::saveTableItemsToList(std::vector<QString> &itemList)
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    int row = ui->tableWidget->rowCount();
    int col = ui->tableWidget->columnCount();
    rpsWindLabSimulator->numberOfCandidate = row;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            QString txt = item->text();
            itemList.push_back(txt);
        }
    } 
}

void RPSWLAccuracyComparisonDialog::readTableItemsFromList(std::vector<QString> itemList)
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    int row = rpsWindLabSimulator->numberOfCandidate;
    int col = 3;
    //ui->tableWidget->insertRow(row);
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
