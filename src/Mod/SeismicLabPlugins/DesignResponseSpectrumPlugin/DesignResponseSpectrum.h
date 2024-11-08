#ifndef DesignResponseSpectrumPlugin_H
#define DesignResponseSpectrumPlugin_H

#include <Mod/SeismicLabAPI/App/IrpsSLTableTool.h>
#include <App/PropertyUnits.h>
#include <Mod/SeismicLabTools/App/ResponseSpectrum/DesignResponseSpectrum.h>


namespace SeismicLab
{
class DesignResponseSpectrum: public SeismicLabAPI::IrpsSLTableTool
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::DesignResponseSpectrum);

public:
DesignResponseSpectrum();
~DesignResponseSpectrum() {};
bool TableToolCompute(const SeismicLabAPI::SeismicLabSimulationData& Data, const mat& inputTable, mat& outputTable);
bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

double computeResponseSpectrum(double time, SeismicLabTools::DesignResponseSpectrum designResponseSpectrum);

void onChanged(const App::Property* prop) override;

void hideAllParameter();
void showEurocode8Parameter();

public:

 //Eurocode 8
 App::PropertyEnumeration DesignCode;
 App::PropertyEnumeration SpacialComponent;
 App::PropertyEnumeration Elasticity;
 App::PropertyEnumeration NationalAnnex;
 App::PropertyPercent DampingRatio;
 App::PropertyFloat ReferencePeakGroundAcceleration;
 App::PropertyEnumeration SpectrumType;
 App::PropertyEnumeration SoilType;
 App::PropertyEnumeration ImportanceClass;
 App::PropertyFloat BehaviorFactor;
 App::PropertyFloat LowerBoundFactor;

};

}// namespace SeismicLab

#endif// DesignResponseSpectrumPlugin_H