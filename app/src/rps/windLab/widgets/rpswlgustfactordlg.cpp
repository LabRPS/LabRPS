#include "rpswlgustfactordlg.h"
#include "ui_rpswlgustfactordlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLGustFactorDlg::RPSWLGustFactorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLGustFactorDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    gustFactor = rpsWindLabSimulator->GetWindLabData().gustFactor;

    ui->comboBoxGustFactor->clear();
    ui->comboBoxGustFactor->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLGustFactor *(*CreateGustFactorCallback)();
	std::map<const QString, CreateGustFactorCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsGustFactorFactory::GetObjectNamesMap().begin(); cohIt != CrpsGustFactorFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxGustFactor->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxGustFactor->findText(gustFactor)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxGustFactor->setCurrentText(gustFactor);
	}
	else if ((nDex == ui->comboBoxGustFactor->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxGustFactor->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxGustFactor, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxGustFactorFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedGustFactorInit( ) ) );


}

RPSWLGustFactorDlg::~RPSWLGustFactorDlg()
{
    delete ui;
}

void RPSWLGustFactorDlg::comboBoxGustFactorFnIndexChanged(int index)
{
    gustFactor = ui->comboBoxGustFactor->currentText();
}

void RPSWLGustFactorDlg::OnBnClickedGustFactorInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLGustFactor* currentSelection = CrpsGustFactorFactory::BuildObject(gustFactor);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
