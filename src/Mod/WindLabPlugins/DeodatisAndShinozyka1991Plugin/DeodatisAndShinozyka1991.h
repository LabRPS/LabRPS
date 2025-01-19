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


#ifndef DEODATISANDSHINOZUKA_PLUGIN_SIMUMETHOD_H
#define DEODATISANDSHINOZUKA_PLUGIN_SIMUMETHOD_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

namespace WindLabAPI { class WindLabSimulationData; }

namespace WindLab {

class CDeodatisAndShinozyka1991 : public WindLabAPI::IrpsWLSimuMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CDeodatisAndShinozyka1991);

public:
    CDeodatisAndShinozyka1991();

    ~CDeodatisAndShinozyka1991() {};

	bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

    bool Simulate(const WindLabAPI::WindLabSimulationData& Data, cube &dPhenomenon);

};

} // namespace App

#endif // WINDLAB_PLUGIN_SIMUMETHOD_H