#pragma once
#include "IrpsSeLDirectionSpreadingFunction.h"

class CRPSSpreadingFunction2 : public IrpsSeLDirectionSpreadingFunction
{
	void ComputeSpreadingFunctionVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeSpreadingFunctionVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeSpreadingFunctionVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeSpreadingFunctionVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeSpreadingFunctionMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeSpreadingFunctionMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeSpreadingFunctionMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeSpreadingFunctionMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeSpreadingFunctionMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeSpreadingFunctionMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeSpreadingFunctionCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeSpreadingFunctionCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeSpreadingFunctionCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeSpreadingFunctionValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

	//others
	bool InRange(double low, double high, double x);
};

