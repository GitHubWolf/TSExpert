#pragma once
class CTSPacketStore;

// CHexView view

class CHexView : public CRichEditView
{
	DECLARE_DYNCREATE(CHexView)

protected:
	CHexView();           // protected constructor used by dynamic creation
	virtual ~CHexView();

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
public:

};


