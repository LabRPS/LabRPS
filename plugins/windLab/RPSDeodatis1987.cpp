
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
bool CRPSDeodatis1987::Simulate(const CRPSWindLabsimuData &Data, mat &dVelocityArray, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation)
{
	// Locale array for the Cholesky decomposed cpsd
	cube dCPSDdecompArray(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfFrequency) ;
	
	//Computing the decomposed psd matrix
	CRPSWindLabFramework::ComputeCrossSpectrumCubePPF(Data, dCPSDdecompArray, strInformation);
    
	// allocate memory for random phases
	mat  drandomPhase(Data.numberOfFrequency, Data.numberOfSpatialPosition);		
    
	// allocate memories for the complex B matrix
    cx_cube dBMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, 2 * Data.numberOfFrequency);
	cx_cube dGMatrix(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, 2 * Data.numberOfFrequency);
	cx_vec xxx(2 * Data.numberOfFrequency);
	cx_vec yyy(2 * Data.numberOfFrequency);
	//std::vector<std::complex<float>> yyy;
	
	std::complex<double> ii(0, 1);

	QString SimuMsg;

	// Generate random phase angle uniformly distribuated over [0, 2*pi]
	CRPSWindLabFramework::GenerateRandomArrayFP(Data, drandomPhase, strInformation);

	// fast Fourier transform in process
	for (int loop = 1; loop <= Data.numberOfSpatialPosition && false == Data.isInterruptionRequested; loop++)
	{
		// Compute matrix B real part and imaginary part separtely
		for (int l = 1; l <= Data.numberOfFrequency && false == Data.isInterruptionRequested; l++) {
			for (int m = 1; m <= loop; m++) {
			
				dBMatrix(loop - 1, m - 1, l - 1) = 2 * sqrt(Data.frequencyIncrement)*dCPSDdecompArray(loop - 1, m - 1, l - 1) *exp(ii * drandomPhase(l - 1, m - 1));
			}
		}
	}

	int iNber_Point = Data.numberOfSpatialPosition;
	int iNber_Frequency = Data.numberOfFrequency;

	for (int loop = 1; loop <= iNber_Point && false == Data.isInterruptionRequested; loop++)
	{
		// Take the vector corresponding to a row and a column 
		for (int m = 1; m <= loop && false == Data.isInterruptionRequested; m++) {

			for (int l = 1; l <= iNber_Frequency && false == Data.isInterruptionRequested; l++) {
	
				xxx(l - 1) = dBMatrix(loop - 1, m - 1, l - 1);
			}

			// compute psd by Fourier transform of each vector 
			Eigen::FFT<double> fft;
			fft.fwd(yyy, xxx);

			// Save the transformed vector in the matrix G
			for (int l = 1; l <= 2 * iNber_Frequency && false == Data.isInterruptionRequested; l++) {
				
				dGMatrix(loop - 1, m - 1, l - 1) = (double)(2 * iNber_Frequency) * yyy(l - 1);

			}
		}

	}

	int q = 0;
	QString msg1, msg2;


	for (int loop = 1; loop <= iNber_Point && false == Data.isInterruptionRequested; loop++)
	{
		// compute random wind velocity as function of time. (see Shinozuka)
		for (int time = 1; time <= Data.numberOfTimeIncrements && false == Data.isInterruptionRequested; time++) {
			q = fmod(time - 1, 2 * iNber_Frequency);

			for (int m = 1; m <= loop; m++) {
				dVelocityArray(time - 1, loop - 1) += real(dGMatrix(loop - 1, m - 1, q)*exp(ii*(double)((time - 1)*Data.timeIncrement*m*Data.timeIncrement / iNber_Point)));
				
			}
		}
	}

	return true;		
}

// The simulation function in large scale mode
bool CRPSDeodatis1987::SimulateInLargeScaleMode(const CRPSWindLabsimuData &Data, QString &strFileName, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation)
{
	return true;
}

