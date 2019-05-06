#include "StdAfx.h"
#include "TSHeaderLocator.h"
#include <algorithm>
CTSHeaderLocator::~CTSHeaderLocator(void)
{
}

CTSHeaderLocator::CTSHeaderLocator(void)
{
	m_uiValidHeaderOffset = 0;
	m_ePacketLength = TS_PACKET_LENGTH_UNKNOWN;
	m_eMinPacketLength = TS_PACKET_LENGTH_UNKNOWN;
	m_eMaxPacketLength = TS_PACKET_LENGTH_UNKNOWN;
	m_pucData = NULL;
	m_uiDataLength = 0;

	/*
	**Add all possible packet length into the store.
	**When a new packet length is added into this program, we must push_back its value into the store.
	*/
	m_storePacketLength.insert(TS_PACKET_LENGTH_188);
	m_storePacketLength.insert(TS_PACKET_LENGTH_204);

	m_eMinPacketLength = *min_element(m_storePacketLength.begin(), m_storePacketLength.end());
	m_eMaxPacketLength = *max_element(m_storePacketLength.begin(), m_storePacketLength.end());
};

UINT32 CTSHeaderLocator::GetValidHeaderOffset(void)
{
	return m_uiValidHeaderOffset;
};
EPacketLength CTSHeaderLocator::GetPacketLength(void)
{
	return m_ePacketLength;
};

EResult CTSHeaderLocator::Parse(UINT32 uiDataLength, UCHAR8 const * pucData)
{
	EResult eResult = FAILURE;
	
	m_pucData = pucData;
	m_uiDataLength = uiDataLength;

	/*
	**Let's compare m_eMinPacketLength with TS_PACKET_LENGTH_UNKNOWN, 
	**after that, we can safely cast m_eMinPacketLength to UINT32.
	*/
	if( ( TS_PACKET_LENGTH_UNKNOWN >= m_eMinPacketLength ) 
		|| ( (UINT32)m_eMinPacketLength > m_uiDataLength ) 
		|| ( NULL == m_pucData ))
	{
		return FAILURE;
	}

	//Find out the maximum and minimum.
	IteratorPacketLength iteratorPacketLength;

	for( iteratorPacketLength = m_storePacketLength.begin();m_storePacketLength.end() != iteratorPacketLength; iteratorPacketLength++)
	{
		if(SUCCESS == ParseWithLength(*iteratorPacketLength))
		{
			return SUCCESS;
		}
	}
	return eResult;
};

EResult CTSHeaderLocator::ParseWithLength(EPacketLength ePacketLength)
{
	EResult eResult = FAILURE;

	if( ( (UINT32)ePacketLength > m_uiDataLength ) || ( NULL == m_pucData ))
	{
		return FAILURE;
	}

	//Save m_uiDataLength into a temp variable.
	UINT32 uiDataLength = m_uiDataLength;

	UINT32 uiNextPos;
	for(UINT32 i = 0; i < (UINT32)ePacketLength; i++)
	{
		//Get the first TS_SYN_BYTE, let's check the TS_SYN_BYTE of next packet.
		if( TS_SYN_BYTE == m_pucData[i])
		{
			for( UINT32 j = 1; MAX_RECHECK_TIMES >= j; j++)
			{
				uiNextPos = i + (j*ePacketLength);
				if(uiNextPos < uiDataLength)
				{
					//If next start byte is not a TS_SYN_BYTE, let's break current loop.
					if( TS_SYN_BYTE != m_pucData[uiNextPos])
					{
						//If FALSE, set the result to be FAILURE, otherwise,the logic is wrong.
						eResult = FAILURE;
						break;
					}
					
					//Now break out from current loop,the first byte is right.
					if(MAX_RECHECK_TIMES == j)
					{
						eResult = SUCCESS;
						m_uiValidHeaderOffset = i;
						m_ePacketLength = ePacketLength;
						return eResult;
					}
				}
				else
				{
					eResult = SUCCESS;
					m_uiValidHeaderOffset = i;
					m_ePacketLength = ePacketLength;
					return eResult;
				}
			}
		}
	}
	return eResult;
};