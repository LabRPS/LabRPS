#include "PreCompiled.h"
#include "AvailableWindows.h"
#include <math.h>
#include <unsupported/Eigen/FFT>
#include <gsl/gsl_sf_bessel.h>

using namespace rps;
using namespace General;

static constexpr double M_PI = 3.14159265358979323846264338327950288;

AvailableWindows::AvailableWindows()
{

}

AvailableWindows::~AvailableWindows()
{

}


void AvailableWindows::BartlettWindow(vec &win, int L)
{
    for (int loop = 0; loop < L; loop++)
    {
        if(0 <= loop && loop <= (L-1)/2)
        {
            win(loop) = 2 * loop/(double)(L - 1);
        }
        else
        {
            win(loop) = 2 - (2 * loop/(double)(L - 1));

        }
    }
}
void AvailableWindows::BartlettHannWindow(vec &win, int L)
{
    for (int loop = 0; loop < L; loop++)
    {
        win(loop) = 0.62 - 0.48 * std::abs((loop / (double)(L - 1)) - 0.5) + 0.38 * std::cos(2 * M_PI * ((loop  /(double)( L- 1)) - 0.5));
    }
}

void AvailableWindows::BlackmanSymmetricWindow(vec &win, int L)
{
    double f = 0.0;
    int M;

    if ( L % 2 == 0)
    {
        M = L/2;
        for (int loop = 0; loop < M; loop++)
        {

            f = 2*M_PI*loop/(double)(L-1);
            win(loop) = 0.42 - 0.50 * std::cos(f) + 0.08*std::cos(2.0*f);
            win(L-loop-1) = win(loop);
        }

    }
    else
    {
        M = (L+1)/2;

        for (int loop = 0; loop < M; loop++)
        {

            f = 2*M_PI*loop/(double)(L-1);
            win(loop) = 0.42 - 0.50 * std::cos(f) + 0.08*std::cos(2*f);
        }

        for (int loop = 0; loop < M - 1; loop++)
        {
            win[L-loop-1] = win[loop];
        }
    }
}

void AvailableWindows::BlackmanWindow(vec &win, int L, int flag)
{

    if(flag == 1)//periodic
    {
        vec win0(L+1);
        BlackmanSymmetricWindow(win0, L+1);

        for (int loop = 0; loop < L; loop++)
        {
            win[loop] = win0[loop];
        }
    }
    else if(flag == 2)//symmetric
    {
        BlackmanSymmetricWindow(win, L);
    }

}
void AvailableWindows::BlackmanHarrisWindow0(vec &win, int L, int flag)
{
    double f = 0.0;
    double N;
    if(flag == 1)//periodic
    {
        N = L - 1;
        for (int loop = 0; loop < L; loop++)
        {
            f = 2*M_PI*loop/(double)N;
            win(loop) = 0.35875 - (0.48829 * std::cos(f)) + (0.14128*std::cos(2.0*f)) - (0.01168*std::cos(3.0*f));
        }
    }
    else if(flag == 2)//symmetric
    {
        N = L;
        for (int loop = 0; loop < L; loop++)
        {
            f = 2*M_PI*loop/(double)(N-1);
            win(loop) = 0.35875 - (0.48829 * std::cos(f)) + (0.14128*std::cos(2.0*f)) - (0.01168*std::cos(3.0*f));
        }
    }
}

void AvailableWindows::BlackmanHarrisWindow(vec &win, int L, int flag)
{
    if(flag == 1)//periodic
    {
        vec win0(L+1);
        BlackmanHarrisWindow0(win0, L+1, flag);

        for (int loop = 0; loop < L; loop++)
        {
            win(loop) = win0(loop);
        }
    }
    else if(flag == 2)//symmetric
    {
        BlackmanHarrisWindow0(win, L, flag);
    }
}

