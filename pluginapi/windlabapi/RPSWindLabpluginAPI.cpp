
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
	 CrpsCoherenceFactory::RegisterCoherence(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeCoherence(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsCoherenceFactory::InitializeCoherence(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterCoherence(const QString name, const QString &pluginName)
 {
	 CrpsCoherenceFactory::UnregisterCoherence(name, pluginName);
 }

 ////////////////////////////////////Location Distribution//////////////////////////////////////////

 void RegisterLocationDistribution(const QString name, const QString &pluginName, const QString &description, LocationDistributionInitFunc init_cb, LocationDistributionFreeFunc free_cb)
 {
	 if (CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsLocationDistributionFactory::RegisterLocationDistribution(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeLocationDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsLocationDistributionFactory::InitializeLocationDistribution(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterLocationDistribution(const QString name, const QString &pluginName)
 {
	 CrpsLocationDistributionFactory::UnregisterLocationDistribution(name, pluginName);
 }


 ////////////////////////////////////Mean wind profile//////////////////////////////////////////

 void RegisterMean(const QString name, const QString &pluginName, const QString &description,  MeanInitFunc init_cb, MeanFreeFunc free_cb)
 {
	 if (CrpsMeanFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsMeanFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsMeanFactory::RegisterMean(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeMean(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsMeanFactory::InitializeMean(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterMean(const QString name, const QString &pluginName)
 {
	 CrpsMeanFactory::UnregisterMean(name, pluginName);
 }


 ////////////////////////////////////Along wind target spectrum//////////////////////////////////////////

 void RegisterXSpectrum(const QString name, const QString &pluginName, const QString &description, XSpectrumInitFunc init_cb, XSpectrumFreeFunc free_cb)
 {
	 if (CrpsXSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsXSpectrumFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsXSpectrumFactory::RegisterXSpectrum(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeXSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsXSpectrumFactory::InitializeXSpectrum(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterXSpectrum(const QString name, const QString &pluginName)
 {
	 CrpsXSpectrumFactory::UnregisterXSpectrum(name, pluginName);
 }


 ////////////////////////////////////Vertical wind target spectrum//////////////////////////////////////////

 void RegisterZSpectrum(const QString name, const QString &pluginName, const QString &description, ZSpectrumInitFunc init_cb, ZSpectrumFreeFunc free_cb)
 {
	 if (CrpsZSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsZSpectrumFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsZSpectrumFactory::RegisterZSpectrum(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeZSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsZSpectrumFactory::InitializeZSpectrum(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterZSpectrum(const QString name, const QString &pluginName)
 {
	 CrpsZSpectrumFactory::UnregisterZSpectrum(name, pluginName);
 }

 ////////////////////////////////////Across wind target spectrum//////////////////////////////////////////

 void RegisterYSpectrum(const QString name, const QString &pluginName, const QString &description, YSpectrumInitFunc init_cb, YSpectrumFreeFunc free_cb)
 {
	 if (CrpsYSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsYSpectrumFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsYSpectrumFactory::RegisterYSpectrum(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeYSpectrum(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsYSpectrumFactory::InitializeYSpectrum(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterYSpectrum(const QString name, const QString &pluginName)
 {
	 CrpsYSpectrumFactory::UnregisterYSpectrum(name, pluginName);
 }

 ////////////////////////////////////Simulation method//////////////////////////////////////////

 void RegisterSimuMethod(const QString name, const QString &pluginName, const QString &description, SimuMethodInitFunc init_cb, SimuMethodFreeFunc free_cb)
 {
	 if (CrpsSimuMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSimuMethodFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

	 CrpsSimuMethodFactory::RegisterSimuMethod(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeSimuMethod(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsSimuMethodFactory::InitializeSimuMethod(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterSimuMethod(const QString name, const QString &pluginName)
 {
	 CrpsSimuMethodFactory::UnregisterSimuMethod(name, pluginName);
 }


 ////////////////////////////////////Frequency distribution//////////////////////////////////////////

 void RegisterFrequencyDistribution(const QString name, const QString &pluginName, const QString &description, FrequencyDistributionInitFunc init_cb, FrequencyDistributionFreeFunc free_cb)
 {
	 if (CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

	 CrpsFrequencyDistributionFactory::RegisterFrequencyDistribution(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeFrequencyDistribution(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsFrequencyDistributionFactory::InitializeFrequencyDistribution(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterFrequencyDistribution(const QString name, const QString &pluginName)
 {
	 CrpsFrequencyDistributionFactory::UnregisterFrequencyDistribution(name, pluginName);
 }


 ////////////////////////////////////Randomness//////////////////////////////////////////

 void RegisterRandomness(const QString name, const QString &pluginName, const QString &description, RandomnessInitFunc init_cb, RandomnessFreeFunc free_cb)
 {
	 if (CrpsRandomnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsRandomnessFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

	 CrpsRandomnessFactory::RegisterRandomness(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeRandomness(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsRandomnessFactory::InitializeRandomness(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterRandomness(const QString name, const QString &pluginName)
 {
	 CrpsRandomnessFactory::UnregisterRandomness(name, pluginName);
 }


 ////////////////////////////////////psd decomposition//////////////////////////////////////////

 void RegisterPSDdecomMethod(const QString name, const QString &pluginName, const QString &description, PSDdecomMethodInitFunc init_cb, PSDdecomMethodFreeFunc free_cb)
 {
	 if (CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

	 CrpsPSDdecomMethodFactory::RegisterPSDdecomMethod(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializePSDdecomMethod(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsPSDdecomMethodFactory::InitializePSDdecomMethod(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterPSDdecomMethod(const QString name, const QString &pluginName)
 {
	 CrpsPSDdecomMethodFactory::UnregisterPSDdecomMethod(name, pluginName);
 }

 ////////////////////////////////////Correlation//////////////////////////////////////////

 void RegisterCorrelation(const QString name, const QString &pluginName, const QString &description, CorrelationInitFunc init_cb, CorrelationFreeFunc free_cb)
 {
	 if (CrpsCorrelationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsCorrelationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

	 CrpsCorrelationFactory::RegisterCorrelation(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeCorrelation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsCorrelationFactory::InitializeCorrelation(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterCorrelation(const QString name, const QString &pluginName)
 {
	 CrpsCorrelationFactory::UnregisterCorrelation(name, pluginName);
 }

 ////////////////////////////////////Modulation//////////////////////////////////////////

 void RegisterModulation(const QString name, const QString &pluginName, const QString &description, ModulationInitFunc init_cb, ModulationFreeFunc free_cb)
 {
	 if (CrpsModulationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsModulationFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }

	 CrpsModulationFactory::RegisterModulation(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeModulation(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsModulationFactory::InitializeModulation(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterModulation(const QString name, const QString &pluginName)
 {
	 CrpsModulationFactory::UnregisterModulation(name, pluginName);
 }

 ////////////////////////////////////table tool object//////////////////////////////////////////

 void RegisterTableTool(const QString name, const QString &pluginName, const QString &description, TableToolInitFunc init_cb, TableToolFreeFunc free_cb)
 {
	 if (CrpsTableToolFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsTableToolFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsTableToolFactory::RegisterTableTool(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeTableTool(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsTableToolFactory::InitializeTableTool(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterTableTool(const QString name, const QString &pluginName)
 {
	 CrpsTableToolFactory::UnregisterTableTool(name, pluginName);
 }

////////////////////////////////////matrix tools object//////////////////////////////////////////

 void RegisterMatrixTool(const QString name, const QString &pluginName, const QString &description, MatrixToolInitFunc init_cb, MatrixToolFreeFunc free_cb)
 {
	 if (CrpsMatrixToolFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsMatrixToolFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsMatrixToolFactory::RegisterMatrixTool(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeMatrixTool(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsMatrixToolFactory::InitializeMatrixTool(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterMatrixTool(const QString name, const QString &pluginName)
 {
	 CrpsMatrixToolFactory::UnregisterMatrixTool(name, pluginName);
 }

 ////////////////////////////////////user defined rps object//////////////////////////////////////////

 void RegisterUserDefinedRPSObject(const QString name, const QString &pluginName, const QString &description, UserDefinedRPSObjectInitFunc init_cb, UserDefinedRPSObjectFreeFunc free_cb)
 {
	 if (CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsUserDefinedRPSObjectFactory::RegisterUserDefinedRPSObject(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeUserDefinedRPSObject(const QString name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsUserDefinedRPSObjectFactory::InitializeUserDefinedRPSObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterUserDefinedRPSObject(const QString name, const QString &pluginName)
 {
	 CrpsUserDefinedRPSObjectFactory::UnregisterUserDefinedRPSObject(name, pluginName);
 }

 