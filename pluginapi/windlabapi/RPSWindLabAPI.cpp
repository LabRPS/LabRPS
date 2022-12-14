// RPScoreAPI.cpp : Defines the initialization routines for the DLL.
//

#include "RPSWindLabAPI.h"
#include <iostream>


// typedef IrpsWLLocationDistribution *(*CreateLocDistrCallback)();
// typedef IrpsWLMean *(*CreateMeanCallback)();
// typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();
// typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();
// typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();
// typedef IrpsWLCoherence *(*CreateCoherenceCallback)();
// typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();
// typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
// typedef IrpsWLRandomness *(*CreateRandomnessCallback)();
// typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
// typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();
// typedef IrpsWLModulation *(*CreateModulationCallback)();
// typedef IrpsWLTableTool *(*CreateTableToolCallback)();
// typedef IrpsWLMatrixTool *(*CreateMatrixToolCallback)();
// typedef IrpsWLUserDefinedRPSObject *(*CreateUserDefinedRPSObjectCallback)();

// typedef IrpsWLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();
// typedef IrpsWLGustFactor *(*CreateGustFactorCallback)();
// typedef IrpsWLKurtosis *(*CreateKurtosisCallback)();
// typedef IrpsWLPeakFactor *(*CreatePeakFactorCallback)();
// typedef IrpsWLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();
// typedef IrpsWLRoughness *(*CreateRoughnessCallback)();
// typedef IrpsWLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();
// typedef IrpsWLSkewness *(*CreateSkewnessCallback)();
// typedef IrpsWLStandardDeviation *(*CreateStandardDeviationCallback)();
// typedef IrpsWLTurbulenceIntensity *(*CreateTurbulenceIntensityCallback)();
// typedef IrpsWLTurbulenceScale *(*CreateTurbulenceScaleCallback)();
// typedef IrpsWLVariance *(*CreateVarianceCallback)();
//typedef IrpsWLWavePassageEffect *(*CreateWavePassageEffectCallback)();


const char * RPSWindLabAPIInfo::getWindLabAPIVersion()
{
	return "0.001";
}

// 	///////Coherence////////
// 	//// instantiate the static variable
// 	CrpsCoherenceFactory::CallbackMap CrpsCoherenceFactory::mCoherences;
// 	std::vector<QString> CrpsCoherenceFactory::mCoherenceNames;
// 	QString CrpsCoherenceFactory::mOwnerPlugin;
// 	//QString CrpsCoherenceFactory::mDescription;
// 	std::map<const QString, QString> CrpsCoherenceFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsCoherenceFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsCoherenceFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsCoherenceFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsCoherenceFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsCoherenceFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsCoherenceFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsCoherenceFactory::mDateMap;
// 	std::map<const QString, QString> CrpsCoherenceFactory::mVersionMap;

// 	QString CrpsCoherenceFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsCoherenceFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
//     void CrpsCoherenceFactory::InitializeCoherence(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
//         mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 

// 	}

// 	void CrpsCoherenceFactory::RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateCoherenceCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mCoherences[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsCoherenceFactory::UnregisterCoherence(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mCoherences.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLCoherence *CrpsCoherenceFactory::BuildCoherence(const QString &name)
// 	{
// 		CallbackMap::iterator it = mCoherences.find(name);
// 		if (it != mCoherences.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateCoherenceCallback>& CrpsCoherenceFactory::GetCoherenceNamesMap()
// 	{
// 		return mCoherences;
// 	}

// 	std::vector<QString> CrpsCoherenceFactory::GetNameVector()
// 	{
// 		return mCoherenceNames;
// 	}

// 	std::map<const QString, QString> & CrpsCoherenceFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsCoherenceFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsCoherenceFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsCoherenceFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsCoherenceFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsCoherenceFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsCoherenceFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsCoherenceFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}


//     std::map<const QString, QString> &  CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Location distribution/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsLocationDistributionFactory::CallbackMap CrpsLocationDistributionFactory::mLocationDistributions;
// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsLocationDistributionFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mDateMap;
// 	std::map<const QString, QString> CrpsLocationDistributionFactory::mVersionMap;

// 	QString CrpsLocationDistributionFactory::mOwnerPlugin;

// 	QString CrpsLocationDistributionFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsLocationDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsLocationDistributionFactory::InitializeLocationDistribution(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsLocationDistributionFactory::RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateLocDistrCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mLocationDistributions[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsLocationDistributionFactory::UnregisterLocationDistribution(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mLocationDistributions.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}		
// 	}

// 	IrpsWLLocationDistribution *CrpsLocationDistributionFactory::BuildLocationDistribution(const QString &name)
// 	{
// 		CallbackMap::iterator it = mLocationDistributions.find(name);
// 		if (it != mLocationDistributions.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}


// 	std::map<const QString, CreateLocDistrCallback>& CrpsLocationDistributionFactory::GetLocDistrNamesMap()
// 	{
// 		return mLocationDistributions;
// 	}

// 	std::map<const QString, QString> & CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsLocationDistributionFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Mean ///////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsMeanFactory::CallbackMap CrpsMeanFactory::mMeans;
// 	QString CrpsMeanFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsMeanFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsMeanFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsMeanFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsMeanFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsMeanFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsMeanFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsMeanFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsMeanFactory::mDateMap;
// 	std::map<const QString, QString> CrpsMeanFactory::mVersionMap;

// 	QString CrpsMeanFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsMeanFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsMeanFactory::InitializeMean(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 

// 	}

// 	void CrpsMeanFactory::RegisterMean(const QString &name, const QString &pluginName, const QString &description, CreateMeanCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mMeans[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);
// 	}

// 	void CrpsMeanFactory::UnregisterMean(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mMeans.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}


// 	}

// 	IrpsWLMean *CrpsMeanFactory::BuildMean(const QString &name)
// 	{
// 		CallbackMap::iterator it = mMeans.find(name);
// 		if (it != mMeans.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateMeanCallback>& CrpsMeanFactory::GetMeanNamesMap()
// 	{
// 		return mMeans;
// 	}

// 	std::map<const QString, QString> & CrpsMeanFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsMeanFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}
// 	std::map<const QString, QString>& CrpsMeanFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsMeanFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsMeanFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsMeanFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsMeanFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsMeanFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }	

// 	///////////////////////////////////////////Along wind target spectrum/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsXSpectrumFactory::CallbackMap CrpsXSpectrumFactory::mXSpectrums;
// 	QString CrpsXSpectrumFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsXSpectrumFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsXSpectrumFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsXSpectrumFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsXSpectrumFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsXSpectrumFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsXSpectrumFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsXSpectrumFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsXSpectrumFactory::mDateMap;
// 	std::map<const QString, QString> CrpsXSpectrumFactory::mVersionMap;

// 	//QString CrpsXSpectrumFactory::mDescription;

// 	QString CrpsXSpectrumFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsXSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsXSpectrumFactory::InitializeXSpectrum(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsXSpectrumFactory::RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateXSpectrumCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mXSpectrums[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsXSpectrumFactory::UnregisterXSpectrum(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mXSpectrums.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLXSpectrum *CrpsXSpectrumFactory::BuildXSpectrum(const QString &name)
// 	{
// 		CallbackMap::iterator it = mXSpectrums.find(name);
// 		if (it != mXSpectrums.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateXSpectrumCallback>& CrpsXSpectrumFactory::GetXSpectrumNamesMap()
// 	{
// 		return mXSpectrums;
// 	}

