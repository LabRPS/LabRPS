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

#ifndef IRPSWLWAVEPASSAGEEFFECT_H
#define IRPSWLWAVEPASSAGEEFFECT_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureWavePassageEffect.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLWavePassageEffect
 * @brief An abstract class representing a wave passage effect.
 *
 * This is a pure virtual class (interface) that defines the interface for all wave passage effects.
 * The wave passage effect is often seen in the simulation of phenomena that have spatial and temporal 
 * correlations, where the observed values of a random process at a given location or time depend on 
 * previous values in a way that mimics the behavior of propagating waves.     
 * Derived classes must implement all its methods. During the implementation of this interface you have 
 * to consider stationarity depending on how your feature varies in time to capture these three situation that
 * may come from the user's inputs (requirements):
 * 
 * 1-The user is willing to simulate stationary wind velocity. f = f(w)
 * 
 * 2-The user is willing to simulate non-stationary wind velocity and has also created a modulation 
 * function in the simulation. f = f(w,t) = G(w) * M(t)
 * 
 * 3-The user is willing to simulate non-stationary wind velocity without creating any
 * modulation function in the simulation. f = f(w,t) 
 */
class IrpsWLWavePassageEffect : public WindLabAPI::WindLabFeatureWavePassageEffect
{
public:

    /**
     * @brief Virtual destructor for IrpsWLWavePassageEffect class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLWavePassageEffect() {};

    /** Compute the wave passage effect between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the wave passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeWavePassageEffectVectorF(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    /** Compute the wave passage effect between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the wave passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeWavePassageEffectVectorT(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    /** Compute the wave passage effect matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the wave passage effect matrix will be computed.
     * @param dTime             the time instant at which the wave passage effect matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed wave passage effect matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeWavePassageEffectMatrixPP(const WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix) = 0;

    /** Compute the wave passage effect value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the wave passage effect value will be computed.
     * @param dTime        the time instant at which the wave passage effect value will be computed.
     * @param dValue       a value to be updated. This is the computed wave passage effect value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeWavePassageEffectValue(const WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue) = 0;

    /** Allows to do any initial taks before any of the other methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLWAVEPASSAGEEFFECT_H
