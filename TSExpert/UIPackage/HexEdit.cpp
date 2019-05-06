// HexEdit.cpp : implementation file
// HexEdit only accepts hex chars, also including RETURN, BACK SPACE, LINE FEED and SPACE.
// It shows the data in hex view.

#include "stdafx.h"
#include "HexEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexEdit
static UINT32 BYTES_PER_LINE = 16;

CHexEdit::CHexEdit()
{
	m_pucData = NULL;
	m_uiDataLength = 0;
	//CRichEditCtrl::SetUndoLimit(10);
	//SetFont(CFont::FromHandle((HFONT)GetStockObject(ANSI_FIXED_FONT)));

}

CHexEdit::~CHexEdit()
{
	ResetData();
}
/*
MFC standard commands fall in the range 0xE000 to 0xEFFF. 
Please do not rely on the specific values of these IDs, 
since they are subject to change in future versions of the library.
Your application should define its commands in the range 0x8000 to 0xDFFF.
*/

#define ID_MY_LOAD_BINARY 0xEEE0
#define ID_MY_LOAD_TEXT   0xEEE1
#define ID_MY_SAVE_BINARY 0xEEE2
#define ID_MY_SAVE_TEXT   0xEEE3

BEGIN_MESSAGE_MAP(CHexEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CHexEdit)
	//ON_WM_CHAR()
	//}}AFX_MSG_MAP
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MY_LOAD_BINARY, LoadFromFileAsBinary)
	ON_COMMAND(ID_MY_LOAD_TEXT, LoadFromFileAsText)
	ON_COMMAND(ID_MY_SAVE_BINARY, SaveToFileAsBinary)
	ON_COMMAND(ID_MY_SAVE_TEXT, SaveToFileAsText)
	ON_COMMAND(ID_EDIT_UNDO,  Undo)
	ON_COMMAND(ID_EDIT_CUT,   CRichEditCtrl::Cut)
	ON_COMMAND(ID_EDIT_COPY,  CRichEditCtrl::Copy)
	ON_COMMAND(ID_EDIT_PASTE, CRichEditCtrl::Paste)	
	ON_COMMAND(ID_EDIT_CLEAR, CRichEditCtrl::Clear)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnSelectAll)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEdit message handlers

void CHexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	//If the input key is what we expected
	if( AcceptableChar(nChar))
	{
		//If the input is legal
		if(LegalInput(nChar, nRepCnt, nFlags ))
			CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
	}
	
}

