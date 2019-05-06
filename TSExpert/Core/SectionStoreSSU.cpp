#include "StdAfx.h"
#include "SectionStoreSSU.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"
#include "TSExpert.h"


CSectionStoreSSU::CSectionStoreSSU(UINT16 uwPid, string sName, CTSParser *pTSParser):CSectionObserver(uwPid, sName, pTSParser)
{
    mDSISectionCount = 0; 
    mDIISectionCount = 0; 
    mDDBSectionCount = 0; 

}

CSectionStoreSSU::~CSectionStoreSSU(void)
{
}


EResult CSectionStoreSSU::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	EResult eResult = FAILURE;

    if(GetShowAllSSUFlag())
    {
        /*Always store it.*/
        eResult = StoreNewData(pTSPacketStore);
    }
    else
    {
        if( SUCCESS == IsMatched(pTSPacketStore))
        {
            eResult = StoreNewData(pTSPacketStore);
        }
    }

	return eResult;
};

EResult CSectionStoreSSU::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
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

    if((TABLEID_DSI == ucTableId) || (TABLEID_DII == ucTableId))
    {
       /*DSI or DII.*/

        if(0x01 >= uwTableIdExtension )
        {
            /*Table ID Extension for DSI shall be 0x0 or 0x01.*/
            strDescription.Format(L"DSI: TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
                ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

        }
        else
        {
            /*Otherwise, it is a DII message.*/
            strDescription.Format(L"DII: TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
                ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

        }
    }
    else if(TABLEID_DDB == ucTableId)
    {
        /*DDB.*/
        strDescription.Format(L"DDB: TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
            ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

    }
    else
    {
        strDescription.Format(L"TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
            ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

    }
	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};


EResult CSectionStoreSSU::GetDescription(CTSPacketStore * pTSPacketStore, const UCHAR8 *pucData, CString& strDescription)
{
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId(pucData);
	UINT16 uwTableIdExtension = CSectionHeaderReader::GetTableIdExtension(pucData);
	UCHAR8 ucVersionNumber = CSectionHeaderReader::GetVersionNumber(pucData);
	UCHAR8 ucSectionNumber = CSectionHeaderReader::GetSectionNumber(pucData);
	UCHAR8 ucLastSectionNumber = CSectionHeaderReader::GetLastSectionNumber(pucData);

    if((TABLEID_DSI == ucTableId) || (TABLEID_DII == ucTableId))
    {
       /*DSI or DII.*/

        if(0x01 >= uwTableIdExtension )
        {
            /*Table ID Extension for DSI shall be 0x0 or 0x01.*/
            strDescription.Format(L"DSI: TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
                ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

        }
        else
        {
            /*Otherwise, it is a DII message.*/
            strDescription.Format(L"DII: TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
                ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

        }
    }
    else if(TABLEID_DDB == ucTableId)
    {
        /*DDB.*/
        strDescription.Format(L"DDB: TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
            ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

    }
    else
    {
        strDescription.Format(L"TableId 0x%02X, TableIdExtension 0x%04X, Version 0x%02X, SectionNumber 0x%02X, LastSectionNumber 0x%02X", 
            ucTableId, uwTableIdExtension, ucVersionNumber, ucSectionNumber, ucLastSectionNumber);

    }

	pTSPacketStore->GetDescription(strDescription);

	return SUCCESS;
};

EResult CSectionStoreSSU::DisplaySectionData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,  CTreeNode * pTreeNodeParent)
{
	/*
	**CSectionObserver::DisplaySectionData(pTSPacketStore,pTreeList, pTreeNodeInput, pTreeNodeParent);
	*/

	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiOffset = 0;
	UCHAR8 ucTableId = 0;
	UINT16 uwTableIdExtension = 0;
	UCHAR8 ucSectionIndicator = 0;

	const UINT32 uiStoredLengthConst = uiStoredLength;
	const UCHAR8 * const pucDataConst = pucData;


	UINT32 uiData;
	UINT32 uiFieldLength;

	while(  (MIN_SECTION_HEADER_LENGTH + 4) <= uiStoredLength )
	{
	    /*8 bytes DVB section header and 4 bytes CRC32 or checksum.*/
		if( (MIN_SECTION_HEADER_LENGTH + 4) > uiStoredLength )
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
		ucTableId = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"table_id", uiOffset, uiFieldLength, uiData );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);	
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 1 Bit section_syntax_indicator.
		uiFieldLength = 1;
		uiData = ((pucData[1] >> 7) & 0x1);
		ucSectionIndicator = (UCHAR8)uiData;
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
		uwTableIdExtension = (UINT16)uiData;
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

        if( ucSectionIndicator )  /*Parse CRC32  in advance.*/  
        {
            // 32 Bit CRC_32.
            uiFieldLength = 32;
            uiData = ((pucDataConst[uiSectionLength -4]<< 24 ) 
                | (pucDataConst[uiSectionLength -3]<< 16 ) 
                | (pucDataConst[uiSectionLength -2]<< 8 )
                | pucDataConst[uiSectionLength -1]);
        
            /*Check CRC32.*/
            UINT32 uiCRC32 = GenerateCRC32(pucDataConst, uiSectionLength + 3);
            if( 0 != uiCRC32 )
            {
                pTreeNode  = new CTreeNode(pTSPacketStore, L"CRC_32", uiOffset + (uiSectionLength - 5 - 4)*8, uiFieldLength, uiData, NODE_WARNING );
                pTreeNode->m_strText.Format(L"CRC_32[%d]: 0x%08X (CRC32 ERROR or length ERROR)", uiFieldLength, uiData);
            }
            else
            {
                pTreeNode  = new CTreeNode(pTSPacketStore, L"CRC_32", uiOffset + (uiSectionLength - 5 - 4)*8, uiFieldLength, uiData );
            }
            
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        
            uiStoredLength -= 4;
        }
        else
        {
            // 32 Bit Checksum.
            uiFieldLength = 32;
            uiData = ((pucDataConst[uiSectionLength -4]<< 24 ) 
                | (pucDataConst[uiSectionLength -3]<< 16 ) 
                | (pucDataConst[uiSectionLength -2]<< 8 )
                | pucDataConst[uiSectionLength -1]);
        
            pTreeNode  = new CTreeNode(pTSPacketStore, L"Checksum", uiOffset + (uiSectionLength - 5 - 4)*8, uiFieldLength, uiData );
        
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        
            uiStoredLength -= 4;
        }


		if(( 5 <= uiSectionLength ) && ( (uiStoredLength + 8 + 4) >= (uiSectionLength + 3)))
		{
            if((TABLEID_DSI == ucTableId) || (TABLEID_DII == ucTableId))
            {
               /*DSI or DII.*/
            
                if(0x01 >= uwTableIdExtension )
                {
                    /*Parse DSI.*/
                    pTreeNode  = new CTreeNode(pTSPacketStore, L"DSI", uiOffset, (uiSectionLength - 5 - 4)*8, VALUE_ZERO, NODE_LOOP ); /*Exclude 5 bytes header and 4 bytes CRC.*/
                    pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                    ParseDSI(pTSPacketStore, pTreeList, pTreeNode, pucData, uiOffset, (uiSectionLength - 5 - 4));
                }
                else
                {
                    /*Parse DII.*/
                    pTreeNode  = new CTreeNode(pTSPacketStore, L"DII", uiOffset, (uiSectionLength - 5 - 4)*8, VALUE_ZERO, NODE_LOOP );
                    pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                    ParseDII(pTSPacketStore, pTreeList, pTreeNode, pucData, uiOffset, (uiSectionLength - 5 - 4));
                }
            }
            else if(TABLEID_DDB == ucTableId)
            {
                /*Parse DDB.*/
                pTreeNode  = new CTreeNode(pTSPacketStore, L"DDB", uiOffset, (uiSectionLength - 5 - 4)*8, VALUE_ZERO, NODE_LOOP );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                ParseDDB(pTSPacketStore, pTreeList, pTreeNode, pucData, uiOffset, (uiSectionLength - 5 - 4));
            }
            else
            {
                /*Unknown.*/
                pTreeNode  = new CTreeNode(pTSPacketStore, L"Unknown", uiOffset, (uiSectionLength - 5 - 4)*8, VALUE_ZERO, NODE_DATA_BYTE ); /*Everything after last_section_number, not including CRC.*/
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            }

            pTreeNodeTmp = pTreeNode;
            uiOffset += (uiSectionLength - 5)*8; /*Offset for 5 bytes header has been subtracted.*/
            pucData += uiSectionLength;          /*section length contains 4 bytes CRC.*/
            uiStoredLength -= (uiSectionLength - 5 - 4);


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

EResult CSectionStoreSSU::SetFilter(UCHAR8 const *pucMask, UCHAR8 const *pucMatch,UINT32 uiFilterLength)
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

EResult CSectionStoreSSU::IsMatched(CTSPacketStore * pTSPacketStore)
{
    if(GetShowAllSSUFlag())
    {
        /*Always unmatched in order to save all of them.*/
        return SUCCESS;
    }
    else
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
    }
}


EResult CSectionStoreSSU::StoreNewData(CTSPacketStore * pTSPacketStoreIn)
{
	IteratorTSPacketStore iteratorTSPacketStore;

	m_uiCount++;

    if(!GetShowAllSSUFlag())
    {
        /*No need to show each section. Let's have a comparison first.*/
        for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
        {
            CTSPacketStore * pTSPacketStoreTo = *iteratorTSPacketStore;
            if (SUCCESS == pTSPacketStoreTo->Match(pTSPacketStoreIn, m_uiMatchLength))
            {
                return FAILURE;
            }
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
}

EResult CSectionStoreSSU::ParseDDB(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiFieldLength = 0;

	UINT32 uiAdaptionLength = 0;

	UINT32 headerLength = 0;

	// N bytes dsmccMessageHeader.
	pTreeNode  = new CTreeNode(pTSPacketStore, L"dsmccDownloadDataHeader", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;

    /*--------------------------------------Key point---------------------------------------------------*/
    /*Parse DsmccMessageHeader.*/
	ParseDsmccMessageHeader(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,uiMessageLength, 1, &headerLength);

	//Update length since we can know it now.
	pTreeNodeTmp->m_uiLength = headerLength*8;

    uiOffset += headerLength*8;
    pucData += headerLength;
    uiMessageLength -= headerLength;

	// N bytes DSMCC download data payload.
    uiFieldLength = uiMessageLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"dsmccMessagePayload", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;

    /*--------------------------------------Key point---------------------------------------------------*/
	ParseDDBPayload(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,uiMessageLength);

	uiOffset += uiFieldLength;

	return SUCCESS;
}

EResult CSectionStoreSSU::ParseDSI(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiFieldLength = 0;

	UINT32 uiAdaptionLength = 0;

	UINT32 headerLength = 0;

    if(GetShowAllSSUFlag())
    {
        CString logMessage;
        logMessage.Format(L"-----------------------------------------------------------------------DSI count %10u\r\n", mDSISectionCount++);
        WriteLog(logMessage);

    }

	// N bytes dsmccMessageHeader.
	pTreeNode  = new CTreeNode(pTSPacketStore, L"dsmccDownloadDataHeader", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;

    /*--------------------------------------Key point---------------------------------------------------*/
    /*Parse DsmccMessageHeader.*/
	ParseDsmccMessageHeader(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,uiMessageLength, 0, &headerLength);

	//Update length since we can know it now.
	pTreeNodeTmp->m_uiLength = headerLength*8;

    uiOffset += headerLength*8;
    pucData += headerLength;
    uiMessageLength -= headerLength;

	// N bytes DSMCC download data payload.
    uiFieldLength = uiMessageLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"dsmccMessagePayload", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;

    /*--------------------------------------Key point---------------------------------------------------*/
	ParseDSIPayload(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,uiMessageLength);

	uiOffset += uiFieldLength;

	return SUCCESS;
}


EResult CSectionStoreSSU::ParseDII(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength)
{

	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiFieldLength = 0;

	UINT32 uiAdaptionLength = 0;

	UINT32 headerLength = 0;

	// N bytes dsmccMessageHeader.
	pTreeNode  = new CTreeNode(pTSPacketStore, L"dsmccDownloadDataHeader", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;

    /*--------------------------------------Key point---------------------------------------------------*/
    /*Parse DsmccMessageHeader.*/
	ParseDsmccMessageHeader(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,uiMessageLength, 0, &headerLength);

	//Update length since we can know it now.
	pTreeNodeTmp->m_uiLength = headerLength*8;

    uiOffset += headerLength*8;
    pucData += headerLength;
    uiMessageLength -= headerLength;

	// N bytes DSMCC download data payload.
    uiFieldLength = uiMessageLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"dsmccMessagePayload", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;

    /*--------------------------------------Key point---------------------------------------------------*/
	ParseDIIPayload(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,uiMessageLength);

	uiOffset += uiFieldLength;

	return SUCCESS;
}

EResult CSectionStoreSSU::ParseDsmccMessageHeader(
                        CTSPacketStore * pTSPacketStore,
                        CTreeList *pTreeList,
                        CTreeNode * pTreeNodeInput,
                        const UCHAR8 *pucData,
                        UINT32 uiOffset,
                        UINT32 uiMessageLengthInput,
                        UINT32 isDDBHeader,
                        UINT32 *pHeaderLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UINT32 uiMessageLength = uiMessageLengthInput;

	UINT32 uiAdaptionLength = 0;
	EResult result = SUCCESS;

    if(uiMessageLength < 12)
    {
        /*DSMCC header is at least 12 bytes.*/
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidDsmccMessageHeader", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }

    if(SUCCESS == result)
    {
        // 8 Bit protocolDiscriminator.
        uiFieldLength = 8;
        uiData = pucData[0];
        pTreeNode  = new CTreeNode(pTSPacketStore, L"protocolDiscriminator", uiOffset, uiFieldLength, uiData );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        // 8 Bit dsmccType.
        uiFieldLength = 8;
        uiData = pucData[1];
        pTreeNode  = new CTreeNode(pTSPacketStore, L"dsmccType", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        
        // 16 Bit dsmccType.
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[2] << 8) | pucData[3]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"messageId", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        
        // 32 Bit transactionId.
        uiFieldLength = 32;
        uiData = (UINT32)( (pucData[4] << 24) | (pucData[5] << 16) | (pucData[6] << 8) | pucData[7]);
        if(isDDBHeader)
        {
            pTreeNode  = new CTreeNode(pTSPacketStore, L"downloadId", uiOffset, uiFieldLength, uiData );
        }
        else
        {
            pTreeNode  = new CTreeNode(pTSPacketStore, L"transactionId", uiOffset, uiFieldLength, uiData );
        }
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        
        
        // 8 Bit reserved.
        uiFieldLength = 8;
        uiData = pucData[8];
        pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        
        // 8 Bit adaptationLength.
        uiFieldLength = 8;
        uiData = pucData[9];
        pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptationLength", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        
        // 16 Bit messageLength.
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[10] << 8) | pucData[11]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"messageLength", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        uiMessageLength -= 12;
        pucData += 12;
    
    }

    if(SUCCESS == result)
    {
        if(uiAdaptionLength > 0)
        {
            if( uiAdaptionLength <= uiMessageLength)
            {
                uiFieldLength = 8;
                uiData = (UINT32)(pucData[0]);
                pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptationType", uiOffset, uiFieldLength, uiData );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
                
                uiFieldLength = (uiAdaptionLength - 1)*8;
                pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptationDataByte", uiOffset, uiFieldLength, uiData, NODE_DATA_BYTE );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
                
                uiMessageLength -= uiAdaptionLength;
                pucData += uiAdaptionLength;
            }
            else
            {
                result = FAILURE;
                
                // Unknown data.
                uiFieldLength = 8*uiMessageLength;
                pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
                
                uiMessageLength = 0;
            }        
        }
    }
    

    if(SUCCESS == result)
    {
        *pHeaderLength = (uiAdaptionLength + 12);
    }
    else
    {
        *pHeaderLength = uiMessageLengthInput;
    }

	return result;
}

EResult CSectionStoreSSU::ParseDDBPayload(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	EResult result = SUCCESS;

    if(uiMessageLength < 6)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }


    if(SUCCESS == result)
    {
        UINT32 moduleId = 0;
        UINT32 blockNumber = 0;

        // 16 Bit moduleId.
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"moduleId", uiOffset, uiFieldLength, uiData );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        moduleId = uiData;
        
        // 8 Bit moduleVersion.
        uiFieldLength = 8;
        uiData = pucData[2];
        pTreeNode  = new CTreeNode(pTSPacketStore, L"moduleVersion", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        // 8 Bit reserved.
        uiFieldLength = 8;
        uiData = pucData[3];
        pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        // 16 Bit blockNumber.
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[4] << 8) | pucData[5]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"blockNumber", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        blockNumber = uiData;

        if(GetShowAllSSUFlag())
        {
            CString logMessage;
            logMessage.Format(L"----DDB count %10u, moduleId %10u, blockNumber %10u\r\n", mDDBSectionCount++, moduleId, blockNumber);
            WriteLog(logMessage);
        }
        
        uiMessageLength -= 6;
        pucData += 6;
    }

    if(SUCCESS == result)
    {
        uiFieldLength = uiMessageLength*8;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"blockDataByte", uiOffset, uiFieldLength, uiData, NODE_DATA_BYTE );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;
    }

    if(uiMessageLength)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;
    }


	return result;
}


EResult CSectionStoreSSU::ParseDSIPayload(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	CTreeNode * pTreeNodeGroups = NULL;
	CTreeNode * pTreeNodeEachGroup = NULL;
	UINT32 uiData = 0;
	UINT32 uiFieldLength;
	UINT32 compatibilityDescriptorLength = 0;
	UINT32 currentGroupLength = 0;
	UINT32 totalGroupLength = 0;
	EResult result = SUCCESS;
	UINT32 privateDataLength = 0;
	UINT32 numberOfGroups = 0;
	UINT32 i = 0;

    if(uiMessageLength < 22)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }

    if(SUCCESS == result)
    {
        // 20 bytes serverId.
        uiFieldLength = 8*20;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"serverId", uiOffset, uiFieldLength, uiData, NODE_DATA_BYTE );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        uiMessageLength -= 20;
        pucData += 20;

    	// 16 Bit CompatibilityDescriptorLength .
    	uiFieldLength = 16;
    	uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
    	pTreeNode  = new CTreeNode(pTSPacketStore, L"CompatibilityDescriptorLength ", uiOffset, uiFieldLength, uiData );
    	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
    	pTreeNodeTmp = pTreeNode;
    	uiOffset += uiFieldLength;

        compatibilityDescriptorLength = uiData;

        uiMessageLength -= 2;
        pucData += 2;
    }

    if(SUCCESS == result)
    {
        /*Check compatibilityDescriptorLength.*/

        if(uiMessageLength < compatibilityDescriptorLength)
        {
            result = FAILURE;
        
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength = 0;
        
        }

    }

    if(SUCCESS == result)
    {
        if(compatibilityDescriptorLength)
        {
            uiFieldLength = compatibilityDescriptorLength*8;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"CompatibilityDescriptor", uiOffset, uiFieldLength, uiData, NODE_LOOP );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
        
            /*---------------------------Key point-------------------------------------------------------------*/
            ParseCompatibilityDescriptor(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,compatibilityDescriptorLength);
        
            uiOffset += uiFieldLength;
        
            uiMessageLength -= compatibilityDescriptorLength;
            pucData += compatibilityDescriptorLength;
        
        }
    }

    if(SUCCESS == result)
    {
        /*Check privateDataLength.*/

        if(2 > uiMessageLength)
        {
            result = FAILURE;
        
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength = 0;
        }
    }

    if(SUCCESS == result)
    {
        // 16 Bit privateDataLength
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"privateDataLength", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        privateDataLength = uiData;

        uiMessageLength -= 2;
        pucData += 2;

    }


    if( (SUCCESS == result) && ( privateDataLength ))
    {
        /*Check NumberOfGroups.*/
        if(2 > uiMessageLength)
        {
            result = FAILURE;
        
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength = 0;
        }

        
        if(SUCCESS == result)
        {
            // 16 Bit NumberOfGroups
            uiFieldLength = 16;
            uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"NumberOfGroups", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;

            numberOfGroups = uiData;
#if 0
            if(0 == numberOfGroups)
            {
                numberOfGroups = 1;
            }
#endif
            uiMessageLength -= 2;
            pucData += 2;
        
        }
        
        if((SUCCESS == result) && (0 != uiMessageLength))
        {
            //uiFieldLength = uiMessageLength*8; /*To be updated later.*/
            pTreeNode  = new CTreeNode(pTSPacketStore, L"Groups", uiOffset, uiFieldLength, uiData, NODE_LOOP );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
        
            pTreeNodeGroups = pTreeNodeTmp;

            for(i = 0; i < numberOfGroups; ++i)
            {
                currentGroupLength = 0;
                
                pTreeNode  = new CTreeNode(pTSPacketStore, L"", uiOffset, 0, uiData, NODE_LOOP_ITEM ); /*Field length will be updated later.*/
                pTreeNode->m_strText.Format(L"Group Info %d", i);
                pTreeList->AppendLastChild( pTreeNode, pTreeNodeGroups);
                pTreeNodeTmp = pTreeNode;
        
                /*Save it.*/
                pTreeNodeEachGroup = pTreeNodeTmp;
        
                /*---------------------------Key point-------------------------------------------------------------*/
                ParseGroupInfo(pTSPacketStore,pTreeList,pTreeNodeEachGroup,pucData,uiOffset,uiMessageLength, &currentGroupLength);
        
                /*Finally update the length.*/
                pTreeNodeEachGroup->m_uiLength = currentGroupLength*8;
        
                uiOffset += currentGroupLength*8;
                uiMessageLength -= currentGroupLength;
                pucData += currentGroupLength;

                totalGroupLength += currentGroupLength;

                if( 0 == uiMessageLength)
                {
                    //No need to continue.
                    break;
                }
            }

            //Update the length finally.
            pTreeNodeGroups->m_uiLength = currentGroupLength*8;
        }
        
        if(SUCCESS == result )
        {
            if(2 > uiMessageLength)
            {
                result = FAILURE;
                
                // Unknown data.
                uiFieldLength = 8*uiMessageLength;
                pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
                
                uiMessageLength = 0;
            }
        }
        
        if(SUCCESS == result )
        {
            // 16 Bit PrivateDataLength.
            uiFieldLength = 16;
            uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"PrivateDataLength", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            privateDataLength = uiData;
            
            uiMessageLength -= 2;
            pucData += 2;
        }
    
    
        if(SUCCESS == result )
        {
            /*Check privateDataLength.*/
            if(privateDataLength > uiMessageLength)
            {
                result = FAILURE;
                
                // Unknown data.
                uiFieldLength = 8*uiMessageLength;
                pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
                
                uiMessageLength = 0;
            }
        }
    
        if(SUCCESS == result )
        {
            if(privateDataLength)
            {
                uiFieldLength = privateDataLength*8;
                pTreeNode  = new CTreeNode(pTSPacketStore, L"PrivateDataBytes", uiOffset, uiFieldLength, uiData, NODE_DATA_BYTE );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
            
                uiMessageLength -= privateDataLength;
                pucData += privateDataLength;
            }
        }
    }

    if(uiMessageLength)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;
    }

	return result;
}



EResult CSectionStoreSSU::ParseDIIPayload(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	CTreeNode * pTreeNodeGroups = NULL;
	CTreeNode * pTreeNodeEachGroup = NULL;
	UINT32 uiData = 0;
	UINT32 uiFieldLength;
	UINT32 compatibilityDescriptorLength = 0;
	UINT32 numberOfModules = 0;
	UINT32 totalModuleLength = 0;
	UINT32 currentModuleLength = 0;
	EResult result = SUCCESS;
	UINT32 privateDataLength = 0;
	UINT32 i = 0;

    if(uiMessageLength < 18)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }

    if(SUCCESS == result)
    {
    
        // 4 bytes downloadId.
        uiFieldLength = 8*4;
        uiData = (UINT32)((pucData[0] << 24) | (pucData[1] << 16) | (pucData[2] << 8 ) | pucData[3]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"downloadId", uiOffset, uiFieldLength, uiData );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        if(GetShowAllSSUFlag())
        {
            CString logMessage;
            logMessage.Format(L"-------------------DII count %10u, downloadId 0x%08x\r\n",  mDIISectionCount++, uiData);
            WriteLog(logMessage);
        }
        
    	// 16 Bit blockSize .
    	uiFieldLength = 16;
    	uiData = (UINT32)((pucData[4] << 8) | pucData[5]);
    	pTreeNode  = new CTreeNode(pTSPacketStore, L"blockSize", uiOffset, uiFieldLength, uiData );
    	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
    	pTreeNodeTmp = pTreeNode;
    	uiOffset += uiFieldLength;

    	// 8 Bit windowSize .
    	uiFieldLength = 8;
    	uiData = (UINT32)( pucData[6]);
    	pTreeNode  = new CTreeNode(pTSPacketStore, L"windowSize", uiOffset, uiFieldLength, uiData );
    	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
    	pTreeNodeTmp = pTreeNode;
    	uiOffset += uiFieldLength;

    	// 8 Bit ackPeriod .
    	uiFieldLength = 8;
    	uiData = (UINT32)( pucData[7]);
    	pTreeNode  = new CTreeNode(pTSPacketStore, L"ackPeriod", uiOffset, uiFieldLength, uiData );
    	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
    	pTreeNodeTmp = pTreeNode;
    	uiOffset += uiFieldLength;

        // 4 bytes tCDownloadWindow.
        uiFieldLength = 8*4;
        uiData = (UINT32)((pucData[8] << 24) | (pucData[9] << 16) | (pucData[10] << 8 ) | pucData[11]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"tCDownloadWindow", uiOffset, uiFieldLength, uiData );
    	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        // 4 bytes tCDownloadScenario.
        uiFieldLength = 8*4;
        uiData = (UINT32)((pucData[12] << 24) | (pucData[13] << 16) | (pucData[14] << 8 ) | pucData[15]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"tCDownloadScenario", uiOffset, uiFieldLength, uiData );
    	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

    	// 16 Bit compatibilityDescriptorLength .
    	uiFieldLength = 16;
    	uiData = (UINT32)((pucData[16] << 8) | pucData[17]);
    	pTreeNode  = new CTreeNode(pTSPacketStore, L"compatibilityDescriptorLength", uiOffset, uiFieldLength, uiData );
    	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
    	pTreeNodeTmp = pTreeNode;
    	uiOffset += uiFieldLength;

        compatibilityDescriptorLength = uiData;

        uiMessageLength -= 18;
        pucData += 18;
    }

    if(SUCCESS == result)
    {
        /*Check compatibilityDescriptorLength.*/

        if(uiMessageLength < compatibilityDescriptorLength)
        {
            result = FAILURE;
        
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength = 0;
        
        }

    }

    if(SUCCESS == result)
    {
        if(compatibilityDescriptorLength)
        {
            uiFieldLength = compatibilityDescriptorLength*8;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"CompatibilityDescriptor", uiOffset, uiFieldLength, uiData, NODE_LOOP );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
        
            /*---------------------------Key point-------------------------------------------------------------*/
            ParseCompatibilityDescriptor(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,compatibilityDescriptorLength);
        
            uiOffset += uiFieldLength;
        
            uiMessageLength -= compatibilityDescriptorLength;
            pucData += compatibilityDescriptorLength;
        
        }
    }


    if(SUCCESS == result)
    {
        /*Check numberOfModules.*/
        if(2 > uiMessageLength)
        {
            result = FAILURE;
        
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength = 0;
        }

        
        if(SUCCESS == result)
        {
            // 16 Bit numberOfModules
            uiFieldLength = 16;
            uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"numberOfModules", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;

            //Save it.
            numberOfModules = uiData;

            uiMessageLength -= 2;
            pucData += 2;
        
        }

        /***********!!!!!!!!!!!!!!!!!!!To parse module info!!!!!!!!!!!!!!!!!!!!!***/
        if((SUCCESS == result) && (0 != uiMessageLength) && (0 != numberOfModules))
        {
            //uiFieldLength = uiMessageLength*8; /*To be updated after all modules have been parsed.*/
            pTreeNode  = new CTreeNode(pTSPacketStore, L"Modules", uiOffset, uiFieldLength, uiData, NODE_LOOP );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
        
            pTreeNodeGroups = pTreeNodeTmp;
            totalModuleLength = 0;

            for(i = 0; i < numberOfModules; ++ i)
            {
                currentModuleLength = 0;
                
                pTreeNode  = new CTreeNode(pTSPacketStore, L"", uiOffset, 0, uiData, NODE_LOOP_ITEM ); /*Field length will be updated later.*/
                pTreeNode->m_strText.Format(L"Module Info %d", i);
                pTreeList->AppendLastChild( pTreeNode, pTreeNodeGroups);
                pTreeNodeTmp = pTreeNode;
        
                /*Save it.*/
                pTreeNodeEachGroup = pTreeNodeTmp;
        
                /*---------------------------Key point-------------------------------------------------------------*/
                ParseModuleInfo(pTSPacketStore,pTreeList,pTreeNodeEachGroup,pucData,uiOffset,uiMessageLength, &currentModuleLength);
        
                /*Finally update the length.*/
                pTreeNodeEachGroup->m_uiLength = currentModuleLength*8;
        
                uiOffset += currentModuleLength*8;
                uiMessageLength -= currentModuleLength;
                pucData += currentModuleLength;

                totalModuleLength += currentModuleLength;

                if( 0 == uiMessageLength)
                {
                    /*No need to continue.*/
                    break;
                }
            }

            /*Finally update the length.*/
            pTreeNodeGroups->m_uiLength = totalModuleLength*8;
            
        }
    }


    if(SUCCESS == result)
    {
        /*Check privateDataLength.*/

        if(2 > uiMessageLength)
        {
            result = FAILURE;
        
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength = 0;
        }
    }

    if(SUCCESS == result)
    {
        // 16 Bit privateDataLength
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"privateDataLength", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        privateDataLength = uiData;

        uiMessageLength -= 2;
        pucData += 2;
    }

    if(SUCCESS == result )
    {
        if((privateDataLength))
        {
            if(privateDataLength < uiMessageLength)
            {
                uiFieldLength = privateDataLength*8;
                pTreeNode  = new CTreeNode(pTSPacketStore, L"PrivateDataBytes", uiOffset, uiFieldLength, uiData, NODE_DATA_BYTE );
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
                
                uiMessageLength -= privateDataLength;
                pucData += privateDataLength;
            }
            else
            {
                result = FAILURE;
                
                // Unknown data.
                uiFieldLength = 8*uiMessageLength;
                pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
                pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
                pTreeNodeTmp = pTreeNode;
                uiOffset += uiFieldLength;
                
                uiMessageLength = 0;
            }
        }
    }


    if(uiMessageLength)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;
    }

   
	return result;
}


