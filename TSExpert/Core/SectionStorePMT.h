#pragma once
#include "TSPublic.h"
#include "SectionObserver.h"

class CSectionStorePMT: public CSectionObserver
{
public:
	explicit CSectionStorePMT(UINT16 uwPid, UINT16 uwServiceId, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewSection(CTSPacketStore * pTSPacketStore);
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent);

public:
	virtual ~CSectionStorePMT(void);
private:
	 UINT16 m_uwServiceId;
};
