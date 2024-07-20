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
#include "IrpsSeLLocationDistribution.h"
#include "SeaLabSimulationDataPy.h"
#include "SeaLabFeature.h"
#include "SeaLabFeatureLocationDistribution.h"
#include "SeaLabFeatureMeanAcceleration.h"
#include "SeaLabFeatureSpectrum.h"
#include "SeaLabFeaturePSDDecompositionMethod.h"
#include "SeaLabFeatureCoherence.h"
#include "SeaLabFeatureSimulationMethod.h"
#include "SeaLabFeatureFrequencyDistribution.h"
#include "SeaLabFeatureRandomness.h"
#include "SeaLabFeatureModulation.h"
#include "SeaLabFeatureCorrelation.h"
#include "SeaLabFeatureTableTool.h"
#include "SeaLabFeatureMatrixTool.h"
#include "SeaLabFeatureCumulativeProbabilityDistribution.h"
#include "SeaLabFeatureKurtosis.h"
#include "SeaLabFeaturePeakFactor.h"
#include "SeaLabFeatureProbabilityDensityFunction.h"
#include "SeaLabFeatureShearVelocityOfFlow.h"
#include "SeaLabFeatureSkewness.h"
#include "SeaLabFeatureStandardDeviation.h"
#include "SeaLabFeatureVariance.h"
#include "SeaLabFeatureWavePassageEffect.h"
#include "SeaLabFeatureUserDefinedRPSObject.h"
#include "SeaLabFeatureMatrixTool.h"
#include "SeaLabFeatureTableTool.h"
#include "SeaLabFeaturePy.h"


namespace SeaLabAPI {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(SeaLabAPI)
{
    PyObject* SeaLabAPIModule = SeaLabAPI::initModule();

    // Add Types to module
    Base::Interpreter().addType(&SeaLabAPI::SeaLabSimulationDataPy ::Type, SeaLabAPIModule, "SeaLabSimulationData");
    Base::Interpreter().addType(&SeaLabAPI::SeaLabFeaturePy::Type, SeaLabAPIModule, "SeaLabFeature");

    SeaLabAPI::SeaLabFeature::init();
    SeaLabAPI::SeaLabFeatureLocationDistribution::init();
    SeaLabAPI::SeaLabFeatureMeanAcceleration ::init();
    SeaLabAPI::SeaLabFeatureSpectrum::init();
    SeaLabAPI::SeaLabFeaturePSDDecompositionMethod::init();
    SeaLabAPI::SeaLabFeatureCoherence::init();
    SeaLabAPI::SeaLabFeatureSimulationMethod::init();
    SeaLabAPI::SeaLabFeatureFrequencyDistribution::init();
    SeaLabAPI::SeaLabFeatureRandomness::init();
    SeaLabAPI::SeaLabFeatureModulation::init();
    SeaLabAPI::SeaLabFeatureCorrelation::init();
    SeaLabAPI::SeaLabFeatureTableTool::init();
    SeaLabAPI::SeaLabFeatureMatrixTool::init();
    SeaLabAPI::SeaLabFeatureCumulativeProbabilityDistribution::init();
    SeaLabAPI::SeaLabFeatureKurtosis::init();
    SeaLabAPI::SeaLabFeaturePeakFactor::init();
    SeaLabAPI::SeaLabFeatureProbabilityDensityFunction::init();
    SeaLabAPI::SeaLabFeatureShearVelocityOfFlow::init();
    SeaLabAPI::SeaLabFeatureSkewness::init();
    SeaLabAPI::SeaLabFeatureStandardDeviation::init();
    SeaLabAPI::SeaLabFeatureVariance::init();
    SeaLabAPI::SeaLabFeatureWavePassageEffect::init();
    SeaLabAPI::SeaLabFeatureUserDefinedRPSObject::init();
    SeaLabAPI::SeaLabSimulationData::init();

    Base::Console().Log("Loading SeaLabAPI module... done\n");

    PyMOD_Return(SeaLabAPIModule);
}
