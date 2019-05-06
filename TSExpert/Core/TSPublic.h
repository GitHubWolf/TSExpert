#pragma once
#include <map>
using namespace std;


typedef signed   int       SINT32;
typedef unsigned int       UINT32;
typedef signed   short int SINT16;
typedef unsigned short int UINT16;
typedef unsigned char      UCHAR8;
typedef signed   char      SCHAR8;

//Synchronize byte.
const SCHAR8 TS_SYN_BYTE = 0x47;



//unsigned long is 32 bits long at 32bits CPU, but it is 64 bits long at 64bits long.
//long is 32 bits long at 32bits CPU, but it is 64 bits long at 64bits long.
typedef unsigned long      ULONG;
typedef signed   long      SLONG;


/*Public type to save the information of Pid and their counter.*/
typedef pair<UINT16, UINT32>  PidCounterPair;
typedef map<UINT16, UINT32>   MapPidCounter;
typedef MapPidCounter::iterator    IteratorPidCounter;


static const UINT32 MIN_SECTION_HEADER_LENGTH = 8;
static const UINT32 MIN_PES_PACKET_HEADER_LENGTH = 6;
static const UINT32 LAST_COMPARE_LENGTH = 8;

static const UINT32 VALUE_ZERO = 0;

//INVALID 32bit value.
static const UINT32 VALUE_MAX = 0xFFFFFFFF;

//Default size to hold PES packet.0 byte.
static const UINT32 DEFAULT_PES_PACKET_SIZE = 0;

//Default size to hold section.4K byte.
static const UINT32 DEFAULT_SECTION_SIZE = 0;

static const UINT32 MAX_FILTER_LENGTH = 12;

static const UINT32 MIN_PES_HEADER_LENGTH = 6;

enum EPacketLength
{
	TS_PACKET_LENGTH_UNKNOWN = -1,
	TS_PACKET_LENGTH_188 = 188,
	TS_PACKET_LENGTH_204 = 204

};

enum EResult
{
	FAILURE = -1,
	SUCCESS = 1,
};

enum EDataType
{
	DATA_TYPE_PESPACKET = 1,
	DATA_TYPE_SECTION   = 2
};

enum EWorkingMode
{
	MODE_LIMITED_LENGTH = 1,
	MODE_APPEND_LENGTH   = 2
};



enum ESearchType
{
	SEARCH_TYPE_TS_PACKET = 1,
    SEARCH_TYPE_DVB_SECTION,
    SEARCH_TYPE_SSU_SECTION,
	SEARCH_TYPE_PES_PACKET
};

enum ERunningStatus
{
	RUNNING_STATUS_READY = 1,
	RUNNING_STATUS_RUNNING,
	RUNNING_STATUS_QUIT
};


