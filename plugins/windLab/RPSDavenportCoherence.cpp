
#include "RPSDavenportCoherence.h"
#include "davenportcoherencedialog.h"
#include "RPSWindLabFramework.h"
#include "../../libraries/rpsTools/rpsTools/src/windVelocity/coherence/DavenportCoherence.h"

#include <QMessageBox>

// The decay coefficient Cx
static double dExponentialDecayCx = 10;

// The decay coefficient Cy
static double dExponentialDecayCy = 7;

// The decay coefficient Cy
static double dExponentialDecayCz = 6;

void CRPSDavenportCoherence::ComputeCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
	double dMeanSpeed1 = 0.0;
	double dMeanSpeed2 = 0.0;
    rps::WindVelocity::DavenportCoherence davenportCoherence;

	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed1, dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dTime, strInformation);
	CRPSWindLabFramework::ComputeMeanWindSpeedValue(Data, dMeanSpeed2, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dTime, strInformation);

    dValue = davenportCoherence.computeCoherenceValue(dLocationJxCoord, dLocationJyCoord, dLocationJzCoord, dLocationKxCoord, dLocationKyCoord, dLocationKzCoord, dFrequency, dMeanSpeed1, dMeanSpeed2);
}

bool CRPSDavenportCoherence::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<DavenportCoherenceDialog> dlg(new DavenportCoherenceDialog(dExponentialDecayCx, dExponentialDecayCy, dExponentialDecayCz));

	if (dlg->exec() == QDialog::Accepted) //
	{
		dExponentialDecayCx = dlg->m_decayCx;
		dExponentialDecayCy = dlg->m_decayCy;
		dExponentialDecayCz = dlg->m_decayCz;
	}

	return true;
}

void CRPSDavenportCoherence::ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dCohVector, QStringList &strInformation)
{
	// The coherence value
	double dCoherenceValue = 0.0;
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dFrequencies(Data.numberOfFrequency);

	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double dTime = Data.minTime + Data.timeIncrement * (Data.timeIndex);

	for (int loop3 = 0; loop3 < Data.numberOfFrequency; loop3++)
	{
		ComputeCoherenceValue(Data, dCoherenceValue, dLocCoord(Data.locationJ, 0), dLocCoord(Data.locationJ, 1), dLocCoord(Data.locationJ, 2), dLocCoord(Data.locationK, 0), dLocCoord(Data.locationK, 1), dLocCoord(Data.locationK, 2), dFrequencies(loop3), dTime, strInformation);

		dCohVector(loop3) = dCoherenceValue;
	}
}
void CRPSDavenportCoherence::ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation)
{
	mat dLocCoord(Data.numberOfSpatialPosition, 3);
	vec dFrequencies(Data.numberOfFrequency);

	// Compute location coordinates
	CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

	double coherence = 0.0;
	double dTime = Data.timeIncrement * (Data.timeIndex);
	double frequency = dFrequencies(Data.frequencyIndex);

	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition; loop1++)
	{
		for (int loop2 = 0; loop2 < Data.numberOfSpatialPosition; loop2++)
		{
			ComputeCoherenceValue(Data, coherence, dLocCoord(loop1, 0), dLocCoord(loop1, 1), dLocCoord(loop1, 2), dLocCoord(loop2, 0), dLocCoord(loop2, 1), dLocCoord(loop2, 2), frequency, dTime, strInformation);

			dCoherenceMatrix(loop1, loop2) = coherence;
		}
	}
}
