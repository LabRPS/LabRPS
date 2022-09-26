#ifndef RPSSeaLABFRAMEWORK_H
#define RPSSeaLABFRAMEWORK_H

#include "RPSSeaLabAPIdefines.h"
#include "RPSSeaLabsimuData.h"

class RPS_CORE_API CRPSSeaLabFramework
{
public:
	CRPSSeaLabFramework();
	~CRPSSeaLabFramework();

	//coherence
	static void ComputeCrossCoherenceVectorF(const CRPSSeaLabsimuData &Data, vec &dCohVector, QStringList &strInformation);

	static void ComputeCrossCoherenceMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation);

	static void ComputeCoherenceCubePPF(const CRPSSeaLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation);

	static void ComputeCoherenceValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	//correlation
	static void ComputeCrossCorrelationVectorT(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation);

	static void ComputeCrossCorrelationVectorP(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation);

	static void ComputeCrossCorrelationMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation);

	static void ComputeCrossCorrelationCubePPT(const CRPSSeaLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation);

	static void ComputeCrossCorrelationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	//directional spectrum
	static void ComputeCrossDirectionalSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeCrossDirectionalSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);
	
	//direction distribution
	static void ComputeDirectionsVectorD(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation);

	static void ComputeDirectionsVectorF(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation);

	static void ComputeDirectionsVectorT(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation);

	static void ComputeDirectionsMatrixDP(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation);

	static void ComputeDirectionsMatrixTD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation);

	static void ComputeDirectionsMatrixFD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation);

	static void ComputeDirectionsCubeFTD(const CRPSSeaLabsimuData &Data, cube &dDirectionCube, QStringList &strInformation);

	static void ComputeDirectionsValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	//direction spreading
	static void ComputeSpreadingFunctionVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeSpreadingFunctionVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeSpreadingFunctionVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeSpreadingFunctionVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeSpreadingFunctionMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeSpreadingFunctionMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeSpreadingFunctionMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeSpreadingFunctionMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeSpreadingFunctionMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeSpreadingFunctionMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeSpreadingFunctionCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeSpreadingFunctionCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeSpreadingFunctionCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeSpreadingFunctionValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	//frequency distribution
	static void ComputeFrequenciesVectorF(const CRPSSeaLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation);

	static void ComputeFrequenciesMatrixFP(const CRPSSeaLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation);

	//location distribution
	static void ComputeLocationCoordinateMatrixP3(const CRPSSeaLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	//wind mean
	static void ComputeMeanWindSpeedVectorP(const CRPSSeaLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation);

	static void ComputeMeanWindSpeedVectorT(const CRPSSeaLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation);

	static void ComputeMeanWindSpeedMatrixTP(const CRPSSeaLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation);

	static void ComputeMeanWindSpeedValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation);

	//modulation function
	static void ComputeModulationVectorT(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	static void ComputeModulationVectorF(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	static void ComputeModulationVectorP(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	static void ComputeModulationVectorD(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation);

	static void ComputeModulationMatrixTP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationMatrixFP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationMatrixTD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationMatrixFD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationMatrixTF(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation);

	static void ComputeModulationCubeTFP(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation);

	static void ComputeModulationCubeTFD(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation);

	static void ComputeModulationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	//psd decomposition
	static void ComputeDecomposedCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation);

	static void ComputeDecomposedCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	//randomness
	static void GenerateRandomArrayFP(const CRPSSeaLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	static void ComputeRandomValue(const CRPSSeaLabsimuData &Data, double &dValue, QStringList &strInformation);

	// psd
	static void ComputeCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	static void ComputeCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	static void ComputeCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

};

#endif
