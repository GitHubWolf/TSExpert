#pragma once
#include "TSPublic.h"

class CTSHeaderReader
{
public:
	CTSHeaderReader(void);
public:
	~CTSHeaderReader(void);
public:
	static UCHAR8 GetSynByte(UCHAR8 const *pucData);
	static UCHAR8 GetErrorIndicator(UCHAR8 const *pucData);
	static UCHAR8 GetUnitStartIndicator(UCHAR8 const *pucData);
	static UCHAR8 GetPriority(UCHAR8 const *pucData);
	static UINT16 GetPid(UCHAR8 const *pucData);
	static UCHAR8 GetScramblingControl(UCHAR8 const *pucData);
	static UCHAR8 GetAdaptationFieldControl(UCHAR8 const *pucData);
	static UCHAR8 GetContinuityCounter(UCHAR8 const *pucData);
	static EResult GetPayloadOffsetAndLength(UCHAR8 const *pucData, UCHAR8 *pucOffset, UCHAR8 *pucLength, EDataType eDataType, UCHAR8 * const pucPointerField);
	static LPWSTR GetScramblingControlName(UCHAR8 const *pucData);
	static LPWSTR GetAdaptationControlName(UCHAR8 const *pucData);
	static LPWSTR GetScramblingControlName(UINT32 uiParameter);
	static LPWSTR GetAdaptationControlName(UINT32 uiParameter);	
};
