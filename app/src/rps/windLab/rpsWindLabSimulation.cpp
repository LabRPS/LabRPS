#include "rpsWindLabSimulation.h"

#include "RPSWindLabAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/windLab/widgets/prswlsimuoptionsdlg.h"
#include "rps/windLab/widgets/rpswindvelocitydefinitiondlg.h"
#include "rps/windLab/widgets/rpswlpsddefinitiondialog.h"
#include "rps/windLab/widgets/rpswlcoherencedlg.h"
#include "rps/windLab/widgets/rpswlcorrelationdlg.h"
#include "rps/windLab/widgets/rpswlmodulationdlg.h"
#include "rps/windLab/widgets/rpswlmeanwinddlg.h"
#include "rps/windLab/widgets/rpswlcomparisondialog.h"
#include "rps/windLab/widgets/rpswlaccuracycomparisondialog.h"
#include "rps/windLab/widgets/crpswlruntabletoolsdlg.h"
#include "rps/windLab/widgets/crpswlrunmatrixtoolsdlg.h"
#include "rps/rpsSimulation.h"
#include "ApplicationWindow.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"
#include "globals.h"
#include "core/Utilities.h"
#include <cmath>
#include <matplot/matplot.h>

#include "src/rps/windLab/widgets/crpswlrunmatrixtoolsdlg.h"
#include "src/rps/windLab/widgets/rpswlcumulativeprobabilitydistributiondlg.h"
#include "src/rps/windLab/widgets/rpswlgustfactordlg.h"
#include "src/rps/windLab/widgets/rpswlkurtosisdlg.h"
#include "src/rps/windLab/widgets/rpswlpeakfactordlg.h"
#include "src/rps/windLab/widgets/rpswlprobabilitydensityfunctiondlg.h"
#include "src/rps/windLab/widgets/rpswlroughnessdlg.h"
#include "src/rps/windLab/widgets/rpswlshearvelocityofflowdlg.h"
#include "src/rps/windLab/widgets/rpswlskewnessdlg.h"
#include "src/rps/windLab/widgets/rpswlstandarddeviationdlg.h"
#include "src/rps/windLab/widgets/rpswlturbulenceintensitydlg.h"
#include "src/rps/windLab/widgets/rpswlturbulencescaledlg.h"
#include "src/rps/windLab/widgets/rpswlvariancedlg.h"
#include "src/rps/windLab/widgets/rpswlwavepassageeffectdlg.h"

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMetaType>

RPSWindLabSimulation::RPSWindLabSimulation(QWidget *parent) : QWidget(parent)
{
    locationJ = 0;
    locationK = 0;
    frequencyIndex = 0;
    timeIndex = 0;

    // initialized windLab simulation data
    windLabDataInitialize();

    WLReadAllTobeInstallObjVersionToRegistry();
    WLReadAllTobeInstallObjPublicationTitleToRegistry();
    WLReadAllTobeInstallObjPublicationLinkToRegistry();
    WLReadAllTobeInstallObjPublicationAuthorToRegistry();
    WLReadAllTobeInstallObjPublicationDateToRegistry();

    // read install windLab from registry if any
    WLReadAllTobeInstallObjectsFromRegistry();
    WLClearAllTobeInstallObjectsFromRegistry();

    // comparison
    comparisonInitial();
}

RPSWindLabSimulation::~RPSWindLabSimulation()
{
    // write install windLab from registry if any

    WLWriteAllTobeInstallObjPublicationTitleToRegistry();
    WLWriteAllTobeInstallObjPublicationLinkToRegistry();
    WLWriteAllTobeInstallObjPublicationAuthorToRegistry();
    WLWriteAllTobeInstallObjPublicationDateToRegistry();
    WLWriteAllTobeInstallObjVersionToRegistry();

    WLWriteAllTobeInstallObjectsToRegistry();

    if(nullptr != comparisonThread)
    {
        QMessageBox::warning(0, "windLab", "worker thread still running.");
        comparisonThread->exit(0);
        comparisonThread->wait(); // <-- wits till the thread has exited
        deleteLater(); // <-- ensures that it will be deleted later when the (main?) event loop executes again
    }
}

void RPSWindLabSimulation::windVelocity()
{
    std::unique_ptr<RPSWindVelocityDefinitionDlg> dlg(new RPSWindVelocityDefinitionDlg(this));

    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().numberOfSpatialPosition = dlg->numberOfSpatialPosition;
        GetWindLabData().numberOfTimeIncrements = dlg->numberOfTimeIncrements;
        GetWindLabData().timeIncrement = dlg->timeIncrement;
        GetWindLabData().minTime = dlg->minTime;
        GetWindLabData().maxTime = dlg->maxTime;
        GetWindLabData().numberOfSample = dlg->numberOfSample;
        GetWindLabData().stationarity = dlg->stationarity;
        GetWindLabData().uniformModulation = dlg->uniformModulation;
        GetWindLabData().gaussianity = dlg->gaussianity;
        GetWindLabData().spatialDistribution = dlg->spatialDistribution;

        // update the statusbar combobox content

        RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
        rpsSimulator->fillLocationJComboBox();
        rpsSimulator->fillLocationKComboBox();
        rpsSimulator->fillTimeComboBox();
    }
}

void RPSWindLabSimulation::spectrumWind()
{
    std::unique_ptr<RPSWLPSDDefinitionDialog> dlg(new RPSWLPSDDefinitionDialog(this));

    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().numberOfFrequency = dlg->numberOfFrequency;
        GetWindLabData().minFrequency = dlg->minFrequency;
        GetWindLabData().maxFrequency = dlg->maxFrequency;
        GetWindLabData().frequencyIncrement = dlg->frequencyIncrement;
        GetWindLabData().direction = dlg->windDirection;

        GetWindLabData().spectrumModel = dlg->spectrumModel;
        GetWindLabData().cpsdDecompositionMethod = dlg->cpsdDecompositionMethod;
        GetWindLabData().freqencyDistribution = dlg->freqencyDistribution;

        RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
        rpsSimulator->fillFrequencyComboBox();
    }
}

void RPSWindLabSimulation::coherenceWind()
{
    std::unique_ptr<RPSWLCoherenceDlg> dlg(new RPSWLCoherenceDlg(this));

    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().coherenceFunction = dlg->coherenceFunction;
    }
}
void RPSWindLabSimulation::correlationWind()
{
    std::unique_ptr<RPSWLCorrelationDlg> dlg(new RPSWLCorrelationDlg(this));

    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().correlationFunction = dlg->correlationFunction;
    }
}
void RPSWindLabSimulation::modulationWind()
{
    std::unique_ptr<RPSWLModulationDlg> dlg(new RPSWLModulationDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().modulationFunction = dlg->modulationFunction;
    }
}

void RPSWindLabSimulation::meanWindVelocity()
{
    std::unique_ptr<RPSWLMeanDlg> dlg(new RPSWLMeanDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().meanFunction = dlg->meanFunction;
    }
}

void RPSWindLabSimulation::cumulativeProbabilityDistribution()
{
    std::unique_ptr<RPSWLCumulativeProbabilityDistributionDlg> dlg(new RPSWLCumulativeProbabilityDistributionDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().cumulativeProbabilityDistribution = dlg->cumulativeProbabilityDistribution;
    }
}
void RPSWindLabSimulation::gustFactor()
{
    std::unique_ptr<RPSWLGustFactorDlg> dlg(new RPSWLGustFactorDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().gustFactor = dlg->gustFactor;
    }
}
void RPSWindLabSimulation::kurtosis()
{
    std::unique_ptr<RPSWLKurtosisDlg> dlg(new RPSWLKurtosisDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().kurtosis = dlg->kurtosis;
    }
}
void RPSWindLabSimulation::peakFactor()
{
    std::unique_ptr<RPSWLPeakFactorDlg> dlg(new RPSWLPeakFactorDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().peakFactor = dlg->peakFactor;
    }
}
void RPSWindLabSimulation::probabilityDensityFunction()
{
    std::unique_ptr<RPSWLProbabilityDensityFunctionDlg> dlg(new RPSWLProbabilityDensityFunctionDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().probabilityDensityFunction = dlg->probabilityDensityFunction;
    }
}
void RPSWindLabSimulation::roughness()
{
    std::unique_ptr<RPSWLRoughnessDlg> dlg(new RPSWLRoughnessDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().roughness = dlg->roughness;
    }
}
void RPSWindLabSimulation::shearVelocityOfFlow()
{
    std::unique_ptr<RPSWLShearVelocityOfFlowDlg> dlg(new RPSWLShearVelocityOfFlowDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().shearVelocityOfFlow = dlg->shearVelocityOfFlow;
    }
}
void RPSWindLabSimulation::skewness()
{
    std::unique_ptr<RPSWLSkewnessDlg> dlg(new RPSWLSkewnessDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().skewness = dlg->skewness;
    }
}
void RPSWindLabSimulation::standardDeviation()
{
    std::unique_ptr<RPSWLStandardDeviationDlg> dlg(new RPSWLStandardDeviationDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().standardDeviation = dlg->standardDeviation;
    }
}
void RPSWindLabSimulation::turbulenceIntensity()
{
    std::unique_ptr<RPSWLTurbulenceIntensityDlg> dlg(new RPSWLTurbulenceIntensityDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().turbulenceIntensity = dlg->turbulenceIntensity;
    }
}
void RPSWindLabSimulation::turbulenceScale()
{
    std::unique_ptr<RPSWLTurbulenceScaleDlg> dlg(new RPSWLTurbulenceScaleDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().turbulenceScale = dlg->turbulenceScale;
    }
}
void RPSWindLabSimulation::variance()
{
    std::unique_ptr<RPSWLVarianceDlg> dlg(new RPSWLVarianceDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().variance = dlg->variance;
    }
}

void RPSWindLabSimulation::wavePassageEffect()
{
    std::unique_ptr<RPSWLWavePassageEffectDlg> dlg(new RPSWLWavePassageEffectDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().wavePassageEffect = dlg->wavePassageEffect;
    }
}

