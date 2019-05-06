// Ip2FileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TSExpert.h"
#include "Ip2FileDialog.h"
#include "UdpSocketHelper.h"

UINT PacketReceiverWorkerFunction( LPVOID pParam )
{
	CIp2FileDialog *pIp2FileDialog = (CIp2FileDialog *)pParam;
	pIp2FileDialog->StartPacketReceiver();
	
	return SUCCESS;
}


static const DWORD DEFAULT_IP_ADDRESS = 0xE0000001;
static const unsigned short DEFAULT_PORT_NUMBER = 1234;



// CIp2FileDialog dialog

IMPLEMENT_DYNAMIC(CIp2FileDialog, CDialog)

CIp2FileDialog::CIp2FileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CIp2FileDialog::IDD, pParent)
	, m_bMulticast(FALSE)
	, m_dwIpAddress(0)
	, m_wPortNumber(0)
	, m_strOutputFileName(_T(""))
	, m_uiPacketCount(0)
	, m_uiDataSize(0)
	, m_uiBitrate(0)
	, m_uiSkippedSeconds(0)
	, m_uiPacketsPerSecond(0)
{
	m_pPacketReceiverWorkerThread = NULL;
	m_bTimeToQuit = false;
	m_uiTimer = 0;
	m_uiCurrentDataSize = 0;
	m_pOutputFile = 0;
}

CIp2FileDialog::~CIp2FileDialog()
{
}

void CIp2FileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_MULTICAST, m_bMulticast);
	DDX_IPAddress(pDX, IDC_IPADDRESS_MULTICAST_ADDRESS, m_dwIpAddress);
	DDX_Text(pDX, IDC_EDIT_PORT_NUMBER, m_wPortNumber);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_FILE_NAME, m_strOutputFileName);
	DDX_Text(pDX, IDC_EDIT_PACKET_COUNT, m_uiPacketCount);
	DDX_Text(pDX, IDC_EDIT_DATA_SIZE, m_uiDataSize);
	DDX_Text(pDX, IDC_EDIT_BITRATE, m_uiBitrate);
	DDX_Text(pDX, IDC_EDIT_TIME_SKIPPED, m_uiSkippedSeconds);
	DDX_Text(pDX, IDC_EDIT_PACKET_PER_SECOND, m_uiPacketsPerSecond);
}


BEGIN_MESSAGE_MAP(CIp2FileDialog, CDialog)
	ON_BN_CLICKED(IDC_CHECK_MULTICAST, &CIp2FileDialog::OnBnClickedCheckMulticast)
	ON_BN_CLICKED(IDC_BUTTON_START, &CIp2FileDialog::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CIp2FileDialog::OnBnClickedButtonStop)
	ON_MESSAGE(ID_MSG_TSEXPERT_CORE, &CIp2FileDialog::OnTSExpertMessage)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CIp2FileDialog message handlers

void CIp2FileDialog::OnBnClickedCheckMulticast()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CIPAddressCtrl *pIPAddressCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_MULTICAST_ADDRESS);

	if( m_bMulticast )
	{		
		pIPAddressCtrl->EnableWindow(TRUE);
	}
	else
	{
		pIPAddressCtrl->EnableWindow(FALSE);
	}

}

