#include "rpsslpsddefinitiondialog.h"
#include "ui_rpsslpsddefinitiondialog.h"
#include "rps/seismicLab/rpsSeismicLabSimulation.h"
#include "RPSSeismicLabAPI.h"

#include <QMessageBox>

RPSSLPSDDefinitionDialog::RPSSLPSDDefinitionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSLPSDDefinitionDialog)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

     numberOfFrequency = rpsSeismicLabSimulator->GetSeismicLabData().numberOfFrequency;
	 minFrequency = rpsSeismicLabSimulator->GetSeismicLabData().minFrequency;
	 maxFrequency = rpsSeismicLabSimulator->GetSeismicLabData().maxFrequency;
	 frequencyIncrement = rpsSeismicLabSimulator->GetSeismicLabData().frequencyIncrement;
	 windDirection = rpsSeismicLabSimulator->GetSeismicLabData().direction;

     spectrumModel = rpsSeismicLabSimulator->GetSeismicLabData().spectrumModel;
	 cpsdDecompositionMethod = rpsSeismicLabSimulator->GetSeismicLabData().cpsdDecompositionMethod;
	 freqencyDistribution = rpsSeismicLabSimulator->GetSeismicLabData().freqencyDistribution;

     ui->lineEditNberOfFreqIncr->setText(QString::number(numberOfFrequency));
     ui->lineEditMinFreq->setText(QString::number(minFrequency));
     ui->lineEditMaxFreq->setText(QString::number(maxFrequency));
     ui->lineEditFreqIncr->setText(QString::number(frequencyIncrement));
     
     if(1 == windDirection)
	{
		ui->radioButtonXDirection->setChecked(Qt::Checked);
	}
	else if(2 == windDirection)
	{
		ui->radioButtonYDirection->setChecked(Qt::Checked);
	}
    else if(3 == windDirection)
	{
		ui->radioButtonZDirection->setChecked(Qt::Checked);
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
	typedef IrpsSLXSpectrum *(*CreateXSpectrumCallback)();
	std::map<const QString, CreateXSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsSLXSpectrumFactory::GetXSpectrumNamesMap().begin(); psdIt != CrpsSLXSpectrumFactory::GetXSpectrumNamesMap().end(); ++psdIt)
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
	typedef IrpsSLYSpectrum *(*CreateYSpectrumCallback)();
	std::map<const QString, CreateYSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsSLYSpectrumFactory::GetYSpectrumNamesMap().begin(); psdIt != CrpsSLYSpectrumFactory::GetYSpectrumNamesMap().end(); ++psdIt)
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
	typedef IrpsSLZSpectrum *(*CreateZSpectrumCallback)();
	std::map<const QString, CreateZSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsSLZSpectrumFactory::GetZSpectrumNamesMap().begin(); psdIt != CrpsSLZSpectrumFactory::GetZSpectrumNamesMap().end(); ++psdIt)
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
	typedef IrpsSLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
	std::map<const QString, CreatePSDdecomMethodCallback> ::iterator psdDecIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (psdDecIt = CrpsSLPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().begin(); psdDecIt != CrpsSLPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().end(); ++psdDecIt)
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
	typedef IrpsSLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
	std::map<const QString, CreateFrequencyDistributionCallback> ::iterator freqDistrIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (freqDistrIt = CrpsSLFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().begin(); freqDistrIt != CrpsSLFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().end(); ++freqDistrIt)
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

   connect( ui->radioButtonXDirection, SIGNAL( toggled(bool) ),
             this, SLOT( radioButtonXDirectionToggled(bool ) ) );
   
   connect( ui->radioButtonYDirection, SIGNAL( toggled(bool) ),
             this, SLOT( radioButtonYDirectionToggled(bool ) ) );
   
   connect( ui->radioButtonZDirection, SIGNAL( toggled(bool) ),
             this, SLOT( radioButtonZDirectionToggled( bool) ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));


}

RPSSLPSDDefinitionDialog::~RPSSLPSDDefinitionDialog()
{
    delete ui;
}


void RPSSLPSDDefinitionDialog::comboBoxPSDModelIndexChanged(int index)
{
    // spectrumModel = ui->comboBoxSpectrumModel->currentText();
}
void RPSSLPSDDefinitionDialog::comboBoxPSDdecompIndexChanged(int index)
{

}

