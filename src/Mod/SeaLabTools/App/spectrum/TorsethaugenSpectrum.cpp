#include "PreCompiled.h"
#include "TorsethaugenSpectrum.h"
#include <math.h>
#include <Mod/SeaLabTools/App/spectrum/TorsethaugenSpectrumPy.h>

#define PI_ 3.14159265358979323846
#define GRAVITY 9.80665

using namespace SeaLabTools;

TorsethaugenSpectrum::TorsethaugenSpectrum()
{

}

TorsethaugenSpectrum::~TorsethaugenSpectrum()
{

}

double  TorsethaugenSpectrum::computeSpectrum(double frequency, double significantWaveHeight, double peakPeriod, bool autoGamma, bool autoSigma, double gamma, double sigma1, double sigma2, bool isDouble)
{
    double peakFrequency = 1.0 / peakPeriod;
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

    double Tpf = a_f * pow(significantWaveHeight, 1.0 / 3.0);
    double Tl = a_e * pow(significantWaveHeight, 0.5);
    double Tu = a_u;
    double e_l = (Tpf - peakPeriod) / (Tpf - Tl);
    double e_u = (peakPeriod - Tpf) / (Tu - Tpf);

    if (peakPeriod < Tl) e_l = 1.0;
    if (peakPeriod > Tu) e_u = 1.0;

    double R,H1,Tp1,s,Gamma1,H2,Tp2;

    if (peakPeriod <= Tpf) {
        R = (1.0-a_10)*exp(-pow(e_l/a_1,2.0))+a_10;
        H1 = R * significantWaveHeight;
        Tp1 = peakPeriod;
        s = 2.0*PI_/GRAVITY*H1/Tp1/Tp1;
        Gamma1 = k_g*pow(s,6.0/7.0);
        H2 = pow(1.0 - R * R, 0.5) * significantWaveHeight;
        Tp2 = Tpf+b_1;
    }
    else{
        R = (1.0-a_20)*exp(-pow(e_u/a_2,2.0))+a_20;
        H1 = R * significantWaveHeight;
        Tp1 = peakPeriod;
        s = 2.0 * PI_ / GRAVITY * significantWaveHeight / Tpf / Tpf;
        Gamma1 = k_g*pow(s,6.0/7.0)*(1.0+a_3*e_u);
        H2 = pow(1.0 - R * R, 0.5) * significantWaveHeight;
        Tp2 = a_f*pow(H2,1.0/3.0);
    }

    if (!autoGamma){
        Gamma1 = gamma;
    }

    if (autoSigma){
        if (frequency <= peakFrequency) sigma = 0.07;
        else sigma = 0.09;
    }
    else{
        if (frequency <= peakFrequency) sigma = sigma1;
        else sigma = sigma2;
    }

    double G0 = 3.26;
    double Ay = (1.0+1.1*pow(log(Gamma1),1.19))/Gamma1;
    double f1n = frequency * Tp1;
    double f2n = frequency * Tp2;
    double S1 = G0*Ay*pow(f1n,-4.0)*exp(-pow(f1n,-4.0))*pow(Gamma1,exp(-pow(f1n-1,2)/2.0/sigma/sigma));
    double S2 = G0*pow(f2n,-4.0)*exp(-pow(f2n,-4.0));

    if (isDouble) return S1+S2;
    else return S1;
}

PyObject* TorsethaugenSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new TorsethaugenSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}