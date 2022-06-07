
#include "RPSSeismicLabFramework.h"
#include <iostream> 
#include <math.h>
#include <fstream>				// rqd. for file i
#include "RPSSeismicLabAPI.h"

using namespace std;


CRPSSeismicLabFramework::CRPSSeismicLabFramework()
{
}

CRPSSeismicLabFramework::~CRPSSeismicLabFramework()
{
}


//coherence
void CRPSSeismicLabFramework::ComputeCrossCoherenceVectorF(const CRPSSeismicLabsimuData &Data, vec &dCohVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCoherence * SelectedCoherenceObject = CrpsSLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCrossCoherenceVectorF(Data, dCohVector, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSSeismicLabFramework::ComputeCrossCoherenceMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCoherence * SelectedCoherenceObject = CrpsSLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCrossCoherenceMatrixPP(Data, dCoherenceMatrix, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSSeismicLabFramework::ComputeCoherenceCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCoherence * SelectedCoherenceObject = CrpsSLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCoherenceCubePPF(Data, dCoherenceCube, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSSeismicLabFramework::ComputeCoherenceValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCoherence * SelectedCoherenceObject = CrpsSLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCoherenceValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
//correlation
void CRPSSeismicLabFramework::ComputeCrossCorrelationVectorT(const CRPSSeismicLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCorrelation * SelectedCorrelationObject = CrpsSLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorrelationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorrelationObject->ComputeCrossCorrelationVectorT(Data, dCorrelationVector, strInformation);

	// Delete the object
	delete SelectedCorrelationObject;
}
void CRPSSeismicLabFramework::ComputeCrossCorrelationVectorP(const CRPSSeismicLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCorrelation * SelectedCorrelationObject = CrpsSLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorrelationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorrelationObject->ComputeCrossCorrelationVectorP(Data, dCorrelationVector, strInformation);

	// Delete the object
	delete SelectedCorrelationObject;
}
void CRPSSeismicLabFramework::ComputeCrossCorrelationMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCorrelation * SelectedCorrelationObject = CrpsSLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorrelationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorrelationObject->ComputeCrossCorrelationMatrixPP(Data, dCorrelationMatrix, strInformation);

	// Delete the object
	delete SelectedCorrelationObject;
}
void CRPSSeismicLabFramework::ComputeCrossCorrelationCubePPT(const CRPSSeismicLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCorrelation * SelectedCorrelationObject = CrpsSLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorrelationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorrelationObject->ComputeCrossCorrelationCubePPT(Data, dCorrelationCube, strInformation);

	// Delete the object
	delete SelectedCorrelationObject;
}
void CRPSSeismicLabFramework::ComputeCrossCorrelationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLCorrelation * SelectedCorrelationObject = CrpsSLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorrelationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorrelationObject->ComputeCrossCorrelationValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedCorrelationObject;
}
//frequency
void CRPSSeismicLabFramework::ComputeFrequenciesVectorF(const CRPSSeismicLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	// Build a frequency distribution object
	IrpsSLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsSLFrequencyDistributionFactory::BuildFrequencyDistribution(Data.freqencyDistribution);

	if (NULL == SelectedFrequencyDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedFrequencyDistributionObject->ComputeFrequenciesVectorF(Data, dFrequencyVector, strInformation);

	// Delete the object
	delete SelectedFrequencyDistributionObject;
}
void CRPSSeismicLabFramework::ComputeFrequenciesMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{
	// Build a frequency distribution object
	IrpsSLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsSLFrequencyDistributionFactory::BuildFrequencyDistribution(Data.freqencyDistribution);

	if (NULL == SelectedFrequencyDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedFrequencyDistributionObject->ComputeFrequenciesMatrixFP(Data, dFrequencyMatrix, strInformation);

	// Delete the object
	delete SelectedFrequencyDistributionObject;
}
//location
void CRPSSeismicLabFramework::ComputeLocationCoordinateMatrixP3(const CRPSSeismicLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsSLLocationDistribution* SelectedDistrObject = CrpsSLLocationDistributionFactory::BuildLocationDistribution(Data.spatialDistribution);

	if (NULL == SelectedDistrObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedDistrObject->ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Delete the object
	delete SelectedDistrObject;
}
//modulation
void CRPSSeismicLabFramework::ComputeModulationVectorT(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorT(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeismicLabFramework::ComputeModulationVectorF(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorF(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeismicLabFramework::ComputeModulationVectorP(const CRPSSeismicLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorP(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeismicLabFramework::ComputeModulationMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixTP(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeismicLabFramework::ComputeModulationMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixFP(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeismicLabFramework::ComputeModulationMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixTF(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeismicLabFramework::ComputeModulationCubeTFP(const CRPSSeismicLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationCubeTFP(Data, dModulationCube, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeismicLabFramework::ComputeModulationValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLModulation * SelectedModulationObject = CrpsSLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
//psd decomposition
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixPP(Data, dCPSDDecomMatrix, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumCubePPF(Data, dCPSDDecomCube, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumCubePPT(Data, dCPSDDecomCube, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeismicLabFramework::ComputeDecomposedPSDValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedPSDValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
//randomness
void CRPSSeismicLabFramework::GenerateRandomArrayFP(const CRPSSeismicLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLRandomness * SelectedRandomnessObject = CrpsSLRandomnessFactory::BuildRandomness(Data.randomnessProvider);

	if (NULL == SelectedRandomnessObject)
	{
		return;
	}

	if (Data.comparisonMode)
	{

	}

	// Compute the frequency distribution object
	SelectedRandomnessObject->GenerateRandomArrayFP(Data, dRandomValueArray, strInformation);

	// Delete the object
	delete SelectedRandomnessObject;
}
void CRPSSeismicLabFramework::ComputeRandomValue(const CRPSSeismicLabsimuData &Data, double &dValue, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLRandomness * SelectedRandomnessObject = CrpsSLRandomnessFactory::BuildRandomness(Data.randomnessProvider);

	if (NULL == SelectedRandomnessObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedRandomnessObject->ComputeRandomValue(Data, dValue, strInformation);

	// Delete the object
	delete SelectedRandomnessObject;
}
//x spectrum
void CRPSSeismicLabFramework::ComputeXCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeXCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLXSpectrum * SelectedXSpectrumObject = CrpsSLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
// Y spectrum
void CRPSSeismicLabFramework::ComputeYCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeYCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLYSpectrum * SelectedYSpectrumObject = CrpsSLYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
// Z spectrum
void CRPSSeismicLabFramework::ComputeZCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSSeismicLabFramework::ComputeZCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSLZSpectrum * SelectedZSpectrumObject = CrpsSLZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}

// X, Y, Z

void CRPSSeismicLabFramework::ComputeCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumVectorF(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumVectorF(Data, dPSDVector, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumVectorT(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumVectorT(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumVectorT(Data, dPSDVector, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumVectorP(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumVectorP(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumVectorP(Data, dPSDVector, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumCubePPF(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumCubePPF(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumCubePPF(Data, dPSDCube, strInformation);
	}
}
void CRPSSeismicLabFramework::ComputeCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSSeismicLabFramework::ComputeXCrossSpectrumCubePPT(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSSeismicLabFramework::ComputeYCrossSpectrumCubePPT(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSSeismicLabFramework::ComputeZCrossSpectrumCubePPT(Data, dPSDCube, strInformation);
	}
}
