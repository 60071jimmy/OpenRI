/*
Copyright 2016 Open Robot Club

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __RI_SOCKET_H__
#define __RI_SOCKET_H__

#include "openri.h"

#if defined(RI_WINDOWS)
  #include <stdio.h>
  #include <string.h>
  //#include <unistd.h>
  #include <conio.h>
  #include <process.h>
  //#include <winsock.h>
//  #include <Ws2def.h>
//  #include <Wsk.h>
  //#include <winsock2.h>
  #include <stdlib.h>
  #include <string.h>
  #include <iphlpapi.h>
#else
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <sys/socket.h>
  #include <sys/ioctl.h>
  #include <netinet/in.h>
  #include <net/if.h>
  #include <net/if_arp.h>
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <netinet/in.h>
  #include <netdb.h>
  #include <fcntl.h>
  #include <errno.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 單一socket最大連線數
 */
#define RI_SOCKET_SOMAXCONN          SOMAXCONN
/**
 * 標明此socket發出的協議，不需要查路由表
 */
#define RI_SOCKET_MSG_DONTROUTE      MSG_DONTROUTE
/**
 * 標明此socket發出的協議，包含帶外數據(指該數據不會被計算在頻寬的帶寬占用)
 */
#define RI_SOCKET_MSG_OOB            MSG_OOB

/**
 * recv數據時使用，將data預讀出來
 */
#define RI_SOCKET_MSG_PEEK           MSG_PEEK

#define RI_SOCKET_MSG_WAITALL        MSG_WAITALL

#define RI_SOCKET_MSG_DONTWAIT       MSG_DONTWAIT
#define RI_SOCKET_MSG_MSG_ERRQUEUE   MSG_ERRQUEUE
#define RI_SOCKET_MSG_MSG_TRUNC      MSG_TRUNC
#define RI_SOCKET_MSG_MSG_EOR        MSG_EOR
#define RI_SOCKET_MSG_MSG_CTRUNC     MSG_CTRUNC

#define RI_SOCKET_MSG_PEEK           MSG_PEEK

/**
 * @brief 初始化此Library
 * @return 成功回傳1，否則回傳錯誤碼
 */
int riSocket_InitLib();


#define RI_SOCKET_PF_UNSPEC      RI_SOCKET_AF_UNSPEC
#define RI_SOCKET_PF_INET        RI_SOCKET_AF_INET
#define RI_SOCKET_PF_IPX         RI_SOCKET_AF_IPX
#define RI_SOCKET_PF_APPLETALK   RI_SOCKET_AF_APPLETALK
#define RI_SOCKET_PF_INET6       RI_SOCKET_AF_INET6
#define RI_SOCKET_PF_IRDA        RI_SOCKET_AF_IRDA

#if defined(RI_WINDOWS)
#define RI_SOCKET_PF_NETBIOS     RI_SOCKET_AF_NETBIOS
#define RI_SOCKET_PF_BTH         RI_SOCKET_AF_BTH
#endif

#define RI_SOCKET_PF_COUNT       RI_SOCKET_AF_COUNT
#define RI_SOCKET_PF_t           RI_SOCKET_AF_t   // Protolcol family. (Must be the same as address family.)


typedef enum {
  RI_SOCKET_SOCK_STREAM    = 0x0,  // A socket type that provides sequenced, reliable, two-way, connection-based byte streams with an OOB data transmission mechanism. This socket type uses the Transmission Control Protocol (TCP) for the Internet address family (AF_INET or AF_INET6).
  RI_SOCKET_SOCK_DGRAM     = 0x1,  // A socket type that supports datagrams, which are connectionless, unreliable buffers of a fixed (typically small) maximum length. This socket type uses the User Datagram Protocol (UDP) for the Internet address family (AF_INET or AF_INET6).
  RI_SOCKET_SOCK_RAW,              // A socket type that provides a raw socket that allows an application to manipulate the next upper-layer protocol header. To manipulate the IPv4 header, the IP_HDRINCL socket option must be set on the socket. To manipulate the IPv6 header, the IPV6_HDRINCL socket option must be set on the socket.
  RI_SOCKET_SOCK_RDM,              // A socket type that provides a reliable message datagram. An example of this type is the Pragmatic General Multicast (PGM) multicast protocol implementation in Windows, often referred to as reliable multicast programming. This type is only supported if the Reliable Multicast Protocol is installed.

#if defined(RI_WINDOWS)
  RI_SOCKET_SOCK_SEQPACKET,        // A socket type that provides a pseudo-stream packet based on datagrams.
#endif

  RI_SOCKET_SOCK_COUNT
} RI_SOCKET_TYPE_t;


