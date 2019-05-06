#include "StdAfx.h"
#include "SectionStoreSDT.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"
#include "Descriptor.h"

CSectionStoreSDT::CSectionStoreSDT(UINT16 uwPid, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{
}

CSectionStoreSDT::~CSectionStoreSDT(void)
{
}


EResult CSectionStoreSDT::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);
	if(( TABLEID_SDT_CURRENT == ucTableId) || ( TABLEID_SDT_OTHER == ucTableId))
	{
		return StoreNewData(pTSPacketStore);
	}

	return FAILURE;
};

EResult CSectionStoreSDT::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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

	strDescription.Format(L"TableId 0x%02X, TransportStreamId 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
		ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);
	pTSPacketStore->GetDescription(strDescription);


	return SUCCESS;
};


EResult CSectionStoreSDT::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
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


	// 16 Bit transport_stream_id.
	uiFieldLength = 16;
	uiData = ((pucData[3]<< 8 )| pucData[4]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData );
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
	if ( 3 > uiStoredLength )
	{
		//Invalid End.
		uiFieldLength = uiStoredLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 16 Bit original_network_id.
	uiFieldLength = 16;
	uiData = ((pucData[0]<< 8 )| pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit reserved_future_use.
	uiFieldLength = 8;
	uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiStoredLength -= 3;
	pucData += 3;


	//Begin the loop.
	uiFieldLength = uiStoredLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"service_descriptions loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 5 <= uiStoredLength )
	{
		UINT32 uiServiceId;
		UINT32 uiRunningStatus;
		UINT32 uiFreeCAMode;

		UINT32 uiDescriptorsLoopLength;

		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit service_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		CTreeNode *pTreeNodeServiceId = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of service_id.
		uiServiceId = uiData;

		// 6 Bit reserved_future_use.
		uiFieldLength = 6;
		uiData = ((pucData[2] >> 2 ) & 0x3F );
		CTreeNode *pTreeNodeReserved1  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 1 Bit EIT_schedule_flag.
		uiFieldLength = 1;
		uiData = ((pucData[2] >> 1)& 0x1 );
		CTreeNode * pTreeNodeScheduleFlag  = new CTreeNode(pTSPacketStore, L"EIT_schedule_flag", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;
		
		// 1 Bit EIT_present_following_flag.
		uiFieldLength = 1;
		uiData = (pucData[2] & 0x1 );
		CTreeNode * pTreeNodePFFlag = new CTreeNode(pTSPacketStore, L"EIT_present_following_flag", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 3 Bit running_status.
		uiFieldLength = 3;
		uiData = ((pucData[3] >> 5) & 0x7 );
		CTreeNode * pTreeNodeRunningStatus = new CTreeNode(pTSPacketStore, L"running_status", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		//Save the value of running_status.
		uiRunningStatus = uiData;

		// 1 Bit free_CA_mode.
		uiFieldLength = 1;
		uiData = ((pucData[3] >> 4) & 0x1 );
		CTreeNode * pTreeNodeFreeCAMode  = new CTreeNode(pTSPacketStore, L"free_CA_mode", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		//Save the value of free_CA_mode.
		uiFreeCAMode = uiData;

		// 12 Bit descriptors_loop_length.
		uiFieldLength = 12;
		uiData = (((pucData[3] &0xF) << 8) | pucData[4]);
		CTreeNode * pTreeNodeDescriptorsLength = new CTreeNode(pTSPacketStore, L"descriptors_loop_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the length of transport_descriptors_length.
		uiDescriptorsLoopLength = uiData;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 5 + uiDescriptorsLoopLength)*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"service_id:0x%04X ,running_status: 0x%02X, free_CA_mode: 0x%02X", uiServiceId, uiRunningStatus, uiFreeCAMode);

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeServiceId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReserved1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeScheduleFlag, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodePFFlag, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeRunningStatus, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeFreeCAMode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeDescriptorsLength, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 5;
		uiStoredLength -= 5;

		//Parse the descriptors that belong to current elementary stream.
		if (( uiStoredLength < uiDescriptorsLoopLength))
		{
			/*Since the length is invalid, we have to reset the length here.*/
			pTreeNodeCurrentLoop->m_uiLength = ( 5 + uiStoredLength)*8;

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

			// descriptors, it is a loop containing descriptors.
			uiFieldLength = uiDescriptorsLoopLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptors loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);

			//Parse descriptors loop.
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
