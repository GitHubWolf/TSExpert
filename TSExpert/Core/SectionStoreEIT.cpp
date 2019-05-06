#include "StdAfx.h"
#include "SectionStoreEIT.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"
#include "Descriptor.h"

CSectionStoreEIT::CSectionStoreEIT(UINT16 uwPid, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{
}

CSectionStoreEIT::~CSectionStoreEIT(void)
{
}


EResult CSectionStoreEIT::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);

	if((TABLEID_EIT_PF_CURRENT == ucTableId) 
		|| (TABLEID_EIT_PF_OTHER == ucTableId)  
		|| (TABLEID_EIT_SCHEDULE_CURRENT == (ucTableId&0xF0)) 
		|| (TABLEID_EIT_SCHEDULE_OTHER == (ucTableId&0xF0)))
	{
		return StoreNewData(pTSPacketStore);
	}

	return FAILURE;
};

EResult CSectionStoreEIT::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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

	strDescription.Format(L"TableId 0x%02X, ServiceId 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
		ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};


EResult CSectionStoreEIT::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
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


	// 16 Bit service_id.
	uiFieldLength = 16;
	uiData = ((pucData[3]<< 8 )| pucData[4]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData );
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
	
	if( 6 > uiStoredLength)
	{
		//Invalid End.
		uiFieldLength = uiStoredLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiStoredLength -= uiStoredLength;
		pucData += uiStoredLength;
		return FAILURE;
	}


	// 16 Bit transport_stream_id.
	uiFieldLength = 16;
	uiData = ((pucData[0]<< 8 )| pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 16 Bit original_network_id.
	uiFieldLength = 16;
	uiData = ((pucData[2]<< 8 )| pucData[3]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit segment_last_section_number.
	uiFieldLength = 8;
	uiData = pucData[4];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"segment_last_section_number", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit last_table_id.
	uiFieldLength = 8;
	uiData = pucData[5];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"last_table_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiStoredLength -= 6;
	pucData += 6;


	//Begin the loop.
	uiFieldLength = uiStoredLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"events loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 12 <= uiStoredLength )
	{
		UINT32 uiEventId;
		UINT32 uiMJD;
		UINT32 uiUTC;
		UINT32 uiDuration;

		UINT32 uiDescriptorsLoopLength = uiStoredLength;

		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit event_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		CTreeNode *pTreeNodeEventId  = new CTreeNode(pTSPacketStore, L"event_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of event_id.
		uiEventId = uiData;

		// 16 Bit MJD.
		uiFieldLength = 16;
		uiData = ((pucData[2]<< 8 )| pucData[3]);
		CTreeNode *pTreeNodeMJD  = new CTreeNode(pTSPacketStore, L"MJD", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of MJD.
		uiMJD = uiData;

		// 24 Bit UTC.
		uiFieldLength = 24;
		uiData = ((pucData[4]<< 16 )| (pucData[5]<< 8 )| pucData[6]);
		CTreeNode *pTreeNodeUTC = new CTreeNode(pTSPacketStore, L"UTC", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of UTC.
		uiUTC = uiData;

		// 24 Bit duration.
		uiFieldLength = 24;
		uiData = ((pucData[7]<< 16 )| (pucData[8]<< 8 )| pucData[9]);
		CTreeNode *pTreeNodeDuration = new CTreeNode(pTSPacketStore, L"duration", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of duration.
		uiDuration = uiData;

		// 3 Bit running_status.
		uiFieldLength = 3;
		uiData = ((pucData[10] >> 5)& 0x7 );
		CTreeNode * pTreeNodeRunningStatus  = new CTreeNode(pTSPacketStore, L"running_status", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;
		
		// 1 Bit free_CA_mode.
		uiFieldLength = 1;
		uiData = ((pucData[10] >> 4)& 0x1 );
		CTreeNode * pTreeNodeFreeCAMode  = new CTreeNode(pTSPacketStore, L"free_CA_mode", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 12 Bit descriptors_loop_length.
		uiFieldLength = 12;
		uiData = ((pucData[10] & 0xF ) << 8) | (pucData[11]);
		CTreeNode * pTreeNodeDescriptorsLoopLength  = new CTreeNode(pTSPacketStore, L"descriptors_loop_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the length of descriptors_loop_length.
		uiDescriptorsLoopLength = uiData;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 12 + uiDescriptorsLoopLength)*8, VALUE_ZERO, NODE_LOOP_ITEM );
		UINT32 uiYear, uiMonth, uiDay;
		CDescriptor::MjdToYmd(uiMJD, uiYear, uiMonth, uiDay);
		pTreeNodeCurrentLoop->m_strText.Format(L"event_id:0x%04X ,date: %04d/%02d/%02d ,time: %02X:%02X:%02X ,duration: %02X:%02X:%02X",
			uiEventId, uiYear, uiMonth, uiDay, pucData[4], pucData[5],pucData[6], pucData[7],pucData[8],pucData[9]);

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeEventId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeMJD, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeUTC, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeDuration, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeRunningStatus, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeFreeCAMode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeDescriptorsLoopLength, pTreeNodeCurrentLoop);


		//Move the pointer.
		pucData += 12;
		uiStoredLength -= 12;

		//Parse the descriptors that belong to current elementary stream.
		if (( uiStoredLength < uiDescriptorsLoopLength))
		{
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
			pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptors loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
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
