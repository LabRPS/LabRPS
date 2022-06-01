#pragma once

#ifndef RPSSEISMICLABFRAMEWORK_H
#define RPSSEISMICLABFRAMEWORK_H

#include "RPSSeismicLabAPIdefines.h"
#include "RPSSeismicLabsimuData.h"

class RPS_CORE_API CRPSSeismicLabFramework
{
public:
	CRPSSeismicLabFramework();
	~CRPSSeismicLabFramework();

	//coherence
	static void ComputeCrossCoherenceVectorF(const CRPSSeismicLabsimuData &Data, vec &dCohVector, QStringList &strInformation);

	static void ComputeCrossCoherenceMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation);

	static void ComputeCoherenceCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation);

	static void ComputeCoherenceValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	//correlation
	static void ComputeCrossCorrelationVectorT(const CRPSSeismicLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation);

	static void ComputeCrossCorrelationVectorP(const CRPSSeismicLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation);

	static void ComputeCrossCorrelationMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation);

	static void ComputeCrossCorrelationCubePPT(const CRPSSeismicLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation);

	static void ComputeCrossCorrelationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	//frequency
	static void ComputeFrequenciesVectorF(const CRPSSeismicLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation);

	static void ComputeFrequenciesMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation);

	//location
	static void ComputeLocationCoordinateMatrixP3(const CRPSSeismicLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	//modulation
	static void ComputeModulationVectorT(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	static void ComputeModulationVectorF(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	static void ComputeModulationVectorP(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	static void ComputeModulationMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationCubeTFP(const CRPSSeismicLabsimuData &Data, cube &dModulationCube, QStringList &strInformation);

	static void ComputeModulationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	//psd decomposition
	static void ComputeDecomposedCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	static void ComputeDecomposedPSDValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	//randomness
	static void GenerateRandomArrayFP(const CRPSSeismicLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	static void ComputeRandomValue(const CRPSSeismicLabsimuData &Data, double &dValue, QStringList &strInformation);

	//x spectrum
	static void ComputeXCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeXCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeXCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeXCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeXCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeXCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeXCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeXCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeXCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeXCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	// Y spectrum
	static void ComputeYCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeYCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeYCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeYCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeYCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeYCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeYCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeYCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeYCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeYCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	// Z spectrum
	static void ComputeZCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeZCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeZCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeZCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeZCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeZCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeZCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeZCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeZCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeZCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	//spectrum X, Y, Z
	static void ComputeCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

};

#endif
