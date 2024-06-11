#ifndef IRPSWLPSDDECOMPOSITIONMETHOD_H
#define IRPSWLPSDDECOMPOSITIONMETHOD_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeaturePSDDecompositionMethod.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLPSDdecompositionMethod : public WindLabAPI::WindLabFeaturePSDDecompositionMethod
{
public:
    virtual ~IrpsWLPSDdecompositionMethod() {};

    virtual bool ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLPSDDECOMPOSITIONMETHOD_H
