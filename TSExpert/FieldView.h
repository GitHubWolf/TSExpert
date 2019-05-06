#pragma once

// CFieldView view

class CFieldView : public CRichEditView
{
	DECLARE_DYNCREATE(CFieldView)

protected:
	CFieldView();           // protected constructor used by dynamic creation
	virtual ~CFieldView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
public:

protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


