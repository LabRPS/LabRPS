/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "WWYang1997Ind.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include "widgets/wwyang1997indinputdlg.h"
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>

using namespace WindLab;
using namespace WindLabAPI;

CWWYang1997Ind::CWWYang1997Ind()
{
numberOfLocation = 3;
numberOfFrequencies = 1024;
locationHeight = 40;
locationSpacing = 5;
meanSpeed = 36.4038;
shearVelocity = 1.76;
upperCutoffFrequency = 4*3.14;
numberOfTimeIncrements = 2*numberOfLocation*numberOfFrequencies;
}
//Initial setting
bool CWWYang1997Ind::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    // the input diolag
    std::unique_ptr<WWYang1997IndInputDlg> dlg(new WWYang1997IndInputDlg(numberOfLocation, numberOfFrequencies, locationHeight, locationSpacing, meanSpeed, shearVelocity, upperCutoffFrequency, numberOfTimeIncrements));

	if (dlg->exec() == QDialog::Accepted) //
	{
        numberOfLocation = dlg->m_numberOfLocation;
        numberOfFrequencies = dlg->m_numberOfFrequencies;
        locationHeight = dlg->m_locationHeight;
        locationSpacing = dlg->m_locationSpacing;
        meanSpeed = dlg->m_meanSpeed;
        shearVelocity = dlg->m_shearVelocity;
        upperCutoffFrequency = dlg->m_upperCutoffFrequency;
        numberOfTimeIncrements = dlg->m_numberOfTimeIncrements;

	}

	return true;
}

// The simulation function 
bool CWWYang1997Ind::Simulate(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray)
{
    auto PbuInfo = CRPSWindLabFramework::getWindLabFeatureDescription(Data.frequencyDistribution.getValue());

    if (!PbuInfo)
    {
       Base::Console().Warning("Invalid frequency distribution. The simulation has failed.\n") ;
       return false;
    }

    if ((PbuInfo->type.getValue(), "Double Index Frequency") == 0 || (PbuInfo->PluginName.getValue(), "WindLabPlugin") == 0)
    {
        Base::Console().Warning("This tool required the wind velocity to be simulated with the double index frequency distribution implemented by the windLab plugin.\n");
        return false;
    }

    int n = numberOfLocation                   ;//the number of location. These locations are evenly distributed at the same height.
    int N = numberOfFrequencies                ;//the number of frequency increments
    double speed = meanSpeed                   ;//the  mean wind speed at the locations's height
    double z = locationHeight                  ;//the height of the locations
    double dy = locationSpacing                ;//the spacing of the locations
    double Uo = shearVelocity                  ;//the shear velocity of the flow
    double wu = upperCutoffFrequency           ;//the upper cutoff frequency
    double Cy = 7                              ;//the decay constant in y direction for the Davenport choherence function
    double pi = 3.14                           ;//the constant pi
    double dt = 2*pi/(2*wu)                    ;//the time increment
    double deltaomega = (double)(wu/(double)N) ;//the frequency increment
    int M = 2*N                                ;//the lenght of fft
    int T = numberOfTimeIncrements             ;//the number of time increment
    vec w(N)                                   ;//the frequency increments vector
    vec t(M*n)                                 ;//the time increment vector
    vec PSD1(N)                                ;//vector containing the auto spectrum
    vec Kz(N)                                  ;//vector containing the cross coherence

    cx_mat B = Eigen::MatrixXcd::Zero(n,M)     ;
    cx_mat G = Eigen::MatrixXcd::Zero(n,M)     ;

    mat thet(N, n)                             ;
    bool returnResult = CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);

    if(!returnResult)
    {
       Base::Console().Warning("The computation of the random phase angle matrix has failed.") ;
       return false;
    }

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;

    double C1;
    double C2;
    double C3;

    // Simulation starts
    for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue(); j++)
    {
        for (int m = 1; m <= j && false == Data.isInterruptionRequested.getValue(); m++)
        {
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                w(l - 1)=(l - 1)*deltaomega+m/n*deltaomega;
            }

            // Auto spectrum
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                PSD1(l - 1)=200*z*Uo*Uo/2/pi/speed/(std::pow(1+50*w(l - 1)*z/speed/2/pi,5.0/3.0));
            }

            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                Kz(l - 1)=std::exp(-0.32*w(l - 1)*dy*Cy/(speed+speed));
            }

            //Compute element of matrix B
            //at point j
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                C1 = std::pow(PSD1(l-1),0.5)*std::pow(Kz(l-1),std::abs(m-j));

                if (m==1){
                    B(m - 1,l - 1) =2*std::sqrt(deltaomega)*C1*std::exp(i2*thet(l - 1,m - 1));
                }
                else{
                    C2 = std::pow(Kz(l-1),2);
                    C3 = std::pow(1-C2,0.5);
                    B(m - 1,l - 1) = 2*std::sqrt(deltaomega)*C1*C3*std::exp(i2*thet(l - 1,m - 1));
                }
            }

        }


        // Fast Fourier Transform (FFT)
        for (int ii = 1; ii <= j && false == Data.isInterruptionRequested.getValue(); ii++)
        {
            G.row(ii-1) = (double)(M) *fft.inv( B.row(ii-1) );

        }
        int q = 0;
        // Generate the wind velocity
        for (int p = 1; p <= M*n && false == Data.isInterruptionRequested.getValue(); p++) {
            q = std::fmod(p-1,M);
            for (int k = 1; k <= j && false == Data.isInterruptionRequested.getValue(); k++) {

                dVelocityArray(p - 1, j - 1)=dVelocityArray(p - 1, j - 1)+std::real(G(k - 1,q)*std::exp(i2*((k)*deltaomega*(p-1)*dt/n)));
            }
        }
    }

    return true;
}