BOOL CIp2FileDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_bMulticast = TRUE;
	m_dwIpAddress = DEFAULT_IP_ADDRESS;
	m_wPortNumber = DEFAULT_PORT_NUMBER;

	/*Disable STOP button.*/
	CButton *pButtonStop = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
	pButtonStop->EnableWindow(FALSE);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CIp2FileDialog::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here

	/*To retrieve data.*/
	UpdateData(TRUE);

	/*Check whether there is a valid multicast address.*/
	if( m_bMulticast && (!IsMulticastAddress((ULONG)htonl(m_dwIpAddress))))
	{
		AfxMessageBox(L"Invalid multicast address. Please re-enter a valid address.");
		CIPAddressCtrl *pIPAddressCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_MULTICAST_ADDRESS);
		pIPAddressCtrl->SetFocus();
		return;
	}


	CFileDialog fileDialog(FALSE, NULL, NULL, (OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT), L"All files|*.*||", NULL);
	if( IDOK != fileDialog.DoModal() )
	{
		return;
	}

	m_strOutputFileName = fileDialog.GetPathName();

	/*To show data.*/
	UpdateData(FALSE);

	CIPAddressCtrl *pIPAddressCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_MULTICAST_ADDRESS);
	pIPAddressCtrl->EnableWindow(FALSE);

	CButton *pButtonMulticast = (CButton *)GetDlgItem(IDC_CHECK_MULTICAST);
	pButtonMulticast->EnableWindow(FALSE);

	CEdit *pEditPortNumber = (CEdit *)GetDlgItem(IDC_EDIT_PORT_NUMBER);
	pEditPortNumber->EnableWindow(FALSE);

	/*Also disable itself.*/
	CButton *pButtonStart = (CButton *)GetDlgItem(IDC_BUTTON_START);
	pButtonStart->EnableWindow(FALSE);

	/*Enable STOP button.*/
	CButton *pButtonStop = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
	pButtonStop->EnableWindow(TRUE);


	/*Clear UI information.*/
	ResetStasticsData();

	m_mutex.Lock();
	if( NULL == m_pPacketReceiverWorkerThread )
	{
		/*Everything OK. We are going to create a thread to receive packets.*/
		m_bTimeToQuit = false;
		m_pPacketReceiverWorkerThread = AfxBeginThread(PacketReceiverWorkerFunction, this);
	}
	m_mutex.Unlock();

	/*If the old timer is still running, shut it down.*/
	if( m_uiTimer )
	{
		/*Stop timer now.*/
		KillTimer(m_uiTimer); 
		m_uiTimer = 0;
	}

	/*Start a timer to refresh UI.*/
	m_uiTimer = SetTimer(1, 1000, 0);

	/*Create a file to save input packets. If NOT empty, close it first.*/
	CloseOutputFile();
	m_pOutputFile  = new CFile(m_strOutputFileName, CFile::shareDenyWrite|CFile::modeCreate|CFile:: modeReadWrite);


}


void CIp2FileDialog::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	CButton *pButtonMulticast = (CButton *)GetDlgItem(IDC_CHECK_MULTICAST);
	pButtonMulticast->EnableWindow(TRUE);

	/*Enable IPAddress input only if it is going to receive multicast.*/
	if(m_bMulticast)
	{
		CIPAddressCtrl *pIPAddressCtrl = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_MULTICAST_ADDRESS);
		pIPAddressCtrl->EnableWindow(TRUE);
	}

	CEdit *pEditPortNumber = (CEdit *)GetDlgItem(IDC_EDIT_PORT_NUMBER);
	pEditPortNumber->EnableWindow(TRUE);

	/*Disable itself.*/
	CButton *pButtonStop = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
	pButtonStop->EnableWindow(FALSE);

	/*Enable START button.*/	
	CButton *pButtonStart = (CButton *)GetDlgItem(IDC_BUTTON_START);
	pButtonStart->EnableWindow(TRUE);

	ShutdownReceiverThread();

	if( m_uiTimer )
	{
		/*Stop timer now.*/
		KillTimer(m_uiTimer); 
		m_uiTimer = 0;
	}

	CloseOutputFile();

}

void CIp2FileDialog::ShutdownReceiverThread()
{
	m_mutex.Lock();

	if( NULL != m_pPacketReceiverWorkerThread )
	{
		m_bTimeToQuit = true;
		m_mutex.Unlock();
		//Sleep(2000);
		WaitForSingleObject(m_pPacketReceiverWorkerThread->m_hThread,INFINITE);

	}
	else
	{
		m_mutex.Unlock();
	}
}

void CIp2FileDialog::CloseOutputFile()
{
	if( NULL != m_pOutputFile )
	{
		m_pOutputFile->Close();

		delete m_pOutputFile;
		m_pOutputFile = NULL;
	}
}


