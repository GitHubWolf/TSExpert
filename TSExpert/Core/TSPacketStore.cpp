#include "StdAfx.h"
#include "TSPacketStore.h"

CTSPacketStore::CTSPacketStore(UINT16 uwPid, UINT32 uiTotalLengh, CTSParser *pTSParser)
{
	m_uiTotalLength = uiTotalLengh;
	m_uiStoredLength = 0;
	m_pucBuffer = new UCHAR8[m_uiTotalLength];	
	m_uiRepeatCount = 1;
	m_uwPid = uwPid;

	m_pTreeNodeRootNode = NULL;
	m_pTSParser = pTSParser;
	m_pTreeList = NULL;
	m_uiFirstPacketNumber = 0;
	m_uiLastPacketNumber = 0;
	m_uiTotalPacketCount = 0;

}

CTSPacketStore::~CTSPacketStore(void)
{

	delete[] m_pucBuffer;
}


EResult CTSPacketStore::AddData(UCHAR8 const *pucData,  UINT32 uiDataLength, UINT32 uiCurrentPacketNumber)
{
	m_uiLastPacketNumber = uiCurrentPacketNumber;
	m_uiTotalPacketCount++;
	if( 0 ==  m_uiFirstPacketNumber )
	{
		/*If m_uiFirstPacketNumber has never been assigned a value.*/
		m_uiFirstPacketNumber = uiCurrentPacketNumber;
	}
	/*
	**For PES packet, 16Bits length is NOT enough. PES_packet_length will sometimes be ZERO,
	**in such case, we will add new data in append mode.
	**A value of 0 indicates that the PES packet length is neither specified nor bounded and is allowed only in
	**PES packets whose payload consists of bytes from a video elementary stream contained in Transport Stream packets.
	*/
	if( VALUE_ZERO == m_uiTotalLength )
	{
		/*Only video PES packet and private sections will reach here.*/
		return AppendData(pucData, uiDataLength);
	}

	//Check the buffer space, so that it will not overflow.
	if(( m_uiStoredLength + uiDataLength) >= m_uiTotalLength)
	{
		memcpy(m_pucBuffer + m_uiStoredLength, pucData, (m_uiTotalLength - m_uiStoredLength));
		m_uiStoredLength = m_uiTotalLength;

		//A new section or pes packet found, return SUCCESS.
		return SUCCESS;
	}
	else
	{
		memcpy(m_pucBuffer + m_uiStoredLength, pucData, uiDataLength);
		m_uiStoredLength += uiDataLength;
		
		//Waiting for more data.
		return FAILURE;
	}
	
	return SUCCESS;
};


EResult CTSPacketStore::AppendData(UCHAR8 const *pucData,  UINT32 uiDataLength)
{
	/*Allocate buffer for the saved and incoming data.*/	
	UINT32 uiNewLength = (m_uiStoredLength + uiDataLength);
	UCHAR8 *pucNewBuffer = new UCHAR8[uiNewLength];

	/*Copy the saved data to the new buffer.*/
	memcpy(pucNewBuffer, m_pucBuffer, m_uiStoredLength);

	/*Append new data to the end.*/
	memcpy(pucNewBuffer + m_uiStoredLength,  pucData,  uiDataLength);

	/*Recaculate data length.*/
	m_uiStoredLength = uiDataLength + m_uiStoredLength;

	/*Free saved data.*/
	delete m_pucBuffer;

	/*Reassign new buffer to m_pucBuffer.*/
	m_pucBuffer = pucNewBuffer;
	
	//Waiting for more data.
	return FAILURE;
};


UCHAR8 const * CTSPacketStore::GetDataAddr(void) const
{
	return m_pucBuffer;
};


UINT32 CTSPacketStore::GetTotalLength(void) const
{
	return m_uiTotalLength;
};

UINT32 CTSPacketStore::GetStoredLength(void) const
{
	return m_uiStoredLength;
};

EResult CTSPacketStore::Match( CTSPacketStore const * pTSPacketStore, UINT32 uiMatchLength)
{
	UCHAR8 const * pucBuffer = pTSPacketStore->GetDataAddr();
	UINT32 uiTotalLength = pTSPacketStore->GetTotalLength();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();

	if( pTSPacketStore == this )
	{
		return SUCCESS;
	}

	if( uiTotalLength != m_uiTotalLength )
	{
		return FAILURE;
	}

	if( uiStoredLength != m_uiStoredLength )
	{
		return FAILURE;
	}

#if 1

    UINT32 uiCompareLength = m_uiStoredLength;


    for(UINT32 i = 0; i < uiCompareLength; i++)
    {
        if( pucBuffer[i] != m_pucBuffer[i])
        {
            return FAILURE;
        }
    }

#else

	UINT32 uiCompareLength = min(m_uiStoredLength, uiMatchLength);


	for(UINT32 i = 0; i < uiCompareLength; i++)
	{
		if( pucBuffer[i] != m_pucBuffer[i])
		{
			return FAILURE;
		}
	}


	/*Compare last 8 bytes.*/
	if( LAST_COMPARE_LENGTH <= uiStoredLength)
	{
		for( UINT32 i = 1; i< (LAST_COMPARE_LENGTH + 1); i++)
		{
			if( pucBuffer[ uiStoredLength - i] != m_pucBuffer[ uiStoredLength - i])
			{
				return FAILURE;
			}
		}
	}
#endif
	//If matched, then increase the repeat count by 1.
	m_uiRepeatCount++;
	return SUCCESS;

};

