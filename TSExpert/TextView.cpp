// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "TSExpert.h"
#include "TextView.h"
#include "TSExpertDoc.h"
#include "TSPacketStore.h"
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CRichEditView)

CTextView::CTextView()
{
	m_pTSPacketSotrer = NULL;
}

CTextView::~CTextView()
{
}

BEGIN_MESSAGE_MAP(CTextView, CRichEditView)
END_MESSAGE_MAP()


// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CRichEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CTextView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTextView message handlers

void CTextView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CRichEditCtrl& richEditCtrl = this->GetRichEditCtrl();
	richEditCtrl.SetFont(CFont::FromHandle((HFONT)GetStockObject(ANSI_FIXED_FONT)));
}

void CTextView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CTSExpertDoc *pDoc = (CTSExpertDoc *)GetDocument();
	if( NULL == pDoc)
	{
		return;
	}

	CTSPacketStore *pTSPacketSotrer = pDoc->m_pTSPacketStore;

	CRichEditCtrl& richEditCtrl = this->GetRichEditCtrl();

	if( NULL == pTSPacketSotrer)
	{
		if( NULL == m_pTSPacketSotrer )
			return ;

		richEditCtrl.SetSel(0, -1);
		richEditCtrl.Clear();
		m_pTSPacketSotrer = pTSPacketSotrer;
		return ;
	}

	UINT32 uiStoredLength = pTSPacketSotrer->GetStoredLength();
	const UCHAR8 *pucData = pTSPacketSotrer->GetDataAddr();
	const UINT32 BYTES_PER_ROW  = 8;

	UINT32 uiRows = uiStoredLength/BYTES_PER_ROW;
	UINT32 uiReservedBytes = uiStoredLength * 3 + (uiRows + 1)*2 + 1;

	//To prevent unnecessary refresh.
	if( m_pTSPacketSotrer != pTSPacketSotrer )
	{
		m_pTSPacketSotrer = pTSPacketSotrer;
		richEditCtrl.SetSel(0, -1);
		richEditCtrl.Clear();

		CString strHexData;
		strHexData.Preallocate(uiReservedBytes);

		UINT32 i = 0;
		while( i < uiStoredLength)
		{
			//strHexData.AppendFormat(L"%c ", pucData[i]);
			if(( 0x20 <= pucData[i]) && ( 0x7F >= pucData[i] ))
			{
				strHexData.AppendFormat(L"%2c ",pucData[i]);
			}
			else
			{
				strHexData.AppendFormat(L"%2c ",'.');
			}
			
			if( 0 == (i+1)%BYTES_PER_ROW )
			{
				strHexData.AppendFormat(L"\r\n");
			}
			i++;
		}

		richEditCtrl.SetWindowTextW(strHexData);
	}

	// Set selected.
	UINT32 uiOffsetBits = pDoc->m_uiOffset;
	UINT32 uiFieldLengthBits = pDoc->m_uiFieldLength;

	if( 0 == uiFieldLengthBits )
	{
		richEditCtrl.SetSel(0, 0);
		return;
	}

	UINT32 uiOffsetBytes = uiOffsetBits/8;
	UINT32 uiFieldLengthBytes = uiFieldLengthBits/8;

	uiFieldLengthBytes = ( ((uiOffsetBits + uiFieldLengthBits - 1)/8) - ((uiOffsetBits)/8) + 1);


	UINT32 uiOffsetRows = uiOffsetBytes/BYTES_PER_ROW;
	UINT32 uiFieldLengthRows = uiFieldLengthBytes/BYTES_PER_ROW;

	richEditCtrl.SetSel(uiOffsetBytes*3 + uiOffsetRows*1, uiOffsetBytes*3 + uiOffsetRows*1 + uiFieldLengthBytes*3 + uiFieldLengthRows*1);


}