void AvailableWindows::BohmanWindow(vec &win, int L)
{
    if (L == 1)
    {
        // Special case for n == 1.
        win(0) = 1.0;
    }
    else
    {
        for (int i = 0; i < L; ++i)
        {
            const double x = fabs(2.0 * i - (L - 1)) / (double)(L - 1);

            win(i) = (1.0 - x) * cos(M_PI * x) + sin(M_PI * x) / M_PI;
        }
    }
}
void AvailableWindows::ChebyshevWindow(vec &win, int L, double r)
{
    // Chebyshev window.
    Eigen::FFT<double> fft;
    std::complex<double> I(0, 1.0);

    //
    // Default value of the "r" parameter is 100.0.

    if (L == 1)
    {
        // Special case for n == 1.
        win[0] = 1.0;
    }
    else
    {
        const int order = L - 1;

        // r is in dB(power).
        // Calculate the amplification factor, e.g. r = +60 --> amplification = 1000.0

        const double amplification = pow(10.0, fabs(r) / 20.0);

        const double beta = cosh(acosh(amplification) / order);

        // Find the window's DFT coefficients
        cx_vec p(L);
        cx_vec pfft(L);

        // Appropriate IDFT and filling up, depending on even/odd length.

        if (L % 2 != 0)
        {
            // Odd length window

            for (int i = 0; i < L; ++i)
            {
                const double x = beta * cos(M_PI * i / L);

                if (x > 1.0)
                {
                    p[i] = cosh(order * acosh(x));
                }
                else if (x < -1.0)
                {
                    p[i] = cosh(order * acosh(-x));
                }
                else
                {
                    p[i] = cos (order * acos(x));
                }
            }

            pfft = fft.fwd(p);

            // Example: n = 11
            //
            // w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9] w[10]
            //
            //                            =
            //
            // p[5] p[4] p[3] p[2] p[1] p[0] p[1] p[2] p[3] p[4] p[5]

            const int h = (L - 1) / 2;

            for (int i = 0; i < L; ++i)
            {
                const int j = (i <= h) ? (h - i) : (i - h);

                win[i] = real(pfft[j]);
            }
        }
        else
        {
            // Even length window

            for (int i = 0; i < L; ++i)
            {
                const double x = beta * cos(M_PI * i / L);

                std::complex<double> z = exp(M_PI  * i * I/(double) L);

                if (x > 1)
                {
                    p[i] =  z * cosh(order * acosh( x));
                }
                else if (x < -1)
                {
                    p[i] = -z * cosh(order * acosh(-x));
                }
                else
                {
                    p[i] =  z * cos (order * acos ( x));
                }
            }

            pfft = fft.fwd(p);

            // Example: n = 10
            //
            // w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9]
            //
            //                         =
            //
            // p[5] p[4] p[3] p[2] p[1] p[1] p[2] p[3] p[4] p[5]

            const int h = L / 2;

            for (int i = 0; i < L; ++i)
            {
                const int j = (i < h) ? (h - i) : (i - h + 1);

                win[i] = real(pfft[j]);
            }
        }

        // Normalize window so the maximum value is 1.

        double maxw = win[0];
        for (int i = 1; i < L; ++i)
        {
            maxw = fmax(maxw, win[i]);
        }

        for (int i = 0; i < L; ++i)
        {
            win[i] /= maxw;
        }
    }
}

