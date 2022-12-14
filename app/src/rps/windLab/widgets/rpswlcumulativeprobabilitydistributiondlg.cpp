#include "rpswlcumulativeprobabilitydistributiondlg.h"
#include "ui_rpswlcumulativeprobabilitydistributiondlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLCumulativeProbabilityDistributionDlg::RPSWLCumulativeProbabilityDistributionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLCumulativeProbabilityDistributionDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    cumulativeProbabilityDistribution = rpsWindLabSimulator->GetWindLabData().cumulativeProbabilityDistribution;

    ui->comboBoxCumulativeProbabilityDistribution->clear();
    ui->comboBoxCumulativeProbabilityDistribution->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();
	std::map<const QString, CreateCumulativeProbabilityDistributionCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().begin(); cohIt != CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxCumulativeProbabilityDistribution->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxCumulativeProbabilityDistribution->findText(cumulativeProbabilityDistribution)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxCumulativeProbabilityDistribution->setCurrentText(cumulativeProbabilityDistribution);
	}
	else if ((nDex == ui->comboBoxCumulativeProbabilityDistribution->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxCumulativeProbabilityDistribution->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxCumulativeProbabilityDistribution, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxCumulativeProbabilityDistributionFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedCumulativeProbabilityDistributionInit( ) ) );


}

RPSWLCumulativeProbabilityDistributionDlg::~RPSWLCumulativeProbabilityDistributionDlg()
{
    delete ui;
}

void RPSWLCumulativeProbabilityDistributionDlg::comboBoxCumulativeProbabilityDistributionFnIndexChanged(int index)
{
    cumulativeProbabilityDistribution = ui->comboBoxCumulativeProbabilityDistribution->currentText();
}

void RPSWLCumulativeProbabilityDistributionDlg::OnBnClickedCumulativeProbabilityDistributionInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLCumulativeProbabilityDistribution* currentSelection = CrpsCumulativeProbabilityDistributionFactory::BuildObject(cumulativeProbabilityDistribution);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
