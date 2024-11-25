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

#ifndef IRPSWLLOCATIONDISTRIBUTION_H
#define IRPSWLLOCATIONDISTRIBUTION_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureLocationDistribution.h>

namespace WindLabAPI {

/**
 * @class IrpsWLLocationDistribution
 * @brief An abstract class representing a location distribution.
 *
 * This is a pure virtual class (interface) that defines the interface for all location distributions.
 * Wind velocity is sampled at multiple points in space to generate a spatial wind field that reflects 
 * both the horizontal variability (such as wind direction changes over a region) and the vertical profile 
 * (wind speed changes with height). The spatial distribution of simulation points is typically achieved by 
 * discretizing the terrain into a grid or set of measurement locations, ensuring that spatial correlation 
 * between nearby points is accounted for.  
 * Derived classes must implement all its methods. 
 */
class IrpsWLLocationDistribution: public WindLabAPI::WindLabFeatureLocationDistribution
{

public:

    /**
     * @brief Virtual destructor for IrpsWLLocationDistribution class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLLocationDistribution() {};

    /** Compute the location coordinates according to their distribution in space.
     * @param Data       the simulation data containing all the simulation parameters input by the user..
     * @param dLocCoord  a matrix to be updated. It should contain the computed location coordinates.
     * @return           return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeLocationCoordinateMatrixP3(const WindLabSimulationData& Data, mat& dLocCoord) = 0;

    /** Allows to do any initial taks before any of the other methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData& Data) = 0;
};

} // namespace WindLabAPI

#endif  // IRPSWLLOCATIONDISTRIBUTION_H
