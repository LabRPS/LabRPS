
#include "RPSDeodatis1987.h"
#include "RPSWindLabFramework.h"
#include "RPSWindLabTools.h"
#include <../../3rdparty/eigen-3.4.0/unsupported/Eigen/FFT>

#include <QMessageBox>
#include <QThread>


//Initial setting
bool CRPSDeodatis1987::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
    QMessageBox::warning(0,"hi", "in Deodatis method");
    return true;
}

// The simulation function 
bool CRPSDeodatis1987::Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, QStringList &strInformation)
{
    int n = Data.numberOfSpatialPosition                       ;
    int N = Data.numberOfFrequency                    ;
    double dt = Data.timeIncrement            ;
    double deltaomega = Data.frequencyIncrement           ;
    int M = 2*N                     ;

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

    // local array for the location coordinates
    mat dLocCoord(n, 3);
    mat frequencies(N,n);

    CRPSWindLabFramework:: ComputeFrequenciesMatrixFP(Data, frequencies, strInformation);
    CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);

    mat thet(N, n);
    CRPSWindLabFramework::GenerateRandomArrayFP(Data, thet, strInformation);

    std::complex<double> i2(0, 1);
    Eigen::FFT<double> fft;

    for (int i = 1; i <= n && false == Data.isInterruptionRequested; i++)
    {
        // Simulation starts
        for (int l = 1; l <= N && false == Data.isInterruptionRequested; l++)
        {
            for (int j = 1; j <= n && false == Data.isInterruptionRequested; j++)
            {
                // compute auto spectrum Sj(w)
                CRPSWindLabFramework::ComputeCrossSpectrumValue(Data,
                                                                 PSD1(j-1, l-1),
                                                                 dLocCoord(j-1,0),
                                                                 dLocCoord(j-1,1),
                                                                 dLocCoord(j-1,2),
                                                                 dLocCoord(j-1,0),
                                                                 dLocCoord(j-1,1),
                                                                 dLocCoord(j-1,2),
                                                                 frequencies(l - 1,j-1),
                                                                 0,
                                                                 strInformation);

                // compte cross coherence Cohjm(w)
                for (int m = 1; m <= n && false == Data.isInterruptionRequested; m++)
                {

                    CRPSWindLabFramework::ComputeCoherenceValue(Data, Kz(j-1, m-1, l-1),
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

            CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, PSD4, PSD3, strInformation);

            for (int j = 1; j <= n && false == Data.isInterruptionRequested; j++)
            {
                for (int m = 1; m <= n && false == Data.isInterruptionRequested; m++)
                {

                    PSD5(j-1, m-1, l-1) =  PSD4(j-1, m-1);
                }

                 PSD(j-1, i-1, l-1) =  PSD5(j-1, i-1, l-1);
            }

        }

        for (int l = 1; l <= N && false == Data.isInterruptionRequested; l++)
        {
            for (int ii = 1; ii <= i && false == Data.isInterruptionRequested; ii++)
            {
                 B(i-1, ii-1, l-1) = 2*sqrt(deltaomega)*abs(PSD(i-1, ii-1, l-1))*exp(i2*thet(l - 1,ii - 1));
            }
        }

        for (int ii = 1; ii <= i && false == Data.isInterruptionRequested; ii++)
        {
            for (int l = 1; l <= N && false == Data.isInterruptionRequested; l++)
            {
                xxx(l-1) =B(i-1, ii-1, l-1);

            }

            yyy = (double)(M) *fft.inv(xxx);


            for (int l = 1; l <= N && false == Data.isInterruptionRequested; l++)
            {
                G(i-1, ii-1, l-1) = yyy(l-1);

            }

        }

        int q = 0;
        // Generate the wind velocity
        for (int p = 1; p <= M*n && false == Data.isInterruptionRequested; p++) {
            q = fmod(p-1,M);
            for (int k = 1; k <= i && false == Data.isInterruptionRequested; k++) {

                dVelocityArray(p - 1, i - 1)=dVelocityArray(p - 1, i - 1)+real(G(i-1,k - 1,q)*exp(i2*((k)*deltaomega*(p-1)*dt/n)));
            }
        }
    }
    return true;
}

// The simulation function in large scale mode
bool CRPSDeodatis1987::SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, QStringList &strInformation)
{
    return true;
}

