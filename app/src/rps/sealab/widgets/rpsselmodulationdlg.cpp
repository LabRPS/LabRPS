#include "rpsselmodulationdlg.h"
#include "ui_rpsselmodulationdlg.h"

#include "ApplicationWindow.h"
#include "RPSSeaLabAPI.h"

RPSSeLModulationDlg::RPSSeLModulationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSeLModulationDlg)
{
    ui->setupUi(this);

     QString noSelection = "<None>";

	RPSSeaLabSimulation *rpsSeaLabSimulator = (RPSSeaLabSimulation *)this->parent();

    modulationFunction = rpsSeaLabSimulator->GetSeaLabData().modulationFunction;

    ui->comboBoxModulationFunc->clear();
    ui->comboBoxModulationFunc->addItem(noSelection);

    /////******modulation model start*******/////////
	typedef IrpsSeLModulation *(*CreateModulationCallback)();
	std::map<const QString, CreateModulationCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (cohIt = CrpsSeLModulationFactory::GetModulationNamesMap().begin(); cohIt != CrpsSeLModulationFactory::GetModulationNamesMap().end(); ++cohIt)
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

RPSSeLModulationDlg::~RPSSeLModulationDlg()
{
    delete ui;
}

void RPSSeLModulationDlg::comboBoxModulationFnIndexChanged(int index)
{
    modulationFunction = ui->comboBoxModulationFunc->currentText();
}

void RPSSeLModulationDlg::OnBnClickedModulationFnInit()
{
	RPSSeaLabSimulation *rpsSeaLabSimulator = (RPSSeaLabSimulation *)this->parent();

	// Build an object
	IrpsSeLModulation* currentSelection = CrpsSeLModulationFactory::BuildModulation(modulationFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeaLabSimulator->GetSeaLabData(), rpsSeaLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
