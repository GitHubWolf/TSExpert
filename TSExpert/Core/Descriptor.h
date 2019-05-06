#pragma once
#include "TSPublic.h"
#include "TreeList.h"

class CDescriptor
{
public:
	static LPWSTR GetDescriptorName(UCHAR8 ucTag);
	static EResult LoopParse(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiLoopLength);
	static EResult Parse(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput, const UCHAR8 *pucData, UINT32 uiOffset);
	static LPWSTR GetStreamTypeName(UINT32 uiParameter);
	static LPWSTR GetServiceTypeName(UINT32 uiParameter);
	static LPWSTR GetEastWestFlagName(UINT32 uiParameter);
	static LPWSTR GetPolarizationName(UINT32 uiParameter);
	static LPWSTR GetModulationNameSatellite(UINT32 uiParameter);
	static LPWSTR GetModulationNameCable(UINT32 uiParameter);
	static LPWSTR GetFECInnerName(UINT32 uiParameter);
	static LPWSTR GetFECOuterName(UINT32 uiParameter);
	static LPWSTR GetDataServiceName(UINT32 uiParameter);
	static LPWSTR GetTeletexTypeName(UINT32 uiParameter);
	static LPWSTR GetLinkageTypeName(UINT32 uiParameter);
	static LPWSTR GetHandOverTypeName(UINT32 uiParameter);
	static LPWSTR GetOriginTypeName(UINT32 uiParameter);
	static LPWSTR GetStreamAndComponentTypeName(UINT32 uiParameterStreamContent, UINT32 uiParameterComponentType);
	static LPWSTR GetLogicalCellPresentationInfoName(UINT32 uiParameter);
	static LPWSTR GetCellLinkageInfoName(UINT32 uiParameter);
	static LPWSTR GetCASystemName(UINT32 uiParameter);
    static LPWSTR GetExtendedDescriptorName(UINT32 uiParameter);
	static LPWSTR GetContentLevelName(UINT32 uiParameter1, UINT32 uiParameter2);
	static LPWSTR GetParentalRatingName(UINT32 uiParameter);
	static LPWSTR GetBandWidthName(UINT32 uiParameter);
	static LPWSTR GetConstellationName(UINT32 uiParameter);
	static LPWSTR GetHierarchyInformationName(UINT32 uiParameter);
	static LPWSTR GetCodeRateName(UINT32 uiParameter);
	static LPWSTR GetGuardIntervalName(UINT32 uiParameter);
	static LPWSTR GetTransmissionModeName(UINT32 uiParameter);
	static LPWSTR GetPrivateDataSpecifierName(UINT32 uiParameter);
	static LPWSTR GetSbSizeName(UINT32 uiParameter);
	static LPWSTR GetLeakRateName(UINT32 uiParameter);
	static LPWSTR GetCodingTypeName(UINT32 uiParameter);
	static LPWSTR GetDataBroadcastIdName(UINT32 uiParameter);
	static LPWSTR GetAncillaryDataIdentifierName(UINT32 uiParameter);
	static LPWSTR GetAnnouncementSupportIndicatorName(UINT32 uiParameter);
	static LPWSTR GetAnnouncementTypeName(UINT32 uiParameter);
	static LPWSTR GetaAdaptationFieldDataIdentifierName(UINT32 uiParameter);
	static LPWSTR GetRunningStatusName(UINT32 uiParameter);
	static LPWSTR GetHierarchyName(UINT32 uiParameter);
	static LPWSTR GetAlignmentTypeName(UINT32 uiParameter);
	static LPWSTR GetAudioTypeName(UINT32 uiParameter);
	static LPWSTR GetChromaFormatName(UINT32 uiParameter);

	static EPidType StreamTypeToPidType(UINT32 uiParameter);
	static LPWSTR GetPidTypeName(EPidType  ePidType);
	static EResult MjdToYmd(ULONG mjd, UINT32 &uiYear, UINT32 &uiMonth, UINT32 &uiDay);
private:
	static LPWSTR GetMPEGDescriptorName(UCHAR8 ucTag);
	static LPWSTR GetDVBDescriptorName(UCHAR8 ucTag);
	static EResult ParseMPEGDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseDVBDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCommonDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);

	/*DVB*/
	static EResult ParseNetworkNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseBouquetNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseStuffingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseServiceListDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseSatelliteDeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCableDeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseVBIDataDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseVBITeletextDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseServiceDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCountryAvailabilityDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseLinkageDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseNVODReferenceDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTimeShiftedServiceDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseShortEventDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseExtendedEventDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTimeShiftedEventDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseComponentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseMosaicDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseStreamIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCAIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseContentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseParentalRatingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTeletextDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTelephoneDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseLocalTimeOffsetDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseSubtitlingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTerrestrialDeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseMultilingualNetworkNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseMultilingualServiceNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseMultilingualBouquetNameDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseMultilingualComponentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParsePrivateDataSpecifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseServiceMoveDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseShortSmoothingBufferDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseFrequencyListDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParsePartialTransportStreamDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseDataBroadcastDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseDataBroadcastIdDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseScramblingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);	
	static EResult ParsePDCDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseAC3Descriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseAncillaryDataDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCellListDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCellFrequencyLinkDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseAnnouncementSupportDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseApplicationSignallingDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseAdaptationFieldDataDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseServiceIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseServiceAvailabilityDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTVAIdDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseContentIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTimeSliceFecIdentifierDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseECMRepetitionRateDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
    static EResult ParseExtensionDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);

    /*Extension_descriptor payload.*/
    static EResult ParseT2DeliverySystemDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset, UINT32 uiDescriptorPayloadLength);


	/*MPEG*/
	static EResult ParseVideoStreamDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseAudioStreamDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseHierarchyDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseRegistrationDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseDataStreamAlignmentDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseTargetBackgroundGridDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseVideoWindowDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCADescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseISO639LanguageDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseSystemClockDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseMultiplexBufferUtilizationDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseCopyrightDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseMaximumBitrateDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParsePrivateDataIndicatorDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseSmoothingBufferDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseSTDDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);
	static EResult ParseIBPDescriptor(CTSPacketStore * pTSPacketStore,CTreeList *pTreeList,  CTreeNode * pTreeNodeInput,const UCHAR8 *pucData, UINT32 uiOffset);

};
