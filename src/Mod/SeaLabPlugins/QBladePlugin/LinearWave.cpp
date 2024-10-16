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
#include "PreCompiled.h"
#ifdef RPS_OS_WIN32
#define NOMINMAX
#include <windows.h>
#endif
#include "LinearWave.h"
#include <math.h>
#include <QDebug>
//#include <GL/gl.h>
#include "Globals.h"
#include "Params.h"
#include <random>
#include <algorithm>


using namespace SeaLab;

LinearWave::LinearWave(
    const SeaLabAPI::SeaLabSimulationData& Data, 
    const App::PropertyTime& TimeOffset, const App::PropertyEnumeration& WaveGeneratorType,
    const App::PropertyFrequency& LowCutOff, const App::PropertyFrequency& HighCutOff,
    const App::PropertyFrequency& SignalSamplingRate, const App::PropertyLength& AmplitudeThreshold,
    /*const App::PropertyEnumeration& SpectrumType, */const App::PropertyLength& SignificantWaveHeight,
    const App::PropertyLength& SignificantWaveAmplitude, const App::PropertyTime& PeakPeriod,
    const App::PropertyFrequency& PeakFrequency, const App::PropertyEnumeration& SpectralPeaks,
    const App::PropertyBool& AutomaticGamma, const App::PropertyBool& AutomaticSigma,
    const App::PropertyFloat& Gamma, const App::PropertyFloat& Sigma1,
    const App::PropertyFloat& Sigma2, const App::PropertyBool& AutomaticOchiHubbleParameters,
    const App::PropertyFloat& SignificantWaveHeight1,
    const App::PropertyFloat& SignificantWaveHeight2, const App::PropertyFrequency& PeakFrequency1,
    const App::PropertyFrequency& PeakFrequency2, const App::PropertyFloat& PeakShape1,
    const App::PropertyFloat& PeakShape2, const App::PropertyEnumeration& DiscretizationMethod,
    const App::PropertyBool& AutomaticFrequencyRange, const App::PropertyFrequency& CutInFrequency,
    const App::PropertyFrequency& CutOutFrequency, const App::PropertyFrequency& MaximumBinWidth,
    const App::PropertyInteger& NumberOfFrequencyBins, const App::PropertyInteger& RandomPhaseSeed,
    const App::PropertyEnumeration& Directionality,
    const App::PropertyAngle& PrincipalWaveDirection, const App::PropertyAngle& MaximumSpread,
    const App::PropertyTime& SpreadingExponent,
    const App::PropertyInteger& NumberOfDirectionalBins, App::PropertyLength& Width,
    const App::PropertyLength& Length, const App::PropertyInteger& WidthGridNumber,
    const App::PropertyInteger& LengthGridNumber, const App::PropertyLength& WaterDepth,
    const App::PropertyAcceleration& Gravity, const App::PropertyTime& AminationTime,
    const App::PropertyTime& AnimationTimeIncrement,
    const App::PropertyTime& AnimationFrameDelay, const App::PropertyBool& Animate)
    : m_Data(Data)
{
    S_frequency = WaveGeneratorType.getValue();
    S_directional = Directionality.getValue();
    autoGamma = AutomaticGamma.getValue();
    autoSigma = AutomaticSigma.getValue();
    autoOchi = AutomaticOchiHubbleParameters.getValue();
    
    if (SpectralPeaks.getValue() == 0)
        doublePeak = false;
    else if (SpectralPeaks.getValue() == 1)
        doublePeak = true;

    DFT_cutIn = LowCutOff.getQuantityValue().getValueAs(Base::Quantity::Hertz);
    DFT_cutOut = HighCutOff.getQuantityValue().getValueAs(Base::Quantity::Hertz);
    DFT_sample = SignalSamplingRate.getQuantityValue().getValueAs(Base::Quantity::Hertz);
    DFT_thresh = AmplitudeThreshold.getQuantityValue().getValueAs(Base::Quantity::Metre);
    Hs = SignificantWaveHeight.getQuantityValue().getValueAs(Base::Quantity::Metre);
    Tp = PeakPeriod.getQuantityValue().getValueAs(Base::Quantity::Second);
    dir_mean = PrincipalWaveDirection.getQuantityValue().getValueAs(Base::Quantity::Degree);
    dir_max = MaximumSpread.getQuantityValue().getValueAs(Base::Quantity::Degree);
    s = SpreadingExponent.getQuantityValue().getValueAs(Base::Quantity::Second);
    f_start = (1.0 / Tp * 0.5);
    f_end = (1.0 / Tp * 10.0);
    d_fMax = MaximumBinWidth.getQuantityValue().getValueAs(Base::Quantity::Hertz);
    discF = NumberOfFrequencyBins.getValue();
    discDir = NumberOfDirectionalBins.getValue();
    timeoffset = TimeOffset.getQuantityValue().getValueAs(Base::Quantity::Second);
    seed = RandomPhaseSeed.getValue();
    sigma1 = Sigma1.getValue();
    sigma2 = Sigma2.getValue();
    gamma = Gamma.getValue();
    S_discretization = DiscretizationMethod.getValue();
    locationIndex = 0;
}

