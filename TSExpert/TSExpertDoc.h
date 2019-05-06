// TSExpertDoc.h : interface of the CTSExpertDoc class
//


#pragma once
#include "afxmt.h"
#include "afxwin.h"
#include "TSHeaderLocator.h"
#include "TSParser.h"

class CTreeNode;
class CTSExpertDoc : public CRichEditDoc
{
	typedef set<CTSParser *> SetTSSearcher;
	typedef SetTSSearcher::iterator IteratorTSSearcher;

protected: // create from serialization only
	CTSExpertDoc();
	DECLARE_DYNCREATE(CTSExpertDoc)

// Attributes
public:
	//Handler to transport stream parser.
	CTSParser *m_pTSParser;
	CTSPacketStore *m_pTSPacketStore;
	UINT32 m_uiOffset, m_uiFieldLength, m_uiFieldValue;
	CTreeNode *m_pCurrentNode;
	MapPidCounter *m_pMapPidCounter;

	/*Thread to parse TS file once user opens an file.*/
	CWinThread* m_pTSParserWorkerThread;
private:
	FILE *mFile;
	UINT32  mFileSize;
	EPacketLength m_ePacketLength;
	UINT32 m_uiValidPacketOffset;

	/*To hold the search result.*/
	SetTSSearcher m_storeTSSearcher;

	CMutex  m_mutex;
// Operations
public:
	FILE * GetFile(void);
	UINT32 GetDataLength(void);
	EPacketLength GetPacketLength(void);
	UINT32 GetFileSize(void);
	UINT32 GetValidOffset(void);
	EResult AddSearcher(CTSParser *pTSSearcher);
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;
// Implementation
public:
	virtual ~CTSExpertDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
public:
	BOOL SendMsgToView(ULONG uiMsg, void *pvParam);
	BOOL PostMsgToView(ULONG uiMsg, void *pvParam);
public:
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
protected:
	virtual BOOL SaveModified();
public:
	virtual void OnCloseDocument();
};


