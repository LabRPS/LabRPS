
#ifndef SEISMICLAB_PLUGIN_KOU_SPANO_PSD_H
#define SEISMICLAB_PLUGIN_KOU_SPANO_PSD_H

#include <Mod/SeismicLabAPI/App/IrpsSLSpectrum.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSKougioumtzoglouAndSpanoSpectrum : public SeismicLabAPI::IrpsSLSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSKougioumtzoglouAndSpanoSpectrum);
public:
	CRPSKougioumtzoglouAndSpanoSpectrum();
	
	~CRPSKougioumtzoglouAndSpanoSpectrum() {};

    bool ComputeCrossSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeAutoSpectrumValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeAutoSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeAutoSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertyFloat ConstantS;


};

} // namespace App

#endif// SEISMICLAB_PLUGIN_KOU_SPANO_PSD_H