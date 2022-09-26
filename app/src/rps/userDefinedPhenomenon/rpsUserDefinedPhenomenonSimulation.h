#ifndef RPSUDERDEFINEDPHENOMENONSIMULATION_H
#define RPSUDERDEFINEDPHENOMENONSIMULATION_H

#include <QWidget>
#include <QComboBox>
#include <QThread>
#include <QTimer>

#include "RPSUserDefinedPhenomenonSimuData.h"
#include "rpsUserDefinedPhenomenonSimulationWorker.h"
#include "rpsUserDefinedPhenomenonSimulationOutputWorker.h"

class XmlStreamWriter;
class XmlStreamReader;

class RPSUserDefinedPhenomenonSimulation : public QWidget
{
  Q_OBJECT

public:
  RPSUserDefinedPhenomenonSimulation(QWidget *parent = nullptr);
  ~RPSUserDefinedPhenomenonSimulation();
  void save(XmlStreamWriter *xmlwriter);
  bool load(XmlStreamReader *xmlreader);
  void saveUserDefinedPhenomenonSimulationData(XmlStreamWriter *xmlwriter);
  bool loadUserDefinedPhenomenonSimulationData(XmlStreamReader *xmlreader);

signals:
  void sendInformation(QStringList infoList);
  void progressBarShow();
  void progressBarHide();
  void progressBarSetValue(int);
  void progressBarSetMin(int);
  void progressBarSetMax(int);
  void progressBarReset();
  void stopped();

public slots:

  // input
  void userDefinedPhenomenon();
 
  // output
  void userDefinedPhenomenonOutput();
  

  // simulation
  void runSimulation();
  void pauseSimulation();
  void stopSimulation();
  void simulationOptions();

  void receiveInformation(QStringList infoList);
  void progressBarShowSL();
  void progressBarHideSL();
  void progressBarSetValueSL(int value);
  void progressBarSetMinSL(int value);
  void progressBarSetMaxSL(int value);
  void progressBarResetSL();

  // display output
  void displayUserDefinedPhenomenon();

private:
  // wind velocity simulation input data
  CRPSUserDefinedPhenomenonSimuData simuData;

  QThread *simulationThread = nullptr;
  RPSUserDefinedPhenomenonSimulationWorker *simulationWorker = nullptr;
  QTimer *simulationTimer = nullptr;

  QThread *simulationOutputThread = nullptr;
  RPSUserDefinedPhenomenonSimulationOutputWorker *simulationOutputWorker = nullptr;
  
  mat m_resultMatrix;

public:
  QStringList information;
  int phenomenonIndex;
  int indexSetIndex;

public:
  CRPSUserDefinedPhenomenonSimuData &GetUserDefinedPhenomenonSimulationData();
  RPSUserDefinedPhenomenonSimulationOutputWorker *GetUserDefinedPhenomenonSimulationOutputWorker();
  RPSUserDefinedPhenomenonSimulationWorker *GetUserDefinedPhenomenonSimulationWorker();

  void simuDataInitialize();

  QStringList FindAllSimulationMethods();
 
  void simulationMethodInital(QString currentSelected);

  void createOutputWorker();
  void createSimulationWorker();
 

  void fillLocationJComboBox(QComboBox *locationJComboBox);
  void fillTimeComboBox(QComboBox *timeComboBox);
  void locJCurrentIndexChanged(int index);
  void timCurrentIndexChanged(int index);
};

#endif // RPSUDERDEFINEDPHENOMENONSIMULATION_H
