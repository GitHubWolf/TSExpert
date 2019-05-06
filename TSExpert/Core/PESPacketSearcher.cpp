#include "StdAfx.h"
#include "PESPacketSearcher.h"
#include "PESPacketHeaderReader.h"
#include "TSTableId.h"

CPESPacketSearcher::CPESPacketSearcher(UINT16 uwPid, string sName, CTSParser *pTSParser):CPESPacketObserver(uwPid, sName, pTSParser)
{

}

CPESPacketSearcher::~CPESPacketSearcher(void)
{
}


EResult CPESPacketSearcher::ProcessNewPESPacket(CTSPacketStore * pTSPacketStore)
{
	EResult eResult = FAILURE;

	eResult = StoreNewData(pTSPacketStore);

	/*Increase saved count, so that the search will quit once it reaches the limit.*/
	m_pTSParser->IncementSavedCount(1);

	//Send a message to the UI to show the message.
	TMsgNewSearchedPESPacket *pMsg = new TMsgNewSearchedPESPacket;
	pMsg->pPESPacketObserver = this;
	pMsg->pTSPacketStore = pTSPacketStore;
	if(SUCCESS != m_pTSParser->SendMsgToView(MESSAGE_NEW_SEARCHED_PES_PACKET, (pMsg) ))
	{
		delete pMsg;
	}

	return eResult;
};

EResult CPESPacketSearcher::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiPacketStartCodePrefix = CPESPacketHeaderReader::GetPacketStartCodePrefix(pucData);
	UINT32 uiStreamId = CPESPacketHeaderReader::GetStreamId(pucData);
	UINT32 uiPESPacketLength = CPESPacketHeaderReader::GetPESPacketLength(pucData);

	strDescription.Format(L"PacketStartCodePrefix 0x%08X, StreamId 0x%02X, PESPacketLength 0x%04X", 
		uiPacketStartCodePrefix, uiStreamId, uiPESPacketLength);
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};

EResult CPESPacketSearcher::DisplayPESPacketData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent)
{
	CPESPacketObserver::DisplayPESPacketData(pTSPacketStore,pTreeList, pTreeNodeInput, pTreeNodeParent);
	return CPESPacketParser::DisplayPESPacketData(pTSPacketStore,pTreeList, pTreeNodeInput, pTreeNodeParent);
};

EResult CPESPacketSearcher::StoreNewData(CTSPacketStore * pTSPacketStoreIn)
{
	return CPESPacketObserver::StoreNewData(pTSPacketStoreIn);
};

