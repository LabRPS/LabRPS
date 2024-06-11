#ifndef IRPSWLLOCATIONDISTRIBUTION_H
#define IRPSWLLOCATIONDISTRIBUTION_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureLocationDistribution.h>

namespace WindLabAPI {

class IrpsWLLocationDistribution: public WindLabAPI::WindLabFeatureLocationDistribution
{

public:
    virtual ~IrpsWLLocationDistribution() {};

    virtual bool ComputeLocationCoordinateMatrixP3(const WindLabSimuData& Data, mat& dLocCoord) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData& Data) = 0;
};

} // namespace WindLabAPI

#endif  // IRPSWLLOCATIONDISTRIBUTION_H