void CTSPacketStore::DumpStoredData(void)
{
	const UINT32 BYTES_PER_ROW  = 32;
	UINT32 uiRows = m_uiStoredLength/BYTES_PER_ROW;
	UINT32 uiLeftBytes = m_uiStoredLength%BYTES_PER_ROW;
	UINT32 uiUsedBytes = 0;
	UINT32 uiOffset = 0;

	UINT32 uiReservedBytes = m_uiStoredLength * 3 + (uiRows + 1)*2 + 1;
	char *pucMsg = new char[uiReservedBytes];
	memset(pucMsg, 0, uiReservedBytes);
	TRACE("\r\n---------------------------------------------------Section --------------------------Repeat %04d---------------\r\n", m_uiRepeatCount);

	for(UINT32 i = 0; i < uiRows; i++ )
	{
		for(UINT32 j = 0; j < BYTES_PER_ROW; j++ )
		{			
			sprintf_s(pucMsg+uiUsedBytes, uiReservedBytes - uiUsedBytes, "%02X ", m_pucBuffer[uiOffset]);
			uiOffset++;

			uiUsedBytes += 3;
		}

		sprintf_s(pucMsg+uiUsedBytes, uiReservedBytes - uiUsedBytes, "\r\n");
		uiUsedBytes += 2;

		TRACE("%s", (pucMsg+uiUsedBytes - 2 - (BYTES_PER_ROW*3)));

	}


	for(UINT32 i = 0; i < uiLeftBytes; i++)
	{
		sprintf_s(pucMsg+uiUsedBytes, uiReservedBytes - uiUsedBytes, "%02X ", m_pucBuffer[uiOffset]);
		uiUsedBytes += 3;
		uiOffset++;
	}

	sprintf_s(pucMsg+uiUsedBytes, uiReservedBytes - uiUsedBytes, "\r\n");
	uiUsedBytes += 2;

	TRACE("%s", (pucMsg+uiUsedBytes - 2 - (uiLeftBytes*3)));

#if 0
	UINT32 i = 0;
	while(i < uiReservedBytes)
	{
		TRACE("%s", pucMsg + i);
		i += (BYTES_PER_ROW*3 + 2) * 4;
	}
#endif

	delete []pucMsg;
#if 0
	for(UINT32 i = 0; i < m_uiStoredLength; i++ )
	{
		TRACE("%02X  ", m_pucBuffer[i]);
		if( 0 == (i + 1 )%uiWidth)
		{
			TRACE("\r\n");
		}
	}
#endif
}

UINT32 CTSPacketStore::GetRepeatCount(void)
{
	return m_uiRepeatCount;
};

EResult CTSPacketStore::SetRootNode(CTreeNode * pTreeNodeInput,CTreeList *pTreeList)
{
	m_pTreeNodeRootNode = pTreeNodeInput;
	m_pTreeList = pTreeList;

	return SUCCESS;
}

CTSParser *CTSPacketStore::GetTSParser(void)
{
	return m_pTSParser;
}

EResult CTSPacketStore::UpdateResult(void)
{
	if(( NULL != m_pTreeNodeRootNode) && ( NULL != m_pTreeList))
	{
		m_pTreeNodeRootNode->m_strText.AppendFormat(L"(Repeat:%4d)", m_uiRepeatCount);
		m_pTreeList->UpdateText(m_pTreeNodeRootNode);
	}

	return SUCCESS;
}

UINT32 CTSPacketStore::GetLastPacketNumber(void)
{
	return m_uiLastPacketNumber;
}

UINT32 CTSPacketStore::GetFirstPacketNumber(void)
{
	return m_uiFirstPacketNumber;
}

UINT32 CTSPacketStore::GetTotalPacketCount(void)
{
	return m_uiTotalPacketCount;
}

EResult CTSPacketStore::GetDescription(CString& strDescription)
{
	strDescription.AppendFormat(L"(Packet:%u[%u, %u])",
		m_uiTotalPacketCount, m_uiFirstPacketNumber, m_uiLastPacketNumber );
	return SUCCESS;
}

