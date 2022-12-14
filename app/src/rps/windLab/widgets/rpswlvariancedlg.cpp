#include "rpswlvariancedlg.h"
#include "ui_rpswlvariancedlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLVarianceDlg::RPSWLVarianceDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLVarianceDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    variance = rpsWindLabSimulator->GetWindLabData().variance;

    ui->comboBoxVariance->clear();
    ui->comboBoxVariance->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLVariance *(*CreateVarianceCallback)();
	std::map<const QString, CreateVarianceCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsVarianceFactory::GetObjectNamesMap().begin(); cohIt != CrpsVarianceFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxVariance->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxVariance->findText(variance)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxVariance->setCurrentText(variance);
	}
	else if ((nDex == ui->comboBoxVariance->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxVariance->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxVariance, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxVarianceFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedVarianceInit( ) ) );


}

RPSWLVarianceDlg::~RPSWLVarianceDlg()
{
    delete ui;
}

void RPSWLVarianceDlg::comboBoxVarianceFnIndexChanged(int index)
{
    variance = ui->comboBoxVariance->currentText();
}

void RPSWLVarianceDlg::OnBnClickedVarianceInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLVariance* currentSelection = CrpsVarianceFactory::BuildObject(variance);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
