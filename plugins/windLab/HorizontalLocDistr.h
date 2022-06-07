#pragma once


// CHorizontalLocDistr dialog

class CHorizontalLocDistr : public CDialogEx
{
	DECLARE_DYNAMIC(CHorizontalLocDistr)

public:
	CHorizontalLocDistr(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CHorizontalLocDistr();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HORY_LOC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	double m_dSpacing;
	double m_dHeight;
	double m_dLength;
};
