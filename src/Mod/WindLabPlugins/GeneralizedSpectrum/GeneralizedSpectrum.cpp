//
#include "GeneralizedAlongWindKaimalSpectrum.h"
#include "GeneralizedAcrossWindKaimalSpectrum.h"
#include "GeneralizedVerticalWindKaimalSpectrum.h"
#include "GeneralizedAlongWindVonKarmanSpectrum.h"
#include "GeneralizedAcrossWindVonKarmanSpectrum.h"
#include "GeneralizedVerticalWindVonKarmanSpectrum.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>


std::string strPluginName = "GeneralizedSpectrum";

PLUGIN_DISPLAY_NAME("GeneralizedSpectrum");
PLUGIN_SYSTEM_NAME("GeneralizedSpectrum");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin implements the generalized spectrum models of Kaimal and von Karamn");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.001");
API_VERSION("0.001");
PLUGIN_RELEASE_DATE("03/12/2022");


std::string objTile = "Prediction of Atmospheric Turbulence Characteristics for Surface Boundary Layer Using Empirical Spectral Methods";
std::string objLink = "http://dx.doi.org/10.1590/0102-7786354008";
std::string objAuthors = "Yagya Dutta Dwivedi, Vasishta Bhargava Nukala , Satya Prasad Maddula, Kiran Nair";
std::string objDate = "29 September 2020";
std::string objVersion = "1.00";

using namespace WindLab;
using namespace WindLabAPI;

RPS_PLUGIN_FUNC IrpsWLXSpectrum *BuildGeneralizedAlongWindKaimalSpectrum()
{
    
    return new CRPSGeneralizedAlongWindKaimalSpectrum;
}

RPS_PLUGIN_FUNC void DestroyGeneralizedAlongWindKaimalSpectrum(IrpsWLXSpectrum *r)
{
    delete r;
}

std::string objName1 = "Generalized Along Wind Kaimal Spectrum";
std::string objDescription1 = "This object implements the generalized along wind Kaimal spectrum";

RPS_PLUGIN_FUNC IrpsWLYSpectrum *BuildGeneralizedAcrossWindKaimalSpectrum()
{
    return new CRPSGeneralizedAcrossWindKaimalSpectrum;
}

RPS_PLUGIN_FUNC void DestroyGeneralizedAcrossWindKaimalSpectrum(IrpsWLYSpectrum *r)
{
    delete r;
}

std::string objName2 = "Generalized Across Wind Kaimal Spectrum";
std::string objDescription2 = "This object implements the generalized across wind Kaimal spectrum";

RPS_PLUGIN_FUNC IrpsWLZSpectrum *BuildGeneralizedVerticalWindKaimalSpectrum()
{
    return new CRPSGeneralizedVerticalWindKaimalSpectrum;
}

RPS_PLUGIN_FUNC void DestroyGeneralizedVerticalWindKaimalSpectrum(IrpsWLZSpectrum *r)
{
    delete r;
}

std::string objName3 = "Generalized Vertical Wind Kaimal Spectrum";
std::string objDescription3 = "This object implements the generalized Vertical wind Kaimal spectrum";

RPS_PLUGIN_FUNC IrpsWLXSpectrum *BuildGeneralizedAlongWindVonKarmanSpectrum()
{
    return new CRPSGeneralizedAlongWindVonKarmanSpectrum;
}

RPS_PLUGIN_FUNC void DestroyGeneralizedAlongWindVonKarmanSpectrum(IrpsWLXSpectrum *r)
{
    delete r;
}

std::string objName4 = "Generalized Along Wind von Karman Spectrum";
std::string objDescription4 = "This object implements the generalized along wind von Karman spectrum";

RPS_PLUGIN_FUNC IrpsWLYSpectrum *BuildGeneralizedAcrossWindVonKarmanSpectrum()
{
    return new CRPSGeneralizedAcrossWindVonKarmanSpectrum;
}