// 	std::map<const QString, QString> & CrpsXSpectrumFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsXSpectrumFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsXSpectrumFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsXSpectrumFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsXSpectrumFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsXSpectrumFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsXSpectrumFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsXSpectrumFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Vertical wind target spectrum/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsZSpectrumFactory::CallbackMap CrpsZSpectrumFactory::mZSpectrums;
// 	QString CrpsZSpectrumFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsZSpectrumFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsZSpectrumFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsZSpectrumFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsZSpectrumFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsZSpectrumFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsZSpectrumFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsZSpectrumFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsZSpectrumFactory::mDateMap;
// 	std::map<const QString, QString> CrpsZSpectrumFactory::mVersionMap;

// 	//QString CrpsZSpectrumFactory::mDescription;

// 	QString CrpsZSpectrumFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsZSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsZSpectrumFactory::InitializeZSpectrum(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsZSpectrumFactory::RegisterZSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateZSpectrumCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mZSpectrums[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsZSpectrumFactory::UnregisterZSpectrum(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mZSpectrums.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLZSpectrum *CrpsZSpectrumFactory::BuildZSpectrum(const QString &name)
// 	{
// 		CallbackMap::iterator it = mZSpectrums.find(name);
// 		if (it != mZSpectrums.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateZSpectrumCallback>& CrpsZSpectrumFactory::GetZSpectrumNamesMap()
// 	{
// 		return mZSpectrums;
// 	}

// 	std::map<const QString, QString> & CrpsZSpectrumFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsZSpectrumFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsZSpectrumFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsZSpectrumFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsZSpectrumFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsZSpectrumFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsZSpectrumFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsZSpectrumFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Across wind target spectrum/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsYSpectrumFactory::CallbackMap CrpsYSpectrumFactory::mYSpectrums;
// 	QString CrpsYSpectrumFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsYSpectrumFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsYSpectrumFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsYSpectrumFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsYSpectrumFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsYSpectrumFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsYSpectrumFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsYSpectrumFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsYSpectrumFactory::mDateMap;
// 	std::map<const QString, QString> CrpsYSpectrumFactory::mVersionMap;

// 	//QString CrpsYSpectrumFactory::mDescription;

// 	QString CrpsYSpectrumFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsYSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsYSpectrumFactory::InitializeYSpectrum(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsYSpectrumFactory::RegisterYSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateYSpectrumCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mYSpectrums[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsYSpectrumFactory::UnregisterYSpectrum(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mYSpectrums.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLYSpectrum *CrpsYSpectrumFactory::BuildYSpectrum(const QString &name)
// 	{
// 		CallbackMap::iterator it = mYSpectrums.find(name);
// 		if (it != mYSpectrums.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateYSpectrumCallback>& CrpsYSpectrumFactory::GetYSpectrumNamesMap()
// 	{
// 		return mYSpectrums;
// 	}

// 	std::map<const QString, QString> & CrpsYSpectrumFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsYSpectrumFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsYSpectrumFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsYSpectrumFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsYSpectrumFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsYSpectrumFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsYSpectrumFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsYSpectrumFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Wind Coherence/////////////////////////////////////////////////

	
// 	///////////////////////////////////////////Simulation method/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsSimuMethodFactory::CallbackMap CrpsSimuMethodFactory::mSimuMethods;
// 	QString CrpsSimuMethodFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsSimuMethodFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsSimuMethodFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsSimuMethodFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsSimuMethodFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsSimuMethodFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsSimuMethodFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsSimuMethodFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsSimuMethodFactory::mDateMap;
// 	std::map<const QString, QString> CrpsSimuMethodFactory::mVersionMap;

// 	//QString CrpsSimuMethodFactory::mDescription;

// 	QString CrpsSimuMethodFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsSimuMethodFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsSimuMethodFactory::InitializeSimuMethod(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsSimuMethodFactory::RegisterSimuMethod(const QString &name, const QString &pluginName, const QString &description, CreateSimuMethodCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mSimuMethods[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsSimuMethodFactory::UnregisterSimuMethod(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mSimuMethods.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLSimuMethod *CrpsSimuMethodFactory::BuildSimuMethod(const QString &name)
// 	{
// 		CallbackMap::iterator it = mSimuMethods.find(name);
// 		if (it != mSimuMethods.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateSimuMethodCallback>& CrpsSimuMethodFactory::GetSimuMethodNamesMap()
// 	{
// 		return mSimuMethods;
// 	}

// 	std::map<const QString, QString> & CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsSimuMethodFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsSimuMethodFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsSimuMethodFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsSimuMethodFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsSimuMethodFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsSimuMethodFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsSimuMethodFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}


// 	std::map<const QString, QString> &  CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Frequency distribution/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsFrequencyDistributionFactory::CallbackMap CrpsFrequencyDistributionFactory::mFrequencyDistributions;
// 	QString CrpsFrequencyDistributionFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsFrequencyDistributionFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mDateMap;
// 	std::map<const QString, QString> CrpsFrequencyDistributionFactory::mVersionMap;

// 	//QString CrpsFrequencyDistributionFactory::mDescription;

// 	QString CrpsFrequencyDistributionFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsFrequencyDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsFrequencyDistributionFactory::InitializeFrequencyDistribution(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsFrequencyDistributionFactory::RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateFrequencyDistributionCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mFrequencyDistributions[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsFrequencyDistributionFactory::UnregisterFrequencyDistribution(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mFrequencyDistributions.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLFrequencyDistribution *CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(const QString &name)
// 	{
// 		CallbackMap::iterator it = mFrequencyDistributions.find(name);
// 		if (it != mFrequencyDistributions.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateFrequencyDistributionCallback>& CrpsFrequencyDistributionFactory::GetFrequencyDistributionNamesMap()
// 	{
// 		return mFrequencyDistributions;
// 	}

// 	std::map<const QString, QString> & CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsFrequencyDistributionFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}
	
// 	std::map<const QString, QString> &  CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

// 	///////////////////////////////////////////Randomness/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsRandomnessFactory::CallbackMap CrpsRandomnessFactory::mRandomness;
// 	QString CrpsRandomnessFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsRandomnessFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsRandomnessFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsRandomnessFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsRandomnessFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsRandomnessFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsRandomnessFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsRandomnessFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsRandomnessFactory::mDateMap;
// 	std::map<const QString, QString> CrpsRandomnessFactory::mVersionMap;

// 	QString CrpsRandomnessFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsRandomnessFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsRandomnessFactory::InitializeRandomness(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsRandomnessFactory::RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateRandomnessCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mRandomness[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsRandomnessFactory::UnregisterRandomness(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mRandomness.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLRandomness *CrpsRandomnessFactory::BuildRandomness(const QString &name)
// 	{
// 		CallbackMap::iterator it = mRandomness.find(name);
// 		if (it != mRandomness.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateRandomnessCallback>& CrpsRandomnessFactory::GetRandomnessNamesMap()
// 	{
// 		return mRandomness;
// 	}

// 	std::map<const QString, QString> & CrpsRandomnessFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsRandomnessFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsRandomnessFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsRandomnessFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsRandomnessFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsRandomnessFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsRandomnessFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsRandomnessFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

