#include "rpswlturbulenceintensitydlg.h"
#include "ui_rpswlturbulenceintensitydlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLTurbulenceIntensityDlg::RPSWLTurbulenceIntensityDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLTurbulenceIntensityDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    turbulenceIntensity = rpsWindLabSimulator->GetWindLabData().turbulenceIntensity;

    ui->comboBoxTurbulenceIntensity->clear();
    ui->comboBoxTurbulenceIntensity->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLTurbulenceIntensity *(*CreateTurbulenceIntensityCallback)();
	std::map<const QString, CreateTurbulenceIntensityCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsTurbulenceIntensityFactory::GetObjectNamesMap().begin(); cohIt != CrpsTurbulenceIntensityFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxTurbulenceIntensity->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxTurbulenceIntensity->findText(turbulenceIntensity)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxTurbulenceIntensity->setCurrentText(turbulenceIntensity);
	}
	else if ((nDex == ui->comboBoxTurbulenceIntensity->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxTurbulenceIntensity->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxTurbulenceIntensity, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxTurbulenceIntensityFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedTurbulenceIntensityInit( ) ) );


}

RPSWLTurbulenceIntensityDlg::~RPSWLTurbulenceIntensityDlg()
{
    delete ui;
}

void RPSWLTurbulenceIntensityDlg::comboBoxTurbulenceIntensityFnIndexChanged(int index)
{
    turbulenceIntensity = ui->comboBoxTurbulenceIntensity->currentText();
}

void RPSWLTurbulenceIntensityDlg::OnBnClickedTurbulenceIntensityInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLTurbulenceIntensity* currentSelection = CrpsTurbulenceIntensityFactory::BuildObject(turbulenceIntensity);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
