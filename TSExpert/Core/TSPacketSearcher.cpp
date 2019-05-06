#include "StdAfx.h"
#include "TSPacketSearcher.h"
#include "TSHeaderReader.h"
#include "Descriptor.h"
#include "TSParser.h"
#include "TSPacketStore.h"

CTSPacketSearcher::CTSPacketSearcher(CTSParser *pTSParser):CTSPacketObserver(pTSParser)
{

}

CTSPacketSearcher::~CTSPacketSearcher(void)
{
	IteratorTSPacketStore iteratorTSPacketStore;
	CTSPacketStore * pTSPacketStore = NULL;
	for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
	{
		pTSPacketStore = *iteratorTSPacketStore;
		//pTSPacketStore->DumpStoredData();
		delete pTSPacketStore;
	}
}

EResult CTSPacketSearcher::ProcessNewPacket(UCHAR8 const *pucData, EPacketLength ePacketLength, UINT32 uiCurrentPacketNumber)
{
	if( NULL == pucData )
	{
		return FAILURE;
	}

	UINT16 uwPid = CTSHeaderReader::GetPid(pucData);
	CTSPacketStore *pTSPacketStore = new CTSPacketStore(uwPid, ePacketLength, m_pTSParser);
	EResult eResult = pTSPacketStore->AddData(pucData, ePacketLength, uiCurrentPacketNumber);

	TMsgNewSearchedTSPacket *pMsg = new TMsgNewSearchedTSPacket;
	pMsg->pTSPacketObserver = this;
	pMsg->pTSPacketStore = pTSPacketStore;
	if( SUCCESS != SendMsgToView(MESSAGE_NEW_SEARCHED_TS_PACKET, (pMsg) ))
	{
		delete pMsg;
	}

	/*Increase saved count, so that the search will quit once it reaches the limit.*/
	m_pTSParser->IncementSavedCount(1);
	return eResult;
}

