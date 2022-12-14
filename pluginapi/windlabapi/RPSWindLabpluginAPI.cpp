
#include "RPSWindLabpluginAPI.h"
#include "RPSWindLabAPI.h"

const char * RPSWindLabPluginAPIInfo::getWindLabPluginAPIVersion()
{
	return "0.001";
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//Fill output pane
 void SimulationOutputText(QString outputText)
{

}

 ////////////////////////////////////coherence//////////////////////////////////////////

 void RegisterCoherence(const QString name, const QString &pluginName, const QString &description, CoherenceInitFunc init_cb, CoherenceFreeFunc free_cb)
 {
	 if (CrpsCoherenceFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsCoherenceFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsCoherenceFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeCoherence(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsCoherenceFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterCoherence(const QString name, const QString &pluginName)
 {
     CrpsCoherenceFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Location Distribution//////////////////////////////////////////

 void RegisterLocationDistribution(const QString name, const QString &pluginName, const QString &description, LocationDistributionInitFunc init_cb, LocationDistributionFreeFunc free_cb)
 {
	 if (CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsLocationDistributionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeLocationDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsLocationDistributionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterLocationDistribution(const QString name, const QString &pluginName)
 {
     CrpsLocationDistributionFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Mean wind profile//////////////////////////////////////////

 void RegisterMean(const QString name, const QString &pluginName, const QString &description,  MeanInitFunc init_cb, MeanFreeFunc free_cb)
 {
	 if (CrpsMeanFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsMeanFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsMeanFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeMean(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsMeanFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterMean(const QString name, const QString &pluginName)
 {
     CrpsMeanFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Along wind target spectrum//////////////////////////////////////////

 void RegisterXSpectrum(const QString name, const QString &pluginName, const QString &description, XSpectrumInitFunc init_cb, XSpectrumFreeFunc free_cb)
 {
	 if (CrpsXSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsXSpectrumFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsXSpectrumFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeXSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsXSpectrumFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterXSpectrum(const QString name, const QString &pluginName)
 {
     CrpsXSpectrumFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Vertical wind target spectrum//////////////////////////////////////////

 void RegisterZSpectrum(const QString name, const QString &pluginName, const QString &description, ZSpectrumInitFunc init_cb, ZSpectrumFreeFunc free_cb)
 {
	 if (CrpsZSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsZSpectrumFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsZSpectrumFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeZSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsZSpectrumFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterZSpectrum(const QString name, const QString &pluginName)
 {
     CrpsZSpectrumFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Across wind target spectrum//////////////////////////////////////////

 void RegisterYSpectrum(const QString name, const QString &pluginName, const QString &description, YSpectrumInitFunc init_cb, YSpectrumFreeFunc free_cb)
 {
	 if (CrpsYSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsYSpectrumFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsYSpectrumFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeYSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsYSpectrumFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterYSpectrum(const QString name, const QString &pluginName)
 {
     CrpsYSpectrumFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Simulation method//////////////////////////////////////////

 void RegisterSimuMethod(const QString name, const QString &pluginName, const QString &description, SimuMethodInitFunc init_cb, SimuMethodFreeFunc free_cb)
 {
	 if (CrpsSimuMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSimuMethodFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsSimuMethodFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeSimuMethod(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsSimuMethodFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterSimuMethod(const QString name, const QString &pluginName)
 {
     CrpsSimuMethodFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Frequency distribution//////////////////////////////////////////

 void RegisterFrequencyDistribution(const QString name, const QString &pluginName, const QString &description, FrequencyDistributionInitFunc init_cb, FrequencyDistributionFreeFunc free_cb)
 {
	 if (CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsFrequencyDistributionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeFrequencyDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsFrequencyDistributionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterFrequencyDistribution(const QString name, const QString &pluginName)
 {
     CrpsFrequencyDistributionFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////Randomness//////////////////////////////////////////

 void RegisterRandomness(const QString name, const QString &pluginName, const QString &description, RandomnessInitFunc init_cb, RandomnessFreeFunc free_cb)
 {
	 if (CrpsRandomnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsRandomnessFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsRandomnessFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeRandomness(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsRandomnessFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterRandomness(const QString name, const QString &pluginName)
 {
     CrpsRandomnessFactory::UnregisterObject(name, pluginName);
 }


 ////////////////////////////////////psd decomposition//////////////////////////////////////////

 void RegisterPSDdecomMethod(const QString name, const QString &pluginName, const QString &description, PSDdecomMethodInitFunc init_cb, PSDdecomMethodFreeFunc free_cb)
 {
	 if (CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsPSDdecomMethodFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializePSDdecomMethod(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsPSDdecomMethodFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterPSDdecomMethod(const QString name, const QString &pluginName)
 {
     CrpsPSDdecomMethodFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Correlation//////////////////////////////////////////

 void RegisterCorrelation(const QString name, const QString &pluginName, const QString &description, CorrelationInitFunc init_cb, CorrelationFreeFunc free_cb)
 {
	 if (CrpsCorrelationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsCorrelationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsCorrelationFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeCorrelation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsCorrelationFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterCorrelation(const QString name, const QString &pluginName)
 {
     CrpsCorrelationFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////Modulation//////////////////////////////////////////

 void RegisterModulation(const QString name, const QString &pluginName, const QString &description, ModulationInitFunc init_cb, ModulationFreeFunc free_cb)
 {
	 if (CrpsModulationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsModulationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

     CrpsModulationFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeModulation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsModulationFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterModulation(const QString name, const QString &pluginName)
 {
     CrpsModulationFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////table tool object//////////////////////////////////////////

 void RegisterTableTool(const QString name, const QString &pluginName, const QString &description, TableToolInitFunc init_cb, TableToolFreeFunc free_cb)
 {
	 if (CrpsTableToolFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsTableToolFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsTableToolFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeTableTool(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsTableToolFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterTableTool(const QString name, const QString &pluginName)
 {
     CrpsTableToolFactory::UnregisterObject(name, pluginName);
 }

////////////////////////////////////matrix tools object//////////////////////////////////////////

 void RegisterMatrixTool(const QString name, const QString &pluginName, const QString &description, MatrixToolInitFunc init_cb, MatrixToolFreeFunc free_cb)
 {
	 if (CrpsMatrixToolFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsMatrixToolFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsMatrixToolFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeMatrixTool(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsMatrixToolFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterMatrixTool(const QString name, const QString &pluginName)
 {
     CrpsMatrixToolFactory::UnregisterObject(name, pluginName);
 }

 ////////////////////////////////////user defined rps object//////////////////////////////////////////

 void RegisterUserDefinedRPSObject(const QString name, const QString &pluginName, const QString &description, UserDefinedRPSObjectInitFunc init_cb, UserDefinedRPSObjectFreeFunc free_cb)
 {
	 if (CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsUserDefinedRPSObjectFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeUserDefinedRPSObject(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsUserDefinedRPSObjectFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterUserDefinedRPSObject(const QString name, const QString &pluginName)
 {
     CrpsUserDefinedRPSObjectFactory::UnregisterObject(name, pluginName);
 }


/////////////////////cumulative probability distribution///////////////

 void RegisterCumulativeProbabilityDistribution(const QString name, const QString &pluginName, const QString &description, CumulativeProbabilityDistributionInitFunc init_cb, CumulativeProbabilityDistributionFreeFunc free_cb)
 {
	 if (CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsCumulativeProbabilityDistributionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeCumulativeProbabilityDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsCumulativeProbabilityDistributionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterCumulativeProbabilityDistribution(const QString name, const QString &pluginName)
 {
     CrpsCumulativeProbabilityDistributionFactory::UnregisterObject(name, pluginName);
 }
 
 /////////////////////Gust factor///////////////

 void RegisterGustFactor(const QString name, const QString &pluginName, const QString &description, GustFactorInitFunc init_cb, GustFactorFreeFunc free_cb)
 {
	 if (CrpsGustFactorFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsGustFactorFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsGustFactorFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeGustFactor(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsGustFactorFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterGustFactor(const QString name, const QString &pluginName)
 {
     CrpsGustFactorFactory::UnregisterObject(name, pluginName);
 }


 /////////////////////Kurtosis/////////////////////////////

 void RegisterKurtosis(const QString name, const QString &pluginName, const QString &description, KurtosisInitFunc init_cb, KurtosisFreeFunc free_cb)
 {
	 if (CrpsKurtosisFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsKurtosisFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsKurtosisFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeKurtosis(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsKurtosisFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterKurtosis(const QString name, const QString &pluginName)
 {
     CrpsKurtosisFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Peak factor//////////////////////////

 void RegisterPeakFactor(const QString name, const QString &pluginName, const QString &description, PeakFactorInitFunc init_cb, PeakFactorFreeFunc free_cb)
 {
	 if (CrpsPeakFactorFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsPeakFactorFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsPeakFactorFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializePeakFactor(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsPeakFactorFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterPeakFactor(const QString name, const QString &pluginName)
 {
     CrpsPeakFactorFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Probability density function///////////////

 void RegisterProbabilityDensityFunction(const QString name, const QString &pluginName, const QString &description, ProbabilityDensityFunctionInitFunc init_cb, ProbabilityDensityFunctionFreeFunc free_cb)
 {
	 if (CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsProbabilityDensityFunctionFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeProbabilityDensityFunction(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsProbabilityDensityFunctionFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterProbabilityDensityFunction(const QString name, const QString &pluginName)
 {
     CrpsProbabilityDensityFunctionFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Roughness///////////////

 void RegisterRoughness(const QString name, const QString &pluginName, const QString &description, RoughnessInitFunc init_cb, RoughnessFreeFunc free_cb)
 {
	 if (CrpsRoughnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsRoughnessFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsRoughnessFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeRoughness(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsRoughnessFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterRoughness(const QString name, const QString &pluginName)
 {
     CrpsRoughnessFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Shear velocity of the flow///////////////

 void RegisterShearVelocityOfFlow(const QString name, const QString &pluginName, const QString &description, ShearVelocityOfFlowInitFunc init_cb, ShearVelocityOfFlowFreeFunc free_cb)
 {
	 if (CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsShearVelocityOfFlowFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeShearVelocityOfFlow(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsShearVelocityOfFlowFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterShearVelocityOfFlow(const QString name, const QString &pluginName)
 {
     CrpsShearVelocityOfFlowFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Skewness///////////////

 void RegisterSkewness(const QString name, const QString &pluginName, const QString &description, SkewnessInitFunc init_cb, SkewnessFreeFunc free_cb)
 {
	 if (CrpsSkewnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSkewnessFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsSkewnessFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeSkewness(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsSkewnessFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterSkewness(const QString name, const QString &pluginName)
 {
     CrpsSkewnessFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Standard deviation///////////////

 void RegisterStandardDeviation(const QString name, const QString &pluginName, const QString &description, StandardDeviationInitFunc init_cb, StandardDeviationFreeFunc free_cb)
 {
	 if (CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsStandardDeviationFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeStandardDeviation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsStandardDeviationFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterStandardDeviation(const QString name, const QString &pluginName)
 {
     CrpsStandardDeviationFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Turbulence intensity///////////////

 void RegisterTurbulenceIntensity(const QString name, const QString &pluginName, const QString &description, TurbulenceIntensityInitFunc init_cb, TurbulenceIntensityFreeFunc free_cb)
 {
	 if (CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsTurbulenceIntensityFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeTurbulenceIntensity(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsTurbulenceIntensityFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterTurbulenceIntensity(const QString name, const QString &pluginName)
 {
     CrpsTurbulenceIntensityFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Variance///////////////

 void RegisterTurbulenceScale(const QString name, const QString &pluginName, const QString &description, TurbulenceScaleInitFunc init_cb, TurbulenceScaleFreeFunc free_cb)
 {
	 if (CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsTurbulenceScaleFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeTurbulenceScale(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsTurbulenceScaleFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterTurbulenceScale(const QString name, const QString &pluginName)
 {
     CrpsTurbulenceScaleFactory::UnregisterObject(name, pluginName);
 }

  void RegisterVariance(const QString name, const QString &pluginName, const QString &description, VarianceInitFunc init_cb, VarianceFreeFunc free_cb)
 {
	 if (CrpsVarianceFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsVarianceFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsVarianceFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeVariance(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsVarianceFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterVariance(const QString name, const QString &pluginName)
 {
     CrpsVarianceFactory::UnregisterObject(name, pluginName);
 }

 /////////////////////Wave passage effect///////////////

 void RegisterWavePassageEffect(const QString name, const QString &pluginName, const QString &description, WavePassageEffectInitFunc init_cb, WavePassageEffectFreeFunc free_cb)
 {
	 if (CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
     CrpsWavePassageEffectFactory::RegisterObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeWavePassageEffect(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
     CrpsWavePassageEffectFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterWavePassageEffect(const QString name, const QString &pluginName)
 {
     CrpsWavePassageEffectFactory::UnregisterObject(name, pluginName);
 }
