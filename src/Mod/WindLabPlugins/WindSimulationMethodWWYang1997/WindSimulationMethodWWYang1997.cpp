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

#include "WWYang1997.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>

std::string strPluginName = "WindSimulationMethodWWYang1997";

using namespace WindLab;
using namespace WindLabAPI;

PLUGIN_NAME("WindSimulationMethodWWYang1997");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin implements the wind velocity simulation method by Yang (An efficient wind field simulation technique for bridges by W. W. Yang et al, 1997)");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("12/10/2022");

RPS_PLUGIN_FUNC IrpsWLSimuMethod *BuildWWYang1997()
{
	return new CWWYang1997;
}

RPS_PLUGIN_FUNC void DestroyWWYang1997(IrpsWLSimuMethod *r)
{
	delete r;
}

std::string objName = "W. W. Yang et al, 1997";
std::string objDescription = "This plugin implements the wind velocity simulation method by Yang (An efficient wind field simulation technique for bridges by W. W. Yang et al, 1997)";
std::string objTile = "An efficient wind field simulation technique for bridges";
std::string objLink = "https://doi.org/10.1016/S0167-6105(97)00111-6";
std::string objAuthors = "W.W. Yang, T.Y.P. Chang, C.C. Chang";
std::string objDate = "June 1997";
std::string objVersion = "1.00";

bool stationarity = true;

PLUGIN_INIT_TYPE()
{
    if (WindLab::CWWYang1997::getClassTypeId() == Base::Type::badType()) {
        WindLab::CWWYang1997::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeSimuMethod(objName,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,
                         stationarity);

	return 1;
}


INSTALL_PLUGIN()
{
    RegisterSimuMethod(objName,
                       strPluginName,
                       objDescription,
                       BuildWWYang1997,
                       DestroyWWYang1997);

	return 1;
}

UNINSTALL_PLUGIN()
{

    UnregisterSimuMethod(objName, strPluginName);

	return 1;
}


