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

#include "ri_httpd.h"
/*
#include "ri_fifo.h"
#include "riArray.h"
#include "ri_thread.h"
#include "ri_lock.h"
*/
#include <ctype.h>

#include <windows.h>



#if defined (RI_LINUX)
//0306 add for sevro
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>
#include <wiringSerial.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <sys/ioctl.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <sys/time.h>
#include <sys/timeb.h>
//#include "../../softServo.h"
//0306 end

//0313
#include <raspicam/raspicam_cv.h>
MPU6050 mpu;
#elif defined(RI_WINDOWS)
#include <stdint.h>
#include <WinBase.h>
#endif
/**
* @file
* @brief 使用gt_socket架設HttpServer
*
* @author LEADERG
*/
using namespace cv;
using namespace std;


Mat getMat(){
    Mat image;
#if defined(RI_PI) || RI_LINUX
    if(useUSBcam==0){
        Camera.grab();
        Camera.retrieve (image);
    }else{
        image=cvQueryFrame(cvcap);
        //   image=cv::Mat(iplimg).clone();
    }
#endif
    return image.clone();

}

#ifdef __cplusplus
extern "C"
{
#endif


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define SPI	0
#define I2C 1
#undef INTERFACE
#define INTERFACE SPI
#define DMP 0
#define RAW 1
#define MPU6050 DMP
#define STABLE_MODE 0
#define CAMERA_MODE 1

#if INTERFACE == SPI
    static const char *devName = "/dev/spidev0.0";
    static uint8_t spi_mode;
    static uint8_t bits = 8;
    static uint32_t speed = 500000;
    static uint16_t spi_delay;
#elif INTERFACE == I2C
    static const char *devName = "/dev/i2c-1";
    //#define ADDRESS	0x04
#endif

#if MPU6050 == DMP
#define DELTA_ERROR 0.01
#define CALICNT 500
    // MPU control/status vars
    bool dmpReady = false;  // set true if DMP init was successful
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer

    // orientation/motion vars
#if defined(RI_LINUX) || RI_PI
    Quaternion q;           // [w, x, y, z]         quaternion container
    VectorInt16 aa;         // [x, y, z]            accel sensor measurements
    VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
    VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
    VectorFloat gravity;    // [x, y, z]            gravity vector
#endif
    float euler[3];         // [psi, theta, phi]    Euler angle container
    float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and
    float delta_ang_yaw = 0;
    float delta_ang_pitch = 0;
    float delta_ang_roll = 0;
    float yaw_init = 0;
    float pitch_init = 0;
    float roll_init = 0;
    float old_yaw = 0;
    float current_yaw = 0;
    int caliCnt = CALICNT;
#endif

    //0306 add sevro
    //form iron
    void control_event(int sig);
    int DELAY_MS = 10;
    int PWM_PIN1 = 4;
    int PWM_PIN2 = 5;
    int default_servo_ang1 = 90;
    int default_servo_ang2 = 90;
    int fd_server_socket, fd_client_socket;
    int len_server, len_client;
    int servo_motor_ready = 0;
    //0306 add end
    int servo_ang1 = 0;
    int servo_ang2 = 0;
    int dc_left =  0;
    int dc_right = 0;
    int fd_i2c;
    int fd_spi;
    int fd_uart;
    bool isServoDataReady = false;
    //pthread_mutex_t mutex_servo_angle;
	HANDLE mutex_servo_angle;
    int camera_mode =  STABLE_MODE;
    /**
    * 影片暫存檔存在SD卡的路徑
    */
    const char *saveTo;
    /**
    * 影片檔所在Server的IP(MinistationAir2的IP)
    */
    const char *serverIP;
    /**
    * 續傳功能使用。記錄各chunk的下載狀態
    */
    char *chunksArray;
    /**
    * 目標影片檔案有幾MB
    */
    int howManyMb;
    /**
    * 影片檔是新的，還是上次沒下載完的。1= 新檔案 0=有暫存檔
    */
    int isNewFile; //1= 新檔案 0=有暫存檔
    /**
    * 影片檔案有幾byte
    */
    ri_int64 tarFileSize; //135824942  7880399 78324274 78643200
    /**
    * 正在下載目標影片檔的第幾個chunk
    */
    int downloadWhere;
    /**
    * 避免同一檔案同時被讀寫產生error，在讀寫影片檔時使用的鎖
    */
    RiLock_t *chunkLock;
    /**
    * 影片檔所在server的port(MinistationAir2的port)
    */
    int port; //這個port是遠端server的port
    /**
    * 影片檔案在server上的路徑
    */
    const char* address;


    /**
    * LocalServer運作狀態，0=未啟動 1=啟動中 2=運行中 3=結束中
    */
    int runningStatus;//0=未啟動 1=啟動中 2=運行中 3=結束中
    /**
    * 影片暫存檔是否已設置完成(分配空間並以FILE指標開啟，處於可以讀寫的狀態)。
    */
    int fileSetOK;//0115增加....file建立完成才能開始上傳
    /**
    * LocalServer的Socket
    */
    RiSocket_t *localSocket;

    /**
    * LocalServerd開在哪個port
    */
    int localServerPort;


    /**
    * 測試用功能。切換LocalServer模式。0=中斷模式，1=連續運行模式。
    */
    int initTest;
    /**
    * 是否正在下載影片檔。1=正在下載 0=沒在下載
    */
    int isFileDownloading;



	HANDLE encCameraThread;





    /**
    * 此Library是否已經初始化
    */
    static int riHttpdIsInit = 0;
    //RiArray_t *imageArray = NULL;
    /**
    * 測試用功能，目前未使用
    */
    char *imageBuf;
    /**
    * 測試用功能，目前未使用
    */
    long imageSize;
    /**
    * 測試用功能，目前未使用
    */
    char *imageName;

    // 20140626: define db constants
    /**
    * 測試用功能，目前未使用
    */
#define dbHost "localhost"
    /**
    * 測試用功能，目前未使用
    */
#define dbDb "rc1"
    /**
    * 測試用功能，目前未使用
    */
#define dbUserName "root"
    /**
    * 測試用功能，目前未使用
    */
#define dbPassword "xxxxxxxxxxx"

    /* 擷取系統時間*/
    long long getSystemTime() {
#if defined(RI_LINUX)
        struct timeb t;
        ftime(&t);
        return 1000 * t.time + t.millitm;
#elif defined(RI_WINDOWS)
        SYSTEMTIME t;
        GetSystemTime(&t);
        return 1000 * t.wSecond + t.wMilliseconds;
#endif
    }
    int cameraRunning = 1;

    char *jpg = NULL;
    int jpgSize;

    void testjpg(){
        FILE *f=fopen("/home/pi/Desktop/a0.jpg", "rb");

        fseek(f, 0, SEEK_END);
        jpgSize = ftell(f);
        fseek(f, 0, SEEK_SET);
        RI_LOGI("jpgSize=%d",jpgSize);

        jpg=(char *)malloc(jpgSize);
        fread(jpg, sizeof(char), jpgSize, f);
        fclose(f);
        //ret = RiSocket_Send(sockClient, (ri_byte *) fileData, (int) isRead,0);

    }
    int useUSBcam=0;

#if defined(RI_PI) || RI_LINUX
    raspicam::RaspiCam_Cv Camera;
    CvCapture *cvcap;
#endif


    int rasp_camera_open(){
        /*
        if ( !Camera.open()) {cerr<<"Error opening camera"<<endl;return -1;}
        return 1;
        */#if defined(RI_PI) || RI_LINUX

        Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
    Camera.set( CV_CAP_PROP_FRAME_WIDTH, 640 );
    Camera.set( CV_CAP_PROP_FRAME_HEIGHT,480 );
    Camera.set(CV_CAP_PROP_FPS,40);
    //  cout<<"Opening Camera..."<<endl;
    if (!Camera.open()) {
        RI_LOGI("Camera open ERR");
        //0320 useUSBcam
        cvcap=cvCaptureFromCAM(0);
        cvSetCaptureProperty(cvcap,CV_CAP_PROP_FRAME_WIDTH,640);
        cvSetCaptureProperty(cvcap,CV_CAP_PROP_FRAME_HEIGHT,480);
        cvSetCaptureProperty(cvcap,CV_CAP_PROP_FPS,40);
        cvSetCaptureProperty( cvcap,CV_CAP_PROP_FORMAT, CV_8UC3 );
        cameraRunning=1;
        useUSBcam=1;
        return -1;

    }else{
        useUSBcam=0;
    }
    cameraRunning=1;
#endif
    return 0;
    }

    int rasp_camera_close(){
#if defined(RI_PI) || RI_LINUX
        if(useUSBcam==0){
            Camera.release();
        }else{
            cvReleaseCapture(&cvcap);
        }
#endif
        //0317add 0326move
        //cameraRunning=0;
        return 0;
    }


    int fcount=0;



    int rasp_getjpg(char *mjpg){
#if defined(RI_PI) || RI_LINUX
        char *fname = (char*)malloc(100);
        sprintf(fname, "c%d.jpg",fcount);
        fcount++;
        /*
        char *ccmd = (char*)malloc(1024);

        sprintf(ccmd, "raspistill -n -q 70 -w 176 -h 144 -t 2 -o c%d.jpg",fcount);
        //sprintf(ccmd, "raspistill -n -q 70 -w 176 -h 144 -t 3000 -tl 0 -o c%04d.jpg");
        //-t 3000 -tl 1000 -o image%04d.jpg
        fcount++;

        system(ccmd);
        free(ccmd);
        */


        cv::Mat image;
        Camera.grab();
        Camera.retrieve (image);

        cv::imwrite(fname,image);




        if(mjpg){
            free(mjpg);
            mjpg=NULL;
        }
        int jpgSize=0;
        FILE *f=fopen(fname, "rb");

        fseek(f, 0, SEEK_END);
        jpgSize = ftell(f);
        fseek(f, 0, SEEK_SET);
        RI_LOGI("jpgSize=%d",jpgSize);

        mjpg=(char *)malloc(jpgSize);
        fread(mjpg, sizeof(char), jpgSize, f);
        fclose(f);

        free(fname);
        return jpgSize;
#endif
        return 1;
    }



    char * getjpg2(int & ss){
#if defined(RI_PI) || RI_LINUX
        fcount++;
        RI_LOGI("grab:%d",fcount);
        cv::Mat image;
        Camera.grab();
        Camera.retrieve (image);
        cv::vector<uchar> buf;
        cv::imencode(".jpg", image, buf, std::vector<int>() );
        char * imageBuf = ( char *) malloc(buf.size());
        ri_memcpy(imageBuf, &buf[0], buf.size());
        ss=buf.size();
        RI_LOGI("encImgSize=%d",ss);
        return imageBuf;
#endif

    }





    //add 0317

    RiSemaphore_t *sem;
    HANDLE thr[4];
    int SEM_NUM=4;



    //cv::Mat timg;

    //int ii0326=0;



    RiLock_t * glock;
    int testt=0;
    char *jpgBuffer=NULL;
    //edit 0325
    char *img_send_ip="192.168.8.104";//192.168.1.207
    //int jpgSize=0;
    void img_cb(char *img,int size){
        RI_LOGI("size----%d",size);
        // clientSocket("192.168.8.90",3456,img,size);
        // clientSocket("192.168.1.205",3456,img,size);
        clientSocket(img_send_ip,3456,img,size);//lesderg2 asus
        //clientSocket("192.168.8.104",3456,img,size);//leaderg asus

        //edit 0325 end
        /*
        RiLock_Lock(glock);
        if(jpgBuffer){
        free(jpgBuffer);
        jpgBuffer=NULL;
        }
        jpgBuffer = ( char *) malloc( size);
        ri_memcpy(jpgBuffer, img,size);
        jpgSize=size;
        RiLock_Unlock(glock);
        */
        return;
    }


    //void* encCamera(void *arg) {
	DWORD WINAPI encCamera(void *arg) {

        int ss=0;
        testt++;
        cv::Mat image=*(cv::Mat*)arg;
        vector<uchar> buf;
        cv::imencode(".jpg", image, buf, std::vector<int>() );
        //char *fname = (char*)malloc(100);
        //sprintf(fname, "c%d.jpg",testt);
        //cv::imwrite(fname,image);
        char * imageBuf = ( char *) malloc(buf.size());
        ri_memcpy(imageBuf, &buf[0], buf.size());
        ss=(int)buf.size();
        RI_LOGI("%d_encImgSize=%d",testt,ss);
        //callback test
        void (*cb_ptr)(char *,int );
        cb_ptr=img_cb;
        (*cb_ptr)(imageBuf,ss);

        free(imageBuf);
        RiSemaphore_Unlock(sem);



        //***0317 thread should detach after use
       // pthread_detach(pthread_self());
		
		CloseHandle(encCameraThread);
		return 0;
		//     return ((void *)0);
    }

    /**
    * @brief 大寫轉小寫
    * 測試用功能，目前未使用
    */
    void urldecode2(char *dst, const char *src) {
        char a, b;
        while (*src) {
            if ((*src == '%') && ((a = src[1]) && (b = src[2])) && (isxdigit(a)
                && isxdigit(b))) {
                    if (a >= 'a')
                        a -= 'a' - 'A';
                    if (a >= 'A')
                        a -= ('A' - 10);
                    else
                        a -= '0';
                    if (b >= 'a')
                        b -= 'a' - 'A';
                    if (b >= 'A')
                        b -= ('A' - 10);
                    else
                        b -= '0';
                    *dst++ = 16 * a + b;
                    src += 3;
            } else {
                *dst++ = *src++;
            }
        }
        *dst++ = '\0';
    }


    /**
    * @brief 初始化此Library
    *
    * @return 成功回傳1，否則回傳錯誤碼
    */
    RI_API int riHttpd_InitLib() {
        if (riHttpdIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riHttpdIsInit = 1;

#if defined(RI_HTTPD_OPEN_SSL)
        // Initializing the ssl library.
        SSL_library_init();
        SSL_load_error_strings();
        ERR_load_BIO_strings();
        OpenSSL_add_all_algorithms();

        // Need to add ctx to the header file so it can be freed when the program finishes execution.
        /*
        // Set up connection
        SSL_CTX *ctx;
        ctx = SSL_CTX_new(SSLv23_server_method());
        if (!ctx) {
        ERR_print_errors_fp(stderr);
        return RI_ERROR;
        }

        // Load server certificate into the SSL context
        if (SSL_CTX_use_certificate_file(ctx, "gt_httpd.crt", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return RI_ERROR;
        }

        // Load the server private-key into the SSL context
        if (SSL_CTX_use_PrivateKey_file(ctx, "gt_httpd.key", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return RI_ERROR;
        }

        // Check if the server certificate and private-key matches.
        if (!SSL_CTX_check_private_key(ctx)) {
        fprintf(stderr,"Private key does not match the certificate public key\n");
        return RI_ERROR;
        }
        */

#endif

        return RI_OK;
    }

    //20150116 edit by Leo

    //int initTest = 1;//0121 add

    /**
    * @brief 取得目標檔案大小
    */
    ri_int64 getFileSize() {

        RI_LOGI("Test4");

        int port = 5080;
        int i = 0;

        ri_int64 ret;

        RI_LOGI("url=%s",serverIP);

        //建立連線
        RiSocket_t *sock = RiSocket_New();
        //20150116增加..timeOut機制
        ret = RiSocket_Open_With_TimeOut(sock, RI_SOCKET_AF_INET,
            RI_SOCKET_SOCK_STREAM, RI_SOCKET_IPPROTO_TCP, 6);
        ret = RiSocket_SetAddressIn(sock, (ri_utf8 *) serverIP, port);
        ret = RiSocket_Connect(sock);
        if (ret == RI_ERROR) {
            RI_LOGE("連線失敗");
            RiSocket_Free(sock);
            return -6;
        }
        //省略取得檔案大小步驟.....
        //	ri_int64 tarFileSize=7880399;
        RI_LOGI("連線OK");
        ///home/pi/Desktop/workspace/test1/openri/src/gt_httpd.cpp|197|error: invalid conversion from ‘void*’ to ‘char*’ [-fpermissive]|
        char* buffer = (char*)malloc(1024);
        ri_int64 downloadSize = 0;
        ri_int64 contentLength = 0;
        char *tarContentLength = NULL;
        char *tarContentLengthTell = NULL;
        char strTag[] = "Content-Length: ";
        //	char *httpGetMsg = "GET /live/streams/temp2.mp4 HTTP/1.1\r\n"
        //		"Host: 192.168.8.140:5080\r\n"
        //		"Connection: close\r\n"
        //		"Accept: */*\r\n"
        //		"Accept-Encoding: gzip, deflate, sdch\r\n"
        //		"\r\n";
        char *httpGetMsg = (char*)malloc(1024);
        sprintf(httpGetMsg, "GET %s HTTP/1.1\r\n"
            "Host: %s:%d\r\n"
            "Connection: close\r\n"
            "Accept: */*\r\n"
            "Accept-Encoding: gzip, deflate, sdch\r\n"
            "\r\n", address, serverIP, port);

        //	GET /live/streams/ HTTP/1.1
        //	Host: 192.168.8.140:5080
        //	Connection: keep-alive
        //	Cache-Control: max-age=0
        //	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
        //	User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36
        //	Accept-Encoding: gzip, deflate, sdch
        //	Accept-Language: zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4

        //	RI_LOGI("RiSocket_Send \n%s\n%d",httpGetMsg,httpGetMsgSize);
        ret = RiSocket_Send(sock, (ri_byte *) httpGetMsg, (int)strlen(httpGetMsg), 0);

        if (ret <= 0) {
            RI_LOGE("RiSocket_Send ERR= %lld\n", ret);
            return -6;
        }
        RI_LOGI("RiSocket_Recv");

        ret = (ri_int64) RiSocket_Recv(sock, (ri_byte *) buffer, 1024, 0);

        RI_LOGI("RiSocket_RecvOK:\n%s",buffer);

        //0116增加...404 Not Found判斷

        if (strstr(buffer, "404 Not Found")) {
            RI_LOGI("404 Not Found");
            return -1;
        }

        //0108測試....拆字串拆出 Content-Length然後轉ri_int64儲存。總之先試試在c拆，真的不行的話再傳給java處理


        tarContentLength = strstr(buffer, strTag);
        if (tarContentLength) {
            tarContentLength += strlen(strTag);
            tarContentLengthTell = strstr(tarContentLength, "\n");
            //strncpy	將字串 s2 最多 n 個字元拷貝到 s1	char *strncpy(char *s1, const char *s2, size_t n);
            char *ContentLengthString = (char*)malloc((int) (tarContentLengthTell
                - tarContentLength));
            strncpy(ContentLengthString, tarContentLength,
                (int) (tarContentLengthTell - tarContentLength));
            //		RI_LOGI("ContentLengthString=\n%s \n%d \n%s",ContentLengthString,strlen(ContentLengthString),tarContentLengthTell);
            contentLength = atoi(ContentLengthString);//atoi抓整數，atof抓小數
            RI_LOGI("長度為%lld",contentLength);
        }

        //	RiSocket_Close(sock);發現Free會呼叫Close....
        RiSocket_Free(sock);

        if (httpGetMsg) {
            free(httpGetMsg);
            httpGetMsg = NULL;
        }
        if (buffer) {
            free(buffer);
            buffer = NULL;
        }
        return contentLength;

    }

    /**
    * @brief 下載影片檔案的目標區塊
    * @param where
    *         該區塊為第幾MB
    * @param sock
    *         與影片所在網址連線的RiSocket
    * @param fp
    *         影片暫存檔的指標
    * @return 2=下載完成 0=下載失敗
    */
    short getChunk(int where, RiSocket_t *sock, FILE *fp) {
        //	RI_LOGI("getChunk++");
        char msg[1024];
        short ret = 2;
        int i = 0;
        //	char buffer[1024 * 1024 * 2];  //這邊有時候會oom......給小一點好了
        char buffer[10240];
        fseek(fp, where * 1024L * 1024, 0);
        ri_int64 downloadSize = 0;
        ri_int64 start, end;
        start = where * 1024 * 1024;
        end = (where + 1) * 1024 * 1024 - 1;
        sprintf(msg, "GET %s HTTP/1.1\r\n"
            "Host: %s:%d\r\n"
            "Cache-Control: max-age=0\r\n"
            "Accept: */*\r\n"
            "User-Agent: GTHTTP\r\n"
            "Accept-Encoding: gzip, deflate, sdch\r\n"
            "Range: bytes=%lld-%lld\r\n"
            "\r\n", address, serverIP, port, start, end);

        //	RI_LOGI("g4");
        //	RI_LOGI("下載檔案開始:%s",msg);

        ri_int64 recvSize = 0;
        recvSize = RiSocket_Send(sock, (ri_byte *) msg, (int)strlen(msg), 0);
        //	RI_LOGI("RiSocket_Send:%lld",recvSize);
        //	RI_LOGI("sizeof(buffer):%d",sizeof(buffer));
        //	return;
        recvSize = RiSocket_Recv(sock, (ri_byte *) buffer, sizeof(buffer), 0);
        if (recvSize <= 0) {
            RI_LOGE("RiSocket_Recv = %lld\n", recvSize);
            //	 		return 1;
        } else {
            //		RI_LOGI("RiSocket_Recv = %lld\n", recvSize);
        }
        //	RI_LOGE("RiSocket_Recv = %s\n", buffer);
        int cut = 0;
        //			RI_LOGE("GET:%s\n", buffer);
        ri_int64 size = 1;

        int times = 0;
        char strTag[] = "Content-Length: ";//目標標籤Content-Length:
        ri_int64 contentLength = 1048576; //總之預設一輪抓1mb
        char *tarContentLength = NULL; //記錄收到訊息中，Content-Length的位置
        char *tarContentLengthTell = NULL; //記錄收到訊息中，Content-Length這行的尾巴
        tarContentLength = strstr(buffer, strTag);
        if (tarContentLength) {
            tarContentLength += strlen(strTag);
            tarContentLengthTell = strstr(tarContentLength, "\n");
            char *ContentLengthString = (char*)malloc((int) (tarContentLengthTell
                - tarContentLength));
            strncpy(ContentLengthString, tarContentLength,
                (int) (tarContentLengthTell - tarContentLength));
            //		RI_LOGI("ContentLengthString=\n%s \n%d \n%s",ContentLengthString,strlen(ContentLengthString),tarContentLengthTell);
            contentLength = atoi(ContentLengthString);//atoi抓整數，atof抓小數
            //		RI_LOGI("長度為%lld",contentLength);

            if (ContentLengthString) {
                free(ContentLengthString);
                ContentLengthString = NULL;
            }
        }

        char *tarChar = NULL;
        //	RI_LOGI("T1");
        tarChar = strstr(buffer, "\r\n\r\n");
        if (tarChar) {
            //		RI_LOGI("T2");
            tarChar += 4;
            fwrite(tarChar, 1, recvSize - (tarChar - buffer), fp);
            downloadSize += recvSize - (tarChar - buffer);
            //		RI_LOGI("T3");
        }
        //	RI_LOGI("T4");
        while (size > 0 && downloadSize < contentLength && (runningStatus == 2
            || runningStatus == 1)) {
                //		RI_LOGI("T5");
                size = RiSocket_Recv(sock, (ri_byte *) buffer, sizeof(buffer), 0);
                //		RI_LOGI("T6");
                fwrite(buffer, 1, size, fp);
                //		RI_LOGI("T7");
                downloadSize += size;
                //		RI_LOGE("GET2:times=%d size=%lld,(%lld)\n",times,size, downloadSize);
                //	RI_LOGE("GET2:%s\n", buffer);
                times++;
        }

        //	RI_LOGI("getChunk--");
        if (downloadSize >= contentLength) {
            return 2;
        } else {
            RI_LOGE("區塊%d下載失敗",where);
            return 0;
        }
    }

    /**
    * @brief LocalServer的下載端。下載目標影片檔案的Thread，會經由runLocalServer啟動
    */
    DWORD WINAPI downloadThread(void *) {
        RI_LOGI("test4");
        isFileDownloading = 1;
        //	char msg[1024];
        //	char* address = "/live/streams/temp.mp4";
        //	char* address = "/live/streams/txt2.mp4";

        int i = 0;

        //1.首先...連線
        int ret = 0;
        RiSocket_t *sock = RiSocket_New();
        ret = RiSocket_Open(sock, RI_SOCKET_AF_INET, RI_SOCKET_SOCK_STREAM,
            RI_SOCKET_IPPROTO_TCP);

        ret = RiSocket_SetAddressIn(sock, (ri_utf8 *) serverIP, 5080);

        ret = RiSocket_Connect(sock);
        //省略取得檔案大小步驟.....
        //	ri_int64 tarFileSize=7880399;
        RI_LOGI("連線OK");

        //2.建立檔案
        RI_LOGI("建立檔案開始");
        FILE *fp;
        //	int howManyMb = 100;
        howManyMb = (int) (tarFileSize / 1024L / 1024 + 1);
        if (isNewFile) {
            //		howManyMb = tarFileSize / 1024 / 1024 + 1; //若他檔案剛好整數mb，就讓它再多1mb
            RI_LOGI("howManyMb:%d",howManyMb);

            fp = fopen(saveTo, "wb");
            if (!fp) {
                RI_LOGI("檔案開啟失敗！！%s",saveTo);
            }
            char* tmp = (char*)calloc(1, 1024 * 1024);
            for (i = 0; i < howManyMb; i++) {
                fwrite(tmp, 1, 1024 * 1024, fp);
            }
            if (tmp) {
                free(tmp);
                tmp = NULL;
            }
            fseek(fp, 0L, 0);
        } else {
            //		//0122測試出來最花時間的是這一段.....
            //		RI_LOGI("搬移檔案開始");
            //		char *tempPath = calloc(512, sizeof(char));
            //		sprintf(tempPath, "%s%s", saveTo, ".re");
            //		rename(saveTo, tempPath);
            //		FILE *ftp;
            //		ftp = fopen(tempPath, "rb");
            //		fp = fopen(saveTo, "wb");
            //		char* tmp = calloc(1, 1048576);
            //		char* tmpcmpty = calloc(1, 1048576);
            //		long long readSize = 1;
            //		RI_LOGI("準備複製");
            //		int where = 0;
            //		//0126測試....1次20mb看看會不會比較快....結果沒差
            //		//		while (readSize > 0) {
            //		////			RI_LOGI("複製第%d chunk,該chunk為%hd",where,chunksArray[where]);
            //		//			RI_LOGI("複製第%d輪",where);
            //		//			readSize = fread(tmp, 1, 1048576, ftp);
            //		//			if (readSize > 0) {
            //		//				fwrite(tmp, 1, readSize, fp);
            //		//			}
            //		//			where++;
            //		//		}
            //		//0123測試.....未下載區塊用填充的方式
            //		for (where = 0; where < howManyMb; where++) {
            //			if (chunksArray[where] == 2) {
            //				//				RI_LOGI("複製第%d chunk,該chunk為%hd",where,chunksArray[where]);
            //				readSize = fread(tmp, 1, 1048576, ftp);
            //				if (readSize > 0) {
            //					fwrite(tmp, 1, readSize, fp);
            //				} else {
            //					//某mb讀入失敗時，該mb填空的，然後設定成未下載
            //					chunksArray[where] = 0;
            //					fwrite(tmpcmpty, 1, 1048576, fp);
            //					fseek(ftp, 1048576L * (where + 1), 0);
            //				}
            //			} else {
            //				//				RI_LOGI("填充第%d chunk,該chunk為%hd",where,chunksArray[where]);
            //				fwrite(tmpcmpty, 1, 1048576, fp);
            //				fseek(ftp, 1048576L * (where + 1), 0);
            //			}
            //		}
            //		RI_LOGI("複製完畢");
            //		fclose(ftp);
            //		remove(tempPath);
            //		if (tmp) {
            //			free(tmp);
            //			tmp = NULL;
            //		}
            //		if (tmpcmpty) {
            //			free(tmpcmpty);
            //			tmpcmpty = NULL;
            //		}
            //		fseek(fp, 0L, 0);
            //		RI_LOGI("搬移檔案OK");

            //0126下午測試....看看有沒有fopen參數可以支援續寫
            //測試結果....rb+可以續寫。太好了，省下複製檔案的時間。

            fp = fopen(saveTo, "rb+");
            fseek(fp, 0L, 0);
        }

        //	short chunksArray[howManyMb];
        if (!chunksArray) {
            chunksArray = (char*)calloc(sizeof(short), howManyMb);
        }
        RI_LOGI("建立檔案OK:%dMB",howManyMb);
        fileSetOK = 1;
        if (initTest) {
            runningStatus = 2;
        }
        //3.下載
        //	chunksArray[0] = getChunk(0, sock, fp);
        //	chunksArray[3] = getChunk(3, sock, fp);
        //	chunksArray[4] = getChunk(4, sock, fp);
        //	chunksArray[1] = getChunk(1, sock, fp);
        //	chunksArray[2] = getChunk(2, sock, fp);
        //	chunksArray[5] = getChunk(5, sock, fp);
        //	chunksArray[6] = getChunk(6, sock, fp);
        //	chunksArray[7] = getChunk(7, sock, fp);

        //	for (i = 0; i < howManyMb; i++) {
        //		if (chunksArray[i] == 0) {
        //			chunksArray[i] == 1;
        //			chunksArray[i] = getChunk(i, sock, fp);
        //		} else if (chunksArray[i] == 1) {
        //			RI_LOGI("chunks%d下載中",chunksArray[i]);
        //		} else {
        //			RI_LOGI("chunks%d已下載",chunksArray[i]);
        //		}
        //	}

        //0113測試 跳躍式下載
        while (runningStatus == 2 || runningStatus == 1) {
            RiLock_Lock(chunkLock);
            if (downloadWhere < 0)
                downloadWhere = 0;
            downloadWhere %= howManyMb;
            RiLock_Unlock(chunkLock);

            if (chunksArray[downloadWhere] == 0) {
                RI_LOGI("chunks%d開始下載",downloadWhere);
                RiLock_Lock(chunkLock);
                //			RI_LOGI("c1");
                chunksArray[downloadWhere] = 1;
                //			RI_LOGI("c2");
                RiLock_Unlock(chunkLock);
                //			RI_LOGI("c3");
                chunksArray[downloadWhere] = (char)getChunk(downloadWhere, sock, fp);
                //			RI_LOGI("c4");
                if (!chunksArray) {
                    RI_LOGI("chunksArray已被釋放，結束下載程序");
                    break;
                } else {
                    int sum;
                    sum = 0;
                    for (i = 0; i < howManyMb; i++) {
                        if (chunksArray[i] == 2) {
                            sum++;
                        }
                    }
                    if (sum >= howManyMb) {
                        break;
                    }
                }
                //			RI_LOGI("c5");
            } else if (chunksArray[downloadWhere] == 1) {
                RI_LOGI("chunks%d下載中",downloadWhere);
            } else {
                //			RI_LOGI("chunks%d已下載",downloadWhere);
            }
            RiLock_Lock(chunkLock);
            downloadWhere++;
            RiLock_Unlock(chunkLock);
        }

        fclose(fp);
        RI_LOGI("下載檔案OK");
        //最後...關閉連線
        RiSocket_Free(sock);
        RI_LOGI("關閉連線OK");
        isFileDownloading = 0;
        return 0;
    }

    /**
    * @brief 舊版的LocalServer的上傳端。目前未使用。
    */
    DWORD WINAPI uploadThread(void *) {

        RI_LOGI("test6");

        //temp 0113
        howManyMb = (int)(tarFileSize / 1024L / 1024 + 1);

        // TCP server
        int ret = 0;
        int backLog = 3;
        char buffer[2048];
        RiSocket_t *sockClient;

        localSocket = RiSocket_New();

        ret = RiSocket_Open(localSocket, RI_SOCKET_AF_INET, RI_SOCKET_SOCK_STREAM,
            RI_SOCKET_IPPROTO_TCP);
        if (ret <= 0) {
            RI_LOGI("RiSocket_Init = %d\n", ret);
            return NULL;
        }

        //20150116增加.....連續Bind測試避免端口被吃掉....試200個應該夠
        int i = 0;
        for (i = 0; i < 200; i++) {

            ret = RiSocket_SetAddressIn(localSocket, (ri_utf8 *) "INADDR_ANY",
                localServerPort);

            if (ret <= 0) {
                RI_LOGI("RiSocket_SetAddressIn = %d\n", ret);
                return NULL;
            }

            ret = RiSocket_Bind(localSocket);
            if (ret <= 0) {
                RI_LOGI("RiSocket_Bind = %d\n", ret);
                localServerPort++;
            } else {
                RI_LOGI("localServer端口開啟： = %d\n", localServerPort);
                break;
            }
        }

        ret = RiSocket_Listen(localSocket, backLog);
        if (ret <= 0) {
            RI_LOGI("RiSocket_Listen = %d\n", ret);
            return NULL;
        }

        char *response = (char*)calloc(12 * 1024, sizeof(char));
        char *response2 = (char*)calloc(12 * 1024, sizeof(char));
        int len;

        char ret_strings[] = "return OK";

        //0112讀出file...先讀個2048kb
        FILE *fp = NULL;
        char *fileData = (char*)calloc(1024 * 16, sizeof(char));

        //0105 Content-Type使用video/*好像會導致瀏覽器只下載不播放?但VideoView卻可正常播放
        sprintf(response, "HTTP/1.1 200 OK\r\n"
            "Server: Apache-Coyote/1.1\r\n"
            "Accept-Ranges: bytes\r\n"
            "Content-Type: video/mp4\r\n"
            "Content-Length: %lld\r\n"
            "\r\n", tarFileSize);

        sprintf(response2, "HTTP/1.1 206 Partial Content\r\n"
            "Server: Apache-Coyote/1.1\r\n"
            "Accept-Ranges: bytes\r\n"
            "Content-Range: bytes 0-%lld/%lld\r\n"
            "Content-Type: video/mp4\r\n"
            "Content-Length: %lld\r\n"
            "\r\n", tarFileSize - 1, tarFileSize, tarFileSize);

        int isfirst = 1;
        ri_int64 sendSize;

        //0115 開始上傳前...先等file建立好
        //0120要改"運行App後，即自動啟動本地Server"，這著讓這邊不等待...但結果非常糟。所以還是繼續保持等待
        while (fileSetOK == 0) {
            RI_LOGI("等待fileSet...\n");
#if defined(RI_LINUX)
            sleep(2);
#elif defined(RI_WINDOWS)
            Sleep(2000);
#endif
        }
        RI_LOGE("確認File已Set:%d",fileSetOK);
        while (runningStatus == 2 || runningStatus == 1 || runningStatus == 0) {
            RI_LOGI("server RUN...\n");

            if (runningStatus == 1) {
                RI_LOGI("發現下載動作啟動==LocalServer進入運行狀態");
                runningStatus = 2;
            }
            sockClient = RiSocket_Accept(localSocket);

            RI_LOGI("server Accept");
            if (runningStatus == 1) {
                RI_LOGI("發現下載動作啟動==LocalServer進入運行狀態");
                runningStatus = 2;
            }

            if (runningStatus != 2 && runningStatus != 0) {
                RI_LOGI("local server中斷...\n");
                break;
            }

            RI_LOGI("cnnect from %s\n",inet_ntoa(localSocket->addr_in.sin_addr));

            ret = RiSocket_Recv(sockClient, (ri_byte *) buffer, sizeof(buffer), 0);
            if (ret <= 0) {
                RI_LOGI("RiSocket_Recv = %d\n", ret);
            }
            RI_LOGI("recv message: %s\n", buffer);

            RI_LOGI("chunksArray判斷");
            //0113 第0chunk必需已下載才開始讓它播放
            while (chunksArray == NULL || chunksArray[0] != 2) {
                RI_LOGE("等待取得影片標頭檔\n");
                if (runningStatus == 0) {
                    RI_LOGI("下載動作未啟動===省略chunksArray判斷");
                    break;
                } else if (runningStatus != 2) {
                    RI_LOGI("local server中斷...\n");
                    break;
                }
#if defined(RI_LINUX)
                sleep(2);
#elif defined(RI_WINDOWS)
                Sleep(2000);
#endif
            }

            if (runningStatus == 0) {
                char nullReturn[] = "HTTP/1.1 423 Locked\r\n"
                    "Server: Apache-Coyote/1.1\r\n"
                    "Content-Type: text/html;charset=utf-8\r\n"
                    "Content-Length: 5\r\n"
                    "\r\n"
                    "NULL\0";
                RiSocket_Send(sockClient, (ri_byte *) nullReturn,
                    sizeof(nullReturn), 0);
                RI_LOGI("local server等待中...回傳null");
                continue;
            }

            /////////
            ri_int64 downloadSize = 0;
            ri_int64 rangeSt = 0;
            ri_int64 rangeEd = 0;
            char *tarContentLength = NULL;
            char *tarContentLengthTell = NULL;
            char strTag[] = "Range: bytes=";
            char strTag2[] = "-";
            //0113測試....拆Range

            tarContentLength = strstr(buffer, strTag);
            if (tarContentLength) {
                tarContentLength += strlen(strTag);
                tarContentLengthTell = strstr(tarContentLength, "\n");
                //strncpy	將字串 s2 最多 n 個字元拷貝到 s1	char *strncpy(char *s1, const char *s2, size_t n);
                char *ContentLengthString = (char*)malloc((int) (tarContentLengthTell
                    - tarContentLength));
                strncpy(ContentLengthString, tarContentLength,
                    (int) (tarContentLengthTell - tarContentLength));
                //			RI_LOGI("ContentLengthString=\n%s \n%d \n%s",ContentLengthString,strlen(ContentLengthString),tarContentLengthTell);
                rangeSt = atoi(ContentLengthString);//atoi抓整數，atof抓小數
                RI_LOGI("RANGE_ST為%lld",rangeSt);
                tarContentLength = strstr(ContentLengthString, strTag2);
                if (tarContentLength) {
                    tarContentLength += strlen(strTag2);
                    rangeEd = atoi(tarContentLength);
                    RI_LOGI("RANGE_ED為%lld",rangeEd);
                } else {
                    RI_LOGI("RANGE_ED未取得");
                }

                if (ContentLengthString) {
                    free(ContentLengthString);
                    ContentLengthString = NULL;
                }

                sprintf(response2, "HTTP/1.1 206 Partial Content\r\n"
                    "Server: Apache-Coyote/1.1\r\n"
                    "Accept-Ranges: bytes\r\n"
                    "Content-Range: bytes %lld-%lld/%lld\r\n"
                    "Content-Type: video/mp4\r\n"
                    "Content-Length: %lld\r\n"
                    "\r\n", rangeSt, tarFileSize - 1, tarFileSize, tarFileSize
                    - rangeSt);

                len = (int) strlen(response2);
                RiSocket_Send(sockClient, (ri_byte *) response2, len, 0);
                RI_LOGE("SEND_%s",response2);

            } else {
                RI_LOGI("沒收到RANGE!!!回200OK");
                len = (int) strlen(response);
                RiSocket_Send(sockClient, (ri_byte *) response, len, 0);
                RI_LOGE("SEND_%s",response);
                //						continue;
            }
            ////////


            //		len = (int) strlen(response);
            //		RiSocket_Send(sockClient, (ri_byte *) response, len, 0);

            sendSize = 0;
            long long tempsend = 0;

            while (!fp) {
                fp = fopen(saveTo, "rb");
                if (fp == NULL) {
                    RI_LOGE("open input file fail!saveTo=%s",saveTo);
#if defined(RI_LINUX)
                    sleep(2);
#elif defined(RI_WINDOWS)
                    Sleep(2000);
#endif//每兩秒嘗試一次開啟檔案
                }
            }
            //		fseek(fp, 0 * 1024L * 1024L, 0);
            fseek(fp, (long)rangeSt, 0);
            while (runningStatus == 2) {
                ri_int64 isRead = 0;
                //			int where = (int) ((sendSize) / 1024 / 1024);
                int where = (int) ((rangeSt + sendSize) / 1024 / 1024);
                if (where < 0)
                where = 0;
                if (where >= howManyMb) {
                    RI_LOGI("where>=howManyMb(%d)",where);
                    break;
                }
                while (chunksArray != NULL && chunksArray[where] != 2
                    //					&& 1 == 2
                    ) {
                        if (chunksArray[where] == 0) {
                            RiLock_Lock(chunkLock);
                            //這邊會有一格位移
                            downloadWhere = where - 1;
                            RiLock_Unlock(chunkLock);
                            RI_LOGI("強制下載目標區塊(%d)",where);
                        } else {
                            RI_LOGI("目標區塊(%d)下載中",where);
                        }
#if defined(RI_LINUX)
                        sleep(2);
#elif defined(RI_WINDOWS)
                        Sleep(2000);
#endif
                        if (runningStatus != 2) {
                            RI_LOGI("runningStage非2，中斷local server");
                            break;
                        }
                }

                //			RI_LOGE("fread:%lld",rangeSt);
                //31641894+16384 =
                isRead = fread(fileData, sizeof(char), 1024L * 16, fp);
                if (isRead <= 0) {
                    RI_LOGE("isRead<=0----%lld",isRead);
                    break;
                } else {
                }
                int ret = 0;
                ret = RiSocket_Send(sockClient, (ri_byte *) fileData, (int)isRead, 0);
                if (ret >= 0) {
                    tempsend += ret;
                } else {
                    RI_LOGE("RiSocket_Send_ret=%d",ret);
                    break;
                }
                int i = 0;
                //			RI_LOGI("目標區塊(%d)send完成====%lld",where,tempsend);
                sendSize += isRead;

            }
            RI_LOGI("send完成====");
            fclose(fp);
            if (fp) {
                fp = NULL;
            }
            buffer[ret] = 0;
            RI_LOGE("server One Round");
        }

        RI_LOGI("test6 RiSocket_Close");
        if (localSocket) {
            RiSocket_Free(sockClient);
            RiSocket_Free(localSocket);
            localSocket = NULL;
        }
        if (response) {
            free(response);
            response = NULL;
        }
        if (response2) {
            free(response2);
            response2 = NULL;
        }
        runningStatus = 0;
        RI_LOGI("test5 --");
        return 0;
    }

    /**
    * @brief LocalServer的上傳端。發送目標影片檔案的Thread，會經由initLocalServer啟動
    */
    DWORD WINAPI uploadThread2(void *) {

        RI_LOGI("test0120");
        //首先......檔案還沒下載所以相關參數的設定順序都要往後


        // TCP server
        int ret = 0;
        //允許同時3個連線....其實設1個就夠了....但測試時把算用瀏覽器連到手機，所以多開幾個
        int backLog = 3;
        char buffer[2048];
        RiSocket_t *sockClient;

        localSocket = RiSocket_New();

        ret = RiSocket_Open(localSocket, RI_SOCKET_AF_INET, RI_SOCKET_SOCK_STREAM,
            RI_SOCKET_IPPROTO_TCP);
        if (ret <= 0) {
            RI_LOGI("RiSocket_Init = %d\n", ret);
            return NULL;
        }

        //20150116增加.....連續Bind測試避免端口被吃掉....試200個應該夠
        int i = 0;
        for (i = 0; i < 200; i++) {

            ret = RiSocket_SetAddressIn(localSocket, (ri_utf8 *) "INADDR_ANY",
                localServerPort);

            if (ret <= 0) {
                RI_LOGI("RiSocket_SetAddressIn = %d\n", ret);
                return NULL;
            }

            ret = RiSocket_Bind(localSocket);
            if (ret <= 0) {
                RI_LOGI("RiSocket_Bind = %d\n", ret);
                localServerPort++;
            } else {
                RI_LOGE("localServer端口開啟： = %d\n", localServerPort);
                break;
            }
        }

        ret = RiSocket_Listen(localSocket, backLog);
        if (ret <= 0) {
            RI_LOGI("RiSocket_Listen = %d\n", ret);
            return NULL;
        }

        char *response = (char*)calloc(12 * 1024, sizeof(char));
        char *response2 = (char*)calloc(12 * 1024, sizeof(char));
        int len;

        char ret_strings[] = "return OK";

        //0112讀出file...先讀個2048kb
        FILE *fp = NULL;
        char *fileData = (char*)calloc(1024 * 16, sizeof(char));

        int isfirst = 1;
        ri_int64 sendSize;

        //0115 開始上傳前...先等file建立好

        RI_LOGE("確認File已Set:%d",fileSetOK);

        while (localSocket) {
            RI_LOGI("server RUN...\n");
            sockClient = RiSocket_Accept(localSocket);
            RI_LOGI("server Accept");

            if (!localSocket) {
                RI_LOGI("local server中斷B...\n");
                break;
            }
            RI_LOGE("Accept..");
            if (localSocket) {
                RI_LOGI("cnnect from %s\n",inet_ntoa(localSocket->addr_in.sin_addr));
            } else {
                RI_LOGE("NULL localSocket");
            }
            RI_LOGE("Before RiSocket_Recv");
            ret = RiSocket_Recv(sockClient, (ri_byte *) buffer, sizeof(buffer), 0);
            if (ret <= 0) {
                RI_LOGI("RiSocket_Recv = %d\n", ret);
            }
            RI_LOGI("recv message: %s\n", buffer);

            RI_LOGI("chunksArray判斷");
            //0113 第0chunk必需已下載才開始讓它播放
            while (chunksArray == NULL || chunksArray[0] != 2) {
                RI_LOGE("等待取得影片標頭檔\n");
                if (runningStatus == 0) {
                    RI_LOGI("下載動作未啟動===省略chunksArray判斷");
                    break;
                } else if (!localSocket) {
                    RI_LOGE("local server中斷A...\n");
                    break;
                }
#if defined(RI_LINUX)
                sleep(2);
#elif defined(RI_WINDOWS)
                Sleep(2000);
#endif
            }

            if (fileSetOK == 0) {
                //這邊改為....沒檔案就回423 lock
                char nullReturn[] = "HTTP/1.1 423 Locked\r\n"
                    "Server: Apache-Coyote/1.1\r\n"
                    "Content-Type: text/html;charset=utf-8\r\n"
                    "Content-Length: 22\r\n"
                    "\r\n"
                    "Server is waiting.....\0";
                RiSocket_Send(sockClient, (ri_byte *) nullReturn,
                    sizeof(nullReturn), 0);
                RI_LOGI("local server等待中...回傳null");
                continue;
            }

            howManyMb = (int)(tarFileSize / 1024L / 1024 + 1);
            sprintf(response, "HTTP/1.1 200 OK\r\n"
                "Server: Apache-Coyote/1.1\r\n"
                "Accept-Ranges: bytes\r\n"
                "Content-Type: video/mp4\r\n"
                "Content-Length: %lld\r\n"
                "\r\n", tarFileSize);

            sprintf(response2, "HTTP/1.1 206 Partial Content\r\n"
                "Server: Apache-Coyote/1.1\r\n"
                "Accept-Ranges: bytes\r\n"
                "Content-Range: bytes 0-%lld/%lld\r\n"
                "Content-Type: video/mp4\r\n"
                "Content-Length: %lld\r\n"
                "\r\n", tarFileSize - 1, tarFileSize, tarFileSize);

            /////////
            ri_int64 downloadSize = 0;
            ri_int64 rangeSt = 0;
            ri_int64 rangeEd = 0;
            char *tarContentLength = NULL;
            char *tarContentLengthTell = NULL;
            char strTag[] = "Range: bytes=";
            char strTag2[] = "-";
            //0113測試....拆Range

            tarContentLength = strstr(buffer, strTag);

            if (tarContentLength) {
                tarContentLength += strlen(strTag);
                tarContentLengthTell = strstr(tarContentLength, "\n");
                //strncpy	將字串 s2 最多 n 個字元拷貝到 s1	char *strncpy(char *s1, const char *s2, size_t n);
                char *ContentLengthString = (char*)malloc((int) (tarContentLengthTell
                    - tarContentLength));
                strncpy(ContentLengthString, tarContentLength,
                    (int) (tarContentLengthTell - tarContentLength));
                //			RI_LOGI("ContentLengthString=\n%s \n%d \n%s",ContentLengthString,strlen(ContentLengthString),tarContentLengthTell);
                rangeSt = atoi(ContentLengthString);//atoi抓整數，atof抓小數
                //0126 發現有時候會接到Range: bytes=1090256920-
                //範圍超過影片大小....
                //試試這時候回最後1byte
                if (rangeSt > tarFileSize - 1) {
                    RI_LOGE("收到大於檔案的位置要求!!%lld",rangeSt);
                    rangeSt = tarFileSize - 1;
                }

                RI_LOGI("RANGE_ST為%lld",rangeSt);

                tarContentLength = strstr(ContentLengthString, strTag2);
                if (tarContentLength) {
                    tarContentLength += strlen(strTag2);
                    rangeEd = atoi(tarContentLength);
                    RI_LOGI("RANGE_ED為%lld",rangeEd);
                } else {
                    RI_LOGI("RANGE_ED未取得");
                }

                if (ContentLengthString) {
                    free(ContentLengthString);
                    ContentLengthString = NULL;
                }

                //0121 add 改成一次最多6mb
                long long sendEnd = rangeSt + (1048576 * 6);
                if (sendEnd > (tarFileSize - 1)) {
                    sendEnd = (tarFileSize - 1);
                }
                //			sprintf(response2, "HTTP/1.1 206 Partial Content\r\n"
                //				"Server: Apache-Coyote/1.1\r\n"
                //				"Accept-Ranges: bytes\r\n"
                //				"Content-Range: bytes %lld-%lld/%lld\r\n"
                //				"Content-Type: video/mp4\r\n"
                //				"Content-Length: %lld\r\n"
                //				"\r\n", rangeSt, tarFileSize - 1, tarFileSize, tarFileSize
                //					- rangeSt);
                if (rangeEd > 0) {
                    sprintf(response2, "HTTP/1.1 206 Partial Content\r\n"
                        "Server: Apache-Coyote/1.1\r\n"
                        "Accept-Ranges: bytes\r\n"
                        "Content-Range: bytes %lld-%lld/%lld\r\n"
                        "Content-Type: video/mp4\r\n"
                        "Content-Length: %lld\r\n"
                        "\r\n", rangeSt, rangeEd, tarFileSize, rangeEd + 1
                        - rangeSt);
                } else {
                    sprintf(response2, "HTTP/1.1 206 Partial Content\r\n"
                        "Server: Apache-Coyote/1.1\r\n"
                        "Accept-Ranges: bytes\r\n"
                        "Content-Range: bytes %lld-%lld/%lld\r\n"
                        "Content-Type: video/mp4\r\n"
                        "Content-Length: %lld\r\n"
                        "\r\n", rangeSt, tarFileSize - 1, tarFileSize, tarFileSize
                        - rangeSt);
                }
                // 0  9
                // 1  8   9    8
                // 2  8   9    6
                // 0  8   9    9
                //			sprintf(response2, "HTTP/1.1 206 Partial Content\r\n"
                //				"Server: Apache-Coyote/1.1\r\n"
                //				"Accept-Ranges: bytes\r\n"
                //				"Content-Range: bytes %lld-%lld/%lld\r\n"
                //				"Content-Type: video/mp4\r\n"
                //				"Content-Length: %lld\r\n"
                //				"\r\n", rangeSt, sendEnd, tarFileSize, sendEnd + 1 - rangeSt);

                len = (int) strlen(response2);
                RiSocket_Send(sockClient, (ri_byte *) response2, len, 0);
                RI_LOGE("SEND_%s",response2);

            } else {
                RI_LOGI("沒收到RANGE!!!回200OK");
                len = (int) strlen(response);
                RiSocket_Send(sockClient, (ri_byte *) response, len, 0);
                RI_LOGE("SEND_%s",response);
                //						continue;
            }
            ////////


            //		len = (int) strlen(response);
            //		RiSocket_Send(sockClient, (ri_byte *) response, len, 0);

            sendSize = 0;
            long long tempsend = 0;

            while (!fp) {
                fp = fopen(saveTo, "rb");
                if (fp == NULL) {
                    RI_LOGE("open input file fail!saveTo=%s",saveTo);
#if defined(RI_LINUX)
                    sleep(2);
#elif defined(RI_WINDOWS)
                    Sleep(2000);
#endif
                }
            }
            //		fseek(fp, 0 * 1024L * 1024L, 0);
            fseek(fp, (long)rangeSt, 0);
            while (runningStatus == 2) {
                ri_int64 isRead = 0;
                //			int where = (int) ((sendSize) / 1024 / 1024);
                int where = (int) ((rangeSt + sendSize) / 1024 / 1024);
                if (where < 0)
                where = 0;
                if (where >= howManyMb) {
                    RI_LOGI("where>=howManyMb(%d)",where);
                    break;
                }
                while (chunksArray != NULL && chunksArray[where] != 2
                    //					&& 1 == 2
                    ) {
                        if (chunksArray[where] == 0) {
                            RiLock_Lock(chunkLock);
                            //這邊會有一格位移
                            downloadWhere = where - 1;
                            //					chunksArray[where] = 1;
                            //					downloadWhere = where;
                            RiLock_Unlock(chunkLock);
                            RI_LOGI("強制下載目標區塊(%d)",where);
                        } else {
                            RI_LOGI("目標區塊(%d)下載中",where);
                        }
#if defined(RI_LINUX)
                        sleep(2);
#elif defined(RI_WINDOWS)
                        Sleep(2000);
#endif
                        if (runningStatus != 2) {
                            RI_LOGI("runningStage非2，中斷這一輪上傳");
                            break;
                        }
                }

                //			RI_LOGE("fread:%lld",rangeSt);
                //31641894+16384 =
                isRead = fread(fileData, sizeof(char), 1024L * 16, fp);
                if (isRead <= 0) {
                    RI_LOGE("isRead<=0----%lld",isRead);
                    break;
                } else {
                }
                int ret = 0;
                ret = RiSocket_Send(sockClient, (ri_byte *) fileData, (int) isRead,
                    0);
                if (ret >= 0) {
                    tempsend += ret;
                } else {
                    //				RI_LOGE("RiSocket_Send_ret=%d",ret);

                    RI_LOGE("RiSocket_Send_ERR_OR_END",ret);
                    break;
                }

                int i = 0;
                //			RI_LOGI("目標區塊(%d)send完成====%lld",where,tempsend);
                sendSize += isRead;

            }
            RI_LOGI("send完成====");

            if (fp) {
                fclose(fp);
                fp = NULL;
            }
            buffer[ret] = 0;
            RI_LOGE("server One Round");

        }

        RI_LOGI("test6 RiSocket_Close");
        //	if (localSocket) {
        //		RiSocket_Free(sockClient);
        //		RiSocket_Free(localSocket);
        //		localSocket = NULL;
        //	}
        if (response) {
            free(response);
            response = NULL;
        }
        if (response2) {
            free(response2);
            response2 = NULL;
        }
        runningStatus = 0;
        RI_LOGI("test6 --");
        return 0;
    }





    //test for control x and y
    double x=0.0;
    double y=0.0;

    //0311 time
    long long preTime=0;
    /**
    * @brief LocalServer的上傳端。發送目標影片檔案的Thread，會經由initLocalServer啟動
    */
    DWORD WINAPI piServerThread2(void *)
    {
        RI_LOGI("\npiServerThread\n");
        // TCP server
        int ret = 0;
        //允許同時10個連線....
        int backLog = 10;//0316 CHANGE TO 10 CONNECT
        char buffer[2048];
        //0401 add
        char header[2];
        char size[4];
        RiSocket_t *sockClient;

        // 2015-04-01 iron
        localSocket = RiSocket_New();

        ret = RiSocket_Open(localSocket, RI_SOCKET_AF_INET, RI_SOCKET_SOCK_STREAM,
            RI_SOCKET_IPPROTO_TCP);
        if (ret <= 0)
        {
            RI_LOGI("RiSocket_Init = %d\n", ret);
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
                return NULL;
            }

            ret = RiSocket_Bind(localSocket);
            if (ret <= 0)
            {
                RI_LOGI("RiSocket_Bind = %d\n", ret);
                localServerPort++;
            }
            else
            {
                RI_LOGE("localServer端口開啟： = %d\n", localServerPort);
                break;
            }
        }

        ret = RiSocket_Listen(localSocket, backLog);
        if (ret <= 0)
        {
            RI_LOGI("RiSocket_Listen = %d\n", ret);
            return NULL;
        }

        //int len;
        char ret_strings[] = "return OK";

        //0115 開始上傳前...先等file建立好

        //RI_LOGE("確認File已Set:%d",fileSetOK);
        //0305 for pi
        runningStatus = 2;
        while (localSocket)
        {
            RI_LOGI("server RUN...\n");
            sockClient = RiSocket_Accept(localSocket);
            RI_LOGI("server Accept");

            if (!localSocket)
            {
                RI_LOGI("local server中斷B...\n");
                break;
            }
            RI_LOGE("Accept..");
            if (localSocket)
            {
                RI_LOGI("cnnect from %s\n",inet_ntoa(localSocket->addr_in.sin_addr));
            }
            else
            {
                RI_LOGE("NULL localSocket");
            }


            //0401 change
            RI_LOGI("Before RiSocket_Recv_header");

            while(1)
            {
                ret = RiSocket_Recv(sockClient, (ri_byte *) header, sizeof(header), 0);
                if(header[0]==0x5a && header[1]==0x5a)
                {
                    //RI_LOGI("get header OK");
                    ret = RiSocket_Recv(sockClient, (ri_byte *) size, sizeof(size), 0);
                    long *sizeptr= (long *) (&size[0]);
                    long getsize=*sizeptr;
                    //RI_LOGI("get Size OK,%ld bytes, %hhd %hhd %hhd %hhd",getsize,size[0],size[1],size[2],size[3]);

                    ret = RiSocket_Recv(sockClient, (ri_byte *) buffer, getsize, 0);
                    //RI_LOGI("\nrecv message: %s\n", buffer);


                    switch(buffer[0])
                    {
                    case 'a'://0x00:
                        RI_LOGI("case 0");
                        break;
                    case 'b'://0x01:
                        RI_LOGI("case 1");
                        break;
                    case 'c'://0x02:
                        RI_LOGI("case 2");
                        break;
                    case 'd'://0x03:
                        RI_LOGI("case 3");
                        break;

                    case 'e'://0x10:
                        RI_LOGI("case 10,buffer[1]=%hd,buffer[2]=%hd",buffer[1],buffer[2]);
                        break;

                    case 'f'://0x05:
                        RI_LOGI("0x05 :%hd, %hd", buffer[1], buffer[2])
                            break;
                    case 'g'://0x11:
                        {


                            RI_LOGI("case 11,buffer=%hd,%hd"
                                ",%hd,%hd,%hd"
                                ",%hd,%hd,%hd,%hd,%hd"

                                ,buffer[1],buffer[2],buffer[3],buffer[4],buffer[5]
                            ,buffer[6],buffer[7],buffer[8],buffer[9],buffer[10]);
                            //0311....big-endia and little-endia...now is ok

                            long long *myptr= (long long *) (&buffer[3]);
                            long long newTime=*myptr;
                            //RI_LOGI("time=%lld",newTime);
                            if(preTime<newTime)
                            {
                                preTime=newTime;
                            }
                            else
                            {
                                RI_LOGI("skip old message...");
                            }
                        }
                        break;
                    case 'H':

                        servo_ang1 = buffer[1];
                        servo_ang2 = buffer[2];
                        isServoDataReady = true;
                        break;
                    case 'S'://0x21
                        RI_LOGI("case STABLE_MODE");
                        while(clientSocket("192.168.8.126", 3335, "S", 1) < 0)
                            break;
                    case 's'://0x22
                        RI_LOGI("case CAMERA_MODE");
                        while(clientSocket("192.168.8.126", 3335, "s", 1) < 0)
                            break;
                    }
                }
                else
                {
                    RI_LOGI("header is not 0x5a0x5a..skip");
                }

            }
            RI_LOGI("server ONE ROUND");
            continue;


            RI_LOGE("Before RiSocket_Recv");
            ret = RiSocket_Recv(sockClient, (ri_byte *) buffer, sizeof(buffer), 0);
            if (ret <= 0)
            {
                RI_LOGI("RiSocket_Recv = %d\n", ret);
            }
            RI_LOGE("ret:%d",ret);
            buffer[ret]='\0';
            RI_LOGI("\nrecv message: %s\n", buffer);


            RI_LOGE("server One Round");

        }

        RI_LOGI("RiSocket_Close");

        runningStatus = 0;
        return 0;
    }

    /**
    * @brief 回傳LocalServer的Port開在哪裡
    * @return LocalServer開啟的Port
    */
    int getlocalServerPort() {
        return localServerPort;
    }

    /**
    * @brief 建立LocalServer
    * @param myLocalServerPort
    *       要把LocalServer的Port開在哪邊
    * @return 成功回傳1
    */
    int initLocalServer(int myLocalServerPort) {

        localServerPort = myLocalServerPort;
        initTest = 1;
        isFileDownloading = 0;
        //0120test....
        //pthread_t sendThread;
        if (initTest == 1) {
            ///home/pi/Desktop/workspace/test1/openri/src/gt_httpd.c|2979|未定義參考到「pthread_create」|
            // in build,-lpthread
            //-fexceptions -lpthread
            ///home/pi/Desktop/workspace/test1/openri/src/gt_httpd.cpp|1230|error: invalid conversion from ‘void* (*)()’ to ‘void* (*)(void*)’ [-fpermissive]|
            CreateThread(NULL/*&sendThread*/, 0, uploadThread2, NULL, 0, NULL);
        }
        RI_LOGE("initLocalServer --");
        return RI_OK;
    }







    HANDLE camThread;
    /**
    * @brief 建立LocalServer2
    * @param myLocalServerPort
    *       要把LocalServer的Port開在哪邊
    * @return 成功回傳1
    */
    int initLocalServer2(int myLocalServerPort) {

        //0311test
        //testjpg();
        //0313 test
        //camera_open();


        localServerPort = myLocalServerPort;
        initTest = 1;
        isFileDownloading = 0;
        //0120test....
        //pthread_t sendThread;
        ///home/pi/Desktop/workspace/test1/openri/src/gt_httpd.c|2979|未定義參考到「pthread_create」|
        // in build,-lpthread
        //-fexceptions -lpthread
        ///home/pi/Desktop/workspace/test1/openri/src/gt_httpd.cpp|1230|error: invalid conversion from ‘void* (*)()’ to ‘void* (*)(void*)’ [-fpermissive]|
        CreateThread(NULL/*&sendThread*/, 0, piServerThread2, NULL, 0, NULL);


        //pthread_create(&camThread, NULL, test0317, NULL);

        RI_LOGE("initLocalServer --");
        return RI_OK;
    }




    //int isFileDownloading = 0;//0121
    //int howManyMb = 100;

    /**
    * @brief 開始讓LocalServer下載影片檔。
    * @param isFileChange
    *         影片url是否有更換，更換=1，沒變=0。若此值為1，這邊會先把上次的影片暫存檔刪除再開始進行下載動作
    * @param myip
    *         影片檔案所在server的IP
    * @param myport
    *         影片檔案所在server的port
    * @param myaddress
    *         影片檔案在server上的路徑
    * @param mysaveTo
    *         暫存影片檔的本機路徑
    * @param fileSpace
    *         SD卡剩餘空間，單位為byte
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int runLocalServer(int isFileChange, const char* myip, int myport,
        const char* myaddress, const char* mysaveTo, long long fileSpace) {
            if (!localServerPort && localServerPort == 0) {
                localServerPort = 3333;
            }
            chunksArray = NULL;
            //	howManyMb = 100;
            isNewFile = 1;

            //0121....這邊也要切換....
            if (!initTest) {
                localSocket = NULL;
            }
            downloadWhere = 0;
            fileSetOK = 0;
            runningStatus = 1;

            RI_LOGI("DownLoadTest...準備啟動LocalServer");
            //	const char *url;
            serverIP = myip;
            RI_LOGI("url=%s",serverIP);
            //	RI_LOGI("url2=%s",gethostbyname(serverIP)->h_name);
            //	RI_LOGI("url3=%s",gethostbyname("www.leadergstaging.com")->h_addr_list[0]);

            //	const char *saveTo;
            saveTo = mysaveTo;
            RI_LOGI("mysaveTo=%s",mysaveTo);
            RI_LOGI("saveTo=%s",saveTo);
            address = myaddress;
            isNewFile = isFileChange;
            port = myport;
            //開thread....加個RiLock_New
            if (!chunkLock) {
                //RiLock_New(&chunkLock);
                chunkLock=RiLock_New();
            }

            //0114測試......抓fileSize
            tarFileSize = getFileSize();

            char *savePath = (char *)calloc(512, sizeof(char));
            sprintf(savePath, "%s%s", saveTo, ".map");
            FILE *fp = NULL;
            fp = fopen(savePath, "rb");
            int needDownloadFile = 0;//若判斷為完整檔案就不用下載
            RI_LOGI("tarFileSize=%lld,fileSpace=%lld",tarFileSize,fileSpace);

            //0126增加判斷....如果user自行把檔案砍掉的情況
            FILE *fp2 = fopen(saveTo, "rb");
            if (!fp2) {
                RI_LOGI("tempFile不存在....當成新檔案");
                needDownloadFile = 1;
                isNewFile = 1;

            } else if (!fp) {

                //0116追加剩餘空間判斷....用c不好抓android的剩餘空間，所以從java端抓了以後傳過來
                if (tarFileSize > fileSpace) {
                    runningStatus = 0;
                    return -3;
                }

                RI_LOGI("map不存在....當成新檔案");
                needDownloadFile = 1;
                isNewFile = 1;
            } else if (isNewFile == 0) {//只有舊檔案才要抓map

                fseek(fp, 0, SEEK_END);
                int size = ftell(fp);
                fseek(fp, 0, SEEK_SET);
                RI_LOGI("試抓map");
                int i = 0;
                chunksArray = (char *)calloc(size, sizeof(short));

                fread(chunksArray, sizeof(short), size, fp);
                RI_LOGI("%d",size);
                for (i = 0; i < size; i++) {
                    RI_LOGI("%d:%hhd",i,chunksArray[i]);
                    if (chunksArray[i] > 2 || chunksArray[i] < 0) {
                        chunksArray[i] = 0;
                    }
                }

                for (i = 0; i < size; i++) {
                    if (chunksArray[i] != 2) {
                        needDownloadFile = 1;
                        break;
                    }
                }
            } else {
                //0127add，isNewFile=1時，需要砍掉後再下載檔案

                //1.砍檔前把FILE關掉
                if (fp2) {
                    fclose(fp2);
                    fp2 = NULL;
                }
                if (fp) {
                    fclose(fp);
                    fp = NULL;
                }
                //2.開始砍
                remove(saveTo);
                remove(savePath);

                RI_LOGI("檔案已砍，準備重新下載");
                needDownloadFile = 1;
                isNewFile = 1;
            }

            if (fp) {
                fclose(fp);
                fp = NULL;
            }
            if (fp2) {
                fclose(fp2);
                fp2 = NULL;
            }

            //0116追加影片不存在判斷與server連不上判斷
            if ((tarFileSize == -1 ||tarFileSize == 0)&& needDownloadFile) {
                RI_LOGI("檔案不存在");
                runningStatus = 0;
                if (chunksArray) {
                    free(chunksArray);
                    chunksArray = NULL;
                }
                return -4;
            } else if (tarFileSize == -6 && needDownloadFile) {
                RI_LOGI("URL連不上");
                runningStatus = 0;
                if (chunksArray) {
                    free(chunksArray);
                    chunksArray = NULL;
                }
                return -6;
            }

            //用 pthread讀取server傳來的封包
            //pthread_t getThread, sendThread;
            if (needDownloadFile) {
                RI_LOGI("檔案不存在或不完整，開啟下載thread");
                CreateThread(NULL/*&getThread*/, 0, downloadThread, NULL, 0, NULL);
            } else {
                RI_LOGI("該檔案為完整檔案！！");
                fileSetOK = 1;
                if (initTest) {
                    runningStatus = 2;
                }
            }
            if (initTest == 0) {
                CreateThread(NULL/*&sendThread*/, 0, uploadThread, NULL, 0, NULL);
            }
            return RI_OK;

    }
    /**
    * @brief 讓LocalServer停止下載動作。
    *
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int stopLocalServer() {

        RI_LOGI("stopLocalServer");
        runningStatus = 3;
        int times = 0;

        //0120改為.....結束播放時localSocket不終止>>>狀況不佳
        //0121 edit
        if (!initTest) {
            if (localSocket) {
                RiSocket_Free(localSocket);
                localSocket = NULL;
            }

            while (runningStatus == 3 && times++ <= 5) {
                RI_LOGI("等待Socket關閉：%d",times);
#if defined(RI_LINUX)
                sleep(2);
#elif defined(RI_WINDOWS)
                Sleep(2000);
#endif
            }
        } else {

            while (isFileDownloading == 1 && times++ <= 10) {
                RI_LOGI("等待isFileDownloading關閉：%d",times);
#if defined(RI_LINUX)
                sleep(2);
#elif(RI_WINDOWS)
                Sleep(2000);
#endif
            }
        }

        if (chunksArray) {
            char *savePath = (char *)calloc(512, sizeof(char));
            sprintf(savePath, "%s%s", saveTo, ".map");

            FILE *fp = NULL;
            fp = fopen(savePath, "wb");
            int i = 0;

            for (i = 0; i < howManyMb; i++) {
                RI_LOGI("%d:%hhd",i,chunksArray[i]);
            }
            fwrite(chunksArray, 1, howManyMb, fp);
            fclose(fp);
            free(chunksArray);
            chunksArray = NULL;
        } else {
            RI_LOGI("chunksArray 不存在!!!");
        }
        fileSetOK = 0;
        if (initTest) {
            runningStatus = 0;
        }
        RI_LOGI("stopLocalServer OK");
        return RI_OK;

    }

    /**
    * @brief 關閉LocalServer
    *
    * @return 成功回傳1，否則回傳錯誤碼
    */
    int freeLocalServer() {
        if (initTest) {
            if (localSocket) {
                RI_LOGI("\nFreeServer pthread_join\n");
                cameraRunning = 0;
                //pthread_join(camThread,NULL);
				WaitForSingleObject(camThread, INFINITE);
                //camera_close();
                RI_LOGI("\nFreeServer start\n");
                RiSocket_Free(localSocket);
                localSocket = NULL;
            }else{
                RI_LOGI("ERR?freeLocalServer_NULL\n");
            }
        }
        return RI_OK;
    }



    //RiSocket_t *client;

    //0401 change....
    RiSocket_t *client=NULL;
    int clientSocket(char* tarIp,int port,char* msg,int size)
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
                RiSocket_Free(client);
                client=NULL;
                RiLock_Unlock(glock);
                return -1;
            }
            ret = RiSocket_SetAddressIn(client, (ri_utf8 *)tarIp, port);
            ret = RiSocket_Connect(client);

            if (ret == RI_ERROR)
            {
                RI_LOGE("連線失敗");
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
    }





    void* runSevro(void *) {
#if defined(RI_LINUX)
        RI_LOGI("runSevro2...");
        int ret, flags, old_servo_ang1, old_servo_ang2, old_dc_left, old_dc_right;
        char cmd[16];
        int checksum = 0;
        char header[2];
        char size[4];
        char buffer[2];

        /*initialize wiringPi*/
        char input;
        (void)signal(SIGINT, control_event);
        (void)signal(SIGQUIT, control_event);


        //softServoSetup(PWM_PIN1,PWM_PIN2,-1,-1,-1,-1,-1,-1);
        servo_ang1 = default_servo_ang1;
        servo_ang2 = default_servo_ang2;
        old_servo_ang1 = servo_ang1;
        old_servo_ang2 = servo_ang2;
        old_dc_left = 0;
        old_dc_right = 0;
        delay(DELAY_MS*100);
        servo_motor_ready = 1;


        RI_LOGI("control servo motor ");
        /* control servo motor*/
        while(1){
            if (!isServoDataReady) 
            {
                usleep(500);
                continue;
            }
            isServoDataReady = false;
#if 0
            if (clientSocket("192.168.8.126", 3335, "h", 1) < 0) {
                printf("----------------> request sensor info ------------->\n");
                usleep(100);
                continue;
            }

            RiSocket_Recv(client, (ri_byte *) header, sizeof(header), 0);
            if(header[0]==0x5a && header[1]==0x5a)
            {
                RI_LOGI("----get header OK");
                ret = RiSocket_Recv(client, (ri_byte *) size, sizeof(size), 0);
                long *sizeptr= (long *) (&size[0]);
                long getsize=*sizeptr;
                RI_LOGI("----get Size OK,%ld bytes, %hhd %hhd %hhd %hhd",getsize,size[0],size[1],size[2],size[3]);

                ret = RiSocket_Recv(client, (ri_byte *) buffer, getsize, 0);

                printf("----receive ang: %d, %d\n", buffer[0], buffer[1]);

            }
#endif
            //while (!isServoDataReady) {}
            printf("----receive ang: %d, %d\n", servo_ang1, servo_ang2);

            if((old_servo_ang1 == servo_ang1) && (old_servo_ang2 == servo_ang2))
            {
                usleep(1000);
                continue;
            }
            //if (!isServoDataReady)
            //  continue;
            //pthread_mutex_lock (&mutex_servo_angle);
            servo_motor_ready = 0;
            checksum = floor(servo_ang1/100) + (int)floor(servo_ang1/10)%10 + servo_ang1%10 +
                floor(servo_ang2/100) + (int)floor(servo_ang2/10)%10 + servo_ang2%10 +
                dc_left + dc_right;
            cmd[0] = servo_ang1;
            cmd[1] = servo_ang2;
            cmd[2] = dc_left;
            cmd[3] = dc_right;
            cmd[4] = checksum;
#if INTERFACE == SPI
            cmd[5] = 0x0A;
            uint8_t rx[ARRAY_SIZE(cmd)] = {0, };
            struct spi_ioc_transfer tr = {
                tr.tx_buf = (unsigned long)cmd,
                tr.rx_buf = (unsigned long)rx,
                tr.len = ARRAY_SIZE(cmd),
                tr.delay_usecs = spi_delay,
                tr.speed_hz = speed,
                tr.bits_per_word = bits,
            };
            printf("SPI data[0]: %d, data[1] %d\n", cmd[0], cmd[1]);
            ret = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr);
            if(ret <1)
                printf("spi send data fail XX\n");
#elif INTERFACR == I2C
            if (write(fd_i2c, cmd, 5) != 1)
                RI_LOGI("i2c send data fail!\n");
#endif

            //printf("send data: %d, %d, %d, %d, %d", cmd[0], cmd[1], cmd[2], cmd[3], cmd[4]);
            old_servo_ang1 = servo_ang1;
            old_servo_ang2 = servo_ang2;
            old_dc_left = dc_left;
            old_dc_right = dc_right;
            delay(DELAY_MS*4);
            servo_motor_ready = 1;
            //pthread_mutex_unlock (&mutex_servo_angle);
        }
