#include "StdAfx.h"
#include "SectionStorePrivate.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"

CSectionStorePrivate::CSectionStorePrivate(UINT16 uwPid, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{

}

CSectionStorePrivate::~CSectionStorePrivate(void)
{
}


EResult CSectionStorePrivate::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	EResult eResult = FAILURE;

	if( SUCCESS == IsMatched(pTSPacketStore))
	{
		eResult = StoreNewData(pTSPacketStore);
	}

	return eResult;
};

EResult CSectionStorePrivate::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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

	strDescription.Format(L"TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
		ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};


EResult CSectionStorePrivate::GetDescription(CTSPacketStore * pTSPacketStore, const UCHAR8 *pucData, CString& strDescription)
{
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);
	UINT16 uwTableIdExtension = CSectionHeaderReader::GetTableIdExtension(pucData);
	UCHAR8 ucVersionNumber = CSectionHeaderReader::GetVersionNumber(pucData);
	UCHAR8 ucSectionNumber = CSectionHeaderReader::GetSectionNumber(pucData);
	UCHAR8 ucLastSectionNumber = CSectionHeaderReader::GetLastSectionNumber(pucData);

	strDescription.Format(L"TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
		ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};

EResult CSectionStorePrivate::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
{
	/*
	**CSectionObserver::DisplaySectionData(pTSPacketStore,pTreeList, pTreeNodeInput, pTreeNodeParent);
	*/

	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiOffset = 0;

	const UINT32 uiStoredLengthConst = uiStoredLength;
	const UCHAR8 * const pucDataConst = pucData;


	UINT32 uiData;
	UINT32 uiFieldLength;

	while(  0 < uiStoredLength )
	{
		if( MIN_SECTION_HEADER_LENGTH > uiStoredLength )
		{
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid section header", uiOffset, uiStoredLength*8, VALUE_ZERO, NODE_SECTION);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
			return FAILURE;
		}

		UINT32 uiSectionLength = CSectionHeaderReader::GetSectionLength(pucData);
		CTreeNode * pTreeNodeCurrentLoop = new CTreeNode(pTSPacketStore, L"", uiOffset, (uiSectionLength + 3)*8, VALUE_ZERO, NODE_SECTION);
		GetDescription(pTSPacketStore, pucData, pTreeNodeCurrentLoop->m_strText );
		pTreeList->AppendLastChild( pTreeNodeCurrentLoop, pTreeNodeInput);
		
		// 8 Bit tabld_id.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"table_id", uiOffset, uiFieldLength, uiData );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);	
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
		pTreeNode  = new CTreeNode(pTSPacketStore, L"section_length", uiOffset, uiFieldLength, uiData );	
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		
		// 16 Bit table_id_extension.
		uiFieldLength = 16;
		uiData = ((pucData[3]<< 8 )| pucData[4]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"table_id_extension", uiOffset, uiFieldLength, uiData );
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

		if(( 5 <= uiSectionLength ) && ( (uiStoredLength + 8) >= (uiSectionLength + 3)))
		{
			uiSectionLength -= 5;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_byte", uiOffset, uiSectionLength*8, VALUE_ZERO, NODE_DATA_BYTE );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiSectionLength*8;
			pucData += uiSectionLength;
			uiStoredLength -= uiSectionLength;
		}
		else
		{
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiStoredLength*8, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiStoredLength*8;
			pucData += uiStoredLength;
			uiStoredLength = 0;

			return FAILURE;
		}

		if( 1 <= uiStoredLength )
		{
			if( 0xFF == pucData[0] )
			{
				break;
			}
		}
		
	}

	return SUCCESS;
};

EResult CSectionStorePrivate::SetFilter(UCHAR8 const *pucMask, UCHAR8 const *pucMatch,UINT32 uiFilterLength)
{
	if( MAX_FILTER_LENGTH < uiFilterLength )
	{
		return FAILURE;
	}

	/*Copy mask and match.*/
	memcpy(m_arrayMask, pucMask, uiFilterLength);
	memcpy(m_arrayMatch, pucMatch, uiFilterLength);
	m_uiFilterLength = uiFilterLength;

	return SUCCESS;
}

EResult CSectionStorePrivate::IsMatched(CTSPacketStore * pTSPacketStore)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	const UCHAR8 *pucMask = m_arrayMask;
	const UCHAR8 *pucMatch = m_arrayMatch;

	UINT32 uiLength = min(uiStoredLength, m_uiFilterLength);

	if( 0 == uiLength )
	{
		return FAILURE;
	}

	for(UINT32 i = 0; i < uiLength; i++)
	{
		if( ( pucMask[i] & pucData[i]) != ( pucMask[i] & pucMatch[i]))
		{
			return FAILURE;
		}
	}

	return SUCCESS;
};


EResult CSectionStorePrivate::StoreNewData(CTSPacketStore * pTSPacketStoreIn)
{
	IteratorTSPacketStore iteratorTSPacketStore;

	m_uiCount++;
	for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
	{
		CTSPacketStore * pTSPacketStoreTo = *iteratorTSPacketStore;
		if (SUCCESS == pTSPacketStoreTo->Match(pTSPacketStoreIn, m_uiMatchLength))
		{
			return FAILURE;
		}
	}

	m_storeTSPacketStore.insert(pTSPacketStoreIn);

	//Send a message to the UI to show the message.
	TMsgNewSection *pMsg = new TMsgNewSection;
	pMsg->pSectionObserver = this;
	pMsg->pTSPacketStore = pTSPacketStoreIn;
	if(SUCCESS != m_pTSParser->SendMsgToView(MESSAGE_NEW_SEARCHED_SECTION, (pMsg) ))
	{
		delete pMsg;
	}


	/*Increase saved count, so that the search will quit once it reaches the limit.*/
	m_pTSParser->IncementSavedCount(1);
	return SUCCESS;
};

