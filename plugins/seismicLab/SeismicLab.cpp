// SeismicLab.cpp : Defines the initialization routines for the DLL.
//
#include "RPSSeismicLabpluginAPI.h"
#include "RPSDeodatis1996.h"
#include "RPSSLUniformRandomPhases.h"
#include "RPSSLRandomPhasesFromFile.h"
#include "AbrahamsonCoherence.h"
#include "BogdanoffGoldbergBernarModulation.h"
#include "CloughPenzienSpectrum.h"
#include "HarichandranVanmarcheCoherence.h"
#include "JenningEtAlModulation.h"
#include "KanaiTajimiSpectrum.h"
#include "RPSSLDoubleIndexFrequency.h"
#include "RPSSLSingleIndexFrequency.h"
#include "SLCholeskyDecomposition.h"
#include "SLHorizontalUniformDistribution.h"
#include "SLVerticalUniformDistribution.h"
#include <QMessageBox>

QString strPluginName = ("seismicLab");

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

PLUGIN_DISPLAY_NAME("seismicLab");
PLUGIN_SYSTEM_NAME("seismicLab");
RANDOM_PHENOMENON("Random Ground Motion");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("1.00");
API_VERSION("1.00");
PLUGIN_RELEASE_DATE("07/01/2021");

RPS_PLUGIN_FUNC IrpsSLSimulationMethod *BuildRPSDeodatis1996()
{
	return new CRPSDeodatis1996;
}

RPS_PLUGIN_FUNC void DestroyRPSDeodatis1996(IrpsSLSimulationMethod *r)
{
	delete r;
}

///////////////////////////////////////////////////////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsSLRandomness *BuildRPSUniformRandomPhases()
{
	return new CRPSSLUniformRandomPhases;
}

RPS_PLUGIN_FUNC void DestroyRPSUniformRandomPhases(IrpsSLRandomness *r)
{
	delete r;
}

