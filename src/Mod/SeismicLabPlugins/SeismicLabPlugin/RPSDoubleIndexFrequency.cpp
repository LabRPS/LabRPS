

#include "RPSDoubleIndexFrequency.h"
#include <QMessageBox>
#include "Widgets/RPSFrequencyDistributionDialog.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::CRPSDoubleIndexFrequency, SeismicLabAPI::SeismicLabFeatureFrequencyDistribution)

CRPSDoubleIndexFrequency::CRPSDoubleIndexFrequency() {

}

bool CRPSDoubleIndexFrequency::ComputeFrequenciesVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, vec &dValVector)
{
	for (int l = 0; l < Data.numberOfFrequency.getValue(); l++)
	{
        ComputeFrequencyValue(Data, location, l, dValVector(l));
	}

	return true;
}

bool CRPSDoubleIndexFrequency::ComputeFrequenciesMatrixFP(const SeismicLabAPI::SeismicLabSimulationData &Data, mat &dMatrix)
{
    mat locationCoord(Data.numberOfSpatialPosition.getValue(), 4);

    bool returnResult = CRPSSeismicLabFramework::ComputeLocationCoordinateMatrixP3(Data, locationCoord);

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


bool CRPSDoubleIndexFrequency::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    // the input diolag
    std::unique_ptr<RPSFrequencyDistributionDialog> dlg(new RPSFrequencyDistributionDialog(2));

    if (dlg->exec() == QDialog::Accepted) //
    {

    }

    return true;
}

bool CRPSDoubleIndexFrequency::ComputeFrequencyValue(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &location, const int &frequencyIndex, double &dValue)
{
    mat locationCoord(Data.numberOfSpatialPosition.getValue(), 4);

    CRPSSeismicLabFramework::ComputeLocationCoordinateMatrixP3(Data,locationCoord);

    int locationIndex = CRPSSeismicLabFramework::getLocationIndex(Data, location);

    if (locationIndex < 0 || locationIndex > Data.numberOfSpatialPosition.getValue())
    {
        return false;
    }

    dValue = Data.minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond) + frequencyIndex * Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond) + (locationIndex + 1)*Data.frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond) / Data.numberOfSpatialPosition.getValue();

    return true;
}

