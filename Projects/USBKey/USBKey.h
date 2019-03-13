// USBKey.h : main header file for the USBKEY application
//

#if !defined(AFX_USBKEY_H__7606D414_0D6B_4004_BAFD_42C3E867A752__INCLUDED_)
#define AFX_USBKEY_H__7606D414_0D6B_4004_BAFD_42C3E867A752__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUSBKeyApp:
// See USBKey.cpp for the implementation of this class
//

class CUSBKeyApp : public CWinApp
{
public:
	CUSBKeyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSBKeyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUSBKeyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBKEY_H__7606D414_0D6B_4004_BAFD_42C3E867A752__INCLUDED_)
