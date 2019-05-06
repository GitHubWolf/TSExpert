#pragma once
#include "TSPublic.h"
#include "PESPacketObserver.h"
#include "SectionStorePMT.h"
#include "PESPacketParser.h"

class CPESPacketSearcher: public CPESPacketObserver
{
public:
	explicit CPESPacketSearcher(UINT16 uwPid, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewPESPacket(CTSPacketStore * pTSPacketStore);
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplayPESPacketData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent);
private:
	EResult StoreNewData(CTSPacketStore * pTSPacketStore);
public:
	virtual ~CPESPacketSearcher(void);
};