void RPSSLPSDDefinitionDialog::comboBoxFrequencyDistrIndexChanged(int index)
{

}

void RPSSLPSDDefinitionDialog::OnBnClickedPSDModelInit()
{
    
    if(1 == windDirection)
    {
        
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLXSpectrum* currentSelection = CrpsSLXSpectrumFactory::BuildXSpectrum(spectrumModel);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
    }
    else if(2 == windDirection)
    {
       
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLYSpectrum* currentSelection = CrpsSLYSpectrumFactory::BuildYSpectrum(spectrumModel);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
    }
    else if(3 == windDirection)
    {
        
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLZSpectrum* currentSelection = CrpsSLZSpectrumFactory::BuildZSpectrum(spectrumModel);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
    }
 
}
void RPSSLPSDDefinitionDialog::OnBnClickedPSDdecompInit()
{
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLPSDdecompositionMethod* currentSelection = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(cpsdDecompositionMethod);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
}

void RPSSLPSDDefinitionDialog::OnBnClickedFrequencyDistrInit()
{
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLFrequencyDistribution* currentSelection = CrpsSLFrequencyDistributionFactory::BuildFrequencyDistribution(freqencyDistribution);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSelection;
}

void RPSSLPSDDefinitionDialog::acceptInput()
 {
    numberOfFrequency = ui->lineEditNberOfFreqIncr->text().toDouble();
    minFrequency = ui->lineEditMinFreq->text().toDouble();
    maxFrequency = ui->lineEditMaxFreq->text().toDouble();
    frequencyIncrement = ui->lineEditFreqIncr->text().toDouble();
	spectrumModel = ui->comboBoxSpectrumModel->currentText();
	cpsdDecompositionMethod = ui->comboBoxCpsdDecomp->currentText();
    freqencyDistribution = ui->comboBoxFreqDistr->currentText();

 }

void RPSSLPSDDefinitionDialog::radioButtonXDirectionToggled(bool)
{
    windDirection = 1;
    
    RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();
    spectrumModel = rpsSeismicLabSimulator->GetSeismicLabData().spectrumModel;

    QString noSelection = "<None>";
    ui->comboBoxSpectrumModel->clear();
	ui->comboBoxSpectrumModel->addItem(noSelection);
  
    /////******spectrum model start*******/////////
	typedef IrpsSLXSpectrum *(*CreateXSpectrumCallback)();
	std::map<const QString, CreateXSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsSLXSpectrumFactory::GetXSpectrumNamesMap().begin(); psdIt != CrpsSLXSpectrumFactory::GetXSpectrumNamesMap().end(); ++psdIt)
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
void RPSSLPSDDefinitionDialog::radioButtonYDirectionToggled(bool)
{
    windDirection = 2;

    RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();
    spectrumModel = rpsSeismicLabSimulator->GetSeismicLabData().spectrumModel;

    QString noSelection = "<None>";
    ui->comboBoxSpectrumModel->clear();
	ui->comboBoxSpectrumModel->addItem(noSelection);

    /////******spectrum model start*******/////////
	typedef IrpsSLYSpectrum *(*CreateYSpectrumCallback)();
	std::map<const QString, CreateYSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsSLYSpectrumFactory::GetYSpectrumNamesMap().begin(); psdIt != CrpsSLYSpectrumFactory::GetYSpectrumNamesMap().end(); ++psdIt)
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
void RPSSLPSDDefinitionDialog::radioButtonZDirectionToggled(bool)
{
    windDirection = 3;

    RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();
    spectrumModel = rpsSeismicLabSimulator->GetSeismicLabData().spectrumModel;

    QString noSelection = "<None>";
    ui->comboBoxSpectrumModel->clear();
	ui->comboBoxSpectrumModel->addItem(noSelection);
   
      /////******spectrum model start*******/////////
	typedef IrpsSLZSpectrum *(*CreateZSpectrumCallback)();
	std::map<const QString, CreateZSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsSLZSpectrumFactory::GetZSpectrumNamesMap().begin(); psdIt != CrpsSLZSpectrumFactory::GetZSpectrumNamesMap().end(); ++psdIt)
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