void AvailableWindows::FatTopWindow0(vec &win, int L, int flag)
{
    double f = 0.0;
    double N;
    if(flag == 1)//periodic
    {
        N = L - 1;
    }
    else if(flag == 2)//symmetric
    {
        N = L;
    }

    for (int loop = 0; loop < L; loop++)
    {
        f = 2*M_PI*loop/(double)(N-1);
        win(loop) = 0.21557895 - (0.41663158 * std::cos(f)) + (0.277263158*std::cos(2.0*f)) - (0.083578947*std::cos(3.0*f))+ (0.006947368*std::cos(4.0*f));
    }

}
void AvailableWindows::FatTopWindow(vec &win, int L, int flag)
{
    if(flag == 1)//periodic
    {
        vec win0(L+1);
        FatTopWindow0(win0, L+1, flag);

        for (int loop = 0; loop < L; loop++)
        {
            win(loop) = win0(loop);
        }
    }
    else if(flag == 2)//symmetric
    {
        FatTopWindow0(win, L, flag);
    }
}
void AvailableWindows::GaussianWindow(vec &win, int L, double alpha)
{
    // Gaussian window.

    // The parameter for the gausswin() function is different for the Matlab, Octave, and SciPy versions of
    // this function:

    // - Matlab uses "Alpha", with a default value of 2.5.
    // - Octave uses "A";
    // - Scipy uses "std".

    //  Matlab vs SciPy:     Alpha * std == (N - 1) / 2

    //  Matlab vs Octave:    Alpha * N == A * (N - 1)

    // In this implementation, we follow the Matlab convention.

    if (L == 1)
    {
        // Special case for n == 1.
        win[0] = 1.0;
    }
    else
    {
        for (int i = 0; i < L; ++i)
        {
            const double x = fabs(2.0 * i - (L - 1)) / (double)(L - 1);
            const double ax = alpha * x;
            const double ax_squared = ax * ax;
            win[i] = exp( -0.5 * ax_squared);
        }
    }
}

void AvailableWindows::HammingWindow0(vec &win, int L, int flag)
{
    double f = 0.0;
    double N;

    if(flag == 1)//periodic
    {
        N = L - 1;
    }
    else if(flag == 2)//symmetric
    {
        N = L;
    }

    for (int loop = 0; loop < L; loop++)
    {
        f = 2*M_PI*loop/(double)N;
        win(loop) = 0.54 - (0.46 * std::cos(f));
    }

}
void AvailableWindows::HammingWindow(vec &win, int L, int flag)
{
    if(flag == 1)//periodic
    {
        vec win0(L+1);
        HammingWindow0(win0, L+1, flag);

        for (int loop = 0; loop < L; loop++)
        {
            win(loop) = win0(loop);
        }
    }
    else if(flag == 2)//symmetric
    {
        HammingWindow0(win, L, flag);
    }
}

void AvailableWindows::HannWindow0(vec &win, int L, int flag)
{
    double f = 0.0;
    double N;
    if(flag == 1)//periodic
    {
        N = L - 1;
    }
    else if(flag == 2)//symmetric
    {
        N = L;
    }

    for (int loop = 0; loop < L; loop++)
    {
        f = 2*M_PI*loop/(double)N;
        win(loop) = 0.5*(1 - std::cos(f));
    }

}
void AvailableWindows::HannWindow(vec &win, int L, int flag)
{
    if(flag == 1)//periodic
    {
        vec win0(L+1);
        HannWindow0(win0, L+1, flag);

        for (int loop = 0; loop < L; loop++)
        {
            win(loop) = win0(loop);
        }
    }
    else if(flag == 2)//symmetric
    {
        HannWindow0(win, L, flag);
    }
}
void AvailableWindows::KaiserWindow(vec &win, int L, double beta)
{
    // Kaiser window.
    //
    // In Matlab, the default value for parameter beta is 0.5.

    if (L == 1)
    {
        // Special case for n == 1.
        win[0] = 1.0;
    }
    else
    {
        for (int i = 0; i < L; ++i)
        {
            const double x = (2.0 * i - (L - 1)) /(double)(L - 1);

            win[i] = gsl_sf_bessel_I0(beta * sqrt(1.0 - x * x)) / gsl_sf_bessel_I0(beta);
        }
    }
}

