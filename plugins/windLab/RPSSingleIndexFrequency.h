
#include "IrpsWLFrequencyDistribution.h"


class CRPSSingleIndexFrequency : public IrpsWLFrequencyDistribution
{

    void ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation);

    void ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation);

    bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

