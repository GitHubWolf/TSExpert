// TSExpertDoc.cpp : implementation of the CTSExpertDoc class
//

#include "stdafx.h"
#include <io.h>
#include "TSExpert.h"

#include "TSExpertDoc.h"

#include "TSPacketProducer.h"
#include "TSExpertView.h"
#include "CntrItem.h"

#ifdef _DEBUG
//#include "VLD.h"
#define new DEBUG_NEW
#endif

//Extern entry to parse the data.
extern UINT TSParserWorkerFunction( LPVOID pParam );


// CTSExpertDoc

IMPLEMENT_DYNCREATE(CTSExpertDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CTSExpertDoc, CRichEditDoc)

END_MESSAGE_MAP()


// CTSExpertDoc construction/destruction

CTSExpertDoc::CTSExpertDoc()
{
	// TODO: add one-time construction code here
	mFile = 0;
	mFileSize = 0;
	m_ePacketLength = TS_PACKET_LENGTH_UNKNOWN;
	m_uiValidPacketOffset = 0;
	m_pTSParserWorkerThread = NULL;

	//Handler to transport stream parser.
	m_pTSParser = NULL;

	m_pTSPacketStore = NULL;
	m_uiOffset = 0;
	m_uiFieldLength = 0;
	m_uiFieldValue  = 0;
	m_pCurrentNode = NULL;
	m_pMapPidCounter = NULL;

}

CTSExpertDoc::~CTSExpertDoc()
{
    if(mFile)
    {
        fclose(mFile);
    }

	if( NULL != m_pTSParser)
	{
		delete m_pTSParser;
	}

	CTSParser *pTSSearcher;
	IteratorTSSearcher iteratorTSSearcher;
	for( iteratorTSSearcher = m_storeTSSearcher.begin(); m_storeTSSearcher.end() != iteratorTSSearcher; iteratorTSSearcher++)
	{
		pTSSearcher = *iteratorTSSearcher;
		delete pTSSearcher;
	}

}

BOOL CTSExpertDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


CRichEditCntrItem* CTSExpertDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CTSExpertCntrItem(preo, const_cast<CTSExpertDoc*>(this));
}

// CTSExpertDoc serialization

void CTSExpertDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CTSExpertDoc diagnostics

#ifdef _DEBUG
void CTSExpertDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CTSExpertDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CTSExpertDoc commands

void CTSExpertDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CRichEditDoc::SetTitle(m_strPathName);
}

BOOL CTSExpertDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CRichEditDoc::OnOpenDocument(lpszPathName))
		return FALSE;

    errno_t error = _wfopen_s( &mFile, lpszPathName, L"rb" );
    if( 0 != error) 
    {
        /*Failed to open a file.*/
        AfxMessageBox(L"Failed to open file.");
        return FALSE;
    }

    /*To get file size.*/
    mFileSize = _filelength(_fileno(mFile));

	/*Check the file size.*/
	if( 0 == mFileSize)
	{
		AfxMessageBox(L"Empty file.Please choose another file.");
		return FALSE;
	}
#define TEST_READ_IN_SIZE (1000)
    /*Read in several packets in order to get packet size.*/
    unsigned char *vData = (unsigned char *)malloc(TEST_READ_IN_SIZE);
    size_t vBytesRead = fread( vData, 1, TEST_READ_IN_SIZE, mFile );

	CTSHeaderLocator TSHeaderLocator;
	TSHeaderLocator.Parse((UINT32)vBytesRead, vData);
	if( TS_PACKET_LENGTH_UNKNOWN == TSHeaderLocator.GetPacketLength() )
	{
		AfxMessageBox(L"Invalid transport stream file.No valid synchronize byte found.");
		return FALSE;
	}

	/*Save the result for the future use.*/
	m_uiValidPacketOffset = TSHeaderLocator.GetValidHeaderOffset();
	m_ePacketLength = TSHeaderLocator.GetPacketLength();

	free(vData);

	fseek(mFile, m_uiValidPacketOffset, SEEK_SET);

	//Start a thread to parse the input data.
	m_pTSParserWorkerThread = AfxBeginThread(TSParserWorkerFunction, this);

	return TRUE;
}


FILE * CTSExpertDoc::GetFile(void)
{
	return mFile;
};

UINT32 CTSExpertDoc::GetDataLength(void)
{
	return (mFileSize - m_uiValidPacketOffset);
};

EPacketLength CTSExpertDoc::GetPacketLength(void)
{
	return m_ePacketLength;
};
UINT32 CTSExpertDoc::GetFileSize(void)
{
	return mFileSize;
};
UINT32 CTSExpertDoc::GetValidOffset(void)
{
	return m_uiValidPacketOffset;
};

BOOL CTSExpertDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	// TODO: Add your specialized code here and/or call the base class
	return CRichEditDoc::CanCloseFrame(pFrame);
}


BOOL CTSExpertDoc::SendMsgToView(ULONG uiMsg,  void *pvParam)
{
	//m_mutex.Lock();
	POSITION pos = GetFirstViewPosition();
	while ( NULL != pos)
	{
		CView* pView = GetNextView(pos);
		if( NULL != pView)
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CTSExpertView)))
			{
				pView->SendMessage(ID_MSG_TSEXPERT_CORE, uiMsg, (LPARAM)pvParam);
				//BOOL bResult = pView->PostMessage(ID_MSG_TSEXPERT_CORE, uiMsg, (LPARAM)pvParam);
				//m_mutex.Unlock();
				//return bResult;
                return TRUE;
			}

		}
	}
	//m_mutex.Unlock();
	return FALSE;
}

BOOL CTSExpertDoc::PostMsgToView(ULONG uiMsg,  void *pvParam)
{
	//m_mutex.Lock();
	POSITION pos = GetFirstViewPosition();
	while ( NULL != pos)
	{
		CView* pView = GetNextView(pos);
		if( NULL != pView)
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CTSExpertView)))
			{
				BOOL bResult = pView->PostMessage(ID_MSG_TSEXPERT_CORE, uiMsg, (LPARAM)pvParam);
				//m_mutex.Unlock();
				return bResult;
			}

		}
	}
	//m_mutex.Unlock();
	return FALSE;
}


BOOL CTSExpertDoc::SaveModified()
{
	// TODO: Add your specialized code here and/or call the base class
	// Do nothing to save the document.
	return TRUE;

	//return CRichEditDoc::SaveModified();
}

EResult CTSExpertDoc::AddSearcher(CTSParser *pTSSearcher)
{
	m_storeTSSearcher.insert(pTSSearcher);
	return SUCCESS;
}
void CTSExpertDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	//m_mutex.Lock();
	if(( NULL != m_pTSParserWorkerThread ) && ( NULL != m_pTSParser ) )
	{
		if ( RUNNING_STATUS_QUIT != m_pTSParser->GetRunningStatus() )
		{
			/*Force the parser to quit.*/
			m_pTSParser->SetForceQuit(TRUE);
		}
		DWORD dwResult = WaitForSingleObject(m_pTSParserWorkerThread->m_hThread, INFINITE);
		TRACE("=================%d\n", dwResult);
	}
	//m_mutex.Unlock();

	return CRichEditDoc::OnCloseDocument();;
}
