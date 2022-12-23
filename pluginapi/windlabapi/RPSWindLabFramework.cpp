
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
void CRPSWindLabFramework::ComputeCrossCorrelationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildObject(Data.correlationFunction);

	if (NULL == SelectedCorreObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCorreObject->ComputeCrossCorrelationVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedCorreObject;
}

//frequency distribution
void CRPSWindLabFramework::ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build a frequency distribution object
    IrpsWLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsFrequencyDistributionFactory::BuildObject(Data.freqencyDistribution);

	if (NULL == SelectedFrequencyDistributionObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedFrequencyDistributionObject->ComputeFrequenciesVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedFrequencyDistributionObject;
}

//location distribution
void CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation)
{
	// Build a location distribution object
    IrpsWLLocationDistribution* SelectedDistrObject = CrpsLocationDistributionFactory::BuildObject(Data.spatialDistribution);

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
void CRPSWindLabFramework::ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build a location distribution object
    IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildObject(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedVectorP(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}

void CRPSWindLabFramework::ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build a location distribution object
    IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildObject(Data.meanFunction);

	if (NULL == SelectedMeanObject)
	{
		return;
	}

	// Compute the location matrix
	SelectedMeanObject->ComputeMeanWindSpeedVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedMeanObject;
}


//modulation function
void CRPSWindLabFramework::ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildObject(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}

void CRPSWindLabFramework::ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildObject(Data.modulationFunction);

	if (NULL == SelectedModulationObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedModulationObject->ComputeModulationVectorP(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedModulationObject;
}


void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

	if (NULL == SelectedPSDdecomMethodObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumMatrixPP(Data, dCPSDDecomMatrix, dPSDMatrix, strInformation);

	// Delete the object
	delete SelectedPSDdecomMethodObject;
}

void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedPSDdecomMethodObject;
}

void CRPSWindLabFramework::ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

    if (NULL == SelectedPSDdecomMethodObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedPSDdecomMethodObject->ComputeDecomposedCrossSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedPSDdecomMethodObject;
}


//randomness
void CRPSWindLabFramework::GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLRandomness * SelectedRandomnessObject = CrpsRandomnessFactory::BuildObject(Data.randomnessProvider);

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
void CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedXSpectrumObject->ComputeXAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}

void CRPSWindLabFramework::ComputeXAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedXSpectrumObject->ComputeXAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}

 void CRPSWindLabFramework::ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
 {
     // Build an along wind psd object
     IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

     if (NULL == SelectedXSpectrumObject)
     {
         return;
     }

     // Compute the frequency distribution object
     SelectedXSpectrumObject->ComputeXCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

     // Delete the object
     delete SelectedXSpectrumObject;
 }



// Y spectrum
void CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedYSpectrumObject->ComputeYAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}

void CRPSWindLabFramework::ComputeYAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedYSpectrumObject->ComputeYAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}

void CRPSWindLabFramework::ComputeYCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

    if (NULL == SelectedYSpectrumObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedYSpectrumObject->ComputeYCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

    // Delete the object
    delete SelectedYSpectrumObject;
}

// Z spectrum
void CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedZSpectrumObject->ComputeZAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}

void CRPSWindLabFramework::ComputeZAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedZSpectrumObject->ComputeZAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}

void CRPSWindLabFramework::ComputeZCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

    if (NULL == SelectedZSpectrumObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedZSpectrumObject->ComputeZCrossSpectrumMatrixPP(Data, dPSDMatrix, strInformation);

    // Delete the object
    delete SelectedZSpectrumObject;
}


//////////
void CRPSWindLabFramework::ComputeCrossCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

	if (NULL == SelectedCoherenceObject)
	{
		return;
	}

	// Compute the frequency distribution object
	SelectedCoherenceObject->ComputeCrossCoherenceValue(Data, dValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedCoherenceObject;
}

