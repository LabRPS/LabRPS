#pragma once
#include "IrpsWLModulation.h"

class CSineModulation : public IrpsWLModulation
{
public:

	void ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation);

	void ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);
};

