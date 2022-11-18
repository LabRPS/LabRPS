#ifndef RPSSIMULATION_H
#define RPSSIMULATION_H

#include <QWidget>
#include "Table.h"
#include "Matrix.h"
#include "rps/seaLab/rpsSeaLabSimulation.h"
#include "rps/seismicLab/rpsSeismicLabSimulation.h"
#include "rps/windLab/rpsWindLabSimulation.h"
#include "rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulation.h"

class MyWidget;

class RPSSimulation : public QWidget
{
  Q_OBJECT

public:
  RPSSimulation(QWidget *parent = nullptr);
  ~RPSSimulation();

private:
  QString selectedRandomPhenomenon;

public:
  QStringList supportedRandomPhenomena;

  RPSSeaLabSimulation *rpsSeaLabSimulator;
  RPSSeismicLabSimulation *rpsSeismicLabSimulator;
  RPSWindLabSimulation *rpsWindLabSimulator;
  RPSUserDefinedPhenomenonSimulation *rpsUserDefinedPhenomenonSimulator;

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
  void WLWriteAllTobeInstalledPluginsToRegistry();
  void WLReadAllTobeInstalledPluginsFromRegistry(const QStringList &pluginList);
  void simulate();
  void convertTableToEigenMatrix(Table* table, mat &eigenMatrix);
  void convertMatrixToEigenMatrix(Matrix* matrix, mat &eigenMatrix);
  void emptyAllToBeUninstalledObjectsMap();

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
  void phenomenonCurrentIndexChanged(int index);
  void indexSetCurrentIndexChanged(int index);
  void fillPhenomenonComboBox();
  void fillIndexSetComboBox();
  void runTool();

  signals:
  void pluginModified(MyWidget *widget);


};

#endif // RPSSIMULATION_H
