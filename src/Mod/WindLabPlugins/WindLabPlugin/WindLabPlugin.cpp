/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "PreCompiled.h"

#include <QString>
#include "WLHorizontalUniformDistribution.h"
#include "WLVerticalUniformDistribution.h"
#include "RPSWLPowerLowProfile.h"
#include "RPSLogarithmicLowProfile.h"
#include "RPSDHLowProfile.h"
#include "RPSKaimalSpectr.h"
#include "RPSDoubleIndexFrequency.h"
#include "RPSSingleIndexFrequency.h"
#include "ZervaModelFrequencyDistribution.h"
#include "RPSDavenportCoherence.h"
#include "CholeskyDecomposition.h"
#include "RPSUniformRandomPhases.h"
#include "RPSRandomPhasesFromFile.h"
#include "SineModulation.h"
#include "ExpoModulation.h"
#include "ThreeParaModulation.h"
#include "RPSDeodatis1996.h"
#include "GeneralSpatialDistribution.h"
#include "RPSKaimalAcrossSpectr.h"
#include "RPSKaimalVerticalSpectr.h"
#include "RPSDavenportSpectrum.h"
#include "RPSHarrisSpectrum.h"
#include "RPSSimuAcrossWindSpectrum.h"
#include "RPSSimuAlongWindSpectrum.h"
#include "RPSSimuVerticalWindSpectrum.h"
#include "RPSvonKarmanAlongWindSpectrum.h"
#include "RPSvonKarmanAcrossWindSpectrum.h"
#include "RPSvonKarmanVerticalWindSpectrum.h"
#include "WLUniformDistributionLocations.h"
#include "RPSWavePassageEffect.h"
#include "TargetCorrelation.h"
#include "RPSKrenkCoherence.h"
#include "RPSTurbulenceIntensityASCE798.h"
#include "WLGridPoints.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>
#include <Base/Console.h>

#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>


// namespace WindLabPlugin
// {
// class Module: public Py::ExtensionModule<Module>
// {
// public:
//     Module() : Py::ExtensionModule<Module>("WindLabPlugin")
//     {
//         initialize("This module is the WindLabPlugin module.");// register with Python
//     }

//     virtual ~Module() {}

// private:
// };

// PyObject* initModule() { return Base::Interpreter().addModule(new Module); }

// }// namespace WindLab

// /* Python entry */
// PyMOD_INIT_FUNC(WindLabPlugin)
// {
//     PyObject* mod = WindLabPlugin::initModule();
//     Base::Console().Log("Loading WindLabPlugin module... done\n");
//     PyMOD_Return(mod);
// }


std::string strPluginName = "WindLabPlugin";
bool stationarity = true;

PLUGIN_NAME("WindLabPlugin");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin adds a series of functionalities to LabRPS for the simulation of wind velocity");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("15/06/2024");

using namespace WindLab;
using namespace WindLabAPI;

std::string objNameGen_D = "General Distribution";
std::string objDescriptionGen_D = "This feature allows the user to add simulation points to WindLab simulation by points coordinates";
std::string objTileGen_D = "LabRPS";
std::string objLinkGen_D = "https://wiki.labrps.com";
std::string objAuthorsGen_D = "LabRPS";
std::string objDateGen_D = "15/06/2024";
std::string objVersionGen_D = "1.0";

RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildGeneralSpatialDistribution()
{
    return new GeneralSpatialDistribution;
}

RPS_PLUGIN_FUNC void DestroyGeneralSpatialDistribution(WindLabAPI::IrpsWLLocationDistribution* r)
{
    delete r;
}

std::string objNameUni_D = "Uniform Distribution";
std::string objDescriptionUni_D = "This feature allows the user to add simulation points that are uniformly distributed along a linne in space";
std::string objTileUni_D = "LabRPS";
std::string objLinkUni_D = "https://wiki.labrps.com";
std::string objAuthorsUni_D = "LabRPS";
std::string objDateUni_D = "15/06/2024";
std::string objVersionUni_D = "1.0";

RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildUniformSpatialDistribution()
{
    return new WLUniformDistributionLocations;
}

RPS_PLUGIN_FUNC void DestroyUniformSpatialDistribution(WindLabAPI::IrpsWLLocationDistribution* r)
{
    delete r;
}

std::string objNameHor_D = "Horizontal Distribution";
std::string objDescriptionHor_D = "This feature allows the user to add simulation points that are uniformly distributed on horizontal line in space";
std::string objTileHor_D = "LabRPS";
std::string objLinkHor_D = "https://wiki.labrps.com";
std::string objAuthorsHor_D = "LabRPS";
std::string objDateHor_D = "15/06/2024";
std::string objVersionHor_D = "1.0";

RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildHorizontalDistr()
{
    return new CWLHorizontalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyHorizontalDistr(IrpsWLLocationDistribution* r)
{
    delete r;
}

std::string objNameVer_D = "Vertical Distribution";
std::string objDescriptionVer_D = "This feature allows the user to add simulation points that are uniformly distributed on vertical line in space";
std::string objTileVer_D = "LabRPS";
std::string objLinkVer_D = "https://wiki.labrps.com";
std::string objAuthorsVer_D = "LabRPS";
std::string objDateVer_D = "15/06/2024";
std::string objVersionVer_D = "1.0";

RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildVerticalDistr()
{
    return new CWLVerticalUniformDistribution;
}

RPS_PLUGIN_FUNC void DestroyVerticalDistr(IrpsWLLocationDistribution* r)
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

RPS_PLUGIN_FUNC IrpsWLLocationDistribution* BuildGridPoints()
{
    return new WLGridPoints;
}

RPS_PLUGIN_FUNC void DestroyGridPoints(IrpsWLLocationDistribution* r) {
    delete r;
}


std::string objNamePow_L = "Power Law Profile";
std::string objDescriptionPow_L = "This feature allows the computation of mean wind speed according to the power law profile";
std::string objTilePow_L = "Advanced Structural Wind Engineering";
std::string objLinkPow_L = "https://link.springer.com/book/10.1007/978-4-431-54337-4";
std::string objAuthorsPow_L = "Yukio Tamura, Ahsan Kareem";
std::string objDatePow_L = "15/06/2024";
std::string objVersionPow_L = "1.0";

RPS_PLUGIN_FUNC IrpsWLMean* BuildRPSPowerLowProfile()
{
    return new RPSWLPowerLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSPowerLowProfile(IrpsWLMean* r)
{
    delete r;
}

std::string objNameLog_L = "Logarithmic Law Profile";
std::string objDescriptionLog_L = "This feature allows the computation of mean wind speed according to the logarithmic law profile";
std::string objTileLog_L = "Advanced Structural Wind Engineering";
std::string objLinkLog_L = "https://link.springer.com/book/10.1007/978-4-431-54337-4";
std::string objAuthorsLog_L = "Yukio Tamura, Ahsan Kareem";
std::string objDateLog_L = "15/06/2024";
std::string objVersionLog_L = "1.0";

RPS_PLUGIN_FUNC IrpsWLMean* BuildRPSLogarithmicLowProfile()
{
    return new RPSLogarithmicLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSLogarithmicLowProfile(IrpsWLMean* r)
{
    delete r;
}

std::string objNameDea_H = "Deaves and Harris Model";
std::string objDescriptionDea_H = "This feature allows the computation of mean wind speed according to the Deaves and Harris model";
std::string objTileDea_H = "Advanced Structural Wind Engineering";
std::string objLinkDea_H = "https://link.springer.com/book/10.1007/978-4-431-54337-4";
std::string objAuthorsDea_H = "Yukio Tamura, Ahsan Kareem";
std::string objDateDea_H = "15/06/2024";
std::string objVersionDea_H = "1.0";

RPS_PLUGIN_FUNC IrpsWLMean* BuildRPSDHLowProfile()
{
    return new CRPSDHLowProfile;
}

RPS_PLUGIN_FUNC void DestroyRPSDHLowProfile(IrpsWLMean* r)
{
    delete r;
}

std::string objNameDou_I = "Double Index Frequency Discretization";
std::string objDescriptionDou_I = "This feature allows the user to discretize frequency according to the double index frequency ";
std::string objTileDou_I = "Simulation of Ergodic Multivariate Stochastic Processes";
std::string objLinkDou_I = "https://doi.org/10.1061/(ASCE)0733-9399(1996)122:8(778)";
std::string objAuthorsDou_I = "George Deodatis";
std::string objDateDou_I = "15/06/2024";
std::string objVersionDou_I = "1.0";

RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution* BuildRPSDoubleIndexFreq()
{
    return new CRPSDoubleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSDoubleIndexFreq(IrpsWLFrequencyDistribution* r)
{
    delete r;
}

std::string objNameSin_I = "Single Index Frequency Discretization";
std::string objDescriptionSin_I = "This feature allows the user to discretize frequency according to the single index frequency ";
std::string objTileSin_I = "Simulation of Stochastic Processes by Spectral Representation";
std::string objLinkSin_I = "https://doi.org/10.1115/1.3119501";
std::string objAuthorsSin_I = "Masanobu Shinozuka, George Deodatis";
std::string objDateSin_I = "15/06/2024";
std::string objVersionSin_I = "1.0";

RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution* BuildRPSSingleIndexFreq()
{
    return new WindLab::CRPSSingleIndexFrequency;
}

RPS_PLUGIN_FUNC void DestroyRPSSingleIndexFreq(IrpsWLFrequencyDistribution* r)
{
    delete r;
}

std::string objNameZer_F = "Zerva Frequency Discretization";
std::string objDescriptionZer_F = "This feature allows the user to discretize frequency according to the Zerva frequency ";
std::string objTileZer_F = "LabRPS";
std::string objLinkZer_F = "https://wiki.labrps.com";
std::string objAuthorsZer_F = "LabRPS";
std::string objDateZer_F = "15/06/2024";
std::string objVersionZer_F = "1.0";

RPS_PLUGIN_FUNC IrpsWLFrequencyDistribution* BuildZervaModelFrequencyDistribution()
{
    return new ZervaModelFrequencyDistribution;
}

RPS_PLUGIN_FUNC void DestroyZervaModelFrequencyDistribution(IrpsWLFrequencyDistribution* r)
{
    delete r;
}

std::string objNameKai_A = "Kaimal Along Wind Spectrum";
std::string objDescriptionKai_A = "This feature allows the user to compute power spectrum density according to the Kaimal along wind spectrum model (1972).";
std::string objTileKai_A = "Spectral characteristics of surface-layer turbulence";
std::string objLinkKai_A = "https://doi.org/10.1002/qj.49709841707";
std::string objAuthorsKai_A = "J. C. Kaimal, J. C. Wyngaard, Y. Izumi, O. R. Coté";
std::string objDateKai_A = "15/06/2024";
std::string objVersionKai_A = "1.0";

RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSKaimalSpectr()
{
    return new CRPSKaimalSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalSpectr(IrpsWLXSpectrum* r)
{
    delete r;
}

std::string objNameKa_Ac = "Kaimal Across Wind Spectrum";
std::string objDescriptionKa_Ac = "This feature allows the user to compute power spectrum density according to the Kaimal across wind spectrum model (1972).";
std::string objTileKa_Ac = "Spectral characteristics of surface-layer turbulence";
std::string objLinkKa_Ac = "https://doi.org/10.1002/qj.49709841707";
std::string objAuthorsKa_Ac = "J. C. Kaimal, J. C. Wyngaard, Y. Izumi, O. R. Coté";
std::string objDateKa_Ac = "15/06/2024";
std::string objVersionKa_Ac = "1.0";
RPS_PLUGIN_FUNC IrpsWLYSpectrum* BuildRPSKaimalAcrossSpectr()
{
    return new CRPSKaimalAcrossSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalAcrossSpectr(IrpsWLYSpectrum* r)
{
    delete r;
}

std::string objNameKai_V = "Kaimal Vertical Wind Spectrum";
std::string objDescriptionKai_V = "This feature allows the user to compute power spectrum density according to the Kaimal vertical wind spectrum model (1972).";
std::string objTileKai_V = "Spectral characteristics of surface-layer turbulence";
std::string objLinkKai_V = "https://doi.org/10.1002/qj.49709841707";
std::string objAuthorsKai_V = "J. C. Kaimal, J. C. Wyngaard, Y. Izumi, O. R. Coté";
std::string objDateKai_V = "15/06/2024";
std::string objVersionKai_V = "1.0";
RPS_PLUGIN_FUNC IrpsWLZSpectrum* BuildRPSKaimalVerticalSpectr()
{
    return new CRPSKaimalVerticalSpectr;
}

RPS_PLUGIN_FUNC void DestroyRPSKaimalVerticalSpectr(IrpsWLZSpectrum* r)
{
    delete r;
}

std::string objNameDav_A = "Davenport Along Wind Spectrum";
std::string objDescriptionDav_A = "This feature allows the user to compute power spectrum density according to the Davenport along wind spectrum model.";
std::string objTileDav_A = "The spectrum of horizontal gustiness near the ground in high winds";
std::string objLinkDav_A = "https://doi.org/10.1002/qj.49708737208";
std::string objAuthorsDav_A = "A. G. Davenport";
std::string objDateDav_A = "15/06/2024";
std::string objVersionDav_A = "1.0";
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSDavenportSpectrum()
{
    return new CRPSDavenportSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSDavenportSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

std::string objNameHar_A = "Harris Along Wind Spectrum";
std::string objDescriptionHar_A = "This feature allows the user to compute power spectrum density according to the Harris along wind spectrum model (1970).";
std::string objTileHar_A = "To be given";
std::string objLinkHar_A = "https://wiki.labrps.com";
std::string objAuthorsHar_A = "Harris";
std::string objDateHar_A = "15/06/2024";
std::string objVersionHar_A = "1.0";
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSHarrisSpectrum()
{
    return new CRPSHarrisSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSHarrisSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

std::string objNameSim_A = "Simu Along Wind Spectrum";
std::string objDescriptionSim_A = "This feature allows the user to compute power spectrum density according to the Simu along wind spectrum model (1974).";
std::string objTileSim_A = "Wind Spectra and Dynamic Alongwind Responsel";
std::string objLinkSim_A = "https://doi.org/10.1061/JSDEAG.0003880";
std::string objAuthorsSim_A = "Emil Simiu";
std::string objDateSim_A = "15/06/2024";
std::string objVersionSim_A = "1.0";

RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSSimuAlongWindSpectrum()
{
    return new CRPSSimuAlongWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuAlongWindSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

std::string objNameSi_Ac = "Simu Across Wind Spectrum";
std::string objDescriptionSi_Ac = "This feature allows the user to compute power spectrum density according to the Simu across wind spectrum model (1974).";
std::string objTileSi_Ac = "Wind Spectra and Dynamic Alongwind Responsel";
std::string objLinkSi_Ac = "https://doi.org/10.1061/JSDEAG.0003880";
std::string objAuthorsSi_Ac = "Emil Simiu";
std::string objDateSi_Ac = "15/06/2024";
std::string objVersionSi_Ac = "1.0";
RPS_PLUGIN_FUNC IrpsWLYSpectrum* BuildRPSSimuAcrossWindSpectrum()
{
    return new CRPSSimuAcrossWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuAcrossWindSpectrum(IrpsWLYSpectrum* r)
{
    delete r;
}

std::string objNameSim_V = "Simu Vertical Wind Spectrum";
std::string objDescriptionSim_V = "This feature allows the user to compute power spectrum density according to the Simu vertical wind spectrum model (1974).";
std::string objTileSim_V = "Wind Spectra and Dynamic Alongwind Responsel";
std::string objLinkSim_V = "https://doi.org/10.1061/JSDEAG.0003880";
std::string objAuthorsSim_V = "Emil Simiu";
std::string objDateSim_V = "15/06/2024";
std::string objVersionSim_V = "1.0";
RPS_PLUGIN_FUNC IrpsWLZSpectrum* BuildRPSSimuVerticalWindSpectrum()
{
    return new CRPSSimuVerticalWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSSimuVerticalWindSpectrum(IrpsWLZSpectrum* r)
{
    delete r;
}

std::string objNameKar_A = "von Karman Along Wind Spectrum";
std::string objDescriptionKar_A = "This feature allows the user to compute power spectrum density according to the Von Karman along wind spectrum model (1974).";
std::string objTileKar_A = "Progress in the Statistical Theory of Turbulence";
std::string objLinkKar_A = "http://www.jstor.org/stable/88224";
std::string objAuthorsKar_A = "Theodore Von Karman";
std::string objDateKar_A = "15/06/2024";
std::string objVersionKar_A = "1.0";
RPS_PLUGIN_FUNC IrpsWLXSpectrum* BuildRPSVonKarmanAlongWindSpectrum()
{
    return new CRPSvonKarmanAlongWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanAlongWindSpectrum(IrpsWLXSpectrum* r)
{
    delete r;
}

std::string objNameK_Acc = "von Karman Across Wind Spectrum";
std::string objDescriptionK_Acc = "This feature allows the user to compute power spectrum density according to the Von Karman across wind spectrum model (1974).";
std::string objTileK_Acc = "Progress in the Statistical Theory of Turbulence";
std::string objLinkK_Acc = "http://www.jstor.org/stable/88224";
std::string objAuthorsK_Acc = "Theodore Von Karman";
std::string objDateK_Acc = "15/06/2024";
std::string objVersionK_Acc = "1.0";
RPS_PLUGIN_FUNC IrpsWLYSpectrum* BuildRPSVonKarmanAcrossWindSpectrum()
{
    return new CRPSvonKarmanAcrossWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanAcrossWindSpectrum(IrpsWLYSpectrum* r)
{
    delete r;
}

std::string objNameKar_V = "von Karman Vertival Wind Spectrum";
std::string objDescriptionKar_V = "This feature allows the user to compute power spectrum density according to the Von Karman vertical wind spectrum model (1974).";
std::string objTileKar_V = "Progress in the Statistical Theory of Turbulence";
std::string objLinkKar_V = "http://www.jstor.org/stable/88224";
std::string objAuthorsKar_V = "Theodore Von Karman";
std::string objDateKar_V = "15/06/2024";
std::string objVersionKar_V = "1.0";
RPS_PLUGIN_FUNC IrpsWLZSpectrum* BuildRPSVonKarmanVerticalWindSpectrum()
{
    return new CRPSvonKarmanVerticalWindSpectrum;
}

RPS_PLUGIN_FUNC void DestroyRPSVonKarmanVerticalWindSpectrum(IrpsWLZSpectrum* r)
{
    delete r;
}

std::string objNameDav_C = "Davenport Coherence Function";
std::string objDescriptionDav_C = "This feature allows the user to compute spatial coherence according to Davenport coherence function (1967).";
std::string objTileDav_C = "The dependence of wind loads on meteorological parameters";
std::string objLinkDav_C = "https://www.aivc.org/resource/dependence-wind-loads-meteorological-parameters";
std::string objAuthorsDav_C = "Davenport A.G.";
std::string objDateDav_C = "15/06/2024";
std::string objVersionDav_C = "1.0";
RPS_PLUGIN_FUNC IrpsWLCoherence* BuildRPSDavenportCoh()
{
    return new CRPSDavenportCoherence;
}

RPS_PLUGIN_FUNC void DestroyRPSDavenportCoh(IrpsWLCoherence* r)
{
    delete r;
}

std::string objNameCho_D = "Cholesky Decomposition";
std::string objDescriptionCho_D = "This feature allows the user to decompose a power spectral density matrix as described in Dedatis (1996).";
std::string objTileCho_D = "Simulation of Ergodic Multivariate Stochastic Processes";
std::string objLinkCho_D = "https://doi.org/10.1061/(ASCE)0733-9399(1996)122:8(778)";
std::string objAuthorsCho_D = "George Deodatis";
std::string objDateCho_D = "15/06/2024";
std::string objVersionCho_D = "1.0";
RPS_PLUGIN_FUNC IrpsWLPSDdecompositionMethod* BuildPSDdecomMethod()
{
    return new CCholeskyDecomposition;
}

RPS_PLUGIN_FUNC void DestroyPSDdecomMethod(IrpsWLPSDdecompositionMethod* r)
{
    delete r;
}

std::string objNameUni_R = "Uniform Random Phases";
std::string objDescriptionUni_R = "This feature allows the user to generate random phases as described in Dedatis (1996).";
std::string objTileUni_R = "Simulation of Ergodic Multivariate Stochastic Processes";
std::string objLinkUni_R = "https://doi.org/10.1061/(ASCE)0733-9399(1996)122:8(778)";
std::string objAuthorsUni_R = "George Deodatis";
std::string objDateUni_R = "15/06/2024";
std::string objVersionUni_R = "1.0";
RPS_PLUGIN_FUNC IrpsWLRandomness* BuildRPSUniformRandomPhases()
{
    return new CRPSUniformRandomPhases;
}

RPS_PLUGIN_FUNC void DestroyRPSUniformRandomPhases(IrpsWLRandomness* r)
{
    delete r;
}

std::string objNameUni_I = "Uniform Random Phases Import";
std::string objDescriptionUni_I = "This feature allows the user to import uniform random phases from file";
std::string objTileUni_I = "LabRPS";
std::string objLinkUni_I = "https://wiki.labrps.com";
std::string objAuthorsUni_I = "LabRPS";
std::string objDateUni_I = "15/06/2024";
std::string objVersionUni_I = "1.0";
RPS_PLUGIN_FUNC IrpsWLRandomness* BuildRPSRandomPhasesFromFile()
{
    return new CRPSRandomPhasesFromFile;
}

RPS_PLUGIN_FUNC void DestroyRPSRandomPhasesFromFile(IrpsWLRandomness* r)
{
    delete r;
}

std::string objNameSin_M = "Sine Wave Modulation Function";
std::string objDescriptionSin_M = "This feature allows the user to compute modulation function as described in Dae-Kun Kwon1 and Ahsan Kareem (2009)";
std::string objTileSin_M = "LabRPS";
std::string objLinkSin_M = "https://wiki.labrps.com";
std::string objAuthorsSin_M = "Dae-Kun Kwon1 and Ahsan Kareem";
std::string objDateSin_M = "15/06/2024";
std::string objVersionSin_M = "1.0";
RPS_PLUGIN_FUNC IrpsWLModulation* BuildSineModulation()
{
    return new CSineModulation;
}

RPS_PLUGIN_FUNC void DestroySineModulation(IrpsWLModulation* r)
{
    delete r;
}

std::string objNameExp_M = "Exponential Modulation Function";
std::string objDescriptionExp_M = "This feature allows the user to compute modulation function as described in Priestley (1965)";
std::string objTileExp_M = "Evolutionary spectra and non-stationary processes";
std::string objLinkExp_M = "https://doi.org/10.1111/j.2517-6161.1965.tb01488.x";
std::string objAuthorsExp_M = "M. B. Priestley";
std::string objDateExp_M = "15/06/2024";
std::string objVersionExp_M = "1.0";
RPS_PLUGIN_FUNC IrpsWLModulation* BuildExpoModulation()
{
    return new CExpoModulation;
}

RPS_PLUGIN_FUNC void DestroyExpoModulation(IrpsWLModulation* r)
{
    delete r;
}

std::string objNameThr_M = "Three Parameter Modulation Function";
std::string objDescriptionThr_M = "This feature allows the user to compute modulation function as described in Xinzhong Chen (2008)";
std::string objTileThr_M = "Analysis of along wind tall building response to transient nonstationary winds";
std::string objLinkThr_M = "https://doi.org/10.1061/(ASCE)0733-9445(2008)134:5(782)";
std::string objAuthorsThr_M = "Xinzhong Chen";
std::string objDateThr_M = "15/06/2024";
std::string objVersionThr_M = "1.0";
RPS_PLUGIN_FUNC IrpsWLModulation* BuildThreeParaModulation()
{
    return new CThreeParaModulation;
}

RPS_PLUGIN_FUNC void DestroyThreeParaModulation(IrpsWLModulation* r)
{
    delete r;
}

std::string objNameDeo_S = "Deodatis Simulation Method";
std::string objDescriptionDeo_S = "This feature allows the user to simulation ergodic random wind velocity as described in Dedatis (1996).";
std::string objTileDeo_S = "Simulation of Ergodic Multivariate Stochastic Processes";
std::string objLinkDeo_S = "https://doi.org/10.1061/(ASCE)0733-9399(1996)122:8(778)";
std::string objAuthorsDeo_S = "George Deodatis";
std::string objDateDeo_S = "15/06/2024";
std::string objVersionDeo_S = "1.0";
RPS_PLUGIN_FUNC IrpsWLSimuMethod* BuildRPSDeodatis1996()
{
    return new CRPSDeodatis1996;
}

RPS_PLUGIN_FUNC void DestroyRPSDeodatis1996(IrpsWLSimuMethod* r)
{
    delete r;
}
std::string objNameWav_P = "Exponential Wave Passage effect";
std::string objDescriptionWav_P = "This feature allows the user to the wave passage effect as described in Guoqing Huang et al. (2013).";
std::string objTileWav_P = "New formulation of Cholesky decomposition and applications in stochastic simulation";
std::string objLinkWav_P = "http://dx.doi.org/10.1016/j.probengmech.2013.04.003";
std::string objAuthorsWav_P = "Guoqing Huang, Haili Liao, Mingshui Li";
std::string objDateWav_P = "15/06/2024";
std::string objVersionWav_P = "1.0";
RPS_PLUGIN_FUNC IrpsWLWavePassageEffect* BuildRPSWavePassageEffect()
{
    return new CRPSWavePassageEffect;
}

RPS_PLUGIN_FUNC void DestroyRPSWavePassageEffect(IrpsWLWavePassageEffect* r) {
    delete r;
}


std::string objNameTar_C = "Target Colerration Tool";
std::string objDescriptionTar_C = "This feature allows the user to compute correlation function from the target power spectral density function";
std::string objTileTar_C = "LabRPS";
std::string objLinkTar_C = "https://wiki.labrps.com";
std::string objAuthorsTar_C = "LabRPS";
std::string objDateTar_C = "15/06/2024";
std::string objVersionTar_C = "1.0";
RPS_PLUGIN_FUNC IrpsWLTableTool* BuildRPSTargetCorrelation()
{
    return new TargetCorrelation;
}

RPS_PLUGIN_FUNC void DestroyRPSTargetCorrelation(IrpsWLTableTool* r) {
    delete r;
}

std::string objNameKre_C = "Krenk Coherence Function";
std::string objDescriptionKre_C = "This feature allows the user to compute spatial coherence according to Krenk coherence function as described in Gonglian et al.";
std::string objTileKre_C = "Analysis of the wind field characteristics induced by the 2019 Typhoon Bailu for the high-speed railway bridge crossing China’s southeast bay";
std::string objLinkKre_C = "https://doi.org/10.1016/j.jweia.2021.104557";
std::string objAuthorsKre_C = "Gonglian Dai, Zhiwei Xu, Y. Frank Chen c, Richard G.J. Flay, Huiming Rao";
std::string objDateKre_C = "15/06/2024";
std::string objVersionKre_C = "1.0";
RPS_PLUGIN_FUNC IrpsWLCoherence* BuildRPSKrenkCoherence()
{
    return new RPSKrenkCoherence;
}

RPS_PLUGIN_FUNC void DestroyRPSKrenkCoherence(IrpsWLCoherence* r) {
    delete r;
}

std::string objNameAsc_T = "ASCE 7.98 Turbulence Intensity";
std::string objDescriptionAsc_T = "This feature allows the user to compute turbulence intensity according to ASCE 7.98.";
std::string objTileAsc_T = "ASCE 7.98";
std::string objLinkAsc_T = "https://www.asce.org/";
std::string objAuthorsAsc_T = "ASCE";
std::string objDateAsc_T = "15/06/2024";
std::string objVersionAsc_T = "1.0";
RPS_PLUGIN_FUNC IrpsWLTurbulenceIntensity* BuildRPSTurbulenceIntensityASCE798()
{
    return new RPSTurbulenceIntensityASCE798;
}

RPS_PLUGIN_FUNC void DestroyRPSTurbulenceIntensityASCE798(IrpsWLTurbulenceIntensity* r)
{
    delete r;
}

PLUGIN_INIT_TYPE()
{ 
    if (WindLab::GeneralSpatialDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::GeneralSpatialDistribution::init();
    }
    if (WindLab::WLUniformDistributionLocations::getClassTypeId() == Base::Type::badType()) {
        WindLab::WLUniformDistributionLocations::init();
    }
    if (WindLab::CWLHorizontalUniformDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::CWLHorizontalUniformDistribution::init();
    }
    if (WindLab::CWLVerticalUniformDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::CWLVerticalUniformDistribution::init();
    }
    if (WindLab::RPSWLPowerLowProfile::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSWLPowerLowProfile::init();
    }
    if (WindLab::RPSLogarithmicLowProfile::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSLogarithmicLowProfile::init();
    }
    if (WindLab::CRPSDHLowProfile::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDHLowProfile::init();
    }
    if (WindLab::CRPSDoubleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDoubleIndexFrequency::init();
    }
    if (WindLab::CRPSSingleIndexFrequency::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSingleIndexFrequency::init();
    }
    if (WindLab::ZervaModelFrequencyDistribution::getClassTypeId() == Base::Type::badType()) {
        WindLab::ZervaModelFrequencyDistribution::init();
    }
    if (WindLab::CRPSKaimalSpectr::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSKaimalSpectr::init();
    }
    if (WindLab::CRPSKaimalAcrossSpectr::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSKaimalAcrossSpectr::init();
    }
    if (WindLab::CRPSKaimalVerticalSpectr::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSKaimalVerticalSpectr::init();
    }
    if (WindLab::CRPSDavenportSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDavenportSpectrum::init();
    }
    if (WindLab::CRPSHarrisSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSHarrisSpectrum::init();
    }
    if (WindLab::CRPSSimuAlongWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSimuAlongWindSpectrum::init();
    }
    if (WindLab::CRPSSimuAcrossWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSimuAcrossWindSpectrum::init();
    }
    if (WindLab::CRPSSimuVerticalWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSSimuVerticalWindSpectrum::init();
    }
    if (WindLab::CRPSvonKarmanAlongWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSvonKarmanAlongWindSpectrum::init();
    }
    if (WindLab::CRPSvonKarmanAcrossWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSvonKarmanAcrossWindSpectrum::init();
    }
    if (WindLab::CRPSvonKarmanVerticalWindSpectrum::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSvonKarmanVerticalWindSpectrum::init();
    }
    if (WindLab::CRPSDavenportCoherence::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDavenportCoherence::init();
    }
    if (WindLab::CCholeskyDecomposition::getClassTypeId() == Base::Type::badType()) {
        WindLab::CCholeskyDecomposition::init();
    }
    if (WindLab::CRPSUniformRandomPhases::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSUniformRandomPhases::init();
    }
    if (WindLab::CRPSRandomPhasesFromFile::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSRandomPhasesFromFile::init();
    }
    if (WindLab::CSineModulation::getClassTypeId() == Base::Type::badType()) {
        WindLab::CSineModulation::init();
    }
    if (WindLab::CExpoModulation::getClassTypeId() == Base::Type::badType()) {
        WindLab::CExpoModulation::init();
    }
    if (WindLab::CThreeParaModulation::getClassTypeId() == Base::Type::badType()) {
        WindLab::CThreeParaModulation::init();
    }
    if (WindLab::CRPSDeodatis1996::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSDeodatis1996::init();
    }
    if (WindLab::CRPSWavePassageEffect::getClassTypeId() == Base::Type::badType()) {
        WindLab::CRPSWavePassageEffect::init();
    }
    if (WindLab::TargetCorrelation::getClassTypeId() == Base::Type::badType()) {
        WindLab::TargetCorrelation::init();
    }
    if (WindLab::RPSKrenkCoherence::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSKrenkCoherence::init();
    }
    if (WindLab::RPSTurbulenceIntensityASCE798::getClassTypeId() == Base::Type::badType()) {
        WindLab::RPSTurbulenceIntensityASCE798::init();
    }
    if (WindLab::WLGridPoints::getClassTypeId() == Base::Type::badType()) {
        WindLab::WLGridPoints::init();
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
   
    InitializeMean(objNamePow_L, strPluginName, objTilePow_L, objLinkPow_L, objAuthorsPow_L, objDatePow_L, objVersionPow_L, stationarity);
    InitializeMean(objNameLog_L, strPluginName, objTileLog_L, objLinkLog_L, objAuthorsLog_L, objDateLog_L, objVersionLog_L, stationarity);
    InitializeMean(objNameDea_H, strPluginName, objTileDea_H, objLinkDea_H, objAuthorsDea_H, objDateDea_H, objVersionDea_H, stationarity);
    
    InitializeFrequencyDistribution(objNameDou_I, strPluginName, objTileDou_I, objLinkDou_I, objAuthorsDou_I, objDateDou_I, objVersionDou_I, stationarity);
    InitializeFrequencyDistribution(objNameSin_I, strPluginName, objTileSin_I, objLinkSin_I, objAuthorsSin_I, objDateSin_I, objVersionSin_I, stationarity);
    InitializeFrequencyDistribution(objNameZer_F, strPluginName, objTileZer_F, objLinkZer_F, objAuthorsZer_F, objDateZer_F, objVersionZer_F, stationarity);
    
    InitializeXSpectrum(objNameKai_A, strPluginName, objTileKai_A, objLinkKai_A, objAuthorsKai_A, objDateKai_A, objVersionKai_A, stationarity);
    InitializeYSpectrum(objNameKa_Ac, strPluginName, objTileKa_Ac, objLinkKa_Ac, objAuthorsKa_Ac, objDateKa_Ac, objVersionKa_Ac, stationarity);
    InitializeZSpectrum(objNameKai_V, strPluginName, objTileKai_V, objLinkKai_V, objAuthorsKai_V, objDateKai_V, objVersionKai_V, stationarity);
    InitializeXSpectrum(objNameDav_A, strPluginName, objTileDav_A, objLinkDav_A, objAuthorsDav_A, objDateDav_A, objVersionDav_A, stationarity);
    InitializeXSpectrum(objNameHar_A, strPluginName, objTileHar_A, objLinkHar_A, objAuthorsHar_A, objDateHar_A, objVersionHar_A, stationarity);
    InitializeXSpectrum(objNameSim_A, strPluginName, objTileSim_A, objLinkSim_A, objAuthorsSim_A, objDateSim_A, objVersionSim_A, stationarity);
    InitializeYSpectrum(objNameSi_Ac, strPluginName, objTileSi_Ac, objLinkSi_Ac, objAuthorsSi_Ac, objDateSi_Ac, objVersionSi_Ac, stationarity);
    InitializeZSpectrum(objNameSim_V, strPluginName, objTileSim_V, objLinkSim_V, objAuthorsSim_V, objDateSim_V, objVersionSim_V, stationarity);
    InitializeXSpectrum(objNameKar_A, strPluginName, objTileKar_A, objLinkKar_A, objAuthorsKar_A, objDateKar_A, objVersionKar_A, stationarity);
    InitializeYSpectrum(objNameK_Acc, strPluginName, objTileK_Acc, objLinkK_Acc, objAuthorsK_Acc, objDateK_Acc, objVersionK_Acc, stationarity);
    InitializeZSpectrum(objNameKar_V, strPluginName, objTileKar_V, objLinkKar_V, objAuthorsKar_V, objDateKar_V, objVersionKar_V, stationarity);

    InitializeCoherence(objNameDav_C, strPluginName, objTileDav_C, objLinkDav_C, objAuthorsDav_C, objDateDav_C, objVersionDav_C, stationarity);
    InitializeCoherence(objNameKre_C, strPluginName, objTileKre_C, objLinkKre_C, objAuthorsKre_C, objDateKre_C, objVersionKre_C, stationarity);

    InitializePSDdecomMethod(objNameCho_D, strPluginName, objTileCho_D, objLinkCho_D, objAuthorsCho_D, objDateCho_D, objVersionCho_D, stationarity);

    InitializeRandomness(objNameUni_R, strPluginName, objTileUni_R, objLinkUni_R, objAuthorsUni_R, objDateUni_R, objVersionUni_R, stationarity);
    InitializeRandomness(objNameUni_I, strPluginName, objTileUni_I, objLinkUni_I, objAuthorsUni_I, objDateUni_I, objVersionUni_I, stationarity);

    InitializeModulation(objNameThr_M, strPluginName, objTileThr_M, objLinkThr_M, objAuthorsThr_M, objDateThr_M, objVersionThr_M, stationarity);
    InitializeModulation(objNameExp_M, strPluginName, objTileExp_M, objLinkExp_M, objAuthorsExp_M, objDateExp_M, objVersionExp_M, stationarity);
    InitializeModulation(objNameSin_M, strPluginName, objTileSin_M, objLinkSin_M, objAuthorsSin_M, objDateSin_M, objVersionSin_M, stationarity);

    InitializeSimuMethod(objNameDeo_S, strPluginName, objTileDeo_S, objLinkDeo_S, objAuthorsDeo_S, objDateDeo_S, objVersionDeo_S, stationarity);
    InitializeWavePassageEffect(objNameWav_P, strPluginName, objTileWav_P, objLinkWav_P, objAuthorsWav_P, objDateWav_P, objVersionWav_P, stationarity);
    InitializeTableTool(objNameTar_C, strPluginName, objTileTar_C, objLinkTar_C, objAuthorsTar_C, objDateTar_C, objVersionTar_C, stationarity);
    InitializeTurbulenceIntensity(objNameAsc_T, strPluginName, objTileAsc_T, objLinkAsc_T, objAuthorsAsc_T, objDateAsc_T, objVersionAsc_T, stationarity);
    
    return 1;
}


INSTALL_PLUGIN()
{
    RegisterLocationDistribution(objNameGen_D, strPluginName, objDescriptionGen_D, BuildGeneralSpatialDistribution, DestroyGeneralSpatialDistribution);
    RegisterLocationDistribution(objNameUni_D, strPluginName, objDescriptionUni_D, BuildUniformSpatialDistribution, DestroyUniformSpatialDistribution);
    RegisterLocationDistribution(objNameHor_D, strPluginName, objDescriptionHor_D, BuildHorizontalDistr, DestroyHorizontalDistr);
    RegisterLocationDistribution(objNameVer_D, strPluginName, objDescriptionVer_D, BuildVerticalDistr, DestroyVerticalDistr);
    RegisterLocationDistribution(objNameGri_P, strPluginName, objDescriptionGri_P, BuildGridPoints, DestroyGridPoints);
   
    RegisterMean(objNamePow_L, strPluginName, objDescriptionPow_L, BuildRPSPowerLowProfile, DestroyRPSPowerLowProfile);
    RegisterMean(objNameLog_L, strPluginName, objDescriptionLog_L, BuildRPSLogarithmicLowProfile, DestroyRPSLogarithmicLowProfile);
    RegisterMean(objNameDea_H, strPluginName, objDescriptionDea_H, BuildRPSDHLowProfile, DestroyRPSDHLowProfile);

    RegisterFrequencyDistribution(objNameDou_I, strPluginName, objDescriptionDou_I, BuildRPSDoubleIndexFreq, DestroyRPSDoubleIndexFreq);
    RegisterFrequencyDistribution(objNameSin_I, strPluginName, objDescriptionSin_I, BuildRPSSingleIndexFreq, DestroyRPSSingleIndexFreq);
    RegisterFrequencyDistribution(objNameZer_F, strPluginName, objDescriptionZer_F, BuildZervaModelFrequencyDistribution, DestroyZervaModelFrequencyDistribution);

    RegisterXSpectrum(objNameKai_A, strPluginName, objDescriptionKai_A, BuildRPSKaimalSpectr, DestroyRPSKaimalSpectr);
    RegisterYSpectrum(objNameKa_Ac, strPluginName, objDescriptionKa_Ac, BuildRPSKaimalAcrossSpectr, DestroyRPSKaimalAcrossSpectr);
    RegisterZSpectrum(objNameKai_V, strPluginName, objDescriptionKai_V, BuildRPSKaimalVerticalSpectr, DestroyRPSKaimalVerticalSpectr);
    RegisterXSpectrum(objNameDav_A, strPluginName, objDescriptionDav_A, BuildRPSDavenportSpectrum, DestroyRPSDavenportSpectrum);
    RegisterXSpectrum(objNameHar_A, strPluginName, objDescriptionHar_A, BuildRPSHarrisSpectrum, DestroyRPSHarrisSpectrum);
    RegisterXSpectrum(objNameSim_A, strPluginName, objDescriptionSim_A, BuildRPSSimuAlongWindSpectrum, DestroyRPSSimuAlongWindSpectrum);
    RegisterYSpectrum(objNameSi_Ac, strPluginName, objDescriptionSi_Ac, BuildRPSSimuAcrossWindSpectrum, DestroyRPSSimuAcrossWindSpectrum);
    RegisterZSpectrum(objNameSim_V, strPluginName, objDescriptionSim_V, BuildRPSSimuVerticalWindSpectrum, DestroyRPSSimuVerticalWindSpectrum);
    RegisterXSpectrum(objNameKar_A, strPluginName, objDescriptionKar_A, BuildRPSVonKarmanAlongWindSpectrum, DestroyRPSVonKarmanAlongWindSpectrum);
    RegisterYSpectrum(objNameK_Acc, strPluginName, objDescriptionK_Acc, BuildRPSVonKarmanAcrossWindSpectrum, DestroyRPSVonKarmanAcrossWindSpectrum);
    RegisterZSpectrum(objNameKar_V, strPluginName, objDescriptionKar_V, BuildRPSVonKarmanVerticalWindSpectrum, DestroyRPSVonKarmanVerticalWindSpectrum);

  
    RegisterCoherence(objNameDav_C, strPluginName, objDescriptionDav_C, BuildRPSDavenportCoh, DestroyRPSDavenportCoh);
    RegisterCoherence(objNameKre_C, strPluginName, objDescriptionKre_C, BuildRPSKrenkCoherence, DestroyRPSKrenkCoherence);

    
    RegisterPSDdecomMethod(objNameCho_D, strPluginName, objDescriptionCho_D, BuildPSDdecomMethod, DestroyPSDdecomMethod);
    
    RegisterRandomness(objNameUni_R, strPluginName, objDescriptionUni_R, BuildRPSUniformRandomPhases, DestroyRPSUniformRandomPhases);
    RegisterRandomness(objNameUni_I, strPluginName, objDescriptionUni_I, BuildRPSRandomPhasesFromFile, DestroyRPSRandomPhasesFromFile);
    
    RegisterModulation(objNameThr_M, strPluginName, objDescriptionThr_M, BuildThreeParaModulation, DestroyThreeParaModulation);
    RegisterModulation(objNameExp_M, strPluginName, objDescriptionExp_M, BuildExpoModulation, DestroyExpoModulation);
    RegisterModulation(objNameSin_M, strPluginName, objDescriptionSin_M, BuildSineModulation, DestroySineModulation);
    
    RegisterSimuMethod(objNameDeo_S, strPluginName, objDescriptionDeo_S, BuildRPSDeodatis1996, DestroyRPSDeodatis1996);
    RegisterWavePassageEffect(objNameWav_P, strPluginName, objDescriptionWav_P, BuildRPSWavePassageEffect, DestroyRPSWavePassageEffect);
    RegisterTableTool(objNameTar_C, strPluginName, objDescriptionTar_C, BuildRPSTargetCorrelation, DestroyRPSTargetCorrelation);
    RegisterTurbulenceIntensity(objNameAsc_T, strPluginName, objDescriptionAsc_T, BuildRPSTurbulenceIntensityASCE798, DestroyRPSTurbulenceIntensityASCE798);

    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterLocationDistribution(objNameGen_D, strPluginName);
    UnregisterLocationDistribution(objNameUni_D, strPluginName);
    UnregisterLocationDistribution(objNameHor_D, strPluginName);
    UnregisterLocationDistribution(objNameVer_D, strPluginName);
    UnregisterLocationDistribution(objNameGri_P, strPluginName);
   
    UnregisterMean(objNamePow_L, strPluginName);
    UnregisterMean(objNameLog_L, strPluginName);
    UnregisterMean(objNameDea_H, strPluginName);

    UnregisterFrequencyDistribution(objNameDou_I, strPluginName);
    UnregisterFrequencyDistribution(objNameSin_I, strPluginName);
    UnregisterFrequencyDistribution(objNameZer_F, strPluginName);

    UnregisterXSpectrum(objNameKai_A, strPluginName);
    UnregisterYSpectrum(objNameKa_Ac, strPluginName);
    UnregisterZSpectrum(objNameKai_V, strPluginName);
    UnregisterXSpectrum(objNameDav_A, strPluginName);
    UnregisterXSpectrum(objNameHar_A, strPluginName);
    UnregisterXSpectrum(objNameSim_A, strPluginName);
    UnregisterYSpectrum(objNameSi_Ac, strPluginName);
    UnregisterZSpectrum(objNameSim_V, strPluginName);
    UnregisterXSpectrum(objNameKar_A, strPluginName);
    UnregisterYSpectrum(objNameK_Acc, strPluginName);
    UnregisterZSpectrum(objNameKar_V, strPluginName);

  
    UnregisterCoherence(objNameDav_C, strPluginName);
    UnregisterCoherence(objNameKre_C, strPluginName);

    
    UnregisterPSDdecomMethod(objNameCho_D, strPluginName);
    
    UnregisterRandomness(objNameUni_R, strPluginName);
    UnregisterRandomness(objNameUni_I, strPluginName);
    
    UnregisterModulation(objNameThr_M, strPluginName);
    UnregisterModulation(objNameExp_M, strPluginName);
    UnregisterModulation(objNameSin_M, strPluginName);
    
    UnregisterSimuMethod(objNameDeo_S, strPluginName);
    UnregisterWavePassageEffect(objNameWav_P, strPluginName);
    UnregisterTableTool(objNameTar_C, strPluginName);
    UnregisterTurbulenceIntensity(objNameAsc_T, strPluginName);

    return 1;
}




