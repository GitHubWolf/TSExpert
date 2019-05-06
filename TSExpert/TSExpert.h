// TSExpert.h : main header file for the TSExpert application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


void WriteLog(CString &log);
void SetShowAllSSUFlag(BOOL enabled);
BOOL GetShowAllSSUFlag(void);


// CTSExpertApp:
// See TSExpert.cpp for the implementation of this class
//

class CTSExpertApp : public CWinApp
{
public:
	CTSExpertApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnCaculateCRC();
	afx_msg void OnCSADescrambling();
	afx_msg void OnNetworkDump();
    virtual int ExitInstance();
};

extern CTSExpertApp theApp;
