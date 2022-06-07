#include "prsselsimuoptionsdlg.h"
#include "ui_prsselsimuoptionsdlg.h"

#include "RPSSeaLabAPI.h"

PRSSeLSimuOptionsDlg::PRSSeLSimuOptionsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PRSSeLSimuOptionsDlg)
{
    ui->setupUi(this);

    noSelection = "<None>";

	RPSSeaLabSimulation *rpsSeaLabSimulator = (RPSSeaLabSimulation *)this->parent();

	currentRandomnessProvider = rpsSeaLabSimulator->GetSeaLabData().randomnessProvider;
	currentsimulationMethod = rpsSeaLabSimulator->GetSeaLabData().simulationMethod;
	comparisonMode = rpsSeaLabSimulator->GetSeaLabData().comparisonMode;
    largeScaleMode = rpsSeaLabSimulator->GetSeaLabData().largeScaleSimulationMode; 
    
	if(true == comparisonMode)
	{
		ui->checkBoxComparMode->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBoxComparMode->setCheckState(Qt::Unchecked);
	}

	 if(true == largeScaleMode)
	{
		ui->checkBoxLargeScaleMode->setCheckState(Qt::Checked);
	}
	else
	{
	   ui->checkBoxLargeScaleMode->setCheckState(Qt::Unchecked);

	}

	///////


    ui->comboBoxRandomness->clear();
    ui->comboBoxSimuMethod->clear();

	ui->comboBoxRandomness->addItem(noSelection);
	ui->comboBoxSimuMethod->addItem(noSelection);

	/////******simulation method start*******/////////
	typedef IrpsSeLSimulationMethod *(*CreateSLSimulationMethodCallback)();
	std::map<const QString, CreateSLSimulationMethodCallback> ::iterator simuMethIt;
		
    // Iterate though the map and show all the registed randomness providers in the combo box
	for (simuMethIt = CrpsSeLSimulationMethodFactory::GetSLSimulationMethodNamesMap().begin(); simuMethIt != CrpsSeLSimulationMethodFactory::GetSLSimulationMethodNamesMap().end(); ++simuMethIt)
	{

		// Add it to the combo box
		ui->comboBoxSimuMethod->addItem(simuMethIt->first);

	}

	// Show the current selected randomness
	// Starting index
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxSimuMethod->findText(currentsimulationMethod)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSimuMethod->setCurrentText(currentsimulationMethod);
	}
	else if ((nDex == ui->comboBoxSimuMethod->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSimuMethod->setCurrentText(noSelection);
	}

	/////******simulation method end*******/////////

	////*******randomness provider start***/////////

    typedef IrpsSeLRandomness *(*CreateRandomnessCallback)();
	std::map<const QString, CreateRandomnessCallback> ::iterator randIt;
		
    // Iterate though the map and show all the registed randomness providers in the combo box
	for (randIt = CrpsSeLRandomnessFactory::GetRandomnessNamesMap().begin(); randIt != CrpsSeLRandomnessFactory::GetRandomnessNamesMap().end(); ++randIt)
	{

		// Add it to the combo box
		ui->comboBoxRandomness->addItem(randIt->first);

	}

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxRandomness->findText(currentRandomnessProvider)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxRandomness->setCurrentText(currentRandomnessProvider);
	}
	else if ((nDex == ui->comboBoxRandomness->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxRandomness->setCurrentText(noSelection);
	}

		////randomness provider end/////////

	connect( ui->comboBoxRandomness, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxRandomnessCurrentIndexChanged( int ) ) );

	connect( ui->comboBoxSimuMethod, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxSimuMethodCurrentIndexChanged( int ) ) );
  
    connect( ui->checkBoxComparMode, SIGNAL( stateChanged( int ) ),
             this, SLOT( checkBoxComparisonModeChanged( int ) ) );
  
    connect( ui->checkBoxLargeScaleMode, SIGNAL( stateChanged( int ) ),
             this, SLOT( checkBoxSLargeScaleSimulationModeChanged( int ) ) );
   
   connect( ui->pushButtonRandomnessInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedRandomnessInit( ) ) );


}

PRSSeLSimuOptionsDlg::~PRSSeLSimuOptionsDlg()
{
    delete ui;
}

void PRSSeLSimuOptionsDlg::comboBoxRandomnessCurrentIndexChanged( int index)
{
	 currentRandomnessProvider = ui->comboBoxRandomness->currentText();

}

void PRSSeLSimuOptionsDlg::comboBoxSimuMethodCurrentIndexChanged( int index)
{
	 currentsimulationMethod = ui->comboBoxSimuMethod->currentText();

}

void PRSSeLSimuOptionsDlg::checkBoxComparisonModeChanged( int state)
{
	if(Qt::Checked == ui->checkBoxComparMode->checkState())
	{
		comparisonMode = true;
	}
	else if(Qt::Unchecked == ui->checkBoxComparMode->checkState())
	{
	   comparisonMode = false;
	}
}

void PRSSeLSimuOptionsDlg::checkBoxSLargeScaleSimulationModeChanged( int state)
{
	if(Qt::Checked == ui->checkBoxLargeScaleMode->checkState())
	{
		largeScaleMode = true;
	}
	else if(Qt::Unchecked == ui->checkBoxLargeScaleMode->checkState())
	{
	   largeScaleMode = false;
	}
}

void PRSSeLSimuOptionsDlg::OnBnClickedRandomnessInit()
{
	RPSSeaLabSimulation *rpsSeaLabSimulator = (RPSSeaLabSimulation *)this->parent();

	// Build an object
	IrpsSeLRandomness* currentRndProvider = CrpsSeLRandomnessFactory::BuildRandomness(currentRandomnessProvider);

	// Check whether good object
	if (NULL == currentRndProvider) { return; }

	// Apply iniatial setting
	currentRndProvider->OnInitialSetting(rpsSeaLabSimulator->GetSeaLabData(), rpsSeaLabSimulator->information);

	// Delete the object
	delete currentRndProvider;
}

