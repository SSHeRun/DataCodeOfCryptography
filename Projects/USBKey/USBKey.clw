; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Start
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "USBKey.h"

ClassCount=3
Class1=CUSBKeyApp
Class2=CUSBKeyDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_USBKEY_DIALOG
Class3=Start
Resource3=IDD_START_DIALOG

[CLS:CUSBKeyApp]
Type=0
HeaderFile=USBKey.h
ImplementationFile=USBKey.cpp
Filter=N

[CLS:CUSBKeyDlg]
Type=0
HeaderFile=USBKeyDlg.h
ImplementationFile=USBKeyDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_USBKEY_DIALOG]
Type=1
Class=CUSBKeyDlg
ControlCount=3
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_EDIT1,edit,1350568068

[DLG:IDD_START_DIALOG]
Type=1
Class=Start
ControlCount=1
Control1=IDC_STATIC,static,1342308353

[CLS:Start]
Type=0
HeaderFile=Start.h
ImplementationFile=Start.cpp
BaseClass=CDialog
Filter=D
LastObject=Start

