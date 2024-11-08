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

//#include "PreCompiled.h"

#include <QString>
#include "WittigSinhaEqualFloors.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>

std::string strPluginName = "WindLabSmeltPlugin";
bool stationarity = true;

PLUGIN_NAME("WindLabSmeltPlugin");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds smelt functionalities to LabRPS for the simulation of wind velocity");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace WindLab;
using namespace WindLabAPI;

std::string objNameWit_S = "Wittig Sinha Equal Floors";
std::string objDescriptionWit_S = "Stochastic model for generating wind loads using discrete frequency functions with Cholesky decomposition and FFTs, as described in Wittig & Sinha (1975), Simulation of multicorrelated random processes using the FFT algorithm";
std::string objTileWit_S = "Simulation of multicorrelated random processes using the FFT algorithm";
std::string objLinkWit_S = "https://doi.org/10.1121/1.380702";
std::string objAuthorsWit_S = "Wittig & Sinha (1975)";
std::string objDateWit_S = "15/06/2024";
std::string objVersionWit_S = "1.0";
RPS_PLUGIN_FUNC IrpsWLSimuMethod* BuildWittigSinhaEqualFloors()
{
  return new WittigSinhaEqualFloors;
}

RPS_PLUGIN_FUNC void DestroyWittigSinhaEqualFloors(IrpsWLSimuMethod* r)
{
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
    if (WindLab::WittigSinhaEqualFloors::getClassTypeId() == Base::Type::badType()) {
        WindLab::WittigSinhaEqualFloors::init();
    }
    
    return 1;
}

PLUGIN_INIT()
{
   InitializeSimuMethod(objNameWit_S, strPluginName, objTileWit_S, objLinkWit_S, objAuthorsWit_S, objDateWit_S, objVersionWit_S, stationarity);
     
    return 1;
}


INSTALL_PLUGIN()
{
    RegisterSimuMethod(objNameWit_S, strPluginName, objDescriptionWit_S, BuildWittigSinhaEqualFloors, DestroyWittigSinhaEqualFloors);
 
    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterSimuMethod(objNameWit_S, strPluginName);
    return 1;
}




