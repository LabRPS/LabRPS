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

#ifndef IRPSWLSIMUMETHOD_H
#define IRPSWLSIMUMETHOD_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureSimulationMethod.h>

namespace WindLabAPI {

/**
 * @class IrpsWLSimuMethod
 * @brief An abstract class representing a simulation method.
 *
 * This is a pure virtual class (interface) that defines the interface for all simulation methods.
 * Simulation methods refer to simulation algorithms which provide powerful tools for modeling complex 
 * systems that involve uncertainty, randomness, or fluctuating behavior, allowing researchers, engineers, 
 * and analysts to study and predict the behavior of these systems in a computationally efficient manner. 
 * Various simulations methods can be found in LabRPS for the simulation of various random phenomena. 
 * Derived classes must implement all its methods.  During the implementation of this interface you have 
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
class IrpsWLSimuMethod : public WindLabAPI::WindLabFeatureSimulationMethod
{
public:

    /**
     * @brief Virtual destructor for IrpsWLSimuMethod class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLSimuMethod() {};

    /** Generate random wind velocity.
     * @param Data             the simulation data containing all the simulation parameters input by the user.
     * @param dVelocityArray   a matrix to be updated. This is generated random wind velocity matrix. 
     * Its first column contains the time increments.
     * @return                 return true if the computation is successful and false in case of failure.
     */		
    virtual bool Simulate(const WindLabSimuData &Data, mat &dVelocityArray) = 0;

    /** Generate random wind velocity in large scale simulation mode.
     * @param Data           the simulation data containing all the simulation parameters input by the user.
     * @param strFileName    In large scale mode, the generated wind velocity is not save in memory. It should 
     * be written to computer disc to avoid memory usage overflow. This is the name of the file in which the 
     * generated wind speed values will be written. You can get the working directory that from the simulation 
     * Data in order to create the full path of the file.
     * @return                 return true if the computation is successful and false in case of failure.
     */	
    virtual bool SimulateInLargeScaleMode(const WindLabSimuData &Data, QString &strFileName) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};


} //namespace WindLabAPI


#endif  // IRPSWLSIMUMETHOD_H
