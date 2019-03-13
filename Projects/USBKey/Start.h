#if !defined(AFX_START_H__5CDD9F59_D702_4A8E_A7BF_D2AFF8C464DD__INCLUDED_)
#define AFX_START_H__5CDD9F59_D702_4A8E_A7BF_D2AFF8C464DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Start.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Start dialog

class Start : public CDialog
{
// Construction
public:
	Start(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Start)
	enum { IDD = IDD_START_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Start)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Start)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_START_H__5CDD9F59_D702_4A8E_A7BF_D2AFF8C464DD__INCLUDED_)
