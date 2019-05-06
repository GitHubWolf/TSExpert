#include "StdAfx.h"
#include "SectionStoreNIT.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"
#include "Descriptor.h"

CSectionStoreNIT::CSectionStoreNIT(UINT16 uwPid, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{
}

CSectionStoreNIT::~CSectionStoreNIT(void)
{
}


EResult CSectionStoreNIT::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);
	if(( TABLEID_NIT_CURRENT == ucTableId) || ( TABLEID_NIT_OTHER == ucTableId))
	{
		return StoreNewData(pTSPacketStore);
	}

	return FAILURE;
};

EResult CSectionStoreNIT::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);
	if( MIN_SECTION_HEADER_LENGTH > uiStoredLength)
	{
		strDescription.Format(L"TableId 0x%02X, INVALID length 0x%04X", ucTableId, uiStoredLength);
		pTSPacketStore->GetDescription(strDescription);

		return FAILURE;
	}

	UINT16 uwTableIdExtension = CSectionHeaderReader::GetTableIdExtension(pucData);
	UCHAR8 ucVersionNumber = CSectionHeaderReader::GetVersionNumber(pucData);
	UCHAR8 ucSectionNumber = CSectionHeaderReader::GetSectionNumber(pucData);
	UCHAR8 ucLastSectionNumber = CSectionHeaderReader::GetLastSectionNumber(pucData);

	strDescription.Format(L"TableId 0x%02X, NetworkId 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
		ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};


