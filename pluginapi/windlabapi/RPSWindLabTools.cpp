
#include "RPSWindLabTools.h"
#include "RPSWindLabAPI.h"


CRPSWindLabTools::CRPSWindLabTools()
{
}

CRPSWindLabTools::~CRPSWindLabTools()
{
}

void CRPSWindLabTools::RPSComputeFFT(vec &realpartinput, vec &imagpartinput, const int &n, const int &k, const int &l, const int &il, vec &realpartoutput, vec &imagpartoutput)
{

     int it, m, is, i, j, nv, l0;
     double p, q, s, vr, vi, poddr, poddi;
    for (it = 0; it <= n - 1; it++)
    {
    	m = it; is = 0;
    	for (i = 0; i <= k - 1; i++)
    	{
    		j = m / 2;
    		is = 2 * is + (m - 2 * j);
    		m = j;
    	}
    	realpartoutput(it) = realpartinput(is); imagpartoutput(it) = imagpartinput(is);
    }
    realpartinput(0) = 1.0; imagpartinput(0) = 0.0;
    p = 6.283185306 / (1.0*n);
    realpartinput(1) = cos(p); imagpartinput(1) = -sin(p);
    if (l != 0) imagpartinput(1) = -imagpartinput(1);
    for (i = 2; i <= n - 1; i++)
    {
    	p = realpartinput(i - 1) * realpartinput(1); q = imagpartinput(i - 1) * imagpartinput(1);
    	s = (realpartinput(i - 1) + imagpartinput(i - 1))*(realpartinput(1) + imagpartinput(1));
    	realpartinput(i) = p - q; imagpartinput(i) = s - p - q;
    }
    for (it = 0; it <= n - 2; it = it + 2)
    {
    	vr = realpartoutput(it); vi = imagpartoutput(it);
    	realpartoutput(it) = vr + realpartoutput(it + 1); imagpartoutput(it) = vi + imagpartoutput(it + 1);
    	realpartoutput(it + 1) = vr - realpartoutput(it + 1); imagpartoutput(it + 1) = vi - imagpartoutput(it + 1);
    }
    m = n / 2; nv = 2;
    for (l0 = k - 2; l0 >= 0; l0--)
    {
    	m = m / 2; nv = 2 * nv;
    	for (it = 0; it <= (m - 1)*nv; it = it + nv)
    		for (j = 0; j <= (nv / 2) - 1; j++)
    		{
    			p = realpartinput(m*j) * realpartoutput(it + j + nv / 2);
    			q = imagpartinput(m*j) * imagpartoutput(it + j + nv / 2);
    			s = realpartinput(m*j) + imagpartinput(m*j);
    			s = s*(realpartoutput(it + j + nv / 2) + imagpartoutput(it + j + nv / 2));
    			poddr = p - q; poddi = s - p - q;
    			realpartoutput(it + j + nv / 2) = realpartoutput(it + j) - poddr;
    			imagpartoutput(it + j + nv / 2) = imagpartoutput(it + j) - poddi;
    			realpartoutput(it + j) = realpartoutput(it + j) + poddr;
    			imagpartoutput(it + j) = imagpartoutput(it + j) + poddi;
    		}
    }
    if (l != 0)
    {
    	for (i = 0; i <= n - 1; i++)
    	{
    		realpartoutput(i) = realpartoutput(i) / (1.0*n);
    		imagpartoutput(i) = imagpartoutput(i) / (1.0*n);
    	}
    	if (il != 0)
    		for (i = 0; i <= n - 1; i++)
    		{
    			realpartinput(i) = sqrt(realpartoutput(i) * realpartoutput(i) + imagpartoutput(i) * imagpartoutput(i));
    			if (fabs(realpartoutput(i))<0.000001*fabs(imagpartoutput(i)))
    			{
    				if ((imagpartoutput(i) * realpartoutput(i))>0) imagpartinput(i) = 90.0;
    				else imagpartinput(i) = -90.0;
    			}
    			else
    				imagpartinput(i) = atan(imagpartoutput(i) / realpartoutput(i))*360.0 / 6.283185306;
    		}
    }
}

