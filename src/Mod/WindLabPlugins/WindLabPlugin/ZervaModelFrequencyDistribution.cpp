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

#include "ZervaModelFrequencyDistribution.h"
#include <Base/Console.h>

using namespace WindLab;

PROPERTY_SOURCE(WindLab::ZervaModelFrequencyDistribution, WindLabAPI::WindLabFeatureFrequencyDistribution)

ZervaModelFrequencyDistribution::ZervaModelFrequencyDistribution()
{
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_WindLab#Zerva_Frequency_Discretization");
}

bool ZervaModelFrequencyDistribution::ComputeFrequenciesVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector)
{
	for (int l = 0; l < Data.numberOfFrequency.getValue(); l++)
	{
        ComputeFrequencyValue(Data, location, l, dValVector(l));
	}

	return true;
}

bool ZervaModelFrequencyDistribution::ComputeFrequenciesMatrixFP(const WindLabAPI::WindLabSimulationData &Data, mat &dMatrix)
{
    Base::Vector3d location(0, 0, 0);//unused

    for (int l = 0; l < Data.numberOfFrequency.getValue(); l++) {
        
        for (int m = 0; m < Data.numberOfSpatialPosition.getValue(); m++) {

            ComputeFrequencyValue(Data, location, l, dMatrix(l, m));
        }
    }
    return true;
}

bool ZervaModelFrequencyDistribution::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    return true;
}

bool ZervaModelFrequencyDistribution::ComputeFrequencyValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue)
{
    dValue = Data.minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond) + (1 + 0.5 * frequencyIndex) * Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
	return true;
}