void LinearWave::GenerateWaveTrains()
{

    waveTrains.clear();
    dispersionPrescribed = false;

    if (S_frequency == SINGLE){
        waveTrain singleTrain;
        singleTrain.omega = 1.0/Tp*2.0*PI_;
        singleTrain.phase = 0.0;
        singleTrain.amplitude = Hs / 2.0;
        singleTrain.A_omega = singleTrain.amplitude * singleTrain.omega;
        singleTrain.A_omega2 = singleTrain.amplitude * singleTrain.omega * singleTrain.omega;
        waveTrains.append(singleTrain);
    }
    else if (S_frequency == JONSWAP && Hs > 0){
        DiscretizeFrequencySpectrum(seed,discF,discDir,d_fMax,Hs,Tp,autoFrequency,autoGamma,autoSigma,f_start,f_end,gamma,sigma1,sigma2);
    }
    else if (S_frequency == ISSC && Hs > 0){
        DiscretizeFrequencySpectrum(seed,discF,discDir,d_fMax,Hs,Tp,autoFrequency,false,true,f_start,f_end,1.0);
    }
    else if (S_frequency == TORSETHAUGEN && Hs > 0){
        DiscretizeFrequencySpectrum(seed,discF,discDir,d_fMax,Hs,Tp,autoFrequency,autoGamma,autoSigma,f_start,f_end,gamma,sigma1,sigma2);
    }
    else if (S_frequency == OCHI_HUBBLE && Hs > 0){
        DiscretizeFrequencySpectrum(seed,discF,discDir,d_fMax,Hs,Tp,autoFrequency,autoGamma,autoSigma,f_start,f_end,gamma,sigma1,sigma2);
    }
    else if (S_frequency == IMP_SPECTRUM && Hs > 0){

       /* spectrumData = FindNumericValuesInFile(2, spectrumFile);
        DiscretizeFrequencySpectrum(seed,discF,discDir,d_fMax,Hs,Tp,autoFrequency,autoGamma,autoSigma,f_start,f_end,gamma,sigma1,sigma2);*/
    }
    else if (S_frequency == IMP_COMPONENTS){
        /*QList<QList<double>> trains = FindNumericValuesInFile(4, waveComponentsFile);

        dispersionPrescribed = true;
        for (int i=0;i<trains.size();i++){
            if (trains.at(i).size() < 5) dispersionPrescribed = false;
        }

        for (int i=0;i<trains.size();i++){
            waveTrain singleTrain;
            singleTrain.omega = trains.at(i).at(0)*2.0*PI_;
            singleTrain.amplitude = trains.at(i).at(1);
            singleTrain.phase = trains.at(i).at(2) / 180.0 * PI_;
            singleTrain.direction = trains.at(i).at(3) / 180.0 * PI_;
            if (dispersionPrescribed) singleTrain.wavenumber = trains.at(i).at(4);
            singleTrain.cosfDIR = cosf(singleTrain.direction);
            singleTrain.sinfDIR = sinf(singleTrain.direction);
            singleTrain.A_omega = singleTrain.amplitude * singleTrain.omega;
            singleTrain.A_omega2 = singleTrain.amplitude * singleTrain.omega * singleTrain.omega;
            waveTrains.append(singleTrain);
        }

        discF = waveTrains.size();*/
    }
    else if (S_frequency == IMP_TIMESERIES){

        /*QVector<float> elevation,frequencies,amplitudes,phases;
        float dT;

        SampleTimeseries(dT,elevation);

        CalculatePSD2(&elevation,frequencies,amplitudes,phases,dT);

        for (int i=0;i<frequencies.size();i++){
            if (frequencies.at(i) >= DFT_cutIn && frequencies.at(i) <= DFT_cutOut && amplitudes.at(i) >= DFT_thresh){
                waveTrain singleTrain;
                singleTrain.omega = frequencies.at(i)*2.0*PI_;
                singleTrain.amplitude = amplitudes.at(i);
                singleTrain.phase = phases.at(i)+PI_/2;
                singleTrain.direction = dir_mean;
                singleTrain.cosfDIR = cosf(singleTrain.direction);
                singleTrain.sinfDIR = sinf(singleTrain.direction);
                singleTrain.A_omega = singleTrain.amplitude * singleTrain.omega;
                singleTrain.A_omega2 = singleTrain.amplitude * singleTrain.omega * singleTrain.omega;
                waveTrains.append(singleTrain);
            }
        }

        discF = waveTrains.size();*/
    }

    if (S_frequency != IMP_COMPONENTS && S_frequency != IMP_TIMESERIES){
        if (S_frequency == SINGLE || S_directional == UNIDIRECTIONAL)
            DiscretizeDirectionalSpectrum(1,dir_mean,dir_max,s);
        else
            DiscretizeDirectionalSpectrum(discDir,dir_mean,dir_max,s);
    }


    std::sort(waveTrains.begin(), waveTrains.end());


}

void LinearWave::SampleTimeseries(float &dt, QVector<float> &elevation){

    //QList<QList<double>> timeseries = FindNumericValuesInFile(2, waveTimeseriesFile);
    //dt = 1.0/DFT_sample;
    //float min = timeseries.at(0).at(0);
    //float max = timeseries.at(timeseries.size()-1).at(0);
    //// decomposition of time signal
    ////1st step sampling...
    //int num = floor((max-min)/dt);
    //for (int i=0;i<num;i++){
    //    float t = min+i*dt;
    //    float amp = 0;
    //    if (t<=timeseries.at(0).at(0))
    //        amp = timeseries.at(0).at(1);
    //    else if (t>=timeseries.at(timeseries.size()-1).at(0))
    //        amp = timeseries.at(timeseries.size()-1).at(1);
    //    else{
    //        for (int j=0;j<timeseries.size()-1;j++){
    //            if (t>=timeseries.at(j).at(0) && t<=timeseries.at(j+1).at(0)){
    //                amp = timeseries.at(j).at(1) +
    //                        (timeseries.at(j+1).at(1)-timeseries.at(j).at(1))*
    //                        (t-timeseries.at(j).at(0))/(timeseries.at(j+1).at(0)-timeseries.at(j).at(0));
    //            }
    //        }
    //    }
    //    elevation.append(amp);
    //}

}

double LinearWave::GetElevation(Base::Vector3d pos, float time){

    float elevation = 0;
    float x = pos.x;
    float y = pos.y;

    for (int i=0;i<waveTrains.size();i++){

        float X = x * waveTrains.at(i).cosfDIR + y * waveTrains.at(i).sinfDIR;

        elevation += waveTrains.at(i).amplitude * sin(waveTrains.at(i).wavenumber * X - waveTrains.at(i).omega*(time+timeoffset) + waveTrains.at(i).phase);
    }

    return elevation;
}

