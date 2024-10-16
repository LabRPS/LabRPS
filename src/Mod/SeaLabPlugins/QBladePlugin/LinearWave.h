/**********************************************************************

    Copyright (C) 2020 David Marten <david.marten@qblade.org>

    This program is licensed under the Academic Public License
    (APL) v1.0; You can use, redistribute and/or modify it in
    non-commercial academic environments under the terms of the
    APL as published by the QBlade project; See the file 'LICENSE'
    for details; Commercial use requires a commercial license
    (contact info@qblade.org).

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

***********************************************************************/

#ifndef LINEARWAVE_H
#define LINEARWAVE_H
#include <Base/Vector3D.h>
#include <QVector>
#include <QStringList>
#include <QList>
#include <App/PropertyUnits.h>
#include <Mod/SeaLabAPI/App/RPSSeaLabFramework.h>

namespace SeaLab {
class LinearWave 
{
public:

    struct waveTrain{
        float phase = 0;
        float omega = 0;
        float direction = 0;
        float amplitude = 0;
        float wavenumber = 0;
        float cosfDIR = 0;
        float sinfDIR = 0;
        float A_omega = 0;
        float A_omega2 = 0;

        bool operator<(const waveTrain& a) const
        {
            return omega < a.omega;
        }
    };

    LinearWave(
        const SeaLabAPI::SeaLabSimulationData& Data, 
        const App::PropertyTime& TimeOffset, const App::PropertyEnumeration& WaveGeneratorType,
        const App::PropertyFrequency& LowCutOff, const App::PropertyFrequency& HighCutOff,
        const App::PropertyFrequency& SignalSamplingRate,
        const App::PropertyLength& AmplitudeThreshold,/* const App::PropertyEnumeration& SpectrumType,*/
        const App::PropertyLength& SignificantWaveHeight,
        const App::PropertyLength& SignificantWaveAmplitude,
        const App::PropertyTime& PeakPeriod, const App::PropertyFrequency& PeakFrequency,
        const App::PropertyEnumeration& SpectralPeaks, const App::PropertyBool& AutomaticGamma,
        const App::PropertyBool& AutomaticSigma, const App::PropertyFloat& Gamma,
        const App::PropertyFloat& Sigma1, const App::PropertyFloat& Sigma2,
        const App::PropertyBool& AutomaticOchiHubbleParameters,
        const App::PropertyFloat& SignificantWaveHeight1,
        const App::PropertyFloat& SignificantWaveHeight2,
        const App::PropertyFrequency& PeakFrequency1, const App::PropertyFrequency& PeakFrequency2,
        const App::PropertyFloat& PeakShape1, const App::PropertyFloat& PeakShape2,
        const App::PropertyEnumeration& DiscretizationMethod,
        const App::PropertyBool& AutomaticFrequencyRange,
        const App::PropertyFrequency& CutInFrequency, const App::PropertyFrequency& CutOutFrequency,
        const App::PropertyFrequency& MaximumBinWidth,
        const App::PropertyInteger& NumberOfFrequencyBins,
        const App::PropertyInteger& RandomPhaseSeed, const App::PropertyEnumeration& Directionality,
        const App::PropertyAngle& PrincipalWaveDirection, const App::PropertyAngle& MaximumSpread,
        const App::PropertyTime& SpreadingExponent,
        const App::PropertyInteger& NumberOfDirectionalBins, App::PropertyLength& Width,
        const App::PropertyLength& Length, const App::PropertyInteger& WidthGridNumber,
        const App::PropertyInteger& LengthGridNumber, const App::PropertyLength& WaterDepth,
        const App::PropertyAcceleration& Gravity, const App::PropertyTime& AminationTime,
        const App::PropertyTime& AnimationTimeIncrement,
        const App::PropertyTime& AnimationFrameDelay, const App::PropertyBool& Animate
    );
    ~LinearWave();

    float DFT_cutIn, DFT_cutOut, DFT_sample, DFT_thresh;
    float Hs, Tp;
    float timeoffset;
    float dir_mean;
    float dir_max;
    float s;
    float f_start, f_end;
    float d_fMax;
    float sigma1, sigma2, gamma;
    float lambda1, lambda2, f1, f2, Hs1, Hs2;
    bool autoOchi, doublePeak;
    double globalLineAlpha;

    int discF;
    int discDir;
    int seed;
    int S_frequency;
    int S_directional;
    int S_discretization;

    bool dispersionPrescribed;
    bool autoSigma, autoGamma, autoFrequency;

    QStringList waveComponentsFile;
    QString waveComponentsFileName;

    QStringList waveTimeseriesFile;
    QString waveTimeseriesFileName;

    QStringList spectrumFile;
    QString spectrumFileName;
    QList<QList<double>> spectrumData;

