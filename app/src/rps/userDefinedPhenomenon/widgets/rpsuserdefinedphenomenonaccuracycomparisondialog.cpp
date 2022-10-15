#include "rpsuserdefinedphenomenonaccuracycomparisondialog.h"
#include "ui_rpsuserdefinedphenomenonaccuracycomparisondialog.h"

#include "RPSUserDefinedPhenomenonAPI.h"
#include "rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulation.h"
#include "rpsuserdefinedphenomenonaccuracycomparisontablezoomindialog.h"


RPSUserDefinedPhenomenonAccuracyComparisonDialog::RPSUserDefinedPhenomenonAccuracyComparisonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSUserDefinedPhenomenonAccuracyComparisonDialog)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

    RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();
    comparisonCategory = rpsUserDefinedPhenomenonSimulator->comparisonCategory;
    comparisonFunction = rpsUserDefinedPhenomenonSimulator->comparisonFunction;
    comparisonCandidate = rpsUserDefinedPhenomenonSimulator->comparisonCandidate;
    resultOutputType = rpsUserDefinedPhenomenonSimulator->resultOutputType;

    ui->comboBoxCategory->clear();
    ui->comboBoxFunction->clear();
    ui->comboBoxCandidate->clear();

    ui->comboBoxCategory->addItem(noSelection);
    ui->comboBoxFunction->addItem(noSelection);
    ui->comboBoxCandidate->addItem(noSelection);

    rpsUserDefinedPhenomenonSimulator->fillCategoryComboBox(ui->comboBoxCategory);
    rpsUserDefinedPhenomenonSimulator->fillFunctionAndCandidateComboBoxes(rpsUserDefinedPhenomenonSimulator->comparisonCategory, ui->comboBoxFunction, ui->comboBoxCandidate);

     if (1 == resultOutputType)
     {
         ui->radioButtonByLoc->setChecked(Qt::Checked);
     }
     else if (2 == resultOutputType)
     {
         ui->radioButtonByFreq->setChecked(Qt::Checked);
     }
     else if (3 == resultOutputType)
     {
         ui->radioButtonByTim->setChecked(Qt::Checked);
     }

    QStringList tableHeader;
    ui->tableWidget->setColumnCount(13);
    tableHeader << "Candidate"
                << "Category"
                << "Function"
                << "User Defined Phenomenon";

    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    //ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // ui->tableWidget->setShowGrid(false);
    // ui->tableWidget->setStyleSheet("QTableView {selection-background-color: blue;}");

    if (rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().comparisonType == 1) // accuracy
    {
      readTableItemsFromList(rpsUserDefinedPhenomenonSimulator->candidateList);
    }

    if(ui->tableWidget->rowCount() == 2)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        ui->pushButtonAdd->setEnabled(false);

    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->pushButtonAdd->setEnabled(true);
    }

    connect(ui->comboBoxCategory, SIGNAL(currentIndexChanged(int)),
            this, SLOT(comboBoxCategoryCurrentIndexChanged(int)));
    connect(ui->comboBoxFunction, SIGNAL(currentIndexChanged(int)),
            this, SLOT(comboBoxFunctionCurrentIndexChanged(int)));
    connect(ui->pushButtonFunctionInit, SIGNAL(clicked()),
            this, SLOT(OnBnClickedFunctionInit()));

    connect(ui->pushButtonCategoryInit, SIGNAL(clicked()),
            this, SLOT(OnBnClickedCategoryInit()));

    connect(ui->pushButtonCandidateInit, SIGNAL(clicked()),
            this, SLOT(OnBnClickedCadidateInit()));

    // connect(ui->radioButtonByLoc, SIGNAL(toggled(bool)),
    //         this, SLOT(radioButtonByLocationToggled(bool)));

    // connect(ui->radioButtonByFreq, SIGNAL(toggled(bool)),
    //         this, SLOT(radioButtonByFrequencyToggled(bool)));

    // connect(ui->radioButtonByTim, SIGNAL(toggled(bool)),
    //         this, SLOT(radioButtonByTimeWindToggled(bool)));

    connect(ui->pushButtonAdd, SIGNAL(clicked()),
            this, SLOT(OnBnClickedTableAddRow()));

    connect(ui->pushButtonDelete, SIGNAL(clicked()),
            this, SLOT(OnBnClickedTableDeleteRow()));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));
}

