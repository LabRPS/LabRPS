#pragma once
#include "RPSSeismicLabsimuData.h"

class IrpsSLModulation
{
public:
    virtual ~IrpsSLModulation() {};

	virtual void ComputeModulationVectorT(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationVectorF(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationVectorP(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation) = 0;

	virtual void ComputeModulationCubeTFP(const CRPSSeismicLabsimuData &Data, cube &dModulationCube, QStringList &strInformation) = 0;

	virtual void ComputeModulationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation) = 0;
};

