#include "StdAfx.h"
#include "Resource.h"
#include "TreeList.h"
#include "SectionObserver.h"
#include "TSPacketStore.h"
#include "PESPacketObserver.h"

CTreeNode::CTreeNode(void)
{
	m_eNodeType = NODE_FIELD;
	m_pTSPacketStore = NULL;
	m_hTreeItem = NULL;//Its value will be set after is is inserted into a tree ctrl.
	m_uiOffset = 0;
	m_uiLength = 0;
	m_uiValue  = 0;

	m_pParent = NULL;
	m_pFirstChild = NULL;
	m_pPrev = NULL;
	m_pNext = NULL;
	m_pLastChild = NULL;
};

CTreeNode::CTreeNode(CTSPacketStore *pTSPacketStore, const wchar_t * pcFieldName, UINT32 uiOffset, UINT32 uiLength, UINT32 uiValue, ENodeType eNodeType)
	:m_strText(pcFieldName)
{
	m_eNodeType = eNodeType;
	m_pTSPacketStore = pTSPacketStore;
	m_hTreeItem = NULL;//Its value will be set after is is inserted into a tree ctrl.
	m_uiOffset = uiOffset;
	m_uiLength = uiLength;
	m_uiValue  = uiValue;

	m_pParent = NULL;
	m_pFirstChild = NULL;
	m_pPrev = NULL;
	m_pNext = NULL;
	m_pLastChild = NULL;

};

CTreeList::CTreeList(CTreeCtrl *pTreeCtrl)
{
	m_pTreeCtrl =  pTreeCtrl;
	m_pTreeNodeList = NULL;

	m_imgTreeList.Create(16, 16, TRUE | ILC_COLOR24, 17, 0);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_TREE_LIST);
	m_imgTreeList.Add(&bitmap,(CBitmap*)NULL);
	m_imgTreeList.SetBkColor(RGB(255,255,255));
	bitmap.Detach();

	pTreeCtrl->SetImageList( &m_imgTreeList, TVSIL_NORMAL);

}

CTreeList::~CTreeList(void)
{
	/*FreeNodeRecursively(m_pTreeNodeList);*/
	FreeNodeRepeatly(m_pTreeNodeList);
}

/*Freelist is a recursive function, do NOT call it for deep recursion, otherwise it will lead to stack overflow.*/
BOOL CTreeList::FreeNodeRecursively(CTreeNode *pTreeNodeInput)
{

	if(NULL == pTreeNodeInput)
	{
		return FALSE;
	}

	if(NULL != pTreeNodeInput->m_pFirstChild )
	{
		FreeNodeRecursively(pTreeNodeInput->m_pFirstChild);
	}

	if(NULL != pTreeNodeInput->m_pNext)
	{
		FreeNodeRecursively(pTreeNodeInput->m_pNext);
	}

	delete pTreeNodeInput;
	return TRUE;
}

BOOL CTreeList::FreeNodeRepeatly(CTreeNode *pTreeNodeInput)
{
	CTreeNode *pTreeNode = pTreeNodeInput;
	CTreeNode *pTreeNodeParent = NULL;
	CTreeNode *pTreeNodeNext = NULL;

	if( NULL == pTreeNode)
	{
		return FALSE;
	}

	while( NULL != pTreeNode )
	{
		while( NULL != pTreeNode->m_pFirstChild )
		{
			pTreeNode = pTreeNode->m_pFirstChild;
		}
		/*OK, it is a node without any children, we can free it now, but save its parent and next first.*/
		pTreeNodeParent = pTreeNode->m_pParent;
		pTreeNodeNext = pTreeNode->m_pNext;
		delete pTreeNode;

		if( NULL != pTreeNodeParent )
		{
			pTreeNodeParent->m_pFirstChild = pTreeNodeNext;
		}

		/*Ready to next loop.*/
		if( NULL != pTreeNodeNext)
		{
			/*The deleted node has peers, set the next loop to handle its peers.*/
			pTreeNode = pTreeNodeNext;
		}
		else
		{
			/*If it is a leaf node without any children and peers, we must go back to its parent.*/
			pTreeNode = pTreeNodeParent;
		}
	}

	return TRUE;

}
BOOL CTreeList::AppendRoot(CTreeNode *pTreeNodeInput)
{
	if( NULL == pTreeNodeInput)
		return FALSE;

	pTreeNodeInput->m_pParent = NULL;

	if( NULL != m_pTreeNodeList )
	{
		
		CTreeNode *pTreeNode = m_pTreeNodeList;
		while(NULL != pTreeNode->m_pNext)
		{
			pTreeNode = pTreeNode->m_pNext;
		}

		pTreeNode->m_pNext = pTreeNodeInput;
		pTreeNodeInput->m_pPrev = pTreeNode;
	}
	else
	{
		m_pTreeNodeList = pTreeNodeInput;
	}

	AddNodeToCtrl(pTreeNodeInput);
	return TRUE;
};


