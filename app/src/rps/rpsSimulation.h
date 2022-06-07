#ifndef RPSSIMULATION_H
#define RPSSIMULATION_H

#include <QWidget>
#include "rps/seaLab/rpsSeaLabSimulation.h"
#include "rps/seismicLab/rpsSeismicLabSimulation.h"
#include "rps/windLab/rpsWindLabSimulation.h"

class RPSSimulation : public QWidget
{
  Q_OBJECT

public:
  RPSSimulation(QWidget *parent = nullptr);
  ~RPSSimulation();

private:
  QString selectedRandomPhenomenon;

public:
  QStringList supportedRandomPhenomena = QStringList()
                                         << tr("Wind Velocity") << tr("Seismic Ground motion") << tr("Sea Surface");

  RPSSeaLabSimulation *rpsSeaLabSimulator;
  RPSSeismicLabSimulation *rpsSeismicLabSimulator;
  RPSWindLabSimulation *rpsWindLabSimulator;

public:
  QString getSelectedRandomPhenomenon();
  bool GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName);
  bool GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName);
  bool IsObjectInstalled(QString &object);
  bool UpdateToBeInstalledObjectsMap(const QString &lstObject);
  bool UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName);
  int RPSWriteInstalledPluginsToRegistry();
  bool IntallRegistryPlugins();
  int RPSReadInstalledPluginsFromRegistry();
  int RPSReadInstalledPluginsFromRegistryCommon();

  public slots:
  void runSimulation();
  void pauseSimulation();
  void stopSimulation();
  void simulationOptions();
  
};

#endif // RPSSIMULATION_H