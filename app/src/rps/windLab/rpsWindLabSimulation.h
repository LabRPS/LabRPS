#ifndef RPSWINDLABSIMULATION_H
#define RPSWINDLABSIMULATION_H

#include <QWidget>
#include <QComboBox>
#include <QThread>
#include <QTimer>

#include "RPSWindLabsimuData.h"
#include "rpsWindLabSimulationWorker.h"
#include "rpsWindLabSimulationOutputWorker.h"

class XmlStreamWriter;
class XmlStreamReader;

class RPSWindLabSimulation : public QWidget
{
  Q_OBJECT

public:
  RPSWindLabSimulation(QWidget *parent = nullptr);
  ~RPSWindLabSimulation();
  void save(XmlStreamWriter *xmlwriter);
  bool load(XmlStreamReader *xmlreader);
  void saveWindLabData(XmlStreamWriter *xmlwriter);
  bool loadWindLabData(XmlStreamReader *xmlreader);

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
  void windVelocity();
  void spectrumWind();
  void coherenceWind();
  void correlationWind();
  void modulationWind();
  void meanWindVelocity();

  // output
  void windVelocityOutput();
  void frequencyDistributionOutput();
  void locationDistributionOutput();
  void spectrumWindOutput();
  void decomposedSpectrumWindOutput();
  void coherenceWindOutput();
  void correlationWindOutput();
  void modulationWindOutput();
  void meanWindVelocityOutput();
  void randomPhaseWindOutput();

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
  void displayWindVelocity();
  void displayFrequencyDistribution();
  void displayLocationDistribution();
  void displaySpectrum();
  void displayXSpectrum();
  void displayYSpectrum();
  void displayZSpectrum();
  void displayDecomposedSpectrum();;
  void displayCoherenceWind();
  void displayCorrelationWind();
  void displayModulationWind();
  void displayMeanWindVelocity();
  void displayRandomPhase();


private:
  // wind velocity simulation input data
  CRPSWindLabsimuData windLabData;

  QThread *simulationThread = nullptr;
  RPSWindLabSimulationWorker *simulationWorker = nullptr;
  QTimer *simulationTimer = nullptr;

  QThread *simulationOutputThread = nullptr;
  RPSWindLabSimulationOutputWorker *simulationOutputWorker = nullptr;

  mat m_resultMatrix;

public:
  QStringList information;
  int locationJ;
  int locationK;
  int frequencyIndex;
  int timeIndex;
  // comparison
  bool mcompareComputationTime;
  bool mcompareMemoryUsage;
  QString comparisonCategory;
  QString comparisonFunction;
  QString comparisonCandidate;
  int minNumberOfLocation;
  int minNumberOfFrequency;
  int minNumberOfTime;
  int numberOfLocationIncrement;
  int numberOfFrequencyIncrement;
  int numberOfTimeIncrement;
  int totalNumber;
  int resultOutputTime;

  QString psdPrefix;

  QStringList categories;
  QStringList functions;
  std::map<QString, QStringList> categoryFunctionListMap;
  std::vector<QString> candidateList;
  int numberOfCandidate;

public:
  CRPSWindLabsimuData &GetWindLabData();
  RPSWindLabSimulationOutputWorker *GetWindLabSimulationOutputWorker();
  RPSWindLabSimulationWorker *GetWindLabSimulationWorker();

  void windLabDataInitialize();
  void WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count);
  void ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count);

  //*******save installed plungins for windLab (start)********//
  void WLWriteAllTobeInstallObjectsToRegistry();
  void WLReadAllTobeInstallObjectsFromRegistry();
  void WLClearAllTobeInstallObjectsFromRegistry();
  void ClearMapFromRegistry(QString &settingsGroupt);

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

  void compareAccuracy();
  void compareComputationTime();
  void compareMemoryUsage();
  void comparisonInitial();
  QStringList FindAllCoherenceFunction();
  QStringList FindAllCorrelationFunctions();
  QStringList FindAllFrequencyDistributions();
  QStringList FindAllMeanWindProfils();
  QStringList FindAllModulationFunctions();
  QStringList FindAllPSDDecompositionMethods();
  QStringList FindAllSimulationMethods();
  QStringList FindAllSpectrumModels();
  void fillCategoryComboBox(QComboBox *categoryComboBox);
  void fillFunctionAndCandidateComboBoxes(QString category, QComboBox *functionComboBox, QComboBox *candidatesComboBox);

  void CoherenceFunctionInital(QString currentSelected);
  void correlationFunctionInital(QString currentSelected);
  void frequencyDistributionInital(QString currentSelected);
  void meanWindProfilInital(QString currentSelected);
  void modulationFunctionInital(QString currentSelected);
  void psdDecompositionMethodInital(QString currentSelected);
  void simulationMethodInital(QString currentSelected);
  void spectrumModelInital(QString currentSelected);
  void randomnessProviderInital(QString currentSelected);
  void candidateInitialData(QString category, QString currentSelected);

  void createOutputWorker();
  void createSimulationWorker();


  void fillLocationJComboBox(QComboBox *locationJComboBox);
  void fillLocationKComboBox(QComboBox *locationKComboBox);
  void fillFrequencyComboBox(QComboBox *frequencyComboBox);
  void fillTimeComboBox(QComboBox *timeComboBox);
  void locJCurrentIndexChanged(int index);
  void locKCurrentIndexChanged(int index);
  void freqCurrentIndexChanged(int index);
  void timCurrentIndexChanged(int index);
};

#endif // RPSWINDLABSIMULATION_H