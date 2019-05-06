#pragma once
#include "TSPublic.h"

class CTSParser;
class CTreeList;
class CTreeNode;
class CTSPacketObserver
{
public:
	CTSPacketObserver(CTSParser *pTSParser);
public:
	virtual ~CTSPacketObserver(void);
	virtual EResult ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber) = 0;
	virtual EResult UpdateResult(void);
	virtual EResult DisplayTSPacketData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent);
	virtual EResult GetTSPacketDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	EResult SendMsgToView(EMessageType eMsg,  void *pvParam);
	EResult PostMsgToView(EMessageType eMsg,  void *pvParam);
protected:
	CTSParser *m_pTSParser;
};
