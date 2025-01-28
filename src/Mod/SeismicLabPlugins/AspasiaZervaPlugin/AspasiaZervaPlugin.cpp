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
#include "RPSAspasiaZerva.h"

#include <Mod/SeismicLabAPI/App/RPSSeismicLabpluginAPI.h>
#include <Base/Console.h>

#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>

std::string strPluginName = "AspasiaZervaPlugin";
bool stationarity = true;

PLUGIN_NAME("AspasiaZervaPlugin");
RANDOM_PHENOMENON("Seismic Ground Motion");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin simulates seismic ground motion according to the approach proposed by Aspasia Zerva (1992)");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("21/12/2024");

using namespace SeismicLab;
using namespace SeismicLabAPI;

std::string objNameAsp_Z = "Aspasia Zerva 1992";
std::string objDescriptionAsp_Z = "This feature simulates seismic ground motion according to equation (1) by ASPASIA ZERVA.";
std::string objTileAsp_Z = "Seismic ground motion simulations from a class of spatial variability models";
std::string objLinkAsp_Z = "https://doi.org/10.1002/eqe.4290210406";
std::string objAuthorsAsp_Z = "Aspasia Zerva";
std::string objDateAsp_Z = "31/12/2024";
std::string objVersionAsp_Z = "1.0";

RPS_PLUGIN_FUNC IrpsSLSimulationMethod* BuildRPSAspasiaZerva()
{
    return new CRPSAspasiaZerva;
}

RPS_PLUGIN_FUNC void DestroyRPSAspasiaZerva(IrpsSLSimulationMethod* r) {
    delete r;
}


PLUGIN_INIT_TYPE()
{ 
    if (SeismicLab::CRPSAspasiaZerva::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSAspasiaZerva::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeSimuMethod(objNameAsp_Z, strPluginName, objTileAsp_Z, objLinkAsp_Z, objAuthorsAsp_Z, objDateAsp_Z, objVersionAsp_Z, !stationarity); 
    return 1;
}


INSTALL_PLUGIN()
{
    RegisterSimuMethod(objNameAsp_Z, strPluginName, objDescriptionAsp_Z, BuildRPSAspasiaZerva, DestroyRPSAspasiaZerva);
    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterSimuMethod(objNameAsp_Z, strPluginName);
    return 1;
}




