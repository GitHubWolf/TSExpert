#include "StdAfx.h"
#include "SectionStorePAT.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"

CSectionStorePAT::CSectionStorePAT(UINT16 uwPid, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{

}

CSectionStorePAT::~CSectionStorePAT(void)
{
}


EResult CSectionStorePAT::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	EResult eResult;
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	if( TABLEID_PAT == CSectionHeaderReader::GetTableId(pucData))
	{
		eResult = StoreNewData(pTSPacketStore);
	}

	if( SUCCESS == eResult )
	{
		//If a new section was found, parse it immediately to get PMT PID.
		ParseForPMTPid(pTSPacketStore);
	}


	return eResult;
};

EResult CSectionStorePAT::ParseForPMTPid(CTSPacketStore * pTSPacketStore)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiSectionLength = CSectionHeaderReader::GetSectionLength(pucData);
	UINT32 uiTotalLength = pTSPacketStore->GetTotalLength();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();

	//Decrease 4 byte CRC.
	if( 4 <= uiStoredLength)
	{
		uiStoredLength -= 4;
	}
	
	if(  MIN_SECTION_HEADER_LENGTH > uiStoredLength )
	{
		return FAILURE;
	}

	UINT16 uwServiceId;
	UINT16 uwPid;

	pucData += 8;
	uiStoredLength -= 8;
	
	while( 4 <= uiStoredLength)
	{

		uwServiceId = ((pucData[0] << 8) | pucData[1] );
		uwPid = (((pucData[2] & 0x01F) << 8) | pucData[3]);

		//If uwServiceId is 0, then the PID is NIT PID, skip it.
		if( 0 != uwServiceId )
		{
			pair<IteratorServiceIdPid, BOOL> result;
			result = m_storeServiceIdPid.insert(make_pair(uwServiceId, uwPid));
			if( TRUE == result.second )
			{
				//NOTE:PMT PID may be the same or different for different service.
				CSectionStorePMT *pSectionStorePMT;
				pSectionStorePMT = new CSectionStorePMT(uwPid, uwServiceId, TABLE_NAME_PMT, m_pTSParser);								
				EResult vAttacheResult = m_pTSParser->AttachSectionObserver(uwPid, pSectionStorePMT);
                if(SUCCESS != vAttacheResult)
                {
                    TRACE("CSectionStorePAT Failed to attach section observer.uwPid 0x%x\n", uwPid);

                }

			}
            else
            {
                TRACE("CSectionStorePAT Failed to insert uwServiceId 0x%x, uwPid 0x%x\n", uwServiceId, uwPid);
            }

		}
		

		TRACE("uwServiceId 0x%04X, uwPid 0x%04X\r\n", uwServiceId, uwPid);
		uiStoredLength -= 4;
		pucData += 4;
	}
	return SUCCESS;
}

EResult CSectionStorePAT::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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

EResult CSectionStorePAT::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
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
	
	//Begin the loop.
	uiFieldLength = uiStoredLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"programs loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;
	
	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 4 <= uiStoredLength )
	{
		UINT16 uwProgramNumber;
		UCHAR8 ucReservedTemp;
		UINT16 uwPid;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffset, 4*8, VALUE_ZERO, NODE_LOOP_ITEM );		

		// 16 Bit program_number.
		uiFieldLength = 16;
		uwProgramNumber = ((pucData[0]<< 8 )| pucData[1]);
		CTreeNode *pTreeNodeProgramNumber  = new CTreeNode(pTSPacketStore, L"program_number", uiOffset, uiFieldLength, uwProgramNumber );
		uiOffset += uiFieldLength;

		// 3 Bit reserved.
		uiFieldLength = 3;
		ucReservedTemp = ((pucData[2]>> 5 ) & 0x7);
		CTreeNode * pTreeNodeReservedTemp  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, ucReservedTemp );
		uiOffset += uiFieldLength;

		// 13 Bit program_map_PID or network_PID.
		uiFieldLength = 13;
		uwPid = ((pucData[2] & 0x1F ) << 8) | (pucData[3] );
		CTreeNode * pTreeNodePid = NULL;
		if( 0 == uwProgramNumber)
		{
			pTreeNodePid  = new CTreeNode(pTSPacketStore, L"network_PID", uiOffset, uiFieldLength, uwPid );
		}
		else
		{
			pTreeNodePid  = new CTreeNode(pTSPacketStore, L"program_map_PID", uiOffset, uiFieldLength, uwPid );

			/*Set service type.*/
			m_pTSParser->SetPidType( uwPid, PID_TYPE_PMT);
		}

		uiOffset += uiFieldLength;



		// Begin to add to the tree control.
		if( 0 == uwProgramNumber)
		{
			pTreeNodeCurrentLoop->m_strText.Format(L"program_number: 0x%04X, network_PID: 0x%04X", uwProgramNumber, uwPid);
		}
		else
		{
			pTreeNodeCurrentLoop->m_strText.Format(L"program_number: 0x%04X, program_map_PID: 0x%04X", uwProgramNumber, uwPid);
		}

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeProgramNumber, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReservedTemp, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodePid, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 4;
		uiStoredLength -= 4;
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
