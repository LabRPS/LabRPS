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

#ifndef RPSUSERLABFRAMEWORK_H
#define RPSUSERLABFRAMEWORK_H

#include "RPSUserLabAPIdefines.h"
#include <Mod/UserLabAPI/App/UserLabSimulationData.h>
#include <Mod/UserLabAPI/App/UserLabFeatureDescription.h>
#include <Base/Vector3D.h>

namespace UserLabAPI {

/**
 * @class CRPSUserLabFramework
 * @brief A helper class to call methods from any active UserLab Features.
 *
 * This class allow the developer to call methods from any active feature in just a single line.
 */
class RPS_CORE_API CRPSUserLabFramework
{
public:

    /// construction
	CRPSUserLabFramework();

    /// destruction
	~CRPSUserLabFramework();

     /** Get the description of a feature by its name
     * @param name     the feature's name.
     * @return         return the feature description.
     */
    static UserLabAPI::UserLabFeatureDescription* getUserLabFeatureDescription(const std::string& name);

     /** Get the current date time
     * @return         return current date and time.
     */
    static std::string getCurrentDateTime();
    
};

} //namespace RPSUSERLABFRAMEWORK_H

#endif
