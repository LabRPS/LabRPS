#include "rpsseawavedefinitiondlg.h"
#include "ui_rpsseawavedefinitiondlg.h"

#include "ApplicationWindow.h"
#include "RPSSeaLabAPI.h"

RPSSeaWaveDefinitionDlg::RPSSeaWaveDefinitionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSSeaWaveDefinitionDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	ApplicationWindow *app = (ApplicationWindow *)this->parent();

     numberOfSpatialPosition = app->GetSeaLabData().numberOfSpatialPosition;
	 numberOfTimeIncrements = app->GetSeaLabData().numberOfTimeIncrements;
	 timeIncrement = app->GetSeaLabData().timeIncrement;
	 minTime = app->GetSeaLabData().minTime;
	 numberOfSample = app->GetSeaLabData().numberOfSample;
	 stationarity = app->GetSeaLabData().stationarity;
	 gaussianity = app->GetSeaLabData().gaussianity;
	 spatialDistribution = app->GetSeaLabData().spatialDistribution;
	 waveType = app->GetSeaLabData().waveType;

     if(true == stationarity)
	{
		ui->radioButtonStationary->setChecked(Qt::Checked);
	}
	else
	{
		ui->radioButtonNonStationary->setChecked(Qt::Checked);
	}

	 if(true == gaussianity)
	{
		ui->radioButtonGaussion->setChecked(Qt::Checked);
	}
	else
	{
	   ui->radioButtonNonGaussion->setChecked(Qt::Checked);

	}

    ui->lineEditSeaNberOfLocation->setText(QString::number(numberOfSpatialPosition));
    ui->lineEditNberOfTimeIncr->setText(QString::number(numberOfTimeIncrements));
    ui->lineEditTimeIncreValue->setText(QString::number(timeIncrement));
    ui->lineEditMinTimeValue->setText(QString::number(minTime));
    ui->lineEditMaxTimeValue->setText(QString::number(minTime + (numberOfTimeIncrements*timeIncrement)));
    ui->lineEditNumberOfSample->setText(QString::number(numberOfSample));

    ui->comboBoxSeaSpationDistr->clear();
    ui->comboBoxSeaWaveType->clear();

	ui->comboBoxSeaSpationDistr->addItem(noSelection);
	ui->comboBoxSeaWaveType->addItem(noSelection);

	ui->comboBoxSeaWaveType->addItem("Capillary wave");
	ui->comboBoxSeaWaveType->addItem("Seiche");
	ui->comboBoxSeaWaveType->addItem("Seismic sea wave");
	ui->comboBoxSeaWaveType->addItem("Tide");
	ui->comboBoxSeaWaveType->addItem("Wind wave");

    /////******spatial location distribution start*******/////////
	typedef IrpsSeLLocationDistribution *(*CreateLocDistrCallback)();
	std::map<const QString, CreateLocDistrCallback> ::iterator locIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (locIt = CrpsSeLLocationDistributionFactory::GetLocDistrNamesMap().begin(); locIt != CrpsSeLLocationDistributionFactory::GetLocDistrNamesMap().end(); ++locIt)
	{
		// Add it to the combo box
		ui->comboBoxSeaSpationDistr->addItem(locIt->first);

	}

	// Show the current selected randomness
	// Starting index
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxSeaSpationDistr->findText(spatialDistribution)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSeaSpationDistr->setCurrentText(spatialDistribution);
	}
	else if ((nDex == ui->comboBoxSeaSpationDistr->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSeaSpationDistr->setCurrentText(noSelection);
	}

    /////******spatial location distribution end*******/////////

    /////***************wave type start***************/////////
    // Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxSeaWaveType->findText(waveType)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSeaWaveType->setCurrentText(waveType);
	}
	else if ((nDex == ui->comboBoxSeaWaveType->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSeaWaveType->setCurrentText(noSelection);
	}

    /////***************wave type end***************/////////

    // connection
    connect( ui->comboBoxSeaSpationDistr, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxSpatialDistrIndexChanged( int ) ) );

	connect( ui->comboBoxSeaWaveType, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxWaveTypeIndexChanged( int ) ) );
  
    connect( ui->radioButtonStationary, SIGNAL(  toggled(bool) ),
             this, SLOT( radioButtonStationarityToggled(bool) ) );
  
    connect( ui->radioButtonNonStationary, SIGNAL(  toggled(bool) ),
             this, SLOT( radioButtonNonStationarityToggled(bool) ) );
   
    connect( ui->radioButtonGaussion, SIGNAL(  toggled(bool) ),
             this, SLOT( radioButtonGaussianityToggled( bool) ) );
  
    connect( ui->radioButtonNonGaussion, SIGNAL(  toggled(bool)  ),
             this, SLOT( radioButtonNonGaussianityToggled( bool) ) );

    connect( ui->pushButtonSpatialDistrInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedSpatialDistrInit( ) ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

RPSSeaWaveDefinitionDlg::~RPSSeaWaveDefinitionDlg()
{
    delete ui;
}


void RPSSeaWaveDefinitionDlg::comboBoxSpatialDistrIndexChanged(int index)
{
    spatialDistribution = ui->comboBoxSeaSpationDistr->currentText();
}

void RPSSeaWaveDefinitionDlg::comboBoxWaveTypeIndexChanged(int index)
{
    waveType = ui->comboBoxSeaWaveType->currentText();
}

void RPSSeaWaveDefinitionDlg::radioButtonStationarityToggled(bool)
{
    stationarity = true;
}

void RPSSeaWaveDefinitionDlg::radioButtonNonStationarityToggled(bool)
{
    stationarity = false;
}

void RPSSeaWaveDefinitionDlg::radioButtonGaussianityToggled(bool)
{
    gaussianity = true;
}

void RPSSeaWaveDefinitionDlg::radioButtonNonGaussianityToggled(bool)
{
    gaussianity = false;
}

void RPSSeaWaveDefinitionDlg::OnBnClickedSpatialDistrInit()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

	// Build an object
	IrpsSeLLocationDistribution* currentSpatialDistr = CrpsSeLLocationDistributionFactory::BuildLocationDistribution(spatialDistribution);

	// Check whether good object
	if (NULL == currentSpatialDistr) { return; }

	// Apply iniatial setting
	currentSpatialDistr->OnInitialSetting(app->GetSeaLabData(), app->information);

	// Delete the object
	delete currentSpatialDistr;
}

 void RPSSeaWaveDefinitionDlg::acceptInput()
 {
    numberOfSpatialPosition = ui->lineEditSeaNberOfLocation->text().toDouble();
    numberOfTimeIncrements = ui->lineEditNberOfTimeIncr->text().toDouble();
    timeIncrement = ui->lineEditTimeIncreValue->text().toDouble();
    minTime = ui->lineEditMinTimeValue->text().toDouble();
    numberOfSample = ui->lineEditNumberOfSample->text().toDouble();
 }
    