void CRPSDeodatis1987::ComputeCPSDDecom3DMatrice(const CRPSWindLabsimuData &Data, cube &dCPSDDecomMatrice, QStringList &strInformation)
{
    // // Local array for the frequencies vector
    // vec dFrequencies;

    // // Local array for the cpsd
    // mat dCPSDarray;

    // // Local 2D array for the decomposed cpsd
    // mat dCPSDdecomarray;

    // // Local 3D array for the decomposed cpsd
    // cube dCPSDdecop3Darray;

    // try
    // {
    // 	// Allocate memory for cpsd array
    // 	dCPSDarray.set_size(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);

    // 	// Allocate memory for the 2D cpsd decomposed array
    // 	dCPSDdecomarray.set_size(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition);

    // 	// Allocate memory for the 3D cpsd decomposed array
    // 	dCPSDdecop3Darray.set_size(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfFrequency);

    // 	dFrequencies.set_size(Data.numberOfFrequency);

    // }
    // catch (CMemoryException* pEx)
    // {
    // 	// Simply show an error message to the user.
    // 	pEx->ReportError();
    // 	pEx->Delete();
    // 	return;
    // }
    // catch (bad_alloc &ba)
    // {
    // 	QString msg(ba.what());
    // 	AfxMessageBox(msg);
    // 	return;
    // }

    // QString msg = ("");

    // for (int loop = 1; loop <= Data.numberOfSpatialPosition && false == Data.isInterruptionRequested; loop++)
    // {
    // 	// Compute the single index frequency (Shinozuka)
    // 	CRPSWindLabFramework::ComputeFrequenciesVectorF(Data, dFrequencies, strInformation);

    // 	// For each frequency increment
    // 	for (int loop3 = 0; loop3 < Data.numberOfFrequency && false == Data.isInterruptionRequested; loop3++)
    // 	{
    // 		// Compute psd matrix for each fequency increment
    // 		CRPSWindLabFramework::ComputeCrossSpectrumMatrixPP(Data, dCPSDarray, strInformation);

    // 		// Compute the cholesky decomposition of the psd matrix
    // 		//CRPSWindLabTools::RPSComputeCholeskyDecomposition(dCPSDarray, Data.numberOfSpatialPosition, dCPSDdecomarray);
    // 		dCPSDdecomarray = chol(dCPSDarray, "lower");

    // 		// For each row
    // 		for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition && false == Data.isInterruptionRequested; loop1++)
    // 		{
    // 			// For each col
    // 			for (int loop2 = 0; loop2 <= loop1 && false == Data.isInterruptionRequested; loop2++)
    // 			{
    // 				// Save each cholesky decomposed matrix in a 3D matrix
    // 				dCPSDdecop3Darray(loop1, loop2, loop3) = dCPSDdecomarray(loop1, loop2);
    // 			}
    // 		}
    // 	}

    // 	// Save only the loop-th colum of each 3D decomposed psd matrix
    // 	for (int loop1 = 0; loop1 < Data.numberOfSpatialPosition && false == Data.isInterruptionRequested; loop1++)
    // 	{
    // 		// For each col
    // 		for (int loop2 = 0; loop2 < Data.numberOfFrequency && false == Data.isInterruptionRequested; loop2++)
    // 		{
    // 			dCPSDDecomMatrice(loop1, loop - 1, loop2) = dCPSDdecop3Darray(loop1, loop - 1, loop2);
    // 		}
    // 	}
    // }

}
