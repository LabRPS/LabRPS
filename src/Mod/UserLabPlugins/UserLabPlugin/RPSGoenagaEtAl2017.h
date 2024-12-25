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

#ifndef USERLAB_PLUGIN_SIMUMETHOD_GOENAGA_2017_H
#define USERLAB_PLUGIN_SIMUMETHOD_GOENAGA_2017_H

#include <Mod/UserLabAPI/App/IrpsULSimulationMethod.h>
#include <App/PropertyUnits.h>

namespace UserLabAPI { class UserLabSimulationData; }

namespace UserLab {

class CRPSGoenagaEtAl2017: public UserLabAPI::IrpsULSimulationMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(UserLab::CRPSGoenagaEtAl2017);

public:
	CRPSGoenagaEtAl2017();

	~CRPSGoenagaEtAl2017() {};

	bool OnInitialSetting(const UserLabAPI::UserLabSimulationData& Data);

    bool Simulate(const UserLabAPI::UserLabSimulationData& Data, cube &dPhenomenon);

    bool SimulateInLargeScaleMode(const UserLabAPI::UserLabSimulationData& Data, QString &strFileName);

    const char* GetPhenomenonName();

public:
    App::PropertyFloat ReferenceWaveNumber; 
    App::PropertyFloat ReferenceSpectrum;
    App::PropertyFloat PavementWavinessIndicator;
};

} // namespace UserLab

#endif // #ifndef USERLAB_PLUGIN_SIMUMETHOD_GOENAGA_2017_H
