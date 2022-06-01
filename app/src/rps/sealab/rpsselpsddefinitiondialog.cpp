#include "rpsselpsddefinitiondialog.h"
#include "ui_rpsselpsddefinitiondialog.h"

#include "ApplicationWindow.h"
#include "RPSSeaLabAPI.h"


RPSSeLPSDDefinitionDialog::RPSSeLPSDDefinitionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSeLPSDDefinitionDialog)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	ApplicationWindow *app = (ApplicationWindow *)this->parent();

     numberOfFrequency = app->GetSeaLabData().numberOfFrequency;
	 minFrequency = app->GetSeaLabData().minFrequency;
	 maxFrequency = app->GetSeaLabData().maxFrequency;
	 frequencyIncrement = app->GetSeaLabData().frequencyIncrement;
	 numberOfDirection = app->GetSeaLabData().numberOfDirection;
	 minDirection = app->GetSeaLabData().minDirection;
	 maxDirection = app->GetSeaLabData().maxDirection;
	 directionIncrement = app->GetSeaLabData().directionIncrement;
	 
     spectrumModel = app->GetSeaLabData().spectrumModel;
	 cpsdDecompositionMethod = app->GetSeaLabData().cpsdDecompositionMethod;
	 freqencyDistribution = app->GetSeaLabData().freqencyDistribution;
	 directionDistributionFunction = app->GetSeaLabData().directionDistributionFunction;
	 directionSpreadingFunction = app->GetSeaLabData().directionSpreadingFunction;
	 directionalSpectrumFunction = app->GetSeaLabData().directionalSpectrumFunction;

     ui->lineEditNberOfFreqIncr->setText(QString::number(numberOfFrequency));
     ui->lineEditMinFreq->setText(QString::number(minFrequency));
     ui->lineEditMaxFreq->setText(QString::number(maxFrequency));
     ui->lineEditFreqIncr->setText(QString::number(frequencyIncrement));
     ui->lineEditDirecNberOfIncr->setText(QString::number(numberOfDirection));
     ui->lineEditMinDirec->setText(QString::number(minDirection));
     ui->lineEditMaxDirec->setText(QString::number(maxDirection));
     ui->lineEditDirecIncr->setText(QString::number(directionIncrement));

    ui->comboBoxSpectrumModel->clear();
    ui->comboBoxCpsdDecomp->clear();
    ui->comboBoxDirSpread->clear();
    ui->comboBoxDirecSpectr->clear();
    ui->comboBoxFreqDistr->clear();
    ui->comboBoxDirDirec->clear();

	ui->comboBoxSpectrumModel->addItem(noSelection);
    ui->comboBoxCpsdDecomp->addItem(noSelection);
	ui->comboBoxDirSpread->addItem(noSelection);
	ui->comboBoxDirecSpectr->addItem(noSelection);
	ui->comboBoxFreqDistr->addItem(noSelection);
	ui->comboBoxDirDirec->addItem(noSelection);


    /////******spectrum model start*******/////////
	typedef IrpsSeLSpectrum *(*CreateXSpectrumCallback)();
	std::map<const QString, CreateXSpectrumCallback> ::iterator psdIt;
		
    // Iterate though the map and show all the registed spectrum models in the combo box
	for (psdIt = CrpsSeLXSpectrumFactory::GetXSpectrumNamesMap().begin(); psdIt != CrpsSeLXSpectrumFactory::GetXSpectrumNamesMap().end(); ++psdIt)
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
	else if ((nDex == ui->comboBoxSpectrumModel->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpectrumModel->setCurrentText(noSelection);
	}
    /////******spectrum model end*******//////////////////////

      /////******PSD decomposition methods start*******/////////
	typedef IrpsSeLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
	std::map<const QString, CreatePSDdecomMethodCallback> ::iterator psdDecIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (psdDecIt = CrpsSeLPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().begin(); psdDecIt != CrpsSeLPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().end(); ++psdDecIt)
	{
		// Add it to the combo box
		ui->comboBoxCpsdDecomp->addItem(psdDecIt->first);

	}

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxCpsdDecomp->findText(cpsdDecompositionMethod)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxCpsdDecomp->setCurrentText(cpsdDecompositionMethod);
	}
	else if ((nDex == ui->comboBoxCpsdDecomp->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxCpsdDecomp->setCurrentText(noSelection);
	}

    /////******PSD decomposition methods end*******/////////

    /////******Direction spreading function start*******/////////
	typedef IrpsSeLDirectionSpreadingFunction *(*CreateSLDirectionSpreadingFunctionCallback)();
	std::map<const QString, CreateSLDirectionSpreadingFunctionCallback> ::iterator sprIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (sprIt = CrpsSeLDirectionSpreadingFunctionFactory::GetDirectionSpreadingFunctionNamesMap().begin(); sprIt != CrpsSeLDirectionSpreadingFunctionFactory::GetDirectionSpreadingFunctionNamesMap().end(); ++sprIt)
	{
		// Add it to the combo box
		ui->comboBoxDirSpread->addItem(sprIt->first);

	}

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxDirSpread->findText(directionSpreadingFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxDirSpread->setCurrentText(directionSpreadingFunction);
	}
	else if ((nDex == ui->comboBoxDirSpread->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxDirSpread->setCurrentText(noSelection);
	}

    /////******Direction spreading function end*******///////////////

    /////**************Directional spectrum start*******//////////////
	typedef IrpsSeLDirectionalSpectrum *(*CreateSLDirectionalSpectrumCallback)();
	std::map<const QString, CreateSLDirectionalSpectrumCallback> ::iterator dirPSDIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (dirPSDIt = CrpsSeLDirectionalSpectrumFactory::GetDirectionalSpectrumNamesMap().begin(); dirPSDIt != CrpsSeLDirectionalSpectrumFactory::GetDirectionalSpectrumNamesMap().end(); ++dirPSDIt)
	{
		// Add it to the combo box
		ui->comboBoxDirecSpectr->addItem(dirPSDIt->first);

	}

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxDirecSpectr->findText(directionalSpectrumFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxDirecSpectr->setCurrentText(directionalSpectrumFunction);
	}
	else if ((nDex == ui->comboBoxDirecSpectr->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxDirecSpectr->setCurrentText(noSelection);
	}

    /////**************Directional spectrum end*******//////////////

    /////*************Frequency distribution start*******/////////
	typedef IrpsSeLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
	std::map<const QString, CreateFrequencyDistributionCallback> ::iterator freqDistrIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (freqDistrIt = CrpsSeLFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().begin(); freqDistrIt != CrpsSeLFrequencyDistributionFactory::GetFrequencyDistributionNamesMap().end(); ++freqDistrIt)
	{
		// Add it to the combo box
		ui->comboBoxFreqDistr->addItem(freqDistrIt->first);

	}

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxFreqDistr->findText(freqencyDistribution)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxFreqDistr->setCurrentText(freqencyDistribution);
	}
	else if ((nDex == ui->comboBoxFreqDistr->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxFreqDistr->setCurrentText(noSelection);
	}

    /////*************Frequency distribution end*******/////////

    /////***********Direction distribution start*******/////////
	typedef IrpsSeLDirectionDistribution *(*CreateSLDirectionDistributionCallback)();
	std::map<const QString, CreateSLDirectionDistributionCallback> ::iterator dirDistrIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (dirDistrIt = CrpsSeLDirectionDistributionFactory::GetDirectionDistributionNamesMap().begin(); dirDistrIt != CrpsSeLDirectionDistributionFactory::GetDirectionDistributionNamesMap().end(); ++dirDistrIt)
	{
		// Add it to the combo box
		ui->comboBoxDirDirec->addItem(dirDistrIt->first);

	}

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxDirDirec->findText(directionDistributionFunction)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxDirDirec->setCurrentText(directionDistributionFunction);
	}
	else if ((nDex == ui->comboBoxDirDirec->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxDirDirec->setCurrentText(noSelection);
	}

    /////***********Direction distribution end*******/////////

    // connection
    connect( ui->comboBoxSpectrumModel, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxPSDModelIndexChanged( int ) ) );

    connect( ui->comboBoxCpsdDecomp, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxPSDdecompIndexChanged( int ) ) );
   
    connect( ui->comboBoxDirSpread, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxDirSpreadingIndexChanged( int ) ) );

    connect( ui->comboBoxDirecSpectr, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxDirPSDIndexChanged( int ) ) );
    
    connect( ui->comboBoxFreqDistr, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxFrequencyDistrIndexChanged( int ) ) );

    connect( ui->comboBoxDirDirec, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxDirDistrIndexChanged( int ) ) );
    
    connect( ui->pushButtonSpectrumModelInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedPSDModelInit( ) ) );

    connect( ui->pushButtonCpsdDecompInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedPSDdecompInit( ) ) );
   
    connect( ui->pushButtonDirecSpreadInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedDirSpreadingInit( ) ) );
    
    connect( ui->pushButtonDirecSpectrInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedDirPSDInit( ) ) );

    connect( ui->pushButtonFreqDistrInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedFrequencyDistrInit( ) ) );
   
    connect( ui->pushButtonDirecDirInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedDirDistrInit( ) ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));


}

