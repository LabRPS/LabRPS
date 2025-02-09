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

#include "widgets/DlgUniformDistributionLocation.h"
#include "WLUniformDistributionLocations.h"
#include <QMessageBox>
#include <Gui/Control.h>


using namespace std;
using namespace SeismicLab;

////////////////////////Horizontal distribution///////////////////////////////////////////////

PROPERTY_SOURCE(SeismicLab::WLUniformDistributionLocations, SeismicLabAPI::SeismicLabFeatureLocationDistribution)

WLUniformDistributionLocations::WLUniformDistributionLocations()
{

	static const char* locationgroup = "Distribution";
    static const char* directionEnum[] = {"X", "Y", "Z", nullptr};

    ADD_PROPERTY_TYPE(FirstPoint, (Base::Vector3d(0,0,40000)), locationgroup, App::Prop_None, "the first point the distribution will start from");
    ADD_PROPERTY_TYPE(Spacing, (5000.0), locationgroup, App::Prop_None, "The even spacing between the points");
	ADD_PROPERTY_TYPE(Directions, ((long int)0), locationgroup, App::Prop_None,"The direction in which the simulation points are uniformly distributed.");

    Directions.setEnums(directionEnum);
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeismicLab#Uniform_Distribution");

}


bool WLUniformDistributionLocations::ComputeLocationCoordinateMatrixP3(const SeismicLabAPI::SeismicLabSimulationData& Data, mat &dLocCoord)
{
	// Computing the location coordinates
	for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue(); loop++)
	{		
		static const char* locationgroup = Directions.getValueAsString();

		if (QString::fromLatin1(Directions.getValueAsString()) == QString::fromLatin1("X"))
		{     
       dLocCoord(loop, 0) = loop + 1;		
       dLocCoord(loop, 1) = (Base::Quantity(FirstPoint.getValue().x, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre) + loop * Spacing.getQuantityValue().getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 2) = (Base::Quantity(FirstPoint.getValue().y, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 3) = (Base::Quantity(FirstPoint.getValue().z, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);

		}
        else if (QString::fromLatin1(Directions.getValueAsString()) == QString::fromLatin1("Y")) {
       dLocCoord(loop, 0) = loop + 1;		
	   dLocCoord(loop, 1) = (Base::Quantity(FirstPoint.getValue().x, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 2) = (Base::Quantity(FirstPoint.getValue().y, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre) + loop * Spacing.getQuantityValue().getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 3) = (Base::Quantity(FirstPoint.getValue().z, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);

        }
        else if (QString::fromLatin1(Directions.getValueAsString()) == QString::fromLatin1("Z")) {
       dLocCoord(loop, 0) = loop + 1;		
	   dLocCoord(loop, 1) = (Base::Quantity(FirstPoint.getValue().x, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 2) = (Base::Quantity(FirstPoint.getValue().y, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 3) = (Base::Quantity(FirstPoint.getValue().z, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre) + loop * Spacing.getQuantityValue().getValueAs(Base::Quantity::Metre);

        }
	}

	return true;	
}


bool WLUniformDistributionLocations::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
	
	SeismicLabGui::UniformLocationDistributionDialogEdit* dlg = new SeismicLabGui::UniformLocationDistributionDialogEdit(FirstPoint, Spacing,Data.spatialDistribution, Directions);
    Gui::Control().showDialog(dlg);

	return true;
}
