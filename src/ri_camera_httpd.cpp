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

/*
**********************************************************************************
* Date           Author      Description
* --------------------------------------------------------------------------------
* 2015-09-30     Ann         log消除, 找到core dumped原因, 
* 2015-10-29     Iron        從QT接收框選圖片區域的座標
* 2015-11-03     Iron        unstable mode影像部旋轉
* 2015-11-05     Ann         影像大小不裁減
* 2015-11-26     Iron        將影像以外的像素塗黑
* 2015-11-26     Iron        加入遠端關閉電源功能
* 2015-11-30     Iron        降低JPG壓縮品質，加入攝影機控制
* 2015-12-01     Ann         加入log檔案
* 2015-12-01     Iron        過濾pitch小於1度的值
* 2015-12-03     Iron        畫面擷取成寬螢幕比例16:9，640x360並將上下裁切
* 2015-12-07     Ann         makefile add LOGFILE to turn on/off the function of logFIle
* 2015-12-11     Ann         zoom out at before shutdown at case 'z' 
* 2015-12-16     Ann         add case 'G' 'J' to control camera zoom far & near
* 2015-12-18     Iron        加入準星校正置中功能
* 2015-12-22     Iron        改為只抓取一張圖片
* 2015-12-28     Iron        使用matchTemplate追蹤目標
* 2016-01-04     Iron        新增相似度判斷機制，加入自動對焦功能開關
* 2016-01-07     Iron        新增使用hsv方式比對pattern和matchtemplate後的圖片
* 2016-01-07     Ann         修改makefile logfile問題
* 2016-01-11     Iron        改為一次只從攝影機擷取一張圖處理並傳送
* 2016-01-12     Iron        利用新舊抓到的物件位置距離來判斷是否抓錯，修正pitch旋轉時會抖動
**********************************************************************************/
#include "ri_httpd.h"
#include <ctype.h>

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if defined(RI_LINUX) 
#include <sys/time.h>
#include <unistd.h>// sleep(3);
#include <sys/timeb.h>//timeb
#include "arduino-serial-lib.h"
#elif defined(RI_WINDOWS)
#define MSG_NOSIGNAL 0
#endif
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\photo\photo.hpp>
#include <opencv2\photo\photo_c.h>
#include <opencv2\features2d\features2d.hpp>
#include <opencv\cv.h>

/*#ifdef __cplusplus
extern "C"
{
#endif*/

using namespace cv;
using namespace std;
#define OFF	0
#define ON 1
#undef CAMERA_ON
#define CAMERA_ON OFF

#define WIDTH	320*2
#define HEIGHT	240*2
#define CENTER_X WIDTH/2
#define CENTER_Y HEIGHT/2
#define MOTOR_SCALE	50000
#define max(a,b) (a>=b ? a:b)
#define SENSOR_IP "192.168.88.103"//"192.168.88.103"//"192.168.8.121"//"192.168.88.103"
#define SENSOR_PORT 3335
//#define HSV_DETECT
//#define CAMSHIFT_DETECT
#define CAMERA 1
#define MOTOR 2
#define SENSOR 3
#define log 0
#define OBJ_TRACK_MATCH

unsigned char camera_cmd[7][7] = { { 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01 }, //STOP
{ 0xFF, 0x01, 0x01, 0x00, 0x00, 0x11, 0x13 }, //FOCUS_NEAR
{ 0xFF, 0x01, 0x00, 0x80, 0x00, 0x11, 0x92 }, //FOCUS_FA
{ 0xFF, 0x01, 0x00, 0x40, 0x00, 0x11, 0x52 }, //ZOOM_WIDE
{ 0xFF, 0x01, 0x00, 0x20, 0x00, 0x11, 0x32 }, //ZOOM_TELE
{ 0xFF, 0x01, 0x00, 0x2B, 0x00, 0x00, 0x2C }, //AUTO_FOCUS
{ 0xFF, 0x01, 0x00, 0x2B, 0x00, 0x02, 0x2E }, //AUTO_FOCUS_OFF

};

enum CAMERA_OPTION { STOP = 0,
    FOCUS_NEAR,
    FOCUS_FAR,
    ZOOM_WIDE,
    ZOOM_TELE,
    AUTO_FOCUS,
    AUTO_FOCUS_OFF
};

enum {
    MODE_NONE = 0,
    MODE_STABLE,
} MODE_TYPE;


typedef struct imgbuf
{
    char *buffer;
    int size;
    bool isSending;
} imgbuf;

typedef struct {
    int id;
    Mat mat;
} IMAGERAW;

imgbuf *saveBuffer[4] = {NULL};

static RiLock_t * glock;
static RiSocket_t *client = NULL;
static RiSocket_t *localSocket;
HANDLE save_mutex;
Mat pattern, match_obj, diff, diff2;
Mat pattern_hsv, match_obj_hsv, background_hsv;
Point ptMatch_old;
Scalar diff_mean, diff_mean2, pattern_mean, match_obj_mean;
int lost_obj_cnt = 0;
static char *img_send_ip;
bool hasObj = false;
bool hasPattern = false;
bool saveBufLock = false;
bool firstMatch = false;
bool isColor = true;
float img_offset_x;
float img_offset_y;
static int camera_mode ;//= MODE_NONE;
int fd_camera_controller;
int focus_rect_X1, focus_rect_Y1, focus_rect_X2, focus_rect_Y2;
int x_rect_1 = 0;
int y_rect_1 = 0;
int x_rect_2 = 0;
int y_rect_2 = 0;
int saveIndex = -1;
int readIndex = 0;
int img_start_x, img_end_x;
int img_start_y, img_end_y;
int send_th_cnt = 0;
static int localServerPort;    
static int riHttpdIsInit = 0;
static int cameraRunning=1;
bool cali = false;  
bool detectFunction = false;  
bool needToInit = true;
FILE *logFile;
char logFIle_message[100];
struct timeval old, current;    
static RiSemaphore_t *sem;
static HANDLE thr[10];
static int SEM_NUM=10;    
bool first_open =true;

Rect selection, trackWindow;
int trackObject = 0;
Mat image, hsv, hue, hist, mask, backproj;

float pitch_ang;
RiSocket_t *sensor_client=NULL;

Point2f point;
Point2f point1;
Point2f point3;


#if CAMERA_ON == ON
CvCapture *cvcap;
VideoCapture cap(0);
VideoCapture cap1(1); 
#endif

Rect ROI;
vector<Point2f> points[2];
vector<Point2f> points_back;
TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
Size subPixWinSize(10, 10), winSize(31, 31);

Mat gray, prevGray, out;
vector<Point2f> features;      
double qLevel = 0.01;       
double minDist = 1.0;      
int MAX_COUNT = 500;
vector<uchar> status;
vector<float> err; 
vector<Mat> getMatArray;
char *imageBuffer;
HANDLE image_buffer_mutex;
long image_buffer_size;    
static RiSocket_t *clientsocket = NULL;
int match_error_count = 0; 
HANDLE sensorThread, sendThread, camThread, conThread;