BOOL CTreeList::AppendChildFromFirst(CTreeNode *pTreeNodeChild, CTreeNode *pTreeNodeParent)
{
	if( NULL == pTreeNodeParent)
	{
		AppendRoot(pTreeNodeChild);
		return TRUE;
	}

	pTreeNodeChild->m_pParent = pTreeNodeParent;
	pTreeNodeParent->m_pLastChild = pTreeNodeChild;

	CTreeNode *pTreeNode = pTreeNodeParent->m_pFirstChild ;
	if( NULL == pTreeNode )
	{
		pTreeNodeParent->m_pFirstChild = pTreeNodeChild;
		//Add it to the tree ctrl.
		AddNodeToCtrl(pTreeNodeChild);
		return TRUE;
	}

	while(NULL != pTreeNode->m_pNext)
	{
		pTreeNode = pTreeNode->m_pNext;
	}

	pTreeNode->m_pNext = pTreeNodeChild;
	pTreeNodeChild->m_pPrev = pTreeNode;

	//Add it to the tree ctrl.
	AddNodeToCtrl(pTreeNodeChild);
	return TRUE;
};


BOOL CTreeList::AppendLastChild(CTreeNode *pTreeNodeChild, CTreeNode *pTreeNodeParent)
{
	if( NULL == pTreeNodeParent)
	{
		AppendRoot(pTreeNodeChild);
		return TRUE;
	}

	if( NULL == pTreeNodeParent->m_pLastChild )
	{
		return AppendChildFromFirst(pTreeNodeChild, pTreeNodeParent);
	}

	return InsertAfter(pTreeNodeChild, pTreeNodeParent->m_pLastChild);
};


BOOL CTreeList::AppendLast(CTreeNode *pTreeNodeInput, CTreeNode *pTreeNodePeer)
{
	if( NULL == pTreeNodePeer)
	{
		AppendRoot(pTreeNodeInput);
		return TRUE;
	}

	//They have the same parent.
	pTreeNodeInput->m_pParent = pTreeNodePeer->m_pParent;
	if( NULL != pTreeNodeInput->m_pParent )
		pTreeNodeInput->m_pParent->m_pLastChild = pTreeNodeInput;

	if( NULL == pTreeNodePeer->m_pNext )
	{
		pTreeNodePeer->m_pNext = pTreeNodeInput;
		pTreeNodeInput->m_pPrev = pTreeNodePeer;

		//Add it to the tree ctrl.
		AddNodeToCtrl(pTreeNodeInput);
		return TRUE;
	}

	CTreeNode *pTreeNode = pTreeNodePeer->m_pNext;
	while( NULL != pTreeNode->m_pNext  )
	{
		pTreeNode = pTreeNode->m_pNext;
	}

	pTreeNode->m_pNext = pTreeNodeInput;
	pTreeNodeInput->m_pPrev = pTreeNode;

	//Add it to the tree ctrl.
	AddNodeToCtrl(pTreeNodeInput);
	return TRUE;
};


