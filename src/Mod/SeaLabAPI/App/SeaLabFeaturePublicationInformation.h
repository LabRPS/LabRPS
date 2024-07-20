
#ifndef WLOBJECTPUBLICATIONINFO_H
#define WLOBJECTPUBLICATIONINFO_H

#include "RPSSeaLabAPIdefines.h"
#include <App/RPSFeature.h>

namespace SeaLabAPI {

class RPS_CORE_API SeaLabFeaturePublicationInformation
{
public:
    SeaLabFeaturePublicationInformation();
    ~SeaLabFeaturePublicationInformation();

	 App::PropertyString PublicationTitle;
	 App::PropertyString PublicationLink;
	 App::PropertyString PublicationAuthor;
	 App::PropertyString PublicationDate;

	bool operator==(const SeaLabAPI::SeaLabFeaturePublicationInformation  &rhs) const
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

} //namespace SeaLabAPI
#endif  // WLOBJECTPUBLICATIONINFO_H