void rotate(Mat img, Mat screen, Mat img1)
    {

        float degree = pitch_ang*(1); // rotate 30 degree     
        float angle = (float)(degree  * CV_PI / 180); // angle in radian
        float a = sin(angle), b = cos(angle); // sine and cosine of angle .row

        if(camera_mode == MODE_STABLE)
        {
            int w_rotate = int(img.rows * fabs(a) +img.cols * fabs(b));
            int h_rotate = int(img.cols* fabs(a) + img.rows * fabs(b));
            Mat rotate_test(h_rotate, w_rotate, CV_8UC3);

            Point2f pt((float)img.cols / 2, (float)img.rows / 2);
            Mat rotation_matrix = getRotationMatrix2D(pt, degree, 1);

            warpAffine(img, rotate_test, rotation_matrix, img.size() );
            rotate_test.copyTo(screen);
        }
        else
            img.copyTo(screen);

        //Mat adjust(img.rows/1.4, img.rows/1.4, CV_8UC3);	
        //rotate_test(Rect(img.cols/2-(img.rows/(2*1.4)) ,img.rows/2-(img.rows/(2*1.4)), img.rows/1.4, img.rows/1.4 )).copyTo(adjust);    
        //adjust(Rect(0, (adjust.rows/2)*7/32, adjust.cols, adjust.cols*9/16 )).copyTo(screen);  

    }