void AvailableWindows::NuttallBlackmanHarrisWindow0(vec &win, int L, int flag)
{
    double f = 0.0;
    double N;
    if(flag == 1)//periodic
    {
        N = L - 1;
    }
    else if(flag == 2)//symmetric
    {
        N = L;
    }

    if(flag == 1)//periodic
    {
        for (int loop = 0; loop < L; loop++)
        {
            f = 2*M_PI*loop/(double)N;
            win(loop) = 0.3635819 - (0.4891775 * std::cos(f)) + (0.1365995*std::cos(2.0*f)) - (0.0106411*std::cos(3.0*f));
        }
    }
    else if(flag == 2)//symmetric
    {
        for (int loop = 0; loop < L; loop++)
        {
            f = 2*M_PI*loop/(double)(N-1);
            win(loop) = 0.3635819 - (0.4891775 * std::cos(f)) + (0.1365995*std::cos(2.0*f)) - (0.0106411*std::cos(3.0*f));
        }
    }
}

void AvailableWindows::NuttallBlackmanHarrisWindow(vec &win, int L, int flag)
{
    if(flag == 1)//periodic
    {
        vec win0(L+1);
        NuttallBlackmanHarrisWindow0(win0, L+1, flag);

        for (int loop = 0; loop < L; loop++)
        {
            win(loop) = win0(loop);
        }
    }
    else if(flag == 2)//symmetric
    {
        NuttallBlackmanHarrisWindow0(win, L, flag);
    }
}

void AvailableWindows::ParzenWindow(vec &win, int L)
{
    // The Parzen window.
    //
    // This is an approximation of the Gaussian window.
    // The Gaussian shape is approximated by two different polynomials, one for x < 0.5 and one for x > 0.5.
    // At x == 0.5, the polynomials meet. The minimum value of the two polynomials is taken.

    if (L == 1)
    {
        // Special case for n == 1.
        win[0] = 1.0;
    }
    else
    {
        for (int i = 0; i < L; ++i)
        {
            const double x = fabs(2.0 * i - (L - 1)) / (double)L;
            const double y = 1.0 - x;

            win[i] = fmin(1.0 - 6.0 * x * x + 6.0 * x * x * x, 2.0 * y * y * y);
        }
    }
}
void AvailableWindows::RectangularWindow(vec &win, int L)
{
    for (int i = 0; i < L; ++i)
    {
        win[i] = 1.0;
    }
}
void AvailableWindows::TrapezedCosineWindow(vec &win, int L, double r)
{
    // Tukey window.

    // This window uses a cosine-shaped ramp-up and ramp-down, with an all-one part in the middle.
    // The parameter 'r' defines the fraction of the window covered by the ramp-up and ramp-down.

    // r <= 0 is identical to a rectangular window.
    // r >= 1 is identical to a Hann window.
    //
    // In Matlab, the default value for parameter r is 0.5.

    if (L == 1)
    {
        // Special case for n == 1.
        win[0] = 1.0;
    }
    else
    {
        r = fmax(0.0, fmin(1.0, r)); // Clip between 0 and 1.

        for (int i = 0; i < L; ++i)
        {
            win[i] = (cos(fmax(fabs((double)i - (L - 1) / 2.0) * (2.0 / (double)(L - 1) / r)  - (1.0 / r - 1.0), 0.0) * M_PI) + 1.0) / 2.0;
        }
    }
}
void AvailableWindows::TriangularWindow(vec &win, int L)
{
    if (L == 1)
    {
        // Special case for n == 1.
        win[0] = 1.0;
    }
    else
    {
        if ( L % 2 == 0)
        {
            for (int loop = 1; loop <= L; loop++)
            {
                if(1 <= loop && loop <= L/2)
                {
                    win(loop - 1) = (2 * loop - 1)/(double)L;
                }
                else
                {
                    win(loop - 1) = 2 - ((2 * loop - 1)/(double)L);

                }
            }
        }
        else
        {
            for (int loop = 1; loop <= L; loop++)
            {
                if(1 <= loop && loop <= (L + 1)/2)
                {
                    win(loop - 1) = 2 * loop/(double)(L + 1);
                }
                else
                {
                    win(loop - 1) = 2 - (2 * loop/(double)(L + 1));

                }
            }
        }
    }
}
