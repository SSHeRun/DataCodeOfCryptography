// Start.cpp : implementation file
//

#include "stdafx.h"
#include "USBKey.h"
#include "Start.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Start dialog


Start::Start(CWnd* pParent /*=NULL*/)
	: CDialog(Start::IDD, pParent)
{
	//{{AFX_DATA_INIT(Start)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Start::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Start)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Start, CDialog)
	//{{AFX_MSG_MAP(Start)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Start message handlers
