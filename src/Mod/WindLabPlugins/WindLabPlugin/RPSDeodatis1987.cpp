

#include "RPSDeodatis1987.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSDeodatis1987, WindLabAPI::WindLabFeatureSimulationMethod)

CRPSDeodatis1987::CRPSDeodatis1987()
{

}


bool CRPSDeodatis1987::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    QMessageBox::warning(0,QString::fromLatin1("Deodatis method"), QString::fromLatin1("No additional data required."));
    return true;
}

bool CRPSDeodatis1987::Simulate(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray)
{
   const bool simResult = stationaryWind(Data, dVelocityArray);
   bool returnResult = true;

   if(!simResult)
   {
       Base::Console().Warning("The simulation has failed.\n");
       return simResult;
   }

   if(!Data.stationarity.getValue() && Data.uniformModulation.getValue())
   {
       vec modulationVar(Data.numberOfTimeIncrements.getValue());
       vec modulationVal(Data.numberOfTimeIncrements.getValue());
       mat dLocCoord(Data.numberOfSpatialPosition.getValue(), 4);

       bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);

       Base::Vector3d location(0, 0, 0);

       for (int j = 0; j < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
       {
           location = Base::Vector3d(dLocCoord(j, 1), dLocCoord(j, 2), dLocCoord(j, 3));

           returnResult = WindLabAPI::CRPSWindLabFramework::ComputeModulationVectorT(Data, location, modulationVar, modulationVal);

           for (int i = 0; i < Data.numberOfTimeIncrements.getValue() && false == Data.isInterruptionRequested.getValue(); i++)
           {
              dVelocityArray(i,j) = modulationVal(i) * dVelocityArray(i,j);
           }
       }

       if(!returnResult)
    {
       Base::Console().Warning("The computation of the modulation function has failed.\n") ;
       return false;
    }

   }
    //while (!Data.isInterruptionRequested.getValue()) {
    //    int a = 0.0;
    //    int b = a * 2*3;
    //}
   return true;
}

// The simulation function
bool CRPSDeodatis1987::stationaryWind(const WindLabAPI::WindLabSimuData& Data, mat &dVelocityArray)
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

    int n = Data.numberOfSpatialPosition.getValue();
    int N = Data.numberOfFrequency.getValue();
    double dt = Data.timeIncrement.getValue();
    double timeMin = Data.minTime.getValue();
    double deltaomega = Data.frequencyIncrement.getValue();
    int M = 2*N;
    int T = Data.numberOfTimeIncrements.getValue();

    cx_mat decomposedPSD2D(n, n);
    cx_cube decomposedPSD3D(n, n, N);
    
    cx_cube B(n, n, M);
    cx_cube G(n, n, M);
    B.setZero();
    G.setZero();

    cx_vec xxx(M);
    cx_vec yyy(M);
    xxx.setZero();
    yyy.setZero();

    // local array for the location coordinates
    mat dLocCoord(n, 4);
    mat frequencies(N,n);

    //compute the simulation point coordinates
    bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
    
    if(!returnResult)
    {
       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
       return false;
    }

    // generate n sequences of random phase angles phi(l), l = 1, 2, ..., N
    mat thet(N, n);
    returnResult = WindLabAPI::CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
    
    if(!returnResult)
    {
       Base::Console().Warning("The generation of the random phase matrix has failed.\n") ;
       return false;
    }

    // compute le frequency matrix. Note that this method required the double indexing frequency
    returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequenciesMatrixFP(Data, frequencies);

    if(!returnResult)
    {
       Base::Console().Warning("The computation of the frequency increments has failed.\n") ;
       return false;
    }

        // the imaginary i
    std::complex<double> i2(0, 1);

    // fast fourier transform
    Eigen::FFT<double> fft;

    // this method is for stationry wind. Spectrum is not function of time
    double time = 0;

    for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++) {
       for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++) { 
           returnResult = WindLabAPI::CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, frequencies(l - 1, m - 1), time, decomposedPSD2D);
           for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++) {
               decomposedPSD3D(j - 1, m - 1, l - 1) = decomposedPSD2D(j - 1, m - 1);
           }
       }

       // compute matrix B
       for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
           for (int j = 1; j <= m && false == Data.isInterruptionRequested.getValue(); j++) {
               B(m - 1, j - 1, l - 1) = 2 * sqrt(deltaomega)
                   * abs(decomposedPSD3D(m - 1, j - 1, l - 1)) * exp(i2 * thet(l - 1, j - 1));
           }
       }

       //compute matrix G
       for (int j = 1; j <= m && false == Data.isInterruptionRequested.getValue(); j++) {
           for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue(); l++) {
               xxx(l - 1) = B(m - 1, j - 1, l - 1);
           }

           yyy = (double)(M)*fft.inv(xxx);

           for (int l = 1; l <= M && false == Data.isInterruptionRequested.getValue(); l++) {
               G(m - 1, j - 1, l - 1) = yyy(l - 1);
           }
       }

       double time = 0;
       int q = 0;
       // Generate the wind velocity

       for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue(); p++) {
           q = fmod(p - 1, M);
           for (int k = 1; k <= m && false == Data.isInterruptionRequested.getValue(); k++) {
               time = (p - 1) * dt + timeMin;
               dVelocityArray(p - 1, 0) = time;
               dVelocityArray(p - 1, m) = dVelocityArray(p - 1, m) + real(G(m - 1, k - 1, q) * exp(i2 * ((k)*deltaomega * (time) / n)));
           }
       }
    }
    return returnResult;
}

