#include "StdAfx.h"
#include "SectionHeaderReader.h"

CSectionHeaderReader::CSectionHeaderReader(void)
{
}

CSectionHeaderReader::~CSectionHeaderReader(void)
{
}


UCHAR8 CSectionHeaderReader::GetTableId(UCHAR8 const *pucData)
{
	return pucData[0];
};
UCHAR8 CSectionHeaderReader::GetSectionSyntaxIndicator(UCHAR8 const *pucData)
{
	UCHAR8 ucSynIndicator;
	ucSynIndicator = ((pucData[1] >> 7) &0x1);
	return ucSynIndicator;
};
UCHAR8 CSectionHeaderReader::GetPrivateIndicator(UCHAR8 const *pucData)
{
	UCHAR8 ucPrivateIndicator;
	ucPrivateIndicator = ((pucData[1] >> 6) &0x1);
	return ucPrivateIndicator;
};

UCHAR8 CSectionHeaderReader::GetReserved(UCHAR8 const *pucData)
{
	UCHAR8 ucReserved;
	ucReserved = ((pucData[1] >> 4) & 0x3);
	return ucReserved;
};


UINT32 CSectionHeaderReader::GetSectionLength(UCHAR8 const *pucData)
{
	UINT32 uiSectionLength;
	uiSectionLength = ((pucData[1] & 0xF) << 8) | (pucData[2]);
	return uiSectionLength;
};


UINT16 CSectionHeaderReader::GetTableIdExtension(UCHAR8 const *pucData)
{
	UINT16 uwTableIdExt = ((pucData[3] << 8) )| (pucData[4]);

	return uwTableIdExt;
};
UCHAR8 CSectionHeaderReader::GetVersionNumber(UCHAR8 const *pucData)
{
	UCHAR8 ucVersionNumber = ((pucData[5] >> 1) &(0x1F));

	return ucVersionNumber;

};

UCHAR8 CSectionHeaderReader::GetSectionNumber(UCHAR8 const *pucData)
{
	UCHAR8 ucSectionNumber = pucData[6];

	return ucSectionNumber;

};


UCHAR8 CSectionHeaderReader::GetLastSectionNumber(UCHAR8 const *pucData)
{
	UCHAR8 ucLastSectionNumber = pucData[7];

	return ucLastSectionNumber;
};


UCHAR8 CSectionHeaderReader::GetByte(UCHAR8 const *pucData, UINT32 uiByte)
{
	UCHAR8 ucLastSectionNumber = pucData[uiByte];

	return ucLastSectionNumber;
};