RPS_PLUGIN_FUNC void DestroyGeneralizedAcrossWindVonKarmanSpectrum(IrpsWLYSpectrum *r)
{
    delete r;
}

std::string objName5 = "Generalized Across Wind von Karman Spectrum";
std::string objDescription5 = "This object implements the generalized across wind von Karman spectrum";

RPS_PLUGIN_FUNC IrpsWLZSpectrum *BuildGeneralizedVerticalWindVonKarmanSpectrum()
{
    return new CRPSGeneralizedVerticalWindVonKarmanSpectrum;
}

RPS_PLUGIN_FUNC void DestroyGeneralizedVerticalWindVonKarmanSpectrum(IrpsWLZSpectrum *r)
{
    delete r;
}

std::string objName6 = "Generalized Vertical Wind von Karman Spectrum";
std::string objDescription6 = "This object implements the generalized Vertical wind von Karman spectrum";
bool stationarity = true;

PLUGIN_INIT_TYPE()
{ 
    if (WindLab::CRPSGeneralizedAcrossWindKaimalSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSGeneralizedAcrossWindKaimalSpectrum::init();
    }
    if (WindLab::CRPSGeneralizedAlongWindKaimalSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSGeneralizedAlongWindKaimalSpectrum::init();
    }
    if (WindLab::CRPSGeneralizedVerticalWindKaimalSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSGeneralizedVerticalWindKaimalSpectrum::init();
    }
    if (WindLab::CRPSGeneralizedAlongWindVonKarmanSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSGeneralizedAlongWindVonKarmanSpectrum::init();
    }
    if (WindLab::CRPSGeneralizedAcrossWindVonKarmanSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSGeneralizedAcrossWindVonKarmanSpectrum::init();
    }
    if (WindLab::CRPSGeneralizedVerticalWindVonKarmanSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSGeneralizedVerticalWindVonKarmanSpectrum::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeXSpectrum(objName1,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,
                        stationarity);
    InitializeYSpectrum(objName2,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,
                        stationarity);
    InitializeZSpectrum(objName3,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate, objVersion,
                        stationarity);
    InitializeXSpectrum(objName4,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,
                        stationarity);
    InitializeYSpectrum(objName5,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,
                        stationarity);
    InitializeZSpectrum(objName6,
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
    RegisterXSpectrum(objName1,
                       strPluginName,
                       objDescription1,
                       BuildGeneralizedAlongWindKaimalSpectrum,
                       DestroyGeneralizedAlongWindKaimalSpectrum);

    RegisterYSpectrum(objName2,
                       strPluginName,
                       objDescription2,
                       BuildGeneralizedAcrossWindKaimalSpectrum,
                       DestroyGeneralizedAcrossWindKaimalSpectrum);

    RegisterZSpectrum(objName3,
                       strPluginName,
                       objDescription3,
                       BuildGeneralizedVerticalWindKaimalSpectrum,
                       DestroyGeneralizedVerticalWindKaimalSpectrum);

    RegisterXSpectrum(objName4,
                       strPluginName,
                       objDescription4,
                       BuildGeneralizedAlongWindVonKarmanSpectrum,
                       DestroyGeneralizedAlongWindVonKarmanSpectrum);

    RegisterYSpectrum(objName5,
                       strPluginName,
                       objDescription5,
                       BuildGeneralizedAcrossWindVonKarmanSpectrum,
                       DestroyGeneralizedAcrossWindVonKarmanSpectrum);

    RegisterZSpectrum(objName6,
                       strPluginName,
                       objDescription6,
                       BuildGeneralizedVerticalWindVonKarmanSpectrum,
                       DestroyGeneralizedVerticalWindVonKarmanSpectrum);

       return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterXSpectrum(objName1, strPluginName);
    UnregisterYSpectrum(objName2, strPluginName);
    UnregisterZSpectrum(objName3, strPluginName);
    UnregisterXSpectrum(objName4, strPluginName);
    UnregisterYSpectrum(objName5, strPluginName);
    UnregisterZSpectrum(objName6, strPluginName);

    return 1;
}


