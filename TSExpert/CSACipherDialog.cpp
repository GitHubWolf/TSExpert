// CSACipherDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TSExpert.h"
#include "CSACipherDialog.h"


// CCSACipherDialog dialog

IMPLEMENT_DYNAMIC(CCSACipherDialog, CDialog)

CCSACipherDialog::CCSACipherDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCSACipherDialog::IDD, pParent)
{

}

CCSACipherDialog::~CCSACipherDialog()
{
}

void CCSACipherDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RICHEDIT_INPUTDATA, m_hexEditInputData);
    DDX_Control(pDX, IDC_RICHEDIT_OUTPUTDATA, m_hexEditOutputData);
    DDX_Control(pDX, IDC_RICHEDIT_ODDCW, m_hexEditOddCw);
    DDX_Control(pDX, IDC_RICHEDIT_EVENCW, m_hexEditEvenCw);
	DDX_Radio(pDX, IDC_RADIO_DATA_TYPES_TS_PACKET, m_siInputDataType);
	DDX_Radio(pDX, IDC_RADIO_OPERATION_TYPES_ENCRYPT_ODD, m_siOperationType);
}


BEGIN_MESSAGE_MAP(CCSACipherDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCSACipherDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SWAP, &CCSACipherDialog::OnBnClickedButtonSwap)
END_MESSAGE_MAP()


// CCSACipherDialog message handlers

void CCSACipherDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	const UINT32 CW_LENGTH = 8;
	UCHAR8 aucOddCw[CW_LENGTH], aucEvenCw[CW_LENGTH];

	EInputDataType eInputDataTpe = (EInputDataType)m_siInputDataType;
	EOperationType eOperationType = (EOperationType)m_siOperationType;

	/*Check hex data.*/
	if( FAILURE == m_hexEditInputData.ConvertStringToHex())
	{
		return;
	}

	UINT32 uiInputDataLength = m_hexEditInputData.GetDataLength();

	if( 0 == uiInputDataLength )
	{
		AfxMessageBox(L"Empty input data, can NOT continue.");
		m_hexEditInputData.SetFocus();
		return;
	}
	/*To Encrypt/Decrypt TS packet.*/
	if( INPUT_DATA_TYPE_TS_PACKET == eInputDataTpe )
	{
		/*Check data length.*/
		if( TS_PACKET_LENGTH_188 > m_hexEditInputData.GetDataLength())
		{
			AfxMessageBox(L"You choosed to process a TS packet,\r\n"
						  L"but your input data is less then 188 bytes,\r\n"
						  L"you must enter more data bytes.");
			m_hexEditInputData.SetFocus();
			return;
		}

	}


	if( FAILURE == m_hexEditOddCw.ConvertStringToHex())
	{
		return;
	}
	
	if( CW_LENGTH !=  m_hexEditOddCw.GetDataLength())
	{
		AfxMessageBox(L"You must enter 8 byte odd control words.");
		m_hexEditOddCw.SetFocus();
		return;
	}
	/*Copy odd cws.*/
	memcpy(aucOddCw, m_hexEditOddCw.GetDataBuffer(), CW_LENGTH);

	if( FAILURE == m_hexEditEvenCw.ConvertStringToHex())
	{
		return;
	}

	if( CW_LENGTH !=  m_hexEditEvenCw.GetDataLength())
	{
		AfxMessageBox(L"You must enter 8 byte even control words.");
		m_hexEditEvenCw.SetFocus();
		return;
	}
	/*Copy even cws.*/
	memcpy(aucEvenCw, m_hexEditEvenCw.GetDataBuffer(), CW_LENGTH);
		



	CCSACipher CSACipher;

	UCHAR8 *pucOutputData = new UCHAR8[uiInputDataLength];
	/*Copy input data to output data buffer.*/
	memcpy(pucOutputData,  m_hexEditInputData.GetDataBuffer(), uiInputDataLength);

	/*Ready to caculate.*/
	if( INPUT_DATA_TYPE_TS_PACKET == eInputDataTpe )
	{
		/*Decrypt or encrypt.*/
		if( OPERATION_TYPE_ENCRYPT_ODD == eOperationType )
		{
			/*Encrypt with odd cw.*/
			CSACipher.SetCW(aucOddCw,  aucEvenCw);
			CSACipher.EncryptTSPacket(pucOutputData, uiInputDataLength, FLAG_ODD);
		}
		else if( OPERATION_TYPE_ENCRYPT_EVEN == eOperationType )
		{
			/*Encrypt with even cw.*/
			CSACipher.SetCW(aucOddCw,  aucEvenCw);
			CSACipher.EncryptTSPacket(pucOutputData, uiInputDataLength, FLAG_EVEN);
		}
		else if( OPERATION_TYPE_DECRYPT_ODD == eOperationType)
		{
			/*Decrypt with odd cw.*/
			CSACipher.SetCW(aucOddCw,  aucOddCw);
			CSACipher.DecryptTSPacket(pucOutputData, uiInputDataLength);
		}
		else if( OPERATION_TYPE_DECRYPT_EVEN == eOperationType)
		{
			CSACipher.SetCW(aucEvenCw,  aucEvenCw);
			CSACipher.DecryptTSPacket(pucOutputData, uiInputDataLength);
		}
	}
	else
	{
		/*Decrypt or encrypt.*/
		if( OPERATION_TYPE_ENCRYPT_ODD == eOperationType )
		{
			/*Encrypt with odd cw.*/
			CSACipher.SetCW(aucOddCw,  aucOddCw);
			CSACipher.EncryptDataBlock(pucOutputData, uiInputDataLength);
		}
		else if( OPERATION_TYPE_ENCRYPT_EVEN == eOperationType )
		{
			/*Encrypt with even cw.*/
			CSACipher.SetCW(aucEvenCw,  aucEvenCw);
			CSACipher.EncryptDataBlock(pucOutputData, uiInputDataLength);
		}
		else if( OPERATION_TYPE_DECRYPT_ODD == eOperationType)
		{
			/*Decrypt with odd cw.*/
			CSACipher.SetCW(aucOddCw,  aucOddCw);
			CSACipher.DecryptDataBlock(pucOutputData, uiInputDataLength);
		}
		else if( OPERATION_TYPE_DECRYPT_EVEN == eOperationType)
		{
			CSACipher.SetCW(aucEvenCw,  aucEvenCw);
			CSACipher.DecryptDataBlock(pucOutputData, uiInputDataLength);
		}
	}

	/*OK, let's show output.*/
	m_hexEditOutputData.LoadFromDataBuffer(pucOutputData, uiInputDataLength);
	delete[] pucOutputData;

}

BOOL CCSACipherDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_hexEditOutputData.SetReadOnly();
	m_siInputDataType = 0;
	m_siOperationType = 0;

	m_hexEditOddCw.SetWindowTextW(L"00 00 00 00 00 00 00 00");
	m_hexEditEvenCw.SetWindowTextW(L"00 00 00 00 00 00 00 00");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCSACipherDialog::OnBnClickedButtonSwap()
{
	// TODO: Add your control notification handler code here
	CString strInputData;
	CString strOutputData;
	m_hexEditInputData.GetWindowText(strInputData);
	m_hexEditOutputData.GetWindowText(strOutputData);

	m_hexEditInputData.SetWindowText(strOutputData);
	m_hexEditOutputData.SetWindowText(strInputData);
}
