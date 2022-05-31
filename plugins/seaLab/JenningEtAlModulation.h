
#include "IrpsSeLModulation.h"

class CJenningEtAlModulation : public IrpsSeLModulation
{
	void ComputeModulationVectorT(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationVectorF(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationVectorP(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationVectorD(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	void ComputeModulationMatrixTP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixFP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixTD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixFD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationMatrixTF(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	void ComputeModulationCubeTFP(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation);

	void ComputeModulationCubeTFD(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation);

	void ComputeModulationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);

};
