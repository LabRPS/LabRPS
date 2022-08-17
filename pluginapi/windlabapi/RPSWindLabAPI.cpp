// RPScoreAPI.cpp : Defines the initialization routines for the DLL.
//


#include "RPSWindLabAPI.h"
#include <iostream>


typedef IrpsWLLocationDistribution *(*CreateLocDistrCallback)();
typedef IrpsWLMean *(*CreateMeanCallback)();
typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();
typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();
typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();
typedef IrpsWLCoherence *(*CreateCoherenceCallback)();
typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();
typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
typedef IrpsWLRandomness *(*CreateRandomnessCallback)();
typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();
typedef IrpsWLModulation *(*CreateModulationCallback)();

const char * RPSWindLabAPIInfo::getWindLabAPIVersion()
{
	return "0.001";
}

	///////Coherence////////
	//// instantiate the static variable
	CrpsCoherenceFactory::CallbackMap CrpsCoherenceFactory::mCoherences;
	std::vector<QString> CrpsCoherenceFactory::mCoherenceNames;
	QString CrpsCoherenceFactory::mOwnerPlugin;
	//QString CrpsCoherenceFactory::mDescription;
	std::map<const QString, QString> CrpsCoherenceFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsCoherenceFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsCoherenceFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsCoherenceFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsCoherenceFactory::mTitleMap;
	std::map<const QString, QString> CrpsCoherenceFactory::mLinkMap;
	std::map<const QString, QString> CrpsCoherenceFactory::mAuthorMap;
	std::map<const QString, QString> CrpsCoherenceFactory::mDateMap;
	std::map<const QString, QString> CrpsCoherenceFactory::mVersionMap;

	QString CrpsCoherenceFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsCoherenceFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}
	
	void CrpsCoherenceFactory::InitializeCoherence(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{		
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsCoherenceFactory::RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateCoherenceCallback cb)
	{
		if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
		{
			return;
		}
		mCoherences[name] = cb;
		mOjectDescriptionMap[name] = description;
		mOjectAndPluginMap[name] = pluginName;
		SetOwnerPlugin(pluginName);
	}

	void CrpsCoherenceFactory::UnregisterCoherence(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mCoherences.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}

	}

	IrpsWLCoherence *CrpsCoherenceFactory::BuildCoherence(const QString &name)
	{
		CallbackMap::iterator it = mCoherences.find(name);
		if (it != mCoherences.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateCoherenceCallback>& CrpsCoherenceFactory::GetCoherenceNamesMap()
	{
		return mCoherences;
	}

	std::vector<QString> CrpsCoherenceFactory::GetNameVector()
	{
		return mCoherenceNames;
	}

	std::map<const QString, QString> & CrpsCoherenceFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsCoherenceFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsCoherenceFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsCoherenceFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsCoherenceFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsCoherenceFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsCoherenceFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsCoherenceFactory::GetVersionMap()
	{
		return mVersionMap;
	}


    std::map<const QString, QString> &  CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Location distribution/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsLocationDistributionFactory::CallbackMap CrpsLocationDistributionFactory::mLocationDistributions;
	std::map<const QString, QString> CrpsLocationDistributionFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsLocationDistributionFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsLocationDistributionFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsLocationDistributionFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsLocationDistributionFactory::mTitleMap;
	std::map<const QString, QString> CrpsLocationDistributionFactory::mLinkMap;
	std::map<const QString, QString> CrpsLocationDistributionFactory::mAuthorMap;
	std::map<const QString, QString> CrpsLocationDistributionFactory::mDateMap;
	std::map<const QString, QString> CrpsLocationDistributionFactory::mVersionMap;

	QString CrpsLocationDistributionFactory::mOwnerPlugin;

	QString CrpsLocationDistributionFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsLocationDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsLocationDistributionFactory::InitializeLocationDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsLocationDistributionFactory::RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateLocDistrCallback cb)
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

	void CrpsLocationDistributionFactory::UnregisterLocationDistribution(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mLocationDistributions.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}		
	}

	IrpsWLLocationDistribution *CrpsLocationDistributionFactory::BuildLocationDistribution(const QString &name)
	{
		CallbackMap::iterator it = mLocationDistributions.find(name);
		if (it != mLocationDistributions.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}


	std::map<const QString, CreateLocDistrCallback>& CrpsLocationDistributionFactory::GetLocDistrNamesMap()
	{
		return mLocationDistributions;
	}

	std::map<const QString, QString> & CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Mean ///////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsMeanFactory::CallbackMap CrpsMeanFactory::mMeans;
	QString CrpsMeanFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsMeanFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsMeanFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsMeanFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsMeanFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsMeanFactory::mTitleMap;
	std::map<const QString, QString> CrpsMeanFactory::mLinkMap;
	std::map<const QString, QString> CrpsMeanFactory::mAuthorMap;
	std::map<const QString, QString> CrpsMeanFactory::mDateMap;
	std::map<const QString, QString> CrpsMeanFactory::mVersionMap;

	QString CrpsMeanFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsMeanFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsMeanFactory::InitializeMean(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;
	}

	void CrpsMeanFactory::RegisterMean(const QString &name, const QString &pluginName, const QString &description, CreateMeanCallback cb)
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

	void CrpsMeanFactory::UnregisterMean(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mMeans.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}


	}

	IrpsWLMean *CrpsMeanFactory::BuildMean(const QString &name)
	{
		CallbackMap::iterator it = mMeans.find(name);
		if (it != mMeans.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateMeanCallback>& CrpsMeanFactory::GetMeanNamesMap()
	{
		return mMeans;
	}

	std::map<const QString, QString> & CrpsMeanFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsMeanFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}
	std::map<const QString, QString>& CrpsMeanFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsMeanFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsMeanFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsMeanFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsMeanFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsMeanFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }	

	///////////////////////////////////////////Along wind target spectrum/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsXSpectrumFactory::CallbackMap CrpsXSpectrumFactory::mXSpectrums;
	QString CrpsXSpectrumFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsXSpectrumFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsXSpectrumFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsXSpectrumFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsXSpectrumFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsXSpectrumFactory::mTitleMap;
	std::map<const QString, QString> CrpsXSpectrumFactory::mLinkMap;
	std::map<const QString, QString> CrpsXSpectrumFactory::mAuthorMap;
	std::map<const QString, QString> CrpsXSpectrumFactory::mDateMap;
	std::map<const QString, QString> CrpsXSpectrumFactory::mVersionMap;

	//QString CrpsXSpectrumFactory::mDescription;

	QString CrpsXSpectrumFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsXSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsXSpectrumFactory::InitializeXSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsXSpectrumFactory::RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateXSpectrumCallback cb)
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

	void CrpsXSpectrumFactory::UnregisterXSpectrum(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mXSpectrums.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLXSpectrum *CrpsXSpectrumFactory::BuildXSpectrum(const QString &name)
	{
		CallbackMap::iterator it = mXSpectrums.find(name);
		if (it != mXSpectrums.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateXSpectrumCallback>& CrpsXSpectrumFactory::GetXSpectrumNamesMap()
	{
		return mXSpectrums;
	}

	std::map<const QString, QString> & CrpsXSpectrumFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsXSpectrumFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsXSpectrumFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsXSpectrumFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsXSpectrumFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsXSpectrumFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsXSpectrumFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsXSpectrumFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Vertical wind target spectrum/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsZSpectrumFactory::CallbackMap CrpsZSpectrumFactory::mZSpectrums;
	QString CrpsZSpectrumFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsZSpectrumFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsZSpectrumFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsZSpectrumFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsZSpectrumFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsZSpectrumFactory::mTitleMap;
	std::map<const QString, QString> CrpsZSpectrumFactory::mLinkMap;
	std::map<const QString, QString> CrpsZSpectrumFactory::mAuthorMap;
	std::map<const QString, QString> CrpsZSpectrumFactory::mDateMap;
	std::map<const QString, QString> CrpsZSpectrumFactory::mVersionMap;

	//QString CrpsZSpectrumFactory::mDescription;

	QString CrpsZSpectrumFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsZSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsZSpectrumFactory::InitializeZSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsZSpectrumFactory::RegisterZSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateZSpectrumCallback cb)
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

	void CrpsZSpectrumFactory::UnregisterZSpectrum(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mZSpectrums.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLZSpectrum *CrpsZSpectrumFactory::BuildZSpectrum(const QString &name)
	{
		CallbackMap::iterator it = mZSpectrums.find(name);
		if (it != mZSpectrums.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateZSpectrumCallback>& CrpsZSpectrumFactory::GetZSpectrumNamesMap()
	{
		return mZSpectrums;
	}

	std::map<const QString, QString> & CrpsZSpectrumFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsZSpectrumFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsZSpectrumFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsZSpectrumFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsZSpectrumFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsZSpectrumFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsZSpectrumFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsZSpectrumFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Across wind target spectrum/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsYSpectrumFactory::CallbackMap CrpsYSpectrumFactory::mYSpectrums;
	QString CrpsYSpectrumFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsYSpectrumFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsYSpectrumFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsYSpectrumFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsYSpectrumFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsYSpectrumFactory::mTitleMap;
	std::map<const QString, QString> CrpsYSpectrumFactory::mLinkMap;
	std::map<const QString, QString> CrpsYSpectrumFactory::mAuthorMap;
	std::map<const QString, QString> CrpsYSpectrumFactory::mDateMap;
	std::map<const QString, QString> CrpsYSpectrumFactory::mVersionMap;

	//QString CrpsYSpectrumFactory::mDescription;

	QString CrpsYSpectrumFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsYSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsYSpectrumFactory::InitializeYSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsYSpectrumFactory::RegisterYSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateYSpectrumCallback cb)
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

	void CrpsYSpectrumFactory::UnregisterYSpectrum(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mYSpectrums.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLYSpectrum *CrpsYSpectrumFactory::BuildYSpectrum(const QString &name)
	{
		CallbackMap::iterator it = mYSpectrums.find(name);
		if (it != mYSpectrums.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateYSpectrumCallback>& CrpsYSpectrumFactory::GetYSpectrumNamesMap()
	{
		return mYSpectrums;
	}

	std::map<const QString, QString> & CrpsYSpectrumFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsYSpectrumFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsYSpectrumFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsYSpectrumFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsYSpectrumFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsYSpectrumFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsYSpectrumFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsYSpectrumFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Wind Coherence/////////////////////////////////////////////////

	
	///////////////////////////////////////////Simulation method/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsSimuMethodFactory::CallbackMap CrpsSimuMethodFactory::mSimuMethods;
	QString CrpsSimuMethodFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsSimuMethodFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsSimuMethodFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsSimuMethodFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsSimuMethodFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsSimuMethodFactory::mTitleMap;
	std::map<const QString, QString> CrpsSimuMethodFactory::mLinkMap;
	std::map<const QString, QString> CrpsSimuMethodFactory::mAuthorMap;
	std::map<const QString, QString> CrpsSimuMethodFactory::mDateMap;
	std::map<const QString, QString> CrpsSimuMethodFactory::mVersionMap;

	//QString CrpsSimuMethodFactory::mDescription;

	QString CrpsSimuMethodFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsSimuMethodFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsSimuMethodFactory::InitializeSimuMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsSimuMethodFactory::RegisterSimuMethod(const QString &name, const QString &pluginName, const QString &description, CreateSimuMethodCallback cb)
	{
		if ((!mOwnerPlugin.isEmpty()) & (mOwnerPlugin != pluginName))
		{
			return;
		}

		mSimuMethods[name] = cb;
		mOjectDescriptionMap[name] = description;
		mOjectAndPluginMap[name] = pluginName;

		SetOwnerPlugin(pluginName);
		//SetDescription(description);

	}

	void CrpsSimuMethodFactory::UnregisterSimuMethod(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mSimuMethods.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLSimuMethod *CrpsSimuMethodFactory::BuildSimuMethod(const QString &name)
	{
		CallbackMap::iterator it = mSimuMethods.find(name);
		if (it != mSimuMethods.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateSimuMethodCallback>& CrpsSimuMethodFactory::GetSimuMethodNamesMap()
	{
		return mSimuMethods;
	}

	std::map<const QString, QString> & CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsSimuMethodFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsSimuMethodFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsSimuMethodFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsSimuMethodFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsSimuMethodFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsSimuMethodFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsSimuMethodFactory::GetVersionMap()
	{
		return mVersionMap;
	}


	std::map<const QString, QString> &  CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Frequency distribution/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsFrequencyDistributionFactory::CallbackMap CrpsFrequencyDistributionFactory::mFrequencyDistributions;
	QString CrpsFrequencyDistributionFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsFrequencyDistributionFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mTitleMap;
	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mLinkMap;
	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mAuthorMap;
	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mDateMap;
	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mVersionMap;

	//QString CrpsFrequencyDistributionFactory::mDescription;

	QString CrpsFrequencyDistributionFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsFrequencyDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsFrequencyDistributionFactory::InitializeFrequencyDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsFrequencyDistributionFactory::RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateFrequencyDistributionCallback cb)
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

	void CrpsFrequencyDistributionFactory::UnregisterFrequencyDistribution(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mFrequencyDistributions.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLFrequencyDistribution *CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(const QString &name)
	{
		CallbackMap::iterator it = mFrequencyDistributions.find(name);
		if (it != mFrequencyDistributions.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateFrequencyDistributionCallback>& CrpsFrequencyDistributionFactory::GetFrequencyDistributionNamesMap()
	{
		return mFrequencyDistributions;
	}

	std::map<const QString, QString> & CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetVersionMap()
	{
		return mVersionMap;
	}
	
	std::map<const QString, QString> &  CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }

	///////////////////////////////////////////Randomness/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsRandomnessFactory::CallbackMap CrpsRandomnessFactory::mRandomness;
	QString CrpsRandomnessFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsRandomnessFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsRandomnessFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsRandomnessFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsRandomnessFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsRandomnessFactory::mTitleMap;
	std::map<const QString, QString> CrpsRandomnessFactory::mLinkMap;
	std::map<const QString, QString> CrpsRandomnessFactory::mAuthorMap;
	std::map<const QString, QString> CrpsRandomnessFactory::mDateMap;
	std::map<const QString, QString> CrpsRandomnessFactory::mVersionMap;

	QString CrpsRandomnessFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsRandomnessFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsRandomnessFactory::InitializeRandomness(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsRandomnessFactory::RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateRandomnessCallback cb)
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

	void CrpsRandomnessFactory::UnregisterRandomness(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mRandomness.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLRandomness *CrpsRandomnessFactory::BuildRandomness(const QString &name)
	{
		CallbackMap::iterator it = mRandomness.find(name);
		if (it != mRandomness.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateRandomnessCallback>& CrpsRandomnessFactory::GetRandomnessNamesMap()
	{
		return mRandomness;
	}

	std::map<const QString, QString> & CrpsRandomnessFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsRandomnessFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsRandomnessFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsRandomnessFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsRandomnessFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsRandomnessFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsRandomnessFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsRandomnessFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }

	///////////////////////////////////////////psd decomposition/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsPSDdecomMethodFactory::CallbackMap CrpsPSDdecomMethodFactory::mPSDdecomMethods;
	QString CrpsPSDdecomMethodFactory::mOwnerPlugin;
	//QString CrpsPSDdecomMethodFactory::mDescription;
	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsPSDdecomMethodFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mTitleMap;
	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mLinkMap;
	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mAuthorMap;
	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mDateMap;
	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mVersionMap;

	QString CrpsPSDdecomMethodFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsPSDdecomMethodFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsPSDdecomMethodFactory::InitializePSDdecomMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsPSDdecomMethodFactory::RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreatePSDdecomMethodCallback cb)
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

	void CrpsPSDdecomMethodFactory::UnregisterPSDdecomMethod(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mPSDdecomMethods.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}

		
	}

	IrpsWLPSDdecompositionMethod *CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(const QString &name)
	{
		CallbackMap::iterator it = mPSDdecomMethods.find(name);
		if (it != mPSDdecomMethods.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreatePSDdecomMethodCallback>& CrpsPSDdecomMethodFactory::GetPSDdecomMethodNamesMap()
	{
		return mPSDdecomMethods;
	}

	std::map<const QString, QString> & CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Correlation/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsCorrelationFactory::CallbackMap CrpsCorrelationFactory::mCorrelations;
	QString CrpsCorrelationFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsCorrelationFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsCorrelationFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsCorrelationFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsCorrelationFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsCorrelationFactory::mTitleMap;
	std::map<const QString, QString> CrpsCorrelationFactory::mLinkMap;
	std::map<const QString, QString> CrpsCorrelationFactory::mAuthorMap;
	std::map<const QString, QString> CrpsCorrelationFactory::mDateMap;
	std::map<const QString, QString> CrpsCorrelationFactory::mVersionMap;

	QString CrpsCorrelationFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsCorrelationFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsCorrelationFactory::InitializeCorrelation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsCorrelationFactory::RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateCorrelationCallback cb)
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

	void CrpsCorrelationFactory::UnregisterCorrelation(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mCorrelations.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLCorrelation *CrpsCorrelationFactory::BuildCorrelation(const QString &name)
	{
		CallbackMap::iterator it = mCorrelations.find(name);
		if (it != mCorrelations.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateCorrelationCallback>& CrpsCorrelationFactory::GetCorrelationNamesMap()
	{
		return mCorrelations;
	}

	std::map<const QString, QString> & CrpsCorrelationFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsCorrelationFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsCorrelationFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsCorrelationFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsCorrelationFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsCorrelationFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsCorrelationFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsCorrelationFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsCorrelationFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	///////////////////////////////////////////Modulation/////////////////////////////////////////////////

	//// instantiate the static variable
	CrpsModulationFactory::CallbackMap CrpsModulationFactory::mModulations;
	QString CrpsModulationFactory::mOwnerPlugin;
	std::map<const QString, QString> CrpsModulationFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsModulationFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsModulationFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsModulationFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsModulationFactory::mTitleMap;
	std::map<const QString, QString> CrpsModulationFactory::mLinkMap;
	std::map<const QString, QString> CrpsModulationFactory::mAuthorMap;
	std::map<const QString, QString> CrpsModulationFactory::mDateMap;
	std::map<const QString, QString> CrpsModulationFactory::mVersionMap;

	QString CrpsModulationFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsModulationFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}

	void CrpsModulationFactory::InitializeModulation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{
		mTobeInstalledObjectsMap[name] = description;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

	void CrpsModulationFactory::RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateModulationCallback cb)
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

	void CrpsModulationFactory::UnregisterModulation(const QString &name, const QString &pluginName)
	{
		if (pluginName == GetOwnerPlugin() && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
		{
			mModulations.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}
		
	}

	IrpsWLModulation *CrpsModulationFactory::BuildModulation(const QString &name)
	{
		CallbackMap::iterator it = mModulations.find(name);
		if (it != mModulations.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateModulationCallback>& CrpsModulationFactory::GetModulationNamesMap()
	{
		return mModulations;
	}

	std::map<const QString, QString> & CrpsModulationFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsModulationFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsModulationFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsModulationFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsModulationFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsModulationFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsModulationFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsModulationFactory::GetVersionMap()
	{
		return mVersionMap;
	}

	std::map<const QString, QString> &  CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }