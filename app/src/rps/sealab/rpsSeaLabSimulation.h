#ifndef RPSSEALABSIMULATION_H
#define RPSSEALABSIMULATION_H

#include <QWidget>
#include "RPSSeaLabsimuData.h"

class RPSSeaLabSimulation : public QWidget
{
  Q_OBJECT
 
 public:

  RPSSeaLabSimulation(QWidget *parent = nullptr);
  ~RPSSeaLabSimulation();

 public slots:

   // input
  void seaSurface();
  void spectrumSea();
  void coherenceSea();
  void correlationSea();
  void modulationSea();

  //output
  void seaSurfaceOutput();
  void frequencyDistributionOutput();
  void locationDistributionOutput();
  void spectrumSeaOutput();
  void coherenceSeaOutput();
  void correlationSeaOutput();
  void modulationSeaOutput();

  //simulation
  void runSimulation();
  void pauseSimulation();
  void stopSimulation();
  void simulationOptions();

  public:

  // sea surface simulation input data
  CRPSSeaLabsimuData seaLabData;
  QStringList information;

  public:

  CRPSSeaLabsimuData& GetSeaLabData();
  void seaLabDataInitialize();
  void WriteMapToRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);
  void ReadMapFromRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);


  //*******save installed plungins for seaLab (start)********//
  void SeLWriteAllTobeInstallObjectsToRegistry();
  void SeLReadAllTobeInstallObjectsFromRegistry();
  void SeLClearAllTobeInstallObjectsFromRegistry();
  void ClearMapFromRegistry(QString& settingsGroupt);

  //*******save installed plungins for seaLab (end)********//
bool GetObjects(std::map<const QString, QString>& map, QStringList& lstObject, QString pluginName);
bool GetToBeInstalledObjectsList(QStringList& lstObject, QString pluginName);
bool GetToBeUninstalledObjectsList(QStringList& lstObject, QString pluginName);
bool IsObjectInstalled(QString& object);
bool UpdateObjectsMap(std::map<const QString, QString>& map, const QString& lstObject);
bool UpdateToBeInstalledObjectsMap(const QString& lstObject);
bool UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName);
bool IsThisObjectInstalled(std::map<const QString, QString>& map, QString& object);
bool UpdateObjectToSkipMap(std::map<const QString, QString>& map, const QString name, const QString pluginName);

  void compareAccuracy();
  void compareComputationTime();
  void compareMemoryUsage();
};

#endif  // RPSSEALABSIMULATION_H