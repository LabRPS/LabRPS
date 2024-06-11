#ifndef WINDLAB_PLUGIN_VERTICALUNIFSD_H
#define WINDLAB_PLUGIN_VERTICALUNIFSD_H

#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include <App/PropertyGeo.h>
#include <App/PropertyUnits.h>

namespace WindLab {

class CWLVerticalUniformDistribution : public WindLabAPI::IrpsWLLocationDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::class CWLVerticalUniformDistribution : public WindLabAPI::IrpsWLLocationDistribution);

public:
	CWLVerticalUniformDistribution();

	~CWLVerticalUniformDistribution() {};

	bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord);

	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
    // the first point the distribution will start from
    App::PropertyPosition LowestPoint;

    // the even spacing between the points
    App::PropertyLength Spacing;

    static App::PropertyQuantityConstraint::Constraints SpacingContraint;
};

} // namespace App

#endif // WINDLAB_PLUGIN_VERTICALUNIFSD_H