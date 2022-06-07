#include "IrpsSLModulation.h"


class CJenningEtAlModulation : public IrpsSLModulation
{
	void ComputeModulationVectorT(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationVectorF(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationVectorP(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationCubeTFP(const CRPSSeismicLabsimuData &Data, cube &dModulationCube, QStringList &strInformation);

	void ComputeModulationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

};
