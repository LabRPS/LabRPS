#ifndef WINDLAB_PLUGIN_GENERALSD_H
#define WINDLAB_PLUGIN_GENERALSD_H

#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include <App/PropertyStandard.h>
#include <App/PropertyGeo.h>

namespace WindLabAPI { class WindLabSimuData; }

class QStringList;

namespace WindLab {

class GeneralSpatialDistribution : public WindLabAPI::IrpsWLLocationDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::GeneralSpatialDistribution);

public:
	GeneralSpatialDistribution();
	
	~GeneralSpatialDistribution() {};

	bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData &Data, mat &dLocCoord);

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData &Data);

    App::PropertyVectorList Locations;

};

} // namespace App

#endif // WINDLAB_PLUGIN_GENERALSD_H
