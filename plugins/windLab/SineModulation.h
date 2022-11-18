
#include "IrpsWLModulation.h"

class CSineModulation : public IrpsWLModulation
{
public:

    void ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

    void ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

    bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

