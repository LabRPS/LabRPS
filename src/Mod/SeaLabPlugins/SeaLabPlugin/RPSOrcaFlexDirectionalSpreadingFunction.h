
#ifndef SEALAB_PLUGIN_OrcaFlex_PSD_H
#define SEALAB_PLUGIN_OrcaFlex_PSD_H

#include <Mod/SeaLabAPI/App/IrpsSeLDirectionalSpreadingFunction.h>
#include <App/PropertyUnits.h>


namespace SeaLab {

class CRPSOrcaFlexDirectionalSpreadingFunction: public SeaLabAPI::IrpsSeLDirectionalSpreadingFunction
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSOrcaFlexDirectionalSpreadingFunction);
public:
	CRPSOrcaFlexDirectionalSpreadingFunction();
	
	~CRPSOrcaFlexDirectionalSpreadingFunction() {};

    bool ComputeDirectionalSpreadingFunctionValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dfrequency, const double &dDirection, double &dValue);
    
    bool ComputeDirectionalSpreadingFunctionVectorF(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dDirection, vec &dVarVector, vec &dValVector);

    bool ComputeDirectionalSpreadingFunctionVectorP(const SeaLabAPI::SeaLabSimulationData& Data, const double &dfrequency, const double &dDirection, vec &dVarVector, vec &dValVector);

    bool ComputeDirectionalSpreadingFunctionVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dfrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

public:

   App::PropertyAngle PrincipalWaveDirection;
   App::PropertyFloat SpreadingExponent;
};

} // namespace App

#endif// SEALAB_PLUGIN_OrcaFlex_PSD_H