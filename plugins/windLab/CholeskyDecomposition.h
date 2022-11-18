
#include "IrpsWLPSDdecompositionMethod.h"


class CCholeskyDecomposition : public IrpsWLPSDdecompositionMethod
{
public:

    void ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

    void ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

    void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

    bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

