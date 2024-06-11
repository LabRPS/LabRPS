// windSimulationMethodWWYang1997.cpp : Defines the initialization routines for the DLL.
//
#include "CholeskyDecomposition.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>

std::string strPluginName = "RPSCholeskyDecomposition";

using namespace WindLab;
using namespace WindLabAPI; 

PLUGIN_DISPLAY_NAME("RPSCholeskyDecomposition");
PLUGIN_SYSTEM_NAME("RPSCholeskyDecomposition");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin provides the tool for the Cholesky decomposition of a matrix.");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.001");
API_VERSION("0.001");
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
std::string objDescription = "This object provides the tool for the Cholesky decomposition of a matrix.";
std::string objTile = "RPS";
std::string objLink = "RPS";
std::string objAuthors = "Kfdani";
std::string objDate = "June 1997";
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


