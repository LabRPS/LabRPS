#include "PreCompiled.h"

#include <QString>
// SeaLab.cpp : Defines the initialization routines for the DLL.
//
#include <Mod/SeaLabAPI/App/RPSSeaLabpluginAPI.h>
#include <Base/Console.h>
#include "RPSQBladeMethods.h"

std::string strPluginName = "QBladePlugin";
bool stationarity = true;

PLUGIN_NAME("QBladePlugin");
RANDOM_PHENOMENON("Sea Surface");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds the sea surface simulation functionalities of QBlade to LabRPS");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace SeaLab;
using namespace SeaLabAPI;

/////////////////////QBlade simulation/////////////////
std::string objNameQbl_M = "QBlade Methods (CE_2.0.4_a)";
std::string objDescriptionQbl_M = "This feature allows the user to simulate sea surface as regular or irregular wave.";
std::string objTileQbl_M = "Linear Wave Theory";
std::string objLinkQbl_M = "https://docs.qblade.org/src/theory/environment/sea/linear_waves.html";
std::string objAuthorsQbl_M = "QBlade";
std::string objDateQbl_M = "15/06/2024";
std::string objVersionQbl_M = "1.0";

RPS_PLUGIN_FUNC IrpsSeLSimulationMethod* BuildQBladeMethods()
{
    return new CRPSQBladeMethods;
}

RPS_PLUGIN_FUNC void DestroyQBladeMethods(SeaLabAPI::IrpsSeLSimulationMethod* r)
{
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
     if (SeaLab::CRPSQBladeMethods::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSQBladeMethods::init();
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
    RegisterSimuMethod(objNameQbl_M, strPluginName, objDescriptionQbl_M, BuildQBladeMethods, DestroyQBladeMethods);

    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterSimuMethod(objNameQbl_M, strPluginName);
    
    return 1;
}




