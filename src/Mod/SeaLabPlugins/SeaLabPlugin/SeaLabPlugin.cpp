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
#include "RPSOchiAndHubbleSpectrum.h"
#include "RPSGaussianSwellSpectrum.h"
#include "RPSBretschneiderSpectrum.h"
#include "RPSISSCSpectrum.h"
#include "RPSITTCSpectrum.h"
#include "RPSScottSpectrum.h"
#include "RPSWENSpectrum.h"
#include "RPSBorgmanDirectionalSpreadingFunction.h"
#include "RPSCos2sTypeDirectionalSpreadingFunction.h"
#include "RPSCosineSquareDirectionalSpreadingFunction.h"
#include "RPSHasselmannDirectionalSpreadingFunction.h" 
#include "RPSLonguetHigginsDirectionalSpreadingFunction.h"



#include <Mod/SeaLabAPI/App/RPSSeaLabPluginAPI.h>
#include <Base/Console.h>

std::string strPluginName = "SeaLabPlugin";
bool stationarity = true;

PLUGIN_NAME("SeaLabPlugin");
RANDOM_PHENOMENON("Sea Surface");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS for the simulation of sea surface elevation");
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
std::string objDescriptionJon_S = "This feature allows the user to compute sea surface elevation spectrum from Jonswap Spectrum";
std::string objTileJon_S = "On environmental conditions and environmental loads. In DNV Recommended Practice DNV-RP-C205. 05 2006";
    std::string objLinkJon_S = "https://www.dnv.com/";
std::string objAuthorsJon_S = "Arne Nestegård, Marit Ronæss, Øistein Hagen, Knut Ronold, and Elzbieta Maria Bitner-Gregersen";
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

//////////////////////////Ochi-Hubble Spectrum//////////////////////////////////////////
std::string objNameOch_S = "Ochi-Hubble Spectrum";
std::string objDescriptionOch_S = "This feature allows the user to compute sea surface spectrum from Ochi-Hubble Spectrum";
std::string objTileOch_S = "Ochi-Hubble spectrum";
std::string objLinkOch_S = "https://www.orcina.com/webhelp/OrcaFlex/Content/html/Waves,Wavespectra.htm";
std::string objAuthorsOch_S = "OrcaFlex";
std::string objDateOch_S = "01/02/2025";
std::string objVersionOch_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildOchiAndHubbleSpectrum()
{
    return new CRPSOchiAndHubbleSpectrum;
}

RPS_PLUGIN_FUNC void DestroyOchiAndHubbleSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

//////////////////////////Gaussian Swell Spectrum//////////////////////////////////////////
std::string objNameGau_S = "Gaussian Swell Spectrum";
std::string objDescriptionGau_S = "This feature allows the user to compute sea surface spectrum from Gaussian swell Spectrum";
std::string objTileGau_S = "Gaussian Swell Spectrum";
std::string objLinkGau_S = "https://www.orcina.com/webhelp/OrcaFlex/Content/html/Waves,Wavespectra.htm";
std::string objAuthorsGau_S = "OrcaFlex";
std::string objDateGau_S = "01/02/2025";
std::string objVersionGau_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildGaussianSwellSpectrum()
{
    return new CRPSGaussianSwellSpectrum;
}

RPS_PLUGIN_FUNC void DestroyGaussianSwellSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

//////////////////////////Bretschneider Spectrum//////////////////////////////////////////
std::string objNameBre_S = "Bretschneider Spectrum";
std::string objDescriptionBre_S = "This feature allows the user to compute sea surface elevation spectrum from Bretschneider Spectrum";
std::string objTileBre_S = "Ocean Wave Mechanics: Applications in Marine Structures";
std::string objLinkBre_S = "https://onlinelibrary.wiley.com/doi/book/10.1002/9781119241652";
std::string objAuthorsBre_S = "Dr. V. Sundar";
std::string objDateBre_S = "06/02/2025";
std::string objVersionBre_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildBretschneiderSpectrum()
{
    return new CRPSBretschneiderSpectrum;
}

RPS_PLUGIN_FUNC void DestroyBretschneiderSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

