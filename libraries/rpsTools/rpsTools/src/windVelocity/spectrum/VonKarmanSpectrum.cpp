#include "VonKarmanSpectrum.h"
#include <math.h>

using namespace rps;
using namespace WindVelocity;

VonKarmanSpectrum::VonKarmanSpectrum()
{

}

VonKarmanSpectrum::~VonKarmanSpectrum()
{

}

double  VonKarmanSpectrum::computeAlongWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, const double &integralLengthScale, const double &standardDeviation)
{
    double dBuf1, dBuf2, dBuf3;
    double dPSD = 0.0;
    double Par1 = 4.0;
    double Par2 = 70.8;
    double PI = 22.0 / 7.0;

    dBuf3 = integralLengthScale / meanSpeed;
 
    dBuf1 = 1.0 + Par2 * frequency * frequency * dBuf3 * dBuf3 / (2.0 * PI * 2.0 * PI);

    dBuf2 = pow(dBuf1, 5.0 / 6.0);

    dPSD = Par1 * standardDeviation * standardDeviation * dBuf3;

    dPSD /= dBuf2;			// (rad/s)

    dPSD /= 2.0*PI;

    return dPSD;
}

double VonKarmanSpectrum::computeAcrossWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, const double &integralLengthScale, const double &standardDeviation)
{
    double dBuf1, dBuf2, dBuf3, dBuf4;
    double dPSD = 0.0;
    double Par1 = 4.0;
    double Par2 = 283.0;
    double Par3 = 755.0;
    double PI = 22.0 / 7.0;

    dBuf3 = integralLengthScale / meanSpeed;
 
    dBuf1 = 1.0 + Par2 * frequency * frequency * dBuf3 * dBuf3 / (2.0 * PI * 2.0 * PI);

    dBuf2 = pow(dBuf1, 11.0 / 6.0);

    dPSD = Par1 * standardDeviation * standardDeviation * dBuf3;

    dPSD /= dBuf2;			// (rad/s)
    
    dBuf4 = 1.0 + Par3 * frequency * frequency * dBuf3 * dBuf3 / (2.0 * PI * 2.0 * PI);

    dPSD *= dBuf4;

    dPSD /= 2.0 * PI;

    return dPSD;
}

double VonKarmanSpectrum::computeVerticalWindAutoSpectrum(const double &frequency, const double &height, const double &meanSpeed, const double &shearVelocity, const double &integralLengthScale, const double &standardDeviation)
{
    double dBuf1, dBuf2, dBuf3, dBuf4;
    double dPSD = 0.0;
    double Par1 = 4.0;
    double Par2 = 283.0;
    double Par3 = 755.0;
    double PI = 22.0 / 7.0;

    dBuf3 = integralLengthScale / meanSpeed;
 
    dBuf1 = 1.0 + Par2 * frequency * frequency * dBuf3 * dBuf3 / (2.0 * PI * 2.0 * PI);

    dBuf2 = pow(dBuf1, 11.0 / 6.0);

    dPSD = Par1 * standardDeviation * standardDeviation * dBuf3;

    dPSD /= dBuf2;			// (rad/s)
    
    dBuf4 = 1.0 + Par3 * frequency * frequency * dBuf3 * dBuf3 / (2.0 * PI * 2.0 * PI);

    dPSD *= dBuf4;

    dPSD /= 2.0 * PI;

    return dPSD;
}
