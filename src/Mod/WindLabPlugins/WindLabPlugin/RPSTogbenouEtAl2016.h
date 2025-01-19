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

#ifndef WINDLAB_PLUGIN_SIMUMETHOD_TOGBENOU_KOFFI_2016_IND_H
#define WINDLAB_PLUGIN_SIMUMETHOD_TOGBENOU_KOFFI_2016_IND_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimulationData; }

namespace WindLab {

class CRPSTogbenouEtAl2016 : public WindLabAPI::IrpsWLSimuMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSTogbenouEtAl2016);

public:
	CRPSTogbenouEtAl2016();

	~CRPSTogbenouEtAl2016() {};

	bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

    bool Simulate(const WindLabAPI::WindLabSimulationData& Data, cube &dPhenomenon);

	void onChanged(const App::Property* prop);

public:

	App::PropertyInteger NumberOfLocation;
	App::PropertyInteger NumberOfFrequencies;
    App::PropertyLength LocationSpacing;
    App::PropertyFloat CoherenceDecayCoefficient;
	App::PropertyFrequency UpperCutOffFrequency;
	App::PropertyInteger NumberOfTimeIncrements;
    App::PropertyLength RoughnessLength;
	App::PropertyLength StartingElevation;
    App::PropertyInteger ReferencePointIndex;
};

} // namespace WindLab

#endif // #ifndef WINDLAB_PLUGIN_SIMUMETHOD_YANG_1997_IND_H