void CIp2FileDialog::StartPacketReceiver()
{ 
	fd_set fdSetRead;
	SOCKET  fdSocket;
	SOCKET fdReturned;
	struct timeval stTimeout;
	SOCKET socketReceiver;
	if(!CreateUdpSocket(socketReceiver, 0, htons(m_wPortNumber), htonl(m_dwIpAddress)))
	{
		m_mutex.Lock();
		/*Failed to create socket, return directly.*/
		m_pPacketReceiverWorkerThread = NULL;
		m_mutex.Unlock();

		return;
	}
	
	char * pcSocketBuffer = new char[IP_PACKET_MTU];


	while( true )
	{
		m_mutex.Lock();
		if(m_bTimeToQuit)
		{
			m_mutex.Unlock();
			break;
		}
		m_mutex.Unlock();

		/*Clear fd_set first.*/
		FD_ZERO(&fdSetRead);

		/*Add socket to receive packets.*/
		FD_SET(socketReceiver, &fdSetRead);
		fdSocket = socketReceiver + 1;

		/*Reset timer.Select will timeout in 2 seconds.*/
		stTimeout.tv_sec = 1;
		stTimeout.tv_usec = 0;

		/*Everything is ready now.Let's select now.*/
		fdReturned = select((int)fdSocket,&fdSetRead,NULL,NULL,&stTimeout);

		if( fdReturned <= 0 )
		{
			/*Nothing got.*/
			int iSocketError = WSAGetLastError();
			continue;
		}

		/*Try to find out which socket has got a packet.*/
		if( FD_ISSET( socketReceiver, &fdSetRead) )
		{

			/*Read socket data here.*/
			sockaddr_in socketAddr;
			memset(&socketAddr, 0, sizeof(socketAddr));

			int siSockLen = sizeof(struct sockaddr_in);

			/*Save the command to the buffer.*/
			int iResult = recvfrom(socketReceiver, (char *)pcSocketBuffer, IP_PACKET_MTU, 0, (struct sockaddr *)&socketAddr,&siSockLen);
			if(  0 < iResult )
			{
				/*We get a packet. Allocate memory to save the incoming packet.*/
				UCHAR8 *pucPacket = new UCHAR8[iResult];

				/*Copy incoming packet.*/
				memcpy(pucPacket, pcSocketBuffer, iResult);

				TMsgIPPacket *pMsg = new TMsgIPPacket;
				pMsg->uiPacketLength = iResult;
				pMsg->uiMilliseconds = (UINT32)(XGetTickCount()/1000);
				pMsg->pucPacket = pucPacket;


				/*Queue the message.*/
				this->PostMessage(ID_MSG_TSEXPERT_CORE, MESSAGE_NEW_IP_PACKET, (LPARAM)pMsg);

				m_mutex.Lock();
				m_uiCurrentDataSize += iResult;
				++m_uiPacketsPerSecond;
				m_mutex.Unlock();
			}

			fdReturned--;
		}

	}


	delete[] pcSocketBuffer;
	CleanUpSocket(socketReceiver);

	m_mutex.Lock();
	m_pPacketReceiverWorkerThread = NULL;
	m_mutex.Unlock();

	TRACE("----------------------StartPacketReceiver End.\n");
}


LRESULT CIp2FileDialog::OnTSExpertMessage(WPARAM wparam,LPARAM lparam)
{
	switch(wparam)
	{
		case MESSAGE_NEW_IP_PACKET:
		{
			HandleIPPacket(lparam);
			break;
		}
		default:
		{
			TRACE("Unhandled message %d\r\n", wparam);
			break;
		}
	}

	return 0;
}

bool CIp2FileDialog::HandleIPPacket(LPARAM lparam)
{
	TMsgIPPacket *pMsg = (TMsgIPPacket *)lparam;

	/*Update stastic data.*/
	++m_uiPacketCount;
	m_uiDataSize += pMsg->uiPacketLength;

	/*To caculate bit rate.*/
	m_uiBitrate = 0;

	/*Write it into file now.*/
	if( NULL != m_pOutputFile )
	{
		m_pOutputFile->Write(pMsg->pucPacket, pMsg->uiPacketLength);
	}

	delete[] pMsg->pucPacket;
	delete pMsg;

	return true;
}


void CIp2FileDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//MessageBeep(0xFFFFFFFF); 
	++m_uiSkippedSeconds;

	m_mutex.Lock();
	m_uiBitrate = m_uiCurrentDataSize*8;
	m_uiCurrentDataSize = 0;
	m_mutex.Unlock();

	/*Refresh UI.*/
	UpdateData(FALSE);

	m_mutex.Lock();
	m_uiPacketsPerSecond = 0;
	m_mutex.Unlock();

	CDialog::OnTimer(nIDEvent);
}


void CIp2FileDialog::ResetStasticsData()
{
	m_uiPacketCount = 0;
	m_uiDataSize = 0;
	m_uiBitrate = 0;
	m_uiSkippedSeconds = 0;

	m_uiCurrentDataSize = 0;
}

void CIp2FileDialog::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	ShutdownReceiverThread();

	CloseOutputFile();

	/*If the old timer is still running, shut it down.*/
	if( m_uiTimer )
	{
		/*Stop timer now.*/
		KillTimer(m_uiTimer); 
		m_uiTimer = 0;
	}

	m_mutex.Lock();
	CDialog::OnClose();
}
