#include "rpsslmodulationdlg.h"
#include "ui_rpsslmodulationdlg.h"

#include "rps/seismicLab/rpsSeismicLabSimulation.h"
#include "RPSSeismicLabAPI.h"

RPSSLModulationDlg::RPSSLModulationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSLModulationDlg)
{
    ui->setupUi(this);

     QString noSelection = "<None>";

	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

    modulationFunction = rpsSeismicLabSimulator->GetSeismicLabData().modulationFunction;

    ui->comboBoxModulationFunc->clear();
    ui->comboBoxModulationFunc->addItem(noSelection);

    /////******modulation model start*******/////////
	typedef IrpsSLModulation *(*CreateModulationCallback)();
	std::map<const QString, CreateModulationCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (cohIt = CrpsSLModulationFactory::GetModulationNamesMap().begin(); cohIt != CrpsSLModulationFactory::GetModulationNamesMap().end(); ++cohIt)
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

RPSSLModulationDlg::~RPSSLModulationDlg()
{
    delete ui;
}

void RPSSLModulationDlg::comboBoxModulationFnIndexChanged(int index)
{
    modulationFunction = ui->comboBoxModulationFunc->currentText();
}

void RPSSLModulationDlg::OnBnClickedModulationFnInit()
{
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLModulation* currentSelection = CrpsSLModulationFactory::BuildModulation(modulationFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
