
#include "RPSDavenportCoherence.h"
#include "widgets/davenportcoherencedialog.h"
#include "RPSWindLabFramework.h"
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/coherence/DavenportCoherence.h"
#include "myWidgets/RPSDavenportCoherenceDialog.h"


#include <QMessageBox>

// The decay coefficient Cx
static double dExponentialDecayCx = 10;

// The decay coefficient Cy
static double dExponentialDecayCy = 7;

// The decay coefficient Cy
static double dExponentialDecayCz = 6;

bool CRPSDavenportCoherence::ComputeCrossCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
    rps::WindVelocity::DavenportCoherence davenportCoherence;

	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dTime, strInformation);
	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dTime, strInformation);

    dValue = davenportCoherence.computeCoherenceValue(dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dMeanSpeed1, dMeanSpeed2);

	return true;
}

bool CRPSDavenportCoherence::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
//	// the input diolag
//	std::unique_ptr<DavenportCoherenceDialog> dlg(new DavenportCoherenceDialog(dExponentialDecayCx, dExponentialDecayCy, dExponentialDecayCz));

//	if (dlg->exec() == QDialog::Accepted) //
//	{
//		dExponentialDecayCx = dlg->m_decayCx;
//		dExponentialDecayCy = dlg->m_decayCy;
//		dExponentialDecayCz = dlg->m_decayCz;
//	}

//	return true;

    // the input diolag
    std::unique_ptr<RPSDavenportCoherenceDialog> dlg(new RPSDavenportCoherenceDialog(dExponentialDecayCx, dExponentialDecayCy, dExponentialDecayCz));

    if (dlg->exec() == QDialog::Accepted) //
    {
        dExponentialDecayCx = dlg->m_constant1;
        dExponentialDecayCy = dlg->m_constant2;
        dExponentialDecayCz = dlg->m_constant3;
    }

    return true;
}

bool CRPSDavenportCoherence::ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
	// The coherence value
	double dCoherenceValue = 0.0;
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
    vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, dVarVector, strInformation);

	const double dTime = Data.minTime + Data.timeIncrement * (Data.timeIndex);

	for (int loop3 = 0; loop3 < Data.numberOfFrequency; loop3++)
	{
        ComputeCrossCoherenceValue(Data, dCoherenceValue, dLocCoord(Data.locationJ, 0), dLocCoord(Data.locationJ, 1), dLocCoord(Data.locationJ, 2), dLocCoord(Data.locationK, 0), dLocCoord(Data.locationK, 1), dLocCoord(Data.locationK, 2), dVarVector(loop3), dTime, strInformation);

		dValVector(loop3) = dCoherenceValue;
	}

	return true;
}

bool CRPSDavenportCoherence::ComputeCrossCoherenceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    // The coherence value
    double dCoherenceValue = 0.0;
    mat dLocCoord(Data.numberOfSpatialPosition, 3);
    vec dFrequencies(Data.numberOfFrequency);
    vec freqVar(Data.numberOfFrequency);

    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    if(!returnResult)
    {
       strInformation.append("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
	
	returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, freqVar, dFrequencies, strInformation);
    if(!returnResult)
    {
       strInformation.append("The computation of the frequencies vector has failed.") ;
       return false;
    }
	
	const double dfrequency = dFrequencies(Data.frequencyIndex);

    for (int loop3 = 0; loop3 < Data.numberOfTimeIncrements; loop3++)
    {
        const double dTime = Data.minTime + Data.timeIncrement * (loop3);
        dVarVector(loop3) = dTime;
        ComputeCrossCoherenceValue(Data, dCoherenceValue, dLocCoord(Data.locationJ, 0), dLocCoord(Data.locationJ, 1), dLocCoord(Data.locationJ, 2), dLocCoord(Data.locationK, 0), dLocCoord(Data.locationK, 1), dLocCoord(Data.locationK, 2), dfrequency, dTime, strInformation);

        dValVector(loop3) = dCoherenceValue;
    }

	return true;
}

bool CRPSDavenportCoherence::ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dFrequencies(Data.numberOfFrequency);
    vec variables(Data.numberOfFrequency);

	// Compute location coordinates
	bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    if(!returnResult)
    {
       strInformation.append("The computation of the location coordinates matrix has failed.") ;
       return false;
    }
	
	returnResult = CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, variables, dFrequencies, strInformation);
if(!returnResult)
    {
       strInformation.append("The computation of the frequencies vector has failed.") ;
       return false;
    }
	double coherence = 0.0;
	double dTime = Data.timeIncrement * (Data.timeIndex);
	double frequency = dFrequencies(Data.frequencyIndex);

	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
		{
            ComputeCrossCoherenceValue(Data, coherence, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), frequency, dTime, strInformation);

			dCoherenceMatrix(loop1, loop2) = coherence;
		}
	}

	return true;
}
