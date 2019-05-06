#pragma once
#include "TSPublic.h"
#include "SectionObserver.h"

class CSectionStoreNIT: public CSectionObserver
{
public:
	explicit CSectionStoreNIT(UINT16 uwPid, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewSection(CTSPacketStore * pTSPacketStore);
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent);
public:
	virtual ~CSectionStoreNIT(void);
};
