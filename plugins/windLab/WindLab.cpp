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
#include "RPSWindLabpluginAPI.h"
#include "GeneralSpatialDistribution.h"


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
	InitializeLocationDistribution(("General Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeLocationDistribution(("Horizontal Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeLocationDistribution(("Vertical Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeMean(("RPS Power Low"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeMean(("RPS Logarithmic Low"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeXSpectrum(("Kaimail Along Wind Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Koffi Daniel"), ("Uniform Random Phases"));
	InitializeCoherence(("Davenport Coherence"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializePSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Koffi Daniel"), ("11/11/2011"));
	InitializeRandomness(("Uniform Random Phases"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeRandomness(("Random Phases Importer"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeModulation(("RPS Three Parameters Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeModulation(("RPS Exponential Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeModulation(("RPS Sine Model"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeSimuMethod(("Deodatis et al 1987"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));

	return 1;
}


INSTALL_PLUGIN()
{
	RegisterLocationDistribution(("General Distribution"), strPluginName, ("The object allows to add a spatial point with x, y, and z coordinates."), BuildGeneralSpatialDistribution, DestroyGeneralSpatialDistribution);	
	RegisterLocationDistribution(("Horizontal Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a horizontal axis"), BuildHorizontalDistr, DestroyHorizontalDistr);	
	RegisterLocationDistribution(("Vertical Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a vertical axis"), BuildVerticalDistr, DestroyVerticalDistr);
	RegisterMean(("RPS Power Low"), strPluginName, ("This is the power low mean wind profile"), BuildRPSPowerLowProfile, DestroyRPSPowerLowProfile);
	RegisterMean(("RPS Logarithmic Low"), strPluginName, ("This is the logarithmic low mean wind profile"), BuildRPSLogarithmicLowProfile, DestroyRPSLogarithmicLowProfile);
	RegisterXSpectrum(("Kaimail Along Wind Spectrum"), strPluginName, ("Allow wind spectrum according to Kaimal"), BuildRPSKaimalSpectr, DestroyRPSKaimalSpectr);
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
	UnregisterXSpectrum(("Kaimail Along Wind Spectrum"), strPluginName);
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


