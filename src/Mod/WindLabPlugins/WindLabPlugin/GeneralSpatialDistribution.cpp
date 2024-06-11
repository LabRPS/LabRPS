#include "Precompiled.h"
#include "GeneralSpatialDistribution.h"
#include <Mod/WindLabAPI/App/WindLabSimuData.h>
#include <Base/Sequencer.h>
#include <Base/Console.h>
#include <Gui/MainWindow.h>
#include <Libraries/Alphaplot/Table.h>
#include <Base/Quantity.h>

using namespace std;
using namespace WindLab;
using namespace WindLabAPI;

//spacing between two adjacent points
PROPERTY_SOURCE(WindLab::GeneralSpatialDistribution, WindLabAPI::WindLabFeatureLocationDistribution)

GeneralSpatialDistribution::GeneralSpatialDistribution()
{
    static const char* Points = "Locations";

    ADD_PROPERTY_TYPE(Locations, (Base::Vector3d()), Points, App::Prop_None,"The list of locations");
}

bool GeneralSpatialDistribution::ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData &Data, mat &dLocCoord)
{
    const std::vector<Base::Vector3d> nodes = Locations.getValues();
    int j = 0;
    for (std::vector<Base::Vector3d>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        dLocCoord(j, 0) = j + 1;
        dLocCoord(j, 1) = it->x;
        dLocCoord(j, 2) = it->y;
        dLocCoord(j, 3) = it->z;

        //dLocCoord(j, 1) = (Base::Quantity(it->x, ())).getValueAs(Base::Quantity::Metre);
        j++;
    }
	return true;
}


bool GeneralSpatialDistribution::OnInitialSetting(const WindLabAPI::WindLabSimuData &Data)
{
	//std::unique_ptr<GeneralDistributionDialog> dlg(new GeneralDistributionDialog(Data.numberOfSpatialPosition.getValue(), pointsMatrix));

	//if (dlg->exec() == QDialog::Accepted) //
	//{
	//	pointsMatrix = dlg->m_pointsMatrix;
	//}

	return true;
}
