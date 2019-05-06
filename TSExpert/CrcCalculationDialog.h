#pragma once
#include "HexEdit.h"
#include "afxwin.h"
#include "CRCGenerator.h"

// CCrcCalculationDialog dialog

class CCrcCalculationDialog : public CDialog
{
	DECLARE_DYNAMIC(CCrcCalculationDialog)

public:
	CCrcCalculationDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCrcCalculationDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CRC_CALCULATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:
	CComboBox m_comboBoxCrcBits;
	CHexEdit m_hexEditDataBytes;
	CHexEdit m_hexEditPolynomial;
	CHexEdit m_hexEditInitValue;
	BOOL m_bReflectInput;
	BOOL m_bReflectOutput;
	CHexEdit m_hexEditXorValue;

	CHexEdit m_hexEditCrcResult;
};
