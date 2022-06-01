
#include "RPSSeismicLabpluginAPI.h"
#include "RPSSeismicLabAPI.h";



////////////////////////////////////Simulation method//////////////////////////////////////////

void RegisterSLSimulationMethod(const QString name, const QString &pluginName, const QString &description, SLSimulationMethodInitFunc init_cb, SLSimulationMethodFreeFunc free_cb)
{
	if (CrpsSLSimulationMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLSimulationMethodFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSLSimulationMethodFactory::RegisterSLSimulationMethod(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeSLSimulationMethod(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLSimulationMethodFactory::InitializeSLSimulationMethod(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnRegisterSLSimulationMethod(const QString name, const QString &pluginName)
{
	CrpsSLSimulationMethodFactory::UnregisterSLSimulationMethod(name, pluginName);
}


////////////////////////////////////////////////////////////////////////////kkkkkk

 ////////////////////////////////////coherence//////////////////////////////////////////

void RegisterCoherence(const QString name, const QString &pluginName, const QString &description, CoherenceInitFunc init_cb, CoherenceFreeFunc free_cb)
{
	if (CrpsSLCoherenceFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLCoherenceFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	CrpsSLCoherenceFactory::RegisterCoherence(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeCoherence(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLCoherenceFactory::InitializeCoherence(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterCoherence(const QString name, const QString &pluginName)
{
	CrpsSLCoherenceFactory::UnregisterCoherence(name, pluginName);
}

////////////////////////////////////Location Distribution//////////////////////////////////////////

void RegisterLocationDistribution(const QString name, const QString &pluginName, const QString &description, LocationDistributionInitFunc init_cb, LocationDistributionFreeFunc free_cb)
{
	if (CrpsSLLocationDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLLocationDistributionFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	CrpsSLLocationDistributionFactory::RegisterLocationDistribution(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeLocationDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLLocationDistributionFactory::InitializeLocationDistribution(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterLocationDistribution(const QString name, const QString &pluginName)
{
	CrpsSLLocationDistributionFactory::UnregisterLocationDistribution(name, pluginName);
}


////////////////////////////////////Along wind target spectrum//////////////////////////////////////////

void RegisterXSpectrum(const QString name, const QString &pluginName, const QString &description, XSpectrumInitFunc init_cb, XSpectrumFreeFunc free_cb)
{
	if (CrpsSLXSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLXSpectrumFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	CrpsSLXSpectrumFactory::RegisterXSpectrum(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeXSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLXSpectrumFactory::InitializeXSpectrum(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterXSpectrum(const QString name, const QString &pluginName)
{
	CrpsSLXSpectrumFactory::UnregisterXSpectrum(name, pluginName);
}


////////////////////////////////////Vertical wind target spectrum//////////////////////////////////////////

void RegisterZSpectrum(const QString name, const QString &pluginName, const QString &description, ZSpectrumInitFunc init_cb, ZSpectrumFreeFunc free_cb)
{
	if (CrpsSLZSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLZSpectrumFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	CrpsSLZSpectrumFactory::RegisterZSpectrum(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeZSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLZSpectrumFactory::InitializeZSpectrum(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterZSpectrum(const QString name, const QString &pluginName)
{
	CrpsSLZSpectrumFactory::UnregisterZSpectrum(name, pluginName);
}

////////////////////////////////////Across wind target spectrum//////////////////////////////////////////

void RegisterYSpectrum(const QString name, const QString &pluginName, const QString &description, YSpectrumInitFunc init_cb, YSpectrumFreeFunc free_cb)
{
	if (CrpsSLYSpectrumFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLYSpectrumFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}
	CrpsSLYSpectrumFactory::RegisterYSpectrum(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeYSpectrum(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLYSpectrumFactory::InitializeYSpectrum(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterYSpectrum(const QString name, const QString &pluginName)
{
	CrpsSLYSpectrumFactory::UnregisterYSpectrum(name, pluginName);
}


////////////////////////////////////Frequency distribution//////////////////////////////////////////

void RegisterFrequencyDistribution(const QString name, const QString &pluginName, const QString &description, FrequencyDistributionInitFunc init_cb, FrequencyDistributionFreeFunc free_cb)
{
	if (CrpsSLFrequencyDistributionFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLFrequencyDistributionFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSLFrequencyDistributionFactory::RegisterFrequencyDistribution(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeFrequencyDistribution(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLFrequencyDistributionFactory::InitializeFrequencyDistribution(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterFrequencyDistribution(const QString name, const QString &pluginName)
{
	CrpsSLFrequencyDistributionFactory::UnregisterFrequencyDistribution(name, pluginName);
}


////////////////////////////////////Randomness//////////////////////////////////////////

void RegisterRandomness(const QString name, const QString &pluginName, const QString &description, RandomnessInitFunc init_cb, RandomnessFreeFunc free_cb)
{
	if (CrpsSLRandomnessFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLRandomnessFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSLRandomnessFactory::RegisterRandomness(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeRandomness(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLRandomnessFactory::InitializeRandomness(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterRandomness(const QString name, const QString &pluginName)
{
	CrpsSLRandomnessFactory::UnregisterRandomness(name, pluginName);
}


////////////////////////////////////psd decomposition//////////////////////////////////////////

void RegisterPSDdecomMethod(const QString name, const QString &pluginName, const QString &description, PSDdecomMethodInitFunc init_cb, PSDdecomMethodFreeFunc free_cb)
{
	if (CrpsSLPSDdecomMethodFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLPSDdecomMethodFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSLPSDdecomMethodFactory::RegisterPSDdecomMethod(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializePSDdecomMethod(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLPSDdecomMethodFactory::InitializePSDdecomMethod(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterPSDdecomMethod(const QString name, const QString &pluginName)
{
	CrpsSLPSDdecomMethodFactory::UnregisterPSDdecomMethod(name, pluginName);
}

////////////////////////////////////Correlation//////////////////////////////////////////

void RegisterCorrelation(const QString name, const QString &pluginName, const QString &description, CorrelationInitFunc init_cb, CorrelationFreeFunc free_cb)
{
	if (CrpsSLCorrelationFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLCorrelationFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSLCorrelationFactory::RegisterCorrelation(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeCorrelation(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLCorrelationFactory::InitializeCorrelation(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterCorrelation(const QString name, const QString &pluginName)
{
	CrpsSLCorrelationFactory::UnregisterCorrelation(name, pluginName);
}

////////////////////////////////////Modulation//////////////////////////////////////////

void RegisterModulation(const QString name, const QString &pluginName, const QString &description, ModulationInitFunc init_cb, ModulationFreeFunc free_cb)
{
	if (CrpsSLModulationFactory::GetTobeInstalledObjectsMap().find(name) ==
		CrpsSLModulationFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

	CrpsSLModulationFactory::RegisterModulation(name, pluginName, description, init_cb);
	(void)free_cb; // we never free these objects
}

void InitializeModulation(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	CrpsSLModulationFactory::InitializeModulation(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate);
}

void UnregisterModulation(const QString name, const QString &pluginName)
{
	CrpsSLModulationFactory::UnregisterModulation(name, pluginName);
}


