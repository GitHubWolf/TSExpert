#pragma once
#include "TSPublic.h"
#include "SectionObserver.h"
#include "SectionStorePMT.h"

class CSectionStorePAT: public CSectionObserver
{
	typedef pair<UINT16, UINT16>  ServiceIdPidPair;
	typedef set<ServiceIdPidPair>  SetServiceIdPid;
	typedef SetServiceIdPid::iterator  IteratorServiceIdPid;

public:
	explicit CSectionStorePAT(UINT16 uwPid, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewSection(CTSPacketStore * pTSPacketStore);
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplaySectionData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent);
public:
	virtual ~CSectionStorePAT(void);
private:
	EResult ParseForPMTPid(CTSPacketStore * pTSPacketStore);

	SetServiceIdPid m_storeServiceIdPid;
};
