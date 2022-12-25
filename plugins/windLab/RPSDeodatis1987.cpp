
#include "RPSDeodatis1987.h"
#include "RPSWindLabFramework.h"
#include <../../3rdparty/eigen-3.4.0/unsupported/Eigen/FFT>

#include <QMessageBox>
#include <QThread>
#include <fstream>

//Initial setting
bool CRPSDeodatis1987::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
    QMessageBox::warning(0,"Deodatis method", "No additional data required.");
    return true;
}

bool CRPSDeodatis1987::Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation)
{
   const bool simResult = stationaryWind(Data, dVelocityArray, strInformation);
   bool returnResult = true;

   if(!simResult)
   {
       strInformation.append("The simulation has failed.");
       return simResult;
   }

   if(!Data.stationarity)
   {
       vec modulationVar(Data.numberOfTimeIncrements);
       vec modulationVal(Data.numberOfTimeIncrements);

       for (int j = 0; j < Data.numberOfSpatialPosition && false == Data.isInterruptionRequested && true == returnResult; j++)
       {
           returnResult = CRPSWindLabFramework::ComputeModulationVectorT(Data, modulationVar, modulationVal, strInformation);

           for (int i = 0; i < Data.numberOfTimeIncrements && false == Data.isInterruptionRequested; i++)
           {
              dVelocityArray(i,j) = modulationVal(i) * dVelocityArray(i,j);
           }
       }

       if(!returnResult)
    {
       strInformation.append("The computation of the modulation function has failed.") ;
       return false;
    }

   }

   return true;
}

