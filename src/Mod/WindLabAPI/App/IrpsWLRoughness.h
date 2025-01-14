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

#ifndef IRPSWLROUGHNESS_H
#define IRPSWLROUGHNESS_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureRoughness.h>

namespace WindLabAPI {

/**
 * @class IrpsWLRoughness
 * @brief An abstract class representing a terrain rounghness.
 *
 * This is a pure virtual class (interface) that defines the interface for all terrain roughnesses.
 * Terrain roughness influences wind velocity by altering wind speed, direction, and turbulence as 
 * it interacts with obstacles such as buildings, vegetation, hills, and other surface features. 
 * Understanding and incorporating the effects of terrain roughness in wind velocity simulations 
 * is crucial for ensuring realistic and reliable results in these applications. Terrain roughness 
 * is a measure of the heterogeneity of the Earth's surface that disrupts the smooth flow of wind. 
 * Rougher terrain typically includes obstacles such as forests, mountains, urban areas, or rugged 
 * landscapes, which cause more significant turbulence and frictional forces on the wind. 
 * Derived classes must implement all its methods. 
 */
class IrpsWLRoughness : public WindLabAPI::WindLabFeatureRoughness
{
public:

    /**
     * @brief Virtual destructor for IrpsWLRoughness class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLRoughness() {};

    /** Compute the roughness value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the roughness value will be computed.
     * @param dValue       a value to be updated. This is the computed roughness value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    virtual bool ComputeRoughnessValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    /** Compute the roughness values at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the roughness value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeRoughnessVectorP(const WindLabSimulationData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the roughness value at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeRoughnessVectorT(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    /** Allows to do any initial taks before any of the other methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLROUGHNESS_H
