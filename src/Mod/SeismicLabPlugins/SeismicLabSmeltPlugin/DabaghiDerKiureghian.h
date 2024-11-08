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


#ifndef SMELT_SL_PLUGIN_SIMUMETHOD_2_H
#define SMELT_SL_PLUGIN_SIMUMETHOD_2_H

#include <Mod/SeismicLabAPI/App/IrpsSLSimulationMethod.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimuData; }

namespace SeismicLab {

class DabaghiDerKiureghian: public SeismicLabAPI::IrpsSLSimulationMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::DabaghiDerKiureghian);

public:
    DabaghiDerKiureghian();

    ~DabaghiDerKiureghian(){};

	//Initial setting
    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

	// The simulation function 
    bool Simulate(const SeismicLabAPI::SeismicLabSimulationData& Data, mat& dVelocityArray);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const SeismicLabAPI::SeismicLabSimulationData& Data, QString &strFileName);

     void onChanged(const App::Property* prop) override;

    App::PropertyEnumeration FaultingType;
    App::PropertyEnumeration SimulationType;
    App::PropertyFloat MomentMagnitude;
    App::PropertyLength DephToRupture;
    App::PropertyLength RuptureDistance;
    App::PropertySpeed ShearVelocity30;
    App::PropertyLength DirectivityParameter;
    App::PropertyAngle DirectivityAnge;
    App::PropertyInteger SimulationNumber;
    App::PropertyInteger RealizationNumber;
    App::PropertyBool Truncate;
    App::PropertyInteger SeedNumber;
    App::PropertyInteger EventIndex;
    App::PropertyString EventName;
};

} // namespace App

#endif // SMELT_SL_PLUGIN_SIMUMETHOD_H