BOOL CTreeList::InsertAfter(CTreeNode *pTreeNodeInput, CTreeNode *pTreeNodePeer)
{
	if( NULL == pTreeNodePeer)
	{
		AppendRoot(pTreeNodeInput);
		return TRUE;
	}

	//They have the same parent.
	pTreeNodeInput->m_pParent = pTreeNodePeer->m_pParent;
	if(( NULL != pTreeNodeInput->m_pParent ) && ( NULL == pTreeNodePeer->m_pNext ))
		pTreeNodeInput->m_pParent->m_pLastChild = pTreeNodeInput;

	if( NULL == pTreeNodePeer->m_pNext )
	{
		pTreeNodePeer->m_pNext = pTreeNodeInput;
		pTreeNodeInput->m_pPrev = pTreeNodePeer;

		//Add it to the tree ctrl.
		AddNodeToCtrl(pTreeNodeInput);
		return TRUE;
	}

	
	CTreeNode *pTreeNode = pTreeNodePeer->m_pNext;

	//Link to the next.
	pTreeNodeInput->m_pNext = pTreeNode;
	pTreeNode->m_pPrev = pTreeNodeInput;

	//Link to the previous.
	pTreeNodeInput->m_pPrev = pTreeNodePeer;
	pTreeNodePeer->m_pNext = pTreeNodeInput;

	//Add it to the tree ctrl.
	AddNodeToCtrl(pTreeNodeInput);
	return TRUE;
};


BOOL CTreeList::InsertBefore(CTreeNode *pTreeNodeInput, CTreeNode *pTreeNodePeer)
{
	if( NULL == pTreeNodePeer)
	{
		AppendRoot(pTreeNodeInput);
		return TRUE;
	}

	//They have the same parent.
	pTreeNodeInput->m_pParent = pTreeNodePeer->m_pParent;
	if(( NULL != pTreeNodeInput->m_pParent ) && ( NULL == pTreeNodePeer->m_pPrev ))
		pTreeNodeInput->m_pParent->m_pFirstChild = pTreeNodeInput;

	if( NULL == pTreeNodePeer->m_pPrev )
	{
		pTreeNodePeer->m_pPrev= pTreeNodeInput;
		pTreeNodeInput->m_pNext  = pTreeNodePeer;

		//Add it to the tree ctrl.
		AddNodeToCtrl(pTreeNodeInput);
		return TRUE;
	}

	
	CTreeNode *pTreeNode = pTreeNodePeer->m_pPrev;

	pTreeNodeInput->m_pNext = pTreeNodePeer;
	pTreeNodePeer->m_pPrev = pTreeNodeInput;

	//Link to the previous.
	pTreeNodeInput->m_pPrev = pTreeNode;
	pTreeNode->m_pNext = pTreeNodeInput;

	//Add it to the tree ctrl.
	AddNodeToCtrl(pTreeNodeInput);
	return TRUE;
};

BOOL CTreeList::AddNodeToCtrl(CTreeNode *pTreeNode)
{
	CTreeNode *pTreeNodePrev = pTreeNode->m_pPrev;

	TVINSERTSTRUCT    tvi;

	// Begin to format the field string.
	if( NODE_FIELD == pTreeNode->m_eNodeType )
	{
		if( 8 >= pTreeNode->m_uiLength )
		{
			pTreeNode->m_strText.AppendFormat(L"[%d]: 0x%02X", pTreeNode->m_uiLength, pTreeNode->m_uiValue);
		}
		else if ( ( 16 >= pTreeNode->m_uiLength ) && ( 8 < pTreeNode->m_uiLength ))
		{
			pTreeNode->m_strText.AppendFormat(L"[%d]: 0x%04X", pTreeNode->m_uiLength, pTreeNode->m_uiValue);
		}
		else
		{
			pTreeNode->m_strText.AppendFormat(L"[%d]: 0x%08X", pTreeNode->m_uiLength, pTreeNode->m_uiValue);
		}
	}
	else if(( NODE_IGNORED == pTreeNode->m_eNodeType ) || ( NODE_DATA_BYTE == pTreeNode->m_eNodeType ))
	{
		pTreeNode->m_strText.AppendFormat(L"[%d]", pTreeNode->m_uiLength);
	}


	tvi.itemex.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;	
	tvi.itemex.pszText = (LPWSTR)pTreeNode->m_strText.GetString();
	tvi.itemex.cchTextMax = 128;
	tvi.itemex.iImage = GetPicIndexFromType(pTreeNode->m_eNodeType);
	tvi.itemex.iSelectedImage = tvi.itemex.iImage;
	tvi.itemex.lParam = (LPARAM)pTreeNode;
	if( NULL == pTreeNode->m_pParent )
	{
		tvi.hParent = NULL;
	}
	else
	{
		tvi.hParent = pTreeNode->m_pParent->m_hTreeItem;
	}
	
	if( NULL == pTreeNodePrev)
	{
		tvi.hInsertAfter = TVI_FIRST;
	}
	else
	{
		tvi.hInsertAfter = pTreeNodePrev->m_hTreeItem;
	}
	


	pTreeNode->m_hTreeItem = m_pTreeCtrl->InsertItem(&tvi);
#if 1
	if(( NODE_IGNORED == pTreeNode->m_eNodeType ) || ( NODE_WARNING == pTreeNode->m_eNodeType))
	{
		m_pTreeCtrl->SelectItem(pTreeNode->m_hTreeItem);
	}
#endif	
	return TRUE;
};

