/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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
# include <QDockWidget>
# include <QStatusBar>
#endif

#include "Simulation.h"
#include "SimulationPy.h"

using namespace App;

PROPERTY_SOURCE(App::Simulation, App::DocumentObject)

Simulation::Simulation()
  : _name("")
{
    ADD_PROPERTY_TYPE(isRunning, (false), 0, App::Prop_None, "Whether the simulation is running or not.");

}

Simulation::~Simulation()
{
}

std::string Simulation::name() const
{
    return _name;
}

void Simulation::setName(const std::string& name)
{
    _name = name;
}


bool Simulation::run()
{   
    return false;
}

bool Simulation::stop()
{
    return false;
}

std::list<std::string> Simulation::listRPSFeatureGroups() const
{
    return std::list<std::string> ();
}

std::list<std::pair<std::string, std::list<std::string>>> Simulation::getRPSFeatures() const
{
   
    return     std::list<std::pair<std::string, std::list<std::string>>>();
}

std::string Simulation::getPhenomenonName() const
{
    return std::string("");
}

std::string Simulation::workbenchName() const
{
    return std::string("");

}

bool Simulation::doubleClicked(void)
{
    return true;
}

void Simulation::onChanged(const App::Property* prop)
{
   
    DocumentObjectGroup::onChanged(prop);
}

PyObject* Simulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new SimulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

void Simulation::slotSimulationAbort(const App::Document& Doc) {

}
