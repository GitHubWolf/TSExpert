#pragma once
#include "TSPublic.h"
#include "TSPacketObserver.h"

#include <map>
using namespace std;

class CTSPacketProducer
{
	typedef pair<UINT16, CTSPacketObserver *>  PidObserverPair;
	typedef multimap<UINT16, CTSPacketObserver *> MultimapPidObserver;
	typedef MultimapPidObserver::iterator    IteratorPidObserver;
public:
	CTSPacketProducer(void);
public:
	EResult AttachObserver(UINT16 uwPid, CTSPacketObserver *pTSPacketObserver);
	EResult DetachtObserver(UINT16 uwPid, CTSPacketObserver *pTSPacketObserver);
	EResult RemoveAllObserver(void);
	EResult SetInfo(EPacketLength ePacketLength, FILE * vFile, UINT32 uiDataLength);
	EResult GetNextPacket(UINT32 uiCurrentPacketNumber);
private:
	EResult NotifyAllObservers(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber);
public:
	~CTSPacketProducer(void);
private:
	MultimapPidObserver m_storeObserver;

	//Which packet type to be used.
	EPacketLength m_ePacketLength;

	//File to read.
	FILE * mFile;

	//Length of data to be parsed.
	UINT32 m_uiDataLength;

	/*Buffer to save each packet.*/
	UCHAR8 mPacketBuffer[300];
};
