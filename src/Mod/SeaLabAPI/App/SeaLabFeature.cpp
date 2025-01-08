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
#include "SeaLabFeature.h"
#include "SeaLabFeaturePy.h"

using namespace SeaLabAPI;
namespace bp = boost::placeholders;

RPS_LOG_LEVEL_INIT("SeaLab",true,true)

PROPERTY_SOURCE(SeaLabAPI::SeaLabFeature, App::RPSFeature)


SeaLabFeature::SeaLabFeature(void)
{
    this->Module.setValue("SeaLab");
}

SeaLabFeature::~SeaLabFeature()
{
}

short SeaLabFeature::mustExecute(void) const
{
    return RPSFeature::mustExecute();
}

App::DocumentObjectExecReturn * SeaLabFeature::recompute(void)
{
    try {
        return App::RPSFeature::recompute();
    }
    catch (Base::Exception& e) {

        App::DocumentObjectExecReturn* ret = new App::DocumentObjectExecReturn(e.what());
        if (ret->Why.empty()) ret->Why = "Unknown exception";
        return ret;
    }
}

App::DocumentObjectExecReturn * SeaLabFeature::execute(void)
{
    return RPSFeature::execute();
}

void SeaLabFeature::onChanged(const App::Property* prop)
{
    RPSFeature::onChanged(prop);
}

PyObject* SeaLabFeature::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        PythonObject = Py::Object(new SeaLabFeaturePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}