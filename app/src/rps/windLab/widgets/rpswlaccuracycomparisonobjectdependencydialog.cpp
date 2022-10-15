#include "rpswlaccuracycomparisonobjectdependencydialog.h"
#include "ui_rpswlaccuracycomparisonobjectdependencydialog.h"
#include "rpswlaccuracycomparisondialog.h"

#include "RPSWindLabAPI.h"
#include "rps/windLab/rpsWindLabSimulation.h"


RPSWLAccuracyComparisonObjectDependencyDialog::RPSWLAccuracyComparisonObjectDependencyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLAccuracyComparisonObjectDependencyDialog)
{
    ui->setupUi(this);

    noSelection = "<None>";

    RPSWindLabSimulation *rpsWindLabSimulator =
        qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
	
    RPSWLAccuracyComparisonDialog *rpsWindLabcomparisonDlg = (RPSWLAccuracyComparisonDialog *)this->parent();

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
    connect( ui->pushButtonCoherenceInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedCoherenceInit( ) ) );
    connect( ui->pushButtonCorrelationInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedCorrelationInit( ) ) );
    connect( ui->pushButtonFrequencyDistrInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedFrequencyDistrInit( ) ) );
    connect( ui->pushButtonSpatialDistrInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedSpatialDistrInit( ) ) );
    connect( ui->pushButtonMeanWindInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedMeanWindInit( ) ) );
    connect( ui->pushButtonModulationInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedModulationInit( ) ) );
    connect( ui->pushButtonSimuMethodInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedSimuMethodInit( ) ) );
    connect( ui->pushButtonRandomnessProInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedRandomnessInit( ) ) );
    connect( ui->pushButtonSpectrumDecompInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedSpectrumDecompInit( ) ) );
    connect( ui->pushButtonSpectrumInit, SIGNAL( clicked() ), this, SLOT( OnBnClickedSpectrumInit( ) ) );

}

RPSWLAccuracyComparisonObjectDependencyDialog::~RPSWLAccuracyComparisonObjectDependencyDialog()
{
    delete ui;
}

void RPSWLAccuracyComparisonObjectDependencyDialog::acceptInput()
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

void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedCoherenceInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->CoherenceFunctionInital(ui->comboBoxCoherence->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedCorrelationInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->correlationFunctionInital(ui->comboBoxCorrelation->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedFrequencyDistrInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->frequencyDistributionInital(ui->comboBoxFrequency->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedSpatialDistrInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->locationDistributionFunctionInital(ui->comboBoxSpatial->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedMeanWindInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->meanWindProfilInital(ui->comboBoxMean->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedModulationInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->modulationFunctionInital(ui->comboBoxModulation->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedSimuMethodInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->simulationMethodInital(ui->comboBoxSimuMethod->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedRandomnessInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->randomnessProviderInital(ui->comboBoxRandomness->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedSpectrumDecompInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->psdDecompositionMethodInital(ui->comboBoxDecomposition->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedSpectrumInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->spectrumModelInital(ui->comboBoxSpectrum->currentText());
}
