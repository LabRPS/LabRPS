#ifndef GENERALIZEDPSD_PLUGIN_VONKARMANZPSD_H
#define GENERALIZEDPSD_PLUGIN_VONKARMANZPSD_H

#include <Mod/WindLabAPI/App/IrpsWLZSpectrum.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CRPSGeneralizedVerticalWindVonKarmanSpectrum : public WindLabAPI::IrpsWLZSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSGeneralizedVerticalWindVonKarmanSpectrum);

public:
	CRPSGeneralizedVerticalWindVonKarmanSpectrum();
	
	~CRPSGeneralizedVerticalWindVonKarmanSpectrum() {};

    bool ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
    App::PropertyLength IntegralLengthScale;
    App::PropertySpeed StandardDeviation;
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

};

} // namespace App

#endif // GENERALIZEDPSD_PLUGIN_VONKARMANZPSD_H