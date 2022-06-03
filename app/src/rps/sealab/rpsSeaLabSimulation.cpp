#include "rpsSeaLabSimulation.h"
#include "ApplicationWindow.h"

#include "untitled3.h"
#include "RPSSeaLabAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/sealab/widgets/rpsseawavedefinitiondlg.h"
#include "rps/sealab/widgets/rpsselpsddefinitiondialog.h"
#include "rps/sealab/widgets/rpsselcoherencedlg.h"
#include "rps/sealab/widgets/rpsselcorrelationdlg.h"
#include "rps/sealab/widgets/rpsselmodulationdlg.h"
#include "rps/sealab/widgets/prsselsimuoptionsdlg.h"

#include "rps/pluginBrower/RPSPluginsBrowser.h"
#include "rps/pluginBrower/pluginbrwoser.h"
#include "rps/pluginBrower/plugininstallerbrowser.h"
#include "RPS.h"

#include <QString>
#include <QMessageBox>
#include <QDebug>

RPSSeaLabSimulation::RPSSeaLabSimulation(QWidget *parent) :
    QWidget(parent)
  {
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

   qDebug() << "permissions command: ";


  if (app->getSelectedRandomPhenomenon() == "Wind Velocity")
  {

  }
  else if(app->getSelectedRandomPhenomenon() == "Seismic Ground motion")
  {

  }
  else if(app->getSelectedRandomPhenomenon() == "Sea Surface")
  {

    // initialized seaLab simulation data
    seaLabDataInitialize();

    // read install seaLab from registry if any
    SeLReadAllTobeInstallObjectsFromRegistry();
    SeLClearAllTobeInstallObjectsFromRegistry();

	IntallRegistrySeaLabPlugins();		
   
  }

}

RPSSeaLabSimulation::~RPSSeaLabSimulation()
{

  QSettings settings;
  selectedRandomPhenomenon = settings.value("rpsPhenomenon", false).toString();

  if (selectedRandomPhenomenon == "Wind Velocity"){


  }else if(selectedRandomPhenomenon == "Seismic Ground motion"){

  }else if(selectedRandomPhenomenon == "Sea Surface"){

    RPSWriteInstalledPluginsToRegistry();

    // write install seaLab from registry if any
    SeLWriteAllTobeInstallObjectsToRegistry();

  }

}


void RPSSeaLabSimulation::seaSurface(){
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  std::unique_ptr<RPSSeaWaveDefinitionDlg> dlg(new RPSSeaWaveDefinitionDlg(app));
  
  if (dlg->exec() == QDialog::Accepted)
  {
	 GetSeaLabData().numberOfSpatialPosition = dlg->numberOfSpatialPosition;
	 GetSeaLabData().numberOfTimeIncrements = dlg->numberOfTimeIncrements;
	 GetSeaLabData().timeIncrement = dlg->timeIncrement;
	 GetSeaLabData().minTime = dlg->minTime;
	 GetSeaLabData().numberOfSample = dlg->numberOfSample;
	 GetSeaLabData().stationarity = dlg->stationarity;
	 GetSeaLabData().gaussianity = dlg->gaussianity;
	 GetSeaLabData().spatialDistribution = dlg->spatialDistribution;
	 GetSeaLabData().waveType = dlg->waveType;
  } 
  
}
void RPSSeaLabSimulation::spectrumSea(){
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

  std::unique_ptr<RPSSeLPSDDefinitionDialog> dlg(new RPSSeLPSDDefinitionDialog(app));
  
  if (dlg->exec() == QDialog::Accepted)
  {
	 GetSeaLabData().numberOfFrequency = dlg->numberOfFrequency;
	 GetSeaLabData().minFrequency = dlg->minFrequency;
	 GetSeaLabData().maxFrequency = dlg->maxFrequency;
	 GetSeaLabData().frequencyIncrement = dlg->frequencyIncrement;
	 GetSeaLabData().numberOfDirection = dlg->numberOfDirection;
	 GetSeaLabData().minDirection = dlg->minDirection;
	 GetSeaLabData().maxDirection = dlg->maxDirection;
	 GetSeaLabData().directionIncrement = dlg->directionIncrement;
   
    GetSeaLabData().spectrumModel = dlg->spectrumModel;
	 GetSeaLabData().cpsdDecompositionMethod = dlg->cpsdDecompositionMethod;
	 GetSeaLabData().freqencyDistribution = dlg->freqencyDistribution;
	 GetSeaLabData().directionDistributionFunction = dlg->directionDistributionFunction;
	 GetSeaLabData().directionSpreadingFunction = dlg->directionSpreadingFunction;
	 GetSeaLabData().directionalSpectrumFunction = dlg->directionalSpectrumFunction;

  } 
}

