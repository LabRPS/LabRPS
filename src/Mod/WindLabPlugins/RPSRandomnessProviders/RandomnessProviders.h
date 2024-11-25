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

#include <Mod/WindLabAPI/App/IrpsWLCumulativeProbabilityDistribution.h>
#include <Mod/WindLabAPI/App/IrpsWLProbabilityDensityFunction.h>
#include <Mod/WindLabAPI/App/IrpsWLRandomness.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimulationData; }

namespace RandomnessProviders
{

//Cauchy PDF
class CWeibullRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CWeibullRandomnessProvider);

public:
    CWeibullRandomnessProvider();

    ~CWeibullRandomnessProvider() {};

   bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

   bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

   bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
};

//Cauchy PDF
class CGaussianRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CGaussianRandomnessProvider);

public:
    CGaussianRandomnessProvider();

    ~CGaussianRandomnessProvider() {};

    bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
    App::PropertySpeed StandardDeviation;
};

//Cauchy PDF
class CExponentialRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CExponentialRandomnessProvider);

public:
    CExponentialRandomnessProvider();

    ~CExponentialRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
};

//Cauchy PDF
class CLaplaceRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLaplaceRandomnessProvider);

public:
    CLaplaceRandomnessProvider();

    ~CLaplaceRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Width;
    App::PropertyFloat Mean;
};

//Cauchy PDF
class CExponentialPowerRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CExponentialPowerRandomnessProvider);

public:
    CExponentialPowerRandomnessProvider();

    ~CExponentialPowerRandomnessProvider() {};

    bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
    App::PropertyFloat Mean;
};

//Cauchy PDF
class CCauchyRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CCauchyRandomnessProvider);

public:
    CCauchyRandomnessProvider();

    ~CCauchyRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
};


//Cauchy PDF
class CRayleighRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CRayleighRandomnessProvider);

public:
    CRayleighRandomnessProvider();

    ~CRayleighRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
};

//Cauchy PDF
class CRayleighTailRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CRayleighTailRandomnessProvider);

public:
    CRayleighTailRandomnessProvider();

    ~CRayleighTailRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat LowerLimit;
};

//Cauchy PDF
class CLandauRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLandauRandomnessProvider);

public:
    CLandauRandomnessProvider();

    ~CLandauRandomnessProvider() {};

      bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);
};

//Cauchy PDF
class CLevyAlphaStableRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLevyAlphaStableRandomnessProvider);

public:
    CLevyAlphaStableRandomnessProvider();

    ~CLevyAlphaStableRandomnessProvider() {};

    bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:
    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
};

//Cauchy PDF
class CLevySkewAlphaStableRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLevySkewAlphaStableRandomnessProvider);

public:
    CLevySkewAlphaStableRandomnessProvider();

    ~CLevySkewAlphaStableRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:
    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
    App::PropertyFloat SkewnessParameter;
};

//Cauchy PDF
class CFlatRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CFlatRandomnessProvider);

public:
    CFlatRandomnessProvider();

    ~CFlatRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat LowerBound;
    App::PropertyFloat UpperBound;
};

//Cauchy PDF
class CGammaRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CGammaRandomnessProvider);

public:
    CGammaRandomnessProvider();

    ~CGammaRandomnessProvider() {};

      bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ParameterA;
    App::PropertyFloat ParameterB;
};

//Cauchy PDF
class CLognormalRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLognormalRandomnessProvider);

public:
    CLognormalRandomnessProvider();

    ~CLognormalRandomnessProvider() {};

      bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
    App::PropertySpeed StandardDeviation;
};

//ChiSquared PDF
class CChiSquaredRandomnessProvider: public WindLabAPI::IrpsWLRandomness
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CChiSquaredRandomnessProvider);

public:
    CChiSquaredRandomnessProvider();

    ~CChiSquaredRandomnessProvider() {};

     bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double& dValue);

    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat& dRandomValueArray);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat DegreeOfFreedom;
};

