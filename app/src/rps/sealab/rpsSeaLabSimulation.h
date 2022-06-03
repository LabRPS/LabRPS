#ifndef RPSSEALABSIMULATION_H
#define RPSSEALABSIMULATION_H

#include <QWidget>
#include "rps/rpsSimulation.h"

class RPSSeaLabSimulation : public QWidget
{
  Q_OBJECT
 
 public:

  RPSSeaLabSimulation(QWidget *parent = nullptr);
  ~RPSSeaLabSimulation();

 private:
 

 public:


 public slots:
   
  void runSimulation();
  void pauseSimulation();
  void stopSimulation();
  void simulationOptions();

   //seaLab
  void seaSurface();
  void spectrumSea();
  void coherenceSea();
  void correlationSea();
  void modulationSea();

  //Simulation
  private:

  // random phenomenon name
  QString selectedRandomPhenomenon;
  QStringList supportedRandomPhenomena = QStringList()
                     <<tr("Wind Velocity") << tr("Seismic Ground motion") << tr("Sea Surface");
  
  public:
   QStringList information;

  // sea surface simulation input data
  CRPSSeaLabsimuData seaLabData;

  public:

  CRPSSeaLabsimuData& GetSeaLabData();
  void seaLabDataInitialize();
  void WriteMapToRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);
  void ReadMapFromRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);
  bool IntallRegistrySeaLabPlugins();
  int RPSWriteToBeInstallObjectsToRegistry();
  int RPSWriteInstalledPluginsToRegistry();
  int RPSReadInstalledPluginsFromRegistry();
  int RPSReadInstalledPluginsFromRegistryCommon();

  //*******save installed plungins for seaLab (start)********//
  void SeLWriteAllTobeInstallObjectsToRegistry();
  void SeLReadAllTobeInstallObjectsFromRegistry();
  void SeLClearAllTobeInstallObjectsFromRegistry();
  void ClearMapFromRegistry(QString& settingsGroupt);

  //*******save installed plungins for seaLab (end)********//
 
};

#endif  // RPSSEALABSIMULATION_H