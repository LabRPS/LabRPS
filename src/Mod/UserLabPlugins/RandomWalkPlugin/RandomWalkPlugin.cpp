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

#include <QString>
#include "RPSRandomWalk.h"

#include <Mod/UserLabAPI/App/RPSUserLabpluginAPI.h>
#include <Base/Console.h>

#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>

std::string strPluginName = "RandomWalkPlugin";
bool stationarity = true;

PLUGIN_NAME("RandomWalkPlugin");
RANDOM_PHENOMENON("User Defined Phenomenon");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin implements tools for the simulation of random walk.");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("21/12/2024");

using namespace UserLab;
using namespace UserLabAPI;

std::string objNameGoe_S = "Random Walk";
std::string objDescriptionGoe_S = "This feature simulates random walk with different options.";
std::string objTileGoe_S = "Random walk";
std::string objLinkGoe_S = "https://github.com/GrHalbgott/random-walk/tree/main?tab=readme-ov-file";
std::string objAuthorsGoe_S = "GrHalbgott";
std::string objDateGoe_S = "19/01/2025";
std::string objVersionGoe_S = "1.0";

RPS_PLUGIN_FUNC IrpsULSimulationMethod* BuildRPSRandomWalk()
{
    return new CRPSRandomWalk;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomWalk(IrpsULSimulationMethod* r) {
    delete r;
}


PLUGIN_INIT_TYPE()
{ 
    if (UserLab::CRPSRandomWalk::getClassTypeId() == Base::Type::badType()) {
        UserLab::CRPSRandomWalk::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeSimulationMethod(objNameGoe_S, strPluginName, objTileGoe_S, objLinkGoe_S, objAuthorsGoe_S, objDateGoe_S, objVersionGoe_S, stationarity); 
    return 1;
}


INSTALL_PLUGIN()
{
    RegisterSimulationMethod(objNameGoe_S, strPluginName, objDescriptionGoe_S, BuildRPSRandomWalk, DestroyRPSRandomWalk);
    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterSimulationMethod(objNameGoe_S, strPluginName);
    return 1;
}




