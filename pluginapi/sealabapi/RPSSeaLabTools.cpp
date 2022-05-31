#include "RPSSeaLabTools.h"


bool CRPSSeaLabTools::m_bSimuIsInProcessFlag;
bool CRPSSeaLabTools::m_bSimuIsPausedFlag;
bool CRPSSeaLabTools::m_bSimuIsStoppedFlag;

CRPSSeaLabTools::CRPSSeaLabTools()
{
}

CRPSSeaLabTools::~CRPSSeaLabTools()
{
}


bool& CRPSSeaLabTools::GetSimuInProcessFlag()
{
	return m_bSimuIsInProcessFlag;
}

void CRPSSeaLabTools::SetSimuInProcessFlag(bool bSimuInProcessFlag)
{
	m_bSimuIsInProcessFlag = bSimuInProcessFlag;
}

bool& CRPSSeaLabTools::GetSimuIsPausedFlag()
{
	return m_bSimuIsPausedFlag;
}

void CRPSSeaLabTools::SetSimuIsPausedFlag(bool bSimuIsPausedFlag)
{
	m_bSimuIsPausedFlag = bSimuIsPausedFlag;
}

bool& CRPSSeaLabTools::GetSimuIsStoppedFlag()
{
	return m_bSimuIsStoppedFlag;
}

void CRPSSeaLabTools::SetSimuIsStoppedFlag(bool bSimuIsStoppedFlag)
{
	m_bSimuIsStoppedFlag = bSimuIsStoppedFlag;
}