Mat getMat(int id)
    {
        ////gettimeofday( &current, NULL );
        int timeuse = 1000000 * ( current.tv_sec - old.tv_sec ) + current.tv_usec - old.tv_usec;
        old = current;	   
        Mat frame;
#if CAMERA_ON == ON
        if (isColor)
            cap.read(frame);//-img
        else
            cap1.read(frame);//-img
#endif
        //timeuse = 1000000 * ( current.tv_sec - old.tv_sec ) + current.tv_usec - old.tv_usec;
        //printf("time use: %d\n", timeuse);
        Mat imgrepair(frame.rows, frame.cols, CV_8UC3);	
        Mat img1(frame.rows, frame.cols, CV_8UC3);
        Mat background_resize;
        //Mat background(HEIGHT, ceil(HEIGHT*16/9), CV_8UC3);
        //Mat background(ceil(WIDTH*9/16), WIDTH, CV_8UC3);
        //img_shift_x = ceil(HEIGHT*16/9)/2 - frame.cols/2;
        //img_shift_y = HEIGHT/2 - frame.rows/2;
        //img_shift_y = HEIGHT/2 - frame.rows/2;

        rotate(frame, imgrepair, img1);
        // tracking(imgrepair, imgrepair); 
        //background.setTo(Scalar(0, 0, 0));
        Mat background((WIDTH * 9 / 16), WIDTH, CV_8UC3);

        // 畫面擷取成寬螢幕比例16:9，640x360並將上下裁切 
        if (cali)
        {

            background.setTo(Scalar(0, 0, 0));
            out = Mat::zeros(background.size(), imgrepair.type());
            out = imgrepair.rowRange(60, 360 + 60);

            // 將準星提供的位置移至畫面正中央 
            out(Rect(img_start_x,
                img_start_y,
                out.cols - img_end_x - img_start_x,
                out.rows - img_end_y - img_start_y)).copyTo(background(Rect(img_end_x,
                img_end_y,
                background.cols - img_end_x - img_start_x,
                background.rows - img_end_y - img_start_y)));
        }
        else {

            background = imgrepair.rowRange(60, 360 + 60);

        }



#ifdef OBJ_TRACK_MATCH
        if(detectFunction){
            resize(background, background_resize, Size((int)background.cols / 2,(int)background.rows / 2) );
            if (hasPattern)
            {

                pattern = background_resize(Rect(x_rect_1 / 2, y_rect_1 / 2, x_rect_2 / 2 - x_rect_1 / 2, y_rect_2 / 2 - y_rect_1 / 2));
                //imwrite("pattern.jpg", pattern);
                cvtColor(pattern, pattern_hsv, CV_BGR2HSV);
                hasPattern = false;
                firstMatch = true;
            }

            if (pattern.data)
            {

                Mat matPMDiff;
                Point ptMatch, ptTemp;
                double valMatch;

                cvtColor(background_resize, background_hsv, CV_BGR2HSV);
                int match_method = CV_TM_CCOEFF_NORMED;
                matchTemplate(background_hsv, pattern_hsv, matPMDiff, match_method);
                //matchTemplate(background_resize, pattern, matPMDiff, match_method);

                if (match_method == CV_TM_SQDIFF_NORMED)
                {
                    minMaxLoc(matPMDiff, &valMatch, NULL, &ptMatch, NULL);
                }
                else
                {
                    minMaxLoc(matPMDiff, NULL, &valMatch, NULL, &ptMatch);
                }

                match_obj = background_resize(Rect(ptMatch.x, ptMatch.y, pattern.cols, pattern.rows));
                cvtColor(match_obj, match_obj_hsv, CV_BGR2HSV);
                //imwrite("match_obj.jpg", match_obj);
                //absdiff(pattern, match_obj, diff);
                absdiff(pattern_hsv, match_obj_hsv, diff);
                pattern_mean = mean(pattern_hsv);
                match_obj_mean = mean(match_obj_hsv);
                diff_mean = mean(diff);

                absdiff(pattern, match_obj, diff2);
                diff_mean2 = mean(diff2);
                float bgr_max_diff = (float)(*std::max_element(diff_mean2.val, diff_mean2.val+3) - *std::min_element(diff_mean2.val, diff_mean2.val+3));
                //printf("pattern (%f, %f, %f, %f), match_obj (%f, %f, %f, %f)\n", pattern_mean[0], pattern_mean[1], pattern_mean[2], pattern_mean[3],
                //                                                         match_obj_mean[0], match_obj_mean[1], match_obj_mean[2], match_obj_mean[3]);
                printf("ptMatch x:%d, y:%d\n", ptMatch.x, ptMatch.y);
                printf("Match hsv avg.....(%f, %f, %f)(%f)\n", diff_mean.val[0], diff_mean.val[1], diff_mean.val[2], valMatch);
                printf("Match bgr avg.....(%f, %f, %f)(%f)\n", diff_mean2.val[0], diff_mean2.val[1], diff_mean2.val[2], bgr_max_diff);
                if (firstMatch)
                {
                    ptMatch_old = ptMatch;
                    firstMatch = false;
                }
                ptTemp = ptMatch - ptMatch_old;

                bool match;
                if (match_method == CV_TM_SQDIFF_NORMED)
                {
                    match = valMatch < 0.25 && diff_mean.val[0] < 40 && diff_mean.val[1] < 40;
                }
                else
                {
                    match = valMatch > 0.2 && (bgr_max_diff < 10 || diff_mean.val[0] < 40) && diff_mean.val[1] < 30 && diff_mean.val[0] + diff_mean.val[1] < 150;
                }

                //rectangle(background, Point(ptMatch.x *2, ptMatch.y *2), Point(ptMatch.x *2 + pattern.cols *2, ptMatch.y *2 + pattern.rows *2), Scalar(255, 0, 0), 1);
                if (match)
                {
                    //printf("diff( %d, %d)\n", ptTemp.x, ptTemp.y);
                    lost_obj_cnt = 0;
                    rectangle(background, Point(ptMatch.x *2, ptMatch.y *2), Point(ptMatch.x *2 + pattern.cols *2, ptMatch.y *2 + pattern.rows *2), Scalar(0, 255, 0), 1);
                    if (abs(ptTemp.x) < 30 && abs(ptTemp.y) < 30)
                    {
                        float lineLength =(float)(pattern.cols > pattern.rows ? pattern.cols/10 : pattern.rows/10);
                        line(background, Point((int)((ptMatch.x *2 + pattern.cols) - lineLength) , ptMatch.y *2 + pattern.rows), Point((int)((ptMatch.x *2 + pattern.cols) + lineLength) , ptMatch.y *2 + pattern.rows), Scalar(255, 255, 255), 1, CV_AA, 0);
                        line(background, Point(ptMatch.x *2 + pattern.cols,(int)((ptMatch.y *2 + pattern.rows) - lineLength)), Point(ptMatch.x *2 + pattern.cols, (int)((ptMatch.y *2 + pattern.rows) + lineLength)), Scalar(255, 255, 255), 1, CV_AA, 0);
                        rectangle(background, Point(ptMatch.x *2, ptMatch.y *2), Point(ptMatch.x *2 + pattern.cols *2, ptMatch.y *2 + pattern.rows *2), Scalar(0, 0, 255), 1);
                        ptMatch_old = ptMatch;
                    }else{
                        match_error_count++;
                    }
                    //rectangle(background, ptMatch, Point(ptMatch.x + pattern.cols, ptMatch.y + pattern.rows), Scalar(0, 0, 255), 2);
                    //if (diff_mean.val[0] < 40 && diff_mean.val[1] < 40 )//&& diff_mean.val[2] < 40)
                    //	rectangle(background, ptMatch, Point(ptMatch.x + pattern.cols, ptMatch.y + pattern.rows), Scalar(0, 255, 0), 2);
                }
                else
                {
                    if (lost_obj_cnt == 100)
                    {
                        printf("no obj\n");
                        pattern.data = NULL;
                        lost_obj_cnt = 0;
                    }
                    else
                        lost_obj_cnt++;

                }
                printf("Number of error count:%d\n", match_error_count);
            }
        }
#endif
        //rectangle(background, Point(x_rect_1, y_rect_1), Point(x_rect_2, y_rect_2), Scalar(255, 0, 0), 1);
        return background;	


        //2015-10-29 detect
        cvtColor(background, gray, COLOR_BGR2GRAY);	
        if(!(points[0].empty()) )
        {

            vector<uchar> status;
            vector<uchar> status_back;
            vector<float> err;
            vector<float> err_back;
            if (prevGray.empty() )
                gray.copyTo(prevGray);

            calcOpticalFlowPyrLK(prevGray, gray,points[0], points[1], status, err);//forward
            calcOpticalFlowPyrLK(gray, prevGray,points[1], points_back, status_back, err_back);//forward



            size_t i, k;
            for( i =k =0; i<points[1].size(); i++)
            {
                if (!status[i])
                    continue;
                err_back[i] = (float)norm(points[0][i]- points_back[i]);				
                if(err_back[i]<1)
                {
                    points[1][k] = points[1][i];
                    k++;
                } 
                else
                    continue;			
            }
            points[1].resize(k);


            for (i = k = 0; i <points[1].size(); i++)
            {

                if (!status[i])
                    continue;

                points[1][k++] = points[1][i];
                circle(background, Point((int)(2*points[1][i].x), (int)(2*points[1][i].y)), 3,CV_RGB(255, 0 , 0), 10);
                rectangle(background,Point((int)(points[1][i].x-(ROI.width/2)), (int)(points[1][i].y-(ROI.height/2))), Point((int)(points[1][i].x+(ROI.width/2)), (int)(points[1][i].y+(ROI.height/2))), CV_RGB(255,0,0), 1); 	               


            }
        }

        //point =Point2f(260.12345,56.58972);
        if (hasObj&& points[1].size() < (int)MAX_COUNT)
        {
            printf("has obj\n");
            points[1].push_back(point);		  
            rectangle(background, Point(x_rect_1, y_rect_1), Point(x_rect_2, y_rect_2), Scalar(255, 0, 0), 1);
            hasObj = false;			

        }

        std::swap(points[1], points[0]);
        //printf("point0 size:    %d     %d   \n", points[0].size(), points[0].empty());	
        cv::swap(prevGray, gray);
        //2015-10-29框選圖片
        //rectangle(imgrepair, Point(x_rect_1, y_rect_1), Point(x_rect_2, y_rect_2), Scalar(255, 0, 0), 1);

        return background;
    }
