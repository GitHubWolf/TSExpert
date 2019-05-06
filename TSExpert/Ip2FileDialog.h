#pragma once
#include "afxmt.h"
#include "afxwin.h"

// CIp2FileDialog dialog

class CIp2FileDialog : public CDialog
{
	DECLARE_DYNAMIC(CIp2FileDialog)

public:
	CIp2FileDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIp2FileDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_IP2FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnTSExpertMessage(WPARAM wparam,LPARAM lparam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckMulticast();

	virtual BOOL OnInitDialog();
	void StartPacketReceiver();
private:
	void ShutdownReceiverThread();
	void CloseOutputFile();
	bool HandleIPPacket(LPARAM lparam);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	void ResetStasticsData();
private:
	BOOL m_bMulticast;
	DWORD m_dwIpAddress;
	short m_wPortNumber;
	CString m_strOutputFileName;

	/*Handle to receiver thread.*/
	CWinThread* m_pPacketReceiverWorkerThread;
	/*If set to true, then receiver thread will quit.*/
	bool m_bTimeToQuit;

	/*Stastics data fields.*/
	UINT m_uiPacketCount;
	UINT m_uiDataSize;
	UINT m_uiBitrate;
	UINT m_uiSkippedSeconds;

	/*Timer to refresh UI.*/
	UINT_PTR m_uiTimer;


	CMutex  m_mutex;
	UINT32 m_uiCurrentDataSize;
	UINT m_uiPacketsPerSecond;

	/*Output file.*/
	CFile *m_pOutputFile;

};
