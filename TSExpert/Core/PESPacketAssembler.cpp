#include "StdAfx.h"
#include "PESPacketAssembler.h"
#include "TSHeaderReader.h"
#include "PESPacketHeaderReader.h"

CPESPacketAssembler::CPESPacketAssembler(CTSParser *pTSParser):CTSPacketObserver(pTSParser)
{
	
}

CPESPacketAssembler::~CPESPacketAssembler(void)
{
	//Remove all stored record.
	IteratorPidStore iteratorPidStore;
	for( iteratorPidStore = m_storePacket.begin(); m_storePacket.end() != iteratorPidStore; iteratorPidStore++)
	{
		delete iteratorPidStore->second;
	}

	//Remove all stored observer.
	IteratorPidPESPacketObserver iteratorPidPESPacketObserver;
	for( iteratorPidPESPacketObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidPESPacketObserver; iteratorPidPESPacketObserver++)
	{
		delete iteratorPidPESPacketObserver->second;
	}

}

EResult CPESPacketAssembler::ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber)
{
	UCHAR8 ucPayloadOffset;
	UCHAR8 ucPayloadLength;
	UCHAR8 ucPointerField = 0;
	EResult eResult = CTSHeaderReader::GetPayloadOffsetAndLength(pucData, &ucPayloadOffset, &ucPayloadLength, DATA_TYPE_PESPACKET, &ucPointerField);

	//If no payload, return right now.
	if(FAILURE == eResult )
	{
		return FAILURE;
	}

	UINT16 uwPid = CTSHeaderReader::GetPid(pucData);
	UCHAR8 ucUnitStartIndicator = CTSHeaderReader::GetUnitStartIndicator(pucData);
	UCHAR8 ucScramblingFlag = CTSHeaderReader::GetScramblingControl(pucData);

	//Get the start position of payload.
	UCHAR8 const *pucPayload = pucData + ucPayloadOffset;


	//If it is a start packet of a section or PES packet.
	if( 0x1 == ucUnitStartIndicator )
	{
		/*
		**If the value of uiPESPacketLength is VALUE_ZERO, when it is passed to CTSPacketStore,
		**CTSPacketStore will add the new data in append mode.
		*/
		UINT32 uiPESPacketLength;
		if(( 0x00 != ucScramblingFlag ) || (  MODE_APPEND_LENGTH == m_pTSParser->GetWorkingMode()))
		{
			/*If the data is scrambled in TS level, or the parser currently is working in MODE_APPEND_LENGTH,
			**we will use a default size to hold PES packet.
			*/
			uiPESPacketLength = VALUE_ZERO;
		}
		else
		{
			//Get the PES packet length.
			uiPESPacketLength = CPESPacketHeaderReader::GetPESPacketLength(pucPayload);
			/*
			**For PES packet, 16Bits length is NOT enough. PES_packet_length will sometimes be ZERO,
			**in such case, we will add new data in append mode.
			*/
			if( VALUE_ZERO != uiPESPacketLength)
			{
				//Add 6 bytes PES packet header length.
				uiPESPacketLength += MIN_PES_PACKET_HEADER_LENGTH;				
			}
		}

		//Find out whether there are other packets saved.
		IteratorPidStore iteratorPidStore;
		for( iteratorPidStore = m_storePacket.begin(); m_storePacket.end() != iteratorPidStore; iteratorPidStore++)
		{
			//There have been some packets saved.
			if( iteratorPidStore->first == uwPid )
			{
				//If there are packets saved, notify the observer to receive the PES packet .
				Notify(uwPid, iteratorPidStore->second);

				//Remove current record, create a new one.
				m_storePacket.erase(iteratorPidStore);
				CTSPacketStore *pTSPacketStore = new CTSPacketStore(uwPid, uiPESPacketLength, m_pTSParser);

				//Get the insert result.
				pair<IteratorPidStore, BOOL > resultPair;
				resultPair = m_storePacket.insert(PidStorePair( uwPid, pTSPacketStore));

				if( TRUE == resultPair.second )
				{
					//Save data.
					eResult = pTSPacketStore->AddData(pucPayload, ucPayloadLength, uiCurrentPacketNumber);

					//If the return result is SUCCESS, it means a new section or pes paket has been merged.
					if( SUCCESS  == eResult)
					{
						Notify(uwPid, pTSPacketStore);
						m_storePacket.erase(resultPair.first);
						return FAILURE;
					}

					//Return.
					return SUCCESS;
				}
				else
				{
					//If FALSE, free the memory.
					delete pTSPacketStore;
					return FAILURE;
				}
			
			}
		}

		//No packets saved, create a new record.
		if( m_storePacket.end() == iteratorPidStore )
		{
			//First packet, create a new record.
			CTSPacketStore *pTSPacketStore = new CTSPacketStore(uwPid, uiPESPacketLength, m_pTSParser);

			//Get the insert result.
			pair<IteratorPidStore, BOOL > resultPair;
			resultPair = m_storePacket.insert(PidStorePair( uwPid, pTSPacketStore));

			if( TRUE == resultPair.second )
			{
				//Save data.
				eResult = pTSPacketStore->AddData(pucPayload, ucPayloadLength, uiCurrentPacketNumber);

				//If the return result is SUCCESS, it means a new section or pes paket has been merged.
				if( SUCCESS  == eResult)
				{
					Notify(uwPid, pTSPacketStore);
					m_storePacket.erase(resultPair.first);
					return FAILURE;
				}

				//Return.
				return SUCCESS;
			}
			else
			{
				//If FALSE, free the memory.
				delete pTSPacketStore;
				return FAILURE;
			}

		}
		
	}
	else
	{
		//Find out whether there are other packets saved.
		IteratorPidStore iteratorPidStore;
		for( iteratorPidStore = m_storePacket.begin(); m_storePacket.end() != iteratorPidStore; iteratorPidStore++)
		{
			//There have been some packets saved.
			if( iteratorPidStore->first == uwPid )
			{
				CTSPacketStore *pTSPacketStore = iteratorPidStore->second;

				//Merge the new packet into the saved buffer.
				eResult = pTSPacketStore->AddData(pucPayload, ucPayloadLength, uiCurrentPacketNumber);
				
				//If the return result is SUCCESS, it means a new section or pes paket has been merged.
				if( SUCCESS  == eResult)
				{
					Notify(uwPid, pTSPacketStore);
					m_storePacket.erase(iteratorPidStore);
					return FAILURE;
				}

				//Return.
				return SUCCESS;
			}
		}

		//No packets saved, skip it.
		if( m_storePacket.end() == iteratorPidStore )
		{
			//return.
			return FAILURE;
		}
		
	}
	return FAILURE;
};



