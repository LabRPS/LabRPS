#ifndef IRPSWLCOHERENCE_H
#define IRPSWLCOHERENCE_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureCoherence.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLCoherence : public WindLabAPI::WindLabFeatureCoherence
{
public:

    virtual ~IrpsWLCoherence() {};

    virtual bool ComputeCrossCoherenceVectorF(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeCrossCoherenceVectorT(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeCrossCoherenceMatrixPP(const WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix) = 0;

    virtual bool ComputeCrossCoherenceValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;
};

} //namespace WindLabAPI

#endif  // IRPSWLCOHERENCE_H
