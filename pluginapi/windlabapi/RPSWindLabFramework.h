#ifndef RPSWINDLABFRAMEWORK_H
#define RPSWINDLABFRAMEWORK_H

#include "RPSWindLabAPIdefines.h"
#include "RPSWindLabsimuData.h"
#include "ObjectDescription.h"

class RPS_CORE_API CRPSWindLabFramework
{
public:
	CRPSWindLabFramework();
	~CRPSWindLabFramework();

	// coherence function
	static void ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dCohVector, QStringList &strInformation);

	static void ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation);

	// correlation function
	static void ComputeCrossCorrelationVectorT(const CRPSWindLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation);

	// frequency distribution
	static void ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation);

	// location distribution
	static void ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	// mean wind speed
	static void ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation);

	// modulation function
	static void ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	// psd decomposition
	static void ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

    static void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

	// randomness
	static void GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	// X spectrum
    static void ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

    static void ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	// Y spectrum
    static void ComputeYAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

    static void ComputeYCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);


	// Z spectrum
    static void ComputeZAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

    static void ComputeZCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);


	// spectrum X, Y, Z
    static void ComputeAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);


	/////
	static void ComputeCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
	static void ComputeCrossCorrelationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
	static void ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation);
	static void ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
	static void ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
	static void ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation);
    static void ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static void ComputeYAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static void ComputeZAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static void ComputeAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static void ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation);

	static ObjectDescription getSpatialDistributionObjDescription(const QString &objectName);
	static ObjectDescription getMeanProfilObjDescription(const QString &objectName);
	static ObjectDescription getAlongWindSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getVerticalWindSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getAcrossWindSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getDecomposedSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getCoherenceFunctionObjDescription(const QString &objectName);
	static ObjectDescription getSimulationMethodObjDescription(const QString &objectName);
	static ObjectDescription getFrequencyDistributionObjDescription(const QString &objectName);
	static ObjectDescription getRandomnessProviderObjDescription(const QString &objectName);
	static ObjectDescription getModulationFunctionObjDescription(const QString &objectName);
	static ObjectDescription getCorrelationFunctionObjDescription(const QString &objectName);
	static ObjectDescription getTableToolObjDescription(const QString &objectName);
	static ObjectDescription getMatrixToolObjDescription(const QString &objectName);
	static ObjectDescription getUserDefinedRPSObjDescription(const QString &objectName);

    static void TableToolCompute(const CRPSWindLabsimuData &Data, const mat &inputTable, mat &outputTable, QStringList &strInformation);
    static void MatrixToolCompute(const CRPSWindLabsimuData &Data, const mat &inputMatrix, mat &outputMatrix, QStringList &strInformation);
    static void UserDefinedRPSObjectCompute(const CRPSWindLabsimuData &Data, cube &dresult, QStringList &strInformation);

};

#endif
