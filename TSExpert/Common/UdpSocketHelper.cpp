#include "StdAfx.h"

#include "UdpSocketHelper.h"


/*Release socket resouces.*/
bool  CleanUpSocket(SOCKET &inputSocket)
{
	if( INVALID_SOCKET == inputSocket )
		return true;

	closesocket(inputSocket);
	inputSocket = INVALID_SOCKET;

	return true;
}

/*
*Create a udp socket to receive or send pakcets.
*NOTE:All input port and address must be in network order.
*/
bool  CreateUdpSocket(SOCKET &socketFd, ULONG ulNonblocking, UINT16 uwPort, ULONG ulMulticastAddress)
{
	/*Create a socket to recast RTP packets, it will join multicast group.*/
	int iResult;

	socketFd = socket(AF_INET, SOCK_DGRAM, 0);

	if( INVALID_SOCKET == socketFd)
	{
		return false;
	}


	const int iOn = 1;
	iResult = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&iOn, sizeof(iOn));
	if( SOCKET_ERROR == iResult )
	{
		CleanUpSocket(socketFd);
		return false;
	}


	const int iRouteNum = 10;
	iResult = setsockopt(socketFd,IPPROTO_IP,IP_MULTICAST_TTL,(char*)&iRouteNum,sizeof(iRouteNum));
	if( SOCKET_ERROR == iResult )
	{
		CleanUpSocket(socketFd);
		return false;
	}


	const int iLoopback = 1;
	iResult = setsockopt(socketFd,IPPROTO_IP,IP_MULTICAST_LOOP,(char*)&iLoopback,sizeof(iLoopback));

	if( SOCKET_ERROR == iResult )
	{
		CleanUpSocket(socketFd);
		return false;
	}

	/*Set to blocking flag according to the input parameter.*/
	ioctlsocket(socketFd,FIONBIO,&ulNonblocking);


	/*If it is necessary to bind to a port.*/
	if( INADDR_ANY != uwPort )
	{
		/*Bind to a certain port.*/
		sockaddr_in socketAddrControl;
		memset(&socketAddrControl, 0, sizeof(socketAddrControl));
		socketAddrControl.sin_family = AF_INET;
		/*The input parameter has been in network order.*/
		socketAddrControl.sin_port = uwPort;
		socketAddrControl.sin_addr.S_un.S_addr = INADDR_ANY;

		iResult = bind(socketFd, (sockaddr*)(&socketAddrControl), sizeof(socketAddrControl));
		if( SOCKET_ERROR == iResult )
		{
			CleanUpSocket(socketFd);
			return false;
		}
	}


	/*If this socket will join a mulicast group.*/
	if( INVALID_IP_ADDRESS != ulMulticastAddress )
	{
		if( IsMulticastAddress( ulMulticastAddress ) )
		{
			/*Here we just support IPv4.*/
			/*Join multicast group.*/	
			ip_mreq multicastRequest;
			memset(&multicastRequest, 0, sizeof(multicastRequest));
			multicastRequest.imr_interface.S_un.S_addr = INADDR_ANY;
			multicastRequest.imr_multiaddr.S_un.S_addr = ulMulticastAddress ;

			//Join a multicast group.
			iResult = setsockopt(socketFd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&multicastRequest,sizeof(multicastRequest));
			if( SOCKET_ERROR == iResult )
			{
				int iResult = WSAGetLastError();
				TRACE("CreateUdpSocket WSAGetLastError : iResult%d, multicastRequest.imr_multiaddr.S_un.S_addr  0x%08x  \r\n", iResult, multicastRequest.imr_multiaddr.S_un.S_addr );
			
				CleanUpSocket(socketFd);
				return false;
			}
		}

	}

	return true;

}

/*NOTE: Input multicast address MUST be in network order.TO verify the return result !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
bool IsMulticastAddress(ULONG ulMulticastAddress)
{
	ULONG ulMulticastAddressHost = ntohl(ulMulticastAddress);

	/*Get the first byte of address. TO verify the return result !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	UCHAR8 ucFirstByte = (UCHAR8)(ulMulticastAddressHost >> 24);
	
	if(( ucFirstByte >= 224 ) && ( ucFirstByte < 240 ))
	{
		return true;
	}

	return false;
}