#endif

    }

    void control_event(int sig)
    {
#if defined(RI_LINUX)
        printf("\b\bExiting....\n");
        //	softPwmWrite(PWM_PIN1, default_servo_ang1);
        //softPwmWrite(PWM_PIN2, default_servo_ang2);
        if(useUSBcam==0){
            Camera.release();
        }else{
            cvReleaseCapture(&cvcap);
        }
        //0317add
        cameraRunning=0;
#if INTERFACE == SPI
        close(fd_spi);
#elif INTERFACE == I2C
        close(fd_i2c);
#endif
        delay(DELAY_MS*100);
        close(fd_server_socket);
        pthread_mutex_destroy(&mutex_servo_angle);
        exit(0);
#endif
    }


    int startSevro() {
#if defined(RI_LINUX)
        printf(".......initialize wiringPi.......\n");
        if(getuid()!=0)
        {
            printf("wiringPi must be run as root. \n");
            //	return NULL;
        }

        if(wiringPiSetup()==-1)
        {
            printf("wiringPi setup failed. \n");
            //return NULL;
        }


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
        RI_LOGI("SPI max speed: %d Hz (%d KHz)\n", speed, speed/1000);
#elif INTERFACE == I2C
        if ((fd_i2c = open(devName, O_RDWR)) < 0) {
            RI_LOGI("I2C: Failed to access %s\n", devName);
        }

        RI_LOGI("I2C: acquiring buss to 0x%x\n", ADDRESS);

        if (ioctl(fd_i2c, I2C_SLAVE, ADDRESS) < 0) {
            RI_LOGI("I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
        }
#endif

        pthread_t sevroThread;
        pthread_create(&sevroThread, NULL, runSevro, NULL);
        return RI_OK;
#endif
    }




#ifdef __cplusplus
}
#endif
