#include "rpswlshearvelocityofflowdlg.h"
#include "ui_rpswlshearvelocityofflowdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLShearVelocityOfFlowDlg::RPSWLShearVelocityOfFlowDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLShearVelocityOfFlowDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    shearVelocityOfFlow = rpsWindLabSimulator->GetWindLabData().shearVelocityOfFlow;

    ui->comboBoxShearVelocityOfFlow->clear();
    ui->comboBoxShearVelocityOfFlow->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();
	std::map<const QString, CreateShearVelocityOfFlowCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().begin(); cohIt != CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxShearVelocityOfFlow->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxShearVelocityOfFlow->findText(shearVelocityOfFlow)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxShearVelocityOfFlow->setCurrentText(shearVelocityOfFlow);
	}
	else if ((nDex == ui->comboBoxShearVelocityOfFlow->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxShearVelocityOfFlow->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxShearVelocityOfFlow, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxShearVelocityOfFlowFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedShearVelocityOfFlowInit( ) ) );


}

RPSWLShearVelocityOfFlowDlg::~RPSWLShearVelocityOfFlowDlg()
{
    delete ui;
}

void RPSWLShearVelocityOfFlowDlg::comboBoxShearVelocityOfFlowFnIndexChanged(int index)
{
    shearVelocityOfFlow = ui->comboBoxShearVelocityOfFlow->currentText();
}

void RPSWLShearVelocityOfFlowDlg::OnBnClickedShearVelocityOfFlowInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLShearVelocityOfFlow* currentSelection = CrpsShearVelocityOfFlowFactory::BuildObject(shearVelocityOfFlow);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
