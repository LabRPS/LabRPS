#include "PreCompiled.h"
#include "WLHorizontalUniformDistribution.h"
#include <QMessageBox>
#include "widgets/DlgHorizontalLocationDistribution.h"
#include <Gui/Control.h>


using namespace WindLab;

////////////////////////Horizontal distribution///////////////////////////////////////////////

PROPERTY_SOURCE(WindLab::CWLHorizontalUniformDistribution, WindLabAPI::WindLabFeatureLocationDistribution)

CWLHorizontalUniformDistribution::CWLHorizontalUniformDistribution()
{

	static const char* locationgroup = "Distribution";

    ADD_PROPERTY_TYPE(FirstPoint, (Base::Vector3d(0,0,40000)), locationgroup, App::Prop_None, "the first point the distribution will start from");

    ADD_PROPERTY_TYPE(Spacing, (5000.0), locationgroup, App::Prop_None, "The even spacing between the points");
}


bool CWLHorizontalUniformDistribution::ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord)
{
	// Computing the location coordinates
	for (int loop = 0; loop < Data.numberOfSpatialPosition.getValue(); loop++)
	{
		//dLocCoord(loop, 0) = loop + 1;		
		//dLocCoord(loop, 1) = FirstPoint.getValue().x + loop * Spacing.getValue();
		//dLocCoord(loop, 2) = FirstPoint.getValue().y;
		//dLocCoord(loop, 3) = FirstPoint.getValue().z;

	   dLocCoord(loop, 0) = loop + 1;		
	   dLocCoord(loop, 1)  = (Base::Quantity(FirstPoint.getValue().x, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre) +  loop * Spacing.getQuantityValue().getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 2) = (Base::Quantity(FirstPoint.getValue().y, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);
       dLocCoord(loop, 3) = (Base::Quantity(FirstPoint.getValue().z, FirstPoint.getUnit())).getValueAs(Base::Quantity::Metre);

	   //double haha = FirstPoint.getValue().x + loop * Spacing.getValue();
    //   Base::Quantity q = Base::Quantity(haha, Base::Unit::Length);
    //   QString st = q.getUserString();
    //   int a = 0;

	}

	return true;	
}


bool CWLHorizontalUniformDistribution::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
	WindLabGui::HorizontalLocationDistributionDialogEdit* dlg = new WindLabGui::HorizontalLocationDistributionDialogEdit(FirstPoint, Spacing,Data.spatialDistribution);
    Gui::Control().showDialog(dlg);

	return true;
}
