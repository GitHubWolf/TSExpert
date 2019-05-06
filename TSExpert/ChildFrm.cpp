// ChildFrm.cpp : implementation of the CChildFrame class
//
#include "stdafx.h"
#include "TSExpert.h"

#include "ChildFrm.h"

#include "TSExpertDoc.h"
#include "TSExpertView.h"
#include "FieldView.h"
#include "HexView.h"
#include "TextView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	/*Get the resolution of screen.*/
	int iFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN);

	/*Create 1 rows with 2 column.*/
	m_wndSplitter.CreateStatic(this, 1, 2);

	/*Create 3 row with 1 columns.*/
	m_wndSplitter1.CreateStatic(&m_wndSplitter, 3, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 1));

	/*Set the col width.*/
	m_wndSplitter.SetColumnInfo(0, (int)(iFullWidth*(0.75)), 0);
	m_wndSplitter.SetColumnInfo(1, (int)(iFullWidth*(0.15)), 0);

	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTSExpertView),  CSize((int)(iFullWidth*(0.75)),(int)(iFullHeight*(0.9))), pContext);

	/*Create views with certain percent of width and height.*/
	m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CHexView),   CSize((int)(iFullWidth*(0.15)),(int)(iFullHeight*(0.35))), pContext);
	m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CTextView),  CSize((int)(iFullWidth*(0.15)),(int)(iFullHeight*(0.35))), pContext);
	m_wndSplitter1.CreateView(2, 0, RUNTIME_CLASS(CFieldView), CSize((int)(iFullWidth*(0.15)),(int)(iFullHeight*(0.2))), pContext);

	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame message handlers

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Add your specialized code here and/or call the base class
	nCmdShow = SW_MAXIMIZE;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}


void CChildFrame::DisplayProgress(UINT32 uiPercent)
{
	//m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), 
	CString msg;
	msg.Format(L"Current progress %d%%", uiPercent);
	m_wndStatusBar.SetPaneText(0, msg);

	if( 100 == uiPercent)
	{
		msg.Format(L"Current progress completed.");
		m_wndStatusBar.SetPaneText(0, msg);
	}
};