// TSExpertView.h : interface of the CTSExpertView class
//


#pragma once
#include "TreeList.h"
class CTSExpertView : public CTreeView
{
protected: // create from serialization only
	CTSExpertView();
	DECLARE_DYNCREATE(CTSExpertView)

// Attributes
public:
	CTSExpertDoc* GetDocument() const;
private:
	CTreeList *m_pTreeList;
	CTreeNode *m_pTreeNodePSI;
	CTreeNode *m_pTreeNodeSI;
	CTreeNode *m_pTreeNodePID;
	/*To save node item of search result.*/
	CTreeNode *m_pTreeNodeCurrentSearcher;

// Operations
public:
	BOOL DisplayStandardSection(LPARAM lparam);
	BOOL DisplayPidCounterResult(LPARAM lparam);
	BOOL DisplayPrivateSection(LPARAM lparam);
	BOOL DisplayTsPacket(LPARAM lparam);
	BOOL DisplayPESPacket(LPARAM lparam);
	BOOL AddNewSearcherItem(LPARAM lparam);
private:
	BOOL DestroyTreeList(void);
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CTSExpertView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg LRESULT OnTSExpertMessage(WPARAM wparam,LPARAM lparam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnAdvancedSearch();
};

#ifndef _DEBUG  // debug version in TSExpertView.cpp
inline CTSExpertDoc* CTSExpertView::GetDocument() const
   { return reinterpret_cast<CTSExpertDoc*>(m_pDocument); }
#endif