/////////////////////////////////////////////////////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsSLRandomness *BuildRPSRandomPhasesFromFile()
{
	return new CRPSSLRandomPhasesFromFile;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomPhasesFromFile(IrpsSLRandomness *r)
{
	delete r;
}

/////////////////////////////////////////////////////////////////////////////////

///////////////////////horizontal uniform location distribution/////////////////
RPS_PLUGIN_FUNC IrpsSLLocationDistribution *BuildHorizontalDistr()
{
	return new CWLHorizontalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyHorizontalDistr(IrpsSLLocationDistribution *r)
{
	delete r;
}

///////////////////////vertical uniform location distribution/////////////////
RPS_PLUGIN_FUNC IrpsSLLocationDistribution *BuildVerticalDistr()
{
	return new CSLVerticalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyVerticalDistr(IrpsSLLocationDistribution *r)
{
	delete r;
}

////////////////////////Double Index Freq//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSLFrequencyDistribution *BuildRPSDoubleIndexFreq()
{
	return new CRPSSLDoubleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSDoubleIndexFreq(IrpsSLFrequencyDistribution *r)
{
	delete r;
}

////////////////////////Double Index Freq//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsSLFrequencyDistribution *BuildRPSSingleIndexFreq()
{
	return new CRPSSLSingleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSSingleIndexFreq(IrpsSLFrequencyDistribution *r)
{
	delete r;
}

////////////////////////Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSLXSpectrum *BuildCloughPenzienSpectrum()
{
	return new CCloughPenzienSpectrum;
}

RPS_PLUGIN_FUNC void DestroyCloughPenzienSpectrum(IrpsSLXSpectrum *r)
{
	delete r;
}

////////////////////////Along wind target spectrum//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSLXSpectrum *BuildKanaiTajimiSpectrum()
{
	return new CKanaiTajimiSpectrum;
}

RPS_PLUGIN_FUNC void DestroyKanaiTajimiSpectrum(IrpsSLXSpectrum *r)
{
	delete r;
}

////////////////////////Davenport coherence funcion//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsSLCoherence *BuildAbrahamsonCoherence()
{
	return new CAbrahamsonCoherence;
}

RPS_PLUGIN_FUNC void DestroyAbrahamsonCoherence(IrpsSLCoherence *r)
{
	delete r;
}

////////////////////////Davenport coherence funcion//////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsSLCoherence *BuildHarichandranVanmarcheCoherence()
{
	return new CHarichandranVanmarcheCoherence;
}

RPS_PLUGIN_FUNC void DestroyHarichandranVanmarcheCoherence(IrpsSLCoherence *r)
{
	delete r;
}

////////////////////////Cholesky decomposition//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSLPSDdecompositionMethod *BuildPSDCholeskyDecomposition()
{
	return new CSLCholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyPSDCholeskyDecomposition(IrpsSLPSDdecompositionMethod *r)
{
	delete r;
}

///////////////////////////////////////////////////////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsSLModulation *BuildBogdanoffGoldbergBernarModulation()
{
	return new CBogdanoffGoldbergBernarModulation;
}

RPS_PLUGIN_FUNC void DestroyBogdanoffGoldbergBernarModulation(IrpsSLModulation *r)
{
	delete r;
}

/////////////////////////////////////////////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSLModulation *BuildJenningEtAlModulation()
{
	return new CJenningEtAlModulation;
}

RPS_PLUGIN_FUNC void DestroyJenningEtAlModulation(IrpsSLModulation *r)
{
	delete r;
}




PLUGIN_INIT()
{
	InitializeSLSimulationMethod(("Deodatis et al 1996"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeRandomness(("Uniform Random Phases"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeRandomness(("Random Phases Importer"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeLocationDistribution(("Horizontal Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeLocationDistribution(("Vertical Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeXSpectrum(("Clough-Penzien Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeXSpectrum(("Kanai-Tajmi Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeCoherence(("Harichandran-Vanmarche Coherence"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeCoherence(("Abrahamson Coherence"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializePSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeModulation(("Bogdanoff-Goldberg-Bernard Modulation function"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeModulation(("Jennings et al. Modulation function"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));

	return 1;
}


INSTALL_PLUGIN()
{
	RegisterSLSimulationMethod(("Deodatis et al 1996"), strPluginName, ("Ground motion simulation method by Deodatis et al 1996"), BuildRPSDeodatis1996, DestroyRPSDeodatis1996);
	RegisterRandomness(("Uniform Random Phases"), strPluginName, ("Uniform random phase sets"), BuildRPSUniformRandomPhases, DestroyRPSUniformRandomPhases);
	RegisterRandomness(("Random Phases Importer"), strPluginName, ("This object allow the user to import the random phases from file"), BuildRPSRandomPhasesFromFile, DestroyRPSRandomPhasesFromFile);
	RegisterLocationDistribution(("Horizontal Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a horizontal axis"), BuildHorizontalDistr, DestroyHorizontalDistr);
	RegisterLocationDistribution(("Vertical Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a vertical axis"), BuildVerticalDistr, DestroyVerticalDistr);
	RegisterXSpectrum(("Clough-Penzien Spectrum"), strPluginName, ("Allow wind spectrum according to Clough-Penzien"), BuildCloughPenzienSpectrum, DestroyCloughPenzienSpectrum);
	RegisterXSpectrum(("Kanai-Tajmi Spectrum"), strPluginName, ("Allow wind spectrum according to Kanai-Tajmi"), BuildKanaiTajimiSpectrum, DestroyKanaiTajimiSpectrum);	
	RegisterFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Single index frequency distribution"), BuildRPSDoubleIndexFreq, DestroyRPSDoubleIndexFreq);
	RegisterFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Double index frequency distribution. This may be useful when ergodic wind is desired"), BuildRPSSingleIndexFreq, DestroyRPSSingleIndexFreq);	
	RegisterCoherence(("Abrahamson Coherence"), strPluginName, ("This is the Harichandran-Vanmarche coherence model"), BuildAbrahamsonCoherence, DestroyAbrahamsonCoherence);
	RegisterCoherence(("Harichandran-Vanmarche Coherence"), strPluginName, ("This is the Abrahamson coherence model"), BuildHarichandranVanmarcheCoherence, DestroyHarichandranVanmarcheCoherence);
	RegisterPSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("The cholesky decomposition of hermitian real matrix"), BuildPSDCholeskyDecomposition, DestroyPSDCholeskyDecomposition);		
	RegisterModulation(("Bogdanoff-Goldberg-Bernard Modulation function"), strPluginName, ("Bogdanoff-Goldberg-Bernard uniform modulation function"), BuildBogdanoffGoldbergBernarModulation, DestroyBogdanoffGoldbergBernarModulation);
	RegisterModulation(("Jennings et al. Modulation function"), strPluginName, ("Jennings et al. uniform modulation function"), BuildJenningEtAlModulation, DestroyJenningEtAlModulation);

	return 1;
}

UNINSTALL_PLUGIN()
{
	UnRegisterSLSimulationMethod(("Deodatis et al 1996"), strPluginName);
	UnregisterRandomness(("Uniform Random Phases"), strPluginName);
	UnregisterRandomness(("Random Phases Importer"), strPluginName);
	UnregisterLocationDistribution(("Horizontal Distribution"), strPluginName);
	UnregisterLocationDistribution(("Vertical Distribution"), strPluginName);
	UnregisterXSpectrum(("Clough-Penzien Spectrum"), strPluginName);
	UnregisterXSpectrum(("Kanai-Tajmi Spectrum"), strPluginName);
	UnregisterFrequencyDistribution(("Double Index Frequency"), strPluginName);
	UnregisterFrequencyDistribution(("Single Index Frequency"), strPluginName);
	UnregisterCoherence(("Harichandran-Vanmarche Coherence"), strPluginName);
	UnregisterCoherence(("Abrahamson Coherence"), strPluginName);
	UnregisterPSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName);
	UnregisterModulation(("Bogdanoff-Goldberg-Bernard Modulation function"), strPluginName);
	UnregisterModulation(("Jennings et al. Modulation function"), strPluginName);

	return 1;
}



