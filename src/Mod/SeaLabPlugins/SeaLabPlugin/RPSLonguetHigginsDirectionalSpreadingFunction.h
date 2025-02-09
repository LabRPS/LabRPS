
#ifndef SEALAB_PLUGIN_LonguetHiggins_PSD_H
#define SEALAB_PLUGIN_LonguetHiggins_PSD_H

#include <Mod/SeaLabAPI/App/IrpsSeLDirectionalSpreadingFunction.h>
#include <App/PropertyUnits.h>


namespace SeaLab {

class CRPSLonguetHigginsDirectionalSpreadingFunction: public SeaLabAPI::IrpsSeLDirectionalSpreadingFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSLonguetHigginsDirectionalSpreadingFunction);
public:
	CRPSLonguetHigginsDirectionalSpreadingFunction();
	
	~CRPSLonguetHigginsDirectionalSpreadingFunction() {};

    bool ComputeDirectionalSpreadingFunctionValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dfrequency, const double &dDirection, double &dValue);
    
    bool ComputeDirectionalSpreadingFunctionVectorF(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dDirection, vec &dVarVector, vec &dValVector);

    bool ComputeDirectionalSpreadingFunctionVectorP(const SeaLabAPI::SeaLabSimulationData& Data, const double &dfrequency, const double &dDirection, vec &dVarVector, vec &dValVector);

    bool ComputeDirectionalSpreadingFunctionVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dfrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

public:

   App::PropertyFrequency PeakFrequency;
   App::PropertySpeed TenMeterHeightMeanWindSpeed;
   App::PropertyAngle MainDirection;
};

} // namespace App

#endif// SEALAB_PLUGIN_LonguetHiggins_PSD_H