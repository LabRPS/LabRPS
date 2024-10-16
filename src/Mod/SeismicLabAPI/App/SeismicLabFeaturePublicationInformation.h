
#ifndef WLOBJECTPUBLICATIONINFO_H
#define WLOBJECTPUBLICATIONINFO_H

#include "RPSSeismicLabAPIdefines.h"
#include <App/RPSFeature.h>

namespace SeismicLabAPI {

class RPS_CORE_API SeismicLabFeaturePublicationInformation
{
public:
    SeismicLabFeaturePublicationInformation();
    ~SeismicLabFeaturePublicationInformation();

	 App::PropertyString PublicationTitle;
	 App::PropertyString PublicationLink;
	 App::PropertyString PublicationAuthor;
	 App::PropertyString PublicationDate;

	bool operator==(const SeismicLabAPI::SeismicLabFeaturePublicationInformation  &rhs) const
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

} //namespace SeismicLabAPI
#endif  // WLOBJECTPUBLICATIONINFO_H