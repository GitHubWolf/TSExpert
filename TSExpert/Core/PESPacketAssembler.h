#pragma once
#include "TSPacketObserver.h"
#include "PESPacketAssembler.h"
#include "TSPacketStore.h"
#include "PESPacketObserver.h"


#include <map>
using namespace std;
class CPESPacketObserver;

class CPESPacketAssembler:
	public CTSPacketObserver
{
	typedef pair<UINT16, CTSPacketStore *>  PidStorePair;
	typedef map<UINT16, CTSPacketStore *> MapPidStore;
	typedef MapPidStore::iterator    IteratorPidStore;

	typedef pair<UINT16, CPESPacketObserver *>  PidPESPacketObserverPair;
	typedef multimap<UINT16, CPESPacketObserver *> MultimapPidPESPacketObserver;
	typedef MultimapPidPESPacketObserver::iterator    IteratorPidPESPacketObserver;

public:
	CPESPacketAssembler(CTSParser *pTSParser);
	virtual EResult ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber);
	virtual EResult UpdateResult(void);
	
	EResult AttachObserver(UINT16 uwPid, CPESPacketObserver *pPESPacketObserver);
	EResult DetachtObserver(UINT16 uwPid, CPESPacketObserver *pPESPacketObserver);
	EResult RemoveAllObserver(void);
private:
	EResult Notify(UINT16 uwPid, CTSPacketStore * pTSPacketStore);
public:
	virtual ~CPESPacketAssembler(void);
private:
	//To store packets temporarily.
	MapPidStore m_storePacket;

	//To store handler that are requestint sections.
	MultimapPidPESPacketObserver m_storeObserver;
};
