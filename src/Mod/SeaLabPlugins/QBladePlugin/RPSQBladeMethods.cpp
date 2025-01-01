

#include "RPSQBladeMethods.h"
#include <Mod/SeaLabAPI/App/RPSSeaLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Base/Console.h>
#include "LinearWave.h"

#include <QMessageBox>
#include <QThread>
#include <fstream>
#include "Globals.h"

using namespace SeaLab;
using namespace SeaLabAPI;

PROPERTY_SOURCE(SeaLab::CRPSQBladeMethods, SeaLabAPI::SeaLabFeatureSimulationMethod)

CRPSQBladeMethods::CRPSQBladeMethods()
{
    ADD_PROPERTY_TYPE(TimeOffset, (0.0), "Parameter", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(WaveGeneratorType, ((long int)3), "Parameter", App::Prop_None, "Parameter");
    static const char* someEnums[] = {"Times Series From File", "Components From File", "Single Wave", "JONSWAP", "ISSC", "TORSETHAUGEN", "OCHI-HUBBLE", nullptr};
    WaveGeneratorType.setEnums(someEnums);

    ADD_PROPERTY_TYPE(LowCutOff, (0.02), "Timeseries Conversion Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(HighCutOff, (0.7), "Timeseries Conversion Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(SignalSamplingRate, (20), "Timeseries Conversion Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(AmplitudeThreshold, (0.001), "Timeseries Conversion Parameters", App::Prop_None, "Parameter");
    
    ADD_PROPERTY_TYPE(SignificantWaveHeight, (8.1), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(SignificantWaveAmplitude, (4.05), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(PeakPeriod, (12.7), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(PeakFrequency, (0.0787), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(SpectralPeaks, ((long int)2), "Main Seastate Parameters", App::Prop_None, "Parameter");
    static const char* spectralPeaks[] = {"Single Peak", "Double Peak", nullptr};
    SpectralPeaks.setEnums(spectralPeaks);
    
    ADD_PROPERTY_TYPE(AutomaticGamma, (true), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(AutomaticSigma, (true), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(Gamma, (1.0), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(Sigma1, (0.07), "Main Seastate Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(Sigma2, (0.09), "Main Seastate Parameters", App::Prop_None, "Parameter");

    ADD_PROPERTY_TYPE(AutomaticOchiHubbleParameters, (true), "Automatic Ochi-Hubble Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(SignificantWaveHeight1, (6.804), "Automatic Ochi-Hubble Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(SignificantWaveHeight2, (4.374), "Automatic Ochi-Hubble Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(PeakFrequency1, (0.077), "Automatic Ochi-Hubble Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(PeakFrequency2, (0.133), "Automatic Ochi-Hubble Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(PeakShape1, (3.0), "Automatic Ochi-Hubble Parameters", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(PeakShape2, (0.932), "Automatic Ochi-Hubble Parameters", App::Prop_None, "Parameter");

    ADD_PROPERTY_TYPE(DiscretizationMethod, ((long int)1), "Frequency Discretization", App::Prop_None, "Parameter");
    static const char* discretizationMethods[] = {"Equal Energy", "Equal Frequency", nullptr};
    DiscretizationMethod.setEnums(discretizationMethods);
    ADD_PROPERTY_TYPE(AutomaticFrequencyRange, (true), "Frequency Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(CutInFrequency, (0.039), "Frequency Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(CutOutFrequency, (0.787), "Frequency Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(MaximumBinWidth, (0.05), "Frequency Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(NumberOfFrequencyBins, (320), "Frequency Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(RandomPhaseSeed, (65535), "Frequency Discretization", App::Prop_None, "Parameter");

    ADD_PROPERTY_TYPE(Directionality, ((long int)1), "Equal Energy Directional Discretization", App::Prop_None, "Parameter");
    static const char* directionalities[] = {"Single Dir", "Cos Spread", nullptr};
    Directionality.setEnums(directionalities);
    ADD_PROPERTY_TYPE(PrincipalWaveDirection, (0.0), "Equal Energy Directional Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(MaximumSpread, (50.0), "Equal Energy Directional Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(SpreadingExponent, (5.0), "Equal Energy Directional Discretization", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(NumberOfDirectionalBins, (12), "Equal Energy Directional Discretization", App::Prop_None, "Parameter");

    ADD_PROPERTY_TYPE(Width, (400000), "Points Grid", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(Length, (400000), "Points Grid", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(WidthGridNumber, (50), "Points Grid", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(LengthGridNumber, (40), "Points Grid", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(WaterDepth, (200000), "Points Grid", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(Gravity, (810), "Points Grid", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(AminationTime, (305457.070), "Animation", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(AnimationTimeIncrement, (0.1), "Animation", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(AnimationFrameDelay, (0.001), "Animation", App::Prop_None, "Parameter");
    ADD_PROPERTY_TYPE(Animate, (false), "Animation", App::Prop_None, "Parameter");
   
    ADD_PROPERTY_TYPE(RequestedVariable, ((long int)0), "Computed Variable", App::Prop_None, "Parameter");
    static const char* requestedVariables[] = {"Wave Elevation", "Wave MSL Velocity x", "Wave MSL Velocity y", "Wave MSL Velocity z", "Wave MSL Acceleration x", "Wave MSL Acceleration y", "Wave MSL Acceleration z", nullptr};
    RequestedVariable.setEnums(requestedVariables);
}

bool CRPSQBladeMethods::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
    QMessageBox::warning(0,QString::fromLatin1("QBlade Method"), QString::fromLatin1("No additional data required."));
    return true;
}

bool CRPSQBladeMethods::Simulate(const SeaLabAPI::SeaLabSimulationData& Data, cube& dPhenomenon)
{

    if (Data.largeScaleSimulationMode.getValue()) {
        Base::Console().Error("The simulation fails.\n");
        return false;
    }

    LinearWave* linearWave = new LinearWave(
        Data,
        TimeOffset, WaveGeneratorType,
        LowCutOff, HighCutOff,
        SignalSamplingRate,
        AmplitudeThreshold, /*SpectrumType,*/
        SignificantWaveHeight,
        SignificantWaveAmplitude, PeakPeriod,
        PeakFrequency, SpectralPeaks,
        AutomaticGamma, AutomaticSigma,
        Gamma, Sigma1,
        Sigma2, AutomaticOchiHubbleParameters,
        SignificantWaveHeight1,
        SignificantWaveHeight2,
        PeakFrequency1, PeakFrequency2,
        PeakShape1, PeakShape2,
        DiscretizationMethod,
        AutomaticFrequencyRange,
        CutInFrequency, CutOutFrequency,
        MaximumBinWidth,
        NumberOfFrequencyBins,
        RandomPhaseSeed, Directionality,
        PrincipalWaveDirection, MaximumSpread,
        SpreadingExponent, NumberOfDirectionalBins,
        Width, Length,
        WidthGridNumber, LengthGridNumber,
        WaterDepth, Gravity,
        AminationTime,
        AnimationTimeIncrement,
        AnimationFrameDelay, Animate
    );
    
    
double sampleN = Data.numberOfSample.getValue();

mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);
bool returnResult = SeaLabAPI::CRPSSeaLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
if (!returnResult)
{
   Base::Console().Warning("The computation of the location coordinates has failed.\n");
   return returnResult;
}
for (int ss = 1; ss <= sampleN && false == Data.isInterruptionRequested.getValue(); ss++) {
// generate n sequences of random phase angles phi(l), l = 1, 2, ..., N
linearWave->randomPhases.resize(linearWave->discF, Data.numberOfSpatialPosition.getValue());
returnResult = SeaLabAPI::CRPSSeaLabFramework::GenerateRandomMatrixFP(Data, linearWave->randomPhases);
if (!returnResult) {
    Base::Console().Warning("The computation of the random phases has failed.\n");
    return returnResult;
}

    if (RequestedVariable.getValue() == 0) {

        double time = 0.0;

        for (int i = 0; i < Data.numberOfSpatialPosition.getValue(); i++) {
            linearWave->locationIndex = i;
            linearWave->GenerateWaveTrains();
            linearWave->CalculateDispersion(
                Gravity.getValue(),
                PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Second));

            for (int j = 0; j < Data.numberOfTimeIncrements.getValue(); j++) {
                time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                    + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                dPhenomenon(j, 0, ss - 1) = time;
                dPhenomenon(j, i + 1, ss - 1) = linearWave->GetElevation(
                    Base::Vector3d(dLocCoord(i, 1), dLocCoord(i, 2), dLocCoord(i, 3)), time);
            }
        }
    }
    else if (RequestedVariable.getValue() == 1) {

        double time = 0.0;

        for (int i = 0; i < Data.numberOfSpatialPosition.getValue(); i++) {
            linearWave->locationIndex = i;
            linearWave->GenerateWaveTrains();
            linearWave->CalculateDispersion(
                Gravity.getValue(),
                PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Metre));

            for (int j = 0; j < Data.numberOfTimeIncrements.getValue(); j++) {
                time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                    + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                Base::Vector3d velocity(0, 0, 0);
                Base::Vector3d acceleration(0, 0, 0);
                linearWave->GetVelocityAndAcceleration(
                    Base::Vector3d(dLocCoord(i, 1), dLocCoord(i, 2), dLocCoord(i, 3)), time, 0,
                    WaterDepth.getQuantityValue().getValueAs(Base::Quantity::Metre), VERTICAL,
                    &velocity, &acceleration);
                dPhenomenon(j, 0, ss - 1) = time;
                dPhenomenon(j, i + 1, ss - 1) = velocity.x;
            }
        }
    }
    else if (RequestedVariable.getValue() == 2) {

        double time = 0.0;

        for (int i = 0; i < Data.numberOfSpatialPosition.getValue(); i++) {
            linearWave->locationIndex = i;
            linearWave->GenerateWaveTrains();
            linearWave->CalculateDispersion(
                Gravity.getValue(),
                PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Metre));

            for (int j = 0; j < Data.numberOfTimeIncrements.getValue(); j++) {
                time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                    + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                Base::Vector3d velocity(0, 0, 0);
                Base::Vector3d acceleration(0, 0, 0);
                linearWave->GetVelocityAndAcceleration(
                    Base::Vector3d(dLocCoord(i, 1), dLocCoord(i, 2), dLocCoord(i, 3)), time, 0,
                    WaterDepth.getQuantityValue().getValueAs(Base::Quantity::Metre), VERTICAL,
                    &velocity, &acceleration);
                dPhenomenon(j, 0, ss - 1) = time;
                dPhenomenon(j, i + 1, ss - 1) = velocity.y;
            }
        }
    }
    else if (RequestedVariable.getValue() == 3) {

        double time = 0.0;

        for (int i = 0; i < Data.numberOfSpatialPosition.getValue(); i++) {
            linearWave->locationIndex = i;
            linearWave->GenerateWaveTrains();
            linearWave->CalculateDispersion(
                Gravity.getValue(),
                PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Metre));

            for (int j = 0; j < Data.numberOfTimeIncrements.getValue(); j++) {
                time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                    + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                Base::Vector3d velocity(0, 0, 0);
                Base::Vector3d acceleration(0, 0, 0);
                linearWave->GetVelocityAndAcceleration(
                    Base::Vector3d(dLocCoord(i, 1), dLocCoord(i, 2), dLocCoord(i, 3)), time, 0,
                    WaterDepth.getQuantityValue().getValueAs(Base::Quantity::Metre), VERTICAL,
                    &velocity, &acceleration);
                dPhenomenon(j, 0, ss - 1) = time;
                dPhenomenon(j, i + 1, ss - 1) = velocity.z;
            }
        }
    }
    else if (RequestedVariable.getValue() == 4) {

        double time = 0.0;

        for (int i = 0; i < Data.numberOfSpatialPosition.getValue(); i++) {
            linearWave->locationIndex = i;
            linearWave->GenerateWaveTrains();
            linearWave->CalculateDispersion(
                Gravity.getValue(),
                PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Metre));

            for (int j = 0; j < Data.numberOfTimeIncrements.getValue(); j++) {
                time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                    + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                Base::Vector3d velocity(0, 0, 0);
                Base::Vector3d acceleration(0, 0, 0);
                linearWave->GetVelocityAndAcceleration(
                    Base::Vector3d(dLocCoord(i, 1), dLocCoord(i, 2), dLocCoord(i, 3)), time, 0,
                    WaterDepth.getQuantityValue().getValueAs(Base::Quantity::Metre), VERTICAL,
                    &velocity, &acceleration);
                dPhenomenon(j, 0, ss - 1) = time;
                dPhenomenon(j, i + 1, ss - 1) = acceleration.x;
            }
        }
    }
    else if (RequestedVariable.getValue() == 5) {

        double time = 0.0;

        for (int i = 0; i < Data.numberOfSpatialPosition.getValue(); i++) {
            linearWave->locationIndex = i;
            linearWave->GenerateWaveTrains();
            linearWave->CalculateDispersion(
                Gravity.getValue(),
                PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Metre));

            for (int j = 0; j < Data.numberOfTimeIncrements.getValue(); j++) {
                time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                    + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                Base::Vector3d velocity(0, 0, 0);
                Base::Vector3d acceleration(0, 0, 0);
                linearWave->GetVelocityAndAcceleration(
                    Base::Vector3d(dLocCoord(i, 1), dLocCoord(i, 2), dLocCoord(i, 3)), time, 0,
                    WaterDepth.getQuantityValue().getValueAs(Base::Quantity::Metre), VERTICAL,
                    &velocity, &acceleration);
                dPhenomenon(j, 0, ss - 1) = time;
                dPhenomenon(j, i + 1, ss - 1) = acceleration.y;
            }
        }
    }
    else if (RequestedVariable.getValue() == 6) {

        double time = 0.0;

        for (int i = 0; i < Data.numberOfSpatialPosition.getValue(); i++) {
            linearWave->locationIndex = i;
            linearWave->GenerateWaveTrains();
            linearWave->CalculateDispersion(
                Gravity.getValue(),
                PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Metre));

            for (int j = 0; j < Data.numberOfTimeIncrements.getValue(); j++) {
                time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second)
                    + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                Base::Vector3d velocity(0, 0, 0);
                Base::Vector3d acceleration(0, 0, 0);
                linearWave->GetVelocityAndAcceleration(
                    Base::Vector3d(dLocCoord(i, 1), dLocCoord(i, 2), dLocCoord(i, 3)), time, 0,
                    WaterDepth.getQuantityValue().getValueAs(Base::Quantity::Metre), VERTICAL,
                    &velocity, &acceleration);
                dPhenomenon(j, 0, ss - 1) = time;
                dPhenomenon(j, i + 1, ss - 1) = acceleration.z;
            }
        }
    }
}
   return true;
}

// The simulation function in large scale mode
bool CRPSQBladeMethods::SimulateInLargeScaleMode(const SeaLabAPI::SeaLabSimulationData& Data, QString &strFileName)
{
    if (!Data.largeScaleSimulationMode.getValue()) {
        Base::Console().Error("The simulation fails.\n");
        return false;
    }
    return false;
}