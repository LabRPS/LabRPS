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

#ifndef IRPSWLTURBULENCEINTENSITY_H
#define IRPSWLTURBULENCEINTENSITY_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureTurbulenceIntensity.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLTurbulenceIntensity
 * @brief An abstract class representing a turbulence intensity.
 *
 * This is a pure virtual class (interface) that defines the interface for all turbulence intensities.
 * Turbulence intensity is a measure of the fluctuations in wind speed relative to the mean wind speed 
 * and is an essential factor in representing the complex, highly variable nature of wind, particularly at 
 * local scales. Turbulence, which consists of chaotic and irregular fluctuations in wind velocity, has 
 * significant implications for the design of structures, the operation of wind turbines, and the 
 * prediction of environmental conditions.   
 * Derived classes must implement all its methods. 
 */
class IrpsWLTurbulenceIntensity : public WindLabAPI::WindLabFeatureTurbulenceIntensity
{
public:

    /**
     * @brief Virtual destructor for IrpsWLTurbulenceIntensity class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLTurbulenceIntensity() {};

    /** Compute the turbulence intensity value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the turbulence intensity value will be computed.
     * @param dValue       a value to be updated. This is the computed turbulence intensity value.
     * @return             return true if the computation is successful and false in case of failure.
     */	    
    virtual bool ComputeTurbulenceIntensityValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    /** Compute the turbulence intensity at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the turbulence intensity value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeTurbulenceIntensityVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the turbulence intensity at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeTurbulenceIntensityVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLTURBULENCEINTENSITY_H
