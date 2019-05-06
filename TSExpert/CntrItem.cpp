// CntrItem.cpp : implementation of the CTSExpertCntrItem class
//

#include "stdafx.h"
#include "TSExpert.h"

#include "TSExpertDoc.h"
#include "TSExpertView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTSExpertCntrItem implementation

IMPLEMENT_SERIAL(CTSExpertCntrItem, CRichEditCntrItem, 0)

CTSExpertCntrItem::CTSExpertCntrItem(REOBJECT* preo, CTSExpertDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CTSExpertCntrItem::~CTSExpertCntrItem()
{
	// TODO: add UpdateResult code here
}


// CTSExpertCntrItem diagnostics

#ifdef _DEBUG
void CTSExpertCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CTSExpertCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

