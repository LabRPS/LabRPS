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

#include "DataReshaper.h"
#include <Gui/Control.h>


using namespace std;
using namespace SeaLab;

////////////////////////Horizontal distribution///////////////////////////////////////////////

PROPERTY_SOURCE(SeaLab::DataReshaper, SeaLabAPI::SeaLabFeatureTableTool)

DataReshaper::DataReshaper()
{
    ADD_PROPERTY_TYPE(LengthNumberOfPoints, (3), "Parameters", App::Prop_None, "The number of points along the length of lthe grid.");
    ADD_PROPERTY_TYPE(WidthNumberOfPoints, (1), "Parameters", App::Prop_None, "The number of points along the width of lthe grid.");
    ADD_PROPERTY_TYPE(TimeIndex, (0), "Parameters", App::Prop_None, "The index of the time instant at with the data will be reshaped.");
}

bool DataReshaper::TableToolCompute(const SeaLabAPI::SeaLabSimulationData &Data, const mat &inputTable, mat &outputTable)
{
    if (inputTable.rows() != Data.numberOfTimeIncrements.getValue() || inputTable.cols() != Data.numberOfSpatialPosition.getValue() + 1)
    {
        Base::Console().Error("Invalid input data.\n");
        return false;
    }

    int pointNumberX = Data.numberOfGridPointsAlongX.getValue();
    int pointNumberY = Data.numberOfGridPointsAlongY.getValue();

    int nPoints = pointNumberX * pointNumberY;
    if (nPoints != Data.numberOfSpatialPosition.getValue())
    {
        Base::Console().Error("The computation fails. The number of simulation points should be %d.\n", nPoints);
        return false;
    }

    vec toBeReshaped = inputTable.row(TimeIndex.getValue()).tail(inputTable.cols() - 1);
    Eigen::Map<mat> theReshaped(toBeReshaped.data(), pointNumberX, pointNumberY);
    outputTable = theReshaped;
    return true;
}

bool DataReshaper::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
	return true;
}
