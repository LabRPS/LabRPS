
#ifndef SEALAB_PLUGIN_OCHIANDHUBBLE_PSD_H
#define SEALAB_PLUGIN_OCHIANDHUBBLE_PSD_H

#include <Mod/SeaLabAPI/App/IrpsSeLFrequencySpectrum.h>
#include <App/PropertyUnits.h>


namespace SeaLab {

class CRPSOchiAndHubbleSpectrum : public SeaLabAPI::IrpsSeLFrequencySpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSOchiAndHubbleSpectrum);
public:
	CRPSOchiAndHubbleSpectrum();
	
	~CRPSOchiAndHubbleSpectrum() {};

    bool ComputeCrossFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeCrossFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossFrequencySpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeAutoFrequencySpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeAutoFrequencySpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeAutoFrequencySpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

public:
    App::PropertyLength SignificantWaveHeight1;
    App::PropertyLength SignificantWaveHeight2;
    App::PropertyFrequency PeakFrequency1;
    App::PropertyFrequency PeakFrequency2;
    App::PropertyFloat PeakShape1;
    App::PropertyFloat PeakShape2;
    App::PropertyBool AutoPara;
    App::PropertyLength SignificantWaveHeight;

};

} // namespace App

#endif// SEALAB_PLUGIN_OCHIANDHUBBLE_PSD_H