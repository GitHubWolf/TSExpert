#pragma once
#include "TSPublic.h"
#include <set>

using namespace std ;

class CTSHeaderLocator
{
	//Define a new vector type to store all possible packet length.
	typedef set<EPacketLength> SetPacketLength;
	typedef SetPacketLength::iterator IteratorPacketLength;

public:
	CTSHeaderLocator(void);

public:
	//Begin to parse the data.
	EResult Parse(UINT32 uiDataLength, UCHAR8 const * pucData);

	//Get the offset position of first synchronize byte.
	UINT32 GetValidHeaderOffset(void);

	//Return length of each packet.
	EPacketLength GetPacketLength(void);
public:
	~CTSHeaderLocator(void);
private:
	EResult ParseWithLength(EPacketLength ePacketLength);

private:
	UINT32 m_uiValidHeaderOffset;

	//To store the parse result.
	EPacketLength m_ePacketLength;

	//The minimum packet length.
	EPacketLength m_eMinPacketLength;

	//The maximum packet length.
	EPacketLength m_eMaxPacketLength;

	//The max re-check times after a correct TS_SYN_BYTE.
	static const SINT32 MAX_RECHECK_TIMES = 3;

	//Vector to store all possible packet length.
	SetPacketLength m_storePacketLength;

	//Data buffer to be parsed.
	UCHAR8 const * m_pucData;

	//Length of data to be parsed.
	UINT32 m_uiDataLength;


};
