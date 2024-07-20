
#ifndef SEISMICLAB_PLUGIN_LOHLIN_H
#define SEISMICLAB_PLUGIN_LOHLIN_H

#include <Mod/SeismicLabAPI/App/IrpsSLCoherence.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSLohAndLinCoherence : public SeismicLabAPI::IrpsSLCoherence
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSLohAndLinCoherence);
public:
	CRPSLohAndLinCoherence();
	
	~CRPSLohAndLinCoherence() {};

    bool ComputeCrossCoherenceVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossCoherenceVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeCrossCoherenceMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

    bool ComputeCrossCoherenceValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

	bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

public:

    App::PropertyFloat ParameterAlpha;
    App::PropertyFloat ParameterB;

};

} // namespace App

#endif // SEISMICLAB_PLUGIN_CHOLESKYDECOMP_H