// FieldView.cpp : implementation file
//

#include "stdafx.h"
#include "TSExpert.h"
#include "FieldView.h"

#include "TSExpertDoc.h"
#include "TSPacketStore.h"
#include "TreeList.h"
// CFieldView

IMPLEMENT_DYNCREATE(CFieldView, CRichEditView)

CFieldView::CFieldView()
{

}

CFieldView::~CFieldView()
{
}

BEGIN_MESSAGE_MAP(CFieldView, CRichEditView)

END_MESSAGE_MAP()


// CFieldView diagnostics

#ifdef _DEBUG
void CFieldView::AssertValid() const
{
	CRichEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CFieldView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFieldView message handlers

void CFieldView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CRichEditCtrl& richEditCtrl = this->GetRichEditCtrl();
	richEditCtrl.SetFont(CFont::FromHandle((HFONT)GetStockObject(ANSI_FIXED_FONT)));

}


void CFieldView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CTSExpertDoc *pDoc = (CTSExpertDoc *)GetDocument();
	if( NULL == pDoc)
	{
		return;
	}

	CTSPacketStore *pTSPacketSotrer = pDoc->m_pTSPacketStore;
	CTreeNode *pTreeNode = pDoc->m_pCurrentNode;

	CRichEditCtrl& richEditCtrl = this->GetRichEditCtrl();

	if(0 != richEditCtrl.GetTextLength())
	{
		richEditCtrl.SetSel(0, -1);
		richEditCtrl.Clear();
	}

	UINT32 uiOffsetBits = pDoc->m_uiOffset;
	UINT32 uiFieldLengthBits = pDoc->m_uiFieldLength;
	UINT32 uiFieldValue = pDoc->m_uiFieldValue;

	if( NULL == pTSPacketSotrer)
	{
		return ;
	}

	UINT32 uiStoredLength = pTSPacketSotrer->GetStoredLength();
	const UCHAR8 *pucData = pTSPacketSotrer->GetDataAddr();


	UINT32 uiOffsetBytes = uiOffsetBits/8;
	UINT32 uiOffset = uiOffsetBits%8;

	UINT32 uiFieldLengthBytes = uiFieldLengthBits/8;

	CString strBinData;

	uiFieldLengthBytes = ( ((uiOffsetBits + uiFieldLengthBits - 1)/8) - ((uiOffsetBits)/8) + 1);

	if(( 64 >= uiFieldLengthBits ) && ( 0 < uiFieldLengthBits))
	{
		UINT32 uiCounter = 0;
		UINT32 uiData;

		strBinData.AppendFormat(L"Binary  :");
		
		UINT32 uiTotalBytes = uiFieldLengthBytes;

		while( uiCounter < uiTotalBytes)
		{
			uiData = pucData[uiOffsetBytes + uiCounter];

			UINT32 j = 0;
			while( j < 8)
			{
				strBinData.AppendFormat(L"%c", ((uiData >> ( 7 - j)) &0x1)?'1':'0');
				j++;
			}
			strBinData.AppendFormat(L" ");

			uiCounter++;
		}

	}

	strBinData.AppendFormat(L"\r\nHeximal : %10X", uiFieldValue);
	strBinData.AppendFormat(L"\r\nDecimal : %10u", uiFieldValue);
	strBinData.AppendFormat(L"\r\nLength  : %10u byte", uiFieldLengthBytes);
	strBinData.AppendFormat(L"\r\nLength  : %10u bit",  uiFieldLengthBits);
	strBinData.AppendFormat(L"\r\nPosition: %10u byte", uiOffsetBytes);
	strBinData.AppendFormat(L"\r\nPosition: %10u bit",  uiOffsetBits);

	richEditCtrl.SetWindowTextW(strBinData);

	if(( 64 >= uiFieldLengthBits ) && ( 0 < uiFieldLengthBits))
	{
		richEditCtrl.SetSel(uiOffset + strlen("Binary  :"), uiOffset + strlen("Binary  :") + uiFieldLengthBits + uiFieldLengthBytes - 1);
	}



}
