

#include "ZervaModelFrequencyDistribution.h"
#include <Base/Console.h>

using namespace SeismicLab;

PROPERTY_SOURCE(SeismicLab::ZervaModelFrequencyDistribution, SeismicLabAPI::SeismicLabFeatureFrequencyDistribution)

ZervaModelFrequencyDistribution::ZervaModelFrequencyDistribution()
{
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Zerva_Frequency_Discretization");

}

bool ZervaModelFrequencyDistribution::ComputeFrequenciesVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector)
{
	for (int l = 0; l < Data.numberOfFrequency.getValue(); l++)
	{
        ComputeFrequencyValue(Data, location, l, dValVector(l));
	}

	return true;
}

bool ZervaModelFrequencyDistribution::ComputeFrequenciesMatrixFP(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dMatrix)
{
    Base::Vector3d location(0, 0, 0);//unused

    for (int l = 0; l < Data.numberOfFrequency.getValue(); l++) {
        
        for (int m = 0; m < Data.numberOfSpatialPosition.getValue(); m++) {

            ComputeFrequencyValue(Data, location, l, dMatrix(l, m));
        }
    }
    return true;
}

bool ZervaModelFrequencyDistribution::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    return true;
}

bool ZervaModelFrequencyDistribution::ComputeFrequencyValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue)
{
    dValue = (Data.minFrequency.getQuantityValue().getValueAs(Base::Quantity::Hertz) + (1 + 0.5 * frequencyIndex) * Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::Hertz)) * ScaleCoefficient.getValue();
	return true;
}

