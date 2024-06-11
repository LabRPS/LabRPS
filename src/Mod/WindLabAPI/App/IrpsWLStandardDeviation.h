#ifndef IRPSWLSTANDARDDEVIATION_H
#define IRPSWLSTANDARDDEVIATION_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureStandardDeviation.h>

namespace WindLabAPI {

class IrpsWLStandardDeviation : public WindLabAPI::WindLabFeatureStandardDeviation
{
public:

    virtual ~IrpsWLStandardDeviation() {};

    virtual bool ComputeStandardDeviationValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeStandardDeviationVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeStandardDeviationVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLSTANDARDDEVIATION_H
