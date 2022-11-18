#include "rpswindvelocitydefinitiondlg.h"
#include "ui_rpswindvelocitydefinitiondlg.h"
#include "rps/windLab/rpsWindLabSimulation.h"
#include "RPSWindLabAPI.h"

RPSWindVelocityDefinitionDlg::RPSWindVelocityDefinitionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSWindVelocityDefinitionDlg)
{
    ui->setupUi(this);

     QString noSelection = "<None>";

	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

     numberOfSpatialPosition = rpsWindLabSimulator->GetWindLabData().numberOfSpatialPosition;
	 numberOfTimeIncrements = rpsWindLabSimulator->GetWindLabData().numberOfTimeIncrements;
	 timeIncrement = rpsWindLabSimulator->GetWindLabData().timeIncrement;
	 minTime = rpsWindLabSimulator->GetWindLabData().minTime;
	 maxTime = rpsWindLabSimulator->GetWindLabData().maxTime;
	 numberOfSample = rpsWindLabSimulator->GetWindLabData().numberOfSample;
	 stationarity = rpsWindLabSimulator->GetWindLabData().stationarity;
	 gaussianity = rpsWindLabSimulator->GetWindLabData().gaussianity;
	 spatialDistribution = rpsWindLabSimulator->GetWindLabData().spatialDistribution;

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

     int min = 1;
     int max = 10000000;

     ui->lineEditNberOfLocation->setRange(min, max);
     ui->lineEditNberOfTimeIncr->setRange(min, max);
     ui->lineEditNumberOfSample->setRange(min, max);

    ui->lineEditNberOfLocation->setValue(numberOfSpatialPosition);
    ui->lineEditNberOfTimeIncr->setValue(numberOfTimeIncrements);
    ui->lineEditTimeIncreValue->setText(QString::number(timeIncrement));
    ui->lineEditMinTimeValue->setText(QString::number(minTime));
    ui->lineEditMaxTimeValue->setText(QString::number(minTime + (numberOfTimeIncrements*timeIncrement)));
    ui->lineEditNumberOfSample->setValue(numberOfSample);

    ui->comboBoxWindSpationDistr->clear();

	ui->comboBoxWindSpationDistr->addItem(noSelection);

    /////******spatial location distribution start*******/////////
	typedef IrpsWLLocationDistribution *(*CreateLocDistrCallback)();
	std::map<const QString, CreateLocDistrCallback> ::iterator locIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (locIt = CrpsLocationDistributionFactory::GetLocDistrNamesMap().begin(); locIt != CrpsLocationDistributionFactory::GetLocDistrNamesMap().end(); ++locIt)
	{
		// Add it to the combo box
		ui->comboBoxWindSpationDistr->addItem(locIt->first);

	}

	// Show the current selected randomness
	// Starting index
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxWindSpationDistr->findText(spatialDistribution)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxWindSpationDistr->setCurrentText(spatialDistribution);
	}
	else if ((nDex == ui->comboBoxWindSpationDistr->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxWindSpationDistr->setCurrentText(noSelection);
	}

    /////******spatial location distribution end*******/////////

    // connection
    connect( ui->comboBoxWindSpationDistr, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxSpatialDistrIndexChanged( int ) ) );
  
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

RPSWindVelocityDefinitionDlg::~RPSWindVelocityDefinitionDlg()
{
    delete ui;
}


void RPSWindVelocityDefinitionDlg::comboBoxSpatialDistrIndexChanged(int index)
{
    spatialDistribution = ui->comboBoxWindSpationDistr->currentText();
}

void RPSWindVelocityDefinitionDlg::radioButtonStationarityToggled(bool)
{
    stationarity = true;
}

void RPSWindVelocityDefinitionDlg::radioButtonNonStationarityToggled(bool)
{
    stationarity = false;
}

void RPSWindVelocityDefinitionDlg::radioButtonGaussianityToggled(bool)
{
    gaussianity = true;
}

void RPSWindVelocityDefinitionDlg::radioButtonNonGaussianityToggled(bool)
{
    gaussianity = false;
}

void RPSWindVelocityDefinitionDlg::OnBnClickedSpatialDistrInit()
{
	RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

	// Build an object
	IrpsWLLocationDistribution* currentSpatialDistr = CrpsLocationDistributionFactory::BuildLocationDistribution(spatialDistribution);

	// Check whether good object
	if (NULL == currentSpatialDistr) { return; }

	// Apply iniatial setting
	currentSpatialDistr->OnInitialSetting(rpsWindLabSimulator->GetWindLabData(), rpsWindLabSimulator->information);

    // show information before deleting the object
	rpsWindLabSimulator->sendInformation(rpsWindLabSimulator->information);
    rpsWindLabSimulator->information.clear();
	
	// Delete the object
	delete currentSpatialDistr;
}

 void RPSWindVelocityDefinitionDlg::acceptInput()
 {
    numberOfSpatialPosition = ui->lineEditNberOfLocation->text().toInt();
    numberOfTimeIncrements = ui->lineEditNberOfTimeIncr->text().toInt();
    timeIncrement = ui->lineEditTimeIncreValue->text().toDouble();
    minTime = ui->lineEditMinTimeValue->text().toDouble();
    maxTime = ui->lineEditMaxTimeValue->text().toDouble();
    numberOfSample = ui->lineEditNumberOfSample->text().toInt();
 }
