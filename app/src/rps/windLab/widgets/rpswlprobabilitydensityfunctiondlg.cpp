#include "rpswlprobabilitydensityfunctiondlg.h"
#include "ui_rpswlprobabilitydensityfunctiondlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLProbabilityDensityFunctionDlg::RPSWLProbabilityDensityFunctionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLProbabilityDensityFunctionDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    probabilityDensityFunction = rpsWindLabSimulator->GetWindLabData().probabilityDensityFunction;

    ui->comboBoxProbabilityDensityFunction->clear();
    ui->comboBoxProbabilityDensityFunction->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();
	std::map<const QString, CreateProbabilityDensityFunctionCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().begin(); cohIt != CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxProbabilityDensityFunction->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxProbabilityDensityFunction->findText(probabilityDensityFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxProbabilityDensityFunction->setCurrentText(probabilityDensityFunction);
	}
	else if ((nDex == ui->comboBoxProbabilityDensityFunction->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxProbabilityDensityFunction->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxProbabilityDensityFunction, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxProbabilityDensityFunctionFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedProbabilityDensityFunctionInit( ) ) );


}

RPSWLProbabilityDensityFunctionDlg::~RPSWLProbabilityDensityFunctionDlg()
{
    delete ui;
}

void RPSWLProbabilityDensityFunctionDlg::comboBoxProbabilityDensityFunctionFnIndexChanged(int index)
{
    probabilityDensityFunction = ui->comboBoxProbabilityDensityFunction->currentText();
}

void RPSWLProbabilityDensityFunctionDlg::OnBnClickedProbabilityDensityFunctionInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLProbabilityDensityFunction* currentSelection = CrpsProbabilityDensityFunctionFactory::BuildObject(probabilityDensityFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
