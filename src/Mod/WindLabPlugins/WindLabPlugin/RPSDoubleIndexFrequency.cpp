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

#include "RPSDoubleIndexFrequency.h"
#include <QMessageBox>
#include "Widgets/RPSFrequencyDistributionDialog.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSDoubleIndexFrequency, WindLabAPI::WindLabFeatureFrequencyDistribution)

CRPSDoubleIndexFrequency::CRPSDoubleIndexFrequency() {

}

bool CRPSDoubleIndexFrequency::ComputeFrequenciesVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, vec &dValVector)
{
	for (int l = 0; l < Data.numberOfFrequency.getValue(); l++)
	{
        ComputeFrequencyValue(Data, location, l, dValVector(l));
	}

	return true;
}

bool CRPSDoubleIndexFrequency::ComputeFrequenciesMatrixFP(const WindLabAPI::WindLabSimuData &Data, mat &dMatrix)
{
    mat locationCoord(Data.numberOfSpatialPosition.getValue(), 4);

    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, locationCoord);

    if (!returnResult)
    {
        return false;
    }

     Base::Vector3d location(0, 0, 0);

    for (int m = 0; m < Data.numberOfSpatialPosition.getValue(); m++) {

         location = Base::Vector3d(locationCoord(m, 1), locationCoord(m, 2), locationCoord(m, 3));

        for (int l = 0; l < Data.numberOfFrequency.getValue(); l++) {

            ComputeFrequencyValue(Data, location, l, dMatrix(l, m));
        }
    }

    return true;
}


bool CRPSDoubleIndexFrequency::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    // the input diolag
    std::unique_ptr<RPSFrequencyDistributionDialog> dlg(new RPSFrequencyDistributionDialog(2));

    if (dlg->exec() == QDialog::Accepted) //
    {

    }

    return true;
}

bool CRPSDoubleIndexFrequency::ComputeFrequencyValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue)
{
    mat locationCoord(Data.numberOfSpatialPosition.getValue(), 4);

    CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data,locationCoord);

    int locationIndex = CRPSWindLabFramework::getLocationIndex(Data, location);

    if (locationIndex < 0 || locationIndex > Data.numberOfSpatialPosition.getValue())
    {
        return false;
    }

    dValue = Data.minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond) + frequencyIndex * Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond) + (locationIndex + 1)*Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond) / Data.numberOfSpatialPosition.getValue();

    return true;
}