// 	///////////////////////////////////////////psd decomposition/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsPSDdecomMethodFactory::CallbackMap CrpsPSDdecomMethodFactory::mPSDdecomMethods;
// 	QString CrpsPSDdecomMethodFactory::mOwnerPlugin;
// 	//QString CrpsPSDdecomMethodFactory::mDescription;
// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsPSDdecomMethodFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mDateMap;
// 	std::map<const QString, QString> CrpsPSDdecomMethodFactory::mVersionMap;

// 	QString CrpsPSDdecomMethodFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsPSDdecomMethodFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsPSDdecomMethodFactory::InitializePSDdecomMethod(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 

// 	}

// 	void CrpsPSDdecomMethodFactory::RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreatePSDdecomMethodCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mPSDdecomMethods[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsPSDdecomMethodFactory::UnregisterPSDdecomMethod(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mPSDdecomMethods.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

		
// 	}

// 	IrpsWLPSDdecompositionMethod *CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(const QString &name)
// 	{
// 		CallbackMap::iterator it = mPSDdecomMethods.find(name);
// 		if (it != mPSDdecomMethods.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreatePSDdecomMethodCallback>& CrpsPSDdecomMethodFactory::GetPSDdecomMethodNamesMap()
// 	{
// 		return mPSDdecomMethods;
// 	}

// 	std::map<const QString, QString> & CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsPSDdecomMethodFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Correlation/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsCorrelationFactory::CallbackMap CrpsCorrelationFactory::mCorrelations;
// 	QString CrpsCorrelationFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsCorrelationFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsCorrelationFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsCorrelationFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsCorrelationFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsCorrelationFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsCorrelationFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsCorrelationFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsCorrelationFactory::mDateMap;
// 	std::map<const QString, QString> CrpsCorrelationFactory::mVersionMap;

// 	QString CrpsCorrelationFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsCorrelationFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsCorrelationFactory::InitializeCorrelation(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsCorrelationFactory::RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateCorrelationCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mCorrelations[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsCorrelationFactory::UnregisterCorrelation(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mCorrelations.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLCorrelation *CrpsCorrelationFactory::BuildCorrelation(const QString &name)
// 	{
// 		CallbackMap::iterator it = mCorrelations.find(name);
// 		if (it != mCorrelations.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateCorrelationCallback>& CrpsCorrelationFactory::GetCorrelationNamesMap()
// 	{
// 		return mCorrelations;
// 	}

// 	std::map<const QString, QString> & CrpsCorrelationFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsCorrelationFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsCorrelationFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsCorrelationFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsCorrelationFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsCorrelationFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsCorrelationFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsCorrelationFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsCorrelationFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
// 	///////////////////////////////////////////Modulation/////////////////////////////////////////////////

// 	//// instantiate the static variable
// 	CrpsModulationFactory::CallbackMap CrpsModulationFactory::mModulations;
// 	QString CrpsModulationFactory::mOwnerPlugin;
// 	std::map<const QString, QString> CrpsModulationFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsModulationFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsModulationFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsModulationFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsModulationFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsModulationFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsModulationFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsModulationFactory::mDateMap;
// 	std::map<const QString, QString> CrpsModulationFactory::mVersionMap;

// 	QString CrpsModulationFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsModulationFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}

// 	void CrpsModulationFactory::InitializeModulation(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsModulationFactory::RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateModulationCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}

// 		mModulations[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;

		
// 		//SetDescription(description);

// 	}

// 	void CrpsModulationFactory::UnregisterModulation(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mModulations.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}
		
// 	}

// 	IrpsWLModulation *CrpsModulationFactory::BuildModulation(const QString &name)
// 	{
// 		CallbackMap::iterator it = mModulations.find(name);
// 		if (it != mModulations.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

// 	std::map<const QString, CreateModulationCallback>& CrpsModulationFactory::GetModulationNamesMap()
// 	{
// 		return mModulations;
// 	}

// 	std::map<const QString, QString> & CrpsModulationFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsModulationFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsModulationFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsModulationFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsModulationFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsModulationFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsModulationFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsModulationFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

// 	std::map<const QString, QString> &  CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

// 	///////Table tool////////
// 	//// instantiate the static variable
// 	CrpsTableToolFactory::CallbackMap CrpsTableToolFactory::mTableTools;
// 	std::vector<QString> CrpsTableToolFactory::mTableToolNames;
// 	QString CrpsTableToolFactory::mOwnerPlugin;
// 	//QString CrpsTableToolFactory::mDescription;
// 	std::map<const QString, QString> CrpsTableToolFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsTableToolFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsTableToolFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsTableToolFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsTableToolFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsTableToolFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsTableToolFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsTableToolFactory::mDateMap;
// 	std::map<const QString, QString> CrpsTableToolFactory::mVersionMap;

// 	QString CrpsTableToolFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsTableToolFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsTableToolFactory::InitializeTableTool(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsTableToolFactory::RegisterTableTool(const QString &name, const QString &pluginName, const QString &description, CreateTableToolCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mTableTools[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsTableToolFactory::UnregisterTableTool(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mTableTools.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLTableTool *CrpsTableToolFactory::BuildTableTool(const QString &name)
// 	{
// 		CallbackMap::iterator it = mTableTools.find(name);
// 		if (it != mTableTools.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateTableToolCallback>& CrpsTableToolFactory::GetTableToolNamesMap()
// 	{
// 		return mTableTools;
// 	}

// 	std::vector<QString> CrpsTableToolFactory::GetNameVector()
// 	{
// 		return mTableToolNames;
// 	}

// 	std::map<const QString, QString> & CrpsTableToolFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsTableToolFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsTableToolFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsTableToolFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsTableToolFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsTableToolFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsTableToolFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsTableToolFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}


//     std::map<const QString, QString> &  CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

// 	///////Matrix tool////////
// 	//// instantiate the static variable
// 	CrpsMatrixToolFactory::CallbackMap CrpsMatrixToolFactory::mMatrixTools;
// 	std::vector<QString> CrpsMatrixToolFactory::mMatrixToolNames;
// 	QString CrpsMatrixToolFactory::mOwnerPlugin;
// 	//QString CrpsMatrixToolFactory::mDescription;
// 	std::map<const QString, QString> CrpsMatrixToolFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsMatrixToolFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsMatrixToolFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsMatrixToolFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsMatrixToolFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsMatrixToolFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsMatrixToolFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsMatrixToolFactory::mDateMap;
// 	std::map<const QString, QString> CrpsMatrixToolFactory::mVersionMap;

// 	QString CrpsMatrixToolFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsMatrixToolFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsMatrixToolFactory::InitializeMatrixTool(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsMatrixToolFactory::RegisterMatrixTool(const QString &name, const QString &pluginName, const QString &description, CreateMatrixToolCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mMatrixTools[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsMatrixToolFactory::UnregisterMatrixTool(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mMatrixTools.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLMatrixTool *CrpsMatrixToolFactory::BuildMatrixTool(const QString &name)
// 	{
// 		CallbackMap::iterator it = mMatrixTools.find(name);
// 		if (it != mMatrixTools.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateMatrixToolCallback>& CrpsMatrixToolFactory::GetMatrixToolNamesMap()
// 	{
// 		return mMatrixTools;
// 	}

