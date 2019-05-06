// TSExpertView.cpp : implementation of the CTSExpertView class
//

#include "stdafx.h"
#include "TSExpert.h"

#include "TSExpertDoc.h"
#include "TSExpertView.h"
#include "ChildFrm.h"

#include "TSPublic.h"
#include "TSPacketStore.h"
#include "SectionObserver.h"
#include "SectionHeaderReader.h"
#include "TSPidCounter.h"
#include "SearchSetupDialog.h"
#include "PESPacketObserver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTSExpertView

IMPLEMENT_DYNCREATE(CTSExpertView, CTreeView)
BEGIN_MESSAGE_MAP(CTSExpertView, CTreeView)
	ON_MESSAGE(ID_MSG_TSEXPERT_CORE, OnTSExpertMessage)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CTSExpertView::OnTvnSelchanged)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ADVANCED_SEARCH, &CTSExpertView::OnAdvancedSearch)
END_MESSAGE_MAP()

// CTSExpertView construction/destruction

CTSExpertView::CTSExpertView()
{
	// TODO: add construction code here
	m_pTreeList = NULL;
	m_pTreeNodePSI = NULL;
	m_pTreeNodeSI = NULL;
	m_pTreeNodePID = NULL;
	m_pTreeNodeCurrentSearcher = NULL;
}

CTSExpertView::~CTSExpertView()
{
	delete m_pTreeList;
}

BOOL CTSExpertView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CTSExpertView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CTSExpertDoc  *pDoc = (CTSExpertDoc  *)GetDocument();
	//Set font.
	CTreeCtrl& treeCtrl = this->GetTreeCtrl();
	treeCtrl.SetFont(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT))); 

	//Set style.
	DWORD dwStyle = GetWindowLong(treeCtrl.m_hWnd,GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	SetWindowLong(treeCtrl.m_hWnd,GWL_STYLE,dwStyle);

	
	m_pTreeList = new CTreeList(&this->GetTreeCtrl());


	//Add file node.
	CTreeNode *pTreeNodeFile = new CTreeNode(NULL, NULL, 0, 0, 0, NODE_FILE);
	pTreeNodeFile->m_strText.Format(L"%s[Size: %dBytes ; Packet type %dByte ; Offset %dBytes]", 
		pDoc->GetPathName(), pDoc->GetFileSize(), pDoc->GetPacketLength(), pDoc->GetValidOffset());
	m_pTreeList->AppendRoot(pTreeNodeFile);

	//Add PSI node.
	CTreeNode *pTreeNodePSI = new CTreeNode(NULL, NULL, 0, 0, 0, NODE_PSI);
	pTreeNodePSI->m_strText.Format(L"%s", m_pTreeList->GetNodeNameFromNodeType(NODE_PSI));
	m_pTreeList->AppendLastChild(pTreeNodePSI, pTreeNodeFile);

	m_pTreeNodePSI = pTreeNodePSI;

	//Add SI node.
	CTreeNode *pTreeNodeSI = new CTreeNode(NULL, NULL, 0, 0, 0, NODE_SI);
	pTreeNodeSI->m_strText.Format(L"%s",m_pTreeList->GetNodeNameFromNodeType(NODE_SI));
	m_pTreeList->AppendLastChild(pTreeNodeSI, pTreeNodeFile);

	m_pTreeNodeSI = pTreeNodeSI;

	//Add PID list node.
	CTreeNode *pTreeNodePID = new CTreeNode(NULL, NULL, 0, 0, 0, NODE_PID_LIST);
	pTreeNodePID->m_strText.Format(L"%s",m_pTreeList->GetNodeNameFromNodeType(NODE_PID_LIST));
	m_pTreeList->AppendLastChild(pTreeNodePID, pTreeNodeFile);

	m_pTreeNodePID = pTreeNodePID;

	//Expand all basic nodes.
	treeCtrl.Expand(treeCtrl.GetRootItem(), TVE_EXPAND);

}


// CTSExpertView diagnostics

#ifdef _DEBUG
void CTSExpertView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTSExpertView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTSExpertDoc* CTSExpertView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTSExpertDoc)));
	return (CTSExpertDoc*)m_pDocument;
}
#endif //_DEBUG


