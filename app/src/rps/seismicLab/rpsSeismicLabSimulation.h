#ifndef RPSSEISMICLABSIMULATION_H
#define RPSSEISMICLABSIMULATION_H

#include <QWidget>
#include "RPSSeismicLabsimuData.h"

class RPSSeismicLabSimulation : public QWidget
{
  Q_OBJECT
 
 public:

  RPSSeismicLabSimulation(QWidget *parent = nullptr);
  ~RPSSeismicLabSimulation();

 public slots:

   // input
  void groundMotion();
  void spectrumSeismic();
  void coherenceSeismic();
  void correlationSeismic();
  void modulationSeismic();

  //output
  void groundMotionOutput();
  void frequencyDistributionOutput();
  void locationDistributionOutput();
  void spectrumSeismicOutput();
  void coherenceSeismicOutput();
  void correlationSeismicOutput();
  void modulationSeismicOutput();

    //simulation
  void runSimulation();
  void pauseSimulation();
  void stopSimulation();
  void simulationOptions();

  public:

  // groun motion simulation input data
  CRPSSeismicLabsimuData seimicLabData;
  QStringList information;

  public:

  CRPSSeismicLabsimuData& GetSeismicLabData();
  void seismicLabDataInitialize();
  void WriteMapToRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);
  void ReadMapFromRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);


  //*******save installed plungins for seismicLab (start)********//
  void SLWriteAllTobeInstallObjectsToRegistry();
  void SLReadAllTobeInstallObjectsFromRegistry();
  void SLClearAllTobeInstallObjectsFromRegistry();
  void ClearMapFromRegistry(QString& settingsGroupt);

  //*******save installed plungins for seismicLab (end)********//
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

#endif  // RPSSEISMICLABSIMULATION_H