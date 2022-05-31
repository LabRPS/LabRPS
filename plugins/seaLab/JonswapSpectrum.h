#pragma once
#include "IrpsSeLSpectrum.h"

class CJonswapSpectrum : public IrpsSeLSpectrum
{
public:
	CJonswapSpectrum();

	void ComputeCrossSpectrumVectorF(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeCrossSpectrumVectorT(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeCrossSpectrumVectorP(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeCrossSpectrumVectorD(const CRPSSeaLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeCrossSpectrumMatrixPP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeCrossSpectrumMatrixTP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeCrossSpectrumMatrixFP(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeCrossSpectrumMatrixTD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeCrossSpectrumMatrixFD(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeCrossSpectrumMatrixTF(const CRPSSeaLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeCrossSpectrumCubePPF(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeCrossSpectrumCubePPD(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeCrossSpectrumCubePPT(const CRPSSeaLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeCrossSpectrumValue(const CRPSSeaLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, const double &dDirection, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation);


	//custom
	double calculateSpectrumIntensityAlpha();
	double calculatePeakFrequencyWp();
	double CalculateJonswapSpectrum(double dFrequency);

public:

	//   S_j (omega) = alpha g^2/omega^5 * exp[-1.2 * (omega_p/omega)^4] * gamma^r
//
//  where r is defined as:
//
//  r = exp[ -(omega - omega_p)^2 / (2*sigma^2*omega_p^2) ]
//
//  Need U_10 (10 m wind speed) and F (fetch) to determine
//     alpha = 0.076 (U_10^2/(F g))^.22
//   omega_p = 22 (g*g/(U_10*F)^(1/3), peak frequency
//     gamma = 3.3
//     sigma = (0.07 for omega<omega_p; 0.09 for omega>omega_p)

	/*double m_IntensityOfSpectrum_dAlpha;
	double m_dGravityAcceleration_G;
	double m__PeakFrequencydOmega_p;
	double m_Gamma;
	double m_dWindSpeed_U10;
	double m_dFetcLength_F;
	double m_dSigma1;
	double m_dSigma2;*/

};

