#include "PreCompiled.h"

#include <QString>
// SeaLab.cpp : Defines the initialization routines for the DLL.
//
#include "WLGridPoints.h"
#include "GeneralSpatialDistribution.h"
#include "RPSDoubleIndexFrequency.h"
#include "RPSSingleIndexFrequency.h"
#include "CholeskyDecomposition.h"
#include "RPSUniformRandomPhases.h"
#include "RPSRandomPhasesFromFile.h"
#include "ZervaModelFrequencyDistribution.h"
#include "RPSJonswapSpectrum.h"
#include "RPSPiersonMoskowitzSpectrum.h"
#include "RPSTorsethaugenSpectrum.h"
#include <Mod/SeaLabAPI/App/RPSSeaLabPluginAPI.h>
#include <Base/Console.h>

std::string strPluginName = "SeaLabPlugin";
bool stationarity = true;

PLUGIN_NAME("SeaLabPlugin");
RANDOM_PHENOMENON("Sea Surface");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS for the simulation of seismic ground motion");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("All");
API_VERSION("ALL");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace SeaLab;
using namespace SeaLabAPI;

///////////////////////General Spatial Distribution/////////////////
std::string objNameGen_D = "General Distribution";
std::string objDescriptionGen_D = "This feature allows the user to add simulation points to WindLab simulation by points coordinates";
std::string objTileGen_D = "LabRPS";
std::string objLinkGen_D = "https://wiki.labrps.com";
std::string objAuthorsGen_D = "LabRPS";
std::string objDateGen_D = "15/06/2024";
std::string objVersionGen_D = "1.0";
RPS_PLUGIN_FUNC IrpsSeLLocationDistribution* BuildGeneralSpatialDistribution()
{
    return new GeneralSpatialDistribution;
}

RPS_PLUGIN_FUNC void DestroyGeneralSpatialDistribution(SeaLabAPI::IrpsSeLLocationDistribution* r)
{
    delete r;
}


std::string objNameGri_P = "Grid Points";
std::string objDescriptionGri_P = "This feature allows the user to add simulation points that are uniformly distributed on vertical line in space";
std::string objTileGri_P = "LabRPS";
std::string objLinkGri_P = "https://wiki.labrps.com";
std::string objAuthorsGri_P = "LabRPS";
std::string objDateGri_P = "15/06/2024";
std::string objVersionGri_P = "1.0";

RPS_PLUGIN_FUNC IrpsSeLLocationDistribution* BuildGridPoints()
{
    return new WLGridPoints;
}

RPS_PLUGIN_FUNC void DestroyGridPoints(IrpsSeLLocationDistribution* r) {
    delete r;
}

