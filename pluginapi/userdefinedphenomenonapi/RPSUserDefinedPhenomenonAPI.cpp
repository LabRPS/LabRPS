// RPScoreAPI.cpp : Defines the initialization routines for the DLL.
//


#include "RPSUserDefinedPhenomenonAPI.h"
#include <iostream>

typedef IrpsUserDefinedPhenomenon *(*CreateUserDefinedPhenomenonCallback)();

const char * RPSUserDefinedPhenomenonAPIInfo::getUserDefinedPhenomenonAPIVersion()
{
	return "0.001";
}

	///////UserDefinedPhenomenon////////
	//// instantiate the static variable
	CrpsUserDefinedPhenomenonFactory::CallbackMap CrpsUserDefinedPhenomenonFactory::mUserDefinedPhenomena;
	std::vector<QString> CrpsUserDefinedPhenomenonFactory::mUserDefinedPhenomenonNames;
	QString CrpsUserDefinedPhenomenonFactory::mOwnerPlugin;
	//QString CrpsUserDefinedPhenomenonFactory::mDescription;
	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mTobeInstalledObjectsMap;
	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mOjectDescriptionMap;
	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mOjectAndPluginMap;
    std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mOjectsSkipDuringUnintallationMap;

	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mTitleMap;
	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mLinkMap;
	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mAuthorMap;
	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mDateMap;
	std::map<const QString, QString> CrpsUserDefinedPhenomenonFactory::mVersionMap;

	QString CrpsUserDefinedPhenomenonFactory::GetOwnerPlugin()
	{
		return mOwnerPlugin;
	}

	void CrpsUserDefinedPhenomenonFactory::SetOwnerPlugin(QString ownerPlugin)
	{
		mOwnerPlugin = ownerPlugin;
	}
	
	void CrpsUserDefinedPhenomenonFactory::InitializeUserDefinedPhenomenon(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
	{		
		mTobeInstalledObjectsMap[name] = pluginName;
		mTitleMap[name] = publicationTitle;
		mLinkMap[name] = publicationLink;
		mAuthorMap[name] = publicationAuthor;
		mDateMap[name] = publicationDate;
		mVersionMap[name] = version;

	}

    void CrpsUserDefinedPhenomenonFactory::RegisterUserDefinedPhenomenon(const QString &name, const QString &pluginName, const QString &description, CreateUserDefinedPhenomenonCallback cb)
	{
        if (mTobeInstalledObjectsMap[name] != pluginName)
		{
			return;
		}
		mUserDefinedPhenomena[name] = cb;
		mOjectDescriptionMap[name] = description;
		mOjectAndPluginMap[name] = pluginName;
	}

	void CrpsUserDefinedPhenomenonFactory::UnregisterUserDefinedPhenomenon(const QString &name, const QString &pluginName)
	{
        if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
        {
			mUserDefinedPhenomena.erase(name);
			mOjectDescriptionMap.erase(name);
			mOjectAndPluginMap.erase(name);

		}

	}

	IrpsUserDefinedPhenomenon *CrpsUserDefinedPhenomenonFactory::BuildUserDefinedPhenomenon(const QString &name)
	{
		CallbackMap::iterator it = mUserDefinedPhenomena.find(name);
		if (it != mUserDefinedPhenomena.end())
		{
			// call the creation callback to construct this derived name
			return (it->second)();
		}

		return NULL;
	}

	std::map<const QString, CreateUserDefinedPhenomenonCallback>& CrpsUserDefinedPhenomenonFactory::GetUserDefinedPhenomenonNamesMap()
	{
		return mUserDefinedPhenomena;
	}

	std::vector<QString> CrpsUserDefinedPhenomenonFactory::GetNameVector()
	{
		return mUserDefinedPhenomenonNames;
	}

	std::map<const QString, QString> & CrpsUserDefinedPhenomenonFactory::GetTobeInstalledObjectsMap()
	{
		return mTobeInstalledObjectsMap;
	}

	std::map<const QString, QString>& CrpsUserDefinedPhenomenonFactory::GetOjectDescriptionMap()
	{
		return mOjectDescriptionMap;
	}

	std::map<const QString, QString>& CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap()
	{
		return mOjectAndPluginMap;
	}

	///
	std::map<const QString, QString>& CrpsUserDefinedPhenomenonFactory::GetTitleMap()
	{
		return mTitleMap;
	}

	std::map<const QString, QString>& CrpsUserDefinedPhenomenonFactory::GetLinkMap()
	{
		return mLinkMap;
	}

	std::map<const QString, QString>& CrpsUserDefinedPhenomenonFactory::GetAuthorMap()
	{
		return mAuthorMap;
	}

	std::map<const QString, QString>& CrpsUserDefinedPhenomenonFactory::GetDateMap()
	{
		return mDateMap;
	}

	std::map<const QString, QString>& CrpsUserDefinedPhenomenonFactory::GetVersionMap()
	{
		return mVersionMap;
	}


    std::map<const QString, QString> &  CrpsUserDefinedPhenomenonFactory::GetOjectsSkipDuringUnintallationMap()
    {
	    return mOjectsSkipDuringUnintallationMap;
    }
	