typedef enum {
  RI_SOCKET_IPPROTO_TCP        = 0x0,  // The Transmission Control Protocol (TCP). This is a possible value when the af parameter is AF_INET or AF_INET6 and the type parameter is SOCK_STREAM.
  RI_SOCKET_IPPROTO_UDP        = 0x1,  // The User Datagram Protocol (UDP). This is a possible value when the af parameter is AF_INET or AF_INET6 and the type parameter is SOCK_DGRAM.

#if defined(RI_WINDOWS)
  RI_SOCKET_BTHPROTO_RFCOMM,           // The Bluetooth Radio Frequency Communications (Bluetooth RFCOMM) protocol. This is a possible value when the af parameter is AF_BTH and the type parameter is SOCK_STREAM. This protocol is supported on Windows XP with SP2 or later.
  RI_SOCKET_IPPROTO_RM,                // The PGM protocol for reliable multicast. This is a possible value when the af parameter is AF_INET and the type parameter is SOCK_RDM. On the Windows SDK released for Windows Vista and later, this value is also called IPPROTO_PGM. This protocol is only supported if the Reliable Multicast Protocol is installed.
#endif

  RI_SOCKET_IPPROTO_COUNT
} RI_SOCKET_PROTOCOL_t;



#ifndef RiSocket_t_init
#define RiSocket_t_init

typedef enum {
    RI_SOCKET_AF_INET       = 0x0,  // The Internet Protocol version 4 (IPv4) address family.
    RI_SOCKET_AF_INET6      = 0x1,  // The Internet Protocol version 6 (IPv6) address family.
    RI_SOCKET_AF_UNSPEC     = 0x2,  // The address family is unspecified.
    RI_SOCKET_AF_IPX,               // The IPX/SPX address family. This address family is only supported if the NWLink IPX/SPX NetBIOS Compatible Transport protocol is installed. This address family is not supported on Windows Vista and later.
    RI_SOCKET_AF_APPLETALK,         // The AppleTalk address family. This address family is only supported if the AppleTalk protocol is installed. This address family is not supported on Windows Vista and later.
    RI_SOCKET_AF_IRDA,              // The Infrared Data Association (IrDA) address family. This address family is only supported if the computer has an infrared port and driver installed.

#if defined(RI_WINDOWS)
    RI_SOCKET_AF_NETBIOS,           // The NetBIOS address family. This address family is only supported if a Windows Sockets provider for NetBIOS is installed.
    RI_SOCKET_AF_BTH,               // The Bluetooth address family. This address family is supported on Windows XP with SP2 or later if the computer has a Bluetooth adapter and driver installed.
#endif

    RI_SOCKET_AF_COUNT
} RI_SOCKET_AF_t;                 // Address family.


typedef struct {
#if defined(RI_WINDOWS)
    SOCKET     sock;
#else
    int        sock;
#endif

    int backLog;
    RI_SOCKET_AF_t af;
    struct sockaddr_in addr_in; 
} RiSocket_t;
#endif

 RiSocket_t *RiSocket_New();

 int RiSocket_Open(RiSocket_t *sock, RI_SOCKET_AF_t af, RI_SOCKET_TYPE_t type, RI_SOCKET_PROTOCOL_t protocol);
 int RiSocket_Open_With_TimeOut(RiSocket_t *sock, RI_SOCKET_AF_t af, RI_SOCKET_TYPE_t type, RI_SOCKET_PROTOCOL_t protocol,int timeOutSec);

 int RiSocket_Free(RiSocket_t *sock);

 int RiSocket_Close(RiSocket_t *sock);

 RiSocket_t *RiSocket_Accept(RiSocket_t *sock);

 int RiSocket_Bind(RiSocket_t *sock);

 int RiSocket_Listen(RiSocket_t *sock, int backLog);

 int RiSocket_Recv(RiSocket_t *sock, ri_byte *buffer, int bufferSize, int flag);

 int RiSocket_RecvFrom(RiSocket_t *sock, ri_byte *buffer, int bufferSize, int flag);

 int RiSocket_Send(RiSocket_t *sock, const ri_byte *buffer, int bufferSize, int flag);

 int RiSocket_SendTo(RiSocket_t *sock, const ri_byte *buffer, int bufferSize, int flag);

 int RiSocket_SetAddressIn(RiSocket_t *sock, ri_utf8 *ipAddress, int port);

 int RiSocket_Connect(RiSocket_t *sock);

#ifdef __cplusplus
}
#endif

#endif /* __RI_SOCKET_H__ */
