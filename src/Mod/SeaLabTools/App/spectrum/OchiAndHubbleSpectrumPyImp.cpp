/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
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

#include <CXX/Objects.hxx>
#include "OchiAndHubbleSpectrum.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of OchiAndHubbleSpectrumPy.xml)
#include "Mod/SeaLabTools/App/spectrum/OchiAndHubbleSpectrumPy.h"
#include "Mod/SeaLabTools/App/spectrum/OchiAndHubbleSpectrumPy.cpp"

//#include <API/SeaLabAPI/RPSSeaLabsimuDataPy.h>

using namespace SeaLabTools;

// returns a string which represents the object e.g. when printed in python
std::string OchiAndHubbleSpectrumPy::representation(void) const
{
    return std::string("<OchiAndHubbleSpectrum object>");
}

PyObject* OchiAndHubbleSpectrumPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new OchiAndHubbleSpectrumPy(new OchiAndHubbleSpectrum());
}

// constructor method
int OchiAndHubbleSpectrumPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* OchiAndHubbleSpectrumPy::computeSpectrum(PyObject *args)
{
    double frequency;
    double peakShape1;
    double peakShape2;
    double peakFrequency1;
    double peakFrequency2;
    double significantWaveHeight1;
    double significantWaveHeight2;

    if (!PyArg_ParseTuple(args, "ddddddd", &frequency, &peakShape1, &peakShape2, &peakFrequency1, &peakFrequency2, &significantWaveHeight1, &significantWaveHeight2))
    return nullptr;
    return Py::new_reference_to(Py::Float(getOchiAndHubbleSpectrumPtr()->computeSpectrum(frequency, peakShape1, peakShape2, peakFrequency1, peakFrequency2, significantWaveHeight1, significantWaveHeight2)));

}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *OchiAndHubbleSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int OchiAndHubbleSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
