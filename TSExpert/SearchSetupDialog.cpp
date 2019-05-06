// SearchSetupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TSExpert.h"
#include "SearchSetupDialog.h"
#include "Descriptor.h"
#include "TSParser.h"
#include "SectionStorePrivate.h"
#include "SectionStoreSSU.h"
#include "TSPacketSearcher.h"
#include "PESPacketSearcher.h"

// CSearchSetupDialog dialog

IMPLEMENT_DYNAMIC(CSearchSetupDialog, CDialog)

UINT32 CSearchSetupDialog::m_uiSearchId = 0;

CSearchSetupDialog::CSearchSetupDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchSetupDialog::IDD, pParent)
{
	m_pTSExpertDoc = NULL;
	m_uiSearchId++;
}

CSearchSetupDialog::~CSearchSetupDialog()
{
}

void CSearchSetupDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_PID, m_listBoxPid);
    DDX_Control(pDX, IDC_EDIT_MASK, m_editMask);
    DDX_Control(pDX, IDC_EDIT_MATCH, m_editMatch);
    DDX_Control(pDX, IDC_COMBO_COUNT, m_comboBoxCount);
    DDX_Text(pDX, IDC_EDIT_SEARCH_ID, m_uiSearchId);
    DDX_Control(pDX, IDC_CHECK_SHOW_ALL_SSU, m_checkBoxShowAllSSU);
}


BEGIN_MESSAGE_MAP(CSearchSetupDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CSearchSetupDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDC_RADIO_SEARCH_TYPE_TS_PACKET, &CSearchSetupDialog::OnBnClickedRadioSearchTypeTsPacket)
    ON_BN_CLICKED(IDC_RADIO_SEARCH_TYPE_SECTION, &CSearchSetupDialog::OnBnClickedRadioSearchTypeSection)
    ON_BN_CLICKED(IDC_RADIO_SEARCH_TYPE_SSU_SECTION, &CSearchSetupDialog::OnBnClickedRadioSearchTypeSsuSection)
    ON_BN_CLICKED(IDC_RADIO_SEARCH_TYPE_PES_PACKET, &CSearchSetupDialog::OnBnClickedRadioSearchTypePesPacket)
END_MESSAGE_MAP()


// CSearchSetupDialog message handlers

BOOL CSearchSetupDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	/*Set font.*/
	m_listBoxPid.SetFont(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT))); 

	/*Fill in pid list.*/
	FillInPidList();

	/*Set default to search section.*/
	((CButton *)GetDlgItem(IDC_RADIO_SEARCH_TYPE_TS_PACKET))->SetCheck(TRUE);
	m_eSearchType = SEARCH_TYPE_TS_PACKET;

	/*Fill in search count.*/
	m_comboBoxCount.InsertString(-1, L"1");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 1);
	m_comboBoxCount.InsertString(-1, L"5");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 5);
	m_comboBoxCount.InsertString(-1, L"10");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 10);
	m_comboBoxCount.InsertString(-1, L"50");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 50);
	m_comboBoxCount.InsertString(-1, L"100");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 100);
	m_comboBoxCount.InsertString(-1, L"500");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 500);
	m_comboBoxCount.InsertString(-1, L"1000");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 1000);
	m_comboBoxCount.InsertString(-1, L"10000");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 10000);
	m_comboBoxCount.InsertString(-1, L"100000");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), 100000);	
	m_comboBoxCount.InsertString(-1, L"All");
	m_comboBoxCount.SetItemData((m_comboBoxCount.GetCount() - 1), VALUE_MAX);
	/*Set default to 5.*/
	m_comboBoxCount.SetCurSel(1);

	m_editMask.SetWindowTextW(L"00");
	m_editMatch.SetWindowTextW(L"00");

    m_checkBoxShowAllSSU.SetCheck(TRUE);

	return TRUE;
}

