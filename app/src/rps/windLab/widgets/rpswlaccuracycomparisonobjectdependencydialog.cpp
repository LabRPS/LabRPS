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

    ui->comboBoxCumulativeProbabilityDistribution->clear();
    ui->comboBoxGustFactor->clear();
    ui->comboBoxKurtosis->clear();
    ui->comboBoxPeakFactor->clear();
    ui->comboBoxProbabilityDensityFunction->clear();
    ui->comboBoxRoughness->clear();
    ui->comboBoxShearVelocityOfFlow->clear();
    ui->comboBoxskewness->clear();
    ui->comboBoxStandardDeviation->clear();
    ui->comboBoxTurbulenceIntensity->clear();
    ui->comboBoxTurbulenceScale->clear();
    ui->comboBoxVariance->clear();
    ui->comboBoxWavePassageEffect->clear();


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

    ui->comboBoxCumulativeProbabilityDistribution->addItem(noSelection);
    ui->comboBoxGustFactor->addItem(noSelection);
    ui->comboBoxKurtosis->addItem(noSelection);
    ui->comboBoxPeakFactor->addItem(noSelection);
    ui->comboBoxProbabilityDensityFunction->addItem(noSelection);
    ui->comboBoxRoughness->addItem(noSelection);
    ui->comboBoxShearVelocityOfFlow->addItem(noSelection);
    ui->comboBoxskewness->addItem(noSelection);
    ui->comboBoxStandardDeviation->addItem(noSelection);
    ui->comboBoxTurbulenceIntensity->addItem(noSelection);
    ui->comboBoxTurbulenceScale->addItem(noSelection);
    ui->comboBoxVariance->addItem(noSelection);
    ui->comboBoxWavePassageEffect->addItem(noSelection);

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

    ui->comboBoxCumulativeProbabilityDistribution->addItems(rpsWindLabSimulator->FindAllCumulativeProbabilityDistribution());
    ui->comboBoxGustFactor->addItems(rpsWindLabSimulator->FindAllGustFactor());
    ui->comboBoxKurtosis->addItems(rpsWindLabSimulator->FindAllKurtosis());
    ui->comboBoxPeakFactor->addItems(rpsWindLabSimulator->FindAllPeakFactor());
    ui->comboBoxProbabilityDensityFunction->addItems(rpsWindLabSimulator->FindAllProbabilityDensityFunction());
    ui->comboBoxRoughness->addItems(rpsWindLabSimulator->FindAllRoughness());
    ui->comboBoxShearVelocityOfFlow->addItems(rpsWindLabSimulator->FindAllShearVelocityOfFlow());
    ui->comboBoxskewness->addItems(rpsWindLabSimulator->FindAllSkewness());
    ui->comboBoxStandardDeviation->addItems(rpsWindLabSimulator->FindAllStandardDeviation());
    ui->comboBoxTurbulenceIntensity->addItems(rpsWindLabSimulator->FindAllTurbulenceIntensity());
    ui->comboBoxTurbulenceScale->addItems(rpsWindLabSimulator->FindAllTurbulenceScale());
    ui->comboBoxVariance->addItems(rpsWindLabSimulator->FindAllVariance());
    ui->comboBoxWavePassageEffect->addItems(rpsWindLabSimulator->FindAllWavePassageEffect());

    ui->comboBoxCoherence->setCurrentText(rpsWindLabSimulator->coherence_);
    ui->comboBoxCorrelation->setCurrentText(rpsWindLabSimulator->correlation_);
    ui->comboBoxFrequency->setCurrentText(rpsWindLabSimulator->frequency_);
    ui->comboBoxMean->setCurrentText(rpsWindLabSimulator->mean_);
    ui->comboBoxModulation->setCurrentText(rpsWindLabSimulator->modulation_);
    ui->comboBoxDecomposition->setCurrentText(rpsWindLabSimulator->decomposition_);
    ui->comboBoxSimuMethod->setCurrentText(rpsWindLabSimulator->simulation_);
    ui->comboBoxSpatial->setCurrentText(rpsWindLabSimulator->spatial_);
    ui->comboBoxRandomness->setCurrentText(rpsWindLabSimulator->randomness_);
    ui->comboBoxSpectrum->setCurrentText(rpsWindLabSimulator->spectrum_);

    ui->comboBoxCumulativeProbabilityDistribution->setCurrentText(rpsWindLabSimulator->cumulativeProbabilityDistribution_);
    ui->comboBoxGustFactor->setCurrentText(rpsWindLabSimulator->gustFactor_);
    ui->comboBoxKurtosis->setCurrentText(rpsWindLabSimulator->kurtosis_);
    ui->comboBoxPeakFactor->setCurrentText(rpsWindLabSimulator->peakFactor_);
    ui->comboBoxProbabilityDensityFunction->setCurrentText(rpsWindLabSimulator->probabilityDensityFunction_);
    ui->comboBoxRoughness->setCurrentText(rpsWindLabSimulator->roughness_);
    ui->comboBoxShearVelocityOfFlow->setCurrentText(rpsWindLabSimulator->shearVelocityOfFlow_);
    ui->comboBoxskewness->setCurrentText(rpsWindLabSimulator->skewness_);
    ui->comboBoxStandardDeviation->setCurrentText(rpsWindLabSimulator->standardDeviation_);
    ui->comboBoxTurbulenceIntensity->setCurrentText(rpsWindLabSimulator->turbulenceIntensity_);
    ui->comboBoxTurbulenceScale->setCurrentText(rpsWindLabSimulator->turbulenceScale_);
    ui->comboBoxVariance->setCurrentText(rpsWindLabSimulator->variance_);
    ui->comboBoxWavePassageEffect->setCurrentText(rpsWindLabSimulator->wavePassageEffect_);


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

    connect( ui->pushButtonCumulativeProbabilityDistribution, SIGNAL( clicked() ), this, SLOT( OnBnClickedCumulativeProbabilityDistribution( ) ) );
    connect( ui->pushButtonGustFactor, SIGNAL( clicked() ), this, SLOT( OnBnClickedGustFactor( ) ) );
    connect( ui->pushButtonKurtosis, SIGNAL( clicked() ), this, SLOT( OnBnClickedKurtosis( ) ) );
    connect( ui->pushButtonPeakFactor, SIGNAL( clicked() ), this, SLOT( OnBnClickedPeakFactor( ) ) );
    connect( ui->pushButtonProbabilityDensityFunction, SIGNAL( clicked() ), this, SLOT( OnBnClickedProbabilityDensityFunction( ) ) );
    connect( ui->pushButtonRoughness, SIGNAL( clicked() ), this, SLOT( OnBnClickedRoughness( ) ) );
    connect( ui->pushButtonShearVelocityOfFlow, SIGNAL( clicked() ), this, SLOT( OnBnClickedShearVelocityOfFlow( ) ) );
    connect( ui->pushButtonSkewness, SIGNAL( clicked() ), this, SLOT( OnBnClickedSkewness( ) ) );
    connect( ui->pushButtonStandardDeviation, SIGNAL( clicked() ), this, SLOT( OnBnClickedStandardDeviation( ) ) );
    connect( ui->pushButtonTurbulenceIntensity, SIGNAL( clicked() ), this, SLOT( OnBnClickedTurbulenceIntensity( ) ) );
    connect( ui->pushButtonTurbulenceScale, SIGNAL( clicked() ), this, SLOT( OnBnClickedTurbulenceScale( ) ) );
    connect( ui->pushButtonVariance, SIGNAL( clicked() ), this, SLOT( OnBnClickedVariance( ) ) );
    connect( ui->pushButtonWavePassageEffect, SIGNAL( clicked() ), this, SLOT( OnBnClickedWavePassageEffect( ) ) );


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

     cumulativeProbabilityDistribution = ui->comboBoxCumulativeProbabilityDistribution->currentText();
     gustFactor = ui->comboBoxGustFactor->currentText();
     kurtosis = ui->comboBoxKurtosis->currentText();
     peakFactor = ui->comboBoxPeakFactor->currentText();
     probabilityDensityFunction = ui->comboBoxProbabilityDensityFunction->currentText();
     roughness = ui->comboBoxRoughness->currentText();
     shearVelocityOfFlow = ui->comboBoxShearVelocityOfFlow->currentText();
     skewness = ui->comboBoxskewness->currentText();
     standardDeviation = ui->comboBoxStandardDeviation->currentText();
     turbulenceIntensity = ui->comboBoxTurbulenceIntensity->currentText();
     turbulenceScale = ui->comboBoxTurbulenceScale->currentText();
     variance = ui->comboBoxVariance->currentText();
     wavePassageEffect = ui->comboBoxWavePassageEffect->currentText();

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
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedCumulativeProbabilityDistribution( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->CumulativeProbabilityDistributionInital(ui->comboBoxCumulativeProbabilityDistribution->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedGustFactor( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->GustFactorInital(ui->comboBoxCumulativeProbabilityDistribution->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedKurtosis( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->KurtosisInital(ui->comboBoxKurtosis->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedPeakFactor( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->PeakFactorInital(ui->comboBoxPeakFactor->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedProbabilityDensityFunction( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->ProbabilityDensityFunctionInital(ui->comboBoxProbabilityDensityFunction->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedRoughness( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->RoughnessInital(ui->comboBoxRoughness->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedShearVelocityOfFlow( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->ShearVelocityOfFlowInital(ui->comboBoxShearVelocityOfFlow->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedSkewness( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->SkewnessInital(ui->comboBoxskewness->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedStandardDeviation( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->StandardDeviationInital(ui->comboBoxStandardDeviation->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedTurbulenceIntensity( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->TurbulenceIntensityInital(ui->comboBoxTurbulenceIntensity->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedTurbulenceScale( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->TurbulenceScaleInital(ui->comboBoxTurbulenceScale->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedVariance( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->VarianceInital(ui->comboBoxVariance->currentText());
}
void RPSWLAccuracyComparisonObjectDependencyDialog::OnBnClickedWavePassageEffect( )
{
    RPSWindLabSimulation *rpsWindLabSimulator = qobject_cast<RPSWindLabSimulation *>(this->parent()->parent());
    rpsWindLabSimulator->WavePassageEffectInital(ui->comboBoxWavePassageEffect->currentText());
}
