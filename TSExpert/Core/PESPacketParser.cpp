#include "stdafx.h"
#include "PESPacketParser.h"


EStreamIdType CPESPacketParser::GetStreamTypeFromStreamId(UINT32 uiParameter)
{
	if(( 0x00 <= uiParameter ) && ( 0xB8 >= uiParameter ))
	{
		return STREAM_ID_UNKNOWN;
	}

	if(( 0xC0 <= uiParameter ) && ( 0xDF >= uiParameter ))
	{
		//ISO/IEC 13818-3 or ISO/IEC 11172-3 or 14496-3 audio stream
		return STREAM_ID_13818_3_11172_3_14496_3_AUDIO_STREAM;
	}

	if(( 0xE0 <= uiParameter ) && ( 0xEF >= uiParameter ))
	{
		//ITU-T Rec. H.262 | ISO/IEC 13818-2 or ISO/IEC 11172-2 or 14496-2 video stream
		return STREAM_ID_H262_13818_2_11172_2_14496_2_VIDEO_STREAM;
	}

	switch(uiParameter)
	{
		// special PS_stream_IDs (these are not PES stream IDs)
		case 0xB9:
			return STREAM_ID_MPEG_PROGRAM_STREAM_END_PS;//MPEG_program_stream_end (PS)
		case 0xBA:
			return STREAM_ID_MPEG_PACK_START_PS;//MPEG_pack_start (PS)
		case 0xBB:
			return STREAM_ID_MPEG_SYSTEM_HEADER_START_PS;//MPEG_system_header_start (PS)
		// PES_stream_IDs
		case 0xBC:
			return STREAM_ID_PROGRAM_STREAM_MAP;//program_stream_map
		case 0xBD:
			return STREAM_ID_PRIVATE_STREAM_1;//private_stream_1
		case 0xBE:
			return STREAM_ID_PADDING_STREAM;//padding_stream
		case 0xBF:
			return STREAM_ID_PRIVATE_STREAM_2;//private_stream_2
		case 0xF0:
			return STREAM_ID_ECM_STREAM;//ECM_stream
		case 0xF1:
			return STREAM_ID_EMM_STREAM;//EMM_stream
		case 0xF2:
			return STREAM_ID_H2220_13818_1_ANNEX_A_13818_6_DSMCC_STREAM;//ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex-A or ISO/IEC 13818-6_DSMCC stream
		case 0xF3:
			return STREAM_ID_13522_STREAM;//ISO/IEC 13522 stream
		case 0xF4:
			return STREAM_ID_H2221_TYPE_A;//ITU-T Rec. H.222.1 type A
		case 0xF5:
			return STREAM_ID_H2221_TYPE_B;//ITU-T Rec. H.222.1 type B
		case 0xF6:
			return STREAM_ID_H2221_TYPE_C;//ITU-T Rec. H.222.1 type C
		case 0xF7:
			return STREAM_ID_H2221_TYPE_D;//ITU-T Rec. H.222.1 type D
		case 0xF8:
			return STREAM_ID_H2221_TYPE_E;//ITU-T Rec. H.222.1 type E
		case 0xF9:
			return STREAM_ID_ANCILLARY_STREAM;//ancillary_stream
		case 0xFA:
			return STREAM_ID_14496_1_SL_PACKETIZED_STREAM;//ISO/IEC14496-1_SL-packetized_stream
		case 0xFB:
			return STREAM_ID_14496_1_FLEXMUX_STREAM;//ISO/IEC14496-1_FlexMux_stream
		case 0xFC:
			return STREAM_ID_METADATA_STREAM;//metadata stream
		case 0xFD:
			return STREAM_ID_EXTENDED_STREAM_ID;//extended_stream_id
		case 0xFE:
			return STREAM_ID_RESERVED_DATA_STREAM;//reserved data stream
		case 0xFF:
			return STREAM_ID_PROGRAM_STREAM_DIRECTORY;//program_stream_directory
	}

	return STREAM_ID_UNKNOWN;
}


LPWSTR CPESPacketParser::GetStreamIdTypeNameFromType(EStreamIdType  eStreamIdType)
{

	switch(eStreamIdType)
	{
		case STREAM_ID_UNKNOWN:
			return L"unknown stream";
		case STREAM_ID_MPEG_PROGRAM_STREAM_END_PS:
			return L"MPEG_program_stream_end (PS)";
		case STREAM_ID_MPEG_PACK_START_PS:
			return L"MPEG_pack_start (PS)";
		case STREAM_ID_MPEG_SYSTEM_HEADER_START_PS:
			return L"MPEG_system_header_start (PS)";
		case STREAM_ID_PROGRAM_STREAM_MAP:
			return L"program_stream_map";
		case STREAM_ID_PRIVATE_STREAM_1:
			return L"private_stream_1";
		case STREAM_ID_PADDING_STREAM:
			return L"padding_stream";
		case STREAM_ID_PRIVATE_STREAM_2:
			return L"private_stream_2";
		case STREAM_ID_13818_3_11172_3_14496_3_AUDIO_STREAM:
			return L"ISO/IEC 13818-3 or ISO/IEC 11172-3 or ISO/IEC 13818-7 or ISO/IEC 14496-3 audio stream";
		case STREAM_ID_H262_13818_2_11172_2_14496_2_VIDEO_STREAM:
			return L"ITU-T Rec. H.262 | ISO/IEC 13818-2 or ISO/IEC 11172-2 or ISO/IEC 14496-2 video stream";
		case STREAM_ID_ECM_STREAM:
			return L"ECM_stream";
		case STREAM_ID_EMM_STREAM:
			return L"EMM_stream";
		case STREAM_ID_H2220_13818_1_ANNEX_A_13818_6_DSMCC_STREAM:
			return L"ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex-A or ISO/IEC 13818-6_DSMCC stream";
		case STREAM_ID_13522_STREAM:
			return L"ISO/IEC 13522 stream";
		case STREAM_ID_H2221_TYPE_A:
			return L"ITU-T Rec. H.222.1 type A";
		case STREAM_ID_H2221_TYPE_B:
			return L"ITU-T Rec. H.222.1 type B";
		case STREAM_ID_H2221_TYPE_C:
			return L"ITU-T Rec. H.222.1 type C";
		case STREAM_ID_H2221_TYPE_D:
			return L"ITU-T Rec. H.222.1 type D";
		case STREAM_ID_H2221_TYPE_E:
			return L"ITU-T Rec. H.222.1 type E";
		case STREAM_ID_ANCILLARY_STREAM:
			return L"ancillary_stream";
		case STREAM_ID_14496_1_SL_PACKETIZED_STREAM:
			return L"ISO/IEC14496-1_SL-packetized_stream";
		case STREAM_ID_14496_1_FLEXMUX_STREAM:
			return L"ISO/IEC14496-1_FlexMux_stream";
		case STREAM_ID_METADATA_STREAM:
			return L"metadata stream";
		case STREAM_ID_EXTENDED_STREAM_ID:
			return L"extended_stream_id";
		case STREAM_ID_RESERVED_DATA_STREAM:
			return L"reserved data stream";
		case STREAM_ID_PROGRAM_STREAM_DIRECTORY:
			return L"program_stream_directory";
	}

	return L"unknown stream";
}

LPWSTR CPESPacketParser::GetStreamIdTypeNameFromId(UINT32 uiParameter)
{
	return GetStreamIdTypeNameFromType(GetStreamTypeFromStreamId(uiParameter));
}


LPWSTR CPESPacketParser::GetTrickModeControlName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x0:
			return L"Fast forward";
		case 0x1:
			return L"Slow motion";
		case 0x2:
			return L"Freeze frame";
		case 0x3:
			return L"Fast reverse";
		case 0x4:
			return L"Slow reverse";
		default:
			return L"Reserved";
	}

	return L"Reserved";
}