//Cauchy PDF
class CWeibullPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CWeibullPDF);

public:
    CWeibullPDF();

    ~CWeibullPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
};

//Cauchy PDF
class CGaussianPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CGaussianPDF);

public:
    CGaussianPDF();

    ~CGaussianPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
    App::PropertySpeed StandardDeviation;
};

//Cauchy PDF
class CExponentialPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CExponentialPDF);

public:
    CExponentialPDF();

    ~CExponentialPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
};

//Cauchy PDF
class CLaplacePDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLaplacePDF);

public:
    CLaplacePDF();

    ~CLaplacePDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Width;
    App::PropertyFloat Mean;
};

//Cauchy PDF
class CExponentialPowerPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CExponentialPowerPDF);

public:
    CExponentialPowerPDF();

    ~CExponentialPowerPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
    App::PropertyFloat Mean;
};

//Cauchy PDF
class CCauchyPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CCauchyPDF);

public:
    CCauchyPDF();

    ~CCauchyPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
};


//Cauchy PDF
class CRayleighPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CRayleighPDF);

public:
    CRayleighPDF();

    ~CRayleighPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
};

//Cauchy PDF
class CRayleighTailPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CRayleighTailPDF);

public:
    CRayleighTailPDF();

    ~CRayleighTailPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat LowerLimit;
};

//Cauchy PDF
class CLandauPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLandauPDF);

public:
    CLandauPDF();

    ~CLandauPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);
};

//Cauchy PDF
class CFlatPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CFlatPDF);

public:
    CFlatPDF();

    ~CFlatPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat LowerBound;
    App::PropertyFloat UpperBound;
};

//Cauchy PDF
class CGammaPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CGammaPDF);

public:
    CGammaPDF();

    ~CGammaPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ParameterA;
    App::PropertyFloat ParameterB;
};

//Cauchy PDF
class CLognormalPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLognormalPDF);

public:
    CLognormalPDF();

    ~CLognormalPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
    App::PropertySpeed StandardDeviation;
};

//ChiSquared PDF
class CChiSquaredPDF: public WindLabAPI::IrpsWLProbabilityDensityFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CChiSquaredPDF);

public:
    CChiSquaredPDF();

    ~CChiSquaredPDF() {};

    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat DegreeOfFreedom;
};


/////////////////////////////////////////////////////////////////////

//Cauchy CPD
class CWeibullCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CWeibullCPD);

public:
    CWeibullCPD();

    ~CWeibullCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CGaussianCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CGaussianCPD);

public:
    CGaussianCPD();

    ~CGaussianCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
    App::PropertySpeed StandardDeviation;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CExponentialCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CExponentialCPD);

public:
    CExponentialCPD();

    ~CExponentialCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CLaplaceCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLaplaceCPD);

public:
    CLaplaceCPD();

    ~CLaplaceCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Width;
    App::PropertyFloat Mean;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CExponentialPowerCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CExponentialPowerCPD);

public:
    CExponentialPowerCPD();

    ~CExponentialPowerCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyFloat ExponentFactor;
    App::PropertyFloat Mean;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CCauchyCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CCauchyCPD);

public:
    CCauchyCPD();

    ~CCauchyCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyEnumeration Types;
};


//Cauchy CPD
class CRayleighCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CRayleighCPD);

public:
    CRayleighCPD();

    ~CRayleighCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ScaleParameter;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CFlatCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CFlatCPD);

public:
    CFlatCPD();

    ~CFlatCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat LowerBound;
    App::PropertyFloat UpperBound;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CGammaCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CGammaCPD);

public:
    CGammaCPD();

    ~CGammaCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat ParameterA;
    App::PropertyFloat ParameterB;
    App::PropertyEnumeration Types;
};

//Cauchy CPD
class CLognormalCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CLognormalCPD);

public:
    CLognormalCPD();

    ~CLognormalCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat Mean;
    App::PropertySpeed StandardDeviation;
    App::PropertyEnumeration Types;
};

