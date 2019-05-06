#pragma once
#include "TSPublic.h"
#include "TreeList.h"
#include "TSPacketStore.h"

static const UINT32 PACKET_START_CODE_PREFIX = 0x000001;
enum EStreamIdType
{
	STREAM_ID_UNKNOWN,//Unhandled.
	STREAM_ID_MPEG_PROGRAM_STREAM_END_PS,//Unhandled.
	STREAM_ID_MPEG_PACK_START_PS,//Unhandled.
	STREAM_ID_MPEG_SYSTEM_HEADER_START_PS,//Unhandled.
	STREAM_ID_PROGRAM_STREAM_MAP,//Unique syntax.
	STREAM_ID_PRIVATE_STREAM_1,
	STREAM_ID_PADDING_STREAM,
	STREAM_ID_PRIVATE_STREAM_2,
	STREAM_ID_13818_3_11172_3_14496_3_AUDIO_STREAM,
	STREAM_ID_H262_13818_2_11172_2_14496_2_VIDEO_STREAM,
	STREAM_ID_ECM_STREAM,
	STREAM_ID_EMM_STREAM,
	STREAM_ID_H2220_13818_1_ANNEX_A_13818_6_DSMCC_STREAM,
	STREAM_ID_13522_STREAM,
	STREAM_ID_H2221_TYPE_A,
	STREAM_ID_H2221_TYPE_B,
	STREAM_ID_H2221_TYPE_C,
	STREAM_ID_H2221_TYPE_D,
	STREAM_ID_H2221_TYPE_E,
	STREAM_ID_ANCILLARY_STREAM,
	STREAM_ID_14496_1_SL_PACKETIZED_STREAM,
	STREAM_ID_14496_1_FLEXMUX_STREAM,
	STREAM_ID_METADATA_STREAM,
	STREAM_ID_EXTENDED_STREAM_ID,
	STREAM_ID_RESERVED_DATA_STREAM,
	STREAM_ID_PROGRAM_STREAM_DIRECTORY
};

enum EStartCodeType
{
	START_CODE_PICTURE,
	START_CODE_SLICE,
	START_CODE_USER_DATA,
	START_CODE_SEQUENCE_HEADER,
	START_CODE_SEQUENCE_ERROR,
	START_CODE_EXTENSION,
	START_CODE_SEQUENCE_END,
	START_CODE_GROUP,
	START_CODE_SYSTEM,
	START_CODE_RESERVED
};

enum EExtensionStartCodeIdentifier
{
	EXTENSION_ID_SEQUENCE,
	EXTENSION_ID_SEQUENCE_DISPLAY,
	EXTENSION_ID_QUANT_MATRIX,
	EXTENSION_ID_COPYRIGHT,
	EXTENSION_ID_SEQUENCE_SCALABLE,
	EXTENSION_ID_PICTURE_DISPLAY,
	EXTENSION_ID_PICTURE_CODING,
	EXTENSION_ID_PICTURE_SPATIAL_SCALABLE,
	EXTENSION_ID_PICTURE_TEMPORAL_SCALABLE,
	EXTENSION_ID_RESERVED	
};


#if 0
video_sequence() 
{
	next_start_code();
	sequence_header();
	if ( nextbits() == extension_start_code ) 
	{
		sequence_extension();
		do 
		{
			extension_and_user_data( 0 );
			do 
			{
				if (nextbits() == group_start_code) 
				{
					group_of_pictures_header();
					extension_and_user_data( 1 );
				}
				picture_header();
				picture_coding_extension();
				extensions_and_user_data( 2 );
				picture_data();
			} 
			while ( (nextbits() == picture_start_code) || (nextbits() == group_start_code) );


			if ( nextbits() != sequence_end_code ) 
			{
				sequence_header();
				sequence_extension();
			}
		} while ( nextbits() != sequence_end_code )
	} 
	else 
	{
			/* ISO/IEC 11172-2 */
	}
	sequence_end_code;
}
#endif


class CPESPacketParser
{
public:
	static EStreamIdType GetStreamTypeFromStreamId(UINT32 uiParameter);
	static LPWSTR GetStreamIdTypeNameFromType(EStreamIdType  eStreamIdType);
	static LPWSTR GetStreamIdTypeNameFromId(UINT32 uiParameter);
	static EStartCodeType GetStartCodeTypeFromStartCode(UINT32 uiParameter);
	static LPWSTR GetStartCodeNameFromType(EStartCodeType  eStartCodeType);
	static LPWSTR GetStartCodeNameFromStartCode(UINT32 uiParameter);	
	static LPWSTR GetTrickModeControlName(UINT32 uiParameter);
	static LPWSTR GetPictureCodingTypeName(UINT32 uiParameter);
	static LPWSTR GetScramblingControlName(UINT32 uiParameter);
	static LPWSTR GetChromaFormatName(UINT32 uiParameter);
	static LPWSTR GetScalableModeName(UINT32 uiParameter);
	static LPWSTR GetExtensionStartCodeIdentifierNameFromId(UINT32 uiParameter);
	static LPWSTR GetExtensionStartCodeIdentifierNameFromType(EExtensionStartCodeIdentifier eExtensionStartCodeIdentifier );
	static EExtensionStartCodeIdentifier GetExtensionStartCodeIdentifierTypeFromId(UINT32 uiParameter );

	static EResult DisplayPESPacketData(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent);
private:
	static EResult ParsePESPacketHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParseVideoPESPacket(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength);
	static EResult ParsePTS(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParsePtsDts(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParseEscr(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParseEsRate(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParseDsmTrickMode(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParseAdditionalCopyInfo(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParsePesPacketCrc(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData);
	static EResult ParsePESExtension(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 *puiLengthTaken, UINT32 uiLeftLength);
	static EResult ParsePackHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiLeftLength);
	static EResult GetNextStartCodeAndLength(const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 &uiTakenLengh);
	static EResult GetNextStartCode(const UCHAR8 *pucData, UINT32 uiStoredLength);
	static EResult ParseVideoContent(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken);
	static EResult ParseSequenceHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken);
	static EResult ParseSequenceExtension(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken);
	static EResult ParseGopHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken);
	static EResult ParsePictureHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken);
	static EResult ParseSlice(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken);
	static EResult ParseExtensionSequence(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionSequenceDisplay(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionQuantMatrix(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionCopyright(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionSequenceScalable(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionPictureDisplay(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionPictureCoding(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionPictureSpatialScalable(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );
	static EResult ParseExtensionPictureTemporalScalable(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset );


};
