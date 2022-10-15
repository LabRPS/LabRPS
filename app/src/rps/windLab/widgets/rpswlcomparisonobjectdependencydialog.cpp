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

void RPSWLComparisonObjectDependencyDialog::OnBnClickedCoherenceInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->CoherenceFunctionInital(ui->comboBoxCoherence->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedCorrelationInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->correlationFunctionInital(ui->comboBoxCorrelation->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedFrequencyDistrInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->frequencyDistributionInital(ui->comboBoxFrequency->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedSpatialDistrInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->locationDistributionFunctionInital(ui->comboBoxSpatial->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedMeanWindInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->meanWindProfilInital(ui->comboBoxMean->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedModulationInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->modulationFunctionInital(ui->comboBoxModulation->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedSimuMethodInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->simulationMethodInital(ui->comboBoxSimuMethod->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedRandomnessInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->randomnessProviderInital(ui->comboBoxRandomness->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedSpectrumDecompInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->psdDecompositionMethodInital(ui->comboBoxDecomposition->currentText());
}
void RPSWLComparisonObjectDependencyDialog::OnBnClickedSpectrumInit( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->spectrumModelInital(ui->comboBoxSpectrum->currentText());
}