enum EPidType
{
	PID_TYPE_PAT = 1,
	PID_TYPE_CAT,
	PID_TYPE_TSDT,
	PID_TYPE_NIT,
	PID_TYPE_BAT_SDT,
	PID_TYPE_EIT,
	PID_TYPE_RST,
	PID_TYPE_TDT_TOT,
	PID_TYPE_NST,
	PID_TYPE_IST,
	PID_TYPE_MT,
	PID_TYPE_DIT,
	PID_TYPE_SIT,
	PID_TYPE_NULL,
	PID_TYPE_PMT,
	PID_TYPE_ECM,
	PID_TYPE_EMM,
	PID_TYPE_H2220_13818_1_ANNEX_A_DSM_CC,		//"H.222.0 or 13818_1 Annex A DSM CC",
	PID_TYPE_H2220_13818_1_PRIVATE_SECTION,		//"H.222.0 or 13818_1 private_sections",
	PID_TYPE_PCR,
	PID_TYPE_11172_VIDEO,						//"11172 Video",
	PID_TYPE_H262_13818_2_11172_2_VIDEO,			//"H.262 or 13818_2 or 11172_2 Video",
	PID_TYPE_11172_AUDIO,						//"11172 Audio",
	PID_TYPE_13818_3_AUDIO,						//"13818_3 Audio",
	PID_TYPE_H2220_13818_1_PRIVATE_PES_PACKET,	//"H.222.0 or 13818_1 private PES packets",
	PID_TYPE_13522_MHEG,							//"13522 MHEG",
	PID_TYPE_H2221,								//"H.222.1",
	PID_TYPE_13818_6_TYPE_A,						//"13818_6 type A",
	PID_TYPE_13818_6_TYPE_B,						//"13818_6 type B",
	PID_TYPE_13818_6_TYPE_C,						//"13818_6 type C",
	PID_TYPE_13818_6_TYPE_D,						//"13818_6 type D",
	PID_TYPE_13818_1_AUXILIARY,					//"13818_1 auxiliary",
	PID_TYPE_13818_7_AUDIO_WITH_ADTS_TRANSPORT_SYNTAX,
	PID_TYPE_14496_2_VISUAL,
	PID_TYPE_14496_3_AUDIO_WITH_LATM_TRANSPORT_SYNTAX,
	PID_TYPE_14496_1_SL_PACKETIZED_STREAM_OR_FLEXMUX_STREAM_CARRIED_IN_PES_PACKETS,
	PID_TYPE_14496_1_SL_PACKETIZED_STREAM_OR_FLEXMUX_STREAM_CARRIED_IN_14496_SECTIONS,
	PID_TYPE_13818_6_DSM_CC_SYNCHRONIZED_DOWNLOAD_PROTOCOL,
	PID_TYPE_METADATA_CARRIED_IN_PES_PACKETS_USING_THE_METADATA_ACCESS_UNIT_WRAPPER,
	PID_TYPE_METADATA_CARRIED_IN_METADATA_SECTIONS,
	PID_TYPE_METADATA_CARRIED_IN_13818_6__DATA_CAROUSEL,
	PID_TYPE_METADATA_CARRIED_IN_13818_6__OBJECT_CAROUSEL,
	PID_TYPE_METADATA_CARRIED_IN_13818_6_SYNCHRONIZED_DOWNLOAD_PROTOCOL_USING_THE_METADATA_ACCESS_UNIT_WRAPPER,
	PID_TYPE_AVC_VIDEO_STREAM_H264_OR_14496_10_VIDEO,
	PID_TYPE_H2220_OR_13818_1_RESERVED,
    PID_TYPE_IPMP_STREAM,
    PID_TYPE_DOLBY_AC3_AUDIO,
    PID_TYPE_DTS_AUDIO,
    PID_TYPE_DOLBY_DITIGAL_PLUS_AUTIO_ATSC,

	PID_TYPE_RESERVED
};

static const char TABLE_NAME_PAT[]  =	"PAT";
static const char TABLE_NAME_PMT[]  =	"PMT";
static const char TABLE_NAME_CAT[]  =	"CAT";
static const char TABLE_NAME_NIT[]  =	"NIT";
static const char TABLE_NAME_TSDT[] =	"TSDT";
static const char TABLE_NAME_SDT[]  =	"SDT";
static const char TABLE_NAME_BAT[]  =	"BAT";
static const char TABLE_NAME_EIT[]  =	"EIT";
static const char TABLE_NAME_TDT[]  =	"TDT";
static const char TABLE_NAME_RST[]  =	"RST";
static const char TABLE_NAME_TOT[]  =	"TOT";
static const char TABLE_NAME_DIT[]  =	"DIT";
static const char TABLE_NAME_SIT[]  =	"SIT";
static const char TABLE_NAME_SSU[]  =	"SSU";
static const char TABLE_NAME_PRIVATE[]  =	"Private";
static const char PACKET_NAME_PES[]  =	"PES";


enum EMessageType
{
	MESSAGE_PARSING_PROGRESS = 0,	/*Used in parser and searcher.*/
	MESSAGE_NEW_STANDARD_SECTION,	/*Used in parser.*/
	MESSAGE_PID_COUNTER_RESULT,		/*Used in parser.*/
	MESSAGE_PARSER_COMPLETED,		/*Used in parser.*/
	MESSAGE_SEARCHER_INFO,			/*Used in searcher.*/
	MESSAGE_NEW_SEARCHED_SECTION,	/*Used in searcher.*/
	MESSAGE_NEW_SEARCHED_TS_PACKET,	/*Used in searcher.*/
	MESSAGE_NEW_SEARCHED_PES_PACKET,	/*Used in searcher.*/
	MESSAGE_SEARCHER_COMPLETED,		/*Used in searcher.*/
	MESSAGE_NEW_IP_PACKET,			/*Used in CIp2FileDialog to notify that a packet has arrived.*/
	MESSAGE_UNKNOWN_LAST
};