// The simulation function
bool CRPSDeodatis1987::stationaryWind(const CRPSWindLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation)
{
    ObjectDescription frequencyDistrDescription = CRPSWindLabFramework::getFrequencyDistributionObjDescription(Data.freqencyDistribution);

//if(NULL = frequencyDistrDescription)
//    {
//       strInformation.append("Invalid frequency distribution. The simulation has failed.") ;
//       return false;
//    }
    if(Data.freqencyDistribution != "Double Index Frequency" ||
       frequencyDistrDescription.m_pluginName != "windLab")
    {
        strInformation.append("This tool required the wind velocity to be simulated with the double index frequency distribution implemented by the windLab plugin.");
        return false;
    }

    int n = Data.numberOfSpatialPosition;
    int N = Data.numberOfFrequency;
    double dt = Data.timeIncrement;
    double deltaomega = Data.frequencyIncrement;
    int M = 2*N;
    int T = Data.numberOfTimeIncrements;

    mat PSD1(n,N);
    cube PSD2(n,n,N);
    mat PSD3(n,n);
    mat PSD4(n,n);
    cube PSD5(n,n,N);
    cube PSD(n,n,N);

    cube Kz(n,n,N);

    cx_vec xxx(M);
    cx_vec yyy(M);

    cx_cube B (n,n,M);
    cx_cube G (n,n,M);

    B.setZero();
    G.setZero();

    xxx.setZero();
    yyy.setZero();

    // local array for the location coordinates
    mat dLocCoord(n, 3);
    mat frequencies(N,n);

    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    if(!returnResult)
    {
       strInformation.append("The computation of the location coordinates matrix has failed.") ;
       return false;
    }

    mat thet(N, n);
    returnResult = CRPSWindLabFramework::GenerateRandomArrayFP(Data, thet, strInformation);
    
    if(!returnResult)
    {
       strInformation.append("The computation of the random phase matrix has failed.") ;
       return false;
    }

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;

    for (int m = 1; m <= n && false == Data.isInterruptionRequested && true == returnResult; m++)
    {
        for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
        {
           returnResult = CRPSWindLabFramework::ComputeFrequencyValue(Data, frequencies(l - 1, m-1), m-1, l - 1, strInformation);
        }
    }

   if(!returnResult)
    {
       strInformation.append("The computation of the frequencies matrix has failed.") ;
       return false;
    }

    for (int i = 1; i <= n && false == Data.isInterruptionRequested && true == returnResult; i++)
    {
        // Simulation starts
        for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
        {
            for (int j = 1; j <= n && false == Data.isInterruptionRequested && true == returnResult; j++)
            {
                // compute auto spectrum Sj(w)
                returnResult = CRPSWindLabFramework::ComputeAutoSpectrumValue(Data,
                                                                 PSD1(j-1, l-1),
                                                                 dLocCoord(j-1,0),
                                                                 dLocCoord(j-1,1),
                                                                 dLocCoord(j-1,2),
                                                                 frequencies(l - 1,j-1),
                                                                 0,
                                                                 strInformation);

                // compte cross coherence Cohjm(w)
                for (int m = 1; m <= n && false == Data.isInterruptionRequested && true == returnResult; m++)
                {

                    returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, Kz(j-1, m-1, l-1),
                                                                dLocCoord(j-1,0),
                                                                dLocCoord(j-1,1),
                                                                dLocCoord(j-1,2),
                                                                dLocCoord(m-1,0),
                                                                dLocCoord(m-1,1),
                                                                dLocCoord(m-1,2),
                                                                frequencies(l - 1,m-1),
                                                                0,
                                                                strInformation);


                    PSD2(j-1, m-1, l-1) = sqrt(PSD1(j-1, l-1)*PSD1(m-1, l-1))*Kz(j-1, m-1, l-1);

                    PSD3(j-1, m-1) = PSD2(j-1, m-1, l-1);

                }

            }

            returnResult = CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, PSD4, PSD3, strInformation);

            for (int j = 1; j <= n && false == Data.isInterruptionRequested && true == returnResult; j++)
            {
                for (int m = 1; m <= n && false == Data.isInterruptionRequested && true == returnResult; m++)
                {

                    PSD5(j-1, m-1, l-1) =  PSD4(j-1, m-1);
                }

                 PSD(j-1, i-1, l-1) =  PSD5(j-1, i-1, l-1);
            }

        }

        for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
        {
            for (int ii = 1; ii <= i && false == Data.isInterruptionRequested && true == returnResult; ii++)
            {
                 B(i-1, ii-1, l-1) = 2*sqrt(deltaomega)*abs(PSD(i-1, ii-1, l-1))*exp(i2*thet(l - 1,ii - 1));
            }
        }

        for (int ii = 1; ii <= i && false == Data.isInterruptionRequested && true == returnResult; ii++)
        {
            for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
            {
                xxx(l-1) =B(i-1, ii-1, l-1);

            }

            yyy = (double)(M) *fft.inv(xxx);


            for (int l = 1; l <= M && false == Data.isInterruptionRequested; l++)
            {
                G(i-1, ii-1, l-1) = yyy(l-1);

            }

        }

        int q = 0;
        // Generate the wind velocity
        for (int p = 1; p <= T && false == Data.isInterruptionRequested && true == returnResult; p++) {
            q = fmod(p-1,M);
            for (int k = 1; k <= i && false == Data.isInterruptionRequested && true == returnResult; k++) {

                dVelocityArray(p - 1, i - 1) = dVelocityArray(p - 1, i - 1) + real(G(i-1,k - 1,q) * exp(i2*((k)*deltaomega*(p-1)*dt/n)));
            }
        }
    }

    return returnResult;
}

