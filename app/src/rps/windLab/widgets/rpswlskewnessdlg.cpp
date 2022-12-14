#include "rpswlskewnessdlg.h"
#include "ui_rpswlskewnessdlg.h"

#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWLSkewnessDlg::RPSWLSkewnessDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLSkewnessDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    skewness = rpsWindLabSimulator->GetWindLabData().skewness;

    ui->comboBoxSkewness->clear();
    ui->comboBoxSkewness->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsWLSkewness *(*CreateSkewnessCallback)();
	std::map<const QString, CreateSkewnessCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsSkewnessFactory::GetObjectNamesMap().begin(); cohIt != CrpsSkewnessFactory::GetObjectNamesMap().end(); ++cohIt)
	{
		// Add it to the combo box
		ui->comboBoxSkewness->addItem(cohIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxSkewness->findText(skewness)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSkewness->setCurrentText(skewness);
	}
	else if ((nDex == ui->comboBoxSkewness->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSkewness->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////


      // connection
    connect( ui->comboBoxSkewness, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxSkewnessFnIndexChanged( int ) ) );
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedSkewnessInit( ) ) );


}

RPSWLSkewnessDlg::~RPSWLSkewnessDlg()
{
    delete ui;
}

void RPSWLSkewnessDlg::comboBoxSkewnessFnIndexChanged(int index)
{
    skewness = ui->comboBoxSkewness->currentText();
}

void RPSWLSkewnessDlg::OnBnClickedSkewnessInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
    IrpsWLSkewness* currentSelection = CrpsSkewnessFactory::BuildObject(skewness);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}