BOOL CHexEdit::ValidSpecificChar(UINT32 uiChar)
{

	if(    ( ' ' == uiChar )	//Space
		|| ( 0x0D == uiChar )//Return, we want to support new line in the hex edit
		|| ( 0x0A == uiChar )//Line Feed
		|| ( 0x08 == uiChar )//Back Space
		)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CHexEdit::ValidHexChar(UINT uiChar)
{

	if(	   ( ('0' <= uiChar ) && ( '9' >= uiChar ) )
		|| ( ('a' <= uiChar ) && ( 'f' >= uiChar ) )
		|| ( ('A' <= uiChar ) && ( 'F' >= uiChar ) )
		)
	{
		return TRUE;
	}

	return FALSE;
}




BOOL CHexEdit::AcceptableChar(UINT uiChar)
{

	if( ValidSpecificChar(uiChar) || ValidHexChar(uiChar) )
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CHexEdit::LegalInput(UINT32 uiChar, UINT32 uiRepCnt, UINT32 uiFlags)
{
	SLONG slPosStart,slPosEnd;
	SINT32 siRow, siColumn;
	SINT32 siLength;

	//If the input is specific char, then just accept it
	if(ValidSpecificChar(uiChar))
	{
		return TRUE;
	}

	SetSel(-1,0); //Deselect
	GetSel(slPosStart,slPosEnd); //Get the position
	siRow = LineFromChar(slPosStart);//Get current row index
	siColumn = slPosStart - LineIndex(siRow);//Get current column index

	CString strBuffer;

	//Get the string length of current line, the parameter of LineLength MUST be -1
	siLength = LineLength( -1 );
	
	if( 1 >= siLength )
	{
		return TRUE;
	}


	//Read current line to the buffer.
	GetLine(siRow, strBuffer.GetBuffer( siLength + 1), siLength);

	strBuffer.ReleaseBuffer( siLength + 1);

	//Allow only 2 serial HexChar'.It will reject three(and above) HexChar', for example " 08F"  is invalid,
	//it shall be divied to be "08 F".


	//If the previous 2 chars are all valid hex char, return FALSE.
	//If siColumn is greater than 2.
	if( 2 <= siColumn )
	{
		if( ValidHexChar(strBuffer.GetAt(siColumn - 1))  &&  ValidHexChar(strBuffer.GetAt(siColumn - 2 )) )
		{
			//Insert a space before
			CWnd::DefWindowProc(WM_CHAR, 0x20 , MAKELPARAM (uiRepCnt , uiFlags )) ;
			CWnd::DefWindowProc(WM_CHAR, uiChar , MAKELPARAM (uiRepCnt , uiFlags )) ;
			return FALSE;
		}
	}

	//If the following 2 chars are all valid hex char, return FALSE.
	//To avoid out-of-range access, it MUST judge the length of current line.
	//If the string length(NOT including LF and CR ) of current line is greater than siColumn for 2(2 chars).
	if( siLength >= (siColumn + 2))
	{
		if( ValidHexChar(strBuffer.GetAt(siColumn))  &&  ValidHexChar(strBuffer.GetAt(siColumn + 1 )) )
		{
			CWnd::DefWindowProc(WM_CHAR, uiChar , MAKELPARAM (uiRepCnt , uiFlags )) ;
			CWnd::DefWindowProc(WM_CHAR, 0x20 , MAKELPARAM (uiRepCnt , uiFlags )) ;
			//Relocate the position
			SetFocus();
			SetSel(slPosStart+1, slPosStart+1);
			return FALSE;
		}
	}


	//If the previous char and the following char are both valid char, return FALSE.
	if(( 1 <= siColumn ) && ( siLength >= (siColumn + 1)))
	{

		if( ValidHexChar(strBuffer.GetAt(siColumn))  &&  ValidHexChar(strBuffer.GetAt(siColumn - 1 )) )
		{
			CWnd::DefWindowProc(WM_CHAR, uiChar , MAKELPARAM (uiRepCnt , uiFlags )) ;
			CWnd::DefWindowProc(WM_CHAR, 0x20 , MAKELPARAM (uiRepCnt , uiFlags )) ;
			return FALSE;
		}
	}

	return TRUE;
}


UINT32 CHexEdit::ConvertHexChar(UINT32 uiChar) 
{
	if(( '0' <= uiChar )&&( '9' >= uiChar))
	{
		return (uiChar - 0x30);
	}		
	else if( ( 'A' <= uiChar ) && ( 'F' >= uiChar ))
	{
		return ( uiChar - 'A' + 10 );
	}
	else if( ( 'a' <= uiChar ) && ( 'f' >= uiChar ))
	{
		return (uiChar - 'a' + 10 );
	}		
	else
	{
		return VALUE_MAX;
	}

	return VALUE_MAX;
}

//This function reads the string from the edit control and converts to the HexData.
//Return 0 if failed, else return 1;
EResult  CHexEdit::ConvertStringToHex(void)
{
	UINT32 uiHigh4b = 0;//High 4 bit
	UINT32 uiLow4b  = 0;//Low 4 bit

	CString strData;

	//If uiCounter%2 is equal to ZERO, then we shall read a byte to the buffer.
	UINT32 uiCounter = 0;

	//Clear the data.
	ResetData();

	//Read the data from control;
	GetWindowText(strData);
	SINT32 siLength = strData.GetLength();
	
	m_pucData = new UCHAR8[siLength];
	memset(m_pucData, 0, siLength);

	if( NULL == m_pucData )
	{
		return FAILURE;
	}


	for(SINT32 i = 0; i < siLength; ++i)
	{
		if( !AcceptableChar(strData.GetAt(i) ))
		{
			ResetData();
			AfxMessageBox(L"Invalid hex char, only 0-9 and  A-F allowed.");
			SetFocus();
			SetSel(i, -1);
			return FAILURE;
		}


		if( ValidHexChar(strData.GetAt(i)))
		{
			uiCounter++;

			if( 0 != uiCounter%2 )
			{
				uiHigh4b = ConvertHexChar(strData.GetAt(i));
			}
			else
			{
				uiLow4b = ConvertHexChar(strData.GetAt(i));

				//If uiCounter is EVEN, put a byte to the data buffer
				m_pucData[m_uiDataLength++] = ((uiHigh4b << 4) | (uiLow4b)) & 0xFF;
			}
		}
	}
	
	return SUCCESS;
}

EResult CHexEdit::ResetData(void)
{
	if( NULL != m_pucData )
	{
		delete[] m_pucData;
	}

	m_pucData = NULL;
	m_uiDataLength = 0;
	
	return SUCCESS;
}



void CHexEdit::SaveToFileAsText(void)
{
	if( FAILURE == ConvertStringToHex())
	{
		return;
	}

	CFileDialog fileDialog(FALSE, NULL, NULL, (OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT), L"All files|*.*||", NULL);
	
	//Save.
	if( IDOK != fileDialog.DoModal() )
	{
		return;
	}
	
	CFile file(fileDialog.GetFileName(), CFile::modeCreate | CFile::modeWrite);
	CString strText;
	GetWindowText(strText);
	CString strTextToStored;
	SINT32 siLength = strText.GetLength();
	UCHAR8 *pucData = new UCHAR8[siLength];
	for(SINT32 i = 0; i < siLength; i++)
	{
		/*Force a convertion.*/
		pucData[i] =  (UCHAR8)(0xFF & strText.GetAt(i));
	}

	file.Write(pucData, siLength);
	delete[] pucData;
	file.Close();

	return;
}

void CHexEdit::LoadFromFileAsText(void)
{
	CFileDialog fileDialog(TRUE, NULL, NULL, (OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT), L"All files|*.*||", NULL);
	
	//Load.
	if( IDOK != fileDialog.DoModal() )
	{
		return;
	}
	
	CFile file(fileDialog.GetPathName(), CFile::modeRead);

	UINT32 uiSize = (UINT32)file.GetLength();
	UCHAR8 *pucData = new UCHAR8[uiSize + 1];
	memset(pucData, 0, uiSize + 1);
	file.Read(pucData, uiSize);
	SetWindowText(CString(pucData));
	delete[] pucData;
	file.Close();

	return;
}



void CHexEdit::LoadFromFileAsBinary(void)
{
	CFileDialog fileDialog(TRUE, NULL, NULL, (OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT), L"All files|*.*||", NULL);
	
	//Load.
	if( IDOK != fileDialog.DoModal() )
	{
		return;
	}
	
	CFile file(fileDialog.GetPathName(), CFile::modeRead);

	CString strText;
	UINT32 uiSize = (UINT32)file.GetLength();
	UCHAR8 *pucData = new UCHAR8[uiSize + 1];
	memset(pucData, 0, uiSize + 1);
	file.Read(pucData, uiSize);

	/*Format input data as heximal.*/
	for(UINT32 i = 0; i < uiSize; i++)
	{
		strText.AppendFormat(L"%02X ",pucData[i]);
		if( 0 == (( i + 1) % BYTES_PER_LINE))
		{
			strText.AppendFormat(L"\r\n");
		}
	}
	SetWindowText(strText);
	delete[] pucData;
	file.Close();

	return;
}

EResult CHexEdit::LoadFromDataBuffer(const UCHAR8 *pucDataBuffer, UINT32 uiDataLength)
{	
	CString strText;
	/*Format input data as heximal.*/
	for(UINT32 i = 0; i < uiDataLength; i++)
	{
		strText.AppendFormat(L"%02X ",pucDataBuffer[i]);
		if( 0 == (( i + 1) % BYTES_PER_LINE))
		{
			strText.AppendFormat(L"\r\n");
		}
	}
	SetWindowText(strText);
	return SUCCESS;;
}

void CHexEdit::SaveToFileAsBinary(void)
{
	if( FAILURE == ConvertStringToHex())
	{
		return;
	}

	CFileDialog fileDialog(FALSE, NULL, NULL, (OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT), L"All files|*.*||", NULL);
	
	//Save.
	if( IDOK != fileDialog.DoModal() )
	{
		return;
	}
	
	CFile file(fileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite);

	file.Write(GetDataBuffer(), GetDataLength());
	file.Close();

	return;
}


UINT32  CHexEdit::GetDataLength(void)
{
	return m_uiDataLength;
}

EResult CHexEdit::ReadNBytes(UINT32& uiReturn, UINT32 uiBytes, UINT32 uiOffset)
{
	if((uiOffset >= m_uiDataLength ) || ( 4 < uiBytes ) || ( 0 == uiBytes ))
		return FAILURE;

	/*Default to read 4 bytes.*/
	UINT32 uiBytesToRead = uiBytes;

	/*If length < uiBytes.*/
	if( ( uiOffset + uiBytes) > m_uiDataLength )
	{
		uiBytesToRead = m_uiDataLength - uiOffset;
	}

	uiReturn = 0;
	for(UINT32 i = uiBytesToRead; i >= 1; i-- )
	{
		uiReturn = uiReturn | (m_pucData[uiOffset + i - 1] << (( uiBytes - i ) * 8));		
	}
	return SUCCESS;
}

const UCHAR8 *CHexEdit::GetDataBuffer(void)
{
	return m_pucData;
}
void CHexEdit::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetFocus();
	CMenu popupMenu;

	popupMenu.CreatePopupMenu();
	popupMenu.AppendMenuW(0, ID_EDIT_UNDO, L"&Undo");
	popupMenu.AppendMenuW(MF_SEPARATOR, 0 );
	popupMenu.AppendMenuW(0, ID_EDIT_CUT, L"&Cut");
	popupMenu.AppendMenuW(0, ID_EDIT_COPY, L"C&opy");
	popupMenu.AppendMenuW(0, ID_EDIT_PASTE, L"&Paste");
	popupMenu.AppendMenuW(0, ID_EDIT_CLEAR, L"C&lear");
	popupMenu.AppendMenuW(0, ID_EDIT_SELECT_ALL, L"Select &All");

	popupMenu.AppendMenuW(MF_SEPARATOR, 0 );
	popupMenu.AppendMenuW(MF_STRING, ID_MY_LOAD_BINARY, L"Load binary");
	popupMenu.AppendMenuW(MF_STRING, ID_MY_LOAD_TEXT,   L"Load text");
	popupMenu.AppendMenuW(MF_STRING, ID_MY_SAVE_BINARY, L"Save as binary");
	popupMenu.AppendMenuW(MF_STRING, ID_MY_SAVE_TEXT,   L"Save as text");

	CPoint pt;
	GetCursorPos(&pt);
	popupMenu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this );

	popupMenu.DestroyMenu();;
}

void CHexEdit::OnSelectAll()
{
	SetSel(0, -1);
}
void CHexEdit::Undo()
{
	CRichEditCtrl::Undo();
}
