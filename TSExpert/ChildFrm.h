// ChildFrm.h : interface of the CChildFrame class
//


#pragma once

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;
	CStatusBar  m_wndStatusBar;
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void ActivateFrame(int nCmdShow = -1);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	void DisplayProgress(UINT32 uiPercent);
};
