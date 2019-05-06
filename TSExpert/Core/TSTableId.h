#pragma once

const UCHAR8 TABLEID_PAT = 0x00;
const UCHAR8 TABLEID_CAT = 0x01;
const UCHAR8 TABLEID_PMT = 0x02;
const UCHAR8 TABLEID_TSDT = 0x03;
/*
**0x04~0x3F Reserved.
*/

const UCHAR8 TABLEID_DSI = 0x3B; /*DownloadServerInitiate DSMCC Section*/
const UCHAR8 TABLEID_DII = 0x3B; /*DownloadInfoIndication DSMCC Section*/
const UCHAR8 TABLEID_DDB = 0x3C; /*DownloadDataBlock DSMCC Section*/


const UCHAR8 TABLEID_NIT_CURRENT = 0x40;
const UCHAR8 TABLEID_NIT_OTHER   = 0x41;
const UCHAR8 TABLEID_SDT_CURRENT = 0x42;
/*
**0x43~0x45 Reserved for future use.
*/
const UCHAR8 TABLEID_SDT_OTHER = 0x46;
/*
**0x47~0x49 Reserved for future use.
*/
const UCHAR8 TABLEID_BAT = 0x4A;
/*
**0x4B~0x4D Reserved for future use.
*/
const UCHAR8 TABLEID_EIT_PF_CURRENT = 0x4E;
const UCHAR8 TABLEID_EIT_PF_OTHER = 0x4F;

/*0x50~0x5F all for EIT CURRENT SCHEDULE table.*/
const UCHAR8 TABLEID_EIT_SCHEDULE_CURRENT = 0x50;

/*0x60~0x6F all for EIT OTHER SCHEDULE table.*/
const UCHAR8 TABLEID_EIT_SCHEDULE_OTHER = 0x60;

const UCHAR8 TABLEID_TDT = 0x70;
const UCHAR8 TABLEID_RST = 0x71;
const UCHAR8 TABLEID_ST = 0x72;
const UCHAR8 TABLEID_TOT = 0x73;
/*
**0x74~0x7D Reserved for future use.
*/
const UCHAR8 TABLEID_DIT = 0x7E;
const UCHAR8 TABLEID_SIT = 0x7F;
/*
**0x80~0xFE User defined.
*/

/*
**0xFF Reserved.
*/

#if 0
Value Description
0x00 program_association_section
0x01 conditional_access_section
0x02 program_map_section
0x03 transport_stream_description_section
0x04 to 0x3F reserved
0x40 network_information_section - actual_network
0x41 network_information_section - other_network
0x42 service_description_section - actual_transport_stream
0x43 to 0x45 reserved for future use
0x46 service_description_section - other_transport_stream
0x47 to 0x49 reserved for future use
0x4A bouquet_association_section
0x4B to 0x4D reserved for future use
0x4E event_information_section - actual_transport_stream, present/following
0x4F event_information_section - other_transport_stream, present/following
0x50 to 0x5F event_information_section - actual_transport_stream, schedule
0x60 to 0x6F event_information_section - other_transport_stream, schedule
0x70 time_date_section
0x71 running_status_section
0x72 stuffing_section
0x73 time_offset_section
0x74 to 0x7D reserved for future use
0x7E discontinuity_information_section
0x7F selection_information_section
0x80 to 0xFE user defined
0xFF reserved
#endif