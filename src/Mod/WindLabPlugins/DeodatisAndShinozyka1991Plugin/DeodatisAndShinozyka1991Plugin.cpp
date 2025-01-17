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

#include "DeodatisAndShinozyka1991.h"

#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>
#include <Base/Console.h>

#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>

std::string strPluginName = "DeodatisAndShinozyka1991Plugin";
bool stationarity = true;

PLUGIN_NAME("DeodatisAndShinozyka1991Plugin");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin simulates random wind velocity according to the conventional spectral representation method proposed by Masanoby Shinozyka and George Deodatis (1991)");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("13/01/2025");

using namespace WindLab;
using namespace WindLabAPI;

std::string objNameDeo_S = "Shinozyka and Deodatis (1991)";
std::string objDescriptionDeo_S = "This feature allows the user to simulates random wind velocity according to the conventional spectral representation method proposed by Masanoby Shinozyka and George Deodatis (1991)";
std::string objTileDeo_S = "“Simulation of stochastic processes by spectral representation";
std::string objLinkDeo_S = "https://doi.org/10.1115/1.3119501";
std::string objAuthorsDeo_S = "Masanoby Shinozyka and George Deodatis";
std::string objDateDeo_S = "13/01/2025";
std::string objVersionDeo_S = "1.0";

RPS_PLUGIN_FUNC IrpsWLSimuMethod* BuildDeodatisAndShinozyka1991()
{
    return new CDeodatisAndShinozyka1991;
}

RPS_PLUGIN_FUNC void DestroyDeodatisAndShinozyka1991(IrpsWLSimuMethod* r)
{
    delete r;
}


PLUGIN_INIT_TYPE()
{ 
    if (WindLab::CDeodatisAndShinozyka1991::getClassTypeId() == Base::Type::badType()) {
        WindLab::CDeodatisAndShinozyka1991::init();
    }

    return 1;
}

PLUGIN_INIT()
{
    InitializeSimuMethod(objNameDeo_S, strPluginName, objTileDeo_S, objLinkDeo_S, objAuthorsDeo_S, objDateDeo_S, objVersionDeo_S, stationarity);    
    return 1;
}


INSTALL_PLUGIN()
{
    RegisterSimuMethod(objNameDeo_S, strPluginName, objDescriptionDeo_S, BuildDeodatisAndShinozyka1991, DestroyDeodatisAndShinozyka1991);
    return 1;
}

UNINSTALL_PLUGIN()
{
   
    UnregisterSimuMethod(objNameDeo_S, strPluginName);
    return 1;
}