// The simulation function in comparison mode
bool CRPSDeodatis1987::SimulateInComparisonMode(const CRPSWindLabsimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, int &minProgress, int &maxProgress, int &currentProgress, QStringList &strInformation)
{
	// // Locale array for the Cholesky decomposed cpsd
	// cube dCPSDdecompArray;
	// try
	// {
	// 	dCPSDdecompArray.set_size(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, Data.numberOfFrequency);
	// }
	// catch (CMemoryException* pEx)
	// {
	// 	// Simply show an error message to the user.
	// 	pEx->ReportError();
	// 	pEx->Delete();
	// 	return false;
	// }
	// catch (bad_alloc &ba)
	// {
	// 	QString msg(ba.what());
	// 	AfxMessageBox(msg);
	// 	return false;
	// }

	// //Computing the decomposed psd matrix
	// // Compute the decomposed cpsd 
	// ComputeCPSDDecom3DMatrice(Data, dCPSDdecompArray, strInformation);


	// cx_vec xxx;
	// cx_vec yyy;
	// cx_cube  dBMatrix;
	// cx_cube  dGMatrix;

	// try
	// {
	// 	dBMatrix.set_size(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, 2 * Data.numberOfFrequency);
	// 	dGMatrix.set_size(Data.numberOfSpatialPosition, Data.numberOfSpatialPosition, 2 * Data.numberOfFrequency);
	// 	xxx.zeros(2 * Data.numberOfFrequency);
	// 	yyy.set_size(2 * Data.numberOfFrequency);
	// }
	// catch (CMemoryException* pEx)
	// {
	// 	// Simply show an error message to the user.
	// 	pEx->ReportError();
	// 	pEx->Delete();
	// 	return false;
	// }
	// catch (bad_alloc &ba)
	// {
	// 	QString msg(ba.what());
	// 	AfxMessageBox(msg);
	// 	return false;
	// }

	// std::complex<double> ii(0, 1);

	// QString SimuMsg;
	

	// //CRPSsimulationTools::SimulationProcess(Data.numberOfSpatialPosition, 0);
	// // Fast Fourier transform in process
	// for (int loop = 1; loop <= Data.numberOfSpatialPosition && false == Data.isInterruptionRequested; loop++)
	// {
	// 	// Compute matrix B real part and imaginary part separtely
	// 	for (int l = 1; l <= Data.numberOfFrequency && false == Data.isInterruptionRequested; l++) {
	// 		for (int m = 1; m <= loop; m++) {

	// 			dBMatrix(loop - 1, m - 1, l - 1) = 2 * sqrt(Data.frequencyIncrement)*dCPSDdecompArray(loop - 1, m - 1, l - 1) *exp(ii * dRandomPhaseArray(l - 1, m - 1));
	// 		}
	// 	}
	// 	//SimuMsg.Format(("We are on the %d simulation"), loop);
	// 	CRPSWindLabTools::UpdateProgress(loop);
	// }

	// if (!dCPSDdecompArray.is_empty())
	// {
	// 	dCPSDdecompArray.reset();
	// }

	// int iNber_Point = Data.numberOfSpatialPosition;
	// int iNber_Frequency = Data.numberOfFrequency;

	// for (int loop = 1; loop <= iNber_Point && false == Data.isInterruptionRequested; loop++)
	// {
	// 	// Take the vector corresponding to a row and a column 
	// 	for (int m = 1; m <= loop && false == Data.isInterruptionRequested; m++) {

	// 		for (int l = 1; l <= iNber_Frequency && false == Data.isInterruptionRequested; l++) {

	// 			xxx(l - 1) = dBMatrix(loop - 1, m - 1, l - 1);
	// 		}

	// 		// compute psd by Fourier transform of each vector 
	// 		yyy = ifft(xxx);

	// 		// Save the transformed vector in the matrix G
	// 		for (int l = 1; l <= 2 * iNber_Frequency && false == Data.isInterruptionRequested; l++) {

	// 			dGMatrix(loop - 1, m - 1, l - 1) = (double)(2 * iNber_Frequency) * yyy(l - 1);

	// 		}
	// 	}

	// }

	// //Delete the memory allocated 
	// if (!xxx.is_empty())
	// {
	// 	xxx.reset();
	// }

	// if (!yyy.is_empty())
	// {
	// 	yyy.reset();
	// }

	// if (!dBMatrix.is_empty())
	// {
	// 	dBMatrix.reset();
	// }

	// int q = 0;
	// QString aa, bb;
	// for (int loop = 1; loop <= iNber_Point && false == Data.isInterruptionRequested; loop++)
	// {
	// 	// compute random wind velocity as function of time. (see Shinozuka)
	// 	for (int time = 1; time <= Data.m_iNumberOfTimeIncrements && false == Data.isInterruptionRequested; time++) {
	// 		q = fmod(time - 1, 2 * iNber_Frequency);

	// 		for (int m = 1; m <= loop; m++) {
	// 			/*aa.Format(("loop - 1 =  %d, m - 1 =  %d, tme - 1 =  %d, q =  %d"), loop - 1, m - 1, time - 1, q);
	// 			AfxMessageBox(aa);*/
	// 			dVelocityArray(time - 1, loop - 1) += real(dGMatrix(loop - 1, m - 1, q)*exp(ii*(double)((time - 1)*Data.m_dTimeIncrement*m*Data.m_dTimeIncrement / iNber_Point)));

	// 		}

	// 	}

	// }

	// if (!dGMatrix.is_empty())
	// {
	// 	dGMatrix.reset();
	// }

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
