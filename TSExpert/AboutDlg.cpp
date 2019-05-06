#include "stdafx.h"

#include "AboutDlg.h"

// CAboutDlg dialog used for App About
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString strInfo;
    strInfo.Format(L"TSExpert Release v4.2.0, May 03, 2019.\r\n");
	strInfo.Append(L"This software is owned by Neil Chen.\r\n");
	strInfo.Append(L"It is for NON-COMMERCIAL use.\r\n");
	strInfo.Append(L"For COMMERCIAL use, you MUST get authorization from GreatChinaWolf@126.com.\r\n");
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_INFO);
	pEdit->SetWindowTextW(strInfo);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