QVector<float> LinearWave::GetElevationPerDirection(Base::Vector3d pos, float time, QVector<float> &waveDir, double deltaDir){

    QVector<float> elevation;

    for (int i=0;i<waveDir.size();i++) elevation.append(0);

    float x = pos.x;
    float y = pos.y;

    for (int i=0;i<waveTrains.size();i++){

        float X = x * waveTrains.at(i).cosfDIR + y * waveTrains.at(i).sinfDIR;
        double direction =  waveTrains.at(i).direction * 180.0 /PI_;
        while(direction < 0) direction += 360.0;

        for (int j=0;j<waveDir.size();j++){

            if (direction >= (waveDir.at(j)-deltaDir/2.0) && direction < (waveDir.at(j)+deltaDir/2.0)){
                elevation[j] += waveTrains.at(i).amplitude * sin(waveTrains.at(i).wavenumber * X - waveTrains.at(i).omega*(time+timeoffset) + waveTrains.at(i).phase);
            }
        }
    }

    return elevation;
}

void LinearWave::GLRenderSurfaceElevation(Base::Vector3d centerPos, float time, float width, float length, int discW, int discL, int GlList, bool showGrid, bool showSurface, bool showGround, double opacity, double groundOpacity, double depth){

        //int z, y;

        //QVector<QVector<Base::Vector3d>> points, normals;

        //for (z = 0; z <= discW; ++z)
        //{
        //    QVector <Base::Vector3d> line;
        //    for (y = 0; y <= discL; ++y)
        //    {
        //        line.append(Base::Vector3d(0,0,0));
        //    }
        //    points.append(line);
        //    normals.append(line);
        //}

        //#pragma omp parallel default (none) shared (centerPos, points, time, width, length, discW, discL)
        //{
        //    #pragma omp for
        //    for (int z = 0; z <= discW; ++z)
        //    {
        //        for (int y = 0; y <= discL; ++y)
        //        {
        //            Base::Vector3d position = Base::Vector3d(centerPos.x + (y * length/discL - length/2.0), centerPos.y + (z * width/discW - width/2.0),0);
        //            points[z][y] = (position + Base::Vector3d(0,0,1)*GetElevation(position,time));
        //        }
        //    }
        //}

        //rgb water;
        //water.r = 56;
        //water.g = 98;
        //water.b = 54;

        //hsv hs = rgb2hsv(water);

        //glNewList(GlList, GL_COMPILE);


        //if (showGround){

        //    glBegin(GL_POLYGON);

        //    glColor4d(44,87,12,groundOpacity);

        //    Base::Vector3d A(-length/2,-width/2,-depth);
        //    Base::Vector3d B(length/2,-width/2,-depth);
        //    Base::Vector3d C(length/2,width/2,-depth);
        //    Base::Vector3d D(-length/2,width/2,-depth);

        //    A+=centerPos;
        //    B+=centerPos;
        //    C+=centerPos;
        //    D+=centerPos;

        //    glNormal3d(0,0,1);

        //    glVertex3d(A.x,A.y,A.z);
        //    glVertex3d(B.x,B.y,B.z);
        //    glVertex3d(C.x,C.y,C.z);
        //    glVertex3d(D.x,D.y,D.z);
        //    glVertex3d(A.x,A.y,A.z);

        //    glEnd();
        //}


        //if (showSurface){


        //    for (int z = 0; z < points.size()-1; ++z)
        //    {
        //        for (int y = 0; y < points.at(z).size()-1; ++y)
        //        {

        //            Base::Vector3d A,B,C;
        //            A = points.at(z).at(y);
        //            B = points.at(z+1).at(y);
        //            C = points.at(z).at(y+1);

        //            Base::Vector3d normal = (C - A) % (B - A);
        //            normal.Normalize();

        //            normals[z][y] += normal/3.0;
        //            normals[z+1][y] += normal/3.0;
        //            normals[z][y+1] += normal/3.0;

        //        }
        //    }

        //    for (int z = 0; z < points.size(); ++z)
        //    {
        //        for (int y = 0; y < points.at(z).size(); ++y)
        //        {
        //            normals[z][y].Normalize();
        //        }
        //    }

        //    glEnable(GL_POINT_SMOOTH);
        //    glEnable(GL_LINE_SMOOTH);
        //    glEnable (GL_BLEND);
        //    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //    glEnable(GL_DEPTH_TEST);

        //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //    glEnable(GL_POLYGON_OFFSET_FILL);  // polygons get a reduced Z-value. Now the grid is drawn onto the WindField surface
        //    glPolygonOffset(1.0, 0);



        //    for (z = 0; z < points.size() - 1; ++z) {
        //        glBegin(GL_TRIANGLE_STRIP);  // the surface
        //        glEnable(GL_POLYGON_OFFSET_FILL);  // polygons get a reduced Z-value. Now the grid is drawn onto the WindField surface
        //        glPolygonOffset(1.0, 0);
        //        for (y = 0; y < points.at(z).size(); ++y) {

        //            if (Hs > 0) hs.v = 2./3. + points.at(z).at(y).z / Hs / 3.0;

        //            glColor4f (hsv2rgb(hs).r, hsv2rgb(hs).g, hsv2rgb(hs).b,opacity);
        //            glNormal3f(normals.at(z).at(y).x, normals.at(z).at(y).y, normals.at(z).at(y).z);
        //            glVertex3f (points.at(z).at(y).x, points.at(z).at(y).y, points.at(z).at(y).z);

        //            if (Hs > 0) hs.v = 2./3. + points.at(z+1).at(y).z / Hs / 3.0;

        //            glColor4f (hsv2rgb(hs).r, hsv2rgb(hs).g, hsv2rgb(hs).b,opacity);
        //            glNormal3f(normals.at(z+1).at(y).x, normals.at(z+1).at(y).y, normals.at(z+1).at(y).z);
        //            glVertex3f (points.at(z+1).at(y).x, points.at(z+1).at(y).y, points.at(z+1).at(y).z);
        //        }
        //        glEnd();
        //    }

        //}

        //if (showGrid){

        //    glColor4d (0, 0, 0, globalLineAlpha/2.0);
        //    glLineWidth(1.0);
        //    for (z = 0; z < points.size(); ++z) {
        //        glBegin(GL_LINE_STRIP);  // the straigth lines
        //        glEnable(GL_POLYGON_OFFSET_FILL);  // polygons get a reduced Z-value. Now the grid is drawn onto the WindField surface
        //        glPolygonOffset(-2, -2);
        //        for (y = 0; y < points.at(z).size(); ++y) {
        //            glVertex3f (points.at(z).at(y).x, points.at(z).at(y).y, points.at(z).at(y).z);
        //        }
        //        glEnd ();
        //    }

        //    glColor4d (0, 0, 0, globalLineAlpha/2.0);
        //    for (y = 0; y < points.at(0).size(); ++y) {
        //        glBegin(GL_LINE_STRIP);  // the straigth lines
        //        glEnable(GL_POLYGON_OFFSET_FILL);  // polygons get a reduced Z-value. Now the grid is drawn onto the WindField surface
        //        glPolygonOffset(-2, -2);
        //        for (z = 0; z < points.size(); ++z) {
        //            glVertex3f (points.at(z).at(y).x, points.at(z).at(y).y, points.at(z).at(y).z);
        //        }
        //        glEnd ();
        //    }
        //}

        //glEndList();


}