// The simulation function in large scale mode
bool CWWYang1997Ind::SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName)
{
    auto PbuInfo = CRPSWindLabFramework::getWindLabFeatureDescription(Data.frequencyDistribution.getValue());

    if (!PbuInfo)
    {
       Base::Console().Warning("Invalid frequency distribution. The simulation has failed.\n") ;
       return false;
    }

    if ((PbuInfo->type.getValue(), "Double Index Frequency") == 0 || (PbuInfo->PluginName.getValue(), "WindLabPlugin") == 0)
    {
        Base::Console().Warning("This tool required the wind velocity to be simulated with the double index frequency distribution implemented by the windLab plugin.\n");
        return false;
    }
    
    // Define an output stream
    std::ofstream fout;

    // open the file output mode to erase its content first
    fout.width(10);
    fout.setf(std::ios::left);
    fout.setf(std::ios::fixed);
    fout.fill('0');
    fout.open(strFileName.toStdString(), std::ios::out);

    double value;

    int n = numberOfLocation                   ;//the number of location. These locations are evenly distributed at the same height.
    int N = numberOfFrequencies                ;//the number of frequency increments
    double speed = meanSpeed                   ;//the  mean wind speed at the locations's height
    double z = locationHeight                  ;//the height of the locations
    double dy = locationSpacing                ;//the spacing of the locations
    double Uo = shearVelocity                  ;//the shear velocity of the flow
    double wu = upperCutoffFrequency           ;//the upper cutoff frequency
    double Cy = 7                              ;//the decay constant in y direction for the Davenport choherence function
    double pi = 3.14                           ;//the constant pi
    double dt = 2*pi/(2*wu)                    ;//the time increment
    double deltaomega = (double)(wu/(double)N) ;//the frequency increment
    int M = 2*N                                ;//the lenght of fft
    int T = numberOfTimeIncrements             ;//the number of time increment
    vec w(N)                                   ;//the frequency increments vector
    vec t(M*n)                                 ;//the time increment vector
    vec PSD1(N)                                ;//vector containing the auto spectrum
    vec Kz(N)                                  ;//vector containing the cross coherence

    cx_mat B = Eigen::MatrixXcd::Zero(n,M)     ;
    cx_mat G = Eigen::MatrixXcd::Zero(n,M)     ;

    mat thet(N, n)                             ;
    bool returnResult = CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);

    if(!returnResult)
    {
       Base::Console().Warning("The computation of the random phase angle matrix has failed.") ;
       return false;
    }

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;

    double C1;
    double C2;
    double C3;

    // Simulation starts
    for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue(); j++)
    {
        for (int m = 1; m <= j && false == Data.isInterruptionRequested.getValue(); m++)
        {
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                w(l - 1)=(l - 1)*deltaomega+m/n*deltaomega;
            }

            // Auto spectrum
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                PSD1(l - 1)=200*z*Uo*Uo/2/pi/speed/(pow(1+50*w(l - 1)*z/speed/2/pi,5.0/3.0));
            }

            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                Kz(l - 1)=exp(-0.32*w(l - 1)*dy*Cy/(speed+speed));
            }

            //Compute element of matrix B
            //at point j
            for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++)
            {
                C1 = pow(PSD1(l-1),0.5)*pow(Kz(l-1),abs(m-j));

                if (m==1){
                    B(m - 1,l - 1) =2*sqrt(deltaomega)*C1*exp(i2*thet(l - 1,m - 1));
                }
                else{
                    C2 = pow(Kz(l-1),2);
                    C3 = pow(1-C2,0.5);
                    B(m - 1,l - 1) = 2*sqrt(deltaomega)*C1*C3*exp(i2*thet(l - 1,m - 1));
                }
            }

        }


        // Fast Fourier Transform (FFT)
        for (int ii = 1; ii <= j && false == Data.isInterruptionRequested.getValue(); ii++)
        {
            G.row(ii-1) = (double)(M) *fft.inv( B.row(ii-1) );

        }
        int q = 0;
         value = 0.0;
        // Generate the wind velocity
        for (int p = 1; p <= M*n && false == Data.isInterruptionRequested.getValue(); p++) {
            q = fmod(p-1,M);
            for (int k = 1; k <= j && false == Data.isInterruptionRequested.getValue(); k++) {

               value = value +real(G(k - 1,q)*exp(i2*((k)*deltaomega*(p-1)*dt/n)));
            }

            fout << value << "\t";

        }

        fout << std::endl;	// New colum

    }

    return true;
}
