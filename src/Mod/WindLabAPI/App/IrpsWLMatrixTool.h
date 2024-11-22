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

#ifndef IRPSWLMATRIXTOOL_H
#define IRPSWLMATRIXTOOL_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureMatrixTool.h>

namespace WindLabAPI {

/**
 * @class IrpsWLMatrixTool
 * @brief An abstract class representing a matrix tool.
 *
 * This is a pure virtual class (interface) that defines the interface for all matrix tools.
 * A matrix tool is a feature (tool) for manipulation data presentated in the form of Alphaplot matrix.  
 * The WindLab framework run this tool on the active alphaplot matrix. Without have an active alphaplot matrix as the active window, 
 * the user will not have access to the command that run this tool. Note that, internally the alphaplot matrix is first 
 * converted into Eigen matrix and is passed to this tool. If you call this tool directly from your code, you don't any alphaplot matrix to be active.   
 * Derived classes must implement all its methods. 
 */
class IrpsWLMatrixTool : public WindLabAPI::WindLabFeatureMatrixTool
{
public:

    /**
     * @brief Virtual destructor for IrpsWLMatrixTool class.
     * Provides proper cleanup in case a derived class object is destroyed.
     */
    virtual ~IrpsWLMatrixTool() {};

    /** Compute the kurtosis at a given location (simulation point) and for all time increments.
     * @param Data           the simulation data containing all the simulation parameters input by the user.
     * @param inputMatrix    a matrix to be updated. This the matrix to be manipulated, analyzed and processed.
     * @param outputMatrix   a matrix to be updated. This is the result matrix.
     * @return               return true if the computation is successful and false in case of failure.
     */
    virtual bool MatrixToolCompute(const WindLabSimuData &Data, const mat &inputMatrix, mat &outputMatrix) = 0;

    /** Allows to do any initial taks before any of the above methods is called.
     * @param Data         the simulation data containing all the simulation parameters input by the user.
     * @return             return true if the computation is successful and false in case of failure.
     */
	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;
};

} //namespace WindLabAPI

#endif  // IRPSWLMATRIXTOOL_H
