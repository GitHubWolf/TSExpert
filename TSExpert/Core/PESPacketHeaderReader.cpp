#include "StdAfx.h"
#include "PESPacketHeaderReader.h"

CPESPacketHeaderReader::CPESPacketHeaderReader(void)
{
}

CPESPacketHeaderReader::~CPESPacketHeaderReader(void)
{
}


UINT32 CPESPacketHeaderReader::GetPacketStartCodePrefix(UCHAR8 const *pucData)
{
	/*24 Bit packet_start_code_prefix.It shall be 0x000001.*/
	UINT32 uiData = ((pucData[0] << 16) | (pucData[1] << 8) | ( pucData[2]));

	return uiData;
}
UINT32 CPESPacketHeaderReader::GetStreamId(UCHAR8 const *pucData)
{
	/*8Bit stream_id.*/
	UINT32 uiData = pucData[3];

	return uiData;
}
UINT32 CPESPacketHeaderReader::GetPESPacketLength(UCHAR8 const *pucData)
{
	/*16Bit PES_packet_length.*/
	UINT32 uiData = ( (pucData[4] << 8) | pucData[5]);

	return uiData;
}