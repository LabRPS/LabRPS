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

#ifndef IRPSWLZSPECTRUM_H
#define IRPSWLZSPECTRUM_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureZSpectrum.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLZSpectrum
 * @brief An abstract class representing an vertical wind spectrum.
 *
 * This is a pure virtual class (interface) that defines the interface for all vertical wind spectrums.
 * The vertical wind component represents the wind velocity in the direction perpendicular to the ground, 
 * at a given position x in the horizontal plane and height 𝑧 above the surface. This component is often less 
 * intuitive than the horizontal components (along-wind and across-wind) but plays a vital role in characterizing 
 * the turbulent structure of wind fields, particularly in the context of boundary layer flows, atmospheric stability, 
 * and interaction with obstacles.      
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
class IrpsWLZSpectrum : public WindLabAPI::WindLabFeatureZSpectrum
{
public:

    /**
     * @brief Virtual destructor for IrpsWLZSpectrum class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLZSpectrum() {};

    /** Compute the cross spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue) = 0;

    /** Compute the cross spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    /** Compute the cross spectrum matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency        the frequency value for which the spectrum matrix will be computed.
     * @param dTime             the time instant at which the spectrum matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed spectrum matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix) = 0;

    /** Compute the auto spectrum value for given time, frequency and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum value will be computed.
     * @param dTime        the time instant at which the spectrum value will be computed.
     * @param dValue       a value to be updated. This is the computed spectrum value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue) = 0;

    /** Compute the auto spectrum between two simulation points for all frequency increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the spectrum passage effect vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the frequency increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the cross spectrum between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frequency value for which the spectrum vector will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLZSPECTRUM_H
