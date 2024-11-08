//
#include "DesignResponseSpectrum.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabpluginAPI.h>

std::string strPluginName = "DesignResponseSpectrumPlugin";

using namespace SeismicLab;
using namespace SeismicLabAPI;

PLUGIN_NAME("DesignResponseSpectrumPlugin");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin allows the user to check the probability density function of the simulated wind velocity.");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("03/12/2022");


RPS_PLUGIN_FUNC IrpsSLTableTool* BuildDesignResponseSpectrum()
{
    return new DesignResponseSpectrum;
}


RPS_PLUGIN_FUNC void DestroyDesignResponseSpectrum(IrpsSLTableTool* r) {
	delete r;
}

std::string objName = "Design Response Spectrum";
std::string objDescription = "This object allows the user to compute the response acceleration spectrum of various design codes.";
std::string objTile = "RPS";
std::string objLink = "RPS";
std::string objAuthors = "Kfdani";
std::string objDate = "June 1997";
std::string objVersion = "1.00";
bool stationarity = true;

PLUGIN_INIT_TYPE()
{
    if (SeismicLab::DesignResponseSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::DesignResponseSpectrum::init();
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
                       BuildDesignResponseSpectrum,
                       DestroyDesignResponseSpectrum);

	return 1;
}

UNINSTALL_PLUGIN()
{

    UnregisterTableTool(objName, strPluginName);

	return 1;
}


