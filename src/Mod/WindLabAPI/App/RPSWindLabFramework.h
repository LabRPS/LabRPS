/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef RPSWINDLABFRAMEWORK_H
#define RPSWINDLABFRAMEWORK_H

#include "RPSWindLabAPIdefines.h"
#include <Mod/WindLabAPI/App/WindLabSimulationData.h>
#include <Mod/WindLabAPI/App/WindLabFeatureDescription.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class CRPSWindLabFramework
 * @brief A helper class to call methods from any active WindLab Features.
 *
 * This class allow the developer to call methods from any active feature in just a single line.
 */
class RPS_CORE_API CRPSWindLabFramework
{
public:

    /// construction
	CRPSWindLabFramework();

    /// destruction
	~CRPSWindLabFramework();

    /** Compute the cross coherence between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the coherence vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossCoherenceVectorF(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross coherence between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the coherence vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossCoherenceVectorT(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross coherence matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the coherence matrix will be computed.
     * @param dTime             the time instant at which the coherence matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed coherence matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossCoherenceMatrixPP(const WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

    /** Compute the cross coherence value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the coherence value will be computed.
     * @param dTime        the time instant at which the coherence value will be computed.
     * @param dValue       a value to be updated. This is the computed coherence value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossCoherenceValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    /** Compute the cross correlation value for given time and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the correlation value will be computed.
     * @param dValue       a value to be updated. This is the computed correlation value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeCrossCorrelationValue(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue);
	
    /** Compute the cross correlation between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossCorrelationVectorT(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector);

    /** Compute the cross correlation matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dTime             the time instant at which the correlation matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed correlation matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossCorrelationMatrixPP(const WindLabSimulationData &Data, const double &dTime, mat &dCorrelationMatrix);

    /** Compute the cumulative probability distribution value for x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param x            a value for with the cumulative probability distribution is computed
     * @param dValue       a value to be updated. This is the computed value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCPDValue(const WindLabSimulationData& Data, const double& x, double& dValue);

    /** Compute the cumulative probability distribution for all increments of variable x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dVarVector   a vector to be updated. It should contains all the variable x increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each variable x increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCPDVectorX(const WindLabSimulationData &Data,  vec &dVarVector, vec &dValVector);

    /** Compute the frequency increment value by frequency index for given location (simulation point).
     * @param Data             the simulation data containing all the simulation parameters input by the user.
     * @param location         a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param frequencyIndex   an integer representing the frequency index where the value will be computed.
     * @param dValue           a value to be updated. This is the computed frequency value.
     * @return                 return true if the computation is successful and false in case of failure.
     */
    static bool ComputeFrequencyValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue);

    /** Compute the frequency increments for all frequency indexes.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency index.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeFrequenciesVectorF(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector);
  
    /** Compute the frequency matrix for all frequency indexes and locations.
     * @param Data       the simulation data containing all the simulation parameters input by the user..
     * @param dMatrix    a matrix to be updated. It should contain the computed frequency matrix.
     * @return           return true if the computation is successful and false in case of failure.
     */
    static bool ComputeFrequenciesMatrixFP(const WindLabSimulationData &Data, mat &dMatrix);

        /** Compute the gust factor value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the gust factor value will be computed.
     * @param dValue       a value to be updated. This is the computed gust factor value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeGustFactorValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the gust factors at a given time and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the gust factor value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeGustFactorVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the gust factors at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeGustFactorVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the kurtosis value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the kurtosis value will be computed.
     * @param dValue       a value to be updated. This is the computed kurtosis value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeKurtosisValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the kurtosis at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the kurtosis value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeKurtosisVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the kurtosis at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeKurtosisVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the location coordinates according to their distribution in space.
     * @param Data       the simulation data containing all the simulation parameters input by the user..
     * @param dLocCoord  a matrix to be updated. It should contain the computed location coordinates.
     * @return           return true if the computation is successful and false in case of failure.
     */
    static bool ComputeLocationCoordinateMatrixP3(const WindLabSimulationData& Data, mat& dLocCoord);

    /** Compute the kurtosis at a given location (simulation point) and for all time increments.
     * @param Data           the simulation data containing all the simulation parameters input by the user.
     * @param inputMatrix    a matrix to be updated. This the matrix to be manipulated, analyzed and processed.
     * @param outputMatrix   a matrix to be updated. This is the result matrix.
     * @return               return true if the computation is successful and false in case of failure.
     */
    static bool MatrixToolCompute(const WindLabSimulationData &Data, const mat &inputMatrix, mat &outputMatrix);

    /** Compute the mean wind speed value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the mean wind speed value will be computed.
     * @param dValue       a value to be updated. This is the computed mean wind speed value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeMeanWindSpeedValue(const WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);

    /** Compute the mean wind speed at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the mean wind speed value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeMeanWindSpeedVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the mean wind speed at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeMeanWindSpeedVectorT(const WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    /** Compute the modulation value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the modulation value will be computed.
     * @param dValue       a value to be updated. This is the computed modulation value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeModulationValue(const WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);

    /** Compute the modulation at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the modulation value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeModulationVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the modulation at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeModulationVectorT(const WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    /** Compute the peak factor value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the peak factor value will be computed.
     * @param dValue       a value to be updated. This is the computed peak factor value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputePeakFactorValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the peak factor at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the peak factor value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputePeakFactorVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the peak factor at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputePeakFactorVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the probability dendity value for x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param x            a value for with the probability dendity is computed
     * @param dValue       a value to be updated. This is the computed value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputePDFValue(const WindLabSimulationData &Data, const double &x, double &dValue);

    /** Compute the probability dendity for all increments of variable x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dVarVector   a vector to be updated. It should contains all the variable x increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each variable x increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputePDFVectorX(const WindLabSimulationData &Data, vec &dVarVector, vec &dValVector);

    /** Compute the decomposed spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the decomposed spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    /** Compute the decomposed spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the decomposed spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    /** Compute the decomposed spectrum matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the decomposed spectrum matrix will be computed.
     * @param dTime             the time instant at which the decomposed spectrum matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed decomposed spectrum matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix);

    /** Generate a random value.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dValue       a value to be updated. This is the generated random value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeRandomValue(const WindLabSimulationData &Data, double &dValue);

    /** Generate the random value matrix for all frequency increments and locations.
     * @param Data       the simulation data containing all the simulation parameters input by the user..
     * @param dMatrix    a matrix to be updated. It should contain the generated random values matrix.
     * @return           return true if the computation is successful and false in case of failure.
     */
    static bool GenerateRandomMatrixFP(const WindLabSimulationData &Data, mat &dRandomValueArray);

    /** Compute the roughness value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the roughness value will be computed.
     * @param dValue       a value to be updated. This is the computed roughness value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeRoughnessValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the roughness values at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the roughness value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeRoughnessVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the roughness value at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeRoughnessVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the shear velocity value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the shear velocity value will be computed.
     * @param dValue       a value to be updated. This is the computed shear velocity value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeShearVelocityOfFlowValue(const WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, double &dValue);

    /** Compute the shear velocity at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the shear velocity value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeShearVelocityOfFlowVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the shear velocity at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeShearVelocityOfFlowVectorT(const WindLabSimulationData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    /** Generate random wind velocity.
     * @param Data             the simulation data containing all the simulation parameters input by the user.
     * @param dVelocityArray   a matrix to be updated. This is generated random wind velocity matrix. 
     * Its first column contains the time increments.
     * @return                 return true if the computation is successful and false in case of failure.
     */		
    static bool Simulate(const WindLabSimulationData &Data, mat &dVelocityArray);

    /** Generate random wind velocity in large scale simulation mode.
     * @param Data           the simulation data containing all the simulation parameters input by the user.
     * @param strFileName    In large scale mode, the generated wind velocity is not save in memory. It should 
     * be written to computer disc to avoid memory usage overflow. This is the name of the file in which the 
     * generated wind speed values will be written. You can get the working directory that from the simulation 
     * Data in order to create the full path of the file.
     * @return                 return true if the computation is successful and false in case of failure.
     */	
    static bool SimulateInLargeScaleMode(const WindLabSimulationData &Data, QString &strFileName);

    /** Compute the skewness value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the skewness value will be computed.
     * @param dValue       a value to be updated. This is the computed skewness value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeSkewnessValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the skewness values at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the skewness value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeSkewnessVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the skewness values at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeSkewnessVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the standard deviation value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the standard deviation value will be computed.
     * @param dValue       a value to be updated. This is the computed standard deviation value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeStandardDeviationValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the standard deviation values at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the standard deviation value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeStandardDeviationVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the standard deviation values at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeStandardDeviationVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the kurtosis at a given location (simulation point) and for all time increments.
     * @param Data           the simulation data containing all the simulation parameters input by the user.
     * @param inputMatrix    a matrix to be updated. This the table to be manipulated, analyzed and processed.
     * @param outputMatrix   a matrix to be updated. This is the result table.
     * @return               return true if the computation is successful and false in case of failure.
     */
    static bool TableToolCompute(const WindLabSimulationData &Data, const mat &inputTable, mat &outputTable);

    /** Compute the turbulence intensity value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the turbulence intensity value will be computed.
     * @param dValue       a value to be updated. This is the computed turbulence intensity value.
     * @return             return true if the computation is successful and false in case of failure.
     */	    
    static bool ComputeTurbulenceIntensityValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the turbulence intensity at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the turbulence intensity value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeTurbulenceIntensityVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the turbulence intensity at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeTurbulenceIntensityVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the turbulence scale value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the turbulence scale value will be computed.
     * @param dValue       a value to be updated. This is the computed turbulence scale value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeTurbulenceScaleValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the turbulence scale at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the turbulence scale value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeTurbulenceScaleVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the turbulence scale at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeTurbulenceScaleVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Run the user defined computation tool.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dresult      a matrix to be updated. This is the computation result.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool UserDefinedRPSObjectCompute(const WindLabSimulationData &Data, mat &dresult);

    /** Compute the variance value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the variance value will be computed.
     * @param dValue       a value to be updated. This is the computed variance value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    static bool ComputeVarianceValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue);

    /** Compute the variance at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the variance value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeVarianceVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the variance at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeVarianceVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector);

    /** Compute the wave passage effect between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the wave passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeWavePassageEffectVectorF(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    /** Compute the wave passage effect between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the wave passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeWavePassageEffectVectorT(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    /** Compute the wave passage effect matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the wave passage effect matrix will be computed.
     * @param dTime             the time instant at which the wave passage effect matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed wave passage effect matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeWavePassageEffectMatrixPP(const WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

    /** Compute the wave passage effect value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the wave passage effect value will be computed.
     * @param dTime        the time instant at which the wave passage effect value will be computed.
     * @param dValue       a value to be updated. This is the computed wave passage effect value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeWavePassageEffectValue(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    /** Compute the cross spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    /** Compute the cross spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the spectrum matrix will be computed.
     * @param dTime             the time instant at which the spectrum matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed spectrum matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    /** Compute the auto spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
        /** Compute the auto spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    /** Compute the cross spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    /** Compute the cross spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the spectrum matrix will be computed.
     * @param dTime             the time instant at which the spectrum matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed spectrum matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    /** Compute the auto spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);

        /** Compute the auto spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */    
    static bool ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    /** Compute the cross spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    /** Compute the cross spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the spectrum matrix will be computed.
     * @param dTime             the time instant at which the spectrum matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed spectrum matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    /** Compute the auto spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);

    /** Compute the auto spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    /** Compute the spectrum value for given time, frequency and locations according to the selected wind direction.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    /** Compute the cross spectrum between two simulation points for all frequency increments according to the selected wind direction.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments according to the selected wind direction.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    /** Compute the cross spectrum matrix for given time and frequency according to the selected wind direction.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the spectrum matrix will be computed.
     * @param dTime             the time instant at which the spectrum matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed spectrum matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    static bool ComputeCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    /** Compute the auto spectrum value for given time, frequency and locations according to the selected wind direction.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);

    /** Compute the auto spectrum between two simulation points for all frequency increments according to the selected wind direction.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    /** Compute the cross spectrum between two simulation points for all time increments according to the selected wind direction.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    static bool ComputeAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    /** Given a location coordinates, this function identify the index (numbering) of the location (simulation point) among all the simulation points (locations).
     * @param Data                  the simulation data containing all the simulation parameters input by the user.
     * @param locationTobeFound     a location (simulation point represented by 3D position vector) whose index is needed.
     * @return                      return the successfuly found index. In case of failure, it returns negative integer.
     */
    static int getLocationIndex(const WindLabAPI::WindLabSimulationData &Data, Base::Vector3d locationTobeFound);

     /** Get the description of a feature by its name
     * @param name     the feature's name.
     * @return         return the feature description.
     */
    static WindLabAPI::WindLabFeatureDescription* getWindLabFeatureDescription(const std::string& name);

     /** Get the current date time
     * @return         return current date and time.
     */
    static std::string getCurrentDateTime();
    
};

} //namespace WindLabAPI

#endif
