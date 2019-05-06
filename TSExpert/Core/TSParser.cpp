#include "StdAfx.h"
#include "TSParser.h"
#include "TSExpertDoc.h"
#include "TSPidCounter.h"
#include "TSPid.h"
#include "TSTableId.h"
#include "SectionAssembler.h"
#include "PESPacketAssembler.h"
#include "SectionStorePAT.h"
#include "SectionStoreNIT.h"
#include "SectionStoreCAT.h"
#include "SectionStoreTSDT.h"
#include "SectionStoreSDT.h"
#include "SectionStoreBAT.h"
#include "SectionStoreEIT.h"
#include "SectionStoreTDT.h"
#include "SectionStoreRST.h"
#include "SectionStoreTOT.h"
#include "SectionStoreSIT.h"
#include "SectionStoreDIT.h"

UINT TSParserWorkerFunction( LPVOID pParam )
{
	CTSExpertDoc *pTSExpertDoc = (CTSExpertDoc *)pParam;

	EPacketLength ePacketLength = pTSExpertDoc->GetPacketLength();
	FILE * vFile  = pTSExpertDoc->GetFile();
	UINT32 uiDataLength = pTSExpertDoc->GetDataLength();

	//Create a CTSParser as worker to analyse the input file.
	pTSExpertDoc->m_pTSParser = new CTSParser;

	CTSParser *pTSParser = pTSExpertDoc->m_pTSParser;

	pTSParser->m_pTSExpertDoc = pTSExpertDoc;

	/*Setup parser task.*/

	/*
	**Create a CTSPidCounter to get notified when CTSPacketProducer find a packet.
	**CTSParser will be responsible for freeing the memory allocated by new.
	*/
	CTSPidCounter *pTSPidCounter = new CTSPidCounter(pTSParser);

	//Add a packet observer.PID_INVALID is a special value.Others shall no use this value.
	pTSParser->AttachPacketObserver(PID_INVALID, pTSPidCounter);

	CSectionStorePAT *pSectionStorePAT = new CSectionStorePAT(PID_PAT, TABLE_NAME_PAT, pTSParser);
	pTSParser->AttachSectionObserver(PID_PAT, pSectionStorePAT);

	CSectionStoreCAT *pSectionStoreCAT = new CSectionStoreCAT(PID_CAT, TABLE_NAME_CAT, pTSParser);
	pTSParser->AttachSectionObserver(PID_CAT, pSectionStoreCAT);

	CSectionStoreNIT *pSectionStoreNIT = new CSectionStoreNIT(PID_NIT, TABLE_NAME_NIT, pTSParser);
	pTSParser->AttachSectionObserver(PID_NIT, pSectionStoreNIT);

	CSectionStoreTSDT *pSectionStoreTSDT = new CSectionStoreTSDT(PID_TSDT, TABLE_NAME_TSDT, pTSParser);
	pTSParser->AttachSectionObserver(PID_TSDT, pSectionStoreTSDT);

	CSectionStoreSDT *pSectionStoreSDT = new CSectionStoreSDT(PID_SDT, TABLE_NAME_SDT, pTSParser);
	pTSParser->AttachSectionObserver(PID_BAT_SDT, pSectionStoreSDT);

	CSectionStoreBAT *pSectionStoreBAT = new CSectionStoreBAT(PID_BAT, TABLE_NAME_BAT, pTSParser);
	pTSParser->AttachSectionObserver(PID_BAT_SDT, pSectionStoreBAT);

	CSectionStoreEIT *pSectionStoreEIT = new CSectionStoreEIT(PID_EIT, TABLE_NAME_EIT, pTSParser);
	pTSParser->AttachSectionObserver(PID_EIT, pSectionStoreEIT);

	CSectionStoreTDT *pSectionStoreTDT = new CSectionStoreTDT(PID_TDT, TABLE_NAME_TDT, pTSParser);
	pTSParser->AttachSectionObserver(PID_TDT, pSectionStoreTDT);

	CSectionStoreRST *pSectionStoreRST = new CSectionStoreRST(PID_RST, TABLE_NAME_RST, pTSParser);
	pTSParser->AttachSectionObserver(PID_RST, pSectionStoreRST);


	CSectionStoreTOT *pSectionStoreTOT = new CSectionStoreTOT(PID_TOT, TABLE_NAME_TOT, pTSParser);
	pTSParser->AttachSectionObserver(PID_TOT, pSectionStoreTOT);

	CSectionStoreDIT *pSectionStoreDIT = new CSectionStoreDIT(PID_DIT, TABLE_NAME_DIT, pTSParser);
	pTSParser->AttachSectionObserver(PID_DIT, pSectionStoreDIT);

	CSectionStoreSIT *pSectionStoreSIT = new CSectionStoreSIT(PID_SIT, TABLE_NAME_SIT, pTSParser);
	pTSParser->AttachSectionObserver(PID_SIT, pSectionStoreSIT);

	pTSParser->StartParse(ePacketLength, vFile, uiDataLength);

	return SUCCESS;
}



