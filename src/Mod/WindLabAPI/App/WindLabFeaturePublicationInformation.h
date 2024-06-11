
#ifndef WLOBJECTPUBLICATIONINFO_H
#define WLOBJECTPUBLICATIONINFO_H

#include "RPSWindLabAPIdefines.h"
#include <App/RPSFeature.h>

namespace WindLabAPI {

class RPS_CORE_API WindLabFeaturePublicationInformation
{
public:
    WindLabFeaturePublicationInformation();
    ~WindLabFeaturePublicationInformation();

	 App::PropertyString PublicationTitle;
	 App::PropertyString PublicationLink;
	 App::PropertyString PublicationAuthor;
	 App::PropertyString PublicationDate;

	bool operator==(const WindLabAPI::WindLabFeaturePublicationInformation  &rhs) const
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
			   Stationarity.getValue() == rhs.Stationarity.getValue();
	}
};

} //namespace WindLabAPI
#endif  // WLOBJECTPUBLICATIONINFO_H