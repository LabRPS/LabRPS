
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

//correlation function
bool CRPSWindLabFramework::ComputeCrossCorrelationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildObject(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedCorreObject;

    //true for sucess and false for failure
    return returnValue;
}

//frequency distribution
bool CRPSWindLabFramework::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build a frequency distribution object
    IrpsWLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsFrequencyDistributionFactory::BuildObject(Data.freqencyDistribution);

	if (NULL == SelectedFrequencyDistributionObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequenciesVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedFrequencyDistributionObject;

    //true for sucess and false for failure
    return returnValue;
}

//location distribution
bool CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// Build a location distribution object
    IrpsWLLocationDistribution* SelectedDistrObject = CrpsLocationDistributionFactory::BuildObject(Data.spatialDistribution);

	if (NULL == SelectedDistrObject)
	{
        return false;
	}

	// Compute the location matrix
    bool returnValue = SelectedDistrObject->ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

	// Delete the object
	delete SelectedDistrObject;

    //true for sucess and false for failure
    return returnValue;
}
//mean wind speed
bool CRPSWindLabFramework::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build a location distribution object
    IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildObject(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

	// Compute the location matrix
    bool returnValue = SelectedMeanObject->ComputeMeanWindSpeedVectorP(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build a location distribution object
    IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildObject(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

	// Compute the location matrix
    bool returnValue = SelectedMeanObject->ComputeMeanWindSpeedVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;

    //true for sucess and false for failure
    return returnValue;
}


//modulation function
bool CRPSWindLabFramework::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildObject(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedModulationObject->ComputeModulationVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildObject(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedModulationObject->ComputeModulationVectorP(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;

    //true for sucess and false for failure
    return returnValue;
}


bool CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixPP(Data, dCPSDDecomMatrix, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedPSDdecomMethodObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedPSDdecomMethodObject;

    //true for sucess and false for failure
    return returnValue;
}


//randomness
bool CRPSWindLabFramework::GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLRandomness * SelectedRandomnessObject = CrpsRandomnessFactory::BuildObject(Data.randomnessProvider);

	if (NULL == SelectedRandomnessObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedRandomnessObject->GenerateRandomArrayFP(Data, dRandomValueArray, strInformation);

	// Delete the object
	delete SelectedRandomnessObject;

    //true for sucess and false for failure
    return returnValue;
}
// X spectrum
bool CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedXSpectrumObject->ComputeXAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeXAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedXSpectrumObject->ComputeXAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

 bool CRPSWindLabFramework::ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
 {
     // Build an along wind psd object
     IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

     if (NULL == SelectedXSpectrumObject)
     {
         return false;
     }

     // Compute the frequency distribution object
     bool returnValue = SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

     // Delete the object
     delete SelectedXSpectrumObject;

     //true for sucess and false for failure
     return returnValue;
 }



// Y spectrum
bool CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedYSpectrumObject->ComputeYAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeYAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedYSpectrumObject->ComputeYAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeYCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

    if (NULL == SelectedYSpectrumObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

    // Delete the object
    delete SelectedYSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

// Z spectrum
bool CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedZSpectrumObject->ComputeZAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeZAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedZSpectrumObject->ComputeZAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeZCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

    if (NULL == SelectedZSpectrumObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

    // Delete the object
    delete SelectedZSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}


//////////
bool CRPSWindLabFramework::ComputeCrossCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceVectorF(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedCoherenceObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCoherenceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedCoherenceObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

    if (NULL == SelectedCoherenceObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedCoherenceObject->ComputeCrossCoherenceMatrixPP(Data, dCoherenceMatrix, strInformation);

    // Delete the object
    delete SelectedCoherenceObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeCrossCorrelationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildObject(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedCorreObject->ComputeCrossCorrelationValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedCorreObject;

    //true for sucess and false for failure
    return returnValue;
}


bool CRPSWindLabFramework::ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation)
{
	// Build a location distribution object
    IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildObject(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
        return false;
	}

	// Compute the location matrix
    bool returnValue = SelectedMeanObject->ComputeMeanWindSpeedValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dTime, strInformation);

	// Delete the object
	delete SelectedMeanObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildObject(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedModulationObject->ComputeModulationValue(Data, dValue, dLocationxCoord, dLocationyCoord, dLocationzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedModulationObject;

    //true for sucess and false for failure
    return returnValue;
}


bool CRPSWindLabFramework::ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedPSDdecomMethodObject->ComputeDecomposedPSDValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLRandomness * SelectedRandomnessObject = CrpsRandomnessFactory::BuildObject(Data.randomnessProvider);

	if (NULL == SelectedRandomnessObject)
	{
        return false;
	}

	if (Data.comparisonMode)
	{

	}

	// Compute the frequency distribution object
    bool returnValue = SelectedRandomnessObject->ComputeRandomValue(Data, dValue, strInformation);

	// Delete the object
	delete SelectedRandomnessObject;

    //true for sucess and false for failure
    return returnValue;
}


bool CRPSWindLabFramework::ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedXSpectrumObject->ComputeXAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeYAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedYSpectrumObject->ComputeYAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeZAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedZSpectrumObject->ComputeZAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;

    //true for sucess and false for failure
    return returnValue;
}


// X, Y, Z

bool CRPSWindLabFramework::ComputeAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
       return CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);
	}
	else if (Data.direction == 2)
	{
        return CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	}
	else if (Data.direction == 3)
	{
       return CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);
	}

    return false;
}

bool CRPSWindLabFramework::ComputeAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
        return CRPSWindLabFramework::ComputeXAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);
	}
	else if (Data.direction == 2)
	{
       return CRPSWindLabFramework::ComputeYAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	}
	else if (Data.direction == 3)
	{
        return CRPSWindLabFramework::ComputeZAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);
	}

    return false;
}

