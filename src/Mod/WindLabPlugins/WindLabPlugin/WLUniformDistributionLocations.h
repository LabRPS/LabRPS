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

#ifndef WINDLAB_PLUGIN_UNIFSD_H
#define WINDLAB_PLUGIN_UNIFSD_H

#include <App/PropertyGeo.h>
#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>
#include <App/PropertyUnits.h>

namespace WindLab {

class WLUniformDistributionLocations : public WindLabAPI::IrpsWLLocationDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::WLUniformDistributionLocations);

public:
	WLUniformDistributionLocations();
	
	~WLUniformDistributionLocations() {};

	bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimulationData& Data, mat &dLocCoord);

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

	// the first point the distribution will start from
    App::PropertyPosition FirstPoint;

	// the even spacing between the points
    App::PropertyLength Spacing;

	// the height at which the points are distributed
    App::PropertyEnumeration Direction;
};

} // namespace App

#endif // WINDLAB_PLUGIN_HORIZONTALUNIFSD_H