CTSParser::CTSParser(void)
{
	m_pSectionAssembler = new CSectionAssembler(this);

	m_pPESPacketAssembler = new CPESPacketAssembler(this);

	//Keep the handler.
	m_storeTSPacketObserver.insert(m_pSectionAssembler);
	m_storeTSPacketObserver.insert(m_pPESPacketAssembler);

	m_pTSExpertDoc = NULL;

	m_uiSearchCount = 0;
	m_uiSavedCount = 0;

	m_eWorkingMode = MODE_LIMITED_LENGTH;

	m_bForceToQuit = FALSE;
	m_eRunningStatus = RUNNING_STATUS_READY;
}

CTSParser::~CTSParser(void)
{
	CTSPacketObserver *pTSPacketObserver;
	IteratorTSPacketObserver iteratorTSPacketObserver;
	for( iteratorTSPacketObserver = m_storeTSPacketObserver.begin(); m_storeTSPacketObserver.end() != iteratorTSPacketObserver; iteratorTSPacketObserver++)
	{
		pTSPacketObserver = *iteratorTSPacketObserver;
		delete pTSPacketObserver;
	}
}

EResult CTSParser::StartParse(EPacketLength ePacketLength, FILE * vFile, UINT32 uiDataLength)
{
	UINT32 uiTotalNumber = uiDataLength/ePacketLength;
	UINT32 uiPercent = 0;
	UINT32 uiLastPercent = 0;
	
	SetRunningStatus(RUNNING_STATUS_RUNNING);
	//Set default service type.
	SetDefaultPidType();

	//Set the data information so that CTSPacketProducer can read the data according to it.
	m_TSPacketProducer.SetInfo(ePacketLength, vFile, uiDataLength );

	UINT32 uiCounter = 0;
	while((SUCCESS ==  m_TSPacketProducer.GetNextPacket(uiCounter)) )
	{
		if( m_bForceToQuit)
		{
			return SUCCESS;
		}

		uiCounter++;
		if(0 == (uiCounter %1000))
		{
			uiPercent = ((uiCounter*100/uiTotalNumber));
			//Don't try to print out same percent.
			if( (uiLastPercent+4) < uiPercent )
			{
				uiLastPercent = uiPercent;

				//Send a message to the UI to show the message.
				TMsgProgress *pMsg = new TMsgProgress;
				pMsg->uiPercent = uiPercent;
				if(SUCCESS != SendMsgToView(MESSAGE_PARSING_PROGRESS, (pMsg) ))
				{
					TRACE("-------uiPercent %d---------SendMsgToView failed.\n", uiPercent);
					delete pMsg;
				}
				else
				{
					TRACE("-------uiPercent %d---------SendMsgToView OK.\n", uiPercent);
				}
			}
		}
	}

	uiPercent = 100;

	//Send a message to the UI to show the message.
	TMsgProgress *pMsg = new TMsgProgress;
	pMsg->uiPercent = uiPercent;
	if(SUCCESS != SendMsgToView(MESSAGE_PARSING_PROGRESS, (pMsg) ))
	{
		delete pMsg;
	}

	/*Send message to UI.Parse is completed.*/
	PostMsgToView(MESSAGE_PARSER_COMPLETED, NULL );

	SetRunningStatus(RUNNING_STATUS_QUIT);
	return SUCCESS;
}


void CTSParser::SetupStandardSectionAssembler(void)
{
	//CSectionAssembler will listen for all SI/PSI packets..
	m_TSPacketProducer.AttachObserver(PID_PAT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_CAT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_TSDT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_NIT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_BAT_SDT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_EIT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_RST, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_TDT_TOT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_DIT, m_pSectionAssembler);
	m_TSPacketProducer.AttachObserver(PID_SIT, m_pSectionAssembler);

}


EResult CTSParser::AttachPacketObserver(UINT16 uwPid, CTSPacketObserver *pTSPacketObserver)
{
	EResult eResult;

	//Add it to the list so that it will be notified.
	eResult = m_TSPacketProducer.AttachObserver(uwPid, pTSPacketObserver);

	if( FAILURE == eResult )
		return FAILURE;

	//Keep the handler.
	m_storeTSPacketObserver.insert(pTSPacketObserver);

	return SUCCESS;
};

EResult CTSParser::AttachSectionObserver(UINT16 uwPid, CSectionObserver *pSectionObserver)
{
	EResult eResult;
	eResult = m_TSPacketProducer.AttachObserver(uwPid, m_pSectionAssembler);

	m_pSectionAssembler->AttachObserver(uwPid, pSectionObserver);

	return SUCCESS;
};

EResult CTSParser::AttachPESPacketObserver(UINT16 uwPid, CPESPacketObserver *pPESPacketObserver)
{
	EResult eResult;
	eResult = m_TSPacketProducer.AttachObserver(uwPid, m_pPESPacketAssembler);

	m_pPESPacketAssembler->AttachObserver(uwPid, pPESPacketObserver);

	return SUCCESS;
};

EResult CTSParser::SetWorkingMode(EWorkingMode eWorkingMode)
{
	m_eWorkingMode = eWorkingMode;
	return SUCCESS;
}

EWorkingMode CTSParser::GetWorkingMode(void)
{
	return m_eWorkingMode;
}

EResult CTSParser::SendMsgToView(EMessageType eMsg, void *pvParam)
{
	/*If we are foreced to quit, do not send message any more.*/
	if( m_bForceToQuit )
		return FAILURE;

	if (TRUE == m_pTSExpertDoc->SendMsgToView(eMsg, pvParam))
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}

	return SUCCESS;
}


EResult CTSParser::PostMsgToView(EMessageType eMsg, void *pvParam)
{
	/*If we are foreced to quit, do not send message any more.*/
	if( m_bForceToQuit )
		return FAILURE;

	if (TRUE == m_pTSExpertDoc->PostMsgToView(eMsg, pvParam))
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}

	return SUCCESS;
}

EResult CTSParser::UpdateResult(void)
{
	CTSPacketObserver *pTSPacketObserver;
	IteratorTSPacketObserver iteratorTSPacketObserver;
	for( iteratorTSPacketObserver = m_storeTSPacketObserver.begin(); m_storeTSPacketObserver.end() != iteratorTSPacketObserver; iteratorTSPacketObserver++)
	{
		pTSPacketObserver = *iteratorTSPacketObserver;
		/*Call UpdateResult to ask the observer to report the result.*/
		pTSPacketObserver->UpdateResult();
	}
	return SUCCESS;
}

EResult CTSParser::SetPidType(UINT32 uwPid, EPidType ePidType)
{
	//Save the type.
	if( PID_TYPE_PCR == ePidType)
	{
		/*
		**Since PCR_PID may be a PID that is used for Video PID or others,
		**We have to handle it specially.
		**Do NOT use PCR_PID type to override PID type.
		*/
		if( 0 == m_storePidType[uwPid] )
		{
			m_storePidType[uwPid] = ePidType;
		}
	}
	else
	{
		m_storePidType[uwPid] = ePidType;
	}

	return SUCCESS;
};

EPidType CTSParser::GetPidType(UINT32 uwPid)
{
	EPidType ePidType = PID_TYPE_RESERVED;

	IteratorPidType iteratorPidType;
	for(iteratorPidType = m_storePidType.begin(); m_storePidType.end() != iteratorPidType; iteratorPidType++)
	{

		if( uwPid == iteratorPidType->first )
		{
			ePidType = iteratorPidType->second;
			break;
		}
	} 	


	return ePidType;
};

EResult  CTSParser::SetDefaultPidType(void)
{
	SetPidType(PID_PAT, PID_TYPE_PAT);
	SetPidType(PID_CAT, PID_TYPE_CAT);
	SetPidType(PID_TSDT, PID_TYPE_TSDT);
	SetPidType(PID_NIT, PID_TYPE_NIT);
	SetPidType(PID_BAT_SDT, PID_TYPE_BAT_SDT);
	SetPidType(PID_EIT, PID_TYPE_EIT);
	SetPidType(PID_RST, PID_TYPE_RST);
	SetPidType(PID_TDT_TOT, PID_TYPE_TDT_TOT);
	SetPidType(PID_NST, PID_TYPE_NST);
	SetPidType(PID_IST, PID_TYPE_IST);
	SetPidType(PID_MT, PID_TYPE_MT);
	SetPidType(PID_DIT, PID_TYPE_DIT);
	SetPidType(PID_SIT, PID_TYPE_SIT);
	SetPidType(PID_NULL, PID_TYPE_NULL);

	return SUCCESS;
}