void LinearWave::GetVelocityAndAcceleration(Base::Vector3d pos, float time, float elevation, float depth, int stretchingType, Base::Vector3d *Vel, Base::Vector3d *Acc, float *dynP, int isFuchs, float dia){

    float x = pos.x;
    float y = pos.y;
    float z = pos.z;

    if (!Vel && !Acc)
        return;
    if (z + depth < 0)
        return;

    double nu = elevation;

    // if no stretching is used the wave elevation is not taken into account and vel and acc are calculated up until MSL at z = 0;
    if (stretchingType == NOSTRETCHING) nu = 0;

    // eval point is above current wave height, return
    if (z > nu)
        return;

    // stretching
    if (stretchingType == VERTICAL){ //vertical (above MSL is treated as at MSL)
        if (z > 0) z = 0;
    }
    else if (stretchingType == WHEELER){ //wheeler
        z = (z-nu)*depth/(nu+depth);
    }
    // end stretching

    if (z + depth < 0) //(2nd check after stretching)
        return;

    for (int i=0;i<waveTrains.size();i++){

        if (depth > 100){

            float X = x * waveTrains.at(i).cosfDIR + y * waveTrains.at(i).sinfDIR;
            float depthVar = expf(waveTrains.at(i).wavenumber*z);

            if (stretchingType == EXTRAPOLATION){ //extrapolation stretching
                if (z > 0)
                {
                    float dEdZ = waveTrains.at(i).wavenumber;
                    depthVar = 1.0f + dEdZ * z;
                }
            }

            float COSF = cos(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase);
            float SINF = sin(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase);

            if (Vel){
                Vel->x +=  waveTrains.at(i).A_omega * waveTrains.at(i).cosfDIR * depthVar * SINF;
                Vel->y +=  waveTrains.at(i).A_omega * waveTrains.at(i).sinfDIR * depthVar * SINF;
                Vel->z +=  -waveTrains.at(i).A_omega * depthVar * COSF;
            }

            if (Acc){
                if (isFuchs){
                    // approximation proposed in USFOS theory manual https://www.usfos.no/manuals/usfos/theory/documents/Usfos_Hydrodynamics.pdf
                    float MFC_acc_factor = std::min( 1.05f*tanhf(2.0f*PI_*depth*waveTrains.at(i).wavenumber/2.0f/PI_)/powf(powf(fabs(PI_*dia*waveTrains.at(i).wavenumber/2.0f/PI_-0.2f),2.2f)+1.0f,0.85f),1.0f);
                    float MFC_phase_shift = GetPhaseMCFPhaseShift(1.0/(dia*waveTrains.at(i).wavenumber/2.0f/PI_));

                    COSF = cos(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase+MFC_phase_shift);
                    SINF = sin(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase+MFC_phase_shift);

                    Acc->x += -waveTrains.at(i).A_omega2 * waveTrains.at(i).cosfDIR * depthVar * COSF * MFC_acc_factor;
                    Acc->y += -waveTrains.at(i).A_omega2 * waveTrains.at(i).sinfDIR * depthVar * COSF * MFC_acc_factor;
                    Acc->z += -waveTrains.at(i).A_omega2 * depthVar * SINF * MFC_acc_factor;
                }
                else{
                    Acc->x += -waveTrains.at(i).A_omega2 * waveTrains.at(i).cosfDIR * depthVar * COSF;
                    Acc->y += -waveTrains.at(i).A_omega2 * waveTrains.at(i).sinfDIR * depthVar * COSF;
                    Acc->z += -waveTrains.at(i).A_omega2 * depthVar * SINF;
                }
            }

            if (dynP){
                float TANH = tanhf(waveTrains.at(i).wavenumber*depth);
                *dynP += TANH * depthVar * waveTrains.at(i).amplitude * SINF;
            }
        }
        else{

            float X = x * waveTrains.at(i).cosfDIR + y * waveTrains.at(i).sinfDIR;

            float SINH = sinhf(waveTrains.at(i).wavenumber*depth);

            float depthVarXY = coshf(waveTrains.at(i).wavenumber*(z+depth))/SINH;
            float depthVarZ = sinhf(waveTrains.at(i).wavenumber*(z+depth))/SINH;

            if (stretchingType == EXTRAPOLATION){ //extrapolation stretching
                if (z > 0)
                {
                    float dEdZVarXY = waveTrains.at(i).wavenumber;
                    float dEdZVarZ = waveTrains.at(i).wavenumber * coshf(waveTrains.at(i).wavenumber*(depth))/SINH;

                    depthVarXY = coshf(waveTrains.at(i).wavenumber*(depth))/SINH + z*dEdZVarXY;
                    depthVarZ = 1.0f + z*dEdZVarZ;
                }
            }

            float COSF = cos(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase);
            float SINF = sin(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase);

            if (Vel){
                Vel->x +=  waveTrains.at(i).A_omega * waveTrains.at(i).cosfDIR * depthVarXY * SINF;
                Vel->y +=  waveTrains.at(i).A_omega * waveTrains.at(i).sinfDIR * depthVarXY * SINF;
                Vel->z +=  -waveTrains.at(i).A_omega * depthVarZ * COSF;
            }

            if (Acc){
                if (isFuchs){
                    // approximation proposed in USFOS theory manual https://www.usfos.no/manuals/usfos/theory/documents/Usfos_Hydrodynamics.pdf
                    float MFC_acc_factor = std::min( 1.05f*tanhf(2.0f*PI_*depth*waveTrains.at(i).wavenumber/2.0f/PI_)/powf(powf(fabs(PI_*dia*waveTrains.at(i).wavenumber/2.0f/PI_-0.2f),2.2f)+1.0f,0.85f),1.0f);
                    float MFC_phase_shift = GetPhaseMCFPhaseShift(1.0/(dia*waveTrains.at(i).wavenumber/2.0f/PI_));

                    //float MFC_phase_shift = PI_/180.0f*((-450.0f/8.0f)*(PI_*dia*waveTrains.at(i).wavenumber/2.0f/PI_-2.0f)-75.0f/pow(PI_*dia*waveTrains.at(i).wavenumber/2.0f/PI_+0.5f,2.0f));

                    COSF = cos(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase+MFC_phase_shift);
                    SINF = sin(waveTrains.at(i).wavenumber*X-waveTrains.at(i).omega*(time+timeoffset)+waveTrains.at(i).phase+MFC_phase_shift);

                    Acc->x += -waveTrains.at(i).A_omega2 * waveTrains.at(i).cosfDIR * depthVarXY * COSF * MFC_acc_factor;
                    Acc->y += -waveTrains.at(i).A_omega2 * waveTrains.at(i).sinfDIR * depthVarXY * COSF * MFC_acc_factor;
                    Acc->z += -waveTrains.at(i).A_omega2 * depthVarZ * SINF * MFC_acc_factor;
                }
                else{
                    Acc->x += -waveTrains.at(i).A_omega2 * waveTrains.at(i).cosfDIR * depthVarXY * COSF;
                    Acc->y += -waveTrains.at(i).A_omega2 * waveTrains.at(i).sinfDIR * depthVarXY * COSF;
                    Acc->z += -waveTrains.at(i).A_omega2 * depthVarZ * SINF;
                }
            }

            if (dynP){
                float TANH = tanhf(waveTrains.at(i).wavenumber*depth);
                *dynP += TANH * depthVarXY * waveTrains.at(i).amplitude * SINF;
            }
        }
    }

}

