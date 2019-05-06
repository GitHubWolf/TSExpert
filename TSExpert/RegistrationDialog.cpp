// RegistrationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TSExpert.h"
#include "RegistrationDialog.h"
#include "CSACipher.h"
#include "CRCGenerator.h"

// CRegistrationDialog dialog

IMPLEMENT_DYNAMIC(CRegistrationDialog, CDialog)

CRegistrationDialog::CRegistrationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRegistrationDialog::IDD, pParent)
{

}

CRegistrationDialog::~CRegistrationDialog()
{
}

void CRegistrationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDITRegistrationData, m_editRegistration);
}


BEGIN_MESSAGE_MAP(CRegistrationDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CRegistrationDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegistrationDialog message handlers

void CRegistrationDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if( FAILURE == m_editRegistration.ConvertStringToHex() )
	{
		return;
	}

	UINT32 uiLengthOfRegistration = sizeof(TRegistrationData) + sizeof(UINT32);

	if( m_editRegistration.GetDataLength() < uiLengthOfRegistration )
	{
		AfxMessageBox(L"Invalid input data.");
		return;
	}

	UCHAR8 *pucDataBuffer = new UCHAR8[ uiLengthOfRegistration ];
	memcpy(pucDataBuffer, m_editRegistration.GetDataBuffer(), uiLengthOfRegistration);
#ifdef WITH_LIMITATION
	/*Check input license.*/
	bool bResult = TRUE;

	/*Descrypt data .*/
	CCSACipher CSACipher;
	CSACipher.SetCW(CSA_KEY,  CSA_KEY);
	CSACipher.DecryptDataBlock(pucDataBuffer, uiLengthOfRegistration );

	TRegistrationData oRegistrationData;
	UINT32 uiFileCRC;

	memcpy(&oRegistrationData, pucDataBuffer, sizeof(TRegistrationData));
	memcpy(&uiFileCRC, pucDataBuffer + sizeof(TRegistrationData), sizeof(UINT32));

	CCRCGenerator CRCGenerator(MY_POLY);
	UINT32 uiCrcResult = CRCGenerator.GetCRC((const UCHAR8*)&oRegistrationData, sizeof(TRegistrationData));	

	if( uiFileCRC == uiCrcResult )
	{

	}
	else
	{
		bResult = FALSE;
	}

	if( MY_FIX1 != oRegistrationData.uiFixed1 )
	{
		bResult = FALSE;
	}

	if( MY_FIX2 != oRegistrationData.uiFixed2 )
	{
		bResult = FALSE;
	}

	SYSTEMTIME oCurrentDateTime;
	::GetLocalTime(&oCurrentDateTime);

	CTime oCurrentTime( oCurrentDateTime );
	CTime oLastTime( oRegistrationData.oLastDateTime );
	CTime oExpiredTime( oRegistrationData.oExpiredDateTime );

	if( oLastTime > oCurrentTime )
	{
		bResult = FALSE;
	}

	if( oCurrentTime > oExpiredTime)
	{
		bResult = FALSE;
	}

	if( oRegistrationData.uiCurrentTimes >= oRegistrationData.uiMaxTimes)
	{
		bResult = FALSE;
	}

	if( FALSE == bResult )
	{
		AfxMessageBox(L"Invalid input data.");
		delete[] pucDataBuffer;
		return;
	}

	CSACipher.EncryptDataBlock(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));
#endif


	DWORD dwDisp; 

	HKEY hKeyNtDrm;
	LONG lRetNtDrm;
	lRetNtDrm = RegCreateKeyEx(HKEY_LOCAL_MACHINE, NT_DRM, 0, NULL, REG_OPTION_NON_VOLATILE,KEY_WRITE, NULL, &hKeyNtDrm, &dwDisp);

	/*Set the registration data.*/
	RegSetValueEx
	(
		hKeyNtDrm,				            // subkey handle 
		MY_KEY,								// value name 
		0,									// must be zero 
		REG_BINARY,						// value type 
		pucDataBuffer,					// pointer to value data 
		uiLengthOfRegistration					// length of value data 
	);

	RegCloseKey(hKeyNtDrm);
	delete[] pucDataBuffer;
	OnOK();
}