void RPSWindLabSimulation::cumulativeProbabilityDistributionOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(cumulativeProbabilityDistributionOutp()));
    connect(simulationOutputWorker, SIGNAL(showCumulativeProbabilityDistributionOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::gustFactorOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(gustFactorOutp()));
    connect(simulationOutputWorker, SIGNAL(showGustFactorOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::kurtosisOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(kurtosisOutp()));
    connect(simulationOutputWorker, SIGNAL(showKurtosisOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::peakFactorOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(peakFactorOutp()));
    connect(simulationOutputWorker, SIGNAL(showPeakFactorOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::probabilityDensityFunctionOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(probabilityDensityFunctionOutp()));
    connect(simulationOutputWorker, SIGNAL(showProbabilityDensityFunctionOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::roughnessOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(roughnessOutp()));
    connect(simulationOutputWorker, SIGNAL(showRoughnessOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::shearVelocityOfFlowOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(shearVelocityOfFlowOutp()));
    connect(simulationOutputWorker, SIGNAL(showShearVelocityOfFlowOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::skewnessOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(skewnessOutp()));
    connect(simulationOutputWorker, SIGNAL(showSkewnessOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::standardDeviationOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(standardDeviationOutp()));
    connect(simulationOutputWorker, SIGNAL(showStandardDeviationOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::turbulenceIntensityOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(turbulenceIntensityOutp()));
    connect(simulationOutputWorker, SIGNAL(showTurbulenceIntensityOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::turbulenceScaleOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(turbulenceScaleOutp()));
    connect(simulationOutputWorker, SIGNAL(showTurbulenceScaleOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::varianceOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(varianceOutp()));
    connect(simulationOutputWorker, SIGNAL(showVarianceOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::wavePassageEffectOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(wavePassageEffectOutp()));
    connect(simulationOutputWorker, SIGNAL(showWavePassageEffectOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}

void RPSWindLabSimulation::frequencyDistributionOutput()
{
    createOutputWorker();

    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(frequencyDistributionOut()));
    connect(simulationOutputWorker, SIGNAL(showFrequencyDistributionOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::locationDistributionOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(locationDistributionOut()));
    connect(simulationOutputWorker, SIGNAL(showLocationDistributionOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::windVelocityOutput()
{
    if (GetWindLabData().isSimulationSuccessful == true)
    {
        displayWindVelocity(GetWindLabData().isSimulationSuccessful);
    }
    else
    {
        information.append("Please make sure you successfully run a simulation first");
        emit sendInformation(information);
        information.clear();

    }
}

void RPSWindLabSimulation::spectrumWindOutput()
{
    createOutputWorker();

    if (1 == GetWindLabData().direction)
    {
        // QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumXModelOut);
        connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumXModelOut()));
        connect(simulationOutputWorker, SIGNAL(showXSpectrumOutput()), this, SLOT(displayOutputResults()));
        psdPrefix = "X";
        emit progressBarShow();
        simulationOutputThread->start();
    }
    else if (2 == GetWindLabData().direction)
    {
        // QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumYModelOut);
        connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumYModelOut()));
        connect(simulationOutputWorker, SIGNAL(showYSpectrumOutput()), this, SLOT(displayOutputResults()));
        psdPrefix = "Y";
        emit progressBarShow();
        simulationOutputThread->start();
    }
    else if (3 == GetWindLabData().direction)
    {
        // QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumZModelOut);
        connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumZModelOut()));
        connect(simulationOutputWorker, SIGNAL(showZSpectrumOutput()), this, SLOT(displayOutputResults()));
        psdPrefix = "Z";
        emit progressBarShow();
        simulationOutputThread->start();
    }
}

void RPSWindLabSimulation::decomposedSpectrumWindOutput()
{
    createOutputWorker();

    // QFuture<void> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumXModelOut);
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(decomposedSpectrumModelOut()));
    connect(simulationOutputWorker, SIGNAL(showDecomposedSpectrumOutput()), this, SLOT(displayOutputResults()));
    emit progressBarShow();
    simulationOutputThread->start();
}

void RPSWindLabSimulation::coherenceWindOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(coherenceOut()));
    connect(simulationOutputWorker, SIGNAL(showCoherenceOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::correlationWindOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(correlationOut()));
    connect(simulationOutputWorker, SIGNAL(showCorrelationOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}
void RPSWindLabSimulation::modulationWindOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(modulationOut()));
    connect(simulationOutputWorker, SIGNAL(showModulationOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}

void RPSWindLabSimulation::meanWindVelocityOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(meanWindVelocityOut()));
    connect(simulationOutputWorker, SIGNAL(showMeanWindVelocityOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}

void RPSWindLabSimulation::randomPhaseWindOutput()
{
    createOutputWorker();
    connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(randomPhaseOut()));
    connect(simulationOutputWorker, SIGNAL(showRandomPhaseOutput()), this, SLOT(displayOutputResults()));

    emit progressBarShow();
    simulationOutputThread->start();
}

CRPSWindLabsimuData &RPSWindLabSimulation::GetWindLabData()
{
    return windLabData;
}

RPSWindLabSimulationOutputWorker *RPSWindLabSimulation::GetWindLabSimulationOutputWorker()
{
    return simulationOutputWorker;
}

RPSWindLabSimulationWorker *RPSWindLabSimulation::GetWindLabSimulationWorker()
{
    return simulationWorker;
}

RPSWindLabComparisonWorker *RPSWindLabSimulation::GetWindLabComparisonWorker()
{
    return comparisonWorker;
}

void RPSWindLabSimulation::windLabDataInitialize()
{
    windLabData.numberOfSpatialPosition = 3;
    windLabData.numberOfSample = 1;
    windLabData.spatialDistribution = "Horizontal Distribution";
    windLabData.numberOfFrequency = 1024;
    windLabData.minFrequency = 0;
    windLabData.maxFrequency = 4*3.14;
    windLabData.frequencyIncrement = windLabData.maxFrequency / windLabData.numberOfFrequency;
    windLabData.coherenceFunction = "Davenport Coherence";
    windLabData.meanFunction = "RPS Logarithmic Low";
    windLabData.simulationApproach = "Spectral Representation Approach";
    windLabData.simulationMethod = "Deodatis et al 1987";
    windLabData.randomnessProvider = "Uniform Random Phases";
    windLabData.spectrumModel = "Kaimal Along Wind Spectrum";
    windLabData.cpsdDecompositionMethod = "RPS Cholesky Decomposition";
    windLabData.freqencyDistribution = "Double Index Frequency";
    windLabData.modulationFunction = "RPS Exponential Model";
    windLabData.direction = 1;
    windLabData.numberOfTimeIncrements = 2 * windLabData.numberOfFrequency * windLabData.numberOfSpatialPosition;
    windLabData.timeIncrement = 3.14/windLabData.maxFrequency;
    windLabData.stationarity = true;
    windLabData.uniformModulation = true;
    windLabData.gaussianity = true;
    windLabData.minTime = 0;
    windLabData.comparisonMode = false;
    windLabData.largeScaleSimulationMode = false;
    windLabData.frequencyDistrType = 2;
    windLabData.frequencyIndex = 0;
    windLabData.timeIndex = 0;
    windLabData.directionIndex = 0;
    windLabData.comparisonCategory = LabRPS::objGroupSimulationMethod;
    windLabData.numberOfTimeLags = windLabData.numberOfFrequency;
    windLabData.comparisonType = 1;
    windLabData.isInterruptionRequested = false;
    windLabData.isSimulationSuccessful = false;

   windLabData.cumulativeProbabilityDistribution = "None";
   windLabData.gustFactor = "None";
   windLabData.kurtosis = "None";
   windLabData.peakFactor = "None";
   windLabData.probabilityDensityFunction = "None";
   windLabData.roughness = "None";
   windLabData.shearVelocityOfFlow = "None";
   windLabData.skewness = "None";
   windLabData.standardDeviation = "None";
   windLabData.turbulenceIntensity = "None";
   windLabData.turbulenceScale = "None";
   windLabData.variance = "None";
   windLabData.wavePassageEffect = "None";

    QSettings settings;
    settings.beginGroup("General");
    windLabData.workingDirPath = settings.value("WorkingDirectory", QCoreApplication::instance()->applicationDirPath()).toString();
    windLabData.indexControls = settings.value("IndexControls", 1).toInt();
    settings.endGroup();
}

void RPSWindLabSimulation::WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{

    if (map.empty())
    {
        return;
    }

    QStringList mapkeylst;
    QStringList mapvaluelst;

    // Iterate though the map
    for (auto it1 = map.begin(); it1 != map.end(); ++it1)
    {
        mapkeylst.append(it1->first);
        mapvaluelst.append(it1->second);
    }

    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.setValue("mapkey", mapkeylst);
    settings.setValue("mapValue", mapvaluelst);
    settings.endGroup();

    count++;
}

void RPSWindLabSimulation::ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    QStringList mapkeylst = settings.value("mapkey").toStringList();
    QStringList mapvaluelst = settings.value("mapValue").toStringList();
    settings.endGroup();

    if (mapkeylst.isEmpty())
    {
        return;
    }

    for (int i = 0; i < mapkeylst.size(); ++i)
    {
        QString key = mapkeylst.at(i);
        QString value = mapvaluelst.at(i);

        map[key] = value;
    }

    count++;
}

void RPSWindLabSimulation::WriteMapToRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{

    if (map.empty())
    {
        return;
    }

    QStringList mapkeylst;
    QStringList mapvaluelst;

    // Iterate though the map
    for (auto it1 = map.begin(); it1 != map.end(); ++it1)
    {
        mapkeylst.append(it1->first);
        mapvaluelst.append(it1->second);
    }

    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.setValue("mapkey", mapkeylst);
    settings.setValue("mapValue", mapvaluelst);
    settings.endGroup();

    count++;
}

void RPSWindLabSimulation::ReadMapFromRegistry2(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    QStringList mapkeylst = settings.value("mapkey").toStringList();
    QStringList mapvaluelst = settings.value("mapValue").toStringList();
    settings.endGroup();

    if (mapkeylst.isEmpty())
    {
        return;
    }

    for (int i = 0; i < mapkeylst.size(); ++i)
    {
        QString key = mapkeylst.at(i);
        QString value = mapvaluelst.at(i);

        map[key] = value;
        PluginManager::GetInstance().GetAllPlugedObjectsMap()[key] = value;
    }

    count++;
}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjectsToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("WLSimMethod"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLLoc"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLXPSD"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLYPSD"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLZPSD"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLCoh"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLDecomp"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLFreq"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLRand"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLMod"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLCorr"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLMean"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLTableTool"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixTool"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObj"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistribution"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactor"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosis"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunction"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLRoughness"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlow"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLSkewness"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviation"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensity"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScale"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLVariance"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffect"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), settingsGroup, count);


}


void RPSWindLabSimulation::WLReadAllTobeInstallObjectsFromRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("WLSimMethod"), count = 1;
    ReadMapFromRegistry2(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLLoc"), count = 1;
    ReadMapFromRegistry2(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLXPSD"), count = 1;
    ReadMapFromRegistry2(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLYPSD"), count = 1;
    ReadMapFromRegistry2(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLZPSD"), count = 1;
    ReadMapFromRegistry2(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLCoh"), count = 1;
    ReadMapFromRegistry2(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLDecomp"), count = 1;
    ReadMapFromRegistry2(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLFreq"), count = 1;
    ReadMapFromRegistry2(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLRand"), count = 1;
    ReadMapFromRegistry2(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLMod"), count = 1;
    ReadMapFromRegistry2(CrpsModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLCorr"), count = 1;
    ReadMapFromRegistry2(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLMean"), count = 1;
    ReadMapFromRegistry2(CrpsMeanFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLTableTool"), count = 1;
    ReadMapFromRegistry2(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixTool"), count = 1;
    ReadMapFromRegistry2(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObj"), count = 1;
    ReadMapFromRegistry2(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistribution"), count = 1;
    ReadMapFromRegistry2(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactor"), count = 1;
    ReadMapFromRegistry2(CrpsGustFactorFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosis"), count = 1;
    ReadMapFromRegistry2(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactor"), count = 1;
    ReadMapFromRegistry2(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunction"), count = 1;
    ReadMapFromRegistry2(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLRoughness"), count = 1;
    ReadMapFromRegistry2(CrpsRoughnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlow"), count = 1;
    ReadMapFromRegistry2(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLSkewness"), count = 1;
    ReadMapFromRegistry2(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviation"), count = 1;
    ReadMapFromRegistry2(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensity"), count = 1;
    ReadMapFromRegistry2(CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScale"), count = 1;
    ReadMapFromRegistry2(CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLVariance"), count = 1;
    ReadMapFromRegistry2(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffect"), count = 1;
    ReadMapFromRegistry2(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);


}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("WLSimMethodTitle"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLLocTitle"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLCohTitle"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLDecompTitle"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLFreqTitle"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLRandTitle"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLModTitle"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLCorrTitle"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLMeanTitle"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolTitle"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolTitle"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjTitle"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionTitle"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorTitle"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisTitle"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorTitle"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionTitle"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessTitle"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowTitle"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessTitle"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationTitle"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityTitle"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleTitle"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceTitle"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectTitle"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);



}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("WLSimMethodTitle"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLLocTitle"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLCohTitle"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLDecompTitle"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLFreqTitle"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLRandTitle"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLModTitle"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLCorrTitle"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLMeanTitle"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjTitle"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionTitle"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorTitle"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisTitle"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorTitle"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionTitle"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessTitle"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowTitle"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessTitle"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationTitle"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityTitle"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleTitle"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceTitle"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectTitle"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("WLSimMethodLink"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLLocLink"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDLink"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDLink"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDLink"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLCohLink"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLDecompLink"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLFreqLink"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLRandLink"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLModLink"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLCorrLink"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLMeanLink"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolLink"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolLink"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjLink"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionLink"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorLink"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisLink"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorLink"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionLink"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessLink"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowLink"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessLink"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationLink"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityLink"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleLink"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceLink"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectLink"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);


}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("WLSimMethodLink"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLLocLink"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLCohLink"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLDecompLink"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLFreqLink"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLRandLink"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLModLink"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLCorrLink"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLMeanLink"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolLink"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolLink"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjLink"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionLink"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorLink"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisLink"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorLink"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionLink"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessLink"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowLink"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessLink"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationLink"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityLink"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleLink"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceLink"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectLink"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);
}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("WLSimMethodAuthor"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLLocAuthor"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLCohAuthor"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLDecompAuthor"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLFreqAuthor"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLRandAuthor"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLModAuthor"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLCorrAuthor"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLMeanAuthor"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjAuthor"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionAuthor"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorAuthor"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisAuthor"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorAuthor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionAuthor"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessAuthor"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowAuthor"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessAuthor"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationAuthor"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityAuthor"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleAuthor"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceAuthor"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectAuthor"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);


}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("WLSimMethodAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLLocAuthor"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLCohAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLDecompAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLFreqAuthor"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLRandAuthor"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLModAuthor"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLCorrAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLMeanAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjAuthor"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorAuthor"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisAuthor"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessAuthor"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowAuthor"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationAuthor"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceAuthor"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectAuthor"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);
}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("WLSimMethodDate"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLLocDate"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDDate"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDDate"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDDate"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLCohDate"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLDecompDate"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLFreqDate"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLRandDate"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLModDate"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLCorrDate"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLMeanDate"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolDate"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolDate"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjDate"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionDate"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorDate"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisDate"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorDate"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionDate"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessDate"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowDate"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessDate"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationDate"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityDate"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleDate"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceDate"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectDate"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("WLSimMethodDate"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLLocDate"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLCohDate"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLDecompDate"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLFreqDate"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLRandDate"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLModDate"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLCorrDate"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLMeanDate"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolDate"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolDate"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjDate"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionDate"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorDate"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisDate"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorDate"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionDate"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessDate"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowDate"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessDate"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationDate"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityDate"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleDate"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceDate"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectDate"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLWriteAllTobeInstallObjVersionToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = ("WLSimMethodVersion"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLLocVersion"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLCohVersion"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLDecompVersion"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLFreqVersion"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLRandVersion"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLModVersion"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLCorrVersion"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLMeanVersion"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolVersion"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolVersion"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjVersion"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionVersion"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorVersion"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisVersion"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorVersion"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionVersion"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessVersion"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowVersion"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessVersion"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationVersion"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityVersion"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleVersion"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceVersion"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectVersion"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);

}

void RPSWindLabSimulation::WLReadAllTobeInstallObjVersionToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = ("WLSimMethod"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLLocVersion"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLXPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLYPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLZPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLCohVersion"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLDecompVersion"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLFreqVersion"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLRandVersion"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLModVersion"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLCorrVersion"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLMeanVersion"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLTableToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLMatrixToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLUserDefinedRPSObjVersion"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLCumulativeProbabilityDistributionVersion"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLGustFactorVersion"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLKurtosisVersion"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLPeakFactorVersion"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLProbabilityDensityFunctionVersion"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLRoughnessVersion"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLShearVelocityOfFlowVersion"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLSkewnessVersion"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLStandardDeviationVersion"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceIntensityVersion"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLTurbulenceScaleVersion"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLVarianceVersion"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = ("WLWavePassageEffectVersion"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);
}

void RPSWindLabSimulation::WLClearAllTobeInstallObjectsFromRegistry()
{
    QString settingsGroup;

    settingsGroup = ("WLSimMethod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLLoc");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLXPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLYPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLZPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCoh");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLDecomp");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLFreq");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRand");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCorr");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMean");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTableTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMatrixTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLUserDefinedRPSObj");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = ("WLSimMethodTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLLocTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLXPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLYPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLZPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCohTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLDecompTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLFreqTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRandTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLModTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCorrTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMeanTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTableToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMatrixToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLUserDefinedRPSObjTitle");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = ("WLSimMethodLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLLocLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLXPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLYPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLZPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCohLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLDecompLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLFreqLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRandLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLModLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCorrLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMeanLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTableToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMatrixToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLUserDefinedRPSObjLink");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = ("WLSimMethodAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLLocAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLXPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLYPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLZPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCohAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLDecompAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLFreqAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRandAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLModAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCorrAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMeanAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTableToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMatrixToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLUserDefinedRPSObjAuthor");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = ("WLSimMethodDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLLocDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLXPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLYPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLZPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCohDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLDecompDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLFreqDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRandDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLModDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCorrDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMeanDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTableToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMatrixToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLUserDefinedRPSObjDate");
    ClearMapFromRegistry(settingsGroup);



    //
    settingsGroup = ("WLSimMethodVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLLocVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLXPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLYPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLZPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCohVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLDecompVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLFreqVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRandVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLModVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCorrVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMeanVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTableToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLMatrixToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLUserDefinedRPSObjVersion");
    ClearMapFromRegistry(settingsGroup);

    //////////////////////////////////////////////////////

    settingsGroup = ("WLCumulativeProbabilityDistribution");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLGustFactor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLKurtosis");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLPeakFactor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLProbabilityDensityFunction");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRoughness");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLShearVelocityOfFlow");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLSkewness");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLStandardDeviation");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceIntensity");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceScale");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLVariance");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLWavePassageEffect");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCumulativeProbabilityDistributionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLGustFactorTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLKurtosisTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLPeakFactorTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLProbabilityDensityFunctionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRoughnessTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLShearVelocityOfFlowTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLSkewnessTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLStandardDeviationTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceIntensityTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceScaleTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLVarianceTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLWavePassageEffectTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCumulativeProbabilityDistributionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLGustFactorLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLKurtosisLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLPeakFactorLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLProbabilityDensityFunctionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRoughnessLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLShearVelocityOfFlowLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLSkewnessLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLStandardDeviationLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceIntensityLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceScaleLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLVarianceLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLWavePassageEffectLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCumulativeProbabilityDistributionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLGustFactorAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLKurtosisAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLPeakFactorAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLProbabilityDensityFunctionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRoughnessAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLShearVelocityOfFlowAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLSkewnessAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLStandardDeviationAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceIntensityAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceScaleAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLVarianceAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLWavePassageEffectAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCumulativeProbabilityDistributionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLGustFactorDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLKurtosisDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLPeakFactorDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLProbabilityDensityFunctionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRoughnessDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLShearVelocityOfFlowDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLSkewnessDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLStandardDeviationDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceIntensityDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceScaleDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLVarianceDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLWavePassageEffectDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLCumulativeProbabilityDistributionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLGustFactorVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLKurtosisVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLPeakFactorVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLProbabilityDensityFunctionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLRoughnessVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLShearVelocityOfFlowVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLSkewnessVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLStandardDeviationVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceIntensityVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLTurbulenceScaleVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLVarianceVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = ("WLWavePassageEffectVersion");
    ClearMapFromRegistry(settingsGroup);

}

void RPSWindLabSimulation::ClearMapFromRegistry(QString &settingsGroup)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.remove(""); // removes the group, and all it keys
    settings.endGroup();
}

bool RPSWindLabSimulation::GetObjects(std::map<const QString, QString> &map, QStringList &lstObject, QString pluginName)
{
    if (!map.empty())
    {
        // Iterate though the map and show all the registed objects
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (!it->first.isEmpty())
            {
                if (it->second == pluginName)
                {
                    lstObject.append(it->first);
                }
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool RPSWindLabSimulation::GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName)
{
    lstObject.clear();

    try
    {
        GetObjects(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);

        GetObjects(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsGustFactorFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsRoughnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
        GetObjects(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);

    }
    catch (const std::exception &e)
    {
        return false;
    }

    return true;
}

bool RPSWindLabSimulation::GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName)
{
    lstObject.clear();
    try
    {
        GetObjects(CrpsSimuMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsXSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsYSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsZSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsMeanFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsTableToolFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsMatrixToolFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), lstObject, pluginName);

        GetObjects(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsGustFactorFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsKurtosisFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsPeakFactorFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsRoughnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsSkewnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsTurbulenceScaleFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsVarianceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
        GetObjects(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), lstObject, pluginName);

    }
    catch (const std::exception &e)
    {
        return false;
    }

    return true;
}

bool RPSWindLabSimulation::IsObjectInstalled(QString &object)
{
    if (IsThisObjectInstalled(CrpsSimuMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsLocationDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsXSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsYSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsZSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsCoherenceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsRandomnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsModulationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsMeanFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    if (IsThisObjectInstalled(CrpsTableToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsMatrixToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsGustFactorFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsKurtosisFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsPeakFactorFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsRoughnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsSkewnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsStandardDeviationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsTurbulenceScaleFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsVarianceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (IsThisObjectInstalled(CrpsWavePassageEffectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    return false;
}


bool RPSWindLabSimulation::UpdateObjectsMap(std::map<const QString, QString> &map, const QString &lstObject)
{
    if (!map.empty())
    {
        if (map.find(lstObject) != map.end())
        {
            map.erase(lstObject);
        }
    }

    return true;
}

bool RPSWindLabSimulation::UpdateObjectToSkipMap(std::map<const QString, QString> &map, const QString name, const QString pluginName)
{
    map[name] = pluginName;
    return true;
}

bool RPSWindLabSimulation::UpdateToBeInstalledObjectsMap(const QString &lstObject)
{
    try
    {
        UpdateObjectsMap(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject);

        UpdateObjectsMap(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsGustFactorFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsRoughnessFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject);
        UpdateObjectsMap(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject);

    }
    catch (const std::exception &e)
    {
        return false;
    }

    return true;
}

bool RPSWindLabSimulation::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
    try
    {
        UpdateObjectToSkipMap(CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

        UpdateObjectToSkipMap(CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
        UpdateObjectToSkipMap(CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

    }
    catch (const std::exception &e)
    {
        return false;
    }

    return true;
}

bool RPSWindLabSimulation::isThisPluginInstalled(const QString &pluginName)
{

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsSimuMethodFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsXSpectrumFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsYSpectrumFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsZSpectrumFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsCoherenceFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsRandomnessFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsModulationFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsCorrelationFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsMeanFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsTableToolFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsMatrixToolFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsGustFactorFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsKurtosisFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsPeakFactorFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsRoughnessFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsSkewnessFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsTurbulenceScaleFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsVarianceFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    if(IsThisObjectGroupPluggedInThisPlugin(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), pluginName)){return true;}

    return false;
}

bool RPSWindLabSimulation::IsThisObjectGroupPluggedInThisPlugin(const std::map<const QString, QString> &map, const QString &pluginName)
{
    if (!map.empty())
    {
        //go through the map
        for(auto& it:map)
        {
            //if mapped value is pluginName
            //then return true
            if(it.second == pluginName)
            {
                return true;
            }
        }
    }

    return false;
}

void RPSWindLabSimulation::emptyAllToBeUninstalledObjectsMap()
{
    try
    {
        CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap().clear();

        CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap().clear();



    }
    catch (const std::exception &e)
    {

    }
}


bool RPSWindLabSimulation::IsThisObjectInstalled(std::map<const QString, QString> &map, QString &object)
{
    if (!map.empty())
    {
        if (map.find(object) != map.end())
        {
            return true;
        }
    }

    return false;
}

void RPSWindLabSimulation::runSimulation()
{
    if (!GetWindLabData().comparisonMode)
    {
        createSimulationWorker();
        connect(simulationWorker, SIGNAL(showWindVelocityOutput(bool)), this, SLOT(displayWindVelocity(bool)));
        emit progressBarShow();
        simulationThread->start();
    }
    else
    {
        if (GetWindLabData().comparisonType == 1) // accuracy
        {
            createComparisonWorker();
            connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareAccuracy()));
            connect(comparisonWorker, SIGNAL(showAccuracyComparisonOutput()), this, SLOT(displayAccuracyComparisonResults()));
            emit progressBarShow();
            comparisonThread->start();
        }
        else if (GetWindLabData().comparisonType == 2) // time
        {
            createComparisonWorker();
            connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareTime()));
            connect(comparisonWorker, SIGNAL(showTimeComparisonOutput()), this, SLOT(displayTimeComparisonResults()));

            emit progressBarShow();
            comparisonThread->start();
        }
        else if (GetWindLabData().comparisonType == 3) // memory
        {
            createComparisonWorker();
            connect(comparisonThread, SIGNAL(started()), comparisonWorker, SLOT(compareMemory()));
            connect(comparisonWorker, SIGNAL(showMemoryComparisonOutput()), this, SLOT(displayMemoryComparisonResults()));
            emit progressBarShow();
            comparisonThread->start();
        }
    }
}
void RPSWindLabSimulation::pauseSimulation()
{
    // // from https://stackoverflow.com/questions/4093159/what-is-the-correct-way-to-implement-a-qthread-example-please
    // simulationOutputThread = new QThread();
    // simulationOutputWorker = new RPSWindLabSimulationOutputWorker(windLabData, information, locationJ, locationK, frequencyIndex, timeIndex);

    // simulationOutputWorker->moveToThread(simulationOutputThread);

    // connect(simulationOutputThread, SIGNAL(started()), simulationOutputWorker, SLOT(spectrumXModelOut()));
    // connect(this, SIGNAL(stopped()), simulationOutputWorker, SLOT(stop()), Qt::DirectConnection);

    // // connect(simulationOutputWorker, SIGNAL(destroyed()), simulationOutputThread, SLOT(quit()));
    // // connect(simulationOutputThread, SIGNAL(finished()), simulationOutputThread, SLOT(deleteLater()));

    // connect(simulationOutputWorker, SIGNAL(finished()), simulationOutputThread, SLOT(quit()));
    // connect(simulationOutputWorker, SIGNAL(finished()), simulationOutputWorker, SLOT(deleteLater()));
    // connect(simulationOutputThread, SIGNAL(finished()), simulationOutputThread, SLOT(deleteLater()));

    // connect(simulationOutputWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
    // connect(simulationOutputWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
    // connect(simulationOutputWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

    // //qRegisterMetaType<MatrixXd> >("MatrixXd");
    // connect(simulationOutputWorker, SIGNAL(sendOutputMatrix(MatrixXd)), this, SLOT(receiveOutputMatrix(MatrixXd)), Qt::QueuedConnection);

    // simulationOutputThread->start();

    // qDebug() << "Allowed thread:" << pool.maxThreadCount() ;
    // qDebug() << QThread::idealThreadCount();
    // qDebug() << QThreadPool::globalInstance->maxThreadCount();

    // information.append(QString::number(QThread::idealThreadCount()));
    // information.append(QString::number(QThreadPool::globalInstance->maxThreadCount()));

    // emit sendInformation(information);

    // QFuture<mat> future = QtConcurrent::run(simulationOutputWorker, &RPSWindLabSimulationOutputWorker::spectrumXModelOut);

    // mat result = future.result();

    // RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    // ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    // // allocate memory for the table
    // 	Table *table = app->newTable("haha", GetWindLabData().numberOfFrequency, GetWindLabData().numberOfTimeIncrements);

    // 	// fill the table with computed coherence
    // 	for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
    // 	{
    // 		for (int j = 0; j < GetWindLabData().numberOfTimeIncrements; j++)
    // 		{
    // 			table->setCellValue(i, j, result(i,j));
    // 		}
    // 	}

    // 	table->showNormal();

    // QMessageBox::warning(this, "future", QString::number(result.rows()));
}
void RPSWindLabSimulation::stopSimulation()
{
    if (nullptr == simulationThread || !simulationThread->isRunning())
    {
        return;
    }
    information.append("Stopping the simulation...");
    emit sendInformation(information);
    information.clear();
    emit stopped();
}

void RPSWindLabSimulation::simulationOptions()
{
    std::unique_ptr<PRSWLSimuOptionsDlg> dlg(new PRSWLSimuOptionsDlg(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        GetWindLabData().simulationMethod = dlg->currentsimulationMethod;
        GetWindLabData().randomnessProvider = dlg->currentRandomnessProvider;
        GetWindLabData().comparisonMode = dlg->comparisonMode;
        GetWindLabData().largeScaleSimulationMode = dlg->largeScaleMode;
    }
}

void RPSWindLabSimulation::compareAccuracy()
{
    std::unique_ptr<RPSWLAccuracyComparisonDialog> dlg(new RPSWLAccuracyComparisonDialog(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        comparisonCategory = dlg->comparisonCategory;
        comparisonFunction = dlg->comparisonFunction;
        comparisonCandidate = dlg->comparisonCandidate;
        // resultOutputType = dlg->resultOutputType;
        GetWindLabData().comparisonType = 1;

        coherence_ = dlg->coherence;
        correlation_ = dlg->correlation;
        frequency_ = dlg->frequency;
        mean_ = dlg->mean;
        modulation_ = dlg->modulation;
        decomposition_ = dlg->decomposition;
        simulation_ = dlg->simulation;
        spatial_ = dlg->spatial;
        randomness_ = dlg->randomness;
        spectrum_ = dlg->spectrum;
        cumulativeProbabilityDistribution_ = dlg->cumulativeProbabilityDistribution;
        gustFactor_ = dlg->gustFactor;
        kurtosis_ = dlg->kurtosis;
        peakFactor_ = dlg->peakFactor;
        probabilityDensityFunction_ = dlg->probabilityDensityFunction;
        roughness_ = dlg->roughness;
        shearVelocityOfFlow_ = dlg->shearVelocityOfFlow;
        skewness_ = dlg->skewness;
        standardDeviation_ = dlg->standardDeviation;
        turbulenceIntensity_ = dlg->turbulenceIntensity;
        turbulenceScale_ = dlg->turbulenceScale;
        variance_ = dlg->variance;
        wavePassageEffect_ = dlg->wavePassageEffect;
    }
}
void RPSWindLabSimulation::compareComputationTime()
{
    mcompareComputationTime = true;
    std::unique_ptr<RPSWLComparisonDialog> dlg(new RPSWLComparisonDialog(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        mcompareComputationTime = dlg->compareComputationTime;
        mcompareMemoryUsage = dlg->compareMemoryUsage;
        comparisonCategory = dlg->comparisonCategory;
        comparisonFunction = dlg->comparisonFunction;
        comparisonCandidate = dlg->comparisonCandidate;
        minNumberOfLocation = dlg->minNumberOfLocation;
        minNumberOfFrequency = dlg->minNumberOfFrequency;
        minNumberOfTime = dlg->minNumberOfTime;
        numberOfLocationIncrement = dlg->numberOfLocationIncrement;
        numberOfFrequencyIncrement = dlg->numberOfFrequencyIncrement;
        numberOfTimeIncrement = dlg->numberOfTimeIncrement;
        totalNumber = dlg->totalNumber;
        resultOutputType = dlg->resultOutputType;

        GetWindLabData().comparisonType = 2;

        coherence_ = dlg->coherence;
        correlation_ = dlg->correlation;
        frequency_ = dlg->frequency;
        mean_ = dlg->mean;
        modulation_ = dlg->modulation;
        decomposition_ = dlg->decomposition;
        simulation_ = dlg->simulation;
        spatial_ = dlg->spatial;
        randomness_ = dlg->randomness;
        spectrum_ = dlg->spectrum;
        cumulativeProbabilityDistribution_ = dlg->cumulativeProbabilityDistribution;
        gustFactor_ = dlg->gustFactor;
        kurtosis_ = dlg->kurtosis;
        peakFactor_ = dlg->peakFactor;
        probabilityDensityFunction_ = dlg->probabilityDensityFunction;
        roughness_ = dlg->roughness;
        shearVelocityOfFlow_ = dlg->shearVelocityOfFlow;
        skewness_ = dlg->skewness;
        standardDeviation_ = dlg->standardDeviation;
        turbulenceIntensity_ = dlg->turbulenceIntensity;
        turbulenceScale_ = dlg->turbulenceScale;
        variance_ = dlg->variance;
        wavePassageEffect_ = dlg->wavePassageEffect;
    }
}
void RPSWindLabSimulation::compareMemoryUsage()
{
    mcompareMemoryUsage = true;
    std::unique_ptr<RPSWLComparisonDialog> dlg(new RPSWLComparisonDialog(this));
    if (dlg->exec() == QDialog::Accepted)
    {
        mcompareComputationTime = dlg->compareComputationTime;
        mcompareMemoryUsage = dlg->compareMemoryUsage;
        comparisonCategory = dlg->comparisonCategory;
        comparisonFunction = dlg->comparisonFunction;
        comparisonCandidate = dlg->comparisonCandidate;
        minNumberOfLocation = dlg->minNumberOfLocation;
        minNumberOfFrequency = dlg->minNumberOfFrequency;
        minNumberOfTime = dlg->minNumberOfTime;
        numberOfLocationIncrement = dlg->numberOfLocationIncrement;
        numberOfFrequencyIncrement = dlg->numberOfFrequencyIncrement;
        numberOfTimeIncrement = dlg->numberOfTimeIncrement;
        totalNumber = dlg->totalNumber;
        resultOutputType = dlg->resultOutputType;

        GetWindLabData().comparisonType = 3;

        coherence_ = dlg->coherence;
        correlation_ = dlg->correlation;
        frequency_ = dlg->frequency;
        mean_ = dlg->mean;
        modulation_ = dlg->modulation;
        decomposition_ = dlg->decomposition;
        simulation_ = dlg->simulation;
        spatial_ = dlg->spatial;
        randomness_ = dlg->randomness;
        spectrum_ = dlg->spectrum;
        cumulativeProbabilityDistribution_ = dlg->cumulativeProbabilityDistribution;
        gustFactor_ = dlg->gustFactor;
        kurtosis_ = dlg->kurtosis;
        peakFactor_ = dlg->peakFactor;
        probabilityDensityFunction_ = dlg->probabilityDensityFunction;
        roughness_ = dlg->roughness;
        shearVelocityOfFlow_ = dlg->shearVelocityOfFlow;
        skewness_ = dlg->skewness;
        standardDeviation_ = dlg->standardDeviation;
        turbulenceIntensity_ = dlg->turbulenceIntensity;
        turbulenceScale_ = dlg->turbulenceScale;
        variance_ = dlg->variance;
        wavePassageEffect_ = dlg->wavePassageEffect;
    }
}

void RPSWindLabSimulation::comparisonInitial()
{
    int index = 0;
    categories.append(LabRPS::objGroupCoherenceFunction);
    categories.append(LabRPS::objGroupCorrelationFunction);
    categories.append(LabRPS::objGroupFrequencyDistribution);
    categories.append(LabRPS::objGroupMeanWindProfile);
    categories.append(LabRPS::objGroupModulationFunction);
    categories.append(LabRPS::objGroupSpectrumDecompositionMethod);
    categories.append(LabRPS::objGroupSimulationMethod);
    categories.append(LabRPS::objGroupAlongWindSpectrum);
    categories.append(LabRPS::objGroupAcrossWindSpectrum);
    categories.append(LabRPS::objGroupVerticalWindSpectrum);

    categories.append(LabRPS::objGroupCumulativeProbabilityDistribution);
    categories.append(LabRPS::objGroupGustFactor);
    categories.append(LabRPS::objGroupKurtosis);
    categories.append(LabRPS::objGroupPeakFactor);
    categories.append(LabRPS::objGroupProbabilityDensityFunction);
    categories.append(LabRPS::objGroupRoughness);
    categories.append(LabRPS::objGroupShearVelocityOfFlow);
    categories.append(LabRPS::objGroupSkewness);
    categories.append(LabRPS::objGroupStandardDeviation);
    categories.append(LabRPS::objGroupTurbulenceIntensity);
    categories.append(LabRPS::objGroupTurbulenceScale);
    categories.append(LabRPS::objGroupVariance);
    categories.append(LabRPS::objGroupWavePassageEffect);


    functions.append(LabRPS::ComputeCrossCoherenceVectorF);
    functions.append(LabRPS::ComputeCrossCoherenceVectorT);
    categoryFunctionListMap[categories.at(0)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeCrossCorrelationVectorT);
    categoryFunctionListMap[categories.at(1)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeFrequenciesVectorF);
    categoryFunctionListMap[categories.at(2)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeMeanWindSpeedVectorP);
    functions.append(LabRPS::ComputeMeanWindSpeedVectorT);
    categoryFunctionListMap[categories.at(3)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeModulationVectorT);
    functions.append(LabRPS::ComputeModulationVectorP);
    categoryFunctionListMap[categories.at(4)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeDecomposedCrossSpectrumVectorF);
    functions.append(LabRPS::ComputeDecomposedCrossSpectrumVectorT);
    categoryFunctionListMap[categories.at(5)] = functions;
    functions.clear();

    functions.append(LabRPS::Simulate);
    functions.append(LabRPS::SimulateInLargeScaleMode);
    categoryFunctionListMap[categories.at(6)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeXAutoSpectrumVectorF);
    functions.append(LabRPS::ComputeXAutoSpectrumVectorT);
    categoryFunctionListMap[categories.at(7)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeYAutoSpectrumVectorF);
    functions.append(LabRPS::ComputeYAutoSpectrumVectorT);
    categoryFunctionListMap[categories.at(8)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeZAutoSpectrumVectorF);
    functions.append(LabRPS::ComputeZAutoSpectrumVectorT);
    categoryFunctionListMap[categories.at(9)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeCDFVectorP);
    categoryFunctionListMap[categories.at(10)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeGustFactorVectorP);
    functions.append(LabRPS::ComputeGustFactorVectorT);
    categoryFunctionListMap[categories.at(11)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeKurtosisVectorP);
    functions.append(LabRPS::ComputeKurtosisVectorT);
    categoryFunctionListMap[categories.at(12)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputePeakFactorVectorP);
    functions.append(LabRPS::ComputePeakFactorVectorT);
    categoryFunctionListMap[categories.at(13)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputePDFVectorP);
    categoryFunctionListMap[categories.at(14)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeRoughnessVectorP);
    functions.append(LabRPS::ComputeRoughnessVectorT);
    categoryFunctionListMap[categories.at(15)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeShearVelocityOfFlowVectorP);
    functions.append(LabRPS::ComputeShearVelocityOfFlowVectorT);
    categoryFunctionListMap[categories.at(16)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeSkewnessVectorP);
    functions.append(LabRPS::ComputeSkewnessVectorT);
    categoryFunctionListMap[categories.at(17)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeStandardDeviationVectorP);
    functions.append(LabRPS::ComputeStandardDeviationVectorT);
    categoryFunctionListMap[categories.at(18)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeTurbulenceIntensityVectorP);
    functions.append(LabRPS::ComputeTurbulenceIntensityVectorT);
    categoryFunctionListMap[categories.at(19)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeTurbulenceScaleVectorT);
    functions.append(LabRPS::ComputeTurbulenceScaleVectorP);
    categoryFunctionListMap[categories.at(20)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeVarianceVectorP);
    functions.append(LabRPS::ComputeVarianceVectorT);
    categoryFunctionListMap[categories.at(21)] = functions;
    functions.clear();

    functions.append(LabRPS::ComputeWavePassageEffectVectorF);
    functions.append(LabRPS::ComputeWavePassageEffectVectorT);
    categoryFunctionListMap[categories.at(22)] = functions;
    functions.clear();


    comparisonCategory = categories.at(6);
    comparisonFunction = categoryFunctionListMap[comparisonCategory].at(0);
    comparisonCandidate = "";
    minNumberOfLocation = GetWindLabData().numberOfSpatialPosition;
    minNumberOfFrequency = GetWindLabData().numberOfFrequency;
    minNumberOfTime = GetWindLabData().numberOfTimeIncrements;
    numberOfLocationIncrement = 0;
    numberOfFrequencyIncrement = 0;
    numberOfTimeIncrement = 0;
    totalNumber = 3;
    resultOutputType = 1;
}

QStringList RPSWindLabSimulation::FindAllSpatialDistribution()
{
    QStringList theList;
    /////******coherence model start*******/////////
    typedef IrpsWLLocationDistribution *(*CreateLocDistrCallback)();
    std::map<const QString, CreateLocDistrCallback>::iterator locIt;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (locIt = CrpsLocationDistributionFactory::GetObjectNamesMap().begin(); locIt != CrpsLocationDistributionFactory::GetObjectNamesMap().end(); ++locIt)
    {
        // Add it to the combo box
        theList.append(locIt->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllRandomnessProvider()
{
    QStringList theList;
    /////******coherence model start*******/////////
    typedef IrpsWLRandomness *(*CreateRandomnessCallback)();
    std::map<const QString, CreateRandomnessCallback>::iterator randIt;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (randIt = CrpsRandomnessFactory::GetObjectNamesMap().begin(); randIt != CrpsRandomnessFactory::GetObjectNamesMap().end(); ++randIt)
    {
        // Add it to the combo box
        theList.append(randIt->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllCoherenceFunction()
{
    QStringList theList;
    /////******coherence model start*******/////////
    typedef IrpsWLCoherence *(*CreateCoherenceCallback)();
    std::map<const QString, CreateCoherenceCallback>::iterator cohIt;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsCoherenceFactory::GetObjectNamesMap().begin(); cohIt != CrpsCoherenceFactory::GetObjectNamesMap().end(); ++cohIt)
    {
        // Add it to the combo box
        theList.append(cohIt->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllCorrelationFunctions()
{
    QStringList theList;

    /////******correlation model start*******/////////
    typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();
    std::map<const QString, CreateCorrelationCallback>::iterator corrIt;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (corrIt = CrpsCorrelationFactory::GetObjectNamesMap().begin(); corrIt != CrpsCorrelationFactory::GetObjectNamesMap().end(); ++corrIt)
    {
        // Add it to the combo box
        theList.append(corrIt->first);
    }

    return theList;
}
QStringList RPSWindLabSimulation::FindAllFrequencyDistributions()
{
    QStringList theList;

    typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
    std::map<const QString, CreateFrequencyDistributionCallback>::iterator freqDistrIt;

    // Iterate though the map and show all the registed spatial distribution in the combo box
    for (freqDistrIt = CrpsFrequencyDistributionFactory::GetObjectNamesMap().begin(); freqDistrIt != CrpsFrequencyDistributionFactory::GetObjectNamesMap().end(); ++freqDistrIt)
    {
        // Add it to the combo box
        theList.append(freqDistrIt->first);
    }
    return theList;
}
QStringList RPSWindLabSimulation::FindAllMeanWindProfils()
{
    QStringList theList;
    typedef IrpsWLMean *(*CreateMeanCallback)();
    std::map<const QString, CreateMeanCallback>::iterator meanIt;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (meanIt = CrpsMeanFactory::GetObjectNamesMap().begin(); meanIt != CrpsMeanFactory::GetObjectNamesMap().end(); ++meanIt)
    {
        // Add it to the combo box
        theList.append(meanIt->first);
    }

    return theList;
}
QStringList RPSWindLabSimulation::FindAllModulationFunctions()
{
    QStringList theList;
    typedef IrpsWLModulation *(*CreateModulationCallback)();
    std::map<const QString, CreateModulationCallback>::iterator cohIt;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (cohIt = CrpsModulationFactory::GetObjectNamesMap().begin(); cohIt != CrpsModulationFactory::GetObjectNamesMap().end(); ++cohIt)
    {
        // Add it to the combo box
        theList.append(cohIt->first);
    }
    return theList;
}
QStringList RPSWindLabSimulation::FindAllPSDDecompositionMethods()
{
    QStringList theList;
    typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
    std::map<const QString, CreatePSDdecomMethodCallback>::iterator psdDecIt;

    // Iterate though the map and show all the registed spatial distribution in the combo box
    for (psdDecIt = CrpsPSDdecomMethodFactory::GetObjectNamesMap().begin(); psdDecIt != CrpsPSDdecomMethodFactory::GetObjectNamesMap().end(); ++psdDecIt)
    {
        // Add it to the combo box
        theList.append(psdDecIt->first);
    }
    return theList;
}
QStringList RPSWindLabSimulation::FindAllSimulationMethods()
{
    QStringList theList;
    typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();
    std::map<const QString, CreateSimuMethodCallback>::iterator simuMethIt;

    // Iterate though the map and show all the registed randomness providers in the combo box
    for (simuMethIt = CrpsSimuMethodFactory::GetObjectNamesMap().begin(); simuMethIt != CrpsSimuMethodFactory::GetObjectNamesMap().end(); ++simuMethIt)
    {
        // Add it to the combo box
        theList.append(simuMethIt->first);
    }
    return theList;
}

QStringList RPSWindLabSimulation::FindAllSpectrumModels()
{
    QStringList theList;
    if (1 == GetWindLabData().direction)
    {
        /////******spectrum model start*******/////////
        typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();
        std::map<const QString, CreateXSpectrumCallback>::iterator psdIt;

        // Iterate though the map and show all the registed spectrum models in the combo box
        for (psdIt = CrpsXSpectrumFactory::GetObjectNamesMap().begin(); psdIt != CrpsXSpectrumFactory::GetObjectNamesMap().end(); ++psdIt)
        {
            // Add it to the combo box
            theList.append(psdIt->first);
        }
    }
    else if (2 == GetWindLabData().direction)
    {
        /////******spectrum model start*******/////////
        typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();
        std::map<const QString, CreateYSpectrumCallback>::iterator psdIt;

        // Iterate though the map and show all the registed spectrum models in the combo box
        for (psdIt = CrpsYSpectrumFactory::GetObjectNamesMap().begin(); psdIt != CrpsYSpectrumFactory::GetObjectNamesMap().end(); ++psdIt)
        {
            // Add it to the combo box
            theList.append(psdIt->first);
        }
    }
    else if (3 == GetWindLabData().direction)
    {
        /////******spectrum model start*******/////////
        typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();
        std::map<const QString, CreateZSpectrumCallback>::iterator psdIt;

        // Iterate though the map and show all the registed spectrum models in the combo box
        for (psdIt = CrpsZSpectrumFactory::GetObjectNamesMap().begin(); psdIt != CrpsZSpectrumFactory::GetObjectNamesMap().end(); ++psdIt)
        {
            // Add it to the combo box
            theList.append(psdIt->first);
        }
    }
    return theList;
}

QStringList RPSWindLabSimulation::FindAllCumulativeProbabilityDistribution()
{
    QStringList theList;
    typedef IrpsWLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();
    std::map<const QString, CreateCumulativeProbabilityDistributionCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().begin(); it != CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllGustFactor()
{
    QStringList theList;
    typedef IrpsWLGustFactor *(*CreateGustFactorCallback)();
    std::map<const QString, CreateGustFactorCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsGustFactorFactory::GetObjectNamesMap().begin(); it != CrpsGustFactorFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllKurtosis()
{
    QStringList theList;
    typedef IrpsWLKurtosis *(*CreateKurtosisCallback)();
    std::map<const QString, CreateKurtosisCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsKurtosisFactory::GetObjectNamesMap().begin(); it != CrpsKurtosisFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllPeakFactor()
{
    QStringList theList;
    typedef IrpsWLPeakFactor *(*CreatePeakFactorCallback)();
    std::map<const QString, CreatePeakFactorCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsPeakFactorFactory::GetObjectNamesMap().begin(); it != CrpsPeakFactorFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllProbabilityDensityFunction()
{
    QStringList theList;
    typedef IrpsWLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();
    std::map<const QString, CreateProbabilityDensityFunctionCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().begin(); it != CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllRoughness()
{
    QStringList theList;
    typedef IrpsWLRoughness *(*CreateRoughnessCallback)();
    std::map<const QString, CreateRoughnessCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsRoughnessFactory::GetObjectNamesMap().begin(); it != CrpsRoughnessFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllShearVelocityOfFlow()
{
    QStringList theList;
    typedef IrpsWLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();
    std::map<const QString, CreateShearVelocityOfFlowCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().begin(); it != CrpsShearVelocityOfFlowFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllSkewness()
{
    QStringList theList;
    typedef IrpsWLSkewness *(*CreateSkewnessCallback)();
    std::map<const QString, CreateSkewnessCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsSkewnessFactory::GetObjectNamesMap().begin(); it != CrpsSkewnessFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllStandardDeviation()
{
    QStringList theList;
    typedef IrpsWLStandardDeviation *(*CreateStandardDeviationCallback)();
    std::map<const QString, CreateStandardDeviationCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsStandardDeviationFactory::GetObjectNamesMap().begin(); it != CrpsStandardDeviationFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllTurbulenceIntensity()
{
    QStringList theList;
    typedef IrpsWLTurbulenceIntensity *(*CreateTurbulenceIntensityCallback)();
    std::map<const QString, CreateTurbulenceIntensityCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsTurbulenceIntensityFactory::GetObjectNamesMap().begin(); it != CrpsTurbulenceIntensityFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllTurbulenceScale()
{
    QStringList theList;
    typedef IrpsWLTurbulenceScale *(*CreateTurbulenceScaleCallback)();
    std::map<const QString, CreateTurbulenceScaleCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsTurbulenceScaleFactory::GetObjectNamesMap().begin(); it != CrpsTurbulenceScaleFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllVariance()
{
    QStringList theList;
    typedef IrpsWLVariance *(*CreateVarianceCallback)();
    std::map<const QString, CreateVarianceCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsVarianceFactory::GetObjectNamesMap().begin(); it != CrpsVarianceFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}

QStringList RPSWindLabSimulation::FindAllWavePassageEffect()
{
    QStringList theList;
    typedef IrpsWLWavePassageEffect *(*CreateWavePassageEffectCallback)();
    std::map<const QString, CreateWavePassageEffectCallback>::iterator it;

    // Iterate though the map and show all the registed spectrum models in the combo box
    for (it = CrpsWavePassageEffectFactory::GetObjectNamesMap().begin(); it != CrpsWavePassageEffectFactory::GetObjectNamesMap().end(); ++it)
    {
        // Add it to the combo box
        theList.append(it->first);
    }

    return theList;
}


void RPSWindLabSimulation::fillCategoryComboBox(QComboBox *categoryComboBox)
{
    categoryComboBox->addItems(categories);
    categoryComboBox->setCurrentText(comparisonCategory);
}

void RPSWindLabSimulation::fillFunctionAndCandidateComboBoxes(QString category, QComboBox *functionComboBox, QComboBox *candidatesComboBox)
{
    functionComboBox->clear();
    candidatesComboBox->clear();

    switch (categories.indexOf(category))
    {
    case 0:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(0)]);
        candidatesComboBox->addItems(FindAllCoherenceFunction());
        break;
    case 1:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(1)]);
        candidatesComboBox->addItems(FindAllCorrelationFunctions());
        break;
    case 2:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(2)]);
        candidatesComboBox->addItems(FindAllFrequencyDistributions());
        break;
    case 3:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(3)]);
        candidatesComboBox->addItems(FindAllMeanWindProfils());
        break;
    case 4:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(4)]);
        candidatesComboBox->addItems(FindAllModulationFunctions());
        break;
    case 5:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(5)]);
        candidatesComboBox->addItems(FindAllPSDDecompositionMethods());
        break;
    case 6:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(6)]);
        candidatesComboBox->addItems(FindAllSimulationMethods());
        break;
    case 7:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(7)]);
        if (1 != GetWindLabData().direction)
        {
            break;
        }
        candidatesComboBox->addItems(FindAllSpectrumModels());
        break;
    case 8:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(8)]);
        if (2 != GetWindLabData().direction)
        {
            break;
        }
        candidatesComboBox->addItems(FindAllSpectrumModels());
        break;
    case 9:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(9)]);
        if (3 != GetWindLabData().direction)
        {
            break;
        }
        candidatesComboBox->addItems(FindAllSpectrumModels());
        break;
    case 10:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(10)]);
        candidatesComboBox->addItems(FindAllCumulativeProbabilityDistribution());
        break;
    case 11:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(11)]);
        candidatesComboBox->addItems(FindAllGustFactor());
        break;
    case 12:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(12)]);
        candidatesComboBox->addItems(FindAllKurtosis());
        break;
    case 13:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(13)]);
        candidatesComboBox->addItems(FindAllPeakFactor());
        break;
    case 14:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(14)]);
        candidatesComboBox->addItems(FindAllProbabilityDensityFunction());
        break;
    case 15:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(15)]);
        candidatesComboBox->addItems(FindAllRoughness());
        break;
    case 16:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(16)]);
        candidatesComboBox->addItems(FindAllShearVelocityOfFlow());
        break;
    case 17:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(17)]);
        candidatesComboBox->addItems(FindAllSkewness());
        break;
    case 18:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(18)]);
        candidatesComboBox->addItems(FindAllStandardDeviation());
        break;
    case 19:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(19)]);
        candidatesComboBox->addItems(FindAllTurbulenceIntensity());
        break;
    case 20:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(20)]);
        candidatesComboBox->addItems(FindAllTurbulenceScale());
        break;
    case 21:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(21)]);
        candidatesComboBox->addItems(FindAllVariance());
        break;
    case 22:
        functionComboBox->addItems(categoryFunctionListMap[categories.at(22)]);
        candidatesComboBox->addItems(FindAllWavePassageEffect());
        break;
    default:
        qWarning("Unknown comparison category");
        break;
    }

    functionComboBox->setCurrentText(comparisonFunction);
    candidatesComboBox->setCurrentText(comparisonCandidate);
}

void RPSWindLabSimulation::CoherenceFunctionInital(QString currentSelected)
{
    // Build an object
    IrpsWLCoherence *currentSelection = CrpsCoherenceFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}
void RPSWindLabSimulation::correlationFunctionInital(QString currentSelected)
{
    // Build an object
    IrpsWLCorrelation *currentSelection = CrpsCorrelationFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}
void RPSWindLabSimulation::locationDistributionFunctionInital(QString currentSelected)
{
    // Build an object
    IrpsWLLocationDistribution *currentSelection = CrpsLocationDistributionFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}
void RPSWindLabSimulation::frequencyDistributionInital(QString currentSelected)
{
    // Build an object
    IrpsWLFrequencyDistribution *currentSelection = CrpsFrequencyDistributionFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}
void RPSWindLabSimulation::meanWindProfilInital(QString currentSelected)
{
    // Build an object
    IrpsWLMean *currentSelection = CrpsMeanFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}
void RPSWindLabSimulation::modulationFunctionInital(QString currentSelected)
{
    // Build an object
    IrpsWLModulation *currentSelection = CrpsModulationFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}
void RPSWindLabSimulation::psdDecompositionMethodInital(QString currentSelected)
{
    // Build an object
    IrpsWLPSDdecompositionMethod *currentSelection = CrpsPSDdecomMethodFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}
void RPSWindLabSimulation::simulationMethodInital(QString currentSelected)
{
    // Build an object
    IrpsWLSimuMethod *currentRndProvider = CrpsSimuMethodFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentRndProvider)
    {
        return;
    }

    // Apply iniatial setting
    currentRndProvider->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentRndProvider;
}
void RPSWindLabSimulation::spectrumModelInital(QString currentSelected)
{
    if (1 == GetWindLabData().direction)
    {

        // Build an object
        IrpsWLXSpectrum *currentSelection = CrpsXSpectrumFactory::BuildObject(currentSelected);

        // Check whether good object
        if (NULL == currentSelection)
        {
            return;
        }

        // Apply iniatial setting
        currentSelection->OnInitialSetting(GetWindLabData(), information);

        // Delete the object
        delete currentSelection;
    }
    else if (2 == GetWindLabData().direction)
    {

        // Build an object
        IrpsWLYSpectrum *currentSelection = CrpsYSpectrumFactory::BuildObject(currentSelected);

        // Check whether good object
        if (NULL == currentSelection)
        {
            return;
        }

        // Apply iniatial setting
        currentSelection->OnInitialSetting(GetWindLabData(), information);

        // Delete the object
        delete currentSelection;
    }
    else if (3 == GetWindLabData().direction)
    {

        // Build an object
        IrpsWLZSpectrum *currentSelection = CrpsZSpectrumFactory::BuildObject(currentSelected);

        // Check whether good object
        if (NULL == currentSelection)
        {
            return;
        }
        // Apply iniatial setting
        currentSelection->OnInitialSetting(GetWindLabData(), information);

        // Delete the object
        delete currentSelection;
    }
}

void RPSWindLabSimulation::randomnessProviderInital(QString currentSelected)
{
    // Build an object
    IrpsWLRandomness *currentRndProvider = CrpsRandomnessFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentRndProvider)
    {
        return;
    }

    // Apply iniatial setting
    currentRndProvider->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentRndProvider;
}

void RPSWindLabSimulation::matrixToolInital(QString currentSelected)
{
    // Build an object
    IrpsWLMatrixTool *currentMatrixTool = CrpsMatrixToolFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentMatrixTool)
    {
        return;
    }

    // Apply iniatial setting
    currentMatrixTool->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentMatrixTool;
}

void RPSWindLabSimulation::tableToolInital(QString currentSelected)
{
    // Build an object
    IrpsWLTableTool *currentTableTool = CrpsTableToolFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentTableTool)
    {
        return;
    }

    // Apply iniatial setting
    currentTableTool->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentTableTool;
}

