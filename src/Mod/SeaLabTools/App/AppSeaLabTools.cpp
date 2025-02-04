/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel <juergen.riegel@web.de>              *
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

#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <Base/Factory.h>
#include <Mod/SeaLabTools/App/spectrum/SeaSurfaceSpectrumPy.h>
#include <Mod/SeaLabTools/App/spectrum/JonswapSpectrumPy.h>
#include <Mod/SeaLabTools/App/spectrum/OchiAndHubbleSpectrumPy.h>
#include <Mod/SeaLabTools/App/spectrum/PiersonMoskowitzSpectrumPy.h>
#include <Mod/SeaLabTools/App/spectrum/TorsethaugenSpectrumPy.h>
#include <Mod/SeaLabTools/App/spectrum/GaussianSwellSpectrumPy.h>
#include "Mod/SeaLabTools/App/spectrum/BretschneiderSpectrumPy.h"
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/DirectionalSpreadingFunctionPy.h>
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/OrcaFlexDirectionalSpreadingFunctionPy.h>



namespace SeaLabTools {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(SeaLabTools)
{
    PyObject* SeaLabToolsModule = SeaLabTools::initModule();

    Base::Interpreter().addType(&SeaLabTools::SeaSurfaceSpectrumPy ::Type, SeaLabToolsModule, "SeaSurfaceSpectrum");
    Base::Interpreter().addType(&SeaLabTools::JonswapSpectrumPy ::Type, SeaLabToolsModule, "JonswapSpectrum");
    Base::Interpreter().addType(&SeaLabTools::OchiAndHubbleSpectrumPy ::Type, SeaLabToolsModule, "OchiAndHubbleSpectrum");
    Base::Interpreter().addType(&SeaLabTools::PiersonMoskowitzSpectrumPy ::Type, SeaLabToolsModule, "PiersonMoskowitzSpectrum");
    Base::Interpreter().addType(&SeaLabTools::TorsethaugenSpectrumPy ::Type, SeaLabToolsModule, "TorsethaugenSpectrum");
    Base::Interpreter().addType(&SeaLabTools::GaussianSwellSpectrumPy ::Type, SeaLabToolsModule, "GaussianSwellSpectrum");
    Base::Interpreter().addType(&SeaLabTools::BretschneiderSpectrumPy ::Type, SeaLabToolsModule, "BretschneiderSpectrum");
    Base::Interpreter().addType(&SeaLabTools::DirectionalSpreadingFunctionPy ::Type, SeaLabToolsModule, "DirectionalSpreadingFunction");
    Base::Interpreter().addType(&SeaLabTools::OrcaFlexDirectionalSpreadingFunctionPy ::Type, SeaLabToolsModule, "OrcaFlexDirectionalSpreadingFunction");

    Base::Console().Log("Loading SeaLabTools module... done\n");

    PyMOD_Return(SeaLabToolsModule);
}
