#pragma once
#include "TSPacketObserver.h"
#include "SectionAssembler.h"
#include "TSPacketStore.h"
#include "SectionObserver.h"


#include <map>
using namespace std;
class CSectionObserver;

class CSectionAssembler:
	public CTSPacketObserver
{
	typedef pair<UINT16, CTSPacketStore *>  PidStorePair;
	typedef map<UINT16, CTSPacketStore *> MapPidStore;
	typedef MapPidStore::iterator    IteratorPidStore;

	typedef pair<UINT16, CSectionObserver *>  PidSectionObserverPair;
	typedef multimap<UINT16, CSectionObserver *> MultimapPidSectionObserver;
	typedef MultimapPidSectionObserver::iterator    IteratorPidSectionObserver;

public:
	CSectionAssembler(CTSParser *pTSParser);
	virtual EResult ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber);
	virtual EResult UpdateResult(void);
	
	EResult AttachObserver(UINT16 uwPid, CSectionObserver *pSectionObserver);
	EResult DetachtObserver(UINT16 uwPid, CSectionObserver *pSectionObserver);
	EResult RemoveAllObserver(void);
private:
	EResult Notify(UINT16 uwPid, CTSPacketStore * pTSPacketStore);
public:
	virtual ~CSectionAssembler(void);
private:
	//To store packets temporarily.
	MapPidStore m_storePacket;

	//To store handler that are requestint sections.
	MultimapPidSectionObserver m_storeObserver;
};
