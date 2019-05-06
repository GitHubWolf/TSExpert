// TSExpert.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TSExpert.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "TSExpertDoc.h"
#include "TSExpertView.h"
#include "AboutDlg.h"
#include "CrcCalculationDialog.h"
#include "CSACipherDialog.h"
#include "RegistrationDialog.h"
#include "Ip2FileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*To save log message written by WriteLog.*/
static FILE *gpLogFile = NULL;
static BOOL gShowAllSSU = FALSE;

void InitLogFile(void);
void WriteLog(CString &log);
void CloseLogFile(void);


// char * to TCHAR *.
static TCHAR* A2U(char* str)
{
  int nLen=(int)strlen(str)+1;
  int   nwLen=MultiByteToWideChar(CP_ACP,0,str,nLen,NULL,0);
  TCHAR   *tstr;
  tstr=new TCHAR[nLen];
  MultiByteToWideChar(CP_ACP,0,str,nLen,tstr,nwLen);
  return tstr;
}

// TCHAR * to char *.
static char* U2A(TCHAR* tstr)
{
  char *str;
  int   nLen=(int)wcslen(tstr)+1;
  str=new char[nLen];
  WideCharToMultiByte(CP_ACP,0,tstr,nLen,str,2*nLen,NULL,NULL);
  return str;
}


// CTSExpertApp

BEGIN_MESSAGE_MAP(CTSExpertApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTSExpertApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CTSExpertApp::OnFileOpen)
	ON_COMMAND(ID_CACULATE_CRC, &CTSExpertApp::OnCaculateCRC)
	ON_COMMAND(ID_CSA_DESCRAMBLER, &CTSExpertApp::OnCSADescrambling)
	ON_COMMAND(ID_NETWORK_DUMP, &CTSExpertApp::OnNetworkDump)

	
END_MESSAGE_MAP()


// CTSExpertApp construction

CTSExpertApp::CTSExpertApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTSExpertApp object

CTSExpertApp theApp;


// CTSExpertApp initialization

BOOL CTSExpertApp::InitInstance()
{

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	AfxInitRichEdit2();

    InitLogFile();

#ifdef WITH_LIMITATION
	HKEY hKeyNtDrm;
	LONG lRetNtDrm;
	lRetNtDrm = RegOpenKeyEx( HKEY_LOCAL_MACHINE,NT_DRM, 0, KEY_READ|KEY_WRITE, &hKeyNtDrm );
#endif

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("TS Expert By Neil"));
	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_TSExpertTYPE,
		RUNTIME_CLASS(CTSExpertDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CTSExpertView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	//Enable drag and drop.
	m_pMainWnd->DragAcceptFiles(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//Don't open the default document.
	if( CCommandLineInfo::FileNew == cmdInfo.m_nShellCommand)
	{
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	}

#ifdef WITH_LIMITATION
	if( ERROR_SUCCESS != lRetNtDrm )
	{
		/*NOT registered.Let's show the registration dialog.*/
		CRegistrationDialog registrationDialog;
		registrationDialog.DoModal();

		RegCloseKey(hKeyNtDrm);
		return FALSE;
	}
#endif

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it
	m_nCmdShow = SW_MAXIMIZE;
#ifdef WITH_LIMITATION
	UINT32 uiLengthOfRegistration = sizeof(TRegistrationData) + sizeof(UINT32);
	/*Allocate new buffer.*/
	UCHAR8 *pucDataBuffer = new UCHAR8[ uiLengthOfRegistration ];

	TRegistrationData oRegistrationData;
	DWORD dwDisp;
	DWORD dwType = REG_BINARY;


	lRetNtDrm = RegQueryValueEx(hKeyNtDrm, MY_KEY, NULL,&dwType,(LPBYTE)pucDataBuffer,&dwDisp);

	if( ERROR_SUCCESS != lRetNtDrm )
	{
		delete[] pucDataBuffer;
		RegCloseKey(hKeyNtDrm);
		return FALSE;
	}

	/*Descrypt data .*/
	CCSACipher CSACipher;
	CSACipher.SetCW(CSA_KEY,  CSA_KEY);
	CSACipher.DecryptDataBlock(pucDataBuffer, uiLengthOfRegistration );

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
		delete[] pucDataBuffer;
		RegCloseKey(hKeyNtDrm);
		return FALSE;
	}

	if( MY_FIX1 != oRegistrationData.uiFixed1 )
	{
		delete[] pucDataBuffer;
		RegCloseKey(hKeyNtDrm);
		return FALSE;
	}

	if( MY_FIX2 != oRegistrationData.uiFixed2 )
	{
		delete[] pucDataBuffer;
		RegCloseKey(hKeyNtDrm);	
		return FALSE;
	}

	SYSTEMTIME oCurrentDateTime;
	::GetLocalTime(&oCurrentDateTime);

	CTime oCurrentTime( oCurrentDateTime );
	CTime oLastTime( oRegistrationData.oLastDateTime );
	CTime oExpiredTime( oRegistrationData.oExpiredDateTime );

	if( oLastTime > oCurrentTime )
	{
		delete[] pucDataBuffer;
		RegCloseKey(hKeyNtDrm);
		return FALSE;
	}

	if( oCurrentTime > oExpiredTime)
	{
		delete[] pucDataBuffer;
		RegCloseKey(hKeyNtDrm);

		return FALSE;
	}

	if( oRegistrationData.uiCurrentTimes >= oRegistrationData.uiMaxTimes)
	{
		delete[] pucDataBuffer;
		RegCloseKey(hKeyNtDrm);

		return FALSE;
	}

	/*Currently, the license is valid. Increase the executed times.*/
	oRegistrationData.uiCurrentTimes += 1;
	/*Save current time.*/
	::GetLocalTime(&oRegistrationData.oLastDateTime);

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


	/*Re-caculate CRC.*/
	uiCrcResult = CRCGenerator.GetCRC((const UCHAR8*)&oRegistrationData, sizeof(TRegistrationData));

	/*Copy back to the buffer.*/
	memcpy(pucDataBuffer, &oRegistrationData, sizeof(TRegistrationData));
	memcpy(pucDataBuffer + sizeof(TRegistrationData), &uiCrcResult, sizeof(UINT32));

	/*Encrypt it.*/
	CSACipher.EncryptDataBlock(pucDataBuffer, sizeof(TRegistrationData) + sizeof(UINT32));

	/*Write back.*/
	lRetNtDrm = RegSetValueEx
	(
		hKeyNtDrm,				            // subkey handle 
		MY_KEY,								// value name 
		0,									// must be zero 
		REG_BINARY,						// value type 
		pucDataBuffer,					// pointer to value data 
		uiLengthOfRegistration					// length of value data 
	);

	delete[] pucDataBuffer;
	RegCloseKey(hKeyNtDrm);

	if( ERROR_SUCCESS != lRetNtDrm )
	{
		return FALSE;
	}
#endif
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}
void CTSExpertApp::OnCaculateCRC()
{
	CCrcCalculationDialog CrcDialog;
	CrcDialog.DoModal();
}
void CTSExpertApp::OnCSADescrambling()
{
	CCSACipherDialog CsaCipherDialog;
	CsaCipherDialog.DoModal();
}
void CTSExpertApp::OnNetworkDump()
{
	CIp2FileDialog Ip2FileDialog;
	Ip2FileDialog.DoModal();
}


