#pragma once
#include "Hexedit.h"

#define NT_DRM L"SOFTWARE\\Microsoft\\NT_DRM\\DATA\\"
#define MY_KEY L"SIG"


// CRegistrationDialog dialog

class CRegistrationDialog : public CDialog
{
	DECLARE_DYNAMIC(CRegistrationDialog)

public:
	CRegistrationDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRegistrationDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_REGISTRAION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CHexEdit m_editRegistration;
	afx_msg void OnBnClickedOk();
};