//////////////////////////ISSC Spectrum//////////////////////////////////////////
std::string objNameISSC_S = "ISSC Spectrum";
std::string objDescriptionISSC_S = "This feature allows the user to compute sea surface elevation spectrum from ISSC Spectrum";
std::string objTileISSC_S = "Ocean Wave Mechanics: Applications in Marine Structures";
std::string objLinkISSC_S = "https://onlinelibrary.wiley.com/doi/book/10.1002/9781119241652";
std::string objAuthorsISSC_S = "Dr. V. Sundar";
std::string objDateISSC_S = "06/02/2025";
std::string objVersionISSC_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildISSCSpectrum() {
    return new CRPSISSCSpectrum;
}

RPS_PLUGIN_FUNC void DestroyISSCSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

//////////////////////////ITTC Spectrum//////////////////////////////////////////
std::string objNameITTC_S = "ITTC Spectrum";
std::string objDescriptionITTC_S = "This feature allows the user to compute sea surface elevation spectrum from ITTC Spectrum";
std::string objTileITTC_S = "Ocean Wave Mechanics: Applications in Marine Structures";
std::string objLinkITTC_S = "https://onlinelibrary.wiley.com/doi/book/10.1002/9781119241652";
std::string objAuthorsITTC_S = "Dr. V. Sundar";
std::string objDateITTC_S = "06/02/2025";
std::string objVersionITTC_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildITTCSpectrum() {
    return new CRPSITTCSpectrum;
}

RPS_PLUGIN_FUNC void DestroyITTCSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

//////////////////////////Scott Spectrum//////////////////////////////////////////
std::string objNameScott_S = "Scott Spectrum";
std::string objDescriptionScott_S = "This feature allows the user to compute sea surface elevation spectrum from Scott Spectrum";
std::string objTileScott_S = "Ocean Wave Mechanics: Applications in Marine Structures";
std::string objLinkScott_S = "https://onlinelibrary.wiley.com/doi/book/10.1002/9781119241652";
std::string objAuthorsScott_S = "Dr. V. Sundar";
std::string objDateScott_S = "06/02/2025";
std::string objVersionScott_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildScottSpectrum() {
    return new CRPSScottSpectrum;
}

RPS_PLUGIN_FUNC void DestroyScottSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}


//////////////////////////WEN Spectrum//////////////////////////////////////////
std::string objNameWEN_S = "WEN Spectrum";
std::string objDescriptionWEN_S = "This feature allows the user to compute sea surface elevation spectrum from WEN Spectrum";
std::string objTileWEN_S = "Ocean Wave Mechanics: Applications in Marine Structures";
std::string objLinkWEN_S = "https://onlinelibrary.wiley.com/doi/book/10.1002/9781119241652";
std::string objAuthorsWEN_S = "Dr. V. Sundar";
std::string objDateWEN_S = "06/02/2025";
std::string objVersionWEN_S = "1.0";

RPS_PLUGIN_FUNC IrpsSeLFrequencySpectrum* BuildWENSpectrum() {
    return new CRPSWENSpectrum;
}

RPS_PLUGIN_FUNC void DestroyWENSpectrum(IrpsSeLFrequencySpectrum* r) {
    delete r;
}

//////////////////////////Borgman Directional Spreading Function//////////////////////////////////////////
std::string objNameBorgman_D = "Borgman Directional Spreading Function";
std::string objDescriptionBorgman_D = "This feature allows the user to compute sea wave directional spreading function according to Borgman model";
std::string objTileBorgman_D = "Ocean Waves: The Stochastic Approach (Cambridge Ocean Technology Series)";
std::string objLinkBorgman_D = "https://doi.org/10.1017/CBO9780511529559";
std::string objAuthorsBorgman_D = "Michel K. Ochi, I. Dyer, R. Eatock Taylor, J. N. Newman, W. G. Price";
std::string objDateBorgman_D = "06/02/2025";
std::string objVersionBorgman_D = "1.0";

RPS_PLUGIN_FUNC IrpsSeLDirectionalSpreadingFunction* BuildBorgmanDirectionalSpreadingFunction()
{
    return new CRPSBorgmanDirectionalSpreadingFunction;
}

RPS_PLUGIN_FUNC void DestroyBorgmanDirectionalSpreadingFunction(IrpsSeLDirectionalSpreadingFunction* r) {
    delete r;
}

