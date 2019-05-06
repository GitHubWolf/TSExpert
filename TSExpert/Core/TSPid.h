#pragma once
#include "TSPublic.h"

const UINT16 PID_PAT  = 0x0000;
const UINT16 PID_CAT  = 0x0001;
const UINT16 PID_TSDT = 0x0002;
/*
**0x0003 to 0x000F = reserved.
*/
const UINT16 PID_NIT  = 0x0010;
//const UINT16 PID_ST   = 0x0010;

const UINT16 PID_BAT  = 0x0011;
const UINT16 PID_SDT  = 0x0011;
const UINT16 PID_BAT_SDT  = 0x0011;
//const UINT16 PID_ST   = 0x0011;


const UINT16 PID_EIT  = 0x0012;
//const UINT16 PID_ST   = 0x0012;

const UINT16 PID_RST  = 0x0013;
//const UINT16 PID_ST   = 0x0013;

const UINT16 PID_TDT  = 0x0014;
const UINT16 PID_TOT  = 0x0014;
const UINT16 PID_TDT_TOT  = 0x0014;
//const UINT16 PID_ST   = 0x0014;

const UINT16 PID_NST  = 0x0015;
const UINT16 PID_IST  = 0x001C;
const UINT16 PID_MT   = 0x001D;
/*
**0x0015 network synchronization
**0x0016 to 0x001B reserved
**0x001C inband signalling
**0x001D measurement
*/

const UINT16 PID_DIT  = 0x001E;
const UINT16 PID_SIT  = 0x001F;

const UINT16 PID_NULL  = 0x1FFF;

/*0xFFFF is out of range, but it can be used as a special value.*/
const UINT16 PID_INVALID  = 0xFFFF;

#if 0
AC-3     Dolby AC-3 audio coding (ITU-R  BS 1196 )    �ű�AC-3��Ƶ����
BAT      Bouquet Association Table                      ҵ��Ⱥ������
BCD      Binary Coded Decimal                         �����Ʊ���ʮ������
bslbf    bit string, left bit first                   ���ش�����λ����
CA       Conditional Access                            ��������
CAT      Conditional Access Table                       �������ձ�
CRC      Cyclic Redundancy Check                      ѭ������У��
CLUT     Colour Look-Up Table                         ��ɫ���ұ�
DAB      Digital Audio Broadcasting                     ������Ƶ�㲥
DIT      Discontinuity Information Table DVB             �����Ϣ��
DVD      Digital Versatile Disc                          ���ּ�������
EBU      European Broadcasting Union                    ŷ�޹㲥����
EIT      Event Information Table                        �¼���Ϣ��
EMM      Entitlement Management Message                ��Ȩ������Ϣ
EPG      Electronic Program Guide                       ���ӽ�Ŀָ��
ETS      European Telecommunication Standard            ŷ�޵��ű�׼
ETSI     European Telecommunication Standard Institute     ŷ�޵��ű�׼ίԱ��
FEC      Forward Error Correction                       ǰ�����
IEC      International Electronical Commission             ���ʵ繤ίԱ��
IRD      Integrated Receiver Decoder                     �ۺϽ��ս�����
ISO      International Organization for Standardization       ���ʱ�׼����֯
JTC      Joint Technical Committee                       ���ϼ���ίԱ��
LSB      Least Significated Bit                           �����Чλ
MJD      Modified Julian Date                           ��������������
MPEG     Moving Pictures Expert Group                   �˶�ͼ��ר����
NIT      Nerwork Information Table                      ������Ϣ��
NVOD     Near Video On Demand                        ׼��Ƶ�㲥
PAT      Program Association Table                     ��Ŀ������
PID      Packet  Identifier                             ����ʶ��
PMT      Program Map Table                            ��Ŀӳ���
PSI      Program Specific Information                   ��Ŀ�ض���Ϣ
PSTN     Public Switched Telephone Network              ���������绰��
QAM      Quadrature Amplitude Modulation                ��������
QPSK     Quaternary Phase Shift Keying                   �������Ƽ���
rpchof   remainder polynomial coefficients,highest order first  ��������ʽϵ������������
RS       Reed-Solomon                               ���-������          
RST      Running Status Table                          ����״̬��
ScF      Scale Factor                                  ��������
SDT      Service Description Table                      ҵ��������
SI       Service Information                           ҵ����Ϣ
SIT      Selection Information Table                    ѡ����Ϣ��
SMI      Storage Media Interoperability                   �洢ý�廥������
ST       Stuffing Table                                ����
TDT      Time and Date Table                          ʱ������ڱ�
TOT      Time Offset Table                            ʱ��ƫ�Ʊ�
TSDT     Transport Stream Description Table              ������������
TS       Transport Stream                            ������
UTC      Universal Time, Co-ordinated                   ���껯��ͨ��ʱ��
VBI      Vertical Blanking Interval                       �����
VPS      Video Programme System                      ��Ƶ��Ŀϵͳ
WSS      Wide Screen Signallling                        ����Ļ����

#endif