void CRPSWindLabTools::RPSComputeCholeskyDecomposition(const mat &dMatrix, const int &iRow, mat &ddecomposedMatrix)
{
    // double Sum;

    // for (int i = 0; i < iRow; i++)
    // {
    // 	for (int j = 0; j < iRow; j++)
    // 	{
    // 		ddecomposedMatrix[i * iRow + j] = 0;
    // 	}
    // }

    // // compute Lower triangular matrix
    // for (int k = 0; k < iRow; k++)
    // {
    // 	Sum = 0;
    // 	for (int j = 0; j < k - 1; j++)
    // 		Sum += pow(ddecomposedMatrix[k * iRow + j], 2);
    // 	ddecomposedMatrix[k * iRow + k] = sqrt(dMatrix[k * iRow + k] - Sum);
    // 	for (int i = 0; i < k - 1; i++)
    // 	{
    // 		Sum = 0;
    // 		for (int j = 0; j < i - 1; j++)
    // 			Sum += ddecomposedMatrix[i * iRow + j] * ddecomposedMatrix[k * iRow + j];
    // 		ddecomposedMatrix[k * iRow + i] = (dMatrix[k * iRow + i] - Sum) / ddecomposedMatrix[i * iRow + i];
    // 	}
    // }

    // return;
}

// void CRPSWindLabTools::GenerateRandomArray(const double &dMin, const double &dMax, const int &iRow, const int &iCol, mat &dRandomValueArray)
// {
// // 	const int &n = iRow;
// // 	const int &N = iCol;
// // 	const int &MAX = iRow;

// // 	srand((unsigned)time(NULL));
// // 	for (int loop = 0; loop < n; loop++) {
// // 		for (int loop1 = 0; loop1 < iCol; loop1++) {

// // 			dRandomValueArray[loop *iCol + loop1] = rand() % MAX;
// // 			dRandomValueArray[loop *iCol + loop1] = dMin + (double)(dMax * dRandomValueArray[loop *iCol + loop1] / MAX);
// // 		}
// // 	}	
// // }

// // void CRPSWindLabTools::PSDtoCorrelation(const CRPSWindLabsimuData &Data, vec &dTargetSpectrum, vec &dTargetCorr)
// // {
// // 	int iNbrOfFrequency = Data.m_iNumberOfFrequency;

// // 	vec dImagPartX;
// // 	vec dImagPartY;
// // 	vec dTargetCorrLocal;


// // 	try
// // 	{
// // 		dImagPartX.set_size(iNbrOfFrequency);
// // 		dImagPartY.set_size(iNbrOfFrequency);
// // 		dTargetCorrLocal.set_size(iNbrOfFrequency);
// // 	}
// // 	catch (CMemoryException* pEx)
// // 	{
// // 		// Simply show an error message to the user.
// // 		pEx->ReportError();
// // 		pEx->Delete();
// // 		return;
// // 	}
// // 	catch (bad_alloc &ba)
// // 	{
// // 		QString msg(ba.what());
// // 		AfxMessageBox(msg);
// // 		return;
// // 	}

// // 	// compute psd by Fourier transform of the correlation function
// // 	CRPSWindLabTools::RPSComputeFFT(dTargetSpectrum, dImagPartX, iNbrOfFrequency, (int)(log(iNbrOfFrequency) / log(2)), 1, 1, dTargetCorrLocal, dImagPartY);


// // 	// For each frequency increment
// // 	for (int i = 0; i < iNbrOfFrequency; i++)
// // 	{
// // 		// local variable used to arrange the correlation in symetric way
// // 		int po = abs(i - iNbrOfFrequency / 2);

// // 		//Arrange the correlation in symetric way
// // 		dTargetCorr(i) = 2 * Data.m_dMaxFrequency*dTargetCorrLocal(po);
// // 	}

// }

// void CRPSWindLabTools::ComputeSimulatedCorrByFFT(const CRPSWindLabsimuData &Data, const mat &dVelocities, const int &iLocationJ, const int &iLocationK, vec &dSimulatedCorr)
// {
// 	// /*mat velo;
// 	// velo.set_size(Data.m_iNumberOfTimeIncrements, 1);