//////////////////////////Cos2s Directional Spreading Function//////////////////////////////////////////
std::string objNameCos2s_D = "Cos2s Directional Spreading Function";
std::string objDescriptionCos2s_D = "This feature allows the user to compute sea wave directional spreading function according to Cos2s type model";
std::string objTileCos2s_D = "Estimation of Directional Wave Spectrum Using Measurement Array Pressure Data on Bottom - Mounted Offshore Structure in Incident and Diffracted Wave Field ";
std::string objLinkCos2s_D = "https://doi.org/10.1155/2022/9764478";
std::string objAuthorsCos2s_D = "Xiaodong Song, Zilong Ti, Yuanzhou Zhou";
std::string objDateCos2s_D = "06/02/2025";
std::string objVersionCos2s_D = "1.0";

RPS_PLUGIN_FUNC IrpsSeLDirectionalSpreadingFunction* BuildCos2sDirectionalSpreadingFunction()
{
    return new CRPSCos2sTypeDirectionalSpreadingFunction;
}

RPS_PLUGIN_FUNC void DestroyCos2sDirectionalSpreadingFunction(IrpsSeLDirectionalSpreadingFunction* r) {
    delete r;
}


//////////////////////////CosineSquare Directional Spreading Function//////////////////////////////////////////
std::string objNameCosineSquare_D = "Cosine Squared Directional Spreading Function";
std::string objDescriptionCosineSquare_D = "This feature allows the user to compute sea wave directional spreading function according to Cosine Squared model";
std::string objTileCosineSquare_D = "Ocean Waves: The Stochastic Approach (Cambridge Ocean Technology Series)";
std::string objLinkCosineSquare_D = "https://doi.org/10.1017/CBO9780511529559";
std::string objAuthorsCosineSquare_D = "Michel K. Ochi, I. Dyer, R. Eatock Taylor, J. N. Newman, W. G. Price";
std::string objDateCosineSquare_D = "06/02/2025";
std::string objVersionCosineSquare_D = "1.0";

RPS_PLUGIN_FUNC IrpsSeLDirectionalSpreadingFunction* BuildCosineSquareDirectionalSpreadingFunction()
{
    return new CRPSCosineSquareDirectionalSpreadingFunction;
}

RPS_PLUGIN_FUNC void DestroyCosineSquareDirectionalSpreadingFunction(IrpsSeLDirectionalSpreadingFunction* r) {
    delete r;
}

//////////////////////////Hasselmann Directional Spreading Function//////////////////////////////////////////
std::string objNameHasselmann_D = "Hasselmann Directional Spreading Function";
std::string objDescriptionHasselmann_D = "This feature allows the user to compute sea wave directional spreading function according to Hasselmann model";
std::string objTileHasselmann_D = "Ocean Waves: The Stochastic Approach (Cambridge Ocean Technology Series)";
std::string objLinkHasselmann_D = "https://doi.org/10.1017/CBO9780511529559";
std::string objAuthorsHasselmann_D = "Michel K. Ochi, I. Dyer, R. Eatock Taylor, J. N. Newman, W. G. Price";
std::string objDateHasselmann_D = "06/02/2025";
std::string objVersionHasselmann_D = "1.0";

RPS_PLUGIN_FUNC IrpsSeLDirectionalSpreadingFunction* BuildHasselmannDirectionalSpreadingFunction()
{
    return new CRPSHasselmannDirectionalSpreadingFunction;
}

RPS_PLUGIN_FUNC void DestroyHasselmannDirectionalSpreadingFunction(IrpsSeLDirectionalSpreadingFunction* r) {
    delete r;
}


//////////////////////////LonguetHiggins Directional Spreading Function//////////////////////////////////////////
std::string objNameLonguetHiggins_D = "Longuet-Higgins Directional Spreading Function";
std::string objDescriptionLonguetHiggins_D = "This feature allows the user to compute sea wave directional spreading function according to Longuet-Higgins model";
std::string objTileLonguetHiggins_D = "REALISTIC SIMULATION OF OCEAN SURFACE USING WAVESPECTRA";
    std::string objLinkLonguetHiggins_D = "https://hal.science/hal-00307938";
std::string objAuthorsLonguetHiggins_D = "Jocelyn Frechot";
std::string objDateLonguetHiggins_D = "06/02/2025";
std::string objVersionLonguetHiggins_D = "1.0";

RPS_PLUGIN_FUNC IrpsSeLDirectionalSpreadingFunction* BuildLonguetHigginsDirectionalSpreadingFunction()
{
    return new CRPSLonguetHigginsDirectionalSpreadingFunction;
}

