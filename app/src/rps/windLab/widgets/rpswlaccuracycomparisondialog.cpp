#include "rpswlaccuracycomparisondialog.h"
#include "ui_rpswlaccuracycomparisondialog.h"

#include "RPSWindLabAPI.h"
#include "rps/windLab/rpsWindLabSimulation.h"
#include "rpswlaccuracycomparisonobjectdependencydialog.h"
#include "rpswlaccuracycomparisontablezoomindialog.h"
#include <QMessageBox>


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
    // resultOutputType = rpsWindLabSimulator->resultOutputType;

    ui->comboBoxCategory->clear();
    ui->comboBoxFunction->clear();
    ui->comboBoxCandidate->clear();

    ui->comboBoxCategory->addItem(noSelection);
    ui->comboBoxFunction->addItem(noSelection);
    ui->comboBoxCandidate->addItem(noSelection);

    rpsWindLabSimulator->fillCategoryComboBox(ui->comboBoxCategory);
    rpsWindLabSimulator->fillFunctionAndCandidateComboBoxes(rpsWindLabSimulator->comparisonCategory, ui->comboBoxFunction, ui->comboBoxCandidate);

    // if (1 == resultOutputType)
    // {
    //     ui->radioButtonByLoc->setChecked(Qt::Checked);
    // }
    // else if (2 == resultOutputType)
    // {
    //     ui->radioButtonByFreq->setChecked(Qt::Checked);
    // }
    // else if (3 == resultOutputType)
    // {
    //     ui->radioButtonByTim->setChecked(Qt::Checked);
    // }

    QStringList tableHeader;
    ui->tableWidget->setColumnCount(26);
    tableHeader << "Candidate"
                << "Category"
                << "Function"
                << "Coherence function"
                << "Correlation function"
                << "Frequency distribution"
                << "Mean profile"
                << "Modulation Function"
                << "PSD decomposition method"
                << "Simulation method"
                << "Spatial distribution"
                << "Randomness provider"
                << "Spectrum model"
                << "Cumulative Probability Distribution"
                << "Gust Factor"
                << "Kurtosis"
                << "Peak Factor"
                << "Probability Density Function"
                << "Roughness"
                << "Shear Velocity of Flow"
                << "Skewness"
                << "Standard Deviation"
                << "Turbulence Intensity"
                << "Turbulence Scale"
                << "Variance"
                << "Wave Passage Effect";

    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    //ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // ui->tableWidget->setShowGrid(false);
    // ui->tableWidget->setStyleSheet("QTableView {selection-background-color: blue;}");

    if (rpsWindLabSimulator->GetWindLabData().comparisonType == 1) // accuracy
    {
      readTableItemsFromList(rpsWindLabSimulator->candidateList);
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

RPSWLAccuracyComparisonDialog::~RPSWLAccuracyComparisonDialog()
{
    delete ui;
}


void RPSWLAccuracyComparisonDialog::comboBoxCategoryCurrentIndexChanged(int)
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    QString cat = ui->comboBoxCategory->currentText();

    rpsWindLabSimulator->fillFunctionAndCandidateComboBoxes(cat, ui->comboBoxFunction, ui->comboBoxCandidate);

    ui->tableWidget->setRowCount(0);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->pushButtonAdd->setEnabled(true);
}

void RPSWLAccuracyComparisonDialog::comboBoxFunctionCurrentIndexChanged(int)
{
    ui->tableWidget->setRowCount(0);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->pushButtonAdd->setEnabled(true);
}

void RPSWLAccuracyComparisonDialog::OnBnClickedFunctionInit()
{
    std::unique_ptr<RPSWLAccuracyComparisonTableZoomInDialog> dlg(new RPSWLAccuracyComparisonTableZoomInDialog(this));
	
   dlg->exec();
}
void RPSWLAccuracyComparisonDialog::OnBnClickedCategoryInit()
{
     std::unique_ptr<RPSWLAccuracyComparisonObjectDependencyDialog> dlg(new RPSWLAccuracyComparisonObjectDependencyDialog(this));
	
    if (dlg->exec() == QDialog::Accepted)
	{
	 coherence = dlg->coherence;
     correlation = dlg->correlation;
     frequency = dlg->frequency;
     mean = dlg->mean;
     modulation = dlg->modulation;
     decomposition = dlg->decomposition;
     simulation = dlg->simulation;
     spatial = dlg->spatial;
     randomness = dlg->randomness;
     spectrum = dlg->spectrum;

     cumulativeProbabilityDistribution = dlg->cumulativeProbabilityDistribution;
     gustFactor = dlg->gustFactor;
     kurtosis = dlg->kurtosis;
     peakFactor = dlg->peakFactor;
     probabilityDensityFunction = dlg->probabilityDensityFunction;
     roughness = dlg->roughness;
     shearVelocityOfFlow = dlg->shearVelocityOfFlow;
     skewness = dlg->skewness;
     standardDeviation = dlg->standardDeviation;
     turbulenceIntensity = dlg->turbulenceIntensity;
     turbulenceScale = dlg->turbulenceScale;
     variance = dlg->variance;
     wavePassageEffect = dlg->wavePassageEffect;

	}
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
    //resultOutputType = 1;
}
void RPSWLAccuracyComparisonDialog::radioButtonByFrequencyToggled(bool)
{
    //resultOutputType = 2;
}
void RPSWLAccuracyComparisonDialog::radioButtonByTimeWindToggled(bool)
{
    //resultOutputType = 3;
}

