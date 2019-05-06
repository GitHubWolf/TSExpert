#include "StdAfx.h"
#include "CRCGenerator.h"
#include <iostream>
using namespace std;
CCRCGenerator::CCRCGenerator(	
					UINT32 uiPolynomial, 
					SINT32 siWidth,
					UINT32 uiInitRegisterValue,
					BOOL   bReflectInByte,
					BOOL   bReflectOutCRC,
					UINT32 uiValueToXOR)
{
	m_uiPolynomial = uiPolynomial;
	m_siWidth = siWidth;
	m_bReflectInByte = bReflectInByte;
	m_bReflectOutCRC = bReflectOutCRC;

	m_uiValueToXOR = uiValueToXOR;
	
	m_uiInitValue = uiInitRegisterValue;        

	/*Init the table.*/
	memset(m_auiTable, 0, sizeof(UINT32)*TABLE_ARRAY_SIZE);

	GenerateLookupTable();
}

/* 
** Returns the value v with the bottom b [0,32] bits reflected.
** Example: Reflect(0x3e23L,3) == 0x3e26                        
*/
UINT32 CCRCGenerator::Reflect(UINT32 uiValue, SINT32 siBitLength)
{
	UINT32 uiTemp = uiValue;
	for ( SINT32 i = 0 ;  i < siBitLength;  i++)
	{
		if (uiTemp & 1L)
		{
			uiValue |=  BITMASK( ( siBitLength - 1 ) - i );
		}
		else
		{
			uiValue &= (~ BITMASK( ( siBitLength - 1 ) - i ) );
		}

		uiTemp>>=1;
	}
	return uiValue;
}

/* 
** Returns a longword whose value is (2^pCrcParameter->siWidth)-1,
** The trick is to do this portably (e.g. without doing <<32). 
*/
UINT32 CCRCGenerator::GetWidthMask (void)
{
	return (((1L<<(m_siWidth-1))-1L)<<1)|1L;
}

UINT32 CCRCGenerator::GenCrcWithTable(const UCHAR8 * pucBuffer,UINT32 uiLength)
{
	UINT32 uiChar;
	UINT32 uiTopBit = BITMASK(m_siWidth - 1);
	UINT32 uiRegister = m_uiInitValue;
	UINT32 uiCaculatedLength = 0;

	while(uiLength--)
	{
		uiChar = *pucBuffer++;
		uiCaculatedLength++;
		if( m_bReflectInByte )
		{
			uiRegister = (uiRegister >> 8) ^ m_auiTable[((uiRegister) ^ uiChar) & 0xFF];
		}
		else
		{
			uiRegister = (uiRegister << 8) ^ m_auiTable[((uiRegister >> ( m_siWidth - 8 )) ^ uiChar) & 0xFF];
		}
	}

	if( m_bReflectInByte )
	{
		uiRegister = Reflect(uiRegister, m_siWidth);
	}

	return uiRegister;
}

UINT32 CCRCGenerator::GenCrcWithoutTable(const UCHAR8 * pucBuffer,UINT32 uiLength)
{
	UINT32 uiChar;
	UINT32 uiTopBit = BITMASK(m_siWidth - 1);
	UINT32 uiRegister = m_uiInitValue;
	UINT32 uiPolynomial = m_uiPolynomial;

	while(uiLength--)
	{
		uiChar = *pucBuffer++;
		if (m_bReflectInByte) 
		{
			uiChar = Reflect(uiChar,8);
		}
		
		uiRegister ^= ( uiChar << ( m_siWidth - 8 ) );
		
		for ( SINT32 i = 0 ;  8 > i ; i++)
		{
			if (uiRegister & uiTopBit)
			{
				uiRegister = (uiRegister << 1) ^ uiPolynomial;
			}		
			else
			{
				uiRegister <<= 1;
			}
			
			uiRegister &= GetWidthMask();
		}
	}

	return uiRegister;
}

UINT32 CCRCGenerator::GenerateTableItem(SINT32 siIndex)
{
	UINT32 uiRegister = 0;
	UINT32 uiTopBit = BITMASK(m_siWidth-1);
	UINT32 uiIndex = (UINT32) siIndex;
	UINT32 uiPolynomial = m_uiPolynomial;

	if( m_bReflectInByte )
	{
		 uiIndex = Reflect(uiIndex,8);
	}


	uiRegister = uiIndex << (m_siWidth-8);
	for (SINT32 i=0;  8 > i ; i++)
	{
		if (uiRegister & uiTopBit)
		{
			uiRegister = (uiRegister << 1) ^ uiPolynomial;
		}			
		else
		{
			uiRegister <<= 1;
		}
		
	}

	if (m_bReflectInByte) 
	{
		uiRegister = Reflect(uiRegister,m_siWidth);
	}

	return (uiRegister & GetWidthMask());

}

EResult CCRCGenerator::GenerateLookupTable(void)
{
	for (SINT32 i = 0; TABLE_ARRAY_SIZE > i; i++)
	{
		m_auiTable[i] = GenerateTableItem(i);
	}
	return SUCCESS;
}

UINT32 CCRCGenerator::GetCRC(const UCHAR8 * pucBuffer,UINT32 uiLength)
{
	UINT32 uiCRCResult;
	BOOL bUseLookupTable = TRUE;

	if(( GetWidthMask() != m_uiInitValue ) && ( 0x0  != m_uiInitValue ))
	{
		bUseLookupTable = FALSE;
	}

	/*To use lookup table or not.*/
	if( bUseLookupTable )
	{
		uiCRCResult = GenCrcWithTable(pucBuffer,uiLength); 
	}
	else
	{
		uiCRCResult = GenCrcWithoutTable(pucBuffer,uiLength);
	}
	
	if (m_bReflectOutCRC)
	{
		uiCRCResult = m_uiValueToXOR ^ Reflect(uiCRCResult,m_siWidth);
	}
	else
	{
		uiCRCResult = m_uiValueToXOR ^ uiCRCResult;
	}

	uiCRCResult = uiCRCResult& GetWidthMask();
	return uiCRCResult;
}

EResult CCRCGenerator::DumpLookupTable(void)
{
#if 0
	#define TB_FILE   "CrcTable.txt"
	FILE *outfile;
	#define WR(X) fprintf(outfile,(X))
	#define WP(X,Y) fprintf(outfile,(X),(Y))
	outfile = fopen(TB_FILE,"w");
	char *form    = ((m_siWidth/8)==2) ? "0x%04X	" : "0x%08X	";

	WR("/****************************CRC Table****************************/\n");
	WR("/*****************************************************************/\n");

	for (SINT32 i = 0; TABLE_ARRAY_SIZE > i; i++)
	{
		WP(form,(UINT32) m_auiTable[i]);
		printf(form, m_auiTable[i]);

		if( 0 == ((i+1)%4))
		{
			WR("\n");
			printf("\n");
		}
	}

	WR("/*****************************************************************/\n");
	WR("/*******************************End*******************************/\n");

	fclose(outfile);
#endif
	return SUCCESS;
}
