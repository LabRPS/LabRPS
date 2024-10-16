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

#include <Base/Console.h>
#include <Base/Interpreter.h>

#include "UserDefinedPhenomenonLabSimulation.h"
#include "UserDefinedPhenomenonLabSimulationPy.h"
#include "UserDefinedPhenomenonLabSimulationComparison.h"
#include "UserDefinedPhenomenonLabSimulationComparisonPy.h"


namespace UserDefinedPhenomenonLab {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(UserDefinedPhenomenonLab)
{
     //load dependent module
    try {
        Base::Interpreter().runString("import UserDefinedPhenomenonLabAPI");
        Base::Interpreter().runString("import GeneralTools");

    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }

    PyObject* userdefinedphenomenonlabModule = UserDefinedPhenomenonLab::initModule();

    // Add Types to module
    Base::Interpreter().addType(&UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulationPy                   ::Type, userdefinedphenomenonlabModule, "UserDefinedPhenomenonLabSimulation");
    Base::Interpreter().addType(&UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulationComparisonPy         ::Type, userdefinedphenomenonlabModule, "UserDefinedPhenomenonLabSimulationComparison");

    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation           ::init();
    UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulationComparison ::init();

    Base::Console().Log("Loading UserDefinedPhenomenonLab module... done\n");

    PyMOD_Return(userdefinedphenomenonlabModule);
}
