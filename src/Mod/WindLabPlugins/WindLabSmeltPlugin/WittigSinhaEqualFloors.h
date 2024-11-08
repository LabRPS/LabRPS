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


#ifndef SMELT_PLUGIN_SIMUMETHOD_WL_H
#define SMELT_PLUGIN_SIMUMETHOD_WL_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class WittigSinhaEqualFloors : public WindLabAPI::IrpsWLSimuMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::WittigSinhaEqualFloors);

public:
    WittigSinhaEqualFloors();

    ~WittigSinhaEqualFloors(){};

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// The simulation function 
    bool Simulate(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName);

    void onChanged(const App::Property* prop) override;

    App::PropertyEnumeration ExposureCategory;
    App::PropertySpeed GustSpeed;
    App::PropertyLength Height;
    App::PropertyInteger SeedNumber;
    App::PropertyInteger EventIndex;
    App::PropertyString EventName;
};

} // namespace App

#endif// SMELT_PLUGIN_SIMUMETHOD_WL_H