EResult CPESPacketAssembler::Notify(UINT16 uwPid, CTSPacketStore * pTSPacketStore)
{

	IteratorPidPESPacketObserver iteratorPESPacketObserver;

	for(iteratorPESPacketObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPESPacketObserver; iteratorPESPacketObserver++)
	{
		if( uwPid == iteratorPESPacketObserver->first )
		{
			CPESPacketObserver * pObserver = iteratorPESPacketObserver->second;
			EResult eResult = pObserver->ProcessNewPESPacket(pTSPacketStore);

			if( SUCCESS ==  eResult)
			{
				return SUCCESS;
			}
			
			//Multimap used, one PID may be mapped to more CPESPacketObserver.
			//return SUCCESS;
		}
	}

	//No observer receives current PES packet, free it.
	if( m_storeObserver.end() == iteratorPESPacketObserver )
	{
		delete pTSPacketStore;
		return FAILURE;
	}

	return FAILURE;
};


EResult CPESPacketAssembler::AttachObserver(UINT16 uwPid, CPESPacketObserver *pPESPacketObserver)
{
	if( NULL == pPESPacketObserver)
	{
		return FAILURE;
	}

	if(m_storeObserver.insert(PidPESPacketObserverPair(uwPid, pPESPacketObserver))->second)
	{
		TRACE("[%s, %d]m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
	return SUCCESS;
};
EResult CPESPacketAssembler::DetachtObserver(UINT16 uwPid, CPESPacketObserver *pPESPacketObserver)
{
	if( NULL == pPESPacketObserver)
	{
		return FAILURE;
	}
	EResult eResult = FAILURE;

	IteratorPidPESPacketObserver iteratorPidPESPacketObserver;
	for( iteratorPidPESPacketObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidPESPacketObserver; )
	{
		if(( iteratorPidPESPacketObserver->first == uwPid ) && ( iteratorPidPESPacketObserver->second == pPESPacketObserver ))
		{
			m_storeObserver.erase(iteratorPidPESPacketObserver++);
			TRACE("[%s, %d]m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
		}
		else
		{
			iteratorPidPESPacketObserver++;
		}
	}
	
	return SUCCESS;
};


EResult CPESPacketAssembler::RemoveAllObserver(void)
{
	m_storeObserver.clear();
	TRACE("[%s, %d]m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
	return SUCCESS;
};

EResult CPESPacketAssembler::UpdateResult(void)
{
	IteratorPidPESPacketObserver iteratorPidPESPacketObserver;
	for( iteratorPidPESPacketObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidPESPacketObserver; iteratorPidPESPacketObserver++)
	{
		CPESPacketObserver * pPESPacketObserver = iteratorPidPESPacketObserver->second;
		pPESPacketObserver->UpdateResult();
	}
	
	return SUCCESS;
}
