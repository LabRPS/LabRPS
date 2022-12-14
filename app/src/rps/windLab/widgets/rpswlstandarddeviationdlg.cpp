#include "rpswlstandarddeviationdlg.h"
#include "ui_rpswlstandarddeviationdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLStandardDeviationDlg::RPSWLStandardDeviationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLStandardDeviationDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    standardDeviation = rpsWindLabSimulator->GetWindLabData().standardDeviation;

    ui->comboBoxStandardDeviation->clear();
    ui->comboBoxStandardDeviation->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLStandardDeviation *(*CreateStandardDeviationCallback)();
	std::map<const QString, CreateStandardDeviationCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsStandardDeviationFactory::GetObjectNamesMap().begin(); cohIt != CrpsStandardDeviationFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxStandardDeviation->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxStandardDeviation->findText(standardDeviation)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxStandardDeviation->setCurrentText(standardDeviation);
	}
	else if ((nDex == ui->comboBoxStandardDeviation->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxStandardDeviation->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxStandardDeviation, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxStandardDeviationFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedStandardDeviationInit( ) ) );


}

RPSWLStandardDeviationDlg::~RPSWLStandardDeviationDlg()
{
    delete ui;
}

void RPSWLStandardDeviationDlg::comboBoxStandardDeviationFnIndexChanged(int index)
{
    standardDeviation = ui->comboBoxStandardDeviation->currentText();
}

void RPSWLStandardDeviationDlg::OnBnClickedStandardDeviationInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLStandardDeviation* currentSelection = CrpsStandardDeviationFactory::BuildObject(standardDeviation);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