RPS_PLUGIN_FUNC void DestroyLonguetHigginsDirectionalSpreadingFunction(IrpsSeLDirectionalSpreadingFunction* r) {
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
    if (SeaLab::CRPSOchiAndHubbleSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSOchiAndHubbleSpectrum::init();
    }
    if (SeaLab::CRPSGaussianSwellSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSGaussianSwellSpectrum::init();
    }
    if (SeaLab::CRPSBretschneiderSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSBretschneiderSpectrum::init();
    }
    if (SeaLab::CRPSISSCSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSISSCSpectrum::init();
    }
    if (SeaLab::CRPSITTCSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSITTCSpectrum::init();
    }
    if (SeaLab::CRPSScottSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSScottSpectrum::init();
    }
    if (SeaLab::CRPSWENSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSWENSpectrum::init();
    }
    if (SeaLab::CRPSBorgmanDirectionalSpreadingFunction::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSBorgmanDirectionalSpreadingFunction::init();
    }
    if (SeaLab::CRPSCos2sTypeDirectionalSpreadingFunction::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSCos2sTypeDirectionalSpreadingFunction::init();
    }
    if (SeaLab::CRPSCosineSquareDirectionalSpreadingFunction::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSCosineSquareDirectionalSpreadingFunction::init();
    }
    if (SeaLab::CRPSHasselmannDirectionalSpreadingFunction::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSHasselmannDirectionalSpreadingFunction::init();
    }
    if (SeaLab::CRPSLonguetHigginsDirectionalSpreadingFunction::getClassTypeId() == Base::Type::badType()) {
        SeaLab::CRPSLonguetHigginsDirectionalSpreadingFunction::init();
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
    InitializeFrequencySpectrum(objNameOch_S, strPluginName, objTileOch_S, objLinkOch_S, objAuthorsOch_S, objDateOch_S, objVersionOch_S, stationarity);
    InitializeFrequencySpectrum(objNameGau_S, strPluginName, objTileGau_S, objLinkGau_S, objAuthorsGau_S, objDateGau_S, objVersionGau_S, stationarity);
    InitializeFrequencySpectrum(objNameBre_S, strPluginName, objTileBre_S, objLinkBre_S, objAuthorsBre_S, objDateBre_S, objVersionBre_S, stationarity);
    InitializeFrequencySpectrum(objNameISSC_S, strPluginName, objTileISSC_S, objLinkISSC_S, objAuthorsISSC_S, objDateISSC_S, objVersionISSC_S, stationarity);
    InitializeFrequencySpectrum(objNameITTC_S, strPluginName, objTileITTC_S, objLinkITTC_S, objAuthorsITTC_S, objDateITTC_S, objVersionITTC_S, stationarity);
    InitializeFrequencySpectrum(objNameScott_S, strPluginName, objTileScott_S, objLinkScott_S, objAuthorsScott_S, objDateScott_S, objVersionScott_S, stationarity);
    InitializeFrequencySpectrum(objNameWEN_S, strPluginName, objTileWEN_S, objLinkWEN_S, objAuthorsWEN_S, objDateWEN_S, objVersionWEN_S, stationarity);

    InitializeDirectionalSpreadingFunction(objNameBorgman_D, strPluginName, objTileBorgman_D, objLinkBorgman_D, objAuthorsBorgman_D, objDateBorgman_D, objVersionBorgman_D, stationarity);
    InitializeDirectionalSpreadingFunction(objNameCos2s_D, strPluginName, objTileCos2s_D, objLinkCos2s_D, objAuthorsCos2s_D, objDateCos2s_D, objVersionCos2s_D, stationarity);
    InitializeDirectionalSpreadingFunction(objNameCosineSquare_D, strPluginName, objTileCosineSquare_D, objLinkCosineSquare_D, objAuthorsCosineSquare_D, objDateCosineSquare_D, objVersionCosineSquare_D, stationarity);
    InitializeDirectionalSpreadingFunction(objNameHasselmann_D, strPluginName, objTileHasselmann_D, objLinkHasselmann_D, objAuthorsHasselmann_D, objDateHasselmann_D, objVersionHasselmann_D, stationarity);
    InitializeDirectionalSpreadingFunction(objNameLonguetHiggins_D, strPluginName, objTileLonguetHiggins_D, objLinkLonguetHiggins_D, objAuthorsLonguetHiggins_D, objDateLonguetHiggins_D, objVersionLonguetHiggins_D, stationarity);

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

    RegisterFrequencySpectrum(objNameJon_S, strPluginName, objDescriptionJon_S, BuildJonswapSpectrum, DestroyJonswapSpectrum);
    RegisterFrequencySpectrum(objNameMos_S, strPluginName, objDescriptionMos_S, BuildPiersonMoskowitzSpectrum, DestroyPiersonMoskowitzSpectrum);
    RegisterFrequencySpectrum(objNameTor_S, strPluginName, objDescriptionTor_S, BuildTorsethaugenSpectrum, DestroyTorsethaugenSpectrum);
    RegisterFrequencySpectrum(objNameOch_S, strPluginName, objDescriptionOch_S, BuildOchiAndHubbleSpectrum, DestroyOchiAndHubbleSpectrum);
    RegisterFrequencySpectrum(objNameGau_S, strPluginName, objDescriptionGau_S, BuildGaussianSwellSpectrum, DestroyGaussianSwellSpectrum);
    RegisterFrequencySpectrum(objNameBre_S, strPluginName, objDescriptionBre_S, BuildBretschneiderSpectrum, DestroyBretschneiderSpectrum);
    RegisterFrequencySpectrum(objNameISSC_S, strPluginName, objDescriptionISSC_S, BuildISSCSpectrum, DestroyISSCSpectrum);
    RegisterFrequencySpectrum(objNameITTC_S, strPluginName, objDescriptionITTC_S, BuildITTCSpectrum, DestroyITTCSpectrum);
    RegisterFrequencySpectrum(objNameScott_S, strPluginName, objDescriptionScott_S, BuildScottSpectrum, DestroyScottSpectrum);
    RegisterFrequencySpectrum(objNameWEN_S, strPluginName, objDescriptionWEN_S, BuildWENSpectrum, DestroyWENSpectrum);

    RegisterDirectionalSpreadingFunction(objNameBorgman_D, strPluginName, objDescriptionBorgman_D, BuildBorgmanDirectionalSpreadingFunction, DestroyBorgmanDirectionalSpreadingFunction);
    RegisterDirectionalSpreadingFunction(objNameCos2s_D, strPluginName, objDescriptionCos2s_D, BuildCos2sDirectionalSpreadingFunction, DestroyCos2sDirectionalSpreadingFunction);
    RegisterDirectionalSpreadingFunction(objNameCosineSquare_D, strPluginName, objDescriptionCosineSquare_D, BuildCosineSquareDirectionalSpreadingFunction, DestroyCosineSquareDirectionalSpreadingFunction);
    RegisterDirectionalSpreadingFunction(objNameHasselmann_D, strPluginName, objDescriptionHasselmann_D, BuildHasselmannDirectionalSpreadingFunction, DestroyHasselmannDirectionalSpreadingFunction);
    RegisterDirectionalSpreadingFunction(objNameLonguetHiggins_D, strPluginName, objDescriptionLonguetHiggins_D, BuildLonguetHigginsDirectionalSpreadingFunction, DestroyLonguetHigginsDirectionalSpreadingFunction);

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
    UnregisterFrequencySpectrum(objNameOch_S, strPluginName);
    UnregisterFrequencySpectrum(objNameGau_S, strPluginName);
    UnregisterFrequencySpectrum(objNameBre_S, strPluginName);
    UnregisterFrequencySpectrum(objNameISSC_S, strPluginName);
    UnregisterFrequencySpectrum(objNameITTC_S, strPluginName);
    UnregisterFrequencySpectrum(objNameScott_S, strPluginName);
    UnregisterFrequencySpectrum(objNameWEN_S, strPluginName);

    UnregisterDirectionalSpreadingFunction(objNameBorgman_D, strPluginName);
    UnregisterDirectionalSpreadingFunction(objNameCos2s_D, strPluginName);
    UnregisterDirectionalSpreadingFunction(objNameCosineSquare_D, strPluginName);
    UnregisterDirectionalSpreadingFunction(objNameHasselmann_D, strPluginName);
    UnregisterDirectionalSpreadingFunction(objNameLonguetHiggins_D, strPluginName);

    return 1;
}