double LinearWave::GetPhaseMCFPhaseShift(double x){

    // interpolation is based on data in Table 1.1 (p.38) of the USFOS theory manual https://www.usfos.no/manuals/usfos/theory/documents/Usfos_Hydrodynamics.pdf

    if (x < ratio[0]) return phase[0] / 180.0 * PI_;

    if (x > ratio[arrLength-1]) return phase[arrLength-1] / 180.0 * PI_;

    for (int i = 0; i< arrLength-1; i++){

        if (x >= ratio[i] && x <= ratio[i+1])
            return (phase[i] + (phase[i+1]-phase[i])/(ratio[i+1]-ratio[i])*(x-ratio[i])) / 180.0 * PI_;
    }

    return 0;


}

void LinearWave::Copy(LinearWave *wave){

    DFT_cutIn = wave->DFT_cutIn;
    DFT_cutOut = wave->DFT_cutOut;
    DFT_sample = wave->DFT_sample;
    DFT_thresh = wave->DFT_thresh;
    Hs = wave->Hs;
    Tp = wave->Tp;
    timeoffset = wave->timeoffset;
    dir_mean = wave->dir_mean;
    dir_max = wave->dir_max;
    s = wave->s;
    f_start = wave->f_start;
    f_end = wave->f_end;
    d_fMax = wave->d_fMax;
    sigma1 = wave->sigma1;
    sigma2 = wave->sigma2;
    gamma = wave->gamma;
    lambda1 = wave->lambda1;
    lambda2 = wave->lambda2;
    f1 = wave->f1;
    f2 = wave->f2;
    Hs1 = wave->Hs1;
    Hs2 = wave->Hs2;
    autoOchi = wave->doublePeak;
    discF = wave->discF;
    discDir = wave->discDir;
    seed = wave->seed;
    S_frequency = wave->S_frequency;
    S_directional = wave->S_directional;
    S_discretization = wave->S_discretization;
    dispersionPrescribed = wave->dispersionPrescribed;
    autoSigma = wave->autoSigma;
    autoGamma = wave->autoGamma;
    autoFrequency = wave->autoFrequency;
    waveComponentsFile = wave->waveComponentsFile;
    waveComponentsFileName = wave->waveComponentsFileName;
    waveTimeseriesFile = wave->waveTimeseriesFile;
    waveTimeseriesFileName = wave->waveTimeseriesFileName;
    spectrumFile = wave->spectrumFile;
    spectrumFileName = wave->spectrumFileName;
    spectrumData = wave->spectrumData;

}


