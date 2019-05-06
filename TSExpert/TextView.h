#pragma once
class CTSPacketStore;

// CTextView view

class CTextView : public CRichEditView
{
	DECLARE_DYNCREATE(CTextView)

protected:
	CTextView();           // protected constructor used by dynamic creation
	virtual ~CTextView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	CTSPacketStore *m_pTSPacketSotrer;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


