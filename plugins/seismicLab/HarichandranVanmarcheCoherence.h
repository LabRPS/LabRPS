
#include "IrpsSLCoherence.h"


class CHarichandranVanmarcheCoherence : public IrpsSLCoherence
{
	void ComputeCrossCoherenceVectorF(const CRPSSeismicLabsimuData &Data, vec &dCohVector, QStringList &strInformation);

	void ComputeCrossCoherenceMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation);

	void ComputeCoherenceCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation);

	void ComputeCoherenceValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

};