void RPSWindLabSimulation::CumulativeProbabilityDistributionInital(QString currentSelected)
{
    // Build an object
    IrpsWLCumulativeProbabilityDistribution *currentSelection = CrpsCumulativeProbabilityDistributionFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::GustFactorInital(QString currentSelected)
{
    // Build an object
    IrpsWLGustFactor *currentSelection = CrpsGustFactorFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::KurtosisInital(QString currentSelected)
{
    // Build an object
    IrpsWLKurtosis *currentSelection = CrpsKurtosisFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::PeakFactorInital(QString currentSelected)
{
    // Build an object
    IrpsWLPeakFactor *currentSelection = CrpsPeakFactorFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::ProbabilityDensityFunctionInital(QString currentSelected)
{
    // Build an object
    IrpsWLProbabilityDensityFunction *currentSelection = CrpsProbabilityDensityFunctionFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::RoughnessInital(QString currentSelected)
{
    // Build an object
    IrpsWLRoughness *currentSelection = CrpsRoughnessFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::ShearVelocityOfFlowInital(QString currentSelected)
{
    // Build an object
    IrpsWLShearVelocityOfFlow *currentSelection = CrpsShearVelocityOfFlowFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::SkewnessInital(QString currentSelected)
{
    // Build an object
    IrpsWLSkewness *currentSelection = CrpsSkewnessFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::StandardDeviationInital(QString currentSelected)
{
    // Build an object
    IrpsWLStandardDeviation *currentSelection = CrpsStandardDeviationFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::TurbulenceIntensityInital(QString currentSelected)
{
    // Build an object
    IrpsWLTurbulenceIntensity *currentSelection = CrpsTurbulenceIntensityFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::TurbulenceScaleInital(QString currentSelected)
{
    // Build an object
    IrpsWLTurbulenceScale *currentSelection = CrpsTurbulenceScaleFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::VarianceInital(QString currentSelected)
{
    // Build an object
    IrpsWLVariance *currentSelection = CrpsVarianceFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}

void RPSWindLabSimulation::WavePassageEffectInital(QString currentSelected)
{
    // Build an object
    IrpsWLWavePassageEffect *currentSelection = CrpsWavePassageEffectFactory::BuildObject(currentSelected);

    // Check whether good object
    if (NULL == currentSelection)
    {
        return;
    }

    // Apply iniatial setting
    currentSelection->OnInitialSetting(GetWindLabData(), information);

    // Delete the object
    delete currentSelection;
}


void RPSWindLabSimulation::candidateInitialData(QString category, QString currentSelected)
{
    switch (categories.indexOf(category))
    {
    case 0:
        CoherenceFunctionInital(currentSelected);
        break;
    case 1:
        correlationFunctionInital(currentSelected);
        break;
    case 2:
        frequencyDistributionInital(currentSelected);
        break;
    case 3:
        meanWindProfilInital(currentSelected);
        break;
    case 4:
        modulationFunctionInital(currentSelected);
        break;
    case 5:
        psdDecompositionMethodInital(currentSelected);
        break;
    case 6:
        simulationMethodInital(currentSelected);
        break;
    case 7:
        spectrumModelInital(currentSelected);
        break;
    case 8:
        spectrumModelInital(currentSelected);
        break;
    case 9:
        spectrumModelInital(currentSelected);
        break;
    case 10:
        CumulativeProbabilityDistributionInital(currentSelected);
        break;
    case 11:
        GustFactorInital(currentSelected);
        break;
    case 12:
        KurtosisInital(currentSelected);
        break;
    case 13:
        PeakFactorInital(currentSelected);
        break;
    case 14:
        ProbabilityDensityFunctionInital(currentSelected);
        break;
    case 15:
        RoughnessInital(currentSelected);
        break;
    case 16:
        ShearVelocityOfFlowInital(currentSelected);
        break;
    case 17:
        SkewnessInital(currentSelected);
        break;
    case 18:
        StandardDeviationInital(currentSelected);
        break;
    case 19:
        TurbulenceIntensityInital(currentSelected);
        break;
    case 20:
        TurbulenceScaleInital(currentSelected);
        break;
    case 21:
        VarianceInital(currentSelected);
        break;
    case 22:
        WavePassageEffectInital(currentSelected);
        break;
    default:
        qWarning("Unknown comparison category");
        break;
    }
}


void RPSWindLabSimulation::receiveInformation(QStringList infoList)
{
    emit sendInformation(infoList);
}

void RPSWindLabSimulation::progressBarShowSL()
{
    emit progressBarShow();
}
void RPSWindLabSimulation::progressBarHideSL()
{
    emit progressBarHide();
    qApp->processEvents();
}
void RPSWindLabSimulation::progressBarSetValueSL(int value)
{
    // QMessageBox::warning(0, "1", "in setvalue");
    emit progressBarSetValue(value);
}
void RPSWindLabSimulation::progressBarSetMinSL(int value)
{
    emit progressBarSetMin(value);
}
void RPSWindLabSimulation::progressBarSetMaxSL(int value)
{
    // QMessageBox::warning(0, "1", "in set max");
    emit progressBarSetMax(value);
}

void RPSWindLabSimulation::progressBarResetSL()
{
    // QMessageBox::warning(0, "1", "in reset");
    emit progressBarReset();
}
void RPSWindLabSimulation::fillLocationJComboBox(QComboBox *locationJComboBox)
{
    int count = GetWindLabData().numberOfSpatialPosition;
    int limit = 0;

    QSettings settings;
    settings.beginGroup("General");
    limit = settings.value("ComboBoxItemsCountLimit", 6144).toInt();
    settings.endGroup();

    if(count > limit)
    {
        count = limit;
    }

    locationJComboBox->clear();

    locationJComboBox->addItem("None");

    for (int i = 0; i < count; i++)
    {
        locationJComboBox->addItem(QString::number(i + 1));
    }
    locationJComboBox->addItem("All");
}
void RPSWindLabSimulation::fillLocationKComboBox(QComboBox *locationKComboBox)
{
    fillLocationJComboBox(locationKComboBox);
}
void RPSWindLabSimulation::fillFrequencyComboBox(QComboBox *frequencyComboBox)
{
    int count = GetWindLabData().numberOfFrequency;
    int limit = 0;

    QSettings settings;
    settings.beginGroup("General");
    limit = settings.value("ComboBoxItemsCountLimit", 6144).toInt();
    settings.endGroup();

    if(count > limit)
    {
        count = limit;
    }

    frequencyComboBox->clear();

    frequencyComboBox->addItem("None");
    for (int i = 0; i < count; i++)
    {
        frequencyComboBox->addItem(QString::number(i + 1));
    }
    frequencyComboBox->addItem("All");
}
void RPSWindLabSimulation::fillTimeComboBox(QComboBox *timeComboBox)
{
    int count = GetWindLabData().numberOfTimeIncrements;
    int limit = 0;

    QSettings settings;
    settings.beginGroup("General");
    limit = settings.value("ComboBoxItemsCountLimit", 6144).toInt();
    settings.endGroup();

    if(count > limit)
    {
        count = limit;
    }

    timeComboBox->clear();

    timeComboBox->addItem("None");
    for (int i = 0; i < count; i++)
    {
        timeComboBox->addItem(QString::number(i + 1));
    }
    timeComboBox->addItem("All");
}

void RPSWindLabSimulation::locJCurrentIndexChanged(int index)
{
    locationJ = index;

    if (0 == index || GetWindLabData().numberOfSpatialPosition + 1 == index)
    {
        GetWindLabData().locationJ = 0;
    }
    else if (index > 0 &&
             index <= GetWindLabData().numberOfSpatialPosition)
    {
        GetWindLabData().locationJ = index - 1;
    }
}
void RPSWindLabSimulation::locKCurrentIndexChanged(int index)
{
    locationK = index;

    if (0 == index || GetWindLabData().numberOfSpatialPosition + 1 == index)
    {
        GetWindLabData().locationK = 0;
    }
    else if (index > 0 &&
             index <= GetWindLabData().numberOfSpatialPosition)
    {
        GetWindLabData().locationK = index - 1;
    }
}
void RPSWindLabSimulation::freqCurrentIndexChanged(int index)
{
    frequencyIndex = index;

    if (0 == index || GetWindLabData().numberOfFrequency + 1 == index)
    {
        GetWindLabData().frequencyIndex = 0;
    }
    else if (index > 0 &&
             index <= GetWindLabData().numberOfFrequency)
    {
        GetWindLabData().frequencyIndex = index - 1;
    }
}
void RPSWindLabSimulation::timCurrentIndexChanged(int index)
{
    timeIndex = index;

    if (0 == index || GetWindLabData().numberOfTimeIncrements + 1 == index)
    {
        GetWindLabData().timeIndex = 0;
    }
    else if (index > 0 &&
             index <= GetWindLabData().numberOfTimeIncrements)
    {
        GetWindLabData().timeIndex = index - 1;
    }
}

//void RPSWindLabSimulation::displayLocationDistribution()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the spectrum results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    QTime t;
//    t.start();

//    // prepare the name of the table
//    QString arrayName = "Locations";

//    // allocate memory for the table
//    Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 3);

//    // fill the table with computed coherence
//    for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
//    {
//        table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, 0));
//        table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, 1));
//        table->setCellValue(i, 2, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, 2));
//    }

//    table->showNormal();
//    information.append(tr("The computed spatial distribution took %1 ms to be displayed").arg(QString::number(t.elapsed())));

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

//void RPSWindLabSimulation::displayMeanWindVelocity()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the spectrum results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
//            locationK == 0 &&
//            frequencyIndex == 0 &&
//            timeIndex > 0 &&
//            timeIndex <= GetWindLabData().numberOfTimeIncrements)
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = tr("Mean (All, None, None, %1)").arg(timeIndex);

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
//        {
//            table->setCellValue(i, 0, i + 1);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();
//        information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else if (locationJ > 0 &&
//             locationJ <= GetWindLabData().numberOfSpatialPosition &&
//             locationK == 0 &&
//             frequencyIndex == 0 &&
//             timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = tr("Mean (%1, None, None, All)").arg(locationJ);

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

//        double timeInr = 0.0;

//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
//        {
//            timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
//            table->setCellValue(i, 0, timeInr);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();
//        information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
//             locationK == 0 &&
//             frequencyIndex == 0 &&
//             timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = "Mean (All, None, None, All)";

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition);

//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
//        {
//            for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
//            {
//                table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
//            }
//        }

//        table->showNormal();

//        information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = tr("Mean (All, None, None, %1)").arg(timeIndex);

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfSpatialPosition, 2);

//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
//        {
//            table->setCellValue(i, 0, i + 1);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();
//        information.append(tr("The computed mean wind velocities took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

//void RPSWindLabSimulation::displayRandomPhase()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the frequency results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
//            locationK == 0 &&
//            frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
//            timeIndex == 0)
//    {

//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = "RandomPhase (All, None, All, None)";

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
//        {
//            for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
//            {
//                table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
//            }
//        }
//        table->showNormal();
//        information.append(tr("The computed random phases took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = "RandomPhase (All, None, All, None)";

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, GetWindLabData().numberOfSpatialPosition);

//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
//        {
//            for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
//            {
//                table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
//            }
//        }
//        table->showNormal();
//        information.append(tr("The computed random phases took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

void RPSWindLabSimulation::displayOutputResults()
{

    if(1 == GetWindLabSimulationOutputWorker()->workerOutputType)
    {
        displayOutputVectorResults();
    }
    else if(2 == GetWindLabSimulationOutputWorker()->workerOutputType)
    {
        displayOutputMatrixResults();
    }
    else if(3 == GetWindLabSimulationOutputWorker()->workerOutputType)
    {
        displayOutputMatrix2Results();
    }
}

void RPSWindLabSimulation::displayOutputVectorResults()
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    information = information + GetWindLabSimulationOutputWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the spectrum results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    QTime t;
    t.start();

    // prepare the name of the table
    QString arrayName = GetWindLabSimulationOutputWorker()->tableName;

    const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));


    // allocate memory for the table
    Table *table = app->newTable(arrayName, rws, 2);

    // fill the table with computed coherence
    for (int i = 0; i < rws; i++)
    {
        table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
        table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
    }

    table->showNormal();

    // Either this if you use UTF-8 anywhere
    std::string strTitle = GetWindLabSimulationOutputWorker()->plotTitle.toUtf8().constData();
    std::string strxlabel = GetWindLabSimulationOutputWorker()->plotxlable.toUtf8().constData();
    std::string strylabel = GetWindLabSimulationOutputWorker()->plotylabel.toUtf8().constData();

    std::string_view Title = strTitle;
    std::string_view Xlabel = strxlabel;
    std::string_view Ylabel = strylabel;


    using namespace matplot;
    auto f = figure(true);
    plot(GetWindLabSimulationOutputWorker()->m_ResultVector2,GetWindLabSimulationOutputWorker()->m_ResultVector)->line_width(2);
    xlabel(Xlabel);
    ylabel(Ylabel);
    title(Title);
    f->draw();

    QApplication::restoreOverrideCursor();

    information.append(tr("The results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayOutputMatrixResults()
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    information = information + GetWindLabSimulationOutputWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the spectrum results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    QTime t;
    t.start();

    // prepare the name of the table
    QString arrayName = GetWindLabSimulationOutputWorker()->tableName;

    const int rws = GetWindLabSimulationOutputWorker()->m_ResultMatrix.rows();
    const int cls = GetWindLabSimulationOutputWorker()->m_ResultMatrix.cols();

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    // allocate memory for the table
    Table *table = app->newTable(arrayName, rws, cls);

    // fill the table with computed coherence
    for (int i = 0; i < rws; i++)
    {
        for (int j = 0; j < cls; j++)
        {
            table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i,j));
        }
    }


    table->showNormal();

    // Either this if you use UTF-8 anywhere
    std::string strTitle = GetWindLabSimulationOutputWorker()->plotTitle.toUtf8().constData();
    std::string strxlabel = GetWindLabSimulationOutputWorker()->plotxlable.toUtf8().constData();
    std::string strylabel = GetWindLabSimulationOutputWorker()->plotylabel.toUtf8().constData();

    std::string_view Title = strTitle;
    std::string_view Xlabel = strxlabel;
    std::string_view Ylabel = strylabel;

    vec colAt = GetWindLabSimulationOutputWorker()->m_ResultMatrix.col(GetWindLabData().locationJ);

    using namespace matplot;
    auto f = figure(true);
    plot(colAt)->line_width(2);
    xlabel(Xlabel);
    ylabel(Ylabel);
    title(Title);
    f->draw();

    QApplication::restoreOverrideCursor();

    information.append(tr("The results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayOutputMatrix2Results()
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    information = information + GetWindLabSimulationOutputWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the spectrum results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    QTime t;
    t.start();

    // prepare the name of the table
    QString arrayName = GetWindLabSimulationOutputWorker()->tableName;

    const int rws = GetWindLabSimulationOutputWorker()->m_ResultMatrix2.rows();
    const int cls = GetWindLabSimulationOutputWorker()->m_ResultMatrix2.cols();

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    // allocate memory for the table
    Table *table = app->newTable(arrayName, rws, cls);


    // fill the table with computed coherence
    for (int i = 0; i < rws; i++)
    {
        for (int j = 0; j < cls; j++)
        {
            table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix2(i,j));
        }
    }

    table->showNormal();

    // Either this if you use UTF-8 anywhere
    std::string strTitle = GetWindLabSimulationOutputWorker()->plotTitle.toUtf8().constData();
    std::string strxlabel = GetWindLabSimulationOutputWorker()->plotxlable.toUtf8().constData();
    std::string strylabel = GetWindLabSimulationOutputWorker()->plotylabel.toUtf8().constData();

    std::string_view Title = strTitle;
    std::string_view Xlabel = strxlabel;
    std::string_view Ylabel = strylabel;

    vec colAt = GetWindLabSimulationOutputWorker()->m_ResultMatrix2.col(GetWindLabData().locationJ);

    using namespace matplot;
    auto f = figure(true);
    plot(colAt)->line_width(2);
    xlabel(Xlabel);
    ylabel(Ylabel);
    title(Title);
    f->draw();

    QApplication::restoreOverrideCursor();

    information.append(tr("The results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabSimulationOutputWorker()->finished();
}

void RPSWindLabSimulation::displayAComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    app->updateLog(logAccuracyComparisonInfo(GetWindLabComparisonWorker()->isComparisonSuccessful, "Your Comparison"));

    information = information + GetWindLabComparisonWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the comparison results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    QTime t;
    t.start();

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    // allocate memory for the table
    Table *table = app->newTable(tableName, row, 4);
    table->setColName(0, variableName +" 1");
    table->setColName(1, candidat1);
    table->setColName(2, variableName +" 2");
    table->setColName(3, candidat2);

    // fill the table with computed coherence
    for (int i = 0; i < row; i++)
    {
        table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate1Variable(i));
        table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate1(i));
        table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate2Variable(i));
        table->setCellValue(i, 3, GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate2(i));
    }

    table->showNormal();
    information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // Either this if you use UTF-8 anywhere
    std::string strTitle = tableName.toUtf8().constData();
    std::string strxlabel = variableName.toUtf8().constData();
    std::string strylabel = tableName.toUtf8().constData();
    std::string strcandidat1 = candidat1.toUtf8().constData();
    std::string strcandidat2 = candidat2.toUtf8().constData();


    std::string_view Title = strTitle;
    std::string_view Xlabel = strxlabel;
    std::string_view Ylabel = strylabel;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    using namespace matplot;
    auto f = figure(true);
    auto p1 = plot(GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate1Variable, GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate1);

    hold(on);
    auto p2 = plot(GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate2Variable, GetWindLabComparisonWorker()->m_resultValueResultVectorCandidate2);

    auto lgd1 = matplot::legend({p1, p2}, {strcandidat1, strcandidat2});

    lgd1->box(false);
    p1->line_width(2);
    p2->line_width(2);
    xlabel(Xlabel);
    ylabel(Ylabel);
    title(Title);
    f->draw();

    QApplication::restoreOverrideCursor();

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayWindVelocityASimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    app->updateLog(logAccuracyComparisonInfo(GetWindLabComparisonWorker()->isComparisonSuccessful, "Your Comparison"));


    information = information + GetWindLabComparisonWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the comparison results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    if (!(locationJ > 0 && locationJ <= GetWindLabData().numberOfSpatialPosition))
    {
        GetWindLabData().locationJ = 0;
        //        emit GetWindLabComparisonWorker()->finished();
        //        return;
    }

    const double rws = GetWindLabComparisonWorker()->m_resultValueMatrixCandidate1.rows();
    const double cls = GetWindLabComparisonWorker()->m_resultValueMatrixCandidate1.cols();

    if (rws != GetWindLabData().numberOfTimeIncrements ||
            cls != GetWindLabData().numberOfSpatialPosition ||
            GetWindLabComparisonWorker()->m_resultValueMatrixCandidate1.size() != GetWindLabComparisonWorker()->m_resultValueMatrixCandidate2.size())
    {
        information.append("Sizes not compatible. Both simulation method  must give results array of same size.");
        emit sendInformation(information);
        information.clear();
        return;
    }

    QTime t;
    t.start();

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    // allocate memory for the table
    Table *table = app->newTable(tableName, row, 3);
    table->setColName(0, " Time");
    table->setColName(1, candidat1);
    table->setColName(2, candidat2);

    std::vector<double> X(rws);
    std::vector<double> Y1(rws);
    std::vector<double> Y2(rws);


    // fill the table with computed coherence
    for (int i = 0; i < rws; i++)
    {
        X[i] = GetWindLabData().minTime + GetWindLabData().timeIncrement*i;
        Y1[i] = GetWindLabComparisonWorker()->m_resultValueMatrixCandidate1(i,GetWindLabData().locationJ);
        Y2[i] = GetWindLabComparisonWorker()->m_resultValueMatrixCandidate2(i,GetWindLabData().locationJ);

        table->setCellValue(i, 0, X[i]);
        table->setCellValue(i, 1, Y1[i]);
        table->setCellValue(i, 2, Y2[i]);
    }

    table->showNormal();
    information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // Either this if you use UTF-8 anywhere
    std::string strTitle = "Simulation Method Accuracy Comparison";
    std::string strxlabel = variableName.toUtf8().constData();
    std::string strylabel = tableName.toUtf8().constData();
    std::string strcandidat1 = candidat1.toUtf8().constData();
    std::string strcandidat2 = candidat2.toUtf8().constData();


    std::string_view Title = strTitle;
    std::string_view Xlabel = strxlabel;
    std::string_view Ylabel = strylabel;

    using namespace matplot;
    auto f = figure(true);
    auto p1 = plot(X, Y1);

    hold(on);
    auto p2 = plot(X, Y2);

    auto lgd1 = matplot::legend({p1, p2}, {strcandidat1, strcandidat2});

    lgd1->box(false);
//    p1->line_width(2);
//    p2->line_width(2);
    xlabel(Xlabel);
    ylabel(Ylabel);
    title(Title);
    f->show();

    QApplication::restoreOverrideCursor();

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayWindVelocityALargeScaleSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    // RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    // ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    // information = information + GetWindLabComparisonWorker()->getInformation();
    // information.append("Please wait. LabRPS is now showing the comparison results...");
    // emit sendInformation(information);
    // emit progressBarHide();

    // qApp->processEvents();
    // information.clear();

    // QTime t;
    // t.start();

    // // allocate memory for the table
    // Table *table = app->newTable(tableName, row, 3);
    // table->setColName(0, variableName);
    // table->setColName(1, candidat1);
    // table->setColName(2, candidat2);

    // // fill the table with computed coherence
    // for (int i = 0; i < row; i++)
    // {
    // 	table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_resultVectorVariable(i));
    // 	table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_resultCandidate1(i, GetWindLabData().locationJ));
    // 	table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_resultCandidate2(i, GetWindLabData().locationJ));
    // }

    // table->showNormal();
    // information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // // send info the main window to show it
    // emit sendInformation(information);

    // // clear the information list
    // information.clear();

    // // delete the worker
    // GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayWindVelocityTSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    app->updateLog(logTimeComparisonInfo(GetWindLabComparisonWorker()->isComparisonSuccessful, "Your Comparison"));

    information = information + GetWindLabComparisonWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the comparison results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    if (!(locationJ > 0 && locationJ <= GetWindLabData().numberOfSpatialPosition))
    {
        GetWindLabData().locationJ = 0;
        //        emit GetWindLabComparisonWorker()->finished();
        //        return;
    }

    QTime t;
    t.start();

    // allocate memory for the table
    Table *table = app->newTable(tableName, row, 5);
    table->setColName(0, "Locations");
    table->setColName(1, "Frequencies");
    table->setColName(2, "Times");
    table->setColName(3, candidat1);
    table->setColName(4, candidat2);

    // fill the table with computed coherence
    for (int i = 0; i < row; i++)
    {
        table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_locationVectorVariable(i));
        table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_frequencyVectorVariable(i));
        table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_timeVectorVariable(i));
        table->setCellValue(i, 3, GetWindLabComparisonWorker()->m_computationTimeResultVectorCandidate1(i));
        table->setCellValue(i, 4, GetWindLabComparisonWorker()->m_computationTimeResultVectorCandidate2(i));
    }

    table->showNormal();
    information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayWindVelocityTLargeScaleSimComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    // RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    // ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    // information = information + GetWindLabComparisonWorker()->getInformation();
    // information.append("Please wait. LabRPS is now showing the comparison results...");
    // emit sendInformation(information);
    // emit progressBarHide();

    // qApp->processEvents();
    // information.clear();

    // QTime t;
    // t.start();

    // // allocate memory for the table
    // Table *table = app->newTable(tableName, row, 3);
    // table->setColName(0, variableName);
    // table->setColName(1, candidat1);
    // table->setColName(2, candidat2);

    // // fill the table with computed coherence
    // for (int i = 0; i < row; i++)
    // {
    // 	table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_resultVectorVariable(i));
    // 	table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_resultCandidate1(i, GetWindLabData().locationJ));
    // 	table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_resultCandidate2(i, GetWindLabData().locationJ));
    // }

    // table->showNormal();
    // information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));

    // // send info the main window to show it
    // emit sendInformation(information);

    // // clear the information list
    // information.clear();

    // // delete the worker
    // GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayTComparisonResults(const QString &candidat1, const QString &candidat2, const QString &tableName, const QString &variableName, const int &row)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    app->updateLog(logTimeComparisonInfo(GetWindLabComparisonWorker()->isComparisonSuccessful, "Your Comparison"));

    information = information + GetWindLabComparisonWorker()->getInformation();
    information.append("Please wait. LabRPS is now showing the comparison results...");
    emit sendInformation(information);
    emit progressBarHide();

    qApp->processEvents();
    information.clear();

    QTime t;
    t.start();

    // allocate memory for the table
    Table *table = app->newTable(tableName, row, 5);
    table->setColName(0, "Locations");
    table->setColName(1, "Frequencies");
    table->setColName(2, "Times");
    table->setColName(3, candidat1);
    table->setColName(4, candidat2);

    // fill the table with computed coherence
    for (int i = 0; i < row; i++)
    {
        table->setCellValue(i, 0, GetWindLabComparisonWorker()->m_locationVectorVariable(i));
        table->setCellValue(i, 1, GetWindLabComparisonWorker()->m_frequencyVectorVariable(i));
        table->setCellValue(i, 2, GetWindLabComparisonWorker()->m_timeVectorVariable(i));
        table->setCellValue(i, 3, GetWindLabComparisonWorker()->m_computationTimeResultVectorCandidate1(i));
        table->setCellValue(i, 4, GetWindLabComparisonWorker()->m_computationTimeResultVectorCandidate2(i));
    }

    table->showNormal();
    information.append(tr("The comparison results took %1 ms to be displayed").arg(QString::number(t.elapsed())));


    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabComparisonWorker()->finished();
}
void RPSWindLabSimulation::displayAccuracyComparisonResults()
{
    int count = candidateList.size();
    QString candidate1 = candidateList[0];
    QString comparisonCategory = candidateList[1];
    QString comparisonFunction = candidateList[2];
    QString coherence1 = candidateList[3];
    QString correlation1 = candidateList[4];
    QString frequency1 = candidateList[5];
    QString mean1 = candidateList[6];
    QString modulation1 = candidateList[7];
    QString decomposition1 = candidateList[8];
    QString simulation1 = candidateList[9];
    QString spatial1 = candidateList[10];
    QString randomness1 = candidateList[11];
    QString spectrum1 = candidateList[12];

    QString cumulativeProbabilityDistribution1 = candidateList[13];
    QString gustFactor1 = candidateList[14];
    QString kurtosis1 = candidateList[15];
    QString peakFactor1 = candidateList[16];
    QString probabilityDensityFunction1 = candidateList[17];
    QString roughness1 = candidateList[18];
    QString shearVelocityOfFlow1 = candidateList[19];
    QString skewness1 = candidateList[20];
    QString standardDeviation1 = candidateList[21];
    QString turbulenceIntensity1 = candidateList[22];
    QString turbulenceScale1 = candidateList[23];
    QString variance1 = candidateList[24];
    QString wavePassageEffect1 = candidateList[25];
    
    QString candidate2 = candidateList[26];
    QString comparisonCategory2 = candidateList[27];
    QString comparisonFunction2 = candidateList[28];
    QString coherence2 = candidateList[29];
    QString correlation2 = candidateList[30];
    QString frequency2 = candidateList[31];
    QString mean2 = candidateList[32];
    QString modulation2 = candidateList[33];
    QString decomposition2 = candidateList[34];
    QString simulation2 = candidateList[35];
    QString spatial2 = candidateList[36];
    QString randomness2 = candidateList[37];
    QString spectrum2 = candidateList[38];

    QString cumulativeProbabilityDistribution2 = candidateList[39];
    QString gustFactor2 = candidateList[40];
    QString kurtosis2 = candidateList[41];
    QString peakFactor2 = candidateList[42];
    QString probabilityDensityFunction2 = candidateList[43];
    QString roughness2 = candidateList[44];
    QString shearVelocityOfFlow2 = candidateList[45];
    QString skewness2 = candidateList[46];
    QString standardDeviation2 = candidateList[47];
    QString turbulenceIntensity2 = candidateList[48];
    QString turbulenceScale2 = candidateList[49];
    QString variance2 = candidateList[50];
    QString wavePassageEffect2 = candidateList[51];

    if (comparisonCategory == LabRPS::objGroupCoherenceFunction)
    {
        if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorF)
        {
            displayAComparisonResults(candidate1, candidate2, "CoherenceF", "Frequency", GetWindLabData().numberOfFrequency);
        }
        else if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "CoherenceT", "Frequency", GetWindLabData().numberOfFrequency);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupCorrelationFunction)
    {
        if (comparisonFunction == LabRPS::ComputeCrossCorrelationVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "CorrelationT", "Time Lag", GetWindLabData().numberOfTimeIncrements);

        }

    }
    else if (comparisonCategory == LabRPS::objGroupFrequencyDistribution)
    {
        if (comparisonFunction == LabRPS::ComputeFrequenciesVectorF)
        {
            displayAComparisonResults(candidate1, candidate2, "Frequency", "Numbering", GetWindLabData().numberOfFrequency);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupMeanWindProfile)
    {
        if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "MeanP", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "MeanT", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupModulationFunction)
    {
        if (comparisonFunction == LabRPS::ComputeModulationVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "ModulationT", "Time", GetWindLabData().numberOfTimeIncrements);
        }
        if (comparisonFunction == LabRPS::ComputeModulationVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "ModulationP", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupSpectrumDecompositionMethod)
    {
        if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorF)
        {
            displayAComparisonResults(candidate1, candidate2, "DecomposedpsdF", "Frequency", GetWindLabData().numberOfFrequency);
        }
        else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "DecomposedpsdT", "Time", GetWindLabData().numberOfTimeIncrements);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupSimulationMethod)
    {
        if (comparisonFunction == LabRPS::Simulate)
        {
            displayWindVelocityASimComparisonResults(candidate1, candidate2, "Velocity", "Time", GetWindLabData().numberOfTimeIncrements);
        }
        else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && GetWindLabData().largeScaleSimulationMode)
        {
            displayWindVelocityALargeScaleSimComparisonResults(candidate1, candidate2, "Velocity", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupAlongWindSpectrum && 1 == GetWindLabData().direction)
    {
        if (comparisonFunction == LabRPS::ComputeXAutoSpectrumVectorF)
        {
            displayAComparisonResults(candidate1, candidate2, "XSpectrumF", "Frequency", GetWindLabData().numberOfFrequency);
        }
        else if (comparisonFunction == LabRPS::ComputeXAutoSpectrumVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "XSpectrumF", "Time", GetWindLabData().numberOfTimeIncrements);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupAcrossWindSpectrum && 2 == GetWindLabData().direction)
    {
        if (comparisonFunction == LabRPS::ComputeYAutoSpectrumVectorF)
        {
            displayAComparisonResults(candidate1, candidate2, "YSpectrumF", "Frequency", GetWindLabData().numberOfFrequency);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupVerticalWindSpectrum && 3 == GetWindLabData().direction)
    {
        if (comparisonFunction == LabRPS::ComputeZAutoSpectrumVectorF)
        {
            displayAComparisonResults(candidate1, candidate2, "ZSpectrumF", "Frequency", GetWindLabData().numberOfFrequency);
        }
        else if (comparisonFunction == LabRPS::ComputeZAutoSpectrumVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "ZSpectrumF", "Time", GetWindLabData().numberOfTimeIncrements);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupCumulativeProbabilityDistribution)
    {
        if (comparisonFunction == LabRPS::ComputeCDFVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "CPD", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupGustFactor)
    {
        if (comparisonFunction == LabRPS::ComputeGustFactorVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "GustFactor", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeGustFactorVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "GustFactor", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupKurtosis)
    {
        if (comparisonFunction == LabRPS::ComputeKurtosisVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "Kurtosis", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeKurtosisVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "Kurtosis", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupPeakFactor)
    {
        if (comparisonFunction == LabRPS::ComputePeakFactorVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "PeakFactor", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputePeakFactorVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "GustFactor", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupProbabilityDensityFunction)
    {
        if (comparisonFunction == LabRPS::ComputePDFVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "PDF", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupRoughness)
    {
        if (comparisonFunction == LabRPS::ComputeRoughnessVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "Roughness", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeRoughnessVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "Roughness", "Time", GetWindLabData().numberOfTimeIncrements);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupShearVelocityOfFlow)
    {
        if (comparisonFunction == LabRPS::ComputeShearVelocityOfFlowVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "ShearVelocity", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeShearVelocityOfFlowVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "ShearVelocity", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupSkewness)
    {
        if (comparisonFunction == LabRPS::ComputeSkewnessVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "Skewness", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeSkewnessVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "Skewness", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupStandardDeviation)
    {
        if (comparisonFunction == LabRPS::ComputeStandardDeviationVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "StandardDeviation", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeStandardDeviationVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "StandardDeviation", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupTurbulenceIntensity)
    {
        if (comparisonFunction == LabRPS::ComputeTurbulenceIntensityVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "TurbulenceIntensity", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeTurbulenceIntensityVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "TurbulenceIntensity", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupTurbulenceScale)
    {
        if (comparisonFunction == LabRPS::ComputeTurbulenceScaleVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "TurbulenceScale", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeTurbulenceScaleVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "TurbulenceScale", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupVariance)
    {
        if (comparisonFunction == LabRPS::ComputeVarianceVectorP)
        {
            displayAComparisonResults(candidate1, candidate2, "Variance", "Numbering", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeVarianceVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "Variance", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupWavePassageEffect)
    {
        if (comparisonFunction == LabRPS::ComputeWavePassageEffectVectorF)
        {
            displayAComparisonResults(candidate1, candidate2, "WavePassage", "Frequency", GetWindLabData().numberOfSpatialPosition);
        }
        else if (comparisonFunction == LabRPS::ComputeWavePassageEffectVectorT)
        {
            displayAComparisonResults(candidate1, candidate2, "WavePassage", "Time", GetWindLabData().numberOfTimeIncrements);
        }
    }

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayTimeComparisonResults()
{
    int count = candidateList.size();
    QString candidate1 = candidateList[0];
    QString comparisonCategory = candidateList[1];
    QString comparisonFunction = candidateList[2];
    QString coherence1 = candidateList[3];
    QString correlation1 = candidateList[4];
    QString frequency1 = candidateList[5];
    QString mean1 = candidateList[6];
    QString modulation1 = candidateList[7];
    QString decomposition1 = candidateList[8];
    QString simulation1 = candidateList[9];
    QString spatial1 = candidateList[10];
    QString randomness1 = candidateList[11];
    QString spectrum1 = candidateList[12];

    QString cumulativeProbabilityDistribution1 = candidateList[13];
    QString gustFactor1 = candidateList[14];
    QString kurtosis1 = candidateList[15];
    QString peakFactor1 = candidateList[16];
    QString probabilityDensityFunction1 = candidateList[17];
    QString roughness1 = candidateList[18];
    QString shearVelocityOfFlow1 = candidateList[19];
    QString skewness1 = candidateList[20];
    QString standardDeviation1 = candidateList[21];
    QString turbulenceIntensity1 = candidateList[22];
    QString turbulenceScale1 = candidateList[23];
    QString variance1 = candidateList[24];
    QString wavePassageEffect1 = candidateList[25];
    
    QString candidate2 = candidateList[26];
    QString comparisonCategory2 = candidateList[27];
    QString comparisonFunction2 = candidateList[28];
    QString coherence2 = candidateList[29];
    QString correlation2 = candidateList[30];
    QString frequency2 = candidateList[31];
    QString mean2 = candidateList[32];
    QString modulation2 = candidateList[33];
    QString decomposition2 = candidateList[34];
    QString simulation2 = candidateList[35];
    QString spatial2 = candidateList[36];
    QString randomness2 = candidateList[37];
    QString spectrum2 = candidateList[38];

    QString cumulativeProbabilityDistribution2 = candidateList[39];
    QString gustFactor2 = candidateList[40];
    QString kurtosis2 = candidateList[41];
    QString peakFactor2 = candidateList[42];
    QString probabilityDensityFunction2 = candidateList[43];
    QString roughness2 = candidateList[44];
    QString shearVelocityOfFlow2 = candidateList[45];
    QString skewness2 = candidateList[46];
    QString standardDeviation2 = candidateList[47];
    QString turbulenceIntensity2 = candidateList[48];
    QString turbulenceScale2 = candidateList[49];
    QString variance2 = candidateList[50];
    QString wavePassageEffect2 = candidateList[51];

    QString variableName = "Name";

    //	if (1 == resultOutputType)
    //	{
    //		variableName = "Locations(n)";
    //	}
    //	else if (2 == resultOutputType)
    //	{
    //		variableName = "Frequencies(n)";
    //	}
    //	else if (3 == resultOutputType)
    //	{
    //		variableName = "Times(n)";
    //	}

    if (comparisonCategory == LabRPS::objGroupCoherenceFunction)
    {
        if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorF)
        {
            displayTComparisonResults(candidate1, candidate2, "CoherenceF", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeCrossCoherenceVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "CoherenceT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupCorrelationFunction)
    {
        if (comparisonFunction == LabRPS::ComputeCrossCorrelationVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "CorrelationT", variableName, totalNumber);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupFrequencyDistribution)
    {
        if (comparisonFunction == LabRPS::ComputeFrequenciesVectorF)
        {
            displayTComparisonResults(candidate1, candidate2, "Frequency", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupMeanWindProfile)
    {
        if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "MeanP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeMeanWindSpeedVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "MeanT", variableName, totalNumber);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupModulationFunction)
    {
        if (comparisonFunction == LabRPS::ComputeModulationVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "ModulationP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeModulationVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "ModulationT", variableName, totalNumber);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupSpectrumDecompositionMethod)
    {
        if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorF)
        {
            displayTComparisonResults(candidate1, candidate2, "DecomposedpsdF", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeDecomposedCrossSpectrumVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "DecomposedpsdT", variableName, totalNumber);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupSimulationMethod)
    {
        if (comparisonFunction == LabRPS::Simulate)
        {
            displayWindVelocityTSimComparisonResults(candidate1, candidate2, "Velocity", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::SimulateInLargeScaleMode && GetWindLabData().largeScaleSimulationMode)
        {
            displayWindVelocityTLargeScaleSimComparisonResults(candidate1, candidate2, "Velocity", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupAlongWindSpectrum && 1 == GetWindLabData().direction)
    {
        if (comparisonFunction == LabRPS::ComputeXAutoSpectrumVectorF)
        {
            displayTComparisonResults(candidate1, candidate2, "XSpectrumF", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeXAutoSpectrumVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "XSpectrumT", variableName, totalNumber);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupAcrossWindSpectrum && 2 == GetWindLabData().direction)
    {
        if (comparisonFunction == LabRPS::ComputeYAutoSpectrumVectorF)
        {
            displayTComparisonResults(candidate1, candidate2, "YSpectrumF", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeYAutoSpectrumVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "YSpectrumT", variableName, totalNumber);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupVerticalWindSpectrum && 3 == GetWindLabData().direction)
    {
        if (comparisonFunction == LabRPS::ComputeZAutoSpectrumVectorF)
        {
            displayTComparisonResults(candidate1, candidate2, "ZSpectrumF", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeZAutoSpectrumVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "ZSpectrumT", variableName, totalNumber);
        }

    }
    else if (comparisonCategory == LabRPS::objGroupCumulativeProbabilityDistribution)
    {
        if (comparisonFunction == LabRPS::ComputeCDFVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "CPDT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupGustFactor)
    {
        if (comparisonFunction == LabRPS::ComputeGustFactorVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "GustFactorP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeKurtosisVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "GustFactorT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupKurtosis)
    {
        if (comparisonFunction == LabRPS::ComputeKurtosisVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "KurtosisT", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeKurtosisVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "KurtosisT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupPeakFactor)
    {
        if (comparisonFunction == LabRPS::ComputePeakFactorVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "PeakFactorP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputePeakFactorVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "PeakFactorT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupProbabilityDensityFunction)
    {
        if (comparisonFunction == LabRPS::ComputePDFVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "PDFT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupRoughness)
    {
        if (comparisonFunction == LabRPS::ComputeRoughnessVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "RoughnessP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeRoughnessVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "RoughnessT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupShearVelocityOfFlow)
    {
        if (comparisonFunction == LabRPS::ComputeShearVelocityOfFlowVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "ShearVelocityP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeShearVelocityOfFlowVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "ShearVelocityT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupSkewness)
    {
        if (comparisonFunction == LabRPS::ComputeSkewnessVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "SkewnessP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeSkewnessVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "SkewnessT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupStandardDeviation)
    {
        if (comparisonFunction == LabRPS::ComputeStandardDeviationVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "StandardDeviationP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeStandardDeviationVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "StandardDeviationT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupTurbulenceIntensity)
    {
        if (comparisonFunction == LabRPS::ComputeTurbulenceIntensityVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "TurbulenceIntensityP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeTurbulenceIntensityVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "TurbulenceIntensityT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupTurbulenceScale)
    {
        if (comparisonFunction == LabRPS::ComputeTurbulenceScaleVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "TurbulenceScaleP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeTurbulenceScaleVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "TurbulenceScaleT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupVariance)
    {
        if (comparisonFunction == LabRPS::ComputeVarianceVectorP)
        {
            displayTComparisonResults(candidate1, candidate2, "VarianceP", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeVarianceVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "VarianceT", variableName, totalNumber);
        }
    }
    else if (comparisonCategory == LabRPS::objGroupWavePassageEffect)
    {
        if (comparisonFunction == LabRPS::ComputeWavePassageEffectVectorF)
        {
            displayTComparisonResults(candidate1, candidate2, "WavePassageF", variableName, totalNumber);
        }
        else if (comparisonFunction == LabRPS::ComputeWavePassageEffectVectorT)
        {
            displayTComparisonResults(candidate1, candidate2, "WavePassageT", variableName, totalNumber);
        }
    }

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    // delete the worker
    GetWindLabComparisonWorker()->finished();
}

void RPSWindLabSimulation::displayMemoryComparisonResults()
{
}

void RPSWindLabSimulation::displayWindVelocity(bool simulationStatus)
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    app->updateLog(logSimulationInfo(simulationStatus, "Your Simulation"));

    if (nullptr != GetWindLabSimulationWorker())
    {
        information = information + GetWindLabSimulationWorker()->getInformation();
        information.append("Please wait. LabRPS is now showing the random velocity results...");
        emit sendInformation(information);
        information.clear();
        emit progressBarHide();

        // save a copy of the simulated wind velocity
        m_resultMatrix = GetWindLabSimulationWorker()->m_ResultMatrix;
    }
    else if (m_resultMatrix.size() <= 0)
    {
        information.append("Please,run the simulation first.");
        emit sendInformation(information);
        information.clear();
        return;
    }

    qApp->processEvents();
    information.clear();

    if(!simulationStatus)
    {
        information.append("Sorry, the simulation fails.");
        emit sendInformation(information);
        information.clear();
        return;
    }

    if (locationJ > 0 &&
            locationJ <= GetWindLabData().numberOfSpatialPosition &&
            locationK == 0 &&
            frequencyIndex == 0 &&
            timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
    {
        QTime t;
        t.start();

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        // prepare the name of the table
        QString arrayName = tr("RandomVelocity (%1, None, None, All)").arg(locationJ);

        // allocate memory for the table
        Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

        table->setColName(0, "Time");
        table->setColName(1, tr("Location %1").arg(locationJ));

        double timeInr = 0.0;

        std::vector<double> X(GetWindLabData().numberOfTimeIncrements);
        std::vector<double> Y(GetWindLabData().numberOfTimeIncrements);

        // fill the table with computed coherence
        for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
        {
            timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

            table->setCellValue(i, 0, timeInr);
            table->setCellValue(i, 1, m_resultMatrix(i, locationJ));

            X[i] = timeInr;
            Y[i] = m_resultMatrix(i, locationJ);
        }

        table->showNormal();

        using namespace matplot;
        auto f = figure(true);
        plot(X, Y);
        xlabel("Time(s)");
        ylabel("Velocity(m/s)");
        f->show();

        QApplication::restoreOverrideCursor();

        information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
    }
    else /*if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
             locationK == 0 &&
             frequencyIndex == 0 &&
             timeIndex == GetWindLabData().numberOfTimeIncrements + 1)*/
    {
        QTime t;
        t.start();

        // prepare the name of the table
        QString arrayName = "RandomVelocity (All, None, None, All)";

        // allocate memory for the table
        Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, GetWindLabData().numberOfSpatialPosition + 1);

        table->setColName(0, "Time");

        for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
        {
            table->setColName(j + 1, tr("Location %1").arg(j + 1));
        }

        double timeInr = 0.0;

        std::vector<double> X(GetWindLabData().numberOfTimeIncrements);
        std::vector<double> Y(GetWindLabData().numberOfTimeIncrements);
        std::vector<double> Z(GetWindLabData().numberOfTimeIncrements);

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        // fill the table with computed coherence
        for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
        {
            timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

            table->setCellValue(i, 0, timeInr);

            for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
            {
                table->setCellValue(i, j + 1, m_resultMatrix(i, j));
            }
        }

        table->showNormal();


        using namespace matplot;
        auto f = figure(true);

        for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
        {
            for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
            {
                X[i] = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
                Y[i] = j + 1;
                Z[i] = m_resultMatrix(i, j);
            }

            plot3(X, Y, Z);


            hold(on);
        }
        rotate(20, 30);
        xlabel("Time(s)");
        ylabel("Location");
        zlabel("Velocity(m/s)");
        hold(off);
        f->draw();

        QApplication::restoreOverrideCursor();

        information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
    }
    //	else
    //	{
    //		QTime t;
    //		t.start();

    //		// prepare the name of the table
    //        QString arrayName = "RandomVelocity (1, None, None, All)";

    //		// allocate memory for the table
    //		Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

    //		table->setColName(0, "Time");
    //        table->setColName(1, "Location 1");

    //		double timeInr = 0.0;

    //		// fill the table with computed coherence
    //		for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
    //		{
    //			timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;

    //			table->setCellValue(i, 0, timeInr);
    //            table->setCellValue(i, 1, m_resultMatrix(i, 0));
    //		}

    //		table->showNormal();

    //		information.append(tr("The wind velocity simulation took %1 ms to be displayed").arg(QString::number(t.elapsed())));
    //	}

    // send info the main window to show it
    emit sendInformation(information);

    // clear the information list
    information.clear();

    if (nullptr != GetWindLabSimulationWorker())
    {
        // delete the worker
        GetWindLabSimulationWorker()->finished();
    }
}

//void RPSWindLabSimulation::displayFrequencyDistribution()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the frequency results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    if (locationJ > 0 &&
//            locationJ <= GetWindLabData().numberOfSpatialPosition &&
//            locationK == 0 &&
//            frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
//            timeIndex == 0)
//    {

//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = tr("Frequency (%1, None, All, None)").arg(locationJ);

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, i + 1);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();
//        information.append(tr("The computed frequencies took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
//             locationK == 0 &&
//             frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
//             timeIndex == 0)
//    {

//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = "Frequency (All, None, All, None)";

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();
//        const int cls = GetWindLabSimulationOutputWorker()->m_ResultVector.cols();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, cls);

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            for (int j = 0; j < cls; j++)
//            {
//                table->setCellValue(i, j, GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j));
//            }
//        }
//        table->showNormal();
//        information.append(tr("The computed frequencies took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = "Frequency (1, None, All, None)";

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, i + 1);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();
//        information.append(tr("The computed frequencies took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//        // information.append("Sorry, there is no function that meet your requirements.");
//    }

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

//void RPSWindLabSimulation::displayCoherenceWind()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the frequency results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    if (locationJ > 0 &&
//            locationJ <= GetWindLabData().numberOfSpatialPosition &&
//            locationK > 0 &&
//            locationK <= GetWindLabData().numberOfSpatialPosition &&
//            frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
//            timeIndex > 0 &&
//            timeIndex <= GetWindLabData().numberOfTimeIncrements)
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = tr("Coherence (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();
//    }
//    else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
//             locationK == GetWindLabData().numberOfSpatialPosition + 1 &&
//             frequencyIndex > 0 &&
//             frequencyIndex <= GetWindLabData().numberOfFrequency &&
//             timeIndex > 0 &&
//             timeIndex <= GetWindLabData().numberOfTimeIncrements)
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the matrix
//        QString arrayName = tr("Coherence (All, All, %1, %2)").arg(frequencyIndex).arg(timeIndex);

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultMatrix.rows();
//        const int cls = GetWindLabSimulationOutputWorker()->m_ResultMatrix.rows();

//        // allocate memory for the matrix
//        Matrix *matrix = app->newMatrix(arrayName, rws, cls);
//        matrix->setCoordinates(1, rws, 1, cls);
       
//        // fill the matrix with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            for (int j = 0; j < cls; j++)
//            {
//                matrix->setText(i, j, QString::number(GetWindLabSimulationOutputWorker()->m_ResultMatrix(i, j)));
//            }
//        }

//        matrix->showNormal();
//    }
//    else
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = "Coherence (1, 1, All, 1)";

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();
//    }

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

//void RPSWindLabSimulation::displaySpectrum()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the spectrum results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    if (locationJ > 0 &&
//            locationJ <= GetWindLabData().numberOfSpatialPosition &&
//            locationK > 0 &&
//            locationK <= GetWindLabData().numberOfSpatialPosition &&
//            frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
//            timeIndex > 0 &&
//            timeIndex <= GetWindLabData().numberOfTimeIncrements

//            )
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = psdPrefix + tr("Spectrum (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        table->setColName(0, "Frequency");
//        table->setColName(1, "Spectrum");

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();

//        information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
//             locationK == 0 &&
//             frequencyIndex > 0 &&
//             frequencyIndex <= GetWindLabData().numberOfFrequency &&
//             timeIndex > 0 &&
//             timeIndex <= GetWindLabData().numberOfTimeIncrements

//             )
//    {

//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = psdPrefix + tr("Spectrum (All, None, %1, %2)").arg(frequencyIndex).arg(timeIndex);

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        table->setColName(0, "Location");
//        table->setColName(1, "Spectrum");

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, i + 1);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();

//        information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = psdPrefix + "Spectrum (1, 1, All, 1)";

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        table->setColName(0, "Frequency");
//        table->setColName(1, "Spectrum");

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();

//        information.append(tr("The computed spectrum took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

//void RPSWindLabSimulation::displayXSpectrum()
//{
//    displaySpectrum();
//}

//void RPSWindLabSimulation::displayYSpectrum()
//{
//    displaySpectrum();
//}

//void RPSWindLabSimulation::displayZSpectrum()
//{
//    displaySpectrum();
//}

//void RPSWindLabSimulation::displayDecomposedSpectrum()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the spectrum results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    if (locationJ > 0 &&
//            locationJ <= GetWindLabData().numberOfSpatialPosition &&
//            locationK > 0 &&
//            locationK <= GetWindLabData().numberOfSpatialPosition &&
//            frequencyIndex == GetWindLabData().numberOfFrequency + 1 &&
//            timeIndex > 0 &&
//            timeIndex <= GetWindLabData().numberOfTimeIncrements

//            )
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = psdPrefix + tr("DecomposedSpectrum (%1, %2, All, %3)").arg(locationJ).arg(locationK).arg(timeIndex);

//        const int rws = GetWindLabSimulationOutputWorker()->m_ResultVector.rows();

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, rws, 2);

//        table->setColName(0, "Frequency");
//        table->setColName(1, "Spectrum");

//        // fill the table with computed coherence
//        for (int i = 0; i < rws; i++)
//        {
//            table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();

//        information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else if (locationJ == GetWindLabData().numberOfSpatialPosition + 1 &&
//             locationK == locationJ &&
//             frequencyIndex > 0 &&
//             frequencyIndex <= GetWindLabData().numberOfFrequency &&
//             timeIndex > 0 &&
//             timeIndex <= GetWindLabData().numberOfTimeIncrements

//             )
//    {

//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = psdPrefix + tr("DecomposedSpectrum (All, All, %1, %2)").arg(frequencyIndex).arg(timeIndex);

//        // allocate memory for the matrix
//        Matrix *matrix = app->newMatrix(arrayName, GetWindLabData().numberOfSpatialPosition, GetWindLabData().numberOfSpatialPosition);
//        matrix->setCoordinates(1, GetWindLabData().numberOfSpatialPosition, 1, GetWindLabData().numberOfSpatialPosition);

//        // fill the matrix with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfSpatialPosition; i++)
//        {
//            for (int j = 0; j < GetWindLabData().numberOfSpatialPosition; j++)
//            {
//                matrix->setText(i, j, QString::number(GetWindLabSimulationOutputWorker()->m_ResultMatrix2(i, j)));
//            }
//        }

//        matrix->showNormal();

//        information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }

//    else
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = psdPrefix + "DecomposedSpectrum (1, 1, All, 1)";

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfFrequency, 2);

//        table->setColName(0, "Frequency");
//        table->setColName(1, "Spectrum");

//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfFrequency; i++)
//        {
//            table->setCellValue(i, 0, GetWindLabSimulationOutputWorker()->m_ResultVector2(i));
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();

//        information.append(tr("The spectrum decomposition took %1 ms to be displayed").arg(QString::number(t.elapsed())));

//    }

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

//void RPSWindLabSimulation::displayCorrelationWind()
//{
//}
//void RPSWindLabSimulation::displayModulationWind()
//{
//    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
//    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

//    information = information + GetWindLabSimulationOutputWorker()->getInformation();
//    information.append("Please wait. LabRPS is now showing the spectrum results...");
//    emit sendInformation(information);
//    emit progressBarHide();

//    qApp->processEvents();
//    information.clear();

//    if (locationJ > 0 &&
//            locationJ <= GetWindLabData().numberOfSpatialPosition &&
//            locationK == 0 &&
//            frequencyIndex > 0 &&
//            frequencyIndex <= GetWindLabData().numberOfFrequency &&
//            timeIndex == GetWindLabData().numberOfTimeIncrements + 1)
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = tr("Modulation (%1, None, %2, All)").arg(locationJ).arg(frequencyIndex);

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

//        table->setColName(0, "Time");
//        table->setColName(1, "Modulation");

//        double timeInr = 0.0;
//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
//        {
//            timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
//            table->setCellValue(i, 0, timeInr);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();

//        information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }
//    else
//    {
//        QTime t;
//        t.start();

//        // prepare the name of the table
//        QString arrayName = "Modulation (1, None, 1, All)";

//        // allocate memory for the table
//        Table *table = app->newTable(arrayName, GetWindLabData().numberOfTimeIncrements, 2);

//        table->setColName(0, "Time");
//        table->setColName(1, "Modulation");

//        double timeInr = 0.0;
//        // fill the table with computed coherence
//        for (int i = 0; i < GetWindLabData().numberOfTimeIncrements; i++)
//        {
//            timeInr = GetWindLabData().minTime + i * GetWindLabData().timeIncrement;
//            table->setCellValue(i, 0, timeInr);
//            table->setCellValue(i, 1, GetWindLabSimulationOutputWorker()->m_ResultVector(i));
//        }

//        table->showNormal();

//        information.append(tr("The computed modulation function took %1 ms to be displayed").arg(QString::number(t.elapsed())));
//    }

//    // send info the main window to show it
//    emit sendInformation(information);

//    // clear the information list
//    information.clear();

//    // delete the worker
//    GetWindLabSimulationOutputWorker()->finished();
//}

void RPSWindLabSimulation::save(XmlStreamWriter *xmlwriter)
{

    xmlwriter->writeStartElement("windLab");
    saveWindLabData(xmlwriter);
    xmlwriter->writeEndElement();
}

bool RPSWindLabSimulation::load(XmlStreamReader *xmlreader)
{

    if (xmlreader->isStartElement() && xmlreader->name() == "windLab")
    {
        loadWindLabData(xmlreader);
    }
    else // no element
    {
        xmlreader->raiseError(tr("no windLab element found"));
    }

    return !xmlreader->hasError();
}

void RPSWindLabSimulation::saveWindLabData(XmlStreamWriter *xmlwriter)
{

    (windLabData.stationarity) ? xmlwriter->writeAttribute("stationarity", "true")
                               : xmlwriter->writeAttribute("stationarity", "false");
    (windLabData.uniformModulation) ? xmlwriter->writeAttribute("uniformModulation", "true")
                               : xmlwriter->writeAttribute("uniformModulation", "false");
    (windLabData.gaussianity) ? xmlwriter->writeAttribute("gaussianity", "true")
                              : xmlwriter->writeAttribute("gaussianity", "false");
    (windLabData.comparisonMode) ? xmlwriter->writeAttribute("comparisonMode", "true")
                                 : xmlwriter->writeAttribute("comparisonMode", "false");
    (windLabData.largeScaleSimulationMode) ? xmlwriter->writeAttribute("largeScaleSimulationMode", "true")
                                           : xmlwriter->writeAttribute("largeScaleSimulationMode", "false");

    xmlwriter->writeAttribute("numberOfSpatialPosition", QString::number(windLabData.numberOfSpatialPosition));
    xmlwriter->writeAttribute("numberOfFrequency", QString::number(windLabData.numberOfFrequency));
    xmlwriter->writeAttribute("numberOfSample", QString::number(windLabData.numberOfSample));
    xmlwriter->writeAttribute("direction", QString::number(windLabData.direction));
    xmlwriter->writeAttribute("frequencyDistrType", QString::number(windLabData.frequencyDistrType));
    xmlwriter->writeAttribute("numberOfTimeIncrements", QString::number(windLabData.numberOfTimeIncrements));
    xmlwriter->writeAttribute("frequencyIncrement", QString::number(windLabData.frequencyIncrement));
    xmlwriter->writeAttribute("timeIncrement", QString::number(windLabData.timeIncrement));
    xmlwriter->writeAttribute("minTime", QString::number(windLabData.minTime));
    xmlwriter->writeAttribute("maxTime", QString::number(windLabData.maxTime));
    xmlwriter->writeAttribute("minFrequency", QString::number(windLabData.minFrequency));
    xmlwriter->writeAttribute("maxFrequency", QString::number(windLabData.maxFrequency));
    xmlwriter->writeAttribute("locationJ", QString::number(windLabData.locationJ));
    xmlwriter->writeAttribute("locationK", QString::number(windLabData.locationK));
    xmlwriter->writeAttribute("frequencyIndex", QString::number(windLabData.frequencyIndex));
    xmlwriter->writeAttribute("directionIndex", QString::number(windLabData.directionIndex));
    xmlwriter->writeAttribute("timeIndex", QString::number(windLabData.timeIndex));
    xmlwriter->writeAttribute("numberOfTimeLags", QString::number(windLabData.numberOfTimeLags));

    xmlwriter->writeAttribute("spatialDistribution", windLabData.spatialDistribution);
    xmlwriter->writeAttribute("shearVelocity", windLabData.shearVelocity);
    xmlwriter->writeAttribute("meanFunction", windLabData.meanFunction);
    xmlwriter->writeAttribute("spectrumModel", windLabData.spectrumModel);
    xmlwriter->writeAttribute("coherenceFunction", windLabData.coherenceFunction);
    xmlwriter->writeAttribute("simulationApproach", windLabData.simulationApproach);
    xmlwriter->writeAttribute("simulationMethod", windLabData.simulationMethod);
    xmlwriter->writeAttribute("freqencyDistribution", windLabData.freqencyDistribution);
    xmlwriter->writeAttribute("cpsdDecompositionMethod", windLabData.cpsdDecompositionMethod);
    xmlwriter->writeAttribute("randomnessProvider", windLabData.randomnessProvider);
    xmlwriter->writeAttribute("modulationFunction", windLabData.modulationFunction);
    xmlwriter->writeAttribute("correlationFunction", windLabData.correlationFunction);
    xmlwriter->writeAttribute("varianceFunction", windLabData.varianceFunction);
    xmlwriter->writeAttribute("workingDirPath", windLabData.workingDirPath);
    xmlwriter->writeAttribute("comparisonCategory", windLabData.comparisonCategory);

    xmlwriter->writeAttribute("cumulativeProbabilityDistribution", windLabData.cumulativeProbabilityDistribution);
    xmlwriter->writeAttribute("gustFactor", windLabData.gustFactor);
    xmlwriter->writeAttribute("kurtosis", windLabData.kurtosis);
    xmlwriter->writeAttribute("peakFactor", windLabData.peakFactor);
    xmlwriter->writeAttribute("probabilityDensityFunction", windLabData.probabilityDensityFunction);
    xmlwriter->writeAttribute("roughness", windLabData.roughness);
    xmlwriter->writeAttribute("shearVelocityOfFlow", windLabData.shearVelocityOfFlow);
    xmlwriter->writeAttribute("skewness", windLabData.skewness);
    xmlwriter->writeAttribute("standardDeviation", windLabData.standardDeviation);
    xmlwriter->writeAttribute("turbulenceIntensity", windLabData.turbulenceIntensity);
    xmlwriter->writeAttribute("turbulenceScale", windLabData.turbulenceScale);
    xmlwriter->writeAttribute("variance", windLabData.variance);
    xmlwriter->writeAttribute("wavePassageEffect", windLabData.wavePassageEffect);

}


bool RPSWindLabSimulation::loadWindLabData(XmlStreamReader *xmlreader)
{

    bool ok;
    bool bvalue;
    int ivalue;
    double dvalue;
    QString svalue;

    bvalue = xmlreader->readAttributeBool("stationarity", &ok);
    if (ok)
    {
        windLabData.stationarity = bvalue;
    }
    else
    {
        xmlreader->raiseWarning("Stationarity setting error");
    }

    bvalue = xmlreader->readAttributeBool("uniformModulation", &ok);
    if (ok)
    {
        windLabData.uniformModulation = bvalue;
    }
    else
    {
        xmlreader->raiseWarning("Uniform modulation setting error");
    }

    bvalue = xmlreader->readAttributeBool("gaussianity", &ok);
    if (ok)
    {
        windLabData.gaussianity = bvalue;
    }
    else
    {
        xmlreader->raiseWarning("Gaussianity setting error");
    }

    bvalue = xmlreader->readAttributeBool("comparisonMode", &ok);
    if (ok)
    {
        windLabData.comparisonMode = bvalue;
    }
    else
    {
        xmlreader->raiseWarning("Comparison mode setting error");
    }

    bvalue = xmlreader->readAttributeBool("largeScaleSimulationMode", &ok);
    if (ok)
    {
        windLabData.largeScaleSimulationMode = bvalue;
    }
    else
    {
        xmlreader->raiseWarning("Large scale simulation mode setting error");
    }

    ivalue = xmlreader->readAttributeInt("numberOfSpatialPosition", &ok);
    if (ok)
    {
        windLabData.numberOfSpatialPosition = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Number of spatial postion setting error");
    }

    ivalue = xmlreader->readAttributeInt("numberOfFrequency", &ok);
    if (ok)
    {
        windLabData.numberOfFrequency = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Number of frequency setting error");
    }

    ivalue = xmlreader->readAttributeInt("numberOfSample", &ok);
    if (ok)
    {
        windLabData.numberOfSample = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Number of sample setting error");
    }

    ivalue = xmlreader->readAttributeInt("direction", &ok);
    if (ok)
    {
        windLabData.direction = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Wind direction setting error");
    }

    ivalue = xmlreader->readAttributeInt("frequencyDistrType", &ok);
    if (ok)
    {
        windLabData.frequencyDistrType = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Frequency distribution type setting error");
    }

    ivalue = xmlreader->readAttributeInt("numberOfTimeIncrements", &ok);
    if (ok)
    {
        windLabData.numberOfTimeIncrements = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Number of time increments setting error");
    }

    ivalue = xmlreader->readAttributeInt("locationJ", &ok);
    if (ok)
    {
        windLabData.locationJ = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Location J index setting error");
    }

    ivalue = xmlreader->readAttributeInt("locationK", &ok);
    if (ok)
    {
        windLabData.locationK = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Location K index setting error");
    }

    ivalue = xmlreader->readAttributeInt("frequencyIndex", &ok);
    if (ok)
    {
        windLabData.frequencyIndex = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Frequency index setting error");
    }

    ivalue = xmlreader->readAttributeInt("directionIndex", &ok);
    if (ok)
    {
        windLabData.directionIndex = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Direction index setting error");
    }

    ivalue = xmlreader->readAttributeInt("timeIndex", &ok);
    if (ok)
    {
        windLabData.timeIndex = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Time index setting error");
    }

    ivalue = xmlreader->readAttributeInt("numberOfTimeLags", &ok);
    if (ok)
    {
        windLabData.numberOfTimeLags = ivalue;
    }
    else
    {
        xmlreader->raiseWarning("Number of time lags setting error");
    }

    dvalue = xmlreader->readAttributeDouble("frequencyIncrement", &ok);
    if (ok)
    {
        windLabData.frequencyIncrement = dvalue;
    }
    else
    {
        xmlreader->raiseWarning("Frequency increment setting error");
    }

    dvalue = xmlreader->readAttributeDouble("timeIncrement", &ok);
    if (ok)
    {
        windLabData.timeIncrement = dvalue;
    }
    else
    {
        xmlreader->raiseWarning("Time increment setting error");
    }

    dvalue = xmlreader->readAttributeDouble("minTime", &ok);
    if (ok)
    {
        windLabData.minTime = dvalue;
    }
    else
    {
        xmlreader->raiseWarning("Minimum time setting error");
    }

    dvalue = xmlreader->readAttributeDouble("maxTime", &ok);
    if (ok)
    {
        windLabData.maxTime = dvalue;
    }
    else
    {
        xmlreader->raiseWarning("Maximum time setting error");
    }

    dvalue = xmlreader->readAttributeDouble("minFrequency", &ok);
    if (ok)
    {
        windLabData.minFrequency = dvalue;
    }
    else
    {
        xmlreader->raiseWarning("Minimum frequency setting error");
    }

    dvalue = xmlreader->readAttributeDouble("maxFrequency", &ok);
    if (ok)
    {
        windLabData.maxFrequency = dvalue;
    }
    else
    {
        xmlreader->raiseWarning("Maximum frequency setting error");
    }

    svalue = xmlreader->readAttributeString("spatialDistribution", &ok);
    if (ok)
    {
        windLabData.spatialDistribution = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Spatial distribution setting error");
    }

    svalue = xmlreader->readAttributeString("shearVelocity", &ok);
    if (ok)
    {
        windLabData.shearVelocity = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Shear velocity setting error");
    }

    svalue = xmlreader->readAttributeString("meanFunction", &ok);
    if (ok)
    {
        windLabData.meanFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Mean function setting error");
    }

    svalue = xmlreader->readAttributeString("spectrumModel", &ok);
    if (ok)
    {
        windLabData.spectrumModel = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Spectrum model setting error");
    }

    svalue = xmlreader->readAttributeString("coherenceFunction", &ok);
    if (ok)
    {
        windLabData.coherenceFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Coherence function setting error");
    }

    svalue = xmlreader->readAttributeString("simulationApproach", &ok);
    if (ok)
    {
        windLabData.simulationApproach = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Simulation approach setting error");
    }

    svalue = xmlreader->readAttributeString("simulationMethod", &ok);
    if (ok)
    {
        windLabData.simulationMethod = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Simulation method setting error");
    }

    svalue = xmlreader->readAttributeString("freqencyDistribution", &ok);
    if (ok)
    {
        windLabData.freqencyDistribution = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Frequency distribution setting error");
    }

    svalue = xmlreader->readAttributeString("cpsdDecompositionMethod", &ok);
    if (ok)
    {
        windLabData.cpsdDecompositionMethod = svalue;
    }
    else
    {
        xmlreader->raiseWarning("cpsd decompositionMethod setting error");
    }

    svalue = xmlreader->readAttributeString("randomnessProvider", &ok);
    if (ok)
    {
        windLabData.randomnessProvider = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Randomness provider setting error");
    }

    svalue = xmlreader->readAttributeString("modulationFunction", &ok);
    if (ok)
    {
        windLabData.modulationFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Modulation function setting error");
    }

    svalue = xmlreader->readAttributeString("correlationFunction", &ok);
    if (ok)
    {
        windLabData.correlationFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Correlation function setting error");
    }

    svalue = xmlreader->readAttributeString("varianceFunction", &ok);
    if (ok)
    {
        windLabData.varianceFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Variance function setting error");
    }

    svalue = xmlreader->readAttributeString("workingDirPath", &ok);
    if (ok)
    {
        windLabData.workingDirPath = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Working directory path setting error");
    }

    svalue = xmlreader->readAttributeString("comparisonCategory", &ok);
    if (ok)
    {
        windLabData.comparisonCategory = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Comparison category setting error");
    }










    svalue = xmlreader->readAttributeString("cumulativeProbabilityDistribution", &ok);
    if (ok)
    {
        windLabData.cumulativeProbabilityDistribution = svalue;
    }
    else
    {
        xmlreader->raiseWarning("cumulative Probability Distribution loading error");
    }

    svalue = xmlreader->readAttributeString("gustFactor", &ok);
    if (ok)
    {
        windLabData.gustFactor = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Gust Factor loading error");
    }

    svalue = xmlreader->readAttributeString("kurtosis", &ok);
    if (ok)
    {
        windLabData.kurtosis = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Kurtosis loading error");
    }

    svalue = xmlreader->readAttributeString("peakFactor", &ok);
    if (ok)
    {
        windLabData.peakFactor = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Peak Factor loadking error");
    }

    svalue = xmlreader->readAttributeString("probabilityDensityFunction", &ok);
    if (ok)
    {
        windLabData.probabilityDensityFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Probability Density Function loading error");
    }

    svalue = xmlreader->readAttributeString("roughness", &ok);
    if (ok)
    {
        windLabData.roughness = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Roughness loading error");
    }

    svalue = xmlreader->readAttributeString("shearVelocityOfFlow", &ok);
    if (ok)
    {
        windLabData.shearVelocityOfFlow = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Shear Velocity loading error");
    }

    svalue = xmlreader->readAttributeString("standardDeviation", &ok);
    if (ok)
    {
        windLabData.standardDeviation = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Standard Deviation loading error");
    }

    svalue = xmlreader->readAttributeString("turbulenceIntensity", &ok);
    if (ok)
    {
        windLabData.turbulenceIntensity = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Turbulence Intensity loading error");
    }

    svalue = xmlreader->readAttributeString("turbulenceScale", &ok);
    if (ok)
    {
        windLabData.turbulenceScale = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Turbulence Scale error");
    }

    svalue = xmlreader->readAttributeString("meanFunction", &ok);
    if (ok)
    {
        windLabData.meanFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Mean function setting error");
    }

    svalue = xmlreader->readAttributeString("meanFunction", &ok);
    if (ok)
    {
        windLabData.meanFunction = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Mean function setting error");
    }

    svalue = xmlreader->readAttributeString("skewness", &ok);
    if (ok)
    {
        windLabData.skewness = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Skewness loading error");
    }

    svalue = xmlreader->readAttributeString("variance", &ok);
    if (ok)
    {
        windLabData.variance = svalue;
    }
    else
    {
        xmlreader->raiseWarning("variance loading error");
    }

    svalue = xmlreader->readAttributeString("wavePassageEffect", &ok);
    if (ok)
    {
        windLabData.wavePassageEffect = svalue;
    }
    else
    {
        xmlreader->raiseWarning("Wave Passag Effect loading error");
    }



    return !xmlreader->hasError();
}


void RPSWindLabSimulation::runTableTool(const mat &table)
{
    std::unique_ptr<CRPSWLRunTableToolsDlg> dlg(new CRPSWLRunTableToolsDlg(this));

    if (dlg->exec() == QDialog::Accepted)
    {
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        GetWindLabData().tableTool = dlg->tableTool;

        IrpsWLTableTool *currentTableTool = CrpsTableToolFactory::BuildObject(GetWindLabData().tableTool);

        if (NULL == currentTableTool)
        {
            QApplication::restoreOverrideCursor();
            return;
        }

        mat outputResult(table.rows(),table.cols());

        try {
            currentTableTool->TableToolCompute(GetWindLabData(),table, outputResult, information);
        }
        catch(const std::exception &e)
        {
            QString errorMsg = e.what();
        }
        catch(const std::bad_alloc &)
        {
            QString errorMsg = "e.what()";
        }
        catch (...) {
            information.append("Sorry, something went wrong with the " + GetWindLabData().tableTool + " object.");
            emit sendInformation(information);
            information.clear();
        }

        RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
        ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

        Table *table = app->newTable( GetWindLabData().tableTool, outputResult.rows(), outputResult.cols());

        for (int i = 0; i < outputResult.rows(); i++)
        {
            for (int j = 0; j < outputResult.cols(); j++)
            {
                table->setCellValue(i, j, outputResult(i,j));
            }
        }

        table->showNormal();

        emit sendInformation(information);
        information.clear();

        QApplication::restoreOverrideCursor();

    }

}

void RPSWindLabSimulation::runMatrixTool(const mat &matrix)
{
    std::unique_ptr<CRPSWLRunMatrixToolsDlg> dlg(new CRPSWLRunMatrixToolsDlg(this));

    if (dlg->exec() == QDialog::Accepted)
    {
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        GetWindLabData().matrixTool = dlg->matrixTool;

        IrpsWLMatrixTool *currentMatrixTool = CrpsMatrixToolFactory::BuildObject(GetWindLabData().matrixTool);

        if (NULL == currentMatrixTool)
        {
            QApplication::restoreOverrideCursor();
            return;
        }

        mat outputResult(matrix.rows(),matrix.cols());

        currentMatrixTool->MatrixToolCompute(GetWindLabData(),matrix, outputResult, information);

        RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
        ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

        Matrix *matrix = app->newMatrix( GetWindLabData().matrixTool, outputResult.rows(), outputResult.cols());

        matrix->setCoordinates(1, outputResult.rows(), 1, outputResult.cols());

        // fill the matrix with computed coherence
        for (int i = 0; i < outputResult.rows(); i++)
        {
            for (int j = 0; j < outputResult.cols(); j++)
            {
                matrix->setText(i, j, QString::number(outputResult(i,j)));
            }
        }

        matrix->showNormal();
        emit sendInformation(information);
        information.clear();
        QApplication::restoreOverrideCursor();

    }

}

QString RPSWindLabSimulation::logSimulationInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = "<b>[" + dt.toString(Qt::LocalDate) + "&emsp;" +
            ": ''" + name + "'']</b><hr>";


    Utilities::TableColorProfile profile = Utilities::TableColorProfile::Success;
    if (status != true)
        profile = Utilities::TableColorProfile::Failure;

    QString table;
    table =
            Utilities::makeHtmlTable(37, 2, false, profile);

    table = table.arg(tr("Computation Time"), QString::number(GetWindLabSimulationWorker()->getSimulationTime()/1000) + " seconds");
    table = table.arg(tr("Simulation Method"), GetWindLabData().simulationMethod);
    table = table.arg(tr("Coherence Function"), GetWindLabData().coherenceFunction);
    table = table.arg(tr("Location Distribution"), GetWindLabData().spatialDistribution);
    table = table.arg(tr("Mean Wind Profile"), GetWindLabData().meanFunction);
    table = table.arg(tr("Wind Spectrum"), GetWindLabData().spectrumModel);
    table = table.arg(tr("PSD Decomposition Method"), GetWindLabData().cpsdDecompositionMethod);
    table = table.arg(tr("Frequency Distribution"), GetWindLabData().freqencyDistribution);
    table = table.arg(tr("Randomness Provider"), GetWindLabData().randomnessProvider);
    table = table.arg(tr("Modulation Method"), GetWindLabData().modulationFunction);
    table = table.arg(tr("Number of Locations"), QString::number(GetWindLabData().numberOfSpatialPosition));
    table = table.arg(tr("Number of Frequency Increments"), QString::number(GetWindLabData().numberOfFrequency));
    table = table.arg(tr("Frequency Increment"), QString::number(GetWindLabData().frequencyIncrement));
    table = table.arg(tr("Upper Cutoff Frequency"), QString::number(GetWindLabData().maxFrequency));
    table = table.arg(tr("Minimum Frequency"), QString::number(GetWindLabData().minFrequency));
    table = table.arg(tr("Number of Time Increments"), QString::number(GetWindLabData().numberOfTimeIncrements));
    table = table.arg(tr("Time Increment"), QString::number(GetWindLabData().timeIncrement));
    table = table.arg(tr("Minimum Time"), QString::number(GetWindLabData().minTime));

    table = table.arg(tr("Cumulative Probability Distribution"), GetWindLabData().cumulativeProbabilityDistribution);
    table = table.arg(tr("Gust Factor"), GetWindLabData().gustFactor);
    table = table.arg(tr("Kurtosis"), GetWindLabData().kurtosis);
    table = table.arg(tr("Peak Factor"), GetWindLabData().peakFactor);
    table = table.arg(tr("Probability Density Function"), GetWindLabData().probabilityDensityFunction);
    table = table.arg(tr("Roughness"), GetWindLabData().roughness);
    table = table.arg(tr("Shear Velocity Of Flow"), GetWindLabData().shearVelocityOfFlow);
    table = table.arg(tr("Skewness"), GetWindLabData().skewness);
    table = table.arg(tr("Standard Deviation"), GetWindLabData().standardDeviation);
    table = table.arg(tr("Turbulence Intensity"), GetWindLabData().turbulenceIntensity);
    table = table.arg(tr("Turbulence Scale"), GetWindLabData().turbulenceScale);
    table = table.arg(tr("Variance"), GetWindLabData().variance);
    table = table.arg(tr("Wave Passage Effect"), GetWindLabData().wavePassageEffect);

    if(1 == GetWindLabData().direction)
    {
        table = table.arg(tr("Wind Direction"), "Along Wind");
    }
    else if(2 == GetWindLabData().direction)
    {
        table = table.arg(tr("Wind Direction"), "Across Wind");
    }
    else if(3 == GetWindLabData().direction)
    {
        table = table.arg(tr("Wind Direction"), "Vertical Wind");
    }

    if(true == GetWindLabData().stationarity)
    {
        table = table.arg(tr("Stationarity"), "Stationary");
    }
    else
    {
        table = table.arg(tr("Stationarity"), "Non-Stationary");
    }

    if(true == GetWindLabData().uniformModulation)
    {
        table = table.arg(tr("Modulation"), "Uniform");
    }
    else
    {
        table = table.arg(tr("Modulation"), "General");
    }

    if(true == GetWindLabData().gaussianity)
    {
        table = table.arg(tr("Gaussianity"), "Gaussian");
    }
    else
    {
        table = table.arg(tr("Gaussianity"), "Non-Gaussian");
    }

    if(true == GetWindLabData().largeScaleSimulationMode)
    {
        table = table.arg(tr("Large Scale Simulation Mode"), "Yes");
    }
    else
    {
        table = table.arg(tr("Large Scale Simulation Mode"), "No");
    }

    if(true == status)
    {
        table = table.arg(tr("Status"), "Success");
    }
    else
    {
        table = table.arg(tr("Status"), "Failure");
    }

    info += table + "<br>";

    return info;
}


QString RPSWindLabSimulation::logTimeComparisonInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = "<b>[" + dt.toString(Qt::LocalDate) + "&emsp;" +
            ": ''" + name + "'']</b><hr>";


    Utilities::TableColorProfile profile = Utilities::TableColorProfile::Success;
    if (status != true)
        profile = Utilities::TableColorProfile::Failure;

    QString table;
    table =
            Utilities::makeHtmlTable(5, 2, false, profile);

    table = table.arg(tr("Candate 1"), GetWindLabComparisonWorker()->m_candidateList[0]);
    table = table.arg(tr("Candate 2"), GetWindLabComparisonWorker()->m_candidateList[26]);
    table = table.arg(tr("Max Computation Time 1"), QString::number(GetWindLabComparisonWorker()->computationTime1/1000) + " seconds");
    table = table.arg(tr("Max Computation Time 2"), QString::number(GetWindLabComparisonWorker()->computationTime2/1000) + " seconds");

    if(true == status)
    {
        table = table.arg(tr("Status"), "Success");
    }
    else
    {
        table = table.arg(tr("Status"), "Failure");
    }

    info += table + "<br>";

    return info;
}

QString RPSWindLabSimulation::logAccuracyComparisonInfo(bool status, const QString &name) {
    QDateTime dt = QDateTime::currentDateTime();
    QString info = "<b>[" + dt.toString(Qt::LocalDate) + "&emsp;" +
            ": ''" + name + "'']</b><hr>";


    Utilities::TableColorProfile profile = Utilities::TableColorProfile::Success;
    if (status != true)
        profile = Utilities::TableColorProfile::Failure;

    QString table;
    table =
            Utilities::makeHtmlTable(3, 2, false, profile);

    table = table.arg(tr("Candate 1"), GetWindLabComparisonWorker()->m_candidateList[0]);
    table = table.arg(tr("Candate 2"), GetWindLabComparisonWorker()->m_candidateList[26]);
    //table = table.arg(tr("Accuracy"), QString::number(GetWindLabComparisonWorker()->accuracy) + " %");

    if(true == status)
    {
        table = table.arg(tr("Status"), "Success");
    }
    else
    {
        table = table.arg(tr("Status"), "Failure");
    }

    info += table + "<br>";

    return info;
}

void RPSWindLabSimulation::createOutputWorker()
{
    if(2 == windLabData.indexControls)
    {
        saveLineEditIndexes();
    }

    // create a worker
    simulationOutputWorker = new RPSWindLabSimulationOutputWorker(windLabData, information, locationJ, locationK, frequencyIndex, timeIndex);

    // create a new thread and attach the worker to it
    simulationOutputThread = new QThread(this);
    simulationOutputWorker->moveToThread(simulationOutputThread);

    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), simulationOutputWorker, SLOT(stop()), Qt::DirectConnection);

    connect(simulationOutputWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
    connect(simulationOutputWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
    connect(simulationOutputWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

    // add the functionaly to delete the worker after work is done
    connect(simulationOutputWorker, SIGNAL(finished()), simulationOutputWorker, SLOT(deleteLater()));
}

void RPSWindLabSimulation::createSimulationWorker()
{
    if(2 == windLabData.indexControls)
    {
        saveLineEditIndexes();
    }

    // create a worker
    simulationWorker = new RPSWindLabSimulationWorker(windLabData, information, locationJ, locationK, frequencyIndex, timeIndex);

    // create a new thread and attach the worker to it
    simulationThread = new QThread(this);
    simulationWorker->moveToThread(simulationThread);

    // Make the worker watch when the thread starts then let the worker start simulation
    connect(simulationThread, SIGNAL(started()), simulationWorker, SLOT(simulate()));

    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), simulationWorker, SLOT(stop()), Qt::DirectConnection);
    connect(simulationWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
    connect(simulationWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
    connect(simulationWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

    // // add the functionaly to delete the worker after work is done
    // connect(simulationWorker, SIGNAL(finished()), simulationThread, SLOT(quit()));
    // connect(simulationWorker, SIGNAL(finished()), simulationWorker, SLOT(deleteLater()));
    // connect(simulationThread, SIGNAL(finished()), simulationThread, SLOT(deleteLater()));

    // add the functionaly to delete the worker after work is done
    connect(simulationWorker, SIGNAL(finished()), simulationWorker, SLOT(deleteLater()));
}

void RPSWindLabSimulation::createComparisonWorker()
{
    if(2 == windLabData.indexControls)
    {
        saveLineEditIndexes();
    }

    // create a worker
    comparisonWorker = new RPSWindLabComparisonWorker(windLabData,
                                                      information,
                                                      locationJ,
                                                      locationK,
                                                      frequencyIndex,
                                                      timeIndex,
                                                      candidateList,
                                                      resultOutputType,
                                                      minNumberOfLocation,
                                                      minNumberOfFrequency,
                                                      minNumberOfTime,
                                                      numberOfLocationIncrement,
                                                      numberOfFrequencyIncrement,
                                                      numberOfTimeIncrement,
                                                      totalNumber,
                                                      coherence_,
                                                      correlation_,
                                                      frequency_,
                                                      mean_,
                                                      modulation_,
                                                      decomposition_,
                                                      simulation_,
                                                      spatial_,
                                                      randomness_,
                                                      spectrum_,
                                                      cumulativeProbabilityDistribution_,
                                                      gustFactor_,
                                                      kurtosis_,
                                                      peakFactor_,
                                                      probabilityDensityFunction_,
                                                      roughness_,
                                                      shearVelocityOfFlow_,
                                                      skewness_,
                                                      standardDeviation_,
                                                      turbulenceIntensity_,
                                                      turbulenceScale_,
                                                      variance_,
                                                      wavePassageEffect_);

    // create a new thread and attach the worker to it
    comparisonThread = new QThread(this);
    comparisonWorker->moveToThread(comparisonThread);

    // add the functionality to stop the outputing process
    connect(this, SIGNAL(stopped()), comparisonWorker, SLOT(stop()), Qt::DirectConnection);
    connect(comparisonWorker, SIGNAL(sendInformation(QStringList)), this, SLOT(receiveInformation(QStringList)));
    connect(comparisonWorker, SIGNAL(progressBarShow()), this, SLOT(progressBarShowSL()));
    connect(comparisonWorker, SIGNAL(progressBarHide()), this, SLOT(progressBarHideSL()));

    // // add the functionaly to delete the worker after work is done
    // connect(comparisonWorker, SIGNAL(finished()), comparisonThread, SLOT(quit()));
    // connect(comparisonWorker, SIGNAL(finished()), comparisonWorker, SLOT(deleteLater()));
    // connect(comparisonThread, SIGNAL(finished()), comparisonThread, SLOT(deleteLater()));

    // add the functionaly to delete the worker after work is done
    connect(comparisonWorker, SIGNAL(finished()), comparisonWorker, SLOT(deleteLater()));
}

void RPSWindLabSimulation::saveLineEditIndexes()
{
    RPSSimulation *rpsSimulator = (RPSSimulation *)this->parent();
    ApplicationWindow *app = (ApplicationWindow *)rpsSimulator->parent();

    locationJ = app->getLineEditLocJstatusbarbtn()->text().toDouble();
    locationK = app->getLineEditLocKstatusbarbtn()->text().toDouble();
    frequencyIndex = app->getLineEditFreqstatusbarbtn()->text().toDouble();
    timeIndex = app->getLineEditTimstatusbarbtn()->text().toDouble();

    GetWindLabData().locationJ = locationJ;
    GetWindLabData().locationK = locationK;
    GetWindLabData().frequencyIndex = frequencyIndex;
    GetWindLabData().timeIndex = timeIndex;
}