EResult CSectionStoreSSU::ParseCompatibilityDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	CTreeNode * pTreeNodeGroups = NULL;
	CTreeNode * pTreeNodeEachGroup = NULL;
	UINT32 uiData = 0;
	UINT32 uiFieldLength;
	UINT32 numberOfGroups = 0;
	UINT32 currentDescriptorLength = 0;
	UINT32 descriptorCount = 0;
	EResult result = SUCCESS;
	UINT32 i = 0;

    if(uiMessageLength < 2)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }

    if(SUCCESS == result)
    {

    	// 16 Bit descriptorCount .
    	uiFieldLength = 16;
    	uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
    	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptorCount ", uiOffset, uiFieldLength, uiData );
    	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
    	pTreeNodeTmp = pTreeNode;
    	uiOffset += uiFieldLength;

    	descriptorCount = uiData;

        uiMessageLength -= 2;
        pucData += 2;
    }

    if(SUCCESS == result)
    {
        uiFieldLength = uiMessageLength*8;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"Descriptors", uiOffset, uiFieldLength, uiData, NODE_LOOP );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;

        pTreeNodeGroups = pTreeNodeTmp;


        for(i = 0; i < descriptorCount; ++i)
        {
            if(0 == uiMessageLength)
            {
                break;
            }

            currentDescriptorLength = 0;
            
            pTreeNode  = new CTreeNode(pTSPacketStore, L"", uiOffset, 0, uiData, NODE_LOOP_ITEM ); /*Field length will be updated later.*/
    		pTreeNode->m_strText.Format(L"Descriptor %d", i);
            pTreeList->AppendLastChild( pTreeNode, pTreeNodeGroups);
            pTreeNodeTmp = pTreeNode;

            /*Save it.*/
            pTreeNodeEachGroup = pTreeNodeTmp;

            /*---------------------------Key point-------------------------------------------------------------*/
            ParseDescriptor(pTSPacketStore,pTreeList,pTreeNodeEachGroup,pucData,uiOffset,uiMessageLength, &currentDescriptorLength);

            /*Finally update the length.*/
            pTreeNodeEachGroup->m_uiLength = currentDescriptorLength*8;

            uiOffset += currentDescriptorLength*8;
            uiMessageLength -= currentDescriptorLength;
            pucData += currentDescriptorLength;

        }

    }

	return result;

}

