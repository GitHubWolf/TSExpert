#include "stdafx.h"
#include "CSACipher.h"



static const UCHAR8 aucKeyPerm[0x40] =
{
	0x12,0x24,0x09,0x07,0x2A,0x31,0x1D,0x15,0x1C,0x36,0x3E,0x32,0x13,0x21,0x3B,0x40,
	0x18,0x14,0x25,0x27,0x02,0x35,0x1B,0x01,0x22,0x04,0x0D,0x0E,0x39,0x28,0x1A,0x29,
	0x33,0x23,0x34,0x0C,0x16,0x30,0x1E,0x3A,0x2D,0x1F,0x08,0x19,0x17,0x2F,0x3D,0x11,
	0x3C,0x05,0x38,0x2B,0x0B,0x06,0x0A,0x2C,0x20,0x3F,0x2E,0x0F,0x03,0x26,0x10,0x37,
};
static const SINT32 aucSbox1[0x20] = {2,0,1,1,2,3,3,0, 3,2,2,0,1,1,0,3, 0,3,3,0,2,2,1,1, 2,2,0,3,1,1,3,0};
static const SINT32 aucSbox2[0x20] = {3,1,0,2,2,3,3,0, 1,3,2,1,0,0,1,2, 3,1,0,3,3,2,0,2, 0,0,1,2,2,1,3,1};
static const SINT32 aucSbox3[0x20] = {2,0,1,2,2,3,3,1, 1,1,0,3,3,0,2,0, 1,3,0,1,3,0,2,2, 2,0,1,2,0,3,3,1};
static const SINT32 aucSbox4[0x20] = {3,1,2,3,0,2,1,2, 1,2,0,1,3,0,0,3, 1,0,3,1,2,3,0,3, 0,3,2,0,1,2,2,1};
static const SINT32 aucSbox5[0x20] = {2,0,0,1,3,2,3,2, 0,1,3,3,1,0,2,1, 2,3,2,0,0,3,1,1, 1,0,3,2,3,1,0,2};
static const SINT32 aucSbox6[0x20] = {0,1,2,3,1,2,2,0, 0,1,3,0,2,3,1,3, 2,3,0,2,3,0,1,1, 2,1,1,2,0,3,3,0};
static const SINT32 aucSbox7[0x20] = {0,3,2,2,3,0,0,1, 3,0,1,3,1,2,2,1, 1,0,3,3,0,1,1,2, 2,3,1,0,2,3,0,2};


// block - sbox
static const UCHAR8 aucBlockSbox[256] =
{
	0x3A,0xEA,0x68,0xFE,0x33,0xE9,0x88,0x1A,0x83,0xCF,0xE1,0x7F,0xBA,0xE2,0x38,0x12,
	0xE8,0x27,0x61,0x95,0x0C,0x36,0xE5,0x70,0xA2,0x06,0x82,0x7C,0x17,0xA3,0x26,0x49,
	0xBE,0x7A,0x6D,0x47,0xC1,0x51,0x8F,0xF3,0xCC,0x5B,0x67,0xBD,0xCD,0x18,0x08,0xC9,
	0xFF,0x69,0xEF,0x03,0x4E,0x48,0x4A,0x84,0x3F,0xB4,0x10,0x04,0xDC,0xF5,0x5C,0xC6,
	0x16,0xAB,0xAC,0x4C,0xF1,0x6A,0x2F,0x3C,0x3B,0xD4,0xD5,0x94,0xD0,0xC4,0x63,0x62,
	0x71,0xA1,0xF9,0x4F,0x2E,0xAA,0xC5,0x56,0xE3,0x39,0x93,0xCE,0x65,0x64,0xE4,0x58,
	0x6C,0x19,0x42,0x79,0xDD,0xEE,0x96,0xF6,0x8A,0xEC,0x1E,0x85,0x53,0x45,0xDE,0xBB,
	0x7E,0x0A,0x9A,0x13,0x2A,0x9D,0xC2,0x5E,0x5A,0x1F,0x32,0x35,0x9C,0xA8,0x73,0x30,

	0x29,0x3D,0xE7,0x92,0x87,0x1B,0x2B,0x4B,0xA5,0x57,0x97,0x40,0x15,0xE6,0xBC,0x0E,
	0xEB,0xC3,0x34,0x2D,0xB8,0x44,0x25,0xA4,0x1C,0xC7,0x23,0xED,0x90,0x6E,0x50,0x00,
	0x99,0x9E,0x4D,0xD9,0xDA,0x8D,0x6F,0x5F,0x3E,0xD7,0x21,0x74,0x86,0xDF,0x6B,0x05,
	0x8E,0x5D,0x37,0x11,0xD2,0x28,0x75,0xD6,0xA7,0x77,0x24,0xBF,0xF0,0xB0,0x02,0xB7,
	0xF8,0xFC,0x81,0x09,0xB1,0x01,0x76,0x91,0x7D,0x0F,0xC8,0xA0,0xF2,0xCB,0x78,0x60,
	0xD1,0xF7,0xE0,0xB5,0x98,0x22,0xB3,0x20,0x1D,0xA6,0xDB,0x7B,0x59,0x9F,0xAE,0x31,
	0xFB,0xD3,0xB6,0xCA,0x43,0x72,0x07,0xF4,0xD8,0x41,0x14,0x55,0x0D,0x54,0x8B,0xB9,
	0xAD,0x46,0x0B,0xAF,0x80,0x52,0x2C,0xFA,0x8C,0x89,0x66,0xFD,0xB2,0xA9,0x9B,0xC0,
};

