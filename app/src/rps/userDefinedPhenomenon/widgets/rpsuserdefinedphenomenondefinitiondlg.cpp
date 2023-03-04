#include "rpsuserdefinedphenomenondefinitiondlg.h"
#include "ui_rpsuserdefinedphenomenondefinitiondlg.h"
#include "rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulation.h"
#include "RPSUserDefinedPhenomenonAPI.h"
#include <cmath>

RPSUserDefinedPhenomenonDefinitionDlg::RPSUserDefinedPhenomenonDefinitionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPSUserDefinedPhenomenonDefinitionDlg)
{
    ui->setupUi(this);

     QString noSelection = "<None>";

	RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();

     numberOfProcess = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().numberOfProcess;
	 indexSetSize = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().indexSetSize;
	 indexIncrement = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().indexIncrement;
	 minIndexSetValue = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().minIndexSetValue;
	 maxIndexSetValue = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().maxIndexSetValue;
	 numberOfSample = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().numberOfSample;
	 stationarity = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().stationarity;
	 gaussianity = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().gaussianity;
	 userDefinedPhenomenon = rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData().userDefinedPhenomenon;

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

     ui->lineEditTimeIncreValue->setMinimum(-INFINITY);
     ui->lineEditTimeIncreValue->setMaximum(std::numeric_limits<double>::max());
     ui->lineEditMinTimeValue->setMinimum(-INFINITY);
     ui->lineEditMinTimeValue->setMaximum(std::numeric_limits<double>::max());
     ui->lineEditMaxTimeValue->setMinimum(-INFINITY);
     ui->lineEditMaxTimeValue->setMaximum(std::numeric_limits<double>::max());


     ui->lineEditNberOfLocation->setRange(min, max);
     ui->lineEditNberOfTimeIncr->setRange(min, max);
     ui->lineEditNumberOfSample->setRange(min, max);

    ui->lineEditNberOfLocation->setValue(numberOfProcess);
    ui->lineEditNberOfTimeIncr->setValue(indexSetSize);
    ui->lineEditTimeIncreValue->setValue(indexIncrement);
    ui->lineEditMinTimeValue->setValue(minIndexSetValue);
    ui->lineEditMaxTimeValue->setValue(minIndexSetValue + (indexSetSize*indexIncrement));
    ui->lineEditNumberOfSample->setValue(numberOfSample);

    ui->comboBoxWindSpationDistr->clear();

	ui->comboBoxWindSpationDistr->addItem(noSelection);

    /////******spatial location distribution start*******/////////
    typedef IrpsUserDefinedPhenomenon *(*CreateUserDefinedPhenomenonCallback)();
	std::map<const QString, CreateUserDefinedPhenomenonCallback> ::iterator userPhenIt;
		
    // Iterate though the map and show all the registed spatial distribution in the combo box
    for (userPhenIt = CrpsUserDefinedPhenomenonFactory::GetUserDefinedPhenomenonNamesMap().begin(); userPhenIt != CrpsUserDefinedPhenomenonFactory::GetUserDefinedPhenomenonNamesMap().end(); ++userPhenIt)
	{
		// Add it to the combo box
		ui->comboBoxWindSpationDistr->addItem(userPhenIt->first);
	}

	// Show the current selected randomness
	// Starting index
	int nDex = -1;

	// Search the combo list elements from index 0 until the current selected rp is found, then get its index
    if ((nDex != ui->comboBoxWindSpationDistr->findText(userDefinedPhenomenon)))
	{
		// Select the corresponding randomness in the combox based on the index
        ui->comboBoxWindSpationDistr->setCurrentText(userDefinedPhenomenon);
	}
    else if (nDex == ui->comboBoxWindSpationDistr->findText(noSelection))
	{
		// Select the none text then
		ui->comboBoxWindSpationDistr->setCurrentText(noSelection);
	}

    // connection
    connect( ui->comboBoxWindSpationDistr, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxUserDefinedPhenomenonChanged( int ) ) );
  
    connect( ui->radioButtonStationary, SIGNAL(  toggled(bool) ),
             this, SLOT( radioButtonStationarityToggled(bool) ) );
  
    connect( ui->radioButtonNonStationary, SIGNAL(  toggled(bool) ),
             this, SLOT( radioButtonNonStationarityToggled(bool) ) );
   
    connect( ui->radioButtonGaussion, SIGNAL(  toggled(bool) ),
             this, SLOT( radioButtonGaussianityToggled( bool) ) );
  
    connect( ui->radioButtonNonGaussion, SIGNAL(  toggled(bool)  ),
             this, SLOT( radioButtonNonGaussianityToggled( bool) ) );

    connect( ui->pushButtonSpatialDistrInit, SIGNAL( clicked() ),
             this, SLOT( OnBnClickedUserDefinedPhenomenonInit( ) ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

RPSUserDefinedPhenomenonDefinitionDlg::~RPSUserDefinedPhenomenonDefinitionDlg()
{
    delete ui;
}


void RPSUserDefinedPhenomenonDefinitionDlg::comboBoxUserDefinedPhenomenonChanged(int index)
{
    userDefinedPhenomenon = ui->comboBoxWindSpationDistr->currentText();
}

void RPSUserDefinedPhenomenonDefinitionDlg::radioButtonStationarityToggled(bool)
{
    stationarity = true;
}

void RPSUserDefinedPhenomenonDefinitionDlg::radioButtonNonStationarityToggled(bool)
{
    stationarity = false;
}

void RPSUserDefinedPhenomenonDefinitionDlg::radioButtonGaussianityToggled(bool)
{
    gaussianity = true;
}

void RPSUserDefinedPhenomenonDefinitionDlg::radioButtonNonGaussianityToggled(bool)
{
    gaussianity = false;
}

void RPSUserDefinedPhenomenonDefinitionDlg::OnBnClickedUserDefinedPhenomenonInit()
{
	RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator = (RPSUserDefinedPhenomenonSimulation *)this->parent();

	// Build an object
    IrpsUserDefinedPhenomenon* currentSpatialDistr = CrpsUserDefinedPhenomenonFactory::BuildUserDefinedPhenomenon(userDefinedPhenomenon);

	// Check whether good object
	if (NULL == currentSpatialDistr) { return; }

	// Apply iniatial setting
	currentSpatialDistr->OnInitialSetting(rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData(), rpsUserDefinedPhenomenonSimulator->information);

    // show information before deleting the object
	rpsUserDefinedPhenomenonSimulator->sendInformation(rpsUserDefinedPhenomenonSimulator->information);
    rpsUserDefinedPhenomenonSimulator->information.clear();
	
	// Delete the object
	delete currentSpatialDistr;
}

 void RPSUserDefinedPhenomenonDefinitionDlg::acceptInput()
 {
    numberOfProcess = ui->lineEditNberOfLocation->text().toDouble();
    indexSetSize = ui->lineEditNberOfTimeIncr->text().toDouble();
    indexIncrement = ui->lineEditTimeIncreValue->text().toDouble();
    minIndexSetValue = ui->lineEditMinTimeValue->text().toDouble();
    maxIndexSetValue = ui->lineEditMaxTimeValue->text().toDouble();
	numberOfSample = ui->lineEditNumberOfSample->text().toDouble();
 }
