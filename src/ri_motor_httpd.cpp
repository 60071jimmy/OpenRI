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

/*******************************************************************************
* Date           Author      Description                                      *
*******************************************************************************
* 2015-09-07     Iron        加入Qt控制方向旋鈕Icon對應的command
* 2015-09-30     Ann         搖桿控制馬達
*                Ann         log消
* 2015-10-08     Iron        control motor in stable mode
* 2015-10-13     Iron        準星校正
* 2015-10-15     Iron        調整手動速度
* 2015-11-03     Iron        更改馬達左右轉正負號
* 2015-11-19     Iron        加入步進馬達控制邏輯
* 2015-11-26     Iron        修正target校正馬達方向相反，調整馬達手控程式
* 2015-11-26     Iron        加入遠端關閉電源功能
* 2015-12-02     Ann         加入write logfile & getTIme()
* 2015-11-26     Iron        加入遠端關閉電源功能，穩定校正功能先關閉
* 2015-12-03     Ann         修正準星校正會overflow問題
* 2015-12-04     Ann         add mitiple_motor(case x) 
* 2015-12-04     Ann         makefile add LOGFILE to turn on/off the function of logFIle
* 2015-12-07     Iron        加入雷射測距功能
* 2015-12-10     Iron        修正雷射測距
* 2015-12-16     Ann         馬達快速旋轉不調整速度
* 2015-12-28     Iron        加入自動上膛＆彈量計算功能
* 2015-12-30     Ann         加入計算彈量總數（case h）
******************************************************************************/
#include "openri.h"

#define RASPBERRYPI 0
#define ARDUINO 1
#undef HOST
#define HOST ARDUINO

#if defined (RI_WINDOWS)
#include <cmath>
#include <stdint.h>

#elif(RI_LINUX)
#include "gt_httpd.h"
#include "defines.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/timeb.h>
#if HOST == ARDUINO
#include "arduino-serial-lib.h"
#else
#include <wiringPi.h>
#include <raspicam/raspicam_cv.h>
#include <linux/spi/spidev.h>
#endif
#endif





using namespace std;
/**
* @file
* @brief 使用gt_socket架設HttpServer
*
* @author LEADERG
*/

