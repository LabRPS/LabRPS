
#ifndef GENERALIZEDPSD_PLUGIN_VONKARMANYPSD_H
#define GENERALIZEDPSD_PLUGIN_VONKARMANYPSD_H

#include <Mod/WindLabAPI/App/IrpsWLYSpectrum.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CRPSGeneralizedAcrossWindVonKarmanSpectrum : public WindLabAPI::IrpsWLYSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSGeneralizedAcrossWindVonKarmanSpectrum);

public:
	CRPSGeneralizedAcrossWindVonKarmanSpectrum();
	
	~CRPSGeneralizedAcrossWindVonKarmanSpectrum() {};

   bool ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
    App::PropertyFloat ParameterA;
    App::PropertyFloat ParameterB;
    App::PropertyFloat ParameterC;
    App::PropertyFloat ParameterD;
    App::PropertyFloat ParameterE;
    App::PropertyFloat ParameterF;
    App::PropertyFloat ParameterG;
    App::PropertyFloat ParameterH;
    App::PropertyFloat ParameterI;
    App::PropertyFloat ParameterJ;
    App::PropertyLength IntegralLengthScale;
    App::PropertySpeed StandardDeviation;
};

} // namespace App

#endif // GENERALIZEDPSD_PLUGIN_VONKARMANYPSD_H