// USBKeyDlg.h : header file
//
#if !defined(AFX_USBKEYDLG_H__CC86D21B_BBEB_4EA1_946F_BF1422533A40__INCLUDED_)
#define AFX_USBKEYDLG_H__CC86D21B_BBEB_4EA1_946F_BF1422533A40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

#include "GrandDog.h"

/////////////////////////////////////////////////////////////////////////////
// CUSBKeyDlg dialog

class CUSBKeyDlg : public CDialog
{
// Construction
public:
	CUSBKeyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUSBKeyDlg)
	enum { IDD = IDD_USBKEY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSBKeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUSBKeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBKEYDLG_H__CC86D21B_BBEB_4EA1_946F_BF1422533A40__INCLUDED_)
