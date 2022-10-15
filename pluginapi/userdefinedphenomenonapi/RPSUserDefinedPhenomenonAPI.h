

#ifndef RPSUSERDEFINEDPHENOMENONAPI_H
#define RPSUSERDEFINEDPHENOMENONAPI_H

#include "RPSUserDefinedPhenomenonAPIdefines.h"
#include "IrpsUserDefinedPhenomenon.h"

#include <map>
#include<vector>


///
/// A factory object in LabRPS
///

class RPS_CORE_API RPSUserDefinedPhenomenonAPIInfo
{
public:

	static const char * getUserDefinedPhenomenonAPIVersion();
};

///////////UserDefinedPhenomenon///////////////

class RPS_CORE_API CrpsUserDefinedPhenomenonFactory
{
	public:
		typedef IrpsUserDefinedPhenomenon *(*CreateUserDefinedPhenomenonCallback)();

		static void InitializeUserDefinedPhenomenon(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterUserDefinedPhenomenon(const QString &name, const QString &pluginName, const QString &description, CreateUserDefinedPhenomenonCallback cb);

		static void UnregisterUserDefinedPhenomenon(const QString &name, const QString &pluginName);

		static IrpsUserDefinedPhenomenon *BuildUserDefinedPhenomenon(const QString &name);

		static std::vector<QString> GetNameVector();

		static std::map<const QString, CreateUserDefinedPhenomenonCallback>& GetUserDefinedPhenomenonNamesMap();

		static QString GetOwnerPlugin();
		static void SetOwnerPlugin(QString ownerPlugin);
		/*static QString GetDescription();
		static void SetDescription(QString description);*/
		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
		static std::map<const QString, QString> & GetOjectDescriptionMap();
		static std::map<const QString, QString> & GetOjectAndPluginMap();
		static std::map<const QString, QString> & GetTitleMap();
		static std::map<const QString, QString> & GetLinkMap();
		static std::map<const QString, QString> & GetAuthorMap();
		static std::map<const QString, QString> & GetDateMap();
	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
		static std::map<const QString, QString> & GetVersionMap();

	private:
		typedef std::map<const QString, CreateUserDefinedPhenomenonCallback> CallbackMap;
		static CallbackMap mUserDefinedPhenomena;
		static std::vector<QString> mUserDefinedPhenomenonNames;
		static QString mOwnerPlugin;
		//static QString mDescription;
		static std::map<const QString, QString> mTobeInstalledObjectsMap;
		static std::map<const QString, QString> mOjectDescriptionMap;
		static std::map<const QString, QString> mOjectAndPluginMap;
		static std::map<const QString, QString> mTitleMap;
		static std::map<const QString, QString> mLinkMap;
		static std::map<const QString, QString> mAuthorMap;
		static std::map<const QString, QString> mDateMap;
		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
		static std::map<const QString, QString> mVersionMap;

};

#endif //RPSUSERDEFINEDPHENOMENONAPI_H
