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

#ifndef windSimulationMethodWWYang1997_PLUGIN_CWWYang1997_H
#define windSimulationMethodWWYang1997_PLUGIN_CWWYang1997_H

#include <Mod/WindLabAPI/App/IrpsWLSimuMethod.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CWWYang1997 : public WindLabAPI::IrpsWLSimuMethod
{
public:
	//Initial setting
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	// The simulation function 
    bool Simulate(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName);

};

} // namespace App

#endif // windSimulationMethodWWYang1997_PLUGIN_CWWYang1997_H