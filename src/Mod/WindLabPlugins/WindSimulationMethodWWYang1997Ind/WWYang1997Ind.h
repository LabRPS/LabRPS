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

#ifndef windSimulationMethodWWYang1997Ind_PLUGIN_CWWYang1997Ind_H
#define windSimulationMethodWWYang1997Ind_PLUGIN_CWWYang1997Ind_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

namespace WindLabAPI { class WindLabSimulationData; }

namespace WindLab {

class CWWYang1997Ind : public WindLabAPI::IrpsWLSimuMethod
{
public:
		CWWYang1997Ind();

		~CWWYang1997Ind() {};

	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

	// The simulation function 
    bool Simulate(const WindLabAPI::WindLabSimulationData& Data, mat &dVelocityArray);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const WindLabAPI::WindLabSimulationData& Data, QString &strFileName);

private:
int numberOfLocation;
int numberOfFrequencies;
double locationHeight;
double locationSpacing;
double meanSpeed;
double shearVelocity;
double upperCutoffFrequency;
int numberOfTimeIncrements;

};

} // namespace App

#endif // windSimulationMethodWWYang1997Ind_PLUGIN_CWWYang1997Ind_H