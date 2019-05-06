#pragma once
#include "TSPublic.h"
#include "CSACipher.h"
#include "Hexedit.h"

/*Do NOT modify the order of the following enums.*/
enum EInputDataType
{
	INPUT_DATA_TYPE_TS_PACKET = 0,
	INPUT_DATA_TYPE_DATA_BYTES
};

/*Do NOT modify the order of the following enums.*/
enum EOperationType
{
	OPERATION_TYPE_ENCRYPT_ODD = 0,
	OPERATION_TYPE_ENCRYPT_EVEN,
	OPERATION_TYPE_DECRYPT_ODD,
	OPERATION_TYPE_DECRYPT_EVEN,
};

// CCSACipherDialog dialog

class CCSACipherDialog : public CDialog
{
	DECLARE_DYNAMIC(CCSACipherDialog)

public:
	CCSACipherDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCSACipherDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CSA_CIPHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioDataTypesDataBytes();
private:
	CHexEdit m_hexEditInputData;
	CHexEdit m_hexEditOutputData;
	CHexEdit m_hexEditOddCw;
	CHexEdit m_hexEditEvenCw;
	SINT32 m_siInputDataType;
	SINT32 m_siOperationType;


	afx_msg void OnBnClickedRadioDataTypesTsPacket();
	afx_msg void OnBnClickedButtonSwap();
};
