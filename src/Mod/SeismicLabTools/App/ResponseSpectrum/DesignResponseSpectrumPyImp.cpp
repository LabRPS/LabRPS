/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
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

#include <CXX/Objects.hxx>
#include "DesignResponseSpectrum.h"
#include <Base/VectorPy.h>


// inclusion of the generated files (generated out of DesignResponseSpectrumPy.xml)
#include "Mod/SeismicLabTools/App/ResponseSpectrum/DesignResponseSpectrumPy.h"
#include "Mod/SeismicLabTools/App/ResponseSpectrum/DesignResponseSpectrumPy.cpp"

//#include <API/SeismicLabAPI/RPSSeismicLabsimuDataPy.h>

using namespace SeismicLabTools;

// returns a string which represents the object e.g. when printed in python
std::string DesignResponseSpectrumPy::representation(void) const
{
    return std::string("<DesignResponseSpectrum object>");
}

PyObject* DesignResponseSpectrumPy::PyMake(struct _typeobject*, PyObject*, PyObject*)// Python wrapper
{
    // create a new instance of WindPy and the Twin object
    return new DesignResponseSpectrumPy(new DesignResponseSpectrum());
}

// constructor method
int DesignResponseSpectrumPy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

// +++ methods implementer ++++++++++++++++++++++++++++++++++++++++++++++++

PyObject* DesignResponseSpectrumPy::compute_Euro_EN1998_1_2004_Hori_Elastic_Response_Spectrum(PyObject* args)
{
    double time;
    int nationalAnnex = 1;
    double damping = 5;
    double pga = 0.16;
    int spectrumType = 1;
    int groundType = 1;
    int importanceClass = 2;

    if (!PyArg_ParseTuple(args, "d|iddiii", &time, &nationalAnnex, &damping, &pga, &spectrumType, &groundType, &importanceClass))
    return nullptr;
    return Py::new_reference_to(Py::Float(getDesignResponseSpectrumPtr()->compute_Euro_EN1998_1_2004_Hori_Elastic_Response_Spectrum(
            time, nationalAnnex, damping, pga, spectrumType, groundType,
            importanceClass)));

}

PyObject* DesignResponseSpectrumPy::compute_Euro_EN1998_1_2004_Hori_Design_Response_Spectrum(PyObject* args)
{
    double time;
    int nationalAnnex = 1;
    double damping = 5;
    double pga = 0.16;
    int spectrumType = 1;
    int groundType = 1;
    int importanceClass = 2;
    double behaviorFactor = 1.00;
    double lowerBoundFactor = 0.20;

    if (!PyArg_ParseTuple(args, "d|iddiiidd", &time, &nationalAnnex, &damping, &pga, &spectrumType, &groundType, &importanceClass, &behaviorFactor, &lowerBoundFactor))
    return nullptr;
    return Py::new_reference_to(Py::Float(getDesignResponseSpectrumPtr()->compute_Euro_EN1998_1_2004_Hori_Design_Response_Spectrum(
            time, nationalAnnex, damping, pga, spectrumType, groundType, importanceClass, behaviorFactor, lowerBoundFactor)));

}
 
PyObject* DesignResponseSpectrumPy::compute_Euro_EN1998_1_2004_Vert_Elastic_Response_Spectrum(PyObject* args)
{
    double time;
    int nationalAnnex = 1;
    double damping = 5;
    double pga = 0.16;
    int spectrumType = 1;
    int groundType = 1;
    int importanceClass = 2;

    if (!PyArg_ParseTuple(args, "d|iddiii", &time, &nationalAnnex, &damping, &pga, &spectrumType,
                          &groundType, &importanceClass))
        return nullptr;
    return Py::new_reference_to(Py::Float(
        getDesignResponseSpectrumPtr()->compute_Euro_EN1998_1_2004_Vert_Elastic_Response_Spectrum(
            time, nationalAnnex, damping, pga, spectrumType, groundType, importanceClass)));
}

PyObject* DesignResponseSpectrumPy::compute_Euro_EN1998_1_2004_Vert_Design_Response_Spectrum(PyObject* args)
{
    double time;
    int nationalAnnex = 1;
    double damping = 5;
    double pga = 0.16;
    int spectrumType = 1;
    int groundType = 1;
    int importanceClass = 2;
    double behaviorFactor = 1.00;
    double lowerBoundFactor = 0.20;

    if (!PyArg_ParseTuple(args, "d|iddiiidd", &time, &nationalAnnex, &damping, &pga, &spectrumType,
                          &groundType, &importanceClass, &behaviorFactor, &lowerBoundFactor))
        return nullptr;
    return Py::new_reference_to(Py::Float(
        getDesignResponseSpectrumPtr()->compute_Euro_EN1998_1_2004_Vert_Design_Response_Spectrum(
            time, nationalAnnex, damping, pga, spectrumType, groundType, importanceClass,
            behaviorFactor, lowerBoundFactor)));
}

// +++ custom attributes implementer ++++++++++++++++++++++++++++++++++++++++


PyObject *DesignResponseSpectrumPy::getCustomAttributes(const char* /*attr*/) const
{
    return nullptr;
}

int DesignResponseSpectrumPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