void CRPSWindLabFramework::ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

    if (NULL == SelectedCoherenceObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedCoherenceObject->ComputeCrossCoherenceVectorF(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedCoherenceObject;
}

void CRPSWindLabFramework::ComputeCrossCoherenceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

    if (NULL == SelectedCoherenceObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedCoherenceObject->ComputeCrossCoherenceVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedCoherenceObject;
}

void CRPSWindLabFramework::ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
    // Build an along wind psd object
    IrpsWLCoherence * SelectedCoherenceObject = CrpsCoherenceFactory::BuildObject(Data.coherenceFunction);

    if (NULL == SelectedCoherenceObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedCoherenceObject->ComputeCrossCoherenceMatrixPP(Data, dCoherenceMatrix, strInformation);

    // Delete the object
    delete SelectedCoherenceObject;
}

void CRPSWindLabFramework::ComputeCrossCorrelationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLCorrelation * SelectedCorreObject = CrpsCorrelationFactory::BuildObject(Data.correlationFunction);

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
    IrpsWLMean* SelectedMeanObject = CrpsMeanFactory::BuildObject(Data.meanFunction);

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
    IrpsWLModulation * SelectedModulationObject = CrpsModulationFactory::BuildObject(Data.modulationFunction);

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
    IrpsWLPSDdecompositionMethod * SelectedPSDdecomMethodObject = CrpsPSDdecomMethodFactory::BuildObject(Data.cpsdDecompositionMethod);

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
    IrpsWLRandomness * SelectedRandomnessObject = CrpsRandomnessFactory::BuildObject(Data.randomnessProvider);

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


void CRPSWindLabFramework::ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
    IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedXSpectrumObject->ComputeXAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
}

void CRPSWindLabFramework::ComputeYAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedYSpectrumObject->ComputeYAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}

void CRPSWindLabFramework::ComputeZAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildObject(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedZSpectrumObject->ComputeZAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedZSpectrumObject;
}


// X, Y, Z

void CRPSWindLabFramework::ComputeAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
        CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);
	}
	else if (Data.direction == 2)
	{
        CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);

	}
	else if (Data.direction == 3)
	{
        CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(Data, dVarVector, dValVector, strInformation);
	}
}

void CRPSWindLabFramework::ComputeAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
        CRPSWindLabFramework::ComputeXAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);
	}
	else if (Data.direction == 2)
	{
        CRPSWindLabFramework::ComputeYAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);

	}
	else if (Data.direction == 3)
	{
        CRPSWindLabFramework::ComputeZAutoSpectrumVectorT(Data, dVarVector, dValVector, strInformation);
	}
}

