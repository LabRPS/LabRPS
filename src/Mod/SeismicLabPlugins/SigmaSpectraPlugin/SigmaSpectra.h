#ifndef SigmaSpectraPlugin_H
#define SigmaSpectraPlugin_H

#include <Mod/SeismicLabAPI/App/IrpsSLTableTool.h>
#include <App/PropertyUnits.h>
#include <App/PropertyFile.h>

namespace SeismicLab
{
class SigmaSpectra: public SeismicLabAPI::IrpsSLTableTool
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::SigmaSpectra);

public:
SigmaSpectra();
~SigmaSpectra() {};
bool TableToolCompute(const SeismicLabAPI::SeismicLabSimulationData& Data, const mat& inputTable, mat& outputTable);
bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);
void onChanged(const App::Property* prop) override;

public:

 App::PropertyInteger NumberOfDataPoints;
 App::PropertyTime TimeIncrement;
 App::PropertyFile FilePath;
 App::PropertyAcceleration PeakGroundAcceleration;
 App::PropertySpeed PeakGroundVelocity;
 App::PropertyLength PeackGroundDisplacement;
  App::PropertyString Details;
 App::PropertyString ComponentDirectionAizmuth;
 App::PropertySpeed AriasIntensity;
 App::PropertyTime FiveToSeventyFiveAriasIntensityDuration;
 App::PropertyTime FiveToNinetyFiveAriasIntensityDuration;



   //! Arias intensity of the motion
 double m_ariasInt;

 //! Durations
 //@{
 //! 5 to 75 percent of the Arias intensity
 double m_dur5_75;
 //! 5 to 95 percent of the Arias intensity
 double m_dur5_95;

};

}// namespace SeismicLab

#endif// SigmaSpectraPlugin_H