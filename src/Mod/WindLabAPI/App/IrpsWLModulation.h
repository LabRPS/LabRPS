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

#ifndef IRPSWLMODULATION_H
#define IRPSWLMODULATION_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureModulation.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLModulation
 * @brief An abstract class representing a modulation function.
 *
 * This is a pure virtual class (interface) that defines the interface for all modulation function.
 * Unlike stationary processes, where statistical properties (such as mean and variance) remain 
 * constant over time, non-stationary random phenomenon varies in its statistical behavior. A modulation 
 * function is a mathematical tool or algorithm used to adjust the statistical properties of a random process 
 * in a time-dependent manner. 
 * Derived classes must implement all its methods. 
 */
class IrpsWLModulation : public WindLabAPI::WindLabFeatureModulation
{
public:

    /**
     * @brief Virtual destructor for IrpsWLModulation class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLModulation() {};

    /** Compute the modulation value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frquency value for which the modulation value will be computed.
     * @param dTime        the time instant at which the modulation value will be computed.
     * @param dValue       a value to be updated. This is the computed modulation value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    virtual bool ComputeModulationValue(const WindLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue) = 0;

    /** Compute the modulation at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dFrequency   the frquency value for which the modulation value will be computed.
     * @param dTime        the time instant at which the modulation value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeModulationVectorP(const WindLabSimulationData &Data, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the modulation at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dFrequency   the frquency value for which the modulation value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeModulationVectorT(const WindLabSimulationData &Data, Base::Vector3d location, const double &dFrequency, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the modulation at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeModulationVectorF(const WindLabSimulationData &Data, Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector) = 0;
    /** Allows to do any initial taks before any of the other methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLMODULATION_H




