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
#include "QbladeMethods.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>

std::string strPluginName = "WindLabQBladePlugin";
bool stationarity = true;

PLUGIN_NAME("WindLabQBladePlugin");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds Qblade functionalities to LabRPS for the simulation of wind velocity");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace WindLab;
using namespace WindLabAPI;

std::string objNameQbl_M = "QBlade Wind Simulation Methods (CE_2.0.4_a)";
std::string objDescriptionQbl_M = "Wind velocity simulation by QBlade";
std::string objTileQbl_M = "Wind";
std::string objLinkQbl_M = "https://docs.qblade.org/src/theory/environment/wind/wind.html";
std::string objAuthorsQbl_M = "QBlade";
std::string objDateQbl_M = "15/06/2024";
std::string objVersionQbl_M = "1.0";
RPS_PLUGIN_FUNC IrpsWLSimuMethod* BuildQbladeMethods()
{
  return new QbladeMethods;
}

RPS_PLUGIN_FUNC void DestroyQbladeMethods(IrpsWLSimuMethod* r)
{
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
    if (WindLab::QbladeMethods::getClassTypeId() == Base::Type::badType()) {
        WindLab::QbladeMethods::init();
    }
    
    return 1;
}

PLUGIN_INIT()
{
   InitializeSimuMethod(objNameQbl_M, strPluginName, objTileQbl_M, objLinkQbl_M, objAuthorsQbl_M, objDateQbl_M, objVersionQbl_M, stationarity);
     
    return 1;
}


INSTALL_PLUGIN()
{
    RegisterSimuMethod(objNameQbl_M, strPluginName, objDescriptionQbl_M, BuildQbladeMethods, DestroyQbladeMethods);
 
    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterSimuMethod(objNameQbl_M, strPluginName);
    return 1;
}




