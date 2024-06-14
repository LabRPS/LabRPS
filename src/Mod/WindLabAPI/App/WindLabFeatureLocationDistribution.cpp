/***************************************************************************
 *   Copyright (c) 2024 the Team <theTeam@labrps.com>              *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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
#include "WindLabFeatureLocationDistribution.h"
//#include <Mod/WindLabAPI/App/WindLabFeatureLocationDistributionPy.h>

using namespace WindLabAPI;

RPS_LOG_LEVEL_INIT("WindLabFeatureLocationDistribution",true,true)

PROPERTY_SOURCE(WindLabAPI::WindLabFeatureLocationDistribution, WindLabAPI::WindLabFeature)


WindLabFeatureLocationDistribution::WindLabFeatureLocationDistribution(void)
{
}

WindLabFeatureLocationDistribution::~WindLabFeatureLocationDistribution()
{
}

short WindLabFeatureLocationDistribution::mustExecute(void) const
{
    return WindLabFeature::mustExecute();
}

App::DocumentObjectExecReturn * WindLabFeatureLocationDistribution::recompute(void)
{
    try {
        return WindLabAPI::WindLabFeature::recompute();
    }
    catch (Base::Exception& e) {

        App::DocumentObjectExecReturn* ret = new App::DocumentObjectExecReturn(e.what());
        if (ret->Why.empty()) ret->Why = "Unknown exception";
        return ret;
    }
}

App::DocumentObjectExecReturn * WindLabFeatureLocationDistribution::execute(void)
{
    return WindLabFeature::execute();
}

void WindLabFeatureLocationDistribution::onChanged(const App::Property* prop)
{

    WindLabFeature::onChanged(prop);
}

//PyObject* WindLabFeatureLocationDistribution::getPyObject(void)
//{
//    if (PythonObject.is(Py::_None())) {
//        // ref counter is set to 1
//        PythonObject = Py::Object(new WindLabFeatureLocationDistributionPy(this), true);
//    }
//    return Py::new_reference_to(PythonObject);
//}