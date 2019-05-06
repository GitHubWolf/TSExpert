#pragma once
#include <set>
#include <string>
#include "TSPublic.h"
#include "TSPacketStore.h"
#include "TSParser.h"
#include "TreeList.h"
#include "CRC32.h"

using namespace std;

class CSectionObserver
{
public:
	typedef set<CTSPacketStore *> SetTSPacketStore;
	typedef SetTSPacketStore::iterator IteratorTSPacketStore;
public:
	CSectionObserver(UINT16 uwPid, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewSection(CTSPacketStore * pTSPacketStore)=0;
	virtual SINT32  CompareStandardSection(CTSPacketStore * pTSPacketStoreInput1, CTSPacketStore * pTSPacketStoreInput2, UINT32 uiCompareLength = MIN_SECTION_HEADER_LENGTH);
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplaySectionData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent);
	virtual EResult UpdateResult(void);
protected:
	EResult StoreNewData(CTSPacketStore * pTSPacketStore);
	EResult CheckStandardSectionLength(CTSPacketStore * pTSPacketStore);

public:
	virtual ~CSectionObserver(void);
private:
	CSectionObserver(void);
protected:
	SetTSPacketStore m_storeTSPacketStore;
	UINT32 m_uiMatchLength;
	UINT32 m_uiCount;
	UINT16 m_uwPid;
	CTSParser *m_pTSParser;
	string m_sName;
	CTreeList *m_pTreeList;
	CTreeNode * m_pTreeNodeRootNode;
};
