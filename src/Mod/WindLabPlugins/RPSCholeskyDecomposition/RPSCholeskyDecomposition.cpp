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

#include "CholeskyDecomposition.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>

std::string strPluginName = "RPSCholeskyDecomposition";

using namespace WindLab;
using namespace WindLabAPI; 

PLUGIN_NAME("RPSCholeskyDecomposition");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin provides the tool for the Cholesky decomposition of a matrix.");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("26/10/2022");

RPS_PLUGIN_FUNC IrpsWLMatrixTool *BuildRPSCholeskyDecomposition()
{
    return new CholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyRPSCholeskyDecomposition(IrpsWLMatrixTool *r)
{
    delete r;
}

std::string objName = "RPS Cholesky Decomposition";
std::string objDescription = "This feature allows the user to decompose a power spectral density matrix as described in Dedatis (1996).";
std::string objTile = "LabRPS";
std::string objLink = "https://wiki.labrps.com";
std::string objAuthors = "LabRPS";
std::string objDate = "15/06/2024";
std::string objVersion = "1.00";
bool stationarity = true;

PLUGIN_INIT_TYPE()
{
    if (WindLab::CholeskyDecomposition::getClassTypeId() == Base::Type::badType()) {
        WindLab::CholeskyDecomposition::init();
    }
    
    return 1;
}

PLUGIN_INIT()
{
    InitializeMatrixTool(objName,
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
    RegisterMatrixTool(objName,
                       strPluginName,
                       objDescription,
                       BuildRPSCholeskyDecomposition,
                       DestroyRPSCholeskyDecomposition);

    return 1;
}

UNINSTALL_PLUGIN()
{

    UnregisterMatrixTool(objName, strPluginName);

    return 1;
}