////////////////////////Double Index Freq//////////////////////////////////////////
std::string objNameDou_I = "Double Index Frequency Discretization";
std::string objDescriptionDou_I = "This feature allows the user to discretize frequency according to the double index frequency ";
std::string objTileDou_I = "Simulation of Ergodic Multivariate Stochastic Processes";
std::string objLinkDou_I = "https://doi.org/10.1061/(ASCE)0733-9399(1996)122:8(778)";
std::string objAuthorsDou_I = "George Deodatis";
std::string objDateDou_I = "15/06/2024";
std::string objVersionDou_I = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencyDistribution* BuildRPSDoubleIndexFreq()
{
    return new CRPSDoubleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSDoubleIndexFreq(IrpsSeLFrequencyDistribution* r)
{
    delete r;
}

////////////////////////single Index Freq//////////////////////////////////////////
std::string objNameSin_I = "Single Index Frequency Discretization";
std::string objDescriptionSin_I = "This feature allows the user to discretize frequency according to the single index frequency ";
std::string objTileSin_I = "Simulation of Stochastic Processes by Spectral Representation";
std::string objLinkSin_I = "https://doi.org/10.1115/1.3119501";
std::string objAuthorsSin_I = "Masanobu Shinozuka, George Deodatis";
std::string objDateSin_I = "15/06/2024";
std::string objVersionSin_I = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencyDistribution* BuildRPSSingleIndexFreq()
{
    return new SeaLab::CRPSSingleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSSingleIndexFreq(IrpsSeLFrequencyDistribution* r)
{
    delete r;
}

////////////////////////Zerva Freq//////////////////////////////////////////
std::string objNameZer_F = "Zerva Frequency Discretization";
std::string objDescriptionZer_F = "This feature allows the user to discretize frequency according to the Zerva frequency ";
std::string objTileZer_F = "LabRPS";
std::string objLinkZer_F = "https://wiki.labrps.com";
std::string objAuthorsZer_F = "LabRPS";
std::string objDateZer_F = "15/06/2024";
std::string objVersionZer_F = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencyDistribution* BuildZervaModelFrequencyDistribution()
{
    return new ZervaModelFrequencyDistribution;
}

RPS_PLUGIN_FUNC void DestroyZervaModelFrequencyDistribution(IrpsSeLFrequencyDistribution* r)
{
    delete r;
}

//////////////////////////Cholesky decomposition//////////////////////////////////////////
std::string objNameCho_D = "Cholesky Decomposition";
std::string objDescriptionCho_D = "This feature allows the user to decompose a power spectral density matrix as described in Dedatis (1996).";
std::string objTileCho_D = "Simulation of Ergodic Multivariate Stochastic Processes";
std::string objLinkCho_D = "https://doi.org/10.1061/(ASCE)0733-9399(1996)122:8(778)";
std::string objAuthorsCho_D = "George Deodatis";
std::string objDateCho_D = "15/06/2024";
std::string objVersionCho_D = "1.0";

RPS_PLUGIN_FUNC IrpsSeLPSDdecompositionMethod* BuildPSDdecomMethod()
{
    return new CCholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyPSDdecomMethod(IrpsSeLPSDdecompositionMethod* r)
{
    delete r;
}

//////////////////////////uniform random phase//////////////////////////////////////////
std::string objNameUni_R = "Uniform Random Phases";
std::string objDescriptionUni_R = "This feature allows the user to generate random phases as described in Dedatis (1996).";
std::string objTileUni_R = "Simulation of Ergodic Multivariate Stochastic Processes";
std::string objLinkUni_R = "https://doi.org/10.1061/(ASCE)0733-9399(1996)122:8(778)";
std::string objAuthorsUni_R = "George Deodatis";
std::string objDateUni_R = "15/06/2024";
std::string objVersionUni_R = "1.0";

RPS_PLUGIN_FUNC IrpsSeLRandomness* BuildRPSUniformRandomPhases()
{
    return new CRPSUniformRandomPhases;
}

RPS_PLUGIN_FUNC void DestroyRPSUniformRandomPhases(IrpsSeLRandomness* r)
{
    delete r;
}

//////////////////////////import random phase from file//////////////////////////////////////////
std::string objNameUni_I = "Uniform Random Phases Import";
std::string objDescriptionUni_I = "This feature allows the user to import uniform random phases from file";
std::string objTileUni_I = "LabRPS";
std::string objLinkUni_I = "https://wiki.labrps.com";
std::string objAuthorsUni_I = "LabRPS";
std::string objDateUni_I = "15/06/2024";
std::string objVersionUni_I = "1.0";

RPS_PLUGIN_FUNC IrpsSeLRandomness* BuildRPSRandomPhasesFromFile()
{
    return new CRPSRandomPhasesFromFile;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomPhasesFromFile(IrpsSeLRandomness* r)
{
    delete r;
}

//////////////////////////Jonswap Spectrum//////////////////////////////////////////
std::string objNameJon_S = "Jonswap Spectrum (1974)";
std::string objDescriptionJon_S = "This feature allows the user to compute sea surface spectrum from Jonswap Spectrum";
std::string objTileJon_S = "Measurements of Wind Wave Growth and Swell Decay during the Joint North Sea Wave Project ";
    std::string objLinkJon_S = "https://repository.tudelft.nl/record/uuid:f204e188-13b9-49d8-a6dc-4fb7c20562fc";
std::string objAuthorsJon_S = "Hasselmann et al";
std::string objDateJon_S = "15/06/2024";
std::string objVersionJon_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildJonswapSpectrum()
{
    return new CRPSJonswapSpectrum;
}

RPS_PLUGIN_FUNC void DestroyJonswapSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

//////////////////////////Pierson Moskowitz Spectrum//////////////////////////////////////////
std::string objNameMos_S = "Pierson Moskowitz Spectrum (1964)";
std::string objDescriptionMos_S = "This feature allows the user to compute sea surface spectrum from Pierson Moskowitz Spectrum";
std::string objTileMos_S = "A Proposed Spectral form for Fully Developed Wind Sea Based on the Similarity Theory of S. A. Kitaigorodskii";
std::string objLinkMos_S = "http://dx.doi.org/10.1029/JZ069i024p05181";
std::string objAuthorsMos_S = "Pierson, W. and Moskowitz, L";
std::string objDateMos_S = "15/06/2024";
std::string objVersionMos_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildPiersonMoskowitzSpectrum()
{
    return new CRPSPiersonMoskowitzSpectrum;
}

RPS_PLUGIN_FUNC void DestroyPiersonMoskowitzSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}


//////////////////////////Torsethaugen Spectrum//////////////////////////////////////////
std::string objNameTor_S = "Torsethaugen Spectrum";
std::string objDescriptionTor_S = "This feature allows the user to compute sea surface spectrum from Torsethaugen Spectrum";
std::string objTileTor_S = "LabRPS";
std::string objLinkTor_S = "https://wiki.labrps.com";
std::string objAuthorsTor_S = "LabRPS";
std::string objDateTor_S = "15/06/2024";
std::string objVersionTor_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildTorsethaugenSpectrum()
{
    return new CRPSTorsethaugenSpectrum;
}

RPS_PLUGIN_FUNC void DestroyTorsethaugenSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
    if (SeaLab::GeneralSpatialDistribution::getClassTypeId() == Base::Type::badType()) {
        SeaLab::GeneralSpatialDistribution::init();
    }
    if (SeaLab::WLGridPoints::getClassTypeId() == Base::Type::badType()) {
        SeaLab::WLGridPoints::init();
    }
    if (SeaLab::CRPSDoubleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSDoubleIndexFrequency::init();
    }
    if (SeaLab::CRPSSingleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSSingleIndexFrequency::init();
    }
    if (SeaLab::CCholeskyDecomposition::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CCholeskyDecomposition::init();
    }
    if (SeaLab::CRPSUniformRandomPhases::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSUniformRandomPhases::init();
    }
    if (SeaLab::CRPSRandomPhasesFromFile::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSRandomPhasesFromFile::init();
    }
    if (SeaLab::ZervaModelFrequencyDistribution::getClassTypeId() == Base::Type::badType()) {
        SeaLab::ZervaModelFrequencyDistribution::init();
    }
    if (SeaLab::CRPSJonswapSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSJonswapSpectrum::init();
    }
    if (SeaLab::CRPSPiersonMoskowitzSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSPiersonMoskowitzSpectrum::init();
    }
    if (SeaLab::CRPSTorsethaugenSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSTorsethaugenSpectrum::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeLocationDistribution(objNameGen_D, strPluginName, objTileGen_D, objLinkGen_D, objAuthorsGen_D, objDateGen_D, objVersionGen_D, stationarity);
    InitializeLocationDistribution(objNameGri_P, strPluginName, objTileGri_P, objLinkGri_P, objAuthorsGri_P, objDateGri_P, objVersionGri_P, stationarity);

    InitializeFrequencyDistribution(objNameDou_I, strPluginName, objTileDou_I, objLinkDou_I, objAuthorsDou_I, objDateDou_I, objVersionDou_I, stationarity);
    InitializeFrequencyDistribution(objNameSin_I, strPluginName, objTileSin_I, objLinkSin_I, objAuthorsSin_I, objDateSin_I, objVersionSin_I, stationarity);
    InitializeFrequencyDistribution(objNameZer_F, strPluginName, objTileZer_F, objLinkZer_F, objAuthorsZer_F, objDateZer_F, objVersionZer_F, stationarity);

    InitializePSDdecomMethod(objNameCho_D, strPluginName, objTileCho_D, objLinkCho_D, objAuthorsCho_D, objDateCho_D, objVersionCho_D, stationarity);

    InitializeRandomness(objNameUni_R, strPluginName, objTileUni_R, objLinkUni_R, objAuthorsUni_R, objDateUni_R, objVersionUni_R, stationarity);
    InitializeRandomness(objNameUni_I, strPluginName, objTileUni_I, objLinkUni_I, objAuthorsUni_I, objDateUni_I, objVersionUni_I, stationarity);
    
    InitializeFrequencySpectrum(objNameJon_S, strPluginName, objTileJon_S, objLinkJon_S, objAuthorsJon_S, objDateJon_S, objVersionJon_S, stationarity);
    InitializeFrequencySpectrum(objNameMos_S, strPluginName, objTileMos_S, objLinkMos_S, objAuthorsMos_S, objDateMos_S, objVersionMos_S, stationarity);
    InitializeFrequencySpectrum(objNameTor_S, strPluginName, objTileTor_S, objLinkTor_S, objAuthorsTor_S, objDateTor_S, objVersionTor_S, stationarity);

    return 1;
}


INSTALL_PLUGIN()
{
    RegisterLocationDistribution(objNameGen_D, strPluginName, objDescriptionGen_D, BuildGeneralSpatialDistribution, DestroyGeneralSpatialDistribution);
    RegisterLocationDistribution(objNameGri_P, strPluginName, objDescriptionGri_P, BuildGridPoints, DestroyGridPoints);
    
    RegisterFrequencyDistribution(objNameDou_I, strPluginName, objDescriptionDou_I, BuildRPSDoubleIndexFreq, DestroyRPSDoubleIndexFreq);
    RegisterFrequencyDistribution(objNameSin_I, strPluginName, objDescriptionSin_I, BuildRPSSingleIndexFreq, DestroyRPSSingleIndexFreq);
    RegisterFrequencyDistribution(objNameZer_F, strPluginName, objDescriptionZer_F, BuildZervaModelFrequencyDistribution, DestroyZervaModelFrequencyDistribution);

    RegisterPSDdecomMethod(objNameCho_D, strPluginName, objDescriptionCho_D, BuildPSDdecomMethod, DestroyPSDdecomMethod);
    
    RegisterRandomness(objNameUni_R, strPluginName, objDescriptionUni_R, BuildRPSUniformRandomPhases, DestroyRPSUniformRandomPhases);
    RegisterRandomness(objNameUni_I, strPluginName, objDescriptionUni_I, BuildRPSRandomPhasesFromFile, DestroyRPSRandomPhasesFromFile);

    RegisterFrequencySpectrum(objNameJon_S, strPluginName, objDescriptionJon_S,BuildJonswapSpectrum, DestroyJonswapSpectrum);
    RegisterFrequencySpectrum(objNameMos_S, strPluginName, objDescriptionMos_S,BuildPiersonMoskowitzSpectrum, DestroyPiersonMoskowitzSpectrum);
    RegisterFrequencySpectrum(objNameTor_S, strPluginName, objDescriptionTor_S,BuildTorsethaugenSpectrum, DestroyTorsethaugenSpectrum);

    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterLocationDistribution(objNameGen_D, strPluginName);
    UnregisterLocationDistribution(objNameGri_P, strPluginName);

    UnregisterFrequencyDistribution(objNameDou_I, strPluginName);
    UnregisterFrequencyDistribution(objNameSin_I, strPluginName);
    UnregisterFrequencyDistribution(objNameZer_F, strPluginName);
  
    UnregisterPSDdecomMethod(objNameCho_D, strPluginName);

    UnregisterRandomness(objNameUni_R, strPluginName);
    UnregisterRandomness(objNameUni_I, strPluginName);

    UnregisterFrequencySpectrum(objNameJon_S, strPluginName);
    UnregisterFrequencySpectrum(objNameMos_S, strPluginName);
    UnregisterFrequencySpectrum(objNameTor_S, strPluginName);

    return 1;
}




