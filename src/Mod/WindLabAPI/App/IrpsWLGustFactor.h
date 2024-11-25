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

#ifndef IRPSWLGUSTFACTOR_H
#define IRPSWLGUSTFACTOR_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureGustFactor.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLGustFactor
 * @brief An abstract class representing a gust factor.
 *
 * This is a pure virtual class (interface) that defines the interface for all gust factors.
 * The gust factor quantifies the ratio of the peak wind speed (or maximum instantaneous wind velocity) 
 * to the mean wind speed over a specified time period. It is particularly important for applications where 
 * short-term wind extremes need to be modeled, such as in the design of wind-sensitive structures (e.g., buildings, 
 * bridges, wind turbines) and in the wind energy industry, where understanding peak gusts is crucial for turbine 
 * load analysis and fatigue modeling.  
 * Derived classes must implement all its methods. 
 */
class IrpsWLGustFactor : public WindLabAPI::WindLabFeatureGustFactor
{
public:

    /**
     * @brief Virtual destructor for IrpsWLGustFactor class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLGustFactor() {};

    /** Compute the gust factor value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the gust factor value will be computed.
     * @param dValue       a value to be updated. This is the computed gust factor value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    virtual bool ComputeGustFactorValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    /** Compute the gust factors at a given time and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the gust factor value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeGustFactorVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the gust factors at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeGustFactorVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

     /** Allows to do any initial taks before any of the other methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLGUSTFACTOR_H
