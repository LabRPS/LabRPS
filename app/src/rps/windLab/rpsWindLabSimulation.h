#ifndef RPSWINDLABSIMULATION_H
#define RPSWINDLABSIMULATION_H

#include <QWidget>
#include <QComboBox>
#include <QThread>
#include <QTimer>

#include "RPSWindLabsimuData.h"
#include "rpsWindLabSimulationWorker.h"
#include "rpsWindLabSimulationOutputWorker.h"
#include "rpsWindLabComparisonWorker.h"

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

    void cumulativeProbabilityDistribution();
    void gustFactor();
    void kurtosis();
    void peakFactor();
    void probabilityDensityFunction();
    void roughness();
    void shearVelocityOfFlow();
    void skewness();
    void standardDeviation();
    void turbulenceIntensity();
    void turbulenceScale();
    void variance();
    void wavePassageEffect();

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

    void cumulativeProbabilityDistributionOutput();
    void gustFactorOutput();
    void kurtosisOutput();
    void peakFactorOutput();
    void probabilityDensityFunctionOutput();
    void roughnessOutput();
    void shearVelocityOfFlowOutput();
    void skewnessOutput();
    void standardDeviationOutput();
    void turbulenceIntensityOutput();
    void turbulenceScaleOutput();
    void varianceOutput();
    void wavePassageEffectOutput();

    // simulation
    void runSimulation();
    void pauseSimulation();
    void stopSimulation();
    void simulationOptions();
    void runTableTool(const mat &table);
    void runMatrixTool(const mat &matrix);

    void receiveInformation(QStringList infoList);
    void progressBarShowSL();
    void progressBarHideSL();
    void progressBarSetValueSL(int value);
    void progressBarSetMinSL(int value);
    void progressBarSetMaxSL(int value);
    void progressBarResetSL();

    // display output
    void displayWindVelocity(bool simulationStatus);
    //  void displayFrequencyDistribution();
    //  void displayLocationDistribution();
    //  void displaySpectrum();
    //  void displayXSpectrum();
    //  void displayYSpectrum();
    //  void displayZSpectrum();
    //  void displayDecomposedSpectrum();;
    //  void displayCoherenceWind();
    //  void displayCorrelationWind();
    //  void displayModulationWind();
    //  void displayMeanWindVelocity();
    //  void displayRandomPhase();
    void displayOutputResults();
    void displayOutputVectorResults();
    void displayOutputMatrixResults();
    void displayOutputMatrix2Results();

    // display comparison results
    void displayAccuracyComparisonResults();
    void displayTimeComparisonResults();
    void displayMemoryComparisonResults();


    void displayAComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);
    void displayTComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);

    void displayWindVelocityASimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);
    void displayWindVelocityALargeScaleSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);

    void displayWindVelocityTSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);
    void displayWindVelocityTLargeScaleSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row);


private:
    // wind velocity simulation input data
    CRPSWindLabsimuData windLabData;

    QThread *simulationThread = nullptr;
    RPSWindLabSimulationWorker *simulationWorker = nullptr;
    QTimer *simulationTimer = nullptr;

    QThread *simulationOutputThread = nullptr;
    RPSWindLabSimulationOutputWorker *simulationOutputWorker = nullptr;

    QThread *comparisonThread = nullptr;
    RPSWindLabComparisonWorker *comparisonWorker = nullptr;


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
    int resultOutputType;

    QString psdPrefix;

    QStringList categories;
    QStringList functions;
    std::map<QString, QStringList> categoryFunctionListMap;
    std::vector<QString> candidateList;
    int numberOfCandidate;

    std::vector<int> m_resultVectorVariable;
    std::vector<int> m_resultVectorCandidate1;
    std::vector<int> m_resultVectorCandidate2;

    //
    QString coherence_;
    QString correlation_;
    QString frequency_;
    QString mean_;
    QString modulation_;
    QString decomposition_;
    QString simulation_;
    QString spatial_;
    QString randomness_;
    QString spectrum_;
    QString cumulativeProbabilityDistribution_;
    QString gustFactor_;
    QString kurtosis_;
    QString peakFactor_;
    QString probabilityDensityFunction_;
    QString roughness_;
    QString shearVelocityOfFlow_;
    QString skewness_;
    QString standardDeviation_;
    QString turbulenceIntensity_;
    QString turbulenceScale_;
    QString variance_;
    QString wavePassageEffect_;

