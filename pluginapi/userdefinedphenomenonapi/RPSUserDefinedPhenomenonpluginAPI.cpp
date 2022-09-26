
#include "RPSUserDefinedPhenomenonPluginAPI.h"
#include "RPSUserDefinedPhenomenonAPI.h"

const char * RPSUserDefinedPhenomenonPluginAPIInfo::getUserDefinedPhenomenonPluginAPIVersion()
{
	return "0.001";
}

 ////////////////////////////////////UserDefinedPhenomenon//////////////////////////////////////////

 void RegisterUserDefinedPhenomenon(const QString name, const QString &pluginName, const QString &description, UserDefinedPhenomenonInitFunc init_cb, UserDefinedPhenomenonFreeFunc free_cb)
 {
	 if (CrpsUserDefinedPhenomenonFactory::GetTobeInstalledObjectsMap().find(name) ==
		 CrpsUserDefinedPhenomenonFactory::GetTobeInstalledObjectsMap().end())
	 {
		 return;
	 }
	 CrpsUserDefinedPhenomenonFactory::RegisterUserDefinedPhenomenon(name, pluginName, description, init_cb);
	 (void)free_cb; // we never free these objects
 }

 void InitializeUserDefinedPhenomenon(const QString name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version)
 {
	 CrpsUserDefinedPhenomenonFactory::InitializeUserDefinedPhenomenon(name, description, publicationTitle, publicationLink, publicationAuthor, publicationDate, version);
 }

 void UnregisterUserDefinedPhenomenon(const QString name, const QString &pluginName)
 {
	 CrpsUserDefinedPhenomenonFactory::UnregisterUserDefinedPhenomenon(name, pluginName);
 }

 