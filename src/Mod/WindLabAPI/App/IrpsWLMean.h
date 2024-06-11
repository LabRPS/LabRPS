#ifndef IRPSWLMEAN_H
#define IRPSWLMEAN_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureMeanWind.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLMean : public WindLabAPI::WindLabFeatureMeanWind
{
public:

    virtual ~IrpsWLMean() {};

    virtual bool ComputeMeanWindSpeedValue(const WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeMeanWindSpeedVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeMeanWindSpeedVectorT(const WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLMEAN_H
