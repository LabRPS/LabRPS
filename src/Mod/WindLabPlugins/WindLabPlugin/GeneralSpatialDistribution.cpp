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

#include "GeneralSpatialDistribution.h"
#include <Mod/WindLabAPI/App/WindLabSimulationData.h>

using namespace std;
using namespace WindLab;
using namespace WindLabAPI;

//spacing between two adjacent points
PROPERTY_SOURCE(WindLab::GeneralSpatialDistribution, WindLabAPI::WindLabFeatureLocationDistribution)

GeneralSpatialDistribution::GeneralSpatialDistribution()
{
    static const char* Points = "Locations";

    ADD_PROPERTY_TYPE(Locations, (Base::Vector3d()), Points, App::Prop_None,"The list of locations");
    this->OutputUnitString.setValue("m");
}

bool GeneralSpatialDistribution::ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimulationData &Data, mat &dLocCoord)
{
    const std::vector<Base::Vector3d> nodes = Locations.getValues();
    int j = 0;
    for (std::vector<Base::Vector3d>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        dLocCoord(j, 0) = j + 1;
        dLocCoord(j, 1) = it->x;
        dLocCoord(j, 2) = it->y;
        dLocCoord(j, 3) = it->z;

        j++;
    }
	return true;
}


bool GeneralSpatialDistribution::OnInitialSetting(const WindLabAPI::WindLabSimulationData &Data)
{
	return true;
}
