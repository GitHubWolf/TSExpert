// KeyGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeyGenerator.h"
#include "KeyGeneratorDlg.h"

#include "CRCGenerator.h"
#include "CSACipher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CKeyGeneratorDlg dialog




CKeyGeneratorDlg::CKeyGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyGeneratorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CKeyGeneratorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CKeyGeneratorDlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyGeneratorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CKeyGeneratorDlg message handlers

BOOL CKeyGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeyGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKeyGeneratorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// OnOK();
	TRegistrationData oRegistrationData;
	memset(&oRegistrationData, 0, sizeof(TRegistrationData));

	/*Fill in date time.*/
	CDateTimeCtrl *pDateTimePicker = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_TO_EXPIRE);
	pDateTimePicker->GetTime(&oRegistrationData.oExpiredDateTime);
	::GetLocalTime(&oRegistrationData.oLastDateTime);

	/*Fill in times.*/
	CEdit *pEditTimes = (CEdit *)GetDlgItem(IDC_EDIT_MAX_TIMES);
	CString strTimes;
	pEditTimes->GetWindowTextW(strTimes);
	oRegistrationData.uiCurrentTimes = 0;
	oRegistrationData.uiMaxTimes = _wtoi(strTimes.GetString());

	/*User info.*/
	CEdit *pEditUserInfo = (CEdit *)GetDlgItem(IDC_EDIT_USER_INFO);
	CString strUserInfo;
	pEditUserInfo->GetWindowTextW(strUserInfo);
	SINT32 siUserInfoLength = strUserInfo.GetLength();
	if( 0 != siUserInfoLength )
	{
		if( USER_INFO_LENGTH <= siUserInfoLength)
		{
			_tcsncpy_s(oRegistrationData.aucUserInfo, strUserInfo, USER_INFO_LENGTH);
		}
		else
		{
			_tcsncpy_s(oRegistrationData.aucUserInfo, strUserInfo, siUserInfoLength);
		}
	}



	/*Fill in random number*/
	srand( (unsigned)time( NULL ) );
	oRegistrationData.uiRandom1 = rand();
	oRegistrationData.uiRandom2 = rand();
	oRegistrationData.uiRandom3 = rand();
	oRegistrationData.uiRandom4 = rand();
	oRegistrationData.uiRandom5 = rand();

	/*Fill in fixed number.*/
	oRegistrationData.uiFixed1 = MY_FIX1;
	oRegistrationData.uiFixed2 = MY_FIX2;


	CCRCGenerator CRCGenerator(MY_POLY);
	/*Crc result.*/
	UINT32 uiCrcResult = CRCGenerator.GetCRC((const UCHAR8*)&oRegistrationData, sizeof(TRegistrationData));	

	/*Allocate new buffer.*/
	UCHAR8 *pucDataBuffer = new UCHAR8[sizeof(TRegistrationData) + sizeof(UINT32)];
	memcpy(pucDataBuffer, &oRegistrationData, sizeof(TRegistrationData));
	memcpy(pucDataBuffer + sizeof(TRegistrationData), &uiCrcResult, sizeof(UINT32));

	/*Encrypt data buffer.*/
	CCSACipher CSACipher;
	CSACipher.SetCW(CSA_KEY,  CSA_KEY);
	CSACipher.EncryptDataBlock(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));

	CFile fileRegistrationData(L"RegistrationData.dat", CFile::modeWrite|CFile::modeCreate);
	fileRegistrationData.Write(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));
	fileRegistrationData.Close();

	delete[] pucDataBuffer;
	return;
}

void CKeyGeneratorDlg::OnBnClickedButtonCheck()
{
	// TODO: Add your control notification handler code here
	TRegistrationData oRegistrationData;

	/*Allocate new buffer.*/
	UCHAR8 *pucDataBuffer = new UCHAR8[sizeof(TRegistrationData) + sizeof(UINT32)];

	/*Read in.*/
	CFile fileRegistrationData(L"RegistrationData.dat", CFile::modeRead);
	fileRegistrationData.Read(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));
	fileRegistrationData.Close();

	/*Encrypt data buffer.*/
	CCSACipher CSACipher;
	CSACipher.SetCW(CSA_KEY,  CSA_KEY);
	CSACipher.DecryptDataBlock(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));

	UINT32 uiFileCRC;
	memcpy(&oRegistrationData, pucDataBuffer, sizeof(TRegistrationData));
	memcpy(&uiFileCRC, pucDataBuffer + sizeof(TRegistrationData), sizeof(UINT32));

	CCRCGenerator CRCGenerator(MY_POLY);
	UINT32 uiCrcResult = CRCGenerator.GetCRC((const UCHAR8*)&oRegistrationData, sizeof(TRegistrationData));	

	delete[] pucDataBuffer;

	if( uiFileCRC == uiCrcResult )
	{
		AfxMessageBox(L"OK");
	}
	else
	{
		AfxMessageBox(L"ERROR");
	}

	return;

}

void CKeyGeneratorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TRegistrationData oRegistrationData;

	/*Allocate new buffer.*/
	UCHAR8 *pucDataBuffer = new UCHAR8[sizeof(TRegistrationData) + sizeof(UINT32)];

	/*Read in.*/
	CFile fileRegistrationData(L"RegistrationData.dat", CFile::modeRead);
	fileRegistrationData.Read(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));
	fileRegistrationData.Close();

	/*Encrypt data buffer.*/
	CCSACipher CSACipher;
	CSACipher.SetCW(CSA_KEY,  CSA_KEY);
	CSACipher.DecryptDataBlock(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));

	UINT32 uiFileCRC;
	memcpy(&oRegistrationData, pucDataBuffer, sizeof(TRegistrationData));
	memcpy(&uiFileCRC, pucDataBuffer + sizeof(TRegistrationData), sizeof(UINT32));
	delete[] pucDataBuffer;

	CCRCGenerator CRCGenerator(MY_POLY);
	UINT32 uiCrcResult = CRCGenerator.GetCRC((const UCHAR8*)&oRegistrationData, sizeof(TRegistrationData));	

	if( uiFileCRC == uiCrcResult )
	{
		//AfxMessageBox(L"CRC OK");
	}
	else
	{
		AfxMessageBox(L"CRC ERROR");
		return;
	}

	if( MY_FIX1 != oRegistrationData.uiFixed1 )
	{
		AfxMessageBox(L"MY_FIXED1");
	}

	if( MY_FIX2 != oRegistrationData.uiFixed2 )
	{
		AfxMessageBox(L"MY_FIXED2");
	}

	SYSTEMTIME oCurrentDateTime;
	::GetLocalTime(&oCurrentDateTime);

	CTime oCurrentTime( oCurrentDateTime );
	CTime oLastTime( oRegistrationData.oLastDateTime );
	CTime oExpiredTime( oRegistrationData.oExpiredDateTime );

	if( oLastTime > oCurrentTime )
	{
		AfxMessageBox(L"Invalid last time");
		return;
	}

	if( oCurrentTime > oExpiredTime)
	{
		AfxMessageBox(L"Invalid expired time");
		return;
	}

	if( oRegistrationData.uiCurrentTimes >= oRegistrationData.uiMaxTimes)
	{
		AfxMessageBox(L"Exceed max times");
		return;
	}

	return;
}