bool CRPSWindLabFramework::ComputeAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
       return CRPSWindLabFramework::ComputeXAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);
	}
	else if (Data.direction == 2)
	{
       return CRPSWindLabFramework::ComputeYAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);
    }
	else if (Data.direction == 3)
	{
       return CRPSWindLabFramework::ComputeZAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);
    }

    return false;
}

 bool CRPSWindLabFramework::ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation)
 {
     // Build a frequency distribution object
     IrpsWLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsFrequencyDistributionFactory::BuildObject(Data.freqencyDistribution);

     if (NULL == SelectedFrequencyDistributionObject)
     {
         return false;
     }

     // Compute the frequency distribution object
     bool returnValue = SelectedFrequencyDistributionObject->ComputeFrequencyValue(Data, dValue, locationIndex, frequencyIndex, strInformation);

     // Delete the object
     delete SelectedFrequencyDistributionObject;

     //true for sucess and false for failure
     return returnValue;
 }

ObjectDescription CRPSWindLabFramework::getSpatialDistributionObjDescription(const QString &objectName)
{
	ObjectDescription description;
		
    description.m_pluginName =  CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsMeanFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsXSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsYSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsZSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsCoherenceFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsRandomnessFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsModulationFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName =  CrpsCorrelationFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsTableToolFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName = CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()[objectName];
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

    description.m_pluginName =  CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()[objectName];
	description.m_description = CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[objectName];
	description.m_publicationTitle = CrpsUserDefinedRPSObjectFactory::GetTitleMap()[objectName];
	description.m_publicationLink = CrpsUserDefinedRPSObjectFactory::GetLinkMap()[objectName];
	description.m_publicationAuthor = CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[objectName];
	description.m_publicationDate = CrpsUserDefinedRPSObjectFactory::GetDateMap()[objectName];

	return description;
}
ObjectDescription CRPSWindLabFramework::getCDFDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsCumulativeProbabilityDistributionFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getGustFactorDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsGustFactorFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsGustFactorFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsGustFactorFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsGustFactorFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsGustFactorFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsGustFactorFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getKurtosisDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsKurtosisFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsKurtosisFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsKurtosisFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsKurtosisFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsKurtosisFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsKurtosisFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getPeakFactorDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsPeakFactorFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsPeakFactorFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsPeakFactorFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsPeakFactorFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsPeakFactorFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getPDFDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsProbabilityDensityFunctionFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsProbabilityDensityFunctionFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsProbabilityDensityFunctionFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsProbabilityDensityFunctionFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getRoughnessDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsRoughnessFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsRoughnessFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsRoughnessFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsRoughnessFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsRoughnessFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsRoughnessFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getShearVelocityOfFlowDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsShearVelocityOfFlowFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsShearVelocityOfFlowFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsShearVelocityOfFlowFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsShearVelocityOfFlowFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getSkewnessDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsSkewnessFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsSkewnessFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsSkewnessFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsSkewnessFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsSkewnessFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsSkewnessFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getStandardDeviationDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsStandardDeviationFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsStandardDeviationFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsStandardDeviationFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsStandardDeviationFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsStandardDeviationFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getTurbulenceIntensityDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsTurbulenceIntensityFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsTurbulenceIntensityFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsTurbulenceIntensityFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsTurbulenceIntensityFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getTurbulenceScaleDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsTurbulenceScaleFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsTurbulenceScaleFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsTurbulenceScaleFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsTurbulenceScaleFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsTurbulenceScaleFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getVarianceDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsVarianceFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsVarianceFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsVarianceFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsVarianceFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsVarianceFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsVarianceFactory::GetDateMap()[objectName];

    return description;
}
ObjectDescription CRPSWindLabFramework::getWavePassageEffectDescription(const QString &objectName)
{
    ObjectDescription description;

    description.m_pluginName =  CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()[objectName];
    description.m_description = CrpsWavePassageEffectFactory::GetOjectDescriptionMap()[objectName];
    description.m_publicationTitle = CrpsWavePassageEffectFactory::GetTitleMap()[objectName];
    description.m_publicationLink = CrpsWavePassageEffectFactory::GetLinkMap()[objectName];
    description.m_publicationAuthor = CrpsWavePassageEffectFactory::GetAuthorMap()[objectName];
    description.m_publicationDate = CrpsWavePassageEffectFactory::GetDateMap()[objectName];

    return description;
}