void CTreeList::SelectItem(CTreeNode * pTreeNode)
{
	if( NULL != pTreeNode )
		m_pTreeCtrl->SelectItem(pTreeNode->m_hTreeItem);
}

CTreeNode * CTreeList::GetNewNodeForSection(CTreeNode * pTreeNodeParent, CSectionObserver *pSectionObserver, CTSPacketStore  *pTSPacketStoreInput)
{
	CTreeNode *pTreeNodeChild = pTreeNodeParent->m_pFirstChild;
	CTreeNode *pTreeNodeNew;
	CTSPacketStore  *pTSPacketStore;
	SINT32 siCompareResult;

	//It is the first child Node.
	if( NULL == pTreeNodeChild)
	{
		//It is a new node.
		pTreeNodeNew = new  CTreeNode(pTSPacketStoreInput, NULL, 0, pTSPacketStoreInput->GetStoredLength()*8, 0, NODE_SECTION);
		pSectionObserver->GetDescription(pTSPacketStoreInput, pTreeNodeNew->m_strText);
		AppendLastChild(pTreeNodeNew, pTreeNodeParent);
		return pTreeNodeNew;
	}

	while( NULL != pTreeNodeChild )
	{
		pTSPacketStore = pTreeNodeChild->m_pTSPacketStore;
		//Different section Store may own different compare rules.
		siCompareResult = pSectionObserver->CompareStandardSection(pTSPacketStoreInput, pTSPacketStore);
		if( 0 > siCompareResult )
		{
			break;
		}
		pTreeNodeChild = pTreeNodeChild->m_pNext;
	}

	pTreeNodeNew = new  CTreeNode(pTSPacketStoreInput, NULL, 0, pTSPacketStoreInput->GetStoredLength()*8, 0, NODE_SECTION);
	pSectionObserver->GetDescription(pTSPacketStoreInput, pTreeNodeNew->m_strText);
	if( NULL == pTreeNodeChild)
	{
		//No suitable position found, append it to the end.
		AppendLastChild(pTreeNodeNew, pTreeNodeParent);
	}
	else
	{
		//Insert it into the middle or the first.
		InsertBefore(pTreeNodeNew, pTreeNodeChild);
	}

	return pTreeNodeNew;
}

