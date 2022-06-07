#pragma once
#include "IrpsWLModulation.h"


class CThreeParaModulation : public IrpsWLModulation
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

	//Initial setting
	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

public:
	double m_dModAlpha = 4.98;
	double m_dModBeta = 3;
	double m_dModLambda = 0.003; // maximum modulation funtion value occurs at t = 3/1000, 3 = m_dModBeta

};