BOOL CSearchSetupDialog::FillInPidList()
{
	if( NULL == m_pTSExpertDoc)
	{
		return FALSE;
	}
	/*GetPidList.*/
	CTSExpertDoc *pDoc = m_pTSExpertDoc;
	CTSParser *pTSParser = pDoc->m_pTSParser;
	MapPidCounter *pMapPidCounter = pDoc->m_pMapPidCounter;

	if(( NULL == pDoc ) || ( NULL == pTSParser ) || ( NULL == pMapPidCounter ))
	{
		/*The parser is NOT completed.*/
		return FALSE;
	}
	CString str;

	IteratorPidCounter iteratorPidCounter;
	for(iteratorPidCounter = pMapPidCounter->begin(); pMapPidCounter->end() != iteratorPidCounter; iteratorPidCounter++)
	{
		EPidType ePidType = pTSParser->GetPidType(iteratorPidCounter->first);
		str.Format(L"Pid: 0x%4X(%4d), Type: %s", 
			iteratorPidCounter->first, 
			iteratorPidCounter->first,
			CDescriptor::GetPidTypeName( ePidType)
			);
		m_listBoxPid.InsertString(-1, str);
		
		/*Save the PID value to list item.*/
		m_listBoxPid.SetItemData((m_listBoxPid.GetCount() - 1), iteratorPidCounter->first);
	}

	m_listBoxPid.SetCurSel(0);
	return TRUE;
}

BOOL CSearchSetupDialog::SetDocument(CTSExpertDoc *pTSExpertDoc)
{
	m_pTSExpertDoc = pTSExpertDoc;
	return TRUE;
}
void CSearchSetupDialog::OnBnClickedOk()
{
	/*Get TS Parser handler.*/
	CTSParser *pTSParser = m_pTSExpertDoc->m_pTSParser;

	/*Get search type.*/
	ESearchType eSearchType = m_eSearchType;

	/*Get search count.*/
	UINT32 uiSearchCount = (UINT32)m_comboBoxCount.GetItemData(m_comboBoxCount.GetCurSel());

	if( 0 == m_listBoxPid.GetCount() )
	{
		AfxMessageBox(L"No PID selected, can NOT continue.");
		return;
	}
	/*Get PID value.*/
	UINT32 uiPid = (UINT32)m_listBoxPid.GetItemData(m_listBoxPid.GetCurSel());

	/*To store length of mask and match.*/
	UINT32 uiMaskLength, uiMatchLength;
	const UCHAR8 *pucDataMask  = NULL;
	const UCHAR8 *pucDataMatch = NULL;

	if(( SEARCH_TYPE_DVB_SECTION == eSearchType) || ( SEARCH_TYPE_SSU_SECTION == eSearchType))
	{
		/*Get mask.*/
		if (FAILURE == m_editMask.ConvertStringToHex())
		{
			return;
		}
		uiMaskLength = m_editMask.GetDataLength();
		pucDataMask  = m_editMask.GetDataBuffer();

		/*Get match.*/
		if (FAILURE == m_editMatch.ConvertStringToHex())
		{
			return;
		}
		uiMatchLength = m_editMatch.GetDataLength();
		pucDataMatch  = m_editMatch.GetDataBuffer();

		if( 0 == uiMaskLength)
		{
			AfxMessageBox(L"ZERO mask length is now allowed.");
			m_editMask.SetFocus();
			return;
		}

		if( 0 == uiMatchLength)
		{
			AfxMessageBox(L"ZERO match length is now allowed.");
			m_editMatch.SetFocus();
			return;
		}

		if( uiMaskLength != uiMatchLength )
		{
			AfxMessageBox(L"Mask length is NOT equal to match length.");
			m_editMask.SetFocus();
			return;
		}

	}

	/*Get PID type.*/
	EPidType ePidType = pTSParser->GetPidType( uiPid );

	/*If selected PID  is a PID of DVB sections.*/
	if(( PID_TYPE_PAT <= ePidType ) && ( PID_TYPE_H2220_13818_1_PRIVATE_SECTION >= ePidType ))
	{
		if( SEARCH_TYPE_PES_PACKET == eSearchType)
		{
			SINT32 siResult = AfxMessageBox(L"You selected a PID for DVB sections,\r\n"
									L"but you choosed to search PES data,\r\n"
									L"data found will be regarded as a PES packet,\r\n"
									L"it may result to crash,\r\n"
									L"do you really mean it?", 
									MB_YESNOCANCEL
									);
			
			if( IDYES != siResult )
			{
				return;
			}
		}
	}
	else
	{
		if(( SEARCH_TYPE_DVB_SECTION == eSearchType) || ( SEARCH_TYPE_SSU_SECTION == eSearchType))
		{
			SINT32 siResult = AfxMessageBox(L"You selected a PID for PES packets,\r\n"
									L"but you choosed to search section data,\r\n"
									L"data found will be regarded as a section,\r\n"
									L"it may result to crash,\r\n"
									L"do you really mean it?", 
									MB_YESNOCANCEL
									);
			
			if( IDYES != siResult )
			{
				return;
			}
		}
	}

	/*Checking completed.Let's go.*/

	/*Increase search ID.*/
	m_uiSearchId++;
	UpdateData(FALSE);

	CTSExpertDoc *pTSExpertDoc = m_pTSExpertDoc;


	EPacketLength ePacketLength = pTSExpertDoc->GetPacketLength();
	FILE * vFile = pTSExpertDoc->GetFile();
	UINT32 uiDataLength = pTSExpertDoc->GetDataLength();

	//Create a CTSParser as worker to analyse the input file.
	CTSParser *pTSSearcher = new CTSParser;

	pTSExpertDoc->AddSearcher(pTSSearcher);

	pTSSearcher->m_pTSExpertDoc = pTSExpertDoc;

	switch( eSearchType )
	{
		case SEARCH_TYPE_TS_PACKET:
		{
			CTSPacketSearcher *pTSPacketSearcher = new CTSPacketSearcher(pTSSearcher);
			pTSSearcher->AttachPacketObserver(uiPid, pTSPacketSearcher);
			break;
		}
		case SEARCH_TYPE_DVB_SECTION:
		{
			/*Setup parser task to search certain sections.*/
			CSectionStorePrivate *pSectionStorePrivate = new CSectionStorePrivate(uiPid, TABLE_NAME_PRIVATE, pTSSearcher);
			pSectionStorePrivate->SetFilter(pucDataMask, pucDataMatch, uiMaskLength);
			pTSSearcher->AttachSectionObserver(uiPid, pSectionStorePrivate);
			
			break;
		}
		case SEARCH_TYPE_SSU_SECTION:
		{
			/*Setup parser task to search certain sections.*/
			CSectionStoreSSU *pSectionStoreSSU = new CSectionStoreSSU(uiPid, TABLE_NAME_SSU, pTSSearcher);
			pSectionStoreSSU->SetFilter(pucDataMask, pucDataMatch, uiMaskLength);
			pTSSearcher->AttachSectionObserver(uiPid, pSectionStoreSSU);

            /*Set the flag here, it will be read by SSU section parser class.*/
			SetShowAllSSUFlag(m_checkBoxShowAllSSU.GetCheck());

			break;
		}

		case SEARCH_TYPE_PES_PACKET:
		{
			/*Setup parser task to search certain PES packets.*/
			CPESPacketSearcher *pPESPacketSearcher = new CPESPacketSearcher(uiPid, PACKET_NAME_PES, pTSSearcher);
			pTSSearcher->AttachPESPacketObserver(uiPid, pPESPacketSearcher);
			break;
		}
		default:
		{
			AfxMessageBox(L"Program ERROR: unhandled case.");
		}

	}

	fseek(vFile, pTSExpertDoc->GetValidOffset(), SEEK_SET);

	/*Start search with search count.*/
	pTSSearcher->StartSearch(ePacketLength, vFile, uiDataLength, uiPid, uiSearchCount, eSearchType, m_uiSearchId);
	
	CDialog::OnOK();

}

