
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
void CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

	if (NULL == SelectedXSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedXSpectrumObject->ComputeXAutoSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedXSpectrumObject;
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



// Y spectrum
void CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

	if (NULL == SelectedYSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedYSpectrumObject->ComputeYAutoSpectrumVectorF(Data, dPSDVector, strInformation);

	// Delete the object
	delete SelectedYSpectrumObject;
}

void CRPSWindLabFramework::ComputeYCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
    // Build an along wind psd object
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

// Z spectrum
void CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

	if (NULL == SelectedZSpectrumObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedZSpectrumObject->ComputeZAutoSpectrumVectorF(Data, dPSDVector, strInformation);

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


void CRPSWindLabFramework::ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	// Build an along wind psd object
	IrpsWLXSpectrum * SelectedXSpectrumObject = CrpsXSpectrumFactory::BuildXSpectrum(Data.spectrumModel);

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
	IrpsWLYSpectrum * SelectedYSpectrumObject = CrpsYSpectrumFactory::BuildYSpectrum(Data.spectrumModel);

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
	IrpsWLZSpectrum * SelectedZSpectrumObject = CrpsZSpectrumFactory::BuildZSpectrum(Data.spectrumModel);

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

void CRPSWindLabFramework::ComputeAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	if (Data.direction == 1)
	{
        CRPSWindLabFramework::ComputeXAutoSpectrumVectorF(Data, dPSDVector, strInformation);
	}
	else if (Data.direction == 2)
	{
        CRPSWindLabFramework::ComputeYAutoSpectrumVectorF(Data, dPSDVector, strInformation);

	}
	else if (Data.direction == 3)
	{
        CRPSWindLabFramework::ComputeZAutoSpectrumVectorF(Data, dPSDVector, strInformation);
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
     IrpsWLFrequencyDistribution * SelectedFrequencyDistributionObject = CrpsFrequencyDistributionFactory::BuildFrequencyDistribution(Data.freqencyDistribution);

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

void CRPSWindLabFramework::TableToolCompute(const CRPSWindLabsimuData &Data, const mat &inputTable, mat &outputTable, QStringList &strInformation)
{
	IrpsWLTableTool * SelectedTableTool = CrpsTableToolFactory::BuildTableTool(Data.tableTool);

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
	IrpsWLMatrixTool * SelectedMatrixTool = CrpsMatrixToolFactory::BuildMatrixTool(Data.matrixTool);

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
	IrpsWLUserDefinedRPSObject* SelectedUserDefinedRPSObject = CrpsUserDefinedRPSObjectFactory::BuildUserDefinedRPSObject(Data.userDefinedRPSObject);

	if (NULL == SelectedUserDefinedRPSObject)
	{
		return;
	}

	// Compute the frequency distribution object
    SelectedUserDefinedRPSObject->UserDefinedRPSObjectCompute(Data, dresult, strInformation);

	// Delete the object
	delete SelectedUserDefinedRPSObject;
}



