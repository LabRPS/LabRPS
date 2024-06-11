#ifndef IRPSWLFREQUENCYDISTRIBUTION_H
#define IRPSWLFREQUENCYDISTRIBUTION_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureFrequencyDistribution.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLFrequencyDistribution : public WindLabAPI::WindLabFeatureFrequencyDistribution
{
public:
    virtual ~IrpsWLFrequencyDistribution() {};

    virtual bool ComputeFrequencyValue(const WindLabSimuData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue) = 0;

    virtual bool ComputeFrequenciesVectorF(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dValVector) = 0;
  
    virtual bool ComputeFrequenciesMatrixFP(const WindLabSimuData &Data, mat &dMatrix) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

	};

} //namespace WindLabAPI

#endif  // IRPSWLFREQUENCYDISTRIBUTION_H
