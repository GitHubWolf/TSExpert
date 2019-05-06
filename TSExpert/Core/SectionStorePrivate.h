#pragma once
#include "TSPublic.h"
#include "SectionObserver.h"
#include "SectionStorePMT.h"

class CSectionStorePrivate: public CSectionObserver
{
public:
	explicit CSectionStorePrivate(UINT16 uwPid, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewSection(CTSPacketStore * pTSPacketStore);
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplaySectionData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent);
	EResult SetFilter(UCHAR8 const *pucMask, UCHAR8 const *pucMatch,UINT32 uiFilterLength);
	EResult IsMatched(CTSPacketStore * pTSPacketStore);
private:
	EResult StoreNewData(CTSPacketStore * pTSPacketStore);
	EResult GetDescription(CTSPacketStore * pTSPacketStore, const UCHAR8 *pucData, CString& strDescription);
	
public:
	virtual ~CSectionStorePrivate(void);
private:
	UINT32 m_uiFilterLength;
	UCHAR8 m_arrayMask[MAX_FILTER_LENGTH];
	UCHAR8 m_arrayMatch[MAX_FILTER_LENGTH];
};
