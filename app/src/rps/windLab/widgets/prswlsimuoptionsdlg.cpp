#include "prswlsimuoptionsdlg.h"
#include "ui_prswlsimuoptionsdlg.h"

#include "RPSWindLabAPI.h"
#include "rps/windLab/rpsWindLabSimulation.h"


PRSWLSimuOptionsDlg::PRSWLSimuOptionsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PRSWLSimuOptionsDlg)
{
    ui->setupUi(this);

    noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	currentRandomnessProvider = rpsWindLabSimulator->GetWindLabData().randomnessProvider;
	currentsimulationMethod = rpsWindLabSimulator->GetWindLabData().simulationMethod;
	comparisonMode = rpsWindLabSimulator->GetWindLabData().comparisonMode;
    largeScaleMode = rpsWindLabSimulator->GetWindLabData().largeScaleSimulationMode; 
    
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
	typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();
	std::map<const QString, CreateSimuMethodCallback> ::iterator simuMethIt;
		
    // Iterate though the map and show all the registed randomness providers in the combo box
	for (simuMethIt = CrpsSimuMethodFactory::GetSimuMethodNamesMap().begin(); simuMethIt != CrpsSimuMethodFactory::GetSimuMethodNamesMap().end(); ++simuMethIt)
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

    typedef IrpsWLRandomness *(*CreateRandomnessCallback)();
	std::map<const QString, CreateRandomnessCallback> ::iterator randIt;
		
    // Iterate though the map and show all the registed randomness providers in the combo box
	for (randIt = CrpsRandomnessFactory::GetRandomnessNamesMap().begin(); randIt != CrpsRandomnessFactory::GetRandomnessNamesMap().end(); ++randIt)
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

PRSWLSimuOptionsDlg::~PRSWLSimuOptionsDlg()
{
    delete ui;
}

void PRSWLSimuOptionsDlg::comboBoxRandomnessCurrentIndexChanged( int index)
{
	 currentRandomnessProvider = ui->comboBoxRandomness->currentText();

}

void PRSWLSimuOptionsDlg::comboBoxSimuMethodCurrentIndexChanged( int index)
{
	 currentsimulationMethod = ui->comboBoxSimuMethod->currentText();

}

void PRSWLSimuOptionsDlg::checkBoxComparisonModeChanged( int state)
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

void PRSWLSimuOptionsDlg::checkBoxSLargeScaleSimulationModeChanged( int state)
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

void PRSWLSimuOptionsDlg::OnBnClickedRandomnessInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLRandomness* currentRndProvider = CrpsRandomnessFactory::BuildRandomness(currentRandomnessProvider);

	// Check whether good object
	if (NULL == currentRndProvider) { return; }

	// Apply iniatial setting
	currentRndProvider->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentRndProvider;
}

