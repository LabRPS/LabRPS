// HorizontalLocDistr.cpp : implementation file
//
#include "HorizontalLocDistr.h"

// CHorizontalLocDistr dialog

IMPLEMENT_DYNAMIC(CHorizontalLocDistr, CDialogEx)

CHorizontalLocDistr::CHorizontalLocDistr(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HORY_LOC_DIALOG, pParent)
	, m_dSpacing(0)
	, m_dHeight(0)
	, m_dLength(0)
{

}

CHorizontalLocDistr::~CHorizontalLocDistr()
{
}

void CHorizontalLocDistr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SPACING_EDIT, m_dSpacing);
	DDX_Text(pDX, IDC_HEIGHT_EDIT, m_dHeight);
	DDX_Text(pDX, IDC_LENGTH_EDIT, m_dLength);
}


BEGIN_MESSAGE_MAP(CHorizontalLocDistr, CDialogEx)
END_MESSAGE_MAP()


// CHorizontalLocDistr message handlers
