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

#ifndef IRPSWLFREQUENCYDISTRIBUTION_H
#define IRPSWLFREQUENCYDISTRIBUTION_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureFrequencyDistribution.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLFrequencyDistribution
 * @brief An abstract class representing a frequency distribution.
 *
 * This is a pure virtual class (interface) that defines the interface for all correlation functions.
 * A frequency discretization involves breaking down the continuous frequency domain, into discrete frequency bins. 
 * Derived classes must implement all its methods. 
 */
class IrpsWLFrequencyDistribution : public WindLabAPI::WindLabFeatureFrequencyDistribution
{
public:

    /**
     * @brief Virtual destructor for IrpsWLFrequencyDistribution class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLFrequencyDistribution() {};

    /** Compute the frequency increment value by frequency index for given location (simulation point).
     * @param Data             the simulation data containing all the simulation parameters input by the user.
     * @param location         a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param frequencyIndex   an integer representing the frequency index where the value will be computed.
     * @param dValue           a value to be updated. This is the computed frequency value.
     * @return                 return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeFrequencyValue(const WindLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue) = 0;

    /** Compute the frequency increments for all frequency indexes.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each frequency index.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeFrequenciesVectorF(const WindLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector) = 0;
  
    /** Compute the frequency matrix for all frequency indexes and locations.
     * @param Data       the simulation data containing all the simulation parameters input by the user..
     * @param dMatrix    a matrix to be updated. It should contain the computed frequency matrix.
     * @return           return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeFrequenciesMatrixFP(const WindLabSimulationData &Data, mat &dMatrix) = 0;

    /** Allows to do any initial taks before any of the other methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

	};

} //namespace WindLabAPI

#endif  // IRPSWLFREQUENCYDISTRIBUTION_H
