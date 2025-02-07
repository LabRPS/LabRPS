
#ifndef SEALAB_PLUGIN_Hasselmann_PSD_H
#define SEALAB_PLUGIN_Hasselmann_PSD_H

#include <Mod/SeaLabAPI/App/IrpsSeLDirectionalSpreadingFunction.h>
#include <App/PropertyUnits.h>


namespace SeaLab {

class CRPSHasselmannDirectionalSpreadingFunction: public SeaLabAPI::IrpsSeLDirectionalSpreadingFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSHasselmannDirectionalSpreadingFunction);
public:
	CRPSHasselmannDirectionalSpreadingFunction();
	
	~CRPSHasselmannDirectionalSpreadingFunction() {};

    bool ComputeDirectionalSpreadingFunctionValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dfrequency, const double &dDirection, double &dValue);
    
    bool ComputeDirectionalSpreadingFunctionVectorF(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dDirection, vec &dVarVector, vec &dValVector);

    bool ComputeDirectionalSpreadingFunctionVectorP(const SeaLabAPI::SeaLabSimulationData& Data, const double &dfrequency, const double &dDirection, vec &dVarVector, vec &dValVector);

    bool ComputeDirectionalSpreadingFunctionVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dfrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

public:

   App::PropertyFrequency ModalFrequency;
   App::PropertySpeed MeanWindSpeed;
   App::PropertySpeed WaveCelerity;
};

} // namespace App

#endif// SEALAB_PLUGIN_Hasselmann_PSD_H