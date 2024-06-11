#include "PreCompiled.h"

#include <QString>
// WindLab.cpp : Defines the initialization routines for the DLL.
//
#include "WLHorizontalUniformDistribution.h"
#include "WLVerticalUniformDistribution.h"
#include "RPSWLPowerLowProfile.h"
#include "RPSLogarithmicLowProfile.h"
#include "RPSKaimalSpectr.h"
#include "RPSDoubleIndexFrequency.h"
#include "RPSSingleIndexFrequency.h"
#include "RPSDavenportCoherence.h"
#include "CholeskyDecomposition.h"
#include "RPSUniformRandomPhases.h"
#include "RPSRandomPhasesFromFile.h"
#include "SineModulation.h"
#include "ExpoModulation.h"
#include "ThreeParaModulation.h"
#include "RPSDeodatis1987.h"
#include "GeneralSpatialDistribution.h"
#include "RPSKaimalAcrossSpectr.h"
#include "RPSKaimalVerticalSpectr.h"

#include "RPSDavenportSpectrum.h"
#include "RPSHarrisSpectrum.h"
#include "RPSSimuAcrossWindSpectrum.h"
#include "RPSSimuAlongWindSpectrum.h"
#include "RPSSimuVerticalWindSpectrum.h"
#include "RPSvonKarmanAlongWindSpectrum.h"
#include "RPSvonKarmanAcrossWindSpectrum.h"
#include "RPSvonKarmanVerticalWindSpectrum.h"
#include "RPSDHLowProfile.h"
#include "WLUniformDistributionLocations.h"
#include "RPSWavePassageEffect.h"
#include "TargetCorrelation.h"
#include "ZervaModelFrequencyDistribution.h"
#include "RPSKrenkCoherence.h"
#include "RPSTurbulenceIntensityASCE798.h"
#include "WLGridPoints.h"

#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>
#include <Base/Console.h>

std::string strPluginName = "WindLabPlugin";
bool stationarity = true;

PLUGIN_DISPLAY_NAME("WindLabPlugin");
PLUGIN_SYSTEM_NAME("PRSWindLab");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS");
PLUGIN_VERSION("1.00", stationarity);
LABRPS_VERSION("0.001");
API_VERSION("0.001");
PLUGIN_RELEASE_DATE("07/01/2021");
//PLUG_IN_THIS_RP("Random Wind Velocity");

using namespace WindLab;
using namespace WindLabAPI;

///////////////////////General Spatial Distribution/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildGeneralSpatialDistribution()
{
    return new GeneralSpatialDistribution;
}

RPS_PLUGIN_FUNC void DestroyGeneralSpatialDistribution(WindLabAPI::IrpsWLLocationDistribution* r)
{
    delete r;
}

///////////////////////Uniform Distribution/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildUniformSpatialDistribution()
{
    return new WLUniformDistributionLocations;
}

RPS_PLUGIN_FUNC void DestroyUniformSpatialDistribution(WindLabAPI::IrpsWLLocationDistribution* r)
{
    delete r;
}

