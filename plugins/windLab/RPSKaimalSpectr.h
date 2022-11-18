
#include "IrpsWLXSpectrum.h"


class CRPSKaimalSpectr : public IrpsWLXSpectrum
{
public:

    void ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

    void ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

    void ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

    bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

