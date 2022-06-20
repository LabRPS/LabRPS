#include "rpsSimulation.h"
#include "rps/pluginBrower/RPSPluginsBrowser.h"
#include "rps/RPSpluginManager.h"
#include "rps/pluginBrower/plugininstallerbrowser.h"

#include "ApplicationWindow.h"
#include <QString>
#include <QMessageBox>
#include <QSettings>

RPSSimulation::RPSSimulation(QWidget *parent) : QWidget(parent)
{
  QSettings settings;

  selectedRandomPhenomenon = settings.value("rpsPhenomenon", false).toString();

  if (selectedRandomPhenomenon.isEmpty())
  {
    selectedRandomPhenomenon = "Sea Surface";
  }

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator = new RPSWindLabSimulation(this);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator = new RPSSeismicLabSimulation(this);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator = new RPSSeaLabSimulation(this);
  }

  IntallRegistryPlugins();
}

RPSSimulation::~RPSSimulation()
{
  RPSWriteInstalledPluginsToRegistry();
}

QString RPSSimulation::getSelectedRandomPhenomenon()
{
  return selectedRandomPhenomenon;
}

bool RPSSimulation::GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName)
{

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    return rpsWindLabSimulator->GetToBeInstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    return rpsSeismicLabSimulator->GetToBeInstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    return rpsSeaLabSimulator->GetToBeInstalledObjectsList(lstObject, pluginName);
  }

  return false;
}

bool RPSSimulation::GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName)
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    return rpsWindLabSimulator->GetToBeUninstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    return rpsSeismicLabSimulator->GetToBeUninstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    return rpsSeaLabSimulator->GetToBeUninstalledObjectsList(lstObject, pluginName);
  }

  return false;
}

bool RPSSimulation::IsObjectInstalled(QString &object)
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    return rpsWindLabSimulator->IsObjectInstalled(object);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    return rpsSeismicLabSimulator->IsObjectInstalled(object);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    return rpsSeaLabSimulator->IsObjectInstalled(object);
  }

  return false;
}

bool RPSSimulation::UpdateToBeInstalledObjectsMap(const QString &lstObject)
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    return rpsWindLabSimulator->UpdateToBeInstalledObjectsMap(lstObject);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    return rpsSeismicLabSimulator->UpdateToBeInstalledObjectsMap(lstObject);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    return rpsSeaLabSimulator->UpdateToBeInstalledObjectsMap(lstObject);
  }

  return false;
}

bool RPSSimulation::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    return rpsWindLabSimulator->UpdateToBeUninstalledObjectsMap(name, pluginName);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    return rpsSeismicLabSimulator->UpdateToBeUninstalledObjectsMap(name, pluginName);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    return rpsSeaLabSimulator->UpdateToBeUninstalledObjectsMap(name, pluginName);
  }

  return false;
}

int RPSSimulation::RPSWriteInstalledPluginsToRegistry()
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

bool RPSSimulation::IntallRegistryPlugins()
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

int RPSSimulation::RPSReadInstalledPluginsFromRegistry()
{
  RPSReadInstalledPluginsFromRegistryCommon();

  return 1;
}

int RPSSimulation::RPSReadInstalledPluginsFromRegistryCommon()
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

void RPSSimulation::runSimulation()
{
  
  // RPSSimulationThread *simThread = new RPSSimulationThread(this);
  // //QObject::connect(simThread, SIGNAL(finished()), simThread, SLOT(deleteLater()));
  // QObject::connect(simThread, SIGNAL(sendString(QString)), this, SLOT(receiveString(QString)), Qt::QueuedConnection);
  // simThread->start();

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator->runSimulation();
  }

}
void RPSSimulation::pauseSimulation()
{
    if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->pauseSimulation();
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator->pauseSimulation();
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator->pauseSimulation();
  }
}

void RPSSimulation::stopSimulation()
{
}

void RPSSimulation::simulationOptions()
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->simulationOptions();
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator->simulationOptions();
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator->simulationOptions();
  }
}
 void RPSSimulation::simulate()
 {

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator->runSimulation();
  }

 }

void RPSSimulation::rpsPlugins()
{
  std::unique_ptr<PluginInstallerBrowser> dlg(new PluginInstallerBrowser(this));
  dlg->exec();
}

void RPSSimulation::compareAccuracy()
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->compareAccuracy();
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator->compareAccuracy();
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator->compareAccuracy();
  }
}

void RPSSimulation::compareComputationTime()
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->compareComputationTime();
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator->compareComputationTime();
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator->compareComputationTime();
  }
}

void RPSSimulation::compareMemoryUsage()
{
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->compareMemoryUsage();
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    rpsSeismicLabSimulator->compareMemoryUsage();
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    rpsSeaLabSimulator->compareMemoryUsage();
  }
}

void RPSSimulation::receiveString(QString string)
{
  ApplicationWindow *app = (ApplicationWindow *)this->parent();
  app->logInfo = (string);
	app->showResults(true);

  QMessageBox::warning(0, "from thread", string);

}

void RPSSimulation::fillLocationJComboBox()
{
    ApplicationWindow *app = (ApplicationWindow *)this->parent();
  
  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->fillLocationJComboBox(app->getComboxboxLocJstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->fillLocationJComboBox(app->getComboxboxLocJstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->fillLocationJComboBox(app->getComboxboxLocJstatusbarbtn());
  }
}
void RPSSimulation::fillLocationKComboBox()
{
   ApplicationWindow *app = (ApplicationWindow *)this->parent();

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->fillLocationKComboBox(app->getComboxboxLocKstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->fillLocationKComboBox(app->getComboxboxLocKstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->fillLocationKComboBox(app->getComboxboxLocKstatusbarbtn());
  }
}
void RPSSimulation::fillFrequencyComboBox()
{
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

	if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->fillFrequencyComboBox(app->getComboxboxFreqstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->fillFrequencyComboBox(app->getComboxboxFreqstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->fillFrequencyComboBox(app->getComboxboxFreqstatusbarbtn());
  }
}
void RPSSimulation::fillTimeComboBox()
{
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->fillTimeComboBox(app->getComboxboxTimstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->fillTimeComboBox(app->getComboxboxTimstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->fillTimeComboBox(app->getComboxboxTimstatusbarbtn());
  }
}

  void RPSSimulation::locJCurrentIndexChanged(int index)
  {

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->locJCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->locJCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->locJCurrentIndexChanged(index);
  }
  }
  void RPSSimulation::locKCurrentIndexChanged(int index)
  {

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->locKCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->locKCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->locKCurrentIndexChanged(index);
  }
  }
  void RPSSimulation::freqCurrentIndexChanged(int index)
  {

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->freqCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->freqCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->freqCurrentIndexChanged(index);
  }
  }
  void RPSSimulation::timCurrentIndexChanged(int index)
  {

  if (selectedRandomPhenomenon == "Wind Velocity")
  {
    rpsWindLabSimulator->timCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Seismic Ground motion")
  {
    // rpsSeismicLabSimulator->timCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == "Sea Surface")
  {
    // rpsSeaLabSimulator->timCurrentIndexChanged(index);
  }
  }