#include "rpsgroundmotiondefinitiondlg.h"
#include "ui_rpsgroundmotiondefinitiondlg.h"

#include "rps/seismicLab/rpsSeismicLabSimulation.h"
#include "RPSSeismicLabAPI.h"

RPSGroundMotionDefinitionDlg::RPSGroundMotionDefinitionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSGroundMotionDefinitionDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

     numberOfSpatialPosition = rpsSeismicLabSimulator->GetSeismicLabData().numberOfSpatialPosition;
	 numberOfTimeIncrements = rpsSeismicLabSimulator->GetSeismicLabData().numberOfTimeIncrements;
	 timeIncrement = rpsSeismicLabSimulator->GetSeismicLabData().timeIncrement;
	 minTime = rpsSeismicLabSimulator->GetSeismicLabData().minTime;
	 maxTime = rpsSeismicLabSimulator->GetSeismicLabData().maxTime;
	 numberOfSample = rpsSeismicLabSimulator->GetSeismicLabData().numberOfSample;
	 stationarity = rpsSeismicLabSimulator->GetSeismicLabData().stationarity;
	 gaussianity = rpsSeismicLabSimulator->GetSeismicLabData().gaussianity;
	 spatialDistribution = rpsSeismicLabSimulator->GetSeismicLabData().spatialDistribution;
	 soilType = rpsSeismicLabSimulator->GetSeismicLabData().soilType;

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

    ui->lineEditNberOfLocation->setText(QString::number(numberOfSpatialPosition));
    ui->lineEditNberOfTimeIncr->setText(QString::number(numberOfTimeIncrements));
    ui->lineEditTimeIncreValue->setText(QString::number(timeIncrement));
    ui->lineEditMinTimeValue->setText(QString::number(minTime));
    ui->lineEditMaxTimeValue->setText(QString::number(minTime + (numberOfTimeIncrements*timeIncrement)));
    ui->lineEditNumberOfSample->setText(QString::number(numberOfSample));

    ui->comboBoxSpationDistr->clear();
    ui->comboBoxSoilType->clear();

	ui->comboBoxSpationDistr->addItem(noSelection);
	ui->comboBoxSoilType->addItem(noSelection);

	ui->comboBoxSoilType->addItem("Clay");
	ui->comboBoxSoilType->addItem("Deep Cohesionless");
	ui->comboBoxSoilType->addItem("Rock");
	ui->comboBoxSoilType->addItem("Sand");
	ui->comboBoxSoilType->addItem("Soft");
	ui->comboBoxSoilType->addItem("Still");

    /////******spatial location distribution start*******/////////
	typedef IrpsSLLocationDistribution *(*CreateLocDistrCallback)();
	std::map<const QString, CreateLocDistrCallback> ::iterator locIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
	for (locIt = CrpsSLLocationDistributionFactory::GetLocDistrNamesMap().begin(); locIt != CrpsSLLocationDistributionFactory::GetLocDistrNamesMap().end(); ++locIt)
	{
		// Add it to the combo box
		ui->comboBoxSpationDistr->addItem(locIt->first);

	}

	// Show the current selected randomness
	// Starting index
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxSpationDistr->findText(spatialDistribution)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSpationDistr->setCurrentText(spatialDistribution);
	}
	else if ((nDex == ui->comboBoxSpationDistr->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSpationDistr->setCurrentText(noSelection);
	}

    /////******spatial location distribution end*******/////////

    /////***************wave type start***************/////////
    // Search the combo list elements from index 0 until the current selected rp is found, then get its index
	if ((nDex != ui->comboBoxSoilType->findText(soilType)))
	{
		// Select the corresponding randomness in the combox based on the index
		ui->comboBoxSoilType->setCurrentText(soilType);
	}
	else if ((nDex == ui->comboBoxSoilType->findText(noSelection)))
	{
		// Select the none text then
		ui->comboBoxSoilType->setCurrentText(noSelection);
	}

    /////***************wave type end***************/////////

    // connection
    connect( ui->comboBoxSpationDistr, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxSpatialDistrIndexChanged( int ) ) );

	connect( ui->comboBoxSoilType, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxSoilTypeIndexChanged( int ) ) );
  
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

RPSGroundMotionDefinitionDlg::~RPSGroundMotionDefinitionDlg()
{
    delete ui;
}


void RPSGroundMotionDefinitionDlg::comboBoxSpatialDistrIndexChanged(int index)
{
    spatialDistribution = ui->comboBoxSpationDistr->currentText();
}

void RPSGroundMotionDefinitionDlg::comboBoxSoilTypeIndexChanged(int index)
{
    soilType = ui->comboBoxSoilType->currentText();
}

void RPSGroundMotionDefinitionDlg::radioButtonStationarityToggled(bool)
{
    stationarity = true;
}

void RPSGroundMotionDefinitionDlg::radioButtonNonStationarityToggled(bool)
{
    stationarity = false;
}

void RPSGroundMotionDefinitionDlg::radioButtonGaussianityToggled(bool)
{
    gaussianity = true;
}

void RPSGroundMotionDefinitionDlg::radioButtonNonGaussianityToggled(bool)
{
    gaussianity = false;
}

void RPSGroundMotionDefinitionDlg::OnBnClickedSpatialDistrInit()
{
	RPSSeismicLabSimulation *rpsSeismicLabSimulator = (RPSSeismicLabSimulation *)this->parent();

	// Build an object
	IrpsSLLocationDistribution* currentSpatialDistr = CrpsSLLocationDistributionFactory::BuildLocationDistribution(spatialDistribution);

	// Check whether good object
	if (NULL == currentSpatialDistr) { return; }

	// Apply iniatial setting
	currentSpatialDistr->OnInitialSetting(rpsSeismicLabSimulator->GetSeismicLabData(), rpsSeismicLabSimulator->information);

	// Delete the object
	delete currentSpatialDistr;
}

 void RPSGroundMotionDefinitionDlg::acceptInput()
 {
    numberOfSpatialPosition = ui->lineEditNberOfLocation->text().toDouble();
    numberOfTimeIncrements = ui->lineEditNberOfTimeIncr->text().toDouble();
    timeIncrement = ui->lineEditTimeIncreValue->text().toDouble();
    minTime = ui->lineEditMinTimeValue->text().toDouble();
	maxTime = ui->lineEditMaxTimeValue->text().toDouble();
    numberOfSample = ui->lineEditNumberOfSample->text().toDouble();
 }
    