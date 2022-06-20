#include "rpswlmeanwinddlg.h"
#include "ui_rpswlmeanwinddlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLMeanDlg::RPSWLMeanDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLMeanDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    meanFunction = rpsWindLabSimulator->GetWindLabData().meanFunction;

    ui->comboBoxMeanFunc->clear();
    ui->comboBoxMeanFunc->addItem(noSelection);

    /////******mean model start*******/////////
	typedef IrpsWLMean *(*CreateMeanCallback)();
	std::map<const QString, CreateMeanCallback> ::iterator meanIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (meanIt = CrpsMeanFactory::GetMeanNamesMap().begin(); meanIt != CrpsMeanFactory::GetMeanNamesMap().end(); ++meanIt)
	{
		// Add it to the combo box
		ui->comboBoxMeanFunc->addItem(meanIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxMeanFunc->findText(meanFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxMeanFunc->setCurrentText(meanFunction);
	}
	else if ((nDex == ui->comboBoxMeanFunc->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxMeanFunc->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxMeanFunc, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxMeanFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedMeanFnInit( ) ) );


}

RPSWLMeanDlg::~RPSWLMeanDlg()
{
    delete ui;
}

void RPSWLMeanDlg::comboBoxMeanFnIndexChanged(int index)
{
    meanFunction = ui->comboBoxMeanFunc->currentText();
}

void RPSWLMeanDlg::OnBnClickedMeanFnInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLMean* currentSelection = CrpsMeanFactory::BuildMean(meanFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