// 	std::vector<QString> CrpsMatrixToolFactory::GetNameVector()
// 	{
// 		return mMatrixToolNames;
// 	}

// 	std::map<const QString, QString> & CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsMatrixToolFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsMatrixToolFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsMatrixToolFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsMatrixToolFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsMatrixToolFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsMatrixToolFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsMatrixToolFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}


//     std::map<const QString, QString> &  CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

// 	///////user defined rps objects////////
// 	//// instantiate the static variable
// 	CrpsUserDefinedRPSObjectFactory::CallbackMap CrpsUserDefinedRPSObjectFactory::mUserDefinedRPSObjects;
// 	std::vector<QString> CrpsUserDefinedRPSObjectFactory::mUserDefinedRPSObjectNames;
// 	QString CrpsUserDefinedRPSObjectFactory::mOwnerPlugin;
// 	//QString CrpsUserDefinedRPSObjectFactory::mDescription;
// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mDateMap;
// 	std::map<const QString, QString> CrpsUserDefinedRPSObjectFactory::mVersionMap;

// 	QString CrpsUserDefinedRPSObjectFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsUserDefinedRPSObjectFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsUserDefinedRPSObjectFactory::InitializeUserDefinedRPSObject(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsUserDefinedRPSObjectFactory::RegisterUserDefinedRPSObject(const QString &name, const QString &pluginName, const QString &description, CreateUserDefinedRPSObjectCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mUserDefinedRPSObjects[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsUserDefinedRPSObjectFactory::UnregisterUserDefinedRPSObject(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mUserDefinedRPSObjects.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLUserDefinedRPSObject *CrpsUserDefinedRPSObjectFactory::BuildUserDefinedRPSObject(const QString &name)
// 	{
// 		CallbackMap::iterator it = mUserDefinedRPSObjects.find(name);
// 		if (it != mUserDefinedRPSObjects.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateUserDefinedRPSObjectCallback>& CrpsUserDefinedRPSObjectFactory::GetUserDefinedRPSObjectNamesMap()
// 	{
// 		return mUserDefinedRPSObjects;
// 	}

// 	std::vector<QString> CrpsUserDefinedRPSObjectFactory::GetNameVector()
// 	{
// 		return mUserDefinedRPSObjectNames;
// 	}

// 	std::map<const QString, QString> & CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsUserDefinedRPSObjectFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsUserDefinedRPSObjectFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsUserDefinedRPSObjectFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsUserDefinedRPSObjectFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsUserDefinedRPSObjectFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

// ///////cumulative probability distribution////////
// 	//// instantiate the static variable
// 	CrpsCumulativeProbabilityDistributionFactory::CallbackMap CrpsCumulativeProbabilityDistributionFactory::mCumulativeProbabilityDistributions;
// 	std::vector<QString> CrpsCumulativeProbabilityDistributionFactory::mCumulativeProbabilityDistributionNames;
// 	QString CrpsCumulativeProbabilityDistributionFactory::mOwnerPlugin;
// 	//QString CrpsCumulativeProbabilityDistributionFactory::mDescription;
// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mDateMap;
// 	std::map<const QString, QString> CrpsCumulativeProbabilityDistributionFactory::mVersionMap;

// 	QString CrpsCumulativeProbabilityDistributionFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsCumulativeProbabilityDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsCumulativeProbabilityDistributionFactory::InitializeCumulativeProbabilityDistribution(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsCumulativeProbabilityDistributionFactory::RegisterCumulativeProbabilityDistribution(const QString &name, const QString &pluginName, const QString &description, CreateCumulativeProbabilityDistributionCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mCumulativeProbabilityDistributions[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsCumulativeProbabilityDistributionFactory::UnregisterCumulativeProbabilityDistribution(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mCumulativeProbabilityDistributions.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLCumulativeProbabilityDistribution *CrpsCumulativeProbabilityDistributionFactory::BuildCumulativeProbabilityDistribution(const QString &name)
// 	{
// 		CallbackMap::iterator it = mCumulativeProbabilityDistributions.find(name);
// 		if (it != mCumulativeProbabilityDistributions.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateCumulativeProbabilityDistributionCallback>& CrpsCumulativeProbabilityDistributionFactory::GetCumulativeProbabilityDistributionNamesMap()
// 	{
// 		return mCumulativeProbabilityDistributions;
// 	}

// 	std::vector<QString> CrpsCumulativeProbabilityDistributionFactory::GetNameVector()
// 	{
// 		return mCumulativeProbabilityDistributionNames;
// 	}

// 	std::map<const QString, QString> & CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsCumulativeProbabilityDistributionFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsCumulativeProbabilityDistributionFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

// 	///////Gustor factor////////
// 	//// instantiate the static variable
// 	CrpsGustFactorFactory::CallbackMap CrpsGustFactorFactory::mGustFactors;
// 	std::vector<QString> CrpsGustFactorFactory::mGustFactorNames;
// 	QString CrpsGustFactorFactory::mOwnerPlugin;
// 	//QString CrpsGustFactorFactory::mDescription;
// 	std::map<const QString, QString> CrpsGustFactorFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsGustFactorFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsGustFactorFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsGustFactorFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsGustFactorFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsGustFactorFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsGustFactorFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsGustFactorFactory::mDateMap;
// 	std::map<const QString, QString> CrpsGustFactorFactory::mVersionMap;

// 	QString CrpsGustFactorFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsGustFactorFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsGustFactorFactory::InitializeGustFactor(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsGustFactorFactory::RegisterGustFactor(const QString &name, const QString &pluginName, const QString &description, CreateGustFactorCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mGustFactors[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsGustFactorFactory::UnregisterGustFactor(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mGustFactors.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLGustFactor *CrpsGustFactorFactory::BuildGustFactor(const QString &name)
// 	{
// 		CallbackMap::iterator it = mGustFactors.find(name);
// 		if (it != mGustFactors.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateGustFactorCallback>& CrpsGustFactorFactory::GetGustFactorNamesMap()
// 	{
// 		return mGustFactors;
// 	}

// 	std::vector<QString> CrpsGustFactorFactory::GetNameVector()
// 	{
// 		return mGustFactorNames;
// 	}

// 	std::map<const QString, QString> & CrpsGustFactorFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsGustFactorFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsGustFactorFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsGustFactorFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsGustFactorFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsGustFactorFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsGustFactorFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsGustFactorFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

	
//     ///////kurtosis////////
// 	//// instantiate the static variable
// 	CrpsKurtosisFactory::CallbackMap CrpsKurtosisFactory::mKurtosiss;
// 	std::vector<QString> CrpsKurtosisFactory::mKurtosisNames;
// 	QString CrpsKurtosisFactory::mOwnerPlugin;
// 	//QString CrpsKurtosisFactory::mDescription;
// 	std::map<const QString, QString> CrpsKurtosisFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsKurtosisFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsKurtosisFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsKurtosisFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsKurtosisFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsKurtosisFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsKurtosisFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsKurtosisFactory::mDateMap;
// 	std::map<const QString, QString> CrpsKurtosisFactory::mVersionMap;

