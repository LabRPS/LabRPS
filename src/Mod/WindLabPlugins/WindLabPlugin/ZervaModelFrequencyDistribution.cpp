

#include "ZervaModelFrequencyDistribution.h"
#include <Base/Console.h>

using namespace WindLab;

PROPERTY_SOURCE(WindLab::ZervaModelFrequencyDistribution, WindLabAPI::WindLabFeatureFrequencyDistribution)

ZervaModelFrequencyDistribution::ZervaModelFrequencyDistribution()
{

}

bool ZervaModelFrequencyDistribution::ComputeFrequenciesVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dValVector)
{
	for (int l = 0; l < Data.numberOfFrequency.getValue(); l++)
	{
        ComputeFrequencyValue(Data, location, l, dValVector(l));
	}

	return true;
}

bool ZervaModelFrequencyDistribution::ComputeFrequenciesMatrixFP(const WindLabAPI::WindLabSimuData &Data, mat &dMatrix)
{
    Base::Vector3d location(0, 0, 0);//unused

    for (int l = 0; l < Data.numberOfFrequency.getValue(); l++) {
        
        for (int m = 0; m < Data.numberOfSpatialPosition.getValue(); m++) {

            ComputeFrequencyValue(Data, location, l, dMatrix(l, m));
        }
    }
    return true;
}

bool ZervaModelFrequencyDistribution::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    return true;
}

bool ZervaModelFrequencyDistribution::ComputeFrequencyValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue)
{
    dValue = Data.minFrequency.getValue() + (1 + 0.5 * frequencyIndex) * Data.frequencyIncrement.getValue();
	return true;
}

