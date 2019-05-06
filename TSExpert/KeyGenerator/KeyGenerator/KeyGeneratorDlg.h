// KeyGeneratorDlg.h : header file
//

#pragma once


// CKeyGeneratorDlg dialog
class CKeyGeneratorDlg : public CDialog
{
// Construction
public:
	CKeyGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KEYGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedButtonCheck();
public:
	afx_msg void OnBnClickedButton1();
};
