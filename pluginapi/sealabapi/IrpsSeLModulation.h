#pragma once
#include "RPSSeaLabsimuData.h"

class IrpsSeLModulation
{
public:

    virtual ~IrpsSeLModulation() {}

	virtual void ComputeModulationVectorT(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationVectorF(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationVectorP(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationVectorD(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixTP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixFP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixTD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixFD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixTF(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationCubeTFP(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation) = 0;

	virtual void ComputeModulationCubeTFD(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation) = 0;

	virtual void ComputeModulationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation) = 0;
};

