#ifndef RPSUDERDEFINEDPHENOMENONSIMULATION_H
#define RPSUDERDEFINEDPHENOMENONSIMULATION_H

#include <QWidget>
#include <QComboBox>
#include <QThread>
#include <QTimer>

#include "RPSUserDefinedPhenomenonSimuData.h"
#include "rpsUserDefinedPhenomenonSimulationWorker.h"
#include "rpsUserDefinedPhenomenonSimulationOutputWorker.h"
#include "rpsUserDefinedPhenomenonComparisonWorker.h"

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

  // display comparison results
  void displayAccuracyComparisonResults();
  void displayTimeComparisonResults();
  void displayMemoryComparisonResults();


  void displayAComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);
  void displayTComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);

  void displayUserDefinedPhenomenonSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);
  void displayUserDefinedPhenomenonLargeScaleSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);


private:
  // wind velocity simulation input data
  CRPSUserDefinedPhenomenonSimuData simuData;

  QThread *simulationThread = nullptr;
  RPSUserDefinedPhenomenonSimulationWorker *simulationWorker = nullptr;
  QTimer *simulationTimer = nullptr;

  QThread *simulationOutputThread = nullptr;
  RPSUserDefinedPhenomenonSimulationOutputWorker *simulationOutputWorker = nullptr;
  
  QThread *comparisonThread = nullptr;
  RPSUserDefinedPhenomenonComparisonWorker *comparisonWorker = nullptr;

  mat m_resultMatrix;

public:
  QStringList information;
  int phenomenonIndex;
  int indexSetIndex;

  // comparison
  bool mcompareComputationTime;
  bool mcompareMemoryUsage;
  QString comparisonCategory;
  QString comparisonFunction;
  QString comparisonCandidate;
  int minNumberOfProcess;
  int minNumberOfIndexSetIndex;
  int minNumberOfSample;
  int numberOfProcessIncrement;
  int numberOfIndexSetIndexIncrement;
  int numberOfSampleIncrement;
  int totalNumber;
  int resultOutputType;

  QStringList categories;
  QStringList functions;
  std::map<QString, QStringList> categoryFunctionListMap;
  std::vector<QString> candidateList;
  int numberOfCandidate;

   std::vector<int> m_resultVectorVariable;
   std::vector<int> m_resultVectorCandidate1;
   std::vector<int> m_resultVectorCandidate2;

   QString _userDefinedPhenomenon;


public:
  CRPSUserDefinedPhenomenonSimuData &GetUserDefinedPhenomenonSimulationData();
  RPSUserDefinedPhenomenonSimulationOutputWorker *GetUserDefinedPhenomenonSimulationOutputWorker();
  RPSUserDefinedPhenomenonSimulationWorker *GetUserDefinedPhenomenonSimulationWorker();
  RPSUserDefinedPhenomenonComparisonWorker *GetUserDefinedPhenomenonComparisonWorker();

  void simuDataInitialize();
  void WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count);
  void ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count);
  void WriteMapToRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count);
  void ReadMapFromRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count);

  void UDPWriteAllTobeInstallObjectsToRegistry();
  void UDPReadAllTobeInstallObjectsFromRegistry();

void UDPWriteAllTobeInstallObjPublicationTitleToRegistry();
void UDPReadAllTobeInstallObjPublicationTitleToRegistry();

void UDPWriteAllTobeInstallObjPublicationLinkToRegistry();
void UDPReadAllTobeInstallObjPublicationLinkToRegistry();

void UDPWriteAllTobeInstallObjPublicationAuthorToRegistry();
void UDPReadAllTobeInstallObjPublicationAuthorToRegistry();

void UDPWriteAllTobeInstallObjPublicationDateToRegistry();
void UDPReadAllTobeInstallObjPublicationDateToRegistry();

void UDPWriteAllTobeInstallObjVersionToRegistry();
void UDPReadAllTobeInstallObjVersionToRegistry();

void UDPClearAllTobeInstallObjectsFromRegistry();
void ClearMapFromRegistry(QString &settingsGroupt);


  void compareAccuracy();
  void compareComputationTime();
  void compareMemoryUsage();

  void comparisonInitial();
  QStringList FindAllSimulationMethods();

  void fillCategoryComboBox(QComboBox *categoryComboBox);
  void fillFunctionAndCandidateComboBoxes(QString category, QComboBox *functionComboBox, QComboBox *candidatesComboBox);
  void simulationMethodInital(QString currentSelected);
  void candidateInitialData(QString category, QString currentSelected);

  void createOutputWorker();
  void createSimulationWorker();
  void createComparisonWorker();

  void fillLocationJComboBox(QComboBox *locationJComboBox);
  void fillTimeComboBox(QComboBox *timeComboBox);
  void locJCurrentIndexChanged(int index);
  void timCurrentIndexChanged(int index);
  void phenomenonCurrentIndexChanged(int index);
  void indexSetCurrentIndexChanged(int index);
  void fillPhenomenonComboBox(QComboBox *phenomenonComboBox);
  void fillIndexSetComboBox(QComboBox *indexSetComboBox);

//*******save installed plungins for windLab (end)********//
  bool GetObjects(std::map<const QString, QString> &map, QStringList &lstObject, QString pluginName);
  bool GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName);
  bool GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName);
  bool IsObjectInstalled(QString &object);
  bool UpdateObjectsMap(std::map<const QString, QString> &map, const QString &lstObject);
  bool UpdateToBeInstalledObjectsMap(const QString &lstObject);
  bool UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName);
  bool IsThisObjectInstalled(std::map<const QString, QString> &map, QString &object);
  bool UpdateObjectToSkipMap(std::map<const QString, QString> &map, const QString name, const QString pluginName);
  void saveLineEditIndexes();

};

#endif // RPSUDERDEFINEDPHENOMENONSIMULATION_H
