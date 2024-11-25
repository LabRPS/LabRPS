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

#ifndef IRPSWLUSERDEFINEDRPSOBJECT_H
#define IRPSWLUSERDEFINEDRPSOBJECT_H

#include "WindLabSimulationData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureUserDefinedRPSObject.h>

namespace WindLabAPI {

/**
 * @class IrpsWLUserDefinedRPSObject
 * @brief An abstract class representing a user defined object.
 *
 * This is a pure virtual class (interface) that defines the interface for all user defined objects.
 * This class allow to develop any kind of tool for the simulation of random wind velocity.   
 * Derived classes must implement all its methods. 
 */
class IrpsWLUserDefinedRPSObject : public WindLabAPI::WindLabFeatureUserDefinedRPSObject
{
public:

    /**
     * @brief Virtual destructor for IrpsWLUserDefinedRPSObject class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLUserDefinedRPSObject() {};

    /** Run the user defined computation tool.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @param dresult      a matrix to be updated. This is the computation result.
     * @return             return true if the computation is successful and false in case of failure.
     */	
    virtual bool UserDefinedRPSObjectCompute(const WindLabSimulationData &Data, mat &dresult) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimulationData &Data) = 0;
};

} //namespace WindLabAPI


#endif  // IRPSWLUSERDEFINEDRPSOBJECT_H
