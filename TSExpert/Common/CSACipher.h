#pragma once
#include "TSPublic.h"

enum EOddEven
{
	FLAG_ODD,
	FLAG_EVEN
};
class CCSACipher
{
public:
	CCSACipher();
private:
	typedef struct _T_Csa
	{
		/* odd and even keys */
		UCHAR8 aucOddKey[8];
		UCHAR8 aucEvenKey[8];

		UCHAR8 aucOddKeySet[57];
		UCHAR8 aucEvenKeySet[57];

		/* cypher state */
		SINT32     A[11];
		SINT32     B[11];
		SINT32     X, Y, Z;
		SINT32     D, E, F;
		SINT32     p, q, r;
	}TCsa;
private:
	void ComputeKey( UCHAR8 aucKeySet[57], UCHAR8 aucControlWords[8] );
	void StreamCypher( SINT32 siInit, UCHAR8 *aucControlWords, UCHAR8 *pauSb, UCHAR8 *pauCb );
	void BlockDecypher( UCHAR8 aucKeySet[57], UCHAR8 aucIb[8], UCHAR8 aucBd[8] );
	void BlockCypher( UCHAR8 aucKeySet[57], UCHAR8 aucBd[8], UCHAR8 aucIb[8] );
public:
	void SetCW( const UCHAR8 aucOddKey[8], const UCHAR8 aucEvenKey[8] );
	void DoEntropy( UCHAR8 aucOddKey[8], UCHAR8 aucEvenKey[8] );
	EResult DecryptTSPacket( UCHAR8 *pauPacketData, SINT32 siPacketSize );
	EResult EncryptTSPacket( UCHAR8 *pauPacketData, SINT32 siPacketSize, EOddEven eFlag );
	EResult DecryptDataBlock( UCHAR8 *pauPacketData, SINT32 siPacketSize );
	EResult EncryptDataBlock( UCHAR8 *pauPacketData, SINT32 siPacketSize);
	EResult SetWorkingKeyFlag(EOddEven eFlag);

private:
	TCsa m_csaInfo;

	/*Current working key.*/
	UCHAR8 *m_pucCurrentCW;
	UCHAR8 *m_pucCurrentKeySet;
};