LPWSTR CPESPacketParser::GetPictureCodingTypeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x0:
			return L"forbidden";
		case 0x1:
			return L"intra-coded (I)";
		case 0x2:
			return L"predictive-coded (P)";
		case 0x3:
			return L"bidirectionally-predictive-coded (B)";
		case 0x4:
			return L"dc intra-coded (D)";
		default:
			return L"Reserved";
	}

	return L"Reserved";
}


LPWSTR CPESPacketParser::GetScramblingControlName(UINT32 uiParameter )
{
	switch(uiParameter)
	{
		case 0x0:
			return L"No scrambling";
		case 0x1:
			return L"Reserved";
		case 0x2:
			return L"Scrambled with Even Key";
		case 0x3:
			return L"Scrambled with Odd Key";
	}

	return L"Reserved";
}


LPWSTR CPESPacketParser::GetChromaFormatName(UINT32 uiParameter )
{
	switch(uiParameter)
	{
		case 0x0:
			return L"reserved";
		case 0x1:
			return L"4:2:0";
		case 0x2:
			return L"4:2:2";
		case 0x3:
			return L"4:4:4";
	}

	return L"reserved";
}

EExtensionStartCodeIdentifier CPESPacketParser::GetExtensionStartCodeIdentifierTypeFromId(UINT32 uiParameter )
{
	if(( 0x00 == uiParameter ) ||  ( 0x06 == uiParameter ) || (0x0B <= uiParameter ))
	{
		return EXTENSION_ID_RESERVED;
	}
	
	switch(uiParameter)
	{
		case 0x01:
			return EXTENSION_ID_SEQUENCE;
		case 0x02:
			return EXTENSION_ID_SEQUENCE_DISPLAY;
		case 0x03:
			return EXTENSION_ID_QUANT_MATRIX;
		case 0x04:
			return EXTENSION_ID_COPYRIGHT;
		case 0x05:
			return EXTENSION_ID_SEQUENCE_SCALABLE;
		case 0x07:
			return EXTENSION_ID_PICTURE_DISPLAY;
		case 0x08:
			return EXTENSION_ID_PICTURE_CODING;
		case 0x09:
			return EXTENSION_ID_PICTURE_SPATIAL_SCALABLE;
		case 0x0A:
			return EXTENSION_ID_PICTURE_TEMPORAL_SCALABLE;
	}

	return EXTENSION_ID_RESERVED;
}

LPWSTR CPESPacketParser::GetExtensionStartCodeIdentifierNameFromType(EExtensionStartCodeIdentifier eExtensionStartCodeIdentifier )
{
	switch(eExtensionStartCodeIdentifier)
	{
		case EXTENSION_ID_SEQUENCE:
			return L"Sequence_Extension_ID";
		case EXTENSION_ID_SEQUENCE_DISPLAY:
			return L"Sequence_Display_Extension_ID";
		case EXTENSION_ID_QUANT_MATRIX:
			return L"Quant_Matrix_Extension_ID";
		case EXTENSION_ID_COPYRIGHT:
			return L"Copyright_Extension_ID";
		case EXTENSION_ID_SEQUENCE_SCALABLE:
			return L"Sequence_Scalable_Extension_ID";
		case EXTENSION_ID_PICTURE_DISPLAY:
			return L"Picture_Display_Extension_ID";
		case EXTENSION_ID_PICTURE_CODING:
			return L"Picture_Coding_Extension_ID";
		case EXTENSION_ID_PICTURE_SPATIAL_SCALABLE:
			return L"Picture_Spatial_Scalable_Extension_ID";
		case EXTENSION_ID_PICTURE_TEMPORAL_SCALABLE:
			return L"Picture_Temporal_Scalable_Extension_ID";
	}

	return L"reserved";
}


LPWSTR CPESPacketParser::GetExtensionStartCodeIdentifierNameFromId(UINT32 uiParameter)
{
	return GetExtensionStartCodeIdentifierNameFromType(GetExtensionStartCodeIdentifierTypeFromId(uiParameter));
}


LPWSTR CPESPacketParser::GetScalableModeName(UINT32 uiParameter )
{
	switch(uiParameter)
	{
		case 0x0:
			return L"data_partitioning";
		case 0x1:
			return L"spatial_scalability";
		case 0x2:
			return L"SNR_scalability";
		case 0x3:
			return L"temporal_scalability";
	}

	return L"reserved";
}

