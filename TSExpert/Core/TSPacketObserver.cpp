#include "StdAfx.h"
#include "TSPacketObserver.h"
#include "TSParser.h"
#include "TSPacketStore.h"
#include "TSHeaderReader.h"

CTSPacketObserver::CTSPacketObserver(CTSParser *pTSParser)
{
	m_pTSParser = pTSParser;
}

CTSPacketObserver::~CTSPacketObserver(void)
{
}

#if 0
EResult CTSPacketObserver::ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber)
{
	return SUCCESS;
};
#endif
EResult CTSPacketObserver::UpdateResult(void)
{
	return SUCCESS;
}

EResult CTSPacketObserver::SendMsgToView(EMessageType eMsg,  void *pvParam)
{
	return m_pTSParser->SendMsgToView(eMsg, pvParam);
}

EResult CTSPacketObserver::PostMsgToView(EMessageType eMsg,  void *pvParam)
{
	return m_pTSParser->PostMsgToView(eMsg, pvParam);
}


EResult CTSPacketObserver::DisplayTSPacketData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
{
	return SUCCESS;
}

EResult CTSPacketObserver::GetTSPacketDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucUnitStartIndicator = CTSHeaderReader::GetUnitStartIndicator(pucData);
	UCHAR8 ucContinuityCounter = CTSHeaderReader::GetContinuityCounter(pucData);

	strDescription.Format(L"PayloadUnitStartIndicator: %u, ContinuityCounter: %2u, %s, %s", 
		ucUnitStartIndicator, ucContinuityCounter, CTSHeaderReader::GetScramblingControlName(pucData), CTSHeaderReader::GetAdaptationControlName(pucData));
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
}