CTreeNode * CTreeList::GetParentNodeForSection(const ENodeType eNodeType)
{
	CTreeNode *pTreeNodeChild = NULL;
	CTreeNode *pTreeNodeParent = NULL;
	CTreeNode *pTreeNodeNew = NULL;
	CTreeNode *pTreeNode = NULL;
	ENodeType eNodeTypeParent;
	if(( NODE_PSI < eNodeType ) && ( NODE_SI > eNodeType))
	{
		eNodeTypeParent = NODE_PSI;
	}
	else if(( NODE_SI < eNodeType ) && ( NODE_PRIVATE_SECTION > eNodeType))
	{
		eNodeTypeParent = NODE_SI;
	}
	else
	{
		//For other type, just skip it so far.
		return NULL;
	}

	if( NULL == m_pTreeNodeList)
	{
		return NULL;
	}

	//To find the node, whose eNodeType is  NODE_PSI or NODE_SI.
	pTreeNode = m_pTreeNodeList;
	while( NULL != pTreeNode)
	{
		if(  NODE_FILE == pTreeNode->m_eNodeType)
		{
			CTreeNode *pTreeNodeTmp = pTreeNode->m_pFirstChild;
			while(NULL != pTreeNodeTmp)
			{
				if( eNodeTypeParent == pTreeNodeTmp->m_eNodeType)
				{
					pTreeNodeParent = pTreeNodeTmp;
					break;
				}
				pTreeNodeTmp = pTreeNodeTmp->m_pNext;
			}
			break;

		}
		pTreeNode = pTreeNode->m_pNext;
	}

	if( NULL == pTreeNodeParent)
	{
		return NULL;
	}

	/*
	**To add the new node as a child of NODE_PSI or NODE_SI,
	**first check whether there is a child or not.
	*/
	pTreeNodeChild = pTreeNodeParent->m_pFirstChild;
	//It is the first child Node.
	if( NULL == pTreeNodeChild)
	{
		pTreeNodeNew = new  CTreeNode(NULL, NULL, 0, 0, 0, eNodeType);
		pTreeNodeNew->m_strText.Format(L"%s", GetNodeNameFromNodeType(eNodeType));
		AppendLastChild(pTreeNodeNew, pTreeNodeParent);
		return pTreeNodeNew;
	}

	//Compare the node type, we arrange them in the order of eNodeType, from low to high.
	while( NULL != pTreeNodeChild )
	{
		if( eNodeType == pTreeNodeChild->m_eNodeType )
		{
			return pTreeNodeChild;
		}

		if( eNodeType < pTreeNodeChild->m_eNodeType )
		{
			break;
		}

		pTreeNodeChild = pTreeNodeChild->m_pNext;
	}


	//No node with same eNodeType found, create a new one.
	pTreeNodeNew = new  CTreeNode(NULL, NULL, 0, 0, 0, eNodeType);
	pTreeNodeNew->m_strText.Format(L"%s", GetNodeNameFromNodeType(eNodeType));

	if( NULL == pTreeNodeChild)
	{
		//No suitable position found, append it to the end.
		AppendLastChild(pTreeNodeNew, pTreeNodeParent);
	}
	else
	{
		//Insert it into the middle or the first.
		InsertBefore(pTreeNodeNew, pTreeNodeChild);
	}

	return pTreeNodeNew;
}


ENodeType CTreeList::GetNodeTypeFromTableId(UCHAR8 ucTableId)
{
	switch(ucTableId)
	{
		//PSI
		case TABLEID_PAT:
			return NODE_PAT;

		case TABLEID_CAT:
			return NODE_CAT;

		case TABLEID_PMT:
			return NODE_PMT;

		case TABLEID_NIT_CURRENT:
			return NODE_NIT_CURRENT;

		case TABLEID_NIT_OTHER:
			return NODE_NIT_OTHER;

		//SI
		case TABLEID_TSDT:
			return NODE_TSDT;

		case TABLEID_SDT_CURRENT:
			return NODE_SDT_CURRENT;

		case TABLEID_SDT_OTHER:
			return NODE_SDT_OTHER;

		case TABLEID_BAT:
			return NODE_BAT;

		case TABLEID_EIT_PF_CURRENT:
			return NODE_EIT_PF_CURRENT;

		case TABLEID_EIT_PF_OTHER:
			return NODE_EIT_PF_OTHER;
#if 0
		case TABLEID_EIT_SCHEDULE_CURRENT:
			return NODE_EIT_SCHEDULE_CURRENT;

		case TABLEID_EIT_SCHEDULE_OTHER:
			return NODE_EIT_SCHEDULE_OTHER;
#endif
		case TABLEID_TDT:
			return NODE_TDT;

		case TABLEID_RST:
			return NODE_RST;

#if 0
		case TABLEID_ST:
			return NODE
#endif
		case TABLEID_TOT:
			return NODE_TOT;

		case TABLEID_DIT:
			return NODE_DIT;

		case TABLEID_SIT:
			return NODE_SIT;
	}

	if(TABLEID_EIT_SCHEDULE_CURRENT == (ucTableId&0xF0))
	{
		return NODE_EIT_SCHEDULE_CURRENT;
	}

	if(TABLEID_EIT_SCHEDULE_OTHER == (ucTableId&0xF0))
	{
		return NODE_EIT_SCHEDULE_OTHER;
	}


	return NODE_PRIVATE_SECTION;
}