public:
    CRPSWindLabsimuData &GetWindLabData();
    RPSWindLabSimulationOutputWorker *GetWindLabSimulationOutputWorker();
    RPSWindLabSimulationWorker *GetWindLabSimulationWorker();
    RPSWindLabComparisonWorker *GetWindLabComparisonWorker();

    void windLabDataInitialize();
    void WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count);
    void ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count);
    void WriteMapToRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count);
    void ReadMapFromRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count);

    //*******save installed plungins for windLab (start)********//
    void WLWriteAllTobeInstallObjectsToRegistry();
    void WLReadAllTobeInstallObjectsFromRegistry();

    void WLWriteAllTobeInstallObjPublicationTitleToRegistry();
    void WLReadAllTobeInstallObjPublicationTitleToRegistry();

    void WLWriteAllTobeInstallObjPublicationLinkToRegistry();
    void WLReadAllTobeInstallObjPublicationLinkToRegistry();

    void WLWriteAllTobeInstallObjPublicationAuthorToRegistry();
    void WLReadAllTobeInstallObjPublicationAuthorToRegistry();

    void WLWriteAllTobeInstallObjPublicationDateToRegistry();
    void WLReadAllTobeInstallObjPublicationDateToRegistry();

    void WLWriteAllTobeInstallObjVersionToRegistry();
    void WLReadAllTobeInstallObjVersionToRegistry();

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
    bool isThisPluginInstalled(const QString &pluginName);
    bool IsThisObjectGroupPluggedInThisPlugin(const std::map<const QString, QString> &map, const QString &pluginName);
    void emptyAllToBeUninstalledObjectsMap();

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
    QStringList FindAllSpatialDistribution();
    QStringList FindAllRandomnessProvider();
    QStringList FindAllCumulativeProbabilityDistribution();
    QStringList FindAllGustFactor();
    QStringList FindAllKurtosis();
    QStringList FindAllPeakFactor();
    QStringList FindAllProbabilityDensityFunction();
    QStringList FindAllRoughness();
    QStringList FindAllShearVelocityOfFlow();
    QStringList FindAllSkewness();
    QStringList FindAllStandardDeviation();
    QStringList FindAllTurbulenceIntensity();
    QStringList FindAllTurbulenceScale();
    QStringList FindAllVariance();
    QStringList FindAllWavePassageEffect();

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
    void matrixToolInital(QString currentSelected);
    void tableToolInital(QString currentSelected);
    void CumulativeProbabilityDistributionInital(QString currentSelected);
    void GustFactorInital(QString currentSelected);
    void KurtosisInital(QString currentSelected);
    void PeakFactorInital(QString currentSelected);
    void ProbabilityDensityFunctionInital(QString currentSelected);
    void RoughnessInital(QString currentSelected);
    void ShearVelocityOfFlowInital(QString currentSelected);
    void SkewnessInital(QString currentSelected);
    void StandardDeviationInital(QString currentSelected);
    void TurbulenceIntensityInital(QString currentSelected);
    void TurbulenceScaleInital(QString currentSelected);
    void VarianceInital(QString currentSelected);
    void WavePassageEffectInital(QString currentSelected);


    void locationDistributionFunctionInital(QString currentSelected);

    void candidateInitialData(QString category, QString currentSelected);

    void createOutputWorker();
    void createSimulationWorker();
    void createComparisonWorker();

    void fillLocationJComboBox(QComboBox *locationJComboBox);
    void fillLocationKComboBox(QComboBox *locationKComboBox);
    void fillFrequencyComboBox(QComboBox *frequencyComboBox);
    void fillTimeComboBox(QComboBox *timeComboBox);
    void locJCurrentIndexChanged(int index);
    void locKCurrentIndexChanged(int index);
    void freqCurrentIndexChanged(int index);
    void timCurrentIndexChanged(int index);

    void saveLineEditIndexes();
    QString logSimulationInfo(bool status, const QString &name);
    QString logTimeComparisonInfo(bool status, const QString &name);
    QString logAccuracyComparisonInfo(bool status, const QString &name);



};

#endif // RPSWINDLABSIMULATION_H
