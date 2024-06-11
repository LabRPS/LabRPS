#ifndef IRPSWLCPD_H
#define IRPSWLCPD_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureCumulativeProbabilityDistribution.h>

namespace WindLabAPI {

class IrpsWLCumulativeProbabilityDistribution : public WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution
{
public:

    virtual ~IrpsWLCumulativeProbabilityDistribution() {};

    virtual bool ComputeCPDValue(const WindLabSimuData& Data, const double& x, double& dValue) = 0;

    virtual bool ComputeCPDVectorX(const WindLabSimuData &Data,  vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLCPD_H
