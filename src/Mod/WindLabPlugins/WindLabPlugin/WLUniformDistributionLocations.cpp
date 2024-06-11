
#include "widgets/DlgUniformDistributionLocation.h"
#include "WLUniformDistributionLocations.h"
#include <QMessageBox>
#include <Gui/Control.h>


using namespace std;
using namespace WindLab;

////////////////////////Horizontal distribution///////////////////////////////////////////////

PROPERTY_SOURCE(WindLab::WLUniformDistributionLocations, WindLabAPI::WindLabFeatureLocationDistribution)

WLUniformDistributionLocations::WLUniformDistributionLocations()
{

	static const char* locationgroup = "Distribution";
    static const char* directionEnum[] = {"X", "Y", "Z", nullptr};

    ADD_PROPERTY_TYPE(FirstPoint, (Base::Vector3d(0,0,40)), locationgroup, App::Prop_None, "the first point the distribution will start from");
    ADD_PROPERTY_TYPE(Spacing, (5.0), locationgroup, App::Prop_None, "The even spacing between the points");
	ADD_PROPERTY_TYPE(Directions, ((long int)0), locationgroup, App::Prop_None,"The direction in which the simulation points are uniformly distributed.");

    Directions.setEnums(directionEnum);
}


bool WLUniformDistributionLocations::ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord)
{
	// Computing the location coordinates
	for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue(); loop++)
	{		
		static const char* locationgroup = Directions.getValueAsString();

		if (QString::fromLatin1(Directions.getValueAsString()) == QString::fromLatin1("X"))
		{
            //dLocCoord(loop, 0) = loop + 1;		
            //dLocCoord(loop, 1) = FirstPoint.getValue().x + loop * Spacing.getValue();
            //dLocCoord(loop, 2) = FirstPoint.getValue().y;
            //dLocCoord(loop, 3) = FirstPoint.getValue().z;
       
       dLocCoord(loop, 0) = loop + 1;		
       dLocCoord(loop, 1) = (Base::Quantity(FirstPoint.getValue().x, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre) + loop * Spacing.getQuantityValue().getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 2) = (Base::Quantity(FirstPoint.getValue().y, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 3) = (Base::Quantity(FirstPoint.getValue().z, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);

		}
        else if (QString::fromLatin1(Directions.getValueAsString()) == QString::fromLatin1("Y")) {
            //dLocCoord(loop, 0) = loop + 1;		
            //dLocCoord(loop, 1) = FirstPoint.getValue().x;
            //dLocCoord(loop, 2) = FirstPoint.getValue().y + loop * Spacing.getValue();
            //dLocCoord(loop, 3) = FirstPoint.getValue().z;
       dLocCoord(loop, 0) = loop + 1;		
	   dLocCoord(loop, 1) = (Base::Quantity(FirstPoint.getValue().x, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 2) = (Base::Quantity(FirstPoint.getValue().y, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre) + loop * Spacing.getQuantityValue().getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 3) = (Base::Quantity(FirstPoint.getValue().z, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);

        }
        else if (QString::fromLatin1(Directions.getValueAsString()) == QString::fromLatin1("Z")) {
           /* dLocCoord(loop, 0) = loop + 1;		
            dLocCoord(loop, 1) = FirstPoint.getValue().x;
            dLocCoord(loop, 2) = FirstPoint.getValue().y;
            dLocCoord(loop, 3) = FirstPoint.getValue().z + loop * Spacing.getValue();*/
       dLocCoord(loop, 0) = loop + 1;		
	   dLocCoord(loop, 1) = (Base::Quantity(FirstPoint.getValue().x, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 2) = (Base::Quantity(FirstPoint.getValue().y, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 3) = (Base::Quantity(FirstPoint.getValue().z, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre) + loop * Spacing.getQuantityValue().getValueAs(Base::Quantity::Metre);

        }
	}

	return true;	
}


bool WLUniformDistributionLocations::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
	
	WindLabGui::UniformLocationDistributionDialogEdit* dlg = new WindLabGui::UniformLocationDistributionDialogEdit(FirstPoint, Spacing,Data.spatialDistribution, Directions);
    Gui::Control().showDialog(dlg);

	return true;
}