//const char *GetNodeNameFromNodeType(ENodeType eNodeType)
LPWSTR CTreeList::GetNodeNameFromNodeType(ENodeType eNodeType)
{
	switch(eNodeType)
	{
		case NODE_PSI:
			return L"PSI Tables[Program Specific Information]";
		case NODE_PAT:
			return L"PAT [Program Association Table]";
		case NODE_CAT:
			return L"CAT [Conditional Access Table]";
		case NODE_PMT:
			return L"PMT [Program Map Table]";
		case NODE_NIT_CURRENT:
			return L"NIT [Nerwork Information Table-Current]";
		case NODE_NIT_OTHER:
			return L"NIT [Nerwork Information Table-Other]";

		case NODE_SI:
			return L"SI Tables[Service Information]";
		case NODE_TSDT:
			return L"TSDT [Transport Stream Description Table]";
		case NODE_SDT_CURRENT:
			return L"SDT [Service Description Table-Current]";
		case NODE_SDT_OTHER:
			return L"SDT [Service Description Table-Other]";
		case NODE_BAT:
			return L"BAT [Bouquet Association Table]";
		case NODE_EIT_PF_CURRENT:
			return L"EIT [Event Information Table-Current, Present/Following]";
		case NODE_EIT_PF_OTHER:
			return L"EIT [Event Information Table-Other, Present/Following]";
		case NODE_EIT_SCHEDULE_CURRENT:
			return L"EIT [Event Information Table-Current, Schedule]";
		case NODE_EIT_SCHEDULE_OTHER:
			return L"EIT [Event Information Table-Other, Schedule]";


		case NODE_TDT:
			return L"TDT [Time and Date Table]";
		case NODE_RST:
			return L"RST [Running Status Table]";
		case NODE_TOT:
			return L"TOT [Time Offset Table]";
		case NODE_DIT:
			return L"DIT [Discontinuity Information Table]";
		case NODE_SIT:
			return L"SIT [Selection Information Table]";

		case NODE_PID_LIST:
			return L"PID List";

	}

	return L"Unknown type";
}

BOOL CTreeList::UpdateText(CTreeNode *pTreeNodeInput)
{
	m_pTreeCtrl->SetItemText(pTreeNodeInput->m_hTreeItem, pTreeNodeInput->m_strText);

	return TRUE;
}
BOOL CTreeList::UpdateImageIndex(CTreeNode *pTreeNodeInput)
{
	m_pTreeCtrl->SetItemImage(pTreeNodeInput->m_hTreeItem, GetPicIndexFromType(pTreeNodeInput->m_eNodeType), GetPicIndexFromType(pTreeNodeInput->m_eNodeType));

	return TRUE;
}
EResult CTreeList::UpdateChildCount(CTreeNode *pTreeNodeInput)
{
	if( NULL == pTreeNodeInput )
	{
		return FAILURE;
	}

	UINT32 uiChildCount = 0;
	UINT32 uiRepeatCount = 0;
	CTSPacketStore *pTSPacketStore = NULL;;

	CTreeNode *pTreeNodeNext = pTreeNodeInput->m_pFirstChild;
	while( NULL != pTreeNodeNext )
	{
		uiChildCount++;

		pTSPacketStore = pTreeNodeNext->m_pTSPacketStore;
		if( NULL != pTSPacketStore )
		{
			uiRepeatCount += pTSPacketStore->GetRepeatCount();
		}
		pTreeNodeNext = pTreeNodeNext->m_pNext;
	}

	pTreeNodeInput->m_strText.AppendFormat(L"(Total: %u, Repeat: %u)", uiChildCount, uiRepeatCount);
	this->UpdateText(pTreeNodeInput);
	return SUCCESS;
};

