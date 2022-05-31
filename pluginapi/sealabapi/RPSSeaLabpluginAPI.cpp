#include "RPSSeaLabpluginAPI.h"
#include "RPSSeaLabAPI.h"



////////////////////////////////////Simulation method//////////////////////////////////////////

void RegisterSLSimulationMethod(const QString name, const QString &pluginName, const QString &description, SLSimulationMethodInitFunc init_cb, SLSimulationMethodFreeFunc free_cb)
{
	if ( CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	 CrpsSeLSimulationMethodFactory::RegisterSLSimulationMethod(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeSLSimulationMethod(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLSimulationMethodFactory::InitializeSLSimulationMethod(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnRegisterSLSimulationMethod(const QString name, const QString &pluginName)
{
	 CrpsSeLSimulationMethodFactory::UnregisterSLSimulationMethod(name, pluginName);
}


////////////////////////////////////////////////////////////////////////////kkkkkk

 ////////////////////////////////////coherence//////////////////////////////////////////

void RegisterCoherence(const QString name, const QString &pluginName, const QString &description, CoherenceInitFunc init_cb, CoherenceFreeFunc free_cb)
{
	if ( CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	 CrpsSeLCoherenceFactory::RegisterCoherence(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeCoherence(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLCoherenceFactory::InitializeCoherence(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterCoherence(const QString name, const QString &pluginName)
{
	 CrpsSeLCoherenceFactory::UnregisterCoherence(name, pluginName);
}

////////////////////////////////////Location Distribution//////////////////////////////////////////

void RegisterLocationDistribution(const QString name, const QString &pluginName, const QString &description, LocationDistributionInitFunc init_cb, LocationDistributionFreeFunc free_cb)
{
	if ( CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	 CrpsSeLLocationDistributionFactory::RegisterLocationDistribution(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeLocationDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLLocationDistributionFactory::InitializeLocationDistribution(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterLocationDistribution(const QString name, const QString &pluginName)
{
	 CrpsSeLLocationDistributionFactory::UnregisterLocationDistribution(name, pluginName);
}

////////////////////////////////////Mean wind profile//////////////////////////////////////////

void RegisterMean(const QString name, const QString &pluginName, const QString &description, MeanInitFunc init_cb, MeanFreeFunc free_cb)
{
	if (CrpsSeLMeanFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSeLMeanFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	CrpsSeLMeanFactory::RegisterMean(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeMean(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSeLMeanFactory::InitializeMean(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterMean(const QString name, const QString &pluginName)
{
	CrpsSeLMeanFactory::UnregisterMean(name, pluginName);
}


////////////////////////////////////Along wind target spectrum//////////////////////////////////////////

void RegisterXSpectrum(const QString name, const QString &pluginName, const QString &description, XSpectrumInitFunc init_cb, XSpectrumFreeFunc free_cb)
{
	if ( CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	 CrpsSeLXSpectrumFactory::RegisterXSpectrum(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeXSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLXSpectrumFactory::InitializeXSpectrum(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterXSpectrum(const QString name, const QString &pluginName)
{
	 CrpsSeLXSpectrumFactory::UnregisterXSpectrum(name, pluginName);
}


////////////////////////////////////Frequency distribution//////////////////////////////////////////

void RegisterFrequencyDistribution(const QString name, const QString &pluginName, const QString &description, FrequencyDistributionInitFunc init_cb, FrequencyDistributionFreeFunc free_cb)
{
	if ( CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	 CrpsSeLFrequencyDistributionFactory::RegisterFrequencyDistribution(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeFrequencyDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLFrequencyDistributionFactory::InitializeFrequencyDistribution(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterFrequencyDistribution(const QString name, const QString &pluginName)
{
	 CrpsSeLFrequencyDistributionFactory::UnregisterFrequencyDistribution(name, pluginName);
}


////////////////////////////////////Randomness//////////////////////////////////////////

void RegisterRandomness(const QString name, const QString &pluginName, const QString &description, RandomnessInitFunc init_cb, RandomnessFreeFunc free_cb)
{
	if ( CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	 CrpsSeLRandomnessFactory::RegisterRandomness(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeRandomness(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLRandomnessFactory::InitializeRandomness(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterRandomness(const QString name, const QString &pluginName)
{
	 CrpsSeLRandomnessFactory::UnregisterRandomness(name, pluginName);
}


////////////////////////////////////psd decomposition//////////////////////////////////////////

void RegisterPSDdecomMethod(const QString name, const QString &pluginName, const QString &description, PSDdecomMethodInitFunc init_cb, PSDdecomMethodFreeFunc free_cb)
{
	if ( CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	 CrpsSeLPSDdecomMethodFactory::RegisterPSDdecomMethod(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializePSDdecomMethod(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLPSDdecomMethodFactory::InitializePSDdecomMethod(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterPSDdecomMethod(const QString name, const QString &pluginName)
{
	 CrpsSeLPSDdecomMethodFactory::UnregisterPSDdecomMethod(name, pluginName);
}

////////////////////////////////////Correlation//////////////////////////////////////////

void RegisterCorrelation(const QString name, const QString &pluginName, const QString &description, CorrelationInitFunc init_cb, CorrelationFreeFunc free_cb)
{
	if ( CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	 CrpsSeLCorrelationFactory::RegisterCorrelation(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeCorrelation(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLCorrelationFactory::InitializeCorrelation(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterCorrelation(const QString name, const QString &pluginName)
{
	 CrpsSeLCorrelationFactory::UnregisterCorrelation(name, pluginName);
}

////////////////////////////////////Modulation//////////////////////////////////////////

void RegisterModulation(const QString name, const QString &pluginName, const QString &description, ModulationInitFunc init_cb, ModulationFreeFunc free_cb)
{
	if ( CrpsSeLModulationFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsSeLModulationFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	 CrpsSeLModulationFactory::RegisterModulation(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeModulation(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	 CrpsSeLModulationFactory::InitializeModulation(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterModulation(const QString name, const QString &pluginName)
{
	 CrpsSeLModulationFactory::UnregisterModulation(name, pluginName);
}

////////////////////////////////////DirectionalSpectrum//////////////////////////////////////////

void RegisterDirectionalSpectrum(const QString name, const QString &pluginName, const QString &description, DirectionalSpectrumInitFunc init_cb, DirectionalSpectrumFreeFunc free_cb)
{
	if (CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSeLDirectionalSpectrumFactory::RegisterDirectionalSpectrum(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeDirectionalSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSeLDirectionalSpectrumFactory::InitializeDirectionalSpectrum(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterDirectionalSpectrum(const QString name, const QString &pluginName)
{
	CrpsSeLDirectionalSpectrumFactory::UnregisterDirectionalSpectrum(name, pluginName);
}

////////////////////////////////////DirectionDistribution//////////////////////////////////////////

void RegisterDirectionDistribution(const QString name, const QString &pluginName, const QString &description, DirectionDistributionInitFunc init_cb, DirectionDistributionFreeFunc free_cb)
{
	if (CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSeLDirectionDistributionFactory::RegisterDirectionDistribution(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeDirectionDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSeLDirectionDistributionFactory::InitializeDirectionDistribution(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterDirectionDistribution(const QString name, const QString &pluginName)
{
	CrpsSeLDirectionDistributionFactory::UnregisterDirectionDistribution(name, pluginName);
}

////////////////////////////////////DirectionSpreadingFunction//////////////////////////////////////////

void RegisterDirectionSpreadingFunction(const QString name, const QString &pluginName, const QString &description, DirectionSpreadingFunctionInitFunc init_cb, DirectionSpreadingFunctionFreeFunc free_cb)
{
	if (CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSeLDirectionSpreadingFunctionFactory::RegisterDirectionSpreadingFunction(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeDirectionSpreadingFunction(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSeLDirectionSpreadingFunctionFactory::InitializeDirectionSpreadingFunction(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterDirectionSpreadingFunction(const QString name, const QString &pluginName)
{
	CrpsSeLDirectionSpreadingFunctionFactory::UnregisterDirectionSpreadingFunction(name, pluginName);
}