//ChiSquared CPD
class CChiSquaredCPD: public WindLabAPI::IrpsWLCumulativeProbabilityDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(RandomnessProviders::CChiSquaredCPD);

public:
    CChiSquaredCPD();

    ~CChiSquaredCPD() {};

    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, const double& x, double& dValue);

    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:

    App::PropertyFloat DegreeOfFreedom;
    App::PropertyEnumeration Types;
};


/////////////////////////////////////////////////////////////////////
} // namespace RandomnessProviders





//#define RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(_Class_)\
//class _Class_ : public WindLabAPI::IrpsWLRandomness\
//{\
//public:\
//    bool GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat &dRandomValueArray);\
//    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);\
//    bool ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double &dValue);\
//};
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CWeibullRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CGaussianRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CExponentialRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CLaplaceRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CExponentialPowerRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CCauchyRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CRayleighRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CRayleighTailRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CLandauRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CLevyAlphaStableRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CLevySkewAlphaStableRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CFlatRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CGammaRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CLognormalRandomnessProvider)
//RPS_RANDOMNESS_PROVIDERS_CLASS_HEADER(CChiSquaredRandomnessProvider)


//#define RPS_PDF_CLASS_HEADER(_Class_)\
//class _Class_ : public WindLabAPI::IrpsWLProbabilityDensityFunction\
//{\
//public:\
//    bool ComputePDFValue(const WindLabAPI::WindLabSimulationData& Data, const double &x, double &dValue);\
//    bool ComputePDFVectorX(const WindLabAPI::WindLabSimulationData& Data, vec &dVarVector, vec &dValVector);\
//    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);\
//};


//RPS_PDF_CLASS_HEADER(CWeibullPDF)
//RPS_PDF_CLASS_HEADER(CGaussianPDF)
//RPS_PDF_CLASS_HEADER(CExponentialPDF)
//RPS_PDF_CLASS_HEADER(CLaplacePDF)
//RPS_PDF_CLASS_HEADER(CExponentialPowerPDF)
//RPS_PDF_CLASS_HEADER(CCauchyPDF)
//RPS_PDF_CLASS_HEADER(CRayleighPDF)
//RPS_PDF_CLASS_HEADER(CRayleighTailPDF)
//RPS_PDF_CLASS_HEADER(CLandauPDF)
//RPS_PDF_CLASS_HEADER(CFlatPDF)
//RPS_PDF_CLASS_HEADER(CGammaPDF)
//RPS_PDF_CLASS_HEADER(CLognormalPDF)
//RPS_PDF_CLASS_HEADER(CChiSquaredPDF)

//#define RPS_CPD_CLASS_HEADER(_Class_)\
//class _Class_ : public WindLabAPI::IrpsWLCumulativeProbabilityDistribution\
//{\
//public:\
//    bool ComputeCPDValue(const WindLabAPI::WindLabSimulationData& Data, double &dValue, const double &x);\
//    bool ComputeCPDVectorX(const WindLabAPI::WindLabSimulationData& Data, vec &dVarVector, vec &dValVector);\
//    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);\
//};

//RPS_CPD_CLASS_HEADER(CWeibullCPD)
//RPS_CPD_CLASS_HEADER(CGaussianCPD)
//RPS_CPD_CLASS_HEADER(CExponentialCPD)
//RPS_CPD_CLASS_HEADER(CLaplaceCPD)
//RPS_CPD_CLASS_HEADER(CExponentialPowerCPD)
//RPS_CPD_CLASS_HEADER(CCauchyCPD)
//RPS_CPD_CLASS_HEADER(CRayleighCPD)
//RPS_CPD_CLASS_HEADER(CFlatCPD)
//RPS_CPD_CLASS_HEADER(CGammaCPD)
//RPS_CPD_CLASS_HEADER(CLognormalCPD)
//RPS_CPD_CLASS_HEADER(CChiSquaredCPD)


