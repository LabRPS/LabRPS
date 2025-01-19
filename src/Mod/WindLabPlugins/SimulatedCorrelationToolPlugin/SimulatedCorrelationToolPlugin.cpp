//
#include "SimulatedCorrelationTool.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>

std::string strPluginName = "SimulatedCorrelationToolPlugin";

using namespace WindLab;
using namespace WindLabAPI;

PLUGIN_NAME("SimulatedCorrelationToolPlugin");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin allows the user to the simulated coorelation from the simulated wind velocity.");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("15/01/2025");

RPS_PLUGIN_FUNC IrpsWLTableTool *BuildSimulatedCorrelationTool()
{
    return new SimulatedCorrelationTool;
}

RPS_PLUGIN_FUNC void DestroySimulatedCorrelationTool(IrpsWLTableTool *r)
{
	delete r;
}

std::string objName = "Simulated Correlation Tool";
std::string objDescription = "This object allows the user to the simulated coorelation from the simulated wind velocity";
std::string objTile = "LabRPS";
std::string objLink = "RPS";
std::string objAuthors = "LabRPS Team";
std::string objDate = "15/01/2025";
std::string objVersion = "1.00";
bool stationarity = true;


PLUGIN_INIT_TYPE()
{
    if (WindLab::SimulatedCorrelationTool::getClassTypeId() == Base::Type::badType()) {
        WindLab::SimulatedCorrelationTool::init();
    }

    return 1;
}

PLUGIN_INIT()
{
    InitializeTableTool(objName,
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
    RegisterTableTool(objName,
                       strPluginName,
                       objDescription,
                       BuildSimulatedCorrelationTool,
                       DestroySimulatedCorrelationTool);

	return 1;
}

UNINSTALL_PLUGIN()
{

    UnregisterTableTool(objName, strPluginName);

	return 1;
}


