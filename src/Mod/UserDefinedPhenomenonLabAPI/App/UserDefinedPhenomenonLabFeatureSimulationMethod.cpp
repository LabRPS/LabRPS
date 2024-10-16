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


#include "PreCompiled.h"

#ifndef _PreComp_
# include <sstream>
#endif

#include <Base/Console.h>
#include <Base/Exception.h>
#include "UserDefinedPhenomenonLabFeatureSimulationMethod.h"

using namespace UserDefinedPhenomenonLabAPI;

RPS_LOG_LEVEL_INIT("UserDefinedPhenomenonLabFeatureSimulationMethod",true,true)

PROPERTY_SOURCE(UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeatureSimulationMethod, UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature)


UserDefinedPhenomenonLabFeatureSimulationMethod::UserDefinedPhenomenonLabFeatureSimulationMethod(void)
{
}

UserDefinedPhenomenonLabFeatureSimulationMethod::~UserDefinedPhenomenonLabFeatureSimulationMethod()
{
}

short UserDefinedPhenomenonLabFeatureSimulationMethod::mustExecute(void) const
{
    return UserDefinedPhenomenonLabFeature::mustExecute();
}

App::DocumentObjectExecReturn * UserDefinedPhenomenonLabFeatureSimulationMethod::recompute(void)
{
    try {
        return UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature::recompute();
    }
    catch (Base::Exception& e) {

        App::DocumentObjectExecReturn* ret = new App::DocumentObjectExecReturn(e.what());
        if (ret->Why.empty()) ret->Why = "Unknown exception";
        return ret;
    }
}

App::DocumentObjectExecReturn * UserDefinedPhenomenonLabFeatureSimulationMethod::execute(void)
{
    return UserDefinedPhenomenonLabFeature::execute();
}

void UserDefinedPhenomenonLabFeatureSimulationMethod::onChanged(const App::Property* prop)
{

    UserDefinedPhenomenonLabFeature::onChanged(prop);
}