EResult CSectionStoreSSU::ParseGroupInfo(
                        CTSPacketStore * pTSPacketStore,
                        CTreeList *pTreeList,
                        CTreeNode * pTreeNodeInput,
                        const UCHAR8 *pucData,
                        UINT32 uiOffset,
                        UINT32 uiMessageLengthInput,
                        UINT32 *pGroupLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UINT32 groupLength = 0;
	UINT32 groupInfoLength = 0;
	UINT32 privateDataLength = 0;
	EResult result = SUCCESS;
	UINT32 uiMessageLength = uiMessageLengthInput;

	UINT32 compatibilityDescriptorLength = 0;


    if(uiMessageLength < 10)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }

    if(SUCCESS == result )
    {
        // 32 Bit GroupId.
        uiFieldLength = 32;
        uiData = (UINT32)( (pucData[0] << 24) | (pucData[1] << 16) | (pucData[2] << 8) | pucData[3]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"GroupId", uiOffset, uiFieldLength, uiData );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        // 32 Bit GroupSize.
        uiFieldLength = 32;
        uiData = (UINT32)( (pucData[4] << 24) | (pucData[5] << 16) | (pucData[6] << 8) | pucData[7]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"GroupSize", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        uiMessageLength -= 8;
        pucData += 8;
        groupLength += 8;
        
        // 16 Bit CompatibilityDescriptorLength .
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"CompatibilityDescriptorLength ", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        compatibilityDescriptorLength = uiData;
        
        uiMessageLength -= 2;
        pucData += 2;
        groupLength += 2;
    }

    if(SUCCESS == result )
    {
        /*Check compatibilityDescriptorLength.*/
        if(compatibilityDescriptorLength > uiMessageLength)
        {
            result = FAILURE;
            
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            uiMessageLength = 0;
        }
    }

    if(SUCCESS == result )
    {
        if(compatibilityDescriptorLength)
        {
            uiFieldLength = compatibilityDescriptorLength*8;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"CompatibilityDescriptor", uiOffset, uiFieldLength, uiData, NODE_LOOP );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
        
            /*---------------------------Key point-------------------------------------------------------------*/
            ParseCompatibilityDescriptor(pTSPacketStore,pTreeList,pTreeNodeTmp,pucData,uiOffset,compatibilityDescriptorLength);
        
            uiOffset += uiFieldLength;
        
            uiMessageLength -= compatibilityDescriptorLength;
            pucData += compatibilityDescriptorLength;
            groupLength += compatibilityDescriptorLength;
        
        }
    }

    if(SUCCESS == result )
    {
        if(2 > uiMessageLength)
        {
            result = FAILURE;
            
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            uiMessageLength = 0;
        }
    }

    if(SUCCESS == result )
    {
        // 16 Bit GroupInfoLength.
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"GroupInfoLength", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        groupInfoLength = uiData;
        
        uiMessageLength -= 2;
        pucData += 2;
        groupLength += 2;
    }


    if(SUCCESS == result )
    {
        /*Check groupInfoLength.*/
        if(groupInfoLength > uiMessageLength)
        {
            result = FAILURE;
            
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            uiMessageLength = 0;
        }
    }

    if(SUCCESS == result )
    {
        if(groupInfoLength)
        {
            uiFieldLength = groupInfoLength*8;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"GroupInfoBytes", uiOffset, uiFieldLength, uiData, NODE_DATA_BYTE );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength -= groupInfoLength;
            pucData += groupInfoLength;
            groupLength += groupInfoLength;
        }
        
    }

    if(SUCCESS == result)
    {
        *pGroupLength = groupLength;
    }
    else
    {
        *pGroupLength = uiMessageLengthInput;
    }

	return result;
}