// CTSExpertView message handlers
LRESULT CTSExpertView::OnTSExpertMessage(WPARAM wparam,LPARAM lparam)
{
	switch(wparam)
	{
		case MESSAGE_PARSING_PROGRESS:
		{
			CChildFrame * pFrame = (CChildFrame *) GetParentFrame();
			TMsgProgress *pMsg = (TMsgProgress *)lparam;
			UINT32 uiPercent = pMsg->uiPercent;
			pFrame->DisplayProgress(uiPercent);
			delete pMsg;

			if( 100 == uiPercent)
			{
				CTreeCtrl &treeCtrl = this->GetTreeCtrl();
				treeCtrl.RedrawWindow();
			}
			break;
		}
		case MESSAGE_NEW_STANDARD_SECTION:
		{
			DisplayStandardSection(lparam);
			TRACE("MESSAGE_NEW_STANDARD_SECTION %04d\r\n", (ULONG)lparam);

			break;
		}
		case MESSAGE_PID_COUNTER_RESULT:
		{
			DisplayPidCounterResult(lparam);

			break;
		}
		case MESSAGE_PARSER_COMPLETED:
		{
			CTSExpertDoc *pDoc = (CTSExpertDoc *)GetDocument();
			if( NULL == pDoc)
			{
				break;
			}

			CTSParser *pTSParser =  pDoc->m_pTSParser;

			/*All data has been parsed.Call UpdateResult to make all observer to update their result.*/
			pTSParser->UpdateResult();

			m_pTreeList->UpdateAllChildCount(m_pTreeNodePSI);
			m_pTreeList->UpdateAllChildCount(m_pTreeNodeSI);

			/*Reset the private member to be NULL once the parser is completed.*/
			pDoc->m_pTSParserWorkerThread = NULL;
			break;
		}
		case MESSAGE_SEARCHER_INFO:
		{
			AddNewSearcherItem(lparam);
			break;
		}
		case MESSAGE_NEW_SEARCHED_SECTION:
		{
			DisplayPrivateSection(lparam);
			break;
		}
		case MESSAGE_NEW_SEARCHED_TS_PACKET:
		{
			DisplayTsPacket(lparam);
			break;

		}
		case MESSAGE_NEW_SEARCHED_PES_PACKET:
		{
			DisplayPESPacket(lparam);
			break;
		}
		case MESSAGE_SEARCHER_COMPLETED:
		{
			TMsgSearcherCompleted *pMsg = (TMsgSearcherCompleted *)lparam;
			CTSParser *pTSParser =  pMsg->pTSParser;

			/*All data has been parsed.Call UpdateResult to make all observer to update their result.*/
			pTSParser->UpdateResult();

			m_pTreeList->UpdateChildCount(m_pTreeNodeCurrentSearcher);

			delete pMsg;
			break;
		}
		default:
		{
			TRACE("Unhandled message %d\r\n", wparam);
			break;
		}
	}

	return 0;
};

BOOL CTSExpertView::DisplayStandardSection(LPARAM lparam)
{
	TMsgNewSection *pMsg = (TMsgNewSection *)lparam;

	CTSPacketStore  *pTSPacketStore = pMsg->pTSPacketStore;
	CSectionObserver *pSectionObserver = pMsg->pSectionObserver;

	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);

	ENodeType eNodeType = m_pTreeList->GetNodeTypeFromTableId(ucTableId);

	CTreeNode * pTreeNodeParent = m_pTreeList->GetParentNodeForSection(eNodeType);

	CTreeNode * pTreeNodeNew = m_pTreeList->GetNewNodeForSection(pTreeNodeParent, pSectionObserver, pTSPacketStore);

	pSectionObserver->DisplaySectionData(pTSPacketStore, m_pTreeList, pTreeNodeNew, pTreeNodeParent);
	delete pMsg;
	return TRUE;
};


BOOL CTSExpertView::DisplayPrivateSection(LPARAM lparam)
{
	TMsgNewSection *pMsg = (TMsgNewSection *)lparam;

	CTSPacketStore  *pTSPacketStore = pMsg->pTSPacketStore;
	CSectionObserver *pSectionObserver = pMsg->pSectionObserver;

	/*Since private data block may contain multiple sections, new data will be appended to the end.*/
	pSectionObserver->DisplaySectionData(pTSPacketStore, m_pTreeList, m_pTreeNodeCurrentSearcher, m_pTreeNodeCurrentSearcher->m_pParent);
	
	delete pMsg;
	return TRUE;
}


