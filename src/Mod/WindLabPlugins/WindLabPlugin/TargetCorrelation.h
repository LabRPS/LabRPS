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

#ifndef correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H
#define correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H

#include <Mod/WindLabAPI/App/IrpsWLTableTool.h>
#include <App/PropertyUnits.h>


/// pi
static constexpr double pi = 3.14159265358979323846264338327950288;

namespace WindLabAPI { class WindLabSimulationData; }

namespace WindLab {

	class TargetCorrelation: public WindLabAPI::IrpsWLTableTool
	{
        PROPERTY_HEADER_WITH_OVERRIDE(WindLab::TargetCorrelation);

	public:
		TargetCorrelation();

		~TargetCorrelation() {};

		bool TableToolCompute(const WindLabAPI::WindLabSimulationData& Data, const mat& inputTable, mat& outputTable);

		bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

		bool ComputeTargetCorrelation(const WindLabAPI::WindLabSimulationData& Data, std::vector<double>& tau, std::vector<double>& corr);

public:
        App::PropertyInteger fftPointsNumber;

	};

} // namespace App

#endif // correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H