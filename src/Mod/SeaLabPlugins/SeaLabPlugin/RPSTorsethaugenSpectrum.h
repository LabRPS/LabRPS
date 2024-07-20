
#ifndef SEALAB_PLUGIN_TORSETHAUGEN_PSD_H
#define SEALAB_PLUGIN_TORSETHAUGEN_PSD_H

#include <Mod/SeaLabAPI/App/IrpsSeLSpectrum.h>
#include <App/PropertyUnits.h>


namespace SeaLab {

class CRPSTorsethaugenSpectrum : public SeaLabAPI::IrpsSeLSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSTorsethaugenSpectrum);
public:
	CRPSTorsethaugenSpectrum();
	
	~CRPSTorsethaugenSpectrum() {};

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
    App::PropertyBool DoublePeaks;

};

} // namespace App

#endif// SEALAB_PLUGIN_TORSETHAUGEN_PSD_H