#include "JonswapSpectrum.h"
#include "RPSSeaLabFramework.h"
#include "cjonswapspectrumdlg.h"


static double Sigma1 = 0.7;
static double Sigma2 = 0.9;
static double GravityAcceleration_G = 9.81;
static double WindSpeed_U10 = 30;
static double FetcLength_F = 100;
static double Gamma = 3.3;
static double IntensityOfSpectrum_dAlpha = 0;
static double PeakFrequencydOmega_p = 0;


CJonswapSpectrum::CJonswapSpectrum()
{
	/*m_dSigma1 = 0.7;
	m_dSigma2 = 0.9;
	m_dGravityAcceleration_G = 9.81;
	m_dWindSpeed_U10 = 30;
	m_dFetcLength_F = 100;
	m_Gamma = 3.3;*/

}

void CJonswapSpectrum::ComputeCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
	// Local array for the frequencies vector
	vec dFrequencies(Data.numberOfFrequency);
	try
	{
		// Compute the frequency vector
		CRPSSeaLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

		for (int j = 0; j < Data.numberOfFrequency; j++)
		{
			dPSDVector(j) = CalculateJonswapSpectrum(dFrequencies(j));
		}
	}
	catch (...)
	{
		return;
	}
	
}
void CJonswapSpectrum::ComputeCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	for (int i = 0; i < Data.numberOfSpatialPosition; i++)
	{
		for (int j = 0; j < Data.numberOfSpatialPosition; j++)
		{
			dPSDMatrix(i, j) = 111;
		}
	}
}
void CJonswapSpectrum::ComputeCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{
	// Local array for the frequencies vector
	vec dFrequencies(Data.numberOfFrequency);
	try
	{
		// Compute the frequency vector
		CRPSSeaLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

		for (int i = 0; i < Data.numberOfFrequency; i++)
		{
			for (int j = 0; j < Data.numberOfSpatialPosition; j++)
			{
				dPSDMatrix(i, j) = CalculateJonswapSpectrum(dFrequencies(i));
			}
		}
	}
	catch (...)
	{
		return;
	}

}
void CJonswapSpectrum::ComputeCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation)
{

}
void CJonswapSpectrum::ComputeCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation)
{

}

//Initial setting
bool CJonswapSpectrum::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	// the input diolag
	std::unique_ptr<CJonswapSpectrumDlg> dlg(new CJonswapSpectrumDlg(Sigma1, FetcLength_F, GravityAcceleration_G, WindSpeed_U10, Sigma2, Gamma));

	if (dlg->exec() == QDialog::Accepted) //
	{
		Sigma1 = dlg->msigma1;
		FetcLength_F = dlg->mfetcLength;
        GravityAcceleration_G = dlg->mgravityAcceleration;
        WindSpeed_U10 = dlg->mwindSpeed_U10;
		Sigma2 = dlg->msigma2;
        Gamma = dlg->mgamma;

		IntensityOfSpectrum_dAlpha = calculateSpectrumIntensityAlpha();
		PeakFrequencydOmega_p = calculatePeakFrequencyWp();

	}

	return true;
	
}

double CJonswapSpectrum::calculateSpectrumIntensityAlpha()
{
	double velDivF = WindSpeed_U10 / FetcLength_F;

	double tmp = velDivF * WindSpeed_U10 / GravityAcceleration_G;

	return 0.076 * pow(tmp, 0.22);
}

double CJonswapSpectrum::calculatePeakFrequencyWp() 
{
	double velxF = WindSpeed_U10 * FetcLength_F;
	double g2 = GravityAcceleration_G * GravityAcceleration_G;

	return 22 * cbrt(g2 / velxF);
}


double CJonswapSpectrum::CalculateJonswapSpectrum(double dFrequency)
{
	// Compute intermediate values:
	double s = (dFrequency > PeakFrequencydOmega_p ? Sigma2 : Sigma1); // set sigma 
	double dw = dFrequency - PeakFrequencydOmega_p;
	double rexp_denom = s * PeakFrequencydOmega_p;
	double rexp = -pow(dw / rexp_denom, 2) / 2.0;
	double r = exp(rexp);

	double gammaR = pow(Gamma, r);

	double jdistExp = -1.2 * pow(PeakFrequencydOmega_p / dFrequency, 4);
	double c = IntensityOfSpectrum_dAlpha * GravityAcceleration_G * GravityAcceleration_G * pow(dFrequency, -5); // alpha g^2/w^5

	return c * exp(jdistExp) * gammaR;

}