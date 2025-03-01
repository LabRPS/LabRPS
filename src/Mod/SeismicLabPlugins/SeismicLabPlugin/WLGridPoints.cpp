/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "widgets/DlgGridPoints.h"
#include "WLGridPoints.h"
#include <QMessageBox>
#include <Gui/Control.h>


using namespace std;
using namespace SeismicLab;

////////////////////////Horizontal distribution///////////////////////////////////////////////

PROPERTY_SOURCE(SeismicLab::WLGridPoints, SeismicLabAPI::SeismicLabFeatureLocationDistribution)

WLGridPoints::WLGridPoints()
{
    static const char* locationgroup = "Distribution";
    ADD_PROPERTY_TYPE(CenterPoint, (Base::Vector3d(0,0,0)), locationgroup, App::Prop_None, "the center point of the grid.");

    static const char* locationPlanEnum[] = {"XY Plane", "YZ Plane", "XZ Plane", nullptr};
    ADD_PROPERTY_TYPE(LocationPlan, ((long int)0), locationgroup, App::Prop_None,"The plan in which the points a distributed ( parallel to xy, yz, xz).");
    LocationPlan.setEnums(locationPlanEnum);

    ADD_PROPERTY_TYPE(Spacing1, (5000.0), locationgroup, App::Prop_None, "The even spacing between the points along one axis");
    ADD_PROPERTY_TYPE(Spacing2, (5000.0), locationgroup, App::Prop_None, "The even spacing between the points along other axis");
    ADD_PROPERTY_TYPE(Length1, (5000.0), locationgroup, App::Prop_None, "The length along one axis");
    ADD_PROPERTY_TYPE(Length2, (15000.0), locationgroup, App::Prop_None, "The length along other axis");

    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Grid_Points");

}


bool WLGridPoints::ComputeLocationCoordinateMatrixP3(const SeismicLabAPI::SeismicLabSimulationData& Data, mat &dLocCoord)
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


bool WLGridPoints::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	
	SeismicLabGui::GridPointsDialogEdit* dlg = new SeismicLabGui::GridPointsDialogEdit(CenterPoint, Spacing1, Spacing2, Length1, Length2, LocationPlan,Data.spatialDistribution);
    Gui::Control().showDialog(dlg);

	return true;
}
