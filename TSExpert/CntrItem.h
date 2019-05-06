// CntrItem.h : interface of the CTSExpertCntrItem class
//

#pragma once

class CTSExpertDoc;
class CTSExpertView;

class CTSExpertCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CTSExpertCntrItem)

// Constructors
public:
	CTSExpertCntrItem(REOBJECT* preo = NULL, CTSExpertDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CTSExpertDoc* GetDocument()
		{ return reinterpret_cast<CTSExpertDoc*>(CRichEditCntrItem::GetDocument()); }
	CTSExpertView* GetActiveView()
		{ return reinterpret_cast<CTSExpertView*>(CRichEditCntrItem::GetActiveView()); }

	public:
	protected:

// Implementation
public:
	~CTSExpertCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

