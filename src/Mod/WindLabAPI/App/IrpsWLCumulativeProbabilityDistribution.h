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

#ifndef IRPSWLCPD_H
#define IRPSWLCPD_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureCumulativeProbabilityDistribution.h>

namespace WindLabAPI {

/**
 * @class IrpsWLCumulativeProbabilityDistribution
 * @brief An abstract class representing a cumulative probability distribution.
 *
 * This is a pure virtual class (interface) that defines the interface for all cumulative probability distributions.
 * A cumulative probability distribution provides a quantitative measure of the likelihood that 
 * the random phenomenon will fall below a certain threshold, helping to translate the stochastic nature of phenomenon 
 * into usable data for simulations. The cumulative probability distribution is used to describe the 
 * cumulative probability of the phenomenon value occurring within a specified range, offering valuable insights into the 
 * phenomenon behavior and enabling the generation of realistic phenomenon time series. 
 * Derived classes must implement all its methods. 
 */
class IrpsWLCumulativeProbabilityDistribution : public WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution
{
public:

    /**
     * @brief Virtual destructor for IrpsWLCumulativeProbabilityDistribution class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLCumulativeProbabilityDistribution() {};

    /** Compute the cumulative probability distribution value for x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param x            a value for with the cumulative probability distribution is computed
     * @param dValue       a value to be updated. This is the computed value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeCPDValue(const WindLabSimulationData& Data, const double& x, double& dValue) = 0;

    /** Compute the cumulative probability distribution for all increments of variable x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dVarVector   a vector to be updated. It should contains all the variable x increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each variable x increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeCPDVectorX(const WindLabSimulationData &Data,  vec &dVarVector, vec &dValVector) = 0;

     /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLCPD_H