EResult CTSParser::SetSearchCount(UINT32 uiCount)
{
	m_uiSearchCount = uiCount;

	return SUCCESS;
}
EResult CTSParser::IncementSavedCount(UINT32 uiCount)
{
	m_uiSavedCount += uiCount;

	return SUCCESS;
}



EResult CTSParser::StartSearch(EPacketLength ePacketLength, FILE * vFile, UINT32 uiDataLength, UINT32 uiPid, UINT32 uiSearchCount, ESearchType eSearchType, UINT32 uiId)
{
	UINT32 uiTotalNumber = uiDataLength/ePacketLength;
	UINT32 uiPercent = 0;
	UINT32 uiLastPercent = 0;
	BOOL   bSearchAll = FALSE;

	SetRunningStatus(RUNNING_STATUS_RUNNING);

	if( VALUE_MAX == uiSearchCount )
	{
		bSearchAll = TRUE;
	}

	/*Let the searcher work in APPEND mode.*/
	SetWorkingMode(MODE_APPEND_LENGTH);
	
	m_uiSearchCount = uiSearchCount;

	//Inform UI with search infomation.
	TMsgSearcherInfo *pMsgSearcherInfo = new TMsgSearcherInfo;
	pMsgSearcherInfo->uiPid = uiPid;
	pMsgSearcherInfo->uiSearchCount = uiSearchCount;
	pMsgSearcherInfo->eSearchType = eSearchType;
	pMsgSearcherInfo->uiId = uiId;
	if( SUCCESS != SendMsgToView(MESSAGE_SEARCHER_INFO, (pMsgSearcherInfo) ))
	{
		delete pMsgSearcherInfo;
	}

	//Set default service type.
	SetDefaultPidType();

	//Set the data information so that CTSPacketProducer can read the data according to it.
	m_TSPacketProducer.SetInfo(ePacketLength, vFile, uiDataLength );

	UINT32 uiCounter = 0;
	while((SUCCESS ==  m_TSPacketProducer.GetNextPacket(uiCounter))  )
	{
		if(  m_bForceToQuit)
		{
			return SUCCESS;
		}
		uiCounter++;
		if(0 == (uiCounter %1000))
		{
			uiPercent = ((uiCounter*100/uiTotalNumber));
			//Don't try to print out same percent.
			if( uiLastPercent != uiPercent )
			{
				uiLastPercent = uiPercent;

				//Send a message to the UI to show the message.
				TMsgProgress *pMsg = new TMsgProgress;
				pMsg->uiPercent = uiPercent;
				if(SUCCESS != SendMsgToView(MESSAGE_PARSING_PROGRESS, (pMsg) ))
				{
					delete pMsg;
				}
			}
		}

		/*Check search count.*/
		if( !bSearchAll )
		{
			/*Reach the requested count, quit.*/
			if( m_uiSavedCount >= m_uiSearchCount )
			{
				break;
			}
		}
	}

	uiPercent = 100;

	//Send a message to the UI to show the message.
	TMsgProgress *pMsg = new TMsgProgress;
	pMsg->uiPercent = uiPercent;
	if(SUCCESS != SendMsgToView(MESSAGE_PARSING_PROGRESS, (pMsg) ))
	{
		delete pMsg;
	}

	/*Send message to UI.Parse is completed.*/
	TMsgSearcherCompleted *pMsgSearcherCompleted = new TMsgSearcherCompleted;
	pMsgSearcherCompleted->pTSParser = this;
	if(SUCCESS != PostMsgToView(MESSAGE_SEARCHER_COMPLETED, pMsgSearcherCompleted ))
	{
		delete pMsgSearcherCompleted;
	}

	SetRunningStatus(RUNNING_STATUS_QUIT);

	return SUCCESS;
}

EResult CTSParser::SetForceQuit(BOOL bQuit)
{
	/*
	**In fact, we shall protect the variable here.
	**Skip it in current phase.
	**Here we use volatile to mutex.
	*/
	m_bForceToQuit = bQuit;
	return SUCCESS;
}

EResult CTSParser::SetRunningStatus(ERunningStatus eRunningStatus)
{
	/*
	**In fact, we shall protect the variable here.
	**Skip it in current phase.
	**Here we use volatile to mutex.
	*/
	m_eRunningStatus = eRunningStatus;
	return SUCCESS;
}
ERunningStatus CTSParser::GetRunningStatus(void)
{
	/*
	**In fact, we shall protect the variable here.
	**Skip it in current phase.
	**Here we use volatile to mutex.
	*/
	return m_eRunningStatus;
}
