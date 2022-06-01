
#include "RPSSeismicLabTools.h"

bool CRPSSeismicLabTools::m_bSimuIsInProcessFlag;
bool CRPSSeismicLabTools::m_bSimuIsPausedFlag;
bool CRPSSeismicLabTools::m_bSimuIsStoppedFlag;

CRPSSeismicLabTools::CRPSSeismicLabTools()
{
}

CRPSSeismicLabTools::~CRPSSeismicLabTools()
{
}


bool& CRPSSeismicLabTools::GetSimuInProcessFlag()
{
	return m_bSimuIsInProcessFlag;
}

void CRPSSeismicLabTools::SetSimuInProcessFlag(bool bSimuInProcessFlag)
{
	m_bSimuIsInProcessFlag = bSimuInProcessFlag;
}

bool& CRPSSeismicLabTools::GetSimuIsPausedFlag()
{
	return m_bSimuIsPausedFlag;
}

void CRPSSeismicLabTools::SetSimuIsPausedFlag(bool bSimuIsPausedFlag)
{
	m_bSimuIsPausedFlag = bSimuIsPausedFlag;
}

bool& CRPSSeismicLabTools::GetSimuIsStoppedFlag()
{
	return m_bSimuIsStoppedFlag;
}

void CRPSSeismicLabTools::SetSimuIsStoppedFlag(bool bSimuIsStoppedFlag)
{
	m_bSimuIsStoppedFlag = bSimuIsStoppedFlag;
}
