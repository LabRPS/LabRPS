
#include "RPSSeismicLabAPI.h"
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef IrpsSLSimulationMethod *(*CreateSLSimulationMethodCallback)();

typedef IrpsSLLocationDistribution *(*CreateSLLocDistrCallback)();
typedef IrpsSLXSpectrum *(*CreateSLXSpectrumCallback)();
typedef IrpsSLZSpectrum *(*CreateSLZSpectrumCallback)();
typedef IrpsSLYSpectrum *(*CreateSLYSpectrumCallback)();
typedef IrpsSLCoherence *(*CreateSLCoherenceCallback)();
typedef IrpsSLFrequencyDistribution *(*CreateSLFrequencyDistributionCallback)();
typedef IrpsSLRandomness *(*CreateSLRandomnessCallback)();
typedef IrpsSLPSDdecompositionMethod *(*CreateSLPSDdecomMethodCallback)();
typedef IrpsSLCorrelation *(*CreateSLCorrelationCallback)();
typedef IrpsSLModulation *(*CreateSLModulationCallback)();

///////////////////////////////////////////Spectral representation method/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLSimulationMethodFactory::CallbackMap CrpsSLSimulationMethodFactory::mSLSimulationMethods;
QString CrpsSLSimulationMethodFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLSimulationMethodFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLSimulationMethodFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLSimulationMethodFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSLSimulationMethodFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLSimulationMethodFactory::mTitleMap;
std::map<const QString, QString> CrpsSLSimulationMethodFactory::mLinkMap;
std::map<const QString, QString> CrpsSLSimulationMethodFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLSimulationMethodFactory::mDateMap;


//QString CrpsSLSimulationMethodFactory::mDescription;

QString CrpsSLSimulationMethodFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLSimulationMethodFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLSimulationMethodFactory::InitializeSLSimulationMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;

}

/*QString CrpsSLSimulationMethodFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLSimulationMethodFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLSimulationMethodFactory::RegisterSLSimulationMethod(const QString &name, const QString &pluginName, const QString &description, CreateSLSimulationMethodCallback cb)
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

void CrpsSLSimulationMethodFactory::UnregisterSLSimulationMethod(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mSLSimulationMethods.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLSimulationMethod *CrpsSLSimulationMethodFactory::BuildSLSimulationMethod(const QString &name)
{
	CallbackMap::iterator it = mSLSimulationMethods.find(name);
	if (it != mSLSimulationMethods.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLSimulationMethodCallback>& CrpsSLSimulationMethodFactory::GetSLSimulationMethodNamesMap()
{
	return mSLSimulationMethods;
}

std::map<const QString, QString> & CrpsSLSimulationMethodFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLSimulationMethodFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLSimulationMethodFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

std::map<const QString, QString>& CrpsSLSimulationMethodFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLSimulationMethodFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLSimulationMethodFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLSimulationMethodFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////kkkkkkk



///////Coherence////////
//// instantiate the static variable
CrpsSLCoherenceFactory::CallbackMap CrpsSLCoherenceFactory::mCoherences;
std::vector<QString> CrpsSLCoherenceFactory::mCoherenceNames;
QString CrpsSLCoherenceFactory::mOwnerPlugin;
//QString CrpsSLCoherenceFactory::mDescription;
std::map<const QString, QString> CrpsSLCoherenceFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLCoherenceFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLCoherenceFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSLCoherenceFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLCoherenceFactory::mTitleMap;
std::map<const QString, QString> CrpsSLCoherenceFactory::mLinkMap;
std::map<const QString, QString> CrpsSLCoherenceFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLCoherenceFactory::mDateMap;

QString CrpsSLCoherenceFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLCoherenceFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

/*QString CrpsSLCoherenceFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLCoherenceFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLCoherenceFactory::InitializeCoherence(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

void CrpsSLCoherenceFactory::RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateSLCoherenceCallback cb)
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

void CrpsSLCoherenceFactory::UnregisterCoherence(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mCoherences.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLCoherence *CrpsSLCoherenceFactory::BuildCoherence(const QString &name)
{
	CallbackMap::iterator it = mCoherences.find(name);
	if (it != mCoherences.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLCoherenceCallback>& CrpsSLCoherenceFactory::GetCoherenceNamesMap()
{
	return mCoherences;
}

std::vector<QString> CrpsSLCoherenceFactory::GetNameVector()
{
	return mCoherenceNames;
}

std::map<const QString, QString> & CrpsSLCoherenceFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLCoherenceFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLCoherenceFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}


std::map<const QString, QString>& CrpsSLCoherenceFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLCoherenceFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLCoherenceFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLCoherenceFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLCoherenceFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Location distribution/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLLocationDistributionFactory::CallbackMap CrpsSLLocationDistributionFactory::mLocationDistributions;
std::map<const QString, QString> CrpsSLLocationDistributionFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLLocationDistributionFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLLocationDistributionFactory::mOjectAndPluginMap;
std::map<const QString, QString>  CrpsSLLocationDistributionFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLLocationDistributionFactory::mTitleMap;
std::map<const QString, QString> CrpsSLLocationDistributionFactory::mLinkMap;
std::map<const QString, QString> CrpsSLLocationDistributionFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLLocationDistributionFactory::mDateMap;
//std::vector<QString> CrpsSLLocationDistributionFactory::mLocDistrNames;

QString CrpsSLLocationDistributionFactory::mOwnerPlugin;
//QString CrpsSLLocationDistributionFactory::mDescription;

QString CrpsSLLocationDistributionFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLLocationDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLLocationDistributionFactory::InitializeLocationDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLLocationDistributionFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLLocationDistributionFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLLocationDistributionFactory::RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateSLLocDistrCallback cb)
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

void CrpsSLLocationDistributionFactory::UnregisterLocationDistribution(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mLocationDistributions.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}
}

IrpsSLLocationDistribution *CrpsSLLocationDistributionFactory::BuildLocationDistribution(const QString &name)
{
	CallbackMap::iterator it = mLocationDistributions.find(name);
	if (it != mLocationDistributions.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}


std::map<const QString, CreateSLLocDistrCallback>& CrpsSLLocationDistributionFactory::GetLocDistrNamesMap()
{
	return mLocationDistributions;
}

std::map<const QString, QString> & CrpsSLLocationDistributionFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLLocationDistributionFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLLocationDistributionFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

///

std::map<const QString, QString>& CrpsSLLocationDistributionFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLLocationDistributionFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLLocationDistributionFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLLocationDistributionFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}

///////////////////////////////////////////Along wind target spectrum/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLXSpectrumFactory::CallbackMap CrpsSLXSpectrumFactory::mXSpectrums;
QString CrpsSLXSpectrumFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLXSpectrumFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLXSpectrumFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLXSpectrumFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLXSpectrumFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLXSpectrumFactory::mTitleMap;
std::map<const QString, QString> CrpsSLXSpectrumFactory::mLinkMap;
std::map<const QString, QString> CrpsSLXSpectrumFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLXSpectrumFactory::mDateMap;
//QString CrpsSLXSpectrumFactory::mDescription;

QString CrpsSLXSpectrumFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLXSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLXSpectrumFactory::InitializeXSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLXSpectrumFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLXSpectrumFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLXSpectrumFactory::RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateSLXSpectrumCallback cb)
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

void CrpsSLXSpectrumFactory::UnregisterXSpectrum(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mXSpectrums.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLXSpectrum *CrpsSLXSpectrumFactory::BuildXSpectrum(const QString &name)
{
	CallbackMap::iterator it = mXSpectrums.find(name);
	if (it != mXSpectrums.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLXSpectrumCallback>& CrpsSLXSpectrumFactory::GetXSpectrumNamesMap()
{
	return mXSpectrums;
}

std::map<const QString, QString> & CrpsSLXSpectrumFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLXSpectrumFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLXSpectrumFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLXSpectrumFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLXSpectrumFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLXSpectrumFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLXSpectrumFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLXSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}

///////////////////////////////////////////Vertical wind target spectrum/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLZSpectrumFactory::CallbackMap CrpsSLZSpectrumFactory::mZSpectrums;
QString CrpsSLZSpectrumFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLZSpectrumFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLZSpectrumFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLZSpectrumFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLZSpectrumFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLZSpectrumFactory::mTitleMap;
std::map<const QString, QString> CrpsSLZSpectrumFactory::mLinkMap;
std::map<const QString, QString> CrpsSLZSpectrumFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLZSpectrumFactory::mDateMap;
//QString CrpsSLZSpectrumFactory::mDescription;

QString CrpsSLZSpectrumFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLZSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLZSpectrumFactory::InitializeZSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLZSpectrumFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLZSpectrumFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLZSpectrumFactory::RegisterZSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateSLZSpectrumCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mZSpectrums[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void CrpsSLZSpectrumFactory::UnregisterZSpectrum(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mZSpectrums.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLZSpectrum *CrpsSLZSpectrumFactory::BuildZSpectrum(const QString &name)
{
	CallbackMap::iterator it = mZSpectrums.find(name);
	if (it != mZSpectrums.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLZSpectrumCallback>& CrpsSLZSpectrumFactory::GetZSpectrumNamesMap()
{
	return mZSpectrums;
}

std::map<const QString, QString> & CrpsSLZSpectrumFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLZSpectrumFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLZSpectrumFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLZSpectrumFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLZSpectrumFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLZSpectrumFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLZSpectrumFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLZSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Across wind target spectrum/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLYSpectrumFactory::CallbackMap CrpsSLYSpectrumFactory::mYSpectrums;
QString CrpsSLYSpectrumFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLYSpectrumFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLYSpectrumFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLYSpectrumFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLYSpectrumFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLYSpectrumFactory::mTitleMap;
std::map<const QString, QString> CrpsSLYSpectrumFactory::mLinkMap;
std::map<const QString, QString> CrpsSLYSpectrumFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLYSpectrumFactory::mDateMap;
//QString CrpsSLYSpectrumFactory::mDescription;

QString CrpsSLYSpectrumFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLYSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLYSpectrumFactory::InitializeYSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLYSpectrumFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLYSpectrumFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLYSpectrumFactory::RegisterYSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateSLYSpectrumCallback cb)
{
	if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
	{
		return;
	}

	mYSpectrums[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;

	SetOwnerPlugin(pluginName);
	//SetDescription(description);

}

void CrpsSLYSpectrumFactory::UnregisterYSpectrum(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mYSpectrums.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLYSpectrum *CrpsSLYSpectrumFactory::BuildYSpectrum(const QString &name)
{
	CallbackMap::iterator it = mYSpectrums.find(name);
	if (it != mYSpectrums.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLYSpectrumCallback>& CrpsSLYSpectrumFactory::GetYSpectrumNamesMap()
{
	return mYSpectrums;
}

std::map<const QString, QString> & CrpsSLYSpectrumFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLYSpectrumFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLYSpectrumFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLYSpectrumFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLYSpectrumFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLYSpectrumFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLYSpectrumFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLYSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Frequency distribution/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLFrequencyDistributionFactory::CallbackMap CrpsSLFrequencyDistributionFactory::mFrequencyDistributions;
QString CrpsSLFrequencyDistributionFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mTitleMap;
std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mLinkMap;
std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLFrequencyDistributionFactory::mDateMap;
//QString CrpsSLFrequencyDistributionFactory::mDescription;

QString CrpsSLFrequencyDistributionFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLFrequencyDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLFrequencyDistributionFactory::InitializeFrequencyDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLFrequencyDistributionFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLFrequencyDistributionFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLFrequencyDistributionFactory::RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateSLFrequencyDistributionCallback cb)
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

void CrpsSLFrequencyDistributionFactory::UnregisterFrequencyDistribution(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mFrequencyDistributions.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLFrequencyDistribution *CrpsSLFrequencyDistributionFactory::BuildFrequencyDistribution(const QString &name)
{
	CallbackMap::iterator it = mFrequencyDistributions.find(name);
	if (it != mFrequencyDistributions.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLFrequencyDistributionCallback>& CrpsSLFrequencyDistributionFactory::GetFrequencyDistributionNamesMap()
{
	return mFrequencyDistributions;
}

std::map<const QString, QString> & CrpsSLFrequencyDistributionFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLFrequencyDistributionFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLFrequencyDistributionFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLFrequencyDistributionFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLFrequencyDistributionFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLFrequencyDistributionFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLFrequencyDistributionFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////Randomness/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLRandomnessFactory::CallbackMap CrpsSLRandomnessFactory::mRandomness;
QString CrpsSLRandomnessFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLRandomnessFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLRandomnessFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLRandomnessFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLRandomnessFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLRandomnessFactory::mTitleMap;
std::map<const QString, QString> CrpsSLRandomnessFactory::mLinkMap;
std::map<const QString, QString> CrpsSLRandomnessFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLRandomnessFactory::mDateMap;
//QString CrpsSLRandomnessFactory::mDescription;

QString CrpsSLRandomnessFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLRandomnessFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLRandomnessFactory::InitializeRandomness(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLRandomnessFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLRandomnessFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLRandomnessFactory::RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateSLRandomnessCallback cb)
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

void CrpsSLRandomnessFactory::UnregisterRandomness(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mRandomness.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLRandomness *CrpsSLRandomnessFactory::BuildRandomness(const QString &name)
{
	CallbackMap::iterator it = mRandomness.find(name);
	if (it != mRandomness.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLRandomnessCallback>& CrpsSLRandomnessFactory::GetRandomnessNamesMap()
{
	return mRandomness;
}

std::map<const QString, QString> & CrpsSLRandomnessFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLRandomnessFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLRandomnessFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLRandomnessFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLRandomnessFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLRandomnessFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLRandomnessFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLRandomnessFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}
///////////////////////////////////////////psd decomposition/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLPSDdecomMethodFactory::CallbackMap CrpsSLPSDdecomMethodFactory::mPSDdecomMethods;
QString CrpsSLPSDdecomMethodFactory::mOwnerPlugin;
//QString CrpsSLPSDdecomMethodFactory::mDescription;
std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mTitleMap;
std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mLinkMap;
std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLPSDdecomMethodFactory::mDateMap;
QString CrpsSLPSDdecomMethodFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLPSDdecomMethodFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLPSDdecomMethodFactory::InitializePSDdecomMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLPSDdecomMethodFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLPSDdecomMethodFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLPSDdecomMethodFactory::RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreateSLPSDdecomMethodCallback cb)
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

void CrpsSLPSDdecomMethodFactory::UnregisterPSDdecomMethod(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mPSDdecomMethods.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}


}

IrpsSLPSDdecompositionMethod *CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(const QString &name)
{
	CallbackMap::iterator it = mPSDdecomMethods.find(name);
	if (it != mPSDdecomMethods.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLPSDdecomMethodCallback>& CrpsSLPSDdecomMethodFactory::GetPSDdecomMethodNamesMap()
{
	return mPSDdecomMethods;
}

std::map<const QString, QString> & CrpsSLPSDdecomMethodFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLPSDdecomMethodFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLPSDdecomMethodFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLPSDdecomMethodFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLPSDdecomMethodFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLPSDdecomMethodFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLPSDdecomMethodFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}

///////////////////////////////////////////Correlation/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLCorrelationFactory::CallbackMap CrpsSLCorrelationFactory::mCorrelations;
QString CrpsSLCorrelationFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLCorrelationFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLCorrelationFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLCorrelationFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLCorrelationFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLCorrelationFactory::mTitleMap;
std::map<const QString, QString> CrpsSLCorrelationFactory::mLinkMap;
std::map<const QString, QString> CrpsSLCorrelationFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLCorrelationFactory::mDateMap;
//QString CrpsSLCorrelationFactory::mDescription;

QString CrpsSLCorrelationFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLCorrelationFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLCorrelationFactory::InitializeCorrelation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLCorrelationFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLCorrelationFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLCorrelationFactory::RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateSLCorrelationCallback cb)
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

void CrpsSLCorrelationFactory::UnregisterCorrelation(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mCorrelations.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLCorrelation *CrpsSLCorrelationFactory::BuildCorrelation(const QString &name)
{
	CallbackMap::iterator it = mCorrelations.find(name);
	if (it != mCorrelations.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLCorrelationCallback>& CrpsSLCorrelationFactory::GetCorrelationNamesMap()
{
	return mCorrelations;
}

std::map<const QString, QString> & CrpsSLCorrelationFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLCorrelationFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLCorrelationFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLCorrelationFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLCorrelationFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLCorrelationFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLCorrelationFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLCorrelationFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}

///////////////////////////////////////////Modulation/////////////////////////////////////////////////

//// instantiate the static variable
CrpsSLModulationFactory::CallbackMap CrpsSLModulationFactory::mModulations;
QString CrpsSLModulationFactory::mOwnerPlugin;
std::map<const QString, QString> CrpsSLModulationFactory::mTobeInstalledObjectsMap;
std::map<const QString, QString> CrpsSLModulationFactory::mOjectDescriptionMap;
std::map<const QString, QString> CrpsSLModulationFactory::mOjectAndPluginMap;
std::map<const QString, QString> CrpsSLModulationFactory::mOjectsSkipDuringUnintallationMap;

std::map<const QString, QString> CrpsSLModulationFactory::mTitleMap;
std::map<const QString, QString> CrpsSLModulationFactory::mLinkMap;
std::map<const QString, QString> CrpsSLModulationFactory::mAuthorMap;
std::map<const QString, QString> CrpsSLModulationFactory::mDateMap;
//QString CrpsSLModulationFactory::mDescription;

QString CrpsSLModulationFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSLModulationFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSLModulationFactory::InitializeModulation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate)
{
	mTobeInstalledObjectsMap[name] = description;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
}

/*QString CrpsSLModulationFactory::GetDescription()
{
	return mDescription;
}
void CrpsSLModulationFactory::SetDescription(QString description)
{
	mDescription = description;
}*/

void CrpsSLModulationFactory::RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateSLModulationCallback cb)
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

void CrpsSLModulationFactory::UnregisterModulation(const QString &name, const QString &pluginName)
{
	if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mModulations.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);

	}

}

IrpsSLModulation *CrpsSLModulationFactory::BuildModulation(const QString &name)
{
	CallbackMap::iterator it = mModulations.find(name);
	if (it != mModulations.end())
	{
		// call the creation callback to construct this derived name
		return (it->second)();
	}

	return NULL;
}

std::map<const QString, CreateSLModulationCallback>& CrpsSLModulationFactory::GetModulationNamesMap()
{
	return mModulations;
}

std::map<const QString, QString> & CrpsSLModulationFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const QString, QString>& CrpsSLModulationFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const QString, QString>& CrpsSLModulationFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

////

std::map<const QString, QString>& CrpsSLModulationFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const QString, QString>& CrpsSLModulationFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const QString, QString>& CrpsSLModulationFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const QString, QString>& CrpsSLModulationFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const QString, QString> &  CrpsSLModulationFactory::GetOjectsSkipDuringUnintallationMap()
{
	return mOjectsSkipDuringUnintallationMap;
}