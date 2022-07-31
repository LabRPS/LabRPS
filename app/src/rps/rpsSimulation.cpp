#include "rpsSimulation.h"
#include "rps/pluginBrower/RPSPluginsBrowser.h"
#include "rps/RPSpluginManager.h"
#include "rps/pluginBrower/plugininstallerbrowser.h"
#include "ApplicationWindow.h"
#include "globals.h"

#include <QString>
#include <QMessageBox>
#include <QSettings>

RPSSimulation::RPSSimulation(QWidget *parent) : QWidget(parent)
{
  supportedRandomPhenomena.append(LabRPS::rpsPhenomenonWindVelocity);
  supportedRandomPhenomena.append(LabRPS::rpsPhenomenonSeismicGroundMotion);
  supportedRandomPhenomena.append(LabRPS::rpsPhenomenonSeaSurface);

  QSettings settings;

  selectedRandomPhenomenon = settings.value("rpsPhenomenon", LabRPS::rpsPhenomenonWindVelocity).toString();

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator = new RPSWindLabSimulation(this);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator = new RPSSeismicLabSimulation(this);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
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

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    return rpsWindLabSimulator->GetToBeInstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    return rpsSeismicLabSimulator->GetToBeInstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    return rpsSeaLabSimulator->GetToBeInstalledObjectsList(lstObject, pluginName);
  }

  return false;
}

bool RPSSimulation::GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName)
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    return rpsWindLabSimulator->GetToBeUninstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    return rpsSeismicLabSimulator->GetToBeUninstalledObjectsList(lstObject, pluginName);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    return rpsSeaLabSimulator->GetToBeUninstalledObjectsList(lstObject, pluginName);
  }

  return false;
}

bool RPSSimulation::IsObjectInstalled(QString &object)
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    return rpsWindLabSimulator->IsObjectInstalled(object);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    return rpsSeismicLabSimulator->IsObjectInstalled(object);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    return rpsSeaLabSimulator->IsObjectInstalled(object);
  }

  return false;
}

bool RPSSimulation::UpdateToBeInstalledObjectsMap(const QString &lstObject)
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    return rpsWindLabSimulator->UpdateToBeInstalledObjectsMap(lstObject);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    return rpsSeismicLabSimulator->UpdateToBeInstalledObjectsMap(lstObject);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    return rpsSeaLabSimulator->UpdateToBeInstalledObjectsMap(lstObject);
  }

  return false;
}

bool RPSSimulation::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    return rpsWindLabSimulator->UpdateToBeUninstalledObjectsMap(name, pluginName);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    return rpsSeismicLabSimulator->UpdateToBeUninstalledObjectsMap(name, pluginName);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
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
    Descript = it->second->GetPluginSubFolder(); // second veut dire "b", first sera "a" map<a,b>

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
    
    //PluginManager::GetInstance().InitializePlugin(PluginFromReg);
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

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    rpsSeaLabSimulator->runSimulation();
  }
}
void RPSSimulation::pauseSimulation()
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->pauseSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->pauseSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    rpsSeaLabSimulator->pauseSimulation();
  }
}

void RPSSimulation::stopSimulation()
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->stopSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->stopSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    rpsSeaLabSimulator->stopSimulation();
  }
}

void RPSSimulation::simulationOptions()
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->simulationOptions();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->simulationOptions();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    rpsSeaLabSimulator->simulationOptions();
  }
}
void RPSSimulation::simulate()
{

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->runSimulation();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    rpsSeaLabSimulator->runSimulation();
  }
}

void RPSSimulation::rpsPlugins()
{
  std::unique_ptr<PluginInstallerBrowser> dlg(new PluginInstallerBrowser(this));
  dlg->exec();
  emit pluginModified(nullptr);
}

void RPSSimulation::compareAccuracy()
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->compareAccuracy();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->compareAccuracy();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    rpsSeaLabSimulator->compareAccuracy();
  }
}

void RPSSimulation::compareComputationTime()
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->compareComputationTime();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->compareComputationTime();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    rpsSeaLabSimulator->compareComputationTime();
  }
}

void RPSSimulation::compareMemoryUsage()
{
  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->compareMemoryUsage();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    rpsSeismicLabSimulator->compareMemoryUsage();
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
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

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->fillLocationJComboBox(app->getComboxboxLocJstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->fillLocationJComboBox(app->getComboxboxLocJstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->fillLocationJComboBox(app->getComboxboxLocJstatusbarbtn());
  }
}
void RPSSimulation::fillLocationKComboBox()
{
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->fillLocationKComboBox(app->getComboxboxLocKstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->fillLocationKComboBox(app->getComboxboxLocKstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->fillLocationKComboBox(app->getComboxboxLocKstatusbarbtn());
  }
}
void RPSSimulation::fillFrequencyComboBox()
{
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->fillFrequencyComboBox(app->getComboxboxFreqstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->fillFrequencyComboBox(app->getComboxboxFreqstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->fillFrequencyComboBox(app->getComboxboxFreqstatusbarbtn());
  }
}
void RPSSimulation::fillTimeComboBox()
{
  ApplicationWindow *app = (ApplicationWindow *)this->parent();

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->fillTimeComboBox(app->getComboxboxTimstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->fillTimeComboBox(app->getComboxboxTimstatusbarbtn());
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->fillTimeComboBox(app->getComboxboxTimstatusbarbtn());
  }
}

void RPSSimulation::locJCurrentIndexChanged(int index)
{

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->locJCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->locJCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->locJCurrentIndexChanged(index);
  }
}
void RPSSimulation::locKCurrentIndexChanged(int index)
{

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->locKCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->locKCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->locKCurrentIndexChanged(index);
  }
}
void RPSSimulation::freqCurrentIndexChanged(int index)
{

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->freqCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->freqCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->freqCurrentIndexChanged(index);
  }
}
void RPSSimulation::timCurrentIndexChanged(int index)
{

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
    rpsWindLabSimulator->timCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
    // rpsSeismicLabSimulator->timCurrentIndexChanged(index);
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->timCurrentIndexChanged(index);
  }
}

void RPSSimulation::wavCurrentIndexChanged(int index)
{

  if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
  {
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
  {
  }
  else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
  {
    // rpsSeaLabSimulator->wavCurrentIndexChanged(index);
  }
}

void RPSSimulation::WLWriteAllTobeInstalledPluginsToRegistry()
{
  // QStringList pluginList;

  // // an iterator
  // std::map<QString, PluginInstance *>::iterator it;

  // // iterate through all plugins
  // for (it = PluginManager::GetInstance().GetInstalledPluginsNameMap().begin(); it != PluginManager::GetInstance().GetInstalledPluginsNameMap().end(); ++it)
  // {
  //   pluginList.append(it->first);
  // }

  // // the setting objec and group
  // QSettings settings;
  // settings.beginGroup("AllTobeInstalledPluginsRegistry");

  // // save the plugin list
  // settings.setValue("PluginList", pluginList);

  // // end
  // settings.endGroup();
}
void RPSSimulation::WLReadAllTobeInstalledPluginsFromRegistry(const QStringList &pluginList)
{
  // // the setting objec and group
  // QSettings settings;
  // settings.beginGroup("AllTobeInstalledPluginsRegistry");

  // // read the plugin list from registry
  // pluginList = settings.value("PluginList").toStringList();

  // // end
  // settings.endGroup();
}