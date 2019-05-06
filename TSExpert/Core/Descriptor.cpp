#include "StdAfx.h"
#include "Descriptor.h"
#include "TSParser.h"
#include "TSPacketStore.h"
#include "SectionHeaderReader.h"

EResult CDescriptor::ParseMPEGDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UCHAR8 ucDescriptorTag;

	ucDescriptorTag = pucData[0];
	switch(ucDescriptorTag)
	{
		//video_stream_descriptor
		case 0x02:
		{
			return ParseVideoStreamDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//audio_stream_descriptor
		case 0x03:
		{
			return ParseAudioStreamDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//hierarchy_descriptor
		case 0x04:
		{
			return ParseHierarchyDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//registration_descriptor
		case 0x05:
		{
			return ParseRegistrationDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//data_stream_alignment_descriptor
		case 0x06:
		{
			return ParseDataStreamAlignmentDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//target_background_grid_descriptor
		case 0x07:
		{
			return ParseTargetBackgroundGridDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//video_window_descriptor
		case 0x08:
		{
			return ParseVideoWindowDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//CA_descriptor
		case 0x09:
		{
			return ParseCADescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//ISO_639_language_descriptor
		case 0x0A:
		{
			return ParseISO639LanguageDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//system_clock_descriptor
		case 0x0B:
		{
			return ParseSystemClockDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//multiplex_buffer_utilization_descriptor
		case 0x0C:
		{
			return ParseMultiplexBufferUtilizationDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//copyright_descriptor
		case 0x0D:
		{
			return ParseCopyrightDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//maximum_bitrate_descriptor
		case 0x0E:
		{
			return ParseMaximumBitrateDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//private_data_indicator_descriptor
		case 0x0F:
		{
			return ParsePrivateDataIndicatorDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//smoothing_buffer_descriptor
		case 0x10:
		{
			return ParseSmoothingBufferDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//STD_descriptor
		case 0x11:
		{
			return ParseSTDDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//IBP_descriptor
		case 0x12:
		{
			return ParseIBPDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}

#if 0
		/* MPEG DSM-CC */
		//carousel_identifier_descriptor
		case 0x13:
			break;
		//association_tag_descriptor
		case 0x14:
			break;
		//deferred_association_tag_descriptor
		case 0x15:
			break;
		//ISO/IEC13818-6 Reserved
		case 0x16:
			break;

		/* DSM-CC stream descriptors */
		//NPT_reference_descriptor
		case 0x17:
			break;
		//NPT_endpoint_descriptor
		case 0x18:
			break;
		//stream_mode_descriptor
		case 0x19:
			break;
		//stream_event_descriptor
		case 0x1A:
			break;

		/* MPEG-4 descriptors */
		//MPEG4_video_descriptor
		case 0x1B:
			break;
		//MPEG4_audio_descriptor
		case 0x1C:
			break;
		//IOD_descriptor
		case 0x1D:
			break;
		//SL_descriptor
		case 0x1E:
			break;
		//FMC_descriptor
		case 0x1F:
			break;
		//External_ES_ID_descriptor
		case 0x20:
			break;
		//MuxCode_descriptor
		case 0x21:
			break;
		//FMXBufferSize_descriptor
		case 0x22:
			break;
		//MultiplexBuffer_descriptor
		case 0x23:
			break;
		//FlexMuxTiming_descriptor
		//case 0x24:break;

		//Content_labeling_descriptor
		case 0x24:
			break;

		/* TV ANYTIME TS 102 323 descriptors:ISO 13818-1 */
		//metadata_pointer_descriptor
		case 0x25:
			break;
		//metadata_descriptor
		case 0x26:
			break;
		//metadata_STD_descriptor
		case 0x27:
			break;
		//AVC_video_descriptor
		case 0x28:
			break;
		//IPMP_descriptor (MPEG-2 IPMP:ISO 13818-11)
		case 0x29:
			break;
		//AVC_timing_and_HRD_descriptor
		case 0x2A:
			break;
#endif
		default:
		{
			return ParseCommonDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
	}

	return SUCCESS;
}

EResult CDescriptor::ParseDVBDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UCHAR8 ucDescriptorTag;

	ucDescriptorTag = pucData[0];
	switch(ucDescriptorTag)
	{
		 //network_name_descriptor
		case 0x40:
		{
			return ParseNetworkNameDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}

		 //service_list_descriptor
		case 0x41:
		{
			return ParseServiceListDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}

		 //stuffing_descriptor
		case 0x42:
		{
			return ParseStuffingDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //satellite_delivery_system_descriptor
		case 0x43:
		{
			return ParseSatelliteDeliverySystemDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //cable_delivery_system_descriptor
		case 0x44:
		{
			return ParseCableDeliverySystemDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//VBI_data_descriptor
		case 0x45:
		{
			return ParseVBIDataDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //VBI_teletext_descriptor
		case 0x46:
		{
			return ParseVBITeletextDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //bouquet_name_descriptor
		case 0x47:
		{
			return ParseBouquetNameDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//service_descriptor
		case 0x48:
		{
			return ParseServiceDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //country_availibility_descriptor
		case 0x49:
		{
			return ParseCountryAvailabilityDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //linkage_descriptor
		case 0x4A:
		{
			return ParseLinkageDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //NVOD_reference_descriptor
		case 0x4B:
		{
			return ParseNVODReferenceDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}

		 //time_shifted_service_descriptor
		case 0x4C:
		{
			return ParseTimeShiftedServiceDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //short_event_descriptor
		case 0x4D:
		{
			return ParseShortEventDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //extended_event_descriptor
		case 0x4E:
		{
			return ParseExtendedEventDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //time_shifted_event_descriptor
		case 0x4F:
		{
			return ParseTimeShiftedEventDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //component_descriptor
		case 0x50:
		{
			return ParseComponentDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //mosaic_descriptor
		case 0x51:
		{
			return ParseMosaicDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //stream_identifier_descriptor
		case 0x52:
		{
			return ParseStreamIdentifierDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //CA_identifier_descriptor
		case 0x53:
		{
			return ParseCAIdentifierDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //content_descriptor
		case 0x54:
		{
			return ParseContentDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //parental_rating_descriptor
		case 0x55:
		{
			return ParseParentalRatingDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //teletext_descriptor
		case 0x56:
		{
			return ParseTeletextDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //telephone_descriptor
		case 0x57:
		{
			return ParseTelephoneDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //local_time_offset_descriptor
		case 0x58:
		{
			return ParseLocalTimeOffsetDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //subtitling_descriptor
		case 0x59:
		{
			return ParseSubtitlingDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //terrestrial_delivery_system_descriptor
		case 0x5A:
		{
			return ParseTerrestrialDeliverySystemDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //multilingual_network_name_descriptor
		case 0x5B:
		{
			return ParseMultilingualNetworkNameDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //multilingual_bouquet_name_descriptor
		case 0x5C:
		{
			return ParseMultilingualBouquetNameDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //multilingual_service_name_descriptor
		case 0x5D:
		{
			return ParseMultilingualServiceNameDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //multilingual_component_descriptor
		case 0x5E:
		{
			return ParseMultilingualComponentDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //private_data_specifier_descriptor
		case 0x5F:
		{
			return ParsePrivateDataSpecifierDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //service_move_descriptor
		case 0x60:
		{
			return ParseServiceMoveDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//short_smoothing_buffer_descriptor
		case 0x61:
		{
			return ParseShortSmoothingBufferDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //frequency_list_descriptor
		case 0x62:
		{
			return ParseFrequencyListDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //partial_transport_stream_descriptor
		case 0x63:
		{
			return ParsePartialTransportStreamDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //data_broadcast_descriptor
		case 0x64:
		{
			return ParseDataBroadcastDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //scrambling_descriptor
		case 0x65:
		{
			return ParseScramblingDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}		
		 //data_broadcast_id_descriptor
		case 0x66:
		{
			return ParseDataBroadcastIdDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //transport_stream_descriptor
		case 0x67:
		{
			return ParseCommonDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //DSNG_descriptor
		case 0x68:
		{
			return ParseCommonDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //PDC_descriptor
		case 0x69:
		{
			return ParsePDCDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //AC3_descriptor
		case 0x6A:
		{
			return ParseAC3Descriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //ancillary_data_descriptor
		case 0x6B:
		{
			return ParseAncillaryDataDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //cell_list_descriptor
		case 0x6C:
		{
			return ParseCellListDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //cell_frequency_list_descriptor
		case 0x6D:
		{
			return ParseCellFrequencyLinkDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //announcement_support_descriptor
		case 0x6E:
		{
			return ParseAnnouncementSupportDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //application_signalling_descriptor
		case 0x6F:
		{
			return ParseApplicationSignallingDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //adaptation_field_data_descriptor
		case 0x70:
		{
			return ParseAdaptationFieldDataDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //service_identifier_descriptor
		case 0x71:
		{
			return ParseServiceIdentifierDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //service_availability_descriptor
		case 0x72:
		{
			return ParseServiceAvailabilityDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //default_authority_descriptor 		// TS 102 323
		case 0x73:
		{
			return ParseCommonDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //related_content_descriptor 		// TS 102 323
		case 0x74:
		{
			return ParseCommonDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //TVA_id_descriptor 			// TS 102 323
		case 0x75:
		{
			return ParseTVAIdDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//content_identifier_descriptor 	// TS 102 323
		case 0x76:
		{
			return ParseContentIdentifierDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //time_slice_fec_identifier_descriptor 	// EN 300 468 v1.6.1
		case 0x77:
		{
			return ParseTimeSliceFecIdentifierDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		 //ECM_repetition_rate_descriptor 	// EN 300 468 v1.6.1
		case 0x78:
		{
			return ParseECMRepetitionRateDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		//extension descriptor
		case 0x7F:
		{
			return ParseExtensionDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
		default:
		{
			return ParseCommonDescriptor(pTSPacketStore, pTreeList,pTreeNodeInput, pucData, uiOffset);
		}
	}

	return SUCCESS;
}


LPWSTR CDescriptor::GetDescriptorName(UCHAR8 ucTag)
{
	if( 0x40 >  ucTag)
	{
		return GetMPEGDescriptorName(ucTag);
	}
	else
	{
		return GetDVBDescriptorName(ucTag);
	}
};

LPWSTR CDescriptor::GetMPEGDescriptorName(UCHAR8 ucTag)
{
	if(( 0x2B <= ucTag ) && ( 0x3F >= ucTag ))
	{
		return L"ITU-T.Rec.H.222.0|ISO/IEC13818-1 Reserved";
	}

	switch (ucTag)
	{
		case 0x00:
			return L"Reserved";  
		case 0x01:
			return L"Reserved";
		case 0x02:
			return L"video_stream_descriptor";
		case 0x03:
			return L"audio_stream_descriptor";
		case 0x04:
			return L"hierarchy_descriptor";
		case 0x05:
			return L"registration_descriptor";
		case 0x06:
			return L"data_stream_alignment_descriptor";
		case 0x07:
			return L"target_background_grid_descriptor";
		case 0x08:
			return L"video_window_descriptor";
		case 0x09:
			return L"CA_descriptor";
		case 0x0A:
			return L"ISO_639_language_descriptor";
		case 0x0B:
			return L"system_clock_descriptor";
		case 0x0C:
			return L"multiplex_buffer_utilization_descriptor";
		case 0x0D:
			return L"copyright_descriptor";
		case 0x0E:
			return L"maximum_bitrate_descriptor";
		case 0x0F:
			return L"private_data_indicator_descriptor";
		case 0x10:
			return L"smoothing_buffer_descriptor";
		case 0x11:
			return L"STD_descriptor";
		case 0x12:
			return L"IBP_descriptor";                


		 /* MPEG DSM-CC */
		case 0x13:
			return L"carousel_identifier_descriptor";
		case 0x14:
			return L"association_tag_descriptor";
		case 0x15:
			return L"deferred_association_tag_descriptor";
		case 0x16:
			return L"ISO/IEC13818-6 Reserved";

		/* DSM-CC stream descriptors */
		case 0x17:
			return L"NPT_reference_descriptor";
		case 0x18:
			return L"NPT_endpoint_descriptor";
		case 0x19:
			return L"stream_mode_descriptor";
		case 0x1A:
			return L"stream_event_descriptor";

		/* MPEG-4 descriptors */
		case 0x1B:
			return L"MPEG4_video_descriptor";
		case 0x1C:
			return L"MPEG4_audio_descriptor";
		case 0x1D:
			return L"IOD_descriptor";
		case 0x1E:
			return L"SL_descriptor";
		case 0x1F:
			return L"FMC_descriptor";
		case 0x20:
			return L"External_ES_ID_descriptor";
		case 0x21:
			return L"MuxCode_descriptor";
		case 0x22:
			return L"FMXBufferSize_descriptor";
		case 0x23:
			return L"MultiplexBuffer_descriptor";
		//case 0x24:0x24 return L"FlexMuxTiming_descriptor";
		case 0x24:
			return L"Content_labeling_descriptor";

		/* TV ANYTIME TS 102 323 descriptors:ISO 13818-1 */
		case 0x25:
			return L"metadata_pointer_descriptor";
		case 0x26:
			return L"metadata_descriptor";
		case 0x27:
			return L"metadata_STD_descriptor";
		case 0x28:
			return L"AVC_video_descriptor";
		case 0x29:
			return L"IPMP_descriptor (MPEG-2 IPMP:ISO 13818-11)";
		case 0x2A:
			return L"AVC_timing_and_HRD_descriptor";
	};

	return L"Forbidden descriptor in mpeg context";
			
}

LPWSTR CDescriptor::GetDVBDescriptorName(UCHAR8 ucTag)
{
	if(( 0x80 <= ucTag ) && ( 0xAF >= ucTag ))
	{
		return L"User defined/ATSC reserved";
	}

	if(( 0xB0 <= ucTag ) && ( 0xFE >= ucTag ))
	{
		return L"User defined";
	}


	if(( 0xB0 <= ucTag ) && ( 0xFE >= ucTag ))
	{
		return L"Forbidden";
	}

	if( 0x40 > ucTag )
	{
		return L"Forbidden descriptor in DVB context";
	}

	switch (ucTag)
	{
		case 0x40:
			return L"network_name_descriptor";
		case 0x41:
			return L"service_list_descriptor";
		case 0x42:
			return L"stuffing_descriptor";
		case 0x43:
			return L"satellite_delivery_system_descriptor";
		case 0x44:
			return L"cable_delivery_system_descriptor";
		case 0x45:
			return L"VBI_data_descriptor";
		case 0x46:
			return L"VBI_teletext_descriptor";
		case 0x47:
			return L"bouquet_name_descriptor";
		case 0x48:
			return L"service_descriptor";
		case 0x49:
			return L"country_availibility_descriptor";
		case 0x4A:
			return L"linkage_descriptor";
		case 0x4B:
			return L"NVOD_reference_descriptor";
		case 0x4C:
			return L"time_shifted_service_descriptor";
		case 0x4D:
			return L"short_event_descriptor";
		case 0x4E:
			return L"extended_event_descriptor";
		case 0x4F:
			return L"time_shifted_event_descriptor";
		case 0x50:
			return L"component_descriptor";
		case 0x51:
			return L"mosaic_descriptor";
		case 0x52:
			return L"stream_identifier_descriptor";
		case 0x53:
			return L"CA_identifier_descriptor";
		case 0x54:
			return L"content_descriptor";
		case 0x55:
			return L"parental_rating_descriptor";
		case 0x56:
			return L"teletext_descriptor";
		case 0x57:
			return L"telephone_descriptor";
		case 0x58:
			return L"local_time_offset_descriptor";
		case 0x59:
			return L"subtitling_descriptor";
		case 0x5A:
			return L"terrestrial_delivery_system_descriptor";
		case 0x5B:
			return L"multilingual_network_name_descriptor";
		case 0x5C:
			return L"multilingual_bouquet_name_descriptor";
		case 0x5D:
			return L"multilingual_service_name_descriptor";
		case 0x5E:
			return L"multilingual_component_descriptor";
		case 0x5F:
			return L"private_data_specifier_descriptor";
		case 0x60:
			return L"service_move_descriptor";
		case 0x61:
			return L"short_smoothing_buffer_descriptor";
		case 0x62:
			return L"frequency_list_descriptor";
		case 0x63:
			return L"partial_transport_stream_descriptor";
		case 0x64:
			return L"data_broadcast_descriptor";
		case 0x65:
			return L"scrambling_descriptor";
		case 0x66:
			return L"data_broadcast_id_descriptor";
		case 0x67:
			return L"transport_stream_descriptor";
		case 0x68:
			return L"DSNG_descriptor";
		case 0x69:
			return L"PDC_descriptor";
		case 0x6A:
			return L"AC3_descriptor";
		case 0x6B:
			return L"ancillary_data_descriptor";
		case 0x6C:
			return L"cell_list_descriptor";
		case 0x6D:
			return L"cell_frequency_list_descriptor";
		case 0x6E:
			return L"announcement_support_descriptor";
		case 0x6F:
			return L"application_signalling_descriptor";
		case 0x70:
			return L"adaptation_field_data_descriptor";
		case 0x71:
			return L"service_identifier_descriptor";
		case 0x72:
			return L"service_availability_descriptor";
		case 0x73:
			return L"default_authority_descriptor"; 		// TS 102 323
		case 0x74:
			return L"related_content_descriptor"; 		// TS 102 323
		case 0x75:
			return L"TVA_id_descriptor"; 			// TS 102 323
		case 0x76:
			return L"content_identifier_descriptor"; 	// TS 102 323
		case 0x77:
			return L"time_slice_fec_identifier_descriptor"; 	// EN 300 468 v1.6.1
		case 0x78:
			return L"ECM_repetition_rate_descriptor"; 	// EN 300 468 v1.6.1
        case 0x7F:
            return L"extension descriptor ";   // EN 300 468 v1.11.1
        default:
            return L"reserved_descriptor";
	}

	return L"Forbidden descriptor in DVB context";

};



EResult CDescriptor::LoopParse(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiLoopLength)
{
	if( 0 == uiLoopLength ) 
	{
		return FAILURE;
	}


	CTreeNode * pTreeNodeCurrentLoop = NULL;

	//It shall at least contain 2 Bytes, i.e.,descriptor_tag and descriptor_length.
	while(  2 <= uiLoopLength )
	{
		UCHAR8 ucDescriptorTag = pucData[0];
		UCHAR8 ucDescriptorLength = pucData[1];

		if( uiLoopLength < (UINT32)(ucDescriptorLength +2) )
		{
			CTreeNode * pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid descriptor", uiOffset, uiLoopLength*8, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);

			return FAILURE;
		}

		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, CDescriptor::GetDescriptorName(ucDescriptorTag), uiOffset, (ucDescriptorLength + 2)*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeList->AppendLastChild( pTreeNodeCurrentLoop, pTreeNodeInput);


		//Parse all descriptors.
		CDescriptor::Parse( pTSPacketStore,pTreeList,  pTreeNodeCurrentLoop, pucData, uiOffset);

		//Subtract the length of current descriptor.
		uiLoopLength -= (2 + ucDescriptorLength);
		pucData  += (2 + ucDescriptorLength);
		uiOffset += (2 + ucDescriptorLength)*8;
	}

	if( 0 != uiLoopLength)
	{
		CTreeNode *pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiLoopLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);
		uiOffset += uiLoopLength*8;

		return FAILURE;
	}

	return SUCCESS;
};

EResult CDescriptor::Parse(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	UCHAR8 ucDescriptorTag;

	ucDescriptorTag = pucData[0];
	if( 0x40 >  ucDescriptorTag)
	{
		return ParseMPEGDescriptor( pTSPacketStore, pTreeList,   pTreeNodeInput, pucData,  uiOffset);
	}
	else
	{
		return ParseDVBDescriptor( pTSPacketStore, pTreeList,   pTreeNodeInput, pucData,  uiOffset);
	}

	return SUCCESS;
};

LPWSTR CDescriptor::GetStreamTypeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"Reserved";
		case 0x01:
			return L"11172 Video";
		case 0x02:
			return L"H.262 or 13818-2 or 11172-2 Video";
		case 0x03:
			return L"11172 Audio";
		case 0x04:
			return L"13818-3 Audio";
		case 0x05:
			return L"H.222.0 or 13818-1 private_sections";
		case 0x06:
			return L"H.222.0 or 13818-1 private PES packets";
		case 0x07:
			return L"13522 MHEG";
		case 0x08:
			return L"H.222.0 or 13818-1 Annex A DSM CC";
		case 0x09:
			return L"H.222.1";
		case 0x0A:
			return L"13818-6 type A";
		case 0x0B:
			return L"13818-6 type B";
		case 0x0C:
			return L"13818-6 type C";
		case 0x0D:
			return L"13818-6 type D";
		case 0x0E:
			return L"13818-1 auxiliary";
		case 0x0F:
			return L"13818-7 Audio with ADTS transport syntax";
		case 0x10:
			return L"14496-2 Visual";
		case 0x11:
			return L"14496-3 Audio with LATM transport syntax";
		case 0x12:
			return L"14496-1 SL-packetized stream or FlexMux stream carried in PES packets";
		case 0x13:
			return L"14496-1 SL-packetized stream or FlexMux stream carried in 14496 sections";
		case 0x14:
			return L"13818-6 DSM-CC synchronized download protocol";
		case 0x15:
			return L"Metadata carried in PES packets using the Metadata Access Unit Wrapper";
		case 0x16:
			return L"Metadata carried in metadata_sections";
		case 0x17:
			return L"Metadata carried in 13818-6 (DSM-CC) Data Carousel";
		case 0x18:
			return L"Metadata carried in 13818-6 (DSM-CC) Object Carousel";
		case 0x19:
			return L"Metadata carried in 13818-6 Synchronized Download Protocol using the Metadata Access Unit Wrapper";
		case 0x1A:
			return L"IPMP stream";
		case 0x1B:
			return L"AVC video stream H.264 or 14496-10 Video";
		case 0x1C:
			return L"H.222.0 or 13818-1 reserved";
		case 0x7F:
			return L"IPMP stream";
        case 0x80:
            return L"User Private";
        case 0x81:
            return L"Dolby AC3 audio";
        case 0x85:
            return L"DTS audio";
        case 0x87:
            return L"Dolby digital plus audio ATSC";

	}

	if(( 0x80 <= uiParameter ) && ( 0xFF >= uiParameter  ))
	{
		return L"User Private";
	}
	else
	{
        return L"Reserved";
	}

}

EPidType CDescriptor::StreamTypeToPidType(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x01:
			return PID_TYPE_11172_VIDEO;//"11172 Video";
		case 0x02:
			return PID_TYPE_H262_13818_2_11172_2_VIDEO;//"H.262 or 13818-2 or 11172-2 Video";
		case 0x03:
			return PID_TYPE_11172_AUDIO;//"11172 Audio";
		case 0x04:
			return PID_TYPE_13818_3_AUDIO;//"13818-3 Audio";
		case 0x05:
			return PID_TYPE_H2220_13818_1_PRIVATE_SECTION;//"H.222.0 or 13818-1 private_sections";
		case 0x06:
			return PID_TYPE_H2220_13818_1_PRIVATE_PES_PACKET;//"H.222.0 or 13818-1 private PES packets";
		case 0x07:
			return PID_TYPE_13522_MHEG;//"13522 MHEG";
		case 0x08:
			return PID_TYPE_H2220_13818_1_ANNEX_A_DSM_CC;//"H.222.0 or 13818-1 Annex A DSM CC";
		case 0x09:
			return PID_TYPE_H2221;//"H.222.1";
		case 0x0A:
			return PID_TYPE_13818_6_TYPE_A;//"13818-6 type A";
		case 0x0B:
			return PID_TYPE_13818_6_TYPE_B;//"13818-6 type B";
		case 0x0C:
			return PID_TYPE_13818_6_TYPE_C;//"13818-6 type C";
		case 0x0D:
			return PID_TYPE_13818_6_TYPE_D;//"13818-6 type D";
		case 0x0E:
			return PID_TYPE_13818_1_AUXILIARY;//"13818-1 auxiliary";
		case 0x0F:
			return PID_TYPE_13818_7_AUDIO_WITH_ADTS_TRANSPORT_SYNTAX;
		case 0x10:
			return PID_TYPE_14496_2_VISUAL;
		case 0x11:
			return PID_TYPE_14496_3_AUDIO_WITH_LATM_TRANSPORT_SYNTAX;
		case 0x12:
			return PID_TYPE_14496_1_SL_PACKETIZED_STREAM_OR_FLEXMUX_STREAM_CARRIED_IN_PES_PACKETS;
		case 0x13:
			return PID_TYPE_14496_1_SL_PACKETIZED_STREAM_OR_FLEXMUX_STREAM_CARRIED_IN_14496_SECTIONS;
		case 0x14:
			return PID_TYPE_13818_6_DSM_CC_SYNCHRONIZED_DOWNLOAD_PROTOCOL;
		case 0x15:
			return PID_TYPE_METADATA_CARRIED_IN_PES_PACKETS_USING_THE_METADATA_ACCESS_UNIT_WRAPPER;
		case 0x16:
			return PID_TYPE_METADATA_CARRIED_IN_METADATA_SECTIONS;
		case 0x17:
			return PID_TYPE_METADATA_CARRIED_IN_13818_6__DATA_CAROUSEL;
		case 0x18:
			return PID_TYPE_METADATA_CARRIED_IN_13818_6__OBJECT_CAROUSEL;
		case 0x19:
			return PID_TYPE_METADATA_CARRIED_IN_13818_6_SYNCHRONIZED_DOWNLOAD_PROTOCOL_USING_THE_METADATA_ACCESS_UNIT_WRAPPER;
		case 0x1A:
			return PID_TYPE_IPMP_STREAM;
		case 0x1B:
			return PID_TYPE_AVC_VIDEO_STREAM_H264_OR_14496_10_VIDEO;
		case 0x1C:
			return PID_TYPE_H2220_OR_13818_1_RESERVED;
		case 0x7F:
			return PID_TYPE_IPMP_STREAM;
        case 0x81:
            return PID_TYPE_DOLBY_AC3_AUDIO;
        case 0x85:
            return PID_TYPE_DTS_AUDIO;
        case 0x87:
            return PID_TYPE_DOLBY_DITIGAL_PLUS_AUTIO_ATSC;
	}

	return PID_TYPE_RESERVED;
}


LPWSTR CDescriptor::GetPidTypeName(EPidType  ePidType)
{

	switch(ePidType)
	{
		case PID_TYPE_PAT:
			return L"PAT";
		case PID_TYPE_CAT:
			return L"CAT";
		case PID_TYPE_TSDT:
			return L"TSDT";
		case PID_TYPE_NIT:
			return L"NIT";
		case PID_TYPE_BAT_SDT:
			return L"BAT/SDT";
		case PID_TYPE_EIT:
			return L"EIT";
		case PID_TYPE_RST:
			return L"RST";
		case PID_TYPE_TDT_TOT:
			return L"TDT/TOT";
		case PID_TYPE_NST:
			return L"NST";
		case PID_TYPE_IST:
			return L"IST";
		case PID_TYPE_MT:
			return L"MT";
		case PID_TYPE_DIT:
			return L"DIT";
		case PID_TYPE_SIT:
			return L"SIT";
		case PID_TYPE_NULL:
			return L"NULL";
		case PID_TYPE_PMT:
			return L"PMT";
		case PID_TYPE_ECM:
			return L"ECM";
		case PID_TYPE_EMM:
			return L"EMM";
		case PID_TYPE_H2220_13818_1_ANNEX_A_DSM_CC:
			return L"H.222.0 or 13818-1 Annex A DSM CC";
		case PID_TYPE_H2220_13818_1_PRIVATE_SECTION:
			return L"H.222.0 or 13818-1 private_sections";
		case PID_TYPE_PCR:
			return L"PCR";
		case PID_TYPE_11172_VIDEO:
			return L"11172 Video";
		case PID_TYPE_H262_13818_2_11172_2_VIDEO:
			return L"H.262 or 13818-2 or 11172-2 Video";
		case PID_TYPE_11172_AUDIO:
			return L"11172 Audio";
		case PID_TYPE_13818_3_AUDIO:
			return L"13818-3 Audio";
		case PID_TYPE_H2220_13818_1_PRIVATE_PES_PACKET:
			return L"H.222.0 or 13818-1 private PES packets";
		case PID_TYPE_13522_MHEG:
			return L"13522 MHEG";
		case PID_TYPE_H2221:
			return L"H.222.1";
		case PID_TYPE_13818_6_TYPE_A:
			return L"13818-6 type A";
		case PID_TYPE_13818_6_TYPE_B:
			return L"13818-6 type B";
		case PID_TYPE_13818_6_TYPE_C:
			return L"13818-6 type C";
		case PID_TYPE_13818_6_TYPE_D:
			return L"13818-6 type D";
		case PID_TYPE_13818_1_AUXILIARY:
			return L"13818-1 auxiliary";
		case PID_TYPE_13818_7_AUDIO_WITH_ADTS_TRANSPORT_SYNTAX:
			return L"13818-7 Audio with ADTS transport syntax";
		case PID_TYPE_14496_2_VISUAL:
			return L"14496-2 Visual";
		case PID_TYPE_14496_3_AUDIO_WITH_LATM_TRANSPORT_SYNTAX:
			return L"14496-3 Audio with LATM transport syntax";
		case PID_TYPE_14496_1_SL_PACKETIZED_STREAM_OR_FLEXMUX_STREAM_CARRIED_IN_PES_PACKETS:
			return L"14496-1 SL-packetized stream or FlexMux stream carried in PES packets";
		case PID_TYPE_14496_1_SL_PACKETIZED_STREAM_OR_FLEXMUX_STREAM_CARRIED_IN_14496_SECTIONS:
			return L"14496-1 SL-packetized stream or FlexMux stream carried in 14496 sections";
		case PID_TYPE_13818_6_DSM_CC_SYNCHRONIZED_DOWNLOAD_PROTOCOL:
			return L"13818-6 DSM-CC synchronized download protocol";
		case PID_TYPE_METADATA_CARRIED_IN_PES_PACKETS_USING_THE_METADATA_ACCESS_UNIT_WRAPPER:
			return L"Metadata carried in PES packets using the Metadata Access Unit Wrapper";
		case PID_TYPE_METADATA_CARRIED_IN_METADATA_SECTIONS:
			return L"Metadata carried in metadata_sections";
		case PID_TYPE_METADATA_CARRIED_IN_13818_6__DATA_CAROUSEL:
			return L"Metadata carried in 13818-6 (DSM-CC) Data Carousel";
		case PID_TYPE_METADATA_CARRIED_IN_13818_6__OBJECT_CAROUSEL:
			return L"Metadata carried in 13818-6 (DSM-CC) Object Carousel";
		case PID_TYPE_METADATA_CARRIED_IN_13818_6_SYNCHRONIZED_DOWNLOAD_PROTOCOL_USING_THE_METADATA_ACCESS_UNIT_WRAPPER:
			return L"Metadata carried in 13818-6 Synchronized Download Protocol using the Metadata Access Unit Wrapper";
		case PID_TYPE_AVC_VIDEO_STREAM_H264_OR_14496_10_VIDEO:
			return L"AVC video stream H.264 or 14496-10 Video";
		case PID_TYPE_H2220_OR_13818_1_RESERVED:
			return L"H.222.0 or 13818-1 reserved";
		case PID_TYPE_IPMP_STREAM:
			return L"IPMP stream";
        case PID_TYPE_DOLBY_AC3_AUDIO:
            return L"Dolby AC3 audio";
        case PID_TYPE_DTS_AUDIO:
            return L"DTS audio";
        case PID_TYPE_DOLBY_DITIGAL_PLUS_AUTIO_ATSC:
            return L"Dolby digital plus audio ATSC";


		case PID_TYPE_RESERVED:
			return L"Reserved";
	}

	return L"Reserved";
}

LPWSTR CDescriptor::GetServiceTypeName(UINT32 uiParameter)
{

	if(( 0x11 <= uiParameter ) && ( 0x7F >= uiParameter  ))
	{
		return L"Reserved";
	}

	if(( 0x80 <= uiParameter ) && ( 0xFE >= uiParameter  ))
	{
		return L"User defined";
	}


	switch(uiParameter)
	{
		case 0x00:
			return L"reserved";
		case 0x01:
			return L"digital television service";
		case 0x02:
			return L"digital radio sound service";
		case 0x03:
			return L"Teletext service";
		case 0x04:
			return L"NVOD reference service";
		case 0x05:
			return L"NVOD time-shifted service";
		case 0x06:
			return L"mosaic service";
		case 0x07:
			return L"PAL coded signal";
		case 0x08:
			return L"SECAM coded signal";
		case 0x09:
			return L"D/D2-MAC";
		case 0x0A:
			return L"FM-Radio";
		case 0x0B:
			return L"NTSC coded signal";
		case 0x0C:
			return L"data broadcast service";
		case 0x0D:
			return L"reserved for Common Interface Usage";
		case 0x0E:
			return L"RCS Map";
		case 0x0F:
			return L"RCS FLS";
		case 0x10:
			return L"DVB  MHP service";
		case 0xFF:
			return L"reserved";
	}

	return L"Reserved";
}


LPWSTR CDescriptor::GetDataServiceName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"reserved";
		case 0x01:
			return L"EBU teletext";
		case 0x02:
			return L"inverted teletext";
		case 0x03:
			return L"reserved";
		case 0x04:
			return L"VPS";
		case 0x05:
			return L"WSS";
		case 0x06:
			return L"Closed Captioning";
		case 0x07:
			return L"monochrome 4:2:2 samples";
	}

	return L"Reserved";
}


LPWSTR CDescriptor::GetEastWestFlagName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"west";
		case 0x01:
			return L"east";
	}
	return L"Unknown";
}

LPWSTR CDescriptor::GetPolarizationName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"linear - horizontal";
		case 0x01:
			return L"linear - vertical";
		case 0x02:
			return L"circular - left";
		case 0x03:
			return L"circular - right";
	}
	return L"Unknown";
}

LPWSTR CDescriptor::GetModulationNameSatellite(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"not defined";
		case 0x01:
			return L"QPSK";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetModulationNameCable(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"not defined";
		case 0x01:
			return L"16 QAM";
		case 0x02:
			return L"32 QAM";
		case 0x03:
			return L"64 QAM";
		case 0x04:
			return L"128 QAM";
		case 0x05:
			return L"256 QAM";
	}
	return L"reserved";
}


LPWSTR CDescriptor::GetFECInnerName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"not defined";
		case 0x01:
			return L"1/2 conv. code rate";
		case 0x02:
			return L"2/3 conv. code rate";
		case 0x03:
			return L"3/4 conv. code rate";
		case 0x04:
			return L"5/6 conv. code rate";
		case 0x05:
			return L"7/8 conv. code rate";
		case 0x0F:
			return L"No conv. coding";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetFECOuterName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"not defined";
		case 0x01:
			return L"no outer FEC coding";
		case 0x02:
			return L"RS(204/188)";
	}
	return L"reserved";
}


LPWSTR CDescriptor::GetTeletexTypeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"reserved";
		case 0x01:
			return L"initial Teletext page";
		case 0x02:
			return L"Teletext subtitle page";
		case 0x03:
			return L"additional information page";
		case 0x04:
			return L"programme schedule page";
		case 0x05:
			return L"Teletext subtitle page for hearing impaired people";
	}
	return L"reserved";
}


LPWSTR CDescriptor::GetLinkageTypeName(UINT32 uiParameter)
{
	if(( 0x0D <= uiParameter ) && ( 0x7F >= uiParameter  ))
	{
		return L"Reserved";
	}

	if(( 0x80 <= uiParameter ) && ( 0xFE >= uiParameter  ))
	{
		return L"User defined";
	}

	switch(uiParameter)
	{
		case 0x00:
			return L"reserved";
		case 0x01:
			return L"information service";
		case 0x02:
			return L"EPG service";
		case 0x03:
			return L"CA replacement service";
		case 0x04:
			return L"TS containing complete Network/Bouquet SI";
		case 0x05:
			return L"service replacement service";
		case 0x06:
			return L"data broadcast service";
		case 0x07:
			return L"RCS Map";
		case 0x08:
			return L"mobile hand-over";
		case 0x09:
			return L"system software update service";
		case 0x0A:
			return L"TS containing SSU BAT or NIT";
		case 0x0B:
			return L"IP/MAC Notification Table";
		case 0x0C:
			return L"Deferred IP/MAC Notification Table";
	}


	return L"reserved";
}



LPWSTR CDescriptor::GetHandOverTypeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"reserved";
		case 0x01:
			return L"DVB hand-over to an identical service in a neighbouring country";
		case 0x02:
			return L"DVB hand-over to a local variation of the same service";
		case 0x03:
			return L"DVB hand-over to an associated service";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetOriginTypeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"NIT";
		case 0x01:
			return L"SDT";
	}
	return L"reserved";
}



LPWSTR CDescriptor::GetStreamAndComponentTypeName(UINT32 uiParameterStreamContent, UINT32 uiParameterComponentType)
{
	if(0x0 == uiParameterStreamContent )
	{
		return L"reserved";
	}

	if(0x1 == uiParameterStreamContent )
	{
		if( 0x00 == uiParameterComponentType)
		{
			return L"reserved";
		}

		if((0x11 <= uiParameterComponentType ) && (0xAF >= uiParameterComponentType ))
		{
			return L"reserved";
		}

		if((0xB0 <= uiParameterComponentType ) && (0xFE >= uiParameterComponentType ))
		{
			return L"user defined";
		}

		if( 0xFF == uiParameterComponentType)
		{
			return L"reserved";
		}
	}


	if(0x02 == uiParameterStreamContent )
	{
		if( 0x00 == uiParameterComponentType)
		{
			return L"reserved";
		}

		if((0x06 <= uiParameterComponentType ) && (0x3F >= uiParameterComponentType ))
		{
			return L"reserved";
		}

		if((0x42 <= uiParameterComponentType ) && (0xAF >= uiParameterComponentType ))
		{
			return L"reserved";
		}

		if((0xB0 <= uiParameterComponentType ) && (0xFE >= uiParameterComponentType ))
		{
			return L"user defined";
		}

		if( 0xFF == uiParameterComponentType)
		{
			return L"reserved";
		}
	}



	if(0x03 == uiParameterStreamContent )
	{
		if( 0x00 == uiParameterComponentType)
		{
			return L"reserved";
		}

		if((0x04 <= uiParameterComponentType ) && (0x0F >= uiParameterComponentType ))
		{
			return L"reserved";
		}

		if((0x14 <= uiParameterComponentType ) && (0x1F >= uiParameterComponentType ))
		{
			return L"reserved";
		}

		if((0x24 <= uiParameterComponentType ) && (0xAF >= uiParameterComponentType ))
		{
			return L"reserved";
		}

		if((0xB0 <= uiParameterComponentType ) && (0xFE >= uiParameterComponentType ))
		{
			return L"user defined";
		}

		if( 0xFF == uiParameterComponentType)
		{
			return L"reserved";
		}
	}

	if(0x04 == uiParameterStreamContent )
	{
		if((0x00 <= uiParameterComponentType ) && (0x7F >= uiParameterComponentType ))
		{
			return L"reserved for AC-3 audio modes";
		}

		if((0x80 <= uiParameterComponentType ) && (0xFF >= uiParameterComponentType ))
		{
			return L"reserved";
		}

	}


	if((0x05 <= uiParameterStreamContent ) && (0x0B >= uiParameterStreamContent ))
	{
		return L"reserved";
	}


	if((0x0C <= uiParameterStreamContent ) && (0x0F >= uiParameterStreamContent ))
	{
		return L"User defined";
	}

	UINT32 uiParameter = ((uiParameterStreamContent << 8) | ( uiParameterComponentType));
	switch(uiParameter)
	{
		case 0x0101:
			return L"video, 4:3  aspect ratio, 25 Hz";
		case 0x0102:
			return L"video, 16:9 aspect ratio with pan vectors, 25 Hz";
		case 0x0103:
			return L"video, 16:9 aspect ratio without pan vectors, 25 Hz";
		case 0x0104:
			return L"video, > 16:9 aspect ratio, 25 Hz";
		case 0x0105:
			return L"video, 4:3  aspect ratio, 30 Hz";
		case 0x0106:
			return L"video, 16:9 aspect ratio with pan vectors, 30 Hz";
		case 0x0107:
			return L"video, 16:9 aspect ratio without pan vectors, 30 Hz";
		case 0x0108:
			return L"video, > 16:9 aspect ratio, 30 Hz";
		case 0x0109:
			return L"high definition video, 4:3  aspect ratio, 25 Hz";
		case 0x010A:
			return L"high definition video, 16:9 aspect ratio with pan vectors, 25 Hz";
		case 0x010B:
			return L"high definition video, 16:9 aspect ratio without pan vectors, 25 Hz";
		case 0x010C:
			return L"high definition video, > 16:9 aspect ratio, 25 Hz";
		case 0x010D:
			return L"high definition video, 4:3  aspect ratio, 30 Hz";
		case 0x010E:
			return L"high definition video, 16:9 aspect ratio with pan vectors, 30 Hz";
		case 0x010F:
			return L"high definition video, 16:9 aspect ratio without pan vectors, 30 Hz";
		case 0x0110:
			return L"high definition video, > 16:9 aspect ratio, 30 Hz";
		case 0x0201:
			return L"audio, single mono channel";
		case 0x0202:
			return L"audio, dual mono channel";
		case 0x0203:
			return L"audio, stereo (2 channels)";
		case 0x0204:
			return L"audio, multilingual, multi-channel)";
		case 0x0205:
			return L"audio, surround sound";
		case 0x0240:
			return L"audio description for visually impaired";
		case 0x0241:
			return L"audio for the hard of hearing";
		case 0x0301:
			return L"EBU Teletext subtitles";
		case 0x0302:
			return L"associated Teletext";
		case 0x0303:
			return L"VBI data";
		case 0x0310:
			return L"DVB subtitles (normal) with no monitor aspect ratio critical";
		case 0x0311:
			return L"DVB subtitles (normal) for display 4:3 aspect ratio monitor";
		case 0x0312:
			return L"DVB subtitles (normal) for display 16:9 aspect ratio monitor";
		case 0x0313:
			return L"DVB subtitles (normal) for display 2.21:1 aspect ratio monitor";
		case 0x0320:
			return L"DVB subtitles (for the hard hearing) with no monitor aspect ratio critical";
		case 0x0321:
			return L"DVB subtitles (for the hard hearing) for display 4:3 aspect ratio monitor";
		case 0x0322:
			return L"DVB subtitles (for the hard hearing) for display 16:9 aspect ratio monitor";
		case 0x0323:
			return L"DVB subtitles (for the hard hearing) for display 2.21:1 aspect ratio monitor";
	}


	return L"reserved";
}

LPWSTR CDescriptor::GetLogicalCellPresentationInfoName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"undefined";
		case 0x01:
			return L"video";
		case 0x02:
			return L"still picture";
		case 0x03:
			return L"graphics/text";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetCellLinkageInfoName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"undefined";
		case 0x01:
			return L"bouquet related";
		case 0x02:
			return L"service related";
		case 0x03:
			return L"other mosaic related";
		case 0x04:
			return L"event related";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetCASystemName(UINT32 uiParameter)
{
	if(( 0x0000 <= uiParameter ) && ( 0x0000 >= uiParameter  )) 
		return L"Reserved";
	if(( 0x0001 <= uiParameter ) && ( 0x00FF >= uiParameter  )) 
		return L"Standardized Systems";
	if(( 0x0100 <= uiParameter ) && ( 0x01FF >= uiParameter  )) 
		return L"Canal Plus (Seca/MediaGuard)";
	if(( 0x0200 <= uiParameter ) && ( 0x02FF >= uiParameter  )) 
		return L"CCETT";
	if(( 0x0300 <= uiParameter ) && ( 0x03FF >= uiParameter  )) 
		return L"MSG MediaServices GmbH";
	if(( 0x0400 <= uiParameter ) && ( 0x04FF >= uiParameter  )) 
		return L"Eurodec";
	if(( 0x0500 <= uiParameter ) && ( 0x05FF >= uiParameter  )) 
		return L"France Telecom (Viaccess)";
	if(( 0x0600 <= uiParameter ) && ( 0x06FF >= uiParameter  )) 
		return L"Irdeto";
	if(( 0x0700 <= uiParameter ) && ( 0x07FF >= uiParameter  )) 
		return L"Jerrold/GI/Motorola";
	if(( 0x0800 <= uiParameter ) && ( 0x08FF >= uiParameter  )) 
		return L"Matra Communication";
	if(( 0x0900 <= uiParameter ) && ( 0x09FF >= uiParameter  )) 
		return L"News Datacom (Videoguard)";
	if(( 0x0A00 <= uiParameter ) && ( 0x0AFF >= uiParameter  )) 
		return L"Nokia";
	if(( 0x0B00 <= uiParameter ) && ( 0x0BFF >= uiParameter  )) 
		return L"Norwegian Telekom (Conax)";
	if(( 0x0C00 <= uiParameter ) && ( 0x0CFF >= uiParameter  )) 
		return L"NTL";
	if(( 0x0D00 <= uiParameter ) && ( 0x0DFF >= uiParameter  )) 
		return L"Philips (Cryptoworks)";
	if(( 0x0E00 <= uiParameter ) && ( 0x0EFF >= uiParameter  )) 
		return L"Scientific Atlanta (Power VU)";
	if(( 0x0F00 <= uiParameter ) && ( 0x0FFF >= uiParameter  )) 
		return L"Sony";
	if(( 0x1000 <= uiParameter ) && ( 0x10FF >= uiParameter  )) 
		return L"Tandberg Television";
	if(( 0x1100 <= uiParameter ) && ( 0x11FF >= uiParameter  )) 
		return L"Thompson";
	if(( 0x1200 <= uiParameter ) && ( 0x12FF >= uiParameter  )) 
		return L"TV/COM";
	if(( 0x1300 <= uiParameter ) && ( 0x13FF >= uiParameter  )) 
		return L"HPT - Croatian Post and Telecommunications";
	if(( 0x1400 <= uiParameter ) && ( 0x14FF >= uiParameter  )) 
		return L"HRT - Croatian Radio and Television";
	if(( 0x1500 <= uiParameter ) && ( 0x15FF >= uiParameter  )) 
		return L"IBM";
	if(( 0x1600 <= uiParameter ) && ( 0x16FF >= uiParameter  )) 
		return L"Nera";
	if(( 0x1700 <= uiParameter ) && ( 0x17FF >= uiParameter  )) 
		return L"Beta Technik (Betacrypt)";
	if(( 0x1800 <= uiParameter ) && ( 0x18FF >= uiParameter  )) 
		return L"Kudelski SA";
	if(( 0x1900 <= uiParameter ) && ( 0x19FF >= uiParameter  )) 
		return L"Titan Information Systems";
	if(( 0x2000 <= uiParameter ) && ( 0x20FF >= uiParameter  )) 
		return L"Telef車nica Servicios Audiovisuales";
	if(( 0x2100 <= uiParameter ) && ( 0x21FF >= uiParameter  )) 
		return L"STENTOR (France Telecom, CNES and DGA)";
	if(( 0x2200 <= uiParameter ) && ( 0x22FF >= uiParameter  )) 
		return L"Scopus Network Technologies";
	if(( 0x2300 <= uiParameter ) && ( 0x23FF >= uiParameter  )) 
		return L"BARCO AS";
	if(( 0x2400 <= uiParameter ) && ( 0x24FF >= uiParameter  )) 
		return L"StarGuide Digital Networks  ";
	if(( 0x2500 <= uiParameter ) && ( 0x25FF >= uiParameter  )) 
		return L"Mentor Data System, Inc.";
	if(( 0x2600 <= uiParameter ) && ( 0x26FF >= uiParameter  )) 
		return L"European Broadcasting Union";
	if(( 0x4700 <= uiParameter ) && ( 0x47FF >= uiParameter  )) 
		return L"General Instrument";
	if(( 0x4800 <= uiParameter ) && ( 0x48FF >= uiParameter  )) 
		return L"Telemann";
	if(( 0x4900 <= uiParameter ) && ( 0x49FF >= uiParameter  )) 
		return L"Digital TV Industry Alliance of China";
	if(( 0x4A00 <= uiParameter ) && ( 0x4A0F >= uiParameter  )) 
		return L"Tsinghua TongFang";
	if(( 0x4A10 <= uiParameter ) && ( 0x4A1F >= uiParameter  )) 
		return L"Easycas";
	if(( 0x4A20 <= uiParameter ) && ( 0x4A2F >= uiParameter  )) 
		return L"AlphaCrypt";
	if(( 0x4A30 <= uiParameter ) && ( 0x4A3F >= uiParameter  )) 
		return L"DVN Holdings";
	if(( 0x4A40 <= uiParameter ) && ( 0x4A4F >= uiParameter  )) 
		return L"Shanghai Advanced Digital Technology Co. Ltd. (ADT)";
	if(( 0x4A50 <= uiParameter ) && ( 0x4A5F >= uiParameter  )) 
		return L"Shenzhen Kingsky Company (China) Ltd";
	if(( 0x4A60 <= uiParameter ) && ( 0x4A6F >= uiParameter  )) 
		return L"@SKY";
	if(( 0x4A70 <= uiParameter ) && ( 0x4A7F >= uiParameter  )) 
		return L"DreamCrypt";
	if(( 0x4A80 <= uiParameter ) && ( 0x4A8F >= uiParameter  )) 
		return L"THALESCrypt";
	if(( 0x4A90 <= uiParameter ) && ( 0x4A9F >= uiParameter  )) 
		return L"Runcom Technologies";
	if(( 0x4AA0 <= uiParameter ) && ( 0x4AAF >= uiParameter  )) 
		return L"SIDSA";
	if(( 0x4AB0 <= uiParameter ) && ( 0x4ABF >= uiParameter  )) 
		return L"Beijing Compunicate Technology Inc.";
	if(( 0x4AC0 <= uiParameter ) && ( 0x4ACF >= uiParameter  )) 
		return L"Latens Systems Ltd";

	return L"Unknown CA system";
}

LPWSTR CDescriptor::GetExtendedDescriptorName(UINT32 uiParameter)
{
	if(( 0x0C <= uiParameter ) && ( 0x7F >= uiParameter  )) 
		return L"reserved for future use";
	if(( 0x80 <= uiParameter ) && ( 0xFF >= uiParameter  )) 
		return L"user defined";

	switch(uiParameter)
	{
	    case 0x00:
	        return L"mage_icon_descriptor ";
        case 0x01:
            return L"cpcm_delivery_signalling_descriptor ";
        case 0x02:
            return L"CP_descriptor";
        case 0x03:
            return L"CP_identifier_descriptor";
        case 0x04:
            return L"T2_delivery_system_descriptor";
        case 0x05:
            return L"SH_delivery_system_descriptor";
        case 0x06:
            return L"supplementary_audio_descriptor";
        case 0x07:
            return L"network_change_notify_descriptor";
        case 0x08:
            return L"message_descriptor";
        case 0x09:
            return L"target_region_descriptor";
        case 0x0A:
            return L"target_region_name_descriptor";
        case 0x0B:
            return L"service_relocated_descriptor";
        default:
            return L"Unknown descriptor";
	}
	if(( 0x0100 <= uiParameter ) && ( 0x01FF >= uiParameter  )) 
		return L"Canal Plus (Seca/MediaGuard)";
	if(( 0x0200 <= uiParameter ) && ( 0x02FF >= uiParameter  )) 
		return L"CCETT";
	if(( 0x0300 <= uiParameter ) && ( 0x03FF >= uiParameter  )) 
		return L"MSG MediaServices GmbH";
	if(( 0x0400 <= uiParameter ) && ( 0x04FF >= uiParameter  )) 
		return L"Eurodec";
	if(( 0x0500 <= uiParameter ) && ( 0x05FF >= uiParameter  )) 
		return L"France Telecom (Viaccess)";
	if(( 0x0600 <= uiParameter ) && ( 0x06FF >= uiParameter  )) 
		return L"Irdeto";
	if(( 0x0700 <= uiParameter ) && ( 0x07FF >= uiParameter  )) 
		return L"Jerrold/GI/Motorola";
	if(( 0x0800 <= uiParameter ) && ( 0x08FF >= uiParameter  )) 
		return L"Matra Communication";
	if(( 0x0900 <= uiParameter ) && ( 0x09FF >= uiParameter  )) 
		return L"News Datacom (Videoguard)";
	if(( 0x0A00 <= uiParameter ) && ( 0x0AFF >= uiParameter  )) 
		return L"Nokia";
	if(( 0x0B00 <= uiParameter ) && ( 0x0BFF >= uiParameter  )) 
		return L"Norwegian Telekom (Conax)";
	if(( 0x0C00 <= uiParameter ) && ( 0x0CFF >= uiParameter  )) 
		return L"NTL";
	if(( 0x0D00 <= uiParameter ) && ( 0x0DFF >= uiParameter  )) 
		return L"Philips (Cryptoworks)";
	if(( 0x0E00 <= uiParameter ) && ( 0x0EFF >= uiParameter  )) 
		return L"Scientific Atlanta (Power VU)";
	if(( 0x0F00 <= uiParameter ) && ( 0x0FFF >= uiParameter  )) 
		return L"Sony";
	if(( 0x1000 <= uiParameter ) && ( 0x10FF >= uiParameter  )) 
		return L"Tandberg Television";
	if(( 0x1100 <= uiParameter ) && ( 0x11FF >= uiParameter  )) 
		return L"Thompson";
	if(( 0x1200 <= uiParameter ) && ( 0x12FF >= uiParameter  )) 
		return L"TV/COM";
	if(( 0x1300 <= uiParameter ) && ( 0x13FF >= uiParameter  )) 
		return L"HPT - Croatian Post and Telecommunications";
	if(( 0x1400 <= uiParameter ) && ( 0x14FF >= uiParameter  )) 
		return L"HRT - Croatian Radio and Television";
	if(( 0x1500 <= uiParameter ) && ( 0x15FF >= uiParameter  )) 
		return L"IBM";
	if(( 0x1600 <= uiParameter ) && ( 0x16FF >= uiParameter  )) 
		return L"Nera";
	if(( 0x1700 <= uiParameter ) && ( 0x17FF >= uiParameter  )) 
		return L"Beta Technik (Betacrypt)";
	if(( 0x1800 <= uiParameter ) && ( 0x18FF >= uiParameter  )) 
		return L"Kudelski SA";
	if(( 0x1900 <= uiParameter ) && ( 0x19FF >= uiParameter  )) 
		return L"Titan Information Systems";
	if(( 0x2000 <= uiParameter ) && ( 0x20FF >= uiParameter  )) 
		return L"Telef車nica Servicios Audiovisuales";
	if(( 0x2100 <= uiParameter ) && ( 0x21FF >= uiParameter  )) 
		return L"STENTOR (France Telecom, CNES and DGA)";
	if(( 0x2200 <= uiParameter ) && ( 0x22FF >= uiParameter  )) 
		return L"Scopus Network Technologies";
	if(( 0x2300 <= uiParameter ) && ( 0x23FF >= uiParameter  )) 
		return L"BARCO AS";
	if(( 0x2400 <= uiParameter ) && ( 0x24FF >= uiParameter  )) 
		return L"StarGuide Digital Networks  ";
	if(( 0x2500 <= uiParameter ) && ( 0x25FF >= uiParameter  )) 
		return L"Mentor Data System, Inc.";
	if(( 0x2600 <= uiParameter ) && ( 0x26FF >= uiParameter  )) 
		return L"European Broadcasting Union";
	if(( 0x4700 <= uiParameter ) && ( 0x47FF >= uiParameter  )) 
		return L"General Instrument";
	if(( 0x4800 <= uiParameter ) && ( 0x48FF >= uiParameter  )) 
		return L"Telemann";
	if(( 0x4900 <= uiParameter ) && ( 0x49FF >= uiParameter  )) 
		return L"Digital TV Industry Alliance of China";
	if(( 0x4A00 <= uiParameter ) && ( 0x4A0F >= uiParameter  )) 
		return L"Tsinghua TongFang";
	if(( 0x4A10 <= uiParameter ) && ( 0x4A1F >= uiParameter  )) 
		return L"Easycas";
	if(( 0x4A20 <= uiParameter ) && ( 0x4A2F >= uiParameter  )) 
		return L"AlphaCrypt";
	if(( 0x4A30 <= uiParameter ) && ( 0x4A3F >= uiParameter  )) 
		return L"DVN Holdings";
	if(( 0x4A40 <= uiParameter ) && ( 0x4A4F >= uiParameter  )) 
		return L"Shanghai Advanced Digital Technology Co. Ltd. (ADT)";
	if(( 0x4A50 <= uiParameter ) && ( 0x4A5F >= uiParameter  )) 
		return L"Shenzhen Kingsky Company (China) Ltd";
	if(( 0x4A60 <= uiParameter ) && ( 0x4A6F >= uiParameter  )) 
		return L"@SKY";
	if(( 0x4A70 <= uiParameter ) && ( 0x4A7F >= uiParameter  )) 
		return L"DreamCrypt";
	if(( 0x4A80 <= uiParameter ) && ( 0x4A8F >= uiParameter  )) 
		return L"THALESCrypt";
	if(( 0x4A90 <= uiParameter ) && ( 0x4A9F >= uiParameter  )) 
		return L"Runcom Technologies";
	if(( 0x4AA0 <= uiParameter ) && ( 0x4AAF >= uiParameter  )) 
		return L"SIDSA";
	if(( 0x4AB0 <= uiParameter ) && ( 0x4ABF >= uiParameter  )) 
		return L"Beijing Compunicate Technology Inc.";
	if(( 0x4AC0 <= uiParameter ) && ( 0x4ACF >= uiParameter  )) 
		return L"Latens Systems Ltd";

	return L"Unknown CA system";
}


LPWSTR CDescriptor::GetContentLevelName(UINT32 uiParameter1, UINT32 uiParameter2)
{
	if(((0xC <= uiParameter1 ) && ( 0xE >= uiParameter1)) 
		|| ( 0x0 == uiParameter1 )
	   )
	{
		return L"reserved";
	}

	if(0xF == uiParameter1 )
	{
		return L"user defined";
	}

	if(0x1 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x9 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"movie/drama (general)";
			case 0x01:
				return L"detective/thriller";
			case 0x02:
				return L"adventure/western/war";
			case 0x03:
				return L"science fiction/fantasy/horror";
			case 0x04:
				return L"comedy";
			case 0x05:
				return L"soap/melodram/folkloric";
			case 0x06:
				return L"romance";
			case 0x07:
				return L"serious/classical/religious/historical movie/drama";
			case 0x08:
				return L"adult movie/drama";
		}
	}

	if(0x2 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x5 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"news/current affairs (general)";
			case 0x01:
				return L"news/weather report";
			case 0x02:
				return L"news magazine";
			case 0x03:
				return L"documentary";
			case 0x04:
				return L"discussion/interview/debate";
		}
	}

	if(0x3 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x4 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"show/game show (general)";
			case 0x01:
				return L"game show/quiz/contest";
			case 0x02:
				return L"variety show";
			case 0x03:
				return L"talk show";
		}
	}

	if(0x4 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0xC <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"sports (general)";
			case 0x01:
				return L"special events";
			case 0x02:
				return L"sports magazine";
			case 0x03:
				return L"football/soccer";
			case 0x04:
				return L"tennis/squash";
			case 0x05:
				return L"team sports";
			case 0x06:
				return L"athletics";
			case 0x07:
				return L"motor sport";
			case 0x08:
				return L"water sport";
			case 0x09:
				return L"winter sport";
			case 0x0A:
				return L"equestrian";
			case 0x0B:
				return L"martial sports";
		}
	}


	if(0x5 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x6 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"childrens's/youth program (general)";
			case 0x01:
				return L"pre-school children's program";
			case 0x02:
				return L"entertainment (6-14 year old)";
			case 0x03:
				return L"entertainment (10-16 year old)";
			case 0x04:
				return L"information/education/school program";
			case 0x05:
				return L"cartoon/puppets";
		}
	}


	if(0x6 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x7 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"music/ballet/dance (general)";
			case 0x01:
				return L"rock/pop";
			case 0x02:
				return L"serious music/classic music";
			case 0x03:
				return L"folk/traditional music";
			case 0x04:
				return L"jazz";
			case 0x05:
				return L"musical/opera";
			case 0x06:
				return L"ballet";
		}
	}

	if(0x7 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0xC <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"arts/culture (without music, general)";
			case 0x01:
				return L"performing arts";
			case 0x02:
				return L"fine arts";
			case 0x03:
				return L"religion";
			case 0x04:
				return L"popular culture/traditional arts";
			case 0x05:
				return L"literature";
			case 0x06:
				return L"film/cinema";
			case 0x07:
				return L"experimental film/video";
			case 0x08:
				return L"broadcasting/press";
			case 0x09:
				return L"new media";
			case 0x0A:
				return L"arts/culture magazine";
			case 0x0B:
				return L"fashion";
		}
	}

	if(0x8 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x4 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"social/political issues/economics (general)";
			case 0x01:
				return L"magazines/reports/documentary";
			case 0x02:
				return L"economics/social advisory";
			case 0x03:
				return L"remarkable people";
		}
	}

	if(0x9 == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x8 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"education/science/factual topics (general)";
			case 0x01:
				return L"nature/animals/environment";
			case 0x02:
				return L"technology/natural science";
			case 0x03:
				return L"medicine/physiology/psychology";
			case 0x04:
				return L"foreign countries/expeditions";
			case 0x05:
				return L"social/spiritual science";
			case 0x06:
				return L"further education";
			case 0x07:
				return L"languages";
		}
	}

	if(0xA == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x8 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"leisure hobbies (general)";
			case 0x01:
				return L"tourism/travel";
			case 0x02:
				return L"handicraft";
			case 0x03:
				return L"motoring";
			case 0x04:
				return L"fitness & health";
			case 0x05:
				return L"cooking";
			case 0x06:
				return L"advertisement/shopping";
			case 0x07:
				return L"gardening";
		}
	}

	if(0xB == uiParameter1 )
	{
		if( 0xF == uiParameter2)
		{
			return L"user defined";
		}

		if((0x4 <= uiParameter2 ) && (0xE >= uiParameter2 ))
		{
			return L"reserved";
		}

		switch(uiParameter2 )
		{
			case 0x00:
				return L"original language";
			case 0x01:
				return L"black & white";
			case 0x02:
				return L"unpublished";
			case 0x03:
				return L"live broadcast";
		}
	}


	return L"reserved";
}


LPWSTR CDescriptor::GetParentalRatingName(UINT32 uiParameter)
{
	if(( 0x10 <= uiParameter) && ( 0xFF >= uiParameter))
	{
		return L"defined by broadcaster";
	}

	switch(uiParameter)
	{
		case 0x00:
			return L"undefined";
		case 0x01:
			return L"minimum age 4 years";
		case 0x02:
			return L"minimum age 5 years";
		case 0x03:
			return L"minimum age 6 years";
		case 0x04:
			return L"minimum age 7 years";
		case 0x05:
			return L"minimum age 8 years";
		case 0x06:
			return L"minimum age 9 years";
		case 0x07:
			return L"minimum age 10 years";
		case 0x08:
			return L"minimum age 11 years";
		case 0x09:
			return L"minimum age 12 years";
		case 0x0A:
			return L"minimum age 13 years";
		case 0x0B:
			return L"minimum age 14 years";
		case 0x0C:
			return L"minimum age 15 years";
		case 0x0D:
			return L"minimum age 16 years";
		case 0x0E:
			return L"minimum age 17 years";
		case 0x0F:
			return L"minimum age 18 years";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetBandWidthName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"8 MHz";
		case 0x01:
			return L"7 MHz";
		case 0x02:
			return L"6 MHz";
	}
	return L"reserved";
}



LPWSTR CDescriptor::GetConstellationName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"QPSK";
		case 0x01:
			return L"16-QAM";
		case 0x02:
			return L"64-QAM";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetHierarchyInformationName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"non-hierarchical";
		case 0x01:
			return L"汐 = 1";
		case 0x02:
			return L"汐 = 2";
		case 0x03:
			return L"汐 = 4";
	}
	return L"reserved";
}


LPWSTR CDescriptor::GetCodeRateName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"1/2";
		case 0x01:
			return L"2/3";
		case 0x02:
			return L"3/4";
		case 0x03:
			return L"5/6";
		case 0x04:
			return L"7/8";
	}
	return L"reserved";
}


LPWSTR CDescriptor::GetGuardIntervalName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"1/32";
		case 0x01:
			return L"1/16";
		case 0x02:
			return L"1/8";
		case 0x03:
			return L"1/4";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetTransmissionModeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"2k mode";
		case 0x01:
			return L"8k mode";
	}
	return L"reserved";
}

LPWSTR CDescriptor::GetPrivateDataSpecifierName(UINT32 uiParameter)
{
	if(( 0x46545600 <= uiParameter ) && ( 0x46545620 >= uiParameter ))
	{
		return L"FreeTV";
	}

	if(( 0x4F545600 <= uiParameter ) && ( 0x4F5456FF >= uiParameter ))
	{
		return L"OpenTV";
	}

	if(( 0x50484900 <= uiParameter ) && ( 0x504849FF >= uiParameter ))
	{
		return L"Philips DVS";
	}


	switch( uiParameter )
	{
		case 0x00000000: 
			return L"Reserved";
		case 0x00000001: 
			return L"SES";
		case 0x00000002: 
			return L"BskyB 1";
		case 0x00000003: 
			return L"BskyB 2";
		case 0x00000004: 
			return L"BskyB 3";
		case 0x00000005: 
			return L"ARD, ZDF, ORF";
		case 0x00000006: 
			return L"Nokia Multimedia Network Terminals";
		case 0x00000007: 
			return L"AT Entertainment Ltd.";
		case 0x00000008: 
			return L"TV Cabo Portugal";
		case 0x00000009: 
			return L"Nagravision SA 每 Kudelski 1";
		case 0x0000000A: 
			return L"Nagravision SA 每 Kudelski 2";
		case 0x0000000B: 
			return L"Nagravision SA 每 Kudelski 3";
		case 0x0000000C: 
			return L"Nagravision SA 每 Kudelski 4";
		case 0x0000000D: 
			return L"Nagravision SA 每 Kudelski 5";
		case 0x0000000E: 
			return L"Valvision SA";
		case 0x0000000F: 
			return L"Quiero Televisi車n";
		case 0x00000010: 
			return L"La T谷l谷vision Par Satellite (TPS)";
		case 0x00000011: 
			return L"Echostar Communications";
		case 0x00000012: 
			return L"Telia AB";
		case 0x00000013: 
			return L"Viasat";
		case 0x00000014: 
			return L"Senda (Swedish Terrestrial TV)";
		case 0x00000015: 
			return L"MediaKabel";
		case 0x00000016: 
			return L"Casema";
		case 0x00000017: 
			return L"Humax Electronics Co. Ltd.";
		case 0x00000018: 
			return L"@Sky";
		case 0x00000019: 
			return L"Singapore Digital Terrestrial Television";
		case 0x00000020: 
			return L"Lyonnaise Cable 1";
		case 0x00000021: 
			return L"Lyonnaise Cable 2";
		case 0x00000022: 
			return L"Lyonnaise Cable 3";
		case 0x00000023: 
			return L"Lyonnaise Cable 4";
		case 0x00000025: 
			return L"MTV Europe";
		case 0x00000026: 
			return L"Pansonic";
		case 0x00000027: 
			return L"Mentor Data System, Inc.";
		case 0x00000028: 
			return L"EACEM";
		case 0x00000030: 
			return L"Telenor";
		case 0x00000031: 
			return L"TeleDenmark";
		case 0x00000035: 
			return L"Europe Online Networks S.A.";
		case 0x00000038: 
			return L"OTE";
		case 0x00000039: 
			return L"Telewizja Polsat";
		case 0x000000A0: 
			return L"Sentech";
		case 0x000000A1: 
			return L"TechniSat Digital GmbH";
		case 0x000000BE: 
			return L"BetaTechnik";
		case 0x000000C0: 
			return L"Canal+";
		case 0x000000D0: 
			return L"Dolby Laboratories Inc.";
		case 0x000000E0: 
			return L"ExpressVu Inc.";
		case 0x000000F0: 
			return L"France Telecom, CNES and DGA (STENTOR)";
		case 0x00000100: 
			return L"OpenTV";
		case 0x00000150: 
			return L"Loewe Opta GmbH";
		case 0x00000600: 
			return L"UPC 1";
		case 0x00000601: 
			return L"UPC 2";
		case 0x00001000: 
			return L"La T谷l谷vision Par Satellite (TPS)";
		case 0x000022D4: 
			return L"※Spanish Broadcasting Regulator";
		case 0x000022F1: 
			return L"※Swedish Broadcasting Regulator§";
		case 0x0000233A: 
			return L"Independent Television Commission";
		case 0x00006000: 
			return L"News Datacom";
		case 0x00006001: 
			return L"NDC 1";
		case 0x00006002: 
			return L"NDC 2";
		case 0x00006003: 
			return L"NDC 3";
		case 0x00006004: 
			return L"NDC 4";
		case 0x00006005: 
			return L"NDC 5";
		case 0x00006006: 
			return L"NDC 6";
		case 0x00362275: 
			return L"Irdeto";
		case 0x004E544C: 
			return L"NTL";
		case 0x00532D41: 
			return L"Scientific Atlanta";
		case 0x5347444E: 
			return L"StarGuide Digital Networks";
		case 0x00600000: 
			return L"Rh?ne Vision Cable";
		case 0x44414E59: 
			return L"News Datacom (IL) 1";
		case 0x46524549: 
			return L"News Datacom (IL) 1";
		case 0x4A4F4A4F: 
			return L"MSG MediaServices GmbH";
		case 0x53415053: 
			return L"Scientific Atlanta";
		case 0xBBBBBBBB: 
			return L"Bertelsmann Broadband Group";
		case 0xECCA0001: 
			return L"ECCA (European Cable CommunicationsAssociation)";
		case 0xFCFCFCFC: 
			return L"France Telecom";
	}

	return L"reserved";
}


LPWSTR CDescriptor::GetSbSizeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x01:
			return L"1536 bytes";
	}
	return L"DVB_reserved";
}

LPWSTR CDescriptor::GetLeakRateName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"reserved";
		case 0x01:
			return L"0.0009 Mbit/s";
		case 0x02:
			return L"0.0018 Mbit/s";
		case 0x03:
			return L"0.0036 Mbit/s";
		case 0x04:
			return L"0.0072 Mbit/s";
		case 0x05:
			return L"0.0108 Mbit/s";
		case 0x06:
			return L"0.0144 Mbit/s";
		case 0x07:
			return L"0.0216 Mbit/s";
		case 0x08:
			return L"0.0288 Mbit/s";
		case 0x09:
			return L"0.075 Mbit/s";
		case 0x0A:
			return L"0.5 Mbit/s";
		case 0x0B:
			return L"0.5625 Mbit/s";
		case 0x0C:
			return L"0.8437 Mbit/s";
		case 0x0D:
			return L"1.0 Mbit/s";
		case 0x0E:
			return L"1.1250 Mbit/s";
		case 0x0F:
			return L"1.5 Mbit/s";
		case 0x10:
			return L"1.6875 Mbit/s";
		case 0x11:
			return L"2.0 Mbit/s";
		case 0x12:
			return L"2.25 Mbit/s";
		case 0x13:
			return L"2.5 Mbit/s";
		case 0x14:
			return L"3.0 Mbit/s";
		case 0x15:
			return L"3.3750 Mbit/s";
		case 0x16:
			return L"3.5 Mbit/s";
		case 0x17:
			return L"4.0 Mbit/s";
		case 0x18:
			return L"4.5 Mbit/s";
		case 0x19:
			return L"5.0 Mbit/s";
		case 0x1A:
			return L"5.5 Mbit/s";
		case 0x1B:
			return L"6.0 Mbit/s";
		case 0x1C:
			return L"6.5 Mbit/s";
		case 0x1D:
			return L"6.75 Mbit/s";
		case 0x1E:
			return L"7.0 Mbit/s";
		case 0x1F:
			return L"7.5 Mbit/s";
		case 0x20:
			return L"8.0 Mbit/s";
		case 0x21:
			return L"9 Mbit/s";
		case 0x22:
			return L"10 Mbit/s";
		case 0x23:
			return L"11 Mbit/s";
		case 0x24:
			return L"12 Mbit/s";
		case 0x25:
			return L"13 Mbit/s";
		case 0x26:
			return L"13.5 Mbit/s";
		case 0x27:
			return L"14.0 Mbit/s";
		case 0x28:
			return L"15 Mbit/s";
		case 0x29:
			return L"16 Mbit/s";
		case 0x2A:
			return L"17 Mbit/s";
		case 0x2B:
			return L"18 Mbit/s";
		case 0x2C:
			return L"20 Mbit/s";
		case 0x2D:
			return L"22 Mbit/s";
		case 0x2E:
			return L"24 Mbit/s";
		case 0x2F:
			return L"26 Mbit/s";
		case 0x30:
			return L"27 Mbit/s";
		case 0x31:
			return L"28 Mbit/s";
		case 0x32:
			return L"30 Mbit/s";
		case 0x33:
			return L"32 Mbit/s";
		case 0x34:
			return L"34 Mbit/s";
		case 0x35:
			return L"36 Mbit/s";
		case 0x36:
			return L"38 Mbit/s";
		case 0x37:
			return L"40 Mbit/s";
		case 0x38:
			return L"44 Mbit/s";
		case 0x39:
			return L"48 Mbit/s";
		case 0x3A:
			return L"54 Mbit/s";
		case 0x3B:
			return L"72 Mbit/s";
		case 0x3C:
			return L"108 Mbit/s";
		case 0x3D:
			return L"reserved";
	}

	return L"reserved";
}

LPWSTR CDescriptor::GetCodingTypeName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x00:
			return L"not defined";
		case 0x01:
			return L"satellite";
		case 0x02:
			return L"cable";
		case 0x03:
			return L"terrestrial";
	}
	return L"reserved";
}



LPWSTR CDescriptor::GetDataBroadcastIdName(UINT32 uiParameter)
{
	switch(uiParameter)
	{
		case 0x0000:
			return L"Reserved for future use";
		case 0x0001:
			return L"Data pipe";
		case 0x0002:
			return L"Asynchronous data stream";
		case 0x0003:
			return L"Synchronous data stream";
		case 0x0004:
			return L"Synchronised data stream";
		case 0x0005:
			return L"Multi protocol encapsulation";
		case 0x0006:
			return L"Data Carousel";
		case 0x0007:
			return L"Object Carousel";
		case 0x0008:
			return L"DVB ATM streams";
		case 0x0009:
			return L"Higher Protocols based on asynchronous data streams";
		case 0x000A:
			return L"System Software Update"; // TR 102 006

		case 0x000B:
			return L"Reserved for future use by DVB";
		case 0x00F0:
			return L"MHP Object Carousel";	//  from registration at www.dvb.org
		case 0x00F1:
			return L"reserved for MHP Multi Protocol Encapsulation";
		case 0x00F2:
			return L"Reserved for MHP use";
		case 0x00FF:
			return L"Reserved for future use by DVB";

		case 0x0100:
			return L"Eutelsat Data Piping";
		case 0x0101:
			return L"Eutelsat Data Streaming";
		case 0x0102:
			return L"SAGEM IP encapsulation in MPEG-2 PES packets";
		case 0x0103:
			return L"BARCO Data Broadcasting";
		case 0x0104:
			return L"CyberCity Multiprotocol Encapsulation (New Media Communications Ltd.)";
		case 0x0105:
			return L"CyberSat Multiprotocol Encapsulation (New Media Communications Ltd.)";
		case 0x0106:
			return L"The Digital Network";
		case 0x0107:
			return L"OpenTV Data Carousel";
		case 0x0108:
			return L"Panasonic";
		case 0x0109:
			return L"MSG MediaServices GmbH";
		case 0x010A:
			return L"TechnoTrend";
		case 0x010B:
			return L"Canal + Technologies system software download";
		case 0x0110:
			return L"Televizja Polsat";
		case 0x0111:
			return L"UK DTG";
		case 0x0112:
			return L"SkyMedia";
		case 0x0113:
			return L"Intellibyte DataBroadcasting";
		case 0x0114:
			return L"TeleWeb Data Carousel";
		case 0x0115:
			return L"TeleWeb Object Carousel";
		case 0x0116:
			return L"TeleWeb";
		case 0x4444:
			return L"4TV Data Broadcast";
		case 0x4E4F:
			return L"Nokia IP based software delivery";
		case 0xBBB1:
			return L"BBG Data Caroussel";
		case 0xBBB2:
			return L"BBG Object Caroussel";
		case 0xBBBB:
			return L"Bertelsmann Broadband Group";
	}

	if(( 0x000A <= uiParameter ) && ( 0x00FF >= uiParameter ))
	{
		return L"Reserved for future use by DVB";
	}

	if(( 0x0100 <= uiParameter ) && ( 0xFFFE >= uiParameter ))
	{
		return L"Reserved for registration";
	}
	return L"reserved";
}


LPWSTR CDescriptor::GetAncillaryDataIdentifierName(UINT32 uiParameter)
{
	if( uiParameter & 0x1 )
	{
		return L"DVD-Video Ancillary Data";
	}

	if( uiParameter & 0x2 )
	{
		return L"Extended Ancillary Data";
	}

	if( uiParameter & 0x4 )
	{
		return L"Announcement Switching Data";
	}

	if( uiParameter & 0x8 )
	{
		return L"DAB Ancillary Data";
	}

	if( uiParameter & 0x10 )
	{
		return L"Scale Factor Error Check";
	}

	return L"reserved";
}


LPWSTR CDescriptor::GetAnnouncementSupportIndicatorName(UINT32 uiParameter)
{
	if( uiParameter & 0x1 )
	{
		return L"Emergency alarm";
	}

	if( uiParameter & 0x2 )
	{
		return L"Road Traffic flash";
	}

	if( uiParameter & 0x4 )
	{
		return L"Public Transport flash";
	}

	if( uiParameter & 0x8 )
	{
		return L"Warning message";
	}

	if( uiParameter & 0x10 )
	{
		return L"News flash";
	}

	if( uiParameter & 0x20 )
	{
		return L"Weather flash";
	}

	if( uiParameter & 0x40 )
	{
		return L"Event announcement";
	}

	if( uiParameter & 0x80 )
	{
		return L"Personal call";
	}
	return L"reserved";
}



LPWSTR CDescriptor::GetAnnouncementTypeName(UINT32 uiParameter)
{

	switch(uiParameter)
	{
		case 0x00:
			return L"Emergency alarm";
		case 0x01:
			return L"Road Traffic Flash";
		case 0x02:
			return L"Public Transport Flash";
		case 0x03:
			return L"Warning message";
		case 0x04:
			return L"News flash";
		case 0x05:
			return L"Weather flash";
		case 0x06:
			return L"Event announcement";
		case 0x07:
			return L"Personal call";
	}
	return L"reserved";
}


LPWSTR CDescriptor::GetaAdaptationFieldDataIdentifierName(UINT32 uiParameter)
{

	if( uiParameter & 0x1 )
	{
		return L"announcement switching data field";
	}

	return L"reserved";
}


LPWSTR CDescriptor::GetRunningStatusName(UINT32 uiParameter)
{

	switch(uiParameter)
	{
		case 0x00:
			return L"Reserved";
		case 0x01:
			return L"Not yet running";
		case 0x02:
			return L"Starts (or restarts)shortly";
		case 0x03:
			return L"Paused";
		case 0x04:
			return L"Running";
		case 0x05:
			return L"Cancelled";

	}

	return L"reserved";
}

LPWSTR CDescriptor::GetHierarchyName(UINT32 uiParameter)
{

	switch(uiParameter)
	{
		case 0x00:
			return L"Reserved";
		case 0x01:
			return L"ITU-T Rec. H.262 | ISO/IEC 13818-2 Spatial Scalability";
		case 0x02:
			return L"ITU-T Rec. H.262 | ISO/IEC 13818-2 SNR Scalability";
		case 0x03:
			return L"ITU-T Rec. H.262 | ISO/IEC 13818-2 Temporal Scalability";
		case 0x04:
			return L"ITU-T Rec. H.262 | ISO/IEC 13818-2 Data partitioning";
		case 0x05:
			return L"ISO/IEC 13818-3 Extension bitstream";
		case 0x06:
			return L"ITU-T Rec.H222.0 | ISO/IEC 13818-1 Private Stream";
		case 0x07:
			return L"ITU-T Rec. H.262 | ISO/IEC 13818-2 Multi-view Profile";
		case 0x0F:
			return L"Base layer";
	}

	return L"reserved";
}

LPWSTR CDescriptor::GetAlignmentTypeName(UINT32 uiParameter)
{

	switch(uiParameter)
	{
		case 0x00:
			return L"Reserved";
		case 0x01:
			return L"Slice or video access unit";
		case 0x02:
			return L"Video access unit";
		case 0x03:
			return L"GOP or SEQ";
		case 0x04:
			return L"SEQ";
	}

	return L"reserved";
}

LPWSTR CDescriptor::GetAudioTypeName(UINT32 uiParameter)
{

	switch(uiParameter)
	{
		case 0x00:
			return L"Undefined";
		case 0x01:
			return L"Clean effects";
		case 0x02:
			return L"Hearing impaired";
		case 0x03:
			return L"Visual impaired commentary";
	}

	return L"reserved";
}

LPWSTR CDescriptor::GetChromaFormatName(UINT32 uiParameter )
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

//MJD To Year month day.
EResult CDescriptor::MjdToYmd(ULONG mjd, UINT32 &uiYear, UINT32 &uiMonth, UINT32 &uiDay)
{
   SLONG   y,m,d ,k;

   y =  (SLONG) ((mjd  - 15078.2) / 365.25);
   m =  (SLONG) ((mjd - 14956.1 - (SLONG)(y * 365.25) ) / 30.6001);
   d =  (SLONG) (mjd - 14956 - (SLONG)(y * 365.25) - (SLONG)(m * 30.6001));
   k =  (m == 14 || m == 15) ? 1 : 0;
   y = y + k + 1900;
   m = m - 1 - k*12;

   uiYear = y;
   uiMonth = m;
   uiDay = d;
   return SUCCESS;
}

EResult CDescriptor::ParseNetworkNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	// descriptor_length*8 Bit network_name.
	uiFieldLength = uiDescriptorLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"network_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiDescriptorLength + 1];
	memset(pucDataName, 0, (uiDescriptorLength + 1));
	memcpy(pucDataName, pucData + 2, uiDescriptorLength);
	pTreeNode->m_strText.Format(L"network_name[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;
}


EResult CDescriptor::ParseBouquetNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	// descriptor_length*8 Bit bouquet_name.
	uiFieldLength = uiDescriptorLength*8;
	uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"bouquet_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiDescriptorLength + 1];
	memset(pucDataName, 0, (uiDescriptorLength + 1));
	memcpy(pucDataName, pucData + 2, uiDescriptorLength);
	pTreeNode->m_strText.Format(L"bouquet_name[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;
	return SUCCESS;
}

EResult CDescriptor::ParseServiceListDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"streams loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 3 <= uiDescriptorLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit service_id.
		uiFieldLength = 16;
		uiData = ((pucData[0] << 8) | pucData[1]);
		CTreeNode *pTreeNodeServiceId  = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 8 Bit service_type.
		uiFieldLength = 8;
		uiData = pucData[2];
		CTreeNode * pTreeNodeServiceType  = new CTreeNode(pTSPacketStore, L"service_type", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 3 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"ServiceId:0x%04X ,ServiceType: %s", 
			pTreeNodeServiceId->m_uiValue, GetServiceTypeName(pTreeNodeServiceType->m_uiValue));

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeServiceId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeServiceType, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 3;
		uiDescriptorLength -= 3;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;		
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseStuffingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	// descriptor_length*8 Bit stuffing_byte.
	uiFieldLength = uiDescriptorLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"stuffing_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;
}


EResult CDescriptor::ParseSatelliteDeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

  
	if( 11 <= uiDescriptorLength )
	{
		// 32 Bit frequency.
		uiFieldLength = 32;
		uiData = ((pucData[0]<< 24 )| (pucData[1]<< 16 )| (pucData[2]<< 8 )| pucData[3]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"frequency", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"frequency[%d]: %03X.%05X GHz", uiFieldLength, (uiData >> 20), (uiData & 0xFFFFF));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 16 Bit orbital_position.
		uiFieldLength = 16;
		uiData = ((pucData[4]<< 8 )| pucData[5]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"orbital_position", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"orbital_position[%d]: %03X.%01X Degree", uiFieldLength, ((uiData >> 4) & 0xFFF), (uiData & 0xF));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 1 Bit west_east_flag.
		uiFieldLength = 1;
		uiData = ((pucData[6] >> 7) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"west_east_flag", uiOffset, uiFieldLength, uiData , NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"west_east_flag[%d]: %s", uiFieldLength, GetEastWestFlagName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);		
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit polarization.
		uiFieldLength = 2;
		uiData = ((pucData[6] >> 5) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"polarization", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"polarization[%d]: %s", uiFieldLength, GetPolarizationName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 5 Bit modulation.
		uiFieldLength = 5;
		uiData = (pucData[6] & 0x1F );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"modulation", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"modulation[%d]: %s", uiFieldLength, GetModulationNameSatellite(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 28 Bit symbol_rate.
		uiFieldLength = 28;
		uiData = ((pucData[7]<< 20 )| (pucData[8]<< 12 )| (pucData[9]<< 4 )| ((pucData[10] >> 4)&0xF));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"symbol_rate", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"symbol_rate[%d]: %03X.%04X Msymbol/s", uiFieldLength, (uiData >> 16), (uiData & 0xFFFF));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 4 Bit FEC_inner.
		uiFieldLength = 4;
		uiData = (pucData[10] & 0xF);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"FEC_inner", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"FEC_inner[%d]: %s", uiFieldLength, GetFECInnerName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;


		//Move the pointer.
		pucData += 11;
		uiDescriptorLength -= 11;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseCableDeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

  
	if( 11 <= uiDescriptorLength )
	{
		// 32 Bit frequency.
		uiFieldLength = 32;
		uiData = ((pucData[0]<< 24 )| (pucData[1]<< 16 )| (pucData[2]<< 8 )| pucData[3]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"frequency", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"frequency[%d]: %04X.%04X MHz", uiFieldLength, (uiData >> 16), (uiData & 0xFFFF));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 12 Bit reserved_future_use.
		uiFieldLength = 12;
		uiData = ((pucData[4]<< 4 )| ((pucData[5] >> 4) & 0xF));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 4 Bit FEC_outer.
		uiFieldLength = 4;
		uiData = (pucData[5] & 0xF);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"FEC_outer", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"FEC_outer[%d]: %s", uiFieldLength, GetFECInnerName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 8 Bit modulation.
		uiFieldLength = 8;
		uiData = (pucData[6]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"modulation", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"modulation[%d]: %s", uiFieldLength, GetModulationNameCable(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 28 Bit symbol_rate.
		uiFieldLength = 28;
		uiData = ((pucData[7]<< 20 )| (pucData[8]<< 12 )| (pucData[9]<< 4 )| ((pucData[10] >> 4)&0xF));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"symbol_rate", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"symbol_rate[%d]: %03X.%04X Msymbol/s", uiFieldLength, (uiData >> 16), (uiData & 0xFFFF));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 4 Bit FEC_inner.
		uiFieldLength = 4;
		uiData = (pucData[10] & 0xF);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"FEC_inner", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"FEC_inner[%d]: %s", uiFieldLength, GetFECInnerName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;


		//Move the pointer.
		pucData += 11;
		uiDescriptorLength -= 11;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseVBIDataDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorPayloadLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"data_service loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 2 <= uiDescriptorPayloadLength )
	{
		UCHAR8 ucDataServiceId;
		UINT32 uiDescriptorsLoopLength;

		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 8 Bit data_service_id.
		uiFieldLength = 8;
		ucDataServiceId = pucData[0];
		CTreeNode *pTreeNodeSericeId  = new CTreeNode(pTSPacketStore, L"data_service_id", uiOffset, uiFieldLength, ucDataServiceId );
		uiOffset += uiFieldLength;

		// 8 Bit data_service_descriptor_length.
		uiFieldLength = 8;
		uiDescriptorsLoopLength = pucData[1];
		CTreeNode *pTreeNodeDescriptorsLoopLength  = new CTreeNode(pTSPacketStore, L"data_service_descriptor_length", uiOffset, uiFieldLength, uiDescriptorsLoopLength );
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += 2;
		uiDescriptorPayloadLength -= 2;

		CTreeNode * pTreeNodeCurrentLoop = NULL;
		if (( uiDescriptorPayloadLength < uiDescriptorsLoopLength))
		{
			//Invalid End.
			uiFieldLength = (uiDescriptorPayloadLength + 2)*8;
			pTreeNodeCurrentLoop  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffsetCurrentLoop, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			uiOffset += uiFieldLength;

			//Move the pointer.
			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

		}
		else
		{
			pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 2 + uiDescriptorsLoopLength)*8, VALUE_ZERO, NODE_LOOP_ITEM );
			pTreeNodeCurrentLoop->m_strText.Format(L"DataServiceId: 0x%04X, Type: %s", ucDataServiceId, GetDataServiceName(ucDataServiceId) );

			uiDescriptorPayloadLength -= uiDescriptorsLoopLength;
		}

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeSericeId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeDescriptorsLoopLength, pTreeNodeCurrentLoop);



		//Parse the descriptors that belong to current elementary stream.
		if( 0 == uiDescriptorPayloadLength )
		{
			continue;
		}

		if(!( ( 0x01 <= ucDataServiceId ) && ( 0x07 >= ucDataServiceId )))
		{
			// reserved.
			uiFieldLength = uiDescriptorsLoopLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);

			//Set uiOffset after descriptors loop.
			uiOffset += uiFieldLength;

			//Move the pointer.
			pucData += uiDescriptorsLoopLength;

			break;
		}

		//Begin the loop.
		uiFieldLength = uiDescriptorsLoopLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"data loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		/*It is a loop, do NOT subtract the length.*/
		//uiOffset += uiFieldLength;

		CTreeNode * pTreeNodeLoops2 = pTreeNode;       
		while( 1 <= uiDescriptorsLoopLength )
		{

			UINT32 uiOffsetCurrentLoop = uiOffset;

			// 2 Bit reserved.
			uiFieldLength = 2;
			uiData = ((pucData[0] >> 6 ) &0x3);
			CTreeNode *pTreeNodeReserved = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
			uiOffset += uiFieldLength;

			// 1 Bit field_parity.
			uiFieldLength = 1;
			uiData = ((pucData[0] >> 6 ) &0x3);
			CTreeNode *pTreeNodeFieldParity  = new CTreeNode(pTSPacketStore, L"field_parity", uiOffset, uiFieldLength, uiData );
			uiOffset += uiFieldLength;

			// 5 Bit line_offset.
			uiFieldLength = 5;
			uiData = pucData[0];
			CTreeNode *pTreeNodeLineOffset = new CTreeNode(pTSPacketStore, L"line_offset", uiOffset, uiFieldLength, uiData );
			uiOffset += uiFieldLength;

			CTreeNode * pTreeNodeCurrentLoop2 =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 1 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
			pTreeNodeCurrentLoop2->m_strText.Format(L"FieldParity: 0x%02X, LineOffset: 0x%02X", pTreeNodeFieldParity->m_uiValue, pTreeNodeLineOffset->m_uiValue );

			//Append the current loop node.
			pTreeList->AppendLastChild(pTreeNodeCurrentLoop2, pTreeNodeLoops2);
			pTreeList->AppendLastChild(pTreeNodeReserved, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeFieldParity, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeLineOffset, pTreeNodeCurrentLoop2);

			//Move the pointer.
			pucData += 1;
			uiDescriptorsLoopLength -= 1;
		}

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}

EResult CDescriptor::ParseVBITeletextDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorPayloadLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"teletext loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 5 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 5 Bit teletext_type.
		uiFieldLength = 5;
		uiData = ((pucData[3] >> 3) & 0x1F);
		CTreeNode *pTreeNodeTeletextType  = new CTreeNode(pTSPacketStore, L"teletext_type", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;


		// 3 Bit teletext_magazine_number.
		uiFieldLength = 3;
		uiData = (pucData[3] & 0x7);
		CTreeNode *pTreeNodeTeletextMagazineNumber  = new CTreeNode(pTSPacketStore, L"teletext_magazine_number", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 8 Bit teletext_page_number.
		uiFieldLength = 8;
		uiData = (pucData[4]);
		CTreeNode *pTreeNodeTeletextPageNumber  = new CTreeNode(pTSPacketStore, L"teletext_page_number", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;



		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 5 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"language_code: %c%c%c, teletext_type: %s, teletext_magazine_number: 0x%02X, teletext_page_number: 0x%02X",  
				pucData[0], pucData[1], pucData[2],
				GetTeletexTypeName(pTreeNodeTeletextType->m_uiValue),
				pTreeNodeTeletextMagazineNumber->m_uiValue,
				pTreeNodeTeletextPageNumber->m_uiValue
				);


		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeTeletextType, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeTeletextMagazineNumber, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeTeletextPageNumber, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 5;
		uiDescriptorPayloadLength -= 5;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseServiceDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if(  2 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	UINT32 uiNameLength;

	// 8 Bit service_type.
	uiFieldLength = 8;
	uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"service_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"service_type[%d]: %s", uiFieldLength, GetServiceTypeName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit service_provider_name_length.
	uiFieldLength = 8;
	uiData = (pucData[1]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"service_provider_name_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiNameLength = uiData;

	//Move the pointer.
	pucData += 2;
	uiDescriptorPayloadLength -= 2;

	if(uiDescriptorPayloadLength < uiNameLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit network_name.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"service_provider_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"service_provider_name[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;
 
	if( 1 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 8 Bit service_name_length.
	uiFieldLength = 8;
	uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"service_name_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiNameLength = uiData;

	//Move the pointer.
	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if(uiDescriptorPayloadLength < uiNameLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit service_name.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"service_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"service_name[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseCountryAvailabilityDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 1 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 1 Bit country_availability_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"country_availability_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 7 Bit reserved_future_use.
	uiFieldLength = 7;
	uiData = (pucData[0]  & 0x7F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;



	while(  3 <= uiDescriptorPayloadLength )
	{
		// 24 Bit country_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"country_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"country_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 3;
		uiDescriptorPayloadLength -= 3;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseLinkageDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 7 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 16 Bit transport_stream_id.
	uiFieldLength = 16;
	uiData = ((pucData[0]<< 8 )| pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 16 Bit original_network_id.
	uiFieldLength = 16;
	uiData = ((pucData[2]<< 8 )| pucData[3]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 16 Bit service_id.
	uiFieldLength = 16;
	uiData = ((pucData[4]<< 8 )| pucData[5]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit linkage_type.
	uiFieldLength = 8;
	uiData = pucData[6];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"linkage_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"linkage_type[%d]: %s", uiFieldLength, GetLinkageTypeName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 7;
	uiDescriptorPayloadLength -= 7;

	if( 0 == uiDescriptorPayloadLength)
	{
		return FAILURE;
	}

	if( 0x08 != uiData)
	{
		//private_data_byte
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return SUCCESS;
	}

	// 4 Bit hand-over_type.
	uiFieldLength = 4;
	uiData = ((pucData[0] >> 4 ) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"hand-over_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"hand-over_type[%d]: %s ", uiFieldLength, GetHandOverTypeName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	CTreeNode *pTreeNodeHandOverType = pTreeNode;

	// 3 Bit reserved_future_use.
	uiFieldLength = 3;
	uiData = ((pucData[0] >> 1 ) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 1 Bit origin_type.
	uiFieldLength = 1;
	uiData = (pucData[0] & 0x1 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"origin_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"origin_type[%d]: %s ", uiFieldLength, GetOriginTypeName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	CTreeNode *pTreeNodeOriginType = pTreeNode;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if(
		( 0x01 == pTreeNodeHandOverType->m_uiValue )
		|| ( 0x02 == pTreeNodeHandOverType->m_uiValue )
		|| ( 0x03 == pTreeNodeHandOverType->m_uiValue )
	   )
	{
		if( 2 > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			return FAILURE;
		}

		// 16 Bit network_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"network_id", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 2;
		uiDescriptorPayloadLength -= 2;
	}


	if( 0x00 == pTreeNodeOriginType->m_uiValue )
	{
		if( 2 > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
			pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			return FAILURE;
		}

		// 16 Bit initial_service_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"initial_service_id", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 2;
		uiDescriptorPayloadLength -= 2;

	}

	if( 0 != uiDescriptorPayloadLength )
	{
		//private_data_byte
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseNVODReferenceDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"service loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 6 <= uiDescriptorLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit transport_stream_id.
		uiFieldLength = 16;
		uiData = ((pucData[0] << 8) | pucData[1]);
		CTreeNode *pTreeNodeTransportStreamId  = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 16 Bit original_network_id.
		uiFieldLength = 16;
		uiData = ((pucData[2] << 8) | pucData[3]);
		CTreeNode *pTreeNodeOriginalNetworkId  = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 16 Bit service_id.
		uiFieldLength = 16;
		uiData = ((pucData[4] << 8) | pucData[5]);
		CTreeNode *pTreeNodeServiceId  = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 6 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"TransportStreamId:0x%04X ,OriginalNetworkId:0x%04X ,ServiceId:0x%04X", 
			pTreeNodeTransportStreamId->m_uiValue,
			pTreeNodeOriginalNetworkId->m_uiValue,
			pTreeNodeServiceId->m_uiValue);

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeTransportStreamId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeOriginalNetworkId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeServiceId, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 6;
		uiDescriptorLength -= 6;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseTimeShiftedServiceDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;
   
	if( 2 <= uiDescriptorLength )
	{
		// 16 Bit reference_service_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reference_service_id", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += 2;
		uiDescriptorLength -= 2;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseShortEventDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 4 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	UINT32 uiNameLength;

	// 24 Bit language_code.
	uiFieldLength = 24;
	uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 3;
	uiDescriptorPayloadLength -= 3;

	// 8 Bit event_name_length.
	uiFieldLength = 8;
	uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"event_name_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiNameLength = uiData;

	//Move the pointer.
	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( uiNameLength > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit event_name.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"event_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"event_name[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;


	if(  1 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 8 Bit text_length.
	uiFieldLength = 8;
	uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"text_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiNameLength = uiData;

	//Move the pointer.
	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( uiDescriptorPayloadLength < uiNameLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit text.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"text", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"text[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseExtendedEventDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 5 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	UINT32 uiItemLength;

	// 4 Bit descriptor_number.
	uiFieldLength = 4;
	uiData = ( ( pucData[0] >> 4) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_number", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 4 Bit last_descriptor_number.
	uiFieldLength = 4;
	uiData = ( pucData[0] & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"last_descriptor_number", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;


	// 24 Bit language_code.
	uiFieldLength = 24;
	uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 3;
	uiDescriptorPayloadLength -= 3;

	// 8 Bit length_of_items.
	uiFieldLength = 8;
	uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"length_of_items", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiItemLength = uiData;

	//Move the pointer.
	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( uiDescriptorPayloadLength < uiItemLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// items loop.
	uiFieldLength = 8*uiItemLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"items loop", uiOffset, uiFieldLength, uiData, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 1 <= uiItemLength )
	{
		UINT32 uiNameLength;

		// items loop.
		uiFieldLength = 0;
		//uiData = (pucData[0]);
		pTreeNode = new CTreeNode(pTSPacketStore, L"item", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeLoops);
		//pTreeNodeTmp = pTreeNode;
		//uiOffset += uiFieldLength;

		CTreeNode *pTreeNodeCurrentLoop = pTreeNode;

		// 8 Bit item_description_length.
		uiFieldLength = 8;
		uiData = (pucData[0]);
		pTreeNode = new CTreeNode(pTSPacketStore, L"item_description_length", uiOffset, uiFieldLength, uiData);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		//pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

		uiNameLength = uiData;
		pucData += 1;
		uiItemLength -= 1;
		uiDescriptorPayloadLength -= 1;

		if( uiNameLength > uiItemLength )
		{
			//Invalid End.
			uiFieldLength = uiItemLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiItemLength;
			uiDescriptorPayloadLength -= uiItemLength;
			uiItemLength = 0;

			break;
		}


		// descriptor_length*8 Bit item_description.
		uiFieldLength = uiNameLength*8;
		//uiData = pucData[2];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"item_description", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
		UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
		memset(pucDataName, 0, (uiNameLength + 1));
		memcpy(pucDataName, pucData, uiNameLength);
		pTreeNode->m_strText.Format(L"item_description[%d]: %s", uiFieldLength,CString(pucDataName));
		delete [] pucDataName;
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		//pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

		pucData += uiNameLength;
		uiItemLength -= uiNameLength;
		uiDescriptorPayloadLength -= uiNameLength;

		// 8 Bit item_length.
		uiFieldLength = 8;
		uiData = (pucData[0]);
		pTreeNode = new CTreeNode(pTSPacketStore, L"item_length", uiOffset, uiFieldLength, uiData);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		//pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

		uiNameLength = uiData;
		pucData += 1;
		uiItemLength -= 1;
		uiDescriptorPayloadLength -= 1;

		if( uiNameLength > uiItemLength  )
		{
			//Invalid End.
			uiFieldLength = uiItemLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiItemLength;
			uiDescriptorPayloadLength -= uiItemLength;
			uiItemLength = 0;

			break;

		}

		// descriptor_length*8 Bit item_description.
		uiFieldLength = uiNameLength*8;
		//uiData = pucData[2];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"item", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
		pucDataName = new UCHAR8[uiNameLength + 1];
		memset(pucDataName, 0, (uiNameLength + 1));
		memcpy(pucDataName, pucData, uiNameLength);
		pTreeNode->m_strText.Format(L"item[%d]: %s", uiFieldLength,CString(pucDataName));
		delete [] pucDataName;
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		//pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

		pucData += uiNameLength;
		uiItemLength -= uiNameLength;
		uiDescriptorPayloadLength -= uiNameLength;

	}//while( uiItemLength >= 1)


 
	if( 1 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}


	UINT32 uiNameLength;

	// 8 Bit text_length.
	uiFieldLength = 8;
	uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"text_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiNameLength = uiData;

	//Move the pointer.
	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( uiNameLength > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit text.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"text", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"text[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}





EResult CDescriptor::ParseTimeShiftedEventDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;
   
	if( 4 <= uiDescriptorLength )
	{
		// 16 Bit reference_service_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reference_service_id", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 16 Bit reference_event_id.
		uiFieldLength = 16;
		uiData = ((pucData[2]<< 8 )| pucData[3]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reference_event_id", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += 4;
		uiDescriptorLength -= 4;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseComponentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 6 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}


	// 4 Bit reserved_future_use.
	uiFieldLength = 4;
	uiData = ((pucData[0] >> 4) & 0xF);
	pTreeNode = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 12 Bit description field to show the type name.
	uiFieldLength = 12;
	CTreeNode *pTreeNodeDescription = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);

	// 4 Bit stream_content.
	uiFieldLength = 4;
	uiData = (pucData[0] & 0xF);
	CTreeNode *pTreeNodeStreamContent = new CTreeNode(pTSPacketStore, L"stream_content", uiOffset, uiFieldLength, uiData);
	uiOffset += uiFieldLength;

	// 8 Bit component_type.
	uiFieldLength = 8;
	uiData = pucData[1];
	CTreeNode *pTreeNodeComponentType = new CTreeNode(pTSPacketStore, L"component_type", uiOffset, uiFieldLength, uiData );
	uiOffset += uiFieldLength;

	// 8 Bit component_tag.
	uiFieldLength = 8;
	uiData = pucData[2];
	CTreeNode *pTreeNodeComponentTag  = new CTreeNode(pTSPacketStore, L"component_tag", uiOffset, uiFieldLength, uiData );
	uiOffset += uiFieldLength;

	pTreeNodeDescription->m_strText.Format(L"StreamContent: 0x%02X, ComponentType: 0x%02X, ComponentTag: 0x%02X Type: %s",
		pTreeNodeStreamContent->m_uiValue, pTreeNodeComponentType->m_uiValue, pTreeNodeComponentTag->m_uiValue,
		GetStreamAndComponentTypeName(pTreeNodeStreamContent->m_uiValue, pTreeNodeComponentType->m_uiValue));

	pTreeList->InsertAfter(pTreeNodeDescription, pTreeNodeTmp);
	pTreeList->AppendLastChild(pTreeNodeStreamContent, pTreeNodeDescription);
	pTreeList->AppendLastChild(pTreeNodeComponentType, pTreeNodeDescription);
	pTreeList->AppendLastChild(pTreeNodeComponentTag, pTreeNodeDescription);

	pTreeNodeTmp = pTreeNodeDescription;

	//Move the pointer.
	pucData += 3;
	uiDescriptorPayloadLength -= 3;

	// 24 Bit language_code.
	uiFieldLength = 24;
	uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 3;
	uiDescriptorPayloadLength -= 3;


	// descriptor_length*8 Bit text.
	uiFieldLength = uiDescriptorPayloadLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"text", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiDescriptorPayloadLength + 1];
	memset(pucDataName, 0, (uiDescriptorPayloadLength + 1));
	memcpy(pucDataName, pucData, uiDescriptorPayloadLength);
	pTreeNode->m_strText.Format(L"text[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiDescriptorPayloadLength;
	uiDescriptorPayloadLength -= uiDescriptorPayloadLength;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseMosaicDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 1 Bit mosaic_entry_point.
	uiFieldLength = 1;
	uiData = ( ( pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"mosaic_entry_point", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit number_of_horizontal_elementary_cells.
	uiFieldLength = 3;
	uiData = ( ( pucData[0] >> 4) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"number_of_horizontal_elementary_cells", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"number_of_horizontal_elementary_cells[%d]: %d", uiFieldLength, uiData+1);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit reserved_future_use.
	uiFieldLength = 1;
	uiData = ( ( pucData[0] ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit number_of_vertical_elementary_cells.
	uiFieldLength = 3;
	uiData = ( ( pucData[0] ) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"number_of_vertical_elementary_cells", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"number_of_vertical_elementary_cells[%d]: %d", uiFieldLength, uiData+1);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;



	// items loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"logical_cell loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 3 <= uiDescriptorPayloadLength )
	{
		// logical_cell loop.
		uiFieldLength = 3*8;
		CTreeNode *pTreeNodeCurrentLoop = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);


		// 6 Bit logical_cell_id.
		uiFieldLength = 6;
		uiData = ((pucData[0] >> 2 ) & 0x3F);
		CTreeNode * pTreeNodeLogicalCellId = new CTreeNode(pTSPacketStore, L"logical_cell_id", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 7 Bit reserved_future_use.
		uiFieldLength = 7;
		uiData = (((pucData[0] & 0x3 ) << 5) | ((pucData[1] >> 3 ) & 0x1F));
		CTreeNode * pTreeNodeReserved1 = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 3 Bit logical_cell_presentation_info.
		uiFieldLength = 3;
		uiData = (pucData[1] & 0x7 );
		CTreeNode * pTreeNodeLogicalCellPreInfo = new CTreeNode(pTSPacketStore, L"logical_cell_presentation_info", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;


		// 8 Bit elementary_cell_field_length.
		uiFieldLength = 8;
		uiData = (pucData[2]);
		CTreeNode * pTreeNodeElementaryLength = new CTreeNode(pTSPacketStore, L"elementary_cell_field_length", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		pucData += 3;
		uiDescriptorPayloadLength -= 3;

		pTreeNodeCurrentLoop->m_strText.Format(L"logical_cell_id: 0x%02X, logical_cell_presentation_info: %s",
			pTreeNodeLogicalCellId->m_uiValue,
			GetLogicalCellPresentationInfoName(pTreeNodeLogicalCellPreInfo->m_uiValue)
			);

		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLogicalCellId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReserved1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeLogicalCellPreInfo, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeElementaryLength, pTreeNodeCurrentLoop);

		//Save the value of elementary_cell_field_length.
		UINT32 uiCellFieldLength = uiData;


		if( uiCellFieldLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			//We can NOT decide the length of current loop, so we have to add up to it one bye one.
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}

		// uiCellFieldLength*8 Bit elementary_cell loop.
		uiFieldLength = uiCellFieldLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"elementary_cell loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		uiDescriptorPayloadLength -= uiCellFieldLength;

		CTreeNode *  pTreeNodeLoops2 = pTreeNode;
		//The second loop.
		while( 1 <= uiCellFieldLength)
		{

			// Current loop 2.
			uiFieldLength = 1*8;
			CTreeNode * pTreeNodeCurrentLoop2 = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);

			// 2 Bit reserved_future_use.
			uiFieldLength = 2;
			uiData = (pucData[0] & 0x3);
			CTreeNode * pTreeNodeReserver2 = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;

			// 6 Bit elementary_cell_id.
			uiFieldLength = 6;
			uiData = (pucData[0] & 0x3F);
			CTreeNode * pTreeNodeElementaryCellId = new CTreeNode(pTSPacketStore, L"elementary_cell_id", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;			

			pTreeNodeCurrentLoop2->m_strText.Format(L"elementary_cell_id: 0x%02X", 
				pTreeNodeElementaryCellId->m_uiValue);

			pTreeList->AppendLastChild(pTreeNodeCurrentLoop2, pTreeNodeLoops2);
			pTreeList->AppendLastChild(pTreeNodeReserver2, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeElementaryCellId, pTreeNodeCurrentLoop2);

			pucData += 1;
			uiCellFieldLength -= 1;
		}


	 
		if( 1 > uiDescriptorPayloadLength)
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			uiOffset += uiFieldLength;

			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
			return FAILURE;
		}


		// 8 Bit cell_linkage_info.
		uiFieldLength = 8;
		uiData = (pucData[0]);
		pTreeNode = new CTreeNode(pTSPacketStore, L"cell_linkage_info", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
		pTreeNode->m_strText.Format(L"cell_linkage_info[%d]: %s", uiFieldLength, GetCellLinkageInfoName(uiData));		
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

		pucData += 1;
		uiDescriptorPayloadLength -= 1;

		//Save the value of cell_linkage_info.
		UINT32 uiLinkageInfo = uiData;

		//bouquet related
		if( 0x01 == uiLinkageInfo)
		{
			if( 2 > uiDescriptorPayloadLength)
			{
				//Invalid End.
				uiFieldLength = uiDescriptorPayloadLength*8;
				pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;

				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				return FAILURE;
			}
			else
			{
				// 16 Bit bouquet_id.
				uiFieldLength = 16;
				uiData = ((pucData[0] << 8) | pucData[1]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"bouquet_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				
				pucData += 2;
				uiDescriptorPayloadLength -= 2;
			}

			continue;
		}


		//service related or other mosaic related.
		if( ( 0x02 == uiLinkageInfo) || ( 0x03 == uiLinkageInfo))
		{
			if( 6 > uiDescriptorPayloadLength)
			{
				//Invalid End.
				uiFieldLength = uiDescriptorPayloadLength*8;
				pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;

				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				return FAILURE;
			}
			else
			{
				// 16 Bit original_network_id.
				uiFieldLength = 16;
				uiData = ((pucData[0] << 8) | pucData[1]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				
				// 16 Bit transport_stream_id.
				uiFieldLength = 16;
				uiData = ((pucData[2] << 8) | pucData[3]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				// 16 Bit service_id.
				uiFieldLength = 16;
				uiData = ((pucData[4] << 8) | pucData[5]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				pucData += 6;
				uiDescriptorPayloadLength -= 6;
			}

			continue;
		}

		//event related
		if( 0x04 == uiLinkageInfo)
		{
			if( 8 > uiDescriptorPayloadLength)
			{
				//Invalid End.
				uiFieldLength = uiDescriptorPayloadLength*8;
				pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;

				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				return FAILURE;
			}
			else
			{
				// 16 Bit original_network_id.
				uiFieldLength = 16;
				uiData = ((pucData[0] << 8) | pucData[1]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				
				// 16 Bit transport_stream_id.
				uiFieldLength = 16;
				uiData = ((pucData[2] << 8) | pucData[3]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				// 16 Bit service_id.
				uiFieldLength = 16;
				uiData = ((pucData[4] << 8) | pucData[5]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;


				// 16 Bit event_id.
				uiFieldLength = 16;
				uiData = ((pucData[6] << 8) | pucData[7]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"event_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				pucData += 8;
				uiDescriptorPayloadLength -= 8;
			}

			continue;
		}


		//Unknown.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Unknown cell_linkage_info", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		//pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseStreamIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;
   
	if( 1 > uiDescriptorLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 8 Bit component_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"component_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	uiDescriptorLength -= 1;
	pucData += 1;

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseCAIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"CA_system_id loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 2 <= uiDescriptorLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit CA_system_id.
		uiFieldLength = 16;
		uiData = ((pucData[0] << 8) | pucData[1]);
		CTreeNode *pTreeNodeCASystemId  = new CTreeNode(pTSPacketStore, L"CA_system_id", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
		pTreeNodeCASystemId->m_strText.Format(L"CA_system_id[%d]: 0x%04X, Name %s", uiFieldLength, uiData, GetCASystemName(uiData));
		uiOffset += uiFieldLength;

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCASystemId, pTreeNodeLoops);

		//Move the pointer.
		pucData += 2;
		uiDescriptorLength -= 2;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;		
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseContentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"content_nibble_level loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 2 <= uiDescriptorLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 4 Bit content_nibble_level_1.
		uiFieldLength = 4;
		uiData = ((pucData[0] >> 4) & 0xF);
		CTreeNode *pTreeNodeContentNibble1  = new CTreeNode(pTSPacketStore, L"content_nibble_level_1", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 4 Bit content_nibble_level_2.
		uiFieldLength = 4;
		uiData = (pucData[0]  & 0xF);
		CTreeNode *pTreeNodeContentNibble2  = new CTreeNode(pTSPacketStore, L"content_nibble_level_2", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 4 Bit user_nibble.
		uiFieldLength = 4;
		uiData = ((pucData[1] >> 4) & 0xF);
		CTreeNode *pTreeNodeUserNibble1  = new CTreeNode(pTSPacketStore, L"user_nibble", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 4 Bit user_nibble.
		uiFieldLength = 4;
		uiData = (pucData[1]  & 0xF);
		CTreeNode *pTreeNodeUserNibble2  = new CTreeNode(pTSPacketStore, L"user_nibble", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;


		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 2 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"content: %s", 
			GetContentLevelName(pTreeNodeContentNibble1->m_uiValue, pTreeNodeContentNibble2->m_uiValue));

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeContentNibble1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeContentNibble2, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeUserNibble1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeUserNibble2, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 2;
		uiDescriptorLength -= 2;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;		
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseParentalRatingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"parental_rating loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 4 <= uiDescriptorLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit country_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode * pTreeNodeCountryCode  = new CTreeNode(pTSPacketStore, L"country_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeCountryCode->m_strText.Format(L"country_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 8 Bit rating.
		uiFieldLength = 8;
		uiData = ( pucData[3]);
		CTreeNode * pTreeNodeRating = new CTreeNode(pTSPacketStore, L"rating", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 4 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"country_code: %c%c%c, level: %s", 
			pucData[0], pucData[1], pucData[2],
			GetParentalRatingName(pTreeNodeRating->m_uiValue));

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeCountryCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeRating, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 4;
		uiDescriptorLength -= 4;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;		
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseTeletextDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorPayloadLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"teletext loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 5 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 5 Bit teletext_type.
		uiFieldLength = 5;
		uiData = ((pucData[3] >> 3) & 0x1F);
		CTreeNode *pTreeNodeTeletextType  = new CTreeNode(pTSPacketStore, L"teletext_type", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;


		// 3 Bit teletext_magazine_number.
		uiFieldLength = 3;
		uiData = (pucData[3] & 0x7);
		CTreeNode *pTreeNodeTeletextMagazineNumber  = new CTreeNode(pTSPacketStore, L"teletext_magazine_number", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 8 Bit teletext_page_number.
		uiFieldLength = 8;
		uiData = (pucData[4]);
		CTreeNode *pTreeNodeTeletextPageNumber  = new CTreeNode(pTSPacketStore, L"teletext_page_number", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;



		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 5 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"language_code: %c%c%c, teletext_type: %s, teletext_magazine_number: 0x%02X, teletext_page_number: 0x%02X",  
				pucData[0], pucData[1], pucData[2],
				GetTeletexTypeName(pTreeNodeTeletextType->m_uiValue),
				pTreeNodeTeletextMagazineNumber->m_uiValue,
				pTreeNodeTeletextPageNumber->m_uiValue
				);


		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeTeletextType, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeTeletextMagazineNumber, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeTeletextPageNumber, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 5;
		uiDescriptorPayloadLength -= 5;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}
	return SUCCESS;
}



EResult CDescriptor::ParseTelephoneDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 3 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	UINT32 uiNameLength;

	// 2 Bit reserved_future_use.
	uiFieldLength = 2;
	uiData = ((pucData[0] >> 6) & 0x3);
	pTreeNode = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit foreign_availability.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 5) & 0x1);
	pTreeNode = new CTreeNode(pTSPacketStore, L"foreign_availability", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 5 Bit connection_type.
	uiFieldLength = 5;
	uiData = (pucData[0]  & 0x1F);
	pTreeNode = new CTreeNode(pTSPacketStore, L"connection_type", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit reserved_future_use.
	uiFieldLength = 1;
	uiData = ((pucData[1] >> 7) & 0x1);
	pTreeNode = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit country_prefix_length.
	uiFieldLength = 2;
	uiData = ((pucData[1] >> 5) & 0x3);
	pTreeNode = new CTreeNode(pTSPacketStore, L"country_prefix_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//1
	UINT32 uiCountryPrefixLength = uiData;

	// 3 Bit international_area_code_length.
	uiFieldLength = 3;
	uiData = (((pucData[1] >> 2) & 0x7));
	pTreeNode = new CTreeNode(pTSPacketStore, L"international_area_code_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//2
	UINT32 uiInternationalAreaCodeLength = uiData;

	// 2 Bit operator_code_length.
	uiFieldLength = 2;
	uiData = (pucData[1] & 0x3);
	pTreeNode = new CTreeNode(pTSPacketStore, L"operator_code_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//3
	UINT32 uiOperatorCodeLength = uiData;

	// 1 Bit reserved_future_use.
	uiFieldLength = 1;
	uiData = ((pucData[2] >> 7) & 0x1);
	pTreeNode = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit national_area_code_length.
	uiFieldLength = 3;
	uiData = (((pucData[2] >> 4) & 0x7));
	pTreeNode = new CTreeNode(pTSPacketStore, L"national_area_code_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//4
	UINT32 uiNationalAreaCodeLength = uiData;

	// 4 Bit core_number_length.
	uiFieldLength = 4;
	uiData = (pucData[2]  & 0xF);
	pTreeNode = new CTreeNode(pTSPacketStore, L"core_number_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//5
	UINT32 uiCoreNumberLength = uiData;

	//Move the pointer.
	pucData += 3;
	uiDescriptorPayloadLength -= 3;

	UCHAR8 *pucDataName = NULL;
	//1
	uiNameLength = uiCountryPrefixLength;

	if( uiNameLength > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit country_prefix.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"country_prefix", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"country_prefix[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;


	//2
	uiNameLength = uiInternationalAreaCodeLength;

	if( uiNameLength > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit international_area_code.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"international_area_code", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"international_area_code[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;



	//3
	uiNameLength = uiOperatorCodeLength;

	if( uiNameLength > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit operator_code.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"operator_code", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"operator_code[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;


	//4
	uiNameLength = uiNationalAreaCodeLength;

	if( uiNameLength > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit national_area_code.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"national_area_code", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"national_area_code[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;

	//5
	uiNameLength = uiCoreNumberLength;

	if( uiNameLength > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit core_number.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"core_number", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"core_number[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;



	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseLocalTimeOffsetDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorPayloadLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"local time offset loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 13 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit country_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeCountryCode  = new CTreeNode(pTSPacketStore, L"country_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeCountryCode->m_strText.Format(L"country_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 6 Bit country_region_id.
		uiFieldLength = 6;
		uiData = ((pucData[3] >> 2) & 0x3F);
		CTreeNode *pTreeNodeCountryRegionId  = new CTreeNode(pTSPacketStore, L"country_region_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;


		// 1 Bit reserved.
		uiFieldLength = 1;
		uiData = ((pucData[3] >> 1) & 0x1);
		CTreeNode *pTreeNodeReserved1  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 1 Bit local_time_offset_polarity.
		uiFieldLength = 1;
		uiData = (pucData[3]  & 0x1);
		CTreeNode *pTreeNodeLocalTimeOffsetPolarity  = new CTreeNode(pTSPacketStore, L"local_time_offset_polarity", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;


		// 16 Bit local_time_offset.
		uiFieldLength = 16;
		uiData = ((pucData[4] << 8) | (pucData[5]));
		CTreeNode *pTreeNodeLocalTimeOffset  = new CTreeNode(pTSPacketStore, L"local_time_offset", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLocalTimeOffset->m_strText.Format(L"local_time_offset[%d]: %02X:%02X", uiFieldLength, pucData[4], pucData[5]);
		uiOffset += uiFieldLength;

		// 16 Bit MJD.
		uiFieldLength = 16;
		uiData = ((pucData[6]<< 8 )| pucData[7]);
		CTreeNode *pTreeNodeMJD  = new CTreeNode(pTSPacketStore, L"MJD", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		uiOffset += uiFieldLength;

		UINT32 uiMJD = uiData;
		UINT32 uiYear, uiMonth, uiDay;
		CDescriptor::MjdToYmd(uiMJD, uiYear, uiMonth, uiDay);
		pTreeNodeMJD->m_strText.Format(L"date[%d]:0x%04X, %04d/%02d/%02d", uiFieldLength, uiData, uiYear, uiMonth, uiDay );


		// 24 Bit UTC.
		uiFieldLength = 24;
		uiData = ((pucData[8]<< 16 )| (pucData[9]<< 8 )| pucData[10]);
		CTreeNode *pTreeNodeUTC = new CTreeNode(pTSPacketStore, L"UTC", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeUTC->m_strText.Format(L"time[%d]: %02X:%02X:%02X", uiFieldLength,  pucData[8], pucData[9],pucData[10]);
		uiOffset += uiFieldLength;

		// 16 Bit next_time_offset.
		uiFieldLength = 16;
		uiData = ((pucData[11]<< 8 )| pucData[12]);
		CTreeNode *pTreeNodeNextTimeOffset  = new CTreeNode(pTSPacketStore, L"next_time_offset", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 13 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"country_code: %c%c%c, local_time_offset: %02X:%02X",  
				pucData[0], pucData[1], pucData[2],
				pucData[4], pucData[5]
				);


		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeCountryCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeCountryRegionId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReserved1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeLocalTimeOffsetPolarity, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeLocalTimeOffset, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeMJD, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeUTC, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeNextTimeOffset, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 13;
		uiDescriptorPayloadLength -= 13;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}
	return SUCCESS;
}


EResult CDescriptor::ParseSubtitlingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorPayloadLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"subtitling loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 8 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 8 Bit subtitling_type.
		uiFieldLength = 8;
		uiData = (pucData[3]);
		CTreeNode *pTreeNodeSubtitlingType  = new CTreeNode(pTSPacketStore, L"subtitling_type", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;


		// 16 Bit composition_page_id.
		uiFieldLength = 16;
		uiData = ((pucData[4] << 8) | pucData[5]);
		CTreeNode *pTreeNodeCompositionPageId  = new CTreeNode(pTSPacketStore, L"composition_page_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 16 Bit ancillary_page_id.
		uiFieldLength = 16;
		uiData = ((pucData[6] << 8) | pucData[7]);
		CTreeNode *pTreeNodeAncillaryPageId  = new CTreeNode(pTSPacketStore, L"ancillary_page_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;


		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 8 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"language_code: %c%c%c, subtitling_type: 0x%02X, composition_page_id: 0x%04X, ancillary_page_id: 0x%04X",
				pucData[0], pucData[1], pucData[2],
				pTreeNodeSubtitlingType->m_uiValue,
				pTreeNodeCompositionPageId->m_uiValue,
				pTreeNodeAncillaryPageId->m_uiValue
				);


		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeSubtitlingType, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeCompositionPageId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeAncillaryPageId, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 8;
		uiDescriptorPayloadLength -= 8;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}
	return SUCCESS;
}


EResult CDescriptor::ParseTerrestrialDeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

  
	if( 11 <= uiDescriptorLength )
	{
		// 32 Bit centre_frequency.
		uiFieldLength = 32;
		uiData = ((pucData[0]<< 24 )| (pucData[1]<< 16 )| (pucData[2]<< 8 )| pucData[3]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"centre_frequency", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"centre_frequency[%d]: 0x%08X 10Hz", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 3 Bit bandwidth.
		uiFieldLength = 3;
		uiData = ((pucData[4] >> 5 ) & 0x7);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"bandwidth", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"bandwidth[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetBandWidthName(uiData) );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 5 Bit reserved_future_use.
		uiFieldLength = 5;
		uiData = ((pucData[4] ) & 0x1F);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit constellation.
		uiFieldLength = 2;
		uiData = ((pucData[5] >> 6 ) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"constellation", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"constellation[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetConstellationName(uiData) );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 3 Bit hierarchy_information.
		uiFieldLength = 3;
		uiData = ((pucData[5] >> 3 ) & 0x7);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"hierarchy_information", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"hierarchy_information[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetHierarchyInformationName(uiData) );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 3 Bit code_rate-HP_stream.
		uiFieldLength = 3;
		uiData = ((pucData[5]) & 0x7);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"code_rate-HP_stream", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"code_rate-HP_stream[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetCodeRateName(uiData) );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 3 Bit code_rate-LP_stream.
		uiFieldLength = 3;
		uiData = ((pucData[6] >> 5) & 0x7);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"code_rate-LP_stream", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"code_rate-LP_stream[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetCodeRateName(uiData) );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit guard_interval.
		uiFieldLength = 2;
		uiData = ((pucData[6] >> 3) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"guard_interval", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"guard_interval[%d]: 0x%02X, type: %s", uiFieldLength,uiData, GetGuardIntervalName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit transmission_mode.
		uiFieldLength = 2;
		uiData = ((pucData[6] >> 1) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"transmission_mode", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"transmission_mode[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetTransmissionModeName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 1 Bit other_frequency_flag.
		uiFieldLength = 1;
		uiData = ((pucData[6] ) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"other_frequency_flag", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 32 Bit reserved_future_use.
		uiFieldLength = 32;
		uiData = ((pucData[7]<< 24 )| (pucData[8]<< 16 )| (pucData[9]<< 8 )| pucData[10]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;


		//Move the pointer.
		pucData += 11;
		uiDescriptorLength -= 11;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseMultilingualNetworkNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// network_name loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"network_name loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 4 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 8 Bit network_name_length.
		uiFieldLength = 8;
		uiData = (pucData[3]);
		CTreeNode *pTreeNodeNameLength  = new CTreeNode(pTSPacketStore, L"network_name_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		UINT32 uiNameLength;
		uiNameLength = uiData;


		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 4 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"language_code: %c%c%c   ",  
				pucData[0], pucData[1], pucData[2]
				);


		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeNameLength, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 4;
		uiDescriptorPayloadLength -= 4;

		if( uiNameLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength -= uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}


		// descriptor_length*8 Bit network_name.
		uiFieldLength = uiNameLength*8;
		//uiData = pucData[2];
		CTreeNode *pTreeNodeNetworkName  = new CTreeNode(pTSPacketStore, L"network_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
		UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
		memset(pucDataName, 0, (uiNameLength + 1));
		memcpy(pucDataName, pucData, uiNameLength);
		pTreeNodeNetworkName->m_strText.Format(L"network_name[%d]: %s", uiFieldLength,CString(pucDataName));
		pTreeNodeCurrentLoop->m_strText.AppendFormat(L"network_name: %s  ", CString(pucDataName));
		delete [] pucDataName;
		uiOffset += uiFieldLength;

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		pucData += uiNameLength;
		uiDescriptorPayloadLength -= uiNameLength;

		//Append the current loop node.
		pTreeList->AppendLastChild( pTreeNodeNetworkName, pTreeNodeCurrentLoop);
		pTreeList->UpdateText(pTreeNodeCurrentLoop);


	}//while( uiItemLength >= 4)

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseMultilingualServiceNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// service_name loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"service_name loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 4 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 8 Bit service_provider_name_length.
		uiFieldLength = 8;
		uiData = (pucData[3]);
		CTreeNode *pTreeNodeProviderNameLength  = new CTreeNode(pTSPacketStore, L"service_provider_name_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		UINT32 uiNameLength;
		uiNameLength = uiData;


		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 4 )*8, VALUE_ZERO, NODE_LOOP_ITEM );

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeProviderNameLength, pTreeNodeCurrentLoop);
			
		//Move the pointer.
		pucData += 4;
		uiDescriptorPayloadLength -= 4;

		if( uiNameLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			uiOffset += uiFieldLength;
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength -= uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}


		// descriptor_length*8 Bit service_provider_name.
		uiFieldLength = uiNameLength*8;
		//uiData = pucData[2];
		CTreeNode *pTreeNodeServiceProviderName  = new CTreeNode(pTSPacketStore, L"service_provider_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
		UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
		memset(pucDataName, 0, (uiNameLength + 1));
		memcpy(pucDataName, pucData, uiNameLength);
		pTreeNodeServiceProviderName->m_strText.Format(L"service_provider_name[%d]: %s", uiFieldLength,CString(pucDataName));
		pTreeNodeCurrentLoop->m_strText.AppendFormat(L"service_provider_name: %s  ", CString(pucDataName));
		delete [] pucDataName;
		uiOffset += uiFieldLength;

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		pucData += uiNameLength;
		uiDescriptorPayloadLength -= uiNameLength;

		pTreeList->AppendLastChild( pTreeNodeServiceProviderName, pTreeNodeCurrentLoop);
		pTreeList->UpdateText(pTreeNodeCurrentLoop);

		if( 1 > uiDescriptorPayloadLength )
		{

			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			uiOffset += uiFieldLength;
			return FAILURE;
		}

		// 8 Bit service_name_length.
		uiFieldLength = 8;
		uiData = (pucData[0]);
		CTreeNode *pTreeNodeServiceNameLength  = new CTreeNode(pTSPacketStore, L"service_name_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		pTreeList->AppendLastChild(pTreeNodeServiceNameLength, pTreeNodeCurrentLoop);

		uiNameLength = uiData;


		//Move the pointer.
		pucData += 1;
		uiDescriptorPayloadLength -= 1;

		if( uiNameLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}


		// descriptor_length*8 Bit service_name.
		uiFieldLength = uiNameLength*8;
		//uiData = pucData[2];
		CTreeNode *pTreeNodeServiceName  = new CTreeNode(pTSPacketStore, L"service_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
		pucDataName = new UCHAR8[uiNameLength + 1];
		memset(pucDataName, 0, (uiNameLength + 1));
		memcpy(pucDataName, pucData, uiNameLength);
		pTreeNodeServiceName->m_strText.Format(L"service_name[%d]: %s", uiFieldLength,CString(pucDataName));
		pTreeNodeCurrentLoop->m_strText.AppendFormat(L"service_name: %s  ", CString(pucDataName));
		delete [] pucDataName;
		uiOffset += uiFieldLength;

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		pucData += uiNameLength;
		uiDescriptorPayloadLength -= uiNameLength;

		pTreeList->AppendLastChild(pTreeNodeServiceName, pTreeNodeCurrentLoop);
		pTreeList->UpdateText(pTreeNodeCurrentLoop);

	}//while( uiItemLength >= 4)

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseMultilingualBouquetNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// bouquet_name loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"bouquet_name loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 4 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 8 Bit bouquet_name_length.
		uiFieldLength = 8;
		uiData = (pucData[3]);
		CTreeNode *pTreeNodeNameLength  = new CTreeNode(pTSPacketStore, L"bouquet_name_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		UINT32 uiNameLength;
		uiNameLength = uiData;


		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 4 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"language_code: %c%c%c   ",  
				pucData[0], pucData[1], pucData[2]
				);

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeNameLength, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 4;
		uiDescriptorPayloadLength -= 4;

		if( uiNameLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength -= uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}


		// descriptor_length*8 Bit bouquet_name.
		uiFieldLength = uiNameLength*8;
		//uiData = pucData[2];
		CTreeNode *pTreeNodeBouquetName  = new CTreeNode(pTSPacketStore, L"bouquet_name", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
		UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
		memset(pucDataName, 0, (uiNameLength + 1));
		memcpy(pucDataName, pucData, uiNameLength);
		pTreeNodeBouquetName->m_strText.Format(L"bouquet_name[%d]: %s", uiFieldLength,CString(pucDataName));
		pTreeNodeCurrentLoop->m_strText.AppendFormat(L"bouquet_name: %s   ", CString(pucDataName));
		delete [] pucDataName;
		uiOffset += uiFieldLength;

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		pucData += uiNameLength;
		uiDescriptorPayloadLength -= uiNameLength;

		pTreeList->AppendLastChild( pTreeNodeBouquetName, pTreeNodeCurrentLoop);
		pTreeList->UpdateText(pTreeNodeCurrentLoop);


	}//while( uiItemLength >= 4)

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}
	return SUCCESS;
}



EResult CDescriptor::ParseMultilingualComponentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 
	if( 1 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 8 Bit component_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"component_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Move the pointer.
	pucData += 1;
	uiDescriptorPayloadLength -= 1;


	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// component_description loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"component_description loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 4 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 8 Bit text_description_length.
		uiFieldLength = 8;
		uiData = (pucData[3]);
		CTreeNode *pTreeNodeNameLength  = new CTreeNode(pTSPacketStore, L"text_description_length", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		UINT32 uiNameLength;
		uiNameLength = uiData;


		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 4 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"language_code: %c%c%c   ",  
				pucData[0], pucData[1], pucData[2]
				);
				
		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeNameLength, pTreeNodeCurrentLoop);
			
		//Move the pointer.
		pucData += 4;
		uiDescriptorPayloadLength -= 4;

		if( uiNameLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength -= uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}


		// descriptor_length*8 Bit component_description.
		uiFieldLength = uiNameLength*8;
		//uiData = pucData[2];
		CTreeNode *pTreeNodeComponentDescription  = new CTreeNode(pTSPacketStore, L"component_description", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
		UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
		memset(pucDataName, 0, (uiNameLength + 1));
		memcpy(pucDataName, pucData, uiNameLength);
		pTreeNodeComponentDescription->m_strText.Format(L"component_description[%d]: %s", uiFieldLength,CString(pucDataName));
		pTreeNodeCurrentLoop->m_strText.AppendFormat(L"component_description: %s   ", CString(pucDataName));
		delete [] pucDataName;
		uiOffset += uiFieldLength;

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		pucData += uiNameLength;
		uiDescriptorPayloadLength -= uiNameLength;

		pTreeList->AppendLastChild( pTreeNodeComponentDescription, pTreeNodeCurrentLoop);
		pTreeList->UpdateText(pTreeNodeCurrentLoop);


	}//while( uiItemLength >= 4)

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParsePrivateDataSpecifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;
   
	if( 4 <= uiDescriptorLength )
	{
		// 32 Bit private_data_specifier.
		uiFieldLength = 32;
		uiData = ((pucData[0]<< 24 )| (pucData[1]<< 16 )| (pucData[2]<< 8 )| pucData[3]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_specifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"private_data_specifier[%d]: 0x%08X, type: %s", uiFieldLength, uiData, GetPrivateDataSpecifierName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += 4;
		uiDescriptorLength -= 4;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseServiceMoveDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 6 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 16 Bit new_original_network_id.
	uiFieldLength = 16;
	uiData = ((pucData[0]<< 8 )| pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"new_original_network_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 16 Bit new_transport_stream_id.
	uiFieldLength = 16;
	uiData = ((pucData[2]<< 8 )| pucData[3]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"new_transport_stream_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 16 Bit new_service_id.
	uiFieldLength = 16;
	uiData = ((pucData[4]<< 8 )| pucData[5]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"new_service_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Move the pointer.
	pucData += 6;
	uiDescriptorPayloadLength -= 6;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}
	return SUCCESS;
}


EResult CDescriptor::ParseShortSmoothingBufferDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 2 Bit sb_size.
	uiFieldLength = 2;
	uiData = ((pucData[0] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"sb_size", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"sb_size[%d]: %s", uiFieldLength, GetSbSizeName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 6 Bit sb_leak_rate.
	uiFieldLength = 6;
	uiData = ((pucData[0]) & 0x3F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"sb_leak_rate", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"sb_leak_rate[%d]: %s", uiFieldLength, GetLeakRateName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( 0 != uiDescriptorPayloadLength )
	{
		//DVB_reserved
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DVB_reserved", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}
	return SUCCESS;
}



EResult CDescriptor::ParseFrequencyListDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 1 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 6 Bit reserved_future_use.
	uiFieldLength = 6;
	uiData = ((pucData[0] >> 2) & 0x3F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit coding_type.
	uiFieldLength = 2;
	uiData = (pucData[0]  & 0x3 );
	pTreeNode  = new CTreeNode(pTSPacketStore, L"coding_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"coding_type[%d]: %s", uiFieldLength, GetCodingTypeName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;


	UINT32 uiCodingType = uiData;
	while(  4 <= uiDescriptorPayloadLength )
	{
		// 32 Bit centre_frequency.
		uiFieldLength = 32;
		uiData = ((pucData[0]<< 24 )| (pucData[1]<< 16 )| (pucData[2] << 8) | (pucData[3]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"centre_frequency", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );

		
		if( 0x01 == uiCodingType)
		{
			//satellite
			pTreeNode->m_strText.Format(L"centre_frequency[%d]: %03X.%05X GHz", uiFieldLength, (uiData >> 20), (uiData & 0xFFFFF));
		}
		else if( 0x02 == uiCodingType)
		{
			//cable
			pTreeNode->m_strText.Format(L"centre_frequency[%d]: %04X.%04X MHz", uiFieldLength, (uiData >> 16), (uiData & 0xFFFF));

		}
		else if( 0x03 == uiCodingType)
		{
			//terrestrial
			pTreeNode->m_strText.Format(L"centre_frequency[%d]: 0x%08X 10Hz", uiFieldLength, uiData);

		}
		else
		{
			//Unknown
			pTreeNode->m_strText.Format(L"centre_frequency[%d]: 0x%08X", uiFieldLength);

		}
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 4;
		uiDescriptorPayloadLength -= 4;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParsePartialTransportStreamDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

  
	if( 8 <= uiDescriptorLength )
	{
		// 2 Bit DVB_reserved_future_use.
		uiFieldLength = 2;
		uiData = ( (pucData[0] >> 6) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DVB_reserved_future_use", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 22 Bit peak_rate.
		uiFieldLength = 22;
		uiData = ((( pucData[0] & 0x3F) << 16) | (pucData[1] << 8) | (pucData[2]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"peak_rate", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"peak_rate[%d]: 0x%08X 400b/s", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit DVB_reserved_future_use.
		uiFieldLength = 2;
		uiData = ( (pucData[3] >> 6) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DVB_reserved_future_use", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 22 Bit minimum_overall_smoothing_rate.
		uiFieldLength = 22;
		uiData = ((( pucData[3] & 0x3F) << 16) | (pucData[4] << 8) | (pucData[5]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"minimum_overall_smoothing_rate", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"minimum_overall_smoothing_rate[%d]: 0x%08X 400b/s", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit DVB_reserved_future_use.
		uiFieldLength = 2;
		uiData = ( (pucData[6] >> 6) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"DVB_reserved_future_use", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 14 Bit maximum_overall_smoothing_buffer.
		uiFieldLength = 14;
		uiData = ((( pucData[6] & 0x3F) << 8) | (pucData[7]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"maximum_overall_smoothing_buffer", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"maximum_overall_smoothing_buffer[%d]: 0x%08X Byte", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;


		//Move the pointer.
		pucData += 8;
		uiDescriptorLength -= 8;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseDataBroadcastDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if(  4 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 16 Bit data_broadcast_id.
	uiFieldLength = 16;
	uiData = ((pucData[0] << 8) | pucData[1]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"data_broadcast_id", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"data_broadcast_id[%d]: %s", uiFieldLength, GetDataBroadcastIdName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 8 Bit component_tag.
	uiFieldLength = 8;
	uiData = (pucData[2]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"component_tag", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 8 Bit selector_length.
	uiFieldLength = 8;
	uiData = (pucData[3]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"selector_length", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiNameLength = uiData;

	//Move the pointer.
	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if(uiDescriptorPayloadLength < uiNameLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit selector_byte.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"selector_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;
 
	if( 4 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 24 Bit language_code.
	uiFieldLength = 24;
	uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 3;
	uiDescriptorPayloadLength -= 3;


	// 8 Bit text_length.
	uiFieldLength = 8;
	uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"text_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	uiNameLength = uiData;

	//Move the pointer.
	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if(uiDescriptorPayloadLength < uiNameLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// descriptor_length*8 Bit text.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"text", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiNameLength + 1];
	memset(pucDataName, 0, (uiNameLength + 1));
	memcpy(pucDataName, pucData, uiNameLength);
	pTreeNode->m_strText.Format(L"text[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseDataBroadcastIdDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 
	if(  2 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 16 Bit data_broadcast_id.
	uiFieldLength = 16;
	uiData = ((pucData[0] << 8) | pucData[1]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"data_broadcast_id", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"data_broadcast_id[%d]: %s", uiFieldLength, GetDataBroadcastIdName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	uiDescriptorPayloadLength -= 2;
	pucData += 2;

	UINT32 uiNameLength = uiDescriptorPayloadLength;

	// descriptor_length*8 Bit id_selector_byte.
	uiFieldLength = uiNameLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"id_selector_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiNameLength;
	uiDescriptorPayloadLength -= uiNameLength;
 
	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}


	return SUCCESS;
}



EResult CDescriptor::ParseScramblingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	if( 1 > uiDescriptorLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 8 Bit scrambling_mode.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"scrambling_mode", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	uiDescriptorLength -= 1;
	pucData += 1;

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}


	return SUCCESS;
}


EResult CDescriptor::ParseCommonDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	// descriptor_length*8 Bit descriptor_data.
	uiFieldLength = uiDescriptorLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_data", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	return SUCCESS;
}


EResult CDescriptor::ParsePDCDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

  
	if( 3 <= uiDescriptorLength )
	{
		// 4 Bit reserved_future_use.
		uiFieldLength = 4;
		uiData = ( (pucData[0] >> 4) & 0xF);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 5 Bit day.
		uiFieldLength = 5;
		uiData = ((( pucData[0] & 0xF) << 1) | ( (pucData[1] >> 7) & 0x1) );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"day", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"day[%d]: %d days", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 4 Bit month.
		uiFieldLength = 4;
		uiData = ( (pucData[1] >> 3) & 0xF);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"month", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"month[%d]: %d months", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 5 Bit hour.
		uiFieldLength = 5;
		uiData = ((( pucData[1] & 0x7) << 2) | ( (pucData[2] >> 6) & 0x3) );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"hour", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"hour[%d]: %d hours", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 6 Bit minute.
		uiFieldLength = 6;
		uiData = ( pucData[2] & 0x3F );
		pTreeNode  = new CTreeNode(pTSPacketStore, L"minute", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"minute[%d]: %d minutes", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += 3;
		uiDescriptorLength -= 3;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseAC3Descriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 1 Bit component_type_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"component_type_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiComponentTypeFlag = uiData;

	// 1 Bit bsid_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"bsid_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiBsidFlag = uiData;

	// 1 Bit mainid_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 5) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"mainid_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiMainIdFlag = uiData;

	// 1 Bit asvc_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 4) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"asvc_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiAsvcFlag = uiData;

	// 4 Bit reserved_flags.
	uiFieldLength = 4;
	uiData = ((pucData[0]) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_flags", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if(( 0x1 == uiComponentTypeFlag ) && ( 1 <= uiDescriptorPayloadLength ))
	{
		// 8 Bit component_type.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"component_type", uiOffset, uiFieldLength, uiData );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiDescriptorPayloadLength -= 1;
	}


	if(( 0x1 == uiBsidFlag ) && ( 1 <= uiDescriptorPayloadLength ))
	{
		// 8 Bit bsid.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"bsid", uiOffset, uiFieldLength, uiData );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiDescriptorPayloadLength -= 1;
	}


	if(( 0x1 == uiMainIdFlag ) && ( 1 <= uiDescriptorPayloadLength ))
	{
		// 8 Bit mainid.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"mainid", uiOffset, uiFieldLength, uiData );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiDescriptorPayloadLength -= 1;
	}

	if(( 0x1 == uiAsvcFlag ) && ( 1 <= uiDescriptorPayloadLength ))
	{
		// 8 Bit asvc.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"asvc", uiOffset, uiFieldLength, uiData );
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 1;
		uiDescriptorPayloadLength -= 1;
	}

	if( 0 != uiDescriptorPayloadLength )
	{
		//additional_info
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"additional_info", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}


	return SUCCESS;
}

EResult CDescriptor::ParseAncillaryDataDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;
   
	if( 1 > uiDescriptorLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 8 Bit ancillary_data_identifier.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ancillary_data_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"ancillary_data_identifier[%d]: %s", uiFieldLength, GetAncillaryDataIdentifierName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	uiDescriptorLength -= 1;
	pucData += 1;

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseCellListDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 
	// cell loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"cell loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 10 <= uiDescriptorPayloadLength )
	{
		// cell loop.
		uiFieldLength = 10*8;
		CTreeNode *pTreeNodeCurrentLoop = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);


		// 16 Bit cell_id.
		uiFieldLength = 16;
		uiData = ((pucData[0] << 8 ) | (pucData[1]) );
		CTreeNode * pTreeNodeCellId = new CTreeNode(pTSPacketStore, L"cell_id", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 16 Bit cell_latitude.
		uiFieldLength = 16;
		uiData = ((pucData[2] << 8 ) | (pucData[3]) );
		CTreeNode * pTreeNodeCellLatitude = new CTreeNode(pTSPacketStore, L"cell_latitude", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 16 Bit cell_longitude.
		uiFieldLength = 16;
		uiData = ((pucData[4] << 8 ) | (pucData[5]) );
		CTreeNode * pTreeNodeCellLongitude = new CTreeNode(pTSPacketStore, L"cell_longitude", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;


		// 12 Bit cell_extent_of_latitude.
		uiFieldLength = 12;
		uiData = ((pucData[6] << 4 ) | ((pucData[7] >> 4) & 0xF) );
		CTreeNode * pTreeNodeCellExtentLatitude = new CTreeNode(pTSPacketStore, L"cell_extent_of_latitude", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 12 Bit cell_extent_of_longitude.
		uiFieldLength = 12;
		uiData = (((pucData[7] & 0xF) << 8 ) | ((pucData[8] )) );
		CTreeNode * pTreeNodeCellExtentLongitude = new CTreeNode(pTSPacketStore, L"cell_extent_of_longitude", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 8 Bit subcell_info_loop_length.
		uiFieldLength = 8;
		uiData = (pucData[9] );
		CTreeNode * pTreeNodeSubcellInfoLength  = new CTreeNode(pTSPacketStore, L"subcell_info_loop_length", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		pucData += 10;
		uiDescriptorPayloadLength -= 10;

		pTreeNodeCurrentLoop->m_strText.Format(L"cell_id: 0x%04X",	pTreeNodeCellId->m_uiValue);

		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeCellId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeCellLatitude, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeCellLongitude, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeCellExtentLatitude, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeCellExtentLongitude, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeSubcellInfoLength, pTreeNodeCurrentLoop);

		//Save the value of elementary_cell_field_length.
		UINT32 uiCellInfoLength = uiData;


		if( uiCellInfoLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			//We can NOT decide the length of current loop, so we have to add up to it one bye one.
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}

		// uiCellInfoLength*8 Bit subcell_info loop.
		uiFieldLength = uiCellInfoLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"subcell_info loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		uiDescriptorPayloadLength -= uiCellInfoLength;

		CTreeNode *  pTreeNodeLoops2 = pTreeNode;
		//The second loop.
		while( 8 <= uiCellInfoLength)
		{

			// Current loop 2.
			uiFieldLength = 8*8;
			CTreeNode * pTreeNodeCurrentLoop2 = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);

			// 8 Bit cell_id_extension.
			uiFieldLength = 8;
			uiData = (pucData[0] );
			CTreeNode * pTreeNodeCellIdExtension  = new CTreeNode(pTSPacketStore, L"cell_id_extension", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;


			// 16 Bit subcell_latitude.
			uiFieldLength = 16;
			uiData = ((pucData[1] << 8 ) | (pucData[2]) );
			CTreeNode * pTreeNodeSubcellLatitude = new CTreeNode(pTSPacketStore, L"subcell_latitude", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;

			// 16 Bit subcell_longitude.
			uiFieldLength = 16;
			uiData = ((pucData[3] << 8 ) | (pucData[4]) );
			CTreeNode * pTreeNodeSubcellLongitude = new CTreeNode(pTSPacketStore, L"subcell_longitude", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;


			// 12 Bit subcell_extent_of_latitude.
			uiFieldLength = 12;
			uiData = ((pucData[4] << 4 ) | ((pucData[6] >> 4) & 0xF) );
			CTreeNode * pTreeNodeSubcellExtentOfLatitude = new CTreeNode(pTSPacketStore, L"subcell_extent_of_latitude", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;

			// 12 Bit subcell_extent_of_longitude.
			uiFieldLength = 12;
			uiData = (((pucData[6] & 0xF) << 8 ) | ((pucData[7] )) );
			CTreeNode * pTreeNodeSubcellExtentOfLongitude = new CTreeNode(pTSPacketStore, L"subcell_extent_of_longitude", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;


			pTreeNodeCurrentLoop2->m_strText.Format(L"cell_id_extension: 0x%02X", 
				pTreeNodeCellIdExtension->m_uiValue);

			pTreeList->AppendLastChild(pTreeNodeCurrentLoop2, pTreeNodeLoops2);
			pTreeList->AppendLastChild(pTreeNodeCellIdExtension, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeSubcellLatitude, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeSubcellLongitude, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeSubcellExtentOfLatitude, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeSubcellExtentOfLongitude, pTreeNodeCurrentLoop2);

			pucData += 8;
			uiCellInfoLength -= 8;
		}

		if( 0 != uiCellInfoLength )
		{
			//Invalid End.
			uiFieldLength = uiCellInfoLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeLoops2);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			pucData += uiCellInfoLength;
			uiCellInfoLength = 0;
		}

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseCellFrequencyLinkDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 
	// cell_frequency loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"cell_frequency loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 7 <= uiDescriptorPayloadLength )
	{
		// cell loop.
		uiFieldLength = 7*8;
		CTreeNode *pTreeNodeCurrentLoop = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);


		// 16 Bit cell_id.
		uiFieldLength = 16;
		uiData = ((pucData[0] << 8 ) | (pucData[1]) );
		CTreeNode * pTreeNodeCellId = new CTreeNode(pTSPacketStore, L"cell_id", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 32 Bit frequency.
		uiFieldLength = 32;
		uiData = ((pucData[2]<< 24 )| (pucData[3]<< 16 )| (pucData[4]<< 8 )| pucData[5]);
		CTreeNode * pTreeNodeFrequency  = new CTreeNode(pTSPacketStore, L"frequency", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeFrequency->m_strText.Format(L"frequency[%d]: 0x%08X 10Hz", uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 8 Bit subcell_info_loop_length.
		uiFieldLength = 8;
		uiData = (pucData[6] );
		CTreeNode * pTreeNodeSubcellInfoLength  = new CTreeNode(pTSPacketStore, L"subcell_info_loop_length", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		pucData += 7;
		uiDescriptorPayloadLength -= 7;

		pTreeNodeCurrentLoop->m_strText.Format(L"cell_id: 0x%04X, frequency: 0x%08X 10Hz",	pTreeNodeCellId->m_uiValue, pTreeNodeFrequency->m_uiValue);

		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeCellId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeFrequency, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeSubcellInfoLength, pTreeNodeCurrentLoop);

		//Save the value of elementary_cell_field_length.
		UINT32 uiCellInfoLength = uiData;


		if( uiCellInfoLength > uiDescriptorPayloadLength )
		{
			//Invalid End.
			uiFieldLength = uiDescriptorPayloadLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			//We can NOT decide the length of current loop, so we have to add up to it one bye one.
			pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

			pucData += uiDescriptorPayloadLength;
			uiDescriptorPayloadLength = 0;

			break;
		}

		// uiCellInfoLength*8 Bit subcell_info loop.
		uiFieldLength = uiCellInfoLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"subcell_info loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);

		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
		uiDescriptorPayloadLength -= uiCellInfoLength;

		CTreeNode *  pTreeNodeLoops2 = pTreeNode;
		//The second loop.
		while( 5 <= uiCellInfoLength)
		{

			// Current loop 2.
			uiFieldLength = 5*8;
			CTreeNode * pTreeNodeCurrentLoop2 = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);

			// 8 Bit cell_id_extension.
			uiFieldLength = 8;
			uiData = (pucData[0] );
			CTreeNode * pTreeNodeCellIdExtension  = new CTreeNode(pTSPacketStore, L"cell_id_extension", uiOffset, uiFieldLength, uiData);
			uiOffset += uiFieldLength;

			// 32 Bit transposer_frequency.
			uiFieldLength = 32;
			uiData = ((pucData[1]<< 24 )| (pucData[2]<< 16 )| (pucData[3]<< 8 )| pucData[4]);
			CTreeNode * pTreeNodeTransposerFrequency  = new CTreeNode(pTSPacketStore, L"transposer_frequency", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
			pTreeNodeTransposerFrequency->m_strText.Format(L"transposer_frequency[%d]: 0x%08X 10Hz", uiFieldLength, uiData);
			uiOffset += uiFieldLength;


			pTreeNodeCurrentLoop2->m_strText.Format(L"cell_id_extension: 0x%02X, transposer_frequency: 0x%08X 10Hz", 
				pTreeNodeCellIdExtension->m_uiValue, pTreeNodeTransposerFrequency->m_uiValue);

			pTreeList->AppendLastChild(pTreeNodeCurrentLoop2, pTreeNodeLoops2);
			pTreeList->AppendLastChild(pTreeNodeCellIdExtension, pTreeNodeCurrentLoop2);
			pTreeList->AppendLastChild(pTreeNodeTransposerFrequency, pTreeNodeCurrentLoop2);

			pucData += 5;
			uiCellInfoLength -= 5;
		}

		if( 0 != uiCellInfoLength )
		{
			//Invalid End.
			uiFieldLength = uiCellInfoLength*8;
			pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
			pTreeList->AppendLastChild( pTreeNode, pTreeNodeLoops2);
			//pTreeNodeTmp = pTreeNode;
			uiOffset += uiFieldLength;

			pucData += uiCellInfoLength;
			uiCellInfoLength = 0;
		}

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseAnnouncementSupportDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 2 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}


	// 16 Bit announcement_support_indicator.
	uiFieldLength = 16;
	uiData = ((pucData[0] << 8) | pucData[1]);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"announcement_support_indicator", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"announcement_support_indicator[%d]: 0x%04X, type: %s", uiFieldLength, uiData, GetAnnouncementSupportIndicatorName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 2;
	uiDescriptorPayloadLength -= 2;

	// announcement loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"announcement loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 1 <= uiDescriptorPayloadLength )
	{
		// announcement loop.
		uiFieldLength = 1*8;
		CTreeNode *pTreeNodeCurrentLoop = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);


		// 4 Bit announcement_type.
		uiFieldLength = 4;
		uiData = ((pucData[0] >> 4 ) & 0xF);
		CTreeNode * pTreeNodeAnnouncementType = new CTreeNode(pTSPacketStore, L"announcement_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
		pTreeNodeAnnouncementType->m_strText.Format(L"announcement_type[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetAnnouncementTypeName(uiData));
		uiOffset += uiFieldLength;

		// 1 Bit reserved_future_use.
		uiFieldLength = 1;
		uiData = ((pucData[0] >> 3 ) & 0x1);
		CTreeNode * pTreeNodeReserved1 = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 3 Bit reference_type.
		uiFieldLength = 3;
		uiData = (pucData[0] & 0x7 );
		CTreeNode * pTreeNodeReferenceType = new CTreeNode(pTSPacketStore, L"reference_type", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		UINT32 uiReferenceType = uiData;
		pucData += 1;
		uiDescriptorPayloadLength -= 1;

		pTreeNodeCurrentLoop->m_strText.Format(L"announcement_type: 0x%02X, type: %s",
			pTreeNodeAnnouncementType->m_uiValue,
			GetAnnouncementTypeName(pTreeNodeAnnouncementType->m_uiValue)
			);

		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeAnnouncementType, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReserved1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReferenceType, pTreeNodeCurrentLoop);

		//reference_type.
		if(( 0x01 == uiReferenceType ) 
			|| ( 0x02 == uiReferenceType )
			|| ( 0x03 == uiReferenceType )
		  )
		{
			if( 7 > uiDescriptorPayloadLength)
			{
				//Invalid End.
				uiFieldLength = uiDescriptorPayloadLength*8;
				pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				return FAILURE;
			}
			else
			{
				// 16 Bit original_network_id.
				uiFieldLength = 16;
				uiData = ((pucData[0] << 8) | pucData[1]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"original_network_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				// 16 Bit transport_stream_id.
				uiFieldLength = 16;
				uiData = ((pucData[2] << 8) | pucData[3]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"transport_stream_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				// 16 Bit service_id.
				uiFieldLength = 16;
				uiData = ((pucData[4] << 8) | pucData[5]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"service_id", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				// 8 Bit component_tag.
				uiFieldLength = 8;
				uiData = ( pucData[6]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"component_tag", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				pucData += 7;
				uiDescriptorPayloadLength -= 7;
			}

		}

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseApplicationSignallingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"application_signalling loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 3 <= uiDescriptorLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit application_type.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		CTreeNode * pTreeNodeApplicationType  = new CTreeNode(pTSPacketStore, L"application_type", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 3 Bit reserved.
		uiFieldLength = 3;
		uiData = (( pucData[2] >> 5) & 0x7);
		CTreeNode * pTreeNodeReserved1 = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 5 Bit AIT_version_number.
		uiFieldLength = 5;
		uiData = ( pucData[2]  & 0x1F);
		CTreeNode * pTreeNodeAITVersionNumber = new CTreeNode(pTSPacketStore, L"AIT_version_number", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 3 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"application_type: 0x%04X, AIT_version_number: 0x%02X", 
			pTreeNodeApplicationType->m_uiValue, pTreeNodeAITVersionNumber->m_uiValue);

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeApplicationType, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReserved1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeAITVersionNumber, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 3;
		uiDescriptorLength -= 3;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;		
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseAdaptationFieldDataDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;
   
	if( 1 > uiDescriptorLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 8 Bit adaptation_field_data_identifier.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"adaptation_field_data_identifier", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"adaptation_field_data_identifier[%d]: 0x%02X, type:%s", uiFieldLength, uiData, GetaAdaptationFieldDataIdentifierName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	uiDescriptorLength -= 1;
	pucData += 1;

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseServiceIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;

	// descriptor_length*8 Bit textual_service_identifier.
	uiFieldLength = uiDescriptorPayloadLength*8;
	//uiData = pucData[2];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"textual_service_identifier", uiOffset, uiFieldLength, VALUE_ZERO, NODE_SPECIAL);
	UCHAR8 *pucDataName = new UCHAR8[uiDescriptorPayloadLength + 1];
	memset(pucDataName, 0, (uiDescriptorPayloadLength + 1));
	memcpy(pucDataName, pucData, uiDescriptorPayloadLength);
	pTreeNode->m_strText.Format(L"textual_service_identifier[%d]: %s", uiFieldLength,CString(pucDataName));
	delete [] pucDataName;
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += uiDescriptorPayloadLength;
	uiDescriptorPayloadLength -= uiDescriptorPayloadLength;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseServiceAvailabilityDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 1 > uiDescriptorPayloadLength )
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// 1 Bit availability_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"availability_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 7 Bit reserved_future_use.
	uiFieldLength = 7;
	uiData = (pucData[0]  & 0x7F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;



	while(  2 <= uiDescriptorPayloadLength )
	{
		// 16 Bit cell_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"cell_id", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 2;
		uiDescriptorPayloadLength -= 2;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseTVAIdDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

	//Begin the loop.
	uiFieldLength = uiDescriptorLength*8;
	pTreeNode  = new CTreeNode(pTSPacketStore, L"TVA_id loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	/*It is a loop, do NOT subtract the length.*/
	//uiOffset += uiFieldLength;

	CTreeNode * pTreeNodeLoops = pTreeNodeTmp;       
	while( 3 <= uiDescriptorLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 16 Bit TVA_id.
		uiFieldLength = 16;
		uiData = ((pucData[0]<< 8 )| pucData[1]);
		CTreeNode * pTreeNodeTVAId  = new CTreeNode(pTSPacketStore, L"TVA_id", uiOffset, uiFieldLength, uiData );
		uiOffset += uiFieldLength;

		// 5 Bit reserved.
		uiFieldLength = 5;
		uiData = (( pucData[2] >> 3) & 0x1F);
		CTreeNode * pTreeNodeReserved1 = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 3 Bit running_status.
		uiFieldLength = 3;
		uiData = ( pucData[2]  & 0x7);
		CTreeNode * pTreeNodeRunningStatus = new CTreeNode(pTSPacketStore, L"running_status", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
		pTreeNodeRunningStatus->m_strText.Format(L"running_status[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetRunningStatusName(uiData));
		uiOffset += uiFieldLength;

		CTreeNode * pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 3 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"TVA_id: 0x%04X, running_status: %s", 
			pTreeNodeTVAId->m_uiValue, GetRunningStatusName(pTreeNodeRunningStatus->m_uiValue));

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeTVAId, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeReserved1, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeRunningStatus, pTreeNodeCurrentLoop);

		//Move the pointer.
		pucData += 3;
		uiDescriptorLength -= 3;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;		
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseContentIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	// crid loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"crid loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 1 <= uiDescriptorPayloadLength )
	{
		// crid loop.
		uiFieldLength = 1*8;
		CTreeNode *pTreeNodeCurrentLoop = new CTreeNode(pTSPacketStore, L"", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);


		// 6 Bit crid_type.
		uiFieldLength = 6;
		uiData = ((pucData[0] >> 2 ) & 0x3F);
		CTreeNode * pTreeNodeCridType = new CTreeNode(pTSPacketStore, L"crid_type", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		// 2 Bit crid_location.
		uiFieldLength = 2;
		uiData = ((pucData[0] ) & 0x3);
		CTreeNode * pTreeNodeCridLocation = new CTreeNode(pTSPacketStore, L"crid_location", uiOffset, uiFieldLength, uiData);
		uiOffset += uiFieldLength;

		pucData += 1;
		uiDescriptorPayloadLength -= 1;

		pTreeNodeCurrentLoop->m_strText.Format(L"crid_type: 0x%02X, crid_location: 0x%02X",
			pTreeNodeCridType->m_uiValue,
			pTreeNodeCridLocation->m_uiValue
			);

		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeCridType, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeCridLocation, pTreeNodeCurrentLoop);

		if( 0x0 == pTreeNodeCridLocation->m_uiValue)
		{
			if( 1 > uiDescriptorPayloadLength)
			{
				//Invalid End.
				uiFieldLength = uiDescriptorPayloadLength*8;
				pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;

				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				return FAILURE;
			}
			else
			{
				// 8 Bit crid_length.
				uiFieldLength = 8;
				uiData = (pucData[0]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"crid_length", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				UINT32 uiCridLength = uiData;
				
				pucData += 1;
				uiDescriptorPayloadLength -= 1;

				if( uiCridLength > uiDescriptorPayloadLength)
				{
					//Invalid End.
					uiFieldLength = uiDescriptorPayloadLength*8;
					pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
					pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
					uiOffset += uiFieldLength;
					return FAILURE;
				}

				// N byte crid_byte.
				uiFieldLength = 8*uiCridLength;
				//uiData = (pucData[0]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"crid_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

				pucData += uiCridLength;
				uiDescriptorPayloadLength -= uiCridLength;
			}

			continue;
		}


		if( ( 0x1 == pTreeNodeCridLocation->m_uiValue ))
		{
			if( 2 > uiDescriptorPayloadLength)
			{
				//Invalid End.
				uiFieldLength = uiDescriptorPayloadLength*8;
				pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;

				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
				return FAILURE;
			}
			else
			{
				// 16 Bit crid_ref.
				uiFieldLength = 16;
				uiData = ((pucData[0] << 8) | pucData[1]);
				pTreeNode = new CTreeNode(pTSPacketStore, L"crid_ref", uiOffset, uiFieldLength, uiData);
				pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
				uiOffset += uiFieldLength;
				pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;
	
				pucData += 2;
				uiDescriptorPayloadLength -= 2;
			}

			continue;
		}

		//Unknown.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Unknown crid_location", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
		//pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;
		pTreeNodeCurrentLoop->m_uiLength += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}


	return SUCCESS;
}

EResult CDescriptor::ParseTimeSliceFecIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 3 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 1 Bit time_slicing.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"time_slicing", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit mpe_fec.
	uiFieldLength = 2;
	uiData = ((pucData[0] >> 5) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"mpe_fec", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit reserved_for_future_use.
	uiFieldLength = 2;
	uiData = ((pucData[0] >> 3) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved_for_future_use", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit frame_size.
	uiFieldLength = 3;
	uiData = ((pucData[0]) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_size", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit max_burst_duration.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"max_burst_duration", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 4 Bit max_average_rate.
	uiFieldLength = 4;
	uiData = ((pucData[2] >> 4) &0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"max_average_rate", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 4 Bit time_slice_fec_id.
	uiFieldLength = 4;
	uiData = ((pucData[2]) &0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"time_slice_fec_id", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 3;
	uiDescriptorPayloadLength -= 3;

	if( 0 != uiDescriptorPayloadLength )
	{
		//id_selector_byte
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"id_selector_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseECMRepetitionRateDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 16 Bit CA_system_ID.
	uiFieldLength = 16;
	uiData = ((pucData[0] << 8) | pucData[1]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"CA_system_ID", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"CA_system_ID[%d]: 0x%04X, name:%s", uiFieldLength, uiData, GetCASystemName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 16 Bit ECM repetition rate.
	uiFieldLength = 16;
	uiData = ((pucData[2] << 8) | pucData[3]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"ECM repetition rate", uiOffset, uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength )
	{
		//private_data_byte
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseExtensionDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData = 0;
	UINT32 uiFieldLength = 0;
	UCHAR8 ucDescriptorTag = 0;
	UCHAR8 ucDescriptorExtension = 0;

	UINT32 uiDescriptorPayloadLength = 0;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 8 Bit descriptor_tag_extension.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode = new CTreeNode(pTSPacketStore, L"descriptor_tag_extension", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"descriptor_tag_extension[%d]: 0x%02X, name:%s", uiFieldLength, uiData, GetExtendedDescriptorName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	//Save the extension. We need to parse the payloady according to this field.
	ucDescriptorExtension = (UCHAR8)uiData;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	uiFieldLength = 8*uiDescriptorPayloadLength;
	pTreeNode = new CTreeNode(pTSPacketStore, L"descriptor_tag_extension", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);
	pTreeNode->m_strText.Format(L"%s payload", GetExtendedDescriptorName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;


    switch(ucDescriptorExtension)
    {
        case 0x04:
        {            
            ParseT2DeliverySystemDescriptor(pTSPacketStore,pTreeList,pTreeNode,pucData, uiOffset, uiDescriptorPayloadLength);
            break;
        }
        default:
        {
            //No time to parse others.
        }
    }

    //Skip the left data.
	pucData += uiDescriptorPayloadLength;
	uiDescriptorPayloadLength -= uiDescriptorPayloadLength;
	uiOffset += uiFieldLength;


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}

EResult CDescriptor::ParseT2DeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiDescriptorPayloadLength)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeCurrentLoop = NULL;
	CTreeNode * pTreeNodeFrequencies = NULL;
	CTreeNode * pTreeNodeSubcells = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData = 0;
	UINT32 uiFieldLength = 0;
	UCHAR8 ucDescriptorTag = 0;
	UCHAR8 ucDescriptorExtension = 0;
	UINT32 uiCounter = 0;
	UINT32 uiCurrentLoopLength = 0;
	UINT32 uiTfsFlag = 0;
	UINT32 uiFrequencyLoopLength = 0;
	UINT32 uiSubcellLoopLength = 0;
	UINT32 uiFrequencyCounter = 0;
	UINT32 uiSubcellCounter = 0;

    if( 3 > uiDescriptorPayloadLength)
    {
        //Invalid End.
        uiFieldLength = uiDescriptorPayloadLength*8;
        pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
        pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput); 
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
    
        pucData += uiDescriptorPayloadLength;
        uiDescriptorPayloadLength = 0;
    
        return FAILURE;
    }
    
    // 8 Bit plp_id.
    uiFieldLength = 8;
    uiData = pucData[0];
    pTreeNode = new CTreeNode(pTSPacketStore, L"plp_id", uiOffset, uiFieldLength, uiData);
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
    pTreeNodeTmp = pTreeNode;
    uiOffset += uiFieldLength;
    
    // 16 Bit T2_system_id.
    uiFieldLength = 16;
    uiData = ((pucData[1] << 8) | pucData[2]);
    pTreeNode = new CTreeNode(pTSPacketStore, L"T2_system_id", uiOffset, uiFieldLength, uiData);
    pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
    pTreeNodeTmp = pTreeNode;
    uiOffset += uiFieldLength;
    
    pucData += 3;
    uiDescriptorPayloadLength -= 3;
    
    if(2 <= uiDescriptorPayloadLength)
    {
        // 2 Bit SISO/MISO.
        uiFieldLength = 2;
        uiData = (pucData[0] >> 6 )&0x3;
        pTreeNode = new CTreeNode(pTSPacketStore, L"SISO/MISO", uiOffset, uiFieldLength, uiData);
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
    
        // 4 Bit bandwidth.
        uiFieldLength = 4;
        uiData = (pucData[0] >> 2 )&0xF;
        pTreeNode = new CTreeNode(pTSPacketStore, L"bandwidth", uiOffset, uiFieldLength, uiData);
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
    
        // 2 Bit reserved_future_use.
        uiFieldLength = 2;
        uiData = (pucData[0])&0x3;
        pTreeNode = new CTreeNode(pTSPacketStore, L"reserved_future_use", uiOffset, uiFieldLength, uiData);
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
    
    
        // 3 Bit guard_interval.
        uiFieldLength = 3;
        uiData = (pucData[0] >> 5 )&0x7;
        pTreeNode = new CTreeNode(pTSPacketStore, L"guard_interval", uiOffset, uiFieldLength, uiData);
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
    
        // 3 Bit transmission_mode.
        uiFieldLength = 3;
        uiData = (pucData[0] >> 2 )&0x7;
        pTreeNode = new CTreeNode(pTSPacketStore, L"transmission_mode", uiOffset, uiFieldLength, uiData);
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
    
    
        // 1 Bit other_frequency_flag.
        uiFieldLength = 1;
        uiData = (pucData[1] >> 1)&0x1;
        pTreeNode = new CTreeNode(pTSPacketStore, L"other_frequency_flag", uiOffset, uiFieldLength, uiData);
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;
    
        // 1 Bit tfs_flag.
        uiFieldLength = 1;
        uiData = (pucData[1])&0x1;
        pTreeNode = new CTreeNode(pTSPacketStore, L"tfs_flag", uiOffset, uiFieldLength, uiData);
        pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
        pTreeNodeTmp = pTreeNode;
        uiOffset += uiFieldLength;

        //Save the flag.
        uiTfsFlag = uiData;
        
        pucData += 2;
        uiDescriptorPayloadLength -= 2;

        while(4 <= uiDescriptorPayloadLength)
        {
            uiCurrentLoopLength = 0;

            /*We are going into a loop. The length of this loop can only be updated later.*/            
            pTreeNode = new CTreeNode(pTSPacketStore, L"cell", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);
            pTreeNode->m_strText.Format(L"cell %u", uiCounter);
            pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
            pTreeNodeTmp = pTreeNode;

            //Save it as current loop.
            pTreeNodeCurrentLoop = pTreeNode;
            uiCounter++;

            // 16 Bit cell_id.
            uiFieldLength = 16;
            uiData = ((pucData[0] << 8) | pucData[1]);
            pTreeNode = new CTreeNode(pTSPacketStore, L"cell_id", uiOffset, uiFieldLength, uiData);
            pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
            uiOffset += uiFieldLength;

            pucData += 2;
            uiDescriptorPayloadLength -= 2;
            uiCurrentLoopLength += 2;

            if(uiTfsFlag)
            {
                if(uiDescriptorPayloadLength < 1)
                {
                    /*Not enough data.*/
                    break;
                }

                // 8 Bit frequency_loop_length.
                uiFieldLength = 8;
                uiData = pucData[0];
                pTreeNode = new CTreeNode(pTSPacketStore, L"frequency_loop_length", uiOffset, uiFieldLength, uiData);
                pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
                uiOffset += uiFieldLength;

                //Save the length.
                uiFrequencyLoopLength = uiData;

                pucData += 1;
                uiDescriptorPayloadLength -= 1;
                uiCurrentLoopLength += 1;

                if((uiDescriptorPayloadLength < uiFrequencyLoopLength) || ( 0 != (uiFrequencyLoopLength%4)))
                {
                    /*Not enough data or invalid frequency_loop_length.*/
                    break;
                }

                //Add a item to group all frequencies.
                uiFieldLength = uiFrequencyLoopLength*8;
                pTreeNode = new CTreeNode(pTSPacketStore, L"frequencies", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);
                pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);

                //Save the item, we are going to use it to manage all the frequencies.
                pTreeNodeFrequencies = pTreeNode;

                for(uiFrequencyCounter  = 0; uiFrequencyCounter < (uiFrequencyLoopLength/4); ++uiFrequencyCounter)
                {
                    // 32 Bit centre_frequency.
                    uiFieldLength = 32;
                    uiData = ((pucData[0] << 24) | (pucData[1] << 16) | (pucData[2] << 8) | pucData[3]);
                    pTreeNode = new CTreeNode(pTSPacketStore, L"centre_frequency", uiOffset, uiFieldLength, uiData);
                    pTreeList->AppendLastChild( pTreeNode, pTreeNodeFrequencies);
                    uiOffset += uiFieldLength;
                    
                    pucData += 4;
                    uiDescriptorPayloadLength -= 4;
                    uiCurrentLoopLength += 4;
                }
            }
            else
            {
                // 32 Bit centre_frequency.
                uiFieldLength = 32;
                uiData = ((pucData[0] << 24) | (pucData[1] << 16) | (pucData[2] << 8) | pucData[3]);
                pTreeNode = new CTreeNode(pTSPacketStore, L"centre_frequency", uiOffset, uiFieldLength, uiData);
                pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
                uiOffset += uiFieldLength;
                
                pucData += 4;
                uiDescriptorPayloadLength -= 4;
                uiCurrentLoopLength += 4;

            }


            if(uiDescriptorPayloadLength < 1)
            {
                /*Not enough data.*/
                break;
            }


            // 8 Bit subcell_info_loop_length.
            uiFieldLength = 8;
            uiData = pucData[0];
            pTreeNode = new CTreeNode(pTSPacketStore, L"subcell_info_loop_length", uiOffset, uiFieldLength, uiData);
            pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
            uiOffset += uiFieldLength;
            
            //Save the length.
            uiSubcellLoopLength = uiData;
            
            pucData += 1;
            uiDescriptorPayloadLength -= 1;
            uiCurrentLoopLength += 1;


            if((uiDescriptorPayloadLength < uiSubcellLoopLength) || ( 0 != (uiSubcellLoopLength%5)))
            {
                /*Not enough data or invalid subcell_info_loop_length.*/
                break;
            }

            //Add a item to group all frequencies.
            uiFieldLength = uiSubcellLoopLength*8;
            pTreeNode = new CTreeNode(pTSPacketStore, L"subcells", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP_ITEM);
            pTreeList->AppendLastChild( pTreeNode, pTreeNodeCurrentLoop);
            
            //Save the item, we are going to use it to manage all the frequencies.
            pTreeNodeSubcells = pTreeNode;

            for(uiSubcellCounter  = 0; uiSubcellCounter < (uiSubcellLoopLength/5); ++uiSubcellCounter)
            {
                // 8 Bit cell_id_extension.
                uiFieldLength = 8;
                uiData = pucData[0];
                pTreeNode = new CTreeNode(pTSPacketStore, L"cell_id_extension", uiOffset, uiFieldLength, uiData);
                pTreeList->AppendLastChild( pTreeNode, pTreeNodeSubcells);
                uiOffset += uiFieldLength;

                pucData += 1;
                uiDescriptorPayloadLength -= 1;
                uiCurrentLoopLength += 1;

                // 32 Bit transposer_frequency.
                uiFieldLength = 32;
                uiData = ((pucData[0] << 24) | (pucData[1] << 16) | (pucData[2] << 8) | pucData[3]);
                pTreeNode = new CTreeNode(pTSPacketStore, L"transposer_frequency", uiOffset, uiFieldLength, uiData);
                pTreeList->AppendLastChild( pTreeNode, pTreeNodeSubcells);
                uiOffset += uiFieldLength;
                
                pucData += 4;
                uiDescriptorPayloadLength -= 4;
                uiCurrentLoopLength += 4;
            }



            /*Finally update field length for current loop!*/
            pTreeNodeCurrentLoop->m_uiLength = uiCurrentLoopLength*8;
        }
    }

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}




EResult CDescriptor::ParseVideoStreamDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 1 Bit multiple_frame_rate_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"multiple_frame_rate_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 4 Bit frame_rate_code.
	uiFieldLength = 4;
	uiData = ((pucData[0] >> 3) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_rate_code", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 1 Bit MPEG_1_only_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 2) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"MPEG_1_only_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	UINT32 uiMPEG1OnlyFlag = uiData;

	// 1 Bit constrained_parameter_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 1) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"constrained_parameter_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit still_picture_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"still_picture_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if(( 0x0 == uiMPEG1OnlyFlag ) && ( 2 <= uiDescriptorPayloadLength ))
	{
		// 8 Bit profile_and_level_indication.
		uiFieldLength = 8;
		uiData = pucData[0];
		pTreeNode  = new CTreeNode(pTSPacketStore, L"profile_and_level_indication", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit chroma_format.
		uiFieldLength = 2;
		uiData = ((pucData[1] >> 6) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"chroma_format", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"chroma_format[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetChromaFormatName(uiData));
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 1 Bit frame_rate_extension_flag.
		uiFieldLength = 1;
		uiData = ((pucData[1] >> 5) & 0x1);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"frame_rate_extension_flag", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 5 Bit reserved.
		uiFieldLength = 5;
		uiData = ((pucData[1] ) & 0x1F);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += 2;
		uiDescriptorPayloadLength -= 2;
	}

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseAudioStreamDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 1 Bit free_format_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"free_format_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 1 Bit ID.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"ID", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit layer.
	uiFieldLength = 2;
	uiData = ((pucData[0] >> 4) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"layer", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit variable_rate_audio_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 3) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"variable_rate_audio_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 3 Bit reserved.
	uiFieldLength = 3;
	uiData = ((pucData[0]) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseHierarchyDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 4 Bit reserved.
	uiFieldLength = 4;
	uiData = ((pucData[0] >> 4) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 4 Bit hierarchy_type.
	uiFieldLength = 4;
	uiData = ((pucData[0]) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"hierarchy_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"hierarchy_type[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetHierarchyName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit reserved.
	uiFieldLength = 2;
	uiData = ((pucData[1] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 6 Bit hierarchy_layer_index.
	uiFieldLength = 6;
	uiData = ((pucData[1]) & 0x3F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"hierarchy_layer_index", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit reserved.
	uiFieldLength = 2;
	uiData = ((pucData[2] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 6 Bit hierarchy_embedded_layer_index.
	uiFieldLength = 6;
	uiData = ((pucData[2]) & 0x3F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"hierarchy_embedded_layer_index", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 2 Bit reserved.
	uiFieldLength = 2;
	uiData = ((pucData[3] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 6 Bit hierarchy_channel.
	uiFieldLength = 6;
	uiData = ((pucData[3]) & 0x3F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"hierarchy_channel", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseRegistrationDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 32 Bit format_identifier.
	uiFieldLength = 32;
	uiData = ((pucData[0] << 24 ) | ( pucData[1] << 16) | (pucData[2] << 8) | (pucData[3]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"format_identifier", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength )
	{
		//additional_identification_info
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"additional_identification_info", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseDataStreamAlignmentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 8 Bit alignment_type.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"alignment_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"alignment_type[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetAlignmentTypeName(uiData));
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}
	return SUCCESS;
}


EResult CDescriptor::ParseTargetBackgroundGridDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 14 Bit horizontal_size.
	uiFieldLength = 14;
	uiData = ((pucData[0] << 6 ) | (( pucData[1] >> 2) & 0x3F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"horizontal_size", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 14 Bit vertical_size.
	uiFieldLength = 14;
	uiData = (((pucData[1] & 0x3) << 12 ) | (( pucData[2] << 4)) | (( pucData[3] >> 4) & 0xF));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"vertical_size", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 4 Bit aspect_ratio_information.
	uiFieldLength = 4;
	uiData = (( pucData[3] ) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"aspect_ratio_information", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}

EResult CDescriptor::ParseVideoWindowDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 14 Bit horizontal_offset.
	uiFieldLength = 14;
	uiData = ((pucData[0] << 6 ) | (( pucData[1] >> 2) & 0x3F));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"horizontal_offset", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 14 Bit vertical_offset.
	uiFieldLength = 14;
	uiData = (((pucData[1] & 0x3) << 12 ) | (( pucData[2] << 4)) | (( pucData[3] >> 4) & 0xF));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"vertical_offset", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 4 Bit window_priority.
	uiFieldLength = 4;
	uiData = (( pucData[3] ) & 0xF);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"window_priority", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseCADescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 16 Bit CA_system_ID.
	uiFieldLength = 16;
	uiData = ((pucData[0] << 8 ) | (( pucData[1] )));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"CA_system_ID", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
	pTreeNode->m_strText.Format(L"CA_system_ID[%d]: 0x%02X, name: %s", uiFieldLength, uiData, GetCASystemName(uiData));
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 3 Bit reserved.
	uiFieldLength = 3;
	uiData = (( pucData[2] >> 5) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 13 Bit CA_PID.
	uiFieldLength = 13;
	uiData = (((pucData[2] & 0x1F) << 8 ) | (( pucData[3] )));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"CA_PID", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	/*Set service type.*/
	CTSParser *pTSParser = pTSPacketStore->GetTSParser();
	UCHAR8 ucTableId = CSectionHeaderReader::GetTableId( pTSPacketStore->GetDataAddr());
	if( TABLEID_PMT == ucTableId )
	{
		pTSParser->SetPidType( uiData, PID_TYPE_ECM);
	}
	else if(TABLEID_CAT == ucTableId )
	{
		pTSParser->SetPidType( uiData, PID_TYPE_EMM);
	}
	

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength )
	{
		//private_data_byte
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_byte", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}



EResult CDescriptor::ParseISO639LanguageDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 
	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		return FAILURE;
	}

	// language loop.
	uiFieldLength = 8*uiDescriptorPayloadLength;
	//uiData = (pucData[0]);
	pTreeNode = new CTreeNode(pTSPacketStore, L"language loop", uiOffset, uiFieldLength, VALUE_ZERO, NODE_LOOP);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	//uiOffset += uiFieldLength;


	CTreeNode *pTreeNodeLoops = pTreeNodeTmp;
	while( 4 <= uiDescriptorPayloadLength )
	{
		UINT32 uiOffsetCurrentLoop = uiOffset;

		// 24 Bit ISO-639-2[3]_language_code.
		uiFieldLength = 24;
		uiData = ((pucData[0]<< 16 )| (pucData[1]<< 8 )| pucData[2]);
		CTreeNode *pTreeNodeLanguageCode  = new CTreeNode(pTSPacketStore, L"ISO 639_language_code", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNodeLanguageCode->m_strText.Format(L"ISO 639_language_code[%d]: %c%c%c", uiFieldLength, pucData[0], pucData[1], pucData[2]);
		uiOffset += uiFieldLength;

		// 8 Bit audio_type.
		uiFieldLength = 8;
		uiData = (pucData[3]);
		CTreeNode *pTreeNodeAudioType = new CTreeNode(pTSPacketStore, L"audio_type", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
		pTreeNodeAudioType->m_strText.Format(L"audio_type[%d]: 0x%02X, type: %s", uiFieldLength, uiData, GetAudioTypeName(uiData));
		uiOffset += uiFieldLength;

		UINT32 uiNameLength;
		uiNameLength = uiData;


		CTreeNode * pTreeNodeCurrentLoop = NULL;
		pTreeNodeCurrentLoop =  new CTreeNode(pTSPacketStore, L"", uiOffsetCurrentLoop, ( 4 )*8, VALUE_ZERO, NODE_LOOP_ITEM );
		pTreeNodeCurrentLoop->m_strText.Format(L"language_code: %c%c%c   ",  
				pucData[0], pucData[1], pucData[2]
				);

		//Move the pointer.
		pucData += 4;
		uiDescriptorPayloadLength -= 4;

		//Append the current loop node.
		pTreeList->AppendLastChild(pTreeNodeCurrentLoop, pTreeNodeLoops);
		pTreeList->AppendLastChild(pTreeNodeLanguageCode, pTreeNodeCurrentLoop);
		pTreeList->AppendLastChild(pTreeNodeAudioType, pTreeNodeCurrentLoop);

	}//while( uiItemLength >= 4)

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseSystemClockDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 2 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 1 Bit external_clock_reference_indicator.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"external_clock_reference_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 1 Bit reserved.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 6 Bit clock_accuracy_integer.
	uiFieldLength = 6;
	uiData = ((pucData[0] ) & 0x3F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"clock_accuracy_integer", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 3 Bit clock_accuracy_exponent.
	uiFieldLength = 3;
	uiData = ((pucData[1] >> 5) & 0x7);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"clock_accuracy_exponent", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 5 Bit reserved.
	uiFieldLength = 5;
	uiData = ((pucData[1]) & 0x1F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 2;
	uiDescriptorPayloadLength -= 2;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}


	return SUCCESS;
}



EResult CDescriptor::ParseMultiplexBufferUtilizationDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 1 Bit bound_valid_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"bound_valid_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit LTW_offset_lower_bound.
	uiFieldLength = 15;
	uiData = ((((pucData[0]) & 0x7F) << 8) | ( pucData[1]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"LTW_offset_lower_bound", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit reserved.
	uiFieldLength = 1;
	uiData = ((pucData[2] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 15 Bit LTW_offset_upper_bound.
	uiFieldLength = 15;
	uiData = ((((pucData[2]) & 0x7F) << 8) | ( pucData[3]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"LTW_offset_upper_bound", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseCopyrightDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 32 Bit copyright_identifier.
	uiFieldLength = 32;
	uiData = ((pucData[0] << 24 ) | ( pucData[1] << 16) | (pucData[2] << 8) | (pucData[3]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"copyright_identifier", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;

	if( 0 != uiDescriptorPayloadLength )
	{
		//additional_copyright_info
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"additional_copyright_info", uiOffset, uiFieldLength, VALUE_ZERO, NODE_DATA_BYTE);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
	}


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseMaximumBitrateDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 

	if( 3 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 2 Bit reserved.
	uiFieldLength = 2;
	uiData = ((pucData[0] >> 6) & 0x3);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 22 Bit maximum_bitrate.
	uiFieldLength = 22;
	uiData = (((pucData[0] & 0x3F) << 16) | ( pucData[1] << 8) | ( pucData[2]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"maximum_bitrate", uiOffset, uiFieldLength, uiData, NODE_SPECIAL);
	pTreeNode->m_strText.Format(L"maximum_bitrate[%d]: 0x%08X 50Bytes/second", uiFieldLength, uiData);
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	pucData += 3;
	uiDescriptorPayloadLength -= 3;


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParsePrivateDataIndicatorDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;
	pucData += 2;
 

	if( 4 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}

	// 32 Bit private_data_indicator.
	uiFieldLength = 32;
	uiData = ((pucData[0] << 24 ) | ( pucData[1] << 16) | (pucData[2] << 8) | (pucData[3]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"private_data_indicator", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 4;
	uiDescriptorPayloadLength -= 4;


	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}


EResult CDescriptor::ParseSmoothingBufferDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorLength = uiData;

	pucData += 2;

  
	if( 6 <= uiDescriptorLength )
	{
		// 2 Bit reserved.
		uiFieldLength = 2;
		uiData = ( (pucData[0] >> 6) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 22 Bit sb_leak_rate.
		uiFieldLength = 22;
		uiData = ((( pucData[0] & 0x3F) << 16) | (pucData[1] << 8) | (pucData[2]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"sb_leak_rate", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"sb_leak_rate[%d]: 0x%08X 400b/s", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 2 Bit reserved.
		uiFieldLength = 2;
		uiData = ( (pucData[3] >> 6) & 0x3);
		pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		// 22 Bit sb_size.
		uiFieldLength = 22;
		uiData = ((( pucData[3] & 0x3F) << 16) | (pucData[4] << 8) | (pucData[5]));
		pTreeNode  = new CTreeNode(pTSPacketStore, L"sb_size", uiOffset, uiFieldLength, uiData, NODE_SPECIAL );
		pTreeNode->m_strText.Format(L"sb_size[%d]: 0x%08X bytes", uiFieldLength, uiData);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		//Move the pointer.
		pucData += 6;
		uiDescriptorLength -= 6;

	}

	if( 0 != uiDescriptorLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorLength*8;
		pucData += uiDescriptorLength;
		uiDescriptorLength = 0;
		
	}


	return SUCCESS;
}


EResult CDescriptor::ParseSTDDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 1 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 7 Bit reserved.
	uiFieldLength = 7;
	uiData = ((pucData[0] >> 1) & 0x7F);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"reserved", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 1 Bit leak_valid_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] ) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"leak_valid_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 1;
	uiDescriptorPayloadLength -= 1;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}


	return SUCCESS;
}


EResult CDescriptor::ParseIBPDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset)
{
	CTreeNode * pTreeNode = NULL;
	CTreeNode * pTreeNodeTmp = NULL;
	UINT32 uiData;
	UINT32 uiFieldLength;
	UCHAR8 ucDescriptorTag;

	UINT32 uiDescriptorPayloadLength;

	ucDescriptorTag = pucData[0];

	// 8 Bit descriptor_tag.
	uiFieldLength = 8;
	uiData = pucData[0];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_tag", uiOffset, uiFieldLength, uiData );
	pTreeList->AppendLastChild( pTreeNode, pTreeNodeInput);	
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 8 Bit descriptor_length.
	uiFieldLength = 8;
	uiData = pucData[1];
	pTreeNode  = new CTreeNode(pTSPacketStore, L"descriptor_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	//Save the descriptor length.
	uiDescriptorPayloadLength = uiData;

	pucData += 2;
 

	if( 2 > uiDescriptorPayloadLength)
	{
		//Invalid End.
		uiFieldLength = uiDescriptorPayloadLength*8;
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Invalid end", uiOffset, uiFieldLength, VALUE_ZERO, NODE_IGNORED);
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiFieldLength;

		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;

		return FAILURE;
	}


	// 1 Bit closed_gop_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 7) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"closed_gop_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;


	// 1 Bit identical_gop_flag.
	uiFieldLength = 1;
	uiData = ((pucData[0] >> 6) & 0x1);
	pTreeNode  = new CTreeNode(pTSPacketStore, L"identical_gop_flag", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	// 14 Bit max_gop_length.
	uiFieldLength = 14;
	uiData = ((((pucData[0] ) & 0x3F) << 8 ) | (pucData[1]));
	pTreeNode  = new CTreeNode(pTSPacketStore, L"max_gop_length", uiOffset, uiFieldLength, uiData );
	pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
	pTreeNodeTmp = pTreeNode;
	uiOffset += uiFieldLength;

	pucData += 2;
	uiDescriptorPayloadLength -= 2;

	if( 0 != uiDescriptorPayloadLength)
	{
		pTreeNode  = new CTreeNode(pTSPacketStore, L"Data bytes ignored", uiOffset, uiDescriptorPayloadLength*8, VALUE_ZERO, NODE_IGNORED );
		pTreeList->InsertAfter( pTreeNode, pTreeNodeTmp);
		pTreeNodeTmp = pTreeNode;
		uiOffset += uiDescriptorPayloadLength*8;
		pucData += uiDescriptorPayloadLength;
		uiDescriptorPayloadLength = 0;
		
	}

	return SUCCESS;
}
