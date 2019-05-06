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
AC-3     Dolby AC-3 audio coding (ITU-R  BS 1196 )    杜比AC-3音频编码
BAT      Bouquet Association Table                      业务群关联表
BCD      Binary Coded Decimal                         二进制编码十进制数
bslbf    bit string, left bit first                   比特串，左位在先
CA       Conditional Access                            条件接收
CAT      Conditional Access Table                       条件接收表
CRC      Cyclic Redundancy Check                      循环冗余校验
CLUT     Colour Look-Up Table                         彩色查找表
DAB      Digital Audio Broadcasting                     数字音频广播
DIT      Discontinuity Information Table DVB             间断信息表
DVD      Digital Versatile Disc                          数字激光视盘
EBU      European Broadcasting Union                    欧洲广播联盟
EIT      Event Information Table                        事件信息表
EMM      Entitlement Management Message                授权管理信息
EPG      Electronic Program Guide                       电子节目指南
ETS      European Telecommunication Standard            欧洲电信标准
ETSI     European Telecommunication Standard Institute     欧洲电信标准委员会
FEC      Forward Error Correction                       前向纠错
IEC      International Electronical Commission             国际电工委员会
IRD      Integrated Receiver Decoder                     综合接收解码器
ISO      International Organization for Standardization       国际标准化组织
JTC      Joint Technical Committee                       联合技术委员会
LSB      Least Significated Bit                           最低有效位
MJD      Modified Julian Date                           修正的儒略日期
MPEG     Moving Pictures Expert Group                   运动图象专家组
NIT      Nerwork Information Table                      网络信息表
NVOD     Near Video On Demand                        准视频点播
PAT      Program Association Table                     节目关联表
PID      Packet  Identifier                             包标识符
PMT      Program Map Table                            节目映射表
PSI      Program Specific Information                   节目特定信息
PSTN     Public Switched Telephone Network              公共交换电话网
QAM      Quadrature Amplitude Modulation                正交调幅
QPSK     Quaternary Phase Shift Keying                   四相相移键控
rpchof   remainder polynomial coefficients,highest order first  余数多项式系数，高项在先
RS       Reed-Solomon                               里德-所罗门          
RST      Running Status Table                          运行状态表
ScF      Scale Factor                                  比例因子
SDT      Service Description Table                      业务描述表
SI       Service Information                           业务信息
SIT      Selection Information Table                    选择信息表
SMI      Storage Media Interoperability                   存储媒体互操作性
ST       Stuffing Table                                填充表
TDT      Time and Date Table                          时间和日期表
TOT      Time Offset Table                            时间偏移表
TSDT     Transport Stream Description Table              传输流描述表
TS       Transport Stream                            传输流
UTC      Universal Time, Co-ordinated                   坐标化的通用时间
VBI      Vertical Blanking Interval                       场逆程
VPS      Video Programme System                      视频节目系统
WSS      Wide Screen Signallling                        宽屏幕信令

#endif