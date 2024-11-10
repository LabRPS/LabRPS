//
#include "SigmaSpectra.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabpluginAPI.h>

std::string strPluginName = "SigmaSpectraPlugin";

using namespace SeismicLab;
using namespace SeismicLabAPI;

PLUGIN_NAME("SigmaSpectraPlugin");
RANDOM_PHENOMENON("Seismic Ground Motion");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin allows the user to load and display ground motion acceleration from files.");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("03/12/2022");


RPS_PLUGIN_FUNC IrpsSLTableTool* BuildSigmaSpectra()
{
    return new SigmaSpectra;
}


RPS_PLUGIN_FUNC void DestroySigmaSpectra(IrpsSLTableTool* r) {
	delete r;
}

std::string objName = "SigmaSpectra";
std::string objDescription = "This plugin allow the user to explore response accelerations from files.";
std::string objTile = "A semi-automated procedure for selecting and scaling recorded earthquake motions for dynamic analysis";
std::string objLink = "https://doi.org/10.1193/1.2985772";
std::string objAuthors = "Kottke, Albert and Rathje, Ellen M";
std::string objDate = "10/11/2024";
std::string objVersion = "1.00";
bool stationarity = true;

PLUGIN_INIT_TYPE()
{
    if (SeismicLab::SigmaSpectra::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::SigmaSpectra::init();
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
                       BuildSigmaSpectra,
                       DestroySigmaSpectra);

	return 1;
}

UNINSTALL_PLUGIN()
{

    UnregisterTableTool(objName, strPluginName);

	return 1;
}


