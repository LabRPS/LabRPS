#ifndef WINDLAB_PLUGIN_GRIDPOINTS_H
#define WINDLAB_PLUGIN_GRIDPOINTS_H

#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include <App/PropertyGeo.h>
#include <App/PropertyUnits.h>

namespace WindLab {

class WLGridPoints : public WindLabAPI::IrpsWLLocationDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::WLGridPoints);

public:
	WLGridPoints();
	
	~WLGridPoints() {};

	bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord);

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// the center point of the grid
    App::PropertyPosition CenterPoint;

	// the even spacing between the points along one axis
    App::PropertyLength Spacing1;

	// the even spacing between the points along the other axis
    App::PropertyLength Spacing2;

	// the length along one axis
    App::PropertyLength Length1;

	// the length along the other axis
    App::PropertyLength Length2;

	// the plan in which the points a distributed ( parallel to xy, yz, xz)
    App::PropertyEnumeration LocationPlan;
};

} // namespace App

#endif // WINDLAB_PLUGIN_GRIDPOINTS_H
