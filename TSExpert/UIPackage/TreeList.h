#pragma once
#include "TSPublic.h"
#include "TSTableId.h"

class CTreeCtrl;

enum ENodeType
{
	NODE_FILE = 0,
		NODE_PSI = 100,//PAT,PMT,CAT,NIT
			NODE_PAT,
			NODE_CAT,
			NODE_PMT,
			NODE_NIT_CURRENT,
			NODE_NIT_OTHER,
		NODE_SI = 200,
			NODE_TSDT,
			NODE_SDT_CURRENT,
			NODE_SDT_OTHER,
			NODE_BAT,
			NODE_EIT_PF_CURRENT,
			NODE_EIT_PF_OTHER,
			NODE_EIT_SCHEDULE_CURRENT,
			NODE_EIT_SCHEDULE_OTHER,
			NODE_TDT,
			NODE_RST,
			NODE_TOT,
			NODE_DIT,
			NODE_SIT,
		NODE_PRIVATE_SECTION = 300,
			NODE_SECTION,
			NODE_LOOP,
			NODE_LOOP_ITEM,//Contained in NODE_LOOP
			NODE_FIELD,//The text of such node will be formated when output.
			NODE_IGNORED,//The text of such node will be formated when output.But value will not be showed.
			NODE_SPECIAL,//The text of such node will be formated when output.But value will not be showed.
			NODE_DATA_BYTE,//The text of such node will be formated when output.But value will not be showed.
			NODE_WARNING,////The text of such node will be formated when output.But value will not be showed.
		NODE_PID_LIST = 400,
			NODE_PID,
			NODE_TS_PACKET,
			NODE_PES_PACKET,
			NODE_SEARCH_RESULT,
			NODE_SEQUENCE,
			NODE_SEQUENCE_EXTENSION,
			NODE_GOP,
			NODE_FRAME,
			NODE_I_FRAME,
			NODE_B_FRAME,
			NODE_P_FRAME,
			NODE_SLICE,
			NODE_MACROBLOCK,
			NODE_BLOCK,
	NODE_LAST
};





class CTreeNode
{
private:
	CTreeNode(void);
public:
	CTreeNode(CTSPacketStore *pTSPacketStore, const wchar_t * pcFieldName, UINT32 uiOffset, UINT32 uiLength, UINT32 uiValue, ENodeType eNodeType = NODE_FIELD);
public:
	ENodeType m_eNodeType;
	CString    m_strText;
	CTSPacketStore *m_pTSPacketStore;
	HTREEITEM    m_hTreeItem;//Its value will be set after is is inserted into a tree ctrl.
	UINT32     m_uiOffset;//bits
	UINT32     m_uiLength;//bits
	UINT32	   m_uiValue;//Value

	CTreeNode *m_pParent;
	CTreeNode *m_pFirstChild;
	CTreeNode *m_pPrev;
	CTreeNode *m_pNext;
	CTreeNode *m_pLastChild;
};


class CTreeList
{
public:
	explicit CTreeList(CTreeCtrl *pTreeCtrl);
	~CTreeList(void);
public:
	BOOL FreeNodeRecursively(CTreeNode *pTreeNodeInput);
	BOOL FreeNodeRepeatly(CTreeNode *pTreeNodeInput);
	BOOL AppendRoot(CTreeNode *pTreeNodeInput);
	BOOL AppendChildFromFirst(CTreeNode *pTreeNodeChild, CTreeNode *pTreeNodeParent);
	BOOL AppendLastChild(CTreeNode *pTreeNodeChild, CTreeNode *pTreeNodeParent);
	BOOL AppendLast(CTreeNode *pTreeNodeInput, CTreeNode *pTreeNodePeer);
	BOOL InsertAfter(CTreeNode *pTreeNodeInput, CTreeNode *pTreeNodePeer);
	BOOL InsertBefore(CTreeNode *pTreeNodeInput, CTreeNode *pTreeNodePeer);
	BOOL AddNodeToCtrl(CTreeNode *pTreeNode);
	BOOL UpdateText(CTreeNode *pTreeNodeInput);
	BOOL UpdateImageIndex(CTreeNode *pTreeNodeInput);
	CTreeNode *GetParentNodeForSection(const ENodeType eNodeType);
	CTreeNode *GetNewNodeForSection(CTreeNode * pTreeNodeParent, CSectionObserver *pSectionObserver, CTSPacketStore  *pTSPacketStoreInput);
	ENodeType GetNodeTypeFromTableId(UCHAR8 ucTableId);
	LPWSTR GetNodeNameFromNodeType(ENodeType eNodeType);
	void SelectItem(CTreeNode * pTreeNode);
	EResult UpdateChildCount(CTreeNode *pTreeNodeInput);
	EResult UpdateAllChildCount(CTreeNode *pTreeNodeInput);
	CTreeNode *AddSearcherInfoNode(CTreeNode *pTreeNodeInput, TMsgSearcherInfo *pSearchInfo);
	CTreeNode *GetNewNodeForSearchedSection(CTreeNode * pTreeNodeParent, CSectionObserver *pSectionObserver, CTSPacketStore  *pTSPacketStoreInput);
	CTreeNode *GetNewNodeForSearchedTSPacket(CTreeNode * pTreeNodeParent, CTSPacketObserver *pTSPacketObserver, CTSPacketStore  *pTSPacketStoreInput);
	CTreeNode *GetNewNodeForSearchedPESPacket(CTreeNode * pTreeNodeParent, CPESPacketObserver *pPESPacketObserver, CTSPacketStore  *pTSPacketStoreInput);
	LPWSTR GetSearchTypeName(ESearchType eSearchType);
private:
	SINT32 GetPicIndexFromType(const ENodeType eNodeType);
private:
	CTreeCtrl *m_pTreeCtrl;
	CTreeNode * m_pTreeNodeList;
	CImageList   m_imgTreeList;
};
