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
#include <Mod/SeismicLabTools/App/coherence/LohAndLinCoherencePy.h>
#include <Mod/SeismicLabTools/App/coherence/AbrahamsonCoherencePy.h>
#include <Mod/SeismicLabTools/App/coherence/HarichandranVanmarckeCoherencePy.h>
#include <Mod/SeismicLabTools/App/spectrum/CloughPenzienSpectrumPy.h>
#include <Mod/SeismicLabTools/App/spectrum/SeismicGroundMotionSpectrumPy.h>
#include <Mod/SeismicLabTools/App/spectrum/HuZhouSpectrumPy.h>
#include <Mod/SeismicLabTools/App/spectrum/KanaiTajimiSpectrumPy.h>
#include <Mod/SeismicLabTools/App/modulation/ConstantModulationPy.h>
#include <Mod/SeismicLabTools/App/modulation/ExponentialModulationPy.h>
#include <Mod/SeismicLabTools/App/modulation/JenningsEtAl1968ModulationPy.h>
#include <Mod/SeismicLabTools/App/modulation/SaragoniHart1974ModulationPy.h>
#include <Mod/SeismicLabTools/App/modulation/TrapezoidalModulationPy.h>
#include <Mod/SeismicLabTools/App/modulation/BogdanoffGoldbergBernardModulationPy.h>
#include <Mod/SeismicLabTools/App/ResponseSpectrum/BaseDesignResponseSpectrumPy.h>
#include <Mod/SeismicLabTools/App/ResponseSpectrum/DesignResponseSpectrumPy.h>

namespace SeismicLabTools {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(SeismicLabTools)
{
    PyObject* SeismicLabToolsModule = SeismicLabTools::initModule();

    Base::Interpreter().addType(&SeismicLabTools::LohAndLinCoherencePy ::Type, SeismicLabToolsModule, "LohAndLinCoherence");
    Base::Interpreter().addType(&SeismicLabTools::AbrahamsonCoherencePy ::Type, SeismicLabToolsModule, "AbrahamsonCoherence");
    Base::Interpreter().addType(&SeismicLabTools::HarichandranVanmarckeCoherencePy ::Type, SeismicLabToolsModule, "HarichandranVanmarckeCoherence");

    Base::Interpreter().addType(&SeismicLabTools::SeismicGroundMotionSpectrumPy ::Type, SeismicLabToolsModule, "SeismicGroundMotionSpectrum");
    Base::Interpreter().addType(&SeismicLabTools::CloughPenzienSpectrumPy ::Type, SeismicLabToolsModule, "CloughPenzienSpectrum");
    Base::Interpreter().addType(&SeismicLabTools::KanaiTajimiSpectrumPy ::Type, SeismicLabToolsModule, "KanaiTajimiSpectrum");
    Base::Interpreter().addType(&SeismicLabTools::HuZhouSpectrumPy ::Type, SeismicLabToolsModule, "HuZhouSpectrum");

    Base::Interpreter().addType(&SeismicLabTools::ExponentialModulationPy ::Type, SeismicLabToolsModule, "ExponentialModulation");
    Base::Interpreter().addType(&SeismicLabTools::ConstantModulationPy ::Type, SeismicLabToolsModule, "LohAndLinCoherence");
    Base::Interpreter().addType(&SeismicLabTools::JenningsEtAl1968ModulationPy ::Type, SeismicLabToolsModule, "JenningsEtAl1968Modulation");
    Base::Interpreter().addType(&SeismicLabTools::SaragoniHart1974ModulationPy ::Type, SeismicLabToolsModule, "SaragoniHart1974Modulation");
    Base::Interpreter().addType(&SeismicLabTools::TrapezoidalModulationPy ::Type, SeismicLabToolsModule, "TrapezoidalModulation");
    Base::Interpreter().addType(&SeismicLabTools::BogdanoffGoldbergBernardModulationPy ::Type, SeismicLabToolsModule, "BogdanoffGoldbergBernardModulation");

    Base::Interpreter().addType(&SeismicLabTools::BaseDesignResponseSpectrumPy ::Type, SeismicLabToolsModule, "BaseDesignResponseSpectrum");
    Base::Interpreter().addType(&SeismicLabTools::DesignResponseSpectrumPy ::Type, SeismicLabToolsModule, "DesignResponseSpectrum");

    Base::Console().Log("Loading SeismicLabTools module... done\n");

    PyMOD_Return(SeismicLabToolsModule);
}
