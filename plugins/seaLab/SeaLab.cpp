// SeaLab.cpp : Defines the initialization routines for the DLL.
//

#include "RPSSeaLabpluginAPI.h"
#include "RPSSLUniformRandomPhases.h"
#include "RPSSLRandomPhasesFromFile.h"
#include "RPSDeodatis1996.h"
#include "SLHorizontalUniformDistribution.h"
#include "SLVerticalUniformDistribution.h"
#include "JonswapSpectrum.h"
#include "RPSSLSingleIndexFrequency.h"
#include "RPSSLDoubleIndexFrequency.h"
#include "RPSUniformFrequencyDistribution.h"
#include "AbrahamsonCoherence.h"
#include "HarichandranVanmarcheCoherence.h"
#include "SLCholeskyDecomposition.h"
#include "BogdanoffGoldbergBernarModulation.h"
#include "JenningEtAlModulation.h"
#include "RPSSpreadingFunction1.h"
#include "RPSSpreadingFunction2.h"
#include "UnifDistrDirection.h"
#include "RPSDirectionalSpectrum.h"
#include "RPSCorrelationFunction.h"


#include <QString>
#include <QMessageBox>


QString strPluginName = ("seaLab");



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


PLUGIN_DISPLAY_NAME("seaLab");
PLUGIN_SYSTEM_NAME("seaLab");
RANDOM_PHENOMENON("Sea Wave");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("1.00");
API_VERSION("1.00");
PLUGIN_RELEASE_DATE("07/01/2021");
//PLUG_IN_THIS_RP("Random Wind Velocity");

//////////////simulation method start///////////////
RPS_PLUGIN_FUNC IrpsSeLSimulationMethod *BuildRPSDeodatis1996()
{
	return new CRPSDeodatis1996;
}

RPS_PLUGIN_FUNC void DestroyRPSDeodatis1996(IrpsSeLSimulationMethod *r)
{
	delete r;
}

/////////////simulation method end /////////////////

/////////////randomness provider start///////////////
RPS_PLUGIN_FUNC IrpsSeLRandomness *BuildRPSUniformRandomPhases()
{
	return new CRPSSLUniformRandomPhases;
}

RPS_PLUGIN_FUNC void DestroyRPSUniformRandomPhases(IrpsSeLRandomness *r)
{
	delete r;
}

////////////////////////Uniform random phase end/////////////////////////////////////////////////////////////////

////////////////////////Random phase from file start/////////////////////////////////////////////////////////////////