void CRPSWindLabFramework::ComputeAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
        CRPSWindLabFramework::ComputeXAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);
	}
	else if (Data.direction == 2)
	{
        CRPSWindLabFramework::ComputeYAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);
    }
	else if (Data.direction == 3)
	{
        CRPSWindLabFramework::ComputeZAutoSpectrumValue(Data, dValue, xCoord, yCoord, zCoord, dFrequency, dTime, strInformation);
    }
}

 void CRPSWindLabFramework::ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation)
 {
     // Build a frequency distribution object
     IrpsWLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsFrequencyDistributionFactory::BuildObject(Data.freqencyDistribution);

     if (NULL == SelectedFrequencyDistributionObject)
     {
         return;
     }

     // Compute the frequency distribution object
     SelectedFrequencyDistributionObject->ComputeFrequencyValue(Data, dValue, locationIndex, frequencyIndex, strInformation);

     // Delete the object
     delete SelectedFrequencyDistributionObject;
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

void CRPSWindLabFramework::TableToolCompute(const CRPSWindLabsimuData &Data, const mat &inputTable, mat &outputTable, QStringList &strInformation)
{
    IrpsWLTableTool * SelectedTableTool = CrpsTableToolFactory::BuildObject(Data.tableTool);

	if (NULL == SelectedTableTool)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedTableTool->TableToolCompute(Data, inputTable,outputTable, strInformation);

	// Delete the object
	delete SelectedTableTool;
}

void CRPSWindLabFramework::MatrixToolCompute(const CRPSWindLabsimuData &Data, const mat &inputMatrix, mat &outputMatrix, QStringList &strInformation)
{
    IrpsWLMatrixTool * SelectedMatrixTool = CrpsMatrixToolFactory::BuildObject(Data.matrixTool);

	if (NULL == SelectedMatrixTool)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedMatrixTool->MatrixToolCompute(Data, inputMatrix,outputMatrix, strInformation);

	// Delete the object
	delete SelectedMatrixTool;
}

void CRPSWindLabFramework::UserDefinedRPSObjectCompute(const CRPSWindLabsimuData &Data, cube &dresult, QStringList &strInformation)
{
    IrpsWLUserDefinedRPSObject* SelectedUserDefinedRPSObject = CrpsUserDefinedRPSObjectFactory::BuildObject(Data.userDefinedRPSObject);

	if (NULL == SelectedUserDefinedRPSObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedUserDefinedRPSObject->UserDefinedRPSObjectCompute(Data, dresult, strInformation);

	// Delete the object
	delete SelectedUserDefinedRPSObject;
}

void CRPSWindLabFramework::ComputeCDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLCumulativeProbabilityDistribution * SelectedObject = CrpsCumulativeProbabilityDistributionFactory::BuildObject(Data.cumulativeProbabilityDistribution);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeCDFValue(Data, dValue,x , strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeCDFVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLCumulativeProbabilityDistribution * SelectedObject = CrpsCumulativeProbabilityDistributionFactory::BuildObject(Data.cumulativeProbabilityDistribution);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeCDFVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeGustFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLGustFactor * SelectedObject = CrpsGustFactorFactory::BuildObject(Data.gustFactor);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeGustFactorValue(Data, dValue,x , strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeGustFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLGustFactor * SelectedObject = CrpsGustFactorFactory::BuildObject(Data.gustFactor);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeGustFactorVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeGustFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLGustFactor * SelectedObject = CrpsGustFactorFactory::BuildObject(Data.gustFactor);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeGustFactorVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeKurtosisValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLKurtosis * SelectedObject = CrpsKurtosisFactory::BuildObject(Data.kurtosis);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeKurtosisValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeKurtosisVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLKurtosis * SelectedObject = CrpsKurtosisFactory::BuildObject(Data.kurtosis);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeKurtosisVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeKurtosisVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLKurtosis * SelectedObject = CrpsKurtosisFactory::BuildObject(Data.kurtosis);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeKurtosisVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputePeakFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLPeakFactor * SelectedObject = CrpsPeakFactorFactory::BuildObject(Data.peakFactor);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputePeakFactorValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputePeakFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLPeakFactor * SelectedObject = CrpsPeakFactorFactory::BuildObject(Data.peakFactor);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputePeakFactorVectorP(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputePeakFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLPeakFactor * SelectedObject = CrpsPeakFactorFactory::BuildObject(Data.peakFactor);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputePeakFactorVectorT(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputePDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLProbabilityDensityFunction * SelectedObject = CrpsProbabilityDensityFunctionFactory::BuildObject(Data.probabilityDensityFunction);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputePDFValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputePDFVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLProbabilityDensityFunction * SelectedObject = CrpsProbabilityDensityFunctionFactory::BuildObject(Data.probabilityDensityFunction);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputePDFVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeRoughnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLRoughness * SelectedObject = CrpsRoughnessFactory::BuildObject(Data.roughness);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeRoughnessValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeRoughnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLRoughness * SelectedObject = CrpsRoughnessFactory::BuildObject(Data.roughness);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeRoughnessVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeRoughnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLRoughness * SelectedObject = CrpsRoughnessFactory::BuildObject(Data.roughness);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeRoughnessVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeShearVelocityOfFlowValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLShearVelocityOfFlow * SelectedObject = CrpsShearVelocityOfFlowFactory::BuildObject(Data.shearVelocityOfFlow);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeShearVelocityOfFlowValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeShearVelocityOfFlowVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLShearVelocityOfFlow * SelectedObject = CrpsShearVelocityOfFlowFactory::BuildObject(Data.shearVelocityOfFlow);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeShearVelocityOfFlowVectorP(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeShearVelocityOfFlowVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLShearVelocityOfFlow * SelectedObject = CrpsShearVelocityOfFlowFactory::BuildObject(Data.shearVelocityOfFlow);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeShearVelocityOfFlowVectorT(Data,dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeSkewnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLSkewness * SelectedObject = CrpsSkewnessFactory::BuildObject(Data.skewness);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeSkewnessValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeSkewnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLSkewness * SelectedObject = CrpsSkewnessFactory::BuildObject(Data.skewness);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeSkewnessVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeSkewnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLSkewness * SelectedObject = CrpsSkewnessFactory::BuildObject(Data.skewness);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeSkewnessVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeStandardDeviationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLStandardDeviation * SelectedObject = CrpsStandardDeviationFactory::BuildObject(Data.standardDeviation);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeStandardDeviationValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeStandardDeviationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLStandardDeviation * SelectedObject = CrpsStandardDeviationFactory::BuildObject(Data.standardDeviation);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeStandardDeviationVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeStandardDeviationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLStandardDeviation * SelectedObject = CrpsStandardDeviationFactory::BuildObject(Data.standardDeviation);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeStandardDeviationVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeTurbulenceIntensityValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceIntensity * SelectedObject = CrpsTurbulenceIntensityFactory::BuildObject(Data.turbulenceIntensity);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeTurbulenceIntensityValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeTurbulenceIntensityVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceIntensity * SelectedObject = CrpsTurbulenceIntensityFactory::BuildObject(Data.turbulenceIntensity);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeTurbulenceIntensityVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeTurbulenceIntensityVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceIntensity * SelectedObject = CrpsTurbulenceIntensityFactory::BuildObject(Data.turbulenceIntensity);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeTurbulenceIntensityVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeTurbulenceScaleValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceScale * SelectedObject = CrpsTurbulenceScaleFactory::BuildObject(Data.turbulenceScale);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeTurbulenceScaleValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeTurbulenceScaleVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceScale * SelectedObject = CrpsTurbulenceScaleFactory::BuildObject(Data.turbulenceScale);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeTurbulenceScaleVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeTurbulenceScaleVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLTurbulenceScale * SelectedObject = CrpsTurbulenceScaleFactory::BuildObject(Data.turbulenceScale);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeTurbulenceScaleVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeVarianceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation)
{
    // Build the object
    IrpsWLVariance * SelectedObject = CrpsVarianceFactory::BuildObject(Data.variance);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeVarianceValue(Data, dValue, x, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeVarianceVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLVariance * SelectedObject = CrpsVarianceFactory::BuildObject(Data.variance);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeVarianceVectorP(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeVarianceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLVariance * SelectedObject = CrpsVarianceFactory::BuildObject(Data.variance);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the value
    SelectedObject->ComputeVarianceVectorT(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}
void CRPSWindLabFramework::ComputeWavePassageEffectValue(const CRPSWindLabsimuData &Data, double &dRValue, double &dIValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return;
    }

	// Compute the frequency distribution object
    SelectedObject->ComputeWavePassageEffectValue(Data, dRValue, dIValue, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dTime, strInformation);

	// Delete the object
	delete SelectedObject;
}

void CRPSWindLabFramework::ComputeWavePassageEffectVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, cx_vec &dValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedObject->ComputeWavePassageEffectVectorF(Data, dVarVector, dValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}

void CRPSWindLabFramework::ComputeWavePassageEffectVectorT(const CRPSWindLabsimuData &Data, vec &cVarVector, cx_vec &cValVector, QStringList &strInformation)
{
    // Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedObject->ComputeWavePassageEffectVectorT(Data, cVarVector, cValVector, strInformation);

    // Delete the object
    delete SelectedObject;
}

void CRPSWindLabFramework::ComputeWavePassageEffectMatrixPP(const CRPSWindLabsimuData &Data, cx_mat &cMatrix, QStringList &strInformation)
{
    // Build the object
    IrpsWLWavePassageEffect * SelectedObject = CrpsWavePassageEffectFactory::BuildObject(Data.wavePassageEffect);

    if (NULL == SelectedObject)
    {
        return;
    }

    // Compute the frequency distribution object
    SelectedObject->ComputeWavePassageEffectMatrixPP(Data, cMatrix, strInformation);

    // Delete the object
    delete SelectedObject;
}
