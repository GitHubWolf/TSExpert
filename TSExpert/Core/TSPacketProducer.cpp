#include "StdAfx.h"
#include "TSPacketProducer.h"
#include "TSHeaderReader.h"
#include "TSPid.h"
#include "TSHeaderLocator.h"


CTSPacketProducer::CTSPacketProducer(void)
{
	//Which packet type to be used.
	m_ePacketLength = TS_PACKET_LENGTH_UNKNOWN;

	//File to read..
	mFile = NULL;

	//Length of data to be parsed.
	m_uiDataLength = 0;
}

CTSPacketProducer::~CTSPacketProducer(void)
{
}


EResult CTSPacketProducer::AttachObserver(UINT16 uwPid, CTSPacketObserver *pTSPacketObserver)
{
	if( NULL == pTSPacketObserver)
	{
		return FAILURE;
	}

	IteratorPidObserver iteratorPidObserver;
	for( iteratorPidObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidObserver; iteratorPidObserver++)
	{
		if(( iteratorPidObserver->first == uwPid ) && ( iteratorPidObserver->second == pTSPacketObserver ))
		{
			return FAILURE;
		}
	}


	if(m_storeObserver.insert(PidObserverPair(uwPid, pTSPacketObserver))->second)
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
EResult CTSPacketProducer::DetachtObserver(UINT16 uwPid, CTSPacketObserver *pTSPacketObserver)
{
	if( NULL == pTSPacketObserver)
	{
		return FAILURE;
	}
	EResult eResult = FAILURE;

	IteratorPidObserver iteratorPidObserver;
	for( iteratorPidObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidObserver; )
	{
		if(( iteratorPidObserver->first == uwPid ) && ( iteratorPidObserver->second == pTSPacketObserver ))
		{
			m_storeObserver.erase(iteratorPidObserver++);
			TRACE("[%s, %d]m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
		}
		else
		{
			iteratorPidObserver++;
		}
	}
	
	return SUCCESS;
};


EResult CTSPacketProducer::RemoveAllObserver(void)
{
	m_storeObserver.clear();
	TRACE("[%s, %d]m_storeObserver.count() %04d\r\n", __FUNCTION__, __LINE__, m_storeObserver.size());
	return SUCCESS;
};

EResult CTSPacketProducer::SetInfo(EPacketLength ePacketLength, FILE * vFile, UINT32 uiDataLength)
{
	if(( TS_PACKET_LENGTH_UNKNOWN == ePacketLength) || ( NULL == vFile) || ( 0 == uiDataLength))
	{
		return FAILURE;
	}

	//Save the input data.
	m_ePacketLength = ePacketLength;
	mFile = vFile;
	m_uiDataLength = uiDataLength;

	return SUCCESS;
};

EResult CTSPacketProducer::GetNextPacket(UINT32 uiCurrentPacketNumber )
{
	//If the left data is shorter than a packet, return FAILURE to stop.
	if( (UINT32)m_ePacketLength > m_uiDataLength )
	{
		TRACE("GetNextPacket returns FAILURE. m_uiDataLength %04d\r\n", m_uiDataLength);
		return FAILURE;
	}

	/*Read in a packet.*/
	size_t vBytesRead = fread( mPacketBuffer, 1, m_ePacketLength, mFile );
	if(vBytesRead != m_ePacketLength)
	{
	    return FAILURE;
	}
	else
	{
	    if( TS_SYN_BYTE != mPacketBuffer[0])
	    {
            CString vErrorMsg;
            vErrorMsg.Format(L"Out of synchronization at offset %d bytes", ftell(mFile));
	        //AfxMessageBox(vErrorMsg);
	        //return FAILURE;
	    }
	    else
	    {
    	    /*Notify each packet.*/
        	/*
        	**Get current packet and notify all the observers.All the observers must extract before Notify returns.
        	**The first packet number passed in is ZERO, so we would like to add 1 to it.
        	*/
        	NotifyAllObservers(mPacketBuffer, m_ePacketLength, uiCurrentPacketNumber + 1);

        	//Set the pointer to the next packet.
        	m_uiDataLength -= m_ePacketLength;
	    }
	}
	return SUCCESS;
};

EResult CTSPacketProducer::NotifyAllObservers(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber)
{
	IteratorPidObserver iteratorPidObserver;
	UINT16 uwPid = CTSHeaderReader::GetPid(pucData);
    if(0x802 == uwPid)
    {
        TRACE("Haha, program for 0x05.\n");
    }
	for( iteratorPidObserver = m_storeObserver.begin(); m_storeObserver.end() != iteratorPidObserver; iteratorPidObserver++)
	{	
		if(( uwPid == iteratorPidObserver->first ) || ( PID_INVALID == iteratorPidObserver->first ))
		{
			CTSPacketObserver * pTSPacketObserver = (CTSPacketObserver *)iteratorPidObserver->second;
			pTSPacketObserver->ProcessNewPacket(pucData, ePacketLength, uiCurrentPacketNumber);
		}

	}

	return SUCCESS;
};