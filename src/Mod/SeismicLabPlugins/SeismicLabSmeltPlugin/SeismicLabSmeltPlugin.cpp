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
#include "VlachosEtAl.h"
#include "DabaghiDerKiureghian.h"

#include <Mod/SeismicLabAPI/App/RPSSeismicLabpluginAPI.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>

std::string strPluginName = "SeismicLabSmeltPlugin";
bool stationarity = true;

PLUGIN_NAME("SeismicLabSmeltPlugin");
RANDOM_PHENOMENON("Seismic Ground Motion");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds smelt functionalities to LabRPS for the simulation of wind velocity");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace SeismicLab;
using namespace SeismicLabAPI;

std::string objNameVla_P = "Vlachos et al (2018)";
std::string objDescriptionVla_P = "Stochastic model for generating scenario specific ground motion time histories. This is based on the paper: Vlachos C., Papakonstantinou K.G., & Deodatis G. (2018). Predictive model for site specific simulation of ground motions based on earthquake scenarios.";
std::string objTileVla_P = "Predictive model for site specific simulation of ground motions based on earthquake scenarios";
std::string objLinkVla_P = "https://doi.org/10.1002/eqe.2948";
std::string objAuthorsVla_P = "Christos Vlachos, Konstantinos G. Papakonstantinou, George Deodatis (2018)";
std::string objDateVla_P = "15/06/2024";
std::string objVersionVla_P = "1.0";

RPS_PLUGIN_FUNC IrpsSLSimulationMethod* BuildWittigSinhaEqualFloors()
{
  return new VlachosEtAl;
}

RPS_PLUGIN_FUNC void DestroyWittigSinhaEqualFloors(IrpsSLSimulationMethod* r)
{
    delete r;
}

std::string objNameDAn_K = "Dabaghi and Der Kiureghian (2014, 2017, 2018)";
std::string objDescriptionDAn_K = "Stochastic model for simulating near-fault ground motions. Based on the following references: 1. Dabaghi and Der Kiureghian (2014 PEER report) Stochastic Modeling and Simulation of Near-Fault Ground Motions for Performance-Based Earthquake Engineering, 2. Dabaghi and Der Kiureghian (2017 EESD) Stochastic model for simulation of NF GMs, 3. Dabaghi and Der Kiureghian (2018 EESD) Simulation of orthogonal horizontal components of near-fault ground motion for specified EQ source and site characteristics";
std::string objTileDAn_K = "Simulation of orthogonal horizontal components of near-fault ground motion for specified EQ source and site characteristics";
std::string objLinkDAn_K = " https://doi.org/10.1002/eqe.3021";
std::string objAuthorsDAn_K = "Mayssa Dabaghi, Armen Der Kiureghian (2014, 2017, 2018)";
std::string objDateDAn_K = "15/06/2024";
std::string objVersionDAn_K = "1.0";

RPS_PLUGIN_FUNC IrpsSLSimulationMethod* BuildDabaghiDerKiureghian()
{
    return new DabaghiDerKiureghian;
}

RPS_PLUGIN_FUNC void DestroyDabaghiDerKiureghian(IrpsSLSimulationMethod* r)
{
    delete r;
}


PLUGIN_INIT_TYPE()
{ 
    if (SeismicLab::VlachosEtAl::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::VlachosEtAl::init();
    }

    if (SeismicLab::DabaghiDerKiureghian::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::DabaghiDerKiureghian::init();
    }
    
    return 1;
}

PLUGIN_INIT()
{
   InitializeSimuMethod(objNameVla_P, strPluginName, objTileVla_P, objLinkVla_P, objAuthorsVla_P, objDateVla_P, objVersionVla_P, stationarity);
   InitializeSimuMethod(objNameDAn_K, strPluginName, objTileDAn_K, objLinkDAn_K, objAuthorsDAn_K, objDateDAn_K, objVersionDAn_K, stationarity);

    return 1;
}


INSTALL_PLUGIN()
{
    RegisterSimuMethod(objNameVla_P, strPluginName, objDescriptionVla_P, BuildWittigSinhaEqualFloors, DestroyWittigSinhaEqualFloors);
    RegisterSimuMethod(objNameDAn_K, strPluginName, objDescriptionDAn_K, BuildDabaghiDerKiureghian, DestroyDabaghiDerKiureghian);

    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterSimuMethod(objNameVla_P, strPluginName);
    UnregisterSimuMethod(objNameDAn_K, strPluginName);

    return 1;
}