// block - perm
static const UCHAR8 aucBlockPerm[256] =
{
	0x00,0x02,0x80,0x82,0x20,0x22,0xA0,0xA2, 0x10,0x12,0x90,0x92,0x30,0x32,0xB0,0xB2,
	0x04,0x06,0x84,0x86,0x24,0x26,0xA4,0xA6, 0x14,0x16,0x94,0x96,0x34,0x36,0xB4,0xB6,
	0x40,0x42,0xC0,0xC2,0x60,0x62,0xE0,0xE2, 0x50,0x52,0xD0,0xD2,0x70,0x72,0xF0,0xF2,
	0x44,0x46,0xC4,0xC6,0x64,0x66,0xE4,0xE6, 0x54,0x56,0xD4,0xD6,0x74,0x76,0xF4,0xF6,
	0x01,0x03,0x81,0x83,0x21,0x23,0xA1,0xA3, 0x11,0x13,0x91,0x93,0x31,0x33,0xB1,0xB3,
	0x05,0x07,0x85,0x87,0x25,0x27,0xA5,0xA7, 0x15,0x17,0x95,0x97,0x35,0x37,0xB5,0xB7,
	0x41,0x43,0xC1,0xC3,0x61,0x63,0xE1,0xE3, 0x51,0x53,0xD1,0xD3,0x71,0x73,0xF1,0xF3,
	0x45,0x47,0xC5,0xC7,0x65,0x67,0xE5,0xE7, 0x55,0x57,0xD5,0xD7,0x75,0x77,0xF5,0xF7,

	0x08,0x0A,0x88,0x8A,0x28,0x2A,0xA8,0xAA, 0x18,0x1A,0x98,0x9A,0x38,0x3A,0xB8,0xBA,
	0x0C,0x0E,0x8C,0x8E,0x2C,0x2E,0xAC,0xAE, 0x1C,0x1E,0x9C,0x9E,0x3C,0x3E,0xBC,0xBE,
	0x48,0x4A,0xC8,0xCA,0x68,0x6A,0xE8,0xEA, 0x58,0x5A,0xD8,0xDA,0x78,0x7A,0xF8,0xFA,
	0x4C,0x4E,0xCC,0xCE,0x6C,0x6E,0xEC,0xEE, 0x5C,0x5E,0xDC,0xDE,0x7C,0x7E,0xFC,0xFE,
	0x09,0x0B,0x89,0x8B,0x29,0x2B,0xA9,0xAB, 0x19,0x1B,0x99,0x9B,0x39,0x3B,0xB9,0xBB,
	0x0D,0x0F,0x8D,0x8F,0x2D,0x2F,0xAD,0xAF, 0x1D,0x1F,0x9D,0x9F,0x3D,0x3F,0xBD,0xBF,
	0x49,0x4B,0xC9,0xCB,0x69,0x6B,0xE9,0xEB, 0x59,0x5B,0xD9,0xDB,0x79,0x7B,0xF9,0xFB,
	0x4D,0x4F,0xCD,0xCF,0x6D,0x6F,0xED,0xEF, 0x5D,0x5F,0xDD,0xDF,0x7D,0x7F,0xFD,0xFF,
};