bool CRPSWindLabFramework::TableToolCompute(const CRPSWindLabsimuData &Data, const mat &inputTable, mat &outputTable, QStringList &strInformation)
{
    IrpsWLTableTool * SelectedTableTool = CrpsTableToolFactory::BuildObject(Data.tableTool);

	if (NULL == SelectedTableTool)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedTableTool->TableToolCompute(Data, inputTable,outputTable, strInformation);

	// Delete the object
	delete SelectedTableTool;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::MatrixToolCompute(const CRPSWindLabsimuData &Data, const mat &inputMatrix, mat &outputMatrix, QStringList &strInformation)
{
    IrpsWLMatrixTool * SelectedMatrixTool = CrpsMatrixToolFactory::BuildObject(Data.matrixTool);

	if (NULL == SelectedMatrixTool)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedMatrixTool->MatrixToolCompute(Data, inputMatrix,outputMatrix, strInformation);

	// Delete the object
	delete SelectedMatrixTool;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::UserDefinedRPSObjectCompute(const CRPSWindLabsimuData &Data, cube &dresult, QStringList &strInformation)
{
    IrpsWLUserDefinedRPSObject* SelectedUserDefinedRPSObject = CrpsUserDefinedRPSObjectFactory::BuildObject(Data.userDefinedRPSObject);

	if (NULL == SelectedUserDefinedRPSObject)
	{
        return false;
	}

	// Compute the frequency distribution object
    bool returnValue = SelectedUserDefinedRPSObject->UserDefinedRPSObjectCompute(Data, dresult, strInformation);

	// Delete the object
	delete SelectedUserDefinedRPSObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeCDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLCumulativeProbabilityDistribution * SelectedObject = CrpsCumulativeProbabilityDistributionFactory::BuildObject(Data.cumulativeProbabilityDistribution);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeCDFValue(Data, dValue,x , strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeCDFVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLCumulativeProbabilityDistribution * SelectedObject = CrpsCumulativeProbabilityDistributionFactory::BuildObject(Data.cumulativeProbabilityDistribution);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeCDFVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeGustFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLGustFactor * SelectedObject = CrpsGustFactorFactory::BuildObject(Data.gustFactor);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeGustFactorValue(Data, dValue,x , strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeGustFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLGustFactor * SelectedObject = CrpsGustFactorFactory::BuildObject(Data.gustFactor);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeGustFactorVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeGustFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLGustFactor * SelectedObject = CrpsGustFactorFactory::BuildObject(Data.gustFactor);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeGustFactorVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeKurtosisValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLKurtosis * SelectedObject = CrpsKurtosisFactory::BuildObject(Data.kurtosis);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeKurtosisValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeKurtosisVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLKurtosis * SelectedObject = CrpsKurtosisFactory::BuildObject(Data.kurtosis);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeKurtosisVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeKurtosisVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLKurtosis * SelectedObject = CrpsKurtosisFactory::BuildObject(Data.kurtosis);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeKurtosisVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputePeakFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLPeakFactor * SelectedObject = CrpsPeakFactorFactory::BuildObject(Data.peakFactor);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputePeakFactorValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputePeakFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLPeakFactor * SelectedObject = CrpsPeakFactorFactory::BuildObject(Data.peakFactor);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputePeakFactorVectorP(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputePeakFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLPeakFactor * SelectedObject = CrpsPeakFactorFactory::BuildObject(Data.peakFactor);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputePeakFactorVectorT(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputePDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLProbabilityDensityFunction * SelectedObject = CrpsProbabilityDensityFunctionFactory::BuildObject(Data.probabilityDensityFunction);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputePDFValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputePDFVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLProbabilityDensityFunction * SelectedObject = CrpsProbabilityDensityFunctionFactory::BuildObject(Data.probabilityDensityFunction);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputePDFVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeRoughnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLRoughness * SelectedObject = CrpsRoughnessFactory::BuildObject(Data.roughness);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeRoughnessValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeRoughnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLRoughness * SelectedObject = CrpsRoughnessFactory::BuildObject(Data.roughness);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeRoughnessVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeRoughnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLRoughness * SelectedObject = CrpsRoughnessFactory::BuildObject(Data.roughness);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeRoughnessVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeShearVelocityOfFlowValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLShearVelocityOfFlow * SelectedObject = CrpsShearVelocityOfFlowFactory::BuildObject(Data.shearVelocityOfFlow);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeShearVelocityOfFlowVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLShearVelocityOfFlow * SelectedObject = CrpsShearVelocityOfFlowFactory::BuildObject(Data.shearVelocityOfFlow);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowVectorP(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeShearVelocityOfFlowVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLShearVelocityOfFlow * SelectedObject = CrpsShearVelocityOfFlowFactory::BuildObject(Data.shearVelocityOfFlow);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeShearVelocityOfFlowVectorT(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeSkewnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLSkewness * SelectedObject = CrpsSkewnessFactory::BuildObject(Data.skewness);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeSkewnessValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeSkewnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLSkewness * SelectedObject = CrpsSkewnessFactory::BuildObject(Data.skewness);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeSkewnessVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeSkewnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLSkewness * SelectedObject = CrpsSkewnessFactory::BuildObject(Data.skewness);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeSkewnessVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeStandardDeviationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLStandardDeviation * SelectedObject = CrpsStandardDeviationFactory::BuildObject(Data.standardDeviation);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeStandardDeviationValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeStandardDeviationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLStandardDeviation * SelectedObject = CrpsStandardDeviationFactory::BuildObject(Data.standardDeviation);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeStandardDeviationVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeStandardDeviationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLStandardDeviation * SelectedObject = CrpsStandardDeviationFactory::BuildObject(Data.standardDeviation);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeStandardDeviationVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceIntensityValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceIntensity * SelectedObject = CrpsTurbulenceIntensityFactory::BuildObject(Data.turbulenceIntensity);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeTurbulenceIntensityValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceIntensityVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceIntensity * SelectedObject = CrpsTurbulenceIntensityFactory::BuildObject(Data.turbulenceIntensity);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeTurbulenceIntensityVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceIntensityVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceIntensity * SelectedObject = CrpsTurbulenceIntensityFactory::BuildObject(Data.turbulenceIntensity);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeTurbulenceIntensityVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceScaleValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceScale * SelectedObject = CrpsTurbulenceScaleFactory::BuildObject(Data.turbulenceScale);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeTurbulenceScaleValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceScaleVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceScale * SelectedObject = CrpsTurbulenceScaleFactory::BuildObject(Data.turbulenceScale);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeTurbulenceScaleVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeTurbulenceScaleVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceScale * SelectedObject = CrpsTurbulenceScaleFactory::BuildObject(Data.turbulenceScale);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeTurbulenceScaleVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeVarianceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLVariance * SelectedObject = CrpsVarianceFactory::BuildObject(Data.variance);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeVarianceValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeVarianceVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLVariance * SelectedObject = CrpsVarianceFactory::BuildObject(Data.variance);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeVarianceVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeVarianceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLVariance * SelectedObject = CrpsVarianceFactory::BuildObject(Data.variance);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the value
    bool returnValue = SelectedObject->ComputeVarianceVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
bool CRPSWindLabFramework::ComputeWavePassageEffectValue(const CRPSWindLabsimuData &Data, double &dRValue, double &dIValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return false;
    }

	// Compute the frequency distribution object
    bool returnValue = SelectedObject->ComputeWavePassageEffectValue(Data, dRValue, dIValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeWavePassageEffectVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, cx_vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedObject->ComputeWavePassageEffectVectorF(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeWavePassageEffectVectorT(const CRPSWindLabsimuData &Data, vec &cVarVector, cx_vec &cValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedObject->ComputeWavePassageEffectVectorT(Data, cVarVector, cValVector, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}

bool CRPSWindLabFramework::ComputeWavePassageEffectMatrixPP(const CRPSWindLabsimuData &Data, cx_mat &cMatrix, QStringList &strInformation)
{
    // Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return false;
    }

    // Compute the frequency distribution object
    bool returnValue = SelectedObject->ComputeWavePassageEffectMatrixPP(Data, cMatrix, strInformation);

    // Delete the object
    delete SelectedObject;

    //true for sucess and false for failure
    return returnValue;
}