void CSearchSetupDialog::OnBnClickedRadioSearchTypeTsPacket()
{
	m_eSearchType = SEARCH_TYPE_TS_PACKET;
	m_editMask.EnableWindow(FALSE);
	m_editMatch.EnableWindow(FALSE);
    m_checkBoxShowAllSSU.EnableWindow(FALSE);
}

void CSearchSetupDialog::OnBnClickedRadioSearchTypeSection()
{
	m_eSearchType = SEARCH_TYPE_DVB_SECTION;
	m_editMask.EnableWindow(TRUE);
	m_editMatch.EnableWindow(TRUE);
    m_checkBoxShowAllSSU.EnableWindow(FALSE);
}

void CSearchSetupDialog::OnBnClickedRadioSearchTypeSsuSection()
{
	m_eSearchType = SEARCH_TYPE_SSU_SECTION;
	m_editMask.EnableWindow(TRUE);
	m_editMatch.EnableWindow(TRUE);
    m_checkBoxShowAllSSU.EnableWindow(TRUE);
}

void CSearchSetupDialog::OnBnClickedRadioSearchTypePesPacket()
{
	m_eSearchType = SEARCH_TYPE_PES_PACKET;
	m_editMask.EnableWindow(FALSE);
	m_editMatch.EnableWindow(FALSE);
    m_checkBoxShowAllSSU.EnableWindow(FALSE);
}
