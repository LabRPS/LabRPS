#include "rpsselcoherencedlg.h"
#include "ui_rpsselcoherencedlg.h"

#include "ApplicationWindow.h"
#include "RPSSeaLabAPI.h"

RPSSeLCoherenceDlg::RPSSeLCoherenceDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSeLCoherenceDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	ApplicationWindow *app = (ApplicationWindow *)this->parent();

    coherenceFunction = app->rpsSeaLabSimulator->GetSeaLabData().coherenceFunction;

    ui->comboBoxCoherenceFunc->clear();
    ui->comboBoxCoherenceFunc->addItem(noSelection);

    /////******coherence model start*******/////////
	typedef IrpsSeLCoherence *(*CreateCoherenceCallback)();
	std::map<const QString, CreateCoherenceCallback> ::iterator cohIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (cohIt = CrpsSeLCoherenceFactory::GetCoherenceNamesMap().begin(); cohIt != CrpsSeLCoherenceFactory::GetCoherenceNamesMap().end(); ++cohIt)
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
    
     connect( ui->pushButtonWaveTypeInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedCoherenceFnInit( ) ) );


}

RPSSeLCoherenceDlg::~RPSSeLCoherenceDlg()
{
    delete ui;
}

void RPSSeLCoherenceDlg::comboBoxCoherenceFnIndexChanged(int index)
{
    coherenceFunction = ui->comboBoxCoherenceFunc->currentText();
}

void RPSSeLCoherenceDlg::OnBnClickedCoherenceFnInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLCoherence* currentSelection = CrpsSeLCoherenceFactory::BuildCoherence(coherenceFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(app->rpsSeaLabSimulator->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSelection;
}
