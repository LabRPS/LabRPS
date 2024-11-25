/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>         *
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
#include "IrpsWLLocationDistribution.h"
#include "WindLabSimulationDataPy.h"
#include "WindLabFeature.h"
#include "WindLabFeatureLocationDistribution.h"
#include "WindLabFeatureMeanWind.h"
#include "WindLabFeatureXSpectrum.h"
#include "WindLabFeatureZSpectrum.h"
#include "WindLabFeatureYSpectrum.h"
#include "WindLabFeaturePSDDecompositionMethod.h"
#include "WindLabFeatureCoherence.h"
#include "WindLabFeatureSimulationMethod.h"
#include "WindLabFeatureFrequencyDistribution.h"
#include "WindLabFeatureRandomness.h"
#include "WindLabFeatureModulation.h"
#include "WindLabFeatureCorrelation.h"
#include "WindLabFeatureTableTool.h"
#include "WindLabFeatureMatrixTool.h"
#include "WindLabFeatureCumulativeProbabilityDistribution.h"
#include "WindLabFeatureGustFactor.h"
#include "WindLabFeatureKurtosis.h"
#include "WindLabFeaturePeakFactor.h"
#include "WindLabFeatureProbabilityDensityFunction.h"
#include "WindLabFeatureRoughness.h"
#include "WindLabFeatureShearVelocityOfFlow.h"
#include "WindLabFeatureSkewness.h"
#include "WindLabFeatureStandardDeviation.h"
#include "WindLabFeatureTurbulenceIntensity.h"
#include "WindLabFeatureTurbulenceScale.h"
#include "WindLabFeatureVariance.h"
#include "WindLabFeatureWavePassageEffect.h"
#include "WindLabFeatureUserDefinedRPSObject.h"
#include "WindLabFeatureMatrixTool.h"
#include "WindLabFeatureTableTool.h"
#include "WindLabFeaturePy.h"


namespace WindLabAPI {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(WindLabAPI)
{
    PyObject* WindLabAPIModule = WindLabAPI::initModule();

    // Add Types to module
    Base::Interpreter().addType(&WindLabAPI::WindLabSimulationDataPy ::Type, WindLabAPIModule, "WindLabSimulationData");
    Base::Interpreter().addType(&WindLabAPI::WindLabFeaturePy::Type, WindLabAPIModule, "WindLabFeature");

    WindLabAPI::WindLabFeature::init();
    WindLabAPI::WindLabFeatureLocationDistribution::init();
    WindLabAPI::WindLabFeatureMeanWind ::init();
    WindLabAPI::WindLabFeatureXSpectrum::init();
    WindLabAPI::WindLabFeatureZSpectrum::init();
    WindLabAPI::WindLabFeatureYSpectrum::init();
    WindLabAPI::WindLabFeaturePSDDecompositionMethod::init();
    WindLabAPI::WindLabFeatureCoherence::init();
    WindLabAPI::WindLabFeatureSimulationMethod::init();
    WindLabAPI::WindLabFeatureFrequencyDistribution::init();
    WindLabAPI::WindLabFeatureRandomness::init();
    WindLabAPI::WindLabFeatureModulation::init();
    WindLabAPI::WindLabFeatureCorrelation::init();
    WindLabAPI::WindLabFeatureTableTool::init();
    WindLabAPI::WindLabFeatureMatrixTool::init();
    WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution::init();
    WindLabAPI::WindLabFeatureGustFactor::init();
    WindLabAPI::WindLabFeatureKurtosis::init();
    WindLabAPI::WindLabFeaturePeakFactor::init();
    WindLabAPI::WindLabFeatureProbabilityDensityFunction::init();
    WindLabAPI::WindLabFeatureRoughness::init();
    WindLabAPI::WindLabFeatureShearVelocityOfFlow::init();
    WindLabAPI::WindLabFeatureSkewness::init();
    WindLabAPI::WindLabFeatureStandardDeviation::init();
    WindLabAPI::WindLabFeatureTurbulenceIntensity::init();
    WindLabAPI::WindLabFeatureTurbulenceScale::init();
    WindLabAPI::WindLabFeatureVariance::init();
    WindLabAPI::WindLabFeatureWavePassageEffect::init();
    WindLabAPI::WindLabFeatureUserDefinedRPSObject::init();
    WindLabAPI::WindLabSimulationData::init();

    Base::Console().Log("Loading WindLabAPI module... done\n");

    PyMOD_Return(WindLabAPIModule);
}
