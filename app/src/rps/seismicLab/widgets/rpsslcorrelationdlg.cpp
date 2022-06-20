#include "rpsslcorrelationdlg.h"
#include "ui_rpsslcorrelationdlg.h"

#include "rps/seismicLab/rpsSeismicLabSimulation.h"
#include "RPSSeismicLabAPI.h"

RPSSLCorrelationDlg::RPSSLCorrelationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSLCorrelationDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

    correlationFunction = rpsSeismicLabSimulator->GetSeismicLabData().correlationFunction;
 
    ui->comboBoxCorrelationFunc->clear();
    ui->comboBoxCorrelationFunc->addItem(noSelection);

    /////******correlation model start*******/////////
	typedef IrpsSLCorrelation *(*CreateCorrelationCallback)();
	std::map<const QString, CreateCorrelationCallback> ::iterator corrIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (corrIt = CrpsSLCorrelationFactory::GetCorrelationNamesMap().begin(); corrIt != CrpsSLCorrelationFactory::GetCorrelationNamesMap().end(); ++corrIt)
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

RPSSLCorrelationDlg::~RPSSLCorrelationDlg()
{
    delete ui;
}


void RPSSLCorrelationDlg::comboBoxCorrelationFnIndexChanged(int index)
{
    correlationFunction = ui->comboBoxCorrelationFunc->currentText();
}

void RPSSLCorrelationDlg::OnBnClickedCorrelationFnInit()
{
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLCorrelation* currentSelection = CrpsSLCorrelationFactory::BuildCorrelation(correlationFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
}

