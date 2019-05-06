#pragma once
#include <Winsock2.h>
#include <WS2tcpip.h>
#include "TSPublic.h"

static const UINT32 IP_PACKET_MTU = 1500;

const static ULONG INVALID_IP_ADDRESS = 0xFFFFFFFF;

bool  CleanUpSocket(SOCKET &inputSocket);
/*Default value will be blocking.*/
bool  CreateUdpSocket(SOCKET &socketFd, ULONG ulNonblocking = 0, UINT16 uwPort = INADDR_ANY, ULONG ulMulticastAddress = INVALID_IP_ADDRESS);

bool IsMulticastAddress(ULONG ulMulticastAddress);

DWORD64 XGetTickCount(void);