// App command to run the dialog
void CTSExpertApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CTSExpertApp message handlers


void CTSExpertApp::OnFileOpen()
{
	// TODO: Add your command handler code here
    CFileDialog fileDialogOpen(TRUE, L"Transport stream files", NULL, OFN_FILEMUSTEXIST|OFN_READONLY , L"Transport stream files(*.ts;*.mpeg;*.mpg;)|*.ts;*.mpeg;*.mpg;|All files(*.*)|*.*||", NULL);
    
    if(IDOK == fileDialogOpen.DoModal())
    {
        OpenDocumentFile(fileDialogOpen.GetPathName());
    }

}


/*To get current exe path.*/
CString GetCurrentProgramPath(void)
{
    TCHAR vPath[MAX_PATH];
    CString fullPath;

    memset(vPath, 0x0, sizeof(vPath));
    GetModuleFileName( NULL, vPath, MAX_PATH );
    int i = 0, j = 0;
    while( vPath[i]!=0 )
    {
        if( vPath[i]=='\\' )
            j = i;
        i++;
    }
    vPath[j+1] = '\0';

    fullPath.Format(L"%s", vPath );

    return fullPath;
}

/*If the file already exists, this function will overwrite it.*/
BOOL CreateNewFile(BOOL relativeFilePath, CString& fileName, FILE **ppFile)
{
    BOOL result = TRUE;
    UINT counter = 0;

    if(TRUE == result)
    {
        CString vDeviceFileName;
        LPCTSTR vDeviceFileNameStr = NULL;

        if(relativeFilePath)
        {
            /*The file is located in the same folder as the executable.*/
            vDeviceFileName.Format(L"%s%s", GetCurrentProgramPath(), fileName);
        }
        else
        {
            /*The path containing the file is set by the caller. Use it directly.*/
            vDeviceFileName.Format(L"%s", fileName);
        }
        vDeviceFileNameStr = vDeviceFileName;

        /*Convert unicode to char.*/
        const char *pFileName = U2A(vDeviceFileName.GetBuffer());


        /*Try to create device file.*/
        if( 0 != fopen_s( ppFile, pFileName, "w+" )) 
        {
            /*Failed to create a file.*/
            TRACE(L"Failed to create a file.\r\n");
        
            result = FALSE;
            *ppFile = NULL;
        }

        delete pFileName;
    }

    return result;
}


void InitLogFile(void)
{
    CreateNewFile(TRUE, CString("dump.txt"), &gpLogFile);
}
void CloseLogFile(void)
{
    fclose(gpLogFile);
}
void WriteLog(CString &log)
{
    const char *pLog = U2A(log.GetBuffer());
    fprintf(gpLogFile, pLog);
    delete pLog;
}

void SetShowAllSSUFlag(BOOL enabled)
{
    gShowAllSSU = enabled;
}
BOOL GetShowAllSSUFlag(void)
{
    return gShowAllSSU;
}



int CTSExpertApp::ExitInstance()
{
    // TODO: Add your specialized code here and/or call the base class
    CloseLogFile();
    return CWinApp::ExitInstance();
}
