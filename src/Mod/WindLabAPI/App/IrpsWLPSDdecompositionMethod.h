/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>         *
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

#ifndef IRPSWLPSDDECOMPOSITIONMETHOD_H
#define IRPSWLPSDDECOMPOSITIONMETHOD_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeaturePSDDecompositionMethod.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLPSDdecompositionMethod
 * @brief An abstract class representing a power spectrum density decomposition method.
 *
 * This is a pure virtual class (interface) that defines the interface for power spectrum density decomposition methods.
 * To simulate seismic events accurately, it is essential for certain simulation algorithms to perform Power Spectral 
 * Density (PSD) decomposition. Decomposing the PSD into orthogonal components or factorizing it using methods such 
 * as Cholesky Decomposition is a crucial step in those simulation algorithms. In fact, this class is to allow all the community
 * to develop more efficient and optimized algorithms for the Cholesky decomposition usually involved in the specral representation method.
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
class IrpsWLPSDdecompositionMethod : public WindLabAPI::WindLabFeaturePSDDecompositionMethod
{
public:

    /**
     * @brief Virtual destructor for IrpsWLPSDdecompositionMethod class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLPSDdecompositionMethod() {};

    /** Compute the decomposed spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the decomposed spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    /** Compute the decomposed spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the decomposed spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    /** Compute the decomposed spectrum matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the decomposed spectrum matrix will be computed.
     * @param dTime             the time instant at which the decomposed spectrum matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed decomposed spectrum matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLPSDDECOMPOSITIONMETHOD_H
