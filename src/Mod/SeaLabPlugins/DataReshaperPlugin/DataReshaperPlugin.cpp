#include "PreCompiled.h"

#include <QString>
// SeaLab.cpp : Defines the initialization routines for the DLL.
//
#include "DataReshaper.h"
#include <Mod/SeaLabAPI/App/RPSSeaLabPluginAPI.h>

#include <Base/Console.h>

std::string strPluginName = "DataReshaperPlugin";
bool stationarity = true;

PLUGIN_NAME("DataReshaperPlugin");
RANDOM_PHENOMENON("Sea Surface");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS for the simulation of seismic ground motion");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("All");
API_VERSION("ALL");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace SeaLab;
using namespace SeaLabAPI;


std::string objNameDat_R = "Data Reshaper";
std::string objDescriptionDat_R = "This feature allows the user to pick the data at all positions at a given time instance and reshape them into grid.";
std::string objTileDat_R = "LabRPS";
std::string objLinkDat_R = "https://wiki.labrps.com";
std::string objAuthorsDat_R = "LabRPS";
std::string objDateDat_R = "29/12/2024";
std::string objVersionDat_R = "1.0";

RPS_PLUGIN_FUNC IrpsSeLTableTool* BuildDataReshaper()
{
    return new DataReshaper;
}

RPS_PLUGIN_FUNC void DestroyDataReshaper(IrpsSeLTableTool* r) {
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
    if (SeaLab::DataReshaper::getClassTypeId() == Base::Type::badType()) {
        SeaLab::DataReshaper::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeTableTool(objNameDat_R, strPluginName, objTileDat_R, objLinkDat_R, objAuthorsDat_R, objDateDat_R, objVersionDat_R, stationarity);

    return 1;
}


INSTALL_PLUGIN()
{
    RegisterTableTool(objNameDat_R, strPluginName, objDescriptionDat_R, BuildDataReshaper, DestroyDataReshaper);
    
    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterTableTool(objNameDat_R, strPluginName);

    return 1;
}