void RPSWLAccuracyComparisonDialog::acceptInput()
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    comparisonCategory = ui->comboBoxCategory->currentText();
    comparisonFunction = ui->comboBoxFunction->currentText();
    comparisonCandidate = ui->comboBoxCandidate->currentText();
    
    rpsWindLabSimulator->candidateList.clear();
    saveTableItemsToList(rpsWindLabSimulator->candidateList);

}

void RPSWLAccuracyComparisonDialog::OnBnClickedTableAddRow()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();
    QTableWidgetItem *item5 = new QTableWidgetItem();
    QTableWidgetItem *item6 = new QTableWidgetItem();
    QTableWidgetItem *item7 = new QTableWidgetItem();
    QTableWidgetItem *item8 = new QTableWidgetItem();
    QTableWidgetItem *item9 = new QTableWidgetItem();
    QTableWidgetItem *item10 = new QTableWidgetItem();
    QTableWidgetItem *item11 = new QTableWidgetItem();
    QTableWidgetItem *item12 = new QTableWidgetItem();
    QTableWidgetItem *item13 = new QTableWidgetItem();
    QTableWidgetItem *item14 = new QTableWidgetItem();
    QTableWidgetItem *item15 = new QTableWidgetItem();
    QTableWidgetItem *item16 = new QTableWidgetItem();
    QTableWidgetItem *item17 = new QTableWidgetItem();
    QTableWidgetItem *item18 = new QTableWidgetItem();
    QTableWidgetItem *item19 = new QTableWidgetItem();
    QTableWidgetItem *item20 = new QTableWidgetItem();
    QTableWidgetItem *item21 = new QTableWidgetItem();
    QTableWidgetItem *item22 = new QTableWidgetItem();
    QTableWidgetItem *item23 = new QTableWidgetItem();
    QTableWidgetItem *item24 = new QTableWidgetItem();
    QTableWidgetItem *item25 = new QTableWidgetItem();
    QTableWidgetItem *item26 = new QTableWidgetItem();

    item1->setText(ui->comboBoxCandidate->currentText());
    item2->setText(ui->comboBoxCategory->currentText());
    item3->setText(ui->comboBoxFunction->currentText());
    item4->setText(coherence);
    item5->setText(correlation);
    item6->setText(frequency);
    item7->setText(mean);
    item8->setText(modulation);
    item9->setText(decomposition);
    item10->setText(simulation);
    item11->setText(spatial);
    item12->setText(randomness);
    item13->setText(spectrum); 
    item14->setText(cumulativeProbabilityDistribution);
    item15->setText(gustFactor);
    item16->setText(kurtosis);
    item17->setText(peakFactor);
    item18->setText(probabilityDensityFunction);
    item19->setText(roughness);
    item20->setText(shearVelocityOfFlow);
    item21->setText(skewness);
    item22->setText(standardDeviation);
    item23->setText(turbulenceIntensity);
    item24->setText(turbulenceScale);
    item25->setText(variance);
    item26->setText(wavePassageEffect);

    ui->tableWidget->setItem(row, 0, item1);
    ui->tableWidget->setItem(row, 1, item2);
    ui->tableWidget->setItem(row, 2, item3);
    ui->tableWidget->setItem(row, 3, item4);
    ui->tableWidget->setItem(row, 4, item5);
    ui->tableWidget->setItem(row, 5, item6);
    ui->tableWidget->setItem(row, 6, item7);
    ui->tableWidget->setItem(row, 7, item8);
    ui->tableWidget->setItem(row, 8, item9);
    ui->tableWidget->setItem(row, 9, item10);
    ui->tableWidget->setItem(row, 10, item11);
    ui->tableWidget->setItem(row, 11, item12);
    ui->tableWidget->setItem(row, 12, item13);
    ui->tableWidget->setItem(row, 13, item14);
    ui->tableWidget->setItem(row, 14, item15);
    ui->tableWidget->setItem(row, 15, item16);
    ui->tableWidget->setItem(row, 16, item17);
    ui->tableWidget->setItem(row, 17, item18);
    ui->tableWidget->setItem(row, 18, item19);
    ui->tableWidget->setItem(row, 19, item20);
    ui->tableWidget->setItem(row, 20, item21);
    ui->tableWidget->setItem(row, 21, item22);
    ui->tableWidget->setItem(row, 22, item23);
    ui->tableWidget->setItem(row, 23, item24);
    ui->tableWidget->setItem(row, 24, item25);
    ui->tableWidget->setItem(row, 25, item26);

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
void RPSWLAccuracyComparisonDialog::OnBnClickedTableDeleteRow()
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

void RPSWLAccuracyComparisonDialog::saveTableItemsToList(std::vector<QString> &itemList)
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    int row = ui->tableWidget->rowCount();
    int col = ui->tableWidget->columnCount();
    rpsWindLabSimulator->numberOfCandidate = row;

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

void RPSWLAccuracyComparisonDialog::readTableItemsFromList(std::vector<QString> itemList)
{
    if(itemList.empty()){return;}

    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    int row = rpsWindLabSimulator->numberOfCandidate;
    int col = 26;
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
