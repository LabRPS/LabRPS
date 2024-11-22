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

	void onChanged(const App::Property* prop) override;

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

	// the total number of points in the grid
    App::PropertyInteger NumberOfPoints;
};

} // namespace App

#endif // WINDLAB_PLUGIN_GRIDPOINTS_H
