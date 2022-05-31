#include "RPSSeaLabFramework.h"
#include <iostream> 
#include <math.h>
#include <fstream>				// rqd. for file i
#include "RPSSeaLabAPI.h"

using namespace std;


CRPSSeaLabFramework::CRPSSeaLabFramework()
{
}

CRPSSeaLabFramework::~CRPSSeaLabFramework()
{
}

//coherence
void CRPSSeaLabFramework::ComputeCrossCoherenceVectorF(const CRPSSeaLabsimuData &Data, vec &dCohVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCoherence * SelectedCoherenceObject = CrpsSeLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCrossCoherenceVectorF(Data, dCohVector, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSSeaLabFramework::ComputeCrossCoherenceMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCoherence * SelectedCoherenceObject = CrpsSeLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCrossCoherenceMatrixPP(Data, dCoherenceMatrix, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSSeaLabFramework::ComputeCoherenceCubePPF(const CRPSSeaLabsimuData &Data, cube &dCoherenceCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCoherence * SelectedCoherenceObject = CrpsSeLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCoherenceCubePPF(Data, dCoherenceCube, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}
void CRPSSeaLabFramework::ComputeCoherenceValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCoherence * SelectedCoherenceObject = CrpsSeLCoherenceFactory::BuildCoherence(Data.coherenceFunction);

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
void CRPSSeaLabFramework::ComputeCrossCorrelationVectorT(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCorrelation * SelectedCorreObject = CrpsSeLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationVectorT(Data, dCorrelationVector, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
void CRPSSeaLabFramework::ComputeCrossCorrelationVectorP(const CRPSSeaLabsimuData &Data, vec &dCorrelationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCorrelation * SelectedCorreObject = CrpsSeLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationVectorP(Data, dCorrelationVector, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
void CRPSSeaLabFramework::ComputeCrossCorrelationMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCorrelationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCorrelation * SelectedCorreObject = CrpsSeLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationMatrixPP(Data, dCorrelationMatrix, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
void CRPSSeaLabFramework::ComputeCrossCorrelationCubePPT(const CRPSSeaLabsimuData &Data, cube &dCorrelationCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCorrelation * SelectedCorreObject = CrpsSeLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationCubePPT(Data, dCorrelationCube, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}
void CRPSSeaLabFramework::ComputeCrossCorrelationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLCorrelation * SelectedCorreObject = CrpsSeLCorrelationFactory::BuildCorrelation(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, dDirection, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}

//directional spectrum
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumVectorD(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumMatrixTD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumMatrixFD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumCubePPD(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossDirectionalSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionalSpectrum * SelectedDirectionalSpectrumObject = CrpsSeLDirectionalSpectrumFactory::BuildDirectionalSpectrum(Data.directionalSpectrumFunction);

	if (NULL == SelectedDirectionalSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionalSpectrumObject->ComputeCrossDirectionalSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, dDirection, strInformation);

	// Delete the object
	delete SelectedDirectionalSpectrumObject;
}

//direction distribution
void CRPSSeaLabFramework::ComputeDirectionsVectorD(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsVectorD(Data, dDirectionVector, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}
void CRPSSeaLabFramework::ComputeDirectionsVectorF(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsVectorF(Data, dDirectionVector, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}
void CRPSSeaLabFramework::ComputeDirectionsVectorT(const CRPSSeaLabsimuData &Data, vec &dDirectionVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsVectorT(Data, dDirectionVector, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}
void CRPSSeaLabFramework::ComputeDirectionsMatrixDP(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsMatrixDP(Data, dDirectionMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}
void CRPSSeaLabFramework::ComputeDirectionsMatrixTD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsMatrixTD(Data, dDirectionMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}
void CRPSSeaLabFramework::ComputeDirectionsMatrixFD(const CRPSSeaLabsimuData &Data, mat &dDirectionMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsMatrixFD(Data, dDirectionMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}
void CRPSSeaLabFramework::ComputeDirectionsCubeFTD(const CRPSSeaLabsimuData &Data, cube &dDirectionCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsCubeFTD(Data, dDirectionCube, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}
void CRPSSeaLabFramework::ComputeDirectionsValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionDistribution * SelectedDirectionDistributionObject = CrpsSeLDirectionDistributionFactory::BuildDirectionDistribution(Data.directionDistributionFunction);

	if (NULL == SelectedDirectionDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionDistributionObject->ComputeDirectionsValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedDirectionDistributionObject;
}

//direction spreading
void CRPSSeaLabFramework::ComputeSpreadingFunctionVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionVectorD(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionMatrixTD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionMatrixFD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionCubePPD(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}
void CRPSSeaLabFramework::ComputeSpreadingFunctionValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLDirectionSpreadingFunction * SelectedDirectionSpreadingFunctionObject = CrpsSeLDirectionSpreadingFunctionFactory::BuildDirectionSpreadingFunction(Data.directionSpreadingFunction);

	if (NULL == SelectedDirectionSpreadingFunctionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedDirectionSpreadingFunctionObject->ComputeSpreadingFunctionValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dFrequency, dTime, dDirection, strInformation);

	// Delete the object
	delete SelectedDirectionSpreadingFunctionObject;
}

//frequency distribution
void CRPSSeaLabFramework::ComputeFrequenciesVectorF(const CRPSSeaLabsimuData &Data, vec &dFrequencyVector, QStringList &strInformation)
{
	// Build a frequency distribution object
	IrpsSeLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsSeLFrequencyDistributionFactory::BuildFrequencyDistribution(Data.freqencyDistribution);

	if (NULL == SelectedFrequencyDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedFrequencyDistributionObject->ComputeFrequenciesVectorF(Data, dFrequencyVector, strInformation);

	// Delete the object
	delete SelectedFrequencyDistributionObject;
}
void CRPSSeaLabFramework::ComputeFrequenciesMatrixFP(const CRPSSeaLabsimuData &Data, mat &dFrequencyMatrix, QStringList &strInformation)
{
	// Build a frequency distribution object
	IrpsSeLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsSeLFrequencyDistributionFactory::BuildFrequencyDistribution(Data.freqencyDistribution);

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
void CRPSSeaLabFramework::ComputeLocationCoordinateMatrixP3(const CRPSSeaLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsSeLLocationDistribution* SelectedDistrObject = CrpsSeLLocationDistributionFactory::BuildLocationDistribution(Data.spatialDistribution);

	if (NULL == SelectedDistrObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedDistrObject->ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Delete the object
	delete SelectedDistrObject;
}

//wind mean
void CRPSSeaLabFramework::ComputeMeanWindSpeedVectorP(const CRPSSeaLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsSeLMean* SelectedMeanObject = CrpsSeLMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedVectorP(Data, dMeanSpeedVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}
void CRPSSeaLabFramework::ComputeMeanWindSpeedVectorT(const CRPSSeaLabsimuData &Data, vec &dMeanSpeedVector, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsSeLMean* SelectedMeanObject = CrpsSeLMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedVectorT(Data, dMeanSpeedVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}
void CRPSSeaLabFramework::ComputeMeanWindSpeedMatrixTP(const CRPSSeaLabsimuData &Data, mat &dMeanSpeedMatrix, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsSeLMean* SelectedMeanObject = CrpsSeLMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedMatrixTP(Data, dMeanSpeedMatrix, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}
void CRPSSeaLabFramework::ComputeMeanWindSpeedValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
	// Build a location distribution object
	IrpsSeLMean* SelectedMeanObject = CrpsSeLMeanFactory::BuildMean(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dTime, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}

//modulation function
void CRPSSeaLabFramework::ComputeModulationVectorT(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorT(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationVectorF(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorF(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationVectorP(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorP(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationVectorD(const CRPSSeaLabsimuData &Data, vec &dModulationVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorD(Data, dModulationVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationMatrixTP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixTP(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationMatrixFP(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixFP(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationMatrixTD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixTD(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationMatrixFD(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixFD(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationMatrixTF(const CRPSSeaLabsimuData &Data, mat &dModulationMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationMatrixTF(Data, dModulationMatrix, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationCubeTFP(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationCubeTFP(Data, dModulationCube, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationCubeTFD(const CRPSSeaLabsimuData &Data, cube &dModulationCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationCubeTFD(Data, dModulationCube, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}
void CRPSSeaLabFramework::ComputeModulationValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLModulation * SelectedModulationObject = CrpsSeLModulationFactory::BuildModulation(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dFrequency, dTime, dDirection, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}

//psd decomposition
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorD(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixPP(Data, dCPSDDecomMatrix, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixTD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixFD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumCubePPF(Data, dCPSDDecomCube, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumCubePPT(Data, dCPSDDecomCube, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dCPSDDecomCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumCubePPD(Data, dCPSDDecomCube, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}
void CRPSSeaLabFramework::ComputeDecomposedCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsSeLPSDdecomMethodFactory::BuildPSDdecomMethod(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, dDirection, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}

//randomness
void CRPSSeaLabFramework::GenerateRandomArrayFP(const CRPSSeaLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLRandomness * SelectedRandomnessObject = CrpsSeLRandomnessFactory::BuildRandomness(Data.randomnessProvider);

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
void CRPSSeaLabFramework::ComputeRandomValue(const CRPSSeaLabsimuData &Data, double &dValue, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLRandomness * SelectedRandomnessObject = CrpsSeLRandomnessFactory::BuildRandomness(Data.randomnessProvider);

	if (NULL == SelectedRandomnessObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedRandomnessObject->ComputeRandomValue(Data, dValue, strInformation);

	// Delete the object
	delete SelectedRandomnessObject;
}

// psd
void CRPSSeaLabFramework::ComputeCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumVectorT(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumVectorP(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumVectorD(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumMatrixTP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumMatrixFP(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumMatrixTD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumMatrixFD(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumMatrixTF(Data, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumCubePPF(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumCubePPD(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumCubePPT(Data, dPSDCube, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
void CRPSSeaLabFramework::ComputeCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsSeLSpectrum * SelectedSpectrumObject = CrpsSeLXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedSpectrumObject->ComputeCrossSpectrumValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, dDirection, strInformation);

	// Delete the object
	delete SelectedSpectrumObject;
}
