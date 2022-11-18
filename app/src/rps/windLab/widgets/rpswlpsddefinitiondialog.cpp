#include "rpswlpsddefinitiondialog.h"
#include "ui_rpswlpsddefinitiondialog.h"
#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

#include <QMessageBox>

RPSWLPSDDefinitionDialog::RPSWLPSDDefinitionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWLPSDDefinitionDialog)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

     numberOfFrequency = rpsWindLabSimulator->GetWindLabData().numberOfFrequency;
	 minFrequency = rpsWindLabSimulator->GetWindLabData().minFrequency;
	 maxFrequency = rpsWindLabSimulator->GetWindLabData().maxFrequency;
	 frequencyIncrement = rpsWindLabSimulator->GetWindLabData().frequencyIncrement;
	 windDirection = rpsWindLabSimulator->GetWindLabData().direction;

     spectrumModel = rpsWindLabSimulator->GetWindLabData().spectrumModel;
	 cpsdDecompositionMethod = rpsWindLabSimulator->GetWindLabData().cpsdDecompositionMethod;
	 freqencyDistribution = rpsWindLabSimulator->GetWindLabData().freqencyDistribution;

     int min = 1;
     int max = 10000000;

     ui->lineEditNberOfFreqIncr->setRange(min, max);

     ui->lineEditNberOfFreqIncr->setValue(numberOfFrequency);
     ui->lineEditMinFreq->setText(QString::number(minFrequency));
     ui->lineEditMaxFreq->setText(QString::number(maxFrequency));
     ui->lineEditFreqIncr->setText(QString::number(frequencyIncrement));
     
     if(1 == windDirection)
	{
		ui->radioButtonAlongWind->setChecked(Qt::Checked);
	}
	else if(2 == windDirection)
	{
		ui->radioButtonCrossWind->setChecked(Qt::Checked);
	}
    else if(3 == windDirection)
	{
		ui->radioButtonVerticalWind->setChecked(Qt::Checked);
	}

	 
    
    ui->comboBoxSpectrumModel->clear();
    ui->comboBoxCpsdDecomp->clear();
    ui->comboBoxFreqDistr->clear();

	ui->comboBoxSpectrumModel->addItem(noSelection);
    ui->comboBoxCpsdDecomp->addItem(noSelection);
	ui->comboBoxFreqDistr->addItem(noSelection);

    if(1 == windDirection)
    {
        /////******spectrum model start*******/////////
	typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();
	std::map<const QString, CreateXSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsXSpectrumFactory::GetXSpectrumNamesMap().begin(); psdIt != CrpsXSpectrumFactory::GetXSpectrumNamesMap().end(); ++psdIt)
	{
		// Add it to the combo box
		ui->comboBoxSpectrumModel->addItem(psdIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxSpectrumModel->findText(spectrumModel)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSpectrumModel->setCurrentText(spectrumModel);
	}
	else if ((nDex != ui->comboBoxSpectrumModel->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpectrumModel->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////

    }
    else if(2 == windDirection)
    {
        /////******spectrum model start*******/////////
	typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();
	std::map<const QString, CreateYSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsYSpectrumFactory::GetYSpectrumNamesMap().begin(); psdIt != CrpsYSpectrumFactory::GetYSpectrumNamesMap().end(); ++psdIt)
	{
		// Add it to the combo box
		ui->comboBoxSpectrumModel->addItem(psdIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxSpectrumModel->findText(spectrumModel)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSpectrumModel->setCurrentText(spectrumModel);
	}
	else if ((nDex != ui->comboBoxSpectrumModel->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpectrumModel->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////

    }
    else if(3 == windDirection)
    {
        /////******spectrum model start*******/////////
	typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();
	std::map<const QString, CreateZSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsZSpectrumFactory::GetZSpectrumNamesMap().begin(); psdIt != CrpsZSpectrumFactory::GetZSpectrumNamesMap().end(); ++psdIt)
	{
		// Add it to the combo box
		ui->comboBoxSpectrumModel->addItem(psdIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxSpectrumModel->findText(spectrumModel)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSpectrumModel->setCurrentText(spectrumModel);
	}
	else if ((nDex != ui->comboBoxSpectrumModel->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpectrumModel->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////

    }
    
      /////******PSD decomposition methods start*******/////////
	typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
	std::map<const QString, CreatePSDdecomMethodCallback> ::iterator psdDecIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (psdDecIt = CrpsPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().begin(); psdDecIt != CrpsPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().end(); ++psdDecIt)
	{
		// Add it to the combo box
		ui->comboBoxCpsdDecomp->addItem(psdDecIt->first);

	}

    	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxCpsdDecomp->findText(cpsdDecompositionMethod)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxCpsdDecomp->setCurrentText(cpsdDecompositionMethod);
	}
	else if ((nDex != ui->comboBoxCpsdDecomp->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxCpsdDecomp->setCurrentText(noSelection);
	}

    /////******PSD decomposition methods end*******/////////

    /////*************Frequency distribution start*******/////////
	typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
	std::map<const QString, CreateFrequencyDistributionCallback> ::iterator freqDistrIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (freqDistrIt = CrpsFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().begin(); freqDistrIt != CrpsFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().end(); ++freqDistrIt)
	{
		// Add it to the combo box
		ui->comboBoxFreqDistr->addItem(freqDistrIt->first);
	}

     nDex = -1;

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxFreqDistr->findText(freqencyDistribution)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxFreqDistr->setCurrentText(freqencyDistribution);
	}
	else if ((nDex != ui->comboBoxFreqDistr->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxFreqDistr->setCurrentText(noSelection);
	}

    /////*************Frequency distribution end*******/////////

    // connection
    connect( ui->comboBoxSpectrumModel, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxPSDModelIndexChanged( int ) ) );

    connect( ui->comboBoxCpsdDecomp, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxPSDdecompIndexChanged( int ) ) );
       
    connect( ui->comboBoxFreqDistr, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxFrequencyDistrIndexChanged( int ) ) );
    
    connect( ui->pushButtonSpectrumModelInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedPSDModelInit( ) ) );

    connect( ui->pushButtonCpsdDecompInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedPSDdecompInit( ) ) );
   
    connect( ui->pushButtonFreqDistrInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedFrequencyDistrInit( ) ) );

   connect( ui->radioButtonAlongWind, SIGNAL( toggled(bool) ),
             this, SLOT( radioButtonAlongWindToggled(bool ) ) );
   
   connect( ui->radioButtonCrossWind, SIGNAL( toggled(bool) ),
             this, SLOT( radioButtonCrossWindToggled(bool ) ) );
   
   connect( ui->radioButtonVerticalWind, SIGNAL( toggled(bool) ),
             this, SLOT( radioButtonVerticalWindToggled( bool) ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));


}