///////////////////////horizontal uniform location distribution/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildHorizontalDistr()
{
    return new CWLHorizontalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyHorizontalDistr(IrpsWLLocationDistribution* r)
{
    delete r;
}

///////////////////////vertical uniform location distribution/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildVerticalDistr()
{
    return new CWLVerticalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyVerticalDistr(IrpsWLLocationDistribution* r)
{
    delete r;
}

///////////////////////grid points/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildGridPoints()
{
    return new WLGridPoints;
}

RPS_PLUGIN_FUNC void DestroyGridPoints(IrpsWLLocationDistribution* r) {
    delete r;
}

//
///////////////////////mean wind speed power low profile/////////////////
RPS_PLUGIN_FUNC IrpsWLMean* BuildRPSPowerLowProfile()
{
    return new RPSWLPowerLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSPowerLowProfile(IrpsWLMean* r)
{
    delete r;
}


///////////////////////mean wind speed logrithmic low profile/////////////////

RPS_PLUGIN_FUNC IrpsWLMean* BuildRPSLogarithmicLowProfile()
{
    return new RPSLogarithmicLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSLogarithmicLowProfile(IrpsWLMean* r)
{
    delete r;
}

///////////////////////mean wind speed D&H low profile/////////////////

RPS_PLUGIN_FUNC IrpsWLMean* BuildRPSDHLowProfile()
{
    return new CRPSDHLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSDHLowProfile(IrpsWLMean* r)
{
    delete r;
}

////////////////////////Double Index Freq//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution* BuildRPSDoubleIndexFreq()
{
    return new CRPSDoubleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSDoubleIndexFreq(IrpsWLFrequencyDistribution* r)
{
    delete r;
}

////////////////////////Double Index Freq//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution* BuildRPSSingleIndexFreq()
{
    return new WindLab::CRPSSingleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSSingleIndexFreq(IrpsWLFrequencyDistribution* r)
{
    delete r;
}

////////////////////////Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSKaimalSpectr()
{
    return new CRPSKaimalSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalSpectr(IrpsWLXSpectrum* r)
{
    delete r;
}

////////////////////////Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLYSpectrum* BuildRPSKaimalAcrossSpectr()
{
    return new CRPSKaimalAcrossSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalAcrossSpectr(IrpsWLYSpectrum* r)
{
    delete r;
}

////////////////////////Vertical wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLZSpectrum* BuildRPSKaimalVerticalSpectr()
{
    return new CRPSKaimalVerticalSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalVerticalSpectr(IrpsWLZSpectrum* r)
{
    delete r;
}

////////////////////////Davenport Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSDavenportSpectrum()
{
    return new CRPSDavenportSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSDavenportSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

////////////////////////Harris Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSHarrisSpectrum()
{
    return new CRPSHarrisSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSHarrisSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

////////////////////////Simu Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSSimuAlongWindSpectrum()
{
    return new CRPSSimuAlongWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuAlongWindSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

////////////////////////Simu Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLYSpectrum* BuildRPSSimuAcrossWindSpectrum()
{
    return new CRPSSimuAcrossWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuAcrossWindSpectrum(IrpsWLYSpectrum* r)
{
    delete r;
}

////////////////////////Vertical Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLZSpectrum* BuildRPSSimuVerticalWindSpectrum()
{
    return new CRPSSimuVerticalWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuVerticalWindSpectrum(IrpsWLZSpectrum* r)
{
    delete r;
}

//
////////////////////////von Karman Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSVonKarmanAlongWindSpectrum()
{
    return new CRPSvonKarmanAlongWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanAlongWindSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

////////////////////////von Karman Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLYSpectrum* BuildRPSVonKarmanAcrossWindSpectrum()
{
    return new CRPSvonKarmanAcrossWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanAcrossWindSpectrum(IrpsWLYSpectrum* r)
{
    delete r;
}

////////////////////////Vertical von Karman wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLZSpectrum* BuildRPSVonKarmanVerticalWindSpectrum()
{
    return new CRPSvonKarmanVerticalWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanVerticalWindSpectrum(IrpsWLZSpectrum* r)
{
    delete r;
}


//////////////////////////Davenport coherence funcion//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsWLCoherence* BuildRPSDavenportCoh()
{
    return new CRPSDavenportCoherence;
}

RPS_PLUGIN_FUNC void DestroyRPSDavenportCoh(IrpsWLCoherence* r)
{
    delete r;
}


//////////////////////////Cholesky decomposition//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLPSDdecompositionMethod* BuildPSDdecomMethod()
{
    return new CCholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyPSDdecomMethod(IrpsWLPSDdecompositionMethod* r)
{
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLRandomness* BuildRPSUniformRandomPhases()
{
    return new CRPSUniformRandomPhases;
}

RPS_PLUGIN_FUNC void DestroyRPSUniformRandomPhases(IrpsWLRandomness* r)
{
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLRandomness* BuildRPSRandomPhasesFromFile()
{
    return new CRPSRandomPhasesFromFile;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomPhasesFromFile(IrpsWLRandomness* r)
{
    delete r;
}

//////////////////////////Modulation Function//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsWLModulation* BuildSineModulation()
{
    return new CSineModulation;
}

RPS_PLUGIN_FUNC void DestroySineModulation(IrpsWLModulation* r)
{
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLModulation* BuildExpoModulation()
{
    return new CExpoModulation;
}

RPS_PLUGIN_FUNC void DestroyExpoModulation(IrpsWLModulation* r)
{
    delete r;
}

RPS_PLUGIN_FUNC IrpsWLModulation* BuildThreeParaModulation()
{
    return new CThreeParaModulation;
}

RPS_PLUGIN_FUNC void DestroyThreeParaModulation(IrpsWLModulation* r)
{
    delete r;
}

///
RPS_PLUGIN_FUNC IrpsWLSimuMethod* BuildRPSDeodatis1987()
{
    return new CRPSDeodatis1987;
}

RPS_PLUGIN_FUNC void DestroyRPSDeodatis1987(IrpsWLSimuMethod* r)
{
    delete r;
}

RPS_PLUGIN_FUNC IrpsWLWavePassageEffect* BuildRPSWavePassageEffect()
{
    return new CRPSWavePassageEffect;
}

RPS_PLUGIN_FUNC void DestroyRPSWavePassageEffect(IrpsWLWavePassageEffect* r) {
    delete r;
}

RPS_PLUGIN_FUNC IrpsWLTableTool* BuildRPSTargetCorrelation()
{
    return new TargetCorrelation;
}

RPS_PLUGIN_FUNC void DestroyRPSTargetCorrelation(IrpsWLTableTool* r) {
    delete r;
}

RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution* BuildZervaModelFrequencyDistribution()
{
    return new ZervaModelFrequencyDistribution;
}

RPS_PLUGIN_FUNC void DestroyZervaModelFrequencyDistribution(IrpsWLFrequencyDistribution* r)
{
    delete r;
}

RPS_PLUGIN_FUNC IrpsWLCoherence* BuildRPSKrenkCoherence()
{
    return new RPSKrenkCoherence;
}

RPS_PLUGIN_FUNC void DestroyRPSKrenkCoherence(IrpsWLCoherence* r) {
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLTurbulenceIntensity* BuildRPSTurbulenceIntensityASCE798()
{
    return new RPSTurbulenceIntensityASCE798;
}

RPS_PLUGIN_FUNC void DestroyRPSTurbulenceIntensityASCE798(IrpsWLTurbulenceIntensity* r)
{
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
    if (WindLab::GeneralSpatialDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::GeneralSpatialDistribution::init();
    }
    if (WindLab::WLUniformDistributionLocations::getClassTypeId() == Base::Type::badType()) {
        WindLab::WLUniformDistributionLocations::init();
    }
    if (WindLab::CWLHorizontalUniformDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::CWLHorizontalUniformDistribution::init();
    }
    if (WindLab::CWLVerticalUniformDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::CWLVerticalUniformDistribution::init();
    }
    if (WindLab::RPSWLPowerLowProfile::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSWLPowerLowProfile::init();
    }
    if (WindLab::RPSLogarithmicLowProfile::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSLogarithmicLowProfile::init();
    }
    if (WindLab::CRPSDHLowProfile::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDHLowProfile::init();
    }
    if (WindLab::CRPSDoubleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDoubleIndexFrequency::init();
    }
    if (WindLab::CRPSSingleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSingleIndexFrequency::init();
    }
    if (WindLab::CRPSKaimalSpectr::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSKaimalSpectr::init();
    }
    if (WindLab::CRPSKaimalAcrossSpectr::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSKaimalAcrossSpectr::init();
    }
    if (WindLab::CRPSKaimalVerticalSpectr::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSKaimalVerticalSpectr::init();
    }
    if (WindLab::CRPSDavenportSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDavenportSpectrum::init();
    }
    if (WindLab::CRPSHarrisSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSHarrisSpectrum::init();
    }
    if (WindLab::CRPSSimuAlongWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSimuAlongWindSpectrum::init();
    }
    if (WindLab::CRPSSimuAcrossWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSimuAcrossWindSpectrum::init();
    }
    if (WindLab::CRPSSimuVerticalWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSimuVerticalWindSpectrum::init();
    }
    if (WindLab::CRPSvonKarmanAlongWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSvonKarmanAlongWindSpectrum::init();
    }
    if (WindLab::CRPSvonKarmanAcrossWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSvonKarmanAcrossWindSpectrum::init();
    }
    if (WindLab::CRPSvonKarmanVerticalWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSvonKarmanVerticalWindSpectrum::init();
    }
    if (WindLab::CRPSDavenportCoherence::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDavenportCoherence::init();
    }
    if (WindLab::CCholeskyDecomposition::getClassTypeId() == Base::Type::badType()) {
        WindLab::CCholeskyDecomposition::init();
    }
    if (WindLab::CRPSUniformRandomPhases::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSUniformRandomPhases::init();
    }
    if (WindLab::CRPSRandomPhasesFromFile::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSRandomPhasesFromFile::init();
    }
    if (WindLab::CSineModulation::getClassTypeId() == Base::Type::badType()) {
        WindLab::CSineModulation::init();
    }
    if (WindLab::CExpoModulation::getClassTypeId() == Base::Type::badType()) {
        WindLab::CExpoModulation::init();
    }
    if (WindLab::CThreeParaModulation::getClassTypeId() == Base::Type::badType()) {
        WindLab::CThreeParaModulation::init();
    }
    if (WindLab::CRPSDeodatis1987::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDeodatis1987::init();
    }
    if (WindLab::CRPSWavePassageEffect::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSWavePassageEffect::init();
    }
    if (WindLab::TargetCorrelation::getClassTypeId() == Base::Type::badType()) {
        WindLab::TargetCorrelation::init();
    }
    if (WindLab::ZervaModelFrequencyDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::ZervaModelFrequencyDistribution::init();
    }
    if (WindLab::RPSKrenkCoherence::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSKrenkCoherence::init();
    }
    if (WindLab::RPSTurbulenceIntensityASCE798::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSTurbulenceIntensityASCE798::init();
    }
    if (WindLab::WLGridPoints::getClassTypeId() == Base::Type::badType()) {
        WindLab::WLGridPoints::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeLocationDistribution(("General Distribution"), strPluginName, ("LabRPS"), ("LabRPS"), ("LabRPS"), ("01/01/2023"), ("1.00"), stationarity);
    InitializeLocationDistribution(("Uniform Distribution"), strPluginName, ("LabRPS"), ("LabRPS"),("LabRPS"), ("01/01/2023"), ("1.00"), stationarity);
    InitializeLocationDistribution("Horizontal Distribution", strPluginName, "LabRPS", "LabRPS", "LabRPS", "01/01/2023", "1.00", stationarity);
    InitializeLocationDistribution("Vertical Distribution", strPluginName, "LabRPS", "LabRPS", "LabRPS", "01/01/2023", "1.00", stationarity);
    InitializeLocationDistribution(("Grid Points"), strPluginName, ("LabRPS"), ("LabRPS"), ("LabRPS"), ("01/01/2023"), ("1.00"), stationarity);
    InitializeMean("RPS Power Low", strPluginName, "Analysis of the wind field characteristics induced by the 2019 Typhoon Bailu for the high-speed railway bridge crossing China�s southeast bay", "https://doi.org/10.1016/j.jweia.2021.104557", "Gonglian Dai, Zhiwei Xu, Y. Frank Chen, Richard G.J. Flay, Huiming Rao", "01/01/2023", "1.00", stationarity);
    InitializeMean("RPS Logarithmic Low", strPluginName, "Analysis of the wind field characteristics induced by the 2019 Typhoon Bailu for the high-speed railway bridge crossing China�s southeast bay", "https://doi.org/10.1016/j.jweia.2021.104557", "Gonglian Dai, Zhiwei Xu, Y. Frank Chen, Richard G.J. Flay, Huiming Rao", "01/01/2023", "1.00", stationarity);
    InitializeMean("RPS Deaves and Harris", strPluginName, "Advanced Structural Wind Engineering", "https://link.springer.com/book/10.1007/978-4-431-54337-4", "Yukio Tamura, Ahsan Kareem", " Springer Japan 2013", "1.00", stationarity);
    InitializeXSpectrum(("Kaimal Along Wind Spectrum"), strPluginName, "Spectral characteristics of surface-layer turbulence", "To be given", "Kaimal, J. C. et al", "In 1972", "1.00", stationarity);
    InitializeYSpectrum(("Kaimal Across Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeZSpectrum(("Kaimal Vertical Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeXSpectrum(("Davenport Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeXSpectrum(("Harris Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeXSpectrum(("Simu Along Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeYSpectrum(("Simu Across Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeZSpectrum(("Simu Vertical Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeXSpectrum(("von Karman Along Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeYSpectrum(("von Karman Across Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeZSpectrum(("von Karman Vertical Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);

    InitializeFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Koffi Daniel"), "01/01/2023", "1.00", stationarity);
    InitializeCoherence(("Davenport Coherence"), strPluginName, "The dependence of wind load upon meteorological parameters", ("Uniform Random Phases"), "Davenport, A. G.", "01/01/2023", "1.00", stationarity);
    InitializePSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), "Koffi Daniel", "11/11/2011", "1.00", stationarity);
    InitializeRandomness(("Uniform Random Phases"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeRandomness(("Random Phases Importer"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeModulation(("RPS Three Parameters Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeModulation(("RPS Exponential Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeModulation(("RPS Sine Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeSimuMethod(("Deodatis et al 1987"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeWavePassageEffect(("RPS Wave Passage Effect"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeTableTool(("RPS Target Correlation"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeFrequencyDistribution(("Zerva Frequency Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00", stationarity);
    InitializeCoherence(("Krenk Coherence"), strPluginName, "The dependence of wind load upon meteorological parameters", ("Uniform Random Phases"), "Davenport, A. G.", "01/01/2023", "1.00", stationarity);
    InitializeTurbulenceIntensity(("ASCE Turbulence Intensity"), strPluginName, "The dependence of wind load upon meteorological parameters", ("Uniform Random Phases"), "Davenport, A. G.", "01/01/2023", "1.00", stationarity);

    
    return 1;
}


INSTALL_PLUGIN()
{

    Base::Console().Warning("This is from WindLab Plugin");

    RegisterLocationDistribution(("General Distribution"), strPluginName, ("The object allows to add a spatial point with x, y, and z coordinates."), BuildGeneralSpatialDistribution, DestroyGeneralSpatialDistribution);
    RegisterLocationDistribution(("Uniform Distribution"), strPluginName, ("The object allows to add a spatial point with x, y, and z coordinates."), BuildUniformSpatialDistribution, DestroyUniformSpatialDistribution);
    RegisterLocationDistribution(("Horizontal Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a horizontal axis"), BuildHorizontalDistr, DestroyHorizontalDistr);
    RegisterLocationDistribution(("Vertical Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a vertical axis"), BuildVerticalDistr, DestroyVerticalDistr);
    RegisterLocationDistribution(("Grid Points"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a vertical axis"), BuildGridPoints, DestroyGridPoints);
    RegisterMean(("RPS Power Low"), strPluginName, ("This is the power low mean wind profile"), BuildRPSPowerLowProfile, DestroyRPSPowerLowProfile);
    RegisterMean(("RPS Logarithmic Low"), strPluginName, ("This is the logarithmic low mean wind profile"), BuildRPSLogarithmicLowProfile, DestroyRPSLogarithmicLowProfile);
    RegisterMean("RPS Deaves and Harris", strPluginName, ("This is the Deaves and Harris model for mean wind profile"), BuildRPSDHLowProfile, DestroyRPSDHLowProfile);

    RegisterXSpectrum(("Kaimal Along Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSKaimalSpectr, DestroyRPSKaimalSpectr);
    RegisterYSpectrum(("Kaimal Across Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSKaimalAcrossSpectr, DestroyRPSKaimalAcrossSpectr);
    RegisterZSpectrum(("Kaimal Vertical Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSKaimalVerticalSpectr, DestroyRPSKaimalVerticalSpectr);

    RegisterXSpectrum(("Davenport Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSDavenportSpectrum, DestroyRPSDavenportSpectrum);
    RegisterXSpectrum(("Harris Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSHarrisSpectrum, DestroyRPSHarrisSpectrum);
    RegisterXSpectrum(("Simu Along Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSSimuAlongWindSpectrum, DestroyRPSSimuAlongWindSpectrum);
    RegisterYSpectrum(("Simu Across Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSSimuAcrossWindSpectrum, DestroyRPSSimuAcrossWindSpectrum);
    RegisterZSpectrum(("Simu Vertical Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSSimuVerticalWindSpectrum, DestroyRPSSimuVerticalWindSpectrum);
    RegisterXSpectrum(("von Karman Along Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSVonKarmanAlongWindSpectrum, DestroyRPSVonKarmanAlongWindSpectrum);
    RegisterYSpectrum(("von Karman Across Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSVonKarmanAcrossWindSpectrum, DestroyRPSVonKarmanAcrossWindSpectrum);
    RegisterZSpectrum(("von Karman Vertical Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSVonKarmanVerticalWindSpectrum, DestroyRPSVonKarmanVerticalWindSpectrum);

    RegisterFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Single index frequency distribution"), BuildRPSDoubleIndexFreq, DestroyRPSDoubleIndexFreq);
    RegisterFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Double index frequency distribution. This may be useful when ergodic wind is desired"), BuildRPSSingleIndexFreq, DestroyRPSSingleIndexFreq);
    RegisterCoherence(("Davenport Coherence"), strPluginName, ("This is the Davenport coherence model"), BuildRPSDavenportCoh, DestroyRPSDavenportCoh);
    RegisterPSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("The cholesky decomposition of hermitian real matrix"), BuildPSDdecomMethod, DestroyPSDdecomMethod);
    RegisterRandomness(("Uniform Random Phases"), strPluginName, ("Uniform random phase sets"), BuildRPSUniformRandomPhases, DestroyRPSUniformRandomPhases);
    RegisterRandomness(("Random Phases Importer"), strPluginName, ("This object allow the user to import the random phases from file"), BuildRPSRandomPhasesFromFile, DestroyRPSRandomPhasesFromFile);
    RegisterModulation(("RPS Three Parameters Model"), strPluginName, ("Three Parameters Model uniform modulation function"), BuildThreeParaModulation, DestroyThreeParaModulation);
    RegisterModulation(("RPS Exponential Model"), strPluginName, ("Exponential Model uniform modulation function"), BuildExpoModulation, DestroyExpoModulation);
    RegisterModulation(("RPS Sine Model"), strPluginName, ("Sine Model uniform modulation function"), BuildSineModulation, DestroySineModulation);
    RegisterSimuMethod(("Deodatis et al 1987"), strPluginName, ("Wind simulation method by Deodatis et al 1987"), BuildRPSDeodatis1987, DestroyRPSDeodatis1987);
    RegisterWavePassageEffect(("RPS Wave Passage Effect"), strPluginName, ("Wind simulation method by Deodatis et al 1987"), BuildRPSWavePassageEffect, DestroyRPSWavePassageEffect);
    RegisterTableTool(("RPS Target Correlation"), strPluginName, ("Wind simulation method by Deodatis et al 1987"), BuildRPSTargetCorrelation, DestroyRPSTargetCorrelation);
    RegisterFrequencyDistribution(("Zerva Frequency Distribution"), strPluginName, ("Single index frequency distribution"), BuildZervaModelFrequencyDistribution, DestroyZervaModelFrequencyDistribution);
    RegisterCoherence(("Krenk Coherence"), strPluginName, ("This is the Davenport coherence model"), BuildRPSKrenkCoherence, DestroyRPSKrenkCoherence);
    RegisterTurbulenceIntensity(("ASCE Turbulence Intensity"), strPluginName, ("This is the Davenport coherence model"), BuildRPSTurbulenceIntensityASCE798, DestroyRPSTurbulenceIntensityASCE798);

    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterLocationDistribution(("General Distribution"), strPluginName);
    UnregisterLocationDistribution(("Uniform Distribution"), strPluginName);
    UnregisterLocationDistribution(("Horizontal Distribution"), strPluginName);
    UnregisterLocationDistribution(("Vertical Distribution"), strPluginName);
    UnregisterLocationDistribution(("Grid Points"), strPluginName);

    UnregisterMean(("RPS Power Low"), strPluginName);
    UnregisterMean(("RPS Logarithmic Low"), strPluginName);
    UnregisterMean("RPS Deaves and Harris", strPluginName);
    UnregisterXSpectrum(("Kaimal Along Wind Spectrum"), strPluginName);
    UnregisterYSpectrum(("Kaimal Across Wind Spectrum"), strPluginName);
    UnregisterZSpectrum(("Kaimal Vertical Wind Spectrum"), strPluginName);

    UnregisterXSpectrum(("Davenport Wind Spectrum"), strPluginName);
    UnregisterXSpectrum(("Harris Wind Spectrum"), strPluginName);
    UnregisterXSpectrum(("Simu Along Wind Spectrum"), strPluginName);
    UnregisterYSpectrum(("Simu Across Wind Spectrum"), strPluginName);
    UnregisterZSpectrum(("Simu Vertical Wind Spectrum"), strPluginName);
    UnregisterXSpectrum(("von Karman Along Wind Spectrum"), strPluginName);
    UnregisterYSpectrum(("von Karman Across Wind Spectrum"), strPluginName);
    UnregisterZSpectrum(("von Karman Vertical Wind Spectrum"), strPluginName);

    UnregisterFrequencyDistribution(("Double Index Frequency"), strPluginName);
    UnregisterFrequencyDistribution(("Single Index Frequency"), strPluginName);
    UnregisterCoherence(("Davenport Coherence"), strPluginName);
    UnregisterPSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName);
    UnregisterRandomness(("Uniform Random Phases"), strPluginName);
    UnregisterRandomness(("Random Phases Importer"), strPluginName);
    UnregisterModulation(("RPS Three Parameters Model"), strPluginName);
    UnregisterModulation(("RPS Exponential Model"), strPluginName);
    UnregisterModulation(("RPS Sine Model"), strPluginName);
    UnregisterSimuMethod(("Deodatis et al 1987"), strPluginName);
    UnregisterSimuMethod(("RPS Wave Passage Effect"), strPluginName);
    UnregisterTableTool(("RPS Target Correlation"), strPluginName);
    UnregisterFrequencyDistribution(("Zerva Frequency Distribution"), strPluginName);
    UnregisterCoherence(("Krenk Coherence"), strPluginName);
    UnregisterCoherence(("ASCE Turbulence Intensity"), strPluginName);

    return 1;
}




