/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel <juergen.riegel@web.de>              *
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
#include <Base/PyObjectBase.h>
#include <Base/Factory.h>
#include <Mod/WindLabTools/App/coherence/DavenportCoherencePy.h>
#include <Mod/WindLabTools/App/meanWindSpeed/DeavesHarrisMeanWindSpeedPy.h>
#include <Mod/WindLabTools/App/meanWindSpeed/LogarithmicMeanWindSpeedPy.h>
#include <Mod/WindLabTools/App/meanWindSpeed/PowerLawMeanWindSpeedPy.h>
#include <Mod/WindLabTools/App/meanWindSpeed/HongandHong2021MeanWindSpeedPy.h>

#include <Mod/WindLabTools/App/spectrum/DavenportSpectrumPy.h>
#include <Mod/WindLabTools/App/spectrum/GeneralizedKaimalSpectrumPy.h>
#include <Mod/WindLabTools/App/spectrum/GeneralizedVonKarmanSpectrumPy.h>
#include <Mod/WindLabTools/App/spectrum/HarrisSpectrumPy.h>
#include <Mod/WindLabTools/App/spectrum/KaimalSpectrumPy.h>
#include <Mod/WindLabTools/App/spectrum/SimuSpectrumPy.h>
#include <Mod/WindLabTools/App/spectrum/VonKarmanSpectrumPy.h>
#include <Mod/WindLabTools/App/spectrum/WindSpectrumPy.h>
#include <Mod/WindLabTools/App/modulation/ExponentialModulationPy.h>
#include <Mod/WindLabTools/App/modulation/SineModulationPy.h>
#include <Mod/WindLabTools/App/modulation/ThreeParametersModulationPy.h>
#include <Mod/WindLabTools/App/coherence/KrenkCoherencePy.h>
#include <Mod/WindLabTools/App/turbulenceIntensity/TurbulenceIntensityPy.h>
#include <Mod/WindLabTools/App/modulation/DominikEtAl2013Py.h>


namespace WindLabTools {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(WindLabTools)
{
    PyObject* WindLabToolsModule = WindLabTools::initModule();

    Base::Interpreter().addType(&WindLabTools::DeavesHarrisMeanWindSpeedPy ::Type, WindLabToolsModule, "DeavesHarrisMeanWindSpeed");
    Base::Interpreter().addType(&WindLabTools::LogarithmicMeanWindSpeedPy ::Type, WindLabToolsModule, "LogarithmicMeanWindSpeed");
    Base::Interpreter().addType(&WindLabTools::PowerLawMeanWindSpeedPy ::Type, WindLabToolsModule, "PowerLawMeanWindSpeed");
    Base::Interpreter().addType(&WindLabTools::HongandHong2021MeanWindSpeedPy ::Type, WindLabToolsModule, "HongandHong2021MeanWindSpeed");
    
    Base::Interpreter().addType(&WindLabTools::DavenportCoherencePy ::Type, WindLabToolsModule, "DavenportCoherence");
    Base::Interpreter().addType(&WindLabTools::KrenkCoherencePy ::Type, WindLabToolsModule, "KrenkCoherence");
    
    Base::Interpreter().addType(&WindLabTools::TurbulenceIntensityPy ::Type, WindLabToolsModule, "TurbulenceIntensity");
    
    Base::Interpreter().addType(&WindLabTools::DavenportSpectrumPy ::Type, WindLabToolsModule, "DavenportSpectrum");
    Base::Interpreter().addType(&WindLabTools::GeneralizedKaimalSpectrumPy ::Type, WindLabToolsModule, "GeneralizedKaimalSpectrum");
    Base::Interpreter().addType(&WindLabTools::GeneralizedVonKarmanSpectrumPy ::Type, WindLabToolsModule, "GeneralizedVonKarmanSpectrum");
    Base::Interpreter().addType(&WindLabTools::HarrisSpectrumPy ::Type, WindLabToolsModule, "HarrisSpectrum");
    Base::Interpreter().addType(&WindLabTools::KaimalSpectrumPy ::Type, WindLabToolsModule, "KaimalSpectrum");
    Base::Interpreter().addType(&WindLabTools::SimuSpectrumPy ::Type, WindLabToolsModule, "SimuSpectrum");
    Base::Interpreter().addType(&WindLabTools::VonKarmanSpectrumPy ::Type, WindLabToolsModule, "VonKarmanSpectrum");
    Base::Interpreter().addType(&WindLabTools::WindSpectrumPy ::Type, WindLabToolsModule, "WindSpectrum");

    Base::Interpreter().addType(&WindLabTools::ExponentialModulationPy ::Type, WindLabToolsModule, "ExponentialModulation");
    Base::Interpreter().addType(&WindLabTools::SineModulationPy ::Type, WindLabToolsModule, "SineModulation");
    Base::Interpreter().addType(&WindLabTools::ThreeParametersModulationPy ::Type, WindLabToolsModule, "ThreeParametersModulation");
    Base::Interpreter().addType(&WindLabTools::DominikEtAl2013Py ::Type, WindLabToolsModule, "DominikEtAl2013");

    
    Base::Console().Log("Loading WindLabTools module... done\n");

    PyMOD_Return(WindLabToolsModule);
}