// 	// for (int l = 0; l < Data.m_iNumberOfTimeIncrements; l++)
// 	// {
// 	// 	velo(l) = dVelocities(l, iLocationJ);
// 	// }
// 	// mat uu = cor(dVelocities);

// 	// int gg = uu.size();
// 	// int rr;*/
// 	// int a = ceil((log(2 * Data.m_iNumberOfTimeIncrements - 1) / log(2)));
// 	// int b = pow(2, a);

// 	// vec xRe;
// 	// vec xIm;
// 	// vec yRe;
// 	// vec yIm;


// 	// vec xReJ;
// 	// vec xImJ;
// 	// vec yReJ;
// 	// vec yImJ;
	
// 	// vec xReK;
// 	// vec xImK;
// 	// vec yReK;
// 	// vec yImK;
	
// 	// xRe.zeros(b);
// 	// xIm.zeros(b);
// 	// yRe.zeros(b);
// 	// yIm.zeros(b);

// 	// xReJ.zeros(b);
// 	// xImJ.zeros(b);
// 	// yReJ.zeros(b);
// 	// yImJ.zeros(b);

// 	// xReK.zeros(b);
// 	// xImK.zeros(b);
// 	// yReK.zeros(b);
// 	// yImK.zeros(b);

// 	// 	for (int l = 0; l < Data.m_iNumberOfTimeIncrements; l++) {
// 	// 		xReJ(l) = dVelocities(l, iLocationJ);
// 	// 		xReK(l) = dVelocities(l, iLocationK);
// 	// 	}

// 	// 	//vec result = conv(a, reverse(a));

// 	// 	CRPSWindLabTools::RPSComputeFFT(xReJ, xImJ, pow(2, a), a, 0, 1, yReJ, yImJ);

// 	// //compute fft(y) 
// 	// 	CRPSWindLabTools::RPSComputeFFT(xReK, xImK, pow(2, a), a, 0, 1, yReK, yImK);

// 	// // fft(x)*conj(fft(y))
// 	// for (int l = 1; l <= b; l++)
// 	// {
// 	// 	xRe(l - 1) = yReJ(l - 1) * yReK(l - 1) - yImJ(l - 1) * (-yImK(l - 1));
// 	// 	xIm(l - 1) = yReJ(l - 1) * (-yImK(l - 1)) + yImJ(l - 1) * yReK(l - 1);
// 	// }

// 	// //compute ifft(fft(x)*conj(fft(y))) 
// 	// CRPSWindLabTools::RPSComputeFFT(xRe, xIm, pow(2, a), a, 1, 1, yRe, yIm);

// 	// //// Copy values to the correlation vector symetrically R[lag] = R[-lag]
// 	// for (int lag = 0; lag < Data.m_iNumberOfFrequency; lag++)
// 	// {
// 	// 	dSimulatedCorr(lag) = yRe(Data.m_iNumberOfFrequency - lag) / (Data.m_iNumberOfTimeIncrements);
// 	// }

// 	// for (int lag = 0; lag <= Data.m_iNumberOfFrequency; lag++)
// 	// {
// 	// 	dSimulatedCorr(Data.m_iNumberOfFrequency + lag) = yRe(lag) / (Data.m_iNumberOfTimeIncrements);
// 	// }
// }


// bool& CRPSWindLabTools::GetSimuInProcessFlag()
// {
// 	return m_bSimuIsInProcessFlag;
// }

// void CRPSWindLabTools::SetSimuInProcessFlag(bool bSimuInProcessFlag)
// {
// 	// //// Display the message box and store it returned value
// 	// //int msgboxID = MessageBox(NULL, ("LabRPS is currently busy working on something. If you continue the current task may be stopped.\n Are you sure you want to continue?"),
// 	// //	("Caution"), MB_YESNO | MB_ICONQUESTION);