#ifdef __cplusplus
extern "C"
{
#endif


#define sign(x) x>=0 ? 1:0
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define SPI	0
#define I2C 1
#undef INTERFACE
#define INTERFACE	SPI
#define STABLE_MODE 1
#define MANUAL_MODE 0
#define YELLOW "\033[1;33m"
#define CYAN "\033[0;36m"
#define SENSOR_IP "192.168.88.103"//192.168.88.103
#define SENSOR_PORT 3335
#define SETTING_PATH "/home/military205-motor/setting"
#define log 1
#define LLIMIT -1
#define NOLIMIT 0
#define RLIMIT  1
#define LCMD -1
#define RCMD 1

#if HOST == RASPBERRYPI
#define ARDUINO_STAT_PIN	0
#define RPI_STAT_PIN		1
#if INTERFACE == SPI
    static const char *devName = "/dev/spidev0.0";
    static uint8_t spi_mode;
    static uint8_t bits = 8;
    static uint32_t speed = 500000;
    static uint16_t spi_delay;
    int fd_spi;
#elif INTERFACE == I2C
    int fd_i2c;
    static const char *devName = "/dev/i2c-1";
#endif
#elif HOST == ARDUINO
    int fd_serial;
#endif

    const char *laser_cmd[3] = {
        "$CCSNQ,DFL*2E<cr><lf>",
        "$CCSNQ,RCS*22<cr><lf>",
        "$CCSNQ,ACT*36<cr><lf>"
    };

    enum CMD_LASER {
        DEF = 0,
        RCS,
        ACT
    };


    void control_event(int sig);
    int default_yaw_ang = 0;
    int default_roll_ang = 0;
    static int len_server, len_client;
    static int servo_motor_ready = 0;
    int target_x = 0;
    int target_y = 0;
    int mutiple_motor =8;
    volatile int yaw_ang = 0;
    volatile int roll_ang = 0;    
    int signvalue = 1;
    static bool isServoDataReady = false;
    static HANDLE mutex_servo_angle;
    int operate_mode =  STABLE_MODE;
    double yaw_manual_step = 0;
    double roll_manual_step = 0;
    float out_yaw, out_roll;
    FILE *setting_config;
    FILE *logFile;	
    char logFIle_message[100];
    int target =0;
    int isLimit_yaw = 0;
    int isLimit_roll = 0;
    int cmd_lr = 0;
    int cmd_roll = 0;
    int fd_laser_controller = -1;
    char buf_laser[256];
    int bullet_notify[2], bullet_cnt = 0;
	HANDLE conThread;
    /**
    * LocalServer的Socket
    */
    static RiSocket_t *localSocket;

    /**
    * LocalServerd開在哪個port
    */
    static int localServerPort;
    static RiLock_t * glock;
    /**
    * 此Library是否已經初始化
    */
    static int riHttpdIsInit = 0;

    char *getTIme(){
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char *time =asctime(tm);
        std::string time_string(time);
        time_string.replace(time_string.find("\n"), sizeof(" ")-1, "");
        // time_string.replace("\n","");
        strcpy(time, time_string.c_str());
        return time;
    }
    bool first_open =true;
    static void write_logFile(const char *message)
    {
#if defined(LOGFILE)
        if(first_open )
        {
            logFile = fopen( "motor.txt", "a" );
            if ( NULL == logFile ){
                RI_LOGI("Open failure1");
            }
            else
            {
                fprintf(logFile, "====================%s====================\n", getTIme());
                fflush(logFile);
                first_open =false;
            }
        }
        else
        {
            fprintf(logFile, "[%s] %s\n", getTIme(), message);
            fflush(logFile);
        }
#endif

    }

    /*RI_API int RiHttpd_InitLib() {
    if (gtHttpdIsInit == 1) {
    return RI_OK_INIT_ALREADY;
    }
    riHttpdIsInit = 1;

    #if defined(RI_HTTPD_OPEN_SSL)
    // Initializing the ssl library.
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    #endif

    return RI_OK;
    }*/

    bool open_laser_device(const char *dev)
    {
#if defined(RI_LINUX)
        fd_laser_controller = serialport_init(dev, 38400);

        if( fd_laser_controller == -1 )
        {
            sprintf(logFIle_message, "couldn't open laser port %s\n", dev );
            write_logFile(logFIle_message);
            return false;
        }

        write(fd_laser_controller, laser_cmd[RCS], strlen(laser_cmd[RCS]));
        RiThread_SleepMs(500);

        memset(buf_laser,0,256);
        serialport_read_until(fd_laser_controller, buf_laser, '\n', 256, 5000);

        if (strlen(buf_laser) > 0)
            return true;
#endif
        return false;
    }

    DWORD WINAPI piConnects2(void *arg)
    {
        RiSocket_t *sockClient;
        sockClient=(RiSocket_t *)arg;
        int ret = 0;
        int tryCnt = 0;
        char buffer[2048];
        char header[2];
        char size[4];
        std::string resp;

        while(1)
        {
            ret = RiSocket_Recv(sockClient, (ri_byte *) header, sizeof(header), 0);
            if (ret <= 0) 
                goto exit;

            if(header[0]==0x5a && header[1]==0x5a)
            {
                //RI_LOGI("get header OK");           
                ret = RiSocket_Recv(sockClient, (ri_byte *) size, sizeof(size), 0);
                if (ret <= 0)
                    goto exit;

                long *sizeptr= (long *) (&size[0]);
                long getsize=*sizeptr;
                //RI_LOGI("get Size OK,%ld bytes, %hhd %hhd %hhd %hhd",getsize,size[0],size[1],size[2],size[3]);

                ret = RiSocket_Recv(sockClient, (ri_byte *) buffer, getsize, 0);
                if (ret <= 0)
                    goto exit;

                printf("case %c\n", buffer[0]);	
                switch(buffer[0])
                {
                case 'A':// camera
                case 'a':// camera
                    break;
                case 'b'://0x01:
                    cmd_roll = 1;
                    roll_manual_step = (50000)/(360);
                    RI_LOGI("垂直快速下轉\n");                  
                    break;
                case 'B':// 接收UI端傳來下轉指令
                    cmd_roll = 1;
                    roll_manual_step = 12500*mutiple_motor/(4*360*8);
                    RI_LOGI("垂直下轉\n");                   
                    break;
                case 'c'://水平停止0                       
                    //RI_LOGI("水平停止");	
                    yaw_manual_step = 0;
                    break;
                case 'C'://垂直停止    
                    // RI_LOGI("垂直停止");
                    roll_manual_step = 0;
                    break;
                case 'd':// Camera
                    break;
                case 'E':// Sensor
                    break;
                case 'e':// camera
                    break;
                case 'F':// Sensor
                    break;
                case 'f':// camera
                    break;
                case 'G':// camera
                    break;
                case 'g'://0x11:
                    {

                        if (buffer[3] == 0)
                            yaw_ang -= (buffer[1]<<8) + buffer[2];
                        else
                            yaw_ang += (buffer[1]<<8) + buffer[2];

                        if (buffer[6] == 0)
                            roll_ang -= (buffer[4]<<8) + buffer[5];
                        else
                            roll_ang += (buffer[4]<<8) + buffer[5];

                    }
                    break;
                case 'H':/* 接收從sensor傳來的角度差值 */
                    break;
                    long tmp_yaw;
                    tmp_yaw = ((buffer[1]<<8) + (unsigned char)buffer[2]);
                    long tmp_roll;
                    tmp_roll = (buffer[4]<<8) + (unsigned char)buffer[5];

                    if ( buffer[3] == 0 )
                        tmp_yaw *= -1;

                    if ( buffer[6] == 0 )
                        tmp_roll *= -1;

#if MOTOR_TYPE == STEP_MOTOR
                    yaw_ang += tmp_yaw;
                    roll_ang += tmp_roll;
#elif MOTOR_TYPE == SERVO_MOTOR
                    yaw_ang = tmp_yaw;
                    roll_ang = tmp_roll;
#endif

                    RI_LOGI("from gyro: y(%d), r(%d)\n", yaw_ang, roll_ang);
                    isServoDataReady = true;
                    break;
                case 'h':
                    buffer[0] = (((int)bullet_cnt) >> 8);
                    buffer[1] = (((int)bullet_cnt) & 0xFF);
                    printf("bullet %d    %d\n", bullet_cnt,  (((unsigned char)buffer[0]<<8) + (unsigned char)buffer[1]));                     
                    RiSocket_Send(sockClient, (ri_byte *)buffer,2,0); 
                    break;     
                case 'I':
                    memset(buffer, 0, 2048); 
                    if ( fd_laser_controller > 0)
                    {
                        printf("Laser measurement\n");
#if defined(RI_LINUX)
                        write(fd_laser_controller, laser_cmd[ACT], strlen(laser_cmd[ACT]));
                        printf("write command\n");
                        RiThread_SleepMs(500);
                        memset(buf_laser,0,256);
                        serialport_read_until(fd_laser_controller, buf_laser, '\n', 256, 5000);
                        printf("laser: %s\n", buf_laser);
#endif
                        //if (strlen(buf_laser) < 10)
                        //  break;
                    }
                    else {
                        //$SNLRF,G,R,D,,M,A,138.8,M,I,8.3,M*74

                        sprintf(buf_laser, "$SNLRF,sp,R,D,123M");
                    }
                    //char *str;
                    //str = strstr( buf_laser, "D,");
                    resp = buf_laser ;
                    std::cout<<resp<<std::endl;


                    if (resp.length() > 10)
                    {
                        resp = resp.substr(resp.find_first_of("D")+2);
                        resp = resp.erase(resp.find_first_of(",M"));
                        std::cout<<"str len: "<<resp.length()<<std::endl;
                        if (resp.length() == 0)
                            resp = "xx M";
                        else
                            resp += "M";
                        sprintf(buffer, "%s", resp.c_str());
                    }
                    else
                        sprintf(buffer, "xx M");                              

                    printf("resp: %s~~~\n", buffer);
                    RiSocket_Send(sockClient, (ri_byte *)buffer, 20, 0);
                    break;
                case 'i':
                    bullet_cnt = ((unsigned char)buffer[1])<<8;
                    bullet_cnt += (unsigned char)buffer[2];
                    printf("totoal bullet %d, (%d, %d)\n", bullet_cnt, (unsigned char)(buffer[1])<<8, (unsigned char)buffer[2]);
                    break;
                case 'J':// camera
                    break;
                case 'k':// motor, 自動上膛 OFF
                    if (fd_serial != -1)
                    {
                        printf("Auto Reload: OFF\n");
                        sprintf(buffer, "%d\n", 0);
#if defined(RI_LINUX)
                        serialport_write(fd_serial, buffer);
#endif
                    }
                    break;
                case 'K':// motor, 自動上膛 ON
                    if (fd_serial != -1)
                    {
                        printf("Auto Reload: ON\n");
                        sprintf(buffer, "%d\n", 1);
#if defined(RI_LINUX)
                        serialport_write(fd_serial, buffer);
#endif
                    }
                    break;
                case 'l':// 接收UI端傳來左旋指令
                    RI_LOGI("Turn Left Faster\n");
                    cmd_lr = -1;
                    //yaw_manual_step = -(50000*4)/360;                   
                    yaw_manual_step = -(50000)/(360);
                    break;
                case 'L':// 接收UI端傳來左旋指令
                    RI_LOGI("Turn Left\n");
                    cmd_lr = -1;
                    yaw_manual_step = -12500*mutiple_motor/(360*4*8);                 
                    RI_LOGI("yaw_manual_step: %.3f\n", yaw_manual_step);
                    break;
                case 'p':
                    printf("TEST!\n");
                    //int target_x;
                    target_x = ((buffer[1]<<8) + (unsigned char)buffer[2]);
                    //int target_y;
                    target_y = ((buffer[4]<<8)+ (unsigned char)buffer[5]);

                    if ( buffer[3] == 0 )
                        target_x *= 1;

                    if ( buffer[6] == 0 )
                        target_y *= 1;
                    printf("target x: %d, target y: %d\n", target_x, target_y);
                    yaw_manual_step = 50000/360;//*target_x;
                    roll_manual_step = 50000/360;//*target_y;
                    target = 1;
                    break;
                case 'r':// 接收UI端傳來右旋指令
                    cmd_lr = 1;
                    yaw_manual_step = (50000)/(360);
                    RI_LOGI("Turn Right Faster\n");                
                    break;
                case 'R':// 接收UI端傳來右旋指令
                    cmd_lr = 1;
                    yaw_manual_step = 12500*mutiple_motor/(4*360*8);
                    RI_LOGI("Turn Right\n");                 
                    break;
                case 't':// 接收UI端傳來上轉指令
                    cmd_roll = -1;
                    roll_manual_step = -(50000)/(360);
                    RI_LOGI("Turn Up Faster\n");                 
                    break;
                case 'T':// 接收UI端傳來上轉指令
                    cmd_roll = -1;
                    roll_manual_step = -(12500*mutiple_motor)/(4*360*8);
                    RI_LOGI("Turn Up\n");                   
                    break;
                case 'Y':
                case 'S':
                    operate_mode = MANUAL_MODE;//STABLE_MODE;
                    RI_LOGI("case STABLE_MODE: %d\n", operate_mode);
                    sprintf(logFIle_message, "case STABLE_MODE: %d", operate_mode);
                    write_logFile(logFIle_message );
                    //fseek(setting_config, 0, 0);
                    //fprintf( setting_config, "%d\n", operate_mode);					
                    //fflush( setting_config);
                    //RI_LOGI("save config\n");
                    //clientSocket(SENSOR_IP, SENSOR_PORT, "S", 1);
                    break;
                case 's':
                    operate_mode = MANUAL_MODE;
                    sprintf(logFIle_message, "case MANUAL_MODE: %d", operate_mode);
                    write_logFile(logFIle_message );
                    //fseek(setting_config, 0, 0);
                    //fprintf( setting_config, "%d\n", operate_mode);
                    //fflush( setting_config);
                    //RI_LOGI("save config\n");
                    //clientSocket(SENSOR_IP, SENSOR_PORT, "s", 1); 
                    break;
                case 'Z':// sensor
                    break;
                case 'x':
                    mutiple_motor = ((buffer[1]<<8) + (unsigned char)buffer[2]);
                    break;
                case 'z':
                    system("echo 205 | sudo -S poweroff");
                    break;
                }
                fflush(logFile);
            }
            else
            {
                RI_LOGI("header is not 0x5a0x5a..skip");

            }

        }
exit:
        RI_LOGI(CYAN "exit piconnect thread\n");
        write_logFile( "exit piconnect thread");

        CloseHandle(conThread);
        return 0;
    }

    DWORD WINAPI piServerThread3(void *)
    {

        RI_LOGI("\npiServerThread\n");

        // TCP server
        int ret = 0;
        //允許同時10個連線....
        int backLog = 10;//0316 CHANGE TO 10 CONNECT
        RiSocket_t *sockClient;

        localSocket = RiSocket_New();

        ret = RiSocket_Open(localSocket, RI_SOCKET_AF_INET, RI_SOCKET_SOCK_STREAM,
            RI_SOCKET_IPPROTO_TCP);
        if (ret <= 0)
        {

            RI_LOGI("RiSocket_Init = %d\n", ret);
            sprintf(logFIle_message, "RiSocket_Init = %d", ret);
            write_logFile(logFIle_message);
            return NULL;
        }

        //20150116增加.....連續Bind測試避免端口被吃掉....試200個應該夠
        int i = 0;
        for (i = 0; i < 200; i++)
        {

            ret = RiSocket_SetAddressIn(localSocket, (ri_utf8 *) "INADDR_ANY",
                localServerPort);

            if (ret <= 0)
            {

                RI_LOGI("RiSocket_SetAddressIn = %d\n", ret);
                sprintf(logFIle_message, "RiSocket_SetAddressIn = %d", ret);
                write_logFile(logFIle_message);
                return NULL;
            }

            ret = RiSocket_Bind(localSocket);
            if (ret <= 0)
            {

                RI_LOGI("RiSocket_Bind = %d\n", ret);
                sprintf(logFIle_message, "RiSocket_Bind = %d", ret);
                write_logFile(logFIle_message);
                localServerPort++;
            }
            else
            {

                RI_LOGE("localServer port open： = %d\n", localServerPort);
                break;
            }
        }
        fflush(logFile);

        ret = RiSocket_Listen(localSocket, backLog);
        if (ret <= 0)
        {

            RI_LOGI("RiSocket_Listen = %d\n", ret);
            write_logFile("localServer port open");
            return NULL;
        }

        char ret_strings[] = "return OK";

        while (localSocket)
        {

            RI_LOGI("server RUN...\n");
            sockClient = RiSocket_Accept(localSocket);
            RI_LOGI("server Accept");  
            if (!localSocket)
            {   

                RI_LOGI("local server disconnect B...\n");
                write_logFile("local server disconnect B");
                break;
            }

            RI_LOGI("Accept..");


            if (localSocket)
            {

                RI_LOGI("cnnect from %s\n",inet_ntoa(localSocket->addr_in.sin_addr));         

            }
            else
            {
                RI_LOGE("NULL localSocket");
                write_logFile("NULL localSocket\n");
            }


            RI_LOGI("Before RiSocket_Recv_header");

            //pthread_t conThread;
            conThread = CreateThread(NULL/*&conThread*/, NULL, piConnects2, sockClient, 0, NULL);

            RI_LOGI("server ONE ROUND");


            continue;
        }

        RI_LOGI("RiSocket_Close");


        return 0;
    }
    /**
    * @brief 回傳LocalServer的Port開在哪裡
    * @return LocalServer開啟的Port
    */
    static int motor_getlocalServerPort() {
        return localServerPort;
    }

    //static pthread_t camThread;

    static int motor_initLocalServer2(int myLocalServerPort) 
    {

        write_logFile("");
        localServerPort = myLocalServerPort;

        RI_LOGI("port - %d......\n", localServerPort); 
        //0120test....
        //pthread_t sendThread;
        CreateThread(NULL/*&sendThread*/, NULL, piServerThread3, NULL, 0, NULL);

        RI_LOGE("initLocalServer --");

        return RI_OK;
    }


    //0401 change....
    static RiSocket_t *client=NULL;
    int motor_clientSocket(const char* tarIp,int port,const char* msg,int size)
    {
        RiLock_Lock(glock);
        int ret=0;
        if(!client)
        {
            client=RiSocket_New();
            ret= RiSocket_Open_With_TimeOut(client, RI_SOCKET_AF_INET,
                RI_SOCKET_SOCK_STREAM, RI_SOCKET_IPPROTO_TCP, 6);

            if(ret<0)
            {

                RI_LOGE("ERROR OPEN SOCKET AT clientTest");
                write_logFile("[ERROR]ERROR OPEN SOCKET AT clientTest");
                RiSocket_Free(client);
                client=NULL;
                RiLock_Unlock(glock);
                return -1;
            }
            ret = RiSocket_SetAddressIn(client, (ri_utf8 *)tarIp, port);
            ret = RiSocket_Connect(client);

            if (ret == RI_ERROR)
            {

                RI_LOGE("Fail to connect");
                write_logFile("[ERROR]E Fail to connect");
                RiSocket_Free(client);
                client=NULL;
                RiLock_Unlock(glock);
                return -1;
            }
        }
        char vals[2];
        vals[0]=0x5a;
        vals[1]=0x5a;
        ret=RiSocket_Send(client, (ri_byte *)vals,2,0);

        long sizearr[1];
        sizearr[0]=(long)size;
        ret=RiSocket_Send(client, (ri_byte *) sizearr,4,0);

        ret=RiSocket_Send(client, (ri_byte *)msg,size,0);

        if(ret<0)
        {
            RiSocket_Close(client);
            RiSocket_Free(client);
            client=NULL;

        }
        RiLock_Unlock(glock);
        return ret;
        fflush(logFile);
    }


    DWORD WINAPI receiveBullet(void *)
    {
        int timeout = 10, i = 0;
        char eolchar = '\n';
        char cmd[160];


        RI_LOGI("start receive Bullet ");
        while(1){
            i = 0;
            memset(cmd, '\0', 160);
            memset(bullet_notify, '\0', 2);
            if (fd_serial != -1)
            {
#if defined(RI_LINUX)
                serialport_read_until(fd_serial, cmd, eolchar, 160, timeout);
#endif
                char *str = strtok(cmd, "@");
                while (str != NULL)
                {
                    bullet_notify[i++] = atoi(str);
                    str = strtok(NULL, "");
                }

                if (i > 1 && bullet_cnt != 0)
                {
                    bullet_cnt--;
                }
            } 
        }
    }


    DWORD WINAPI runServo(void *) 
    {

        int old_yaw_ang, old_roll_ang;
#if defined(RI_LINUX)
        char cmd[160];
#endif
        int checksum = 0;
        double yaw_stable_maunal = 0;
        double roll_stable_manual =0;

        yaw_ang = default_yaw_ang;
        roll_ang = default_roll_ang;
        old_yaw_ang = yaw_ang;
        old_roll_ang = roll_ang;
        servo_motor_ready = 1;


        //pthread_t receiveThread;
        CreateThread(NULL/*&receiveThread*/, 0, receiveBullet, NULL, 0, NULL);

        RI_LOGI("control servo motor ");
        /* control servo motor*/
        while (1)
        {
            //printf("run servo\n");
            if (operate_mode == STABLE_MODE)
            { 
                if (!isServoDataReady && ( (yaw_manual_step == 0) && (roll_manual_step == 0) ) ) 
                {
                    RiThread_SleepMs(100);							
                    continue;
                }
                isServoDataReady = false;


                if((old_yaw_ang == yaw_ang) && (old_roll_ang == roll_ang) && ( (yaw_manual_step == 0) && (roll_manual_step == 0) ))
                {
                    RiThread_SleepMs(100);
                    continue;
                }


            }
            else if (operate_mode == MANUAL_MODE)
            {
                if ( (yaw_manual_step == 0) && (roll_manual_step == 0) )
                    continue; 

                RiThread_SleepMs(100);
            }

            if(target == 1)
            {
                printf("target_x : %d  TARGET_Y %d\n", target_x, target_y);
                if(abs(target_x) > 0)
                {				
                    yaw_manual_step =(target_x/abs(target_x))* 50000/360;  
                    target_x =target_x-target_x/abs(target_x);          
                    //roll_manual_step = 0;	
                }
                if(target_x == 0)
                    yaw_manual_step = 0;
                if(abs(target_y) > 0)
                {
                    roll_manual_step = (target_y / abs(target_y)) * 50000 / 360;  
                    target_y = target_y - target_y / abs(target_y);          
                    //roll_manual_step = 0;	
                }
                if(target_y == 0)
                    roll_manual_step = 0;	
                if(target_x == 0 && target_y == 0)
                {
                    target = 0;
                }
            }




            servo_motor_ready = 0;
            /* 判斷如果是手動操作則馬達控制角度完全由UI端下指令，反之穩定模式
            則使用陀螺儀輸出的角度做控制*/
            if (operate_mode == MANUAL_MODE)
            {
                //RI_LOGI("out_yaw:  %.3f....\n", out_yaw);
                //out_yaw += yaw_manual_step;
                out_yaw = (float)yaw_manual_step;
                //out_roll += roll_manual_step;
                out_roll = (float)roll_manual_step;
                //RI_LOGI("out_yaw: %.3f step: %.3f....\n", out_yaw, yaw_manual_step);
                /*if ( out_yaw < -87*50000/360)
                out_yaw = -87*50000/360;
                else if ( out_yaw > 85*50000/360 )
                out_yaw = 85*50000/360;

                if ( out_roll < -90*50000/360)
                out_roll = -90*50000/360 ;
                else if ( out_roll > 79*50000/360 )
                out_roll = 79*50000/360;*/
            }
            else if (operate_mode == STABLE_MODE)
            {
                //printf("yaw step bef: %.3f\n", yaw_manual_step);
                //printf("yaw manual step stable: %.1f\n", yaw_manual_step);
                printf("isLimit_roll(%d), cmd_roll(%d)\n", isLimit_roll, cmd_roll);
                // (isLimit_yaw*cmd_lr != 1)
                //{
                yaw_stable_maunal += yaw_manual_step;

                //}
                //if (isLimit_roll*cmd_roll != 1)
                roll_stable_manual += roll_manual_step;
                //else
                //isLimit = false;
                out_yaw = (float)(-yaw_ang + yaw_stable_maunal);//


                out_roll = (float)(-roll_ang + roll_stable_manual);//

                //printf("stable: %.3f  step: %.3f\n",out_yaw,  yaw_manual_step );
            }




            if ( out_yaw < -87*50000/360)
            {
                printf("Exceed horizontal limit---1\n");
                isLimit_yaw = 1;
                //out_yaw = -87*50000/360;

            }
            else if ( out_yaw > 85*50000/360 )
            {
                printf("Exceed horizontal limit---2\n");           
                //out_yaw = 85*50000/360;
                isLimit_yaw = -1;
            }
            else {
                isLimit_yaw = 0;
            }


            if ( out_roll < -70*50000/360)
            {
                printf("Exceed vertical limit---1\n");           
                isLimit_roll = 1;
                //out_roll = -70*50000/360;
            }
            else if ( out_roll > 79*50000/360 )
            {
                printf("Exceed vertical limit---2\n");
                isLimit_roll = -1;
                //out_roll = 79*50000/360; 
            }
            else
                isLimit_roll = 0;

            printf("yaw out---2: %.1f\n", out_yaw);
            printf("roll out---2: %.1f\n", out_roll);
#if defined(RI_LINUX)
#if HOST == RASPBERRYPI
            cmd[0] = (abs(out_yaw)>>8);
            cmd[1] = (abs(out_yaw)&0xFF);//roll_ang;

            if (out_yaw >= 0)
                signvalue = 1;
            else
                signvalue = 0;

            cmd[2] = signvalue;
            cmd[3] = (abs(out_roll)>>8); 
            cmd[4] = (abs(out_roll)&0xFF);

            if (out_roll >= 0)
                signvalue = 1;
            else
                signvalue = 0;

            cmd[5] = signvalue;
            checksum = floor(cmd[0]/100) + (int)floor(cmd[0]/10)%10 + cmd[0]%10 +
                floor(cmd[1]/100) + (int)floor(cmd[1]/10)%10 + cmd[1]%10 +
                floor(cmd[3]/100) + (int)floor(cmd[3]/10)%10 + cmd[3]%10 +
                floor(cmd[4]/100) + (int)floor(cmd[4]/10)%10 + cmd[4]%10 +
                cmd[2] + cmd[5];
            cmd[6] = checksum;
#if INTERFACE == SPI
            cmd[7] = 0x0A;
            uint8_t rx[ARRAY_SIZE(cmd)] = {0, };

            struct spi_ioc_transfer tr = {
                tr.tx_buf = (unsigned long)cmd,
                tr.rx_buf = (unsigned long)rx,
                tr.len = ARRAY_SIZE(cmd),
                tr.delay_usecs = spi_delay,
                tr.speed_hz = speed,
                tr.bits_per_word = bits,
            };

            RI_LOGI(YELLOW "SPI:1[%d-%d-%d(%f)], 2[%d-%d-%d(%f)]\n", cmd[2], cmd[0], cmd[1], out_yaw*360.0/50000, cmd[5], cmd[3], cmd[4],   		out_roll*360.0/50000);

            int ret = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr);
            if(ret <1)
                RI_LOGI("spi send data fail XX\n");

#elif INTERFACR == I2C
            if (write(fd_i2c, cmd, 5) != 1)
                RI_LOGI("i2c send data fail!\n");
#endif
#elif HOST == ARDUINO
            sprintf(cmd, "%d %d %d %d %d %d 0\n", 
                (abs(out_yaw)>>8), (abs(out_yaw)&0xFF), sign(out_yaw), (abs(out_roll)>>8), (abs(out_roll)&0xFF), sign(out_roll));

            if (fd_serial != -1)
                serialport_write(fd_serial, cmd);

            RiThread_SleepMs(5000);
#endif
#endif
            old_yaw_ang = yaw_ang;
            old_roll_ang = roll_ang;
            servo_motor_ready = 1;
            //pthread_mutex_unlock (&mutex_servo_angle);
        }
        fflush(logFile);
    }


    void arudino_changeStat() 
    {
        RI_LOGI("arduino change status $$$$\n");
        yaw_ang = 0;
        roll_ang = 0;
        out_yaw = 0;
        out_roll = 0;
    }

    static int startSevro() 
    {
#if defined(RI_LINUX)
#if HOST == RASPBERRYPI

        RI_LOGI(".......initialize wiringPi.......\n");   
        if(getuid()!=0)
        {
            RI_LOGI("wiringPi must be run as root. \n");      
            //	return NULL;
        }

        if(wiringPiSetup()==-1)
        {	

            RI_LOGI("wiringPi setup failed. \n");
            write_logFile( "wiringPi setup failed. ");
            //return NULL;
        }

        // 註冊中斷通知arduino處於重起狀態
        if (wiringPiISR(ARDUINO_STAT_PIN, INT_EDGE_FALLING, &arudino_changeStat) < 0)
            RI_LOGI("register arduino interrupt fail xxx.\n");


        // notify arduino restart program, rpi pin 12
        pinMode(1, OUTPUT);
        digitalWrite(1, LOW);

        glock=RiLock_New();
        //0120test....
        pthread_mutex_init(&mutex_servo_angle, NULL);
#if INTERFACE == SPI
        if ((fd_spi = open(devName, O_RDWR)) < 0)
            RI_LOGI("SPI: Failed to access %s\n", devName);

        /* spi mode*/
        if (ioctl(fd_spi, SPI_IOC_WR_MODE, &spi_mode) == -1)
            RI_LOGI("SPI: Can't set spi mode\n");

        if (ioctl(fd_spi, SPI_IOC_RD_MODE, &spi_mode) == -1)
            RI_LOGI("SPI: Can't get spi mode\n");

        /* bits per word*/
        if (ioctl(fd_spi, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1)
            RI_LOGI("SPI: Can't set bits per word\n");

        if (ioctl(fd_spi, SPI_IOC_RD_BITS_PER_WORD, &bits) == -1)
            RI_LOGI("SPI: Can't get bits per word\n");

        /* max speed hz*/
        if (ioctl(fd_spi, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
            RI_LOGI("SPI: Can't set max speed hz");

        if (ioctl(fd_spi, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1)
            RI_LOGI("SPI: Can't get max speed hz");

        RI_LOGI("SPI mode: %d\n", spi_mode);
        RI_LOGI("SPI bits per word: %d\n", bits);
        RI_LOGI("SPI max speed: %d Hz (%d KHz)\n", speed, speed / 1000);
#elif INTERFACE == I2C
        if ((fd_i2c = open(devName, O_RDWR)) < 0) {
            RI_LOGI("I2C: Failed to access %s\n", devName);
        }

        RI_LOGI("I2C: acquiring buss to 0x%x\n", ADDRESS);

        if (ioctl(fd_i2c, I2C_SLAVE, ADDRESS) < 0) {
            RI_LOGI("I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
        }
#endif
        digitalWrite(1, HIGH);
#else
        FILE *pipe_dev;
        char str[10], dev[20];
        pipe_dev = popen("ls /dev/ | grep  ACM", "r");

        fgets(str, sizeof(str) - 1, pipe_dev);
        sprintf(dev, "/dev/%s", str);
        dev[strlen(dev) - 1] = '\0';
        pclose(pipe_dev);
        RI_LOGI("%s is arduino port\n", dev);   

        fd_serial = serialport_init("/dev/ttyACM0", 115200);


        if( fd_serial == -1 ) 
        {
            RI_LOGI("couldn't open serial port xxx\n");
            write_logFile("couldn't open serial port xxx");
        }


        serialport_flush(fd_serial);
#endif
#endif

        /* setting_config  = fopen(SETTING_PATH, "r+w");
        if ( setting_config)
        {
        fscanf(setting_config, "%d\n", &operate_mode);
        RI_LOGI("prev mode: %d\n", operate_mode);
        }
        else {
        setting_config  = fopen(SETTING_PATH, "w");
        fprintf( setting_config, "%d\n", operate_mode);
        }*/

        if ( !open_laser_device("/dev/ttyUSB0") )
        {
            write_logFile("Fail to open laser measurement\n");
            printf("Fail to open laser measurement\n");
        }
        else
            printf("Laser measurement opened\n");

        operate_mode = MANUAL_MODE;
        RI_LOGI("Operate mode: %d\n", operate_mode);
        //pthread_t servoThread;
        CreateThread(NULL/*&servoThread*/, NULL, runServo, NULL, 0, NULL);
        fflush(logFile);
        return RI_OK;
    }




#ifdef __cplusplus
}
#endif
