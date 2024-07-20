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
#include "IrpsSLLocationDistribution.h"
#include "SeismicLabSimulationDataPy.h"
#include "SeismicLabFeature.h"
#include "SeismicLabFeatureLocationDistribution.h"
#include "SeismicLabFeatureMeanAcceleration.h"
#include "SeismicLabFeatureSpectrum.h"
#include "SeismicLabFeaturePSDDecompositionMethod.h"
#include "SeismicLabFeatureCoherence.h"
#include "SeismicLabFeatureSimulationMethod.h"
#include "SeismicLabFeatureFrequencyDistribution.h"
#include "SeismicLabFeatureRandomness.h"
#include "SeismicLabFeatureModulation.h"
#include "SeismicLabFeatureCorrelation.h"
#include "SeismicLabFeatureTableTool.h"
#include "SeismicLabFeatureMatrixTool.h"
#include "SeismicLabFeatureCumulativeProbabilityDistribution.h"
#include "SeismicLabFeatureKurtosis.h"
#include "SeismicLabFeaturePeakFactor.h"
#include "SeismicLabFeatureProbabilityDensityFunction.h"
#include "SeismicLabFeatureShearVelocityOfFlow.h"
#include "SeismicLabFeatureSkewness.h"
#include "SeismicLabFeatureStandardDeviation.h"
#include "SeismicLabFeatureVariance.h"
#include "SeismicLabFeatureWavePassageEffect.h"
#include "SeismicLabFeatureUserDefinedRPSObject.h"
#include "SeismicLabFeatureMatrixTool.h"
#include "SeismicLabFeatureTableTool.h"
#include "SeismicLabFeaturePy.h"


namespace SeismicLabAPI {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(SeismicLabAPI)
{
    PyObject* SeismicLabAPIModule = SeismicLabAPI::initModule();

    // Add Types to module
    Base::Interpreter().addType(&SeismicLabAPI::SeismicLabSimulationDataPy ::Type, SeismicLabAPIModule, "SeismicLabSimulationData");
    Base::Interpreter().addType(&SeismicLabAPI::SeismicLabFeaturePy::Type, SeismicLabAPIModule, "SeismicLabFeature");

    SeismicLabAPI::SeismicLabFeature::init();
    SeismicLabAPI::SeismicLabFeatureLocationDistribution::init();
    SeismicLabAPI::SeismicLabFeatureMeanAcceleration ::init();
    SeismicLabAPI::SeismicLabFeatureSpectrum::init();
    SeismicLabAPI::SeismicLabFeaturePSDDecompositionMethod::init();
    SeismicLabAPI::SeismicLabFeatureCoherence::init();
    SeismicLabAPI::SeismicLabFeatureSimulationMethod::init();
    SeismicLabAPI::SeismicLabFeatureFrequencyDistribution::init();
    SeismicLabAPI::SeismicLabFeatureRandomness::init();
    SeismicLabAPI::SeismicLabFeatureModulation::init();
    SeismicLabAPI::SeismicLabFeatureCorrelation::init();
    SeismicLabAPI::SeismicLabFeatureTableTool::init();
    SeismicLabAPI::SeismicLabFeatureMatrixTool::init();
    SeismicLabAPI::SeismicLabFeatureCumulativeProbabilityDistribution::init();
    SeismicLabAPI::SeismicLabFeatureKurtosis::init();
    SeismicLabAPI::SeismicLabFeaturePeakFactor::init();
    SeismicLabAPI::SeismicLabFeatureProbabilityDensityFunction::init();
    SeismicLabAPI::SeismicLabFeatureShearVelocityOfFlow::init();
    SeismicLabAPI::SeismicLabFeatureSkewness::init();
    SeismicLabAPI::SeismicLabFeatureStandardDeviation::init();
    SeismicLabAPI::SeismicLabFeatureVariance::init();
    SeismicLabAPI::SeismicLabFeatureWavePassageEffect::init();
    SeismicLabAPI::SeismicLabFeatureUserDefinedRPSObject::init();
    SeismicLabAPI::SeismicLabSimulationData::init();

    Base::Console().Log("Loading SeismicLabAPI module... done\n");

    PyMOD_Return(SeismicLabAPIModule);
}