EResult CTSPacketSearcher::DisplayTSPacketData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiOffset = 0;

	const UINT32 uiStoredLengthConst = uiStoredLength;
	const UCHAR8 * const pucDataConst = pucData;


	UINT32 uiData;
	UINT32 uiFieldLength;

	// 8 Bit sync_byte.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"sync_byte", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit transport_error_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_error_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit payload_unit_start_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"payload_unit_start_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit transport_priority.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 5) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_priority", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 13 Bit PID.
	uiFieldLength = 13;
	uiData = (((pucData[1] & 0x1F ) << 8 )| pucData[2]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PID", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 2 Bit transport_scrambling_control.
	uiFieldLength = 2;
	uiData = ((pucData[3] >> 6 ) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_scrambling_control", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"transport_scrambling_control[%d]:0x%02X, %s", uiFieldLength, uiData, CTSHeaderReader::GetScramblingControlName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit adaptation_field_control.
	uiFieldLength = 2;
	uiData = ((pucData[3] >> 4 ) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptation_field_control", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"adaptation_field_control[%d]:0x%02X, %s", uiFieldLength, uiData, CTSHeaderReader::GetAdaptationControlName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiAdaptationFieldControl = uiData;

	// 4 Bit continuity_counter.
	uiFieldLength = 4;
	uiData = ((pucData[3]) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"continuity_counter", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*4 byte packet header.*/
	uiStoredLength -= 4;
	pucData += 4;

	/*If adaption_field exists.*/
	if(( 0x2 == uiAdaptationFieldControl ) || ( 0x3 == uiAdaptationFieldControl ))
	{

		UINT32 uiAdaptationFieldLength = pucData[0];

		/*Check if adaptation_field_length is valid. */
		if( (uiAdaptationFieldLength + 1) > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		// N Bit adaptation_field.
		uiFieldLength = (uiAdaptationFieldLength + 1)*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptation_field", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		/*Call the function to parse adaptation field.*/
		DisplayAdaptationField(pTSPacketStore, pTreeList,  pTreeNode, pucData, uiOffset);
		uiOffset += uiFieldLength;



		uiStoredLength -= uiAdaptationFieldLength;
		pucData += uiAdaptationFieldLength;

	}

	/*If data_byte exists.*/
	if(( 0x1 == uiAdaptationFieldControl ) || ( 0x3 == uiAdaptationFieldControl ))
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"data_byte", uiOffset, uiStoredLength*8, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiStoredLength*8;
		pucData += uiStoredLength;
		uiStoredLength = 0;
	}

	return SUCCESS;
}


EResult CTSPacketSearcher::DisplayAdaptationField(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 8 Bit adaptation_field_length.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptation_field_length", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiStoredLength = uiData;

	if( 0 == uiStoredLength)
	{
		return SUCCESS;
	}

	// 1 Bit discontinuity_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"discontinuity_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit random_access_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"random_access_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit elementary_stream_priority_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 5) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"elementary_stream_priority_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit PCR_flag.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 4) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PCR_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPCRFlag = uiData;

	// 1 Bit OPCR_flag.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 3) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"OPCR_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiOPCRFlag = uiData;

	// 1 Bit splicing_point_flag.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"splicing_point_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiSplicingPointFlag = uiData;

	// 1 Bit transport_private_data_flag.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 1) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_private_data_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiTransportPrivateDataFlag = uiData;

	// 1 Bit adaptation_field_extension_flag.
	uiFieldLength = 1;
	uiData = ((pucData[1] ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptation_field_extension_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiAdaptationFieldExtensionFlag = uiData;

	pucData += 2;
	uiStoredLength -= 1;

	if( 0x1 == uiPCRFlag )
	{
		/*Check length here.*/
		if( 6 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}


		// 33 Bit program_clock_reference_base.
		uiFieldLength = 33;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"program_clock_reference_base", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 6 Bit reserved.
		uiFieldLength = 6;
		uiData = (((pucData[4] ) >> 1) & 0x3F);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 9 Bit program_clock_reference_extension.
		uiFieldLength = 9;
		uiData = (((pucData[4] & 0x1 ) << 8) | pucData[5]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"program_clock_reference_extension", uiOffset, uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 6;
		uiStoredLength -= 6;
	}


	if( 0x1 == uiOPCRFlag )
	{
		/*Check length here.*/
		if( 6 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}


		// 33 Bit original_program_clock_reference_base.
		uiFieldLength = 33;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"original_program_clock_reference_base", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 6 Bit reserved.
		uiFieldLength = 6;
		uiData = (((pucData[4] ) >> 1) & 0x3F);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 9 Bit original_program_clock_reference_extension.
		uiFieldLength = 9;
		uiData = (((pucData[4] & 0x1 ) << 8) | pucData[5]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"original_program_clock_reference_extension", uiOffset, uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 6;
		uiStoredLength -= 6;
	}


	if( 0x1 == uiSplicingPointFlag )
	{
		/*Check length here.*/
		if( 1 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		// 8 Bit splice_countdown.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"splice_countdown", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiStoredLength -= 1;
	}

	if( 0x1 == uiTransportPrivateDataFlag )
	{
		/*Check length here.*/
		if( 1 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		// 8 Bit transport_private_data_length.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_private_data_length", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiStoredLength -= 1;

		UINT32 uiTransportPrivateDataLength = uiData;

		/*Check if transport_private_data_length is valid. */
		if( uiTransportPrivateDataLength > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		/*N byte private_data_byte.*/
		uiFieldLength = uiTransportPrivateDataLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiTransportPrivateDataLength;
		uiStoredLength -= uiTransportPrivateDataLength;

	}


	if( 0x1 == uiAdaptationFieldExtensionFlag )
	{
		/*Check length here.*/
		if( 1 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		UINT32 uiAdaptationFieldExtensionLength = pucData[0];

		/*Check if adaptation_field_extension_length is valid. */
		if( (uiAdaptationFieldExtensionLength + 1) > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}
		/*Call the function to parse adaptation field.*/
		DisplayAdaptationFieldExtension(pTSPacketStore, pTreeList,  pTreeNode, pucData, uiOffset);

		pucData += (uiAdaptationFieldExtensionLength + 1);
		uiStoredLength -= (uiAdaptationFieldExtensionLength + 1);

	}


	if( 0 != uiStoredLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"stuffing_byte", uiOffset, uiStoredLength*8, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiStoredLength*8;
		pucData += uiStoredLength;
		uiStoredLength = 0;
		
	}

	return SUCCESS;
}




EResult CTSPacketSearcher::DisplayAdaptationFieldExtension(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 8 Bit adaptation_field_extension_length.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptation_field_extension_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	UINT32 uiStoredLength = uiData;

	if( 1 > uiStoredLength )
	{
		return SUCCESS;
	}

	// 1 Bit ltw_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ltw_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiLtwFlag = uiData;

	// 1 Bit piecewise_rate_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"piecewise_rate_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPiecewiseRateFlag = uiData;

	// 1 Bit seamless_splice_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 5) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"seamless_splice_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiSeamlessSpliceFlag = uiData;

	// 5 Bit reserved.
	uiFieldLength = 5;
	uiData = (pucData[0] & 0x1F );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	pucData += 1;
	uiStoredLength -= 1;

	if( 0x1 == uiLtwFlag)
	{
		/*Check length here.*/
		if( 2 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		// 1 Bit ltw_valid_flag.
		uiFieldLength = 1;
		uiData = ((pucData[0] >> 7) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"ltw_valid_flag", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 15 Bit ltw_offset.
		uiFieldLength = 15;
		uiData = (((pucData[0] & 0x7F )<< 8) | pucData[1]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"ltw_offset", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 2;
		uiStoredLength -= 2;
	}


	if( 0x1 == uiPiecewiseRateFlag)
	{
		/*Check length here.*/
		if( 3 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		// 2 Bit reserved.
		uiFieldLength = 2;
		uiData = ((pucData[0] >> 6) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 22 Bit piecewise_rate.
		uiFieldLength = 22;
		uiData = (((pucData[0] & 0x3F ) << 16) | (pucData[1] << 8) | pucData[2]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"piecewise_rate", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 3;
		uiStoredLength -= 3;
	}

	if(0x1 == uiSeamlessSpliceFlag)
	{
		/*Check length here.*/
		if( 5 > uiStoredLength )
		{
			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		// 4 Bit splice_type.
		uiFieldLength = 4;
		uiData = ((pucData[0] >> 4) & 0xF);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"splice_type", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 3 Bit DTS_next_AU[32..30].
		uiFieldLength = 3;
		uiData = ((pucData[0] >> 1) & 0x7);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DTS_next_AU[32..30]", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 1 Bit marker_bit.
		uiFieldLength = 1;
		uiData = ((pucData[0]) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 15 Bit DTS_next_AU[29..15].
		uiFieldLength = 15;
		uiData = (((pucData[1]) << 7) | ((pucData[2] >> 1)  & 0x7F));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DTS_next_AU[29..15]", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 1 Bit marker_bit.
		uiFieldLength = 1;
		uiData = ((pucData[2]) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 15 Bit DTS_next_AU[14..0].
		uiFieldLength = 15;
		uiData = (((pucData[3]) << 7) | ((pucData[4] >> 1)  & 0x7F));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DTS_next_AU[14..0]", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 1 Bit marker_bit.
		uiFieldLength = 1;
		uiData = ((pucData[4]) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 5;
		uiStoredLength -= 5;
	}

	if( 0x0 != uiStoredLength)
	{
		/*N byte reserved.*/
		uiFieldLength = uiStoredLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;
}

EResult CTSPacketSearcher::GetTSPacketDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucUnitStartIndicator = CTSHeaderReader::GetUnitStartIndicator(pucData);
	UCHAR8 ucContinuityCounter = CTSHeaderReader::GetContinuityCounter(pucData);

	strDescription.Format(L"PayloadUnitStartIndicator: %u, ContinuityCounter: %2u, %s, %s", 
		ucUnitStartIndicator, ucContinuityCounter, CTSHeaderReader::GetScramblingControlName(pucData), 
		CTSHeaderReader::GetAdaptationControlName(pucData));
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};