RPSUserDefinedPhenomenonAccuracyComparisonDialog::~RPSUserDefinedPhenomenonAccuracyComparisonDialog()
{
    delete ui;
}


void RPSUserDefinedPhenomenonAccuracyComparisonDialog::comboBoxCategoryCurrentIndexChanged(int)
{
    RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();

    QString cat = ui->comboBoxCategory->currentText();

    rpsUserDefinedPhenomenonSimulator->fillFunctionAndCandidateComboBoxes(cat, ui->comboBoxFunction, ui->comboBoxCandidate);

    ui->tableWidget->setRowCount(0);
}

void RPSUserDefinedPhenomenonAccuracyComparisonDialog::comboBoxFunctionCurrentIndexChanged(int)
{
    ui->tableWidget->setRowCount(0);
}

void RPSUserDefinedPhenomenonAccuracyComparisonDialog::OnBnClickedFunctionInit()
{
    std::unique_ptr<RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog> dlg(new RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog(this));
	
   dlg->exec();
}
void RPSUserDefinedPhenomenonAccuracyComparisonDialog::OnBnClickedCategoryInit()
{

}
void RPSUserDefinedPhenomenonAccuracyComparisonDialog::OnBnClickedCadidateInit()
{
    RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();

    QString cat = ui->comboBoxCategory->currentText();
    QString candid = ui->comboBoxCandidate->currentText();

    rpsUserDefinedPhenomenonSimulator->candidateInitialData(cat, candid);
}
void RPSUserDefinedPhenomenonAccuracyComparisonDialog::radioButtonByProcessNumberToggled(bool)
{
    // resultOutputType = 1;
}
void RPSUserDefinedPhenomenonAccuracyComparisonDialog::radioButtonByIndexSetIndexToggled(bool)
{
    // resultOutputType = 2;
}
void RPSUserDefinedPhenomenonAccuracyComparisonDialog::radioButtonBySampleNumberToggled(bool)
{
    // resultOutputType = 3;
}

void RPSUserDefinedPhenomenonAccuracyComparisonDialog::acceptInput()
{
    RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();

    comparisonCategory = ui->comboBoxCategory->currentText();
    comparisonFunction = ui->comboBoxFunction->currentText();
    comparisonCandidate = ui->comboBoxCandidate->currentText();
    
    rpsUserDefinedPhenomenonSimulator->candidateList.clear();
    saveTableItemsToList(rpsUserDefinedPhenomenonSimulator->candidateList);

}

void RPSUserDefinedPhenomenonAccuracyComparisonDialog::OnBnClickedTableAddRow()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();

    item1->setText(ui->comboBoxCandidate->currentText());
    item2->setText(ui->comboBoxCategory->currentText());
    item3->setText(ui->comboBoxFunction->currentText());
    item4->setText(userDefinedPhenemenon);


    ui->tableWidget->setItem(row, 0, item1);
    ui->tableWidget->setItem(row, 1, item2);
    ui->tableWidget->setItem(row, 2, item3);
    ui->tableWidget->setItem(row, 3, item4);

    if(ui->tableWidget->rowCount() == 2)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        ui->pushButtonAdd->setEnabled(false);

    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->pushButtonAdd->setEnabled(true);
    }
}
void RPSUserDefinedPhenomenonAccuracyComparisonDialog::OnBnClickedTableDeleteRow()
{
    int row = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(row);
    if(ui->tableWidget->rowCount() == 2)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        ui->pushButtonAdd->setEnabled(false);

    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->pushButtonAdd->setEnabled(true);
    }
}

void RPSUserDefinedPhenomenonAccuracyComparisonDialog::saveTableItemsToList(std::vector<QString> &itemList)
{
    RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();

    int row = ui->tableWidget->rowCount();
    int col = ui->tableWidget->columnCount();
    rpsUserDefinedPhenomenonSimulator->numberOfCandidate = row;

    itemList.clear();

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

void RPSUserDefinedPhenomenonAccuracyComparisonDialog::readTableItemsFromList(std::vector<QString> itemList)
{
    RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();
    int row = rpsUserDefinedPhenomenonSimulator->numberOfCandidate;
    int col = 4;
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
