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

#include "RandomnessProviders.h"
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>

using namespace WindLabAPI;

std::string strPluginName = "RPSRandomnessProviders";

PLUGIN_NAME("RPSRandomnessProviders");
RANDOM_PHENOMENON("Wind Velocity");
PLUGIN_AUTHOR("LabRPS Team");
PLUGIN_DESCRIPTION("This plugin implements various random distributions, correponding probability density functions and cumulative distribution functions");
PLUGIN_VERSION("1.00");
LABRPS_VERSION("0.1");
API_VERSION("0.1");
PLUGIN_RELEASE_DATE("22/11/2022");

RPS_PLUGIN_FUNC IrpsWLRandomness *BuildGaussianRandomnessProvider()
{
    return new RandomnessProviders::CGaussianRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyGaussianRandomnessProvider(IrpsWLRandomness *r)
{
	delete r;
}

std::string objNameWeibull = "Weibull Randomness Provider";
std::string objDescriptionWeibull = "This object implements the Weibull distribution";


RPS_PLUGIN_FUNC IrpsWLRandomness *BuildWeibullRandomnessProvider()
{
     return new RandomnessProviders::CWeibullRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyWeibullRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objName = "Gaussian Randomness Provider";
std::string objDescription = "This object implements the Gaussian distribution";
std::string objTile = "Non-Uniform Random Variate Generation";
std::string objLink = "http://www.eirene.de/Devroye.pdf";
std::string objAuthors = "Luc Devroye";
std::string objDate = "1986";
std::string objVersion = "1.00";

RPS_PLUGIN_FUNC IrpsWLRandomness *BuildExponentialRandomnessProvider()
{
     return new RandomnessProviders::CExponentialRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyExponentialRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameEx = "Exponential Randomness Provider";
std::string objDescriptionEx = "This object implements the Exponential distribution";

RPS_PLUGIN_FUNC IrpsWLRandomness *BuildLaplaceRandomnessProvider()
{
     return new RandomnessProviders::CLaplaceRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyLaplaceRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameLaplace = "Laplace Randomness Provider";
std::string objDescriptionLaplace = "This object implements the Laplace distribution";

//
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildExponentialPowerRandomnessProvider()
{
     return new RandomnessProviders::CExponentialPowerRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyExponentialPowerRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameExponentialPower = "Exponential Power Randomness Provider";
std::string objDescriptionExponentialPower = "This object implements the Exponential Power distribution";

//Cauchy
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildCauchyRandomnessProvider()
{
     return new RandomnessProviders::CCauchyRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyCauchyRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameCauchy = "Cauchy Randomness Provider";
std::string objDescriptionCauchy = "This object implements the Cauchy distribution";

//Rayleigh
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildRayleighRandomnessProvider()
{
     return new RandomnessProviders::CRayleighRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyRayleighRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameRayleigh = "Rayleigh Randomness Provider";
std::string objDescriptionRayleigh = "This object implements the Rayleigh distribution";

//RayleighTail
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildRayleighTailRandomnessProvider()
{
     return new RandomnessProviders::CRayleighTailRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyRayleighTailRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameRayleighTail = "Rayleigh Tail Randomness Provider";
std::string objDescriptionRayleighTail = "This object implements the RayleighTail distribution";

//Landau
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildLandauRandomnessProvider()
{
     return new RandomnessProviders::CLandauRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyLandauRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameLandau = "Landau Randomness Provider";
std::string objDescriptionLandau = "This object implements the Landau distribution";

//LevyAlphaStable
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildLevyAlphaStableRandomnessProvider()
{
    return new RandomnessProviders::CLevyAlphaStableRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyLevyAlphaStableRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameLevyAlphaStable = "LevyAlphaStable Randomness Provider";
std::string objDescriptionLevyAlphaStable = "This object implements the LevyAlphaStable distribution";

//LevySkewAlphaStable
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildLevySkewAlphaStableRandomnessProvider()
{
    return new RandomnessProviders::CLevySkewAlphaStableRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyLevySkewAlphaStableRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameLevySkewAlphaStable = "LevySkewAlphaStable Randomness Provider";
std::string objDescriptionLevySkewAlphaStable = "This object implements the LevySkewAlphaStable distribution";

//Flat
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildFlatRandomnessProvider()
{
    return new RandomnessProviders::CFlatRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyFlatRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameFlat = "Flat Randomness Provider";
std::string objDescriptionFlat = "This object implements the Flat distribution";

//Gamma
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildGammaRandomnessProvider()
{
    return new RandomnessProviders::CGammaRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyGammaRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameGamma = "Gamma Randomness Provider";
std::string objDescriptionGamma = "This object implements the Gamma distribution";

//Lognormal
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildLognormalRandomnessProvider()
{
    return new RandomnessProviders::CLognormalRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyLognormalRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameLognormal = "Lognormal Randomness Provider";
std::string objDescriptionLognormal = "This object implements the Lognormal distribution";

//ChiSquared
RPS_PLUGIN_FUNC IrpsWLRandomness *BuildChiSquaredRandomnessProvider()
{
    return new RandomnessProviders::CChiSquaredRandomnessProvider;
}

RPS_PLUGIN_FUNC void DestroyChiSquaredRandomnessProvider(IrpsWLRandomness *r)
{
    delete r;
}

std::string objNameChiSquared = "ChiSquared Randomness Provider";
std::string objDescriptionChiSquared = "This object implements the ChiSquared distribution";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ADD PDF

RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildWeibullPDF()
{
     return new RandomnessProviders::CWeibullPDF;
}

RPS_PLUGIN_FUNC void DestroyWeibullPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameWeibullPDF = "Weibull PDF";
std::string objDescriptionWeibullPDF = "This object implements the Weibull PDF";

RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildGaussianPDF()
{
     return new RandomnessProviders::CGaussianPDF;
}

RPS_PLUGIN_FUNC void DestroyGaussianPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameGaussianPDF = "Gaussian PDF";
std::string objDescriptionGaussianPDF = "This object implements the Gaussian PDF";

RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildExponentialPDF()
{
     return new RandomnessProviders::CExponentialPDF;
}

RPS_PLUGIN_FUNC void DestroyExponentialPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameExPDF = "Exponential PDF";
std::string objDescriptionExPDF = "This object implements the Exponential PDF";

RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildLaplacePDF()
{
     return new RandomnessProviders::CLaplacePDF;
}

RPS_PLUGIN_FUNC void DestroyLaplacePDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameLaplacePDF = "Laplace PDF";
std::string objDescriptionLaplacePDF = "This object implements the Laplace PDF";

//
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildExponentialPowerPDF()
{
     return new RandomnessProviders::CExponentialPowerPDF;
}

RPS_PLUGIN_FUNC void DestroyExponentialPowerPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameExponentialPowerPDF = "Exponential Power PDF";
std::string objDescriptionExponentialPowerPDF = "This object implements the Exponential Power PDF";

//Cauchy
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildCauchyPDF()
{
    return new RandomnessProviders::CCauchyPDF;
}

RPS_PLUGIN_FUNC void DestroyCauchyPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameCauchyPDF = "Cauchy PDF";
std::string objDescriptionCauchyPDF = "This object implements the Cauchy PDF";

//Rayleigh
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildRayleighPDF()
{
    return new RandomnessProviders::CRayleighPDF;
}

RPS_PLUGIN_FUNC void DestroyRayleighPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameRayleighPDF = "Rayleigh PDF";
std::string objDescriptionRayleighPDF = "This object implements the Rayleigh PDF";

//RayleighTail
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildRayleighTailPDF()
{
    return new RandomnessProviders::CRayleighTailPDF;
}

RPS_PLUGIN_FUNC void DestroyRayleighTailPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameRayleighTailPDF = "Rayleigh Tail PDF";
std::string objDescriptionRayleighTailPDF = "This object implements the RayleighTail PDF";

//Landau
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildLandauPDF()
{
    return new RandomnessProviders::CLandauPDF;
}

RPS_PLUGIN_FUNC void DestroyLandauPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameLandauPDF = "Landau PDF";
std::string objDescriptionLandauPDF = "This object implements the Landau PDF";

//Flat
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildFlatPDF()
{
    return new RandomnessProviders::CFlatPDF;
}

RPS_PLUGIN_FUNC void DestroyFlatPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameFlatPDF = "Flat PDF";
std::string objDescriptionFlatPDF = "This object implements the Flat PDF";

//Gamma
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildGammaPDF()
{
    return new RandomnessProviders::CGammaPDF;
}

RPS_PLUGIN_FUNC void DestroyGammaPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameGammaPDF = "Gamma PDF";
std::string objDescriptionGammaPDF = "This object implements the Gamma PDF";

//Lognormal
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildLognormalPDF()
{
    return new RandomnessProviders::CLognormalPDF;
}

RPS_PLUGIN_FUNC void DestroyLognormalPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameLognormalPDF = "Lognormal PDF";
std::string objDescriptionLognormalPDF = "This object implements the Lognormal PDF";

//ChiSquared
RPS_PLUGIN_FUNC IrpsWLProbabilityDensityFunction *BuildChiSquaredPDF()
{
    return new RandomnessProviders::CChiSquaredPDF;
}

RPS_PLUGIN_FUNC void DestroyChiSquaredPDF(IrpsWLProbabilityDensityFunction *r)
{
    delete r;
}

std::string objNameChiSquaredPDF = "ChiSquared PDF";
std::string objDescriptionChiSquaredPDF = "This object implements the ChiSquared PDF";



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ADD CPD

//Weibull
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildWeibullCPD()
{
    return new RandomnessProviders::CWeibullCPD;
}

RPS_PLUGIN_FUNC void DestroyWeibullCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameWeibullCPD = "Weibull CPD";
std::string objDescriptionWeibullCPD = "This object implements the Weibull CPD";

//
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildGaussianCPD()
{
    return new RandomnessProviders::CGaussianCPD;
}

RPS_PLUGIN_FUNC void DestroyGaussianCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameGaussianCPD = "Gaussian CPD";
std::string objDescriptionGaussianCPD = "This object implements the Gaussian CPD";

RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildExponentialCPD()
{
    return new RandomnessProviders::CExponentialCPD;
}

RPS_PLUGIN_FUNC void DestroyExponentialCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameExCPD = "Exponential CPD";
std::string objDescriptionExCPD = "This object implements the Exponential CPD";

RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildLaplaceCPD()
{
    return new RandomnessProviders::CLaplaceCPD;
}

RPS_PLUGIN_FUNC void DestroyLaplaceCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameLaplaceCPD = "Laplace CPD";
std::string objDescriptionLaplaceCPD = "This object implements the Laplace CPD";

//
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildExponentialPowerCPD()
{
    return new RandomnessProviders::CExponentialPowerCPD;
}

RPS_PLUGIN_FUNC void DestroyExponentialPowerCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameExponentialPowerCPD = "Exponential Power CPD";
std::string objDescriptionExponentialPowerCPD = "This object implements the Exponential Power CPD";

//Cauchy
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildCauchyCPD()
{
    return new RandomnessProviders::CCauchyCPD;
}

RPS_PLUGIN_FUNC void DestroyCauchyCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameCauchyCPD = "Cauchy CPD";
std::string objDescriptionCauchyCPD = "This object implements the Cauchy CPD";

//Rayleigh
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildRayleighCPD()
{
    return new RandomnessProviders::CRayleighCPD;
}

RPS_PLUGIN_FUNC void DestroyRayleighCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameRayleighCPD = "Rayleigh CPD";
std::string objDescriptionRayleighCPD = "This object implements the Rayleigh CPD";

//Flat
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildFlatCPD()
{
    return new RandomnessProviders::CFlatCPD;
}

RPS_PLUGIN_FUNC void DestroyFlatCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameFlatCPD = "Flat CPD";
std::string objDescriptionFlatCPD = "This object implements the Flat CPD";

//Gamma
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildGammaCPD()
{
    return new RandomnessProviders::CGammaCPD;
}

RPS_PLUGIN_FUNC void DestroyGammaCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameGammaCPD = "Gamma CPD";
std::string objDescriptionGammaCPD = "This object implements the Gamma CPD";

//Lognormal
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildLognormalCPD()
{
    return new RandomnessProviders::CLognormalCPD;
}

RPS_PLUGIN_FUNC void DestroyLognormalCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameLognormalCPD = "Lognormal CPD";
std::string objDescriptionLognormalCPD = "This object implements the Lognormal CPD";

//ChiSquared
RPS_PLUGIN_FUNC IrpsWLCumulativeProbabilityDistribution *BuildChiSquaredCPD()
{
    return new RandomnessProviders::CChiSquaredCPD;
}

RPS_PLUGIN_FUNC void DestroyChiSquaredCPD(IrpsWLCumulativeProbabilityDistribution *r)
{
    delete r;
}

std::string objNameChiSquaredCPD = "ChiSquared CPD";
std::string objDescriptionChiSquaredCPD = "This object implements the ChiSquared CPD";
bool stationarity = true;

PLUGIN_INIT_TYPE()
{
     if (RandomnessProviders::CGaussianRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CGaussianRandomnessProvider::init();
    }
     if (RandomnessProviders::CWeibullRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CWeibullRandomnessProvider::init();
    }
     if (RandomnessProviders::CExponentialRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CExponentialRandomnessProvider::init();
    }
     if (RandomnessProviders::CLaplaceRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLaplaceRandomnessProvider::init();
    }
     if (RandomnessProviders::CExponentialPowerRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CExponentialPowerRandomnessProvider::init();
    }
     if (RandomnessProviders::CCauchyRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CCauchyRandomnessProvider::init();
    }
     if (RandomnessProviders::CRayleighRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CRayleighRandomnessProvider::init();
    }
     if (RandomnessProviders::CRayleighTailRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CRayleighTailRandomnessProvider::init();
    }
     if (RandomnessProviders::CLandauRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLandauRandomnessProvider::init();
    }
    if (RandomnessProviders::CLevyAlphaStableRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLevyAlphaStableRandomnessProvider::init();
    }
    if (RandomnessProviders::CLevySkewAlphaStableRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLevySkewAlphaStableRandomnessProvider::init();
    }
    if (RandomnessProviders::CFlatRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CFlatRandomnessProvider::init();
    }
    if (RandomnessProviders::CGammaRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CGammaRandomnessProvider::init();
    }
    if (RandomnessProviders::CLognormalRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLognormalRandomnessProvider::init();
    }
    if (RandomnessProviders::CChiSquaredRandomnessProvider::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CChiSquaredRandomnessProvider::init();
    }
     if (RandomnessProviders::CWeibullPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CWeibullPDF::init();
    }
     if (RandomnessProviders::CGaussianPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CGaussianPDF::init();
     }
     if (RandomnessProviders::CExponentialPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CExponentialPDF::init();
     }
     if (RandomnessProviders::CLaplacePDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLaplacePDF::init();
     }
     if (RandomnessProviders::CExponentialPowerPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CExponentialPowerPDF::init();
     }
    if (RandomnessProviders::CCauchyPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CCauchyPDF::init();
    }
    if (RandomnessProviders::CRayleighPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CRayleighPDF::init();
    }
    if (RandomnessProviders::CRayleighTailPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CRayleighTailPDF::init();
    }
    if (RandomnessProviders::CLandauPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLandauPDF::init();
    }
    if (RandomnessProviders::CFlatPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CFlatPDF::init();
    }
    if (RandomnessProviders::CGammaPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CGammaPDF::init();
    }
    if (RandomnessProviders::CLognormalPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLognormalPDF::init();
    }
    if (RandomnessProviders::CChiSquaredPDF::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CChiSquaredPDF::init();
    }
    if (RandomnessProviders::CWeibullCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CWeibullCPD::init();
    }
    if (RandomnessProviders::CGaussianCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CGaussianCPD::init();
    }
    if (RandomnessProviders::CExponentialCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CExponentialCPD::init();
    }
    if (RandomnessProviders::CLaplaceCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLaplaceCPD::init();
    }
    if (RandomnessProviders::CExponentialPowerCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CExponentialPowerCPD::init();
    }
    if (RandomnessProviders::CCauchyCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CCauchyCPD::init();
    }
    if (RandomnessProviders::CRayleighCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CRayleighCPD::init();
    }
    if (RandomnessProviders::CFlatCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CFlatCPD::init();
    }
    if (RandomnessProviders::CGammaCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CGammaCPD::init();
    }
    if (RandomnessProviders::CLognormalCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CLognormalCPD::init();
    }
    if (RandomnessProviders::CChiSquaredCPD::getClassTypeId() == Base::Type::badType()) {
        RandomnessProviders::CChiSquaredCPD::init();
    }
    return 1;
}


PLUGIN_INIT()
{
    InitializeRandomness(objNameWeibull,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objName,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameEx,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameLaplace,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameExponentialPower,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameCauchy,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameRayleigh,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameRayleighTail,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameLandau,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameLevyAlphaStable,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameLevySkewAlphaStable,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameFlat,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameGamma,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameLognormal,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeRandomness(objNameChiSquared,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    InitializeProbabilityDensityFunction(objNameWeibullPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameGaussianPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameExPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameLaplacePDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameExponentialPowerPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameCauchyPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameRayleighPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameRayleighTailPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameLandauPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameFlatPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameGammaPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameLognormalPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeProbabilityDensityFunction(objNameChiSquaredPDF,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    InitializeCumulativeProbabilityDistribution(objNameWeibullCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameGaussianCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameExCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameLaplaceCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameExponentialPowerCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameCauchyCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameRayleighCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameFlatCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameGammaCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameLognormalCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

    InitializeCumulativeProbabilityDistribution(objNameChiSquaredCPD,
                         strPluginName,
                         objTile,
                         objLink,
                         objAuthors,
                         objDate,
                         objVersion,stationarity);

	return 1;
}


INSTALL_PLUGIN()
{
    RegisterRandomness(objNameWeibull,
                       strPluginName,
                       objDescriptionWeibull,
                       BuildWeibullRandomnessProvider,
                       DestroyWeibullRandomnessProvider);

    RegisterRandomness(objName,
                       strPluginName,
                       objDescription,
                       BuildGaussianRandomnessProvider,
                       DestroyGaussianRandomnessProvider);

    RegisterRandomness(objNameEx,
                       strPluginName,
                       objDescriptionEx,
                       BuildExponentialRandomnessProvider,
                       DestroyExponentialRandomnessProvider);

    RegisterRandomness(objNameLaplace,
                       strPluginName,
                       objDescriptionLaplace,
                       BuildLaplaceRandomnessProvider,
                       DestroyLaplaceRandomnessProvider);

    RegisterRandomness(objNameExponentialPower,
                       strPluginName,
                       objDescriptionExponentialPower,
                       BuildExponentialPowerRandomnessProvider,
                       DestroyExponentialPowerRandomnessProvider);

    RegisterRandomness(objNameCauchy,
                       strPluginName,
                       objDescriptionCauchy,
                       BuildCauchyRandomnessProvider,
                       DestroyCauchyRandomnessProvider);

    RegisterRandomness(objNameRayleigh,
                       strPluginName,
                       objDescriptionRayleigh,
                       BuildRayleighRandomnessProvider,
                       DestroyRayleighRandomnessProvider);

    RegisterRandomness(objNameRayleighTail,
                       strPluginName,
                       objDescriptionRayleighTail,
                       BuildRayleighTailRandomnessProvider,
                       DestroyRayleighTailRandomnessProvider);

    RegisterRandomness(objNameLandau,
                       strPluginName,
                       objDescriptionLandau,
                       BuildLandauRandomnessProvider,
                       DestroyLandauRandomnessProvider);

    RegisterRandomness(objNameLevyAlphaStable,
                       strPluginName,
                       objDescriptionLevyAlphaStable,
                       BuildLevyAlphaStableRandomnessProvider,
                       DestroyLevyAlphaStableRandomnessProvider);

    RegisterRandomness(objNameLevySkewAlphaStable,
                       strPluginName,
                       objDescriptionLevySkewAlphaStable,
                       BuildLevySkewAlphaStableRandomnessProvider,
                       DestroyLevySkewAlphaStableRandomnessProvider);

    RegisterRandomness(objNameFlat,
                       strPluginName,
                       objDescriptionFlat,
                       BuildFlatRandomnessProvider,
                       DestroyFlatRandomnessProvider);

    RegisterRandomness(objNameGamma,
                       strPluginName,
                       objDescriptionGamma,
                       BuildGammaRandomnessProvider,
                       DestroyGammaRandomnessProvider);

    RegisterRandomness(objNameLognormal,
                       strPluginName,
                       objDescriptionLognormal,
                       BuildLognormalRandomnessProvider,
                       DestroyLognormalRandomnessProvider);

    RegisterRandomness(objNameChiSquared,
                       strPluginName,
                       objDescriptionChiSquared,
                       BuildChiSquaredRandomnessProvider,
                       DestroyChiSquaredRandomnessProvider);


    /////////////////////////////////////////////////////////////////////////////////////

    RegisterProbabilityDensityFunction(objNameWeibullPDF,
                       strPluginName,
                       objDescriptionWeibullPDF,
                       BuildWeibullPDF,
                       DestroyWeibullPDF);

    RegisterProbabilityDensityFunction(objNameGaussianPDF,
                       strPluginName,
                       objDescriptionGaussianPDF,
                       BuildGaussianPDF,
                       DestroyGaussianPDF);

    RegisterProbabilityDensityFunction(objNameExPDF,
                       strPluginName,
                       objDescriptionExPDF,
                       BuildExponentialPDF,
                       DestroyExponentialPDF);

    RegisterProbabilityDensityFunction(objNameLaplacePDF,
                       strPluginName,
                       objDescriptionLaplacePDF,
                       BuildLaplacePDF,
                       DestroyLaplacePDF);

    RegisterProbabilityDensityFunction(objNameExponentialPowerPDF,
                       strPluginName,
                       objDescriptionExponentialPowerPDF,
                       BuildExponentialPowerPDF,
                       DestroyExponentialPowerPDF);

    RegisterProbabilityDensityFunction(objNameCauchyPDF,
                       strPluginName,
                       objDescriptionCauchyPDF,
                       BuildCauchyPDF,
                       DestroyCauchyPDF);

    RegisterProbabilityDensityFunction(objNameRayleighPDF,
                       strPluginName,
                       objDescriptionRayleighPDF,
                       BuildRayleighPDF,
                       DestroyRayleighPDF);

    RegisterProbabilityDensityFunction(objNameRayleighTailPDF,
                       strPluginName,
                       objDescriptionRayleighTailPDF,
                       BuildRayleighTailPDF,
                       DestroyRayleighTailPDF);

    RegisterProbabilityDensityFunction(objNameLandauPDF,
                       strPluginName,
                       objDescriptionLandauPDF,
                       BuildLandauPDF,
                       DestroyLandauPDF);

    RegisterProbabilityDensityFunction(objNameFlatPDF,
                       strPluginName,
                       objDescriptionFlatPDF,
                       BuildFlatPDF,
                       DestroyFlatPDF);

    RegisterProbabilityDensityFunction(objNameGammaPDF,
                       strPluginName,
                       objDescriptionGammaPDF,
                       BuildGammaPDF,
                       DestroyGammaPDF);

    RegisterProbabilityDensityFunction(objNameLognormalPDF,
                       strPluginName,
                       objDescriptionLognormalPDF,
                       BuildLognormalPDF,
                       DestroyLognormalPDF);

    RegisterProbabilityDensityFunction(objNameChiSquaredPDF,
                       strPluginName,
                       objDescriptionChiSquaredPDF,
                       BuildChiSquaredPDF,
                       DestroyChiSquaredPDF);


    /////////////////////////////////////////////////////////////////////////////////////

    RegisterCumulativeProbabilityDistribution(objNameWeibullCPD,
                       strPluginName,
                       objDescriptionWeibullCPD,
                       BuildWeibullCPD,
                       DestroyWeibullCPD);

    RegisterCumulativeProbabilityDistribution(objNameGaussianCPD,
                       strPluginName,
                       objDescriptionGaussianCPD,
                       BuildGaussianCPD,
                       DestroyGaussianCPD);

    RegisterCumulativeProbabilityDistribution(objNameExCPD,
                       strPluginName,
                       objDescriptionExCPD,
                       BuildExponentialCPD,
                       DestroyExponentialCPD);

    RegisterCumulativeProbabilityDistribution(objNameLaplaceCPD,
                       strPluginName,
                       objDescriptionLaplaceCPD,
                       BuildLaplaceCPD,
                       DestroyLaplaceCPD);

    RegisterCumulativeProbabilityDistribution(objNameExponentialPowerCPD,
                       strPluginName,
                       objDescriptionExponentialPowerCPD,
                       BuildExponentialPowerCPD,
                       DestroyExponentialPowerCPD);

    RegisterCumulativeProbabilityDistribution(objNameCauchyCPD,
                       strPluginName,
                       objDescriptionCauchyCPD,
                       BuildCauchyCPD,
                       DestroyCauchyCPD);

    RegisterCumulativeProbabilityDistribution(objNameRayleighCPD,
                       strPluginName,
                       objDescriptionRayleighCPD,
                       BuildRayleighCPD,
                       DestroyRayleighCPD);

    RegisterCumulativeProbabilityDistribution(objNameFlatCPD,
                       strPluginName,
                       objDescriptionFlatCPD,
                       BuildFlatCPD,
                       DestroyFlatCPD);

    RegisterCumulativeProbabilityDistribution(objNameGammaCPD,
                       strPluginName,
                       objDescriptionGammaCPD,
                       BuildGammaCPD,
                       DestroyGammaCPD);

    RegisterCumulativeProbabilityDistribution(objNameLognormalCPD,
                       strPluginName,
                       objDescriptionLognormalCPD,
                       BuildLognormalCPD,
                       DestroyLognormalCPD);

    RegisterCumulativeProbabilityDistribution(objNameChiSquaredCPD,
                       strPluginName,
                       objDescriptionChiSquaredCPD,
                       BuildChiSquaredCPD,
                       DestroyChiSquaredCPD);


    return 1;
}

UNINSTALL_PLUGIN()
{
    UnregisterRandomness(objNameWeibull, strPluginName);
    UnregisterRandomness(objName, strPluginName);
    UnregisterRandomness(objNameEx, strPluginName);
    UnregisterRandomness(objNameLaplace, strPluginName);
    UnregisterRandomness(objNameExponentialPower, strPluginName);
    UnregisterRandomness(objNameCauchy, strPluginName);
    UnregisterRandomness(objNameRayleigh, strPluginName);
    UnregisterRandomness(objNameRayleighTail, strPluginName);
    UnregisterRandomness(objNameLandau, strPluginName);
    UnregisterRandomness(objNameLevyAlphaStable, strPluginName);
    UnregisterRandomness(objNameLevySkewAlphaStable, strPluginName);
    UnregisterRandomness(objNameFlat, strPluginName);
    UnregisterRandomness(objNameGamma, strPluginName);
    UnregisterRandomness(objNameLognormal, strPluginName);
    UnregisterRandomness(objNameChiSquared, strPluginName);
    ////////////////////////////////////////////////////////////////////////

    UnregisterProbabilityDensityFunction(objNameWeibullPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameGaussianPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameExPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameLaplacePDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameExponentialPowerPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameCauchyPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameRayleighPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameRayleighTailPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameLandauPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameFlatPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameGammaPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameLognormalPDF, strPluginName);
    UnregisterProbabilityDensityFunction(objNameChiSquaredPDF, strPluginName);

    ////////////////////////////////////////////////////////////////////////

    UnregisterCumulativeProbabilityDistribution(objNameWeibullCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameGaussianCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameExCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameLaplaceCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameExponentialPowerCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameCauchyCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameRayleighCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameFlatCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameGammaCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameLognormalCPD, strPluginName);
    UnregisterCumulativeProbabilityDistribution(objNameChiSquaredCPD, strPluginName);

    return 1;
}


