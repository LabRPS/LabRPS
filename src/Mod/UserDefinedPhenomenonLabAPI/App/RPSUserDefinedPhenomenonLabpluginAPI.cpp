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

#include "PreCompiled.h"

#include "RPSUserDefinedPhenomenonLabpluginAPI.h"
#include "RPSUserDefinedPhenomenonLabAPI.h"

using namespace UserDefinedPhenomenonLabAPI;

const char * RPSUserDefinedPhenomenonLabPluginAPIInfo::getUserDefinedPhenomenonLabPluginAPIVersion()
{
	return "0.1";
}
 
void RegisterSimulationMethod(const std::string name, const std::string& pluginName, const std::string& description, SimulationMethodInitFunc init_cb, SimulationMethodFreeFunc free_cb)
{
	if (CrpsSimulationMethodFactory::GetTobeInstalledObjectsMap().find(name) == CrpsSimulationMethodFactory::GetTobeInstalledObjectsMap().end())
	{
		return;
	}

    CrpsSimulationMethodFactory::RegisterObject(name, pluginName, description, init_cb);
	(void)free_cb; 
 }

 void InitializeSimulationMethod(const std::string name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 {
    CrpsSimulationMethodFactory::InitializeObject(name, pluginName, publicationTitle, publicationLink, publicationAuthor, publicationDate, version, stationarity);
 }

 void UnregisterSimulationMethod(const std::string name, const std::string& pluginName)
 {
    CrpsSimulationMethodFactory::UnregisterObject(name, pluginName);
 }


 