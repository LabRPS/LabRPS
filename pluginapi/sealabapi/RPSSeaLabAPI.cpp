#include "RPSSeaLabAPI.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef IrpsSeLSimulationMethod *(*CreateSLSimulationMethodCallback)();
typedef IrpsSeLMean *(*CreateMeanCallback)();
typedef IrpsSeLLocationDistribution *(*CreateSLLocDistrCallback)();
typedef IrpsSeLSpectrum *(*CreateSLXSpectrumCallback)();
typedef IrpsSeLCoherence *(*CreateSLCoherenceCallback)();
typedef IrpsSeLFrequencyDistribution *(*CreateSLFrequencyDistributionCallback)();
typedef IrpsSeLRandomness *(*CreateSLRandomnessCallback)();
typedef IrpsSeLPSDdecompositionMethod *(*CreateSLPSDdecomMethodCallback)();
typedef IrpsSeLCorrelation *(*CreateSLCorrelationCallback)();
typedef IrpsSeLModulation *(*CreateSLModulationCallback)();

typedef IrpsSeLDirectionalSpectrum *(*CreateSLDirectionalSpectrumCallback)();
typedef IrpsSeLDirectionDistribution *(*CreateSLDirectionDistributionCallback)();
typedef IrpsSeLDirectionSpreadingFunction *(*CreateSLDirectionSpreadingFunctionCallback)();


///////////////////////////////////////////Spectral representation method/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLSimulationMethodFactory::CallbackMap  CrpsSeLSimulationMethodFactory::mSLSimulationMethods;
QString  CrpsSeLSimulationMethodFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLSimulationMethodFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLSimulationMethodFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLSimulationMethodFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLSimulationMethodFactory::mOjectsSkipDuringUnintallationMap;
	
std::map<const QString, QString> CrpsSeLSimulationMethodFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLSimulationMethodFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLSimulationMethodFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLSimulationMethodFactory::mDateMap;
//QString  CrpsSeLSimulationMethodFactory::mDescription;

QString  CrpsSeLSimulationMethodFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLSimulationMethodFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLSimulationMethodFactory::InitializeSLSimulationMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString  CrpsSeLSimulationMethodFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLSimulationMethodFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLSimulationMethodFactory::RegisterSLSimulationMethod(const QString &name, const QString &pluginName, const QString &description, CreateSLSimulationMethodCallback cb)
{

	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mSLSimulationMethods[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLSimulationMethodFactory::UnregisterSLSimulationMethod(const QString &name, const QString &pluginName)
{
	
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mSLSimulationMethods.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLSimulationMethod * CrpsSeLSimulationMethodFactory::BuildSLSimulationMethod(const QString &name)
{
	CallbackMap::iterator it = mSLSimulationMethods.find(name);
	if (it != mSLSimulationMethods.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLSimulationMethodCallback>&  CrpsSeLSimulationMethodFactory::GetSLSimulationMethodNamesMap()
{
	return mSLSimulationMethods;
}

std::map<const QString, QString> &  CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLSimulationMethodFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLSimulationMethodFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}
///
std::map<const QString, QString>& CrpsSeLSimulationMethodFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLSimulationMethodFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLSimulationMethodFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLSimulationMethodFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSeLSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////kkkkkkk
//// instantiate the static variable
CrpsSeLMeanFactory::CallbackMap CrpsSeLMeanFactory::mMeans;
QString CrpsSeLMeanFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSeLMeanFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSeLMeanFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSeLMeanFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSeLMeanFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLMeanFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLMeanFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLMeanFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLMeanFactory::mDateMap;
//QString CrpsMeanFactory::mDescription;

QString CrpsSeLMeanFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSeLMeanFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSeLMeanFactory::InitializeMean(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsMeanFactory::GetDescription()
{
	return mDescription;
}
void CrpsMeanFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSeLMeanFactory::RegisterMean(const QString &name, const QString &pluginName, const QString &description, CreateMeanCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mMeans[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);
}

void CrpsSeLMeanFactory::UnregisterMean(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mMeans.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}


}

IrpsSeLMean *CrpsSeLMeanFactory::BuildMean(const QString &name)
{
	CallbackMap::iterator it = mMeans.find(name);
	if (it != mMeans.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateMeanCallback>& CrpsSeLMeanFactory::GetMeanNamesMap()
{
	return mMeans;
}

std::map<const QString, QString> & CrpsSeLMeanFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSeLMeanFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}
std::map<const QString, QString>& CrpsSeLMeanFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLMeanFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLMeanFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLMeanFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLMeanFactory::GetDateMap()
{
	return mDateMap;
}
std::map<const QString, QString> &  CrpsSeLMeanFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////Coherence////////
//// instantiate the static variable
 CrpsSeLCoherenceFactory::CallbackMap  CrpsSeLCoherenceFactory::mCoherences;
std::vector<QString>  CrpsSeLCoherenceFactory::mCoherenceNames;
QString  CrpsSeLCoherenceFactory::mOwnerPlugin;
//QString  CrpsSeLCoherenceFactory::mDescription;
std::map<const QString, QString>  CrpsSeLCoherenceFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLCoherenceFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLCoherenceFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSeLCoherenceFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLCoherenceFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLCoherenceFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLCoherenceFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLCoherenceFactory::mDateMap;
QString  CrpsSeLCoherenceFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLCoherenceFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

/*QString  CrpsSeLCoherenceFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLCoherenceFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLCoherenceFactory::InitializeCoherence(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

void  CrpsSeLCoherenceFactory::RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateSLCoherenceCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}
	mCoherences[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;
	SetOwnerPlugin(pluginName);
	//SetDescription(description);
}

void  CrpsSeLCoherenceFactory::UnregisterCoherence(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mCoherences.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLCoherence * CrpsSeLCoherenceFactory::BuildCoherence(const QString &name)
{
	CallbackMap::iterator it = mCoherences.find(name);
	if (it != mCoherences.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLCoherenceCallback>&  CrpsSeLCoherenceFactory::GetCoherenceNamesMap()
{
	return mCoherences;
}

std::vector<QString>  CrpsSeLCoherenceFactory::GetNameVector()
{
	return mCoherenceNames;
}

std::map<const QString, QString> &  CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLCoherenceFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLCoherenceFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLCoherenceFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLCoherenceFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLCoherenceFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLCoherenceFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSeLCoherenceFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Location distribution/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLLocationDistributionFactory::CallbackMap  CrpsSeLLocationDistributionFactory::mLocationDistributions;
std::map<const QString, QString>  CrpsSeLLocationDistributionFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLLocationDistributionFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLLocationDistributionFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLLocationDistributionFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLLocationDistributionFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLLocationDistributionFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLLocationDistributionFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLLocationDistributionFactory::mDateMap;
//std::vector<QString>  CrpsSeLLocationDistributionFactory::mLocDistrNames;

QString  CrpsSeLLocationDistributionFactory::mOwnerPlugin;
//QString  CrpsSeLLocationDistributionFactory::mDescription;

QString  CrpsSeLLocationDistributionFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLLocationDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLLocationDistributionFactory::InitializeLocationDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString  CrpsSeLLocationDistributionFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLLocationDistributionFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLLocationDistributionFactory::RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateSLLocDistrCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mLocationDistributions[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLLocationDistributionFactory::UnregisterLocationDistribution(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mLocationDistributions.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}
}

IrpsSeLLocationDistribution * CrpsSeLLocationDistributionFactory::BuildLocationDistribution(const QString &name)
{
	CallbackMap::iterator it = mLocationDistributions.find(name);
	if (it != mLocationDistributions.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}


std::map<const QString, CreateSLLocDistrCallback>&  CrpsSeLLocationDistributionFactory::GetLocDistrNamesMap()
{
	return mLocationDistributions;
}

std::map<const QString, QString> &  CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLLocationDistributionFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLLocationDistributionFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLLocationDistributionFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLLocationDistributionFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLLocationDistributionFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLLocationDistributionFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSeLLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Along wind target spectrum/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLXSpectrumFactory::CallbackMap  CrpsSeLXSpectrumFactory::mXSpectrums;
QString  CrpsSeLXSpectrumFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLXSpectrumFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLXSpectrumFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLXSpectrumFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLXSpectrumFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLXSpectrumFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLXSpectrumFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLXSpectrumFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLXSpectrumFactory::mDateMap;
//QString  CrpsSeLXSpectrumFactory::mDescription;

QString  CrpsSeLXSpectrumFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLXSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLXSpectrumFactory::InitializeXSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString  CrpsSeLXSpectrumFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLXSpectrumFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLXSpectrumFactory::RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateSLXSpectrumCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mXSpectrums[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLXSpectrumFactory::UnregisterXSpectrum(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mXSpectrums.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLSpectrum * CrpsSeLXSpectrumFactory::BuildXSpectrum(const QString &name)
{
	CallbackMap::iterator it = mXSpectrums.find(name);
	if (it != mXSpectrums.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLXSpectrumCallback>&  CrpsSeLXSpectrumFactory::GetXSpectrumNamesMap()
{
	return mXSpectrums;
}

std::map<const QString, QString> &  CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLXSpectrumFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLXSpectrumFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLXSpectrumFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLXSpectrumFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLXSpectrumFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLXSpectrumFactory::GetDateMap()
{
	return mDateMap;
}
std::map<const QString, QString> &  CrpsSeLXSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}

///////////////////////////////////////////Frequency distribution/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLFrequencyDistributionFactory::CallbackMap  CrpsSeLFrequencyDistributionFactory::mFrequencyDistributions;
QString  CrpsSeLFrequencyDistributionFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLFrequencyDistributionFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLFrequencyDistributionFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLFrequencyDistributionFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLFrequencyDistributionFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLFrequencyDistributionFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLFrequencyDistributionFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLFrequencyDistributionFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLFrequencyDistributionFactory::mDateMap;
//QString  CrpsSeLFrequencyDistributionFactory::mDescription;

QString  CrpsSeLFrequencyDistributionFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLFrequencyDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLFrequencyDistributionFactory::InitializeFrequencyDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString  CrpsSeLFrequencyDistributionFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLFrequencyDistributionFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLFrequencyDistributionFactory::RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateSLFrequencyDistributionCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mFrequencyDistributions[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLFrequencyDistributionFactory::UnregisterFrequencyDistribution(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mFrequencyDistributions.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLFrequencyDistribution * CrpsSeLFrequencyDistributionFactory::BuildFrequencyDistribution(const QString &name)
{
	CallbackMap::iterator it = mFrequencyDistributions.find(name);
	if (it != mFrequencyDistributions.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLFrequencyDistributionCallback>&  CrpsSeLFrequencyDistributionFactory::GetFrequencyDistributionNamesMap()
{
	return mFrequencyDistributions;
}

std::map<const QString, QString> &  CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLFrequencyDistributionFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLFrequencyDistributionFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLFrequencyDistributionFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLFrequencyDistributionFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLFrequencyDistributionFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLFrequencyDistributionFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSeLFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Randomness/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLRandomnessFactory::CallbackMap  CrpsSeLRandomnessFactory::mRandomness;
QString  CrpsSeLRandomnessFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLRandomnessFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLRandomnessFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLRandomnessFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLRandomnessFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLRandomnessFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLRandomnessFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLRandomnessFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLRandomnessFactory::mDateMap;
//QString  CrpsSeLRandomnessFactory::mDescription;

QString  CrpsSeLRandomnessFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLRandomnessFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLRandomnessFactory::InitializeRandomness(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;

	
}

/*QString  CrpsSeLRandomnessFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLRandomnessFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLRandomnessFactory::RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateSLRandomnessCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mRandomness[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLRandomnessFactory::UnregisterRandomness(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mRandomness.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLRandomness * CrpsSeLRandomnessFactory::BuildRandomness(const QString &name)
{
	CallbackMap::iterator it = mRandomness.find(name);
	if (it != mRandomness.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLRandomnessCallback>&  CrpsSeLRandomnessFactory::GetRandomnessNamesMap()
{
	return mRandomness;
}

std::map<const QString, QString> &  CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLRandomnessFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLRandomnessFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLRandomnessFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLRandomnessFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLRandomnessFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLRandomnessFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSeLRandomnessFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////psd decomposition/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLPSDdecomMethodFactory::CallbackMap  CrpsSeLPSDdecomMethodFactory::mPSDdecomMethods;
QString  CrpsSeLPSDdecomMethodFactory::mOwnerPlugin;
//QString  CrpsSeLPSDdecomMethodFactory::mDescription;
std::map<const QString, QString>  CrpsSeLPSDdecomMethodFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLPSDdecomMethodFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLPSDdecomMethodFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLPSDdecomMethodFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLPSDdecomMethodFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLPSDdecomMethodFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLPSDdecomMethodFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLPSDdecomMethodFactory::mDateMap;

QString  CrpsSeLPSDdecomMethodFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLPSDdecomMethodFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLPSDdecomMethodFactory::InitializePSDdecomMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString  CrpsSeLPSDdecomMethodFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLPSDdecomMethodFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLPSDdecomMethodFactory::RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreateSLPSDdecomMethodCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mPSDdecomMethods[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLPSDdecomMethodFactory::UnregisterPSDdecomMethod(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mPSDdecomMethods.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}


}

IrpsSeLPSDdecompositionMethod * CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(const QString &name)
{
	CallbackMap::iterator it = mPSDdecomMethods.find(name);
	if (it != mPSDdecomMethods.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLPSDdecomMethodCallback>&  CrpsSeLPSDdecomMethodFactory::GetPSDdecomMethodNamesMap()
{
	return mPSDdecomMethods;
}

std::map<const QString, QString> &  CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLPSDdecomMethodFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLPSDdecomMethodFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLPSDdecomMethodFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLPSDdecomMethodFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLPSDdecomMethodFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLPSDdecomMethodFactory::GetDateMap()
{
	return mDateMap;
}
std::map<const QString, QString> &  CrpsSeLPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Correlation/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLCorrelationFactory::CallbackMap  CrpsSeLCorrelationFactory::mCorrelations;
QString  CrpsSeLCorrelationFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLCorrelationFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLCorrelationFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLCorrelationFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLCorrelationFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLCorrelationFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLCorrelationFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLCorrelationFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLCorrelationFactory::mDateMap;

//QString  CrpsSeLCorrelationFactory::mDescription;

QString  CrpsSeLCorrelationFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLCorrelationFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLCorrelationFactory::InitializeCorrelation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString  CrpsSeLCorrelationFactory::GetDescription()
{
	return mDescription;
}
void  CrpsSeLCorrelationFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void  CrpsSeLCorrelationFactory::RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateSLCorrelationCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mCorrelations[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLCorrelationFactory::UnregisterCorrelation(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mCorrelations.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLCorrelation * CrpsSeLCorrelationFactory::BuildCorrelation(const QString &name)
{
	CallbackMap::iterator it = mCorrelations.find(name);
	if (it != mCorrelations.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLCorrelationCallback>&  CrpsSeLCorrelationFactory::GetCorrelationNamesMap()
{
	return mCorrelations;
}

std::map<const QString, QString> &  CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLCorrelationFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLCorrelationFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLCorrelationFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLCorrelationFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLCorrelationFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLCorrelationFactory::GetDateMap()
{
	return mDateMap;
}
std::map<const QString, QString> &  CrpsSeLCorrelationFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Modulation/////////////////////////////////////////////////

//// instantiate the static variable
 CrpsSeLModulationFactory::CallbackMap  CrpsSeLModulationFactory::mModulations;
QString  CrpsSeLModulationFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLModulationFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLModulationFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLModulationFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLModulationFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLModulationFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLModulationFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLModulationFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLModulationFactory::mDateMap;

//QString  CrpsSeLModulationFactory::mDescription;

QString  CrpsSeLModulationFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLModulationFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLModulationFactory::InitializeModulation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}


void  CrpsSeLModulationFactory::RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateSLModulationCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mModulations[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLModulationFactory::UnregisterModulation(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mModulations.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLModulation * CrpsSeLModulationFactory::BuildModulation(const QString &name)
{
	CallbackMap::iterator it = mModulations.find(name);
	if (it != mModulations.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLModulationCallback>&  CrpsSeLModulationFactory::GetModulationNamesMap()
{
	return mModulations;
}

std::map<const QString, QString> &  CrpsSeLModulationFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLModulationFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLModulationFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLModulationFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLModulationFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLModulationFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLModulationFactory::GetDateMap()
{
	return mDateMap;
}
std::map<const QString, QString> &  CrpsSeLModulationFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}

///////////////////////////////////////////DirectionalSpectrum/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSeLDirectionalSpectrumFactory::CallbackMap  CrpsSeLDirectionalSpectrumFactory::mDirectionalSpectrums;
QString  CrpsSeLDirectionalSpectrumFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLDirectionalSpectrumFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLDirectionalSpectrumFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLDirectionalSpectrumFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLDirectionalSpectrumFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLDirectionalSpectrumFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLDirectionalSpectrumFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLDirectionalSpectrumFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLDirectionalSpectrumFactory::mDateMap;

//QString  CrpsSeLDirectionalSpectrumFactory::mDescription;

QString  CrpsSeLDirectionalSpectrumFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLDirectionalSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLDirectionalSpectrumFactory::InitializeDirectionalSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}


void  CrpsSeLDirectionalSpectrumFactory::RegisterDirectionalSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateSLDirectionalSpectrumCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mDirectionalSpectrums[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLDirectionalSpectrumFactory::UnregisterDirectionalSpectrum(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mDirectionalSpectrums.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLDirectionalSpectrum * CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(const QString &name)
{
	CallbackMap::iterator it = mDirectionalSpectrums.find(name);
	if (it != mDirectionalSpectrums.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLDirectionalSpectrumCallback>&  CrpsSeLDirectionalSpectrumFactory::GetDirectionalSpectrumNamesMap()
{
	return mDirectionalSpectrums;
}

std::map<const QString, QString> &  CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLDirectionalSpectrumFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLDirectionalSpectrumFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLDirectionalSpectrumFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLDirectionalSpectrumFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLDirectionalSpectrumFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLDirectionalSpectrumFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSeLDirectionalSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////DirectionDistribution/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSeLDirectionDistributionFactory::CallbackMap  CrpsSeLDirectionDistributionFactory::mDirectionDistributions;
QString  CrpsSeLDirectionDistributionFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLDirectionDistributionFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLDirectionDistributionFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLDirectionDistributionFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLDirectionDistributionFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLDirectionDistributionFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLDirectionDistributionFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLDirectionDistributionFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLDirectionDistributionFactory::mDateMap;

//QString  CrpsSeLDirectionDistributionFactory::mDescription;

QString  CrpsSeLDirectionDistributionFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLDirectionDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLDirectionDistributionFactory::InitializeDirectionDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}


void  CrpsSeLDirectionDistributionFactory::RegisterDirectionDistribution(const QString &name, const QString &pluginName, const QString &description, CreateSLDirectionDistributionCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mDirectionDistributions[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLDirectionDistributionFactory::UnregisterDirectionDistribution(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mDirectionDistributions.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLDirectionDistribution * CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(const QString &name)
{
	CallbackMap::iterator it = mDirectionDistributions.find(name);
	if (it != mDirectionDistributions.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLDirectionDistributionCallback>&  CrpsSeLDirectionDistributionFactory::GetDirectionDistributionNamesMap()
{
	return mDirectionDistributions;
}

std::map<const QString, QString> &  CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLDirectionDistributionFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLDirectionDistributionFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLDirectionDistributionFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLDirectionDistributionFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLDirectionDistributionFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLDirectionDistributionFactory::GetDateMap()
{
	return mDateMap;
}
std::map<const QString, QString> &  CrpsSeLDirectionDistributionFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////DirectionSpreadingFunction/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSeLDirectionSpreadingFunctionFactory::CallbackMap  CrpsSeLDirectionSpreadingFunctionFactory::mDirectionSpreadingFunctions;
QString  CrpsSeLDirectionSpreadingFunctionFactory::mOwnerPlugin;
std::map<const QString, QString>  CrpsSeLDirectionSpreadingFunctionFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString>  CrpsSeLDirectionSpreadingFunctionFactory::mOjectDescriptionMap;
std::map<const QString, QString>  CrpsSeLDirectionSpreadingFunctionFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSeLDirectionSpreadingFunctionFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSeLDirectionSpreadingFunctionFactory::mTitleMap;
std::map<const QString, QString> CrpsSeLDirectionSpreadingFunctionFactory::mLinkMap;
std::map<const QString, QString> CrpsSeLDirectionSpreadingFunctionFactory::mAuthorMap;
std::map<const QString, QString> CrpsSeLDirectionSpreadingFunctionFactory::mDateMap;

//QString  CrpsSeLDirectionSpreadingFunctionFactory::mDescription;

QString  CrpsSeLDirectionSpreadingFunctionFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void  CrpsSeLDirectionSpreadingFunctionFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void  CrpsSeLDirectionSpreadingFunctionFactory::InitializeDirectionSpreadingFunction(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}


void  CrpsSeLDirectionSpreadingFunctionFactory::RegisterDirectionSpreadingFunction(const QString &name, const QString &pluginName, const QString &description, CreateSLDirectionSpreadingFunctionCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mDirectionSpreadingFunctions[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void  CrpsSeLDirectionSpreadingFunctionFactory::UnregisterDirectionSpreadingFunction(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mDirectionSpreadingFunctions.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSeLDirectionSpreadingFunction * CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(const QString &name)
{
	CallbackMap::iterator it = mDirectionSpreadingFunctions.find(name);
	if (it != mDirectionSpreadingFunctions.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLDirectionSpreadingFunctionCallback>&  CrpsSeLDirectionSpreadingFunctionFactory::GetDirectionSpreadingFunctionNamesMap()
{
	return mDirectionSpreadingFunctions;
}

std::map<const QString, QString> &  CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>&  CrpsSeLDirectionSpreadingFunctionFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>&  CrpsSeLDirectionSpreadingFunctionFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///
std::map<const QString, QString>& CrpsSeLDirectionSpreadingFunctionFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSeLDirectionSpreadingFunctionFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSeLDirectionSpreadingFunctionFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSeLDirectionSpreadingFunctionFactory::GetDateMap()
{
	return mDateMap;
}
std::map<const QString, QString> &  CrpsSeLDirectionSpreadingFunctionFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}