    QVector< QVector <float> > m_VariableData;
    QStringList m_availableVariables;

    QVector<waveTrain> waveTrains;
    const SeaLabAPI::SeaLabSimulationData& m_Data;
    mat randomPhases;
    int locationIndex;

    void GenerateWaveTrains();
    void DiscretizeDirectionalSpectrum(int num_directions, double dir_mean, double dir_max, double s);
    void DiscretizeFrequencySpectrum
        (int seed, int num_f, int num_dir, double df_max, double Hs, double Tp, bool auto_f_range=true, bool auto_gamma=true,
         bool auto_sigma=true, double f_cutIn=0, double f_cutOut=0, double gamma=0, double sigma1=0, double sigma2=0);

    double S_JONSWAP(double f, double Hs, double Tp, bool autoGamma=true, bool autoSigma=true, double gamma=0, double sigma1=0, double sigma2=0);
    double S_TORSETHAUGEN(double f, double Hs, double Tp, bool autoGamma, bool autoSigma, double gamma, double sigma1, double sigma2, bool isDouble);
    double S_ORCHIHUBBLE(double f);
    double S_DIRECTIONAL(double dir, double dir_mean, double dir_max, double s);
    double S_CUSTOM(double f);

    void Copy(LinearWave *wave);
    void CalculateDispersion(double gravity, double depth);
    double GetElevation(Base::Vector3d pos, float time);
    void SampleTimeseries(float &dt, QVector<float> &elevation);
    QVector<float> GetElevationPerDirection(Base::Vector3d pos, float time, QVector<float> &waveDir, double deltaDir);
    void GetVelocityAndAcceleration(Base::Vector3d pos, float time, float elevation = 0, float depth = 100, int stretchingType = 0, Base::Vector3d *Vel = NULL, Base::Vector3d *Acc = NULL, float *dynP = NULL, int isFuchs = 0, float dia = 0);
    void GLRenderSurfaceElevation(Base::Vector3d centerPos, float time, float width, float length, int discW, int discL, int GlList, bool showGrid = true, bool showSurface = true, bool showGround = false, double opacity = 0.7, double groundOpacity = 1.0, double depth = 0);
    void PrepareGraphData(double start, double end, double delta, double depth);

    double GetPhaseMCFPhaseShift(double x);

    const double ratio[95] = {0.314159,0.320571,0.327249,0.334212,0.341477,0.349066,0.356999,0.365301,0.373999,0.383121,0.392699,0.402768,0.413367,0.42454,0.436332,0.448799,0.461999,0.475999,0.490874,0.506708,0.523599,0.541654,
                               0.560999,0.581776,0.604152,0.628319,0.654498,0.682955,0.713998,0.747998,0.785398,0.826735,0.872665,0.923998,0.981748,1.047198,1.121997,1.208305,1.308997,1.427997,1.570796,1.745329,1.963495,2.243995,
                               2.617994,3.141593,3.205707,3.272492,3.34212,3.414775,3.490659,3.569992,3.653015,3.739991,3.831211,3.926991,4.027683,4.133675,4.245395,4.363323,4.48799,4.619989,4.759989,4.908739,5.067085,5.235988,
                               5.416539,5.609987,5.817764,6.041524,6.283185,6.544985,6.829549,7.139983,7.479983,7.853982,8.267349,8.726646,9.239978,9.817477,10.47198,11.21997,12.08305,13.08997,14.27997,15.70796,17.45329,19.63495,
                               22.43995,26.17994,31.41593,39.26991,52.35988,78.53982,157.0796};


    const double phase[95] = {-443.14,-431.77,-420.39,-409.03,-397.66,-386.31,-374.96,-363.61,-352.27,-340.94,-329.62,-318.3,-306.99,-295.7,-284.21,-273.13,-261.87,-250.62,-239.38,-228.16,-216.97,-205.78,-194.62,-183.48,-173.03,
                               -161.95,-150.91,-139.91,-128.95,-118.05,-107.20,-96.43,-85.74,-75.17,-64.67,-54.34,-44.10,-34.26,-24.62,-15.33,-6.53,1.61,8.86,14.83,18.97,20.54,20.52,20.47,20.39,20.26,20.10,19.91,19.68,19.41,19.11,
                               18.77,18.39,17.98,17.54,17.07,16.56,16.03,15.47,14.48,14.27,13.64,13.00,12.34,11.67,11.00,10.32,9.64,8.96,8.29,7.63,6.98,6.35,5.74,5.15,4.59,4.05,3.54,3.06,2.61,2.20,1.82,1.47,1.16,0.89,0.65,0.45,
                               0.29,0.16,0.07,0.02};

    const int arrLength = 95;

};

#endif // LINEARWAVE_H
}