void RPSSeaLabSimulation::coherenceSea(){
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  std::unique_ptr<RPSSeLCoherenceDlg> dlg(new RPSSeLCoherenceDlg(app));
  
  if (dlg->exec() == QDialog::Accepted)
  {
	 GetSeaLabData().coherenceFunction = dlg->coherenceFunction;
	 
  } 
   
}
void RPSSeaLabSimulation::correlationSea(){
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  std::unique_ptr<RPSSeLCorrelationDlg> dlg(new RPSSeLCorrelationDlg(app));
  
  if (dlg->exec() == QDialog::Accepted)
  {
	 GetSeaLabData().correlationFunction = dlg->correlationFunction;
	 
  } 
}
void RPSSeaLabSimulation::modulationSea(){
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

  std::unique_ptr<RPSSeLModulationDlg> dlg(new RPSSeLModulationDlg(app));
  if (dlg->exec() == QDialog::Accepted)
  {
	 GetSeaLabData().modulationFunction = dlg->modulationFunction;
	 
  } 
}

void RPSSeaLabSimulation::runSimulation()
{
//   // Build an object
// 	IrpsSeLRandomness* currentRndProvider = CrpsSeLRandomnessFactory::BuildRandomness(GetSeaLabData().randomnessProvider);

// 	// Check whether good object
// 	if (NULL == currentRndProvider) { return; }

//   mat randomValueArray(GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

// 	// Apply iniatial setting
// 	currentRndProvider->GenerateRandomArrayFP(GetSeaLabData(), randomValueArray, information);

//   QMessageBox::warning(
//         this, ("sim"),
//         QString::number(randomValueArray(0,0)));

//   logInfo = ("hahahahahahaha");
//   showResults(true);
  
//   QString arrayName = ("Random Phase (%1,%2)").arg( GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

//   Table *table = newTable(arrayName, GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

//   for (int j = 0; j < GetSeaLabData().numberOfSpatialPosition; j++) {
//     for (int i = 0; i < GetSeaLabData().numberOfFrequency; i++) {
//     table->setCellValue(i, j, randomValueArray(i,j));
//       table->showNormal();

//     // t->column(i)->setTextAt(i, randomValueArray(i,j)); 
//   }  }


 
}
void RPSSeaLabSimulation::pauseSimulation(){
  //  PlunginIntallationWizard wizard;
  //   wizard.exec();
}
void RPSSeaLabSimulation::stopSimulation(){
    ApplicationWindow *app = (ApplicationWindow *)this->parent();

  std::unique_ptr<PluginInstallerBrowser> dlg(new PluginInstallerBrowser(app));

  // QString strPath = "E:\\NewLabRPSProject\\Staffs\\LabRPS\\LabRPS\\plugins\\";
  // PluginManager::GetInstance().SearchForAllPlugins(strPath);
  // dlg->ui->listWidgetLocalPlugin->addItem("hahaha");

  dlg->exec();
 

}
void RPSSeaLabSimulation::simulationOptions()
{
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  std::unique_ptr<PRSSeLSimuOptionsDlg> dlg(new PRSSeLSimuOptionsDlg(app));
  if (dlg->exec() == QDialog::Accepted)
  {
    GetSeaLabData().simulationMethod = dlg->currentsimulationMethod;
    GetSeaLabData().randomnessProvider = dlg->currentRandomnessProvider;
    GetSeaLabData().comparisonMode = dlg->comparisonMode;
    GetSeaLabData().largeScaleSimulationMode = dlg->largeScaleMode;


  } 
}

CRPSSeaLabsimuData& RPSSeaLabSimulation::GetSeaLabData()
{
	return seaLabData;
}