EResult CTreeList::UpdateAllChildCount(CTreeNode *pTreeNodeInput)
{
	if( NULL == pTreeNodeInput)
	{
		return FAILURE;
	}

	CTreeNode *pTreeNodeNextChild = pTreeNodeInput->m_pFirstChild;
	while( NULL != pTreeNodeNextChild )
	{
		UpdateChildCount(pTreeNodeNextChild);
		pTreeNodeNextChild = pTreeNodeNextChild->m_pNext;
	}
	return SUCCESS;
}

CTreeNode *CTreeList::AddSearcherInfoNode(CTreeNode *pTreeNodeInput, TMsgSearcherInfo *pSearchInfo)
{
	UINT32 uiPid = pSearchInfo->uiPid;
	ESearchType eSearchType = pSearchInfo->eSearchType;
	UINT32 uiId = pSearchInfo->uiId;
	CTreeNode *pNewTreeNode = NULL;

	CTreeNode *pTreeNodeChild = pTreeNodeInput->m_pFirstChild;
	while( NULL != pTreeNodeChild )
	{
		if( uiPid == pTreeNodeChild->m_uiValue )
		{
			break;
		}
		pTreeNodeChild = pTreeNodeChild->m_pNext;
	}

	if( NULL != pTreeNodeChild )
	{
		pNewTreeNode = new CTreeNode(NULL, 0, 0, 0, uiPid, NODE_SEARCH_RESULT);
		pNewTreeNode->m_strText.Format(L"Search type: %s, Search ID: %u", GetSearchTypeName(eSearchType), uiId);
		AppendLastChild(pNewTreeNode, pTreeNodeChild);
	}
	
	/*It shall never reach here.*/
	return pNewTreeNode;
}

LPWSTR CTreeList::GetSearchTypeName(ESearchType eSearchType)
{
	switch(eSearchType)
	{
		case SEARCH_TYPE_TS_PACKET:
			return L"TS Packet";
		case SEARCH_TYPE_DVB_SECTION:
			return L"DVB Section";
        case SEARCH_TYPE_SSU_SECTION:
            return L"SSU Section";
		case SEARCH_TYPE_PES_PACKET:
			return L"PES Packet";
	}

	return L"Unknown search type";
}


CTreeNode * CTreeList::GetNewNodeForSearchedSection(CTreeNode * pTreeNodeParent, CSectionObserver *pSectionObserver, CTSPacketStore  *pTSPacketStoreInput)
{
	
	/*For sections received in search mode, do NOT compare its value, just append it to last for efficiency consideration.*/
	CTreeNode * pTreeNodeNew = new  CTreeNode(pTSPacketStoreInput, NULL, 0, pTSPacketStoreInput->GetStoredLength()*8, 0, NODE_PRIVATE_SECTION);
	pSectionObserver->GetDescription(pTSPacketStoreInput, pTreeNodeNew->m_strText);
	AppendLastChild(pTreeNodeNew, pTreeNodeParent);

#if 0
	CTreeNode *pTreeNodeChild = pTreeNodeParent->m_pFirstChild;
	CTreeNode *pTreeNodeNew;
	CTSPacketStore  *pTSPacketStore;
	SINT32 siCompareResult;

	//It is the first child Node.
	if( NULL == pTreeNodeChild)
	{
		//It is a new node.
		pTreeNodeNew = new  CTreeNode(pTSPacketStoreInput, NULL, 0, pTSPacketStoreInput->GetStoredLength()*8, 0, NODE_PRIVATE_SECTION);
		pSectionObserver->GetDescription(pTSPacketStoreInput, pTreeNodeNew->m_strText);
		AppendLastChild(pTreeNodeNew, pTreeNodeParent);
		return pTreeNodeNew;
	}

	while( NULL != pTreeNodeChild )
	{
		pTSPacketStore = pTreeNodeChild->m_pTSPacketStore;
		//Different section Store may own different compare rules.
		siCompareResult = pSectionObserver->CompareStandardSection(pTSPacketStoreInput, pTSPacketStore);
		if( 0 > siCompareResult )
		{
			break;
		}
		pTreeNodeChild = pTreeNodeChild->m_pNext;
	}


	//No node with same eNodeType found, create a new one.
	pTreeNodeNew = new  CTreeNode(pTSPacketStoreInput, NULL, 0, pTSPacketStoreInput->GetStoredLength()*8, 0, NODE_PRIVATE_SECTION);
	pSectionObserver->GetDescription(pTSPacketStoreInput, pTreeNodeNew->m_strText);
	if( NULL == pTreeNodeChild)
	{
		//No suitable position found, append it to the end.
		AppendLastChild(pTreeNodeNew, pTreeNodeParent);
	}
	else
	{
		//Insert it into the middle or the first.
		InsertBefore(pTreeNodeNew ,pTreeNodeChild);
	}
#endif
	return pTreeNodeNew;
}

