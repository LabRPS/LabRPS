#pragma once

#ifndef RPSSEISMICLABTOOL_H
#define RPSSEISMICLABTOOL_H

#include "RPSSeismicLabAPIdefines.h"
#include "RPSSeismicLabsimuData.h"


using namespace std;

class RPS_CORE_API CRPSSeismicLabTools
{
public:
	CRPSSeismicLabTools();
	~CRPSSeismicLabTools();

	
	// Get the flag telling whether the simulation is in process or not
	static bool& GetSimuInProcessFlag();

	// Set the flag telling whether the simulation is in process or not
	static void SetSimuInProcessFlag(bool bSimuInProcessFlag);

	// Get the flag telling whether the simulation is paused or not
	static bool& GetSimuIsPausedFlag();

	// Set the flag telling whether the simulation is paused or not
	static void SetSimuIsPausedFlag(bool bSimuIsPausedFlag);

	// Get the flag telling whether the simulation is stopped or not
	static bool& GetSimuIsStoppedFlag();

	// Set the flag telling whether the simulation is stopped or not
	static void SetSimuIsStoppedFlag(bool bSimuIsStoppedFlag);

private:

	// is true when simulating
	static bool m_bSimuIsInProcessFlag;

	// is true  when simulation is paused
	static bool m_bSimuIsPausedFlag;

	// is true when the simulation is stopped
	static bool m_bSimuIsStoppedFlag;

	// is true when the simulation is stopped
	static int m_iSimuCompletedAmountOfTask;
};
#endif