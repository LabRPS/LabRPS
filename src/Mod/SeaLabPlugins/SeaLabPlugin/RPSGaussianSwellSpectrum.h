
#ifndef SEALAB_PLUGIN_GAUSSIANSWELL_PSD_H
#define SEALAB_PLUGIN_GAUSSIANSWELL_PSD_H

#include <Mod/SeaLabAPI/App/IrpsSeLFrequencySpectrum.h>
#include <App/PropertyUnits.h>


namespace SeaLab {

class CRPSGaussianSwellSpectrum: public SeaLabAPI::IrpsSeLFrequencySpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSGaussianSwellSpectrum);
public:
	CRPSGaussianSwellSpectrum();
	
	~CRPSGaussianSwellSpectrum() {};

    bool ComputeCrossFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeCrossFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossFrequencySpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeAutoFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeAutoFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeAutoFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

public:

    App::PropertyLength SignificantWaveHeight;
    App::PropertyTime PeakPeriod;
    App::PropertyFloat Sigma;

};

} // namespace App

#endif // SEALAB_PLUGIN_PIERSONMOSKOWITZ_PSD_H