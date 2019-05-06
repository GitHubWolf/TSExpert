#include "StdAfx.h"
#include "TSHeaderReader.h"


#if 0
transport_packet()
{		
	sync_byte	8	bslbf
	transport_error_indicator	1	bslbf
	payload_unit_start_indicator	1	bslbf
	transport_priority	1	bslbf
	PID	13	uimsbf
	transport_scrambling_control	2	bslbf
	adaptation_field_control	2	bslbf
	continuity_counter	4	uimsbf
	if(adaptation_field_control=='10'  || adaptation_field_control=='11')
	{		
		adaptation_field()		
	}		
	if(adaptation_field_control=='01' || adaptation_field_control=='11') 
	{		
		for (i=0;i<N;i++){		
			data_byte	8	bslbf
		}		
	}		
}		
#endif

CTSHeaderReader::CTSHeaderReader(void)
{
}

CTSHeaderReader::~CTSHeaderReader(void)
{
}


UCHAR8 CTSHeaderReader::GetSynByte(UCHAR8 const *pucData)
{
	return pucData[0];
};
UCHAR8 CTSHeaderReader::GetErrorIndicator(UCHAR8 const *pucData)
{
	return ((pucData[1] >> 7) & 0x1);
};
UCHAR8 CTSHeaderReader::GetUnitStartIndicator(UCHAR8 const *pucData)
{
	return ((pucData[1] >> 6) & 0x1);
};
UCHAR8 CTSHeaderReader::GetPriority(UCHAR8 const *pucData)
{
	return ((pucData[1] >> 5) & 0x1);
};
UINT16 CTSHeaderReader::GetPid(UCHAR8 const *pucData)
{
	return (((pucData[1] & 0x1F ) << 8) | pucData[2]);
};
UCHAR8 CTSHeaderReader::GetScramblingControl(UCHAR8 const *pucData)
{
	return ((pucData[3] >> 6) & 0x3);
};
UCHAR8 CTSHeaderReader::GetAdaptationFieldControl(UCHAR8 const *pucData)
{
	return ((pucData[3] >> 4) & 0x3);
};
UCHAR8 CTSHeaderReader::GetContinuityCounter(UCHAR8 const *pucData)
{
	return (pucData[3] & 0xF);
};

EResult CTSHeaderReader::GetPayloadOffsetAndLength(UCHAR8 const *pucData, UCHAR8 *pucOffset, UCHAR8 *pucLength, EDataType eDataType, UCHAR8 * const pucPointerField)
{
	UCHAR8 ucAdaptationFieldControl = GetAdaptationFieldControl(pucData);
	UINT32 uiOffset;
	UCHAR8 ucPointFieldValue = 0;

	/*
	**If adaptation_field_control is '10',no payload, only 183 Bytes adaptation_field.
	**If adaptation_field_control is '00',reserved.
	*/
	if(( 0x2 == ucAdaptationFieldControl ) || ( 0x0 == ucAdaptationFieldControl ))
	{
		return FAILURE;
	}


	/*
	**If adaptation_field_control is '01',no adaptation_field, only 184 Bytes payload.
	*/
	if(0x1 == ucAdaptationFieldControl )
	{
		/*If it has PES data, no pointer_field exists.*/
		if( DATA_TYPE_PESPACKET == eDataType)
		{
			uiOffset = 4;
		}
		else if( DATA_TYPE_SECTION == eDataType)
		{
			/*
			**If payload_unit_start_indicator is '1', read pointer_field to get the offset.
			**If payload_unit_start_indicator is '0', then all is 184 Bytes payload.
			*/
			if( 0x1 == GetUnitStartIndicator( pucData ) )
			{
				ucPointFieldValue = pucData[4];
				uiOffset = 5 + ucPointFieldValue;
			}
			else if(  0x0 == GetUnitStartIndicator( pucData )  )
			{
				uiOffset = 4;
			}
		}
		else
		{
			return FAILURE;
		}


		*pucOffset = uiOffset;
		*pucLength = 188 - uiOffset;
		*pucPointerField = ucPointFieldValue;
		return SUCCESS;
	}

	/*
	**If adaptation_field_control is '11',payload after adaptation_field.
	*/
	if( 0x3 == ucAdaptationFieldControl )
	{

		UCHAR8 ucAdaptationFieldLength = pucData[4];

		/*Skip all adaptation field data.*/
		uiOffset = 5 + ucAdaptationFieldLength;

		/*If it has PES data, no pointer_field exists.*/
		if( DATA_TYPE_PESPACKET == eDataType)
		{
			uiOffset = uiOffset;
		}
		else if( DATA_TYPE_SECTION == eDataType)
		{
			/*
			**If payload_unit_start_indicator is '1', read pointer_field to get the offset.
			**If payload_unit_start_indicator is '0', then all is 184 Bytes payload.
			*/
			if( 0x1 == GetUnitStartIndicator( pucData ) )
			{
				ucPointFieldValue = pucData[uiOffset];
				uiOffset = uiOffset + ucPointFieldValue + 1;
			}
			else if(  0x0 == GetUnitStartIndicator( pucData )  )
			{
				uiOffset = uiOffset;
			}
		}
		else
		{
			return FAILURE;
		}

		*pucOffset = uiOffset;
		*pucLength = 188 - uiOffset;
		*pucPointerField = ucPointFieldValue;
		return SUCCESS;
	}
	return FAILURE;

}

LPWSTR CTSHeaderReader::GetScramblingControlName(UCHAR8 const *pucData)
{
	UCHAR8 ucScramblingControl = GetScramblingControl(pucData);

	return GetScramblingControlName(ucScramblingControl);;
}
LPWSTR CTSHeaderReader::GetAdaptationControlName(UCHAR8 const *pucData)
{
	UCHAR8 ucAdaptationControl = GetAdaptationFieldControl(pucData);

	return GetAdaptationControlName(ucAdaptationControl);
}


LPWSTR CTSHeaderReader::GetScramblingControlName(UINT32 uiParameter )
{
	switch(uiParameter)
	{
		case 0x0:
			return L"No scrambling";
		case 0x1:
			return L"Reserved";
		case 0x2:
			return L"Scrambled with Even Key";
		case 0x3:
			return L"Scrambled with Odd Key";
	}

	return L"Reserved";
}
LPWSTR CTSHeaderReader::GetAdaptationControlName(UINT32 uiParameter)
{	switch(uiParameter)
	{
		case 0x0:
			return L"Reserved";
		case 0x1:
			return L"No adaptation_field, payload only";
		case 0x2:
			return L"Adaptation_field only, no payload";
		case 0x3:
			return L"Adaptation_field followed by payload";
	}

	return L"Reserved";
}