// 	QString CrpsKurtosisFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsKurtosisFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsKurtosisFactory::InitializeKurtosis(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsKurtosisFactory::RegisterKurtosis(const QString &name, const QString &pluginName, const QString &description, CreateKurtosisCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mKurtosiss[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsKurtosisFactory::UnregisterKurtosis(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mKurtosiss.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLKurtosis *CrpsKurtosisFactory::BuildKurtosis(const QString &name)
// 	{
// 		CallbackMap::iterator it = mKurtosiss.find(name);
// 		if (it != mKurtosiss.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateKurtosisCallback>& CrpsKurtosisFactory::GetKurtosisNamesMap()
// 	{
// 		return mKurtosiss;
// 	}

// 	std::vector<QString> CrpsKurtosisFactory::GetNameVector()
// 	{
// 		return mKurtosisNames;
// 	}

// 	std::map<const QString, QString> & CrpsKurtosisFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsKurtosisFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsKurtosisFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsKurtosisFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsKurtosisFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsKurtosisFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsKurtosisFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsKurtosisFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
// ///////peak factor////////
// 	//// instantiate the static variable
// 	CrpsPeakFactorFactory::CallbackMap CrpsPeakFactorFactory::mPeakFactors;
// 	std::vector<QString> CrpsPeakFactorFactory::mPeakFactorNames;
// 	QString CrpsPeakFactorFactory::mOwnerPlugin;
// 	//QString CrpsPeakFactorFactory::mDescription;
// 	std::map<const QString, QString> CrpsPeakFactorFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsPeakFactorFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsPeakFactorFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsPeakFactorFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsPeakFactorFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsPeakFactorFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsPeakFactorFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsPeakFactorFactory::mDateMap;
// 	std::map<const QString, QString> CrpsPeakFactorFactory::mVersionMap;

// 	QString CrpsPeakFactorFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsPeakFactorFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsPeakFactorFactory::InitializePeakFactor(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsPeakFactorFactory::RegisterPeakFactor(const QString &name, const QString &pluginName, const QString &description, CreatePeakFactorCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mPeakFactors[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsPeakFactorFactory::UnregisterPeakFactor(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mPeakFactors.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLPeakFactor *CrpsPeakFactorFactory::BuildPeakFactor(const QString &name)
// 	{
// 		CallbackMap::iterator it = mPeakFactors.find(name);
// 		if (it != mPeakFactors.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreatePeakFactorCallback>& CrpsPeakFactorFactory::GetPeakFactorNamesMap()
// 	{
// 		return mPeakFactors;
// 	}

// 	std::vector<QString> CrpsPeakFactorFactory::GetNameVector()
// 	{
// 		return mPeakFactorNames;
// 	}

// 	std::map<const QString, QString> & CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsPeakFactorFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsPeakFactorFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsPeakFactorFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsPeakFactorFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsPeakFactorFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsPeakFactorFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsPeakFactorFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
// ///////probability density function////////
// 	//// instantiate the static variable
// 	CrpsProbabilityDensityFunctionFactory::CallbackMap CrpsProbabilityDensityFunctionFactory::mProbabilityDensityFunctions;
// 	std::vector<QString> CrpsProbabilityDensityFunctionFactory::mProbabilityDensityFunctionNames;
// 	QString CrpsProbabilityDensityFunctionFactory::mOwnerPlugin;
// 	//QString CrpsProbabilityDensityFunctionFactory::mDescription;
// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mDateMap;
// 	std::map<const QString, QString> CrpsProbabilityDensityFunctionFactory::mVersionMap;

// 	QString CrpsProbabilityDensityFunctionFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsProbabilityDensityFunctionFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsProbabilityDensityFunctionFactory::InitializeProbabilityDensityFunction(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsProbabilityDensityFunctionFactory::RegisterProbabilityDensityFunction(const QString &name, const QString &pluginName, const QString &description, CreateProbabilityDensityFunctionCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mProbabilityDensityFunctions[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsProbabilityDensityFunctionFactory::UnregisterProbabilityDensityFunction(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mProbabilityDensityFunctions.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLProbabilityDensityFunction *CrpsProbabilityDensityFunctionFactory::BuildProbabilityDensityFunction(const QString &name)
// 	{
// 		CallbackMap::iterator it = mProbabilityDensityFunctions.find(name);
// 		if (it != mProbabilityDensityFunctions.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateProbabilityDensityFunctionCallback>& CrpsProbabilityDensityFunctionFactory::GetProbabilityDensityFunctionNamesMap()
// 	{
// 		return mProbabilityDensityFunctions;
// 	}

// 	std::vector<QString> CrpsProbabilityDensityFunctionFactory::GetNameVector()
// 	{
// 		return mProbabilityDensityFunctionNames;
// 	}

// 	std::map<const QString, QString> & CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsProbabilityDensityFunctionFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsProbabilityDensityFunctionFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsProbabilityDensityFunctionFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsProbabilityDensityFunctionFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsProbabilityDensityFunctionFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
// ///////Roughness////////
// 	//// instantiate the static variable
// 	CrpsRoughnessFactory::CallbackMap CrpsRoughnessFactory::mRoughnesss;
// 	std::vector<QString> CrpsRoughnessFactory::mRoughnessNames;
// 	QString CrpsRoughnessFactory::mOwnerPlugin;
// 	//QString CrpsRoughnessFactory::mDescription;
// 	std::map<const QString, QString> CrpsRoughnessFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsRoughnessFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsRoughnessFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsRoughnessFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsRoughnessFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsRoughnessFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsRoughnessFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsRoughnessFactory::mDateMap;
// 	std::map<const QString, QString> CrpsRoughnessFactory::mVersionMap;

// 	QString CrpsRoughnessFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsRoughnessFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsRoughnessFactory::InitializeRoughness(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsRoughnessFactory::RegisterRoughness(const QString &name, const QString &pluginName, const QString &description, CreateRoughnessCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mRoughnesss[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsRoughnessFactory::UnregisterRoughness(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mRoughnesss.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLRoughness *CrpsRoughnessFactory::BuildRoughness(const QString &name)
// 	{
// 		CallbackMap::iterator it = mRoughnesss.find(name);
// 		if (it != mRoughnesss.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateRoughnessCallback>& CrpsRoughnessFactory::GetRoughnessNamesMap()
// 	{
// 		return mRoughnesss;
// 	}

// 	std::vector<QString> CrpsRoughnessFactory::GetNameVector()
// 	{
// 		return mRoughnessNames;
// 	}

// 	std::map<const QString, QString> & CrpsRoughnessFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsRoughnessFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsRoughnessFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsRoughnessFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsRoughnessFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsRoughnessFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsRoughnessFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsRoughnessFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
// ///////Shear velocity of flow////////
// 	//// instantiate the static variable
// 	CrpsShearVelocityOfFlowFactory::CallbackMap CrpsShearVelocityOfFlowFactory::mShearVelocityOfFlows;
// 	std::vector<QString> CrpsShearVelocityOfFlowFactory::mShearVelocityOfFlowNames;
// 	QString CrpsShearVelocityOfFlowFactory::mOwnerPlugin;
// 	//QString CrpsShearVelocityOfFlowFactory::mDescription;
// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mDateMap;
// 	std::map<const QString, QString> CrpsShearVelocityOfFlowFactory::mVersionMap;

// 	QString CrpsShearVelocityOfFlowFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsShearVelocityOfFlowFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsShearVelocityOfFlowFactory::InitializeShearVelocityOfFlow(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsShearVelocityOfFlowFactory::RegisterShearVelocityOfFlow(const QString &name, const QString &pluginName, const QString &description, CreateShearVelocityOfFlowCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mShearVelocityOfFlows[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsShearVelocityOfFlowFactory::UnregisterShearVelocityOfFlow(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mShearVelocityOfFlows.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLShearVelocityOfFlow *CrpsShearVelocityOfFlowFactory::BuildShearVelocityOfFlow(const QString &name)
// 	{
// 		CallbackMap::iterator it = mShearVelocityOfFlows.find(name);
// 		if (it != mShearVelocityOfFlows.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateShearVelocityOfFlowCallback>& CrpsShearVelocityOfFlowFactory::GetShearVelocityOfFlowNamesMap()
// 	{
// 		return mShearVelocityOfFlows;
// 	}

// 	std::vector<QString> CrpsShearVelocityOfFlowFactory::GetNameVector()
// 	{
// 		return mShearVelocityOfFlowNames;
// 	}

// 	std::map<const QString, QString> & CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsShearVelocityOfFlowFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsShearVelocityOfFlowFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsShearVelocityOfFlowFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsShearVelocityOfFlowFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsShearVelocityOfFlowFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
//     ///////skewness////////
// 	//// instantiate the static variable
// 	CrpsSkewnessFactory::CallbackMap CrpsSkewnessFactory::mSkewnesss;
// 	std::vector<QString> CrpsSkewnessFactory::mSkewnessNames;
// 	QString CrpsSkewnessFactory::mOwnerPlugin;
// 	//QString CrpsSkewnessFactory::mDescription;
// 	std::map<const QString, QString> CrpsSkewnessFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsSkewnessFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsSkewnessFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsSkewnessFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsSkewnessFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsSkewnessFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsSkewnessFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsSkewnessFactory::mDateMap;
// 	std::map<const QString, QString> CrpsSkewnessFactory::mVersionMap;

// 	QString CrpsSkewnessFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsSkewnessFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsSkewnessFactory::InitializeSkewness(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsSkewnessFactory::RegisterSkewness(const QString &name, const QString &pluginName, const QString &description, CreateSkewnessCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mSkewnesss[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsSkewnessFactory::UnregisterSkewness(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mSkewnesss.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLSkewness *CrpsSkewnessFactory::BuildSkewness(const QString &name)
// 	{
// 		CallbackMap::iterator it = mSkewnesss.find(name);
// 		if (it != mSkewnesss.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateSkewnessCallback>& CrpsSkewnessFactory::GetSkewnessNamesMap()
// 	{
// 		return mSkewnesss;
// 	}

// 	std::vector<QString> CrpsSkewnessFactory::GetNameVector()
// 	{
// 		return mSkewnessNames;
// 	}

// 	std::map<const QString, QString> & CrpsSkewnessFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsSkewnessFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsSkewnessFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsSkewnessFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsSkewnessFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsSkewnessFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsSkewnessFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsSkewnessFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

	
// ///////standard deviation////////
// 	//// instantiate the static variable
// 	CrpsStandardDeviationFactory::CallbackMap CrpsStandardDeviationFactory::mStandardDeviations;
// 	std::vector<QString> CrpsStandardDeviationFactory::mStandardDeviationNames;
// 	QString CrpsStandardDeviationFactory::mOwnerPlugin;
// 	//QString CrpsStandardDeviationFactory::mDescription;
// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsStandardDeviationFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mDateMap;
// 	std::map<const QString, QString> CrpsStandardDeviationFactory::mVersionMap;

// 	QString CrpsStandardDeviationFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsStandardDeviationFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsStandardDeviationFactory::InitializeStandardDeviation(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsStandardDeviationFactory::RegisterStandardDeviation(const QString &name, const QString &pluginName, const QString &description, CreateStandardDeviationCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mStandardDeviations[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsStandardDeviationFactory::UnregisterStandardDeviation(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mStandardDeviations.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLStandardDeviation *CrpsStandardDeviationFactory::BuildStandardDeviation(const QString &name)
// 	{
// 		CallbackMap::iterator it = mStandardDeviations.find(name);
// 		if (it != mStandardDeviations.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateStandardDeviationCallback>& CrpsStandardDeviationFactory::GetStandardDeviationNamesMap()
// 	{
// 		return mStandardDeviations;
// 	}

// 	std::vector<QString> CrpsStandardDeviationFactory::GetNameVector()
// 	{
// 		return mStandardDeviationNames;
// 	}

// 	std::map<const QString, QString> & CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsStandardDeviationFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsStandardDeviationFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsStandardDeviationFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsStandardDeviationFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsStandardDeviationFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsStandardDeviationFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsStandardDeviationFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
// ///////Turbulence Intensity////////
// 	//// instantiate the static variable
// 	CrpsTurbulenceIntensityFactory::CallbackMap CrpsTurbulenceIntensityFactory::mTurbulenceIntensitys;
// 	std::vector<QString> CrpsTurbulenceIntensityFactory::mTurbulenceIntensityNames;
// 	QString CrpsTurbulenceIntensityFactory::mOwnerPlugin;
// 	//QString CrpsTurbulenceIntensityFactory::mDescription;
// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mDateMap;
// 	std::map<const QString, QString> CrpsTurbulenceIntensityFactory::mVersionMap;

// 	QString CrpsTurbulenceIntensityFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsTurbulenceIntensityFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsTurbulenceIntensityFactory::InitializeTurbulenceIntensity(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsTurbulenceIntensityFactory::RegisterTurbulenceIntensity(const QString &name, const QString &pluginName, const QString &description, CreateTurbulenceIntensityCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mTurbulenceIntensitys[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsTurbulenceIntensityFactory::UnregisterTurbulenceIntensity(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mTurbulenceIntensitys.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLTurbulenceIntensity *CrpsTurbulenceIntensityFactory::BuildTurbulenceIntensity(const QString &name)
// 	{
// 		CallbackMap::iterator it = mTurbulenceIntensitys.find(name);
// 		if (it != mTurbulenceIntensitys.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateTurbulenceIntensityCallback>& CrpsTurbulenceIntensityFactory::GetTurbulenceIntensityNamesMap()
// 	{
// 		return mTurbulenceIntensitys;
// 	}

// 	std::vector<QString> CrpsTurbulenceIntensityFactory::GetNameVector()
// 	{
// 		return mTurbulenceIntensityNames;
// 	}

// 	std::map<const QString, QString> & CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsTurbulenceIntensityFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceIntensityFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceIntensityFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceIntensityFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceIntensityFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
// ///////turbulence scale////////
// 	//// instantiate the static variable
// 	CrpsTurbulenceScaleFactory::CallbackMap CrpsTurbulenceScaleFactory::mTurbulenceScales;
// 	std::vector<QString> CrpsTurbulenceScaleFactory::mTurbulenceScaleNames;
// 	QString CrpsTurbulenceScaleFactory::mOwnerPlugin;
// 	//QString CrpsTurbulenceScaleFactory::mDescription;
// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsTurbulenceScaleFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mDateMap;
// 	std::map<const QString, QString> CrpsTurbulenceScaleFactory::mVersionMap;

// 	QString CrpsTurbulenceScaleFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsTurbulenceScaleFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsTurbulenceScaleFactory::InitializeTurbulenceScale(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsTurbulenceScaleFactory::RegisterTurbulenceScale(const QString &name, const QString &pluginName, const QString &description, CreateTurbulenceScaleCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mTurbulenceScales[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsTurbulenceScaleFactory::UnregisterTurbulenceScale(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mTurbulenceScales.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLTurbulenceScale *CrpsTurbulenceScaleFactory::BuildTurbulenceScale(const QString &name)
// 	{
// 		CallbackMap::iterator it = mTurbulenceScales.find(name);
// 		if (it != mTurbulenceScales.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateTurbulenceScaleCallback>& CrpsTurbulenceScaleFactory::GetTurbulenceScaleNamesMap()
// 	{
// 		return mTurbulenceScales;
// 	}

// 	std::vector<QString> CrpsTurbulenceScaleFactory::GetNameVector()
// 	{
// 		return mTurbulenceScaleNames;
// 	}

// 	std::map<const QString, QString> & CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceScaleFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceScaleFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsTurbulenceScaleFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceScaleFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceScaleFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceScaleFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsTurbulenceScaleFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }

	
//     ///////Variance////////
// 	//// instantiate the static variable
// 	CrpsVarianceFactory::CallbackMap CrpsVarianceFactory::mVariances;
// 	std::vector<QString> CrpsVarianceFactory::mVarianceNames;
// 	QString CrpsVarianceFactory::mOwnerPlugin;
// 	//QString CrpsVarianceFactory::mDescription;
// 	std::map<const QString, QString> CrpsVarianceFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsVarianceFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsVarianceFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsVarianceFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsVarianceFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsVarianceFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsVarianceFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsVarianceFactory::mDateMap;
// 	std::map<const QString, QString> CrpsVarianceFactory::mVersionMap;

// 	QString CrpsVarianceFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsVarianceFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsVarianceFactory::InitializeVariance(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsVarianceFactory::RegisterVariance(const QString &name, const QString &pluginName, const QString &description, CreateVarianceCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mVariances[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsVarianceFactory::UnregisterVariance(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mVariances.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLVariance *CrpsVarianceFactory::BuildVariance(const QString &name)
// 	{
// 		CallbackMap::iterator it = mVariances.find(name);
// 		if (it != mVariances.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateVarianceCallback>& CrpsVarianceFactory::GetVarianceNamesMap()
// 	{
// 		return mVariances;
// 	}

// 	std::vector<QString> CrpsVarianceFactory::GetNameVector()
// 	{
// 		return mVarianceNames;
// 	}

// 	std::map<const QString, QString> & CrpsVarianceFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsVarianceFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsVarianceFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsVarianceFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsVarianceFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsVarianceFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsVarianceFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsVarianceFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }


	
// ///////Wave passage effect////////
// 	//// instantiate the static variable
// 	CrpsWavePassageEffectFactory::CallbackMap CrpsWavePassageEffectFactory::mWavePassageEffects;
// 	std::vector<QString> CrpsWavePassageEffectFactory::mWavePassageEffectNames;
// 	QString CrpsWavePassageEffectFactory::mOwnerPlugin;
// 	//QString CrpsWavePassageEffectFactory::mDescription;
// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mTobeInstalledObjectsMap;
// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mOjectDescriptionMap;
// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mOjectAndPluginMap;
//     std::map<const QString, QString> CrpsWavePassageEffectFactory::mOjectsSkipDuringUnintallationMap;

// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mTitleMap;
// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mLinkMap;
// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mAuthorMap;
// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mDateMap;
// 	std::map<const QString, QString> CrpsWavePassageEffectFactory::mVersionMap;

// 	QString CrpsWavePassageEffectFactory::GetOwnerPlugin()
// 	{
// 		return mOwnerPlugin;
// 	}

// 	void CrpsWavePassageEffectFactory::SetOwnerPlugin(QString ownerPlugin)
// 	{
// 		mOwnerPlugin = ownerPlugin;
// 	}
	
// 	void CrpsWavePassageEffectFactory::InitializeWavePassageEffect(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
// 	{		
// 		mTobeInstalledObjectsMap[name] = pluginName;
// 		mTitleMap[name] = publicationTitle;
// 		mLinkMap[name] = publicationLink;
// 		mAuthorMap[name] = publicationAuthor;
// 		mDateMap[name] = publicationDate;
// 		mVersionMap[name] = version; 


// 	}

// 	void CrpsWavePassageEffectFactory::RegisterWavePassageEffect(const QString &name, const QString &pluginName, const QString &description, CreateWavePassageEffectCallback cb)
// 	{
// 		if (mTobeInstalledObjectsMap[name] != pluginName)
// 		{
// 			return;
// 		}
// 		mWavePassageEffects[name] = cb;
// 		mOjectDescriptionMap[name] = description;
// 		mOjectAndPluginMap[name] = pluginName;
		
// 	}

// 	void CrpsWavePassageEffectFactory::UnregisterWavePassageEffect(const QString &name, const QString &pluginName)
// 	{
// 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
// 		{
// 			mWavePassageEffects.erase(name);
// 			mOjectDescriptionMap.erase(name);
// 			mOjectAndPluginMap.erase(name);

// 		}

// 	}

// 	IrpsWLWavePassageEffect *CrpsWavePassageEffectFactory::BuildWavePassageEffect(const QString &name)
// 	{
// 		CallbackMap::iterator it = mWavePassageEffects.find(name);
// 		if (it != mWavePassageEffects.end())
// 		{
// 			// call the creation callback to construct this derived name
// 			return (it->second)();
// 		}

// 		return NULL;
// 	}

//     std::map<const QString, CreateWavePassageEffectCallback>& CrpsWavePassageEffectFactory::GetWavePassageEffectNamesMap()
// 	{
// 		return mWavePassageEffects;
// 	}

// 	std::vector<QString> CrpsWavePassageEffectFactory::GetNameVector()
// 	{
// 		return mWavePassageEffectNames;
// 	}

// 	std::map<const QString, QString> & CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()
// 	{
// 		return mTobeInstalledObjectsMap;
// 	}

// 	std::map<const QString, QString>& CrpsWavePassageEffectFactory::GetOjectDescriptionMap()
// 	{
// 		return mOjectDescriptionMap;
// 	}

// 	std::map<const QString, QString>& CrpsWavePassageEffectFactory::GetOjectAndPluginMap()
// 	{
// 		return mOjectAndPluginMap;
// 	}

// 	///
// 	std::map<const QString, QString>& CrpsWavePassageEffectFactory::GetTitleMap()
// 	{
// 		return mTitleMap;
// 	}

// 	std::map<const QString, QString>& CrpsWavePassageEffectFactory::GetLinkMap()
// 	{
// 		return mLinkMap;
// 	}

// 	std::map<const QString, QString>& CrpsWavePassageEffectFactory::GetAuthorMap()
// 	{
// 		return mAuthorMap;
// 	}

// 	std::map<const QString, QString>& CrpsWavePassageEffectFactory::GetDateMap()
// 	{
// 		return mDateMap;
// 	}

// 	std::map<const QString, QString>& CrpsWavePassageEffectFactory::GetVersionMap()
// 	{
// 		return mVersionMap;
// 	}

