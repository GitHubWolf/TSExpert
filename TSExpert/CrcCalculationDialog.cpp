// CrcCalculationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TSExpert.h"
#include "CrcCalculationDialog.h"


// CCrcCalculationDialog dialog

IMPLEMENT_DYNAMIC(CCrcCalculationDialog, CDialog)

CCrcCalculationDialog::CCrcCalculationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCrcCalculationDialog::IDD, pParent)
	, m_bReflectInput(FALSE)
	, m_bReflectOutput(FALSE)
{

}

CCrcCalculationDialog::~CCrcCalculationDialog()
{
}

void CCrcCalculationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HEX_RICHEDIT_DATA_BYTES, m_hexEditDataBytes);
	DDX_Control(pDX, IDC_COMBO_CRC_BITS, m_comboBoxCrcBits);
    DDX_Control(pDX, IDC_RICHEDIT_POLYNOMIA, m_hexEditPolynomial);
    DDX_Control(pDX, IDC_RICHEDIT_INITVALUE, m_hexEditInitValue);
    DDX_Check(pDX, IDC_CHECK_REFLECTINPUT, m_bReflectInput);
    DDX_Check(pDX, IDC_CHECK_REFLECTOUTPUT, m_bReflectOutput);
    DDX_Control(pDX, IDC_RICHEDIT_CRCRESULT, m_hexEditCrcResult);
    DDX_Control(pDX, IDC_RICHEDIT_XORVALUE, m_hexEditXorValue);
}


BEGIN_MESSAGE_MAP(CCrcCalculationDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCrcCalculationDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCrcCalculationDialog message handlers

void CCrcCalculationDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if( FAILURE == m_hexEditDataBytes.ConvertStringToHex() )
	{
		return ;
	}

	if( FAILURE == m_hexEditPolynomial.ConvertStringToHex() )
	{
		return ;
	}

	if( FAILURE == m_hexEditInitValue.ConvertStringToHex() )
	{
		return ;
	}

	if( FAILURE == m_hexEditXorValue.ConvertStringToHex() )
	{
		return ;
	}

	UINT32 uiBytes = (UINT32)m_comboBoxCrcBits.GetItemData(m_comboBoxCrcBits.GetCurSel())/8;

	if( uiBytes != m_hexEditPolynomial.GetDataLength() )
	{
		CString msg;
		msg.Format(L"Invalid polynomial, please enter %u bytes heximal polynomial", uiBytes);
		AfxMessageBox(msg);
		m_hexEditPolynomial.SetFocus();
		return ;
	}

	if( uiBytes != m_hexEditInitValue.GetDataLength() )
	{
		CString msg;
		msg.Format(L"Invalid init value, please enter %u bytes heximal init value", uiBytes);
		AfxMessageBox(msg);
		m_hexEditInitValue.SetFocus();
		return ;
	}

	if( uiBytes != m_hexEditXorValue.GetDataLength() )
	{
		CString msg;
		msg.Format(L"Invalid XOR value, please enter %u bytes XOR value", uiBytes);
		AfxMessageBox(msg);
		m_hexEditXorValue.SetFocus();
		return ;
	}

	UINT32 uiPolynomial;
	if( FAILURE == m_hexEditPolynomial.ReadNBytes(uiPolynomial, uiBytes) )
	{
		return ;
	}

	UINT32 uiInitValue;
	if( FAILURE == m_hexEditInitValue.ReadNBytes(uiInitValue, uiBytes) )
	{
		return ;
	}

	UINT32 uiXorValue;
	if( FAILURE == m_hexEditXorValue.ReadNBytes(uiXorValue, uiBytes) )
	{
		return ;
	}

	CCRCGenerator CrcGenerator(	uiPolynomial, uiBytes*8, uiInitValue, m_bReflectInput, m_bReflectOutput, uiXorValue);

	UINT32 uiCrcResult = CrcGenerator.GetCRC(m_hexEditDataBytes.GetDataBuffer(), m_hexEditDataBytes.GetDataLength());
	CString strFormat;
	strFormat.Format(L"%%0%uX", uiBytes*2);
	CString strResult;
	strResult.Format(strFormat, uiCrcResult);
	m_hexEditCrcResult.SetWindowTextW(strResult);

}

BOOL CCrcCalculationDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	/*CRC length.*/
	m_comboBoxCrcBits.InsertString(-1, L"32");
	m_comboBoxCrcBits.SetItemData((m_comboBoxCrcBits.GetCount() - 1), 32);
	m_comboBoxCrcBits.InsertString(-1, L"24");
	m_comboBoxCrcBits.SetItemData((m_comboBoxCrcBits.GetCount() - 1), 24);
	m_comboBoxCrcBits.InsertString(-1, L"16");
	m_comboBoxCrcBits.SetItemData((m_comboBoxCrcBits.GetCount() - 1), 16);
	m_comboBoxCrcBits.InsertString(-1, L"8");
	m_comboBoxCrcBits.SetItemData((m_comboBoxCrcBits.GetCount() - 1), 8);
	m_comboBoxCrcBits.SetCurSel(0);

	/*Polynomial*/
	CString strPolynomial;
	strPolynomial.Format(L"%08X", DEFAULT_POLYNOMIAL);
	m_hexEditPolynomial.SetWindowTextW(strPolynomial);

	/*Init value.*/
	CString strInitValue;
	strInitValue.Format(L"%08X", DEFAULT_REGISTER_VALUE);
	m_hexEditInitValue.SetWindowTextW(strInitValue);

	/*Reflect in.*/
	m_bReflectInput = FALSE;

	/*Reflect out.*/
	m_bReflectOutput = FALSE;

	/*XOR value.*/
	CString strXorValue;
	strXorValue.Format(L"%08X", DEFAULT_XOR_VALUE);
	m_hexEditXorValue.SetWindowTextW(strXorValue);


	UpdateData(FALSE);
	m_hexEditCrcResult.SetWindowTextW(L"");
	m_hexEditCrcResult.SetReadOnly(TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
