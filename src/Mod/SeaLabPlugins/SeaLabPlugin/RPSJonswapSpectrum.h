
#ifndef SEALAB_PLUGIN_JONSWAP_PSD_H
#define SEALAB_PLUGIN_JONSWAP_PSD_H

#include <Mod/SeaLabAPI/App/IrpsSeLSpectrum.h>
#include <App/PropertyUnits.h>

namespace SeaLabAPI { class SeaLabSimulationData; }

namespace SeaLab {

class CRPSJonswapSpectrum : public SeaLabAPI::IrpsSeLSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSJonswapSpectrum);
public:
	CRPSJonswapSpectrum();
	
	~CRPSJonswapSpectrum() {};

    bool ComputeCrossSpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeCrossSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossSpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeAutoSpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeAutoSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeAutoSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

public:

    App::PropertyFrequency SignificantWaveHeight;
    App::PropertyTime PeakPeriod;
    App::PropertyBool AutoGamma;
    App::PropertyBool AutoSigma;
    App::PropertyFloat Gamma;
    App::PropertyFloat Sigma1;
    App::PropertyFloat Sigma2;


};

} // namespace App

#endif // SEALAB_PLUGIN_CHOLESKYDECOMP_H