EResult CSectionStoreSSU::ParseDescriptor(
                        CTSPacketStore * pTSPacketStore,
                        CTreeList *pTreeList,
                        CTreeNode * pTreeNodeInput,
                        const UCHAR8 *pucData,
                        UINT32 uiOffset,
                        UINT32 uiMessageLengthInput,
                        UINT32 *pDescriptorLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UINT32 currentDescriptorLength = 0;
	UINT32 groupInfoLength = 0;
	UINT32 privateDataLength = 0;
	EResult result = SUCCESS;
	UINT32 uiMessageLength = uiMessageLengthInput;

	UINT32 descriptorLength = 0;
	UINT32 subDescriptorCount = 0;


    if(uiMessageLength < 2)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }

    if(SUCCESS == result )
    {
        // 8 Bit descriptorType.
        uiFieldLength = 8;
        uiData = (UINT32)(pucData[0]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptorType", uiOffset, uiFieldLength, uiData );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        // 8 Bit descriptorLength.
        uiFieldLength = 8;
        uiData = (UINT32)(pucData[1]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptorLength", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        descriptorLength = uiData;

        uiMessageLength -= 2;
        pucData += 2;
        currentDescriptorLength += 2;

    }

    if((SUCCESS == result ) && ( 0 != descriptorLength))
    {
        if(( 9 <= descriptorLength) && ( descriptorLength <= uiMessageLength ))
        {
            // 8 Bit specifierType.
            uiFieldLength = 8;
            uiData = (UINT32)(pucData[0]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"specifierType", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            // 24 Bit specifierData.
            uiFieldLength = 24;
            uiData = (UINT32)( (pucData[1] << 16) | (pucData[2] << 8) | pucData[3]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"specifierData", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            // 16 Bit model .
            uiFieldLength = 16;
            uiData = (UINT32)((pucData[4] << 8) | pucData[5]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"model", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            
            // 16 Bit version .
            uiFieldLength = 16;
            uiData = (UINT32)((pucData[6] << 8) | pucData[7]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"version", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            
            // 8 Bit subDescriptorCount.
            uiFieldLength = 8;
            uiData = (UINT32)(pucData[8]);
            pTreeNode  = new CTreeNode(pTSPacketStore, L"subDescriptorCount", uiOffset, uiFieldLength, uiData );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            subDescriptorCount = uiData;
            
            uiMessageLength -= 9;
            pucData += 9;
            currentDescriptorLength += 9;
        }
        else
        {
            result = FAILURE;
        
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength = 0;
        }

    }

    if((SUCCESS == result) && ( 0 != (descriptorLength - 9)))
    {
        uiFieldLength = (descriptorLength - 9)*8;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"subDescriptor", uiOffset, uiFieldLength, uiData, NODE_LOOP );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        
        /*---------------------------Key point-------------------------------------------------------------*/
        /*To parse subdescriptor.*/        
        uiOffset += uiFieldLength;
        
        uiMessageLength -= (descriptorLength - 9);
        pucData += (descriptorLength - 9);

    }

    if(SUCCESS == result)
    {
        *pDescriptorLength = descriptorLength + 2;
    }
    else
    {
        *pDescriptorLength = uiMessageLengthInput;
    }

	return result;
}


EResult CSectionStoreSSU::ParseModuleInfo(
                        CTSPacketStore * pTSPacketStore,
                        CTreeList *pTreeList,
                        CTreeNode * pTreeNodeInput,
                        const UCHAR8 *pucData,
                        UINT32 uiOffset,
                        UINT32 uiMessageLengthInput,
                        UINT32 *pGroupLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UINT32 groupLength = 0;
	UINT32 groupInfoLength = 0;
	EResult result = SUCCESS;
	UINT32 uiMessageLength = uiMessageLengthInput;

	UINT32 moduleInfoLength = 0;


    if(uiMessageLength < 8)
    {
        result = FAILURE;

        // Unknown data.
        uiFieldLength = 8*uiMessageLength;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        uiMessageLength = 0;

    }

    if(SUCCESS == result )
    {
        // 16 Bit moduleId.
        uiFieldLength = 16;
        uiData = (UINT32)((pucData[0] << 8) | pucData[1]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"moduleId", uiOffset, uiFieldLength, uiData );
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        // 32 Bit moduleSize.
        uiFieldLength = 32;
        uiData = (UINT32)( (pucData[2] << 24) | (pucData[3] << 16) | (pucData[4] << 8) | pucData[5]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"moduleSize", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        // 8 Bit moduleVersion.
        uiFieldLength = 8;
        uiData = (UINT32)( pucData[6]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"moduleVersion", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        // 8 Bit moduleInfoLength.
        uiFieldLength = 8;
        uiData = (UINT32)( pucData[7]);
        pTreeNode  = new CTreeNode(pTSPacketStore, L"moduleInfoLength", uiOffset, uiFieldLength, uiData );
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
        
        moduleInfoLength = uiData;
        
        uiMessageLength -= 8;
        pucData += 8;
        groupLength += 8;

    }

    if(SUCCESS == result )
    {
        /*Check moduleInfoLength.*/
        if(moduleInfoLength > uiMessageLength)
        {
            result = FAILURE;
            
            // Unknown data.
            uiFieldLength = 8*uiMessageLength;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"InvalidData", uiOffset, uiFieldLength, VALUE_ZERO, NODE_WARNING  );
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp); 
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
            
            uiMessageLength = 0;
        }
    }

    if(SUCCESS == result )
    {
        if(moduleInfoLength)
        {
            uiFieldLength = moduleInfoLength*8;
            pTreeNode  = new CTreeNode(pTSPacketStore, L"moduleInfoByte", uiOffset, uiFieldLength, uiData, NODE_DATA_BYTE);
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;
            uiOffset += uiFieldLength;
        
            uiMessageLength -= moduleInfoLength;
            pucData += moduleInfoLength;
            groupLength += moduleInfoLength;
        
        }
    }

    if(SUCCESS == result)
    {
        *pGroupLength = groupLength;
    }
    else
    {
        *pGroupLength = uiMessageLengthInput;
    }

	return result;
}


