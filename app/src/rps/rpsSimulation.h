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
  void simulate();

  public slots:
  void runSimulation();
  void pauseSimulation();
  void stopSimulation();
  void simulationOptions();
  void rpsPlugins();
  void compareAccuracy();
  void compareComputationTime();
  void compareMemoryUsage();
  void receiveString(QString string);
  void fillLocationJComboBox();
  void fillLocationKComboBox();
  void fillFrequencyComboBox();
  void fillTimeComboBox();
  void locJCurrentIndexChanged(int index);
  void locKCurrentIndexChanged(int index);
  void freqCurrentIndexChanged(int index);
  void timCurrentIndexChanged(int index);
  void wavCurrentIndexChanged(int index);


};

#endif // RPSSIMULATION_H