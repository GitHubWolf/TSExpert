#pragma once
#include "TSPublic.h"
#include "SectionObserver.h"
#include "SectionStorePMT.h"

class CSectionStoreSSU: public CSectionObserver
{
public:
	explicit CSectionStoreSSU(UINT16 uwPid, string sName, CTSParser *pTSParser);
public:
	virtual EResult ProcessNewSection(CTSPacketStore * pTSPacketStore);
	virtual EResult GetDescription(CTSPacketStore * pTSPacketStore, CString& strDescription);
	virtual EResult DisplaySectionData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent);
	EResult SetFilter(UCHAR8 const *pucMask, UCHAR8 const *pucMatch,UINT32 uiFilterLength);
	EResult IsMatched(CTSPacketStore * pTSPacketStore);
private:
	EResult StoreNewData(CTSPacketStore * pTSPacketStore);
	EResult GetDescription(CTSPacketStore * pTSPacketStore, const UCHAR8 *pucData, CString& strDescription);
    EResult ParseDSI(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength);
    EResult ParseDII(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength);
    EResult ParseDDB(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength);
    EResult ParseDsmccMessageHeader(
                            CTSPacketStore * pTSPacketStore,
                            CTreeList *pTreeList,
                            CTreeNode * pTreeNodeInput,
                            const UCHAR8 *pucData,
                            UINT32 uiOffset,
                            UINT32 uiMessageLength,
                            UINT32 isDDBHeader,
                            UINT32 *pHeaderLength);
    EResult ParseDDBPayload(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength);
    EResult ParseDSIPayload(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength);
    EResult ParseDIIPayload(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength);
    EResult ParseCompatibilityDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiMessageLength);
    EResult ParseGroupInfo(
                            CTSPacketStore * pTSPacketStore,
                            CTreeList *pTreeList,
                            CTreeNode * pTreeNodeInput,
                            const UCHAR8 *pucData,
                            UINT32 uiOffset,
                            UINT32 uiMessageLength,
                            UINT32 *pGroupInfoLength);

    EResult ParseDescriptor(
                            CTSPacketStore * pTSPacketStore,
                            CTreeList *pTreeList,
                            CTreeNode * pTreeNodeInput,
                            const UCHAR8 *pucData,
                            UINT32 uiOffset,
                            UINT32 uiMessageLengthInput,
                            UINT32 *pDescriptorLength);
    EResult ParseModuleInfo(
                            CTSPacketStore * pTSPacketStore,
                            CTreeList *pTreeList,
                            CTreeNode * pTreeNodeInput,
                            const UCHAR8 *pucData,
                            UINT32 uiOffset,
                            UINT32 uiMessageLength,
                            UINT32 *pGroupInfoLength);

public:
	virtual ~CSectionStoreSSU(void);
private:
	UINT32 m_uiFilterLength;
	UCHAR8 m_arrayMask[MAX_FILTER_LENGTH];
	UCHAR8 m_arrayMatch[MAX_FILTER_LENGTH];


    UINT32 mDSISectionCount; 
    UINT32 mDIISectionCount; 
    UINT32 mDDBSectionCount; 

};
