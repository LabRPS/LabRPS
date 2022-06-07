#include "rpsselcorrelationdlg.h"
#include "ui_rpsselcorrelationdlg.h"

#include "ApplicationWindow.h"
#include "RPSSeaLabAPI.h"

RPSSeLCorrelationDlg::RPSSeLCorrelationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSeLCorrelationDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSSeaLabSimulation *rpsSeaLabSimulator = (RPSSeaLabSimulation *)this->parent();

    correlationFunction = rpsSeaLabSimulator->GetSeaLabData().correlationFunction;
 
    ui->comboBoxCorrelationFunc->clear();
    ui->comboBoxCorrelationFunc->addItem(noSelection);

    /////******correlation model start*******/////////
	typedef IrpsSeLCorrelation *(*CreateCorrelationCallback)();
	std::map<const QString, CreateCorrelationCallback> ::iterator corrIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (corrIt = CrpsSeLCorrelationFactory::GetCorrelationNamesMap().begin(); corrIt != CrpsSeLCorrelationFactory::GetCorrelationNamesMap().end(); ++corrIt)
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

RPSSeLCorrelationDlg::~RPSSeLCorrelationDlg()
{
    delete ui;
}


void RPSSeLCorrelationDlg::comboBoxCorrelationFnIndexChanged(int index)
{
    correlationFunction = ui->comboBoxCorrelationFunc->currentText();
}

void RPSSeLCorrelationDlg::OnBnClickedCorrelationFnInit()
{
	RPSSeaLabSimulation *rpsSeaLabSimulator = (RPSSeaLabSimulation *)this->parent();

	// Build an object
	IrpsSeLCorrelation* currentSelection = CrpsSeLCorrelationFactory::BuildCorrelation(correlationFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeaLabSimulator->GetSeaLabData(), rpsSeaLabSimulator->information);

	// Delete the object
	delete currentSelection;
}

