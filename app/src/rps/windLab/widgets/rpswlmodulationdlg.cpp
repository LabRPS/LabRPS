#include "rpswlmodulationdlg.h"
#include "ui_rpswlmodulationdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLModulationDlg::RPSWLModulationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLModulationDlg)
{
    ui->setupUi(this);

     QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    modulationFunction = rpsWindLabSimulator->GetWindLabData().modulationFunction;

    ui->comboBoxModulationFunc->clear();
    ui->comboBoxModulationFunc->addItem(noSelection);

    /////******modulation model start*******/////////
	typedef IrpsWLModulation *(*CreateModulationCallback)();
	std::map<const QString, CreateModulationCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsModulationFactory::GetObjectNamesMap().begin(); cohIt != CrpsModulationFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxModulationFunc->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxModulationFunc->findText(modulationFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxModulationFunc->setCurrentText(modulationFunction);
	}
	else if ((nDex == ui->comboBoxModulationFunc->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxModulationFunc->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxModulationFunc, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxModulationFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonModulationInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedModulationFnInit( ) ) );


}

RPSWLModulationDlg::~RPSWLModulationDlg()
{
    delete ui;
}

void RPSWLModulationDlg::comboBoxModulationFnIndexChanged(int index)
{
    modulationFunction = ui->comboBoxModulationFunc->currentText();
}

void RPSWLModulationDlg::OnBnClickedModulationFnInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLModulation* currentSelection = CrpsModulationFactory::BuildObject(modulationFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
