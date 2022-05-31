#pragma once
#include "IrpsSeLCoherence.h"

class CAbrahamsonCoherence : public IrpsSeLCoherence
{
	public:
	void ComputeCrossCoherenceVectorF(const CRPSSeaLabsimuData &Data, vec &dCohVector, QStringList &strInformation);

	void ComputeCrossCoherenceMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation);

	void ComputeCoherenceCubePPF(const CRPSSeaLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation);

	void ComputeCoherenceValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);
};

