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
using namespace SeaLab;

////////////////////////Horizontal distribution///////////////////////////////////////////////

PROPERTY_SOURCE(SeaLab::WLGridPoints, SeaLabAPI::SeaLabFeatureLocationDistribution)

WLGridPoints::WLGridPoints()
{
    static const char* locationgroup = "Distribution";
    ADD_PROPERTY_TYPE(GridStartingPoint, (Base::Vector3d(0,0,0)), locationgroup, App::Prop_None, "the starting point of the grid.");
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeaLab#Grid_Points");

}


bool WLGridPoints::ComputeLocationCoordinateMatrixP3(const SeaLabAPI::SeaLabSimulationData& Data, mat &dLocCoord)
{
    int pointNumberX = Data.numberOfGridPointsAlongX.getValue();
    int pointNumberY = Data.numberOfGridPointsAlongY.getValue();

    int nPoints = pointNumberX * pointNumberY;
    if (nPoints != Data.numberOfSpatialPosition.getValue())
    {
        Base::Console().Error("The computation fails. The number of simulation points should be %d.\n", nPoints);
        return false;
    }

    std::vector<Base::Vector3d> points;

    for (int loop1 = 0; loop1 < pointNumberX; loop1++){
       for (int loop2 = 0; loop2 < pointNumberY; loop2++){
         Base::Vector3d position = Base::Vector3d(GridStartingPoint.getValue().x + loop1 * Data.gridSpacingAlongX.getQuantityValue().getValueAs(Base::Quantity::Metre), GridStartingPoint.getValue().y + loop2 * Data.gridSpacingAlongY.getQuantityValue().getValueAs(Base::Quantity::Metre), GridStartingPoint.getValue().z);
         points.push_back(position);
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


bool WLGridPoints::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
	
	SeaLabGui::GridPointsDialogEdit* dlg = new SeaLabGui::GridPointsDialogEdit(GridStartingPoint, Data.spatialDistribution);
    Gui::Control().showDialog(dlg);

	return true;
}