void RPSSeaLabSimulation::seaLabDataInitialize()
{
    seaLabData.numberOfSpatialPosition = 3;
	seaLabData.numberOfSample = 1;
	seaLabData.numberOfFrequency = 1024;
	seaLabData.minFrequency = 0;
	seaLabData.maxFrequency = 20;
	seaLabData.numberOfTimeIncrements = 2 * seaLabData.numberOfFrequency*seaLabData.numberOfSpatialPosition;
	seaLabData.timeIncrement = 0.25;
	seaLabData.frequencyIncrement = seaLabData.maxFrequency / seaLabData.numberOfFrequency;
	seaLabData.stationarity = 1;
	seaLabData.gaussianity = 1;
	seaLabData.minTime = 0;
	seaLabData.frequencyIndex = 0;
	seaLabData.timeIndex = 0;
	seaLabData.directionIndex = 0;
	seaLabData.directionalSpectrumFunction = ("RPS Directional Spectrum"); 
	seaLabData.simulationMethod = ("Deodatis et al 1996");
	seaLabData.spatialDistribution = ("Horizontal Distribution");
	seaLabData.coherenceFunction = ("Abrahamson Coherence");
	seaLabData.randomnessProvider = ("Uniform Random Phases");
	seaLabData.spectrumModel = ("Jonswap Spectrum");
	seaLabData.directionSpreadingFunction = ("RPS Spreading Function 1");
	seaLabData.directionDistributionFunction = ("RPS Uniform Direction Distribution");
	seaLabData.cpsdDecompositionMethod = ("RPS Cholesky Decomposition");
	seaLabData.freqencyDistribution = ("RPS Uniform Frequency Distribution");
	seaLabData.modulationFunction = ("Bogdanoff-Goldberg-Bernard Modulation function");
	seaLabData.direction = 1;
	seaLabData.numberOfDirection = 1024;
	seaLabData.minDirection = -1.57;
	seaLabData.maxDirection = 1.57;
	seaLabData.directionIncrement = (seaLabData.maxDirection - seaLabData.minDirection) / seaLabData.numberOfDirection;
	seaLabData.comparisonCategory = ("Simulation Method");
	seaLabData.numberOfTimeLags = seaLabData.numberOfFrequency;
    seaLabData.waveType = "Wind wave";
	seaLabData.correlationFunction = ("RPS Correlation");

}


int RPSSeaLabSimulation::RPSWriteToBeInstallObjectsToRegistry()
{
//   int i = 1;
// 	QString PlgName;
// 	QString Descript;
  
//   // number of plugins to be installed
// 	int NberOfInstalledPlugins = PluginManager::GetInstance().GetInstalledPluginsMap().size();

//   QSettings settings;
  
//   settings.beginGroup("To Be Installed Objects");
//   settings.setValue("NberOfInstalledPlugins", NberOfInstalledPlugins);
  
//   std::map<QString, PluginInstance *>::iterator it;
// 	for (it = PluginManager::GetInstance().GetInstalledPluginsMap().begin(); it != PluginManager::GetInstance().GetInstalledPluginsMap().end(); ++it)
// 	{
// 		// Get the plugin names
// 		Descript = it->second->GetPluginSbubFolder(); // second veut dire "b", first sera "a" map<a,b>

// 		// Make a name of each plugin to be saved
//     PlgName = tr("%1").arg(i);

// 		settings.setValue(PlgName, Descript);

// 		i++;
// 	}

//   settings.endGroup();

	return 1;
}

int RPSSeaLabSimulation::RPSWriteInstalledPluginsToRegistry()
{
  int i = 1;
	QString PlgName;
	QString Descript;
  
  // number of plugins to be installed
	int NberOfInstalledPlugins = PluginManager::GetInstance().GetInstalledPluginsMap().size();

  QSettings settings;
  settings.beginGroup("To Be Installed Objects");
  settings.setValue("NberOfInstalledPlugins", NberOfInstalledPlugins);
  
  std::map<QString, PluginInstance *>::iterator it;
	for (it = PluginManager::GetInstance().GetInstalledPluginsMap().begin(); it != PluginManager::GetInstance().GetInstalledPluginsMap().end(); ++it)
	{
		// Get the plugin names
		Descript = it->second->GetPluginSbubFolder(); // second veut dire "b", first sera "a" map<a,b>

		// Make a name of each plugin to be saved
    PlgName = tr("%1").arg(i);

		settings.setValue(PlgName, Descript);

		i++;
	}

  settings.endGroup();

	return 1;
}

int RPSSeaLabSimulation::RPSReadInstalledPluginsFromRegistry()
{
	RPSReadInstalledPluginsFromRegistryCommon();

	return 1;
}

int RPSSeaLabSimulation::RPSReadInstalledPluginsFromRegistryCommon()
{
  int i = 1;
	QString PlgName;
	QString Descript;
  
  QSettings settings;
  
  settings.beginGroup("To Be Installed Objects");
  int NberOfInstalledPlugins = settings.value("NberOfInstalledPlugins").toInt();

 
// Read one by one plugins saved in registry
	for (int i = 1; i <= NberOfInstalledPlugins; i++)
	{
		// Make a name of each plugin to be saved
    PlgName = tr("%1").arg(i);

    QString value = settings.value(PlgName).toString();
    
		PluginManager::GetInstance().GetInstalledPluginsInRegVector().push_back(value);
	}

  settings.endGroup();

	return 1;
}