// The simulation function in large scale mode
bool CRPSDeodatis1987::SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName)
{
//    WindLabFeatureDescription frequencyDistrDescription = WindLabAPI::CRPSWindLabFramework::getFrequencyDistributionObjDescription(Data.frequencyDistribution.getValue());
//
////if(NULL == &frequencyDistrDescription)
////    {
////       Base::Console().Warning("Invalid frequency distribution. The simulation has failed.\n") ;
////       return false;
////    }
//    
//    if(Data.frequencyDistribution.getValue() != "Double Index Frequency" ||
//       frequencyDistrDescription.PluginName != "windLab")
//    {
//        Base::Console().Warning("This tool required the wind velocity to be simulated with the double index frequency distribution implemented by the windLab plugin.");
//        return false;
//    }
//
//         // Define an output stream
//         std::ofstream fout;
//
//         // open the file output mode to erase its content first
//         fout.width(10);
//         fout.setf(std::ios::left);
//         fout.setf(std::ios::fixed);
//         fout.fill('0');
//         fout.open(strFileName.toStdString(), std::ios::out);
//
//         double value;
//
//         int n = Data.numberOfSpatialPosition.getValue();
//         int N = Data.numberOfFrequency.getValue();
//         double dt = Data.timeIncrement.getValue();
//         double deltaomega = Data.frequencyIncrement.getValue();
//         int M = 2*N;
//         int T = Data.numberOfTimeIncrements.getValue();
//
//         mat PSD1(n,N);
//         cube PSD2(n,n,N);
//         mat PSD3(n,n);
//         mat PSD4(n,n);
//         cube PSD5(n,n,N);
//         cube PSD(n,n,N);
//
//         cube Kz(n,n,N);
//
//         cx_vec xxx(M);
//         cx_vec yyy(M);
//
//         cx_cube B (n,n,M);
//         cx_cube G (n,n,M);
//
//         B.setZero();
//         G.setZero();
//
//         xxx.setZero();
//         yyy.setZero();
//
//         // local array for the location coordinates
//         mat dLocCoord(n, 4);
//         mat frequencies(N,n);
//
//         bool returnResult = WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord);
//
//       if(!returnResult)
//       {
//       Base::Console().Warning("The computation of the location coordinates matrix has failed.\n") ;
//       return false;
//       }
//         mat thet(N, n);
//         returnResult = WindLabAPI::CRPSWindLabFramework::GenerateRandomMatrixFP(Data, thet);
//       
//       if(!returnResult)
//       {
//       Base::Console().Warning("The computation of the random phase matrix has failed.\n") ;
//       return false;
//       }
//         std::complex<double> i2(0, 1);
//         Eigen::FFT<double> fft;
//
//         for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++)
//         {
//             for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
//             {
//                returnResult = WindLabAPI::CRPSWindLabFramework::ComputeFrequencyValue(Data, frequencies(l - 1, m-1), m-1, l - 1);
//             }
//         }
//
//         for (int i = 1; i <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
//         {
//             // Simulation starts
//             for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
//             {
//                 for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
//                 {
//                     // compute auto spectrum Sj(w)
//                     returnResult = WindLabAPI::CRPSWindLabFramework::ComputeCrossSpectrumValue(Data,
//                                                                      PSD1(j-1, l-1),
//                                                                      dLocCoord(j-1,1),
//                                                                      dLocCoord(j-1,2),
//                                                                      dLocCoord(j-1,3),
//                                                                      frequencies(l - 1,j-1),
//                                                                      0);
//
//                     // compte cross coherence Cohjm(w)
//                     for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++)
//                     {
//
//                         returnResult = WindLabAPI::CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, Kz(j-1, m-1, l-1),
//                                                                     dLocCoord(j-1,1),
//                                                                     dLocCoord(j-1,2),
//                                                                     dLocCoord(j-1,3),
//                                                                     dLocCoord(m-1,1),
//                                                                     dLocCoord(m-1,2),
//                                                                     dLocCoord(m-1,3),
//                                                                     frequencies(l - 1,m-1),
//                                                                     0);
//
//
//                         PSD2(j-1, m-1, l-1) = sqrt(PSD1(j-1, l-1)*PSD1(m-1, l-1))*Kz(j-1, m-1, l-1);
//
//                         PSD3(j-1, m-1) = PSD2(j-1, m-1, l-1);
//
//                     }
//
//                 }
//
//                 returnResult = WindLabAPI::CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, PSD4, PSD3);
//
//                 for (int j = 1; j <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
//                 {
//                     for (int m = 1; m <= n && false == Data.isInterruptionRequested.getValue() && true == returnResult; m++)
//                     {
//
//                         PSD5(j-1, m-1, l-1) =  PSD4(j-1, m-1);
//                     }
//
//                      PSD(j-1, i-1, l-1) =  PSD5(j-1, i-1, l-1);
//                 }
//
//             }
//
//             for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
//             {
//                 for (int ii = 1; ii <= i && false == Data.isInterruptionRequested.getValue() && true == returnResult; ii++)
//                 {
//                      B(i-1, ii-1, l-1) = 2*sqrt(deltaomega)*abs(PSD(i-1, ii-1, l-1))*exp(i2*thet(l - 1,ii - 1));
//                 }
//             }
//
//             for (int ii = 1; ii <= i && false == Data.isInterruptionRequested.getValue() && true == returnResult; ii++)
//             {
//                 for (int l = 1; l <= N && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
//                 {
//                     xxx(l-1) =B(i-1, ii-1, l-1);
//
//                 }
//
//                 yyy = (double)(M) *fft.inv(xxx);
//
//
//                 for (int l = 1; l <= M && false == Data.isInterruptionRequested.getValue() && true == returnResult; l++)
//                 {
//                     G(i-1, ii-1, l-1) = yyy(l-1);
//
//                 }
//
//             }
//
//             int q = 0;
//             // Generate the wind velocity
//             for (int p = 1; p <= T && false == Data.isInterruptionRequested.getValue() && true == returnResult; p++) {
//                 q = fmod(p-1,M);
//                 value = 0.0;
//                 for (int k = 1; k <= i && false == Data.isInterruptionRequested.getValue() && true == returnResult; k++) {
//                     value = value + real(G(i-1,k - 1,q)*exp(i2*((k)*deltaomega*(p-1)*dt/n)));
//                 }
//
//                 fout << value << "\t";
//             }
//
//             fout << std::endl;	// New colum
//         }
//
//         fout.close();
//
//         return returnResult;

return false;
}
