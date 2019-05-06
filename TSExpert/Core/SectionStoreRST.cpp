#include "StdAfx.h"
#include "SectionStoreRST.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"
#include "Descriptor.h"

CSectionStoreRST::CSectionStoreRST(UINT16 uwPid, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{
}

CSectionStoreRST::~CSectionStoreRST(void)
{
}


EResult CSectionStoreRST::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);
	if(TABLEID_RST == ucTableId)
	{
		return StoreNewData(pTSPacketStore);
	}

	return FAILURE;
};

EResult CSectionStoreRST::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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


	strDescription.Format(L"TableId 0x%02X", ucTableId);
	pTSPacketStore->GetDescription(strDescription);


	return SUCCESS;
};



EResult CSectionStoreRST::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
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

	if( 3 > uiStoredLength )
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


	// Subtract 8 Byte section header.
	uiStoredLength -= 3;
	pucData += 3;

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
	pTreeNode  = new CTreeNode(pTSPacketStore, L"events loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 9 <= uiStoredLength )
	{
		UINT32 uiTransportStreamId;
		UINT32 uiOriginalNetworkId;
		UINT32 uiServiceId;
		UINT32 uiEventId;
		UINT32 uiRuningStatus;

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


		// 16 Bit service_id.
		uiFieldLength = 16;
		uiData = ((pucData[4]<< 8 )| pucData[5]);
		CTreeNode *pTreeNodeServiceId  = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of service_id.
		uiServiceId = uiData;

		// 16 Bit event_id.
		uiFieldLength = 16;
		uiData = ((pucData[6]<< 8 )| pucData[7]);
		CTreeNode *pTreeNodeEventId  = new CTreeNode(pTSPacketStore, L"event_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of event_id.
		uiEventId = uiData;


		// 5 Bit reserved_future_use.
		uiFieldLength = 5;
		uiData = ((pucData[8] >> 3)& 0x1F );
		CTreeNode * pTreeNodeReservedTemp1  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;
		
		// 3 Bit running_status.
		uiFieldLength = 3;
		uiData = (pucData[8] & 0x7 );
		CTreeNode * pTreeNodeRunningStatus  = new CTreeNode(pTSPacketStore, L"running_status", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// Save the value of running_status.
		uiRuningStatus = uiData;
		
		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, 9*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"transport_stream_id:0x%04X ,original_network_id: 0x%04X, service_id: 0x%04X, event_id: 0x%04X, running_status: 0x%04X", uiTransportStreamId, uiOriginalNetworkId, uiServiceId, uiEventId, uiRuningStatus);

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeTransportStreamId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeOriginalNetworkId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeServiceId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeEventId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReservedTemp1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeRunningStatus, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 9;
		uiStoredLength -= 9;

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
