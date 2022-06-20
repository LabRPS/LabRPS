#include "rpswlcorrelationdlg.h"
#include "ui_rpswlcorrelationdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLCorrelationDlg::RPSWLCorrelationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLCorrelationDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    correlationFunction = rpsWindLabSimulator->GetWindLabData().correlationFunction;
 
    ui->comboBoxCorrelationFunc->clear();
    ui->comboBoxCorrelationFunc->addItem(noSelection);

    /////******correlation model start*******/////////
	typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();
	std::map<const QString, CreateCorrelationCallback> ::iterator corrIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (corrIt = CrpsCorrelationFactory::GetCorrelationNamesMap().begin(); corrIt != CrpsCorrelationFactory::GetCorrelationNamesMap().end(); ++corrIt)
	{
		// Add it to the combo box
		ui->comboBoxCorrelationFunc->addItem(corrIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxCorrelationFunc->findText(correlationFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxCorrelationFunc->setCurrentText(correlationFunction);
	}
	else if ((nDex == ui->comboBoxCorrelationFunc->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxCorrelationFunc->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxCorrelationFunc, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxCorrelationFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonCorrelationInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedCorrelationFnInit( ) ) );


}

RPSWLCorrelationDlg::~RPSWLCorrelationDlg()
{
    delete ui;
}


void RPSWLCorrelationDlg::comboBoxCorrelationFnIndexChanged(int index)
{
    correlationFunction = ui->comboBoxCorrelationFunc->currentText();
}

void RPSWLCorrelationDlg::OnBnClickedCorrelationFnInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLCorrelation* currentSelection = CrpsCorrelationFactory::BuildCorrelation(correlationFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}