RPS_PLUGIN_FUNC IrpsSeLRandomness *BuildRPSRandomPhasesFromFile()
{
	return new CRPSSLRandomPhasesFromFile;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomPhasesFromFile(IrpsSeLRandomness *r)
{
	delete r;
}

////////////////////////Random phase from file end/////////////////////////////////////////////////////////////////

///////////////////////horizontal uniform location distribution start/////////////////
RPS_PLUGIN_FUNC IrpsSeLLocationDistribution *BuildHorizontalDistr()
{
	return new CSeLHorizontalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyHorizontalDistr(IrpsSeLLocationDistribution *r)
{
	delete r;
}
///////////////////////horizontal uniform location distribution end/////////////////

///////////////////////vertical uniform location distribution start/////////////////
RPS_PLUGIN_FUNC IrpsSeLLocationDistribution *BuildVerticalDistr()
{
	return new CSLVerticalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyVerticalDistr(IrpsSeLLocationDistribution *r)
{
	delete r;
}
///////////////////////vertical uniform location distribution end/////////////////


////////////////////////target spectrum start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLSpectrum *BuildJonswapSpectrum()
{
	return new CJonswapSpectrum;
}

RPS_PLUGIN_FUNC void DestroyJonswapSpectrum(IrpsSeLSpectrum *r)
{
	delete r;
}
////////////////////////target spectrum end//////////////////////////////////////////

/////////////////////////single index frequency start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLFrequencyDistribution *BuildRPSSingleIndexFreq()
{
	return new CRPSSLSingleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSSingleIndexFreq(IrpsSeLFrequencyDistribution *r)
{
	delete r;
}
////////////////////////single index frequency end//////////////////////////////////////////

////////////////////////double index frequency start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLFrequencyDistribution *BuildRPSDoubleIndexFreq()
{
	return new CRPSSLDoubleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSDoubleIndexFreq(IrpsSeLFrequencyDistribution *r)
{
	delete r;
}
////////////////////////double index frequency end//////////////////////////////////////////

////////////////////////uniform frequency distribution start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLFrequencyDistribution *BuildUniformFrequencyDistribution()
{
	return new CRPSUniformFrequencyDistribution;
}

RPS_PLUGIN_FUNC void DestroyUniformFrequencyDistribution(IrpsSeLFrequencyDistribution *r)
{
	delete r;
}
////////////////////////uniform frequency distribution end//////////////////////////////////////////

////////////////////////Abrahamson coherence start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLCoherence *BuildAbrahamsonCoherence()
{
	return new CAbrahamsonCoherence;
}

RPS_PLUGIN_FUNC void DestroyAbrahamsonCoherence(IrpsSeLCoherence *r)
{
	delete r;
}
////////////////////////Abrahamson coherence end//////////////////////////////////////////

////////////////////////Harichandranvanmar coherence start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLCoherence *BuildHarichandranVanmarcheCoherence()
{
	return new CHarichandranVanmarcheCoherence;
}

RPS_PLUGIN_FUNC void DestroyHarichandranVanmarcheCoherence(IrpsSeLCoherence *r)
{
	delete r;
}
////////////////////////Harichandranvanmar coherence end//////////////////////////////////////////
 
////////////////////////cholesky decomposition start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLPSDdecompositionMethod *BuildPSDCholeskyDecomposition()
{
	return new CSLCholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyPSDCholeskyDecomposition(IrpsSeLPSDdecompositionMethod *r)
{
	delete r;
}
////////////////////////cholesky decomposition coherence end//////////////////////////////////////////

////////////////////////Bog modulation start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLModulation *BuildBogdanoffGoldbergBernarModulation()
{
	return new CBogdanoffGoldbergBernarModulation;
}

RPS_PLUGIN_FUNC void DestroyBogdanoffGoldbergBernarModulation(IrpsSeLModulation *r)
{
	delete r;
}
////////////////////////Bog modulation end//////////////////////////////////////////
 
////////////////////////Jen modulation start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLModulation *BuildJenningEtAlModulation()
{
	return new CJenningEtAlModulation;
}

RPS_PLUGIN_FUNC void DestroyJenningEtAlModulation(IrpsSeLModulation *r)
{
	delete r;
}
////////////////////////Jen modulation end//////////////////////////////////////////

////////////////////////direction spreading 1 start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLDirectionSpreadingFunction *BuildRPSSpreadingFunction1()
{
	return new CRPSSpreadingFunction1;
}

RPS_PLUGIN_FUNC void DestroyRPSSpreadingFunction1(IrpsSeLDirectionSpreadingFunction *r)
{
	delete r;
}
////////////////////////direction spreading 1 end//////////////////////////////////////////


////////////////////////direction spreading 2 start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLDirectionSpreadingFunction *BuildRPSSpreadingFunction2()
{
	return new CRPSSpreadingFunction2;
}

RPS_PLUGIN_FUNC void DestroyRPSSpreadingFunction2(IrpsSeLDirectionSpreadingFunction *r)
{
	delete r;
}
////////////////////////direction spreading 2 end//////////////////////////////////////////
 
////////////////////////direction distribution start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLDirectionDistribution *BuildUnifDistrDirection()
{
	return new CUnifDistrDirection;
}

RPS_PLUGIN_FUNC void DestroyUnifDistrDirection(IrpsSeLDirectionDistribution *r)
{
	delete r;
}
//////////////////////direction distribution end//////////////////////////////////////////
 
////////////////////////directional spectrum start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLDirectionalSpectrum *BuildDirectionalSpectrum()
{
	return new CRPSDirectionalSpectrum;
}

RPS_PLUGIN_FUNC void DestroyDirectionalSpectrum(IrpsSeLDirectionalSpectrum *r)
{
	delete r;
}
////////////////////////directional spectrum end//////////////////////////////////////////
 
////////////////////////correlation function start//////////////////////////////////////////
RPS_PLUGIN_FUNC IrpsSeLCorrelation *BuildCorrelationFunction()
{
	return new CRPSCorrelationFunction;
}

RPS_PLUGIN_FUNC void DestroyCorrelationFunction(IrpsSeLCorrelation *r)
{
	delete r;
}
////////////////////////correlation function end//////////////////////////////////////////

PLUGIN_INIT()
{
	InitializeSLSimulationMethod(("Deodatis et al 1996"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeRandomness(("Uniform Random Phases"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeRandomness(("Random Phases Importer"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeLocationDistribution(("Horizontal Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeLocationDistribution(("Vertical Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeXSpectrum(("Jonswap Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeFrequencyDistribution(("RPS Uniform Frequency Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeCoherence(("Harichandran-Vanmarche Coherence"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeCoherence(("Abrahamson Coherence"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializePSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeModulation(("Bogdanoff-Goldberg-Bernard Modulation function"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeModulation(("Jennings et al. Modulation function"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeDirectionSpreadingFunction(("RPS Spreading Function 1"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeDirectionSpreadingFunction(("RPS Spreading Function 2"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeDirectionDistribution(("RPS Uniform Direction Distribution"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeDirectionalSpectrum(("RPS Directional Spectrum"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	InitializeCorrelation(("RPS Correlation"), strPluginName, ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"), ("Uniform Random Phases"));
	return 1;
}


INSTALL_PLUGIN()
{
	RegisterSLSimulationMethod(("Deodatis et al 1996"), strPluginName, ("Ground motion simulation method by Deodatis et al 1996"), BuildRPSDeodatis1996, DestroyRPSDeodatis1996);
	RegisterRandomness(("Uniform Random Phases"), strPluginName, ("Uniform random phase sets"), BuildRPSUniformRandomPhases, DestroyRPSUniformRandomPhases);
	RegisterRandomness(("Random Phases Importer"), strPluginName, ("This object allow the user to import the random phases from file"), BuildRPSRandomPhasesFromFile, DestroyRPSRandomPhasesFromFile);
	RegisterLocationDistribution(("Horizontal Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a horizontal axis"), BuildHorizontalDistr, DestroyHorizontalDistr);
	RegisterLocationDistribution(("Vertical Distribution"), strPluginName, ("This object allows you to define a set of locations which are uniformly disctributed along a vertical axis"), BuildVerticalDistr, DestroyVerticalDistr);
	RegisterXSpectrum(("Jonswap Spectrum"), strPluginName, ("Allow wind spectrum according to Clough-Penzien"), BuildJonswapSpectrum, DestroyJonswapSpectrum);
	RegisterFrequencyDistribution(("Double Index Frequency"), strPluginName, ("Single index frequency distribution"), BuildRPSDoubleIndexFreq, DestroyRPSDoubleIndexFreq);
	RegisterFrequencyDistribution(("Single Index Frequency"), strPluginName, ("Double index frequency distribution. This may be useful when ergodic wind is desired"), BuildRPSSingleIndexFreq, DestroyRPSSingleIndexFreq);
	RegisterFrequencyDistribution(("RPS Uniform Frequency Distribution"), strPluginName, ("RPS Uniform Frequency Distribution. A default frequency distribution by LabRPS"), BuildUniformFrequencyDistribution, DestroyUniformFrequencyDistribution);
	RegisterCoherence(("Abrahamson Coherence"), strPluginName, ("This is the Harichandran-Vanmarche coherence model"), BuildAbrahamsonCoherence, DestroyAbrahamsonCoherence);
	RegisterCoherence(("Harichandran-Vanmarche Coherence"), strPluginName, ("This is the Abrahamson coherence model"), BuildHarichandranVanmarcheCoherence, DestroyHarichandranVanmarcheCoherence);
	RegisterPSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName, ("The cholesky decomposition of hermitian real matrix"), BuildPSDCholeskyDecomposition, DestroyPSDCholeskyDecomposition);		
	RegisterModulation(("Bogdanoff-Goldberg-Bernard Modulation function"), strPluginName, ("Bogdanoff-Goldberg-Bernard uniform modulation function"), BuildBogdanoffGoldbergBernarModulation, DestroyBogdanoffGoldbergBernarModulation);
	RegisterModulation(("Jennings et al. Modulation function"), strPluginName, ("Jennings et al. uniform modulation function"), BuildJenningEtAlModulation, DestroyJenningEtAlModulation);
	RegisterDirectionSpreadingFunction(("RPS Spreading Function 1"), strPluginName, ("uniform direction spreading function"), BuildRPSSpreadingFunction1, DestroyRPSSpreadingFunction1);
	RegisterDirectionSpreadingFunction(("RPS Spreading Function 2"), strPluginName, ("uniform direction spreading function"), BuildRPSSpreadingFunction2, DestroyRPSSpreadingFunction2);
	RegisterDirectionDistribution(("RPS Uniform Direction Distribution"), strPluginName, ("uniform direction spreading function"), BuildUnifDistrDirection, DestroyUnifDistrDirection);
	RegisterDirectionalSpectrum(("RPS Directional Spectrum"), strPluginName, ("uniform direction spreading function"), BuildDirectionalSpectrum, DestroyDirectionalSpectrum);
	RegisterCorrelation(("RPS Correlation"), strPluginName, ("This function computes correlation from the user selected spectrum."), BuildCorrelationFunction, DestroyCorrelationFunction);

	return 1;
}

UNINSTALL_PLUGIN()
{
	UnRegisterSLSimulationMethod(("Deodatis et al 1996"), strPluginName);
	UnregisterRandomness(("Uniform Random Phases"), strPluginName);
    UnregisterRandomness(("Random Phases Importer"), strPluginName);
	UnregisterLocationDistribution(("Horizontal Distribution"), strPluginName);
	UnregisterLocationDistribution(("Vertical Distribution"), strPluginName);
	UnregisterXSpectrum(("Jonswap Spectrum"), strPluginName);
	UnregisterFrequencyDistribution(("Double Index Frequency"), strPluginName);
	UnregisterFrequencyDistribution(("Single Index Frequency"), strPluginName);
	UnregisterFrequencyDistribution(("RPS Uniform Frequency Distribution"), strPluginName);
	UnregisterCoherence(("Harichandran-Vanmarche Coherence"), strPluginName);
	UnregisterCoherence(("Abrahamson Coherence"), strPluginName);
	UnregisterPSDdecomMethod(("RPS Cholesky Decomposition"), strPluginName);
	UnregisterModulation(("Bogdanoff-Goldberg-Bernard Modulation function"), strPluginName);
	UnregisterModulation(("Jennings et al. Modulation function"), strPluginName);
	UnregisterDirectionSpreadingFunction(("RPS Spreading Function 1"), strPluginName);
	UnregisterDirectionSpreadingFunction(("RPS Spreading Function 2"), strPluginName);
	UnregisterDirectionDistribution(("RPS Uniform Direction Distribution"), strPluginName);
	UnregisterDirectionalSpectrum(("RPS Directional Spectrum"), strPluginName);
	UnregisterCorrelation(("RPS Correlation"), strPluginName);

	return 1;
}



