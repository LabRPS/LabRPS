#include "rpsslcoherencedlg.h"
#include "ui_rpsslcoherencedlg.h"

#include "rps/seismicLab/rpsSeismicLabSimulation.h"
#include "RPSSeismicLabAPI.h"

RPSSLCoherenceDlg::RPSSLCoherenceDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSLCoherenceDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

    coherenceFunction = rpsSeismicLabSimulator->GetSeismicLabData().coherenceFunction;

    ui->comboBoxCoherenceFunc->clear();
    ui->comboBoxCoherenceFunc->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsSLCoherence *(*CreateCoherenceCallback)();
	std::map<const QString, CreateCoherenceCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (cohIt = CrpsSLCoherenceFactory::GetCoherenceNamesMap().begin(); cohIt != CrpsSLCoherenceFactory::GetCoherenceNamesMap().end(); ++cohIt)
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
    
     connect( ui->pushButtonSoilTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedCoherenceFnInit( ) ) );


}

RPSSLCoherenceDlg::~RPSSLCoherenceDlg()
{
    delete ui;
}

void RPSSLCoherenceDlg::comboBoxCoherenceFnIndexChanged(int index)
{
    coherenceFunction = ui->comboBoxCoherenceFunc->currentText();
}

void RPSSLCoherenceDlg::OnBnClickedCoherenceFnInit()
{
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLCoherence* currentSelection = CrpsSLCoherenceFactory::BuildCoherence(coherenceFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
