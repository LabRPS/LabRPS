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

#ifndef IRPSWLPDF_H
#define IRPSWLPDF_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureProbabilityDensityFunction.h>

namespace WindLabAPI {

/**
 * @class IrpsWLProbabilityDensityFunction
 * @brief An abstract class representing a peak factor.
 *
 * This is a pure virtual class (interface) that defines the interface for probability dendity function.
 * The PDF is central to modeling the inherent randomness of the phenomenon, ensuring that simulations 
 * reflect both the expected and extreme behaviors of the phenomenon. A Probability Density Function 
 * describes the likelihood of a random variable (in this case, wind velocity) assuming a particular 
 * value within a given range. 
 * Derived classes must implement all its methods. 
 */
class IrpsWLProbabilityDensityFunction : public WindLabAPI::WindLabFeatureProbabilityDensityFunction
{
public:

    /**
     * @brief Virtual destructor for IrpsWLProbabilityDensityFunction class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLProbabilityDensityFunction() {};

    /** Compute the probability dendity value for x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param x            a value for with the probability dendity is computed
     * @param dValue       a value to be updated. This is the computed value.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputePDFValue(const WindLabSimuData &Data, const double &x, double &dValue) = 0;

    /** Compute the probability dendity for all increments of variable x.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dVarVector   a vector to be updated. It should contains all the variable x increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each variable x increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputePDFVectorX(const WindLabSimuData &Data, vec &dVarVector, vec &dValVector) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLPDF_H
