#include "rpswlwavepassageeffectdlg.h"
#include "ui_rpswlwavepassageeffectdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLWavePassageEffectDlg::RPSWLWavePassageEffectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLWavePassageEffectDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    wavePassageEffect = rpsWindLabSimulator->GetWindLabData().wavePassageEffect;

    ui->comboBoxWavePassageEffect->clear();
    ui->comboBoxWavePassageEffect->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLWavePassageEffect *(*CreateWavePassageEffectCallback)();
	std::map<const QString, CreateWavePassageEffectCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsWavePassageEffectFactory::GetObjectNamesMap().begin(); cohIt != CrpsWavePassageEffectFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxWavePassageEffect->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxWavePassageEffect->findText(wavePassageEffect)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxWavePassageEffect->setCurrentText(wavePassageEffect);
	}
	else if ((nDex == ui->comboBoxWavePassageEffect->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxWavePassageEffect->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxWavePassageEffect, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxWavePassageEffectFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedWavePassageEffectInit( ) ) );


}

RPSWLWavePassageEffectDlg::~RPSWLWavePassageEffectDlg()
{
    delete ui;
}

void RPSWLWavePassageEffectDlg::comboBoxWavePassageEffectFnIndexChanged(int index)
{
    wavePassageEffect = ui->comboBoxWavePassageEffect->currentText();
}

void RPSWLWavePassageEffectDlg::OnBnClickedWavePassageEffectInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLWavePassageEffect* currentSelection = CrpsWavePassageEffectFactory::BuildObject(wavePassageEffect);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
