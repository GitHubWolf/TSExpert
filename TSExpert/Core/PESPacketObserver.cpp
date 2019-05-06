#include "StdAfx.h"
#include "PESPacketObserver.h"
#include "PESPacketHeaderReader.h"
#include "TSTableId.h"

CPESPacketObserver::CPESPacketObserver(UINT16 uwPid, string sName, CTSParser *pTSParser):m_sName(sName)
{
	m_uiCount = 0;

	m_pTSParser = pTSParser;

	m_uwPid = uwPid;

	m_pTreeList = NULL;
	m_pTreeNodeRootNode = NULL;
}

CPESPacketObserver::CPESPacketObserver(void)
{

};

CPESPacketObserver::~CPESPacketObserver(void)
{
	TRACE("TableName %4s, m_uwPid 0x%04X, m_uiCount %4d\r\n", m_sName.c_str() ,m_uwPid, m_uiCount);
	IteratorTSPacketStore iteratorTSPacketStore;
	CTSPacketStore * pTSPacketStore = NULL;
	for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
	{
		pTSPacketStore = *iteratorTSPacketStore;
		//pTSPacketStore->DumpStoredData();
		delete pTSPacketStore;
	}
}

#if 0

EResult CPESPacketObserver::ProcessNewPESPacket(CTSPacketStore * pTSPacketStore)
{
	return FAILURE;
};

#endif

EResult CPESPacketObserver::StoreNewData(CTSPacketStore * pTSPacketStoreIn)
{
	m_uiCount++;

	m_storeTSPacketStore.insert(pTSPacketStoreIn);
	return SUCCESS;
};

EResult CPESPacketObserver::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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

EResult CPESPacketObserver::DisplayPESPacketData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent)
{
	pTSPacketStore->SetRootNode(pTreeNodeInput,pTreeList);
	m_pTreeList = pTreeList;
	m_pTreeNodeRootNode = pTreeNodeParent;
	return SUCCESS;
};

EResult CPESPacketObserver::UpdateResult(void)
{
	IteratorTSPacketStore iteratorTSPacketStore;
	CTSPacketStore * pTSPacketStore = NULL;
	for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
	{
		pTSPacketStore = *iteratorTSPacketStore;
		pTSPacketStore->UpdateResult();		
	}
	return SUCCESS;
};
