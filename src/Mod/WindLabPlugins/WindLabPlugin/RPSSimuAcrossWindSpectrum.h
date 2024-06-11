
#ifndef WINDLAB_PLUGIN_SIMUYPSD_H
#define WINDLAB_PLUGIN_SIMUYPSD_H

#include <Mod/WindLabAPI/App/IrpsWLYSpectrum.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {


class CRPSSimuAcrossWindSpectrum : public WindLabAPI::IrpsWLYSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSSimuAcrossWindSpectrum);

public:
	CRPSSimuAcrossWindSpectrum();
	
	~CRPSSimuAcrossWindSpectrum() {};

    bool ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
App::PropertySpeed ShearVelocity;
App::PropertyFloat Constant1;
App::PropertyFloat Constant2;

};

} // namespace App

#endif // WINDLAB_PLUGIN_SIMUYPSD_H