RPSSeLPSDDefinitionDialog::~RPSSeLPSDDefinitionDialog()
{
    delete ui;
}

void RPSSeLPSDDefinitionDialog::comboBoxPSDModelIndexChanged(int index)
{
    spectrumModel = ui->comboBoxSpectrumModel->currentText();
}
void RPSSeLPSDDefinitionDialog::comboBoxPSDdecompIndexChanged(int index)
{
    cpsdDecompositionMethod = ui->comboBoxCpsdDecomp->currentText();
}
void RPSSeLPSDDefinitionDialog::comboBoxDirSpreadingIndexChanged(int index)
{
   directionSpreadingFunction  = ui->comboBoxDirSpread->currentText();
}
void RPSSeLPSDDefinitionDialog::comboBoxDirPSDIndexChanged(int index)
{
    directionalSpectrumFunction = ui->comboBoxDirecSpectr->currentText();
}
void RPSSeLPSDDefinitionDialog::comboBoxFrequencyDistrIndexChanged(int index)
{
    freqencyDistribution = ui->comboBoxFreqDistr->currentText();
}
void RPSSeLPSDDefinitionDialog::comboBoxDirDistrIndexChanged(int index)
{
    directionDistributionFunction = ui->comboBoxDirDirec->currentText();
}

void RPSSeLPSDDefinitionDialog::OnBnClickedPSDModelInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLSpectrum* currentSelection = CrpsSeLXSpectrumFactory::BuildXSpectrum(spectrumModel);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(app->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSelection;
}
void RPSSeLPSDDefinitionDialog::OnBnClickedPSDdecompInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLPSDdecompositionMethod* currentSelection = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(cpsdDecompositionMethod);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(app->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSelection;
}
void RPSSeLPSDDefinitionDialog::OnBnClickedDirSpreadingInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLDirectionSpreadingFunction* currentSelection = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(directionSpreadingFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(app->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSelection;
}
void RPSSeLPSDDefinitionDialog::OnBnClickedDirPSDInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLDirectionalSpectrum* currentSelection = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(directionalSpectrumFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(app->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSelection;
}
void RPSSeLPSDDefinitionDialog::OnBnClickedFrequencyDistrInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLFrequencyDistribution* currentSelection = CrpsSeLFrequencyDistributionFactory::BuildFrequencyDistribution(freqencyDistribution);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(app->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSelection;
}
void RPSSeLPSDDefinitionDialog::OnBnClickedDirDistrInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLDirectionDistribution* currentSelection = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(directionDistributionFunction);

	// Check whether good object
	if (NULL == currentSelection) { return; }

	// Apply iniatial setting
	currentSelection->OnInitialSetting(app->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSelection;
}

void RPSSeLPSDDefinitionDialog::acceptInput()
 {
    numberOfFrequency = ui->lineEditNberOfFreqIncr->text().toDouble();
    minFrequency = ui->lineEditMinFreq->text().toDouble();
    maxFrequency = ui->lineEditMaxFreq->text().toDouble();
    frequencyIncrement = ui->lineEditFreqIncr->text().toDouble();
    numberOfDirection = ui->lineEditDirecNberOfIncr->text().toDouble();
    minDirection = ui->lineEditMinDirec->text().toDouble();
    maxDirection = ui->lineEditMaxDirec->text().toDouble();
    directionIncrement = ui->lineEditDirecIncr->text().toDouble();

 }

