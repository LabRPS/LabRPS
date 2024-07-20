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
#include "SeaLabFeatureLocationDistribution.h"
//#include <Mod/SeaLabAPI/App/SeaLabFeatureLocationDistributionPy.h>

using namespace SeaLabAPI;

RPS_LOG_LEVEL_INIT("SeaLabFeatureLocationDistribution",true,true)

PROPERTY_SOURCE(SeaLabAPI::SeaLabFeatureLocationDistribution, SeaLabAPI::SeaLabFeature)


SeaLabFeatureLocationDistribution::SeaLabFeatureLocationDistribution(void)
{
}

SeaLabFeatureLocationDistribution::~SeaLabFeatureLocationDistribution()
{
}

short SeaLabFeatureLocationDistribution::mustExecute(void) const
{
    return SeaLabFeature::mustExecute();
}

App::DocumentObjectExecReturn * SeaLabFeatureLocationDistribution::recompute(void)
{
    try {
        return SeaLabAPI::SeaLabFeature::recompute();
    }
    catch (Base::Exception& e) {

        App::DocumentObjectExecReturn* ret = new App::DocumentObjectExecReturn(e.what());
        if (ret->Why.empty()) ret->Why = "Unknown exception";
        return ret;
    }
}

App::DocumentObjectExecReturn * SeaLabFeatureLocationDistribution::execute(void)
{
    return SeaLabFeature::execute();
}

void SeaLabFeatureLocationDistribution::onChanged(const App::Property* prop)
{

    SeaLabFeature::onChanged(prop);
}

//PyObject* SeaLabFeatureLocationDistribution::getPyObject(void)
//{
//    if (PythonObject.is(Py::_None())) {
//        // ref counter is set to 1
//        PythonObject = Py::Object(new SeaLabFeatureLocationDistributionPy(this), true);
//    }
//    return Py::new_reference_to(PythonObject);
//}