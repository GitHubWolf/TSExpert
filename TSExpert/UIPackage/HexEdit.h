#pragma once
#include "TSPublic.h"

class CHexEdit : public CRichEditCtrl
{
// Construction
public:
	CHexEdit();

// Attributes
public:
private:
	UCHAR8 *m_pucData;
	UINT32 m_uiDataLength;


// Operations
public:
	EResult  ConvertStringToHex(void);
	UINT32  GetDataLength(void);
	EResult ReadNBytes(UINT32& uiReturn, UINT32 uiBytes = 4, UINT32 uiOffset = 0);
	const UCHAR8 *GetDataBuffer(void);
	EResult  ResetData(void);
	EResult LoadFromDataBuffer(const UCHAR8 *pucDataBuffer, UINT32 uiDataLength);

private:
	BOOL AcceptableChar(UINT32 uiChar);
	BOOL ValidSpecificChar(UINT32 uiChar);
	BOOL ValidHexChar(UINT32 uiChar);
	BOOL LegalInput(UINT32 uiChar, UINT32 uiRepCnt, UINT32 uiFlags);
	UINT32 ConvertHexChar(UINT32 uiChar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHexEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHexEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSelectAll();
	afx_msg void Undo();
	//}}AFX_MSG
	afx_msg void  SaveToFileAsBinary(void);
	afx_msg void  SaveToFileAsText(void);
	afx_msg void  LoadFromFileAsBinary(void);
	afx_msg void  LoadFromFileAsText(void);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};
