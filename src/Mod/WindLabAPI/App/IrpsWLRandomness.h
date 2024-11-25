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

#ifndef IRPSWLRANDOMNESS_H
#define IRPSWLRANDOMNESS_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureRandomness.h>

namespace WindLabAPI {

/**
 * @class IrpsWLRandomness
 * @brief An abstract class representing a randomness provider.
 *
 * This is a pure virtual class (interface) that defines the interface for randomness providers.
 * Random phenomenon exhibits random and fluctuating behavior that needs to be accurately represented 
 * in simulations to capture both long-term trends and short-term fluctuations. One of the key elements 
 * in the simulation process is the incorporation of random phases in the construction of the phenomenon. 
 * Derived classes must implement all its methods. 
 */
class IrpsWLRandomness : public WindLabAPI::WindLabFeatureRandomness
{
public:

    /**
     * @brief Virtual destructor for IrpsWLRandomness class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLRandomness() {};

    /** Generate a random value.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dValue       a value to be updated. This is the generated random value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeRandomValue(const WindLabSimulationData &Data, double &dValue) = 0;

    /** Generate the random value matrix for all frequency increments and locations.
     * @param Data       the simulation data containing all the simulation parameters input by the user..
     * @param dMatrix    a matrix to be updated. It should contain the generated random values matrix.
     * @return           return true if the computation is successful and false in case of failure.
     */
    virtual bool GenerateRandomMatrixFP(const WindLabSimulationData &Data, mat &dRandomValueArray) = 0;

    /** Allows to do any initial taks before any of the other methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLRANDOMNESS_H
