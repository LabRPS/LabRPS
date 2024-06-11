
#ifndef WLOBJECTDESCRIPTION_H
#define WLOBJECTDESCRIPTION_H

#include "RPSWindLabAPIdefines.h"
#include <App/RPSFeature.h>

namespace WindLabAPI {

class RPS_CORE_API WindLabFeatureDescription
{
public:
    WindLabFeatureDescription();
    ~WindLabFeatureDescription();

	 App::PropertyString PluginName;
	 App::PropertyString PublicationTitle;
	 App::PropertyString PublicationLink;
	 App::PropertyString PublicationAuthor;
	 App::PropertyString PublicationDate;
	 App::PropertyString ReleaseDate;
	 App::PropertyString Author;
	 App::PropertyString Version;
	 App::PropertyString APIVersion;
	 App::PropertyString PluginVersion;
     App::PropertyString type;
     App::PropertyString group;
     App::PropertyBool Stationarity;

	App::PropertyString LabRPSVersion;
	App::PropertyString Path;
	App::PropertyString ObjectName;
	App::PropertyString Description;

	bool operator==(const WindLabAPI::WindLabFeatureDescription& rhs) const
	{
        return PluginName.getValue() == rhs.PluginName.getValue() &&
			   Description.getValue() == rhs.Description.getValue() &&
			   PublicationTitle.getValue() == rhs.PublicationTitle.getValue() &&
			   PublicationLink.getValue() == rhs.PublicationLink.getValue() &&
			   PublicationAuthor.getValue() == rhs.PublicationAuthor.getValue() &&
			   PublicationDate.getValue() == rhs.PublicationDate.getValue() &&
			   ObjectName.getValue() == rhs.ObjectName.getValue() &&
			   ReleaseDate.getValue() == rhs.ReleaseDate.getValue() &&
			   Author.getValue() == rhs.Author.getValue() &&
			   Version.getValue() == rhs.Version.getValue() &&
			   LabRPSVersion.getValue() == rhs.LabRPSVersion.getValue() &&
			   APIVersion.getValue() == rhs.APIVersion.getValue() && 
			   PluginVersion.getValue() == rhs.PluginVersion.getValue() && 
			   Stationarity.getValue() == rhs.Stationarity.getValue() &&
			   type.getValue() == rhs.type.getValue() &&
			   group.getValue() == rhs.type.getValue();

	}
};

} //namespace WindLabAPI
#endif  // WLOBJECTDESCRIPTION_H