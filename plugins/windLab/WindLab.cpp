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

#include "RPSWindLabpluginAPI.h"


QString strPluginName = ("windLab");


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


PLUGIN_DISPLAY_NAME("windLab");
PLUGIN_SYSTEM_NAME("PRSWindLab");
RANDOM_PHENOMENON("Random Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("1.00");
API_VERSION("1.00");
PLUGIN_RELEASE_DATE("07/01/2021");
//PLUG_IN_THIS_RP("Random Wind Velocity");

///////////////////////General Spatial Distribution/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution *BuildGeneralSpatialDistribution()
{
    return new GeneralSpatialDistribution;
}

RPS_PLUGIN_FUNC void DestroyGeneralSpatialDistribution(IrpsWLLocationDistribution *r)
{
    delete r;
}

///////////////////////horizontal uniform location distribution/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution *BuildHorizontalDistr()
{
    return new CWLHorizontalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyHorizontalDistr(IrpsWLLocationDistribution *r)
{
    delete r;
}

///////////////////////vertical uniform location distribution/////////////////
RPS_PLUGIN_FUNC IrpsWLLocationDistribution *BuildVerticalDistr()
{
    return new CWLVerticalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyVerticalDistr(IrpsWLLocationDistribution *r)
{
    delete r;
}

///////////////////////mean wind speed power low profile/////////////////
RPS_PLUGIN_FUNC IrpsWLMean *BuildRPSPowerLowProfile()
{
    return new CRPSWLPowerLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSPowerLowProfile(IrpsWLMean *r)
{
    delete r;
}

///////////////////////mean wind speed logrithmic low profile/////////////////

RPS_PLUGIN_FUNC IrpsWLMean *BuildRPSLogarithmicLowProfile()
{
    return new CRPSLogarithmicLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSLogarithmicLowProfile(IrpsWLMean *r)
{
    delete r;
}

///////////////////////mean wind speed D&H low profile/////////////////

RPS_PLUGIN_FUNC IrpsWLMean *BuildRPSDHLowProfile()
{
    return new CRPSDHLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSDHLowProfile(IrpsWLMean *r)
{
    delete r;
}

////////////////////////Double Index Freq//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution *BuildRPSDoubleIndexFreq()
{
    return new CRPSDoubleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSDoubleIndexFreq(IrpsWLFrequencyDistribution *r)
{
    delete r;
}

////////////////////////Double Index Freq//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution *BuildRPSSingleIndexFreq()
{
    return new CRPSSingleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSSingleIndexFreq(IrpsWLFrequencyDistribution *r)
{
    delete r;
}

////////////////////////Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum *BuildRPSKaimalSpectr()
{
    return new CRPSKaimalSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalSpectr(IrpsWLXSpectrum *r)
{
    delete r;
}

////////////////////////Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLYSpectrum *BuildRPSKaimalAcrossSpectr()
{
    return new CRPSKaimalAcrossSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalAcrossSpectr(IrpsWLYSpectrum *r)
{
    delete r;
}

////////////////////////Vertical wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLZSpectrum *BuildRPSKaimalVerticalSpectr()
{
    return new CRPSKaimalVerticalSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalVerticalSpectr(IrpsWLZSpectrum *r)
{
    delete r;
}

////////////////////////Davenport Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum *BuildRPSDavenportSpectrum()
{
    return new CRPSDavenportSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSDavenportSpectrum(IrpsWLXSpectrum *r)
{
    delete r;
}

////////////////////////Harris Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum *BuildRPSHarrisSpectrum()
{
    return new CRPSHarrisSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSHarrisSpectrum(IrpsWLXSpectrum *r)
{
    delete r;
}

////////////////////////Simu Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum *BuildRPSSimuAlongWindSpectrum()
{
    return new CRPSSimuAlongWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuAlongWindSpectrum(IrpsWLXSpectrum *r)
{
    delete r;
}

////////////////////////Simu Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLYSpectrum *BuildRPSSimuAcrossWindSpectrum()
{
    return new CRPSSimuAcrossWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuAcrossWindSpectrum(IrpsWLYSpectrum *r)
{
    delete r;
}

////////////////////////Vertical Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLZSpectrum *BuildRPSSimuVerticalWindSpectrum()
{
    return new CRPSSimuVerticalWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuVerticalWindSpectrum(IrpsWLZSpectrum *r)
{
    delete r;
}

//
////////////////////////von Karman Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLXSpectrum *BuildRPSVonKarmanAlongWindSpectrum()
{
    return new CRPSvonKarmanAlongWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanAlongWindSpectrum(IrpsWLXSpectrum *r)
{
    delete r;
}

////////////////////////von Karman Across wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLYSpectrum *BuildRPSVonKarmanAcrossWindSpectrum()
{
    return new CRPSvonKarmanAcrossWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanAcrossWindSpectrum(IrpsWLYSpectrum *r)
{
    delete r;
}

////////////////////////Vertical von Karman wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLZSpectrum *BuildRPSVonKarmanVerticalWindSpectrum()
{
    return new CRPSvonKarmanVerticalWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanVerticalWindSpectrum(IrpsWLZSpectrum *r)
{
    delete r;
}


////////////////////////Davenport coherence funcion//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsWLCoherence *BuildRPSDavenportCoh()
{
    return new CRPSDavenportCoherence;
}

RPS_PLUGIN_FUNC void DestroyRPSDavenportCoh(IrpsWLCoherence *r)
{
    delete r;
}


////////////////////////Cholesky decomposition//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsWLPSDdecompositionMethod *BuildPSDdecomMethod()
{
	return new CCholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyPSDdecomMethod(IrpsWLPSDdecompositionMethod *r)
{
	delete r;
}


RPS_PLUGIN_FUNC IrpsWLRandomness *BuildRPSUniformRandomPhases()
{
    return new CRPSUniformRandomPhases;
}

RPS_PLUGIN_FUNC void DestroyRPSUniformRandomPhases(IrpsWLRandomness *r)
{
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLRandomness *BuildRPSRandomPhasesFromFile()
{
    return new CRPSRandomPhasesFromFile;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomPhasesFromFile(IrpsWLRandomness *r)
{
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLModulation *BuildSineModulation()
{
    return new CSineModulation;
}

RPS_PLUGIN_FUNC void DestroySineModulation(IrpsWLModulation *r)
{
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLModulation *BuildExpoModulation()
{
    return new CExpoModulation;
}

RPS_PLUGIN_FUNC void DestroyExpoModulation(IrpsWLModulation *r)
{
    delete r;
}

RPS_PLUGIN_FUNC IrpsWLModulation *BuildThreeParaModulation()
{
    return new CThreeParaModulation;
}

RPS_PLUGIN_FUNC void DestroyThreeParaModulation(IrpsWLModulation *r)
{
    delete r;
}


RPS_PLUGIN_FUNC IrpsWLSimuMethod *BuildRPSDeodatis1987()
{
    return new CRPSDeodatis1987;
}

RPS_PLUGIN_FUNC void DestroyRPSDeodatis1987(IrpsWLSimuMethod *r)
{
    delete r;
}

PLUGIN_INIT()
{
    InitializeLocationDistribution("General Distribution", strPluginName, "LabRPS", "LabRPS", "LabRPS", "01/01/2023", "1.00");
    InitializeLocationDistribution("Horizontal Distribution", strPluginName, "LabRPS", "LabRPS", "LabRPS", "01/01/2023", "1.00");
    InitializeLocationDistribution("Vertical Distribution", strPluginName, "LabRPS", "LabRPS", "LabRPS", "01/01/2023", "1.00");
    InitializeMean("RPS Power Low", strPluginName, "Analysis of the wind field characteristics induced by the 2019 Typhoon Bailu for the high-speed railway bridge crossing China’s southeast bay", "https://doi.org/10.1016/j.jweia.2021.104557", "Gonglian Dai, Zhiwei Xu, Y. Frank Chen, Richard G.J. Flay, Huiming Rao", "01/01/2023", "1.00");
    InitializeMean("RPS Logarithmic Low", strPluginName, "Analysis of the wind field characteristics induced by the 2019 Typhoon Bailu for the high-speed railway bridge crossing China’s southeast bay", "https://doi.org/10.1016/j.jweia.2021.104557", "Gonglian Dai, Zhiwei Xu, Y. Frank Chen, Richard G.J. Flay, Huiming Rao", "01/01/2023", "1.00");
    InitializeMean("RPS Deaves and Harris", strPluginName, "Advanced Structural Wind Engineering", "https://link.springer.com/book/10.1007/978-4-431-54337-4", "Yukio Tamura, Ahsan Kareem", " Springer Japan 2013", "1.00");
    InitializeXSpectrum(("Kaimal Along Wind Spectrum"), strPluginName, "Spectral characteristics of surface-layer turbulence", "To be given", "Kaimal, J. C. et al", "In 1972", "1.00");
    InitializeYSpectrum(("Kaimal Across Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeZSpectrum(("Kaimal Vertical Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeXSpectrum(("Davenport Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeXSpectrum(("Harris Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeXSpectrum(("Simu Along Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeYSpectrum(("Simu Across Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeZSpectrum(("Simu Vertical Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeXSpectrum(("von Karman Along Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeYSpectrum(("von Karman Across Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeZSpectrum(("von Karman Vertical Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");

    InitializeFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Koffi Daniel"), "01/01/2023", "1.00");
    InitializeCoherence(("Davenport Coherence"), strPluginName, "The dependence of wind load upon meteorological parameters", ("Uniform Random Phases"), "Davenport, A. G.", "01/01/2023", "1.00");
    InitializePSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), "Koffi Daniel", "11/11/2011", "1.00");
    InitializeRandomness(("Uniform Random Phases"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeRandomness(("Random Phases Importer"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeModulation(("RPS Three Parameters Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeModulation(("RPS Exponential Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeModulation(("RPS Sine Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");
    InitializeSimuMethod(("Deodatis et al 1987"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), "01/01/2023", "1.00");

	return 1;
}


INSTALL_PLUGIN()
{
    RegisterLocationDistribution(("General Distribution"), strPluginName, ("The object allows to add a spatial point with x, y, and z coordinates."), BuildGeneralSpatialDistribution, DestroyGeneralSpatialDistribution);
    RegisterLocationDistribution(("Horizontal Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a horizontal axis"), BuildHorizontalDistr, DestroyHorizontalDistr);
    RegisterLocationDistribution(("Vertical Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a vertical axis"), BuildVerticalDistr, DestroyVerticalDistr);
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

    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterLocationDistribution(("General Distribution"), strPluginName);
    UnregisterLocationDistribution(("Horizontal Distribution"), strPluginName);
    UnregisterLocationDistribution(("Vertical Distribution"), strPluginName);
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

	return 1;
}


