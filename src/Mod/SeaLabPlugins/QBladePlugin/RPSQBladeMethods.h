
#ifndef SEALAB_PLUGIN_QBLADE_SIMUMETHOD_H
#define SEALAB_PLUGIN_QBLADE_SIMUMETHOD_H

#include <Mod/SeaLabAPI/App/IrpsSeLSimulationMethod.h>
#include <App/PropertyUnits.h>


namespace SeaLab {

class CRPSQBladeMethods: public SeaLabAPI::IrpsSeLSimulationMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CRPSQBladeMethods);

public:
    CRPSQBladeMethods();

    ~CRPSQBladeMethods() {};

	//Initial setting
	bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

	// The simulation function 
    bool Simulate(const SeaLabAPI::SeaLabSimulationData& Data, cube& dPhenomenon);

	// The simulation function in large scale mode 
    bool SimulateInLargeScaleMode(const SeaLabAPI::SeaLabSimulationData& Data, QString &strFileName);

    //virtual void onChanged(const App::Property* prop);

public:

    App::PropertyTime TimeOffset;
    App::PropertyEnumeration WaveGeneratorType;
    App::PropertyFrequency LowCutOff;
    App::PropertyFrequency HighCutOff;
    App::PropertyFrequency SignalSamplingRate;
    App::PropertyLength AmplitudeThreshold;
    //App::PropertyEnumeration SpectrumType;
    App::PropertyLength SignificantWaveHeight;
    App::PropertyLength SignificantWaveAmplitude;
    App::PropertyTime PeakPeriod;
    App::PropertyFrequency PeakFrequency;
    App::PropertyEnumeration SpectralPeaks;
    App::PropertyBool AutomaticGamma;
    App::PropertyBool AutomaticSigma;
    App::PropertyFloat Gamma;
    App::PropertyFloat Sigma1;
    App::PropertyFloat Sigma2;
    App::PropertyBool AutomaticOchiHubbleParameters;
    App::PropertyFloat SignificantWaveHeight1;
    App::PropertyFloat SignificantWaveHeight2;
    App::PropertyFrequency PeakFrequency1;
    App::PropertyFrequency PeakFrequency2;
    App::PropertyFloat PeakShape1;
    App::PropertyFloat PeakShape2;
    App::PropertyEnumeration DiscretizationMethod;
    App::PropertyBool AutomaticFrequencyRange;
    App::PropertyFrequency CutInFrequency;
    App::PropertyFrequency CutOutFrequency;
    App::PropertyFrequency MaximumBinWidth;
    App::PropertyInteger NumberOfFrequencyBins;
    App::PropertyInteger RandomPhaseSeed;
    App::PropertyEnumeration Directionality;
    App::PropertyAngle PrincipalWaveDirection;
    App::PropertyAngle MaximumSpread;
    App::PropertyTime SpreadingExponent;
    App::PropertyInteger NumberOfDirectionalBins;

    App::PropertyLength Width;
    App::PropertyLength Length;
    App::PropertyInteger WidthGridNumber;
    App::PropertyInteger LengthGridNumber;
    App::PropertyLength WaterDepth;
    App::PropertyAcceleration Gravity;
    App::PropertyTime AminationTime;
    App::PropertyTime AnimationTimeIncrement;
    App::PropertyTime AnimationFrameDelay;
    App::PropertyBool Animate;
    App::PropertyEnumeration RequestedVariable;
};

} // namespace App

#endif // WINDLAB_PLUGIN_SIMUMETHOD_H