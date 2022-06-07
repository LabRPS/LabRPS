

#include "IrpsSLXSpectrum.h"


class CKanaiTajimiSpectrum : public IrpsSLXSpectrum
{
	void ComputeXCrossSpectrumVectorF(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeXCrossSpectrumVectorT(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeXCrossSpectrumVectorP(const CRPSSeismicLabsimuData &Data, vec &dPSDVector, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixPP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixTP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixFP(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumMatrixTF(const CRPSSeismicLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	void ComputeXCrossSpectrumCubePPF(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeXCrossSpectrumCubePPT(const CRPSSeismicLabsimuData &Data, cube &dPSDCube, QStringList &strInformation);

	void ComputeXCrossSpectrumValue(const CRPSSeismicLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);
};