// The simulation function in large scale mode
bool CRPSDeodatis1987::SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, QStringList &strInformation)
{
    ObjectDescription frequencyDistrDescription = CRPSWindLabFramework::getFrequencyDistributionObjDescription(Data.freqencyDistribution);

//if(NULL == &frequencyDistrDescription)
//    {
//       strInformation.append("Invalid frequency distribution. The simulation has failed.") ;
//       return false;
//    }
    
    if(Data.freqencyDistribution != "Double Index Frequency" ||
       frequencyDistrDescription.m_pluginName != "windLab")
    {
        strInformation.append("This tool required the wind velocity to be simulated with the double index frequency distribution implemented by the windLab plugin.");
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

         int n = Data.numberOfSpatialPosition                       ;
         int N = Data.numberOfFrequency                    ;
         double dt = Data.timeIncrement            ;
         double deltaomega = Data.frequencyIncrement           ;
         int M = 2*N                     ;
         int T = Data.numberOfTimeIncrements;

         mat PSD1(n,N);
         cube PSD2(n,n,N);
         mat PSD3(n,n);
         mat PSD4(n,n);
         cube PSD5(n,n,N);
         cube PSD(n,n,N);

         cube Kz(n,n,N);

         cx_vec xxx(M);
         cx_vec yyy(M);

         cx_cube B (n,n,M);
         cx_cube G (n,n,M);

         B.setZero();
         G.setZero();

         xxx.setZero();
         yyy.setZero();

         // local array for the location coordinates
         mat dLocCoord(n, 3);
         mat frequencies(N,n);

         bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

       if(!returnResult)
       {
       strInformation.append("The computation of the location coordinates matrix has failed.") ;
       return false;
       }
         mat thet(N, n);
         returnResult = CRPSWindLabFramework::GenerateRandomArrayFP(Data, thet, strInformation);
       
       if(!returnResult)
       {
       strInformation.append("The computation of the random phase matrix has failed.") ;
       return false;
       }
         std::complex<double> i2(0, 1);
         Eigen::FFT<double> fft;

         for (int m = 1; m <= n && false == Data.isInterruptionRequested && true == returnResult; m++)
         {
             for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
             {
                returnResult = CRPSWindLabFramework::ComputeFrequencyValue(Data, frequencies(l - 1, m-1), m-1, l - 1, strInformation);
             }
         }

         for (int i = 1; i <= n && false == Data.isInterruptionRequested && true == returnResult; i++)
         {
             // Simulation starts
             for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
             {
                 for (int j = 1; j <= n && false == Data.isInterruptionRequested && true == returnResult; j++)
                 {
                     // compute auto spectrum Sj(w)
                     returnResult = CRPSWindLabFramework::ComputeAutoSpectrumValue(Data,
                                                                      PSD1(j-1, l-1),
                                                                      dLocCoord(j-1,0),
                                                                      dLocCoord(j-1,1),
                                                                      dLocCoord(j-1,2),
                                                                      frequencies(l - 1,j-1),
                                                                      0,
                                                                      strInformation);

                     // compte cross coherence Cohjm(w)
                     for (int m = 1; m <= n && false == Data.isInterruptionRequested && true == returnResult; m++)
                     {

                         returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, Kz(j-1, m-1, l-1),
                                                                     dLocCoord(j-1,0),
                                                                     dLocCoord(j-1,1),
                                                                     dLocCoord(j-1,2),
                                                                     dLocCoord(m-1,0),
                                                                     dLocCoord(m-1,1),
                                                                     dLocCoord(m-1,2),
                                                                     frequencies(l - 1,m-1),
                                                                     0,
                                                                     strInformation);


                         PSD2(j-1, m-1, l-1) = sqrt(PSD1(j-1, l-1)*PSD1(m-1, l-1))*Kz(j-1, m-1, l-1);

                         PSD3(j-1, m-1) = PSD2(j-1, m-1, l-1);

                     }

                 }

                 returnResult = CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, PSD4, PSD3, strInformation);

                 for (int j = 1; j <= n && false == Data.isInterruptionRequested && true == returnResult; j++)
                 {
                     for (int m = 1; m <= n && false == Data.isInterruptionRequested && true == returnResult; m++)
                     {

                         PSD5(j-1, m-1, l-1) =  PSD4(j-1, m-1);
                     }

                      PSD(j-1, i-1, l-1) =  PSD5(j-1, i-1, l-1);
                 }

             }

             for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
             {
                 for (int ii = 1; ii <= i && false == Data.isInterruptionRequested && true == returnResult; ii++)
                 {
                      B(i-1, ii-1, l-1) = 2*sqrt(deltaomega)*abs(PSD(i-1, ii-1, l-1))*exp(i2*thet(l - 1,ii - 1));
                 }
             }

             for (int ii = 1; ii <= i && false == Data.isInterruptionRequested && true == returnResult; ii++)
             {
                 for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
                 {
                     xxx(l-1) =B(i-1, ii-1, l-1);

                 }

                 yyy = (double)(M) *fft.inv(xxx);


                 for (int l = 1; l <= M && false == Data.isInterruptionRequested && true == returnResult; l++)
                 {
                     G(i-1, ii-1, l-1) = yyy(l-1);

                 }

             }

             int q = 0;
             // Generate the wind velocity
             for (int p = 1; p <= T && false == Data.isInterruptionRequested && true == returnResult; p++) {
                 q = fmod(p-1,M);
                 value = 0.0;
                 for (int k = 1; k <= i && false == Data.isInterruptionRequested && true == returnResult; k++) {
                     value = value + real(G(i-1,k - 1,q)*exp(i2*((k)*deltaomega*(p-1)*dt/n)));
                 }

                 fout << value << "\t";
             }

             fout << std::endl;	// New colum
         }

         fout.close();

         return returnResult;
}
