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

#include "openri.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @file
    * @brief 用來控制Socket(網路連線端口)
    *
    * @author LEADERG
    */

    /**
    * 此Library是否已經初始化
    */
    static int riSocketIsInit = 0;
    /**
    * @brief 初始化此Library
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int riSocket_InitLib() {
#if defined(RI_WINDOWS)
        static WSADATA wsadata;
        WORD version;
        int ret;

        if (riSocketIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riSocketIsInit = 1;

        // Initialize WinSock2.2 DLL
        ri_memset(&wsadata, 0, sizeof(WSADATA));
        version = MAKEWORD(2,2);
        ret = WSAStartup(version, &wsadata);

        if(ret == SOCKET_ERROR)
        {
            RI_LOGE("WSAStartup == SOCKET_ERROR");
            return RI_ERROR;
        }
#else
        if (riSocketIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riSocketIsInit = 1;
#endif

        return RI_OK;
    }


    /**
    * @brief 一個轉換function，把RI_SOCKET_AF_t的值轉換成socket.h的address family種類(INET、IPX....等等)
    * @param af RI_SOCKET_AF_t類別
    * @return 對應的address family種類
    */
    int riSocket_GetAf(RI_SOCKET_AF_t af) {
        if (af == RI_SOCKET_AF_UNSPEC)
            return AF_UNSPEC;

        if (af == RI_SOCKET_AF_INET)
            return AF_INET;

        if (af == RI_SOCKET_AF_IPX)
            return AF_IPX;

        if (af == RI_SOCKET_AF_APPLETALK)
            return AF_APPLETALK;

        //  if(af == RI_SOCKET_AF_INET6)
        //    return AF_INET6;
        //  if(af == RI_SOCKET_AF_IRDA)
        //    return AF_IRDA;

#if defined(RI_WINDOWS)
        if(af == RI_SOCKET_AF_NETBIOS)
            return AF_NETBIOS;
        //  if(RI_SOCKET_AF_BTH)
        //    return AF_BTH;
#endif

        return AF_UNSPEC;
    }



    /**
    * @brief 一個轉換function，把RI_SOCKET_TYPE_t的值轉換成socket.h定義的socket種類(RDM、DGRAM、STREAM...等等)
    * @param type RI_SOCKET_TYPE_t類別
    * @return 對應的socket種類
    */
    int riSocket_GetType(RI_SOCKET_TYPE_t type) {
        if (type == RI_SOCKET_SOCK_STREAM)
            return SOCK_STREAM;

        if (type == RI_SOCKET_SOCK_DGRAM)
            return SOCK_DGRAM;

        if (type == RI_SOCKET_SOCK_RAW)
            return SOCK_RAW;

        if (type == RI_SOCKET_SOCK_RDM)
            return SOCK_RDM;

#if defined(RI_WINDOWS)
        if(type == RI_SOCKET_SOCK_SEQPACKET)
            return SOCK_SEQPACKET;
#endif

        return 0;
    }


    /**
    * @brief 一個轉換function，把RI_SOCKET_PROTOCOL_t的值轉換成socket.h定義的protocol種類(TCP、UDP...等等)
    * @param type RI_SOCKET_PROTOCOL_t類別
    * @return 對應的protocol種類
    */
    int riSocket_GetProtocol(RI_SOCKET_PROTOCOL_t protocol) {
        if (protocol == RI_SOCKET_IPPROTO_TCP)
            return IPPROTO_TCP;

        if (protocol == RI_SOCKET_IPPROTO_UDP)
            return IPPROTO_UDP;

#if defined(RI_WINDOWS)
        //  if(protocol == RI_SOCKET_BTHPROTO_RFCOMM)
        //    return BTHPROTO_RFCOMM;

        //  if(protocol == RI_SOCKET__IPPROTO_RM)
        //    return IPPROTO_RM;
#endif

        return 0;
    }

    /**
    * @brief 建立一個新的RiSocket_t
    * @return 成功則回傳建立好的RiSocket_t，否則回傳NULL
    */
    RiSocket_t *RiSocket_New() {
        RiSocket_t *sock;

        if (riSocketIsInit == 0)
            return NULL;

        sock = (RiSocket_t *) ri_calloc(1, sizeof(RiSocket_t));
        if (sock == NULL) {
            return NULL;
        }

        sock->sock = -1;

        return sock;
    }

    /**
    * @brief 使用目標RiSocket_t開啟一個網路接口
    * @param sock 目標RiSocket_t
    * @param af RI_SOCKET_AF_t定義的address family種類
    * @param type RI_SOCKET_TYPE_t定義的socket種類
    * @param protocol RI_SOCKET_PROTOCOL_t定義的protocol種類
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int RiSocket_Open(RiSocket_t *sock, RI_SOCKET_AF_t af,
        RI_SOCKET_TYPE_t type, RI_SOCKET_PROTOCOL_t protocol) {
            if (sock == NULL)
                return RI_ERROR_PARAMETER_0;
            if (af >= RI_SOCKET_AF_COUNT)
                return RI_ERROR_PARAMETER_1;
            if (type >= RI_SOCKET_SOCK_COUNT)
                return RI_ERROR_PARAMETER_2;
            if (protocol >= RI_SOCKET_IPPROTO_COUNT)
                return RI_ERROR_PARAMETER_3;
            if (sock->sock >= 0)
                return RI_OK_INIT_ALREADY;


            sock->sock = socket(riSocket_GetAf(af), riSocket_GetType(type),
                riSocket_GetProtocol(protocol));

            if (sock->sock == -1) {
                return RI_ERROR_INIT_ALREADY;
            }

            // 20140630: check the status of keep-alive
            char optval;
#if defined(RI_LINUX)
            socklen_t optlen = sizeof(optval);
            if (getsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
                perror("getsockopt()");
                close(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            optval = 1;
            optlen = sizeof(optval);
            if (setsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
                perror("setsockopt()");
                close(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            if (getsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
                perror("getsockopt()");
                close(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            int reuse = 1;
            if ((setsockopt(sock->sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
                < 0) {
                    RI_LOGI("setsockopt failed");
                    perror("setsockopt failed");
            }
#else (RI_WINDOWS)
            if (getsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, (int *)&optval) < 0) {
                perror("getsockopt()");
                closesocket(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            optval = 1;
            if (setsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, (int)optval) < 0) {
                perror("setsockopt()");
                closesocket(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            if (getsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, (int *)&optval) < 0) {
                perror("getsockopt()");
                closesocket(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            char reuse = 1;
            if ((setsockopt(sock->sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
                < 0) {
                    RI_LOGI("setsockopt failed");
                    perror("setsockopt failed");
                    closesocket(sock->sock);
                    exit(1);
            }
#endif

            // Set keep-alive active


#if defined(RI_CONFIG_IOS)

            int sing;
            socklen_t slen = sizeof(optval);
            if (setsockopt(sock->sock, SOL_SOCKET, SO_NOSIGPIPE, &sing, slen) == -1) {
                RI_LOGI("sing Set Err??");
            }
#endif
            return RI_OK;
    }
    /**
    * @brief 使用目標RiSocket_t嘗試開啟一個網路接口，此方法有設置TimeOut
    * @param sock 目標RiSocket_t
    * @param af RI_SOCKET_AF_t定義的address family種類
    * @param type RI_SOCKET_TYPE_t定義的socket種類
    * @param protocol RI_SOCKET_PROTOCOL_t定義的protocol種類
    * @param timeOutSec 設置幾秒為TimeOut
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int RiSocket_Open_With_TimeOut(RiSocket_t *sock, RI_SOCKET_AF_t af,
        RI_SOCKET_TYPE_t type, RI_SOCKET_PROTOCOL_t protocol, int timeOutSec) {

            if (sock == NULL)
                return RI_ERROR_PARAMETER_0;
            if (af >= RI_SOCKET_AF_COUNT)
                return RI_ERROR_PARAMETER_1;
            if (type >= RI_SOCKET_SOCK_COUNT)
                return RI_ERROR_PARAMETER_2;
            if (protocol >= RI_SOCKET_IPPROTO_COUNT)
                return RI_ERROR_PARAMETER_3;
            if (sock->sock >= 0)
                return RI_OK_INIT_ALREADY;
#if defined(RI_LINUX)
            sock->sock = socket(gtSocket_GetAf(af), riSocket_GetType(type),
                riSocket_GetProtocol(protocol));

            if (sock->sock == -1) {
                return RI_ERROR_INIT_ALREADY;
            }

            int optval;
            socklen_t optlen = sizeof(optval);
            if (getsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
                perror("getsockopt()");
                close(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            // Set keep-alive active
            optval = 1;
            optlen = sizeof(optval);
            if (setsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
                perror("setsockopt()");
                close(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            if (getsockopt(sock->sock, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
                perror("getsockopt()");
                close(sock->sock);
                exit(1);
            }
            RI_LOGI("SO_KEEPALIVE = %s", (optval ? "ON" : "OFF"));

            int reuse = 1;
            if ((setsockopt(sock->sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
                < 0) {
                    RI_LOGI("setsockopt failed");
                    perror("setsockopt failed");
            }

            struct timeval timeo;
            timeo.tv_sec = timeOutSec;
            timeo.tv_usec = 0;
            socklen_t len = sizeof(timeo);
            if (setsockopt(sock->sock, SOL_SOCKET, SO_SNDTIMEO, &timeo, len) == -1) {
                RI_LOGI("TIMEOUT Set Err??");


            }
#endif
#if defined(RI_CONFIG_IOS)
            int sing;
            socklen_t slen = sizeof(optval);
            if (setsockopt(sock->sock, SOL_SOCKET, SO_NOSIGPIPE, &sing, slen) == -1) {
                RI_LOGI("sing Set Err??");

            }
#endif
            return RI_OK;
    }
    /**
    * @brief 釋放目標RiSocket_t
    * @param riArray
    *        要釋放的RiSocket_t
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int RiSocket_Free(RiSocket_t *sock) {

        if (sock == NULL)
            return RI_ERROR_NULL_POINTER;

        RiSocket_Close(sock);

        ri_free(sock);
        RI_LOGI("socket has free");
        return RI_OK;
    }

    /**
    * @brief 關閉目標RiSocket_t的網路端口
    * @param sock
    *        目標RiSocket_t
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int RiSocket_Close(RiSocket_t *sock) {
        int ret = 0;

        if (sock == NULL)
            return RI_ERROR_NULL_POINTER;

#if defined(RI_WINDOWS)
        if (sock->sock >= 0) {
            ret = closesocket(sock->sock);
            sock->sock = -1;
        }

        if(ret != 0) {
            //RI_LOGE("RiSocket_Close: closesocket() = %d", ret);
            return RI_ERROR;
        }
#else
        RI_LOGI("closing socket");
        if (sock->sock >= 0) {
            int err = 1;
            socklen_t len = sizeof(err);
            if (-1 == getsockopt(sock->sock, SOL_SOCKET, SO_ERROR, (char *) &err,
                &len))
                RI_LOGE("get SO_ERROR");
            if (err)
                errno = err;
            if (shutdown(sock->sock, SHUT_RDWR) < 0)
                if (errno != ENOTCONN && errno != EINVAL)
                    RI_LOGE("shutdown");
            ret = close(sock->sock);
            sock->sock = -1;
        }

        if (ret != 0) {
            RI_LOGE("RiSocket_Close: close() = %d", ret);
            return RI_ERROR;
        }
#endif

        return RI_OK;
    }

    /**
    * @brief 設置目標RiSocket_t的ipAddress
    * @param sock
    *        設置目標RiSocket_t
    * @param ipAddress
    *        要設定的IP位址
    * @param port
    *        要設定的port
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int RiSocket_SetAddressIn(RiSocket_t *sock, ri_utf8 *ipAddress, int port) {
        if (sock == NULL)
            return RI_ERROR_PARAMETER_0;
        if (ipAddress == NULL)
            return RI_ERROR_PARAMETER_1;
        if (port <= 0)
            return RI_ERROR_PARAMETER_2;

        if (sock->af == RI_SOCKET_AF_INET) {
            sock->addr_in.sin_family = riSocket_GetAf(sock->af);

            if (strcmp("INADDR_ANY", (const char *) ipAddress) == 0) {
                sock->addr_in.sin_addr.s_addr = INADDR_ANY;
            } else {
                sock->addr_in.sin_addr.s_addr = inet_addr((const char *) ipAddress);
            }

            sock->addr_in.sin_port = htons(port);
        } else {
            return RI_ERROR;
        }

        return RI_OK;
    }

    /**
    * @brief 讓目標RiSocket_t進行bind動作，使Socket與目標端口建立關聯
    * @param sock 目標RiSocket_t
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int RiSocket_Bind(RiSocket_t *sock) {
        int ret;

        if (sock == NULL)
            return RI_ERROR_NULL_POINTER;

        if (sock->af == RI_SOCKET_AF_INET) {
            ret = bind(sock->sock, (struct sockaddr *) &sock->addr_in,
                sizeof(sock->addr_in));
        } else {
            //RI_LOGE("RiSocket_Bind: Not match" RI_NL);
            return RI_ERROR;
        }

        if (ret != 0) {
            //RI_LOGE("RiSocket_Bind: bind() = %d", ret);
            return RI_ERROR;
        }

        return RI_OK;
    }

    /**
    * @brief 讓目標RiSocket_t開始監聽端口
    * @param sock 目標RiSocket_t
    * @param backLog 允許連接上限
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int RiSocket_Listen(RiSocket_t *sock, int backLog) {
        int ret;

        if (sock == NULL)
            return RI_ERROR_PARAMETER_0;
        if (sock == NULL)
            return RI_ERROR_PARAMETER_1;

        ret = listen(sock->sock, backLog);

        if (ret != 0) {
            //RI_LOGE("RiSocket_Listen: listen() = %d", ret);
            return RI_ERROR;
        }

        return RI_OK;
    }


    /**
    * @brief 讓目標RiSocket_t開始接收端口
    * @param sock 目標RiSocket_t
    * @return 連進來的Client端socket
    */
    RiSocket_t *RiSocket_Accept(RiSocket_t *sock) {
        //RI_LOGI("RiSocket_t_RiSocket_Accept");
        RiSocket_t *sockNew;
        struct sockaddr_in addr;

#if defined(RI_WINDOWS)
        int addr_len = sizeof(struct sockaddr);
#else
        socklen_t addr_len = sizeof(struct sockaddr);
#endif
        RI_LOGI("RiSocket_t_RiSocket_Accept2");
        if (sock == NULL)
            return NULL;

        sockNew = (RiSocket_t *) ri_calloc(1, sizeof(RiSocket_t));

        if (sockNew == NULL) {
            return NULL;
        }

        sockNew->sock = accept(sock->sock, (struct sockaddr *) &addr, &addr_len);

        RI_LOGI("connect from %s", inet_ntoa(addr.sin_addr));

#if defined(RI_WINDOWS)
        if(sockNew->sock == INVALID_SOCKET) {
            RI_LOGE("RiSocket_Accept: sockNew->sock == INVALID_SOCKET");
            ri_free(sockNew);
            return NULL;
        }
#else
        if (sockNew->sock < 0) {
            RI_LOGE("RiSocket_Accept: %s", strerror(errno));
            ri_free(sockNew);
            return NULL;
        }
#endif

        
        RI_LOGI("RiSocket_t_RiSocket_Accept OK");
        return sockNew;
    }


    /**
    * @brief 透過目標RiSocket_t發送data
    * @param sock 目標RiSocket_t
    * @param buffer 要發送的data
    * @param bufferSize data有多大
    * @param flag 要設置的額外flag，例如MSG_DONTROUTE、MSG_OOB、MSG_PEEK
    * @return 發出幾byte
    */
    int RiSocket_Send(RiSocket_t *sock, const ri_byte *buffer, int bufferSize,
        int flag) {
            if (sock == NULL)
                return RI_ERROR_PARAMETER_0;
            if (buffer == NULL)
                return 0;
            if (bufferSize <= 0)
                return 0;
#if defined(RI_LINUX)
            int ret = (int) send(sock->sock, buffer, (size_t) bufferSize, flag);
#else(RI_WINDOWS)
            int ret = (int) send(sock->sock, (char*)buffer, (size_t)bufferSize, flag);
#endif

            if (ret <= 0) {
                RI_LOGE("SEND ERROR_%d",ret);
            }
            return ret;
    }

    /**
    * @brief 透過目標RiSocket_t發送data，指定發送位置為RiSocket_t->sock->addr_in所指定的位址
    * @param sock 目標RiSocket_t
    * @param buffer 要發送的data
    * @param bufferSize data有多大
    * @param flag 要設置的額外flag，例如MSG_DONTROUTE、MSG_OOB、MSG_PEEK
    * @return 發出幾byte
    */
      int RiSocket_SendTo(RiSocket_t *sock, const ri_byte *buffer,
        int bufferSize, int flag) {
            if (sock == NULL)
                return RI_ERROR_PARAMETER_0;
            if (buffer == NULL)
                return 0;
            if (bufferSize <= 0)
                return 0;
#if defined(RI_LINUX)
            return sendto(sock->sock, buffer, bufferSize, flag,
                (struct sockaddr *) &sock->addr_in, sizeof(sock->addr_in));
#else (RI_WINDOWS)
            return sendto(sock->sock, (char*)buffer, bufferSize, flag,
                (struct sockaddr *) &sock->addr_in, sizeof(sock->addr_in));
#endif
    }


    /**
    * @brief 透過目標RiSocket_t接收data
    * @param sock 目標RiSocket_t
    * @param buffer 要接收data到哪個buffer
    * @param bufferSize 要接收幾byte
    * @param flag 要設置的額外flag，例如MSG_DONTROUTE、MSG_OOB、MSG_PEEK
    * @return 接收到幾byte
    */
      int RiSocket_Recv(RiSocket_t *sock, ri_byte *buffer, int bufferSize,
        int flag) {
            if (sock == NULL)
                return RI_ERROR_PARAMETER_0;
            if (buffer == NULL)
                return 0;
            if (bufferSize <= 0)
                return 0;
#if defined(RI_LINUX)
            return recv(sock->sock, buffer, bufferSize, flag);
#else(RI_WINDOWS)
            return recv(sock->sock, (char*)buffer, bufferSize, flag);
#endif
    }


    /**
    * @brief 透過目標RiSocket_t接收data，指定接收RiSocket_t->sock->addr_in所指定的位址
    * @param sock 目標RiSocket_t
    * @param buf 要接收data到哪個buffer
    * @param bufSize 要接收幾byte
    * @param flag 要設置的額外flag，例如MSG_DONTROUTE、MSG_OOB、MSG_PEEK
    * @return 接收到幾byte
    */
      int RiSocket_RecvFrom(RiSocket_t *sock, ri_byte *buf, int bufSize,
        int flag) {
#if defined(RI_WINDOWS)
            int addrlen;
#else
            socklen_t addrlen;
#endif

            if (sock == NULL)
                return RI_ERROR_PARAMETER_0;
            if (buf == NULL)
                return 0;
            if (bufSize <= 0)
                return 0;

            addrlen = sizeof(sock->addr_in);

            return recvfrom(sock->sock, (char *) buf, bufSize, flag,
                (struct sockaddr *) &sock->addr_in, &addrlen);
    }


    /**
    * @brief 使用目標RiSocket_t建立連線
    * @param sock 目標RiSocket_t
    * @return 成功回傳1，否則回傳錯誤碼
    */
      int RiSocket_Connect(RiSocket_t *sock) {
        int ret;

        if (sock == NULL)
            return RI_ERROR_NULL_POINTER;

        if (sock->af == RI_SOCKET_AF_INET) {
            ret = connect(sock->sock, (struct sockaddr *) &sock->addr_in,
                sizeof(struct sockaddr));
        } else {
            RI_LOGE("RiSocket_Connect: Not match");
            return RI_ERROR;
        }

        if (ret != 0) {
            RI_LOGE("RiSocket_Connect: connect() = %d", ret);
            return RI_ERROR;
        }

        return RI_OK;
    }

#ifdef __cplusplus
}
#endif