// 	// //if (bSimuInProcessFlag && m_bSimuIsInProcessFlag)
// 	// //{
// 	// //	// if the butuon no is clicked then...
// 	// //	if (msgboxID == IDYES)
// 	// //	{
// 	// //		m_bSimuIsInProcessFlag = bSimuInProcessFlag;
// 	// //		return;
// 	// //	}
// 	// //	else
// 	// //	{
// 	// //		return;
// 	// //	}
// 	// //}
	

// 	// m_bSimuIsInProcessFlag = bSimuInProcessFlag;

// }

// bool& CRPSWindLabTools::GetSimuIsPausedFlag()
// {
// 	return m_bSimuIsPausedFlag;
// }

// void CRPSWindLabTools::SetSimuIsPausedFlag(bool bSimuIsPausedFlag)
// {
// 	// m_bSimuIsPausedFlag = bSimuIsPausedFlag;
// }

// bool& CRPSWindLabTools::GetSimuIsStoppedFlag()
// {
// 	return m_bSimuIsStoppedFlag;
// }

// void CRPSWindLabTools::SetSimuCompletedAmountOfTask(const int &iSimuCompletedAmountOfTask)
// {
// 	// m_iSimuCompletedAmountOfTask = iSimuCompletedAmountOfTask;
// }

// int& CRPSWindLabTools::GeSimuCompletedAmountOfTask()
// {
// 	return m_iSimuCompletedAmountOfTask;
// }

// void CRPSWindLabTools::SetSimuIsStoppedFlag(bool bSimuIsStoppedFlag)
// {
// 	// m_bSimuIsStoppedFlag = bSimuIsStoppedFlag;
// }

// void CRPSWindLabTools::WriteMatrixToFile(const int &row, const int &colum, const mat &array, const QString &sFileName)
// {
// 	// // Define an output stream
// 	// ofstream fout;

// 	// // open the file output mode to erase its content first
// 	// fout.width(10);
// 	// fout.setf(ios::left);
// 	// fout.setf(ios::fixed);
// 	// fout.fill('0');
// 	// fout.open(sFileName, ios::out);

// 	// // FOR EACH ROW AND COL
// 	// for (int j = 0; j < row; j++)
// 	// {
// 	// 	// FOR EACH Column
// 	// 	for (int i = 0; i< colum; i++)
// 	// 	{

// 	// 		fout << array[j * colum + i] << "\t";
// 	// 	}
// 	// 	fout << endl;	// New row
// 	// }

// 	// fout.close();
// }

// void CRPSWindLabTools::WriteMatrixAsBinary(const int &row, const int &colum, const mat &array, const QString &sFileName)
// {
// 	// // Define an output stream
// 	// ofstream fout;

// 	// // Open the file stream
// 	// fout.open(sFileName, ios::binary | ios::out);
	
// 	// // For each line
// 	// for (int loop = 0; loop < row; loop++)
// 	// {
// 	// 	// For each data poconst int &in the line
// 	// 	for (int k = 0; k < colum; k++)
// 	// 	{
// 	// 		// Write wind data to file
// 	// 		fout.write(reinterpret_cast<const char*>(&array[loop * colum + k]), std::streamsize(sizeof(double)));

// 	// 	}
// 	// }

// 	// fout.close();

// 	return;
// }

// const int &CRPSWindLabTools::WLMod(const int &x, const int &y)
// {
// 	// if (y == 0)
// 	// 	return x;
// 	// else if (x == y)
// 	// 	return 0;
// 	// else
// 	// 	return x - floor(x / y) *y;

// 	return 0;
// }

// void CRPSWindLabTools::SimulationProcess(const int &iTotalTask, const int &iTaskCompleted)
// {
	
// }

// void CRPSWindLabTools::UpdateProgress()
// {
// }

// void CRPSWindLabTools::UpdateProgress(const int &iCompletedAmount)
// {
// 	// /*m_ctrlProcessBarDlg->PostMessage(UWM_UPDATE_PROGRESS);*/
// 	// SetSimuCompletedAmountOfTask(iCompletedAmount);
// }

// void CRPSWindLabTools::DisableProgressBar()
// {
// }

// void CRPSWindLabTools::SendSimuInfo(QString msg)
// {
// 	// LPWSTR pszText = (LPWSTR)(LPCWSTR)msg;

// }