#include "StdAfx.h"
#include "TSPidCounter.h"
#include "TSHeaderReader.h"
#include "Descriptor.h"
#include "TSParser.h"

CTSPidCounter::CTSPidCounter(CTSParser *pTSParser):CTSPacketObserver(pTSParser)
{
	m_uiTotalNumber = 0;
}

CTSPidCounter::~CTSPidCounter(void)
{

}

EResult CTSPidCounter::ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber)
{
	//m_storePidCounter.insert(PidCounterPair(11, 11));
	UINT16 uwPid = CTSHeaderReader::GetPid(pucData);

	//Increment the counter.
	m_storePidCounter[uwPid]++;

	//Increment total number.
	m_uiTotalNumber++;

	return SUCCESS;
}

MapPidCounter const *CTSPidCounter::GetResult(void)
{
	return &m_storePidCounter;
}
UINT32 CTSPidCounter::GetTotalNumber(void)
{
	return m_uiTotalNumber;
}

EResult CTSPidCounter::UpdateResult(void)
{
	//Send a message to the UI to show the message.
	TMsgCounterResult *pMsg = new TMsgCounterResult;
	pMsg->pMapPidCounter = &m_storePidCounter;
	pMsg->pTSPidCounter = this;
	if(SUCCESS != PostMsgToView(MESSAGE_PID_COUNTER_RESULT, (pMsg) ))
	{
		delete pMsg;
	}

	return SUCCESS;
}
EResult CTSPidCounter::DisplayResult(CTreeList *pTreeList, CTreeNode * pTreeNodeInput)
{
	CTreeNode * pTreeNode = NULL;

	pTreeNodeInput->m_strText.Format(L"%s: %d Packets with %d PIDs", 
		pTreeList->GetNodeNameFromNodeType(NODE_PID_LIST),
		m_uiTotalNumber,
		m_storePidCounter.size()
		);
	pTreeList->UpdateText(pTreeNodeInput);

	IteratorPidCounter iteratorPidCounter;
	for(iteratorPidCounter = m_storePidCounter.begin(); m_storePidCounter.end() != iteratorPidCounter; iteratorPidCounter++)
	{
		EPidType ePidType = m_pTSParser->GetPidType(iteratorPidCounter->first);
		/*
		**Individual PID with individual number.
		**Value for PID node is its PID.
		*/
		pTreeNode  = new CTreeNode(NULL, L"", 0, 0, iteratorPidCounter->first, NODE_PID );
		pTreeNode->m_strText.Format(L"Pid: 0x%4X(%4d), Packets: %6d(%.2f%%), Type: %s", 
			iteratorPidCounter->first, 
			iteratorPidCounter->first,
			iteratorPidCounter->second,
			iteratorPidCounter->second*100.00/m_uiTotalNumber,
			CDescriptor::GetPidTypeName( ePidType)
			);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	}

	return SUCCESS;
}