CCSACipher::CCSACipher()
{
	memset( &m_csaInfo, 0, sizeof(m_csaInfo) );

	m_pucCurrentCW = NULL;
	m_pucCurrentKeySet = NULL;
}

void CCSACipher::SetCW(const UCHAR8 aucOddKey[8], const UCHAR8 aucEvenKey[8] )
{
	memcpy( m_csaInfo.aucOddKey, aucOddKey, 8 );
	memcpy( m_csaInfo.aucEvenKey, aucEvenKey, 8 );

	DoEntropy(m_csaInfo.aucOddKey, m_csaInfo.aucEvenKey);

	ComputeKey( m_csaInfo.aucOddKeySet,  m_csaInfo.aucOddKey );
	ComputeKey( m_csaInfo.aucEvenKeySet, m_csaInfo.aucEvenKey );

	/*Set default.*/
	SetWorkingKeyFlag(FLAG_ODD);
}

void CCSACipher::DoEntropy(UCHAR8 aucOddKey[8], UCHAR8 aucEvenKey[8] )
{
	aucOddKey[3] = aucOddKey[0] + aucOddKey[1] + aucOddKey[2];
	aucOddKey[7] = aucOddKey[4] + aucOddKey[5] + aucOddKey[6];

	aucEvenKey[3] = aucEvenKey[0] + aucEvenKey[1] + aucEvenKey[2];
	aucEvenKey[7] = aucEvenKey[4] + aucEvenKey[5] + aucEvenKey[6];
}

EResult CCSACipher::DecryptTSPacket(UCHAR8 *pucPacketData, SINT32 siPacketSize )
{
	SINT32     siHeaderLength;

	/* transport scrambling control */
	if( 0 == (pucPacketData[3]&0x80)  )
	{
		/* not scrambled */
		return SUCCESS;
	}
	
	if( pucPacketData[3] & 0x40 )
	{
		SetWorkingKeyFlag(FLAG_ODD);
	}
	else
	{
		SetWorkingKeyFlag(FLAG_EVEN);
	}

	/* clear transport scrambling control */
	pucPacketData[3] &= 0x3F;

	siHeaderLength = 4;
	if( pucPacketData[3] & 0x20 )
	{
		/* skip adaption field */
		siHeaderLength += pucPacketData[4] + 1;
	}

	if( 188 - siHeaderLength < 8 )
	{
		return FAILURE;
	}

	return DecryptDataBlock(&pucPacketData[siHeaderLength], ( siPacketSize - siHeaderLength));
	
}

EResult CCSACipher::EncryptTSPacket(UCHAR8 *pucPacketData, SINT32 siPacketSize, EOddEven eFlag )
{
	SINT32 siHeaderLength = 4; /* hdr len */
	SINT32 n;

	/* set transport scrambling control */
	pucPacketData[3] |= 0x80;
	if( FLAG_ODD == eFlag )
	{
		pucPacketData[3] |= 0x40;
	}

	SetWorkingKeyFlag(eFlag);
	
	/* hdr len */
	siHeaderLength = 4;
	if( pucPacketData[3]&0x20 )
	{
		/* skip adaption field */
		siHeaderLength += pucPacketData[4] + 1;
	}

	n = (siPacketSize - siHeaderLength) / 8;

	if( 0 >= n  )
	{
		pucPacketData[3] &= 0x3f;
		return FAILURE;
	}

	return EncryptDataBlock(&pucPacketData[siHeaderLength], ( siPacketSize - siHeaderLength));
}