RPSWLPSDDefinitionDialog::~RPSWLPSDDefinitionDialog()
{
    delete ui;
}


void RPSWLPSDDefinitionDialog::comboBoxPSDModelIndexChanged(int index)
{
    spectrumModel = ui->comboBoxSpectrumModel->currentText();
}
void RPSWLPSDDefinitionDialog::comboBoxPSDdecompIndexChanged(int index)
{
    spectrumModel = ui->comboBoxSpectrumModel->currentText();
}

void RPSWLPSDDefinitionDialog::comboBoxFrequencyDistrIndexChanged(int index)
{
    spectrumModel = ui->comboBoxSpectrumModel->currentText();
}

void RPSWLPSDDefinitionDialog::OnBnClickedPSDModelInit()
{
    
    if(1 == windDirection)
    {
        
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLXSpectrum* currentSelection = CrpsXSpectrumFactory::BuildXSpectrum(spectrumModel);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
    }
    else if(2 == windDirection)
    {
       
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLYSpectrum* currentSelection = CrpsYSpectrumFactory::BuildYSpectrum(spectrumModel);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
    }
    else if(3 == windDirection)
    {
        
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLZSpectrum* currentSelection = CrpsZSpectrumFactory::BuildZSpectrum(spectrumModel);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
    }
 
}
void RPSWLPSDDefinitionDialog::OnBnClickedPSDdecompInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLPSDdecompositionMethod* currentSelection = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(cpsdDecompositionMethod);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}

