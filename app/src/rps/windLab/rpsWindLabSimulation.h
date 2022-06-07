#ifndef RPSWINDLABSIMULATION_H
#define RPSWINDLABSIMULATION_H

#include <QWidget>
#include "RPSWindLabsimuData.h"

class RPSWindLabSimulation : public QWidget
{
  Q_OBJECT
 
 public:

  RPSWindLabSimulation(QWidget *parent = nullptr);
  ~RPSWindLabSimulation();

 public slots:

   // input
  void windVelocity();
  void spectrumWind();
  void coherenceWind();
  void correlationWind();
  void modulationWind();
  void meanWindVelocity();

  //output
  void windVelocityOutput();
  void spectrumWindOutput();
  void coherenceWindOutput();
  void correlationWindOutput();
  void modulationWindOutput();
  void meanWindVelocityOutput();

    //simulation
  void runSimulation();
  void pauseSimulation();
  void stopSimulation();
  void simulationOptions();

  public:

  // wind velocity simulation input data
  CRPSWindLabsimuData windLabData;
  QStringList information;
  
  public:

  CRPSWindLabsimuData& GetWindLabData();
  void windLabDataInitialize();
  void WriteMapToRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);
  void ReadMapFromRegistry(std::map<const QString, QString> & map, QString& settingsGroup, int& count);


  //*******save installed plungins for windLab (start)********//
  void WLWriteAllTobeInstallObjectsToRegistry();
  void WLReadAllTobeInstallObjectsFromRegistry();
  void WLClearAllTobeInstallObjectsFromRegistry();
  void ClearMapFromRegistry(QString& settingsGroupt);

  //*******save installed plungins for windLab (end)********//
bool GetObjects(std::map<const QString, QString>& map, QStringList& lstObject, QString pluginName);
bool GetToBeInstalledObjectsList(QStringList& lstObject, QString pluginName);
bool GetToBeUninstalledObjectsList(QStringList& lstObject, QString pluginName);
bool IsObjectInstalled(QString& object);
bool UpdateObjectsMap(std::map<const QString, QString>& map, const QString& lstObject);
bool UpdateToBeInstalledObjectsMap(const QString& lstObject);
bool UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName);
bool IsThisObjectInstalled(std::map<const QString, QString>& map, QString& object);
bool UpdateObjectToSkipMap(std::map<const QString, QString>& map, const QString name, const QString pluginName);

 

 
};

#endif  // RPSWINDLABSIMULATION_H