void CCSACipher::ComputeKey( UCHAR8 aucKeySet[57], UCHAR8 aucControlWords[8] )
{
	SINT32 i,j,k;
	SINT32 bit[64];
	SINT32 newbit[64];
	SINT32 kb[9][8];

	/* from a cw create 56 key bytes, here aucKeySet[1..56] */

	/* load aucControlWords SINT32o kb[7][1..8] */
	for( i = 0; i < 8; i++ )
	{
		kb[7][i+1] = aucControlWords[i];
	}

	/* calculate all kb[6..1][*] */
	for( i = 0; i < 7; i++ )
	{
		/* do a 64 bit perm on kb */
		for( j = 0; j < 8; j++ )
		{
			for( k = 0; k < 8; k++ )
			{
				bit[j*8+k] = (kb[7-i][1+j] >> (7-k)) & 1;
				newbit[aucKeyPerm[j*8+k]-1] = bit[j*8+k];
			}
		}
		for( j = 0; j < 8; j++ )
		{
			kb[6-i][1+j] = 0;
			for( k = 0; k < 8; k++ )
			{
				kb[6-i][1+j] |= newbit[j*8+k] << (7-k);
			}
		}
	}

	/* xor to give aucKeySet */
	for( i = 0; i < 7; i++ )
	{
		for( j = 0; j < 8; j++ )
		{
			aucKeySet[1+i*8+j] = kb[1+i][1+j] ^ i;
		}
	}
}

