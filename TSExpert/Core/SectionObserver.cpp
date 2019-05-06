#include "StdAfx.h"
#include "SectionObserver.h"
#include "SectionHeaderReader.h"
#include "TSTableId.h"

CSectionObserver::CSectionObserver(UINT16 uwPid, string sName, CTSParser *pTSParser):m_sName(sName)
{
	//Default length to check the store data, subclass may also choose to change this value.
	m_uiMatchLength = MIN_SECTION_HEADER_LENGTH;

	m_uiCount = 0;

	m_pTSParser = pTSParser;

	m_uwPid = uwPid;

	m_pTreeList = NULL;
	m_pTreeNodeRootNode = NULL;
}

CSectionObserver::CSectionObserver(void)
{

};

CSectionObserver::~CSectionObserver(void)
{
	TRACE("TableName %4s, m_uwPid 0x%04X, m_uiCount %4d\r\n", m_sName.c_str() ,m_uwPid, m_uiCount);
	IteratorTSPacketStore iteratorTSPacketStore;
	CTSPacketStore * pTSPacketStore = NULL;
	for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
	{
		pTSPacketStore = *iteratorTSPacketStore;
		//pTSPacketStore->DumpStoredData();
		delete pTSPacketStore;
	}
}

#if 0

EResult CSectionObserver::ProcessNewSection(CTSPacketStore * pTSPacketStore)
{
	return FAILURE;
};

#endif

EResult CSectionObserver::StoreNewData(CTSPacketStore * pTSPacketStoreIn)
{
	IteratorTSPacketStore iteratorTSPacketStore;

	m_uiCount++;

	for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
	{
		CTSPacketStore * pTSPacketStoreTo = *iteratorTSPacketStore;
		if (SUCCESS == pTSPacketStoreTo->Match(pTSPacketStoreIn, m_uiMatchLength))
		{
			return FAILURE;
		};
	}

	m_storeTSPacketStore.insert(pTSPacketStoreIn);

	//Send a message to the UI to show the message.
	TMsgNewSection *pMsg = new TMsgNewSection;
	pMsg->pSectionObserver = this;
	pMsg->pTSPacketStore = pTSPacketStoreIn;
	if(SUCCESS != m_pTSParser->SendMsgToView(MESSAGE_NEW_STANDARD_SECTION, (pMsg) ))
	{
		delete pMsg;
	}
	return SUCCESS;
};


SINT32  CSectionObserver::CompareStandardSection(CTSPacketStore * pTSPacketStoreInput1, CTSPacketStore * pTSPacketStoreInput2, UINT32 uiCompareLength)
{
	UINT32 uiDataLength1 = pTSPacketStoreInput1->GetStoredLength();
	UINT32 uiDataLength2 = pTSPacketStoreInput2->GetStoredLength();
	
	UINT32 uiLength = min(uiDataLength1, uiDataLength2);
	uiLength = min(uiLength, uiCompareLength);

	const UCHAR8 *pucData1 = pTSPacketStoreInput1->GetDataAddr();
	const UCHAR8 *pucData2 = pTSPacketStoreInput2->GetDataAddr();

	UINT32 i = 0;
	while( 1 <= uiLength )
	{
		if( pucData1[i] != pucData2[i])
		{
			if( pucData1[i]  > pucData2[i])
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
		i++;
		uiLength--;

		//Skip the second and third byte, do not compare section length.
		if( 1 == i)
		{
			if( 2 <= uiLength )
			{
				uiLength -= 2;
			}

			i += 2;
		}
	}
	return 0;
};

EResult CSectionObserver::GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
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


EResult CSectionObserver::CheckStandardSectionLength(CTSPacketStore * pTSPacketStore)
{
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	if( MIN_SECTION_HEADER_LENGTH > uiStoredLength)
	{
		return FAILURE;
	}

	return SUCCESS;
};

EResult CSectionObserver::DisplaySectionData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent)
{
	pTSPacketStore->SetRootNode(pTreeNodeInput,pTreeList);
	m_pTreeList = pTreeList;
	m_pTreeNodeRootNode = pTreeNodeParent;
	return SUCCESS;
};

EResult CSectionObserver::UpdateResult(void)
{
	IteratorTSPacketStore iteratorTSPacketStore;
	CTSPacketStore * pTSPacketStore = NULL;
	for(iteratorTSPacketStore = m_storeTSPacketStore.begin(); m_storeTSPacketStore.end() != iteratorTSPacketStore; iteratorTSPacketStore++)
	{
		pTSPacketStore = *iteratorTSPacketStore;
		pTSPacketStore->UpdateResult();		
	}
	return SUCCESS;
};
