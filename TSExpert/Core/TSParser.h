#pragma once
#include "TSPublic.h"
#include "TSPacketProducer.h"

#include <set>

using namespace std;
class CTSExpertDoc;
class CTSPacketObserver;
class CSectionObserver;
class CSectionAssembler;
class CPESPacketAssembler;

class CTSParser
{
	typedef set<CTSPacketObserver *> SetTSPacketObserver;
	typedef SetTSPacketObserver::iterator IteratorTSPacketObserver;

	typedef pair<UINT32, EPidType>  PidTypePair;
	typedef map<UINT32, EPidType>   MapPidType;
	typedef MapPidType::iterator    IteratorPidType;
public:
	CTSParser(void);
	EResult StartParse(EPacketLength ePacketLength, FILE * vFile, UINT32 uiDataLength);
	EResult StartSearch(EPacketLength ePacketLength, FILE * vFile, UINT32 uiDataLength, UINT32 uiPid, UINT32 uiSearchCount, ESearchType eSearchType, UINT32 uiId);
	EResult AttachPacketObserver(UINT16 uwPid, CTSPacketObserver *pTSPacketObserver);
	EResult AttachSectionObserver(UINT16 uwPid, CSectionObserver *pSectionObserver);
	EResult AttachPESPacketObserver(UINT16 uwPid, CPESPacketObserver *pPESPacketObserver);
	void SetupStandardSectionAssembler(void);
	EResult SendMsgToView(EMessageType uiMsg,  void *pvParam);
	EResult PostMsgToView(EMessageType uiMsg,  void *pvParam);
	EResult SetPidType(UINT32 uwPid, EPidType ePidType);
	EPidType GetPidType(UINT32 uwPid);
	EResult UpdateResult(void);
	EResult SetSearchCount(UINT32 uiCount);
	EResult IncementSavedCount(UINT32 uiCount = 1);
	EResult SetWorkingMode(EWorkingMode eWorkingMode);
	EWorkingMode GetWorkingMode(void);
	EResult SetForceQuit(BOOL bQuit);
	ERunningStatus GetRunningStatus( void );
public:
	~CTSParser(void);
private:
	SetTSPacketObserver m_storeTSPacketObserver;

private:
	EResult SetDefaultPidType(void);
	EResult SetRunningStatus(ERunningStatus eRunningStatus);
private:
	//Create a CTSPacketProducer to read every TS packet.
	CTSPacketProducer m_TSPacketProducer;

	//Create a CSectionAssembler as an entry for all sections.
	CSectionAssembler *m_pSectionAssembler;

	//Create a CSectionAssembler as an entry for all sections.
	CPESPacketAssembler *m_pPESPacketAssembler;

	/*Save the Pid and its type.*/
	MapPidType m_storePidType;

	/*Save the count that user wishes to search.*/
	UINT32 m_uiSearchCount;

	/*Save the count that has been saved.*/
	UINT32 m_uiSavedCount;

	EWorkingMode m_eWorkingMode;

	/*We use volatile to ensure the sequence access.*/
	volatile BOOL m_bForceToQuit;
	volatile ERunningStatus m_eRunningStatus;

public:
	CTSExpertDoc *m_pTSExpertDoc;
};
