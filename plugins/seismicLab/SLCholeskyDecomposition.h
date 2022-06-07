
#include "IrpsSLPSDdecompositionMethod.h"

class CSLCholeskyDecomposition : public IrpsSLPSDdecompositionMethod
{
public:
	void ComputeDecomposedCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	void ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	void ComputeDecomposedPSDValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

};