CTreeNode * CTreeList::GetNewNodeForSearchedTSPacket(CTreeNode * pTreeNodeParent, CTSPacketObserver *pTSPacketObserver, CTSPacketStore  *pTSPacketStoreInput)
{
	CTreeNode *pTreeNodeNew = new CTreeNode(pTSPacketStoreInput, NULL, 0, pTSPacketStoreInput->GetStoredLength()*8, 0, NODE_TS_PACKET);
	pTSPacketObserver->GetTSPacketDescription(pTSPacketStoreInput, pTreeNodeNew->m_strText);

	AppendLastChild(pTreeNodeNew, pTreeNodeParent);
	return pTreeNodeNew;
}


CTreeNode * CTreeList::GetNewNodeForSearchedPESPacket(CTreeNode * pTreeNodeParent, CPESPacketObserver *pPESPacketObserver, CTSPacketStore  *pTSPacketStoreInput)
{
	CTreeNode *pTreeNodeNew = new CTreeNode(pTSPacketStoreInput, NULL, 0, pTSPacketStoreInput->GetStoredLength()*8, 0, NODE_PES_PACKET);
	pPESPacketObserver->GetDescription(pTSPacketStoreInput, pTreeNodeNew->m_strText);

	AppendLastChild(pTreeNodeNew, pTreeNodeParent);
	return pTreeNodeNew;
}

SINT32 CTreeList::GetPicIndexFromType(const ENodeType eNodeType)
{
	if( NODE_FILE == eNodeType )
		return 0;
	if(( NODE_PSI <= eNodeType ) && ( NODE_SI > eNodeType ))
		return 1;
	if(( NODE_SI <= eNodeType ) && ( NODE_PRIVATE_SECTION > eNodeType ))
		return 2;
	if( NODE_PRIVATE_SECTION == eNodeType )
		return 3;
	if( NODE_SECTION == eNodeType )
		return 4;
	if( NODE_LOOP == eNodeType )
		return 5;
	if( NODE_LOOP_ITEM == eNodeType )
		return 6;
	
	if( NODE_IGNORED == eNodeType )
		return 8;
	if( NODE_DATA_BYTE == eNodeType )	
		return 9;
	if( NODE_WARNING == eNodeType )
		return 10;
	if( NODE_PID_LIST == eNodeType )
		return 11;
	if( NODE_PID == eNodeType )
		return 12;
	if( NODE_TS_PACKET == eNodeType )
		return 13;
	if( NODE_PES_PACKET == eNodeType )
		return 14;
				

	if( NODE_SEARCH_RESULT == eNodeType )
		return 15;
	if( NODE_SEQUENCE == eNodeType )
		return 16;
	if( NODE_SEQUENCE_EXTENSION == eNodeType )
		return 17;
	if( NODE_GOP == eNodeType )
		return 18;
	if( NODE_FRAME == eNodeType )
		return 19;
	if( NODE_I_FRAME == eNodeType )
		return 20;
	if( NODE_B_FRAME == eNodeType )
		return 21;
	if( NODE_P_FRAME == eNodeType )
		return 22;
	if( NODE_SLICE == eNodeType )
		return 23;
	if( NODE_MACROBLOCK == eNodeType )
		return 24;
	if( NODE_BLOCK == eNodeType )
		return 25;

	return 7;
}
