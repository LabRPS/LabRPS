#ifndef WINDLAB_PLUGIN_HORIZONTALUNIFSD_H
#define WINDLAB_PLUGIN_HORIZONTALUNIFSD_H

#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include <App/PropertyGeo.h>
#include <App/PropertyUnits.h>

namespace WindLab {

class CWLHorizontalUniformDistribution : public WindLabAPI::IrpsWLLocationDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CWLHorizontalUniformDistribution);

public:
	CWLHorizontalUniformDistribution();
	
	~CWLHorizontalUniformDistribution() {};

	bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord);

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// the first point the distribution will start from
    App::PropertyPosition FirstPoint;

	// the even spacing between the points
    App::PropertyLength Spacing;
};

} // namespace App

#endif // WINDLAB_PLUGIN_HORIZONTALUNIFSD_H
