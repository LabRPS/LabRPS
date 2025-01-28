#include "PreCompiled.h"

#include <QString>
// SeismicLab.cpp : Defines the initialization routines for the DLL.
//
#include "WLHorizontalUniformDistribution.h"
#include "WLVerticalUniformDistribution.h"
#include "WLGridPoints.h"
#include "RPSDoubleIndexFrequency.h"
#include "RPSSingleIndexFrequency.h"
#include "CholeskyDecomposition.h"
#include "RPSUniformRandomPhases.h"
#include "RPSRandomPhasesFromFile.h"
#include "GeneralSpatialDistribution.h"
#include "WLUniformDistributionLocations.h"
#include "RPSWavePassageEffect.h"
#include "ZervaModelFrequencyDistribution.h"
#include "RPSCloughPenzienSpectrum.h"
#include "RPSKanaiTajimiSpectrum.h"
#include "RPSHuZhouSpectrum.h"
#include "RPSConstantModulation.h"
#include "RPSExponentialModulation.h"
#include "RPSJenningsEtAl1968Modulation.h"
#include "RPSSaragoniHart1974Modulation.h"
#include "RPSTrapezoidalModulation.h"
#include "RPSBogdanoffGoldbergBernardModulation.h"
#include "RPSBoxCarModulation.h"
#include "RPSAbrahamsonCoherence.h"
#include "RPSHarichandranVanmarckeCoherence.h"
#include "RPSLohAndLinCoherence.h"
#include "RPSKougioumtzoglouAndSpanoSpectrum.h"

#include <Mod/SeismicLabAPI/App/RPSSeismicLabPluginAPI.h>
#include <Base/Console.h>

std::string strPluginName = "SeismicLabPlugin";
bool stationarity = true;

PLUGIN_NAME("SeismicLabPlugin");
RANDOM_PHENOMENON("Seismic Ground Motion");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS for the simulation of seismic ground motion");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace SeismicLab;
using namespace SeismicLabAPI;

///////////////////////General Spatial Distribution/////////////////
std::string objNameGen_D = "General Distribution";
std::string objDescriptionGen_D = "This feature allows the user to add simulation points to WindLab simulation by points coordinates";
std::string objTileGen_D = "LabRPS";
std::string objLinkGen_D = "https://wiki.labrps.com";
std::string objAuthorsGen_D = "LabRPS";
std::string objDateGen_D = "15/06/2024";
std::string objVersionGen_D = "1.0";
RPS_PLUGIN_FUNC IrpsSLLocationDistribution* BuildGeneralSpatialDistribution()
{
    return new GeneralSpatialDistribution;
}

RPS_PLUGIN_FUNC void DestroyGeneralSpatialDistribution(SeismicLabAPI::IrpsSLLocationDistribution* r)
{
    delete r;
}

///////////////////////Uniform Distribution/////////////////
std::string objNameUni_D = "Uniform Distribution";
std::string objDescriptionUni_D = "This feature allows the user to add simulation points that are uniformly distributed along a linne in space";
std::string objTileUni_D = "LabRPS";
std::string objLinkUni_D = "https://wiki.labrps.com";
std::string objAuthorsUni_D = "LabRPS";
std::string objDateUni_D = "15/06/2024";
std::string objVersionUni_D = "1.0";

RPS_PLUGIN_FUNC IrpsSLLocationDistribution* BuildUniformSpatialDistribution()
{
    return new WLUniformDistributionLocations;
}

RPS_PLUGIN_FUNC void DestroyUniformSpatialDistribution(SeismicLabAPI::IrpsSLLocationDistribution* r)
{
    delete r;
}

///////////////////////horizontal uniform location distribution/////////////////
std::string objNameHor_D = "Horizontal Distribution";
std::string objDescriptionHor_D = "This feature allows the user to add simulation points that are uniformly distributed on horizontal line in space";
std::string objTileHor_D = "LabRPS";
std::string objLinkHor_D = "https://wiki.labrps.com";
std::string objAuthorsHor_D = "LabRPS";
std::string objDateHor_D = "15/06/2024";
std::string objVersionHor_D = "1.0";

