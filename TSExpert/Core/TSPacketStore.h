#pragma once
#include "TSPublic.h"
#include "TreeList.h"

class CTSParser;
class CTSPacketStore
{
public:
	explicit CTSPacketStore(UINT16 uwPid, UINT32 uiDataLength, CTSParser *pTSParser);
public:
	EResult AddData(UCHAR8 const *pucData,  UINT32 uiDataLength, UINT32 uiCurrentPacketNumber);
	UCHAR8 const * GetDataAddr(void) const;
	UINT32 GetTotalLength(void) const;
	UINT32 GetStoredLength(void) const ;
	EResult Match( CTSPacketStore const * pTSPacketStore, UINT32 uiMatchLength);
	void DumpStoredData(void);
	UINT32 GetRepeatCount(void);
	EResult SetRootNode(CTreeNode * pTreeNodeInput,CTreeList *pTreeList);
	CTSParser *GetTSParser(void);
	virtual EResult UpdateResult(void);
	UINT32 GetFirstPacketNumber(void);
	UINT32 GetLastPacketNumber(void);
	UINT32 GetTotalPacketCount(void);
	EResult GetDescription(CString& strDescription);

private:
	EResult AppendData(UCHAR8 const *pucData,  UINT32 uiDataLength);

public:
	~CTSPacketStore(void);
private:
	UCHAR8 * m_pucBuffer;
	UINT32 m_uiTotalLength;
	//Buffer space that has been used.
	UINT32 m_uiStoredLength;
	//Repeat times of current section.
	UINT32 m_uiRepeatCount;
	UINT16 m_uwPid;
	UINT32 m_uiFirstPacketNumber;
	UINT32 m_uiLastPacketNumber;
	UINT32 m_uiTotalPacketCount;
	CTreeNode * m_pTreeNodeRootNode;
	CTSParser * m_pTSParser;
	CTreeList * m_pTreeList;

};
