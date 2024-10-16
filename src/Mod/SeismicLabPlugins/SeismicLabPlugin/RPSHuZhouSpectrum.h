
#ifndef SEISMICLAB_PLUGIN_HUZHOUPSD_H
#define SEISMICLAB_PLUGIN_HUZHOUPSD_H

#include <Mod/SeismicLabAPI/App/IrpsSLSpectrum.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSHuZhouSpectrum : public SeismicLabAPI::IrpsSLSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSHuZhouSpectrum);
public:
	CRPSHuZhouSpectrum();
	
	~CRPSHuZhouSpectrum() {};

    bool ComputeCrossSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeAutoSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeAutoSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeAutoSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertyFrequency GroundNaturalFrequency;
    App::PropertyFloat GroundDampingRatio;
    App::PropertyFrequency LowFrequencyControlFactor;
    App::PropertyFloat ConstantSpectralIntensity;


};

} // namespace App

#endif // SEISMICLAB_PLUGIN_HUZHOUPSD_H