#pragma once
#include "afxwin.h"
#include "TSExpertDoc.h"
#include "HexEdit.h"

// CSearchSetupDialog dialog
class CSearchSetupDialog : public CDialog
{
	DECLARE_DYNAMIC(CSearchSetupDialog)

public:
	CSearchSetupDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchSetupDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_SEARCH_SETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL SetDocument(CTSExpertDoc *pTSExpertDoc);
private:
	CTSExpertDoc *m_pTSExpertDoc;
	CComboBox m_comboBoxCount;
	CHexEdit m_editMask;
	CHexEdit m_editMatch;
	CListBox m_listBoxPid;
	ESearchType m_eSearchType;
    CButton m_checkBoxShowAllSSU;
private:
	BOOL FillInPidList();
	afx_msg void OnBnClickedOk();
private:
	static UINT32 m_uiSearchId;
public:
    afx_msg void OnBnClickedRadioSearchTypeTsPacket();
    afx_msg void OnBnClickedRadioSearchTypeSection();
    afx_msg void OnBnClickedRadioSearchTypeSsuSection();
    afx_msg void OnBnClickedRadioSearchTypePesPacket();
};
