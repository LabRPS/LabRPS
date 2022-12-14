#include "rpswlturbulencescaledlg.h"
#include "ui_rpswlturbulencescaledlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLTurbulenceScaleDlg::RPSWLTurbulenceScaleDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLTurbulenceScaleDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    turbulenceScale = rpsWindLabSimulator->GetWindLabData().turbulenceScale;

    ui->comboBoxTurbulenceScale->clear();
    ui->comboBoxTurbulenceScale->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLTurbulenceScale *(*CreateTurbulenceScaleCallback)();
	std::map<const QString, CreateTurbulenceScaleCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsTurbulenceScaleFactory::GetObjectNamesMap().begin(); cohIt != CrpsTurbulenceScaleFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxTurbulenceScale->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxTurbulenceScale->findText(turbulenceScale)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxTurbulenceScale->setCurrentText(turbulenceScale);
	}
	else if ((nDex == ui->comboBoxTurbulenceScale->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxTurbulenceScale->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxTurbulenceScale, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxTurbulenceScaleFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedTurbulenceScaleInit( ) ) );


}

RPSWLTurbulenceScaleDlg::~RPSWLTurbulenceScaleDlg()
{
    delete ui;
}

void RPSWLTurbulenceScaleDlg::comboBoxTurbulenceScaleFnIndexChanged(int index)
{
    turbulenceScale = ui->comboBoxTurbulenceScale->currentText();
}

void RPSWLTurbulenceScaleDlg::OnBnClickedTurbulenceScaleInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLTurbulenceScale* currentSelection = CrpsTurbulenceScaleFactory::BuildObject(turbulenceScale);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
