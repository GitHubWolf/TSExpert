#include "StdAfx.h"
#include "SectionStorePMT.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"
#include "Descriptor.h"

CSectionStorePMT::CSectionStorePMT(UINT16 uwPid,  UINT16 uwServiceId, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{
	m_uwServiceId = uwServiceId;
}

CSectionStorePMT::~CSectionStorePMT(void)
{
}


EResult CSectionStorePMT::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);
	EResult eResult = FAILURE;
	if( TABLEID_PMT == ucTableId)
	{
		UINT16 uwServiceId = ((pucData[3] << 8) | pucData[4]);
		if( m_uwServiceId == uwServiceId )
		{
			eResult = StoreNewData(pTSPacketStore);
		}
	}

	return eResult;
};

EResult CSectionStorePMT::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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

	strDescription.Format(L"TableId 0x%02X, ProgramNumber 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
		ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};


EResult CSectionStorePMT::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
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

	
	

	// 1 Bit '0'.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"'0'", uiOffset, uiFieldLength, uiData );
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


	// 16 Bit program_number.
	uiFieldLength = 16;
	uiData = ((pucData[3]<< 8 )| pucData[4]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"program_number", uiOffset, uiFieldLength, uiData );
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

	// 3 Bit reserved.
	uiFieldLength = 3;
	uiData = ((pucData[0] >> 5)&0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 13 Bit PCR_PID.
	uiFieldLength = 13;
	uiData = (((pucData[0] &0x1F) << 8) | pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PCR_PID", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*Set PCR_PID type.*/
	m_pTSParser->SetPidType( uiData, PID_TYPE_PCR);

	uiStoredLength -= 2;
	pucData += 2;

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

	// 4 Bit reserved.
	uiFieldLength = 4;
	uiData = ((pucData[0] >> 4)&0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 12 Bit program_info_length.
	uiFieldLength = 12;
	uiData = (((pucData[0] &0xF) << 8) | pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"program_info_length", uiOffset, uiFieldLength, uiData );
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
	}
	else
	{
		// uiDescriptorsLoopLength is valid. 

		// program_info_descriptors, it is a loop containing descriptors.
		uiFieldLength = uiDescriptorsLoopLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"program_info_descriptors loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		//Parse program_info_descriptors loop.
		CDescriptor::LoopParse( pTSPacketStore,pTreeList,  pTreeNode, pucData, uiOffset, uiDescriptorsLoopLength);

		//Set uiOffset after descriptors loop.
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += uiDescriptorsLoopLength;
		uiStoredLength -= uiDescriptorsLoopLength;

	}

	//Begin the loop.
	uiFieldLength = uiStoredLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"streams loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 5 <= uiStoredLength )
	{
		UCHAR8 ucStreamType;
		UINT16 uwPid;
		UINT32 uiDescriptorsLoopLength;

		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 8 Bit stream_type.
		uiFieldLength = 8;
		ucStreamType = pucData[0];
		CTreeNode *pTreeNodeStreamType  = new CTreeNode(pTSPacketStore, L"stream_type", uiOffset, uiFieldLength, ucStreamType );
		uiOffset += uiFieldLength;

		// 3 Bit reserved.
		uiFieldLength = 3;
		uiData = ((pucData[1]>> 5 ) & 0x7);
		CTreeNode * pTreeNodeReservedTemp1  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 13 Bit elementary_PID.
		uiFieldLength = 13;
		uwPid = ((pucData[1] & 0x1F ) << 8) | (pucData[2] );
		CTreeNode * pTreeNodePid  = new CTreeNode(pTSPacketStore, L"elementary_PID", uiOffset, uiFieldLength, uwPid );
		uiOffset += uiFieldLength;

		/*Set service type.*/
		m_pTSParser->SetPidType( uwPid, CDescriptor::StreamTypeToPidType(ucStreamType));

		// 4 Bit reserved.
		uiFieldLength = 4;
		uiData = ((pucData[3] >> 4)& 0xF );
		CTreeNode * pTreeNodeReservedTemp2  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;
		
		// 12 Bit ES_info_length.
		uiFieldLength = 12;
		uiData = ((pucData[3] & 0xF ) << 8) | (pucData[4]);
		CTreeNode * pTreeNodeESInfoLength  = new CTreeNode(pTSPacketStore, L"ES_info_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the length of ES_info.
		uiDescriptorsLoopLength = uiData;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 5 + uiDescriptorsLoopLength)*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"Pid: 0x%04X, Type:%s", uwPid, CDescriptor::GetStreamTypeName(ucStreamType));

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeStreamType, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReservedTemp1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodePid, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReservedTemp2, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeESInfoLength, pTreeNodeCurrentLoop);

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

			// stream_info_descriptors, it is a loop containing descriptors.
			uiFieldLength = uiDescriptorsLoopLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"stream_info_descriptors loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
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
