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

#ifndef IRPSWLPEAKFACTOR_H
#define IRPSWLPEAKFACTOR_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeaturePeakFactor.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

/**
 * @class IrpsWLPeakFactor
 * @brief An abstract class representing a peak factor.
 *
 * This is a pure virtual class (interface) that defines the interface for peak factors.
 * The peak factor is defined as the ratio of the maximum wind velocity (or gust) observed over 
 * a specific time interval to the root mean square (RMS) value, or sometimes the mean value, 
 * of the wind speed over the same period. It provides a measure of how much more intense the 
 * peaks in the wind velocity are compared to the typical values. In other words, 
 * it quantifies the “spikiness” or extremity of wind gusts in relation to the background wind speed. 
 * Derived classes must implement all its methods. 
 */
class IrpsWLPeakFactor : public WindLabAPI::WindLabFeaturePeakFactor
{
public:

    /**
     * @brief Virtual destructor for IrpsWLPeakFactor class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLPeakFactor() {};

    /** Compute the peak factor value for given time and location.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dTime        the time instant at which the peak factor value will be computed.
     * @param dValue       a value to be updated. This is the computed peak factor value.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    virtual bool ComputePeakFactorValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    /** Compute the peak factor at a given time instant and for all locations (simulation points).
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dTime        the time instant at which the peak factor value will be computed.
     * @param dVarVector   a vector to be updated. It should contains all the location numbers used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each location stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputePeakFactorVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    /** Compute the peak factor at a given location (simulation point) and for all time increments.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param location     a location (simulation point represented by 3D position vector) where wind velocity time series is desired.
     * @param dVarVector   a vector to be updated. It should contains all the time increments used to compute each value stored in dValVector.
     * @param dValVector   a vector to be updated. It should contain all the values computed for each time increment stored in dVarVector.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool ComputePeakFactorVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLPEAKFACTOR_H
