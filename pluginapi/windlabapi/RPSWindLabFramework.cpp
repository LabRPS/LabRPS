
#include "RPSWindLabFramework.h"
#include <iostream> 
#include <math.h>
#include <fstream>				// rqd. for file i
#include "RPSWindLabAPI.h"

using namespace std;

CRPSWindLabFramework::CRPSWindLabFramework()
{
}

CRPSWindLabFramework::~CRPSWindLabFramework()
{
}

//coherence function
void CRPSWindLabFramework::ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dCohVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCrossCoherenceVectorF(Data, dCohVector, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCrossCoherenceMatrixPP(Data, dCoherenceMatrix, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSWindLabFramework::ComputeCoherenceCubePPF(const CRPSWindLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCoherenceCubePPF(Data, dCoherenceCube, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}

//correlation function
void CRPSWindLabFramework::ComputeCrossCorrelationVectorT(const CRPSWindLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationVectorT(Data, dCorrelationVector, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
void CRPSWindLabFramework::ComputeCrossCorrelationVectorP(const CRPSWindLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationVectorP(Data, dCorrelationVector, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
void CRPSWindLabFramework::ComputeCrossCorrelationMatrixPP(const CRPSWindLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationMatrixPP(Data, dCorrelationMatrix, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
void CRPSWindLabFramework::ComputeCrossCorrelationCubePPT(const CRPSWindLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationCubePPT(Data, dCorrelationCube, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
//frequency distribution
void CRPSWindLabFramework::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	// Build a frequency distribution object
	IrpsWLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(Data.freqencyDistribution);

	if (NULL == SelectedFrequencyDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedFrequencyDistributionObject->ComputeFrequenciesVectorF(Data, dFrequencyVector, strInformation);

	// Delete the object
	delete SelectedFrequencyDistributionObject;
}
void CRPSWindLabFramework::ComputeFrequenciesMatrixFP(const CRPSWindLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{
	// Build a frequency distribution object
	IrpsWLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(Data.freqencyDistribution);

	if (NULL == SelectedFrequencyDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedFrequencyDistributionObject->ComputeFrequenciesMatrixFP(Data, dFrequencyMatrix, strInformation);

	// Delete the object
	delete SelectedFrequencyDistributionObject;
}
//location distribution
void CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsWLLocationDistribution* SelectedDistrObject = CrpsLocationDistributionFactory::BuildLocationDistribution(Data.spatialDistribution);

	if (NULL == SelectedDistrObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedDistrObject->ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Delete the object
	delete SelectedDistrObject;
}
//mean wind speed
void CRPSWindLabFramework::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedVectorP(Data, dMeanSpeedVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}
void CRPSWindLabFramework::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedVectorT(Data, dMeanSpeedVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}
void CRPSWindLabFramework::ComputeMeanWindSpeedMatrixTP(const CRPSWindLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedMatrixTP(Data, dMeanSpeedMatrix, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}
//modulation function
void CRPSWindLabFramework::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorT(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSWindLabFramework::ComputeModulationVectorF(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorF(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSWindLabFramework::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorP(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSWindLabFramework::ComputeModulationMatrixTP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixTP(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSWindLabFramework::ComputeModulationMatrixFP(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixFP(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSWindLabFramework::ComputeModulationMatrixTF(const CRPSWindLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixTF(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSWindLabFramework::ComputeModulationCubeTFP(const CRPSWindLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationCubeTFP(Data, dModulationCube, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
//psd decomposition

void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixPP(Data, dCPSDDecomMatrix, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}

void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}

void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumCubePPF(Data, dCPSDDecomCube, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumCubePPT(Data, dCPSDDecomCube, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}

//randomness
void CRPSWindLabFramework::GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLRandomness * SelectedRandomnessObject = CrpsRandomnessFactory::BuildRandomness(Data.randomnessProvider);

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
// X spectrum
void CRPSWindLabFramework::ComputeXCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSWindLabFramework::ComputeXCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSWindLabFramework::ComputeXCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CRPSWindLabFramework::ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSWindLabFramework::ComputeXCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSWindLabFramework::ComputeXCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSWindLabFramework::ComputeXCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSWindLabFramework::ComputeXCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}
void CRPSWindLabFramework::ComputeXCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}

// Y spectrum
void CRPSWindLabFramework::ComputeYCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}
void CRPSWindLabFramework::ComputeYCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}

// Z spectrum
void CRPSWindLabFramework::ComputeZCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}
void CRPSWindLabFramework::ComputeZCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedZSpectrumObject->ComputeZCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}


//////////
void CRPSWindLabFramework::ComputeCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCoherenceValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}

void CRPSWindLabFramework::ComputeCrossCorrelationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}


void CRPSWindLabFramework::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dTime, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}

void CRPSWindLabFramework::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}


void CRPSWindLabFramework::ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedPSDValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}

void CRPSWindLabFramework::ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLRandomness * SelectedRandomnessObject = CrpsRandomnessFactory::BuildRandomness(Data.randomnessProvider);

	if (NULL == SelectedRandomnessObject)
	{
		return;
	}

	if (Data.comparisonMode)
	{

	}

	// Compute the frequency distribution object
	SelectedRandomnessObject->ComputeRandomValue(Data, dValue, strInformation);

	// Delete the object
	delete SelectedRandomnessObject;
}


void CRPSWindLabFramework::ComputeXCrossSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedXSpectrumObject->ComputeXCrossSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}

void CRPSWindLabFramework::ComputeYCrossSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedYSpectrumObject->ComputeYCrossSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}

void CRPSWindLabFramework::ComputeZCrossSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

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

void CRPSWindLabFramework::ComputeCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumVectorF(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumVectorF(Data, dPSDVector, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumVectorT(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumVectorT(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumVectorT(Data, dPSDVector, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumVectorP(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumVectorP(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumVectorP(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumVectorP(Data, dPSDVector, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumMatrixTP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumMatrixFP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumMatrixTF(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumCubePPF(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumCubePPF(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumCubePPF(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumCubePPF(Data, dPSDCube, strInformation);
	}
}
void CRPSWindLabFramework::ComputeCrossSpectrumCubePPT(const CRPSWindLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
		CRPSWindLabFramework::ComputeXCrossSpectrumCubePPT(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 2)
	{
		CRPSWindLabFramework::ComputeYCrossSpectrumCubePPT(Data, dPSDCube, strInformation);
	}
	else if (Data.direction == 3)
	{
		CRPSWindLabFramework::ComputeZCrossSpectrumCubePPT(Data, dPSDCube, strInformation);
	}
}

ObjectDescription CRPSWindLabFramework::getSpatialDistributionObjDescription(const QString &objectName)
{
	ObjectDescription description;
		
	description.m_pluginName = CrpsLocationDistributionFactory::GetOwnerPlugin();
	description.m_description = CrpsLocationDistributionFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsLocationDistributionFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsLocationDistributionFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsLocationDistributionFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsLocationDistributionFactory::GetDateMap()[objectName];

	return description;
}


ObjectDescription CRPSWindLabFramework::getMeanProfilObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsMeanFactory::GetOwnerPlugin();
	description.m_description = CrpsMeanFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsMeanFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsMeanFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsMeanFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsMeanFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getAlongWindSpectrumObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsXSpectrumFactory::GetOwnerPlugin();
	description.m_description = CrpsXSpectrumFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsXSpectrumFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsXSpectrumFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsXSpectrumFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsXSpectrumFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getVerticalWindSpectrumObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsYSpectrumFactory::GetOwnerPlugin();
	description.m_description = CrpsYSpectrumFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsYSpectrumFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsYSpectrumFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsYSpectrumFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsYSpectrumFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getAcrossWindSpectrumObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsZSpectrumFactory::GetOwnerPlugin();
	description.m_description = CrpsZSpectrumFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsZSpectrumFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsZSpectrumFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsZSpectrumFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsZSpectrumFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getDecomposedSpectrumObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsPSDdecomMethodFactory::GetOwnerPlugin();
	description.m_description = CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsPSDdecomMethodFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsPSDdecomMethodFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsPSDdecomMethodFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsPSDdecomMethodFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getCoherenceFunctionObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsCoherenceFactory::GetOwnerPlugin();
	description.m_description = CrpsCoherenceFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsCoherenceFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsCoherenceFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsCoherenceFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsCoherenceFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getSimulationMethodObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsSimuMethodFactory::GetOwnerPlugin();
	description.m_description = CrpsSimuMethodFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsSimuMethodFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsSimuMethodFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsSimuMethodFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsSimuMethodFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getFrequencyDistributionObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsFrequencyDistributionFactory::GetOwnerPlugin();
	description.m_description = CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsFrequencyDistributionFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsFrequencyDistributionFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsFrequencyDistributionFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsFrequencyDistributionFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getRandomnessProviderObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsRandomnessFactory::GetOwnerPlugin();
	description.m_description = CrpsRandomnessFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsRandomnessFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsRandomnessFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsRandomnessFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsRandomnessFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getModulationFunctionObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsModulationFactory::GetOwnerPlugin();
	description.m_description = CrpsModulationFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsModulationFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsModulationFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsModulationFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsModulationFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getCorrelationFunctionObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsCorrelationFactory::GetOwnerPlugin();
	description.m_description = CrpsCorrelationFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsCorrelationFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsCorrelationFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsCorrelationFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsCorrelationFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getTableToolObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsTableToolFactory::GetOwnerPlugin();
	description.m_description = CrpsTableToolFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsTableToolFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsTableToolFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsTableToolFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsTableToolFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getMatrixToolObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsMatrixToolFactory::GetOwnerPlugin();
	description.m_description = CrpsMatrixToolFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsMatrixToolFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsMatrixToolFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsMatrixToolFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsMatrixToolFactory::GetDateMap()[objectName];

	return description;
}

ObjectDescription CRPSWindLabFramework::getUserDefinedRPSObjDescription(const QString &objectName)
{
	ObjectDescription description;

	description.m_pluginName = CrpsUserDefinedRPSObjectFactory::GetOwnerPlugin();
	description.m_description = CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsUserDefinedRPSObjectFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsUserDefinedRPSObjectFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsUserDefinedRPSObjectFactory::GetDateMap()[objectName];

	return description;
}

void CRPSWindLabFramework::TableToolComputePFT(const CRPSWindLabsimuData &Data, const mat &inputTable, mat &outputTable, QStringList &strInformation)
{
	IrpsWLTableTool * SelectedTableTool = CrpsTableToolFactory::BuildTableTool(Data.tableTool);

	if (NULL == SelectedTableTool)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedTableTool->TableToolComputePFT(Data, inputTable,outputTable, strInformation);

	// Delete the object
	delete SelectedTableTool;
}

void CRPSWindLabFramework::MatrixToolComputePFT(const CRPSWindLabsimuData &Data, const mat &inputMatrix, mat &outputMatrix, QStringList &strInformation)
{
	IrpsWLMatrixTool * SelectedMatrixTool = CrpsMatrixToolFactory::BuildMatrixTool(Data.matrixTool);

	if (NULL == SelectedMatrixTool)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedMatrixTool->MatrixToolComputePFT(Data, inputMatrix,outputMatrix, strInformation);

	// Delete the object
	delete SelectedMatrixTool;
}

void CRPSWindLabFramework::UserDefinedRPSObjectComputePFT(const CRPSWindLabsimuData &Data, cube &dresultCube, QStringList &strInformation)
{
	IrpsWLUserDefinedRPSObject* SelectedUserDefinedRPSObject = CrpsUserDefinedRPSObjectFactory::BuildUserDefinedRPSObject(Data.userDefinedRPSObject);

	if (NULL == SelectedUserDefinedRPSObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedUserDefinedRPSObject->UserDefinedRPSObjectComputePFT(Data, dresultCube, strInformation);

	// Delete the object
	delete SelectedUserDefinedRPSObject;
}