void LinearWave::CalculateDispersion(double gravity, double depth){

    if (dispersionPrescribed) return;

    // after J. Guo, "Simple and explicit solution of wave dispersion equation", Coastal Engineering 45, pp. 71-74, 2002.
    #pragma omp parallel default (none) shared (gravity,depth)
    {
        #pragma omp for
        for (int i=0;i<waveTrains.size();i++){
                waveTrains[i].wavenumber = pow(waveTrains.at(i).omega,2.0) / gravity * pow(1.0-expf(-pow(waveTrains.at(i).omega*sqrtf(depth/gravity),5.0/2.0)),-2.0/5.0);
        }
    }
}

double LinearWave::S_JONSWAP(double f, double Hs, double Tp, bool autoGamma, bool autoSigma, double gamma, double sigma1, double sigma2){

    double fp = 1/Tp;
    double sigma;

    if (autoGamma){
        if (Tp/sqrt(Hs) <= 3.6) gamma = 5.0;
        else if (Tp/sqrt(Hs) > 3.6 && Tp/sqrt(Hs) <= 5) gamma = exp(5.75-1.15*Tp/sqrt(Hs));
        else gamma = 1;
    }

    if (autoSigma){
        if (f <= fp) sigma = 0.07;
        else sigma = 0.09;
    }
    else{
        if (f <= fp) sigma = sigma1;
        else sigma = sigma2;
    }

    double f_ratio = f/fp;

    return 0.3125*pow(Hs,2.0)*Tp*pow(f_ratio,-5.0)*exp(-1.25*pow(f_ratio,-4.0))*(1.0-0.287*log(gamma))*pow(gamma,exp(-0.5*pow((f_ratio-1.0)/sigma,2.0)));

}

double LinearWave::S_CUSTOM(double f){

    if (f<spectrumData.at(0).at(0) || f>spectrumData.at(spectrumData.size()-1).at(0)) return 0;

    for (int i=0;i<spectrumData.size()-1;i++){
        if (f >= spectrumData.at(i).at(0) && f <= spectrumData.at(i+1).at(0)){
            return spectrumData.at(i).at(1) + (spectrumData.at(i+1).at(1)-spectrumData.at(i).at(1)) * (f-spectrumData.at(i).at(0))/(spectrumData.at(i+1).at(0)-spectrumData.at(i).at(0));
        }
    }

    return 0;
}

double LinearWave::S_ORCHIHUBBLE(double f){

    double w1 = f1*2.0*PI_;
    double w2 = f2*2.0*PI_;
    double w = f*2.0*PI_;

    double S1 = 1./4. * pow(((4.0*lambda1+1)/4.0)*pow(w1,4),lambda1)/tgamma(lambda1)*pow(Hs1,2)/pow(w,4.0*lambda1+1)*exp(-(4.0*lambda1+1)/4.0*pow(w1/w,4));
    double S2 = 1./4. * pow(((4.0*lambda2+1)/4.0)*pow(w2,4),lambda2)/tgamma(lambda2)*pow(Hs2,2)/pow(w,4.0*lambda2+1)*exp(-(4.0*lambda2+1)/4.0*pow(w2/w,4));

    return S1+S2;

}

double LinearWave::S_TORSETHAUGEN(double f, double Hs, double Tp, bool autoGamma, bool autoSigma, double gamma, double sigma1, double sigma2, bool isDouble){

    double fp = 1.0/Tp;
    double sigma;

    //parameters from Torsethaugen, K., & Haver, S. (2004). Simplified Double Peak Spectral Model for Ocean Waves. Trondheim, Norway: SINTEF

    double a_f = 6.6;
    double a_e = 2.0;
    double a_u = 25;
    double a_10 = 0.7;
    double a_1 = 0.5;
    double k_g = 35.0;
    double b_1 = 2.0;
    double a_20 = 0.6;
    double a_2 = 0.3;
    double a_3 = 6;

    double Tpf = a_f * pow(Hs,1.0/3.0);
    double Tl = a_e * pow(Hs,0.5);
    double Tu = a_u;
    double e_l = (Tpf-Tp)/(Tpf-Tl);
    double e_u = (Tp-Tpf)/(Tu-Tpf);

    if (Tp < Tl) e_l = 1.0;
    if (Tp > Tu) e_u = 1.0;

    double R,H1,Tp1,s,Gamma1,H2,Tp2;

    if (Tp<=Tpf){
        R = (1.0-a_10)*exp(-pow(e_l/a_1,2.0))+a_10;
        H1 = R*Hs;
        Tp1 = Tp;
        s = 2.0*PI_/GRAVITY*H1/Tp1/Tp1;
        Gamma1 = k_g*pow(s,6.0/7.0);
        H2 = pow(1.0-R*R,0.5)*Hs;
        Tp2 = Tpf+b_1;
    }
    else{
        R = (1.0-a_20)*exp(-pow(e_u/a_2,2.0))+a_20;
        H1 = R*Hs;
        Tp1 = Tp;
        s = 2.0*PI_/GRAVITY*Hs/Tpf/Tpf;
        Gamma1 = k_g*pow(s,6.0/7.0)*(1.0+a_3*e_u);
        H2 = pow(1.0-R*R,0.5)*Hs;
        Tp2 = a_f*pow(H2,1.0/3.0);
    }

    if (!autoGamma){
        Gamma1 = gamma;
    }

    if (autoSigma){
        if (f <= fp) sigma = 0.07;
        else sigma = 0.09;
    }
    else{
        if (f <= fp) sigma = sigma1;
        else sigma = sigma2;
    }

    double G0 = 3.26;
    double Ay = (1.0+1.1*pow(log(Gamma1),1.19))/Gamma1;
    double f1n = f*Tp1;
    double f2n = f*Tp2;
    double S1 = G0*Ay*pow(f1n,-4.0)*exp(-pow(f1n,-4.0))*pow(Gamma1,exp(-pow(f1n-1,2)/2.0/sigma/sigma));
    double S2 = G0*pow(f2n,-4.0)*exp(-pow(f2n,-4.0));

    if (isDouble) return S1+S2;
    else return S1;

}

