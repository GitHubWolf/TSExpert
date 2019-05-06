#pragma once
#include "TSPublic.h"

class CPESPacketHeaderReader
{
public:
	CPESPacketHeaderReader(void);
public:
	static UINT32 GetPacketStartCodePrefix(UCHAR8 const *pucData);
	static UINT32 GetStreamId(UCHAR8 const *pucData);
	static UINT32 GetPESPacketLength(UCHAR8 const *pucData);
public:
	~CPESPacketHeaderReader(void);
};
