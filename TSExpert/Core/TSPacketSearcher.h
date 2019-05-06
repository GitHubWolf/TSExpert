#pragma once
#include "TSPacketObserver.h"
#include "TreeList.h"
#include <set>

using namespace std;
class CTSParser;

class CTSPacketSearcher :
	public CTSPacketObserver
{
	typedef set<CTSPacketStore *> SetTSPacketStore;
	typedef SetTSPacketStore::iterator IteratorTSPacketStore;
public:
	CTSPacketSearcher(CTSParser *pTSParser);
	virtual EResult ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber);
	virtual EResult DisplayTSPacketData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent);
	virtual EResult GetTSPacketDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	
public:
	virtual ~CTSPacketSearcher(void);
protected:
	SetTSPacketStore m_storeTSPacketStore;
private:
	EResult DisplayAdaptationFieldExtension(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, const UCHAR8 *pucData, UINT32 uiOffset);
	EResult DisplayAdaptationField(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, const UCHAR8 *pucData, UINT32 uiOffset);

};