void RPSSeaLabSimulation::WriteMapToRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count)
{

	if (map.empty())
	{
		return;
	}

  QStringList mapkeylst;
	QStringList mapvaluelst;

  //Iterate though the map 
	for (auto it1 = map.begin(); it1 != map.end(); ++it1)
	{
		mapkeylst.append(it1->first);
		mapvaluelst.append(it1->second);
	}

    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.setValue("mapkey", mapkeylst);
    settings.setValue("mapValue", mapvaluelst);
    settings.endGroup(); 

	count ++;
}

void RPSSeaLabSimulation::ReadMapFromRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    QStringList mapkeylst = settings.value("mapkey").toStringList();
    QStringList mapvaluelst = settings.value("mapValue").toStringList();
    settings.endGroup();
 

	if (mapkeylst.isEmpty())
	{
		return;
	}

	for (int i = 0; i < mapkeylst.size(); ++i)
  {
    QString key = mapkeylst.at(i);
	QString value = mapvaluelst.at(i);
    
    map[key] = value;
	PluginManager::GetInstance().GetAllPlugedObjectsMap()[key] = value;

  }

	count++;
}

void RPSSeaLabSimulation::SeLWriteAllTobeInstallObjectsToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("SeLSimMethod"), count = 1;
	WriteMapToRegistry(CrpsSeLSimulationMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLLoc"), count = 1;
	WriteMapToRegistry(CrpsSeLLocationDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLXPSD"), count = 1;
	WriteMapToRegistry(CrpsSeLXSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLCoh"), count = 1;
	WriteMapToRegistry(CrpsSeLCoherenceFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDecomp"), count = 1;
	WriteMapToRegistry(CrpsSeLPSDdecomMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLFreq"), count = 1;
	WriteMapToRegistry(CrpsSeLFrequencyDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLRand"), count = 1;
	WriteMapToRegistry(CrpsSeLRandomnessFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLMod"), count = 1;
	WriteMapToRegistry(CrpsSeLModulationFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpec"), count = 1;
	WriteMapToRegistry(CrpsSeLDirectionalSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDirDistr"), count = 1;
	WriteMapToRegistry(CrpsSeLDirectionDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpread"), count = 1;
	WriteMapToRegistry(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectDescriptionMap(), settingsGroup, count);

    settingsGroup = ("SeLCorr"), count = 1;
	WriteMapToRegistry(CrpsSeLCorrelationFactory::GetOjectDescriptionMap(), settingsGroup, count);

}

void RPSSeaLabSimulation::SeLReadAllTobeInstallObjectsFromRegistry()
{
	int count = 1;

	QString settingsGroup;

	settingsGroup = ("SeLSimMethod"), count = 1;
	ReadMapFromRegistry(CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLLoc"), count = 1;
	ReadMapFromRegistry(CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLXPSD"), count = 1;
	ReadMapFromRegistry(CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLCoh"), count = 1;
	ReadMapFromRegistry(CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDecomp"), count = 1;
	ReadMapFromRegistry(CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLFreq"), count = 1;
	ReadMapFromRegistry(CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLRand"), count = 1;
	ReadMapFromRegistry(CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLMod"), count = 1;
	ReadMapFromRegistry(CrpsSeLModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpec"), count = 1;
	ReadMapFromRegistry(CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDirDistr"), count = 1;
	ReadMapFromRegistry(CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLDirSpread"), count = 1;
	ReadMapFromRegistry(CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SeLCorr"), count = 1;
	ReadMapFromRegistry(CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);


}

bool RPSSeaLabSimulation::IntallRegistrySeaLabPlugins()
{
	// Read the installed plugins from registry
  RPSReadInstalledPluginsFromRegistry();

	// Install each of them
	for (int i = 0; i < PluginManager::GetInstance().GetInstalledPluginsInRegVector().size(); i++)
	{
		QString PluginFromReg = PluginManager::GetInstance().GetInstalledPluginsInRegVector().at(i);
		PluginManager::GetInstance().InstallPlugin(PluginFromReg);
	}
 
	return true;
}

void RPSSeaLabSimulation::SeLClearAllTobeInstallObjectsFromRegistry()
{
	QString settingsGroup;

	settingsGroup = ("SeLSimMethod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLLoc");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLXPSD");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLCoh");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDecomp");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLFreq");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLRand");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLMod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDirSpec");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDirDistr");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SeLDirSpread");
	ClearMapFromRegistry(settingsGroup);

}

void RPSSeaLabSimulation::ClearMapFromRegistry(QString& settingsGroup)
{
	
    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.remove(""); //removes the group, and all it keys
    settings.endGroup(); 
}