#include "rpswlkurtosisdlg.h"
#include "ui_rpswlkurtosisdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLKurtosisDlg::RPSWLKurtosisDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLKurtosisDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    kurtosis = rpsWindLabSimulator->GetWindLabData().kurtosis;

    ui->comboBoxKurtosis->clear();
    ui->comboBoxKurtosis->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLKurtosis *(*CreateKurtosisCallback)();
	std::map<const QString, CreateKurtosisCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsKurtosisFactory::GetObjectNamesMap().begin(); cohIt != CrpsKurtosisFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxKurtosis->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxKurtosis->findText(kurtosis)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxKurtosis->setCurrentText(kurtosis);
	}
	else if ((nDex == ui->comboBoxKurtosis->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxKurtosis->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxKurtosis, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxKurtosisFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedKurtosisInit( ) ) );


}

RPSWLKurtosisDlg::~RPSWLKurtosisDlg()
{
    delete ui;
}

void RPSWLKurtosisDlg::comboBoxKurtosisFnIndexChanged(int index)
{
    kurtosis = ui->comboBoxKurtosis->currentText();
}

void RPSWLKurtosisDlg::OnBnClickedKurtosisInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLKurtosis* currentSelection = CrpsKurtosisFactory::BuildObject(kurtosis);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
