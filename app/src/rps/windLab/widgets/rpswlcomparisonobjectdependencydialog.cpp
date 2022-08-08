#include "rpswlcomparisonobjectdependencydialog.h"
#include "ui_rpswlcomparisonobjectdependencydialog.h"
#include "rpswlcomparisondialog.h"

#include "RPSWindLabAPI.h"
#include "rps/windLab/rpsWindLabSimulation.h"


RPSWLComparisonObjectDependencyDialog::RPSWLComparisonObjectDependencyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLComparisonObjectDependencyDialog)
{
    ui->setupUi(this);

    noSelection = "<None>";

    RPSWindLabSimulation *rpsWindLabSimulator =
        qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
	
    RPSWLComparisonDialog *rpsWindLabcomparisonDlg = (RPSWLComparisonDialog *)this->parent();

    ui->comboBoxCoherence->clear();
    ui->comboBoxCorrelation->clear();
    ui->comboBoxFrequency->clear();
    ui->comboBoxMean->clear();
    ui->comboBoxModulation->clear();
    ui->comboBoxDecomposition->clear();
    ui->comboBoxSimuMethod->clear();
    ui->comboBoxSpatial->clear();
    ui->comboBoxRandomness->clear();
    ui->comboBoxSpectrum->clear();

    ui->comboBoxCoherence->addItem(noSelection);
    ui->comboBoxCorrelation->addItem(noSelection);
    ui->comboBoxFrequency->addItem(noSelection);
    ui->comboBoxMean->addItem(noSelection);
    ui->comboBoxModulation->addItem(noSelection);
    ui->comboBoxDecomposition->addItem(noSelection);
    ui->comboBoxSimuMethod->addItem(noSelection);
    ui->comboBoxSpatial->addItem(noSelection);
    ui->comboBoxRandomness->addItem(noSelection);
    ui->comboBoxSpectrum->addItem(noSelection);

    ui->comboBoxCoherence->addItems(rpsWindLabSimulator->FindAllCoherenceFunction());
    ui->comboBoxCorrelation->addItems(rpsWindLabSimulator->FindAllCorrelationFunctions());
    ui->comboBoxFrequency->addItems(rpsWindLabSimulator->FindAllFrequencyDistributions());
    ui->comboBoxMean->addItems(rpsWindLabSimulator->FindAllMeanWindProfils());
    ui->comboBoxModulation->addItems(rpsWindLabSimulator->FindAllModulationFunctions());
    ui->comboBoxDecomposition->addItems(rpsWindLabSimulator->FindAllPSDDecompositionMethods());
    ui->comboBoxSimuMethod->addItems(rpsWindLabSimulator->FindAllSimulationMethods());
    ui->comboBoxSpatial->addItems(rpsWindLabSimulator->FindAllSpatialDistribution());
    ui->comboBoxRandomness->addItems(rpsWindLabSimulator->FindAllRandomnessProvider());
    ui->comboBoxSpectrum->addItems(rpsWindLabSimulator->FindAllSpectrumModels());

    ui->comboBoxCoherence->setCurrentText(rpsWindLabcomparisonDlg->coherence);
    ui->comboBoxCorrelation->setCurrentText(rpsWindLabcomparisonDlg->correlation);
    ui->comboBoxFrequency->setCurrentText(rpsWindLabcomparisonDlg->frequency);
    ui->comboBoxMean->setCurrentText(rpsWindLabcomparisonDlg->mean);
    ui->comboBoxModulation->setCurrentText(rpsWindLabcomparisonDlg->modulation);
    ui->comboBoxDecomposition->setCurrentText(rpsWindLabcomparisonDlg->decomposition);
    ui->comboBoxSimuMethod->setCurrentText(rpsWindLabcomparisonDlg->simulation);
    ui->comboBoxSpatial->setCurrentText(rpsWindLabcomparisonDlg->spatial);
    ui->comboBoxRandomness->setCurrentText(rpsWindLabcomparisonDlg->randomness);
    ui->comboBoxSpectrum->setCurrentText(rpsWindLabcomparisonDlg->spectrum);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

RPSWLComparisonObjectDependencyDialog::~RPSWLComparisonObjectDependencyDialog()
{
    delete ui;
}

void RPSWLComparisonObjectDependencyDialog::acceptInput()
{
    coherence = ui->comboBoxCoherence->currentText();
     correlation = ui->comboBoxCorrelation->currentText();
     frequency = ui->comboBoxFrequency->currentText();
     mean = ui->comboBoxMean->currentText();
     modulation = ui->comboBoxModulation->currentText();
     decomposition = ui->comboBoxDecomposition->currentText();
     simulation = ui->comboBoxSimuMethod->currentText();
     spatial = ui->comboBoxSpatial->currentText();
     randomness = ui->comboBoxRandomness->currentText();
     spectrum = ui->comboBoxSpectrum->currentText();

}

