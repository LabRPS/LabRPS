#pragma once

#ifndef RPSWINDLABTOOL_H
#define RPSWINDLABTOOL_H

#include "RPSWindLabAPIdefines.h"
#include "RPSWindLabsimuData.h"


using namespace std;

class RPS_CORE_API CRPSWindLabTools
{
public:
	CRPSWindLabTools();
	~CRPSWindLabTools();

// 	/////////////////////Simulation tools/////////////////////////////////////////////////////

// 	// Compute the FFT of a vector
// 	static void RPSComputeFFT(vec &realpartinput, vec &imagpartinput, const int &n, const int &k, const int &l, const int &il, vec &realpartoutput, vec &imagpartoutput);

// 	// Compute the Cholesky decomposition of a matrix
// 	static void RPSComputeCholeskyDecomposition(const mat &dMatrix, const int &iRow, mat &ddecomposedMatrix);

// 	//Generate an array of random const double &precision values between dMin and dMax
// 	static void GenerateRandomArray(const double &dMin, const double &dMax, const int &iRow, const int &iCol, mat &dRandomValueArray);

// 	// This function writes a 2D array to file (formatted)
// 	static void WriteMatrixToFile(const int &row, const int &colum, const mat &array, const QString &sFileName);

// 	// This function writes a 2D array to file (As binary)
// 	static void WriteMatrixAsBinary(const int &row, const int &colum, const mat &array, const QString &sFileName);

// 	// Compute the correlation from a psd
// 	static void PSDtoCorrelation(const CRPSWindLabsimuData &Data, vec &dTargetSpectrum, vec &dTargetCorr);

// 	// Compute correlation from simulated processes
// 	static void ComputeSimulatedCorrByFFT(const CRPSWindLabsimuData &Data, const mat &dVelocities, const int &iLocationJ, const int &iLocationK, vec &dSimulatedCorr);


	

// 	//// Compute correlation from simulated processes
// 	//static void Vectorize2D(const CRPSWindLabsimuData &Data, double** d2Dmatrix, const int &iRwo, const int &iCol, CRPSPDoubleArray &d1DVectorisedMatrix);
// 	//static void IVectorize2D(const CRPSWindLabsimuData &Data, const CRPSPDoubleArray &d1DVectorisedMatrix, const int &iRwo, const int &iCol, double** d2Dmatrix);

// 	//static void Vectorize3D(const CRPSWindLabsimuData &Data, double*** d3Dmatrix, const int &iRwo, const int &iCol, const int &iz, CRPSPDoubleArray &d1DVectorisedMatrix);
// 	//static void IVectorize3D(const CRPSWindLabsimuData &Data, const CRPSPDoubleArray &d1DVectorisedMatrix, const int &iRwo, const int &iCol, const int &iz, double*** d2Dmatrix);

// 	///////////////// Plugin tools ///////////////////////////////////////////////////////////

// 	// Get the flag telling whether the simulation is in process or not
// 	static bool& GetSimuInProcessFlag();

// 	// Set the flag telling whether the simulation is in process or not
// 	static void SetSimuInProcessFlag(bool bSimuInProcessFlag);

// 	// Get the flag telling whether the simulation is paused or not
// 	static bool& GetSimuIsPausedFlag();

// 	// Set the flag telling whether the simulation is paused or not
// 	static void SetSimuIsPausedFlag(bool bSimuIsPausedFlag);

// 	// Get the flag telling whether the simulation is stopped or not
// 	static bool& GetSimuIsStoppedFlag();

// 	// Set the flag telling whether the simulation is stopped or not
// 	static void SetSimuIsStoppedFlag(bool bSimuIsStoppedFlag);

// 	// Get the flag telling whether the simulation is stopped or not
// 	static int& GeSimuCompletedAmountOfTask();

// 	// Set the flag telling whether the simulation is stopped or not
// 	static void SetSimuCompletedAmountOfTask(const int &iSimuCompletedAmountOfTask);

// 	static const int &WLMod(const int &x, const int &y);

// 	// This function takes care of the simulation progress in plugin
// 	static void SimulationProcess(const int &iTotalTask, const int &iTaskCompleted);

// 	static void UpdateProgress(const int &iCompletedAmount);
// 	static void UpdateProgress();
// 	static void DisableProgressBar();
// 	static void SendSimuInfo(QString msg);

// private:

// 	// is true when simulating
// 	static bool m_bSimuIsInProcessFlag;

// 	// is true  when simulation is paused
// 	static bool m_bSimuIsPausedFlag;

// 	// is true when the simulation is stopped
// 	static bool m_bSimuIsStoppedFlag;

// 	// is true when the simulation is stopped
// 	static int m_iSimuCompletedAmountOfTask;

};

#endif

