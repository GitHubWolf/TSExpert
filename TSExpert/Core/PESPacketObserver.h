#pragma once
#include <set>
#include <string>
#include "TSPublic.h"
#include "TSPacketStore.h"
#include "TSParser.h"
#include "TreeList.h"
#include "CRC32.h"

using namespace std;

class CPESPacketObserver
{
public:
	typedef set<CTSPacketStore *> SetTSPacketStore;
	typedef SetTSPacketStore::iterator IteratorTSPacketStore;
public:
	CPESPacketObserver(UINT16 uwPid, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewPESPacket(CTSPacketStore * pTSPacketStore)=0;
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplayPESPacketData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent);
	virtual EResult UpdateResult(void);
protected:
	EResult StoreNewData(CTSPacketStore * pTSPacketStore);

public:
	virtual ~CPESPacketObserver(void);
private:
	CPESPacketObserver(void);
protected:
	SetTSPacketStore m_storeTSPacketStore;
	UINT32 m_uiCount;
	UINT16 m_uwPid;
	CTSParser *m_pTSParser;
	string m_sName;
	CTreeList *m_pTreeList;
	CTreeNode * m_pTreeNodeRootNode;
};
