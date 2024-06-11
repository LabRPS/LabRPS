
#include "widgets/DlgGridPoints.h"
#include "WLGridPoints.h"
#include <QMessageBox>
#include <Gui/Control.h>


using namespace std;
using namespace WindLab;

////////////////////////Horizontal distribution///////////////////////////////////////////////

PROPERTY_SOURCE(WindLab::WLGridPoints, WindLabAPI::WindLabFeatureLocationDistribution)

WLGridPoints::WLGridPoints()
{
    static const char* locationgroup = "Distribution";
    ADD_PROPERTY_TYPE(CenterPoint, (Base::Vector3d(0,0,0)), locationgroup, App::Prop_None, "the center point of the grid.");

    static const char* locationPlanEnum[] = {"XY Plane", "YZ Plane", "XZ Plane", nullptr};
    ADD_PROPERTY_TYPE(LocationPlan, ((long int)0), locationgroup, App::Prop_None,"The plan in which the points a distributed ( parallel to xy, yz, xz).");
    LocationPlan.setEnums(locationPlanEnum);

    ADD_PROPERTY_TYPE(Spacing1, (5000.0), locationgroup, App::Prop_None, "The even spacing between the points along one axis");
    ADD_PROPERTY_TYPE(Spacing2, (5000.0), locationgroup, App::Prop_None, "The even spacing between the points along other axis");
    ADD_PROPERTY_TYPE(Length1, (50000.0), locationgroup, App::Prop_None, "The length along one axis");
    ADD_PROPERTY_TYPE(Length2, (50000.0), locationgroup, App::Prop_None, "The length along other axis");
}


bool WLGridPoints::ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord)
{
    int pointNumber1 = Length1.getValue() / Spacing1.getValue();
    int pointNumber2 = Length2.getValue() / Spacing2.getValue();
    int nPoints = pointNumber1 * pointNumber2;
    if (nPoints != Data.numberOfSpatialPosition.getValue())
    {
        Base::Console().Warning("The computation fails. The number of simulation points should be %d.\n", nPoints);
        return false;
    }

    std::vector<Base::Vector3d> points;

    if (QString::fromLatin1(LocationPlan.getValueAsString()) == QString::fromLatin1("XY Plane")) {
       for (int loop1 = 0; loop1 < pointNumber1; loop1++){
          for (int loop2 = 0; loop2 < pointNumber2; loop2++){
            Base::Vector3d position = Base::Vector3d(CenterPoint.getValue().x + loop1 * Spacing1.getQuantityValue().getValueAs(Base::Quantity::Metre), CenterPoint.getValue().y + loop2 * Spacing2.getQuantityValue().getValueAs(Base::Quantity::Metre),CenterPoint.getValue().z);
            points.push_back(position);
          }
       }
    }
        else if (QString::fromLatin1(LocationPlan.getValueAsString()) == QString::fromLatin1("YZ Plane")) {
        for (int loop1 = 0; loop1 < pointNumber1; loop1++){
          for (int loop2 = 0; loop2 < pointNumber2; loop2++){
            Base::Vector3d position = Base::Vector3d(CenterPoint.getValue().x, CenterPoint.getValue().y + loop1 * Spacing1.getQuantityValue().getValueAs(Base::Quantity::Metre),CenterPoint.getValue().z + loop2 * Spacing2.getQuantityValue().getValueAs(Base::Quantity::Metre));
            points.push_back(position);
          }
       }
        }
        else if (QString::fromLatin1(LocationPlan.getValueAsString()) == QString::fromLatin1("XZ Plane")) {
         for (int loop1 = 0; loop1 < pointNumber1; loop1++){
          for (int loop2 = 0; loop2 < pointNumber2; loop2++){
            Base::Vector3d position = Base::Vector3d(CenterPoint.getValue().x + loop1 * Spacing1.getQuantityValue().getValueAs(Base::Quantity::Metre), CenterPoint.getValue().y, CenterPoint.getValue().z + loop2 * Spacing2.getQuantityValue().getValueAs(Base::Quantity::Metre));
            points.push_back(position);
          }
       }
        }
        if (points.empty())
       return false;
    for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue(); loop++) {
       dLocCoord(loop, 0) = loop + 1;
       dLocCoord(loop, 1) = points.at(loop).x;
       dLocCoord(loop, 2) = points.at(loop).y;
       dLocCoord(loop, 3) = points.at(loop).z;
    }

	return true;	
}


bool WLGridPoints::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
	
	WindLabGui::GridPointsDialogEdit* dlg = new WindLabGui::GridPointsDialogEdit(CenterPoint, Spacing1, Spacing2, Length1, Length2, LocationPlan,Data.spatialDistribution);
    Gui::Control().showDialog(dlg);

	return true;
}
