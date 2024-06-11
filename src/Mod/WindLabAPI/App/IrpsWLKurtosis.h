#ifndef IRPSWLKURTOSIS_H
#define IRPSWLKURTOSIS_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureKurtosis.h>

namespace WindLabAPI {

class IrpsWLKurtosis : public WindLabAPI::WindLabFeatureKurtosis
{
public:

    virtual ~IrpsWLKurtosis() {};

    virtual bool ComputeKurtosisValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeKurtosisVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeKurtosisVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLKURTOSIS_H
