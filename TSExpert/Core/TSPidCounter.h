#pragma once
#include "TSPacketObserver.h"
#include "TreeList.h"


using namespace std;
class CTSParser;
class CTSPidCounter :
	public CTSPacketObserver
{
public:
	CTSPidCounter(CTSParser *pTSParser);
	virtual EResult ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber);
	virtual EResult UpdateResult(void);
	EResult DisplayResult(CTreeList *pTreeList, CTreeNode * pTreeNodeInput);
	MapPidCounter const *GetResult(void);
	UINT32 GetTotalNumber(void);

public:
	virtual ~CTSPidCounter(void);

private:
	MapPidCounter m_storePidCounter;

	UINT32 m_uiTotalNumber;

};