EResult CSectionStoreNIT::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
{
	CSectionObserver::DisplaySectionData(pTSPacketStore,pTreeList, pTreeNodeInput, pTreeNodeParent);

	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiOffset = 0;
	
	const UINT32 uiStoredLengthConst = uiStoredLength;
	const UCHAR8 * const pucDataConst = pucData;

	UINT32 uiData;
	UINT32 uiFieldLength;

	if( MIN_SECTION_HEADER_LENGTH > uiStoredLength )
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid section header", 0, uiStoredLength*8, VALUE_ZERO, NODE_FIELD);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		return FAILURE;
	}


	// 8 Bit tabld_id.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"table_id", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit section_syntax_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"section_syntax_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	
	

	// 1 Bit reserved_future_use.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit reserved.
	uiFieldLength = 2;
	uiData = ((pucData[1] >> 4) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 12 Bit section_length.
	uiFieldLength = 12;
	uiData = (((pucData[1] & 0xF ) << 8 )| pucData[2]);
	if( uiStoredLengthConst != ( uiData + 3) )
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"section_length", uiOffset, uiFieldLength, uiData, NODE_WARNING );
		pTreeNode->m_strText.Format(L"section_length[%d]: 0x%04X (Length ERROR)", uiFieldLength, uiData);
	}
	else
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"section_length", uiOffset, uiFieldLength, uiData );
	}	
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 16 Bit network_id.
	uiFieldLength = 16;
	uiData = ((pucData[3]<< 8 )| pucData[4]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"network_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit reserved.
	uiFieldLength = 2;
	uiData = ((pucData[5] >> 6 ) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 5 Bit version_number.
	uiFieldLength = 5;
	uiData = ((pucData[5] >> 1 ) & 0x1F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"version_number", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 1 Bit current_next_indicator.
	uiFieldLength = 1;
	uiData = (pucData[5] & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"current_next_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit section_number.
	uiFieldLength = 8;
	uiData = pucData[6];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"section_number", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit last_section_number.
	uiFieldLength = 8;
	uiData = pucData[7];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"last_section_number", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// Subtract 8 Byte section header.
	uiStoredLength -= 8;
	pucData += 8;

	//Check the left length.
	if ( 4 > uiStoredLength )
	{
		//Invalid End.
		uiFieldLength = uiStoredLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}


	if( TRUE )  /*Parse CRC32  in advance.*/  
	{
		// 32 Bit CRC_32.
		uiFieldLength = 32;
		uiData = ((pucDataConst[uiStoredLengthConst -4]<< 24 ) 
			| (pucDataConst[uiStoredLengthConst -3]<< 16 ) 
			| (pucDataConst[uiStoredLengthConst -2]<< 8 )
			| pucDataConst[uiStoredLengthConst -1]);

		/*Check CRC32.*/
		UINT32 uiCRC32 = GenerateCRC32(pucDataConst, uiStoredLengthConst);
		if( 0 != uiCRC32 )
		{
			pTreeNode  = new CTreeNode(pTSPacketStore, L"CRC_32", (uiStoredLengthConst - 4)*8, uiFieldLength, uiData, NODE_WARNING );
			pTreeNode->m_strText.Format(L"CRC_32[%d]: 0x%08X (CRC32 ERROR or length ERROR)", uiFieldLength, uiData);
		}
		else
		{
			pTreeNode  = new CTreeNode(pTSPacketStore, L"CRC_32", (uiStoredLengthConst - 4)*8, uiFieldLength, uiData );
		}
		
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);

		uiStoredLength -= 4;
	}

	//Check the left length.
	if ( 2 > uiStoredLength )
	{
		//Invalid End.
		uiFieldLength = uiStoredLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	UINT32 uiDescriptorsLoopLength;

	// 4 Bit reserved_future_use.
	uiFieldLength = 4;
	uiData = ((pucData[0] >> 4)&0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 12 Bit network_descriptors_length.
	uiFieldLength = 12;
	uiData = (((pucData[0] &0xF) << 8) | pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"network_descriptors_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// Save length of DescriptorsLoop.
	uiDescriptorsLoopLength = uiData;

	uiStoredLength -= 2;
	pucData += 2;


	if (( uiStoredLength < uiDescriptorsLoopLength))
	{
		//Invalid End.
		uiFieldLength = uiStoredLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += uiStoredLength;
		uiStoredLength = 0;

		return FAILURE;
	}
	else
	{
		// uiDescriptorsLoopLength is valid. 

		// network_descriptors, it is a loop containing descriptors.
		uiFieldLength = uiDescriptorsLoopLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"network_descriptors loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		//Parse descriptors loop.
		CDescriptor::LoopParse( pTSPacketStore,pTreeList,  pTreeNode, pucData, uiOffset, uiDescriptorsLoopLength);

		//Set uiOffset after descriptors loop.
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += uiDescriptorsLoopLength;
		uiStoredLength -= uiDescriptorsLoopLength;

	}


	//Check the left length.
	if ( 2 > uiStoredLength )
	{
		//Invalid End.
		uiFieldLength = uiStoredLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}


	// 4 Bit reserved_future_use.
	uiFieldLength = 4;
	uiData = ((pucData[0] >> 4)&0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 12 Bit transport_stream_loop_length.
	uiFieldLength = 12;
	uiData = (((pucData[0] &0xF) << 8) | pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_stream_loop_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// Save length of DescriptorsLoop.
	uiDescriptorsLoopLength = uiData;

	uiStoredLength -= 2;
	pucData += 2;


	//Begin the loop.
	uiFieldLength = uiStoredLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_streams loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 6 <= uiStoredLength )
	{
		UINT32 uiTransportStreamId;
		UINT32 uiOriginalNetworkId;

		UINT32 uiDescriptorsLoopLength;

		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit transport_stream_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		CTreeNode *pTreeNodeTransportStreamId  = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of transport_stream_id.
		uiTransportStreamId = uiData;

		// 16 Bit original_network_id.
		uiFieldLength = 16;
		uiData = ((pucData[2]<< 8 )| pucData[3]);
		CTreeNode *pTreeNodeOriginalNetworkId  = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of original_network_id.
		uiOriginalNetworkId = uiData;


		// 4 Bit reserved_future_use.
		uiFieldLength = 4;
		uiData = ((pucData[4] >> 4)& 0xF );
		CTreeNode * pTreeNodeReservedTemp1  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;
		
		// 12 Bit transport_descriptors_length.
		uiFieldLength = 12;
		uiData = ((pucData[4] & 0xF ) << 8) | (pucData[5]);
		CTreeNode * pTreeNodeTransportDescriptorsLength  = new CTreeNode(pTSPacketStore, L"transport_descriptors_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the length of transport_descriptors_length.
		uiDescriptorsLoopLength = uiData;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 6 + uiDescriptorsLoopLength)*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"transport_stream_id:0x%04X ,original_network_id: 0x%04X", uiTransportStreamId, uiOriginalNetworkId);

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeTransportStreamId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeOriginalNetworkId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReservedTemp1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeTransportDescriptorsLength, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 6;
		uiStoredLength -= 6;

		//Parse the descriptors that belong to current elementary stream.
		if (( uiStoredLength < uiDescriptorsLoopLength))
		{
			/*Since the length is invalid, we have to reset the length here.*/
			pTreeNodeCurrentLoop->m_uiLength = ( 6 + uiStoredLength)*8;

			//Invalid End.
			uiFieldLength = uiStoredLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			uiOffset += uiFieldLength;

			//Move the pointer.
			pucData += uiStoredLength;
			uiStoredLength = 0;

			break;
		}
		else
		{
			// uiDescriptorsLoopLength is valid. 

			// stream_info_descriptors, it is a loop containing descriptors.
			uiFieldLength = uiDescriptorsLoopLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_descriptors loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);

			//Parse stream_info_descriptors loop.
			CDescriptor::LoopParse( pTSPacketStore,pTreeList,  pTreeNode, pucData, uiOffset, uiDescriptorsLoopLength);

			//Set uiOffset after descriptors loop.
			uiOffset += uiFieldLength;

			//Move the pointer.
			pucData += uiDescriptorsLoopLength;
			uiStoredLength -= uiDescriptorsLoopLength;
		}
	}

	if( 0 != uiStoredLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiStoredLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiStoredLength*8;

		pucData += uiStoredLength;
		uiStoredLength = 0;
		
	}
	return SUCCESS;
};
