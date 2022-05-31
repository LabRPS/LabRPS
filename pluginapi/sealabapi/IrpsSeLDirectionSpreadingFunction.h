#pragma once
#include "RPSSeaLabsimuData.h"

class IrpsSeLDirectionSpreadingFunction
{
public:

    virtual ~IrpsSeLDirectionSpreadingFunction() {}

	virtual void ComputeSpreadingFunctionVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation) = 0;

	virtual void ComputeSpreadingFunctionValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation) = 0;
	
	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;

};
