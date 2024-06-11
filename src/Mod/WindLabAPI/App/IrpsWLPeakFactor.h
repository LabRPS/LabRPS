#ifndef IRPSWLPEAKFACTOR_H
#define IRPSWLPEAKFACTOR_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeaturePeakFactor.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLPeakFactor : public WindLabAPI::WindLabFeaturePeakFactor
{
public:

    virtual ~IrpsWLPeakFactor() {};

    virtual bool ComputePeakFactorValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputePeakFactorVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputePeakFactorVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLPEAKFACTOR_H