BOOL CTSExpertView::DisplayTsPacket(LPARAM lparam)
{
	TMsgNewSearchedTSPacket *pMsg = (TMsgNewSearchedTSPacket *)lparam;

	CTSPacketStore  *pTSPacketStore = pMsg->pTSPacketStore;
	CTSPacketObserver *pTSPacketObserver = pMsg->pTSPacketObserver;

	CTreeNode * pTreeNodeNew = m_pTreeList->GetNewNodeForSearchedTSPacket(m_pTreeNodeCurrentSearcher, pTSPacketObserver, pTSPacketStore);

	pTSPacketObserver->DisplayTSPacketData(pTSPacketStore, m_pTreeList, pTreeNodeNew, pTreeNodeNew->m_pParent);

	delete pMsg;
	return TRUE;
}


BOOL CTSExpertView::DisplayPESPacket(LPARAM lparam)
{
	TMsgNewSearchedPESPacket *pMsg = (TMsgNewSearchedPESPacket *)lparam;

	CTSPacketStore  *pTSPacketStore = pMsg->pTSPacketStore;
	CPESPacketObserver *pPESPacketObserver = pMsg->pPESPacketObserver;

	CTreeNode * pTreeNodeNew = m_pTreeList->GetNewNodeForSearchedPESPacket(m_pTreeNodeCurrentSearcher, pPESPacketObserver, pTSPacketStore);

	pPESPacketObserver->DisplayPESPacketData(pTSPacketStore, m_pTreeList, pTreeNodeNew, pTreeNodeNew->m_pParent);

	delete pMsg;
	return TRUE;
}

BOOL CTSExpertView::AddNewSearcherItem(LPARAM lparam)
{
	TMsgSearcherInfo *pMsg = (TMsgSearcherInfo *)lparam;
	CTreeNode *pTreeNodePid = m_pTreeNodePID;
	CTreeNode *pTreeNodeNew =  m_pTreeList->AddSearcherInfoNode(pTreeNodePid, pMsg);
	m_pTreeNodeCurrentSearcher = pTreeNodeNew;

	delete pMsg;
	return TRUE;
}

BOOL CTSExpertView::DisplayPidCounterResult(LPARAM lparam)
{
	CTSExpertDoc *pDoc = (CTSExpertDoc *)GetDocument();
	TMsgCounterResult *pMsg = (TMsgCounterResult *)lparam;

	/*Save the pid counter result pointer.*/
	pDoc->m_pMapPidCounter = pMsg->pMapPidCounter;
	CTSPidCounter *pTSPidCounter = pMsg->pTSPidCounter; 
	pTSPidCounter->DisplayResult(m_pTreeList, m_pTreeNodePID);
	delete pMsg;
	return TRUE;
}


void CTSExpertView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CTreeCtrl& treeCtrl = this->GetTreeCtrl();
	HTREEITEM hItem = treeCtrl.GetSelectedItem();

	if( NULL == hItem )
	{
		*pResult = 0;
		return;
	}

	CTSExpertDoc *pDoc = (CTSExpertDoc *)GetDocument();
	if( NULL == pDoc)
	{
		*pResult = 0;
		return;
	}

	//Save the selected information.
	CTreeNode * pTreeNode = (CTreeNode *)treeCtrl.GetItemData(hItem);

	pDoc->m_pTSPacketStore = pTreeNode->m_pTSPacketStore;
	pDoc->m_uiOffset = pTreeNode->m_uiOffset;
	pDoc->m_uiFieldLength = pTreeNode->m_uiLength;
	pDoc->m_uiFieldValue = pTreeNode->m_uiValue;
	pDoc->m_pCurrentNode = pTreeNode;

	//Update all view.
	pDoc->UpdateAllViews(this);

	*pResult = 0;
}
void CTSExpertView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnRButtonDown(nFlags, point);

	CTreeCtrl &treeCtrl = GetTreeCtrl();
	UINT uFlags;
	HTREEITEM hItem = treeCtrl.HitTest(point, &uFlags);

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
	   treeCtrl.Select(hItem, TVGN_CARET);
	}
}

void CTSExpertView::OnAdvancedSearch()
{
	// TODO: Add your command handler code here
	CSearchSetupDialog searchDialog;
	searchDialog.SetDocument(GetDocument());
	INT_PTR nReturn = searchDialog.DoModal();
	if( IDOK == nReturn)
	{
		/*Select the new node.*/
		m_pTreeList->SelectItem(m_pTreeNodeCurrentSearcher);
	}
}
