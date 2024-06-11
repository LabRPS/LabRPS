#ifndef WINDLAB_PLUGIN_UNIFSD_H
#define WINDLAB_PLUGIN_UNIFSD_H

#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include <App/PropertyGeo.h>
#include <App/PropertyUnits.h>

namespace WindLab {

class WLUniformDistributionLocations : public WindLabAPI::IrpsWLLocationDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::WLUniformDistributionLocations);

public:
	WLUniformDistributionLocations();
	
	~WLUniformDistributionLocations() {};

	bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord);

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// the first point the distribution will start from
    App::PropertyPosition FirstPoint;

	// the even spacing between the points
    App::PropertyLength Spacing;

	// the height at which the points are distributed
    App::PropertyEnumeration Directions;
};

} // namespace App

#endif // WINDLAB_PLUGIN_HORIZONTALUNIFSD_H