/*Message type and format*/
/*--------------MESSAGE_PARSING_PROGRESS--------------------*/
typedef struct _TMsgProgress
{
	UINT32 uiPercent;
}TMsgProgress;



/*--------------MESSAGE_NEW_STANDARD_SECTION--------------------*/
class CSectionObserver;
class CTSPacketStore;
typedef struct _TMsgNewSection
{
	CSectionObserver *pSectionObserver;
	CTSPacketStore  *pTSPacketStore;
}TMsgNewSection;

/*--------------MESSAGE_PID_COUNTER_RESULT--------------------*/
class CTSPidCounter;
typedef struct _TMsgCounterResult
{
	MapPidCounter *pMapPidCounter;
	CTSPidCounter *pTSPidCounter;
}TMsgCounterResult;

/*--------------MESSAGE_PARSER_COMPLETED--------------------*/
#if 0
typedef struct _TMsgParserCompleted
{
}TMsgParserCompleted;
#endif

/*--------------MESSAGE_SEARCHER_INFO--------------------*/
typedef struct _TMsgSearcherInfo
{
	UINT32 uiPid;
	UINT32 uiSearchCount;
	ESearchType eSearchType;
	UINT32 uiId;
}TMsgSearcherInfo;

/*--------------MESSAGE_SEARCHER_COMPLETED--------------------*/
class CTSParser;
typedef struct _TMsgSearcherCompleted
{
	CTSParser *pTSParser;
}TMsgSearcherCompleted;


/*--------------MESSAGE_NEW_SEARCHED_SECTION--------------------*/
#if 0
class CSectionObserver;
class CTSPacketStore;
typedef struct _TMsgNewSection
{
	CSectionObserver *pSectionObserver;
	CTSPacketStore  *pTSPacketStore;
}TMsgNewSection;
#endif

/*--------------MESSAGE_NEW_SEARCHED_TS_PACKET--------------------*/
class CTSPacketObserver;
typedef struct _TMsgNewSearchedTSPacket
{
	CTSPacketObserver *pTSPacketObserver;
	CTSPacketStore  *pTSPacketStore;
}TMsgNewSearchedTSPacket;

/*--------------MESSAGE_NEW_SEARCHED_PES_PACKET--------------------*/
class CPESPacketObserver;
typedef struct _TMsgNewSearchedPESPacket
{
	CPESPacketObserver *pPESPacketObserver;
	CTSPacketStore  *pTSPacketStore;
}TMsgNewSearchedPESPacket;


/*--------------MESSAGE_NEW_IP_PACKET--------------------*/
typedef struct _TMsgIPPacket
{
	UINT32 uiPacketLength;
	UINT32 uiMilliseconds; 
	UCHAR8 *pucPacket;
}TMsgIPPacket;

static const UINT32 MY_POLY = 0x04C11DB7;
static const UINT32 MY_FIX1 = 0x19800503;
static const UINT32 MY_FIX2 = 0x19841106;
static const UCHAR8 CSA_KEY[] = {0x2E, 0xDD, 0x31, 0x93, 0x37, 0xAF, 0x99, 0x65};
static const UINT32 USER_INFO_LENGTH = 32;


typedef struct _TRegistrationData
{
	UINT32 uiRandom1;
	UINT32 uiFixed1;
	SYSTEMTIME oLastDateTime;
	UINT32 uiRandom2;
	UINT32 uiRandom3;
	SYSTEMTIME oExpiredDateTime;
	UINT32 uiRandom4;
	UINT32 uiMaxTimes;
	UINT32 uiCurrentTimes;
	UINT32 uiRandom5;
	UINT32 uiFixed2;
	TCHAR aucUserInfo[USER_INFO_LENGTH + 1];
}TRegistrationData;
