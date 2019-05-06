#pragma once
#include "TSPublic.h"

class CSectionHeaderReader
{
public:
	CSectionHeaderReader(void);
public:
	static UCHAR8 GetTableId(UCHAR8 const *pucData);
	static UCHAR8 GetSectionSyntaxIndicator(UCHAR8 const *pucData);
	static UCHAR8 GetPrivateIndicator(UCHAR8 const *pucData);
	static UCHAR8 GetReserved(UCHAR8 const *pucData);	
	static UINT32 GetSectionLength(UCHAR8 const *pucData);
	static UINT16 GetTableIdExtension(UCHAR8 const *pucData);
	static UCHAR8 GetVersionNumber(UCHAR8 const *pucData);
	static UCHAR8 GetSectionNumber(UCHAR8 const *pucData);
	static UCHAR8 GetLastSectionNumber(UCHAR8 const *pucData);
	static UCHAR8 GetByte(UCHAR8 const *pucData, UINT32 uiByte);
public:
	~CSectionHeaderReader(void);
};