double LinearWave::S_DIRECTIONAL(double dir, double dir_mean, double dir_max, double s){

    double C = sqrt(PI_)*tgamma(s+1)/2.0/dir_max/tgamma(s+0.5);

    return C * pow(fabs(cos(PI_*(dir-dir_mean)/2.0/dir_max)),2.0*s);

}


void LinearWave::DiscretizeFrequencySpectrum
    (int seed, int num_f, int num_dir, double df_max, double Hs, double Tp, bool auto_f_range, bool auto_gamma, bool auto_sigma, double f_cutIn, double f_cutOut, double gamma, double sigma1, double sigma2){

    if (S_directional == UNIDIRECTIONAL) num_dir = 1;
    double num_f_total = num_f;

    if (auto_f_range){
        f_cutIn = 0.5*1.0/Tp;
        f_cutOut = 10.0*1.0/Tp;
        if (S_frequency == OCHI_HUBBLE){
            f_cutIn = 0.5*f1;
            f_cutOut = 10.0*f2;
        }
    }

    QVector<double> frequencies;

    int disc = 100000;
    double delta_f = (f_cutOut-f_cutIn)/disc;

    for (int i=0;i<=disc;i++){
        frequencies.append(f_cutIn+delta_f*i);
    }

    QVector<double> intS;
    QVector<double> S;

    double area = 0;
    double discS;
    for (int i=0;i<frequencies.size();i++){
        if (S_frequency == JONSWAP || S_frequency == ISSC){
            discS = S_JONSWAP(frequencies.at(i),Hs,Tp,auto_gamma,auto_sigma,gamma,sigma1,sigma2)*delta_f;
            area += discS;
        }
        else if (S_frequency == TORSETHAUGEN){
            discS = S_TORSETHAUGEN(frequencies.at(i),Hs,Tp,auto_gamma,auto_sigma,gamma,sigma1,sigma2,doublePeak)*delta_f;
            area += discS;
        }
        else if (S_frequency == OCHI_HUBBLE){
            discS = S_ORCHIHUBBLE(frequencies.at(i))*delta_f;
            area += discS;
            Hs = pow(Hs1*Hs1+Hs2*Hs2,0.5);
        }
        else if (S_frequency == IMP_SPECTRUM){
            discS = S_CUSTOM(frequencies.at(i))*delta_f;
            area += discS;
        }
        S.append(discS);
        intS.append(area);
    }

    double sig2 = Hs*Hs/16.0;
    double normFactor = sig2/area;

    double const_energy = area/num_f_total;

    double energy = const_energy/2.0;

    QVector<double> discretized_f;
    QVector<double> amplitudes, phases;

    srand(seed);

    double f_range_neg = f_cutIn;
    double f_range_pos;
    double scaleFac;
    double thet = 0.0;
    if (S_discretization == EQUAL_FREQUENCY){

        double d_f = (f_cutOut-f_cutIn)/num_f_total;


        for (int i=0;i<num_f_total;i++){

            double f = f_cutIn+d_f*i+d_f/2;
            double en = 0;

            for (int j=0;j<frequencies.size();j++){
                if (frequencies.at(j)>=f-d_f/2.0 && frequencies.at(j) <= f+d_f/2.0)
                    en+=S.at(j);
            }
            //std::srand((unsigned int)time(0));
            //phases.append(double(rand())/double(RAND_MAX) * 2.0 * PI_);
            phases.append(randomPhases(i, locationIndex));

            discretized_f.append((f));
            amplitudes.append(sqrt(2.0*en*normFactor));
        }


    }
    else if(S_discretization == EQUAL_ENERGY){

        for (int i=0;i<num_f_total;i++){

            if (energy > intS.at(intS.size()-1)){
                f_range_pos = frequencies.at(intS.size()-1);
                scaleFac = (intS.at(intS.size()-1)-energy+const_energy)/const_energy;
            }
            else{
                for (int j=0;j<intS.size()-1;j++){
                    if (energy >= intS.at(j) && energy <= intS.at(j+1)){
                        f_range_pos = frequencies.at(j) + (frequencies.at(j+1)-frequencies.at(j)) * (energy-intS.at(j))/(intS.at(j+1)-intS.at(j));
                        scaleFac = 1.0;
                    }
                }
            }

            double frange = (f_range_pos-f_range_neg);

            if (frange > df_max){

                double energy_start = energy-const_energy;
                if (energy_start < 0) energy_start = 0;
                double f_range_start = f_range_neg;

                while (energy_start < energy){
                    int subStep = 1;

                    bool subComplete = false;

                    while(subComplete == false){

                        subStep++;

                        subComplete = true;

                        double energy_int = energy_start + const_energy/subStep;

                        if (energy_int > intS.at(intS.size()-1)){
                            f_range_pos = frequencies.at(intS.size()-1);
                            scaleFac = (intS.at(intS.size()-1)-energy_int+const_energy/subStep)/(const_energy/subStep);
                        }
                        else{
                            for (int j=0;j<intS.size()-1;j++){
                                if (energy_int >= intS.at(j) && energy_int <= intS.at(j+1)){
                                    f_range_pos = frequencies.at(j) + (frequencies.at(j+1)-frequencies.at(j)) * (energy_int-intS.at(j))/(intS.at(j+1)-intS.at(j));
                                    scaleFac = 1.0;
                                }
                            }
                        }

                        if ((f_range_pos-f_range_start) > df_max) subComplete = false;
                    }

                    //phases.append(double(rand())/double(RAND_MAX) * 2.0 * PI_);
                    phases.append(randomPhases(i, locationIndex));

                    discretized_f.append(f_range_pos);
                    amplitudes.append(sqrt(2.0*const_energy*normFactor)/subStep*scaleFac);
                    f_range_start = f_range_pos;
                    energy_start += const_energy/subStep;
                }
                energy = energy_start+const_energy;
                f_range_neg = f_range_start;
            }
            else{
                //phases.append(double(rand())/double(RAND_MAX) * 2.0 * PI_);
                phases.append(randomPhases(i, locationIndex));

                discretized_f.append(f_range_pos);
                amplitudes.append(sqrt(2.0*const_energy*normFactor)*scaleFac);
                energy+=const_energy;
                f_range_neg = f_range_pos;
            }

            if (scaleFac<1.0) break;
        }
    }

    waveTrains.clear();

    for (int i=0;i<amplitudes.size();i++){

        waveTrain train;
        train.amplitude = amplitudes.at(i);
        train.phase = phases.at(i);
        train.omega = discretized_f.at(i) * 2.0 * PI_;
        train.A_omega = train.amplitude * train.omega;
        train.A_omega2 = train.amplitude * train.omega * train.omega;
        waveTrains.append(train);
    }
}