void CCSACipher::StreamCypher(SINT32 siInit, UCHAR8 *aucControlWords, UCHAR8 *pauSb, UCHAR8 *pauCb )
{
	SINT32 i,j, k;
	SINT32 extra_B;
	SINT32 s1,s2,s3,s4,s5,s6,s7;
	SINT32 next_A1;
	SINT32 next_B1;
	SINT32 next_E;

	if( siInit )
	{
		// load first 32 bits of CK SINT32o A[1]..A[8]
		// load last  32 bits of CK SINT32o B[1]..B[8]
		// all other regs = 0
		for( i = 0; i < 4; i++ )
		{
			m_csaInfo.A[1+2*i+0] = ( aucControlWords[i] >> 4 )&0x0f;
			m_csaInfo.A[1+2*i+1] = ( aucControlWords[i] >> 0 )&0x0f;

			m_csaInfo.B[1+2*i+0] = ( aucControlWords[4+i] >> 4 )&0x0f;
			m_csaInfo.B[1+2*i+1] = ( aucControlWords[4+i] >> 0 )&0x0f;
		}

		m_csaInfo.A[9] = m_csaInfo.A[10] = 0;
		m_csaInfo.B[9] = m_csaInfo.B[10] = 0;

		m_csaInfo.X = m_csaInfo.Y = m_csaInfo.Z = 0;
		m_csaInfo.D = m_csaInfo.E = m_csaInfo.F = 0;
		m_csaInfo.p = m_csaInfo.q = m_csaInfo.r = 0;
	}

	// 8 bytes per operation
	for( i = 0; i < 8; i++ )
	{
		SINT32 op = 0;
		SINT32 in1 = 0;    /* gcc warn */
		SINT32 in2 = 0;

		if( siInit )
		{
			in1 = ( pauSb[i] >> 4 )&0x0f;
			in2 = ( pauSb[i] >> 0 )&0x0f;
		}

		// 2 bits per iteration
		for( j = 0; j < 4; j++ )
		{
			// from A[1]..A[10], 35 bits are selected as inputs to 7 s-boxes
			// 5 bits input per s-box, 2 bits output per s-box
			s1 = aucSbox1[ (((m_csaInfo.A[4]>>0)&1)<<4) | (((m_csaInfo.A[1]>>2)&1)<<3) | (((m_csaInfo.A[6]>>1)&1)<<2) | (((m_csaInfo.A[7]>>3)&1)<<1) | (((m_csaInfo.A[9]>>0)&1)<<0) ];
			s2 = aucSbox2[ (((m_csaInfo.A[2]>>1)&1)<<4) | (((m_csaInfo.A[3]>>2)&1)<<3) | (((m_csaInfo.A[6]>>3)&1)<<2) | (((m_csaInfo.A[7]>>0)&1)<<1) | (((m_csaInfo.A[9]>>1)&1)<<0) ];
			s3 = aucSbox3[ (((m_csaInfo.A[1]>>3)&1)<<4) | (((m_csaInfo.A[2]>>0)&1)<<3) | (((m_csaInfo.A[5]>>1)&1)<<2) | (((m_csaInfo.A[5]>>3)&1)<<1) | (((m_csaInfo.A[6]>>2)&1)<<0) ];
			s4 = aucSbox4[ (((m_csaInfo.A[3]>>3)&1)<<4) | (((m_csaInfo.A[1]>>1)&1)<<3) | (((m_csaInfo.A[2]>>3)&1)<<2) | (((m_csaInfo.A[4]>>2)&1)<<1) | (((m_csaInfo.A[8]>>0)&1)<<0) ];
			s5 = aucSbox5[ (((m_csaInfo.A[5]>>2)&1)<<4) | (((m_csaInfo.A[4]>>3)&1)<<3) | (((m_csaInfo.A[6]>>0)&1)<<2) | (((m_csaInfo.A[8]>>1)&1)<<1) | (((m_csaInfo.A[9]>>2)&1)<<0) ];
			s6 = aucSbox6[ (((m_csaInfo.A[3]>>1)&1)<<4) | (((m_csaInfo.A[4]>>1)&1)<<3) | (((m_csaInfo.A[5]>>0)&1)<<2) | (((m_csaInfo.A[7]>>2)&1)<<1) | (((m_csaInfo.A[9]>>3)&1)<<0) ];
			s7 = aucSbox7[ (((m_csaInfo.A[2]>>2)&1)<<4) | (((m_csaInfo.A[3]>>0)&1)<<3) | (((m_csaInfo.A[7]>>1)&1)<<2) | (((m_csaInfo.A[8]>>2)&1)<<1) | (((m_csaInfo.A[8]>>3)&1)<<0) ];

			/* use 4x4 xor to produce extra nibble for T3 */
			extra_B = ( ((m_csaInfo.B[3]&1)<<3) ^ ((m_csaInfo.B[6]&2)<<2) ^ ((m_csaInfo.B[7]&4)<<1) ^ ((m_csaInfo.B[9]&8)>>0) ) |
				( ((m_csaInfo.B[6]&1)<<2) ^ ((m_csaInfo.B[8]&2)<<1) ^ ((m_csaInfo.B[3]&8)>>1) ^ ((m_csaInfo.B[4]&4)>>0) ) |
				( ((m_csaInfo.B[5]&8)>>2) ^ ((m_csaInfo.B[8]&4)>>1) ^ ((m_csaInfo.B[4]&1)<<1) ^ ((m_csaInfo.B[5]&2)>>0) ) |
				( ((m_csaInfo.B[9]&4)>>2) ^ ((m_csaInfo.B[6]&8)>>3) ^ ((m_csaInfo.B[3]&2)>>1) ^ ((m_csaInfo.B[8]&1)>>0) ) ;

			// T1 = xor all inputs
			// in1,in2, D are only used in T1 during initialisation, not generation
			next_A1 = m_csaInfo.A[10] ^ m_csaInfo.X;
			if( siInit ) next_A1 = next_A1 ^ m_csaInfo.D ^ ((j % 2) ? in2 : in1);

			// T2 =  xor all inputs
			// in1,in2 are only used in T1 during initialisation, not generation
			// if p=0, use this, if p=1, rotate the result left
			next_B1 = m_csaInfo.B[7] ^ m_csaInfo.B[10] ^ m_csaInfo.Y;
			if( siInit) next_B1 = next_B1 ^ ((j % 2) ? in1 : in2);

			// if p=1, rotate left
			if( m_csaInfo.p ) next_B1 = ( (next_B1 << 1) | ((next_B1 >> 3) & 1) ) & 0xf;

			// T3 = xor all inputs
			m_csaInfo.D = m_csaInfo.E ^ m_csaInfo.Z ^ extra_B;

			// T4 = sum, carry of Z + E + r
			next_E = m_csaInfo.F;
			if( m_csaInfo.q )
			{
				m_csaInfo.F = m_csaInfo.Z + m_csaInfo.E + m_csaInfo.r;
				// r is the carry
				m_csaInfo.r = (m_csaInfo.F >> 4) & 1;
				m_csaInfo.F = m_csaInfo.F & 0x0f;
			}
			else
			{
				m_csaInfo.F = m_csaInfo.E;
			}
			m_csaInfo.E = next_E;

			for( k = 10; k > 1; k-- )
			{
				m_csaInfo.A[k] = m_csaInfo.A[k-1];
				m_csaInfo.B[k] = m_csaInfo.B[k-1];
			}
			m_csaInfo.A[1] = next_A1;
			m_csaInfo.B[1] = next_B1;

			m_csaInfo.X = ((s4&1)<<3) | ((s3&1)<<2) | (s2&2) | ((s1&2)>>1);
			m_csaInfo.Y = ((s6&1)<<3) | ((s5&1)<<2) | (s4&2) | ((s3&2)>>1);
			m_csaInfo.Z = ((s2&1)<<3) | ((s1&1)<<2) | (s6&2) | ((s5&2)>>1);
			m_csaInfo.p = (s7&2)>>1;
			m_csaInfo.q = (s7&1);

			// require 4 loops per output byte
			// 2 output bits are a function of the 4 bits of D
			// xor 2 by 2
			op = (op << 2)^ ( (((m_csaInfo.D^(m_csaInfo.D>>1))>>1)&2) | ((m_csaInfo.D^(m_csaInfo.D>>1))&1) );
		}
		// return input data during init
		pauCb[i] = siInit ? pauSb[i] : op;
	}
}