EResult CPESPacketParser::DisplayPESPacketData(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, CTreeNode * pTreeNodeParent)
{
	const UCHAR8 *pucData = pTSPacketStore->GetDataAddr();
	UINT32 uiStoredLength = pTSPacketStore->GetStoredLength();
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiOffset = 0;

	UINT32 uiData;
	UINT32 uiFieldLength;

	if( MIN_PES_HEADER_LENGTH > uiStoredLength )
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid PES packet header", 0, uiStoredLength*8, VALUE_ZERO, NODE_IGNORED);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		return FAILURE;
	}


	// 24 Bit packet_start_code_prefix.
	uiFieldLength = 24;
	uiData = ((pucData[0] << 16) | (pucData[1] << 8) | ( pucData[2]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"packet_start_code_prefix", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPacketStartCodePrefix = uiData;

	// 8 Bit stream_id.
	uiFieldLength = 8;
	uiData = pucData[3];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"stream_id", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"stream_id[%d]: 0x%04X, Type: %s", uiFieldLength, uiData, GetStreamIdTypeNameFromId(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	EStreamIdType eStreamIdType = GetStreamTypeFromStreamId(uiData);


	// 16 Bit PES_packet_length.
	uiFieldLength = 16;
	uiData = ((pucData[4]<< 8 )| pucData[5]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_packet_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*Move.*/
	uiStoredLength -= 6;
	pucData += 6;

	if( PACKET_START_CODE_PREFIX != uiPacketStartCodePrefix)
	{
		/*Maybe it is encrypted.If so, quit.*/
		uiFieldLength = 8*uiStoredLength;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"encrypted_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return SUCCESS;
	}

	/*Continue to parse.*/

	if( STREAM_ID_PADDING_STREAM == eStreamIdType )
	{
		/*padding_byte.*/
		uiFieldLength = 8*uiStoredLength;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"padding_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return SUCCESS;
	}
	else if( STREAM_ID_PROGRAM_STREAM_MAP == eStreamIdType)
	{
		/*program_stream_map*/
	}
	else if( STREAM_ID_H2220_13818_1_ANNEX_A_13818_6_DSMCC_STREAM == eStreamIdType )
	{
		/*ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex A or ISO/IEC 13818-6_DSMCC_stream*/
	}
	else if( STREAM_ID_PROGRAM_STREAM_DIRECTORY == eStreamIdType )
	{
		/*program_stream_directory*/
	}
	else if
		(
			 ( STREAM_ID_PRIVATE_STREAM_2 == eStreamIdType )
			||( STREAM_ID_ECM_STREAM == eStreamIdType )
			||( STREAM_ID_EMM_STREAM == eStreamIdType )
			||( STREAM_ID_H2221_TYPE_E == eStreamIdType )
			||(STREAM_ID_UNKNOWN == eStreamIdType )
			||(STREAM_ID_MPEG_PROGRAM_STREAM_END_PS == eStreamIdType )
			||(STREAM_ID_MPEG_PACK_START_PS == eStreamIdType )
			||(STREAM_ID_MPEG_SYSTEM_HEADER_START_PS == eStreamIdType )			
		)
	{
		/*PES_packet_data_byte.*/
		uiFieldLength = 8*uiStoredLength;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_packet_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return SUCCESS;
	}
	else
	{
		/*Others will have a PES packet header.*/
		if( 3 <= uiStoredLength )
		{
			/*Read PES_header_data_length.*/
			UINT32 uiPESHeaderDataLength = pucData[2];

			/*Check the length.*/
			if( ( uiPESHeaderDataLength + 3) > uiStoredLength )
			{
				/*Invalid end.*/
				uiFieldLength = 8*uiStoredLength;
				pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
				pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
				pTreeNodeTmp = pTreeNode;
				uiOffset += uiFieldLength;

				return SUCCESS;
			}

			/*PES_header.*/
			uiFieldLength = 8*( uiPESHeaderDataLength + 3);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_header", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;

			ParsePESPacketHeader(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );

			uiOffset += uiFieldLength;
			pucData += ( 3 + uiPESHeaderDataLength );
			uiStoredLength -= ( 3 + uiPESHeaderDataLength );

			/*PES_packet_data_byte.*/
			uiFieldLength = 8*( uiStoredLength );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_packet_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;

			if( STREAM_ID_H262_13818_2_11172_2_14496_2_VIDEO_STREAM == eStreamIdType)
				ParseVideoPESPacket(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData, uiStoredLength);

			uiOffset += uiFieldLength;
			pucData += uiStoredLength;
		}
		else
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
		}
	}
	return SUCCESS;
};

EResult CPESPacketParser::ParsePESPacketHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 2 Bit '10'.
	uiFieldLength = 2;
	uiData = (( pucData[0] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"'10'", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit PES_scrambling_control.
	uiFieldLength = 2;
	uiData = (( pucData[0] >> 4) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_scrambling_control", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"PES_scrambling_control[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetScramblingControlName(uiData) );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit PES_priority.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 3) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_priority", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit data_alignment_indicator.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"data_alignment_indicator", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit copyright.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 1) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"copyright", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit original_or_copy.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 0) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"original_or_copy", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;	

	// 2 Bit PTS_DTS_flags.
	uiFieldLength = 2;
	uiData = (( pucData[1] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS_DTS_flags", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPtsDtsFlags = uiData;

	// 1 Bit ESCR_flag.
	uiFieldLength = 1;
	uiData = (( pucData[1] >> 5) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ESCR_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiEscrFlag = uiData;

	// 1 Bit ES_rate_flag.
	uiFieldLength = 1;
	uiData = (( pucData[1] >> 4) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ES_rate_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiEsRateFlag = uiData;

	// 1 Bit DSM_trick_mode_flag.
	uiFieldLength = 1;
	uiData = (( pucData[1] >> 3) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"DSM_trick_mode_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiDSMTrickModeFlag = uiData;

	// 1 Bit additional_copy_info_flag.
	uiFieldLength = 1;
	uiData = (( pucData[1] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"additional_copy_info_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiAdditionalCopyInfoFlag = uiData;
	
	// 1 Bit PES_CRC_flag.
	uiFieldLength = 1;
	uiData = (( pucData[1] >> 1) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_CRC_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPesCrcFlag = uiData;


	// 1 Bit PES_extension_flag.
	uiFieldLength = 1;
	uiData = (( pucData[1] >> 0) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_extension_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPesExtensionFlag = uiData;

	// 8 Bit PES_header_data_length.
	uiFieldLength = 8;
	uiData = ( pucData[2]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_header_data_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiStoredLength = uiData;

	/*Move.*/
	pucData += 3;


	if( 0x2 == uiPtsDtsFlags )
	{
		if( 5 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8*5;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		ParsePTS(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );
		uiOffset += uiFieldLength;

		pucData += 5;
		uiStoredLength -= 5;
	}


	if( 0x3 == uiPtsDtsFlags )
	{
		if( 10 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8*10;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS DTS", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		ParsePtsDts(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );
		uiOffset += uiFieldLength;
		
		pucData += 10;
		uiStoredLength -= 10;
		
	}


	if( 0x1 == uiEscrFlag )
	{
		if( 6 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8*6;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"ESCR", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		ParseEscr(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );
		uiOffset += uiFieldLength;

		pucData += 6;
		uiStoredLength -= 6;
	}
	
	if( 0x1 == uiEsRateFlag )
	{
		if( 3 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8*3;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"ES_rate", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		ParseEsRate(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );
		uiOffset += uiFieldLength;

		pucData += 3;
		uiStoredLength -= 3;
	}


	if( 0x1 == uiDSMTrickModeFlag )
	{
		if( 1 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8*1;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DSM_trick_mode", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		ParseDsmTrickMode(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );
		uiOffset += uiFieldLength;

		pucData += 1;
		uiStoredLength -= 1;
	}

	if( 0x1 == uiAdditionalCopyInfoFlag )
	{
		if( 1 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8*1;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"additional_copy_info", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		ParseAdditionalCopyInfo(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );
		uiOffset += uiFieldLength;

		pucData += 1;
		uiStoredLength -= 1;
	}

	if( 0x1 == uiPesCrcFlag )
	{
		if( 2 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8*2;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"previous_PES_packet_CRC", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		ParsePesPacketCrc(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData );
		uiOffset += uiFieldLength;

		pucData += 2;
		uiStoredLength -= 2;
	}

	if( 0x1 == uiPesExtensionFlag )
	{
		UINT32 uiLengthTaken;
		
		//uiFieldLength = 8*2;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_extension", uiOffset, uiFieldLength,VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		EResult eParseResult = ParsePESExtension(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData, &uiLengthTaken, uiStoredLength);
		uiFieldLength = uiLengthTaken*8;
		pTreeNode->m_uiLength = uiFieldLength;
		uiOffset += uiFieldLength;

		pucData += uiLengthTaken;
		uiStoredLength -= uiLengthTaken;

		if( FAILURE == eParseResult )
		{
			return FAILURE;
		}

		
	}

	
	/*stuffing_byte.*/
	uiFieldLength = 8*( uiStoredLength );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"stuffing_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;


	return SUCCESS;
}



EResult CPESPacketParser::ParseVideoPESPacket(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiCurrentLoopOffset;
	CTreeNode *pTreeNodeCurrentLoop;

	while( 4 <= uiStoredLength )
	{

		UINT32 uiNextStartCodeOffset;
		/*Check the first 3 byte.*/
		if( FAILURE == GetNextStartCodeAndLength(pucData, uiStoredLength, uiNextStartCodeOffset) )
		{
			pucData += 1;
			uiStoredLength -= 1;
			uiOffset += 8;
			continue;
		}

		uiCurrentLoopOffset = uiOffset;

		UINT32 uiNextStartCode = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
		UINT32 uiStartCode = ( pucData[3]  );
		EStartCodeType  eStartCodeType = GetStartCodeTypeFromStartCode(uiStartCode);
		
		pTreeNodeCurrentLoop = new CTreeNode(pTSPacketStore, L"", uiCurrentLoopOffset, (4 )*8, VALUE_ZERO, NODE_LOOP_ITEM);

		pTreeNodeCurrentLoop->m_strText.Format(L"next_start_code: 0x%08X, start_code: 0x%02X, type: %s",
			uiNextStartCode,
			uiStartCode,
			GetStartCodeNameFromStartCode(uiStartCode));
		pTreeList->AppendLastChild( pTreeNodeCurrentLoop,  pTreeNodeInput);

		UINT32 uiLengthTaken = 0;
		ParseVideoContent(pTSPacketStore, pTreeList, pTreeNodeCurrentLoop, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset, uiLengthTaken);

		pucData += (uiLengthTaken );
		uiStoredLength -= (uiLengthTaken );
		uiOffset += uiLengthTaken*8;
		/*Re-assign length.*/
		pTreeNodeCurrentLoop->m_uiLength = uiLengthTaken*8;
		
	}
	return SUCCESS;
}

EResult CPESPacketParser::ParsePTS(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 4 Bit '0010'.
	uiFieldLength = 4;
	uiData = (( pucData[0] >> 4) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"'0010'", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit PTS [32..30].
	uiFieldLength = 3;
	uiData = (( pucData[0] >> 1) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS [32..30]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[0]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit PTS [29..15].
	uiFieldLength = 15;
	uiData = (( pucData[1] << 7 ) | (( pucData[2] >> 1 ) & 0x7F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS [29..15]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[2]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit PTS [14..0].
	uiFieldLength = 15;
	uiData = (( pucData[3] << 7 ) | (( pucData[4] >> 1 ) & 0x7F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS [14..0]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[4]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;

}


EResult CPESPacketParser::ParsePtsDts(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 4 Bit '0011'.
	uiFieldLength = 4;
	uiData = (( pucData[0] >> 4) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"'0011'", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit PTS [32..30].
	uiFieldLength = 3;
	uiData = (( pucData[0] >> 1) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS [32..30]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[0]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit PTS [29..15].
	uiFieldLength = 15;
	uiData = (( pucData[1] << 7 ) | (( pucData[2] >> 1 ) & 0x7F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS [29..15]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[2]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit PTS [14..0].
	uiFieldLength = 15;
	uiData = (( pucData[3] << 7 ) | (( pucData[4] >> 1 ) & 0x7F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PTS [14..0]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[4]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	pucData += 5;

	// 4 Bit '0001'.
	uiFieldLength = 4;
	uiData = (( pucData[0] >> 4) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"'0001'", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit DTS [32..30].
	uiFieldLength = 3;
	uiData = (( pucData[0] >> 1) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"DTS [32..30]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[0]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit DTS [29..15].
	uiFieldLength = 15;
	uiData = (( pucData[1] << 7 ) | (( pucData[2] >> 1 ) & 0x7F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"DTS [29..15]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[2]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit DTS [14..0].
	uiFieldLength = 15;
	uiData = (( pucData[3] << 7 ) | (( pucData[4] >> 1 ) & 0x7F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"DTS [14..0]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[4]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;

}



EResult CPESPacketParser::ParseEscr(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 2 Bit reserved.
	uiFieldLength = 2;
	uiData = (( pucData[0] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 3 Bit ESCR_base[32..30].
	uiFieldLength = 3;
	uiData = (( pucData[0] >> 3) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ESCR_base[32..30]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 2 ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit ESCR_base[29..15].
	uiFieldLength = 15;
	uiData = (( ( pucData[0] & 0x3) << 13) | ( pucData[1] << 5) | (( pucData[2] >> 3) & 0x1F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ESCR_base[29..15]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[2] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit ESCR_base[14..0].
	uiFieldLength = 15;
	uiData = (( ( pucData[2] & 0x3) << 13) | ( pucData[3] << 5) | (( pucData[4] >> 3) & 0x1F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ESCR_base[14..0]", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[4] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 9 Bit ESCR_extension.
	uiFieldLength = 9;
	uiData = ( ((pucData[4] & 0x3) << 7) | ((pucData[5] >> 1 )  & 0x7F) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ESCR_extension", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[5]) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;

}

EResult CPESPacketParser::ParseEsRate(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 7 ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
	pTreeNodeTmp = pTreeNode;	
	uiOffset += uiFieldLength;

	// 22 Bit ES_rate.
	uiFieldLength = 22;
	uiData = ((( pucData[0] & 0x3F) << 15) | ( pucData[1] << 7) | (( pucData[2] >> 1) & 0x7F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ES_rate", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[2]  ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;

}

EResult CPESPacketParser::ParseDsmTrickMode(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 3 Bit trick_mode_control.
	uiFieldLength = 3;
	uiData = (( pucData[0] >> 5 ) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"trick_mode_control", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"trick_mode_control[%d]: 0x%04X, Type: %s", uiFieldLength, uiData, GetTrickModeControlName(uiData));
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
	pTreeNodeTmp = pTreeNode;
	
	uiOffset += uiFieldLength;

	UINT32 uiTrickModeControl = uiData;

	switch(uiTrickModeControl)
	{
		case 0x0:
		{
			// 2 Bit field_id.
			uiFieldLength = 2;
			uiData = (( pucData[0] >> 3 ) & 0x3);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"field_id", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			// 1 Bit intra_slice_refresh.
			uiFieldLength = 1;
			uiData = (( pucData[0] >> 2 ) & 0x1);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"intra_slice_refresh", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			// 2 Bit frequency_truncation.
			uiFieldLength = 2;
			uiData = (( pucData[0] ) & 0x3);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"frequency_truncation", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			break;
		}
		case 0x1:
		{
			// 5 Bit rep_cntrl.
			uiFieldLength = 5;
			uiData = (( pucData[0] ) & 0x1F);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"rep_cntrl", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
		
			break;
		}
		case 0x2:
		{
			// 2 Bit field_id.
			uiFieldLength = 2;
			uiData = (( pucData[0] >> 3 ) & 0x3);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"field_id", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			// 3 Bit reserved.
			uiFieldLength = 3;
			uiData = (( pucData[0] ) & 0x7);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			break;
		}
		case 0x3:
		{
			// 2 Bit field_id.
			uiFieldLength = 2;
			uiData = (( pucData[0] >> 3 ) & 0x3);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"field_id", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			// 1 Bit intra_slice_refresh.
			uiFieldLength = 1;
			uiData = (( pucData[0] >> 2 ) & 0x1);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"intra_slice_refresh", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			// 2 Bit frequency_truncation.
			uiFieldLength = 2;
			uiData = (( pucData[0] ) & 0x3);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"frequency_truncation", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
		
			break;
		}
		case 0x4:
		{
			// 5 Bit rep_cntrl.
			uiFieldLength = 5;
			uiData = (( pucData[0] ) & 0x1F);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"rep_cntrl", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			
			break;
		}
		default:
		{
			// 5 Bit reserved.
			uiFieldLength = 5;
			uiData = (( pucData[0] ) & 0x1F);
			pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			
			break;
		}
	}

	return SUCCESS;
}

EResult CPESPacketParser::ParseAdditionalCopyInfo(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 1 Bit marker_bit.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 7 ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
	pTreeNodeTmp = pTreeNode;	
	uiOffset += uiFieldLength;

	// 7 Bit additional_copy_info.
	uiFieldLength = 7;
	uiData = (( pucData[0]  ) & 0x7F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"additional_copy_info", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;
}


EResult CPESPacketParser::ParsePesPacketCrc(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeCurrentLoop, UINT32 uiOffset, const UCHAR8 *pucData)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	// 16 Bit previous_PES_packet_CRC.
	uiFieldLength = 16;
	uiData = (( pucData[0] << 8 ) |  pucData[1] );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"previous_PES_packet_CRC", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
	uiOffset += uiFieldLength;

	return SUCCESS;
}



EResult CPESPacketParser::ParsePESExtension(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 *puiLengthTaken, UINT32 uiLeftLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	*puiLengthTaken= 0;

	UINT32 uiStoredLength = uiLeftLength;
	
	if( 1 > uiStoredLength )
	{
		return SUCCESS;
	}

	// 1 Bit PES_private_data_flag.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_private_data_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPESPrivateDataFlag = uiData;

	// 1 Bit pack_header_field_flag.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"pack_header_field_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPackHeaderFieldFlag = uiData;

	// 1 Bit program_packet_sequence_counter_flag.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 5) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"program_packet_sequence_counter_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiProgramPacketSequenceCounterFlag = uiData;


	// 1 Bit P-STD_buffer_flag.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 4) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"P-STD_buffer_flag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPstdBufferFlag = uiData;

	// 1 Bit reserved.
	uiFieldLength = 3;
	uiData = (( pucData[0]  >> 1) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit PES_extension_flag_2.
	uiFieldLength = 1;
	uiData = (( pucData[0] >> 0) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_extension_flag_2", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;	

	UINT32 uiPESExtensionFlag2 = uiData;

	/*Move.*/
	pucData += 1;
	uiStoredLength -= 1;
	*puiLengthTaken += 1;


	if( 0x1 == uiPESPrivateDataFlag )
	{
		if( 16 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			*puiLengthTaken += uiStoredLength;

			return FAILURE;
		}

		uiFieldLength = 8*16;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_private_data", uiOffset, uiFieldLength,VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 16;
		uiStoredLength -= 16;
		*puiLengthTaken += 16;
	}


	if( 0x1 == uiPackHeaderFieldFlag )
	{
		if( 1 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			*puiLengthTaken += uiStoredLength;

			return FAILURE;
		}

		uiFieldLength = 8*1;
		uiData = ( pucData[0] );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"pack_field_length", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiStoredLength -= 1;
		*puiLengthTaken += 1;

		UINT32 uiPackFieldLength = uiData;

		if( uiPackFieldLength > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			*puiLengthTaken += uiStoredLength;

			return FAILURE;
		}
		
		uiFieldLength = 8*uiPackFieldLength;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"pack_header", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_LOOP_ITEM);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		ParsePackHeader(pTSPacketStore, pTreeList, pTreeNode, uiOffset, pucData, uiPackFieldLength);
		uiOffset += uiFieldLength;

		pucData += uiPackFieldLength;
		uiStoredLength -= uiPackFieldLength;
		*puiLengthTaken += uiPackFieldLength;
	}


	if( 0x1 == uiProgramPacketSequenceCounterFlag )
	{
		if( 2 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			*puiLengthTaken += uiStoredLength;

			return FAILURE;
		}

		uiFieldLength = 1;
		uiData = (( pucData[0] >> 7 ) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 7;
		uiData = (( pucData[0]  ) & 0x7F);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"program_packet_sequence_counter", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		uiData = (( pucData[1] >> 7 ) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		uiData = (( pucData[1] >> 6 ) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"MPEG1_MPEG2_identifier", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 6;
		uiData = (( pucData[1]  ) & 0x3F);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"original_stuff_length", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;


		pucData += 2;
		uiStoredLength -= 2;
		*puiLengthTaken += 2;

	}


	if( 0x1 == uiPstdBufferFlag )
	{
		if( 2 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			*puiLengthTaken += uiStoredLength;

			return FAILURE;
		}

		uiFieldLength = 2;
		uiData = (( pucData[0] >> 6 ) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"'01'", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		uiData = (( pucData[0] >> 5 ) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"P-STD_buffer_scale", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 15;
		uiData = ((( pucData[0] & 0x1F ) << 8) | (pucData[1]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"P-STD_buffer_size", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 2;
		uiStoredLength -= 2;
		*puiLengthTaken += 2;

	}


	if( 0x1 == uiPESExtensionFlag2 )
	{
		if( 1 > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			*puiLengthTaken += uiStoredLength;

			return FAILURE;
		}

		uiFieldLength = 1;
		uiData = (( pucData[0] >> 7 ) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;

		uiFieldLength = 7;
		uiData = ( pucData[0] & 0x7F  );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"PES_extension_field_length", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiStoredLength -= 1;
		*puiLengthTaken += 1;

		UINT32 uiPESExtensionFieldLength = uiData;

		if( uiPESExtensionFieldLength > uiStoredLength )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiStoredLength;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			*puiLengthTaken += uiStoredLength;

			return FAILURE;
		}
		
		uiFieldLength = 8*uiPESExtensionFieldLength;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiPESExtensionFieldLength;
		uiStoredLength -= uiPESExtensionFieldLength;
		*puiLengthTaken += uiPESExtensionFieldLength;
	}


	return SUCCESS;
}



EResult CPESPacketParser::ParsePackHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiLeftLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;


	UINT32 uiStoredLength = uiLeftLength;
	
	if( 15 > uiStoredLength )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiStoredLength;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 32 Bit pack_start_code.
	uiFieldLength = 32;
	uiData = (( pucData[0] << 24) | ( pucData[1] << 16) | ( pucData[2] << 8) | ( pucData[3] ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"pack_start_code", uiOffset, uiFieldLength, uiData);
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	return SUCCESS;
}

EResult CPESPacketParser::GetNextStartCodeAndLength(const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 &uiTakenLengh)
{
	EResult eResult = FAILURE;
	UINT32 uiStoredLengthConst = uiStoredLength;
	uiTakenLengh = 0;
	if( 3 > uiStoredLength )
	{
		return FAILURE;
	}
	
	if(( 0x0 != pucData[0]) || ( 0x0 != pucData[1]) || ( 0x1 != pucData[2]))
	{
		return FAILURE;
	}

	uiStoredLength -= 3;
	pucData += 3;
	uiTakenLengh += 3;

	/*Try to locate the offset of next start code.*/
	while( 3 <= uiStoredLength )
	{
		if(( 0x0 != pucData[0]) || ( 0x0 != pucData[1]) || ( 0x1 != pucData[2]))
		{
			uiStoredLength--;
			uiTakenLengh++;
			pucData++;
			continue;
		}
		else
		{
			return SUCCESS;
		}
	}

	
	/*We have NOT found the next start code.*/
	uiTakenLengh = uiStoredLengthConst;

	return SUCCESS;
}


EResult CPESPacketParser::GetNextStartCode(const UCHAR8 *pucData, UINT32 uiStoredLength)
{
	EResult eResult = FAILURE;
	UINT32 uiStoredLengthConst = uiStoredLength;
	if( 3 > uiStoredLength )
	{
		return FAILURE;
	}
	
	if(( 0x0 != pucData[0]) || ( 0x0 != pucData[1]) || ( 0x1 != pucData[2]))
	{
		return FAILURE;
	}

	return SUCCESS;
}


EStartCodeType CPESPacketParser::GetStartCodeTypeFromStartCode(UINT32 uiParameter)
{
	if(( 0x01 <= uiParameter ) && ( 0xAF >= uiParameter ))
	{
		return START_CODE_SLICE;
	}

	if(( 0xB9 <= uiParameter ) && ( 0xFF >= uiParameter ))
	{
		return START_CODE_SYSTEM;
	}

	switch(uiParameter)
	{
		case 0x00:
			return START_CODE_PICTURE;
		case 0xB0:
		case 0xB1:
		case 0xB6:
			return START_CODE_RESERVED;
		case 0xB2:
			return START_CODE_USER_DATA;
		case 0xB3:
			return START_CODE_SEQUENCE_HEADER;
		case 0xB4:
			return START_CODE_SEQUENCE_ERROR;
		case 0xB5:
			return START_CODE_EXTENSION;
		case 0xB7:
			return START_CODE_SEQUENCE_END;
		case 0xB8:
			return START_CODE_GROUP;
	}

	return START_CODE_RESERVED;
}
LPWSTR CPESPacketParser::GetStartCodeNameFromType(EStartCodeType  eStartCodeType)
{
	switch(eStartCodeType)
	{
		case START_CODE_PICTURE:
			return L"picture_start_code";
		case START_CODE_SLICE:
			return L"slice_start_code";
		case START_CODE_USER_DATA:
			return L"user_data_start_code";
		case START_CODE_SEQUENCE_HEADER:
			return L"sequence_header_code";
		case START_CODE_SEQUENCE_ERROR:
			return L"sequence_error_code";
		case START_CODE_EXTENSION:
			return L"extension_start_code";
		case START_CODE_SEQUENCE_END:
			return L"sequence_end_code";
		case START_CODE_GROUP:
			return L"group_start_code";
		case START_CODE_SYSTEM:
			return L"system start codes";
		case START_CODE_RESERVED:
			return L"reserved";
	}

	return L"reserved";
}
LPWSTR CPESPacketParser::GetStartCodeNameFromStartCode(UINT32 uiParameter)
{
	return GetStartCodeNameFromType(GetStartCodeTypeFromStartCode(uiParameter));
}

EResult CPESPacketParser::ParseVideoContent(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	UINT32 uiNextStartCode = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
	UINT32 uiStartCode = ( pucData[3]  );
	EStartCodeType  eStartCodeType = GetStartCodeTypeFromStartCode(uiStartCode);

	switch(eStartCodeType)
	{
		case START_CODE_SEQUENCE_HEADER:
		{
			ParseSequenceHeader(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset, uiLengthTaken);
			break;
		}
		case START_CODE_EXTENSION:
		{
			ParseSequenceExtension(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset, uiLengthTaken);
			break;
		}
		case START_CODE_GROUP:
		{
			ParseGopHeader(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset, uiLengthTaken);
			break;			
		}
		case START_CODE_PICTURE:
		{
			ParsePictureHeader(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset, uiLengthTaken);
			break;			

		}
		case START_CODE_SLICE:
		{
			//ParsePictureHeaderAndSlice(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset, uiLengthTaken);
			ParseSlice(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset, uiLengthTaken);
			break;			
		}
		case START_CODE_USER_DATA:
		case START_CODE_SEQUENCE_ERROR:
		case START_CODE_SEQUENCE_END:
		case START_CODE_SYSTEM:
		case START_CODE_RESERVED:
		{
			/*24 Bit next_start_code*/
			uiFieldLength = 24;
			uiData = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"next_start_code", uiOffset, uiFieldLength, uiData );
			pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
			pTreeNodeTmp = pTreeNode;

			uiOffset += uiFieldLength;

			/*8 Bit start_code*/
			uiFieldLength = 8;
			uiData = ( ( pucData[3]  ) );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"start_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
			pTreeNode->m_strText.Format(L"start_code[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetStartCodeNameFromStartCode(uiData));
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;

			
			uiOffset += uiFieldLength;

			uiFieldLength = (uiNextStartCodeOffset - 4)*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"data byte to be parsed", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			uiLengthTaken += uiNextStartCodeOffset;
			pucData += uiNextStartCodeOffset;
			uiStoredLength -= uiNextStartCodeOffset;
			
		}
		
	}

	return SUCCESS;
}



EResult CPESPacketParser::ParseSequenceHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	uiLengthTaken += uiNextStartCodeOffset;
	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE;
	pTreeList->UpdateImageIndex(pTreeNodeInput);

	if( 12 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}



	/*24 Bit next_start_code*/
	uiFieldLength = 24;
	uiData = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"next_start_code", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*8 Bit start_code*/
	uiFieldLength = 8;
	uiData = ( ( pucData[3]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"start_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"start_code[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetStartCodeNameFromStartCode(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	uiFieldLength = 12;
	uiData = ( ( pucData[0]  << 4)  | (( pucData[1] >> 4) & 0xF) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"horizontal_size_value", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 12;
	uiData = ( (( pucData[1]  & 0xF ) << 8)  | ( pucData[2] ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"vertical_size_value", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 4;
	uiData = ( ( pucData[3] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"aspect_ratio_information", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 4;
	uiData = ( ( pucData[3]  ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_rate_code", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	uiFieldLength = 18;
	uiData = ( ( pucData[0] << 10  ) | ( pucData[1] << 2  ) | ( ( pucData[2] >> 6)  & 0x3  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"bit_rate_value", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"bit_rate_value[%d]: 0x%02X,  %f Mbps", uiFieldLength, uiData, (400 * 1.00 )*uiData/(1024 *1024) );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[2] >> 5) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 10;
	uiData = ( ( ( pucData[2] & 0x1F ) << 5 ) | (( pucData[3] >> 3) & 0x1F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"vbv_buffer_size_value", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = (( pucData[3] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"constrained_parameters_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = (( pucData[3] >> 1) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"load_intra_quantiser_matrix", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiLoadIntraQuantiserMatrix = uiData;

	pucData += 3;
	uiStoredLength -= 3;
	uiNextStartCodeOffset -= 3;

	if( 0x1 == uiLoadIntraQuantiserMatrix )
	{
		if( (64 + 1) > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

	
		uiFieldLength = 8*64;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"intra_quantiser_matrix[64]", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 64;
		uiStoredLength -= 64;
		uiNextStartCodeOffset -= 64;
	
	}

	uiFieldLength = 1;
	uiData = (( pucData[0] ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"load_non_intra_quantiser_matrix", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiLoadNonIntraQuantiserMatrix = uiData;

	pucData += 1;
	uiStoredLength -= 1;
	uiNextStartCodeOffset -= 1;

	if( 0x1 == uiLoadNonIntraQuantiserMatrix )
	{
		if( ( 64 ) > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

	
		uiFieldLength = 8*64;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"non_intra_quantiser_matrix[64]", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 64;
		uiStoredLength -= 64;
		uiNextStartCodeOffset -= 64;
	
	}


	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;
}


EResult CPESPacketParser::ParseSequenceExtension(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	uiLengthTaken += uiNextStartCodeOffset;
	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 5 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}



	/*24 Bit next_start_code*/
	uiFieldLength = 24;
	uiData = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"next_start_code", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*8 Bit start_code*/
	uiFieldLength = 8;
	uiData = ( ( pucData[3]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"start_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"start_code[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetStartCodeNameFromStartCode(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	/*To parse the extension.*/
	EExtensionStartCodeIdentifier eExtensionStartCodeIdentifier = GetExtensionStartCodeIdentifierTypeFromId(uiData);
	switch(eExtensionStartCodeIdentifier)
	{
		case EXTENSION_ID_SEQUENCE:
			return ParseExtensionSequence(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_SEQUENCE_DISPLAY:
			return ParseExtensionSequenceDisplay(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_QUANT_MATRIX:
			return ParseExtensionQuantMatrix(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_COPYRIGHT:
			return ParseExtensionCopyright(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_SEQUENCE_SCALABLE:
			return ParseExtensionSequenceScalable(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_PICTURE_DISPLAY:
			return ParseExtensionPictureDisplay(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_PICTURE_CODING:
			return ParseExtensionPictureCoding(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_PICTURE_SPATIAL_SCALABLE:
			return ParseExtensionPictureSpatialScalable(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
		case EXTENSION_ID_PICTURE_TEMPORAL_SCALABLE:
			return ParseExtensionPictureTemporalScalable(pTSPacketStore, pTreeList, pTreeNodeInput, uiOffset, pucData, uiStoredLength, uiNextStartCodeOffset);
	}
	return SUCCESS;
}

EResult CPESPacketParser::ParseExtensionSequence(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 6 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 8;
	uiData = ((  (pucData[0] & 0xF) << 4 ) | (( pucData[1] >> 4) & 0xF));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"profile_and_level_indication", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[1] >> 3 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"progressive_sequence", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 2;
	uiData = ( ( pucData[1] >> 1 ) & 0x3 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"chroma_format", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"chroma_format[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetChromaFormatName(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 2;
	uiData = ((( ( pucData[1] ) & 0x1 ) << 1) | (( pucData[2] >> 7) & 0x1) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"horizontal_size_extension", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 2;
	uiData = ( ( pucData[2] >> 5 ) & 0x3 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"vertical_size_extension", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 12;
	uiData = (( ( pucData[2] & 0x1F ) << 7 ) | (( pucData[3] >> 1) & 0x7F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"bit_rate_extension", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( pucData[3] & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 8;
	uiData = ( pucData[4] );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"vbv_buffer_size_extension", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = (( pucData[5]  >> 7 ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"low_delay", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 2;
	uiData = (( pucData[5]  >> 5 ) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_rate_extension_n", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 5;
	uiData = (( pucData[5] ) & 0x1F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_rate_extension_d", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 6;
	uiStoredLength -= 6;
	uiNextStartCodeOffset -= 6;

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}


EResult CPESPacketParser::ParseExtensionSequenceDisplay(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 1 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 3;
	uiData = ((pucData[0] >> 1) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"video_format", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[0] ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"colour_description", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiStoredLength -= 1;
	uiNextStartCodeOffset -= 1;
	
	UINT32 uiColourDescription = uiData;
	if( 0x1 == uiColourDescription)
	{
		if( 3 > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 8;
		uiData = ( pucData[0] );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"colour_primaries", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 8;
		uiData = ( pucData[1] );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"transfer_characteristics", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 8;
		uiData = ( pucData[2] );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"matrix_coefficients", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 3;
		uiStoredLength -= 3;
		uiNextStartCodeOffset -= 3;
	}


	if( 4 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 14 Bit display_horizontal_size.
	uiFieldLength = 14;
	uiData = ((pucData[0] << 6 ) | (( pucData[1] >> 2) & 0x3F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"display_horizontal_size", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = (( pucData[1] >> 1) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 14 Bit display_vertical_size.
	uiFieldLength = 14;
	uiData = (((pucData[1] & 0x1) << 13 ) | (( pucData[2] << 5)) | (( pucData[3] >> 3) & 0x1F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"display_vertical_size", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}



EResult CPESPacketParser::ParseExtensionQuantMatrix(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 1 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 3) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"load_intra_quantiser_matrix", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	if( 0x1 == uiData )
	{
		if( (64 + 1) > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

	
		uiFieldLength = 8*64;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"intra_quantiser_matrix[64]", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 64;
		uiStoredLength -= 64;
		uiNextStartCodeOffset -= 64;
	
	}

	uiFieldLength = 1;
	uiData = ((pucData[0] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"load_non_intra_quantiser_matrix", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	if( 0x1 == uiData )
	{
		if( (64 + 1) > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

	
		uiFieldLength = 8*64;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"non_intra_quantiser_matrix[64]", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 64;
		uiStoredLength -= 64;
		uiNextStartCodeOffset -= 64;
	
	}



	uiFieldLength = 1;
	uiData = ((pucData[0] >> 1) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"chroma_intra_quantiser_matrix", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	if( 0x1 == uiData )
	{
		if( (64 + 1) > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

	
		uiFieldLength = 8*64;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"chroma_intra_quantiser_matrix[64]", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 64;
		uiStoredLength -= 64;
		uiNextStartCodeOffset -= 64;
	
	}

	uiFieldLength = 1;
	uiData = ((pucData[0] ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"chroma_non_intra_quantiser_matrix", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	if( 0x1 == uiData )
	{
		if( (64 + 1) > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

	
		uiFieldLength = 8*64;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"chroma_non_intra_quantiser_matrix[64]", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 64;
		uiStoredLength -= 64;
		uiNextStartCodeOffset -= 64;
	
	}

	pucData += 1;
	uiStoredLength -= 1;
	uiNextStartCodeOffset -= 1;
		
	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}


EResult CPESPacketParser::ParseExtensionCopyright(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 11 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 1;
	uiData = ( ( pucData[0] >> 3 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"copyright_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 8;
	uiData = ((  (pucData[0] & 0x7) << 5 ) | (( pucData[1] >> 3) & 0x1F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"copyright_identifier", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[1] >> 2 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"original_or_copy", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 7;
	uiData = (( ( pucData[1]  ) & 0x3 ) | (( pucData[2] >> 3) & 0x1F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[2] >> 2 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 20;
	uiData = ((( ( pucData[2] ) & 0x3 ) << 18) | ( (pucData[3]) << 10 ) | ( (pucData[4]) << 2 ) | ( (pucData[5] >> 6) & 0x3 )  );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"copyright_number_1", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[5] >> 5 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 22;
	uiData = ((( ( pucData[5] ) & 0x1F ) << 17) | ( (pucData[6]) << 9 ) | ( (pucData[7]) << 1 ) | ( (pucData[8] >> 7) & 0x1 )  );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"copyright_number_2", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[8] >> 6 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 22;
	uiData = ((( ( pucData[8] ) & 0x3F ) << 16) | ( (pucData[9]) << 8 ) | ( (pucData[10]) )  );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"copyright_number_3", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 11;
	uiStoredLength -= 11;
	uiNextStartCodeOffset -= 11;

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}


EResult CPESPacketParser::ParseExtensionSequenceScalable(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 2 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 2;
	uiData = ((pucData[0] >> 2) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"scalable_mode", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"scalable_mode[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetScalableModeName(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiScalableMode = uiData;

	uiFieldLength = 4;
	uiData = ((((pucData[0] ) & 0x3) << 2) | ((pucData[1]  >> 6) & 0x3));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"layer_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	if( 0x1 == uiScalableMode)
	{
		/*spatial scalability*/
		if( 8 > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 14;
		uiData = (( ( pucData[1]  & 0x3F) << 8) | (pucData[2]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"lower_layer_prediction_horizontal_size", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		uiData = ( (( pucData[3] ) >> 7) & 0x1 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 14;
		uiData = (( ( pucData[3]  & 0x7F) << 7) | ( ( (pucData[4]) >> 1) & 0x7F));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"lower_layer_prediction_vertical_size", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 5;
		uiData = ( ( ( ( pucData[4] ) & 0x1 ) << 4) | ( ( pucData[5] >> 4) & 0xF));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"horizontal_subsampling_factor_m", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 5;
		uiData = ( ( ( pucData[5] ) & 0xF) | ( ( pucData[6] >> 7) & 0x1));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"horizontal_subsampling_factor_n", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 5;
		uiData = ( ( pucData[6] >> 2) & 0x1F);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"vertical_subsampling_factor_m", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 5;
		uiData = ( ( ( pucData[6] & 0x3) << 3) | (( pucData[7] >> 5) & 0x7));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"vertical_subsampling_factor_n", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 8;
		uiStoredLength -= 8;
		uiNextStartCodeOffset -= 8;
	}
	else if( 0x1 == uiScalableMode)
	{
		/*temporal scalability*/
		if( 3 > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}

		uiFieldLength = 1;
		uiData = ( (( pucData[1] ) >> 5) & 0x1 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"picture_mux_enable", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		if( 0x1 == uiData )
		{
			uiFieldLength = 1;
			uiData = ( (( pucData[1] ) >> 4) & 0x1 );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"mux_to_progressive_sequence", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			uiFieldLength = 3;
			uiData = ( (( pucData[1] ) >> 1) & 0x7 );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"picture_mux_order", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			uiFieldLength = 3;
			uiData = ( (( pucData[1]  & 0x1 ) << 2) |((pucData[2] >> 6) & 0x3) );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"picture_mux_factor", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			
		}
		else
		{
			uiFieldLength = 3;
			uiData = ( (( pucData[1] ) >> 2) & 0x7 );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"picture_mux_order", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			uiFieldLength = 3;
			uiData = ( (( pucData[1]  & 0x3 ) << 1) |((pucData[2] >> 7) & 0x1) );
			pTreeNode  = new CTreeNode(pTSPacketStore, L"picture_mux_factor", uiOffset, uiFieldLength, uiData );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
		}

		pucData += 3;
		uiStoredLength -= 3;
		uiNextStartCodeOffset -= 3;

	}

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}


EResult CPESPacketParser::ParseExtensionPictureDisplay(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;
	UINT32 uiNextStartCodeOffsetBits = uiNextStartCodeOffset*8;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 1 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiNextStartCodeOffsetBits -= 4;

	while( 34 <= uiNextStartCodeOffsetBits )	
	{
		uiFieldLength = 16;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_centre_horizontal_offset", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		
		uiFieldLength = 16;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_centre_vertical_offset", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		
		uiNextStartCodeOffsetBits -= 34;
	}
	
	return SUCCESS;

}


EResult CPESPacketParser::ParseExtensionPictureCoding(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 5 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 4;
	uiData = ( ( pucData[0] ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"forward_horizontal", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 4;
	uiData = ( ( pucData[1]  >> 4) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"forward_vertical", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 4;
	uiData = ( ( pucData[1] ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"backward_horizontal", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 4;
	uiData = ( ( pucData[2]  >> 4) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"backward_vertical", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 2;
	uiData = ( ( pucData[2] >> 2 ) & 0x3 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"intra_dc_precision", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 2;
	uiData = ( ( pucData[2] ) & 0x3 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"picture_structure", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 7 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"top_field_first", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 6 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_pred_frame_dct", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 5 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"concealment_motion_vectors", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 4 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"q_scale_type", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 3 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"intra_vlc_format", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 2 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"alternate_scan", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 1 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"repeat_first_field", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3]  ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"chroma_420_type", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[4] >> 7 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"progressive_frame", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[4] >> 6 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"composite_display_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiCompositeDisplayFlag = uiData;

	if( 0x1 == uiCompositeDisplayFlag )
	{
		if( 2 > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			return FAILURE;
		}
		
		uiFieldLength = 1;
		uiData = ( ( pucData[4] >> 5 ) & 0x1 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"v_axis", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 3;
		uiData = ( ( pucData[4] >> 2 ) & 0x7 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"field_sequence", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		uiData = ( ( pucData[4] >> 1 ) & 0x1 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"sub_carrier", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 7;
		uiData = (( ( pucData[4] & 0x1 ) << 6 ) | (( pucData[5] >> 2) & 0x3F));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"burst_amplitude", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 8;
		uiData = (( ( pucData[5] & 0x3 ) << 6 ) | (( pucData[6] >> 2) & 0x3F));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"sub_carrier_phase", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 7;
		uiStoredLength -= 7;
		uiNextStartCodeOffset -= 7;

	}
	else
	{
		pucData += 5;
		uiStoredLength -= 5;
		uiNextStartCodeOffset -= 5;
	}

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}


EResult CPESPacketParser::ParseExtensionPictureSpatialScalable(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 7 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 8;
	uiData = ((  (pucData[0] & 0xF) << 6 ) | (( pucData[1] >> 2) & 0x3F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"lower_layer_temporal_reference", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[1] >> 1 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 15;
	uiData = (( ( pucData[1] & 0x1) << 14) | ( pucData[2] << 6 ) | ( ( pucData[3]  >> 2)& 0x3F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"lower_layer_horizontal_offset", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 1 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 15;
	uiData = (( ( pucData[3] & 0x1) << 14) | ( pucData[4] << 6 ) | ( ( pucData[5]  >> 2)& 0x3F ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"lower_layer_vertical_offset", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	uiFieldLength = 2;
	uiData = ( ( pucData[5] )& 0x3 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"spatial_temporal_weight_code_table_index", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = (( pucData[6]  >> 7 ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"lower_layer_progressive_frame", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = (( pucData[6]  >> 6 ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"lower_layer_deinterlaced_field_select", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 7;
	uiStoredLength -= 7;
	uiNextStartCodeOffset -= 7;

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}


EResult CPESPacketParser::ParseExtensionPictureTemporalScalable(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset )
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	pTreeNodeInput->m_eNodeType = NODE_SEQUENCE_EXTENSION;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 4 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4 ) & 0xF );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"extension_start_code_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"extension_start_code_identifier[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetExtensionStartCodeIdentifierNameFromId(uiData));
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 2;
	uiData = ( ( pucData[0]  >> 2 ) & 0x3 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reference_select_code", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 10;
	uiData = (( ( pucData[0]  & 0x3 ) << 8  ) | ( pucData[1] ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"forward_temporal_reference", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	uiFieldLength = 1;
	uiData = (( pucData[2]  >> 7 ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"marker_bit", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 10;
	uiData = (( ( pucData[2]  & 0x7F ) << 3  ) | ( pucData[3] ));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"backward_temporal_reference", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;

}


EResult CPESPacketParser::ParseGopHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	uiLengthTaken += uiNextStartCodeOffset;
	pTreeNodeInput->m_eNodeType = NODE_GOP;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 8 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}



	/*24 Bit next_start_code*/
	uiFieldLength = 24;
	uiData = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"next_start_code", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*8 Bit start_code*/
	uiFieldLength = 8;
	uiData = ( ( pucData[3]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"start_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"start_code[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetStartCodeNameFromStartCode(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	uiFieldLength = 25;
	uiData = ( ( pucData[0] << 17 ) | ( pucData[1] << 9) | ( pucData[2] << 1) | ((pucData[3] >> 7)  & 0x1));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"time_code", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 6 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"closed_gop", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiFieldLength = 1;
	uiData = ( ( pucData[3] >> 5 ) & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"broken_link", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;
}

EResult CPESPacketParser::ParsePictureHeader(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	uiLengthTaken += uiNextStartCodeOffset;
	pTreeNodeInput->m_eNodeType = NODE_FRAME;
	pTreeList->UpdateImageIndex(pTreeNodeInput);

	if( 8 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	/*24 Bit next_start_code*/
	uiFieldLength = 24;
	uiData = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"next_start_code", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*8 Bit start_code*/
	uiFieldLength = 8;
	uiData = ( ( pucData[3]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"start_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"start_code[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetStartCodeNameFromStartCode(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	uiFieldLength = 10;
	uiData = ( ( pucData[0] << 2 ) | ( (pucData[1] >> 6)  & 0x3) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"temporal_reference", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	
	uiFieldLength = 3;
	uiData = ( ( pucData[1] >> 3 ) & 0x7 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"picture_coding_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"picture_coding_type[%d]: 0x%02X, Type: %s", uiFieldLength, uiData, GetPictureCodingTypeName(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiPictureCodingType = uiData;
	if(( 0x1 <= uiPictureCodingType ) && ( 0x3 >= uiPictureCodingType ))
	{
		switch( uiPictureCodingType )
		{
			case 0x1:
			{
				pTreeNodeInput->m_eNodeType = NODE_I_FRAME;
				break;
			}
			case 0x2:
			{
				pTreeNodeInput->m_eNodeType = NODE_P_FRAME;
				break;
			}
			case 0x3:
			{
				pTreeNodeInput->m_eNodeType = NODE_B_FRAME;
				break;
			}
		}

		pTreeList->UpdateImageIndex(pTreeNodeInput);
	}

	uiFieldLength = 16;
	uiData = (( ( pucData[1] & 0x7 ) << 13 ) | ( pucData[2] << 5 ) | (( pucData[3] >> 3) & 0x1F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"vbv_delay", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	const UCHAR8 *pucDataTemp = pucData + 3;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	if( 0x3 == uiPictureCodingType )
	{
		if( 1 > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}
	
		uiFieldLength = 1;
		uiData = ( ( pucDataTemp[0] >> 2 ) & 0x1 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"full_pel_forward_vector", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 3;
		uiData = ( (( ( pucDataTemp[0]  ) & 0x3 ) << 1) | (pucDataTemp[1] >> 7) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"forward_f_code", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 1;
		uiData = ( ( pucDataTemp[1] >> 6 ) & 0x1 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"full_pel_backward_vector", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 3;
		uiData = (  (pucDataTemp[1] >>3) & 0x7);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"backward_f_code", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;	
	}

	if( 0x2 == uiPictureCodingType )
	{
		if( 1 > uiNextStartCodeOffset )
		{
			/*Invalid end.*/
			uiFieldLength = 8*uiNextStartCodeOffset;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			return FAILURE;
		}
	
		uiFieldLength = 1;
		uiData = ( ( pucDataTemp[0] >> 2 ) & 0x1 );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"full_pel_forward_vector", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		uiFieldLength = 3;
		uiData = ( (( ( pucDataTemp[0]  ) & 0x3 ) << 1) | (pucDataTemp[1] >> 7) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"forward_f_code", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		
	}

	if( ( 0x2 == uiPictureCodingType ) || ( 0x3 == uiPictureCodingType ))
	{
		pucData += 1;
		uiStoredLength -= 1;
		uiNextStartCodeOffset -= 1;
	}

	
	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;
}


EResult CPESPacketParser::ParseSlice(CTSPacketStore * pTSPacketStore, CTreeList *pTreeList, CTreeNode * pTreeNodeInput, UINT32 uiOffset, const UCHAR8 *pucData, UINT32 uiStoredLength, UINT32 uiNextStartCodeOffset, UINT32 &uiLengthTaken)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;

	UINT32 uiData;
	UINT32 uiFieldLength;

	uiLengthTaken += uiNextStartCodeOffset;
	pTreeNodeInput->m_eNodeType = NODE_SLICE;
	pTreeList->UpdateImageIndex(pTreeNodeInput);
	
	if( 8 > uiNextStartCodeOffset )
	{
		/*Invalid end.*/
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	/*24 Bit next_start_code*/
	uiFieldLength = 24;
	uiData = (( pucData[0] << 16 ) | ( pucData[1] << 8 ) | ( pucData[2]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"next_start_code", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode , pTreeNodeInput);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*8 Bit start_code*/
	uiFieldLength = 8;
	uiData = ( ( pucData[3]  ) );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"start_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"start_code[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetStartCodeNameFromStartCode(uiData));
	pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiStoredLength -= 4;
	uiNextStartCodeOffset -= 4;

	if( 0 != uiNextStartCodeOffset )
	{
		uiFieldLength = 8*uiNextStartCodeOffset;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"slice data bytes", uiOffset, uiFieldLength, VALUE_ZERO,  NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode , pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
	}

	return SUCCESS;
}