void RPSWLPSDDefinitionDialog::OnBnClickedFrequencyDistrInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLFrequencyDistribution* currentSelection = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(freqencyDistribution);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

	// Delete the object
	delete currentSelection;
}

void RPSWLPSDDefinitionDialog::acceptInput()
 {
    numberOfFrequency = ui->lineEditNberOfFreqIncr->text().toDouble();
    minFrequency = ui->lineEditMinFreq->text().toDouble();
    maxFrequency = ui->lineEditMaxFreq->text().toDouble();
    frequencyIncrement = ui->lineEditFreqIncr->text().toDouble();
	spectrumModel = ui->comboBoxSpectrumModel->currentText();
	cpsdDecompositionMethod = ui->comboBoxCpsdDecomp->currentText();
    freqencyDistribution = ui->comboBoxFreqDistr->currentText();

 }

void RPSWLPSDDefinitionDialog::radioButtonAlongWindToggled(bool)
{
    windDirection = 1;
    
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    spectrumModel = rpsWindLabSimulator->GetWindLabData().spectrumModel;

    QString noSelection = "<None>";
    ui->comboBoxSpectrumModel->clear();
	ui->comboBoxSpectrumModel->addItem(noSelection);
  
    /////******spectrum model start*******/////////
	typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();
	std::map<const QString, CreateXSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsXSpectrumFactory::GetXSpectrumNamesMap().begin(); psdIt != CrpsXSpectrumFactory::GetXSpectrumNamesMap().end(); ++psdIt)
	{
		// Add it to the combo box
		ui->comboBoxSpectrumModel->addItem(psdIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxSpectrumModel->findText(spectrumModel)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSpectrumModel->setCurrentText(spectrumModel);
	}
	else if ((nDex != ui->comboBoxSpectrumModel->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpectrumModel->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////

}
void RPSWLPSDDefinitionDialog::radioButtonCrossWindToggled(bool)
{
    windDirection = 2;

    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    spectrumModel = rpsWindLabSimulator->GetWindLabData().spectrumModel;

    QString noSelection = "<None>";
    ui->comboBoxSpectrumModel->clear();
	ui->comboBoxSpectrumModel->addItem(noSelection);

    /////******spectrum model start*******/////////
	typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();
	std::map<const QString, CreateYSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsYSpectrumFactory::GetYSpectrumNamesMap().begin(); psdIt != CrpsYSpectrumFactory::GetYSpectrumNamesMap().end(); ++psdIt)
	{
		// Add it to the combo box
		ui->comboBoxSpectrumModel->addItem(psdIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxSpectrumModel->findText(spectrumModel)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSpectrumModel->setCurrentText(spectrumModel);
	}
	else if ((nDex != ui->comboBoxSpectrumModel->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpectrumModel->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////
}
void RPSWLPSDDefinitionDialog::radioButtonVerticalWindToggled(bool)
{
    windDirection = 3;

    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    spectrumModel = rpsWindLabSimulator->GetWindLabData().spectrumModel;

    QString noSelection = "<None>";
    ui->comboBoxSpectrumModel->clear();
	ui->comboBoxSpectrumModel->addItem(noSelection);
   
      /////******spectrum model start*******/////////
	typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();
	std::map<const QString, CreateZSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsZSpectrumFactory::GetZSpectrumNamesMap().begin(); psdIt != CrpsZSpectrumFactory::GetZSpectrumNamesMap().end(); ++psdIt)
	{
		// Add it to the combo box
		ui->comboBoxSpectrumModel->addItem(psdIt->first);

	}

	// return value
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected is found
	if ((nDex != ui->comboBoxSpectrumModel->findText(spectrumModel)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSpectrumModel->setCurrentText(spectrumModel);
	}
	else if ((nDex != ui->comboBoxSpectrumModel->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpectrumModel->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////

}