RPS_PLUGIN_FUNC IrpsSLLocationDistribution* BuildHorizontalDistr()
{
    return new CWLHorizontalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyHorizontalDistr(IrpsSLLocationDistribution* r)
{
    delete r;
}

// ///////////////////////vertical uniform location distribution/////////////////
std::string objNameVer_D = "Vertical Distribution";
std::string objDescriptionVer_D = "This feature allows the user to add simulation points that are uniformly distributed on vertical line in space";
std::string objTileVer_D = "LabRPS";
std::string objLinkVer_D = "https://wiki.labrps.com";
std::string objAuthorsVer_D = "LabRPS";
std::string objDateVer_D = "15/06/2024";
std::string objVersionVer_D = "1.0";

 RPS_PLUGIN_FUNC IrpsSLLocationDistribution* BuildVerticalDistr()
 {
     return new CWLVerticalUniformDistribution;
 }

 RPS_PLUGIN_FUNC void DestroyVerticalDistr(IrpsSLLocationDistribution* r)
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

RPS_PLUGIN_FUNC IrpsSLLocationDistribution* BuildGridPoints()
{
    return new WLGridPoints;
}

RPS_PLUGIN_FUNC void DestroyGridPoints(IrpsSLLocationDistribution* r) {
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

RPS_PLUGIN_FUNC IrpsSLFrequencyDistribution* BuildRPSDoubleIndexFreq()
{
    return new CRPSDoubleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSDoubleIndexFreq(IrpsSLFrequencyDistribution* r)
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

RPS_PLUGIN_FUNC IrpsSLFrequencyDistribution* BuildRPSSingleIndexFreq()
{
    return new SeismicLab::CRPSSingleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSSingleIndexFreq(IrpsSLFrequencyDistribution* r)
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

RPS_PLUGIN_FUNC IrpsSLFrequencyDistribution* BuildZervaModelFrequencyDistribution()
{
    return new ZervaModelFrequencyDistribution;
}

RPS_PLUGIN_FUNC void DestroyZervaModelFrequencyDistribution(IrpsSLFrequencyDistribution* r)
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

RPS_PLUGIN_FUNC IrpsSLPSDdecompositionMethod* BuildPSDdecomMethod()
{
    return new CCholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyPSDdecomMethod(IrpsSLPSDdecompositionMethod* r)
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

RPS_PLUGIN_FUNC IrpsSLRandomness* BuildRPSUniformRandomPhases()
{
    return new CRPSUniformRandomPhases;
}

RPS_PLUGIN_FUNC void DestroyRPSUniformRandomPhases(IrpsSLRandomness* r)
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

RPS_PLUGIN_FUNC IrpsSLRandomness* BuildRPSRandomPhasesFromFile()
{
    return new CRPSRandomPhasesFromFile;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomPhasesFromFile(IrpsSLRandomness* r)
{
    delete r;
}

//////////////////////////wave propagation effect//////////////////////////////////////////
std::string objNameWav_P = "Exponential Wave Passage effect";
std::string objDescriptionWav_P = "This feature allows the user to the wave passage effect as described in Guoqing Huang et al. (2013).";
std::string objTileWav_P = "New formulation of Cholesky decomposition and applications in stochastic simulation";
std::string objLinkWav_P = "http://dx.doi.org/10.1016/j.probengmech.2013.04.003";
std::string objAuthorsWav_P = "Guoqing Huang, Haili Liao, Mingshui Li";
std::string objDateWav_P = "15/06/2024";
std::string objVersionWav_P = "1.0";

RPS_PLUGIN_FUNC IrpsSLWavePassageEffect* BuildRPSWavePassageEffect()
{
    return new CRPSWavePassageEffect;
}

RPS_PLUGIN_FUNC void DestroyRPSWavePassageEffect(IrpsSLWavePassageEffect* r) {
    delete r;
}

//////////////////////////Clough Penzien Spectrum//////////////////////////////////////////
std::string objNameClo_S = "Clough-Penzien Spectrum";
std::string objDescriptionClo_S = "This feature allows the user to compute seismic ground motion spectrum according to the Clough-Penzien spectral model.";
std::string objTileClo_S = "Dynamics of Structures";
std::string objLinkClo_S = "https://www.csiamerica.com/books/dynamics-of-structures";
std::string objAuthorsClo_S = "Ray Clough & Joe Penzien";
std::string objDateClo_S = "15/06/2024";
std::string objVersionClo_S = "1.0";

RPS_PLUGIN_FUNC IrpsSLSpectrum* BuildCRPSCloughPenzienSpectrum()
{
    return new CRPSCloughPenzienSpectrum;
}

RPS_PLUGIN_FUNC void DestroyCRPSCloughPenzienSpectrum(IrpsSLSpectrum* r) {
    delete r;
}

//////////////////////////Clough Penzien Spectrum//////////////////////////////////////////
std::string objNameTaj_S = "Tajimi-Kanai Spectrum";
std::string objDescriptionTaj_S = "This feature allows the user to compute seismic ground motion spectrum according to the Clough-Penzien spectral model.";
std::string objTileTaj_S = "Semi-empirical formula for the seismic characteristics of the ground";
std::string objLinkTaj_S = "https://doi.org/10.3130/aijsaxx.57.1.0_281";
std::string objAuthorsTaj_S = "Tajimi-Kanai";
std::string objDateTaj_S = "15/06/2024";
std::string objVersionTaj_S = "1.0";

RPS_PLUGIN_FUNC IrpsSLSpectrum* BuildCRPSKanaiTajimiSpectrum()
{
    return new CRPSKanaiTajimiSpectrum;
}

RPS_PLUGIN_FUNC void DestroyCRPSKanaiTajimiSpectrum(IrpsSLSpectrum* r) { delete r; }

//////////////////////////Kougioumtzoglou And Spano Spectrum//////////////////////////////////////////
std::string objNameKou_S = "Kougioumtzoglou And Spano Spectrum 2009";
std::string objDescriptionKou_S = "This feature allows the user to compute seismic ground motion spectrum according to Kougioumtzoglou And Spano spectral model.";
std::string objTileKou_S = "An approximate approach for nonlinear system response determination under evolutionary stochastic excitation ";
std::string objLinkKou_S = "https://www.jstor.org/stable/24111962";
std::string objAuthorsKou_S = "Ioannis A. Kougioumtzoglou and Pol D. Spanos";
std::string objDateKou_S = "07/12/2024";
std::string objVersionKou_S = "1.0";

RPS_PLUGIN_FUNC IrpsSLSpectrum* BuildCRPSKougioumtzoglouAndSpanoSpectrum()
{
    return new CRPSKougioumtzoglouAndSpanoSpectrum;
}

RPS_PLUGIN_FUNC void DestroyCRPSKougioumtzoglouAndSpanoSpectrum(IrpsSLSpectrum* r) { delete r; }

//////////////////////////Clough Penzien Spectrum//////////////////////////////////////////
std::string objNameHuz_S = "Hu Zhou Spectrum";
std::string objDescriptionHuz_S = "This feature allows the user to compute seismic ground motion spectrum according to the Hu Zhou spectral model.";
std::string objTileHuz_S = "The response of the elastic system under the stationary and nonstationary ground motions";
std::string objLinkHuz_S = "https://wiki.labrps.com";
std::string objAuthorsHuz_S = "Hu Y, Zhou X";
std::string objDateHuz_S = "15/06/2024";
std::string objVersionHuz_S = "1.0";

RPS_PLUGIN_FUNC IrpsSLSpectrum* BuildCRPSHuZhouSpectrum()
{
    return new CRPSHuZhouSpectrum;
}

RPS_PLUGIN_FUNC void DestroyCRPSHuZhouSpectrum(IrpsSLSpectrum* r) {
    delete r;
}

//////////////////////////constant modulation//////////////////////////////////////////
std::string objNameCon_M = "Constant Modulation Function";
std::string objDescriptionCon_M = "This feature allows the user to input the modulation where the level of the intensity is constant and equal to 1.0 by default.";
std::string objTileCon_M = "LabRPS";
std::string objLinkCon_M = "https://wiki.labrps.com";
std::string objAuthorsCon_M = "LabRPS";
std::string objDateCon_M = "15/06/2024";
std::string objVersionCon_M = "1.0";

RPS_PLUGIN_FUNC IrpsSLModulation* BuildCRPSConstantModulation()
{
    return new CRPSConstantModulation;
}


RPS_PLUGIN_FUNC void DestroyCRPSConstantModulation(IrpsSLModulation* r) {
    delete r;
}

//////////////////////////Exponntial modulation//////////////////////////////////////////
std::string objNameExp_M = "Exponential Modulation Function";
std::string objDescriptionExp_M = "This feature allows the user to input the modulation based on exponential envelope shape.";
std::string objTileExp_M = "Autocorrelation and power spectral density functions of the Parkfield earthquake of June 27, 1966";
std::string objLinkExp_M = "https://doi.org/10.1785/BSSA0590041475";
std::string objAuthorsExp_M = "Shih-Chi Liu";
std::string objDateExp_M = "15/06/2024";
std::string objVersionExp_M = "1.0";

RPS_PLUGIN_FUNC IrpsSLModulation* BuildCRPSExponentialModulation()
{
    return new CRPSExponentialModulation;
}


RPS_PLUGIN_FUNC void DestroyCRPSExponentialModulation(IrpsSLModulation* r) {
    delete r;
}

//////////////////////////Jennings modulation//////////////////////////////////////////
std::string objNameJen_M = "Jennings Modulation Function";
std::string objDescriptionJen_M = "This feature allows the user to input the modulation based on a compound envelope shape.";
std::string objTileJen_M = "Simulated earthquake motions";
std::string objLinkJen_M = "https://authors.library.caltech.edu/records/t6brp-aj746";
std::string objAuthorsJen_M = "Jennings Paul C., Housner,George W., Tsai N.C. ";
std::string objDateJen_M = "15/06/2024";
std::string objVersionJen_M = "1.0";

RPS_PLUGIN_FUNC IrpsSLModulation* BuildCRPSJenningsEtAl1968Modulation()
{
    return new CRPSJenningsEtAl1968Modulation;
}

RPS_PLUGIN_FUNC void DestroyCRPSJenningsEtAl1968Modulation(IrpsSLModulation* r) {
    delete r;
}

//////////////////////////Saragoni modulation//////////////////////////////////////////
std::string objNameSar_M = "Saragoni and Hart Modulation Function";
std::string objDescriptionSar_M = "This feature allows the user to input the modulation according to Saragoni and Hart envelope shape.";
std::string objTileSar_M = "Simulation of artificial earthquakes";
std::string objLinkSar_M = "https://doi.org/10.1002/eqe.4290020305";
std::string objAuthorsSar_M = "Saragoni G. R. and Hart G. C. ";
std::string objDateSar_M = "15/06/2024";
std::string objVersionSar_M = "1.0";

RPS_PLUGIN_FUNC IrpsSLModulation* BuildCRPSSaragoniHart1974Modulation()
{
    return new CRPSSaragoniHart1974Modulation;
}

RPS_PLUGIN_FUNC void DestroyCRPSSaragoniHart1974Modulation(IrpsSLModulation* r) {
    delete r;
}

//////////////////////////Trapezoidal modulation//////////////////////////////////////////
std::string objNameTra_M = "Trapezoidal Modulation Function";
std::string objDescriptionTra_M = "This feature allows the user to input the modulation based on trapezoidal envelope shape.";
std::string objTileTra_M = "Evaluation of the methods for response analysis under non - stationary excitation";
std::string objLinkTra_M = "https://www.researchgate.net/publication/274471923_Evaluation_of_the_Methods_for_Response_Analysis_under_Non-Stationary_Excitation";
std::string objAuthorsTra_M = "R.S. Jangid and T.K. Datta";
std::string objDateTra_M = "15/06/2024";
std::string objVersionTra_M = "1.0";

RPS_PLUGIN_FUNC IrpsSLModulation* BuildCRPSTrapezoidalModulation()
{
    return new CRPSTrapezoidalModulation;
}

RPS_PLUGIN_FUNC void DestroyCRPSTrapezoidalModulation(IrpsSLModulation* r) {
    delete r;
}

//////////////////////////BogdanoffGold modulation//////////////////////////////////////////
std::string objNameBog_M = "Bogdanoff Goldberg Bernard Modulation Function";
std::string objDescriptionBog_M = "This feature allows the user to input the modulation based on Bogdanoff Goldberg Bernard envelope shape.";
std::string objTileBog_M = "Response of a simple structure to a random earthquake-type disturbance.";
std::string objLinkBog_M = "https://doi.org/10.1785/BSSA0510020293";
std::string objAuthorsBog_M = "Bogdanoff J. L., Goldberg J. E. & Bernard M. C.";
std::string objDateBog_M = "15/06/2024";
std::string objVersionBog_M = "1.0";

RPS_PLUGIN_FUNC IrpsSLModulation* BuildCRPSBogdanoffGoldbergBernardModulation()
{
    return new CRPSBogdanoffGoldbergBernardModulation;
}

RPS_PLUGIN_FUNC void DestroyCRPSBogdanoffGoldbergBernardModulation(IrpsSLModulation* r)
{
    delete r;
}

//////////////////////////Box Car modulation//////////////////////////////////////////
std::string objNameBox_M = "Box Car Modulation Function";
std::string objDescriptionBox_M = "This feature allows the user to input the modulation based on box car envelope shape.";
std::string objTileBox_M = "Evaluation of the methods for response analysis under non - stationary excitation";
std::string objLinkBox_M = "https://www.researchgate.net/publication/274471923_Evaluation_of_the_Methods_for_Response_Analysis_under_Non-Stationary_Excitation";
std::string objAuthorsBox_M = "R.S. Jangid and T.K. Datta";
std::string objDateBox_M = "15/06/2024";
std::string objVersionBox_M = "1.0";

RPS_PLUGIN_FUNC IrpsSLModulation* BuildCRPSBoxCarModulation()
{
    return new CRPSBoxCarModulation;
}

RPS_PLUGIN_FUNC void DestroyCRPSBoxCarModulation(IrpsSLModulation* r) {
    delete r;
}
//////////////////////////Abrahamson Coherence//////////////////////////////////////////
std::string objNameAbr_C = "Abrahamson Coherence Function";
std::string objDescriptionAbr_C = "This feature allows the user to input the coherence based Abrahamson coherence function.";
std::string objTileAbr_C = "Non-stationary stochastic vector processes: seismic ground motion applications";
std::string objLinkAbr_C = "https://doi.org/10.1016/0266-8920(96)00007-0";
std::string objAuthorsAbr_C = "George Deodatis";
std::string objDateAbr_C = "15/06/2024";
std::string objVersionAbr_C = "1.0";

RPS_PLUGIN_FUNC IrpsSLCoherence* BuildCRPSAbrahamsonCoherence()
{
    return new CRPSAbrahamsonCoherence;
}

RPS_PLUGIN_FUNC void DestroyCRPSAbrahamsonCoherence(IrpsSLCoherence* r) {
    delete r;
}

//////////////////////////Harichandran Coherence//////////////////////////////////////////
std::string objNameHar_C = "Harichandran-Vanmarcke Coherence Function";
std::string objDescriptionHar_C = "This feature allows the user to input the modulation based Harichandran-Vanmarcke coherence model.";
std::string objTileHar_C = "Stochastic Variation of Earthquake Ground Motion in Space and Time";
std::string objLinkHar_C = "https://doi.org/10.1061/(ASCE)0733-9399(1986)112:2(154)";
std::string objAuthorsHar_C = "Ronald S. Harichandran and Erik H. Vanmarcke";
std::string objDateHar_C = "15/06/2024";
std::string objVersionHar_C = "1.0";

RPS_PLUGIN_FUNC IrpsSLCoherence* BuildCRPSHarichandranVanmarckeCoherence()
{
    return new CRPSHarichandranVanmarckeCoherence;
}

RPS_PLUGIN_FUNC void DestroyCRPSHarichandranVanmarckeCoherence(IrpsSLCoherence* r) {
    delete r;
}

//////////////////////////Loh And Lin Coherence//////////////////////////////////////////
std::string objNameLoh_C = "Loh and Lin Coherence Function";
std::string objDescriptionLoh_C = "This feature allows the user to input the modulation based Loh and Lin coherence model.";
std::string objTileLoh_C = "Directionality and simulation in spatial variation of seismic waves";
std::string objLinkLoh_C = "https://doi.org/10.1016/0141-0296(90)90019-O";
std::string objAuthorsLoh_C = "Chin-Hsiung Loh and Su-Gen Lin";
std::string objDateLoh_C = "15/06/2024";
std::string objVersionLoh_C = "1.0";

RPS_PLUGIN_FUNC IrpsSLCoherence* BuildCRPSLohAndLinCoherence()
{
    return new CRPSLohAndLinCoherence;
}

RPS_PLUGIN_FUNC void DestroyCRPSLohAndLinCoherence(IrpsSLCoherence* r) {
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
    if (SeismicLab::GeneralSpatialDistribution::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::GeneralSpatialDistribution::init();
    }
    if (SeismicLab::WLUniformDistributionLocations::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::WLUniformDistributionLocations::init();
    }
    if (SeismicLab::CWLHorizontalUniformDistribution::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CWLHorizontalUniformDistribution::init();
    }
     if (SeismicLab::CWLVerticalUniformDistribution::getClassTypeId() == Base::Type::badType()) {
         SeismicLab::CWLVerticalUniformDistribution::init();
     }
    if (SeismicLab::CRPSDoubleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSDoubleIndexFrequency::init();
    }
    if (SeismicLab::CRPSSingleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSSingleIndexFrequency::init();
    }
    if (SeismicLab::CCholeskyDecomposition::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CCholeskyDecomposition::init();
    }
    if (SeismicLab::CRPSUniformRandomPhases::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSUniformRandomPhases::init();
    }
    if (SeismicLab::CRPSRandomPhasesFromFile::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSRandomPhasesFromFile::init();
    }
    if (SeismicLab::CRPSWavePassageEffect::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSWavePassageEffect::init();
    }
    if (SeismicLab::ZervaModelFrequencyDistribution::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::ZervaModelFrequencyDistribution::init();
    }
    if (SeismicLab::CRPSCloughPenzienSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSCloughPenzienSpectrum::init();
    }
    if (SeismicLab::CRPSKanaiTajimiSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSKanaiTajimiSpectrum::init();
    }
    if (SeismicLab::CRPSHuZhouSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSHuZhouSpectrum::init();
    }

     if (SeismicLab::CRPSConstantModulation::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSConstantModulation::init();
    }
    if (SeismicLab::CRPSExponentialModulation::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSExponentialModulation::init();
    }
    if (SeismicLab::CRPSJenningsEtAl1968Modulation::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSJenningsEtAl1968Modulation::init();
    }
    if (SeismicLab::CRPSSaragoniHart1974Modulation::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSSaragoniHart1974Modulation::init();
    }
    if (SeismicLab::CRPSTrapezoidalModulation::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSTrapezoidalModulation::init();
    }
    if (SeismicLab::CRPSBogdanoffGoldbergBernardModulation::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSBogdanoffGoldbergBernardModulation::init();
    }
    if (SeismicLab::CRPSBoxCarModulation::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSBoxCarModulation::init();
    }
    if (SeismicLab::CRPSAbrahamsonCoherence::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSAbrahamsonCoherence::init();
    }
    if (SeismicLab::CRPSHarichandranVanmarckeCoherence::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSHarichandranVanmarckeCoherence::init();
    }
    if (SeismicLab::CRPSLohAndLinCoherence::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSLohAndLinCoherence::init();
    }
    if (SeismicLab::CRPSKougioumtzoglouAndSpanoSpectrum::getClassTypeId() == Base::Type::badType()) {
        SeismicLab::CRPSKougioumtzoglouAndSpanoSpectrum::init();
    }
    return 1;
}

PLUGIN_INIT()
{
    InitializeLocationDistribution(objNameGen_D, strPluginName, objTileGen_D, objLinkGen_D, objAuthorsGen_D, objDateGen_D, objVersionGen_D, stationarity);
    InitializeLocationDistribution(objNameUni_D, strPluginName, objTileUni_D, objLinkUni_D, objAuthorsUni_D, objDateUni_D, objVersionUni_D, stationarity);
    InitializeLocationDistribution(objNameHor_D, strPluginName, objTileHor_D, objLinkHor_D, objAuthorsHor_D, objDateHor_D, objVersionHor_D, stationarity);
    InitializeLocationDistribution(objNameVer_D, strPluginName, objTileVer_D, objLinkVer_D, objAuthorsVer_D, objDateVer_D, objVersionVer_D, stationarity);
    InitializeLocationDistribution(objNameGri_P, strPluginName, objTileGri_P, objLinkGri_P, objAuthorsGri_P, objDateGri_P, objVersionGri_P, stationarity);

    InitializeFrequencyDistribution(objNameDou_I, strPluginName, objTileDou_I, objLinkDou_I, objAuthorsDou_I, objDateDou_I, objVersionDou_I, stationarity);
    InitializeFrequencyDistribution(objNameSin_I, strPluginName, objTileSin_I, objLinkSin_I, objAuthorsSin_I, objDateSin_I, objVersionSin_I, stationarity);
    InitializeFrequencyDistribution(objNameZer_F, strPluginName, objTileZer_F, objLinkZer_F, objAuthorsZer_F, objDateZer_F, objVersionZer_F, stationarity);

    InitializePSDdecomMethod(objNameCho_D, strPluginName, objTileCho_D, objLinkCho_D, objAuthorsCho_D, objDateCho_D, objVersionCho_D, stationarity);

    InitializeRandomness(objNameUni_R, strPluginName, objTileUni_R, objLinkUni_R, objAuthorsUni_R, objDateUni_R, objVersionUni_R, stationarity);
    InitializeRandomness(objNameUni_I, strPluginName, objTileUni_I, objLinkUni_I, objAuthorsUni_I, objDateUni_I, objVersionUni_I, stationarity);

    InitializeWavePassageEffect(objNameWav_P, strPluginName, objTileWav_P, objLinkWav_P, objAuthorsWav_P, objDateWav_P, objVersionWav_P, stationarity);

    InitializeSpectrum(objNameClo_S, strPluginName, objTileClo_S, objLinkClo_S, objAuthorsClo_S, objDateClo_S, objVersionClo_S, stationarity);
    InitializeSpectrum(objNameTaj_S, strPluginName, objTileTaj_S, objLinkTaj_S, objAuthorsTaj_S, objDateTaj_S, objVersionTaj_S, stationarity);
    InitializeSpectrum(objNameHuz_S, strPluginName, objTileHuz_S, objLinkHuz_S, objAuthorsHuz_S, objDateHuz_S, objVersionHuz_S, stationarity);
    InitializeSpectrum(objNameKou_S, strPluginName, objTileKou_S, objLinkKou_S, objAuthorsKou_S, objDateKou_S, objVersionKou_S, !stationarity);

    InitializeModulation(objNameCon_M, strPluginName, objTileCon_M, objLinkCon_M, objAuthorsCon_M, objDateCon_M, objVersionCon_M, stationarity);
    InitializeModulation(objNameExp_M, strPluginName, objTileExp_M, objLinkExp_M, objAuthorsExp_M, objDateExp_M, objVersionExp_M, stationarity);
    InitializeModulation(objNameJen_M, strPluginName, objTileJen_M, objLinkJen_M, objAuthorsJen_M, objDateJen_M, objVersionJen_M, stationarity);
    InitializeModulation(objNameSar_M, strPluginName, objTileSar_M, objLinkSar_M, objAuthorsSar_M, objDateSar_M, objVersionSar_M, stationarity);
    InitializeModulation(objNameTra_M, strPluginName, objTileTra_M, objLinkTra_M, objAuthorsTra_M, objDateTra_M, objVersionTra_M, stationarity);
    InitializeModulation(objNameBog_M, strPluginName, objTileBog_M, objLinkBog_M, objAuthorsBog_M, objDateBog_M, objVersionBog_M, stationarity);
    InitializeModulation(objNameBox_M, strPluginName, objTileBox_M, objLinkBox_M, objAuthorsBox_M, objDateBox_M, objVersionBox_M, stationarity);

    InitializeCoherence(objNameAbr_C, strPluginName, objTileAbr_C, objLinkAbr_C, objAuthorsAbr_C, objDateAbr_C, objVersionAbr_C, stationarity);
    InitializeCoherence(objNameHar_C, strPluginName, objTileHar_C, objLinkHar_C, objAuthorsHar_C, objDateHar_C, objVersionHar_C, stationarity);
    InitializeCoherence(objNameLoh_C, strPluginName, objTileLoh_C, objLinkLoh_C, objAuthorsLoh_C, objDateLoh_C, objVersionLoh_C, stationarity);
    
    return 1;
}


INSTALL_PLUGIN()
{
    RegisterLocationDistribution(objNameGen_D, strPluginName, objDescriptionGen_D, BuildGeneralSpatialDistribution, DestroyGeneralSpatialDistribution);
    RegisterLocationDistribution(objNameUni_D, strPluginName, objDescriptionUni_D, BuildUniformSpatialDistribution, DestroyUniformSpatialDistribution);
    RegisterLocationDistribution(objNameHor_D, strPluginName, objDescriptionHor_D, BuildHorizontalDistr, DestroyHorizontalDistr);
    RegisterLocationDistribution(objNameVer_D, strPluginName, objDescriptionVer_D, BuildVerticalDistr, DestroyVerticalDistr);
    RegisterLocationDistribution(objNameGri_P, strPluginName, objDescriptionGri_P, BuildGridPoints, DestroyGridPoints);
    
    RegisterFrequencyDistribution(objNameDou_I, strPluginName, objDescriptionDou_I, BuildRPSDoubleIndexFreq, DestroyRPSDoubleIndexFreq);
    RegisterFrequencyDistribution(objNameSin_I, strPluginName, objDescriptionSin_I, BuildRPSSingleIndexFreq, DestroyRPSSingleIndexFreq);
    RegisterFrequencyDistribution(objNameZer_F, strPluginName, objDescriptionZer_F, BuildZervaModelFrequencyDistribution, DestroyZervaModelFrequencyDistribution);

    RegisterPSDdecomMethod(objNameCho_D, strPluginName, objDescriptionCho_D, BuildPSDdecomMethod, DestroyPSDdecomMethod);
    
    RegisterRandomness(objNameUni_R, strPluginName, objDescriptionUni_R, BuildRPSUniformRandomPhases, DestroyRPSUniformRandomPhases);
    RegisterRandomness(objNameUni_I, strPluginName, objDescriptionUni_I, BuildRPSRandomPhasesFromFile, DestroyRPSRandomPhasesFromFile);

    RegisterWavePassageEffect(objNameWav_P, strPluginName, objDescriptionWav_P, BuildRPSWavePassageEffect, DestroyRPSWavePassageEffect);

    RegisterSpectrum(objNameClo_S, strPluginName, objDescriptionClo_S, BuildCRPSCloughPenzienSpectrum, DestroyCRPSCloughPenzienSpectrum);
    RegisterSpectrum(objNameTaj_S, strPluginName, objDescriptionTaj_S, BuildCRPSKanaiTajimiSpectrum, DestroyCRPSKanaiTajimiSpectrum);
    RegisterSpectrum(objNameHuz_S, strPluginName, objDescriptionHuz_S, BuildCRPSHuZhouSpectrum, DestroyCRPSHuZhouSpectrum);
    RegisterSpectrum(objNameKou_S, strPluginName, objDescriptionKou_S, BuildCRPSKougioumtzoglouAndSpanoSpectrum, DestroyCRPSKougioumtzoglouAndSpanoSpectrum);

    RegisterModulation(objNameCon_M, strPluginName, objDescriptionCon_M, BuildCRPSConstantModulation, DestroyCRPSConstantModulation);
    RegisterModulation(objNameExp_M, strPluginName, objDescriptionExp_M, BuildCRPSExponentialModulation, DestroyCRPSExponentialModulation);
    RegisterModulation(objNameJen_M, strPluginName, objDescriptionJen_M, BuildCRPSJenningsEtAl1968Modulation, DestroyCRPSJenningsEtAl1968Modulation);
    RegisterModulation(objNameSar_M, strPluginName, objDescriptionSar_M, BuildCRPSSaragoniHart1974Modulation, DestroyCRPSSaragoniHart1974Modulation);
    RegisterModulation(objNameTra_M, strPluginName, objDescriptionTra_M, BuildCRPSTrapezoidalModulation, DestroyCRPSTrapezoidalModulation);
    RegisterModulation(objNameBog_M, strPluginName, objDescriptionBog_M, BuildCRPSBogdanoffGoldbergBernardModulation, DestroyCRPSBogdanoffGoldbergBernardModulation);
    RegisterModulation(objNameBox_M, strPluginName, objDescriptionBox_M, BuildCRPSBoxCarModulation, DestroyCRPSBoxCarModulation);

    RegisterCoherence(objNameAbr_C, strPluginName, objDescriptionAbr_C, BuildCRPSAbrahamsonCoherence, DestroyCRPSAbrahamsonCoherence);
    RegisterCoherence(objNameHar_C, strPluginName, objDescriptionHar_C, BuildCRPSHarichandranVanmarckeCoherence, DestroyCRPSHarichandranVanmarckeCoherence);
    RegisterCoherence(objNameLoh_C, strPluginName, objDescriptionLoh_C, BuildCRPSLohAndLinCoherence, DestroyCRPSLohAndLinCoherence);

    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterLocationDistribution(objNameGen_D, strPluginName);
    UnregisterLocationDistribution(objNameUni_D, strPluginName);
    UnregisterLocationDistribution(objNameHor_D, strPluginName);
    UnregisterLocationDistribution(objNameVer_D, strPluginName);
    UnregisterLocationDistribution(objNameGri_P, strPluginName);

    UnregisterFrequencyDistribution(objNameDou_I, strPluginName);
    UnregisterFrequencyDistribution(objNameSin_I, strPluginName);
    UnregisterFrequencyDistribution(objNameZer_F, strPluginName);
  
    UnregisterPSDdecomMethod(objNameCho_D, strPluginName);

    UnregisterRandomness(objNameUni_R, strPluginName);
    UnregisterRandomness(objNameUni_I, strPluginName);

    UnregisterWavePassageEffect(objNameWav_P, strPluginName);

    UnregisterSpectrum(objNameClo_S, strPluginName);
    UnregisterSpectrum(objNameTaj_S, strPluginName);
    UnregisterSpectrum(objNameHuz_S, strPluginName);
    UnregisterSpectrum(objNameKou_S, strPluginName);

    UnregisterModulation(objNameCon_M, strPluginName);
    UnregisterModulation(objNameExp_M, strPluginName);
    UnregisterModulation(objNameJen_M, strPluginName);
    UnregisterModulation(objNameSar_M, strPluginName);
    UnregisterModulation(objNameTra_M, strPluginName);
    UnregisterModulation(objNameBog_M, strPluginName);
    UnregisterModulation(objNameBox_M, strPluginName);

    UnregisterCoherence(objNameAbr_C, strPluginName);
    UnregisterCoherence(objNameHar_C, strPluginName);
    UnregisterCoherence(objNameLoh_C, strPluginName);


    return 1;
}