#ifdef __cplusplus
extern "C"
{
#endif

#define DEBUG 0    
    
    void contourFilter(Mat imgrepair, Mat maskrepair, Mat img, float offset_x, float offset_y, bool obj)
    {

        GaussianBlur( maskrepair, maskrepair, Size(9, 9), 2, 2 );
        vector<vector<Point> > yellow_contour;
        vector<Vec4i> hierarchy;
        findContours(maskrepair, yellow_contour, hierarchy,  CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE , cvPoint(0,0));

        vector<Rect>recv(yellow_contour.size());
        vector<Vec3f>circles;
        for(int i=0; i<yellow_contour.size(); i++)
        {
            //set ROI
            recv[i]= boundingRect( Mat(yellow_contour[i]) );
            float area =(float)abs(contourArea(yellow_contour[i]));

            if(area>3000)//when area>3000, setROI and detect circle
            {
                Rect ROI= Rect(recv[i].x, recv[i].y, recv[i].width, recv[i].height);
                Mat graycircle= imgrepair(ROI);
                cvtColor(graycircle, graycircle, CV_BGR2GRAY);
                HoughCircles(graycircle, circles, CV_HOUGH_GRADIENT
                    ,2 , graycircle.cols/2);

                for(int x=0; x<circles.size(); x++)
                {
                    int radious =cvRound(circles[x][2]);
                    circle( img, Point(cvRound(circles[x][0]+ROI.x), cvRound(circles[x][1])+ROI.y), radious,Scalar(0,0,255), 3);
                    offset_x = circles[x][0]+ROI.x -CENTER_X;
                    offset_y = circles[x][1]+ROI.y -CENTER_Y;
                    obj = true;
#if log
                    printf("has obj\n");
#endif
                }
            }
        }
    }

    bool addNewPoints()
    {  
        return points[0].size() <= 1;
    }    

    static long long getSystemTime() {
#if defined(RI_LINUX)
        struct timeb t;
        ftime(&t);
        return 1000 * t.time + t.millitm;
#endif
        return 0;
    }

    char *getTime(){
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char *time =asctime(tm);
        std::string time_string(time);
        time_string.replace(time_string.find("\n"), sizeof(" ")-1, "");
        // time_string.replace("\n","");
        strcpy(time, time_string.c_str());
        return time;
    }

    void write_logFile(const char *message)
    {
#if defined(LOGFILE)
        if(first_open )
        {
            logFile = fopen( "camera.txt", "a" );
            if ( NULL == logFile ){
                RI_LOGI("Open failure1");
            }
            else
            {
                fprintf(logFile, "====================%s====================\n", getTime());
                fflush(logFile);
                first_open =false;
            }
        }
        else
        {
            fprintf(logFile, "[%s] %s", getTime(), message);
            fflush(logFile);
        }
#endif
    }

    static int camera_open()
    {
#if log
        RI_LOGI("Camera open ");
#endif
#if CAMERA_ON == ON
        if(!cap.isOpened()) {
            printf("Cam open 0 failed\n");
            write_logFile( "[ERROR]Cam open 0 failed");
            //fflush(logFile);
            exit(0);
        }

        if(!cap1.isOpened()) {
            printf("Cam open 1 failed\n");
            write_logFile( "[ERROR]Cam open 1 failed");
            //fflush(logFile);         
            //		exit(0);
        }

        cap.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
        cap.set(CV_CAP_PROP_FPS,30);

        cap1.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);
        cap1.set(CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
        cap1.set(CV_CAP_PROP_FPS,30);
#endif
        return 0;
    }

    int camera_close()
    {
#if CAMERA_ON == ON
        cvReleaseCapture(&cvcap);
        cap.release();
        cap1.release();
#endif
        return 0;
    }

    static int fcount=0;

    int sensor_clientSocket(const char* tarIp,int port,char* msg,int size)
    {
        int ret = 0;
        if(!sensor_client)
        {
            sensor_client = RiSocket_New();
            ret = RiSocket_Open_With_TimeOut(sensor_client, RI_SOCKET_AF_INET,
                RI_SOCKET_SOCK_STREAM, RI_SOCKET_IPPROTO_TCP, 1);
            if(ret < 0)
                goto error;

            ret = RiSocket_SetAddressIn(sensor_client, (ri_utf8 *)tarIp, port);
            ret = RiSocket_Connect(sensor_client);

            if (ret == RI_ERROR)
                goto error;
        }
        char vals[2];
        vals[0] = 0x5a;
        vals[1] = 0x5a;


        ret = RiSocket_Send(sensor_client, (ri_byte *)vals,2,MSG_NOSIGNAL);
        if(ret < 0)
            goto error;

        long sizearr[1];
        sizearr[0] = (long)size;
        ret = RiSocket_Send(sensor_client, (ri_byte *) sizearr,4,MSG_NOSIGNAL);
        if(ret < 0)
            goto error;

        ret = RiSocket_Send(sensor_client, (ri_byte *)msg,size,MSG_NOSIGNAL);
        if(ret < 0)
            goto error;

        return ret;
error:
#if log
        RI_LOGE("連線失敗");
#endif    
        // write_logFile("[ERROR]連線失敗");
        RiSocket_Close(sensor_client);
        RiSocket_Free(sensor_client);
        sensor_client = NULL;

        return ret;
    }

    void sendCmd(int server_name, const char *ip, int port, char cmd)
    {
        sensor_clientSocket(ip, port, &cmd, 1);     
    }

    DWORD WINAPI getPitch(void *)
    {
        char buff[5];
        int ret;

        while(1)
        {
            if ( camera_mode != MODE_STABLE )
            {
                RiThread_SleepUs(500);
                continue; 
            }
            sendCmd(SENSOR, SENSOR_IP, SENSOR_PORT, 'Z');
            ret = RiSocket_Recv(sensor_client, (ri_byte *)buff, 3, 0);
            if (ret <= 0)
            {
                RiThread_SleepUs(500);
                continue;
            }

            pitch_ang = 0;
            pitch_ang = (float)(((buff[0]<<8) + (unsigned char)buff[1]) * 360.0 / 50000.0);
            if (buff[2] == 0)
                pitch_ang *= -1;

            if (fabs(pitch_ang) < 1)
                pitch_ang = 0;
            //printf("pitch ====== %f\n",pitch_ang);
            RiThread_SleepUs(500);
        }

        CloseHandle(sensorThread);
        return 0;
    }

    void tracking(Mat &frame, Mat &output)
    {

        cvtColor(frame, gray, CV_BGR2GRAY); 
        frame.copyTo(output); 
        // 添加特征点

        if (addNewPoints()) 
        { 
            goodFeaturesToTrack(gray, features, MAX_COUNT, qLevel, minDist); 
            points[0].insert(points[0].end(), features.begin(), features.end());                
        } 

        if (prevGray.empty()) 
        { 
            gray.copyTo(prevGray); 
        }  

        //calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err); 
        // 去掉一些不好的特征点     



        // 显示特征点和运动轨迹

        for (size_t i=0; i<points[1].size(); i++) 
        { 

            circle(output, points[1][i], 3, Scalar(255, 0, 0), -1);

        }


        // 把当前跟踪结果作为下一此参考

        swap(points[1], points[0]); 
        swap(prevGray, gray); 



    }    

    void img_cb_josh(char* msg,int size, int id)
    {
        WaitForSingleObject(save_mutex, INFINITE);

        saveIndex ++;
        saveIndex %= 4;

#if 0
        if (saveBuffer[saveIndex] && (saveIndex != readIndex))//!saveBufLock)
        {
            printf("釋放沒用到的圖：%d\n",saveIndex);
            free(saveBuffer[saveIndex]->buffer);
            free(saveBuffer[saveIndex]);
            saveBuffer[saveIndex] = NULL;
        }
#endif
#if log
        printf("<===儲存新的圖: %d\n", id);

#endif

        if (saveBuffer[saveIndex] == NULL)
        {

            saveBuffer[saveIndex] = (imgbuf*)malloc(sizeof(imgbuf));
            saveBuffer[saveIndex]->size = 0;
            saveBuffer[saveIndex]->isSending = false;

            RI_LOGI("%d: New saveBuf[%d]......\n", id, saveIndex);


            //saveBuffer[saveIndex]->buffer = (char*)malloc(size);
        }

        //RI_LOGI("buff size: %d\n...........\n", saveBuffer[saveIndex]->size);

        if (saveBuffer[saveIndex]->size == 0)
        {
            saveBuffer[saveIndex]->buffer = (char*)malloc(size);

            //RI_LOGI("New buf: %d........\n", id);

        }
        else if (size > saveBuffer[saveIndex]->size)
        {
            saveBuffer[saveIndex]->buffer=(char*)realloc(saveBuffer[saveIndex]->buffer,sizeof(char)*size);

            //RI_LOGI("reNew buf: %d......\n", id);

        }

        if (!saveBuffer[saveIndex]->isSending)
        {
            ri_memcpy(saveBuffer[saveIndex]->buffer, msg, size);
            saveBuffer[saveIndex]->size = size;
        }


        //RI_LOGI("AAAA3: saveBuffer[%d] OK\n",saveIndex);		
        ReleaseMutex(save_mutex);
        return;
    }

    static void img_cb(char *img,int size, int id)
    {
        img_cb_josh(img,size, id);

        return;
    }

    static void* encCamera(void *arg)
    {

        int ss = 0;
        IMAGERAW imageRaw = *(IMAGERAW*)arg;
        Mat mat = imageRaw.mat;
        int id = imageRaw.id;

        //printf("%d Raw create +++++\n", id);
        if(mat.data)
        {
            //gettimeofday( &old, NULL );

            vector<uchar> img_temp_buf;
            std::vector<int> compression_params;
            compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
            compression_params.push_back(60);
            cv::imencode(".jpg", mat, img_temp_buf, compression_params);

            //gettimeofday( &current, NULL );

            int timeuse = 1000000 * ( current.tv_sec - old.tv_sec ) + current.tv_usec - old.tv_usec;

            //RI_LOGI("escape time: %d us\n", timeuse);

            char * imageBuf = ( char *) malloc(img_temp_buf.size());
            ri_memcpy(imageBuf, &img_temp_buf[0], img_temp_buf.size());
            ss = (int)img_temp_buf.size();
            void (*cb_ptr)(char *,int, int );
            cb_ptr =img_cb;
            (*cb_ptr)(imageBuf,ss, id);

            free(imageBuf);

        }

        //RiSemaphore_Post(sem);

        //RI_LOGI("%d Raw destory -----\n", id);

        CloseHandle(encCamera);
        return 0;
    }

    DWORD WINAPI sendBufferTo(void*)
    {
        struct timeval start, end;
        int ret = 0;

		memset(&start, 0, sizeof(timeval));
		memset(&end, 0, sizeof(timeval));

        while(cameraRunning)
        {
            if(!client )
            {

                RI_LOGE("<send th>: -----------------%d\n", send_th_cnt++);

                client=RiSocket_New();
                ret= RiSocket_Open_With_TimeOut(client, RI_SOCKET_AF_INET,
                    RI_SOCKET_SOCK_STREAM, RI_SOCKET_IPPROTO_TCP, 6);//tcp chang to udp

                if(ret<0)
                {

                    RI_LOGE("ERROR OPEN SOCKET AT clientTest");
                    //write_logFile("[ERROR]ERROR OPEN SOCKET AT clientTest");
                    RiSocket_Free(client);
                    client=NULL;
                    continue;
                }
                ret = RiSocket_SetAddressIn(client, (ri_utf8 *)img_send_ip, 3456);//3456
                ret = RiSocket_Connect(client);
                if (ret == RI_ERROR)
                {

                    RI_LOGE("connect fail");	
                    write_logFile("[ERROR]connect fail\n");
                    RiSocket_Free(client);
                    client=NULL;
                    continue;
                }
            }

            if (saveBuffer[readIndex] == NULL || saveIndex == readIndex)
            {
                continue;
            }

            saveBuffer[readIndex]->isSending = true;
            //gettimeofday( &start, NULL );

            //RI_LOGI("===>傳送的圖：%d\n", readIndex);			           
            imgbuf *sendBuffer = (imgbuf*)malloc(sizeof(imgbuf));
            sendBuffer->buffer = (char*)malloc(saveBuffer[readIndex]->size);
            ri_memcpy(sendBuffer->buffer, saveBuffer[readIndex]->buffer, saveBuffer[readIndex]->size);
            sendBuffer->size = saveBuffer[readIndex]->size;
            ri_byte vals[2] = {0x5a,0x5a};
            ret=RiSocket_Send(client, vals, 2, MSG_NOSIGNAL);//tcp chang to udp
            if(ret<0)
            {

                RI_LOGE("Send vals fail");
                //write_logFile("[ERROR]Send vals失敗\n");

                RiSocket_Close(client);
                RiSocket_Free(client);
                client=NULL;
            }

            long sizearr[1];
            sizearr[0]=(long)sendBuffer->size;
            ret=RiSocket_Send(client, (ri_byte *)sizearr, 4, MSG_NOSIGNAL);

            if(ret<0)
            {

                RI_LOGE("Send sizearr fail");
                //write_logFile("[ERROR]Send sizearr失敗\n");

                RiSocket_Close(client);
                RiSocket_Free(client);
                client=NULL;
            }
            // ret=RiSocket_SendTo(client, (ri_byte *)sendBuffer->buffer, sendBuffer->size, MSG_NOSIGNAL);
            //fprintf(logFile, "send buffer before:%s\n", getTime());
            ret=RiSocket_Send(client, (ri_byte *)saveBuffer[readIndex]->buffer, saveBuffer[readIndex]->size, 0);
            //fprintf(logFile, "send buffer after:%s\n", getTime());
            if(ret<0)
            {

                RI_LOGE("Send imagebuffer fail");
                write_logFile("[ERROR]Send imagebuffer fail\n");
                RiSocket_Close(client);
                RiSocket_Free(client);
                client=NULL;
            }

#if 0
            if (saveBuffer[readIndex]) {
                if (readIndex == saveIndex) {
                    printf("!!!!! double free buf %d !!!!!!\n", readIndex);
                    saveBufLock = true;
                }
                free(saveBuffer[readIndex]->buffer);
                free(saveBuffer[readIndex]);
                saveBuffer[readIndex] = NULL;
                saveBufLock = false;
            }
#endif
            free(sendBuffer->buffer);
            free(sendBuffer);

            saveBuffer[readIndex]->isSending = false;
            //gettimeofday( &end, NULL );
            int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;

            //RI_LOGI("===>傳送成功 (%d), %dus oooooo\n",readIndex, timeuse);
            readIndex ++;
            readIndex %= 4;

        }

        CloseHandle(sendBufferTo);
        return 0;
	} 

	DWORD WINAPI getImageBuffer(void *)
	{
		while(cameraRunning)
		{
			Mat mat = getMat(0);
			getMatArray.push_back(mat);			
		}
		return 0;
	}

	DWORD WINAPI processImageBuffer(void *)
	{
		while(cameraRunning)
		{
			if (getMatArray.size() > 0){
				RI_LOGI("MatArray.size = %d",getMatArray.size());
				Mat mat = getMatArray.back();
				getMatArray.clear();

				vector<uchar> img_temp_buf;
				std::vector<int> compression_params;
				compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
				compression_params.push_back(60);
				//mat to vector<uchar>
				WaitForSingleObject(image_buffer_mutex, INFINITE);
				cv::imencode(".jpg", mat, img_temp_buf, compression_params);
				imageBuffer = (char *)malloc(img_temp_buf.size());
				//vector<uchar> to char*
				ri_memcpy(imageBuffer, &img_temp_buf[0], img_temp_buf.size());
				image_buffer_size = (long)img_temp_buf.size();
				ReleaseMutex(image_buffer_mutex);
			}
		}
		return 0;
	}

	DWORD WINAPI sendImageBuffer(void *)
	{
		int ret = 0;
		while(cameraRunning)
		{
			if (imageBuffer != NULL)
			{
				printf("get new pic *********\n");
				if(!client )
				{
					RI_LOGI("buffer size = %ld",image_buffer_size);
					RI_LOGE("<send th>: -----------------%d\n", send_th_cnt++);

					client = RiSocket_New();
					ret = RiSocket_Open_With_TimeOut(client, RI_SOCKET_AF_INET,
						RI_SOCKET_SOCK_STREAM, RI_SOCKET_IPPROTO_TCP, 6);//tcp chang to udp

					if(ret<0)
					{
						RI_LOGE("ERROR OPEN SOCKET AT clientTest");
						//write_logFile("[ERROR]ERROR OPEN SOCKET AT clientTest");
						RiSocket_Free(client);
						client=NULL;
						continue;
					}
					ret = RiSocket_SetAddressIn(client, (ri_utf8 *)img_send_ip, 3456);//3456
					ret = RiSocket_Connect(client);
					if (ret == RI_ERROR)
					{

						RI_LOGE("connect fail");	
						write_logFile("[ERROR]connect fail\n");
						RiSocket_Free(client);
						client=NULL;
						continue;

					}
				}

				ri_byte vals[2] = {0x5a,0x5a};
				ret = RiSocket_Send(client, vals, 2, MSG_NOSIGNAL);//tcp chang to udp

				if(ret<0)
				{
					RI_LOGE("Send vals fail");
					//write_logFile("[ERROR]Send vals失敗\n");

					RiSocket_Close(client);
					RiSocket_Free(client);
					client=NULL;
				}


				long sizearr[1];
				sizearr[0] = image_buffer_size;//(long)img_temp_buf.size();
				ret = RiSocket_Send(client, (ri_byte *)sizearr, 4, MSG_NOSIGNAL);

				if(ret < 0)
				{
					RI_LOGE("Send sizearr fail");
					//write_logFile("[ERROR]Send sizearr失敗\n");

					RiSocket_Close(client);
					RiSocket_Free(client);
					client = NULL;
				}

				ret = RiSocket_Send(client, (ri_byte *)imageBuffer, sizearr[0], 0);
				//fprintf(logFile, "send buffer after:%s\n", getTime());
				if(ret < 0)
				{
					RI_LOGE("Send imagebuffer fail");
					write_logFile("[ERROR]Send imagebuffer fail\n");
					RiSocket_Close(client);
					RiSocket_Free(client);
					client = NULL;

				}   
				imageBuffer = NULL;
			}
		}
		return 0;
	}

    void joeDerFunction()
    {
        camera_open();
        //pthread_mutex_init(&image_buffer_mutex, NULL);
		image_buffer_mutex = CreateMutex(NULL, false, NULL);
        /*pthread_t getImageThread;
        pthread_t processImageThread;
        pthread_t sendImageThread;*/

        CreateThread(NULL/*&getImageThread*/, 0, getImageBuffer, NULL, 0, NULL);
        CreateThread(NULL/*&processImageThread*/, 0, processImageBuffer, NULL, 0, NULL);
        CreateThread(NULL/*&sendImageThread*/, 0, sendImageBuffer, NULL, 0, NULL);

    }

    DWORD WINAPI runingCamera(void *)
    {

        RI_LOGI("runingCamera...");
        int i = 0;
        int ret = 0;
        sem = RiSemaphore_New(4);
        RiLock_t * glock;
        glock = RiLock_New();
        Mat tmat[4];
        IMAGERAW imgRaw[4];
        int firstTime = 1;
        HANDLE saveThread[4];
        save_mutex = CreateMutex(NULL, false, NULL);
        Mat frame;
        camera_open();

        while(cameraRunning)
        {
            //printf("get new pic *********%d\n",i);
            imgRaw[0].id = 0;//(i%4);

            //gettimeofday( &old, NULL );
            imgRaw[0].mat = getMat(0);
#if 1
            vector<uchar> img_temp_buf;
            std::vector<int> compression_params;
            compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
            compression_params.push_back(60);
            //mat to vector<uchar>
            cv::imencode(".jpg", imgRaw[0].mat, img_temp_buf, compression_params);
            char * imageBuf = ( char *) malloc(img_temp_buf.size());
            //vector<uchar> to char*
            ri_memcpy(imageBuf, &img_temp_buf[0], img_temp_buf.size());   

            if(!client )
            {

                RI_LOGE("<send th>: -----------------%d\n", send_th_cnt++);

                client = RiSocket_New();
                ret = RiSocket_Open_With_TimeOut(client, RI_SOCKET_AF_INET,
                    RI_SOCKET_SOCK_STREAM, RI_SOCKET_IPPROTO_TCP, 6);//tcp chang to udp

                if(ret<0)
                {

                    RI_LOGE("ERROR OPEN SOCKET AT clientTest");
                    //write_logFile("[ERROR]ERROR OPEN SOCKET AT clientTest");
                    RiSocket_Free(client);
                    client=NULL;
                    continue;
                }
                ret = RiSocket_SetAddressIn(client, (ri_utf8 *)img_send_ip, 3456);//3456
                ret = RiSocket_Connect(client);
                if (ret == RI_ERROR)
                {

                    RI_LOGE("connect fail");	
                    write_logFile("[ERROR]connect fail\n");
                    RiSocket_Free(client);
                    client=NULL;
                    continue;
                }
            }

            ri_byte vals[2] = {0x5a,0x5a};
            ret = RiSocket_Send(client, vals, 2, MSG_NOSIGNAL);//tcp chang to udp
            if(ret<0)
            {

                RI_LOGE("Send vals fail");
                //write_logFile("[ERROR]Send vals失敗\n");

                RiSocket_Close(client);
                RiSocket_Free(client);
                client=NULL;
            }

            long sizearr[1];
            sizearr[0] = (long)img_temp_buf.size();
            ret = RiSocket_Send(client, (ri_byte *)sizearr, 4, MSG_NOSIGNAL);

            if(ret < 0)
            {

                RI_LOGE("Send sizearr fail");
                //write_logFile("[ERROR]Send sizearr失敗\n");

                RiSocket_Close(client);
                RiSocket_Free(client);
                client = NULL;
            }

            ret = RiSocket_Send(client, (ri_byte *)imageBuf, sizearr[0], 0);
            //fprintf(logFile, "send buffer after:%s\n", getTime());
            if(ret < 0)
            {

                RI_LOGE("Send imagebuffer fail");
                write_logFile("[ERROR]Send imagebuffer fail\n");
                RiSocket_Close(client);
                RiSocket_Free(client);
                client = NULL;
            }     

            //gettimeofday( &current, NULL );
            //int timeuse = 1000000 * ( current.tv_sec - old.tv_sec ) + current.tv_usec - old.tv_usec;
            //printf("time use: %d\n", timeuse);
#endif


#if 0
            int r = RiSemaphore_Wait(sem);
            pthread_create(&saveThread[0], NULL, encCamera, &(imgRaw[0]));//tmat[i%4]));
            if (firstTime == 1)
            {
                pthread_create(&sendThread, NULL, sendBufferTo,NULL);
                firstTime = 0;
            }
#endif
        }

        for(i=0; i<4; i++)
        {
            WaitForSingleObject(saveThread[i], INFINITE);
        }

        RI_LOGI("free sem");
        RiSemaphore_Free(sem);
        RI_LOGI("free sem OK");
        RiLock_Free(glock);
        RI_LOGI("runingCamera...OK");
        CloseHandle(save_mutex);
        CloseHandle(camThread);
        return 0;
    }
    //0407 add
    DWORD WINAPI piConnects(void *arg)
    {
        RiSocket_t *sockClient;
        sockClient=(RiSocket_t *)arg;

        int ret = 0, cali_x, cali_y;
        char buffer[2048];
        //0401 add
        char header[2];
        char size[4];
        while(1)
        {
            ret = RiSocket_Recv(sockClient, (ri_byte *) header, sizeof(header), 0);

            if (ret <= 0)
                goto exit;
            if(header[0]==0x5a && header[1]==0x5a)
            {
                RI_LOGI("get header OK\n");            

                ret = RiSocket_Recv(sockClient, (ri_byte *) size, sizeof(size), 0);
                if (ret <= 0)
                    goto exit;

                long *sizeptr = (long *)(&size[0]);
                long getsize =* sizeptr;
                RI_LOGI("get Size OK,%ld bytes, %hhd %hhd %hhd %hhd",getsize, size[0], size[1], size[2], size[3]);


                ret = RiSocket_Recv(sockClient, (ri_byte *)buffer, getsize, 0);
                if (ret <= 0)
                {
                    RI_LOGI("size not match xxxxx\n");
                    write_logFile("size not match xxxxx\n");
                    goto exit;	
                }		         
                RI_LOGI("\nrecv message: %s\n", buffer);

                RI_LOGI("cmd: %c\n", buffer[0]);
                switch(buffer[0])
                {
                case 'A':// Camera controller Zoom in
                    printf("Camera Zoom in");
#if defined(RI_LINUX)
                    write(fd_camera_controller, &camera_cmd[ZOOM_TELE], 7);
#endif
                    break;
                case 'a':// Camera controller Zoom out
                    printf("Camera Zoom out\n");
#if defined(RI_LINUX)
                    write(fd_camera_controller, &camera_cmd[ZOOM_WIDE], 7);
#endif
                    break;
                case 'B':// motor
                case 'b':// motor
                case 'C':// motor
                case 'c':// motor
                    break;
                case 'D':
                    break;
                case 'd':// Camera controller stop
                    printf("Camera Stop\n");
#if defined(RI_LINUX)
                    write(fd_camera_controller, &camera_cmd[STOP], 7);
#endif
                    break;
                case 'E':// sensor
                    break;
                case 'e'://??原本的case r
                    printf("Focus rect\n");
                    focus_rect_X1 = (buffer[1]<<8) | buffer[2];
                    focus_rect_Y1 = (buffer[3]<<8) | buffer[4];
                    focus_rect_X2 = (buffer[5]<<8) | buffer[6];
                    focus_rect_Y2 = (buffer[7]<<8) | buffer[8];
                    selection.x = focus_rect_X1;
                    selection.y = focus_rect_Y1;
                    selection.width = focus_rect_X2 - focus_rect_X1;
                    selection.height = focus_rect_Y2 - focus_rect_Y1;

                    selection &= Rect(0, 0, WIDTH, HEIGHT);
                    trackObject = -1;
                    break;
                case 'F':
                    cali = true;
                    cali_x = (buffer[1]<<8) + (unsigned char)buffer[2];
                    cali_y = (buffer[4]<<8) + (unsigned char)buffer[5];
                    //printf("cali x: %d, cali y: %d\n", cali_x, cali_y);
                    if (buffer[3] == 0)
                    {
                        //cali_x *= -1;
                        img_start_x = 0;
                        img_end_x = cali_x;
                    }
                    else {
                        img_end_x = 0;
                        img_start_x = cali_x;
                    }

                    if (buffer[6] == 0)
                    {
                        //cali_y *= -1;
                        img_start_y = 0;
                        img_end_y = cali_y;
                    }
                    else {
                        img_end_y = 0;
                        img_start_y = cali_y;
                    }

                    break;
                case 'f':
                    //printf("reset cali img\n");
                    cali = false;
                    break;
                case 'G':
                    printf("camera zoom near\n");
#if defined(RI_LINUX)
                    write(fd_camera_controller, &camera_cmd[FOCUS_NEAR], 7);
#endif
                    break;
                case 'g'://???
                    break;
                case 'H':// motor
                    break;
                case 'I':// motor
                    break;
                case 'J':
                    printf("camera zoom far\n");
#if defined(RI_LINUX)
                    write(fd_camera_controller, &camera_cmd[FOCUS_FAR], 7);
#endif
                    break;
                case 'L':// motor
                case 'l':// motor
                    break;
                    break;
                case 'O':
                    isColor = !isColor;
                    break;
                case 'N':
                    printf("detect on\n");
                    detectFunction = true;
                    break;
                case 'n':
                    printf("detect off\n");
                    detectFunction = false;
                    break;
                case 'P'://2015-10-29從QT取得框選的座標位置
                    x_rect_1 = (int)((buffer[1] << 8) + (unsigned char)buffer[2]) * 640 / 1366;
                    y_rect_1 = (int)((buffer[3] << 8) + (unsigned char)buffer[4]) * 360 / 768;
                    x_rect_2 = (int)((buffer[5] << 8) + (unsigned char)buffer[6]) * 640 / 1366;
                    y_rect_2 = (int)((buffer[7] << 8) + (unsigned char)buffer[8]) * 360 / 768;
                    match_error_count = 0;
                    printf("case p (%d, %d) (%d, %d)\n", x_rect_1, y_rect_1, x_rect_2, y_rect_2);
                    point1 = Point2f((float)x_rect_1, (float)y_rect_1);
                    point3 = Point2f((float)x_rect_2, (float)y_rect_2);
                    point = Point2f((point1.x+point3.x)/2, (point1.y+point3.y)/2);
                    ROI = Rect((int)point1.x ,(int)point1.y, (int)(point3.x-point1.x), (int)(point3.y-point1.y));
                    hasObj = true;
                    hasPattern = true;
                    break;
                case 'p':// motor
                case 'R':// motor
                case 'r':// motor
                    break;
                case 'S':
                    printf("case STABLE\n");
                    camera_mode = MODE_STABLE;
                    break;
                case 's':
                    printf("case CAMERA_NONE\n");
                    camera_mode = MODE_NONE;
                    break;
                case 'T':// motor
                case 't':// motor
                    break;
                case 'Y':// motor
                    break;
                case 'Z':// sensor
                    break;
                case 'z':						
                    system("echo 205 | sudo -S poweroff");
                    break;
                }
                //fflush(logFile);

            }
            else
            {
                RI_LOGI("header is not 0x5a0x5a..skip");
            }

        }

exit:
        CloseHandle(conThread);
        //fflush(logFile);
        return NULL;
    }

	
    DWORD WINAPI piServerThread(void *)
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
            //sprintf(logFIle_message, "RiSocket_Init = %d\n", ret);
            //write_logFile(logFIle_message);
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
                // sprintf(logFIle_message, "RiSocket_SetAddressIn = %d\n", ret);
                write_logFile(logFIle_message);
                return NULL;
            }

            ret = RiSocket_Bind(localSocket);
            if (ret <= 0)
            {

                RI_LOGI("RiSocket_Bind = %d\n", ret);
                // sprintf(logFIle_message, "RiSocket_Bind = %d\n", ret);
                write_logFile(logFIle_message);

                localServerPort++;
            }
            else
            {

                RI_LOGE("localServer port open： = %d\n", localServerPort);
                break;
            }
        }
        //fflush(logFile);
        ret = RiSocket_Listen(localSocket, backLog);
        if (ret <= 0)
        {

            RI_LOGI("RiSocket_Listen = %d\n", ret);
            //sprintf(logFIle_message, "RiSocket_Listen = %d\n", ret);
            write_logFile(logFIle_message);

            return NULL;
        }

        while (localSocket)
        {

            RI_LOGI("server RUN...\n");
            //write_logFile( "server RUN...\n");

            sockClient = RiSocket_Accept(localSocket);

            RI_LOGI("server Accept");
            if (!localSocket)
            {	
                // write_logFile( "[ERROR]local server中斷B...\n");
                RI_LOGI("local server disconnect B...\n");
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
                write_logFile( "[ERROR]NULL localSocket\n");
            }


            RI_LOGI("Before RiSocket_Recv_header");
            //pthread_t conThread;

            conThread = CreateThread(NULL/*&conThread*/, NULL, piConnects, sockClient, 0, NULL);
            RI_LOGI("server ONE ROUND");

            continue;

        }
        RI_LOGI("RiSocket_Close");
        CloseHandle(sendThread);
        return 0;

    }

    //static pthread_t camThread;
	
    
    static int camera_initLocalServer2(int myLocalServerPort)
    {
        localServerPort = myLocalServerPort;

        //pthread_t sendThread;
        //pthread_t sensorThread;
		
        sendThread = CreateThread(NULL/*&sendThread*/, 0, piServerThread, NULL, 0, NULL);

        //joeDerFunction();
        camThread = CreateThread(NULL/*&camThread*/, 0, runingCamera, NULL, 0, NULL);
        sensorThread = CreateThread(NULL/*&sensorThread*/, 0, getPitch, NULL, 0, NULL);
#if defined(RI_LINUX)
        fd_camera_controller = serialport_init("/dev/ttyUSB0", 9600);
        if( fd_camera_controller == -1 )
        {
            serialport_close(fd_camera_controller);
            printf("無法開啟相機控制序列埠\n");
            //write_logFile( "[ERROR]無法開啟相機控制序列埠\n");

        }
        else {
            serialport_flush(fd_camera_controller);
            printf("相機控制模組正常\n");
            write(fd_camera_controller, &camera_cmd[ZOOM_WIDE], 7);	


        }

        RI_LOGE("initLocalServer --");
#endif
        return RI_OK;
    }

    static int camera_clientSocket(char* tarIp,int port,char* msg,int size)
    {
        RiLock_Lock(glock);
        int ret=0;
        if(!clientsocket)
        {
            clientsocket=RiSocket_New();
            ret= RiSocket_Open_With_TimeOut(clientsocket, RI_SOCKET_AF_INET,
                RI_SOCKET_SOCK_STREAM, RI_SOCKET_IPPROTO_TCP, 6);

            if(ret<0)
            {

                RI_LOGE("ERROR OPEN SOCKET AT clientTest");
                //write_logFile( "[ERROR]ERROR OPEN SOCKET AT clientTest\n");
                RiSocket_Free(clientsocket);
                clientsocket=NULL;
                RiLock_Unlock(glock);
                return -1;
            }
            ret = RiSocket_SetAddressIn(clientsocket, (ri_utf8 *)tarIp, port);
            ret = RiSocket_Connect(clientsocket);

            if (ret == RI_ERROR)
            {

                RI_LOGE("connect fail");
                //write_logFile( "[ERROR]連線失敗\n");


                RiSocket_Free(clientsocket);
                clientsocket=NULL;
                RiLock_Unlock(glock);
                return -1;
            }
        }
        char vals[2];
        vals[0]=0x5a;
        vals[1]=0x5a;
        ret=RiSocket_Send(clientsocket, (ri_byte *)vals,2,MSG_NOSIGNAL);

        long sizearr[1];
        sizearr[0]=(long)size;
        ret=RiSocket_Send(clientsocket, (ri_byte *) sizearr,4,MSG_NOSIGNAL);

        ret=RiSocket_Send(clientsocket, (ri_byte *)msg,size,MSG_NOSIGNAL);

        if(ret<0)
        {
            RiSocket_Close(clientsocket);
            RiSocket_Free(clientsocket);
            clientsocket=NULL;

        }
        RiLock_Unlock(glock);
        return ret;
    }


#ifdef __cplusplus
}
#endif
/*

#ifdef __cplusplus
}
#endif
*/