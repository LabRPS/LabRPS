#include "rpswlpeakfactordlg.h"
#include "ui_rpswlpeakfactordlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLPeakFactorDlg::RPSWLPeakFactorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLPeakFactorDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    peakFactor = rpsWindLabSimulator->GetWindLabData().peakFactor;

    ui->comboBoxPeakFactor->clear();
    ui->comboBoxPeakFactor->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLPeakFactor *(*CreatePeakFactorCallback)();
	std::map<const QString, CreatePeakFactorCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsPeakFactorFactory::GetObjectNamesMap().begin(); cohIt != CrpsPeakFactorFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxPeakFactor->addItem(cohIt->first);
	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxPeakFactor->findText(peakFactor)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxPeakFactor->setCurrentText(peakFactor);
	}
	else if ((nDex == ui->comboBoxPeakFactor->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxPeakFactor->setCurrentText(noSelection);
	}

    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxPeakFactor, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxPeakFactorFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedPeakFactorInit( ) ) );
}

RPSWLPeakFactorDlg::~RPSWLPeakFactorDlg()
{
    delete ui;
}

void RPSWLPeakFactorDlg::comboBoxPeakFactorFnIndexChanged(int index)
{
    peakFactor = ui->comboBoxPeakFactor->currentText();
}

void RPSWLPeakFactorDlg::OnBnClickedPeakFactorInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLPeakFactor* currentSelection = CrpsPeakFactorFactory::BuildObject(peakFactor);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
