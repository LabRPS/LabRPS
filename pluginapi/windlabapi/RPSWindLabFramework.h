#ifndef RPSWINDLABFRAMEWORK_H
#define RPSWINDLABFRAMEWORK_H

#include "RPSWindLabAPIdefines.h"
#include "RPSWindLabsimuData.h"
#include "ObjectDescription.h"

class RPS_CORE_API CRPSWindLabFramework
{
public:
	CRPSWindLabFramework();
	~CRPSWindLabFramework();

	// coherence function
    static bool ComputeCrossCoherenceVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeCrossCoherenceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeCrossCoherenceMatrixPP(const CRPSWindLabsimuData &Data, mat &dCoherenceMatrix, QStringList &strInformation);

	// correlation function
    static bool ComputeCrossCorrelationVectorT(const CRPSWindLabsimuData &Data,  vec &dVarVector, vec &dValVector, QStringList &strInformation);

	// frequency distribution
    static bool ComputeFrequenciesVectorF(const CRPSWindLabsimuData &Data,  vec &dVarVector, vec &dValVector, QStringList &strInformation);

	// location distribution
    static bool ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	// mean wind speed
    static bool ComputeMeanWindSpeedVectorP(const CRPSWindLabsimuData &Data,  vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeMeanWindSpeedVectorT(const CRPSWindLabsimuData &Data,  vec &dVarVector, vec &dValVector, QStringList &strInformation);

	// modulation function
    static bool ComputeModulationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeModulationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

	// psd decomposition
    static bool ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation);

	// randomness
    static bool GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation);

	// X spectrum
    static bool ComputeXAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeXAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeXCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);

	// Y spectrum
    static bool ComputeYAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeYAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeYCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);


	// Z spectrum
    static bool ComputeZAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeZAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeZCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);


	// spectrum X, Y, Z
    static bool ComputeAutoSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeAutoSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation);

    static bool ComputeCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dPSDMatrix, QStringList &strInformation);


	/////
    static bool ComputeCrossCoherenceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeCrossCorrelationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeMeanWindSpeedValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dTime, QStringList &strInformation);
    static bool ComputeModulationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationxCoord, const double &dLocationyCoord, const double &dLocationzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation);
    static bool ComputeXAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeYAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeZAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeAutoSpectrumValue(const CRPSWindLabsimuData &Data, double &dValue, const double &xCoord, const double &yCoord, const double &zCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);
    static bool ComputeFrequencyValue(const CRPSWindLabsimuData &Data, double &dValue, const int &locationIndex, const int &frequencyIndex, QStringList &strInformation);

	static ObjectDescription getSpatialDistributionObjDescription(const QString &objectName);
	static ObjectDescription getMeanProfilObjDescription(const QString &objectName);
	static ObjectDescription getAlongWindSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getVerticalWindSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getAcrossWindSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getDecomposedSpectrumObjDescription(const QString &objectName);
	static ObjectDescription getCoherenceFunctionObjDescription(const QString &objectName);
	static ObjectDescription getSimulationMethodObjDescription(const QString &objectName);
	static ObjectDescription getFrequencyDistributionObjDescription(const QString &objectName);
	static ObjectDescription getRandomnessProviderObjDescription(const QString &objectName);
	static ObjectDescription getModulationFunctionObjDescription(const QString &objectName);
	static ObjectDescription getCorrelationFunctionObjDescription(const QString &objectName);
	static ObjectDescription getTableToolObjDescription(const QString &objectName);
	static ObjectDescription getMatrixToolObjDescription(const QString &objectName);
	static ObjectDescription getUserDefinedRPSObjDescription(const QString &objectName);
    static ObjectDescription getCDFDescription(const QString &objectName);
    static ObjectDescription getGustFactorDescription(const QString &objectName);
    static ObjectDescription getKurtosisDescription(const QString &objectName);
    static ObjectDescription getPeakFactorDescription(const QString &objectName);
    static ObjectDescription getPDFDescription(const QString &objectName);
    static ObjectDescription getRoughnessDescription(const QString &objectName);
    static ObjectDescription getShearVelocityOfFlowDescription(const QString &objectName);
    static ObjectDescription getSkewnessDescription(const QString &objectName);
    static ObjectDescription getStandardDeviationDescription(const QString &objectName);
    static ObjectDescription getTurbulenceIntensityDescription(const QString &objectName);
    static ObjectDescription getTurbulenceScaleDescription(const QString &objectName);
    static ObjectDescription getVarianceDescription(const QString &objectName);
    static ObjectDescription getWavePassageEffectDescription(const QString &objectName);

    static bool TableToolCompute(const CRPSWindLabsimuData &Data, const mat &inputTable, mat &outputTable, QStringList &strInformation);
    static bool MatrixToolCompute(const CRPSWindLabsimuData &Data, const mat &inputMatrix, mat &outputMatrix, QStringList &strInformation);
    static bool UserDefinedRPSObjectCompute(const CRPSWindLabsimuData &Data, cube &dresult, QStringList &strInformation);

    static bool ComputeCDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeCDFVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeGustFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeGustFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeGustFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeKurtosisValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeKurtosisVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeKurtosisVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputePeakFactorValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputePeakFactorVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputePeakFactorVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputePDFValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputePDFVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeRoughnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeRoughnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeRoughnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeShearVelocityOfFlowValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeShearVelocityOfFlowVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeShearVelocityOfFlowVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeSkewnessValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeSkewnessVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeSkewnessVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeStandardDeviationValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeStandardDeviationVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeStandardDeviationVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeTurbulenceIntensityValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeTurbulenceIntensityVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeTurbulenceIntensityVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeTurbulenceScaleValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeTurbulenceScaleVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeTurbulenceScaleVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeVarianceValue(const CRPSWindLabsimuData &Data, double &dValue, const double &x, QStringList &strInformation) ;
    static bool ComputeVarianceVectorP(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;
    static bool ComputeVarianceVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation) ;

    static bool ComputeWavePassageEffectVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, cx_vec &cValVector, QStringList &strInformation);
    static bool ComputeWavePassageEffectVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, cx_vec &cValVector, QStringList &strInformation);
    static bool ComputeWavePassageEffectMatrixPP(const CRPSWindLabsimuData &Data, cx_mat &cMatrix, QStringList &strInformation);
    static bool ComputeWavePassageEffectValue(const CRPSWindLabsimuData &Data, double &dRValue, double &dIValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation);

};

#endif
