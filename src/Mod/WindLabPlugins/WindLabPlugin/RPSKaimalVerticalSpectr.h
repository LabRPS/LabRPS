
#ifndef WINDLAB_PLUGIN_KAIMALZPSD_H
#define WINDLAB_PLUGIN_KAIMALZPSD_H

#include <Mod/WindLabAPI/App/IrpsWLZSpectrum.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {


class CRPSKaimalVerticalSpectr : public WindLabAPI::IrpsWLZSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSKaimalAcrossSpectr);

public:
	CRPSKaimalVerticalSpectr();
	
	~CRPSKaimalVerticalSpectr() {};

    bool ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
    App::PropertySpeed ShearVelocity;
    App::PropertyFloat Constant1;
    App::PropertyFloat Constant2;

};

} // namespace App

#endif // WINDLAB_PLUGIN_KAIMALZPSD_H