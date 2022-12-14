#include "rpswlroughnessdlg.h"
#include "ui_rpswlroughnessdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLRoughnessDlg::RPSWLRoughnessDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLRoughnessDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    roughness = rpsWindLabSimulator->GetWindLabData().roughness;

    ui->comboBoxRoughness->clear();
    ui->comboBoxRoughness->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLRoughness *(*CreateRoughnessCallback)();
	std::map<const QString, CreateRoughnessCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsRoughnessFactory::GetObjectNamesMap().begin(); cohIt != CrpsRoughnessFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxRoughness->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxRoughness->findText(roughness)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxRoughness->setCurrentText(roughness);
	}
	else if ((nDex == ui->comboBoxRoughness->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxRoughness->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxRoughness, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxRoughnessFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedRoughnessInit( ) ) );


}

RPSWLRoughnessDlg::~RPSWLRoughnessDlg()
{
    delete ui;
}

void RPSWLRoughnessDlg::comboBoxRoughnessFnIndexChanged(int index)
{
    roughness = ui->comboBoxRoughness->currentText();
}

void RPSWLRoughnessDlg::OnBnClickedRoughnessInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLRoughness* currentSelection = CrpsRoughnessFactory::BuildObject(roughness);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