void CCSACipher::BlockDecypher( UCHAR8 aucKeySet[57], UCHAR8 aucIb[8], UCHAR8 aucBd[8] )
{
	SINT32 i;
	SINT32 perm_out;
	SINT32 R[9];
	SINT32 next_R8;

	for( i = 0; i < 8; i++ )
	{
		R[i+1] = aucIb[i];
	}

	// loop over aucKeySet[56]..aucKeySet[1]
	for( i = 56; i > 0; i-- )
	{
		const SINT32 sbox_out = aucBlockSbox[ aucKeySet[i]^R[7] ];
		perm_out = aucBlockPerm[sbox_out];

		next_R8 = R[7];
		R[7] = R[6] ^ perm_out;
		R[6] = R[5];
		R[5] = R[4] ^ R[8] ^ sbox_out;
		R[4] = R[3] ^ R[8] ^ sbox_out;
		R[3] = R[2] ^ R[8] ^ sbox_out;
		R[2] = R[1];
		R[1] = R[8] ^ sbox_out;

		R[8] = next_R8;
	}

	for( i = 0; i < 8; i++ )
	{
		aucBd[i] = R[i+1];
	}
}

void CCSACipher::BlockCypher( UCHAR8 aucKeySet[57], UCHAR8 aucBd[8], UCHAR8 aucIb[8] )
{
	SINT32 i;
	SINT32 perm_out;
	SINT32 R[9];
	SINT32 next_R1;

	for( i = 0; i < 8; i++ )
	{
		R[i+1] = aucBd[i];
	}

	// loop over aucKeySet[1]..aucKeySet[56]
	for( i = 1; i <= 56; i++ )
	{
		UCHAR8 ucIndex = aucKeySet[i]^R[8];
		const SINT32 sbox_out = aucBlockSbox[ ucIndex ];
		perm_out = aucBlockPerm[sbox_out];

		next_R1 = R[2];
		R[2] = R[3] ^ R[1];
		R[3] = R[4] ^ R[1];
		R[4] = R[5] ^ R[1];
		R[5] = R[6];
		R[6] = R[7] ^ perm_out;
		R[7] = R[8];
		R[8] = R[1] ^ sbox_out;

		R[1] = next_R1;
	}

	for( i = 0; i < 8; i++ )
	{
		aucIb[i] = R[i+1];
	}
}