//     std::map<const QString, QString> &  CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap()
//     {
// 	    return mOjectsSkipDuringUnintallationMap;
//     }
////////////////////////////////////////////////////////////////////////////

#define WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(_ObjectClass_, _ObjectInterface_, _CreateCallback_) \
typedef _ObjectInterface_ *(*_CreateCallback_)(); \
	_ObjectClass_::CallbackMap _ObjectClass_::mObjects; \
	std::vector<QString> _ObjectClass_::mObjectNames; \
	QString _ObjectClass_::mOwnerPlugin; \
	std::map<const QString, QString> _ObjectClass_::mTobeInstalledObjectsMap; \
	std::map<const QString, QString> _ObjectClass_::mOjectDescriptionMap; \
	std::map<const QString, QString> _ObjectClass_::mOjectAndPluginMap; \
    std::map<const QString, QString> _ObjectClass_::mOjectsSkipDuringUnintallationMap; \
	std::map<const QString, QString> _ObjectClass_::mTitleMap; \
	std::map<const QString, QString> _ObjectClass_::mLinkMap; \
	std::map<const QString, QString> _ObjectClass_::mAuthorMap; \
	std::map<const QString, QString> _ObjectClass_::mDateMap; \
	std::map<const QString, QString> _ObjectClass_::mVersionMap; \
	QString _ObjectClass_::GetOwnerPlugin() \
	{ \
		return mOwnerPlugin; \
	} \
	void _ObjectClass_::SetOwnerPlugin(QString ownerPlugin) \
	{ \
		mOwnerPlugin = ownerPlugin; \
	} \	
	void _ObjectClass_::InitializeObject(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version) \
	{ \		
        mTobeInstalledObjectsMap[name] = pluginName; \
		mTitleMap[name] = publicationTitle; \
		mLinkMap[name] = publicationLink; \
		mAuthorMap[name] = publicationAuthor; \
		mDateMap[name] = publicationDate; \
		mVersionMap[name] = version; \ 
	} \
    void _ObjectClass_::RegisterObject(const QString &name, const QString &pluginName, const QString &description, _CreateCallback_ cb) \
	{ \
		if (mTobeInstalledObjectsMap[name] != pluginName) \
		{ \
			return; \
		} \
		mObjects[name] = cb; \
		mOjectDescriptionMap[name] = description; \
		mOjectAndPluginMap[name] = pluginName; \		
	} \
	void _ObjectClass_::UnregisterObject(const QString &name, const QString &pluginName) \
	{ \
		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end()) \
		{ \
			mObjects.erase(name); \
			mOjectDescriptionMap.erase(name); \
			mOjectAndPluginMap.erase(name); \
		} \
	} \
	_ObjectInterface_ *_ObjectClass_::BuildObject(const QString &name) \
	{ \
		CallbackMap::iterator it = mObjects.find(name); \
		if (it != mObjects.end()) \
		{ \
			return (it->second)(); \
		} \
		return NULL; \
	} \
    std::map<const QString, _CreateCallback_>& _ObjectClass_::GetObjectNamesMap() \
	{ \
		return mObjects; \
	} \
	std::vector<QString> _ObjectClass_::GetNameVector() \
	{ \
		return mObjectNames; \
	} \
    std::map<const QString, QString>& _ObjectClass_::GetTobeInstalledObjectsMap() \
	{ \
		return mTobeInstalledObjectsMap; \
	} \
	std::map<const QString, QString>& _ObjectClass_::GetOjectDescriptionMap() \
	{ \
		return mOjectDescriptionMap; \
	} \
	std::map<const QString, QString>& _ObjectClass_::GetOjectAndPluginMap() \
	{ \
		return mOjectAndPluginMap; \
	} \
	std::map<const QString, QString>& _ObjectClass_::GetTitleMap() \
	{ \
		return mTitleMap; \
	} \
	std::map<const QString, QString>& _ObjectClass_::GetLinkMap() \
	{ \
		return mLinkMap; \
	} \
	std::map<const QString, QString>& _ObjectClass_::GetAuthorMap() \
	{ \
		return mAuthorMap; \
	} \
	std::map<const QString, QString>& _ObjectClass_::GetDateMap() \
	{ \
		return mDateMap; \
	} \
	std::map<const QString, QString>& _ObjectClass_::GetVersionMap() \
	{ \
		return mVersionMap; \
	} \
    std::map<const QString, QString>& _ObjectClass_::GetOjectsSkipDuringUnintallationMap() \
    { \
	    return mOjectsSkipDuringUnintallationMap; \
    } 



WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsCoherenceFactory, IrpsWLCoherence, IrpsWLCoherenceCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsLocationDistributionFactory, IrpsWLLocationDistribution, IrpsWLLocationDistributionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsMeanFactory, IrpsWLMean, IrpsWLMeanCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsXSpectrumFactory, IrpsWLXSpectrum, IrpsWLXSpectrumCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsZSpectrumFactory, IrpsWLZSpectrum, IrpsWLZSpectrumCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsYSpectrumFactory, IrpsWLYSpectrum, IrpsWLYSpectrumCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsSimuMethodFactory, IrpsWLSimuMethod, IrpsWLSimuMethodCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsFrequencyDistributionFactory, IrpsWLFrequencyDistribution, IrpsWLFrequencyDistributionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsRandomnessFactory, IrpsWLRandomness, IrpsWLRandomnessCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsPSDdecomMethodFactory, IrpsWLPSDdecompositionMethod, IrpsWLPSDdecompositionMethodCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsCorrelationFactory, IrpsWLCorrelation, IrpsWLCorrelationCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsModulationFactory, IrpsWLModulation, IrpsWLModulationCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsTableToolFactory, IrpsWLTableTool, IrpsWLTableToolCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsMatrixToolFactory, IrpsWLMatrixTool, IrpsWLMatrixToolCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsUserDefinedRPSObjectFactory, IrpsWLUserDefinedRPSObject, IrpsWLUserDefinedRPSObjectCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsCumulativeProbabilityDistributionFactory, IrpsWLCumulativeProbabilityDistribution, IrpsWLCumulativeProbabilityDistributionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsGustFactorFactory, IrpsWLGustFactor, IrpsWLGustFactorCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsKurtosisFactory, IrpsWLKurtosis, IrpsWLKurtosisCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsPeakFactorFactory, IrpsWLPeakFactor, IrpsWLPeakFactorCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsProbabilityDensityFunctionFactory, IrpsWLProbabilityDensityFunction, IrpsWLProbabilityDensityFunctionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsRoughnessFactory, IrpsWLRoughness, IrpsWLRoughnessCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsShearVelocityOfFlowFactory, IrpsWLShearVelocityOfFlow, IrpsWLShearVelocityOfFlowCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsSkewnessFactory, IrpsWLSkewness, IrpsWLSkewnessCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsStandardDeviationFactory, IrpsWLStandardDeviation, IrpsWLStandardDeviationCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsTurbulenceIntensityFactory, IrpsWLTurbulenceIntensity, IrpsWLTurbulenceIntensityCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsTurbulenceScaleFactory, IrpsWLTurbulenceScale, IrpsWLTurbulenceScaleCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsVarianceFactory, IrpsWLVariance, IrpsWLVarianceCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_SOURCE(CrpsWavePassageEffectFactory, IrpsWLWavePassageEffect, IrpsWLWavePassageEffectCallback)


