#include "StdAfx.h"
#include "SectionAssembler.h"
#include "TSHeaderReader.h"
#include "SectionHeaderReader.h"

CSectionAssembler::CSectionAssembler(CTSParser *pTSParser):CTSPacketObserver(pTSParser)
{
	
}

CSectionAssembler::~CSectionAssembler(void)
{
	//Remove all stored record.
	IteratorPidStore iteratorPidStore;
	for( iteratorPidStore = m_storePacket.begin(); m_storePacket.end() != iteratorPidStore; iteratorPidStore++)
	{
		delete iteratorPidStore->second;
	}

	//Remove all stored observer.
	IteratorPidSectionObserver iteratorPidSectionObserver;
	for( iteratorPidSectionObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidSectionObserver; iteratorPidSectionObserver++)
	{
		delete iteratorPidSectionObserver->second;
	}

}

EResult CSectionAssembler::ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber)
{
	UCHAR8 ucPayloadOffset;
	UCHAR8 ucPayloadLength;
	UCHAR8 ucPointerField = 0;
	EResult eResult = CTSHeaderReader::GetPayloadOffsetAndLength(pucData, &ucPayloadOffset, &ucPayloadLength, DATA_TYPE_SECTION, &ucPointerField);

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


	//If it is a start packet of a SI/PSI section.
	if( 0x1 == ucUnitStartIndicator )
	{
		/*
		**If the value of uiSectionLength is VALUE_ZERO, when it is passed to CTSPacketStore,
		**CTSPacketStore will add the new data in append mode.
		*/	
		UINT32 uiSectionLength;

		//if(( 0x00 != ucScramblingFlag ) || (  MODE_APPEND_LENGTH == m_pTSParser->GetWorkingMode()))
		if( 0x00 != ucScramblingFlag )/*Updated at 2011.06.30. Section assembler should not use APPEND mode.*/
		{
			/*If the data is scrambled in TS level, or the parser currently is working in MODE_APPEND_LENGTH,
			**we will use a default size to hold PES packet.
			*/
			uiSectionLength = VALUE_ZERO;
		}
		else
		{
			//Get the section length.
			uiSectionLength = CSectionHeaderReader::GetSectionLength(pucPayload);

			/*
			** Sometimes a TS packet may contain multiple sections.
			** In such case, the section length NOT enough to hold all the sections.
			** And we also want to get notified with a single section in a single TS packet.
			*/
			//Add 3 bytes sectioin header length.
			uiSectionLength += 3;
		}

		//Find out whether there are other packets saved.
		IteratorPidStore iteratorPidStore;
		for( iteratorPidStore = m_storePacket.begin(); m_storePacket.end() != iteratorPidStore; iteratorPidStore++)
		{
			//There have been some packets saved.
			if( iteratorPidStore->first == uwPid )
			{
				//If there are packets saved, notify the observer to receive the section .
				if( 0 != ucPointerField)
				{
					/*Current TS packet contains some part of previous section.*/

					CTSPacketStore *pTSPacketStoreOld = iteratorPidStore->second;
					
					//Merge left part into the old one.
					eResult = pTSPacketStoreOld->AddData(pucPayload - ucPointerField, ucPointerField, uiCurrentPacketNumber);

					Notify(uwPid, iteratorPidStore->second);
				}
				else
				{
					Notify(uwPid, iteratorPidStore->second);
				}
				

				//Remove current record, create a new one.
				m_storePacket.erase(iteratorPidStore);
				CTSPacketStore *pTSPacketStore = new CTSPacketStore(uwPid, uiSectionLength, m_pTSParser);

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
			CTSPacketStore *pTSPacketStore = new CTSPacketStore(uwPid, uiSectionLength, m_pTSParser);

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



EResult CSectionAssembler::Notify(UINT16 uwPid, CTSPacketStore * pTSPacketStore)
{

	IteratorPidSectionObserver iteratorSectionObserver;

	for(iteratorSectionObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorSectionObserver; iteratorSectionObserver++)
	{
		if( uwPid == iteratorSectionObserver->first )
		{
			CSectionObserver * pObserver = iteratorSectionObserver->second;
			EResult eResult = pObserver->ProcessNewSection(pTSPacketStore);

			if( SUCCESS ==  eResult)
			{
				return SUCCESS;
			}
			
			//Multimap used, one PID may be mapped to more CSectionObserver.
			//return SUCCESS;
		}
	}

	//No observer receives current section, free it.
	if( m_storeObserver.end() == iteratorSectionObserver )
	{
		delete pTSPacketStore;
		return FAILURE;
	}

	return FAILURE;
};


EResult CSectionAssembler::AttachObserver(UINT16 uwPid, CSectionObserver *pSectionObserver)
{
	if( NULL == pSectionObserver)
	{
		return FAILURE;
	}

	if(m_storeObserver.insert(PidSectionObserverPair(uwPid, pSectionObserver))->second)
	{
		TRACE("[%s, %d] m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
	return SUCCESS;
};
EResult CSectionAssembler::DetachtObserver(UINT16 uwPid, CSectionObserver *pSectionObserver)
{
	if( NULL == pSectionObserver)
	{
		return FAILURE;
	}
	EResult eResult = FAILURE;

	IteratorPidSectionObserver iteratorPidSectionObserver;
	for( iteratorPidSectionObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidSectionObserver; )
	{
		if(( iteratorPidSectionObserver->first == uwPid ) && ( iteratorPidSectionObserver->second == pSectionObserver ))
		{
			m_storeObserver.erase(iteratorPidSectionObserver++);
			TRACE("[%s,%d] m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
		}
		else
		{
			iteratorPidSectionObserver++;
		}
	}
	
	return SUCCESS;
};


EResult CSectionAssembler::RemoveAllObserver(void)
{
	m_storeObserver.clear();
	TRACE("[%s,%d] m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
	return SUCCESS;
};

EResult CSectionAssembler::UpdateResult(void)
{
	IteratorPidSectionObserver iteratorPidSectionObserver;
	for( iteratorPidSectionObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidSectionObserver; iteratorPidSectionObserver++)
	{
		CSectionObserver * pSectionObserver = iteratorPidSectionObserver->second;
		pSectionObserver->UpdateResult();
	}
	
	return SUCCESS;
}