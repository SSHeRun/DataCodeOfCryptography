// USBKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "USBKey.h"
#include "Start.h"
#include "USBKeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUSBKeyDlg dialog

CUSBKeyDlg::CUSBKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSBKeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUSBKeyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUSBKeyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUSBKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CUSBKeyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnStart)
	ON_BN_CLICKED(IDC_BUTTON2, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSBKeyDlg message handlers

BOOL CUSBKeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUSBKeyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUSBKeyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUSBKeyDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	CString editText;//存储对话框消息
	CString serialNum;//USBKey串号
	ULONG Num;
	std::string strUserPwd="#jsUser!&";
	char message[16];//要写入的消息
	char message_out[16];//读取消息存放位置
	memset(message,0,16);
	memset(message_out,0,16);
	message[0] = 'H';
	message[1] = 'e';
	message[2] = 'l';
	message[3] = 'l';
	message[4] = 'o';
	message[5] = ' ';
	message[6] = 'U';
	message[7] = 'S';
	message[8] = 'B';
	message[9] = 'K';
	message[10] = 'e';
	message[11] = 'y';
	ULONG m_ulDogHandle;//加密狗句柄
	UCHAR ucDegree = '\0';
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	HRESULT rs = RC_OpenDog( 1, "JlcssDog", &m_ulDogHandle );//打开USBKey
	if(rs != ((HRESULT)0x00000000L)){
		pEdit->GetWindowText(editText);
		pEdit->SetWindowText(editText+"无法找到USBKey\r\n");	
	}else{
		pEdit->GetWindowText(editText);
		pEdit->SetWindowText(editText+"找到并打开USBKey\r\n");
		ULONG ulBufLen = sizeof( RC_HARDWARE_INFO );
		rs = RC_GetProductCurrentNo( m_ulDogHandle, &Num );//取得硬件序列号
		if(rs != ((HRESULT)0x00000000L)){
			pEdit->GetWindowText(editText);
			pEdit->SetWindowText(editText+"读取USBKey序列号失败\r\n");
		}else{
			pEdit->GetWindowText(editText);
			serialNum.Format("%d",Num);
			pEdit->SetWindowText(editText+"USBKey Serial Number:"+serialNum+"\r\n");
			RC_CloseDog( m_ulDogHandle );//关闭USBKey
			pEdit->GetWindowText(editText);
			pEdit->SetWindowText(editText+"关闭USBKey\r\n");
			rs = RC_OpenDog( 1, "JlcssDog", &m_ulDogHandle );//重新打开
			rs = RC_VerifyPassword( m_ulDogHandle, 1, 
				const_cast<char *>( strUserPwd.c_str() ), &ucDegree );//验证密码
			if(rs != ((HRESULT)0x00000000L)){
				pEdit->GetWindowText(editText);
				pEdit->SetWindowText(editText+"验证失败\r\n");
			}
			rs = RC_WriteFile( m_ulDogHandle, 0x3f00, 0x0001, 0, 
				sizeof(message), reinterpret_cast< unsigned char* >( &message ) );//写入信息
			if(rs != ((HRESULT)0x00000000L)){
				pEdit->GetWindowText(editText);
				pEdit->SetWindowText(editText+"写入消息失败\r\n");
			}else{
				pEdit->GetWindowText(editText);
				pEdit->SetWindowText(editText+"成功写入消息:"+message+"\r\n");
				rs = RC_ReadFile( m_ulDogHandle, 0x3f00, 0x0001, 0,
					sizeof(message_out), reinterpret_cast< unsigned char* >( &message_out ) );//读取信息
				if(rs != ((HRESULT)0x00000000L)){
					pEdit->GetWindowText(editText);
					pEdit->SetWindowText(editText+"读取消息失败\r\n");
				}else{
					pEdit->GetWindowText(editText);
					pEdit->SetWindowText(editText+"成功读取消息:"+message_out+"\r\n");
					RC_CloseDog( m_ulDogHandle );//关闭
					if(MessageBox("成功启动加密狗","success",MB_OK)==IDOK){
						Start startDlg ;
						startDlg.DoModal();
					}
				}
			}
		}
	}
	

	
}

void CUSBKeyDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit1->SetWindowText("");
	
}