void LinearWave::DiscretizeDirectionalSpectrum(int num_directions, double dir_mean, double dir_max, double s){

    dir_mean *= PI_ / 180.0;
    dir_max *= PI_ / 180.0;

    if (num_directions <= 1 || dir_max == 0){
        for (int i=0;i<waveTrains.size();i++){
            waveTrains[i].direction = dir_mean;
            waveTrains[i].cosfDIR = cosf(waveTrains[i].direction);
            waveTrains[i].sinfDIR = sinf(waveTrains[i].direction);
        }
        return;
    }

    QVector<double> intDir, discDir;

    int disc = 100000;

    double deltaDir = 2*dir_max/disc;

    for (int i=0;i<=disc;i++){
        discDir.append(-dir_max+(deltaDir*i)+dir_mean);
    }

    double areaDir = 0;
    for (int i=0;i<discDir.size();i++){
        areaDir += S_DIRECTIONAL(discDir.at(i),dir_mean,dir_max,s)*deltaDir;
        intDir.append(areaDir);
    }

    //equal energy discretization for the directions

    QVector<double> dirSteps;

    for (int i=0;i<num_directions;i++){

        double directionalenergy = 1.0/num_directions*i + 1.0/num_directions/2.0;

        for (int j=0;j<intDir.size()-1;j++){
            if (directionalenergy >= intDir.at(j) && directionalenergy <= intDir.at(j+1)){
                dirSteps.append(discDir.at(j) + (discDir.at(j+1)-discDir.at(j)) * (directionalenergy-intDir.at(j))/(intDir.at(j+1)-intDir.at(j)));
            }
        }
    }

    srand(seed);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dirSteps.begin(), dirSteps.end(), g);

    for (int i=0;i<waveTrains.size();i++){
        waveTrains[i].direction = dirSteps.at(i%(dirSteps.size()));
        waveTrains[i].cosfDIR = cosf(waveTrains[i].direction);
        waveTrains[i].sinfDIR = sinf(waveTrains[i].direction);
    }

}

LinearWave::~LinearWave() {
    //	glDeleteLists(m_glListIndex, 1);
    waveTrains.clear();
}

void LinearWave::PrepareGraphData(double start, double end, double delta, double depth)
{

    m_availableVariables.clear();
    m_VariableData.clear();

    m_availableVariables.append(QString::fromLatin1("Time [s]"));
    m_availableVariables.append(QString::fromLatin1("Wave Elevation [m]"));
    m_availableVariables.append(QString::fromLatin1("Wave MSL Velocity x [m/s]"));
    m_availableVariables.append(QString::fromLatin1("Wave MSL Velocity y [m/s]"));
    m_availableVariables.append(QString::fromLatin1("Wave MSL Velocity z [m/s]"));
    m_availableVariables.append(QString::fromLatin1("Wave MSL Acceleration x [m/s]"));
    m_availableVariables.append(QString::fromLatin1("Wave MSL Acceleration y [m/s]"));
    m_availableVariables.append(QString::fromLatin1("Wave MSL Acceleration z [m/s]"));

    QVector<float> time, elevation, velocityx, velocityy, velocityz, accelerationx, accelerationy,
        accelerationz;

    int numSteps = (end - start) / delta;

    for (int i = 0; i < numSteps; i++) {
        time.append(start + i * delta);
        elevation.append(0);
        velocityx.append(0);
        velocityy.append(0);
        velocityz.append(0);
        accelerationx.append(0);
        accelerationy.append(0);
        accelerationz.append(0);
    }

#pragma omp parallel default(none) shared(time, elevation, velocityx, velocityy, velocityz,        \
                                          accelerationx, accelerationy, accelerationz, depth)
    {
#pragma omp for
        for (int i = 0; i < time.size(); i++) {
            Base::Vector3d velocity(0, 0, 0), acceleration(0, 0, 0);
            elevation[i] = GetElevation(Base::Vector3d(0, 0, 0), time[i]);
            GetVelocityAndAcceleration(Base::Vector3d(0, 0, 0), time[i], 0, depth, VERTICAL, &velocity, &acceleration);
            velocityx[i] = velocity.x;
            velocityy[i] = velocity.y;
            velocityz[i] = velocity.z;
            accelerationx[i] = acceleration.x;
            accelerationy[i] = acceleration.y;
            accelerationz[i] = acceleration.z;
        }
    }

    m_VariableData.append(time);
    m_VariableData.append(elevation);
    m_VariableData.append(velocityx);
    m_VariableData.append(velocityy);
    m_VariableData.append(velocityz);
    m_VariableData.append(accelerationx);
    m_VariableData.append(accelerationy);
    m_VariableData.append(accelerationz);
}