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

#ifndef WINDLAB_PLUGIN_TURBULENCEINTENSITYASCE98_H
#define WINDLAB_PLUGIN_TURBULENCEINTENSITYASCE98_H

#include <Mod/WindLabAPI/App/IrpsWLTurbulenceIntensity.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimulationData; }

namespace WindLab {

class RPSTurbulenceIntensityASCE798: public WindLabAPI::IrpsWLTurbulenceIntensity
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::RPSTurbulenceIntensityASCE798);

public:
    RPSTurbulenceIntensityASCE798();

    ~RPSTurbulenceIntensityASCE798() {};

    bool ComputeTurbulenceIntensityValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    bool ComputeTurbulenceIntensityVectorP(const WindLabAPI::WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeTurbulenceIntensityVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

   bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:
   App::PropertyFloat TenMetersHighTurbulenceIntensity;

};

} // namespace App

#endif // WINDLAB_PLUGIN_KRENKCOHERENCE_H