EResult CCSACipher::SetWorkingKeyFlag(EOddEven eFlag)
{
	if( FLAG_EVEN  == eFlag )
	{
		m_pucCurrentCW = m_csaInfo.aucEvenKey;
		m_pucCurrentKeySet = m_csaInfo.aucEvenKeySet;
	}
	else
	{
		m_pucCurrentCW = m_csaInfo.aucOddKey;
		m_pucCurrentKeySet = m_csaInfo.aucOddKeySet;
	
	}
	return SUCCESS;
}

EResult CCSACipher::DecryptDataBlock( UCHAR8 *pauPacketData, SINT32 siPacketSize )
{
	UCHAR8 *pucCurrentCW = m_pucCurrentCW;
	UCHAR8 *pucCurrentKeySet = m_pucCurrentKeySet;

	UCHAR8  aucIB[8], aucStream[8], aucBlock[8];
	SINT32  siResidue;
	SINT32  i, j, n;

	/* init csa state */
	StreamCypher(1, pucCurrentCW, pauPacketData, aucIB );

	/* */
	n = (siPacketSize / 8);
	if( n < 0 )
	{
		return FAILURE;
	}
	

	siResidue = (siPacketSize % 8);    
	for( i = 1; i < n + 1; i++ )
	{
		BlockDecypher( pucCurrentKeySet, aucIB, aucBlock );
		if( i != n )
		{
			StreamCypher(0, pucCurrentCW, NULL, aucStream );
			for( j = 0; j < 8; j++ )
			{
				/* xor aucIB with aucStream */
				aucIB[j] = pauPacketData[8*i+j] ^ aucStream[j];
			}
		}
		else
		{
			/* last aucBlock */
			for( j = 0; j < 8; j++ )
			{
				aucIB[j] = 0;
			}
		}
		/* xor aucIB with aucBlock */
		for( j = 0; j < 8; j++ )
		{
			pauPacketData[8*(i-1)+j] = aucIB[j] ^ aucBlock[j];
		}
	}

	if( siResidue > 0 )
	{
		StreamCypher(0, pucCurrentCW, NULL, aucStream );
		for( j = 0; j < siResidue; j++ )
		{
			pauPacketData[siPacketSize - siResidue + j] ^= aucStream[j];
		}
	}

	return SUCCESS;
}

EResult CCSACipher::EncryptDataBlock( UCHAR8 *pauPacketData, SINT32 siPacketSize)
{
	UCHAR8 *pucCurrentCW = m_pucCurrentCW;
	UCHAR8 *pucCurrentKeySet = m_pucCurrentKeySet;
	UCHAR8  aucIB[184/8+2][8], aucStream[8], aucBlock[8];
	SINT32 n, siResidue;
	SINT32 i, j;

	n = (siPacketSize / 8);
	siResidue = (siPacketSize % 8);

	/* */
	for( i = 0; i < 8; i++ )
	{
		aucIB[n+1][i] = 0;
	}

	for( i = n; i  > 0; i-- )
	{
		for( j = 0; j < 8; j++ )
		{
			aucBlock[j] = pauPacketData[8*(i-1)+j] ^aucIB[i+1][j];
		}
		BlockCypher( pucCurrentKeySet, aucBlock, aucIB[i] );
	}

	/* init csa state */
	StreamCypher( 1, pucCurrentCW, aucIB[1], aucStream );

	for( i = 0; i < 8; i++ )
	{
		pauPacketData[i] = aucIB[1][i];
	}
	for( i = 2; i < n+1; i++ )
	{
		StreamCypher( 0, pucCurrentCW, NULL, aucStream );
		for( j = 0; j < 8; j++ )
		{
			pauPacketData[8*(i-1)+j] = aucIB[i][j] ^ aucStream[j];
		}
	}
	if( siResidue > 0 )
	{
		StreamCypher( 0, pucCurrentCW, NULL, aucStream );
		for( j = 0; j < siResidue; j++ )
		{
			pauPacketData[siPacketSize - siResidue + j] ^= aucStream[j];
		}
	}

	return SUCCESS;
}
