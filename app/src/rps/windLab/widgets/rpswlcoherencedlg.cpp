#include "rpswlcoherencedlg.h"
#include "ui_rpswlcoherencedlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLCoherenceDlg::RPSWLCoherenceDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLCoherenceDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    coherenceFunction = rpsWindLabSimulator->GetWindLabData().coherenceFunction;

    ui->comboBoxCoherenceFunc->clear();
    ui->comboBoxCoherenceFunc->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLCoherence *(*CreateCoherenceCallback)();
	std::map<const QString, CreateCoherenceCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (cohIt = CrpsCoherenceFactory::GetCoherenceNamesMap().begin(); cohIt != CrpsCoherenceFactory::GetCoherenceNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxCoherenceFunc->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxCoherenceFunc->findText(coherenceFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxCoherenceFunc->setCurrentText(coherenceFunction);
	}
	else if ((nDex == ui->comboBoxCoherenceFunc->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxCoherenceFunc->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxCoherenceFunc, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxCoherenceFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedCoherenceFnInit( ) ) );


}

RPSWLCoherenceDlg::~RPSWLCoherenceDlg()
{
    delete ui;
}

void RPSWLCoherenceDlg::comboBoxCoherenceFnIndexChanged(int index)
{
    coherenceFunction = ui->comboBoxCoherenceFunc->currentText();
}

void RPSWLCoherenceDlg::OnBnClickedCoherenceFnInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLCoherence* currentSelection = CrpsCoherenceFactory::BuildCoherence(coherenceFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
