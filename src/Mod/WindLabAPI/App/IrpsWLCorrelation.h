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

#ifndef IRPSWLCORRELATION_H
#define IRPSWLCORRELATION_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureCorrelation.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLCorrelation
 * @brief An abstract class representing a correlation function.
 *
 * This is a pure virtual class (interface) that defines the interface for all correlation functions.
 * A correlation function is a fundamental tool in the simulation of random phenomenon, 
 * playing a key role in modeling the statistical dependencies between fluctuations at different 
 * points in space and time. Derived classes must implement all its methods. 
 */
class IrpsWLCorrelation : public WindLabAPI::WindLabFeatureCorrelation
{
public:

    /**
     * @brief Virtual destructor for IrpsWLCorrelation class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLCorrelation() {};

    /** Compute the cross correlation value for given time and locations.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the correlation value will be computed.
     * @param dValue       a value to be updated. This is the computed correlation value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    virtual bool ComputeCrossCorrelationValue(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue) = 0;
	
    /** Compute the cross correlation between two simulation points for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param locationJ    a location J (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param locationK    a location K (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeCrossCorrelationVectorT(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the cross correlation matrix for given time and frequency.
     * @param Data              the simulation data containing all the simulation parameters input by the user.
     * @param dTime             the time instant at which the correlation matrix will be computed.
     * @param dCoherenceMatrix  a matrix to be updated. It should contain the computed correlation matrix.
     * @return                  return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputeCrossCorrelationMatrixPP(const WindLabSimuData &Data, const double &dTime, mat &dCorrelationMatrix) = 0;
	
     /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */   
	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLCORRELATION_H
